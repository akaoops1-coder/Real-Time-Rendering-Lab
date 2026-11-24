# RTR Universal Rendering Benchmark Tool V1 Phase 1 구현 보고

작성일: 2026-11-02 KST · 범위: **MaterialSwap Core Runner 실제 구현과 기존 목업 보완**

실제 `RTR_Advanced`에 전용 Runtime 플러그인과 15개 테스트 Asset을 추가했다. DX12·SM6의 Visible 게임 창에서 Standard A/B와 Calibration A/A를 각각 6회 × 300프레임 수집했고, 정상 실행의 Material·Camera·CVar와 우선순위·해상도 복원 읽기가 모두 일치했다. **Phase 2~4는 구현하지 않았다.** Runtime 검증 Suite의 13개 사례는 모두 예상 상태와 복원 읽기를 통과했고, 기존 보호 파일 153개가 일치했다. 최종 빌드에서 실제 Details의 Validate Preset 버튼과 기본 Standalone Play 실행도 확인했고, 추가 6회 × 300프레임과 복원을 검증했다.

## 1. Implementation Summary

구현 경로는 `local path withheld`다. 플러그인 전용 `/URBenchmark/` Content에 새 Level·Runner·Preset·Material을 만들었다. 기존 Production Level에 Runner를 저장하거나 Production Shader의 Static Switch를 바꾸는 방식은 사용하지 않았다.

| 구현 기능 | 현재 동작 |
|---|---|
| 설정용 Blueprint | `BP_URB_Runner`에서 Data Asset Preset과 자동 시작 여부를 Details로 선택 |
| Test Preset | UDataAsset에 TestID·Tag·Material Slot·CameraTag·MIC A/B·Warmup·Capture·반복·해상도·예산 FPS 저장 |
| 유일한 대상 식별 | Actor Tag, 해당 Actor 안의 Mesh Component Tag, Camera Tag가 각각 하나만 일치해야 실행 |
| MaterialSwap | 사전 준비한 MIC 두 개를 교체하고 Warmup 전·Capture 전후 실제 Slot Material 읽기 확인 |
| 실행 모드 | 기본 Standard A/B; 별도 Calibration A/A; Standard 앞의 Calibration은 사용자 선택 |
| 수집·완료 | Phase 0 FCsvProfiler 경로를 재사용해 요청 프레임 수·Metadata·비동기 저장 완료·Raw 유효성 검사 |
| 준비 상태 | Shader·Material·초기 로딩·Streaming·PSO 준비를 확인한 뒤 동일 Warmup 수행 |
| 상태·복원 | IDLE·VALIDATING·PREPARING·WARMUP·CAPTURING·RESTORING·COMPLETED·FAILED·CANCELLED; Material·Camera·CVar와 우선순위·해상도 복원 |
| 결과 | 고유 RunID별 Raw CSV, Manifest.json, Execution.log, Completion.json |

Capture 중 Runner 상태 HUD와 엔진 CSV 프레임 표시를 숨긴다. `GAreScreenMessagesEnabled`는 Capture 구간에만 false로 두고, `csv.AlwaysShowFrameCount=0`을 임시 적용해 원래 값·우선순위를 복원한다. 이후 다른 상태와 완료·실패는 간단한 표시 및 로그로 확인하게 했다. 기존 결과 파일은 덮어쓰지 않는다. Target FPS=60은 예산용이며 실제 Capture를 60FPS로 제한하지 않는다.

기존 Dark UI와 레이아웃을 유지해 HTML 목업을 보완했다. Report에는 낮은 시각적 우선순위의 CPU/Frame A/B·Delta 표와 A/A 변동·A/B 변동·Noise Floor·Delta·판정 이유를 추가했다. 주요 보조 글자는 12px 이상으로 키웠다. Details 목업에는 Tag 기반 식별·중복 오류·선택 Calibration·기본 Standalone 메뉴 흐름을 반영했다. 두 목업은 Chrome으로 렌더링해 잘림·겹침을 확인했으며, 모든 예시 수치는 가상 데이터로 표시했다.

