"""Deterministic statistics and conservative RTR V1 comparison policy.

This module accepts ingest.load_run output. It does not modify inputs or raw
files, remove outliers, infer an absent calibration, or substitute GPU passes.
Only GPUTime receives the GPU Impact and Budget grades defined by the Master.
"""
from __future__ import annotations

from collections.abc import Mapping
from decimal import Decimal, localcontext
import hashlib
import json
import math
from pathlib import Path
import re


ANALYZER_VERSION = "0.3.0"
SCHEMA_VERSION = 1
METRICS = ("GPUTime", "FrameTime", "GameThreadTime", "RenderThreadTime")
POLICY_PATH = Path(__file__).with_name("policy.json")
DEFAULT_POLICY = {
    "version": "RTR-V1-Phase3-Candidate-1",
    "minimum_noise_floor_ms": 0.05,
    "maximum_relative_spread_percent": 5.0,
    "minimum_variant_runs": 3,
    "minimum_calibration_runs": 6,
    "impact_green_max_percent": 2.0,
    "impact_yellow_max_percent": 5.0,
    "budget_green_max_percent": 70.0,
    "budget_yellow_max_percent": 100.0,
}


def _finite_number(value):
    if not isinstance(value, (int, float)) or isinstance(value, bool):
        return False
    try:
        return math.isfinite(value)
    except (OverflowError, TypeError):
        return False


def _d(value):
    return Decimal(str(value))


def parse_policy(config=None):
    """Return validated complete policy; reject unknown or unsafe settings."""
    if config is None:
        supplied = {}
    elif isinstance(config, (str, Path)):
        supplied = json.loads(Path(config).read_text(encoding="utf-8-sig"))
    elif isinstance(config, Mapping):
        supplied = dict(config)
    else:
        raise ValueError("평가 Config는 JSON 객체 또는 JSON 파일이어야 합니다.")
    if not isinstance(supplied, dict):
        raise ValueError("평가 Config 최상위 값은 JSON 객체여야 합니다.")
    unknown = sorted(set(supplied) - set(DEFAULT_POLICY))
    if unknown:
        raise ValueError("지원하지 않는 평가 Config 항목: " + ", ".join(unknown))
    policy = {**DEFAULT_POLICY, **supplied}
    if not isinstance(policy["version"], str) or not policy["version"].strip() or len(policy["version"]) > 128:
        raise ValueError("평가 정책 version은 비어 있지 않은 128자 이하 문자열이어야 합니다.")
    for key in set(policy) - {"version"}:
        if not _finite_number(policy[key]):
            raise ValueError("평가 Config 값은 유한한 숫자여야 합니다: " + key)
    if policy["minimum_noise_floor_ms"] < 0:
        raise ValueError("minimum_noise_floor_ms는 0 이상이어야 합니다.")
    if policy["maximum_relative_spread_percent"] <= 0:
        raise ValueError("maximum_relative_spread_percent는 0보다 커야 합니다.")
    for key, minimum in (("minimum_variant_runs", 3), ("minimum_calibration_runs", 6)):
        if not isinstance(policy[key], int) or policy[key] < minimum:
            raise ValueError(f"{key}는 {minimum} 이상의 정수여야 합니다.")
    if not 0 <= policy["impact_green_max_percent"] < policy["impact_yellow_max_percent"]:
        raise ValueError("Impact 경계는 0 <= GREEN < YELLOW 순서여야 합니다.")
    if not 0 < policy["budget_green_max_percent"] < policy["budget_yellow_max_percent"]:
        raise ValueError("Budget 경계는 0 < GREEN < YELLOW 순서여야 합니다.")
    return policy


def _median(values):
    ordered = sorted(values)
    count = len(ordered)
    if not count:
        return None
    middle = count // 2
    if count % 2:
        return ordered[middle]
    return float((_d(ordered[middle - 1]) + _d(ordered[middle])) / 2)


def summarize_samples(values):
    """Mean/median/nearest-rank P95 over every supplied valid sample (ms)."""
    samples = list(values)
    if not samples:
        return {"sample_count": 0, "mean_ms": None, "median_ms": None,
                "p95_ms": None, "min_ms": None, "max_ms": None}
    if any(not _finite_number(value) or value < 0 for value in samples):
        raise ValueError("통계 Sample에 결측·비유한·음수 값이 있습니다.")
    ordered = sorted(float(value) for value in samples)
    with localcontext() as context:
        context.prec = 80
        mean = float(sum((_d(value) for value in ordered), Decimal(0)) / len(ordered))
        median = _median(ordered)
    p95_rank = (95 * len(ordered) + 99) // 100
    result = {"sample_count": len(ordered), "mean_ms": mean, "median_ms": median,
              "p95_ms": ordered[p95_rank - 1], "min_ms": ordered[0], "max_ms": ordered[-1]}
    if any(value is not None and not _finite_number(value) for value in result.values()):
        raise ValueError("집계 통계가 유한한 출력 범위를 벗어났습니다.")
    return result


