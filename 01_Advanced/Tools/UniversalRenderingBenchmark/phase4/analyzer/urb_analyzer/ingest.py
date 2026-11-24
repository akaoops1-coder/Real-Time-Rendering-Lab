"""Read-only, versioned Unreal CSV/Manifest ingestion.

Only exact UE 5.8 RTR timing columns are mapped. Invalid samples retain their
frame position as None; they are never removed, imputed, or replaced by a pass.
Metric failures are separate from structural/provenance failures so intact CPU
measurements can remain available diagnostically when GPU timing is absent.
"""
from __future__ import annotations

import csv
import hashlib
import io
import json
import math
from pathlib import Path
import re
import stat
from typing import Any

METRICS = ("FrameTime", "GameThreadTime", "RenderThreadTime", "GPUTime")
MAPPING_VERSION = "UE5.8-RTR-CSV-v1"
SUPPORTED_ENGINE = (5, 8)
_META_KEY = re.compile(r"^\[([^\[\]]+)\]$")
_ENGINE = re.compile(r"^5\.8\.\d+(?:-|$)")
_SHA256 = re.compile(r"^[0-9a-fA-F]{64}$")
_MAX_BYTES = 512 * 1024 * 1024


def _sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def _integer(value: Any, minimum: int = 0) -> bool:
    return isinstance(value, int) and not isinstance(value, bool) and value >= minimum


def _finite(value: Any) -> bool:
    return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value)


def _near(actual: Any, expected: Any) -> bool:
    try:
        a, b = float(actual), float(expected)
        return math.isfinite(a) and math.isfinite(b) and math.isclose(a, b, rel_tol=1e-6, abs_tol=1e-5)
    except (ValueError, TypeError, OverflowError):
        return False


def _reparse(path: Path) -> bool:
    info = path.lstat()
    return stat.S_ISLNK(info.st_mode) or bool(getattr(info, "st_file_attributes", 0) & 0x400)


def _safe_path(root: Path, relative: str) -> Path:
    candidate = root / relative
    for part in [root, *list(candidate.parents)[:len(Path(relative).parts) - 1], candidate]:
        if part.exists() and _reparse(part):
            raise ValueError("REPARSE_POINT_NOT_SUPPORTED: " + relative)
    if not candidate.resolve().is_relative_to(root.resolve()):
        raise ValueError("INPUT_PATH_ESCAPES_RUN_DIRECTORY: " + relative)
    return candidate


def _read_file(root: Path, relative: str, hashes: dict[str, str]) -> bytes:
    path = _safe_path(root, relative)
    if not path.is_file():
        raise ValueError("FILE_MISSING: " + relative)
    if path.stat().st_size > _MAX_BYTES:
        raise ValueError("FILE_EXCEEDS_512_MIB_READER_LIMIT: " + relative)
    data = path.read_bytes()
    hashes[relative] = _sha(data)
    return data


def _json_pairs(items: list[tuple[str, Any]]) -> dict:
    result = {}
    for key, value in items:
        if key in result:
            raise ValueError("DUPLICATE_JSON_KEY: " + key)
        result[key] = value
    return result


def _read_json(root: Path, name: str, hashes: dict[str, str]) -> dict:
    data = _read_file(root, name, hashes)
    value = json.loads(data.decode("utf-8-sig"), object_pairs_hook=_json_pairs,
                       parse_constant=lambda value: (_ for _ in ()).throw(ValueError("NONFINITE_JSON_NUMBER: " + value)))
    if not isinstance(value, dict):
        raise ValueError("JSON_OBJECT_REQUIRED: " + name)
    def validate_text(item):
        if isinstance(item, str):
            item.encode("utf-8")
        elif isinstance(item, dict):
            for key, child in item.items():
                validate_text(key)
                validate_text(child)
        elif isinstance(item, list):
            for child in item:
                validate_text(child)
    # JSON permits escaped surrogate code units syntactically; native UTF-8
    # provenance and portable output require well-formed Unicode strings.
    validate_text(value)
    return value


