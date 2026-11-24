# RTR Universal Rendering Benchmark Tool V1 Phase 2 구현 보고

작성일: 2026-11-03 KST · 범위: **Generic Action Support**

MaterialSwap, ScalarParameter, ActorVisibility, ConsoleVariable을 한 Test Preset의 Action Type으로 선택하도록 통합했다. 기존 Runner의 Warmup·반복 측정·CSV Capture·파일 검증을 유지하고 Action별 적용 읽기와 복원을 추가했다. 실제 DX12·SM6 Standalone 검증 36개가 모두 예상 종료 상태와 적용·복원 검사를 통과했다. 정상 실행 14개에서 90개 Capture·27,000개 유효 프레임을 얻었고 기존 보호 파일 153개와 Phase 1 테스트 Asset 15개의 해시가 일치했다. Phase 3 Analyzer·Grades·HTML Report Generator는 구현하지 않았다.

## 1. 구현 범위와 구조

실제 설치 경로는 `local path withheld`다. 공통 Runner는 실행 순서·준비·Warmup·CSV·완료·취소를 담당하고, 실행마다 만든 UURBAction이 선택한 Action의 대상 검증·상태 보관·적용·읽기 확인·복원을 담당한다. 기존 BP_URB_Runner와 Phase 1 Asset을 재사용하며 Phase 2 시험 Asset은 새 `/URBenchmark/Phase2/`에만 추가했다.

기본 조건은 1920×1080, Screen Percentage 100, Capture마다 Warmup 120프레임과 Capture 300프레임, Variant별 3회다. A/B 순서는 A → B → B → A → A → B이며 Target FPS=60은 향후 예산 평가용이다. Calibration은 모든 Action에서 실제 A 상태를 두 라벨로 반복한다. 선택한 Run Calibration은 A/A 여섯 Capture 뒤 A/B 여섯 Capture를 수행한다.

CSV Helper는 Phase 1 소스와 같은 내용이다. 요청 파일과 완료 Callback의 식별, 비동기 쓰기 완료, 실제 Header 이름, 정확한 유효 프레임 수와 GPU·CPU 데이터 검증을 그대로 사용한다. Capture 전후에는 Action 상태와 환경 CVar·Camera·해상도를 읽어 확인하고, Capture 중 HUD를 숨긴다. 오류·취소·정상 완료의 모든 종료 경로는 상태 복원을 거친다.

## 2. Action별 동작과 복원

| Action | 검증·적용 | 복원과 기록 |
|---|---|---|
| MaterialSwap | 유일한 Actor·Mesh Component와 Slot, 준비한 Material A/B를 확인하고 Slot 교체 | 원래 Slot Material과 실제 읽기 결과 |
| ScalarParameter | 원래 Slot Material의 Global Scalar 존재와 유한한 A/B 값 확인; transient DMI 한 개를 만들어 재사용 | 원래 Scalar 값, DMI Scalar 값과 원래 Slot Material 복원; DMI 경로·Object ID 기록 |
| ActorVisibility | Actor 범위는 Actor Hidden In Game, Component 범위는 Visible·Hidden In Game 변경; Shadow 정책 별도 적용 | Actor·Component별 원래 flag와 Cast Shadow·Cast Hidden Shadow 각각 복원; IsVisible·ShouldRender 읽기 기록 |
| ConsoleVariable | 고정 Allowlist와 Runtime flag·범위 확인; 적용 값·우선순위·태그 읽기 | 원래 값·우선순위·태그를 모두 읽어 복원 확인 |

Scalar 예제는 `URB_Blend` 원래 0.35, A=0, B=1이다. Material의 색상과 Roughness를 바꾸는 합성 검증이며 실제 Hair Shader 비용을 뜻하지 않는다. ActorVisibility의 세 Shadow 정책은 Preserve Original, Disable Shadows, Disable Hidden Shadows다. Component 설정은 자식으로 전파하지 않으며 Actor의 Shadow 정책은 해당 Actor가 소유한 Primitive Component에 적용한다.

