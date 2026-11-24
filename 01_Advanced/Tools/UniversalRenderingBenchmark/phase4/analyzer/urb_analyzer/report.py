"""Dependency-free, offline presentation of verified URB analysis results.

The caller owns file creation and source bundling. This module never reads or
writes measurement files and never calculates a performance grade.
"""
from __future__ import annotations

import csv
from html import escape
import io
import json
import math
from pathlib import PurePosixPath
from urllib.parse import quote, unquote, urlsplit


METRICS = ("GPUTime", "FrameTime", "GameThreadTime", "RenderThreadTime")
METRIC_LABELS = {
    "GPUTime": "GPU Frame Time", "FrameTime": "Frame Time",
    "GameThreadTime": "Game Thread Time", "RenderThreadTime": "Render Thread Time",
}
_COLORS = {
    "GREEN": "green", "YELLOW": "yellow", "RED": "red", "IMPROVED": "blue",
    "RELIABLE": "green", "INCONCLUSIVE": "gray", "UNAVAILABLE": "gray",
    "PASS": "green", "WARNING": "yellow", "FAIL": "red", "CANCELLED": "gray",
    "UNSUPPORTED": "gray",
}
_VALID_MEASUREMENTS = {"PASS", "WARNING"}


def _json(value):
    return json.dumps(value, ensure_ascii=False, sort_keys=True, allow_nan=False, separators=(",", ":"))


def _check_result(result):
    if not isinstance(result, dict):
        raise TypeError("Analysis result must be a dictionary")
    # Reject NaN/Infinity anywhere, including metadata that is not displayed.
    _json(result)


def _e(value):
    return escape("UNAVAILABLE" if value is None else str(value), quote=True)


def _num(value):
    return float(value) if isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value) else None


def _fmt(value, digits=4, signed=False, suffix=""):
    number = _num(value)
    if number is None:
        return "UNAVAILABLE"
    return format(number, ("+" if signed else "") + f".{digits}f") + suffix


def _badge(value, label=None):
    code = str(value) if value in _COLORS else "UNAVAILABLE"
    return f'<span class="badge {_COLORS[code]}">{_e(label if label is not None else code)}</span>'


def _metric(result, name):
    metrics = result.get("metrics", {})
    return metrics.get(name, {}) if isinstance(metrics, dict) else {}


def _group(metric, name):
    value = metric.get(name, {})
    return value if isinstance(value, dict) else {}


def _effective_grades(result, metric):
    if result.get("measurement_status") not in _VALID_MEASUREMENTS:
        return {key: "UNAVAILABLE" for key in ("confidence", "impact_grade", "budget_grade_a", "budget_grade_b")}
    grades = {key: metric.get(key, "UNAVAILABLE") for key in ("confidence", "impact_grade", "budget_grade_a", "budget_grade_b")}
    if grades["confidence"] != "RELIABLE" and grades["impact_grade"] in ("GREEN", "YELLOW", "RED", "IMPROVED"):
        grades["impact_grade"] = "INCONCLUSIVE" if grades["confidence"] == "INCONCLUSIVE" else "UNAVAILABLE"
    if _num(metric.get("delta_ms")) is None:
        grades["impact_grade"] = "UNAVAILABLE"
    for key, suffix in (("a", "a"), ("b", "b")):
        group = _group(metric, key)
        if group.get("integrity_valid") is False or group.get("stability_valid") is False or _num(group.get("representative_ms")) is None:
            grades["budget_grade_" + suffix] = "UNAVAILABLE"
    return grades


def _local_href(value):
    """Allow bundled relative files only, never executable or remote URLs."""
    if not isinstance(value, str) or not value:
        return None
    try:
        parsed = urlsplit(value)
    except ValueError:
        return None
    if parsed.scheme or parsed.netloc or parsed.query or parsed.fragment:
        return None
    decoded = unquote(parsed.path)
    if decoded.startswith(("/", "\\")) or "\\" in decoded or ":" in decoded:
        return None
    if any(ord(c) < 32 or ord(c) == 127 for c in decoded):
        return None
    parts = PurePosixPath(decoded).parts
    if not parts or any(part in (".", "..") for part in parts):
        return None
    return quote(decoded, safe="/-._~")


def _source_rows(result):
    rows = []
    sources = result.get("sources", [])
    if isinstance(sources, dict):
        sources = [{"label": key, "sha256": value} for key, value in sources.items()]
    for source in sources:
        if not isinstance(source, dict):
            continue
        label = source.get("label", source.get("path", "Source"))
        href = _local_href(source.get("href"))
        name = f'<a href="{_e(href)}">{_e(label)}</a>' if href else _e(label)
        rows.append(f'<tr><td>{name}</td><td class="hash">{_e(source.get("sha256"))}</td></tr>')
    return "".join(rows) or '<tr><td colspan="2">원본 파일 연결 정보 없음</td></tr>'


def _list(items, empty="기록된 항목 없음"):
    if not items:
        return f'<p class="muted">{_e(empty)}</p>'
    return "<ul>" + "".join(f"<li>{_e(_json(item) if isinstance(item, (dict, list)) else item)}</li>" for item in items) + "</ul>"


def _kv_rows(values):
    return "".join(f'<tr><th scope="row">{_e(key)}</th><td>{_e(value)}</td></tr>' for key, value in values)


def _metadata_table(values):
    return "".join(f'<tr><th scope="row">{_e(key)}</th><td>{_e(_json(value) if isinstance(value, (dict, list)) else value)}</td></tr>' for key, value in sorted(values.items())) if isinstance(values, dict) else ""