def impact_grade(impact_percent_budget, policy=None):
    """Classify an already reliable GPU delta; analyze_run applies all gates."""
    policy = parse_policy(policy)
    if not _finite_number(impact_percent_budget):
        return "UNAVAILABLE"
    value = _d(impact_percent_budget)
    if value < 0:
        return "IMPROVED"
    if value <= _d(policy["impact_green_max_percent"]):
        return "GREEN"
    if value <= _d(policy["impact_yellow_max_percent"]):
        return "YELLOW"
    return "RED"


def budget_grade(usage_percent, policy=None):
    """Classify an already valid and stable absolute GPU budget usage."""
    policy = parse_policy(policy)
    if not _finite_number(usage_percent) or usage_percent < 0:
        return "UNAVAILABLE"
    if _d(usage_percent) <= _d(policy["budget_green_max_percent"]):
        return "GREEN"
    if _d(usage_percent) <= _d(policy["budget_yellow_max_percent"]):
        return "YELLOW"
    return "RED"


def _messages(value):
    if value is None:
        return []
    if isinstance(value, str):
        return [value] if value else []
    if isinstance(value, list):
        return [str(item) for item in value if item is not None and str(item)]
    return [str(value)]


def _unique(values):
    return list(dict.fromkeys(values))


def _has_metric_errors(value):
    return isinstance(value, dict) and any(_messages(messages) for messages in value.values())


def _ratio_percent(numerator, denominator):
    if not _finite_number(numerator) or not _finite_number(denominator) or denominator <= 0:
        return None
    with localcontext() as context:
        context.prec = 80
        result = float(100 * _d(numerator) / _d(denominator))
    return result if math.isfinite(result) else None


def _group(captures, metric, manifest, policy, minimum_runs):
    valid_runs, invalid_runs = [], []
    pooled = []
    for capture in captures:
        errors = _messages(capture.get("metric_errors", {}).get(metric))
        errors.extend(_messages(capture.get("errors")))
        values = capture.get("samples", {}).get(metric, [])
        available = capture.get("metric_available", {}).get(metric, metric in capture.get("samples", {}))
        expected = capture.get("capture_frames_requested", manifest.get("captureFrames"))
        if expected is None:
            record = capture.get("record", {})
            expected = record.get("captureFramesRequested")
        if not available:
            errors.append("Metric을 사용할 수 없습니다.")
        if not isinstance(values, list) or not values:
            errors.append("유효 Sample이 없습니다.")
            values = []
        if isinstance(expected, int) and not isinstance(expected, bool) and len(values) != expected:
            errors.append("요청한 프레임 수와 Metric Sample 수가 다릅니다.")
        if capture.get("status") != "PASS":
            errors.append("정상 완료한 Capture가 아닙니다.")
        if any(not _finite_number(value) or value < 0 or (metric == "GPUTime" and value <= 0) for value in values):
            errors.append("결측·비유한·음수 또는 0 GPU Sample이 있습니다.")
        entry = {key: capture.get(key) for key in
                 ("capture_index", "variant", "mode", "actual_action_variant", "file", "sha256")}
        if errors:
            invalid_runs.append({**entry, "errors": _unique(errors), "sample_count": len(values)})
            continue
        try:
            stats = summarize_samples(values)
        except (ValueError, OverflowError) as error:
            invalid_runs.append({**entry, "errors": [str(error)], "sample_count": len(values)})
            continue
        valid_runs.append({**entry, "stats": stats, "samples_ms": list(values)})
        pooled.extend(values)
    medians = [entry["stats"]["median_ms"] for entry in valid_runs]
    representative = _median(medians)
    range_ms = float(_d(max(medians)) - _d(min(medians))) if medians else None
    spread = _ratio_percent(range_ms, representative)
    integrity = bool(captures) and not invalid_runs and len(valid_runs) == len(captures)
    enough = len(valid_runs) >= minimum_runs
    stability = bool(integrity and enough and representative is not None and representative > 0
                     and spread is not None and spread <= policy["maximum_relative_spread_percent"])
    return {"run_count": len(valid_runs), "expected_run_count": len(captures),
            "invalid_run_count": len(invalid_runs), "sample_count": len(pooled),
            "representative_ms": representative, "run_medians_ms": medians,
            "median_of_run_p95_ms": _median([entry["stats"]["p95_ms"] for entry in valid_runs]),
            "range_ms": range_ms, "relative_spread_percent": spread,
            "pooled": summarize_samples(pooled), "runs": valid_runs,
            "invalid_runs": invalid_runs, "integrity_valid": integrity,
            "minimum_runs_met": enough, "stability_valid": stability}


