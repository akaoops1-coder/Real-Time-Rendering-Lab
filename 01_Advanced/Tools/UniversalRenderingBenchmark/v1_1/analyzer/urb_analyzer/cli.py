"""Offline analyzer launcher and immutable, portable report bundles."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import stat
import sys
from urllib.parse import quote
import uuid
import webbrowser

from . import __version__
from .analysis import analyze_run, parse_policy
from .ingest import load_run
from .report import render_report, render_summary_csv


class AnalyzerError(Exception):
    """An actionable user error, without an internal Python traceback."""


def _canonical(value):
    return json.dumps(value, ensure_ascii=False, sort_keys=True, allow_nan=False, separators=(",", ":")).encode("utf-8")


def _json_bytes(value):
    return (json.dumps(value, ensure_ascii=False, sort_keys=True, allow_nan=False, indent=2) + "\n").encode("utf-8")


def _sha(data):
    return hashlib.sha256(data).hexdigest().upper()


def _implementation_snapshot():
    package = Path(__file__).resolve().parent
    files = {}
    for path in sorted(package.rglob("*.py"), key=lambda item: item.relative_to(package).as_posix()):
        if "__pycache__" not in path.relative_to(package).parts:
            if _reparse(path):
                raise AnalyzerError("분석기 코드가 링크 경로입니다: " + str(path))
            files[path.relative_to(package).as_posix()] = _sha(path.read_bytes())
    if not files:
        raise AnalyzerError("분석기 구현 파일을 확인할 수 없습니다.")
    return {"sha256": _sha(_canonical(files)), "files": files}


def _validate_implementation(expected):
    if _implementation_snapshot() != expected:
        raise AnalyzerError("분석 도중 분석기 구현이 변경됐습니다. 분석기를 새로 실행하세요.")


def _reparse(path):
    return path.is_symlink() or bool(getattr(path.lstat(), "st_file_attributes", 0) & getattr(stat, "FILE_ATTRIBUTE_REPARSE_POINT", 0x400))


def _source_file(root, relative):
    if not isinstance(relative, str) or not relative or ":" in relative or "\\" in relative or any(ord(c) < 32 for c in relative):
        raise AnalyzerError("원본 파일 경로가 안전하지 않습니다.")
    parts = PurePosixPath(relative).parts
    if not parts or PurePosixPath(relative).is_absolute() or ".." in parts:
        raise AnalyzerError("원본 파일 경로가 측정 폴더 밖을 가리킵니다.")
    candidate = root.joinpath(*parts)
    current = root
    for part in parts:
        current = current / part
        if not current.exists() or _reparse(current):
            raise AnalyzerError("원본 파일이 없거나 링크 경로입니다: " + relative)
    if not candidate.is_file() or not candidate.resolve().is_relative_to(root.resolve()):
        raise AnalyzerError("원본 파일 경로를 확인할 수 없습니다: " + relative)
    return candidate


def _source_roles(run, calibration):
    roles = [("Benchmark", run)]
    if calibration is not None:
        roles.append(("Calibration", calibration))
    return roles


def _validate_sources(roles):
    for _, run in roles:
        root = Path(run["source_dir"])
        for relative, digest in sorted(run.get("source_hashes", {}).items()):
            try:
                current = _sha(_source_file(root, relative).read_bytes())
            except OSError as error:
                raise AnalyzerError("원본 파일을 다시 읽지 못했습니다: " + relative) from error
            if current != str(digest).upper():
                raise AnalyzerError("분석 중 원본 파일이 변경됐습니다. 측정 종료 후 다시 분석하세요: " + relative)


def _existing_matches(folder, expected):
    if _reparse(folder) or not folder.is_dir():
        return False
    actual = {}
    for path in folder.rglob("*"):
        if _reparse(path):
            return False
        if path.is_file():
            actual[path.relative_to(folder).as_posix()] = _sha(path.read_bytes())
    return actual == expected


def _input_path(path):
    path = Path(path).expanduser().absolute()
    if not path.is_dir() or _reparse(path):
        raise AnalyzerError("실제 측정 결과 폴더를 선택하세요: " + str(path))
    return path.resolve()


def _output_path(path):
    # Inspect the selected path before resolve() discards redirect identity.
    selected = Path(path).expanduser().absolute()
    for component in (selected, *selected.parents):
        if component.exists() or component.is_symlink():
            if _reparse(component):
                raise AnalyzerError("분석 저장 폴더 또는 상위 폴더가 링크 경로입니다: " + str(component))
    return selected.resolve()


def _portable_provenance(result, roles):
    replacements = []
    for role, item in roles:
        path = Path(item["source_dir"])
        for original in {str(path), path.as_posix()}:
            replacements.append((original, "Sources/" + role))
    replacements.sort(key=lambda pair: len(pair[0]), reverse=True)
    def visit(value):
        if isinstance(value, str):
            for original, bundled in replacements:
                value = re.sub(re.escape(original) + r"(?=$|[\\/\s'\"\]\),:])", lambda _: bundled, value, flags=re.IGNORECASE if os.name == "nt" else 0)
            return value
        if isinstance(value, list):
            return [visit(child) for child in value]
        if isinstance(value, dict):
            return {key: visit(child) for key, child in value.items()}
        return value
    return visit(result)


def analyze_to_bundle(run_dir, calibration_dir=None, policy_path=None, output_root=None):
    """Analyze one Run and return its immutable bundle path and result.

    Return ``(bundle_path, result, reused)``. A diagnostic FAIL/CANCELLED report
    is still a report; the command's exit status distinguishes invalid data.
    """
    source_dir = _input_path(run_dir)
    implementation = _implementation_snapshot()
    calibration_path = _input_path(calibration_dir) if calibration_dir is not None else None
    if calibration_path == source_dir:
        raise AnalyzerError("A/B 결과와 별도 Calibration에 같은 폴더를 지정할 수 없습니다.")
    policy = parse_policy(policy_path if policy_path is not None else Path(__file__).with_name("policy.json"))
    run = load_run(source_dir)
    calibration = load_run(calibration_path) if calibration_path is not None else None
    if calibration is not None and run.get("run_id") and run.get("run_id") == calibration.get("run_id"):
        raise AnalyzerError("A/B 결과와 Calibration의 RunID가 같습니다. 서로 다른 측정을 지정하세요.")
    roles = _source_roles(run, calibration)
    _validate_sources(roles)
    identity = {"analyzer_version": __version__, "implementation_sha256": implementation["sha256"], "policy": policy, "inputs": {role: {"run_id": item.get("run_id"), "source_hashes": item.get("source_hashes", {})} for role, item in roles}}
    analysis_id = _sha(_canonical(identity))
    result = _portable_provenance(analyze_run(run, calibration=calibration, policy=policy), roles)
    result["analyzer_version"] = __version__
    result["implementation_sha256"] = implementation["sha256"]
    result["analysis_id"] = analysis_id
    # Bundled links refer to exact verified source copies, with no dependency on
    # the original absolute paths when the HTML folder is moved or shared.
    sources = []
    for role, item in roles:
        for relative, digest in sorted(item.get("source_hashes", {}).items()):
            href = "Sources/" + role + "/" + relative
            sources.append({"label": role + "/" + relative, "path": relative, "role": role, "run_id": item.get("run_id"), "href": quote(href, safe="/-._~"), "sha256": str(digest).upper()})
    result["sources"] = sources
    core = {"Analysis.json": _json_bytes(result), "Summary.csv": render_summary_csv(result).encode("utf-8-sig"), "Report.html": render_report(result).encode("utf-8")}
    root = _output_path(output_root if output_root is not None else source_dir / "Analysis")
    for _, item in roles:
        raw_dir = Path(item["source_dir"]) / "Raw"
        if root == raw_dir or root.is_relative_to(raw_dir):
            raise AnalyzerError("원본 Raw 폴더 안에는 분석 결과를 저장할 수 없습니다.")
    root.mkdir(parents=True, exist_ok=True)
    if _reparse(root):
        raise AnalyzerError("분석 저장 폴더가 링크 경로입니다.")
    target = root / (__version__ + "_" + analysis_id[:12])
    output_hashes = {name: _sha(data) for name, data in core.items()}
    for source in sources:
        # percent-encoded href is for HTML only, the physical bundle path is the
        # original relative source filename under a fixed role directory.
        output_hashes["Sources/" + source["role"] + "/" + source["path"]] = source["sha256"]
    receipt = {"schema_version": 1, "analyzer_version": __version__, "implementation_sha256": implementation["sha256"], "implementation_files": implementation["files"], "analysis_id": analysis_id, "inputs": identity["inputs"], "policy": policy, "source_integrity_verified": True, "artifacts": output_hashes, "manifest_excludes_itself": True}
    core["AnalysisManifest.json"] = _json_bytes(receipt)
    expected = {**output_hashes, "AnalysisManifest.json": _sha(core["AnalysisManifest.json"])}
    if target.exists():
        _validate_sources(roles)
        _validate_implementation(implementation)
        if _existing_matches(target, expected):
            return target, result, True
        raise AnalyzerError("같은 분석 ID의 기존 결과가 변경돼 덮어쓰지 않았습니다: " + str(target))
    staging = root / (".staging-" + analysis_id[:12] + "-" + uuid.uuid4().hex[:8])
    staging.mkdir(exist_ok=False)
    try:
        for role, item in roles:
            base = Path(item["source_dir"])
            for relative, expected_hash in sorted(item.get("source_hashes", {}).items()):
                data = _source_file(base, relative).read_bytes()
                if _sha(data) != str(expected_hash).upper():
                    raise AnalyzerError("원본 파일이 복사 전에 변경됐습니다: " + relative)
                destination = staging / "Sources" / role / relative
                destination.parent.mkdir(parents=True, exist_ok=True)
                if destination.exists():
                    raise AnalyzerError("분석 원본 복사 경로가 중복됩니다: " + relative)
                with destination.open("xb") as stream:
                    stream.write(data)
        for name, data in core.items():
            with (staging / name).open("xb") as stream:
                stream.write(data)
        _validate_sources(roles)
        _validate_implementation(implementation)
        if not _existing_matches(staging, expected):
            raise AnalyzerError("저장한 분석 산출물의 해시가 일치하지 않습니다.")
        if target.exists():
            if _existing_matches(target, expected):
                # Preserve this harmless staging folder rather than delete any
                # directory during a simultaneous invocation.
                return target, result, True
            raise AnalyzerError("동시에 같은 분석 ID의 다른 결과가 생성됐습니다.")
        os.rename(staging, target)  # Windows refuses replacement of an existing directory.
    except Exception as error:
        try:
            (staging / "Failure.txt").write_text(str(error), encoding="utf-8")
        except OSError:
            pass
        if isinstance(error, AnalyzerError):
            raise
        raise AnalyzerError("분석 결과 저장을 완료하지 못했습니다: " + str(error)) from error
    return target, result, False


def _exit_code(result):
    return 0 if result.get("measurement_status") in ("PASS", "WARNING") else 2


def _open_report(bundle):
    webbrowser.open((bundle / "Report.html").resolve().as_uri())


def _gui():
    try:
        import tkinter as tk
        from tkinter import filedialog, messagebox
    except ImportError as error:
        raise AnalyzerError("Python의 tkinter가 필요합니다. 또는 폴더 경로를 지정하는 명령행 실행을 사용하세요.") from error
    app = tk.Tk()
    app.title("RTR Benchmark Analyzer")
    app.geometry("460x150")
    app.resizable(False, False)
    tk.Label(app, text="실측 Run 폴더를 선택하면 Summary.csv와 Report.html을 만듭니다.", wraplength=420, justify="left", font=("Malgun Gothic", 12), padx=20, pady=24).pack(fill="both", expand=True)
    # A visible owner keeps Windows' native directory chooser discoverable and
    # prevents a modal dialog being attached only to a withdrawn Tk window.
    app.update_idletasks()
    app.update()
    try:
        initial = Path.home() / "Documents" / "Unreal Projects" / "RTR_Advanced" / "Saved" / "URBenchmark"
        run_dir = filedialog.askdirectory(parent=app, title="분석할 URBenchmark 결과 폴더 선택", initialdir=str(initial if initial.is_dir() else Path.home()), mustexist=True)
        if not run_dir:
            return 0
        use_reference = messagebox.askyesnocancel("A/A Calibration 연결", "별도로 측정한 A/A Calibration 결과를 연결할까요?\n\n같은 Run에 A/A를 함께 수집했다면 아니요를 선택하세요. 연결하지 않아도 분석할 수 있으며 비교 Confidence가 보류될 수 있습니다.", parent=app)
        if use_reference is None:
            return 0
        calibration_dir = None
        if use_reference:
            calibration_dir = filedialog.askdirectory(parent=app, title="연결할 A/A Calibration 결과 폴더 선택", initialdir=str(Path(run_dir).parent), mustexist=True)
            if not calibration_dir:
                return 0
        try:
            bundle, result, reused = analyze_to_bundle(run_dir, calibration_dir)
            _open_report(bundle)
            title = "분석 완료" if _exit_code(result) == 0 else "측정 자료 확인 필요"
            text = f"상태: {result.get('measurement_status', 'UNAVAILABLE')}\n\n리포트 위치:\n{bundle / 'Report.html'}\n\n" + ("같은 입력·정책의 기존 결과를 확인했습니다." if reused else "원본 CSV를 보존한 새 분석 결과를 저장했습니다.")
            (messagebox.showinfo if _exit_code(result) == 0 else messagebox.showwarning)(title, text, parent=app)
            return _exit_code(result)
        except (AnalyzerError, OSError, ValueError, TypeError) as error:
            messagebox.showerror("분석을 완료하지 못했습니다", str(error), parent=app)
            return 2
    finally:
        app.destroy()


def main(argv=None):
    parser = argparse.ArgumentParser(description="RTR Universal Rendering Benchmark 오프라인 분석")
    parser.add_argument("run_dir", nargs="?", type=Path, help="Raw·Manifest·Completion이 있는 측정 결과 폴더")
    parser.add_argument("--calibration", type=Path, help="별도 A/A Calibration 결과 폴더")
    parser.add_argument("--policy", type=Path, help="평가 정책 JSON")
    parser.add_argument("--output-root", type=Path, help="분석 묶음을 만들 상위 폴더")
    parser.add_argument("--open", action="store_true", help="완료 후 HTML 리포트 열기")
    parser.add_argument("--gui", action="store_true", help="결과 폴더 선택 창 사용")
    args = parser.parse_args(argv)
    try:
        if args.gui or args.run_dir is None:
            if args.run_dir is not None or args.calibration or args.policy or args.output_root or args.open:
                parser.error("--gui는 다른 분석 옵션과 함께 사용할 수 없습니다.")
            return _gui()
        bundle, result, reused = analyze_to_bundle(args.run_dir, args.calibration, args.policy, args.output_root)
        print(json.dumps({"status": result.get("measurement_status"), "report": str(bundle / "Report.html"), "analysis_id": result.get("analysis_id"), "reused": reused}, ensure_ascii=False))
        if args.open:
            _open_report(bundle)
        return _exit_code(result)
    except (AnalyzerError, OSError, ValueError, TypeError) as error:
        print("URB Analyzer: " + str(error), file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