CVar Allowlist는 `r.Tonemapper.Sharpen`의 0~10 유한 실수와 `r.BloomQuality`의 0~5 정수다. 임의 명령 문자열을 실행하지 않으며 목록 밖·범위 밖·Runtime 미지원 값은 `measurementStatus=UNSUPPORTED`로 거부한다. Run 상태는 FAILED로 종료하며 원인을 남긴다.

## 3. 실제 테스트 결과

검증 대상은 실제 RTR_Advanced, Unreal Engine 5.8.3 CL58210709, RTX 5080, DX12·SM6 Visible Standalone이다. 각 사례는 같은 최종 플러그인 Binary로 실행하고 결과 폴더와 Binary SHA-256을 묶어 기록한다. 컴파일 성공과 실제 Capture 성공을 구분한다.

정상 Action·Calibration·기존 Phase 1 호환 실행 14개를 아래 RunID에서 확인했다. 각 Capture는 120 Warmup 뒤 300개 유효 프레임을 수집했으며, Action·Camera·환경 CVar와 우선순위·태그·해상도의 복원 읽기가 일치했다. 36개 검증의 최종 집계는 정상 COMPLETED 14개, 예상 FAILED 16개, 예상 CANCELLED 6개이며 모두 PASS다.

| 실행 | RunID | Capture와 유효 프레임 | 상태·복원 |
|---|---|---|---|
| Scalar | `20261103T033600_URB2_Scalar_FD9E5632` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| VisibilityActor | `20261103T033629_URB2_VisibilityActor_328A257B` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| ConsoleVariable | `20261103T033654_URB2_ConsoleVariable_5F0442F2` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| MaterialSwap | `20261103T033752_URB2_MaterialSwap_A2E1F28C` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| VisibilityComponent | `20261103T033817_URB2_VisibilityComponent_F7C2F03C` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| VisibilityNoShadows | `20261103T033842_URB2_VisibilityNoShadows_909A2C7B` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| VisibilityNoHiddenShadows | `20261103T033907_URB2_VisibilityNoHiddenShadows_9EB72285` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| ConsoleBloom | `20261103T033932_URB2_ConsoleVariableBloom_C25200CC` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| ConsoleOriginalLayer | `20261103T033957_URB2_ConsoleVariable_F093F092` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| ScalarCalibration | `20261103T034023_URB2_CalibrationScalar_8E4B0AE2` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| VisibilityCalibration | `20261103T034048_URB2_CalibrationVisibility_A895BFB5` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| ConsoleCalibration | `20261103T034113_URB2_CalibrationConsoleVariable_B8917BEA` | 6 × 300 = 1,800 | COMPLETED; 복원 true |
| ScalarWithCalibration | `20261103T034138_URB2_ScalarWithCalibration_7DB2E5BF` | 12 × 300 = 3,600 | COMPLETED; 복원 true |
| LegacyPhase1 | `20261103T034733_URB_Standard_AE38CF4A` | 6 × 300 = 1,800 | COMPLETED; 복원 true |

Scalar는 URB_Blend 0/1을 읽었고 같은 DMI Object ID를 모든 Capture에서 유지했으며 종료 시 원래 약 0.35와 원래 Material을 복원했다. ActorVisibility는 Actor Hidden In Game 또는 Component Visible·Hidden In Game을 지정한 A/B 값으로 읽었고, 원래 서로 다른 Component별 Visibility·Shadow flag를 복원했다. Sharpen은 원래 -1의 Constructor 우선순위에서 0/2를 적용한 뒤 -1·원래 우선순위·태그로 복원했다. 원래 Console 우선순위 0.75를 준비한 별도 개발 검증도 0/2 적용 뒤 0.75·Console 우선순위로 복원했다. BloomQuality는 0/5를 적용하고 원래 값·우선순위·태그를 복원했다.