**미구현 범위:** ScalarParameter·ActorVisibility·ConsoleVariable·범용 Action 확장, 제품 CSV Analyzer, Noise/Confidence 평가, Impact/Budget 등급, Summary.csv와 Report.html 자동 생성. 아래의 단순 검증 통계는 제품 Analyzer 기능이 아니다.

## 2. Test Results

실행 환경은 Unreal Engine 5.8.3, RTX 5080, DX12·SM6, 실제 1920×1080이다. 성공한 두 실행은 실제 RTR 프로젝트의 `/URBenchmark/Maps/L_URB_MaterialSwap`을 별도 Visible 게임 프로세스에서 열었다. Offscreen 결과로 Visible 검증을 대신하지 않았다. 기존 작업 Editor는 종료하지 않았다.

| 요청 테스트 | 확인 결과 | 판정 |
|---|---|---|
| Test 01 — Standalone Execution | 실제 RTR 프로젝트의 Visible 게임 창에서 Standard·Calibration 완료. 최종 빌드의 실제 Validate Preset 버튼·기본 Standalone Play 조작과 추가 6회 수집 완료 | PASS |
| Test 02 — Material A/B | OFF/ON MIC를 기본 A→B→B→A→A→B로 6회 교체; 각 300프레임과 Material 읽기 검증 완료 | PASS |
| Test 03 — Static Switch MIC | 새 Parent의 UseDetail Switch OFF=false·ON=true, 두 MIC의 Override=true 읽기; DMI 교체와 구분한 실제 MIC 실행 | PASS |
| Test 04 — Shader Model 6 | 두 성공 Run의 Manifest와 Runtime에서 D3D12·SM6 확인 | PASS |
| Test 05 — A/A Calibration | 같은 실제 MIC_A를 두 라벨로 6회 × 300프레임 수집; 별도 Preset으로 실행 | PASS |
| Test 06 — Error & Restoration | 누락·중복·Slot·Material 적용·Capture Busy·Warmup/Capture 취소가 예상 FAILED/CANCELLED와 일치하고 필요한 복원 읽기 확인 | PASS — Runtime 경로 |
| Test 07 — Production Asset Protection | 기존 `.uproject + Content + Config` 153개 보호 파일 SHA-256 일치, 기존 보호 경로의 추가·누락 없음. 새 기능은 전용 Plugins/URBenchmark 경로에 추가 | PASS |

### 완료한 정상 실행

| 실행 | RunID | 유효 Capture / Frame | 최종 상태 | 복원 읽기 |
|---|---|---|---|---|
| Standard Visible | `20261102T133753_URB_Standard_FFF255F9` | 6개 × 300 = 1,800 | COMPLETED | Material·Camera·CVar와 우선순위·해상도 모두 true |
| Calibration Visible | `20261102T133818_URB_Calibration_F3CFE00A` | 6개 × 300 = 1,800 | COMPLETED | Material·Camera·CVar와 우선순위·해상도 모두 true |

실제 출력 Metric은 `FrameTime`, `GameThreadTime`, `RenderThreadTime`, `GPUTime`이며 단위는 ms다. Helper는 실제 Header 이름을 찾고 끝의 반복 Header·Metadata를 제외한다. GPU 값의 부재·무효·0을 정상 GPU 수집으로 처리하지 않는다.

최종 HUD 수정본의 Calibration 여섯 Run에서 GPU Median은 2.34485~2.35220ms였고 Run Median의 최대−최소 범위는 **0.00735ms**였다. FrameTime Run Median 범위는 3.76450~3.85545ms였다. 이는 해당 실행의 단순 변동 기록이며 Noise Floor·RELIABLE·성능 등급 판정이 아니다. Standard GPU Run Median 범위 2.34455~2.34955ms도 특정 Shader의 추가 비용으로 해석하지 않는다.

