# RTR Universal Rendering Benchmark Tool V1 Phase 3 구현 보고

작성일: 2026-11-03 KST · 범위: CSV Analyzer, GPU 평가 정책, 오프라인 HTML Report와 분석 Launcher

실제 Unreal CSV를 읽어 반복 통계·Summary.csv·Report.html을 생성하는 외부 Analyzer를 구현했다. 측정 상태·GPU Impact·절대 GPU Budget·비교 Confidence를 분리하며, 이전 단계 자료의 부족한 환경 증거를 추정하여 채우지 않는다. 실제 자료·정책·리포트와 원본 보호를 검증했다. 실제 마우스·키보드로 Launcher의 폴더 선택부터 브라우저 표시까지 완주하는 검사는 Phase 4에 남아 있으며 V1 전체 완료를 선언하지 않는다.

## 1. 구현 기능

Python 3.10 표준 라이브러리만 사용하는 외부 Analyzer를 추가했다. Native Runner는 환경 Metadata를 보완하며 기존 Action 처리와 Warmup·반복·CSV Capture Helper를 유지한다.

| 영역 | 구현 내용 |
|---|---|
| 입력 검사 | Manifest·Completion·CSV 식별·상태·정확한 열 이름·프레임·유한 값·중복 ID·안전한 경로 검사 |
| CSV Mapping | UE 5.8 실제 출력과 뒤에 추가되는 선택 통계 열 검증; GPU Pass·CPU로 GPUTime 대체 금지 |
| 통계 | Run별 Mean·Median·nearest-rank P95·Min·Max·Sample 수, Median of Run Medians, 별도 Pooled 통계 |
| 평가 | 조정 가능한 Impact 2%/5%, Budget 70%/100%, A/A·A/B Range·Noise Floor·독립 상태와 이유 |
| 리포트 | 실제 자료를 사용하는 GPU 중심 HTML, CPU 보조 표, A/A 진단, 정책·경고·원본 링크 |
| 분석 저장 | 입력·정책·분석 버전의 AnalysisID, Sources 복사본, 원본·산출물 해시와 재실행 일치 확인 |
| Launcher | Analyze.cmd 더블클릭 폴더 선택, 선택 Calibration 연결, 완료 HTML 열기와 CLI |
| Git 제외 | 개발 도구의 소스·문서·Asset·측정 결과가 있는 폴더 전체를 .gitignore에 등록 |

GPU Impact와 GPU Budget 정책은 GPUTime에만 적용한다. FrameTime·GameThreadTime·RenderThreadTime은 통계·변화량·안정성의 보조 자료이며 GPU 색상 기준을 적용하지 않는다.

## 2. 환경 증거와 판정 계약

Native schemaVersion 3의 Fingerprint에 Engine·GPU·Driver·OS·CPU·RHI, Camera Transform·FOV, 해상도·Screen Percentage, Scalability, 환경 CVar, SceneType·World, 원본 파일·Actor Transform·Runner Build 해시와 Action A 설정을 기록한다. CSV는 해당 Fingerprint를 참조한다. 정확한 Payload JSON의 UTF-8 SHA256과 객체 일치를 확인한 후 Canonical Payload를 A/A·A/B 조건 비교에 사용한다.

측정 전후 원본 해시의 일치와 Capture 전후 고정 환경 검증이 필요하다. 명시적으로 확인된 환경 변경은 정상 Budget 색상을 막고, Fingerprint 원문·객체·SHA256 무결성 오류는 분석 FAIL이다. 이전 Phase 1~2 Raw는 통계를 제공하되 완전한 환경 증거가 없으면 비교 Confidence를 보류한다.

Scene State Declared Static은 사용자의 장면 통제 선언이다. 자동 검사는 기록한 범위의 전후 조건을 확인하며 애니메이션·Material 내부 시간 효과·조명·배경 부하 등 장면의 모든 상태를 자동 증명하지 않는다. 이 선언은 기본값 false이고, 제어한 전용 장면에만 사용한다.