| 실제 적용 확인 | A 읽기 | B 읽기 | 종료 시 원래 상태 |
|---|---|---|---|
| Scalar URB_Blend | 0 | 1 | 원래 Scalar 약 0.35와 원래 MIC, transient Scalar 모두 일치 |
| Actor Visibility | ActorHidden=false, Primary ShouldRender=true | ActorHidden=true, Primary ShouldRender=false | ActorHidden=false; Primary·Secondary 각 원래 flag 일치 |
| Component Visibility | Visible=true, HiddenInGame=false | Visible=false, HiddenInGame=true | Visible=true·HiddenInGame=false·원래 Shadow flag 일치 |
| Disable Shadows 정책 | scoped CastShadow=false | scoped CastShadow=false | 원래 CastShadow=true 복원 |
| Disable Hidden Shadows 정책 | owned Primitive의 CastHiddenShadow=false | owned Primitive의 CastHiddenShadow=false | 원래 Primary=false·Secondary=true 각각 복원 |
| Sharpen 기본 원본 | 0 | 2 | -1·Constructor 우선순위·None 태그 복원 |
| Sharpen Console 원본 | 0 | 2 | 0.75·Console 우선순위·원래 태그 복원 |
| BloomQuality | 0 | 5 | 원래 값·우선순위·태그 복원 |

별도 A/A의 논리 라벨은 A/B 순서지만 실제 Action 상태는 모두 A였다. Run Calibration을 켠 ScalarWithCalibration은 A/A 여섯 Capture와 A/B 여섯 Capture를 하나의 실행으로 수집하고 복원했다.

| 오류·취소 검증 | 사례 수 | 예상·실제 종료 | 적용·복원 검사 |
|---|---|---|---|
| 누락 Scalar·Slot·중복 Component, 누락·중복 Actor·Component, 미지원·범위·정수 CVar | 9 | FAILED | 변경 전 거부, PASS |
| Scalar·Visibility·CVar 적용 읽기 불일치 | 3 | FAILED | 원래 Action·환경 복원, PASS |
| Scalar·Visibility·CVar가 Capture 중 바뀜 | 3 | FAILED | CSV 보존·실패 표시·복원, PASS |
| CSV Profiler Busy | 1 | FAILED | Capture 시작 거부·복원, PASS |
| Scalar·Visibility·CVar Warmup 취소 | 3 | CANCELLED | 원래 Action·환경 복원, PASS |
| Scalar·Visibility·CVar Capture 취소 | 3 | CANCELLED | 파일 완료 뒤 취소·복원, PASS |

정상 실행의 네 필수 Metric은 FrameTime, GameThreadTime, RenderThreadTime, GPUTime이며 실제 Header 이름으로 검사했다. GPU 값은 유한하며 0보다 크고, Capture별 필수 Metric·Metadata·300프레임·A/B 식별이 일치한다. LegacyPhase1은 기존 Level과 DA_URB_Standard를 변경하지 않은 상태에서 새 DLL로 6회 수집·복원하여 이전 Asset의 기본 MaterialSwap 동작을 확인했다.

**Editor UI 추가 검증도 PASS다.** 별도 Editor에서 Action Type 드롭다운의 네 선택지와 Scalar Parameter·A/B 값·Capture 설정을 확인하고, Validate Preset 버튼의 VALID 결과를 확인했다. 기본 Play 메뉴의 Standalone Game을 실행해 실제 게임 창의 URB COMPLETED를 관찰했다. 추가 RunID는 `20261103T035022_URB2_Scalar_368AC986`이며 같은 최종 Binary로 6×300프레임과 Scalar·Material·Camera·CVar·해상도 복원을 확인했다. 이는 위 36개 Runtime Suite와 별도의 실행이다. Editor UI 검증과 UI 관찰 기록에 근거를 남겼다. Preset 값을 바꾸거나 Production Asset을 저장하지 않았고 Capture 중 UI 조작·Screenshot을 수행하지 않았다.

Phase 2 Verification의 case_count=36, all_cases_pass=true, phase2_validation_pass=true와 production_protection.unchanged=true 결과를 확인했다. 기존 Phase 1 Content 보호의 asset_count=15, all_unchanged=true도 확인했다. Runtime Suite는 예상 종료 상태와 실제 종료 상태를 기록한다. 오류 사례의 PASS는 정상 Benchmark 완료를 뜻하지 않고, 예상한 거부·취소와 복원 동작을 확인했다는 뜻이다. 검증용 Fault Injection은 개발 빌드의 테스트 장치이며 일반 Preset 기능과 구분한다. 검사 스크립트는 Evidence 확인 도구이며 Phase 3 제품 Analyzer가 아니다.

