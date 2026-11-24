# RTR Universal Rendering Benchmark Tool V1 — Master Specification

문서 버전: 1.4 · 갱신일: 2026-11-03 · 본문 언어: 한국어

**V1 구현과 개발자 검증을 완료했다. Phase 0~4의 A~I, 수정한 시험 환경의 Runtime 19개 사례, 실제 Editor→Standalone→Explorer 분석 Launcher 흐름, Esc 취소·복원, 원본 보호와 HTML 화면을 확인했다. Native 1.0.0-V1과 Analyzer 0.3.1을 제공한다. 사용자의 직접 검증은 아직 수행하지 않았으며 실행 안내에 따라 시작할 수 있다. 전체 Character Scene의 Hair·Skin·Eye 측정은 별도 작업이다.**

## 1. 목적과 완료 모습

Material 및 Rendering Feature의 A/B 성능을 같은 조건에서 반복 측정하고, 원본 CSV·요약 CSV·독립형 HTML 리포트로 확인하는 재사용 도구를 만든다. 사용자는 Unreal Details Panel에서 Preset과 대상을 지정하고 Standalone 측정을 시작한 뒤, 분석 실행 파일을 더블클릭해 리포트를 연다. 새 테스트를 추가할 때 Runner 코드를 수정하지 않는다.

적용 대상은 Hair·Skin·Eye에 한정하지 않는다. 일반 Static Mesh Material, Stylized Shader, POM, Environment Material, Foliage 및 지원되는 Runtime Rendering Feature에도 동일한 측정 흐름을 사용한다. 실제 Character Scene과 부하를 높인 Stress Scene은 서로 다른 조건으로 기록한다. Stress Scene의 수치를 실제 게임의 비용으로 환산하지 않는다.

우선순위는 **정확성 → 재사용성 → 안정성 → 사용성 → 디자인**이다.

| 항목 | 계획값 / 원칙 |
|---|---|
| 이름 | RTR Universal Rendering Benchmark Tool V1 |
| 범위 | Level 2 Generic Rendering Feature Benchmark |
| 조사 확인 환경 | Unreal Engine 5.8.3 / Changelist 58210709 / NVIDIA GeForce RTX 5080 / Driver 617.42 |
| 실행 환경 확정 | Phase 0에서 D3D12·SM5·GPU/CPU CSV를 확인했다. Phase 1은 실제 RTR_Advanced의 SM6·Visible Standalone과 CSV 수집·복원을 검증했다. Phase 2의 추가 Action도 같은 엔진·RHI·Feature Level에서 별도로 실측 검증했다. |
| RTR 참고 경로 | `local path withheld` |
| 기존 문서 참고 경로 | 위 경로의 `01_Advanced/PBRCharacter` |
| 기존 Unreal 프로젝트 확인 경로 | `local path withheld` — Benchmark 플러그인·전용 테스트 Asset과 실행 대상; Production Asset 보호 |
| 승인된 최종 도구 산출물 위치 | `local path withheld` — 없는 폴더는 새로 만든다. |
| 검증·준비 작업 위치 | 현재 작업 공간의 `rtr_benchmark_phase4_20261103/` — 기존 Action·Capture·Analyzer를 유지하며 A~I 최종 시험·사용자 흐름·보존을 검증한다. |

## 2. 변경 금지와 실행 범위

- 기존 Production Material·Material Instance·Material Function, 기존 Level, 프로젝트 Rendering Settings, 기존 문서의 관련 없는 내용과 Figure를 수정·저장·이동·삭제하지 않는다. 기존 Git 변경 사항도 보존하며 Commit·Push하지 않는다.
- Phase 1의 실제 `RTR_Advanced/Plugins/URBenchmark/` Runtime 플러그인을 확장한다. Phase 2는 새 `/URBenchmark/Phase2/` Content와 전용 Level을 추가하고 기존 Phase 1 테스트 Asset은 보존한다. Production Level에 Runner를 영구 배치하지 않는다.
- RTR의 `01_Advanced/Tools/UniversalRenderingBenchmark/`에는 도구 문서·시안·소스·Asset·검증 증거를 정리한다. 사용자 요청으로 이 폴더 전체를 저장소 `.gitignore`에 등록하여 GitHub에 올리지 않는다. 포트폴리오에 쓸 문서·결과는 사용자가 별도 경로로 복사한다. Commit·Push나 자동 공개는 수행하지 않는다.
- `sources/`와 동기화된 참고 자료는 읽기 전용이다.
- 기존 Editor의 미저장 작업을 보호한다. 원래 Editor를 임의 종료하거나 현재 Production Material·Level을 저장하지 않는다. 새 플러그인 반영에는 별도 Editor 프로세스 또는 이후 사용자가 선택하는 재시작을 사용한다.
- 테스트 Asset은 `/URBenchmark/` 전용 경로에만 만든다. Static Switch는 새 테스트용 Parent와 사전 컴파일한 MIC 두 개를 사용하고 Production Asset의 Switch를 변경하지 않는다.
- 기존 프로젝트의 Module·Build·렌더링 설정과 `.uproject`를 유지하는 작은 Runtime 플러그인 구성을 우선한다. `EnabledByDefault` 자동 인식 방식은 실제 실행으로 확인하기 전까지 동작 검증 완료로 표시하지 않는다. 변경이 추가로 필요하면 필요성과 영향을 먼저 설명한다.
- 정상·실패·취소 경로에서 원래 Material·Scalar·Visibility·Shadow·Camera·Runtime 설정을 복원한다. 강제 종료 시 복원을 보장하지 않으며 안전한 중단을 우선한다. 실행 전후 보호한 원본 파일의 해시와 새로 추가한 파일 목록을 보고한다.

## 3. 시스템 구조

`Test Preset → Runtime Benchmark Runner → Unreal CSV Profiler → External Python Analyzer → Summary.csv + Report.html`