정책은 원래 Master Specification의 후보값을 유지한다. `NoiseFloor=max(RangeAA,RangeA,RangeB,0.05ms)`이며 그룹별 Relative Spread 상한 후보는 5%다. 유효한 같은 조건 A/A 여섯 Capture, Variant별 세 Run, 안정성·자료 검증을 통과하고 `abs(Delta)>NoiseFloor`일 때 비교를 RELIABLE로 표시한다. Noise 안의 음수는 IMPROVED가 아니다. 이는 통계적 유의성·p-value·신뢰구간의 증명이 아니다.

## 3. 실제 검증 결과

2026-11-03 KST에 실제 RTR_Advanced, Unreal Engine 5.8.3 CL58210709, RTX 5080의 DX12·SM6 자료로 검증했다. 최종 결과와 범위는 Phase 3 전체 검증을 따른다.

| 검증 그룹 | 실제 결과 | 증거 |
|---|---|---|
| 단위·통합 시험 | 82개 실행, 80개 통과, 심볼릭 링크 생성 권한이 필요한 2개 검사 건너뜀 | UnitTests.log |
| 기존 자료 분석 | 이전 실제 Run 37개 모두 예상 분석 상태 통과; 입력 파일 214개 해시 불변 | BatchAnalysis.json |
| 새 Native Metadata | A/A+A/B·A/A·A/B 세 Run, 총 24 Capture·7,200프레임; Capture별 300 유효 프레임 | NativeMetadata_Verification.json |
| 새 분석 모드 | 결합 Run·A/A 단독·별도 A/A 연결 A/B·A/A 없는 A/B의 네 모드 통과 | NativeReports.json |
| 재현성·원본 | 같은 입력·정책·구현의 재실행은 같은 AnalysisID·같은 경로·동일 바이트; 새 Run 원본 파일 36개 해시 불변 | NativeReports.json |
| 화면 | 실제 Prefix 리포트의 Desktop·폭 500px 좁은 화면 검증; 현재 리포트로 화면 기록 | VisualQA.json · Desktop · 500px |
| Launcher | 실제 보이는 앱 창 실행 확인; 대화상자·브라우저만 대체하고 Parser·통계·묶음·원본 해시를 실행한 GUI 소프트웨어 흐름 2건 통과 | LauncherUI_Verification.json · GUI 검사 |
| 보호 | Production 보호 파일 153개·이전 Benchmark Content 39개 불변, 새 Preset 세 개만 추가 | NativeMetadata_Verification.json |

심볼릭 링크 검사 두 건은 이 Windows 계정이 링크를 생성할 권한이 없어 건너뛰었으며 통과로 세지 않았다. 경로 이탈·중복·잘못된 Raw·해시 불일치의 나머지 검사는 수행했다. Launcher의 실제 폴더 선택을 마우스·키보드로 완주하는 검사는 Computer Use 앱 접근 확인 시간초과로 수행하지 못했다. 실제 보이는 앱 창은 확인했고 테스트 프로세스만 정리했으며 원래 Editor는 유지했다. 이 결과를 실제 UI 완주 검증으로 대체하지 않는다.

기존 Run 37개의 분석 상태는 WARNING 15개, FAIL 13개, UNSUPPORTED 3개, CANCELLED 6개였다. 이전 완료 자료에는 새 Native Raw SHA256 기록과 완전한 환경 Fingerprint가 없어 WARNING·비교 판정 보류로 남겼다. 실패·취소·미지원 자료에는 정상 GPU 등급을 주지 않았다.

새 세 Run의 식별자는 다음과 같다.

| Run | RunID | Capture |
|---|---|---:|
| Prefix A/A+A/B | 20261103T061010_URB3_Prefix_7519434A | 12 |
| 별도 A/A | 20261103T061046_URB3_AA_8C990F9A | 6 |
| 별도 A/B | 20261103T061111_URB3_AB_275A51C5 | 6 |

새 자료의 A/A와 A/B 환경 Fingerprint는 일치했고 Calibration은 VALID였다. 실제 판정은 작은 음수 Delta를 개선으로 오인하지 않았다.

| 분석 | GPU A 대표값 ms | GPU B 대표값 ms | Delta ms | Noise Floor ms | GPU Impact / Confidence |
|---|---:|---:|---:|---:|---|
| Prefix | 2.53170 | 2.51225 | −0.01945 | 0.05 | INCONCLUSIVE / INCONCLUSIVE |
| 별도 A/A 연결 A/B | 2.53550 | 2.51590 | −0.01960 | 0.05 | INCONCLUSIVE / INCONCLUSIVE |
| A/A 없는 같은 A/B | 2.53550 | 2.51590 | −0.01960 | 0.05 | INCONCLUSIVE / INCONCLUSIVE |