def _bar(label, value, maximum, klass=""):
    number = _num(value)
    width = min(100.0, max(0.0, number / maximum * 100.0)) if number is not None and maximum > 0 else 0.0
    text = _fmt(value, suffix=" ms")
    return f'<div class="chart-row"><span>{_e(label)}</span><div class="bar-track" role="img" aria-label="{_e(label)} {_e(text)}"><div class="bar-fill {klass}" style="width:{width:.6f}%"></div></div><strong>{_e(text)}</strong></div>'


def _run_medians_table(metric, calibration_only=False):
    names = (("calibration_group", "A/A · 실제 A 상태"),) if calibration_only else (("a", "Variant A"), ("b", "Variant B"))
    rows = []
    for key, label in names:
        group = _group(metric, key)
        medians = group.get("run_medians_ms", [])
        formatted = " · ".join(_fmt(value) for value in medians) or "UNAVAILABLE"
        rows.append(f'<tr><th scope="row">{_e(label)}</th><td>{_e(group.get("run_count", 0))}</td><td class="median-list">{_e(formatted)}</td><td>{_e(_fmt(group.get("range_ms")))}</td></tr>')
    return '<div class="table-scroll"><table><caption>GPU Run Median · 단위 ms</caption><thead><tr><th>상태</th><th>유효 Run</th><th>각 Run Median</th><th>Range</th></tr></thead><tbody>' + "".join(rows) + '</tbody></table></div>'


def _capture_order(metric, calibration_only=False):
    keys = ("calibration_group",) if calibration_only else ("a", "b")
    runs = [run for key in keys for run in _group(metric, key).get("runs", []) if isinstance(run, dict)]
    if not runs:
        return "UNAVAILABLE"
    try:
        runs.sort(key=lambda run: int(run.get("capture_index", -1)))
    except (ValueError, TypeError):
        return "UNAVAILABLE"
    return " → ".join(str(run.get("variant", "?")) for run in runs)


def _budget_row(label, value, representative, grade, green_limit, yellow_limit, scale):
    number = _num(value)
    width = min(100.0, max(0.0, number / scale * 100.0)) if number is not None else 0.0
    visible_grade = grade if grade in ("GREEN", "YELLOW", "RED") else "UNAVAILABLE"
    klass = _COLORS[visible_grade]
    text = f'{_fmt(value, 2, suffix="%")} · {_fmt(representative, suffix=" ms")}'
    return f'<div class="budget-row"><div class="budget-top"><span>{_e(label)} {_badge(visible_grade)}</span><strong>{_e(text)}</strong></div><div class="budget-track" role="img" aria-label="{_e(label)} GPU 예산 사용률 {_e(_fmt(value, 2, suffix="%"))}"><div class="budget-fill {klass}" style="width:{width:.6f}%"></div><span class="budget-tick" style="left:{green_limit / scale * 100:.6f}%"></span><span class="budget-tick" style="left:{yellow_limit / scale * 100:.6f}%"></span></div></div>'


def _statistics_details(result):
    rows = []
    for name in METRICS:
        metric = _metric(result, name)
        for key, label in (("a", "A"), ("b", "B"), ("calibration_group", "A/A")):
            group = _group(metric, key)
            if not group:
                continue
            pooled = group.get("pooled", {})
            rows.append('<tr>' + "".join(f'<td>{_e(value)}</td>' for value in (
                METRIC_LABELS[name], label, group.get("run_count", 0), group.get("sample_count", 0),
                _fmt(group.get("representative_ms")), _fmt(group.get("range_ms")),
                _fmt(group.get("relative_spread_percent"), 2),
                _fmt(pooled.get("mean_ms")), _fmt(pooled.get("median_ms")), _fmt(pooled.get("p95_ms")),
                _fmt(group.get("median_of_run_p95_ms")), _fmt(pooled.get("min_ms")), _fmt(pooled.get("max_ms")),
            )) + '</tr>')
    pooled_table = '<div class="table-scroll"><table><caption>Metric별 집계 통계 · 단위 ms, Relative Spread만 %</caption><thead><tr><th>Metric</th><th>그룹</th><th>Run</th><th>Sample</th><th>Median of Run Medians</th><th>Run Median Range</th><th>Relative Spread %</th><th>Pooled Mean</th><th>Pooled Median</th><th>Pooled P95</th><th>Median of Run P95</th><th>Pooled Min</th><th>Pooled Max</th></tr></thead><tbody>' + ("".join(rows) or '<tr><td colspan="13">통계 없음</td></tr>') + '</tbody></table></div>'
    rows = []
    for name in METRICS:
        metric = _metric(result, name)
        for key, label in (("a", "A"), ("b", "B"), ("calibration_group", "A/A")):
            for run in _group(metric, key).get("runs", []):
                stats = run.get("stats", {})
                rows.append('<tr>' + "".join(f'<td>{_e(value)}</td>' for value in (
                    METRIC_LABELS[name], label, run.get("capture_index"), run.get("mode"), stats.get("sample_count", 0),
                    _fmt(stats.get("mean_ms")), _fmt(stats.get("median_ms")), _fmt(stats.get("p95_ms")),
                    _fmt(stats.get("min_ms")), _fmt(stats.get("max_ms")), run.get("file"),
                )) + '</tr>')
    run_table = '<div class="table-scroll"><table><caption>각 Capture 통계 · 단위 ms</caption><thead><tr><th>Metric</th><th>그룹</th><th>Capture Index</th><th>Mode</th><th>Sample</th><th>Mean</th><th>Median</th><th>P95</th><th>Min</th><th>Max</th><th>원본 CSV</th></tr></thead><tbody>' + ("".join(rows) or '<tr><td colspan="11">Capture 통계 없음</td></tr>') + '</tbody></table></div>'
    metric_reasons = "".join(f'<h3>{_e(METRIC_LABELS[name])}</h3>{_list(_metric(result, name).get("reasons", []))}' for name in METRICS)
    return f'<details class="panel"><summary>전체 통계와 Metric별 판정 근거</summary><p class="caption">P95는 nearest-rank 방식입니다. Pooled P95는 모든 유효 프레임을 합친 값이며 각 Run P95의 중앙값과 구별합니다. 화면의 반올림은 판정에 사용하지 않습니다.</p>{pooled_table}{run_table}<div class="metric-reasons">{metric_reasons}</div></details>'