| 구성 | 책임 |
|---|---|
| Blueprint Runner | `BP_URB_Runner`가 Native Runner를 상속하는 설정용 Wrapper. Preset 선택·Details 노출·Level 배치와 실행 진입점을 제공 |
| Test Preset | `UDataAsset` 기반 `UURBTestPreset`. ActionType·Action별 설정·Tag·Capture 조건·RunMode·선택 Calibration을 저장 |
| Details Panel | 코드 편집 없이 사용자 설정 |
| CSV Profiler | 실제 프레임별 CPU/GPU 데이터 수집 |
| Native Runner | 대상의 유일한 Tag 매칭, 공통 실행 순서·준비·Warmup·진행 상태·복원과 선택한 Action의 검증·적용을 담당. Blueprint가 같은 검증 경로를 재사용 |
| 독립 C++ CSV Helper | 별도 Capture Component가 Phase 0의 FCsvProfiler API로 정확한 프레임 수·Metadata·저장 완료·파일 상태 검증을 담당 |
| External Python Analyzer | 실제 CSV 구조 검사, 통계·등급·리포트 생성 |
| Windows Launcher | 분석 실행, 입력 검증, 결과 위치 안내 |

Phase 1의 작은 Runtime 플러그인으로 Native Runner·Preset·Capture Helper를 제공하고 Phase 2의 Action 처리부를 통합한다. 대규모 Plugin Framework는 만들지 않는다. Blueprint Graph에서 수집·복원 로직을 중복 구현하지 않으며, 사용자는 Graph나 C++를 편집하지 않는다.

Unreal Python은 Editor 준비·검사에만 사용한다. Runtime 반복 측정을 Python Editor Scripting에 의존시키지 않는다. Phase 0에서 검증한 실제 명령·API만 구현 계약으로 확정한다. CSV 명령 실행 요청과 파일 쓰기 완료를 같은 사건으로 간주하지 않는다.

## 4. Preset과 기본 측정 조건

| 설정 | 기본값 / 검증 |
|---|---|
| TestID / TestName | 안정적인 식별자 / 읽기 쉬운 이름 |
| SceneType | Character / General / Stress 등 명시 |
| Target Level / CameraTag | 전용 Level과 CameraTag로 Camera를 유일하게 찾아 Transform·FOV 고정 |
| TargetActorTag / TargetComponentTag | Action에 필요한 Actor와 Component를 유일하게 식별; 누락·중복은 오류. ConsoleVariable은 대상 Mesh를 요구하지 않는다 |
| ActionType | MaterialSwap / ScalarParameter / ActorVisibility / ConsoleVariable 중 한 개 선택 |
| Variant A / B | Action별 값·Material·표시 이름 |
| Material Slot | 유효한 Slot Index·이름 확인 |
| WarmupFrames | 120; 각 Capture 전 동일하게 실행 |
| CaptureFrames | 300; Warmup·교체 프레임 제외 |
| RepeatCount | Variant별 3회; 유효하지 않은 Run을 제외하고 3회 미만이면 확정 판정 금지 |
| TargetFPS | 60; **평가 예산 계산용이며 측정 중 FPS 제한값이 아니다.** |
| Resolution | 1920×1080; 요청값과 적용 확인값을 모두 기록 |
| ScreenPercentage | 100; Dynamic Resolution 비활성화·적용 확인 |
| RunMode | 기본 StandardBenchmark(A/B); CalibrationValidation(A/A) 별도 선택 |
| RunCalibration | 기본 false; Standard 실행 전에 A/A를 추가할지 사용자가 선택 |
| CalibrationReferenceRunID | 별도 Calibration 결과 식별자를 기록할 수 있음; 유효성·Confidence 분석은 Phase 3 |
| OutputDirectory | 실제 실행 프로젝트의 `Saved/URBenchmark/<고유 RunID>/` |

VSync·FPS 제한·Scalability·RHI·조명·애니메이션·시간 변화·Camera·Screen Percentage를 동일하게 유지한다. 상태를 변경했다면 변경 전 값, 적용값과 복원 결과를 기록한다. 목표 FPS를 60으로 선택해도 측정은 성능 차이를 가리지 않도록 제한 없이 수행한다. 제한 해제 여부를 확인하지 못하면 Warning을 표시한다.

Shader/PSO·Texture Streaming 준비 상태를 확인하고 최초 준비 시간은 Capture에서 제외한다. 준비가 끝나지 않았다면 Warmup을 늘리거나 실패 원인을 기록한다. Capture 중 Asset 생성, Material 컴파일, Variant 교체, 분석 실행, Screenshot 저장을 하지 않는다.

### Calibration과 Standard 실행

**Calibration / Validation Mode**는 선택한 Action의 실제 A 상태를 A/A 두 라벨에 적용해 기본 6회 수집한다. MaterialSwap은 Material A, ScalarParameter는 Scalar A, ActorVisibility는 Visibility A, ConsoleVariable은 CVar A를 유지한다. 초기 설정과 환경 변경 후 안정성 점검에 사용한다. **Standard Benchmark Mode**는 선택한 Action의 A/B 상태를 기본 6회 수집한다. `RunCalibration=false`가 기본이며 매 A/B 실행 전 A/A를 강제하지 않는다. 사용자가 Standard에서 `RunCalibration=true`를 선택하면 A/A 구간을 먼저 수집한 뒤 A/B를 수행한다.

별도 Calibration을 참조해도 A/B 실행을 허용한다. Phase 1~2는 Run Mode·Calibration 여부·참조 RunID를 Metadata에 기록하며 Confidence 분석은 수행하지 않는다. Phase 3에서는 같은 조건의 유효 Calibration이 없으면 비교 Confidence와 확정 Impact Grade를 보류한다. Calibration 부재는 A/B Raw CSV 수집을 막는 오류가 아니다.

### 지원 Action