Prefix의 A/A Median Range는 0.02590ms, A/B Range는 각각 0.00090/0.00145ms였다. 별도 A/A Range는 0.02980ms, 별도 A/B Range는 0.02305/0.02045ms였다. 관측한 변동은 초기 0.05ms 후보 Floor보다 작았고 A/B Delta도 Floor 안에 있어 후보값을 유지했다. 이 한 장비·합성 장면으로 보편적인 센서 오차를 확정하지 않았다.

안정적인 절대 GPU 값의 A/B Budget은 두 비교 모두 GREEN이었지만 Impact를 GREEN·IMPROVED로 바꾸지 않았다. A/A 단독 리포트는 안정성 진단이며 A/B 비용·Budget 등급을 제공하지 않는다. 실제 HTML 예제는 ActualScalarReport에 독립된 Sources 묶음과 함께 보관한다. 테스트용 합성 숫자와 이 실측 수치는 섞지 않았다.

## 4. 오류 처리와 제약

초기 Asset 준비에서는 비동기 Asset Registry 검색 전에 Phase 2 원본 Preset을 찾지 못했다. 전용 플러그인 경로의 동기 검색과 실제 로드 확인을 추가한 뒤 새 Preset 세 개를 생성했다. 기존 Asset은 저장하지 않았다.

첫 Native Metadata 실행은 Windows에서 구현되지 않은 일반 Platform SHA256 API를 호출해 종료됐다. Windows CNG의 SHA256 구현과 알려진 abc 벡터 검사를 사용하도록 고친 뒤 실제 파일·Payload 해시와 24개 Capture를 검증했다. 초기 NO_COMPLETION·실패 로그는 BeforeNativeSHA256Fix에 보존했다. 해당 실패를 정상 Run으로 분석하지 않았다.

최종 Native 버전은 파일 해시·Fingerprint 초기화를 마친 뒤 Warmup 카운터를 0으로 두고 Capture마다 120개의 준비된 프레임을 기다린다. 이전 배치에서 준비 작업이 Warmup 끝에 위치할 수 있던 점을 보완하고 세 Run을 다시 수집했다. Capture 시작 경계의 첫 Sample도 원본대로 통계에 포함하며 임의로 제외하지 않는다. 첫 프레임의 긴 값이 관측되어도 그 원인을 파일 해시 하나로 단정하지 않는다.

필수 Metric의 결측·무효 값을 0으로 채우거나 다른 열로 대체하지 않는다. GPU가 없으면 GPU 평가를 UNAVAILABLE로 두고 사용할 수 있는 CPU 진단은 보존한다. 실패·취소·미지원 Run, 무결성 오류, 불안정한 Variant에는 정상 GPU 등급을 부여하지 않는다. 유효한 안정적 절대 GPU 값은 Calibration 부재 또는 작은 A/B 차이로 비교를 보류하더라도 Budget을 표시할 수 있다.

분석기는 입력을 수정하지 않고 버전별 분석 폴더에 결과와 검증한 Sources 복사본을 저장한다. 원본이 분석 도중 바뀌거나 같은 AnalysisID의 기존 결과가 달라지면 덮어쓰지 않는다. 분석 폴더 전체를 이동해야 원본 링크도 유지된다. HTML은 자체 표시 자원을 포함하며 서버·외부 Framework·CDN을 사용하지 않는다.

지원 입력은 실제 검증한 UE 5.8 CSV Mapping과 이 Runner의 Manifest다. 다른 엔진·Shipping·패키징·다른 장비·Production Character Scene을 이번 검증 결과로 보증하지 않는다. 실행에는 Python 3.10 이상과 GUI 사용 시 tkinter가 필요하며 독립 배포용 exe는 이번 필수 범위가 아니다. 한국어 오류 해결과 실행 절차는 실행 안내를 따른다.