### 오류·취소 경로

아래 PASS는 Benchmark가 성공했다는 뜻이 아니라, **예상한 FAILED 또는 CANCELLED와 필요한 복원 동작을 확인했다는 뜻**이다. 개발용 Fault Injection으로 재현한 항목은 실제 Runtime 경로에서 실행하되 일반 Preset 기능과 구분한다.

| 사례 | 재현 방법 | 현재 확인 결과 |
|---|---|---|
| Target Actor 없음 | `DA_URB_MissingActor` | PASS — 예상 FAILED |
| Component 없음 | `DA_URB_MissingComponent` | PASS — 예상 FAILED |
| Material Slot 오류 | `DA_URB_InvalidSlot` | PASS — 예상 FAILED |
| Actor Tag 중복 | `DA_URB_DuplicateActor` | PASS — 임의 선택 없이 FAILED |
| Component Tag 중복 | `DA_URB_DuplicateComponent` | PASS — 임의 선택 없이 FAILED |
| Camera 없음 | `DA_URB_MissingCamera` | PASS — 예상 FAILED |
| Camera Tag 중복 | `DA_URB_DuplicateCamera` | PASS — 임의 선택 없이 FAILED |
| Material 적용 실패 | 개발용 Material 읽기 불일치 주입 | PASS — 예상 FAILED |
| Capture 시작 실패 | 개발용 CSV Profiler Busy 조건 주입 | PASS — 예상 FAILED |
| Warmup 중 취소 | 개발용 Warmup 30프레임 시점 취소 요청 | PASS — CANCELLED와 복원 읽기 |
| Capture 중 취소 | 개발용 Capture 도중 취소 요청 | PASS — 파일 완료 뒤 CANCELLED·복원, 짧은 CSV를 정상 Benchmark로 판정하지 않음 |

기본 Evidence는 Runtime Case Suite와 사례별 Runtime Log·Completion/Manifest다. 실제 원본 Run은 `RTR_Advanced/Saved/URBenchmark/<RunID>/`에 보존한다. Phase 1 Verification의 `case_count=13`, `all_cases_pass=true`, `phase1_validation_pass=true`로 Runtime Suite와 보호 해시의 최종 집계를 확인했다. 검증 전 오류는 상태 변경이 없으며, 변경 후 오류·취소는 Material·Camera·CVar와 우선순위·해상도 복원 읽기가 모두 true다.

### 초기 실패와 수정 검증

첫 Asset 생성 시도에서 Static Switch 입력을 A/B로 연결한 경로가 실패했다. 실제 Expression의 True/False 입력으로 수정한 뒤 새 Parent와 MIC 생성·Switch 값 읽기·Asset 저장을 완료했다. Asset Creation 기록의 상태는 COMPLETED, 생성·저장 Asset은 15개, Material Compile Error 목록은 비어 있다.

초기 Runtime `20261102T131144_URB_Standard_74DB7A1E`는 Capture가 없는 실패 실행으로 남겼다. 준비 대기 중 취소되었으며 Material·Camera·CVar 복원은 true였지만 해상도 복원은 false여서 최종 상태가 FAILED였다. BeginPlay 시점의 Viewport 크기 0을 원래 해상도로 보관한 문제를 확인했다.

자동 시작을 첫 유효 게임 Viewport·PlayerController가 준비된 Tick으로 늦추고, A/B Material의 준비를 `EnsureIsComplete`와 준비 상태 검사로 보완했다. 수정 후 Standard·Calibration의 현재 Run은 Capture와 모든 복원 읽기를 통과했다. **이전 준비 지연 전체가 B Material 미렌더링 하나 때문에 발생했다고 단정하지 않는다.** 초기 실패 자료를 성공 Run에 합치거나 덮어쓰지 않았다.

## 3. Unreal Assets