def _empty_csv() -> dict:
    return {"sha256": None, "mapping_version": MAPPING_VERSION,
            "metric_columns": {}, "samples": {m: [] for m in METRICS},
            "metric_errors": {m: [] for m in METRICS},
            "metric_available": {m: False for m in METRICS},
            "metric_valid_frames": {m: 0 for m in METRICS},
            "valid_frames": 0, "data_rows": 0, "errors": [], "warnings": [],
            "metadata": {}, "header_evolution": {}}


def _parse_csv_bytes(data: bytes) -> dict:
    result = _empty_csv()
    result["sha256"] = _sha(data)
    errors = result["errors"]
    try:
        # UE's commandline footer uses non-RFC nested quotes. Its recorded CSV
        # dialect is supported, while row/schema/metadata checks remain strict.
        rows = list(csv.reader(io.StringIO(data.decode("utf-8-sig"), newline="")))
    except (UnicodeError, csv.Error) as error:
        errors.append("CSV_DECODE_ERROR: " + str(error))
        return result
    if not rows or not rows[0]:
        errors.append("CSV_EMPTY_OR_HEADER_MISSING")
        return result
    initial = rows[0]
    for metric in METRICS:
        count = initial.count(metric)
        if count != 1:
            result["metric_errors"][metric].append("EXACT_TIMING_HEADER_COUNT: expected 1, found " + str(count))
        else:
            result["metric_columns"][metric] = initial.index(metric)
    headers = [(i, row) for i, row in enumerate(rows)
               if i == 0 or row == initial or sum(m in row for m in METRICS) >= 2
               or (row[:len(initial)] == initial and any(m in row for m in METRICS))]
    header_indexes = {i for i, _ in headers}
    final = headers[-1][1]
    append_only = len(final) >= len(initial) and final[:len(initial)] == initial
    for i, header in headers:
        if len(header) < len(initial) or header != final[:len(header)]:
            append_only = False
            errors.append("CSV_HEADER_REMAP_AT_ROW: " + str(i + 1))
        for metric, column in result["metric_columns"].items():
            if header.count(metric) != 1 or header.index(metric) != column:
                append_only = False
                errors.append("CSV_REQUIRED_COLUMN_MOVED: " + metric)
    if not append_only:
        errors.append("CSV_HEADER_EXPANSION_NOT_PROVEN_APPEND_ONLY")
    previous_width = len(initial)
    footer_seen = False
    widths = {}
    for i, row in enumerate(rows[1:], 2):
        if i - 1 in header_indexes:
            if footer_seen:
                errors.append("CSV_HEADER_AFTER_METADATA: row " + str(i))
            continue
        if not row or all(not cell for cell in row):
            continue
        if row[0].startswith("["):
            footer_seen = True
            if len(row) % 2:
                errors.append("CSV_METADATA_ODD_FIELD_COUNT: row " + str(i))
            for j in range(0, len(row) - 1, 2):
                match = _META_KEY.fullmatch(row[j])
                if not match:
                    errors.append("CSV_METADATA_INVALID_KEY: row " + str(i))
                    continue
                key = match.group(1).lower()
                if key in result["metadata"]:
                    errors.append("CSV_METADATA_DUPLICATE_KEY: " + key)
                else:
                    result["metadata"][key] = row[j + 1]
            continue
        result["data_rows"] += 1
        widths[str(len(row))] = widths.get(str(len(row)), 0) + 1
        if footer_seen:
            errors.append("CSV_DATA_AFTER_METADATA: row " + str(i))
        valid_shape = append_only and len(initial) <= len(row) <= len(final) and len(row) >= previous_width
        if not valid_shape:
            errors.append("CSV_ROW_SHAPE_INVALID: row " + str(i))
        previous_width = max(previous_width, len(row))
        row_values = {}
        for metric in METRICS:
            value = None
            column = result["metric_columns"].get(metric)
            if column is not None:
                if valid_shape and column < len(row):
                    try:
                        number = float(row[column])
                        if not math.isfinite(number) or number < 0 or (metric == "GPUTime" and number <= 0):
                            raise ValueError("non-finite or invalid sign")
                        value = number
                    except (ValueError, OverflowError):
                        result["metric_errors"][metric].append("INVALID_TIMING_VALUE_AT_ROW: " + str(i))
                else:
                    result["metric_errors"][metric].append("TIMING_VALUE_UNREADABLE_AT_ROW: " + str(i))
            result["samples"][metric].append(value)
            row_values[metric] = value
            if value is not None:
                result["metric_valid_frames"][metric] += 1
        if all(value is not None for value in row_values.values()):
            result["valid_frames"] += 1
    if not footer_seen:
        errors.append("CSV_METADATA_FOOTER_MISSING")
    if result["metadata"].get("hasheaderrowatend") == "1" and len(headers) < 2:
        errors.append("CSV_FINAL_HEADER_MISSING")
    if result["data_rows"] == 0:
        errors.append("CSV_HAS_NO_DATA_FRAMES")
    for metric in METRICS:
        result["metric_available"][metric] = not result["metric_errors"][metric] and result["data_rows"] > 0
    result["header_evolution"] = {"initial_columns": len(initial), "final_columns": len(final),
                                  "append_only_verified": append_only, "header_rows": len(headers),
                                  "data_column_counts": widths}
    return result