| Action | 동작 | 합격에 필요한 확인 |
|---|---|---|
| MaterialSwap | 지정 Mesh Component의 한 Slot에 A/B Material 교체 | 실제 Slot Material 읽기 확인; 원래 Material 복원; Static Switch는 미리 준비한 MI 두 개 사용 |
| ScalarParameter | 준비한 Dynamic Material Instance의 Scalar A/B 변경 | Global Scalar 존재·값 읽기 확인; transient DMI 한 개 재사용; 원래 Material·값 복원. Material Layer·Custom Primitive Data Parameter는 미지원 |
| ActorVisibility | Actor 또는 Component의 지정 Visibility 상태 변경 | Visible·HiddenInGame·Shadow 정책을 구별하여 기록; 실제 렌더 상태와 복원 확인 |
| ConsoleVariable | Allowlist의 Runtime 변경 가능 CVar A/B 적용 | 원래 값·설정 우선순위·태그 보존, 적용 후 읽기 확인, 복원 확인 |

Phase 2 Allowlist의 초기 항목은 `r.Tonemapper.Sharpen`(유한한 실수 0~10)과 `r.BloomQuality`(정수 0~5)다. Allowlist는 코드에 고정하고 Details에서 선택한다.

재시작·Shader 재컴파일이 필요한 CVar, 적용을 확인할 수 없는 CVar, Runtime에서 변경 불가능한 값은 `UNSUPPORTED`로 처리한다. CVar를 임의 명령 문자열로 실행하는 범용 콘솔 입력은 V1 범위에서 제외한다.

## 5. Runner 실행 계약

1. Preset·대상·Camera·출력 경로·지원 Metric을 검증한다.
2. 원래 Material·Visibility·CVar·측정 환경을 보관한다.
3. 테스트 환경 적용과 준비 상태를 확인한다.
4. Variant 적용 → 적용 결과 읽기 확인 → Warmup → Capture 시작을 수행한다.
5. 요청한 유효 프레임을 수집하고 Capture 완료와 파일 저장 완료를 확인한다.
6. 파일을 TestID·Variant·RunIndex·CaptureID와 연결한 뒤 다음 Capture로 이동한다.
7. 모든 Capture 종료 또는 오류 시 원래 상태를 복원하고 결과를 기록한다.
8. 파일 존재만으로 성공 처리하지 않고 Header·유효 프레임 수·필수 Metric을 확인한다.
9. 분석·리포트 생성은 Capture 프로세스 종료 후 수행한다.

Standard의 기본 순서는 **A → B → B → A → A → B**, Variant별 3회다. Calibration Mode는 같은 순서의 두 라벨에 선택한 Action의 실제 A 상태를 적용한다. 각 Capture에는 독립 Warmup을 적용한다. 반복 횟수가 달라지면 미리 정한 균형 순서를 Manifest에 저장한다. 실패한 Run을 조용히 누락하거나 가장 좋은 Run만 선택하지 않는다. 재시도는 별도 CaptureID와 이유를 기록하고 원본 실패 자료를 보존한다.

상태는 `IDLE → VALIDATING → PREPARING → WARMUP → CAPTURING → RESTORING → COMPLETED`를 기본으로 하며 `FAILED`·`CANCELLED`를 별도로 지원한다. 화면에는 현재 Variant·Run 수·상태만 작게 표시하고 실제 Capture 구간은 숨기거나 고정한다. 완료·실패 표시에는 결과 폴더와 원인을 제공한다.

## 6. Metric과 통계 정의

Phase 0에서 확인한 필수 Column은 `FrameTime`, `GameThreadTime`, `RenderThreadTime`, `GPUTime`이며 단위는 ms다. Phase 1도 실제 Header 이름으로 식별하고 SM6 실출력의 유효성을 확인한다. Column 위치는 고정하지 않는다. CSV 끝의 반복 Header와 Metadata를 프레임으로 세지 않는다. GPU Pass 하나를 전체 GPU Frame Time으로 사용하지 않는다. CPU Frame·Game·Draw 값을 GPU 값으로 대체하지 않는다.

다음 통계·등급·리포트 계산은 Phase 3의 구현 계약이다. Phase 1~2의 기존 Raw도 읽지만 완전한 환경 Fingerprint가 없는 이전 자료에서는 비교 Confidence를 보류한다. 기존 자료에 환경 증거를 추정하여 채우지 않는다.

각 Metric에 대해 Raw 값, 유효 Sample 수, Mean·Median·P95·Min·Max를 Run별로 계산한다. P95는 오름차순 정렬한 N개 값의 `ceil(0.95×N)`번째 값인 nearest-rank 방식으로 고정한다. 엔진이 내보낸 집계값과 Analyzer의 집계값은 출처를 구분한다.

V1의 대표 A/B 비교값은 **각 Run의 Median을 구한 뒤 그 Median들의 Median을 취한 값**이다. 이를 `A_MedianOfRunMedians`·`B_MedianOfRunMedians`로 명시한다. 반복 길이에 따라 긴 Run이 과도하게 가중되지 않게 한다. Run별 Mean·Median·P95와 전체 유효 프레임을 합친 Pooled Mean·Median·P95는 별도 열로 제공한다. Pooled P95와 Run P95의 Median을 같은 이름으로 표시하지 않는다.

`DeltaMs = B_MedianOfRunMedians - A_MedianOfRunMedians`

`DeltaPercentBaseline = 100 × DeltaMs / A_MedianOfRunMedians`

A 대표값이 0 이하이거나 유효하지 않으면 Baseline 대비 변화율은 `UNAVAILABLE`이다. 결측값을 0으로 채우거나 성능을 좋게 보이도록 Outlier를 임의 제거하지 않는다. 제외가 필요한 Sample은 사전 정의된 유효성 규칙과 이유·개수·원본 위치를 남긴다.

## 7. 성능 평가 정책

다음 색상은 **RTR의 조정 가능한 초기 정책**이다. Unreal 공식 기준이나 Shader 품질 판정이 아니다. 정책 버전과 Threshold를 결과마다 저장한다. 화면에는 비교 지표·장면 GPU 예산·측정 Confidence를 분리한다.

