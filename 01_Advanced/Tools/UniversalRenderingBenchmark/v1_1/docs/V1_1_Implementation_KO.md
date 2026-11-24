# Report V1.1 Implementation and Validation

> Updated: 2026-11-03 KST · Product: Report V1.1 · Analyzer: 0.4.0

## Result

측정 결과의 의미를 첫 화면에서 읽을 수 있도록 한국어 결론·근거·추천 다음 행동과 실제 A/B 설정을 추가했다. 현재 V1을 보존하고 `UniversalRenderingBenchmark/v1_1/`에 별도 배치한다. Master Specification·Phase 3/4 구현·User Guide와 실제 Scalar Report를 검토한 범위는 [Document Review Notes](Interpretation_Guide_Review_Notes.md)에 기록했다.

## Changes

| File / Area | 변경 내용 |
|---|---|
| `analyzer/urb_analyzer/report.py` | 결론 우선 표시, 독립 상태, Action별 A/B 설정, 7개 Metric 도움말, CPU·기술 정보 접기, 가독성·반응형·CSP |
| `analyzer/urb_analyzer/__init__.py` | Analyzer 버전을 `0.4.0`으로 구별하여 새 Analysis ID 생성 |
| `Analyze.pyw`, `Analyze.cmd` | V1.1 전용 진입점 추가 |
| `docs/Benchmark_Report_Interpretation_Guide_KO.md` | 실제 Scalar 수치·독립 상태·판정별 행동·Metric·CPU·증거 보존 해석 가이드 |
| `tests/test_v11.py`, 검증 Script·Evidence | 기존 회귀 검사에 V1.1 해석·안전성·Action 의미 검증 추가 |
| `examples/`, `Figures/V1_1/` | 동일 실측의 새 Report·원본 Report·실제 브라우저 화면 보존 |

기존 패키지와 비교한 코드 변경은 `report.py`, `__init__.py` 두 파일이다. `analysis.py`, `ingest.py`, `policy.json`, `cli.py`, `__main__.py`는 바이트가 동일하다. `SUMMARY_COLUMNS`, `_csv_cell`, `render_summary_csv`의 소스도 동일하다. 측정·통계·Confidence·등급·Raw·Manifest와 Native 실행 경로를 변경하지 않았다.

Scalar는 숫자 설정으로 표시하며 `0/1`을 일반적인 OFF/ON으로 단정하지 않는다. ActorVisibility는 Actor의 HiddenInGame과 Component의 Visible/HiddenInGame을 구별하고 ShadowPolicy를 보존한다. 추천 행동은 A/B 판정과 독립된 GPU Budget YELLOW/RED도 설명한다.

## Actual Scalar Example

| Item | 기존 V1 / V1.1 동일 결과 |
|---|---|
| RunID | `20261103T114935_URB4_Scalar_30CCDBF0` |
| Setting | `ScalarParameter · URB_Blend · A=0 → B=1` |
| GPU A / B | `2.9288 / 2.92615 ms` (4자리 표시 B=`2.9261`) |
| Delta / Noise Floor | `-0.00265 / 0.0509 ms` (표시 Delta=`-0.0027`) |
| Measurement / Confidence / Impact | `PASS / INCONCLUSIVE / INCONCLUSIVE` |
| GPU Budget A / B | `GREEN / GREEN` |
| Old / New Analysis | `0.3.1_C8B6BCA5E40C` / `0.4.0_4CF2BD549D9F` |

Delta 절댓값이 Noise Floor 이하여서 우열 판단을 보류한다. GPU Budget GREEN은 장면 전체 GPU 대표값이 예산 이내라는 별도 평가다. CPU/Frame 세 Metric도 이번 자료에서는 INCONCLUSIVE이므로 음수 CPU Delta를 개선 확정으로 읽지 않는다. 새 Unreal Capture를 실행한 결과가 아니라 같은 Raw의 재분석이다.

## Regression and Reproducibility