새 Asset은 모두 `/URBenchmark/` 플러그인 Content 안에 있다.

| 종류 | Asset |
|---|---|
| Blueprint Runner | `/URBenchmark/Blueprints/BP_URB_Runner` |
| 전용 Test Level | `/URBenchmark/Maps/L_URB_MaterialSwap` |
| Static Switch Parent | `/URBenchmark/Materials/M_URB_StaticSwitch` |
| Variant A / B | `/URBenchmark/Materials/MI_URB_Detail_OFF`, `/URBenchmark/Materials/MI_URB_Detail_ON` |
| 복원 확인용 원래 Material | `/URBenchmark/Materials/MI_URB_Original` |
| 정상 Preset | `/URBenchmark/Presets/DA_URB_Standard` |
| Calibration Preset | `/URBenchmark/Presets/DA_URB_Calibration` |
| 오류 Preset 7개 | `DA_URB_MissingActor`, `DA_URB_MissingComponent`, `DA_URB_InvalidSlot`, `DA_URB_DuplicateActor`, `DA_URB_DuplicateComponent`, `DA_URB_MissingCamera`, `DA_URB_DuplicateCamera` — 모두 `/URBenchmark/Presets/` |

총 15개다. 테스트 Scene은 Sphere 63개, 고정 Camera와 독립 조명, 유효 대상·Tag 중복 검증용 Fixture로 구성했다. UseDetail Static Switch는 테스트 Material의 색 분기를 바꾸는 최소 기능이다. Hair PDO, PBR Character Shader 또는 Production Shader의 성능 결과가 아니다.

## 4. Technical Decisions

**Blueprint는 설정·배치용 Wrapper, Native Runner는 제어 로직, 별도 Capture Component는 CSV 수집 장치**로 역할을 나눴다. Blueprint Graph에서 파일 완료·오류·복원 처리를 다시 구현하지 않아 동일한 검증 경로를 사용한다. 사용자는 Preset과 Details만 편집한다.

| 구성 | 책임 |
|---|---|
| `UURBTestPreset` | UDataAsset 기반 조건 저장; Actor/Component/Camera Tag, MIC와 RunMode |
| `AURBRunner` / `BP_URB_Runner` | Preset 복사, 유일한 대상 찾기, 준비·교체·Warmup·반복, 상태 표시, 원상 복원 |
| `UURBCaptureComponent` | FCsvProfiler 점유·정확한 프레임 수·Metadata·비동기 파일 완료·실제 CSV 유효성 확인 |

Helper는 Phase 0에서 확인한 `BeginCapture`·`OnCSVProfileFinished`·`IsCapturing`·`IsWritingFile`·`IsEndCapturePending` 경로를 재사용했다. CSV Writer의 완료 알림은 Game Thread로 전달한 뒤 대상 파일과 상태를 확인한다. 파일 존재나 Capture 요청 성공만으로 완료 처리하지 않는다. CSV Profiler가 다른 Capture에 사용 중이면 임의로 정상 Benchmark를 시작하지 않는다.

플러그인은 Runtime Module 하나와 전용 Content를 가진 작은 구성이다. EnabledByDefault 방식으로 프로젝트에 로드되며 새 기능을 위해 기존 프로젝트를 C++ Project Module로 전환하는 구조는 사용하지 않았다. 기존 `.uproject`·Config·Content의 무변경은 보호 파일 153개 해시 대조로 확인했다. Saved·Intermediate·공용 엔진 Cache는 이 보호 파일 집계에 포함하지 않는다. 준비·Asset 생성용 Python은 Editor에서만 사용하며 Runtime은 Python에 의존하지 않는다.

## 5. User Guide

상세 안내는 Phase 1 실행 안내에 있다.