CSS = r"""
:root{color-scheme:dark;--bg:#10151c;--card:#19212c;--line:#303c4c;--fg:#e9eef5;--muted:#a8b7c9;--green:#6fdec2;--yellow:#f2cd73;--red:#ff8c92;--blue:#94b9ff}
*{box-sizing:border-box}body{margin:0;background:radial-gradient(ellipse at 15% 8%,#1d2b37 0,transparent 35%),var(--bg);font:14px/1.65 "Segoe UI","Malgun Gothic",sans-serif;color:var(--fg)}a{color:#add0ff;text-decoration:underline;text-underline-offset:3px}a:focus-visible,summary:focus-visible{outline:2px solid var(--yellow);outline-offset:4px}.banner{background:#18352f;border-bottom:1px solid #386b5f;padding:9px 32px;color:#b9eddf;font-size:12px;display:flex;justify-content:space-between;gap:12px}.wrap{max-width:1280px;margin:auto;padding:30px 32px 36px}.brand{font-size:12px;letter-spacing:.17em;color:var(--green);font-weight:700}.header{display:flex;justify-content:space-between;align-items:center;gap:24px;margin:6px 0 23px}h1{font-size:32px;letter-spacing:-.025em;margin:3px 0 7px;line-height:1.3;overflow-wrap:anywhere}h2{font-size:17px;margin:0 0 5px}h3{font-size:14px;margin:18px 0 8px}.sub,.caption,.muted{color:var(--muted);font-size:12px}.caption{margin:4px 0 17px}.badge{border-radius:5px;display:inline-block;padding:5px 9px;font-size:12px;font-weight:700;white-space:nowrap}.green{background:#1d3e37;color:var(--green);border:1px solid #3b7869}.yellow{background:#493c22;color:var(--yellow);border:1px solid #836a34}.red{background:#45292f;color:var(--red);border:1px solid #82454f}.gray{background:#2a3340;color:#c5d0dd;border:1px solid #536173}.blue{background:#243751;color:var(--blue);border:1px solid #496994}.statusbar{display:flex;gap:12px;flex-wrap:wrap;padding:14px 17px;background:#17202a;border:1px solid var(--line);border-radius:7px;margin-bottom:18px;font-size:12px;align-items:center}.statusbar strong{margin-right:5px}.run-id{overflow-wrap:anywhere;font-size:12px}.cards{display:grid;grid-template-columns:repeat(3,1fr);gap:15px;margin-bottom:18px}.card,.panel{background:linear-gradient(145deg,#1d2733,#17202a);border:1px solid var(--line);border-radius:8px}.card{padding:19px 21px;min-width:0}.label{color:var(--muted);font-size:12px}.value{font-size:36px;letter-spacing:-.035em;font-weight:650;margin:7px 0;line-height:1.25;overflow-wrap:anywhere}.value.unavailable{font-size:21px;color:#b8c5d5}.unit{font-size:16px;font-weight:400;letter-spacing:0;color:#b9c7d8;margin-left:5px}.card p{margin:7px 0 0;font-size:12px;color:#b6c4d3}.two-col,.foot-grid{display:grid;grid-template-columns:1fr 1fr;gap:18px;margin-bottom:18px}.panel{padding:21px 22px;min-width:0;margin-bottom:18px}.two-col>.panel,.foot-grid>.panel{margin-bottom:0}.measure-head{display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap}.chart-row{display:grid;grid-template-columns:65px 1fr 99px;align-items:center;gap:10px;margin:18px 0;font-size:12px}.chart-row strong{text-align:right;font-size:12px}.bar-track{height:27px;background:#101821;border-radius:4px;position:relative}.bar-fill{height:100%;border-radius:4px;background:#6f9ac1;box-shadow:inset 0 1px #ffffff30}.bar-fill.b{background:#d4af64}.axis{margin:0 109px 0 75px;display:flex;justify-content:space-between;font-size:12px;color:var(--muted)}.impact-number{font-size:29px;font-weight:650;margin:12px 0 14px;line-height:1.35}.impact-number small{font-size:12px;color:#bbc9da;font-weight:400;display:block;margin-top:4px}.formula{font-size:12px;line-height:1.9;color:#b5c4d6;background:#121b25;border-radius:4px;padding:11px 12px;overflow-wrap:anywhere}.thresholds{font-size:12px;color:#b5c4d6;margin:15px 0}.budget-row{margin:16px 0 19px}.budget-top{display:flex;justify-content:space-between;align-items:center;gap:12px;font-size:12px;margin-bottom:8px;flex-wrap:wrap}.budget-track{height:12px;position:relative;background:#101821;border-radius:3px}.budget-fill{height:100%;border:0;border-radius:3px}.budget-tick{position:absolute;top:-4px;height:20px;border-left:1px dashed #cfdeea88}.ticks{display:flex;justify-content:space-between;color:var(--muted);font-size:12px}.table-scroll{overflow-x:auto;max-width:100%}table{width:100%;border-collapse:collapse;font-size:12px;text-align:left}caption{text-align:left;color:var(--muted);font-size:12px;padding:11px 0 8px}th,td{border-top:1px solid var(--line);padding:8px 7px;vertical-align:top}thead th{color:#b3c2d3;font-weight:500;white-space:nowrap}td:not(:first-child){font-variant-numeric:tabular-nums}th[scope=row]{font-weight:500}.median-list{overflow-wrap:anywhere}.metadata td{overflow-wrap:anywhere;white-space:pre-wrap}.metadata th{width:34%;overflow-wrap:anywhere}.hash{font:12px/1.8 Consolas,monospace;overflow-wrap:anywhere;word-break:break-all;min-width:180px}.summary-box{border-left:3px solid #7794b4;background:#1c2937;padding:17px 20px;margin-bottom:18px;border-radius:4px}.summary-box p{margin:0;font-size:13px;line-height:1.9}.warning-box{border-left:3px solid var(--yellow)}.error-box{border-left:3px solid var(--red)}ul{padding-left:21px;margin:8px 0}li{font-size:12px;line-height:1.85;margin:4px 0;overflow-wrap:anywhere}details>summary{cursor:pointer;font-size:14px;font-weight:650}details[open]>summary{margin-bottom:16px}.metric-reasons{margin-top:18px}.policy-text{font-size:12px;line-height:1.9;color:#b9c6d6}.source-table td:first-child{max-width:340px;overflow-wrap:anywhere}pre{white-space:pre-wrap;overflow-wrap:anywhere;font:12px/1.8 Consolas,"Malgun Gothic",monospace;margin:12px 0 0}.definition{font-size:12px;line-height:1.9;color:#b5c4d5}footer{margin-top:24px;font-size:12px;color:#9dadc0;display:flex;justify-content:space-between;gap:16px;flex-wrap:wrap}code{font:12px/1.8 Consolas,monospace;overflow-wrap:anywhere}.sr-only{position:absolute;width:1px;height:1px;margin:-1px;overflow:hidden;clip:rect(0,0,0,0);white-space:nowrap}
@media(max-width:900px){.two-col,.foot-grid{grid-template-columns:1fr}.wrap{padding:24px 18px}.banner{padding:9px 18px}.header{display:block}.header>.badge{margin-top:13px}h1{font-size:27px}.cards{gap:9px}.card{padding:16px 13px}.value{font-size:29px}}
@media(max-width:600px){.cards{grid-template-columns:1fr}.panel{padding:18px 14px}.banner{display:block}.banner span{display:block}.header{margin-bottom:18px}.chart-row{grid-template-columns:48px 1fr 93px;gap:7px}.axis{margin-left:55px;margin-right:100px}.metadata th{width:38%}.statusbar{gap:8px}.value.unavailable{font-size:22px}}
@media print{body{background:white;color:#111}.wrap{max-width:none;padding:12px}.card,.panel,.statusbar,.summary-box{background:white;border-color:#aaa;color:#111;break-inside:avoid}.sub,.caption,.muted,.label,.policy-text,.definition,footer{color:#444}.banner{background:white;color:#111}.two-col,.foot-grid{grid-template-columns:1fr}.table-scroll{overflow:visible}th,td{border-color:#ccc}.badge{color:#111;background:#eee;border-color:#888}details{display:block}.bar-track,.budget-track{border:1px solid #888}a{color:#111}.hash{min-width:0}}
"""