### 7.1 Performance Impact

`FrameBudgetMs = 1000 / TargetFPS`

`ImpactPercentBudget = 100 × DeltaMs / FrameBudgetMs`

| 조건 | Impact Grade | 의미 |
|---|---|---|
| 유효한 GPU 데이터 없음 | UNAVAILABLE | GPU 평가 불가 |
| 비교 Confidence 부족 | INCONCLUSIVE | 차이를 판단할 근거 부족 |
| 신뢰할 수 있는 DeltaMs < 0 | IMPROVED | 비교 장면의 GPU 시간 감소 |
| 0 ≤ Impact ≤ 2% | GREEN | 낮은 추가 비용 |
| 2% < Impact ≤ 5% | YELLOW | 품질 대비 비용 검토 |
| Impact > 5% | RED | 최적화 우선 검토 |

경계값은 반올림 전 수치로 판정한다. 2.000%는 GREEN, 5.000%는 YELLOW다. 음수라도 Noise Floor 안이면 `IMPROVED` 대신 `INCONCLUSIVE`다. RED는 기능 제거 지시가 아니다.

예를 들어 A=8.40ms, B=9.00ms, 60FPS이면 Delta=+0.60ms, Baseline 대비 +7.14%, 예산 대비 Impact=3.60%다. 두 퍼센트의 분모가 다르므로 이름을 생략하지 않는다. 이 숫자는 **시안용 가상 값이며 실측 결과가 아니다.**

### 7.2 Frame Budget

각 Variant의 대표 GPU 값으로 `BudgetUsagePercent = 100 × GPUTimeMs / FrameBudgetMs`를 계산한다.

| GPU Budget 사용률 | Budget Grade |
|---|---|
| 0~70% 이하 | GREEN |
| 70% 초과~100% 이하 | YELLOW |
| 100% 초과 | RED |
| 절대 GPU 측정값이 누락·무효·불안정 | UNAVAILABLE |

A/B를 각각 표시한다. GPU Budget Grade만으로 전체 시스템이 목표 FPS를 달성한다고 표현하지 않는다. Frame·Game·Draw/Render Thread 값과 CPU 제한 가능성을 함께 보여준다. Noise Floor보다 작은 A/B 차이는 Impact가 `INCONCLUSIVE`이더라도 두 Variant의 절대 GPU 측정이 안정적이면 Budget 사용률은 표시할 수 있다. 이 경우 “차이 판정 보류”를 명확히 유지한다. 데이터 자체가 실패·불안정한 경우 Budget에도 정상 색상을 부여하지 않는다.

### 7.3 Measurement Confidence — V1 후보 규칙

이 규칙은 재현 가능한 보수적 초기 판정 정책이다. Phase 3에서 실제 반복 자료와 경계·오류 시험으로 계산과 판정 보류 동작을 검증했다. **0.05ms와 5%는 후보 정책으로 유지하며 장비·장면 전반의 공식 오차로 확정하지 않는다.** 3회 반복으로 통계적 유의성을 증명하지 않으며 Confidence Interval·p-value로 소개하지 않는다.

1. 확정 비교 Confidence를 평가하려면 같은 실제 Variant 상태로 기본 6회 수집한 유효 Calibration을 연결한다. 매 A/B 직전 실행을 강제하지 않으며 별도 Calibration 또는 사용자가 선택한 RunCalibration 결과를 참조할 수 있다. A/B와 Camera·해상도·RHI·Scalability·Warmup·CaptureFrames·장면 상태가 일치해야 한다. A/A Manifest 식별자와 환경 Fingerprint를 A/B 결과에 연결한다.
2. Run별 Median을 `mAA[1..6]`, `mA[1..r]`, `mB[1..r]`로 둔다. `RangeAA=max(mAA)-min(mAA)`, `RangeA=max(mA)-min(mA)`, `RangeB=max(mB)-min(mB)`를 계산한다.
3. `NoiseFloorMs=max(RangeAA, RangeA, RangeB, MinimumNoiseFloorMs)`로 정의한다. 초기 `MinimumNoiseFloorMs=0.05ms`는 조정 가능한 후보값이며 출력 정밀도·장비 변동을 검증해 확정한다. 이 값을 실제 센서 정밀도나 공식 오차로 주장하지 않는다.
4. 안정성은 각 그룹의 `RelativeSpread=100×Range/Median`으로 확인한다. 기본 후보 상한은 5%다. Median이 0 이하이면 무효다. A/A와 A/B 어느 그룹이든 상한을 넘거나 Thermal/Clock/Background Load의 확인된 급변이 있으면 `INCONCLUSIVE`다.
5. 필수 Metric·Capture 매칭·프레임 수·조건 일치·Run 수가 유효하고, A/A가 존재하며, 안정성 검사를 통과하고, `abs(DeltaMs)>NoiseFloorMs`일 때 비교 Confidence를 `RELIABLE`로 표시한다. 같거나 작으면 `INCONCLUSIVE`다.
6. GPU 전체 Metric이 없으면 GPU Confidence는 `UNAVAILABLE`다. A/A가 없거나 환경이 다르면 수집한 A/B Raw는 유지하고 `INCONCLUSIVE`로 표시하여 확정 Impact Grade만 보류한다. A/B 실행 자체를 금지하지 않는다. 반복 횟수 부족도 확정 판정 보류로 처리한다.

환경이 안정적이어도 작은 차이는 회색 판정 보류가 될 수 있다. 사용자는 이를 “비용 없음”으로 읽지 않아야 한다. 더 긴 Capture·더 많은 반복·더 나은 환경 통제를 제안하며, Stress Scene 재시험 결과는 별도 장면으로 기록한다.

### 7.4 독립 상태 필드