1. 기존 미저장 Production 작업 Editor를 유지하고, 새 플러그인을 읽은 Editor 프로세스에서 `/URBenchmark/Maps/L_URB_MaterialSwap`을 연다.
2. `BP_URB_Runner`를 선택하고 Preset에 `DA_URB_Standard` 또는 `DA_URB_Calibration`을 지정한다.
3. Preset Details에서 대상 Tag·Slot·MIC·Capture 조건을 확인하고, 필요한 변경은 Preset·전용 Level에 저장한다. 원래 Production Asset은 저장하지 않는다.
4. `Validate Preset`으로 설정을 확인하고 **Play ▾ → Standalone Game**을 실행한다. Auto Run On Begin Play가 켜져 있으면 자동 측정한다.
5. 완료·실패·취소 상태와 복원 결과를 확인한 뒤 `Saved/URBenchmark/<RunID>/`를 연다. 사용자 취소는 Esc 경로를 제공하며 실제 입력 검증 상태는 최종 UI 검증 기록을 따른다.

Standard의 RunCalibration은 기본 false다. Calibration을 매 A/B 앞에 강제하지 않는다. 별도 Calibration 또는 선택 실행 결과의 연결 정보는 기록하지만, Phase 3 이전에는 최종 Confidence를 표시하지 않는다.

## 6. Remaining Issues

- 최종 빌드의 Runtime Suite 13개 사례와 보호 파일 153개 해시 대조를 완료했다. 실제 Editor 버튼·기본 Standalone Play 조작과 추가 6회 Capture도 완료했다. Editor UI 검증 증거를 참조한다.
- 개발용 Fault Injection으로 취소 API 경로를 확인하는 것과 실제 Esc 키 입력·Editor 메뉴 조작은 구분한다. 최종 결과에는 각각의 증거를 제시해야 한다.
- 이번 Scene은 최소 Static Switch 색 분기 검증이다. 실제 Character·Hair 기능 비용·품질 차이를 측정한 결과는 없다.
- 강제 종료·프로세스 충돌에서는 파일 저장 완료나 모든 Runtime 복원을 보장하지 않는다. EndPlay는 가능한 복원을 시도하고 중단된 Capture를 완료로 표시하지 않는다.
- 기존 Editor가 동시에 실행되어 있다. 이번 단계는 수집 기능과 복원 검증을 확인하는 것이며 성능 차이에 확정 등급을 부여하지 않는다.
- 새 Native 플러그인은 이미 열린 기존 Editor에 자동으로 모두 반영되지 않을 수 있다. 미저장 작업을 닫거나 강제로 저장하지 않고 별도 Editor 또는 이후 사용자가 선택한 재시작으로 사용한다.
- 시안의 Confidence·Impact·Budget·CPU 표는 화면 제안이다. 실제 CSV 연동과 보고서 생성은 Phase 3 이전에 구현하지 않는다.

## 7. Next Phase Recommendation

최종 검증에서 Phase 1의 실행·오류·취소·복원·원본 보호와 사용자 흐름을 확인한 뒤 사용자의 승인을 기다린다. Phase 2는 ScalarParameter·ActorVisibility·ConsoleVariable을 같은 Preset/Runner 흐름으로 확장하는 단계다. 각 Action의 실제 적용 읽기와 복원, Runtime CVar Allowlist를 검증하고 현재 MaterialSwap의 정확한 수집·파일 완료 경로를 유지해야 한다.

Phase 3의 Analyzer·Noise·Confidence·성능 등급·Report Generator와 Phase 4의 전체 통합 검증은 이후 승인 범위다. 이번 작업에서 선행 구현하지 않는다.


최종 GUI 실행 RunID는 `20261102T134209_URB_Standard_A5D95ED8`다. 완료 후에는 원래 플레이어 시점·창 크기로 복원하므로 Benchmark Camera의 구도와 달라질 수 있다. 테스트 Level의 기본 플레이어 시점에서는 엔진 Exposure 안내가 나타날 수 있으며, 완료 후 장면을 Production 성능 결과로 해석하지 않는다.