FINGERPRINT_KEYS = (
    "engineVersion", "gpu", "driver", "os", "cpu", "rhi", "featureLevel",
    "resolution", "screenPercentage", "warmupFrames", "captureFrames",
    "targetFPSBudgetOnly", "sceneType", "sceneStatePolicy", "worldPackage",
    "contentSHA256", "sceneTransformSHA256", "camera", "scalability", "environmentCVars", "actionA",
    "runnerBuildSHA256",
)
ACTION_A_KEYS = (
    "actionType", "targetActorTag", "targetComponentTag", "materialSlot",
    "parameterName", "valueA", "materialA", "visibilityScope", "visibleA",
    "hiddenInGameA", "shadowPolicy", "cvarName", "cvarValueA",
)
ENVIRONMENT_CVARS = (
    "r.ScreenPercentage", "r.VSync", "t.MaxFPS", "r.DynamicRes.OperationMode",
    "r.GPUCsvStatsEnabled", "csv.AlwaysShowFrameCount",
)
HASH_PATTERN = re.compile(r"^[0-9a-fA-F]{64}$")


def validate_measurement_fingerprint(manifest, captures=None):
    """Validate recorded environment evidence before allowing AA/AB matching.

    Native SHA hashes the exact stored UTF-8 payloadJson. Comparison uses the
    canonical JSON digest after that evidence is validated, so object order is
    not a cross-run condition and no opaque declared hash is trusted alone.
    """
    codes, reasons = [], []

    def reject(code, message):
        if code not in codes:
            codes.append(code)
            reasons.append(message)

    result = {"valid": False, "canonical_sha256": None, "payload_sha256": None,
              "payload": None, "reason_codes": codes, "reasons": reasons}
    if not isinstance(manifest, dict) or not isinstance(manifest.get("schemaVersion"), int) or isinstance(manifest.get("schemaVersion"), bool) or manifest["schemaVersion"] < 3:
        reject("FINGERPRINT_MISSING", "이전 수집 자료에 완전한 환경 Fingerprint가 없습니다.")
        return result
    fingerprint = manifest.get("measurementFingerprint")
    if not isinstance(fingerprint, dict) or fingerprint.get("schema_version") != 1:
        reject("FINGERPRINT_SCHEMA", "지원하는 환경 Fingerprint 형식이 아닙니다.")
        return result
    payload, serialized = fingerprint.get("payload"), fingerprint.get("payloadJson")
    declared = fingerprint.get("sha256")
    if not isinstance(payload, dict) or not isinstance(serialized, str) or not isinstance(declared, str) or not HASH_PATTERN.fullmatch(declared):
        reject("FINGERPRINT_INCOMPLETE", "환경 Fingerprint의 Payload·원문·SHA256이 완전하지 않습니다.")
        return result
    result["payload"] = payload
    result["payload_sha256"] = hashlib.sha256(serialized.encode("utf-8")).hexdigest().upper()
    if result["payload_sha256"] != declared.upper():
        reject("FINGERPRINT_HASH", "환경 Fingerprint 원문 SHA256이 일치하지 않습니다.")

    def reject_duplicate_keys(pairs):
        value = {}
        for key, item in pairs:
            if key in value:
                raise ValueError("Duplicate fingerprint JSON key: " + key)
            value[key] = item
        return value

    try:
        decoded = json.loads(serialized, object_pairs_hook=reject_duplicate_keys,
                             parse_constant=lambda text: (_ for _ in ()).throw(ValueError(text)))
        if decoded != payload:
            reject("FINGERPRINT_PAYLOAD", "환경 Fingerprint 객체와 저장한 JSON 원문이 다릅니다.")
        canonical = json.dumps(payload, ensure_ascii=False, sort_keys=True, separators=(",", ":"), allow_nan=False)
        result["canonical_sha256"] = hashlib.sha256(canonical.encode("utf-8")).hexdigest().upper()
    except (ValueError, TypeError, OverflowError):
        reject("FINGERPRINT_JSON", "환경 Fingerprint JSON에 유효하지 않은 값이 있습니다.")
    missing = [key for key in FINGERPRINT_KEYS if key not in payload]
    if missing:
        reject("FINGERPRINT_FIELDS", "환경 Fingerprint 필드가 누락되었습니다: " + ", ".join(missing))
    for key in ("engineVersion", "gpu", "driver", "os", "cpu", "rhi", "featureLevel", "sceneType", "worldPackage"):
        if not isinstance(payload.get(key), str) or not payload[key].strip():
            reject("FINGERPRINT_FIELDS", "환경 Fingerprint의 식별 필드가 비어 있습니다: " + key)
    if payload.get("sceneStatePolicy") != "DeclaredStatic":
        reject("SCENE_STATE_UNVERIFIED", "장면의 고정 상태 선언을 확인할 수 없습니다.")
    for key in ("contentSHA256", "sceneTransformSHA256", "runnerBuildSHA256"):
        if not isinstance(payload.get(key), str) or not HASH_PATTERN.fullmatch(payload[key]):
            reject("FINGERPRINT_FIELDS", "장면 또는 Runner SHA256 필드가 유효하지 않습니다.")
    for key in ("warmupFrames", "captureFrames", "targetFPSBudgetOnly"):
        if not isinstance(payload.get(key), int) or isinstance(payload[key], bool) or payload[key] <= 0:
            reject("FINGERPRINT_FIELDS", "환경 Fingerprint의 프레임 설정이 유효하지 않습니다.")
    resolution = payload.get("resolution")
    if not isinstance(resolution, list) or len(resolution) != 2 or any(not isinstance(value, int) or isinstance(value, bool) or value < 1 for value in resolution):
        reject("FINGERPRINT_FIELDS", "환경 Fingerprint 해상도가 유효하지 않습니다.")
    if not _finite_number(payload.get("screenPercentage")) or payload["screenPercentage"] <= 0:
        reject("FINGERPRINT_FIELDS", "환경 Fingerprint Screen Percentage가 유효하지 않습니다.")
    camera = payload.get("camera")
    if not isinstance(camera, dict):
        reject("FINGERPRINT_CAMERA", "Camera Transform·FOV 기록이 없습니다.")
    else:
        for key in ("location", "rotation"):
            if not isinstance(camera.get(key), list) or len(camera[key]) != 3 or any(not _finite_number(value) for value in camera[key]):
                reject("FINGERPRINT_CAMERA", "Camera Transform 기록이 유효하지 않습니다.")
        if not _finite_number(camera.get("fov")) or not 0 < camera["fov"] < 180:
            reject("FINGERPRINT_CAMERA", "Camera FOV 기록이 유효하지 않습니다.")
    scalability = payload.get("scalability")
    if not isinstance(scalability, dict) or not scalability or any(not isinstance(name, str) or not name.startswith("sg.") or not isinstance(value, str) or not value for name, value in scalability.items()):
        reject("FINGERPRINT_SCALABILITY", "Scalability 적용 상태를 확인할 수 없습니다.")
    variables = payload.get("environmentCVars")
    if not isinstance(variables, dict) or any(not isinstance(variables.get(name), str) or not variables[name] for name in ENVIRONMENT_CVARS):
        reject("FINGERPRINT_CVARS", "측정 환경 CVar 여섯 개의 적용 상태를 확인할 수 없습니다.")
    action = payload.get("actionA")
    if not isinstance(action, dict) or any(key not in action for key in ACTION_A_KEYS) or action.get("actionType") not in ("MaterialSwap", "ScalarParameter", "ActorVisibility", "ConsoleVariable"):
        reject("FINGERPRINT_ACTION", "같은 A 상태를 확인할 Action 설정 기록이 완전하지 않습니다.")
    if manifest.get("sourceSnapshotStable") is False:
        reject("SOURCE_SNAPSHOT_CHANGED", "측정 전후 장면·설정 원본 해시가 변경되었습니다.")
    elif manifest.get("sourceSnapshotStable") is not True:
        reject("SOURCE_SNAPSHOT_UNVERIFIED", "측정 전후 장면·설정 원본 해시의 일치를 확인할 수 없습니다.")
    if manifest.get("sourceSnapshotStable") is True:
        content_hash = payload.get("contentSHA256", "")
        for key in ("sourceContentSHA256", "sourceContentSHA256After"):
            observed = manifest.get(key)
            if not isinstance(observed, str) or not HASH_PATTERN.fullmatch(observed) or observed.upper() != str(content_hash).upper():
                reject("FINGERPRINT_SOURCE_HASH", "Fingerprint와 측정 전후 장면·설정 원본 해시가 일치하지 않습니다.")
    expected_pairs = (("engineVersion", "engineVersion"), ("gpu", "gpu"), ("rhi", "rhi"),
                      ("featureLevel", "featureLevel"), ("warmupFrames", "warmupFrames"),
                      ("captureFrames", "captureFrames"), ("targetFPSBudgetOnly", "targetFPSBudgetOnly"),
                      ("screenPercentage", "screenPercentageRequested"))
    for payload_key, manifest_key in expected_pairs:
        if manifest_key in manifest and payload.get(payload_key) != manifest[manifest_key]:
            reject("FINGERPRINT_MANIFEST", "환경 Fingerprint와 Manifest 설정이 일치하지 않습니다.")
    native_records = manifest.get("captures", [])
    if not isinstance(native_records, list):
        native_records = []
    by_index = {record.get("captureIndex"): record for record in native_records if isinstance(record, dict)}
    selected = captures if captures is not None else native_records
    if not selected:
        reject("CAPTURE_ENVIRONMENT_UNVERIFIED", "Fingerprint를 연결할 Capture 기록이 없습니다.")
    for capture in selected:
        if not isinstance(capture, dict):
            reject("CAPTURE_ENVIRONMENT_UNVERIFIED", "Capture 환경 검증 기록이 유효하지 않습니다.")
            continue
        index = capture.get("capture_index", capture.get("captureIndex"))
        record = by_index.get(index, capture)
        if record.get("invariantEnvironmentVerifiedBefore") is not True or record.get("invariantEnvironmentVerifiedAfter") is not True:
            reject("CAPTURE_ENVIRONMENT_UNVERIFIED", "Capture 전후 Camera·Scalability·환경 검증을 확인할 수 없습니다.")
    result["valid"] = not codes
    return result