원본 Fingerprint는 프로젝트 Content·Config·uproject와 Benchmark Content 전체를 보수적으로 묶는다. 별도 Calibration 이후 다른 Asset·Preset을 저장해도 조건 불일치로 판단할 수 있다. 장면·Preset 준비를 마친 뒤 A/A와 A/B를 수집하며, 이전 자료의 누락된 조건을 수동 추정하여 일치 처리하지 않는다.

CSV 읽기와 인용부호 처리는 [Python 3.10 csv 공식 문서](https://docs.python.org/3.10/library/csv.html), Mean·Median 정의는 [Python 3.10 statistics 공식 문서](https://docs.python.org/3.10/library/statistics.html)와 대조했다. P95는 Python의 quantiles 기본값을 쓰지 않고 Master의 nearest-rank 정의를 직접 적용한다. [Epic CSV Profiler 문서](https://dev.epicgames.com/documentation/en-us/unreal-engine/csv-profiler?application_version=4.27)는 CSV Profiler의 개념 배경이며, 실제 5.8.3 구조와 API는 설치 엔진의 `Core/Public/ProfilingDebugging/CsvProfiler.h`, `Core/Private/ProfilingDebugging/CsvProfiler.cpp`와 실출력으로 확인한다.

## 5. 변경 파일과 저장 범위

| 변경 영역 | 내용 |
|---|---|
| Analyzer | ingest.py, analysis.py, policy.json, report.py, cli.py, package 진입점 |
| Launcher | Analyze.cmd, Analyze.pyw |
| Native Metadata | URBMetadata.h/.cpp, Runner의 Metadata 연결, Preset의 SceneType·SceneStateDeclaredStatic |
| 기존 수집·Action | Phase 2 Action 처리와 Capture Helper 내용 유지 |
| 새 Asset | /URBenchmark/Phase3/Presets의 Prefix·AA·AB Preset 세 개 |
| 문서·증거 | Master v1.3, Phase 3 실행 안내·보고서, 검사·빌드·실측·HTML·해시 Evidence |
| 저장소 설정 | 도구 폴더 전체에 대한 루트 .gitignore 규칙 |

실제 플러그인은 `RTR_Advanced/Plugins/URBenchmark/`에 있고 도구 보관 위치는 `Real-Time-Rendering-Lab/01_Advanced/Tools/UniversalRenderingBenchmark/`다. Production Asset·기존 Level·프로젝트 Rendering Settings와 관련 없는 저장소 변경은 보존한다. 사용자가 나중에 선택한 문서·결과를 포트폴리오 경로로 복사할 수 있도록 분석 묶음을 독립적으로 구성했다. 이 작업에서 GitHub 업로드·Commit·Push는 수행하지 않는다.

## 6. 사용자 실행 방법

1. 새 모듈을 읽은 Editor에서 Benchmark 전용 Level을 열고 원하는 Action Preset을 지정한다. 통제한 장면에서만 Scene State Declared Static을 켠다.
2. Standalone Game으로 수집하고 URB COMPLETED와 Completion의 복원을 확인한다. 필요한 경우 A/A를 같은 Run에 먼저 수집하거나 별도 Run으로 보관한다.
3. `phase3/analyzer/Analyze.cmd`를 더블클릭하고 분석할 Run 폴더를 선택한다.
4. 별도 A/A가 있으면 연결한다. 결합 Run은 추가 Calibration 없이 분석할 수 있다.
5. 열린 Report.html에서 Measurement·Impact·Budget·Confidence와 실제 판정 이유를 읽는다. 숫자·원본·정책은 함께 보관한다.

상세 옵션·오류 해결·정책 조정은 Phase 3 실행 안내를 따른다. 사용자가 완성 뒤 직접 테스트할 수 있도록 실행 단계를 제공하며 이번 보고에서 사용자에게 별도 Phase 2 확인 작업을 요구하지 않는다.

## 7. 다음 단계와 승인 대기

Phase 3의 구현·실측 분석·정책·리포트 검증 결과를 전달하고 **Phase 4 진행 전 사용자 승인을 기다린다**. 원래 로드맵대로 Phase 4에서 사용성·최종 문서·전체 사용자 흐름을 검증한다. V1 전체 완성 후 실제 PBR Character Scene의 Hair·Skin·Eye Material을 측정하고 시각적 HTML Report를 확인한다. 합성 장면의 수치를 실제 Character 기능의 고정 비용으로 해석하지 않는다.