def parse_capture_csv(path: Path) -> dict:
    """Parse one CSV independently; load_run additionally checks provenance."""
    path = Path(path)
    result = _empty_csv()
    try:
        if _reparse(path):
            raise ValueError("REPARSE_POINT_NOT_SUPPORTED")
        if path.stat().st_size > _MAX_BYTES:
            raise ValueError("FILE_EXCEEDS_512_MIB_READER_LIMIT")
        return _parse_csv_bytes(path.read_bytes())
    except (OSError, ValueError) as error:
        result["errors"].append("CSV_READ_ERROR: " + str(error))
        return result


def _verify_action(description: dict, readback: Any, variant: str) -> list[str]:
    errors = []
    if not isinstance(readback, dict) or readback.get("verified") is not True:
        return ["ACTION_READBACK_NOT_VERIFIED"]
    suffix = "B" if variant == "B" else "A"
    if readback.get("actualVariant") != variant:
        errors.append("ACTION_READBACK_VARIANT_MISMATCH")
    action = description.get("actionType")
    if action == "MaterialSwap":
        expected = description.get("variant" + suffix)
        if not expected or any(readback.get(k) != expected for k in ("actualMaterial", "expectedMaterial")):
            errors.append("MATERIAL_READBACK_MISMATCH")
    elif action in ("ScalarParameter", "ConsoleVariable"):
        expected = description.get("value" + suffix)
        if not _finite(expected) or not _near(readback.get("actualValue"), expected) or not _near(readback.get("expectedValue"), expected):
            errors.append("ACTION_VALUE_READBACK_MISMATCH")
        if action == "ScalarParameter":
            if readback.get("parameter") != description.get("parameter") or not description.get("dynamicMaterialObjectID") or readback.get("dynamicMaterialObjectID") != description.get("dynamicMaterialObjectID") or readback.get("actualMaterial") != description.get("dynamicMaterial"):
                errors.append("SCALAR_PARAMETER_OR_REUSED_DMI_MISMATCH")
        elif readback.get("actualPriority") != readback.get("expectedPriority") or readback.get("actualTag") != readback.get("expectedTag"):
            errors.append("CVAR_PRIORITY_OR_TAG_READBACK_MISMATCH")
    elif action == "ActorVisibility":
        original = description.get("original", {})
        actor_scope = description.get("visibilityScope") == "Actor"
        actor_hidden = description.get("hiddenInGame" + suffix) if actor_scope else original.get("actorHiddenInGame")
        if readback.get("actorHiddenInGame") is not actor_hidden or not isinstance(actor_hidden, bool):
            errors.append("ACTOR_HIDDEN_READBACK_MISMATCH")
        originals = {item.get("component"): item for item in original.get("components", []) if isinstance(item, dict)}
        current = readback.get("components", [])
        if not isinstance(current, list) or not originals or len(current) != len(originals):
            return errors + ["VISIBILITY_COMPONENT_SET_MISMATCH"]
        names = [item.get("component") for item in current if isinstance(item, dict)]
        if len(set(names)) != len(current) or set(names) != set(originals):
            errors.append("VISIBILITY_COMPONENT_SET_MISMATCH")
        for item in current:
            if not isinstance(item, dict):
                errors.append("VISIBILITY_COMPONENT_RECORD_INVALID")
                continue
            before = originals.get(item.get("component"), {})
            visible = before.get("visibleFlag") if actor_scope else description.get("visible" + suffix)
            hidden = before.get("hiddenInGame") if actor_scope else description.get("hiddenInGame" + suffix)
            if item.get("visibleFlag") is not visible or item.get("hiddenInGame") is not hidden or item.get("valid") is not True or item.get("registered") is not True or item.get("shouldRender") is not bool(visible and not hidden and not actor_hidden):
                errors.append("VISIBILITY_RENDER_READBACK_MISMATCH")
            for key, policy in (("castShadow", "DisableShadows"), ("castHiddenShadow", "DisableHiddenShadows")):
                if key in before:
                    expected = False if description.get("shadowPolicy") == policy else before[key]
                    if item.get(key) is not expected:
                        errors.append("SHADOW_READBACK_MISMATCH: " + key)
    else:
        errors.append("ACTION_DESCRIPTION_UNSUPPORTED")
    return errors