def _is_completed(run):
    manifest = run.get("manifest", {})
    return manifest.get("status") == "COMPLETED" and not _messages(run.get("errors"))


def _calibration_context(run, calibration):
    captures = run.get("captures", [])
    inline = [capture for capture in captures if capture.get("mode") == "Calibration"]
    reference = run if inline else calibration
    selected = inline if inline else ([capture for capture in reference.get("captures", []) if capture.get("mode") == "Calibration"] if reference else [])
    manifest = run.get("manifest", {})
    current_fp = validate_measurement_fingerprint(manifest, captures)
    reference_fp = validate_measurement_fingerprint(reference.get("manifest", {}), selected) if reference else None
    codes, reasons = [], []

    def reject(code, message):
        if code not in codes:
            codes.append(code)
            reasons.append(message)

    if not reference or not selected:
        reject("CALIBRATION_MISSING", "유효한 A/A Calibration이 연결되지 않았습니다.")
    if reference and not _is_completed(reference):
        reject("CALIBRATION_INVALID_RUN", "Calibration이 정상 완료한 Run이 아닙니다.")
    if any(capture.get("actual_action_variant") != "A" for capture in selected):
        reject("CALIBRATION_NOT_AA", "Calibration Capture의 실제 Action 상태가 모두 A가 아닙니다.")
    declared_ref = manifest.get("calibrationReferenceRunID", "")
    if reference and not inline and declared_ref and declared_ref != reference.get("run_id", reference.get("manifest", {}).get("runID")):
        reject("CALIBRATION_REFERENCE_ID", "선택한 Calibration과 Manifest의 참조 RunID가 다릅니다.")
    if not current_fp["valid"]:
        for code, reason in zip(current_fp["reason_codes"], current_fp["reasons"]):
            reject(code, reason)
    if reference_fp and not reference_fp["valid"]:
        reject("CALIBRATION_FINGERPRINT_UNVERIFIED", "Calibration의 완전한 환경 검증을 확인할 수 없습니다.")
    match = bool(current_fp["valid"] and reference_fp and reference_fp["valid"] and current_fp["canonical_sha256"] == reference_fp["canonical_sha256"])
    if current_fp["valid"] and reference_fp and reference_fp["valid"] and not match:
        reject("CALIBRATION_ENVIRONMENT_MISMATCH", "Calibration과 A/B의 장면·Camera·해상도·Action A·환경이 다릅니다.")
    return {"reference": reference, "captures": selected, "source": "inline" if inline else "reference" if reference else "none",
            "eligible": bool(reference and selected and _is_completed(reference) and match and not codes),
            "fingerprint": current_fp, "reference_fingerprint": reference_fp,
            "environment_match": match, "reason_codes": codes, "reasons": reasons}