def render_report(result: dict) -> str:
    """Render actual analyzed values as a portable HTML document."""
    _check_result(result)
    gpu = _metric(result, "GPUTime")
    a, b, aa = (_group(gpu, key) for key in ("a", "b", "calibration_group"))
    grades = _effective_grades(result, gpu)
    calibration_only = result.get("analysis_mode") == "CalibrationOnly"
    environment = result.get("environment", {})
    policy = result.get("policy", {})
    policy = policy if isinstance(policy, dict) else {}
    target = result.get("target_fps")
    frame_budget = result.get("frame_budget_ms")
    title = result.get("test_name") or result.get("test_id") or "RTR Benchmark"
    scene = environment.get("scene_type", environment.get("sceneType", "UNAVAILABLE"))
    gpu_name = environment.get("gpu", "UNAVAILABLE")
    rhi = environment.get("rhi", "UNAVAILABLE")
    feature = environment.get("feature_level", environment.get("featureLevel", "UNAVAILABLE"))
    resolution = environment.get("resolution", environment.get("actualResolution", "UNAVAILABLE"))
    status = result.get("measurement_status", "UNAVAILABLE")
    impact_green = _num(policy.get("impact_green_max_percent"))
    impact_yellow = _num(policy.get("impact_yellow_max_percent"))
    budget_green = _num(policy.get("budget_green_max_percent"))
    budget_yellow = _num(policy.get("budget_yellow_max_percent"))

    def card(label, value, note, *, unit="ms", digits=4, signed=False):
        number = _num(value)
        text = _fmt(value, digits, signed) if number is not None else "UNAVAILABLE"
        suffix = f'<span class="unit">{_e(unit)}</span>' if number is not None and unit else ""
        unavailable = " unavailable" if number is None else ""
        return f'<div class="card"><div class="label">{_e(label)}</div><div class="value{unavailable}">{_e(text)}{suffix}</div><p>{_e(note)}</p></div>'

    if calibration_only:
        cards = card("A/A · 실제 A 상태의 GPU", aa.get("representative_ms"), "Calibration Run Median들의 중앙값") + card("A/A Run Median Range", aa.get("range_ms"), "Run Median의 최대 − 최소") + card("유효 Calibration Runs", aa.get("run_count"), f'유효 Sample {aa.get("sample_count", 0)}개', unit="runs", digits=0)
        comparison = _bar("A/A", aa.get("representative_ms"), max(_num(aa.get("representative_ms")) or 0, 0.001) * 1.25)
        comparison_note = "동일한 실제 A 상태를 반복한 Calibration입니다. A/B 차이와 Impact Grade를 판정하지 않습니다."
    else:
        cards = card("VARIANT A · BASELINE GPU", a.get("representative_ms"), "각 Run Median의 중앙값") + card("VARIANT B · CANDIDATE GPU", b.get("representative_ms"), "각 Run Median의 중앙값") + card("GPU DELTA · B − A", gpu.get("delta_ms"), f'A 대비 {_fmt(gpu.get("delta_percent_baseline"), 2, True, "%")} · 예산 대비 {_fmt(gpu.get("impact_percent_budget"), 2, True, "%")}', signed=True)
        maximum = max(_num(a.get("representative_ms")) or 0, _num(b.get("representative_ms")) or 0, 0.001) * 1.25
        comparison = _bar("A", a.get("representative_ms"), maximum) + _bar("B", b.get("representative_ms"), maximum, "b")
        comparison += f'<div class="axis"><span>0</span><span>{_e(_fmt(maximum / 2, 2))}</span><span>{_e(_fmt(maximum, 2))} ms</span></div>'
        comparison_note = "낮을수록 빠름 · 같은 Metric의 A/B를 비교합니다."

    delta = gpu.get("delta_ms")
    noise = gpu.get("noise_floor_ms")
    impact_value = gpu.get("impact_percent_budget")
    budget_scale = max(120.0, budget_yellow or 0, (_num(gpu.get("budget_usage_percent_a")) or 0) * 1.05, (_num(gpu.get("budget_usage_percent_b")) or 0) * 1.05)
    budget_rows = ""
    if budget_green is not None and budget_yellow is not None and 0 <= budget_green < budget_yellow:
        budget_rows = _budget_row("Variant A", gpu.get("budget_usage_percent_a"), a.get("representative_ms"), grades["budget_grade_a"], budget_green, budget_yellow, budget_scale) + _budget_row("Variant B", gpu.get("budget_usage_percent_b"), b.get("representative_ms"), grades["budget_grade_b"], budget_green, budget_yellow, budget_scale)
    else:
        budget_rows = '<p class="muted">유효한 Budget 정책이 없어 예산 막대를 표시하지 않습니다.</p>'
    confidence_empty_reason = (
        "기록한 조건이 일치하는 A/A 연결, 필요한 반복 수와 반복 안정성 검사를 통과했고, 실제 A/B 차이의 절댓값이 Noise Floor보다 큽니다."
        if grades["confidence"] == "RELIABLE" else "판정 이유가 제공되지 않았습니다."
    )
    confidence_rows = _kv_rows((
        ("A/A Baseline Variation", f'{_fmt(gpu.get("range_aa_ms"), suffix=" ms")} · {_fmt(gpu.get("relative_spread_aa_percent"), 2, suffix="%") }'),
        ("A/B Run-to-Run Variation", f'A {_fmt(gpu.get("range_a_ms", a.get("range_ms")), suffix=" ms")} · B {_fmt(gpu.get("range_b_ms", b.get("range_ms")), suffix=" ms")}'),
        ("Estimated Noise Floor", _fmt(noise, suffix=" ms")),
        ("Actual A/B Delta", _fmt(delta, signed=True, suffix=" ms")),
    ))
    cpu_rows = []
    for name in METRICS[1:]:
        metric = _metric(result, name)
        left = _group(metric, "calibration_group" if calibration_only else "a")
        right = _group(metric, "b")
        values = (METRIC_LABELS[name], _fmt(left.get("representative_ms"), suffix=" ms"), _fmt(left.get("range_ms"), suffix=" ms") if calibration_only else _fmt(right.get("representative_ms"), suffix=" ms"), _fmt(metric.get("delta_ms"), signed=True, suffix=" ms"), metric.get("confidence", "UNAVAILABLE"))
        cpu_rows.append('<tr>' + "".join(f'<td>{_e(value)}</td>' for value in values) + '</tr>')
    warning_panels = ""
    if result.get("errors"):
        warning_panels += '<section class="panel error-box"><h2>분석 오류</h2>' + _list(result["errors"]) + '</section>'
    if result.get("warnings"):
        warning_panels += '<section class="panel warning-box"><h2>확인할 사항</h2>' + _list(result["warnings"]) + '</section>'
    if status not in _VALID_MEASUREMENTS:
        interpretation = "완료된 유효 A/B 측정으로 해석할 수 없습니다. 남아 있는 수치는 원인 확인용이며 GPU Impact와 Budget Grade를 부여하지 않습니다."
    elif calibration_only:
        interpretation = "같은 실제 A 상태의 반복 변동을 확인한 Calibration 결과입니다. 별도 A/B 측정과 환경이 일치하는지 확인한 뒤 비교 분석에 연결합니다."
    elif grades["confidence"] != "RELIABLE":
        interpretation = f'관측 GPU 차이는 {_fmt(delta, signed=True, suffix=" ms")}입니다. {_fmt(noise, suffix=" ms")}의 Noise Floor와 Calibration·반복 안정성·조건 일치 근거를 함께 확인해야 합니다. 현재 비교 판정은 {grades["confidence"]}이며 비용이 없다는 의미가 아닙니다.'
    else:
        interpretation = f'GPU 시간은 A 대비 {_fmt(delta, signed=True, suffix=" ms")} 변화했습니다. Baseline 대비 {_fmt(gpu.get("delta_percent_baseline"), 2, True, "%")}, 목표 프레임 예산 대비 {_fmt(impact_value, 2, True, "%")}이며 Impact는 {grades["impact_grade"]}입니다. 이 결과는 기록된 장면과 조건에 해당합니다.'
    calibration = result.get("calibration", {})
    calibration_text = json.dumps(calibration, ensure_ascii=False, sort_keys=True, indent=2, allow_nan=False)
    policy_text = json.dumps(policy, ensure_ascii=False, sort_keys=True, indent=2, allow_nan=False)
    aa_note = "A/A Calibration · A/B 비교 없음" if calibration_only else "GPU와 CPU를 구분한 실제 CSV 분석"
    return f'''<!doctype html>
<html lang="ko"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><meta name="referrer" content="no-referrer"><title>{_e(title)} · RTR Performance Report</title><style>{CSS}</style></head>
<body><div class="banner"><span>실측 CSV 분석 · 오프라인 리포트</span><span>{_e(aa_note)}</span></div><main class="wrap">
<div class="brand">RTR / UNIVERSAL RENDERING BENCHMARK</div>
<header class="header"><div><h1>{_e(title)}</h1><div class="sub">{_e(scene)} · Target {_e(target)} FPS · {_e(gpu_name)} · {_e(resolution)} · {_e(rhi)} / {_e(feature)}</div></div>{_badge(grades["impact_grade"], "IMPACT · " + str(grades["impact_grade"]))}</header>
<div class="statusbar"><span><strong>Measurement Status</strong>{_badge(status)}</span><span><strong>Confidence</strong>{_badge(grades["confidence"])}</span><span><strong>GPU Budget A / B</strong>{_badge(grades["budget_grade_a"])} {_badge(grades["budget_grade_b"])}</span><span class="run-id">Test ID: {_e(result.get("test_id"))}<br>Run ID: {_e(result.get("run_id"))}</span></div>
{warning_panels}<section class="cards" aria-label="GPU 핵심 결과">{cards}</section>
<div class="two-col"><section class="panel"><h2>GPU Frame Time Comparison</h2><p class="caption">{_e(comparison_note)}</p>{comparison}{_run_medians_table(gpu, calibration_only)}<p class="caption">{"Calibration Capture 라벨 순서" if calibration_only else "Benchmark Capture 순서"}: {_e(_capture_order(gpu, calibration_only))}<br>대표값은 Run Median들의 중앙값입니다. 유효 Run·Sample 수는 아래 통계에서 확인합니다.</p></section>
<section class="panel"><div class="measure-head"><h2>Performance Impact</h2>{_badge(grades["impact_grade"])}</div><p class="caption">기능 변화에 따른 추가 GPU 시간 / 목표 프레임 예산</p><div class="impact-number">{_e(_fmt(impact_value, 2, True, "%"))}<small>{_e(_fmt(delta, signed=True, suffix=" ms"))} / {_e(_fmt(frame_budget, suffix=" ms"))}</small></div><div class="formula">FrameBudgetMs = 1000 / TargetFPS<br>ImpactPercentBudget = 100 × DeltaMs / FrameBudgetMs<br>DeltaPercentBaseline = 100 × DeltaMs / A_MedianOfRunMedians</div><p class="thresholds">GREEN ≤ {_e(_fmt(impact_green, 2))}% · YELLOW ≤ {_e(_fmt(impact_yellow, 2))}% · RED &gt; {_e(_fmt(impact_yellow, 2))}%<br>비교 Confidence가 충분할 때만 등급을 확정합니다. 반올림 전 원값으로 판정합니다.</p></section></div>
<div class="two-col"><section class="panel"><h2>GPU Frame Budget</h2><p class="caption">Target {_e(target)} FPS · GPU 시간 예산 {_e(_fmt(frame_budget, suffix=" ms"))}</p>{budget_rows}<div class="ticks"><span>0%</span><span>표시 축 상한 {_e(_fmt(budget_scale, 1))}%</span></div><p class="definition">GREEN ≤ {_e(_fmt(budget_green, 2))}% · YELLOW ≤ {_e(_fmt(budget_yellow, 2))}% · RED &gt; {_e(_fmt(budget_yellow, 2))}%<br>안정적인 절대 GPU 시간의 예산 사용률입니다. GPU Budget만으로 전체 시스템의 목표 FPS 달성을 보장하지 않습니다.</p></section>
<section class="panel"><div class="measure-head"><h2>Measurement Confidence</h2>{_badge(grades["confidence"])}</div><p class="caption">A/A와 A/B의 반복 변동 및 조건 일치</p><table><caption class="sr-only">GPU Confidence 판정 근거</caption><tbody>{confidence_rows}</tbody></table><h3>Confidence Evaluation Reason</h3>{_list(gpu.get("reasons", []), confidence_empty_reason)}<p class="definition">Range는 Run Median의 최대−최소입니다. Noise Floor는 AA·A·B Range와 최소 정책값의 최댓값입니다. 3회 반복을 통계적 유의성이나 신뢰구간으로 해석하지 않습니다.</p></section></div>
<section class="panel"><div class="measure-head"><h2>CPU / Frame Timing Comparison</h2>{_badge("UNAVAILABLE", "보조 지표 · GPU와 구분")}</div><p class="caption">각 Run Median의 중앙값 · 단위 ms</p><div class="table-scroll"><table><caption class="sr-only">CPU와 Frame 시간 비교</caption><thead><tr><th>Metric</th><th>{"A/A 대표값" if calibration_only else "Variant A"}</th><th>{"A/A Range" if calibration_only else "Variant B"}</th><th>Delta · B − A</th><th>Confidence</th></tr></thead><tbody>{''.join(cpu_rows)}</tbody></table></div><p class="definition">CPU와 GPU는 파이프라인으로 겹쳐 실행되므로 시간을 합산하지 않습니다. Frame Time은 전체 프레임 지표이고 Game/Render Thread 시간과 구분합니다. 이 표만으로 병목을 확정하지 않습니다.</p></section>
<section class="summary-box"><h2>결과 해석</h2><p>{_e(interpretation)}</p></section>
{_statistics_details(result)}
<div class="foot-grid"><section class="panel"><h2>측정 환경과 Action</h2><div class="table-scroll"><table class="metadata"><caption>기록된 실행 조건</caption><tbody>{_metadata_table(environment)}</tbody></table></div><details><summary>Action 적용 설정</summary><pre>{_e(json.dumps(result.get("action", {}), ensure_ascii=False, sort_keys=True, indent=2, allow_nan=False))}</pre></details></section><section class="panel"><h2>Calibration과 평가 정책</h2><p class="policy-text">Calibration은 매 A/B 실행 직전 필수가 아닙니다. 연결한 유효 A/A와 환경 Fingerprint가 일치해야 확정 비교를 해석할 수 있습니다.</p><details><summary>Calibration 연결과 상태</summary><pre>{_e(calibration_text)}</pre></details><details><summary>적용한 정책 원값</summary><pre>{_e(policy_text)}</pre></details><p class="policy-text">RTR 정책이며 Unreal 공식 등급이 아닙니다. 최소 Noise Floor와 변동 상한은 조정 가능한 초기 정책값이며 장비의 공식 오차나 통계 검정 결과가 아닙니다.</p></section></div>
<section class="panel"><h2>원본과 분석 산출물</h2><p class="caption">원본 CSV·Manifest는 수정하지 않습니다. 링크가 있는 파일은 이 리포트와 함께 보관된 복사본입니다. SHA-256으로 원본 동일성을 확인할 수 있습니다.</p><div class="table-scroll"><table class="source-table"><caption class="sr-only">원본 파일과 SHA-256</caption><thead><tr><th>파일</th><th>SHA-256</th></tr></thead><tbody>{_source_rows(result)}</tbody></table></div><div class="source-links"><a href="Summary.csv">Summary.csv</a> · <a href="Analysis.json">Analysis.json</a></div></section>
<footer><span>RTR Universal Rendering Benchmark Tool V1 · Offline Performance Report</span><span>Analyzer {_e(result.get("analyzer_version"))} · Schema {_e(result.get("schema_version"))} · Policy {_e(policy.get("version"))}</span></footer></main></body></html>'''