## 4. 오류 처리와 제약

Scalar는 Global Parameter만 지원한다. Material Layer Parameter와 Custom Primitive Data에 연결한 Scalar는 지원하지 않으며 Static Switch를 Scalar로 변경할 수 없다. ActorVisibility는 독립 Actor를 대상으로 하며 Child Actor는 부모의 표시 조건을 상속하므로 거부한다. 숨겨진 Level이나 특수한 디버그 렌더링 조건에서 실제 ShouldRender가 기대 상태와 다르면 완료 처리하지 않는다. ShouldRender는 엔진의 표시 조건 읽기이며 화면의 모든 픽셀·Shadow를 자동 비교한 결과는 아니다.

CVar 값 변경에는 원래 설정 우선순위의 이력을 보존하는 임시 변경을 사용한다. 일반 원본은 고유 태그의 SetByTemp 항목을 추가하고 종료 시 그 항목만 Unset한다. 원래 값이 최상위 Console 우선순위이면 원래 우선순위·태그의 값을 바꿨다가 원래 값으로 되돌린다. Constructor 기본값에 ReplaceCurrentPriorityAndTag를 그대로 호출하면 Unreal 5.8에서 거부되는 경로를 설치 소스로 확인했고 이 경로를 사용하지 않는다.

초기 Evidence 검사기에서는 CSV의 선택 Stat Column이 수집 중 뒤에 추가된 행을 길이 불일치로 거부했다. 필수 네 Metric의 위치는 유지되어 있었으며, Raw와 Runtime 수집부는 변경하지 않았다. 검사기는 끝 Header가 초기 Header의 순서를 그대로 보존한 채 뒤에 Column을 추가하고 필수 Metric의 위치가 유일·동일한 경우만 허용하도록 보완했다. 초기 검사 결과는 Inspection_Attempt01.json에 보존했다. 이 보완은 실제 Unreal CSV 형식에 대한 Evidence 검사 규칙 수정이다.

이미 열린 Editor는 메모리에 읽은 Phase 1 Native Module을 계속 사용할 수 있다. 기존 Editor를 강제 종료하지 않고 새 DLL 이름과 Module Manifest로 다음 실행 프로세스가 Phase 2를 읽도록 설치했다. 사용자는 미저장 작업을 정리한 뒤 Editor를 새로 열어 Phase 2를 실행해야 한다. 단순히 Level만 다시 여는 것으로 Native Module이 바뀌지 않는다.

Runtime Last Message와 Output Log의 오류 원문은 영어다. 한국어 원인·확인 방법은 실행 안내의 오류 해결 표에 제공하며 UI 문구 정리는 Phase 4 사용성 검증에 남긴다.

정상 취소는 CSV 쓰기가 끝난 뒤 복원한다. 강제 종료·프로세스 충돌의 복원은 보장하지 않으며 EndPlay는 중단 기록과 가능한 복원만 수행한다. 패키징·Shipping, 다른 엔진 버전·장비, Production Character Scene은 이번 단계의 실측 범위가 아니다. 합성 Scene 수치를 실제 Hair·Skin·Eye 비용으로 환산하지 않는다.