| 필드 | 값 | 책임 |
|---|---|---|
| MeasurementStatus | PASS / WARNING / FAIL / UNSUPPORTED / CANCELLED | 실행·자료 완전성과 지원 여부 |
| ImpactGrade | GREEN / YELLOW / RED / IMPROVED / INCONCLUSIVE / UNAVAILABLE | 기능의 추가 GPU 비용 |
| BudgetGradeA / B | GREEN / YELLOW / RED / UNAVAILABLE | 각 Variant의 절대 GPU 예산 |
| Confidence | RELIABLE / INCONCLUSIVE / UNAVAILABLE | A/B 차이 해석 가능성 |

PASS를 GREEN과 동의어로 사용하지 않는다. 정상 Capture라도 차이가 작으면 PASS + INCONCLUSIVE가 가능하다. CSV 누락·GPU 미지원·실행 실패를 0ms 또는 GREEN으로 표시하지 않는다.

## 8. 출력·Metadata 계약

```text
Saved/URBenchmark/<Timestamp>_<TestID>_<UniqueRunID>/
  Raw/                 원본 Capture CSV, 손실 없이 보존
  Manifest.json        Capture 연결과 환경·상태·정책
  Execution.log        상태 전이, 오류와 복원 기록
  Completion.json      완료·실패·취소와 복원 상태
  Summary.csv          Phase 3부터 생성
  Report.html          Phase 3부터 생성
```

고유 RunID를 사용해 기존 결과를 덮어쓰지 않는다. Analyzer는 Raw·Native Manifest·Completion을 수정하지 않는다. 원본 해시는 별도 분석용 `AnalysisManifest.json`에 기록하며 `Analysis/<AnalyzerVersion>_<AnalysisID>/`에 Summary.csv·Report.html·Analysis.json·AnalysisManifest.json·Sources/를 보관한다. Sources에는 읽은 입력의 해시가 일치하는 복사본을 넣어 리포트 묶음을 오프라인으로 이동할 수 있게 한다. 같은 입력·정책·분석 버전의 재실행은 같은 결과를 확인하며, 다른 정책·입력은 별도 분석 묶음이 된다.

Manifest에는 TestID·TestName·SceneType·ActionType·Preset Fingerprint·RunMode·RunCalibration·CalibrationReferenceRunID·Variant·RunIndex·CaptureID·측정 순서·Capture 시작/완료 시각·원본 파일 경로와 해시·요청/유효 Frame 수·Warmup·엔진 Build·GPU/Driver·OS·RHI·해상도·Screen Percentage·Camera·Scalability·VSync/FPS 제한·Metric Mapping/단위·Action 적용 확인·복원 결과·AA 연결·Threshold 버전을 저장한다. 파일명 추정만으로 Variant를 연결하지 않는다.

Phase 3 수집 Metadata는 Native `schemaVersion=3`을 사용한다. 환경 Fingerprint에는 Engine·GPU·Driver·OS·CPU·RHI, 해상도·Screen Percentage, Camera Transform·FOV, Scalability, 환경 CVar, SceneType·World·원본 Content/Config/uproject 해시, Actor Transform 해시, Action A 상태와 Runner Build 해시를 저장한다. 저장한 Payload JSON의 정확한 UTF-8 SHA256을 검증한 뒤 순서에 독립적인 Canonical Payload로 A/A와 A/B를 비교한다. Capture CSV도 해당 Fingerprint를 참조한다.

`Scene State Declared Static`은 사용자가 애니메이션·조명·시간 변화·배경 작업을 통제했다는 선언이다. 자동 검사는 Camera·Scalability·환경 CVar·Actor Transform과 원본 파일의 전후 상태를 확인하며 장면의 모든 동작을 증명하지 않는다. 기본값은 false이고, 제어하지 않은 장면에 true를 지정하지 않는다. 전후 원본 해시 변경이나 고정 환경 검증의 명시적 실패는 정상 Budget 색상을 막는다. Fingerprint 원문·객체·SHA256의 무결성 오류는 분석 FAIL이며 GPU 등급을 부여하지 않는다.

Summary는 Metric별 행을 사용해 GPU와 CPU를 구분한다. 필수 필드는 식별자·환경·설정·유효 Run/Sample 수·Run별 및 집계 통계·DeltaMs·Baseline 대비 %·FrameBudgetMs·ImpactPercentBudget·NoiseFloorMs·RelativeSpread·독립 상태 필드·Warning·원본 참조다. 실제 제공되지 않은 Metric은 명시적인 결측값과 사유를 기록한다.

## 9. Unreal Details Panel 시안

아래는 **설계 시안**이며 이미 구현된 Unreal UI가 아니다. 기본 Unreal Details Panel을 사용하고 별도 Editor Utility Widget은 필수로 만들지 않는다.

```text
BP_URB_Runner — Details
  Test Preset           [Hair PDO / General Material / Custom]
  Test ID / Name        [Hair_PDO_001] [Hair PDO]
  Scene Type            [Character]
  Action Type           [MaterialSwap]
  Target Actor Tag      [URB_Target]
  Component Tag         [URB_Mesh]
  Material Slot         [0]
  Variant A             [MI_Test_Hair_PDO_Off]
  Variant B             [MI_Test_Hair_PDO_On]
  Camera Tag            [URB_Camera]

  Run Mode              [Standard Benchmark / Calibration Validation]
  Run Calibration       [false] ※ Standard 전에 A/A 선택 추가
  Calibration Reference [선택 RunID]

  Capture Settings
    Target FPS          [60]   ※ 평가 예산 16.67ms
    Resolution          [1920 × 1080]
    Screen Percentage   [100]
    Warmup Frames       [120]
    Capture Frames      [300]
    Repeat / Variant    [3]
    Order               A → B → B → A → A → B
    Output Folder       [Saved/URBenchmark/...]

  Validation            [Validate Preset] 대상 / 설정 / 저장 경로 확인
  Run Instructions      Unreal Play ▾ → Standalone Game → 자동 측정
  Last Result           [완료/실패] [결과 폴더 열기]
```