| Check | 검증 결과 / Evidence |
|---|---|
| Original V1 tests | 85개 중 83개 통과·2개 Skip |
| V1.1 tests | 96개 중 94개 통과·2개 Skip / [Unit Regression](../evidence/Unit_Regression.json) |
| Complete result equality | 버전·구현 SHA·Analysis ID 세 식별 필드 외 전체 Analysis 값 동일 |
| Summary CSV | AnalyzerVersion 외 전 열·행 내용 동일, 생성 소스 동일 |
| Determinism | 동일 입력 재실행은 같은 Analysis ID·경로·바이트를 재사용, 출력 위치가 달라도 파일 바이트 동일 |
| Immutable evidence | 실제 Run·이전 Report·Source 해시 불변, 16개 Source·18개 로컬 링크·산출물 SHA 검증 통과 |
| Preservation | 기존 V1·실제 Run·Plugin 보호 파일 3,059개 변경 없음 / Protection |

상세 비교는 [Reproducibility Regression](../evidence/Reproducibility_Regression.json)과 V1.1 Test Log를 따른다. 두 Skip은 이 Windows 계정의 symlink 생성 권한 제한이며 통과로 세지 않는다. 기존 테스트의 기대값을 수정하지 않았다. 기존 Phase4 설치본을 기준으로도 재검증했다.

## HTML and Visual Validation

실측 Scalar 1종과 UI 검증용 가상 판정 15종을 1440·768·390px의 실제 브라우저 Viewport에서 확인했다. `PASS/WARNING/FAIL/CANCELLED/UNSUPPORTED`, `IMPROVED/GREEN/YELLOW/RED/INCONCLUSIVE/UNAVAILABLE`, Calibration 단독·근거 부족·GPU 누락과 Budget 색상을 포함한다. 가상 자료는 Synthetic UI Verification으로 명확히 표시한다.

48개 화면의 페이지 가로 넘침·외부 요청·Script·깨진 문자가 없고 최소 글자 크기는 14px다. 긴 상세 표는 개별 가로 스크롤 영역을 사용한다. 결론·상태·설정의 배치와 Korean 글자·CPU 주의문·실패·Calibration·RED 화면을 사람이 확인했다. 실제 샘플의 Enter로 도움말 열기와 마우스로 닫기, Hover Title을 검증했다. Browser Verification에 자동 검증과 화면 확인을 기록했다.

HTML은 외부 자원·Script·Form을 사용하지 않으며 Content Security Policy를 포함한다. Metadata는 Escape하고 Source 링크는 안전한 상대 경로만 허용한다. 악의적인 Metadata·주소·비유한 값과 기존 CSV Formula Injection 방어의 회귀 검사를 통과했다.

검사는 독립 Headless Chrome에서 수행했다. 모바일 실기기의 터치 입력은 검증하지 않았다. Headless Touch Event는 전달됐지만 Disclosure Click으로 연결되지 않아 터치 조작 통과로 기록하지 않았다. Native HTML Disclosure의 키보드·마우스 동작과 반응형 표시를 검증 범위로 삼는다.

## Evidence and Use

[실측 V1.1 Report](../examples/ActualScalarReport/0.4.0_4CF2BD549D9F/Report.html), 원본 V1 Report, [해석 가이드](Benchmark_Report_Interpretation_Guide_KO.md)를 함께 확인한다. Figure는 [Desktop](../Figures/V1_1/Report_Scalar_Desktop.png), [390px](../Figures/V1_1/Report_Scalar_Narrow390.png), CPU / Technical Details에 보존한다.

기존 루트 Launcher는 V1을 유지한다. 새 리포트를 만들 때 `v1_1/Analyze.pyw`를 선택한다. 새 버전의 Analysis는 자체 SHA와 ID를 사용하므로 기존 V1과 바이트가 다른 것은 의도한 버전 구분이다. Raw·Manifest·통계·정책의 동일성과 Report 표시 버전의 차이를 구별한다.

이번 변경에는 새 Native Build·Production Asset·Unreal Project 설정·선택 Character Scene 전체 측정이 포함되지 않는다. 원본 Report·Raw와 Native V1의 검증 상태는 그대로 보존한다.