SUMMARY_COLUMNS = (
    "RowType", "TestID", "TestName", "RunID", "Metric", "Unit", "MeasurementStatus", "Confidence",
    "Variant", "Mode", "CaptureIndex", "ActualActionVariant", "RawFile", "RawSHA256",
    "RunSampleCount", "RunMeanMs", "RunMedianMs", "RunP95Ms", "RunMinMs", "RunMaxMs",
    "A_ValidRunCount", "B_ValidRunCount", "AA_ValidRunCount", "A_SampleCount", "B_SampleCount", "AA_SampleCount",
    "A_MedianOfRunMedians", "B_MedianOfRunMedians", "AA_MedianOfRunMedians", "A_MedianOfRunP95Ms", "B_MedianOfRunP95Ms", "AA_MedianOfRunP95Ms",
    "A_PooledMeanMs", "A_PooledMedianMs", "A_PooledP95Ms", "A_PooledMinMs", "A_PooledMaxMs",
    "B_PooledMeanMs", "B_PooledMedianMs", "B_PooledP95Ms", "B_PooledMinMs", "B_PooledMaxMs",
    "AA_PooledMeanMs", "AA_PooledMedianMs", "AA_PooledP95Ms", "AA_PooledMinMs", "AA_PooledMaxMs",
    "DeltaMs", "DeltaPercentBaseline", "TargetFPS", "FrameBudgetMs", "ImpactPercentBudget", "ImpactGrade",
    "BudgetUsagePercentA", "BudgetUsagePercentB", "BudgetGradeA", "BudgetGradeB",
    "RangeAA_Ms", "RangeA_Ms", "RangeB_Ms", "RelativeSpreadAA_Percent", "RelativeSpreadA_Percent", "RelativeSpreadB_Percent", "NoiseFloorMs",
    "Reasons", "ReasonCodes", "Warnings", "Errors", "AnalyzerVersion", "SchemaVersion", "PolicyVersion", "AnalysisMode",
    "CalibrationJSON", "PolicyJSON", "EnvironmentJSON", "ActionJSON", "SourcesJSON",
)