Phase 1의 MaterialSwap에 이어 Phase 2에서 네 Action을 같은 Preset에 통합한다. Actor·Component·Camera Tag가 누락되거나 두 개 이상과 일치하면 임의 선택하지 않고 오류를 표시한다. 전용 Standalone 시작 버튼 대신 Unreal 기본 Play 메뉴를 우선 사용한다. Phase 2 Details는 Action에 필요한 필드만 표시하며 Scalar는 Parameter와 A/B 값, Visibility는 대상과 정책, CVar는 Allowlist 선택과 A/B 값을 보여준다. 사용자가 코드를 수정하거나 긴 명령을 입력하지 않도록 한다. 잘못된 Slot·누락된 대상은 실행 전에 원인을 표시한다. Phase 2의 오류 원문은 영어이며 한국어 원인·확인 방법은 실행 안내에 제공한다. 최종 UI의 한국어 안내는 Phase 4 사용성 검증에 포함한다.

## 10. HTML 성능 리포트 시안

`Report.html`은 인터넷·서버·외부 Framework 없이 브라우저에서 열린다. 외부 CDN·웹폰트·네트워크 요청을 사용하지 않는다. 시안은 페이지 상단에 “가상 데이터 / 실측 아님”을 고정 표시한다. 실제 리포트에서는 실측 출처와 RunID를 표시한다.

| 영역 | 내용 |
|---|---|
| Header | TestName·SceneType·RunID·실측/시안 구분·Timestamp |
| Environment | Engine·GPU·Driver·RHI·해상도·TargetFPS·FrameBudget |
| Summary Cards | A GPU·B GPU·Delta ms·Baseline 대비 %·예산 대비 Impact |
| A/B Comparison | 0부터 시작하는 동일 축의 GPU 막대와 ms 숫자, Run별 Median 점 |
| Performance Impact | 2%·5% 경계, 현재 위치, Grade와 한국어 설명 |
| Frame Budget | A/B 각각 70%·100% 경계와 사용률; 초과를 잘라 숨기지 않음 |
| Confidence | 선택해 연결한 A/A Baseline Variation·A/B Run-to-Run Variation·Estimated Noise Floor·Actual A/B Delta·판정 이유 |
| CPU / Frame | GPU보다 낮은 시각적 우선순위의 Frame·Game·Render A/B·Delta 비교 표 |
| Interpretation | 실제 데이터·정책으로만 생성한 짧은 설명 |
| Evidence | Raw 파일·Manifest·Summary 경로와 Warning·복원 결과 |
| Policy | Threshold 버전·대표 통계·Noise 규칙·한계 |

Phase 1에서는 기존 Dark UI·Summary Cards·GPU 비교·Impact Gauge·Budget·Confidence·Analysis Summary를 유지하며 위 정보와 12px 이상 주요 보조 문구를 목업에 반영한다. 실제 CSV 연동·통계·HTML 생성은 Phase 3에서 구현한다.

색상만으로 의미를 전달하지 않고 Grade·숫자·설명을 함께 제공한다. 신뢰도가 부족하면 Impact 영역을 회색으로 표시한다. Missing GPU는 빈 막대와 사유를 보여주며 0ms 막대를 그리지 않는다. 여러 Test를 모을 때 환경이 다르면 그룹을 분리하고 전체 순위로 단정하지 않는다.

예시 표현: “Variant B의 GPU 시간이 0.60ms 증가했습니다. 60FPS 예산의 3.60%에 해당하여 YELLOW입니다. 시각적 개선과 추가 비용을 비교해 판단하세요.” 이 문장은 앞서 제시한 **가상 값**에 대한 시안이다.

## 11. 단계별 목적·산출물·합격 기준

### Phase 0 — Feasibility Validation · 완료한 선행 단계

**목적:** 이 장비와 실제 엔진에서 CPU/GPU CSV 수집 및 Runtime 교체·Warmup·Capture 연결이 가능한지 확인한다. 이후 단계의 기술 계약을 실출력으로 확정한다.

**수행:** 실제 프로젝트·엔진 위치를 읽기 전용 조사하고 격리 실험 환경을 만든다. 지원되는 CSV Capture 명령·옵션을 확인한다. Render가 활성화된 Standalone 또는 적절한 독립 프로세스에서 실제 CSV를 수집한다. NullRHI 결과를 GPU 실측으로 사용하지 않는다. 작은 진단 코드로 Material A/B Runtime 교체·프레임 경계·파일 완료·Capture 식별을 검증할 수 있으나 제품 Runner·범용 Analyzer를 완성하지 않는다.

**산출물:** 환경 정보, 사용한 명령/API, Raw CSV, Header·단위와 Metric Mapping, 유효 Frame 수와 간단한 실측 통계, Runtime 적용 증거, CaptureID 매칭, 로그, 원본 무변경 확인, 제한과 권장 구조, 다음 단계 예상 영향.

**합격 기준:**

- [ ] 실제 엔진 Build·GPU·Driver·DX12/RHI를 확인했다.
- [ ] 독립 실행 환경에서 유효한 CSV를 얻었고 Capture 저장 완료를 검증했다.
- [ ] 실제 Frame·Game·Draw/Render·GPU 전체 Frame Metric의 존재·단위·의미를 확인했다. 없는 항목은 명시적으로 실패·미지원 처리했다.
- [ ] GPU 값은 0·결측·CPU 대체값이 아니며 Render가 수행된 실측이다.
- [ ] 최소 진단으로 A/B Material 적용·Warmup·Capture 경계와 Capture별 식별을 확인했다.
- [ ] 원본 Unreal 프로젝트·Production Asset·설정에 변경이 없음을 확인했다.
- [ ] 지원 범위·남은 실패와 권장 구현 방식을 증거 경로와 함께 보고했다.

모든 필수 항목을 충족하지 못하면 Phase 0 전체 PASS로 표시하지 않는다. 환경 조사만 끝나면 “조사 완료 / 실측 미완료”, GPU만 안 되면 “CPU 수집 확인 / GPU 미지원 또는 미확인”처럼 실제 도달 지점을 보고한다. GPU 수집 대안이 구조 변경을 요구하면 제안으로 남긴다. Phase 0의 독립 DX12·SM5 실행과 12×300프레임 수집은 선행 보고서로 확인했다. 이후 사용자 요청으로 Phase 1이 승인되었다. 이 결과를 SM6·Visible Standalone 검증으로 대체하지 않는다.