def _validate_restoration(manifest: dict, legacy: bool) -> list[str]:
    errors = []
    restoration = manifest.get("restoration", {})
    if not isinstance(restoration, dict):
        return ["RESTORATION_RECORD_INVALID"]
    for key in (("material" if legacy else "action"), "camera", "cvarsAndPriorities", "resolution"):
        if restoration.get(key) is not True:
            errors.append("RESTORATION_UNVERIFIED: " + key)
    if not legacy and restoration.get("runtimeChangesMade"):
        action = manifest.get("actionRestoration", {})
        if not isinstance(action, dict) or action.get("restored") is not True:
            errors.append("ACTION_RESTORATION_UNVERIFIED")
        env = manifest.get("environmentRestoration", [])
        if not isinstance(env, list) or len(env) < 6 or any(not isinstance(item, dict) or item.get("restored") is not True or item.get("originalValue") != item.get("actualValueString") or item.get("originalPriority") != item.get("actualPriority") or item.get("originalTag") != item.get("actualTag") for item in env):
            errors.append("ENVIRONMENT_RESTORATION_UNVERIFIED")
    return errors


def load_run(path: Path) -> dict:
    """Load a run without writing any source file; all failures become data."""
    root = Path(path).expanduser().absolute()
    result = {"source_dir": str(root), "mapping_version": MAPPING_VERSION,
              "unsupported_schema": False, "manifest": {}, "run_id": "", "test_id": "",
              "captures": [], "errors": [], "warnings": [], "source_hashes": {},
              "metric_errors": {m: [] for m in METRICS}}
    errors, warnings, hashes = result["errors"], result["warnings"], result["source_hashes"]
    try:
        if not root.is_dir() or _reparse(root):
            raise ValueError("RUN_DIRECTORY_MISSING_OR_REPARSE_POINT")
        manifest = completion = None
        for name in ("Manifest.json", "Completion.json"):
            try:
                value = _read_json(root, name, hashes)
                if name == "Manifest.json":
                    manifest = value
                else:
                    completion = value
            except (OSError, ValueError, UnicodeError) as error:
                errors.append(name + ": " + str(error))
        selected = completion if completion is not None else manifest
        if selected is None:
            return result
        for name in ("Execution.log", "SourceContentIndex.json"):
            try:
                if (root / name).exists():
                    _read_file(root, name, hashes)
                elif name == "Execution.log":
                    warnings.append("EXECUTION_LOG_NOT_PRESENT")
            except (OSError, ValueError) as error:
                errors.append(name + ": " + str(error))
        result["manifest"] = selected
        raw_run_id, raw_test_id = selected.get("runID", ""), selected.get("testID", "")
        result["run_id"] = raw_run_id if isinstance(raw_run_id, str) else ""
        result["test_id"] = raw_test_id if isinstance(raw_test_id, str) else ""
        if not result["run_id"] or not result["test_id"]:
            errors.append("RUN_AND_TEST_IDENTIFIERS_REQUIRED")
        if manifest is not None and completion is not None and manifest != completion:
            errors.append("MANIFEST_COMPLETION_MISMATCH")
        if not isinstance(selected.get("engineVersion"), str) or not _ENGINE.match(selected["engineVersion"]):
            result["unsupported_schema"] = True
            errors.append("UNSUPPORTED_ENGINE_MAPPING: UE 5.8 is the only validated CSV mapping")
        schema_version = selected.get("schemaVersion")
        if schema_version is not None and (not _integer(schema_version) or schema_version != 3):
            result["unsupported_schema"] = True
            errors.append("UNSUPPORTED_SOURCE_SCHEMA_VERSION: " + str(schema_version))
        execution = selected.get("status")
        result["execution_status"] = execution
        result["measurement_status"] = selected.get("measurementStatus")
        if execution != "COMPLETED":
            errors.append("RUN_NOT_COMPLETED: " + str(execution))
        records = selected.get("captures", [])
        if not isinstance(records, list):
            errors.append("CAPTURE_LIST_INVALID")
            return result
        legacy = "actionType" not in selected
        result["legacy_phase1"] = legacy
        if legacy:
            warnings.append("LEGACY_PHASE1_MATERIALSWAP: Action configuration and environment fingerprint were not recorded")
        errors.extend(_validate_restoration(selected, legacy))
        if execution == "COMPLETED":
            expected_count = selected.get("expectedCaptures")
            if not _integer(expected_count, 1) or expected_count != len(records):
                errors.append("EXPECTED_CAPTURE_COUNT_MISMATCH")
            for field in ("captureFrames", "warmupFrames", "repeatCount", "targetFPSBudgetOnly"):
                if not _integer(selected.get(field), 1):
                    errors.append("CAPTURE_CONFIGURATION_INVALID: " + field)
            if not _finite(selected.get("screenPercentageRequested")) or selected["screenPercentageRequested"] <= 0:
                errors.append("SCREEN_PERCENTAGE_INVALID")
        seen_indexes, seen_files, seen_ids = set(), set(), set()
        mode_groups = []
        for position, record in enumerate(records):
            capture = _empty_csv()
            capture.update({"capture_index": record.get("captureIndex") if isinstance(record, dict) else None,
                            "variant": record.get("variant") if isinstance(record, dict) else None,
                            "mode": record.get("mode") if isinstance(record, dict) else None,
                            "status": record.get("status") if isinstance(record, dict) else None,
                            "file": record.get("file", "") if isinstance(record, dict) else "",
                            "record": record, "actual_action_variant": None, "capture_id": None})
            result["captures"].append(capture)
            ce = capture["errors"]
            if not isinstance(record, dict):
                ce.append("CAPTURE_RECORD_INVALID")
                continue
            index, variant, mode, filename = capture["capture_index"], capture["variant"], capture["mode"], capture["file"]
            if not _integer(index) or index != position or index in seen_indexes:
                ce.append("CAPTURE_INDEX_INVALID_OR_DUPLICATED")
            if isinstance(index, (str, int, float, bool, type(None))):
                seen_indexes.add(index)
            if variant not in ("A", "B") or mode not in ("Benchmark", "Calibration"):
                ce.append("VARIANT_OR_MODE_INVALID")
            actual = "A" if mode == "Calibration" else variant
            capture["actual_action_variant"] = record.get("actualActionVariant", actual)
            if capture["actual_action_variant"] != actual:
                ce.append("ACTUAL_ACTION_VARIANT_MISMATCH")
            if not mode_groups or mode_groups[-1][0] != mode:
                mode_groups.append([mode, []])
            mode_groups[-1][1].append(variant)
            if capture["status"] != "PASS":
                ce.append("CAPTURE_NOT_PASS: " + str(capture["status"]))
            if record.get("error") and capture["status"] == "PASS":
                ce.append("PASS_CAPTURE_HAS_ERROR")
            requested = record.get("captureFramesRequested")
            if not _integer(requested, 1) or requested != selected.get("captureFrames"):
                ce.append("REQUESTED_CAPTURE_FRAME_CONFIGURATION_MISMATCH")
            if not _integer(record.get("warmupFramesActual"), 1) or record["warmupFramesActual"] < selected.get("warmupFrames", 0):
                ce.append("WARMUP_FRAME_COUNT_UNVERIFIED")
            if legacy:
                if record.get("materialReadbackAfterCapture") is not True:
                    ce.append("LEGACY_MATERIAL_READBACK_UNVERIFIED")
            else:
                description = selected.get("action", {})
                if not isinstance(description, dict) or description.get("actionType") != selected.get("actionType") or record.get("actionType") != selected.get("actionType"):
                    ce.append("ACTION_TYPE_DESCRIPTION_MISMATCH")
                else:
                    for field in ("actionReadbackBeforeCapture", "actionReadbackAfterCapture"):
                        ce.extend(field + ": " + item for item in _verify_action(description, record.get(field), actual))
                if record.get("actionStateVerifiedAfterCapture") is not True:
                    ce.append("ACTION_POST_CAPTURE_STATE_UNVERIFIED")
                for field in ("environmentReadbackBeforeCapture", "environmentReadbackAfterCapture"):
                    env = record.get(field, [])
                    if not isinstance(env, list) or len(env) < 6 or any(not isinstance(item, dict) or item.get("verified") is not True or not _near(item.get("actualValue"), item.get("expectedValue")) or item.get("actualPriority") != item.get("expectedPriority") or item.get("actualTag") != item.get("expectedTag") for item in env):
                        ce.append("ENVIRONMENT_READBACK_UNVERIFIED: " + field)
                if record.get("environmentStateVerifiedAfterCapture") is not True:
                    ce.append("ENVIRONMENT_POST_CAPTURE_STATE_UNVERIFIED")
            safe_name = isinstance(filename, str) and bool(filename) and Path(filename).name == filename and not any(c in filename for c in '/\\:') and not any(ord(c) < 32 for c in filename) and filename.lower().endswith(".csv") and filename.rstrip(" .") == filename
            if not safe_name or filename.casefold() in seen_files:
                ce.append("CAPTURE_FILENAME_UNSAFE_OR_DUPLICATED")
                continue
            seen_files.add(filename.casefold())
            try:
                parsed = _parse_csv_bytes(_read_file(root, "Raw/" + filename, hashes))
                saved_errors = list(ce)
                capture.update(parsed)
                capture["errors"] = saved_errors + parsed["errors"]
                ce = capture["errors"]
            except (OSError, ValueError) as error:
                ce.append("RAW_READ_ERROR: " + str(error))
                continue
            meta = capture["metadata"]
            recorded_raw_hash = record.get("sha256")
            if schema_version == 3:
                if not isinstance(recorded_raw_hash, str) or not _SHA256.fullmatch(recorded_raw_hash):
                    ce.append("RAW_SHA256_RECORD_MISSING_OR_INVALID")
                elif recorded_raw_hash.lower() != capture["sha256"].lower():
                    ce.append("RAW_SHA256_RECORD_MISMATCH")
            elif recorded_raw_hash is None:
                capture["warnings"].append("LEGACY_RAW_CHECKSUM_NOT_RECORDED")
                warnings.append("LEGACY_RAW_CHECKSUM_NOT_RECORDED: Raw/" + filename)
            elif not isinstance(recorded_raw_hash, str) or not _SHA256.fullmatch(recorded_raw_hash) or recorded_raw_hash.lower() != capture["sha256"].lower():
                ce.append("RAW_SHA256_RECORD_MISMATCH")
            pairs = {"urbrunid": result["run_id"], "urbtestid": result["test_id"], "urbcaptureindex": str(index),
                     "urbvariant": variant, "urbmode": mode, "urbactualmaterial": record.get("actualMaterial"),
                     "urbcaptureframes": str(requested), "engineversion": selected.get("engineVersion"),
                     "rhiname": selected.get("rhi"), "rhifeaturelevel": selected.get("featureLevel"), "gpu": selected.get("gpu")}
            if not legacy:
                pairs.update(urbactiontype=selected.get("actionType"), urbactualactionvariant=actual)
            for key, value in pairs.items():
                if value is None or key not in meta or meta[key] != value:
                    ce.append("CSV_METADATA_MANIFEST_MISMATCH: " + key)
            if schema_version == 3:
                fingerprint = selected.get("measurementFingerprint", {})
                fingerprint_hash = fingerprint.get("sha256") if isinstance(fingerprint, dict) else None
                record_hash = record.get("measurementFingerprintSHA256")
                if not isinstance(fingerprint_hash, str) or not _SHA256.fullmatch(fingerprint_hash):
                    ce.append("MEASUREMENT_FINGERPRINT_SHA256_INVALID")
                else:
                    if not isinstance(record_hash, str) or record_hash.lower() != fingerprint_hash.lower():
                        ce.append("FINGERPRINT_RECORD_MANIFEST_MISMATCH")
                    if meta.get("urbmeasurementfingerprint", "").lower() != fingerprint_hash.lower():
                        ce.append("FINGERPRINT_CSV_MANIFEST_MISMATCH")
                if meta.get("urbsourceschemaversion") != "3":
                    ce.append("CSV_SOURCE_SCHEMA_VERSION_MISMATCH")
            elif "urbsourceschemaversion" in meta:
                ce.append("CSV_SOURCE_SCHEMA_NOT_DECLARED_IN_MANIFEST")
            resolution = selected.get("actualResolution", "")
            match = re.fullmatch(r"(\d+)x(\d+)", resolution) if isinstance(resolution, str) else None
            if not match or any(meta.get("systemresolution.res" + axis) != match.group(number) for axis, number in (("x", 1), ("y", 2))):
                ce.append("CSV_RESOLUTION_MANIFEST_MISMATCH")
            csv_id = meta.get("csvid")
            capture["capture_id"] = csv_id
            if not csv_id or csv_id in seen_ids:
                ce.append("CSV_CAPTURE_ID_MISSING_OR_DUPLICATED")
            seen_ids.add(csv_id)
            explicit_id = record.get("captureID")
            if explicit_id is not None and str(explicit_id) != csv_id:
                ce.append("EXPLICIT_CAPTURE_ID_MISMATCH")
            if capture["status"] == "PASS" and (capture["data_rows"] != requested or record.get("validFrames") != capture["data_rows"]):
                ce.append("CAPTURE_FRAME_COUNT_MISMATCH")
            if not _ENGINE.match(meta.get("engineversion", "")):
                ce.append("CSV_ENGINE_MAPPING_UNSUPPORTED")
        if execution == "COMPLETED" and _integer(selected.get("repeatCount"), 1):
            repeat = selected["repeatCount"]
            order = [value for i in range(repeat) for value in (("B", "A") if i % 2 else ("A", "B"))]
            if [group[0] for group in mode_groups] not in (["Benchmark"], ["Calibration"], ["Calibration", "Benchmark"]):
                errors.append("CAPTURE_MODE_GROUP_ORDER_INVALID")
            for mode, variants in mode_groups:
                if variants != order:
                    errors.append("BALANCED_CAPTURE_ORDER_MISMATCH: " + str(mode))
        for capture in result["captures"]:
            errors.extend("Capture " + str(capture["capture_index"]) + ": " + item for item in capture["errors"])
            for metric in METRICS:
                result["metric_errors"][metric].extend("Capture " + str(capture["capture_index"]) + ": " + item for item in capture["metric_errors"][metric])
        raw_folder = _safe_path(root, "Raw")
        if raw_folder.is_dir():
            for extra in sorted(raw_folder.iterdir(), key=lambda p: p.name.casefold()):
                if extra.suffix.lower() == ".csv" and extra.name.casefold() not in seen_files:
                    relative = "Raw/" + extra.name
                    try:
                        _read_file(root, relative, hashes)
                        warnings.append("UNREFERENCED_RAW_CSV_PRESERVED: " + relative)
                    except (OSError, ValueError) as error:
                        errors.append("UNREFERENCED_RAW_READ_ERROR: " + str(error))
        # Catch an in-progress writer or external mutation during ingestion.
        for relative, expected_hash in list(hashes.items()):
            try:
                if _sha(_safe_path(root, relative).read_bytes()) != expected_hash:
                    errors.append("SOURCE_CHANGED_DURING_READ: " + relative)
            except (OSError, ValueError) as error:
                errors.append("SOURCE_RECHECK_FAILED: " + relative + ": " + str(error))
    except (OSError, ValueError, TypeError, KeyError, AttributeError, IndexError, OverflowError) as error:
        errors.append("RUN_STRUCTURE_INVALID: " + str(error))
    return result