def _csv_cell(value):
    if value is None:
        return ""
    if isinstance(value, (int, float)) and not isinstance(value, bool):
        return value
    text = str(value)
    # Preserve numeric negative measurements while neutralizing untrusted text.
    if text.lstrip().lstrip("\ufeff").lstrip().startswith(("=", "+", "-", "@")) or (text and ord(text[0]) < 32):
        return "'" + text
    return text


def render_summary_csv(result: dict) -> str:
    """Return UTF-8 CSV content; caller may encode utf-8-sig for Excel."""
    _check_result(result)
    output = io.StringIO(newline="")
    writer = csv.DictWriter(output, fieldnames=SUMMARY_COLUMNS, lineterminator="\r\n", extrasaction="raise")
    writer.writeheader()
    for name in METRICS:
        metric = _metric(result, name)
        grades = _effective_grades(result, metric)
        a, b, aa = (_group(metric, key) for key in ("a", "b", "calibration_group"))
        row = {
            "RowType": "AGGREGATE", "TestID": result.get("test_id"), "TestName": result.get("test_name"), "RunID": result.get("run_id"),
            "Metric": name, "Unit": "ms", "MeasurementStatus": result.get("measurement_status"), "Confidence": grades["confidence"],
            "DeltaMs": metric.get("delta_ms"), "DeltaPercentBaseline": metric.get("delta_percent_baseline"), "TargetFPS": result.get("target_fps"),
            "FrameBudgetMs": result.get("frame_budget_ms"), "ImpactPercentBudget": metric.get("impact_percent_budget"), "ImpactGrade": grades["impact_grade"],
            "BudgetUsagePercentA": metric.get("budget_usage_percent_a"), "BudgetUsagePercentB": metric.get("budget_usage_percent_b"), "BudgetGradeA": grades["budget_grade_a"], "BudgetGradeB": grades["budget_grade_b"],
            "RangeAA_Ms": metric.get("range_aa_ms", aa.get("range_ms")), "RangeA_Ms": metric.get("range_a_ms", a.get("range_ms")), "RangeB_Ms": metric.get("range_b_ms", b.get("range_ms")),
            "RelativeSpreadAA_Percent": metric.get("relative_spread_aa_percent", aa.get("relative_spread_percent")), "RelativeSpreadA_Percent": a.get("relative_spread_percent"), "RelativeSpreadB_Percent": b.get("relative_spread_percent"), "NoiseFloorMs": metric.get("noise_floor_ms"),
            "Reasons": " | ".join(str(v) for v in metric.get("reasons", [])), "ReasonCodes": " | ".join(str(v) for v in metric.get("reason_codes", [])),
            "Warnings": " | ".join(str(v) for v in result.get("warnings", [])), "Errors": " | ".join(str(v) for v in result.get("errors", [])),
            "AnalyzerVersion": result.get("analyzer_version"), "SchemaVersion": result.get("schema_version"), "PolicyVersion": result.get("policy", {}).get("version"), "AnalysisMode": result.get("analysis_mode"),
            "CalibrationJSON": _json(result.get("calibration", {})), "PolicyJSON": _json(result.get("policy", {})), "EnvironmentJSON": _json(result.get("environment", {})), "ActionJSON": _json(result.get("action", {})), "SourcesJSON": _json(result.get("sources", [])),
        }
        for prefix, group in (("A", a), ("B", b), ("AA", aa)):
            row[prefix + "_ValidRunCount"] = group.get("run_count", 0)
            row[prefix + "_SampleCount"] = group.get("sample_count", 0)
            row[prefix + "_MedianOfRunMedians"] = group.get("representative_ms")
            row[prefix + "_MedianOfRunP95Ms"] = group.get("median_of_run_p95_ms")
            pooled = group.get("pooled", {})
            for suffix, stat in (("MeanMs", "mean_ms"), ("MedianMs", "median_ms"), ("P95Ms", "p95_ms"), ("MinMs", "min_ms"), ("MaxMs", "max_ms")):
                row[prefix + "_Pooled" + suffix] = pooled.get(stat)
        writer.writerow({key: _csv_cell(value) for key, value in row.items()})
        for key, label in (("a", "A"), ("b", "B"), ("calibration_group", "AA")):
            for run in _group(metric, key).get("runs", []):
                run_row = dict(row)
                stats = run.get("stats", {})
                run_row.update({"RowType": "RUN", "Variant": run.get("variant", label), "Mode": run.get("mode"), "CaptureIndex": run.get("capture_index"), "ActualActionVariant": run.get("actual_action_variant"), "RawFile": run.get("file"), "RawSHA256": run.get("sha256"), "RunSampleCount": stats.get("sample_count"), "RunMeanMs": stats.get("mean_ms"), "RunMedianMs": stats.get("median_ms"), "RunP95Ms": stats.get("p95_ms"), "RunMinMs": stats.get("min_ms"), "RunMaxMs": stats.get("max_ms")})
                writer.writerow({column: _csv_cell(value) for column, value in run_row.items()})
    return output.getvalue()