### Phase 1 — Core Material A/B Benchmark와 목업 보완 · 완료한 선행 단계

**목적:** Phase 0에서 검증한 방식으로 한 번의 실행에서 반복 Material A/B 측정과 복원을 끝내는 최소 제품을 만든다.

**산출물:** 실제 RTR 프로젝트의 새 Runtime 플러그인, Native Runner를 상속한 BP_URB_Runner, UDataAsset Preset, 전용 Test Level·Static Switch Parent·MIC, 기본 Details 설정, 상태 표시, Raw/Manifest/Execution/Completion, 수정 목업, Phase 1 실행 안내와 검증 보고.

**합격 기준:** 실제 RTR_Advanced의 SM6·Visible Standalone에서 Runner를 실행한다. 사전 컴파일한 Static Switch MIC 두 개의 A/B와 별도 A/A Calibration을 각각 기본 6 Capture로 검증하되, 일반 사용자 A/B 실행에 A/A를 매번 강제하지 않는다. 각 Capture에 120 Warmup·300 유효 Frame·유일한 식별자가 있고 순서가 일치한다. Preset만 바꾸어 실행하며 Camera·해상도·환경·실제 Material을 확인한다. 누락·중복 Actor/Component/Camera Tag, Slot 오류, Material 적용 실패, Capture 실패, 사용자 취소·정상 중단에서 실패 감지와 가능한 원상 복구를 검증한다. CSV 누락이나 GPU Timing 부재를 정상 GPU Benchmark로 표시하지 않는다. Production Asset·기존 Level의 무변경을 확인한다. HTML은 수정된 가상 목업만 제공하고 실제 Analyzer·Confidence·등급·Report Generator는 구현하지 않는다. **실행 증거와 변경 목록 보고 후 Phase 2 승인을 기다린다.**

### Phase 2 — Generic Action Support · 구현·실측 검증 완료

**목적:** Runner 코드를 다시 작성하지 않고 네 Action을 Preset으로 선택하게 한다.

**산출물:** MaterialSwap·ScalarParameter·ActorVisibility·ConsoleVariable 처리부, Action별 Preset, 검증·복원 규칙, CVar Allowlist.

**합격 기준:** 각 Action에 최소 하나의 실제 A/B 시험을 수행한다. 적용값·대상·Slot·Parameter·Visibility/Shadow 정책·CVar 읽기 확인이 기록된다. 같은 Runner로 새 Preset을 추가해 실행한다. 미지원 CVar를 명확히 거부한다. 정상·실패·취소에서 원래 상태를 복원한다. **기능별 PASS/WARNING/FAIL 보고 후 Phase 3 승인을 기다린다.**

### Phase 3 — Analyzer·Grades·HTML Report · 구현·검증 완료

**목적:** 실제 Raw CSV를 반복 가능한 통계와 정직한 해석으로 변환한다.

**산출물:** 외부 Analyzer, 버전별 CSV Mapping, Summary.csv, 독립형 Report.html, 조정 가능한 평가 Config, 더블클릭 분석 Launcher, 정책 검증 기록.

**합격 기준:** 실제 CSV 구조로 Parser를 검증하고 수동 계산 표본과 대표 통계·P95·Delta가 일치한다. 2%·5%·70%·100% 경계와 음수·0·누락·무효·짧은 Capture·중복 ID를 검증한다. A/A·AB 변동과 Noise Floor 후보를 실측 자료로 검토한다. Noise 안의 음수에 IMPROVED를 주지 않는다. GPU 누락·실패·불안정 자료에 GREEN을 주지 않는다. 원본 해시가 유지되고 분석 재실행 결과가 동일하다. HTML이 오프라인에서 정상 표시되고 시안 값이 실측으로 섞이지 않는다. **정책과 리포트 확인 후 Phase 4 승인을 기다린다.**

### Phase 4 — Usability·Documentation·Final Validation · 구현·개발자 검증 완료

**목적:** 사용자가 코드 수정 없이 반복 실행하고 결과를 해석할 수 있는 상태로 완성한다.

**산출물:** 정리한 Details Panel, 분석 Launcher, 한국어 설치·실행·Preset 작성·측정법·결과 해석·오류 해결·Known Limitations 문서, 최종 검증 목록과 실제 화면.

**합격 기준:** 다음 최종 Test를 실제 Unreal에서 수행하고 Evidence를 남긴다.

| Test | 확인할 내용 |
|---|---|
| A — A/A | 같은 상태의 반복 변동과 Confidence 판정 |
| B — Hair | 승인된 격리 복사본의 PDO 등 한 기능 A/B; Production 수정 없음 |
| C — General Material | Character와 무관한 Static Mesh Material A/B |
| D — Scalar | Parameter 값 적용·측정·복원 |
| E — Visibility | 지정 Visibility/Shadow 동작과 복원 |
| F — Runtime CVar | Allowlist 항목 적용 읽기·측정·복원 |
| G — Error Handling | 누락 대상·잘못된 Slot·Metric 누락·실패·취소 |
| H — Reuse | 새 Preset 추가만으로 실행, Runner 코드 수정 없음 |
| I — User Workflow | Preset 선택 → Standalone → 완료 확인 → 분석 더블클릭 → HTML 확인 |

각 Test의 PASS/WARNING/FAIL·Raw 위치·측정 Metric·제한을 공개한다. 임의의 성능 수치 목표를 만족했다는 이유만으로 Tool 완료를 판정하지 않는다. 실제 사용 흐름과 원본 무변경이 모두 확인되어야 V1 완료다.