def _source_records(run, calibration=None):
    result = []
    for source in (run, calibration):
        if not source:
            continue
        run_id = source.get("run_id", source.get("manifest", {}).get("runID", "Unknown"))
        hashes = source.get("source_hashes", {})
        if not isinstance(hashes, dict):
            continue
        for path, digest in sorted(hashes.items()):
            result.append({"label": str(run_id) + "/" + str(path), "path": str(path),
                           "source_dir": str(source.get("source_dir", "")), "run_id": run_id, "sha256": digest})
    return result


def analyze_run(run, calibration=None, policy=None):
    """Produce serializable statistics, independent statuses and reasons."""
    policy = parse_policy(policy)
    if not isinstance(run, dict):
        raise ValueError("분석 입력은 ingest.load_run의 Run 객체여야 합니다.")
    manifest = run.get("manifest", {})
    if not isinstance(manifest, dict):
        manifest = {}
    errors = _messages(run.get("errors"))
    warnings = _messages(run.get("warnings"))
    native_status = manifest.get("status")
    native_measurement = manifest.get("measurementStatus")
    if native_measurement == "UNSUPPORTED":
        measurement = "UNSUPPORTED"
    elif native_status == "CANCELLED" or native_measurement == "CANCELLED":
        measurement = "CANCELLED"
    elif native_status != "COMPLETED" or errors:
        measurement = "FAIL"
    elif _has_metric_errors(run.get("metric_errors")) or warnings:
        measurement = "WARNING"
    else:
        measurement = "PASS"
    if native_status != "COMPLETED" and not errors:
        errors.append("정상 완료한 측정 Run이 아닙니다: " + str(native_status))
    target_fps = manifest.get("targetFPSBudgetOnly")
    if not _finite_number(target_fps) or target_fps <= 0:
        errors.append("Target FPS 예산값이 유효하지 않습니다.")
        frame_budget = None
        if measurement not in ("UNSUPPORTED", "CANCELLED"):
            measurement = "FAIL"
    else:
        frame_budget = float(Decimal(1000) / _d(target_fps))
        if not _finite_number(frame_budget) or frame_budget <= 0:
            errors.append("Target FPS로 계산한 프레임 예산이 유한한 양수 범위를 벗어났습니다.")
            frame_budget = None
            if measurement not in ("UNSUPPORTED", "CANCELLED"):
                measurement = "FAIL"
    captures = run.get("captures", [])
    if not isinstance(captures, list):
        captures = []
        errors.append("Capture 배열이 유효하지 않습니다.")
        measurement = "FAIL"
    indices = [capture.get("capture_index") for capture in captures]
    files = [capture.get("file") for capture in captures]
    if len(set(indices)) != len(indices) or len(set(files)) != len(files):
        errors.append("Capture 식별자 또는 파일이 중복되었습니다.")
        if measurement not in ("UNSUPPORTED", "CANCELLED"):
            measurement = "FAIL"
    benchmark = [capture for capture in captures if capture.get("mode") == "Benchmark"]
    aa = [capture for capture in captures if capture.get("mode") == "Calibration"]
    calibration_only = bool(aa and not benchmark)
    context = _calibration_context(run, calibration)
    reference = context["reference"]
    reference_manifest = reference.get("manifest", {}) if reference else {}
    if any(code in context["fingerprint"]["reason_codes"] for code in ("FINGERPRINT_HASH", "FINGERPRINT_PAYLOAD", "FINGERPRINT_JSON", "FINGERPRINT_SOURCE_HASH")):
        errors.append("환경 Fingerprint의 저장 원문·Payload·SHA256 무결성 검증에 실패했습니다.")
        if measurement not in ("UNSUPPORTED", "CANCELLED"):
            measurement = "FAIL"
    disruptions = _messages(manifest.get("confirmedEnvironmentDisruptions"))
    if reference:
        disruptions += _messages(reference_manifest.get("confirmedEnvironmentDisruptions"))
    for source_manifest in (manifest, reference_manifest):
        if source_manifest.get("sourceSnapshotStable") is False:
            disruptions.append("측정 전후 장면·설정 원본 해시가 변경되었습니다.")
        native_captures = source_manifest.get("captures", [])
        if isinstance(native_captures, list) and any(isinstance(record, dict) and
                (record.get("invariantEnvironmentVerifiedBefore") is False or record.get("invariantEnvironmentVerifiedAfter") is False)
                for record in native_captures):
            disruptions.append("Capture 전후 고정 환경 검증에 실패한 기록이 있습니다.")
    disruptions = _unique(disruptions)
    global_valid = measurement not in ("FAIL", "UNSUPPORTED", "CANCELLED") and not errors
    a_captures = [capture for capture in benchmark if capture.get("variant") == "A"]
    b_captures = [capture for capture in benchmark if capture.get("variant") == "B"]
    all_required_valid = not any(_has_metric_errors(capture.get("metric_errors")) for capture in captures)
    if reference:
        all_required_valid = all_required_valid and not any(_has_metric_errors(capture.get("metric_errors")) for capture in context["captures"])
    metrics = {}
    for metric in METRICS:
        a = _group(a_captures, metric, manifest, policy, policy["minimum_variant_runs"])
        b = _group(b_captures, metric, manifest, policy, policy["minimum_variant_runs"])
        group_aa = _group(context["captures"], metric, reference_manifest, policy, policy["minimum_calibration_runs"])
        representative_a, representative_b = a["representative_ms"], b["representative_ms"]
        pair_valid = a["integrity_valid"] and b["integrity_valid"] and representative_a is not None and representative_b is not None
        delta = float(_d(representative_b) - _d(representative_a)) if pair_valid else None
        baseline_percent = _ratio_percent(delta, representative_a) if delta is not None else None
        impact_percent = _ratio_percent(delta, frame_budget) if delta is not None else None
        ranges = [group_aa["range_ms"], a["range_ms"], b["range_ms"], policy["minimum_noise_floor_ms"]]
        noise_floor = max(value for value in ranges if value is not None)
        reason_codes, reasons = [], []

        def reason(code, text):
            if code not in reason_codes:
                reason_codes.append(code)
                reasons.append(text)

        if calibration_only:
            confidence = "UNAVAILABLE"
            reason("CALIBRATION_ONLY", "A/A 안정성 진단이며 A/B 비용 비교를 수행하지 않습니다.")
        elif not global_valid:
            confidence = "UNAVAILABLE"
            reason("MEASUREMENT_INVALID", "실패·취소·미지원 또는 무결성 오류가 있어 성능 판정을 제공하지 않습니다.")
        elif not pair_valid:
            confidence = "UNAVAILABLE"
            reason("METRIC_UNAVAILABLE", "양쪽 Variant의 완전한 Metric 자료가 없습니다.")
        elif representative_a <= 0 or representative_b <= 0:
            confidence = "UNAVAILABLE"
            reason("NON_POSITIVE_REPRESENTATIVE", "대표값이 0 이하여서 변화율·안정성을 평가할 수 없습니다.")
        else:
            confidence = "RELIABLE"
            if not a["minimum_runs_met"] or not b["minimum_runs_met"]:
                reason("INSUFFICIENT_VARIANT_RUNS", f"Variant별 유효 Run {policy['minimum_variant_runs']}회가 필요합니다.")
            if not a["stability_valid"] or not b["stability_valid"]:
                reason("VARIANT_UNSTABLE", "A 또는 B의 반복 Median 변동이 안정성 조건을 통과하지 못했습니다.")
            for code, text in zip(context["reason_codes"], context["reasons"]):
                reason(code, text)
            if not context["eligible"] and not context["reason_codes"]:
                reason("CALIBRATION_UNVERIFIED", "같은 조건의 A/A 연결을 확인할 수 없습니다.")
            if not group_aa["integrity_valid"]:
                reason("CALIBRATION_METRIC_UNAVAILABLE", "A/A의 완전한 Metric 자료가 없습니다.")
            if not group_aa["minimum_runs_met"]:
                reason("INSUFFICIENT_CALIBRATION_RUNS", f"유효 A/A Capture {policy['minimum_calibration_runs']}개가 필요합니다.")
            if group_aa["integrity_valid"] and group_aa["minimum_runs_met"] and not group_aa["stability_valid"]:
                reason("CALIBRATION_UNSTABLE", "A/A Median 변동이 안정성 조건을 통과하지 못했습니다.")
            if not all_required_valid:
                reason("REQUIRED_METRIC_UNAVAILABLE", "필수 GPU·CPU Metric 중 완전하지 않은 항목이 있습니다.")
            if disruptions:
                reason("CONFIRMED_ENVIRONMENT_DISRUPTION", "확인된 실행 환경 급변이 있습니다: " + "; ".join(disruptions))
            if abs(_d(delta)) <= _d(noise_floor):
                reason("DELTA_WITHIN_NOISE_FLOOR", "A/B 차이가 Noise Floor 이하이므로 차이 판정을 보류합니다.")
            if reason_codes:
                confidence = "INCONCLUSIVE"
        grade = "UNAVAILABLE"
        usage_a = usage_b = None
        budget_a = budget_b = "UNAVAILABLE"
        if metric == "GPUTime":
            if confidence == "RELIABLE":
                grade = impact_grade(impact_percent, policy)
            elif confidence == "INCONCLUSIVE":
                grade = "INCONCLUSIVE"
            if global_valid and not calibration_only and not disruptions:
                if a["stability_valid"]:
                    usage_a = _ratio_percent(representative_a, frame_budget)
                    budget_a = budget_grade(usage_a, policy)
                if b["stability_valid"]:
                    usage_b = _ratio_percent(representative_b, frame_budget)
                    budget_b = budget_grade(usage_b, policy)
        else:
            reason("GPU_ONLY_GRADE_POLICY", "CPU·Frame 지표는 보조 통계이며 GPU Impact·Budget 색상 정책을 적용하지 않습니다.")
        metrics[metric] = {
            "name": metric, "unit": "ms", "a": a, "b": b,
            "calibration_group": group_aa, "delta_ms": delta,
            "delta_percent_baseline": baseline_percent,
            "impact_percent_budget": impact_percent,
            "confidence": confidence, "impact_grade": grade,
            "budget_grade_a": budget_a, "budget_grade_b": budget_b,
            "budget_usage_percent_a": usage_a, "budget_usage_percent_b": usage_b,
            "noise_floor_ms": noise_floor, "range_aa_ms": group_aa["range_ms"],
            "range_a_ms": a["range_ms"], "range_b_ms": b["range_ms"],
            "relative_spread_aa_percent": group_aa["relative_spread_percent"],
            "reason_codes": reason_codes, "reasons": reasons,
        }
    gpu_aa = metrics["GPUTime"]["calibration_group"]
    if not context["captures"]:
        calibration_status = "MISSING"
    elif not context["eligible"]:
        calibration_status = "UNVERIFIED_ENVIRONMENT" if not context["environment_match"] else "INVALID_RUN"
    elif not gpu_aa["integrity_valid"] or not gpu_aa["minimum_runs_met"]:
        calibration_status = "INVALID_DATA"
    elif not gpu_aa["stability_valid"]:
        calibration_status = "UNSTABLE"
    else:
        calibration_status = "VALID"
    warnings += context["reasons"]
    warnings.append("Noise Floor와 변동 상한은 RTR V1 후보 정책이며 통계적 유의성·신뢰구간을 증명하지 않습니다.")
    if disruptions:
        warnings.append("확인된 환경 급변: " + "; ".join(disruptions))
    environment = {key: manifest.get(key) for key in
                   ("engineVersion", "gpu", "rhi", "featureLevel", "actualResolution", "screenPercentageRequested",
                    "warmupFrames", "captureFrames", "repeatCount", "camera", "sceneType", "startedUTC", "finishedUTC")}
    if context["fingerprint"]["payload"]:
        environment.update(context["fingerprint"]["payload"])
    calibration_result = {
        "status": calibration_status, "source": context["source"],
        "reference_run_id": reference.get("run_id", reference_manifest.get("runID")) if reference else None,
        "aa_capture_count": len(context["captures"]),
        "environment_match": context["environment_match"],
        "fingerprint": context["fingerprint"], "reference_fingerprint": context["reference_fingerprint"],
        "reason_codes": context["reason_codes"], "reasons": context["reasons"],
        "metrics": {name: {key: value for key, value in item["calibration_group"].items() if key not in ("runs", "invalid_runs")}
                    for name, item in metrics.items()},
    }
    result = {
        "schema_version": SCHEMA_VERSION, "analyzer_version": ANALYZER_VERSION,
        "run_id": run.get("run_id", manifest.get("runID", "Unknown")),
        "test_id": run.get("test_id", manifest.get("testID", "Unknown")),
        "test_name": manifest.get("testName", run.get("test_id", "Unknown")),
        "source_dir": str(run.get("source_dir", "")),
        "analysis_mode": "CalibrationOnly" if calibration_only else "StandardBenchmark",
        "native_status": native_status, "measurement_status": measurement,
        "target_fps": target_fps, "frame_budget_ms": frame_budget,
        "metrics": metrics, "warnings": _unique(warnings), "errors": _unique(errors),
        "environment": environment, "action": manifest.get("action", {}),
        "calibration": calibration_result, "policy": policy,
        "sources": _source_records(run, calibration if context["source"] == "reference" else None),
        "confirmed_environment_disruptions": disruptions,
        "p95_method": "nearest-rank ceil(0.95*N)",
        "representative_method": "median of run medians",
        "outlier_removal": "none",
    }
    # Catch non-finite values before a caller serializes an invalid JSON result.
    json.dumps(result, ensure_ascii=False, allow_nan=False)
    return result