기술 근거는 [Epic UMaterialInstanceDynamic 5.8 API](https://dev.epicgames.com/documentation/unreal-engine/API/Runtime/Engine/UMaterialInstanceDynamic)와 [Epic IConsoleVariable 5.8 API](https://dev.epicgames.com/documentation/unreal-engine/API/Runtime/Core/IConsoleVariable?lang=en-US)다. 설치된 5.8.3의 `Core/Public/HAL/IConsoleManager.h`, `Core/Private/HAL/ConsoleManager.cpp`, `Engine/Private/Components/SceneComponent.cpp`, `Engine/Private/Actor.cpp`로 우선순위·태그·Constructor 예외와 Visibility 읽기 동작을 대조했다. 독립 코드 검토는 검토한 소스 해시와 확인 항목을 기록한다.

## 5. 변경 파일과 Asset 보호

| 변경 영역 | 내용 |
|---|---|
| Native Source 추가 | URBAction.h/.cpp, URBCVarOverride.h/.cpp |
| Native Source 갱신 | URBTestPreset.h의 Action 선택·조건별 설정, URBRunner.h/.cpp의 공통 Action 연결·읽기·복원 |
| Native 수집부 | URBCaptureComponent.h/.cpp 내용 유지 |
| Plugin Descriptor | Version 2·VersionName 0.2.0-Phase2로 도구 버전 표기 갱신 |
| 설치 Binary | Phase 2 DLL과 UnrealEditor.modules; 이전 DLL은 보존 |
| 새 Material 2개 | M_URB2_Scalar, MI_URB2_Original |
| 새 Level 1개 | /URBenchmark/Phase2/Maps/L_URB_GenericActions |
| 새 Preset 21개 | 정상 Action·Shadow 정책·Calibration·오류 재현 Preset |
| 문서·검증 | Master v1.2, Phase 2 실행 안내·보고서, 준비·검증 스크립트, 로그·Raw·Manifest·Completion·해시 Evidence |

새 Asset은 총 24개이며 기존 Phase 1 Blueprint·Material·Preset·Level은 저장하지 않는다. 기존 `.uproject`, Production Content·Config와 관련 없는 저장소 문서·사용자 Git 변경은 보호한다. 실행 전후 SHA-256 비교에서 `.uproject + Content + Config` 153개가 모두 일치했고 기존 Content·Config의 추가·누락 파일은 없었다. 기존 Phase 1 Benchmark Content 15개도 모두 일치했다. 새 파일 목록과 설치 Binary는 Evidence에 기록했다. Commit·Push는 하지 않는다.

## 6. 사용자 실행 방법

1. 미저장 작업을 보호한 뒤 Phase 2 플러그인을 읽은 새 Unreal Editor에서 `/URBenchmark/Phase2/Maps/L_URB_GenericActions`를 연다.
2. World Outliner에서 BP_URB_Runner_Phase2를 선택하고 Preset을 지정한다. 기본 예제는 DA_URB2_Scalar다.
3. `/URBenchmark/Phase2/Presets/`의 Scalar, VisibilityActor, VisibilityComponent, ConsoleVariable, ConsoleVariableBloom 또는 MaterialSwap Preset을 선택할 수 있다. Preset의 Action Type과 Action별 A/B 값을 확인한다.
4. Validate Preset을 눌러 확인하고 변경한 Benchmark Preset·전용 Level만 저장한다.
5. 상단 Play 메뉴의 Standalone Game으로 실행한다. `URB COMPLETED`와 `Saved/URBenchmark/<RunID>/Completion.json`의 COMPLETED 및 복원 결과를 확인한다.
6. 취소는 Standalone 창에서 Esc를 누른 뒤 CANCELLED·복원 완료를 기다린다.

상세 항목·오류 해결은 Phase 2 실행 안내를 따른다. 결과는 Capture별 GPU·CPU Raw CSV와 실행 기록이며 이 단계에서는 자동 HTML 리포트가 생기지 않는다.

## 7. 다음 단계와 승인 대기

Phase 2의 요청 기능과 실제 실행·오류·취소·복원·원본 보존 검증을 완료했다. **Phase 3 시작 전에 사용자 승인을 기다린다**. 기존 순서대로 Phase 3에서 CSV Analyzer·통계·Confidence·Impact/Budget Grade·HTML Report Generator를 구현하고 Phase 4에서 사용성·문서·최종 흐름을 검증한다.

V1 전체가 완성되면 Production을 수정하지 않는 전용 PBR Character 시험 환경에서 Hair·Skin·Eye Material을 측정하고 실제 수치가 연결된 시각적 HTML Report까지 확인한다. 이번 단계에서 V1 전체 완료를 선언하지 않는다.