Phase 4 Native 배포 버전은 `1.0.0-V1`이며 외부 Analyzer는 `0.3.1`이다. Analyzer는 RELIABLE일 때 차단 사유가 없는 것을 이유 누락으로 표시하던 문구를 바꾸어 통과한 A/A·반복·안정성·Noise Floor 조건을 설명한다. Parser·통계·Confidence·등급 정책·저장·CLI는 유지한다. Details에는 한국어 설명을 추가하고 Action별 필요한 필드만 표시한다. Property·Enum 이름·기본값·직렬화·Runtime Action·Warmup·CSV Capture 구조는 유지한다. Calibration Reference Run ID는 기록용으로 남기고 Analyzer에서 실제 A/A 폴더를 선택하여 연결한다.

새 시험 Asset은 `/URBenchmark/Phase4/`의 23개 Package다. 공통 Action Level과 Hair 단독 Level 두 개, Preset 14개, 시험 Material·MIC·Mesh와 Pawn 없는 시험 GameMode Blueprint를 제공한다. 두 Level은 이 GameMode를 사용하며 Hair Camera는 FOV 48로 전체 Mesh를 담는다. Hair A/B는 복사한 Parent·MIC·Mesh에서 `Use_HairPDO` OFF/ON만 비교하고 Production은 저장하지 않는다. Texture·Material Function은 현재 프로젝트의 `/Game/ASF/` Asset을 읽기 전용 참조하므로 Hair 예제는 Plugin만 빈 프로젝트에 복사하여 완전히 이식할 수 있는 구성은 아니다.

초기 실제 화면에서 DefaultPawn의 구체가 외부 Camera에 나타나 Hair를 가리는 시험 환경 문제를 발견했다. 수정 전 실행·분석은 보존하되 Hair 성능의 최종 근거로 채택하지 않았다. Pawn 없는 GameMode와 Camera 수정을 적용한 뒤 A~H와 오류 경로를 포함한 19개 Runtime 사례 전체를 첫 실행에서 통과하고 실제 Hair 표시까지 확인했다. 정상 11개 Run·126 Capture·37,800프레임과 Production 보호 153개·기존 Benchmark Content 42개 불변을 독립 검증했다. I는 새 Editor에서 Preset 선택·검증, Standalone 모드 선택 후 초록색 Play, 완료·복원, Explorer에서 Analyze.pyw 실제 더블클릭, Run 폴더 선택과 HTML 열림까지 완주했다. 실제 Esc 입력도 취소와 쓰기 완료 후 복원을 확인했다. 현재 0.3.1 HTML의 Desktop·500px 화면과 로컬 링크를 검증했다. 최종 상태·RunID·리포트·화면은 `Phase4_Implementation_KO.md`와 Evidence를 기준으로 한다.

## 12. V1 제외 범위

Multi-Action 한 Test, Multi-Camera·Multi-Level Batch, 모바일 기기 자동 실행, Shader Instruction 자동 분석, GPU Pass Breakdown 자동 분석, Unreal Insights 자동 해석, Screenshot 자동 비교, 온라인 Dashboard·Database·Backend, PDF Report, CI/CD·Gauntlet, 독립 Application은 V1 필수 범위에서 제외한다. **독립형 HTML Report는 V1 필수다.**

## 13. Phase 결과 보고 양식

각 단계 보고에는 수행 범위, 실제 완료·미완료, 실행 환경, 검증 방법, Evidence 경로, 변경 파일, 원본 보존 확인, 오류·제약, 다음 단계 제안을 포함한다. 미실행을 PASS로 표기하지 않는다. 측정값과 가상 시안 값을 분리한다. 다음 Phase 승인을 받기 전에는 해당 Phase 코드·Asset·제품 기능을 구현하지 않는다.

이번 작업의 종료 지점인 **승인된 Phase 4 구현·실측·사용자 흐름의 개발자 검증을 완료**했다. 사용자는 V1 첫 실행 안내로 직접 시험할 수 있다. A~I와 증거는 Phase 4 보고서·`phase4/evidence/Final_Verification.json`을 따른다. 배포 복사본의 최종 해시 확인은 별도 복사 검증 기록으로 구별한다. 사용자 검증은 아직 수행하지 않았고, V1 이후 실제 PBR Character Scene의 Hair·Skin·Eye 전체 측정은 별도 작업이다.

## 14. 기술 근거

- [Epic IConsoleVariable 5.8 API](https://dev.epicgames.com/documentation/unreal-engine/API/Runtime/Core/IConsoleVariable?lang=en-US): CVar 읽기·설정·우선순위 이력 API를 참고하며 설치된 5.8.3 소스로 실제 복원 경로를 확인한다.
- [Epic Python Editor Scripting](https://dev.epicgames.com/documentation/en-us/unreal-engine/scripting-the-unreal-editor-using-python): Python의 Editor 전용 범위를 확인한다.
- [Epic Command Line Arguments](https://dev.epicgames.com/documentation/en-us/unreal-engine/command-line-arguments-in-unreal-engine): `-game` 독립 게임 실행 방식을 확인한다.
- [Epic Command Line Reference](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-command-line-arguments-reference): `-csvGpuStats` 등의 실행 옵션을 확인한다.
- [Epic CSV Profiler 4.27 문서](https://dev.epicgames.com/documentation/unreal-engine/csv-profiler?application_version=4.27): Capture 명령 개요를 참고한다. 해당 문서는 이전 버전이므로 5.8.3 동작과 Column을 확정하는 근거는 설치된 소스와 Phase 0 실출력이다.

설치 소스의 `Engine/Source/Runtime/Core/Public/ProfilingDebugging/CsvProfiler.h`와 대응 `.cpp`에서 Capture·비동기 저장 API를 확인한다. `Engine/Source/Runtime/Launch/Private/LaunchEngineLoop.cpp`의 `GPUTime`·`GameThreadTime`·`RenderThreadTime` 기록을 확인하고 실제 CSV Header와 대조한다. `GPU/*` Pass 값은 전체 `GPUTime`으로 대체하거나 합산하지 않는다.
