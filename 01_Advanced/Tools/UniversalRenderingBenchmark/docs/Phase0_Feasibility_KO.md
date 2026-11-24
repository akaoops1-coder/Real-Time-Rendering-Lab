# RTR Universal Rendering Benchmark Tool V1 Phase 0 실측 검증

검증일: 2026-11-02 KST · 상태: **Feasibility PASS — 독립 DX12 SM5 게임 모드 진단 범위**

실제 GPU/CPU CSV 수집, Dynamic Material Instance A/B 교체, Capture 전 120프레임 Warmup, 300프레임 수집, 비동기 파일 완료와 Capture 식별 연결을 확인했다. **Phase 1~4 제품 기능은 구현하지 않았으며 사용자 승인 대기 상태다.** 기존 Production Shader의 비용 또는 Green/Yellow/Red 등급을 측정한 결과는 아니다.

## 1. 확인한 환경과 보호 범위

| 항목 | 실제 확인값 |
|---|---|
| Engine | Unreal Engine 5.8.3, CL 58210709 |
| OS | Windows 11 25H2, 10.0.26200.9711 |
| CPU | AMD Ryzen 7 5800X 8-Core |
| GPU / Driver | NVIDIA GeForce RTX 5080 / 617.42 |
| 실행 | `UnrealEditor-Cmd.exe <독립 프로젝트> /Engine/Maps/Entry -game -RenderOffscreen -dx12 -csvGpuStats` |
| 실제 RHI / Shader | D3D12 / SM5 / PCD3D_SM5 |
| 실제 Viewport | 1920×1080 |
| 실제 설정 읽기 | ScreenPercentage=100, VSync=0, t.MaxFPS=0, DynamicRes.OperationMode=0, GPUCsvStatsEnabled=1 |
| Scene | Engine Sphere 63개, 고정 Camera(-1300,0,0), 독립 Directional Light |
| Material Instances | Engine BasicShapeMaterial / WorldGridMaterial을 Parent로 한 `MID_URB_Phase0_A/B` |
| 보호한 기존 프로젝트 | `local path withheld` |
| 원본 보존 확인 | `.uproject`와 Content·Config 아래 전체 **153개 파일** SHA-256 일치, 추가·누락 없음 |

원본 Editor는 이미 실행 중이었고 그대로 두었다. 별도 프로세스의 자체 Config와 Runtime 객체만 사용했다. 원본 Content·Config·프로젝트 파일을 저장하거나 변경하지 않았다. 무변경 확인 범위에는 원본 Saved·Intermediate·공용 엔진 Cache는 포함하지 않는다. 엔진 실행 중 일반적인 Cache 생성은 발생했다.

## 2. 실제 실행과 결과

먼저 Engine Material 두 개로 예비 12회 수집을 성공시켰다. 이후 Dynamic Material Instance를 생성·재사용하는 최종 진단으로 다시 12회 수집했다. 예비 원본도 보존했다. 아래 판정과 통계는 **최종 Instance 실행** 기준이다.

| 검증 | 실제 결과 | 판정 |
|---|---|---|
| 독립 Runtime 실행 | 게임 모드와 GPU 렌더링 실행; Capture 전 PNG로 실제 Sphere 렌더 확인 | PASS |
| A/A | A/B 두 라벨의 실제 Material은 같은 MID_A; `A B B A A B` 6회 | PASS |
| A/B | MID_A / MID_B를 `A B B A A B` 순서로 교체; 각 Variant 3회 | PASS |
| Warmup | 12회 모두 Capture 전 120프레임; Shader 준비 확인 후 시작 | PASS |
| CSV | 12개 모두 유효한 숫자 프레임 300개, 총 3,600프레임 | PASS |
| GPU | 12개 모두 `GPUTime` 300개가 양수·유한값 | PASS |
| CPU / Frame | `FrameTime`, `GameThreadTime`, `RenderThreadTime` 실출력 확인 | PASS |
| Material 적용 | 모든 교체에서 63개 Component의 Slot 읽기 결과가 지정 MID와 일치 | PASS |
| 식별 | CSV Metadata의 TestID·CaptureIndex·Variant·ActualMaterial과 이벤트 기록 대조 | PASS |
| 경계·완료 | Apply → CaptureRequest → FileFinished → CaptureComplete 순서가 12회 모두 일치 | PASS |
| 설정·해상도 | 요청값과 Runtime 읽기 값 일치 | PASS |
| 종료 | 마지막 파일 쓰기 완료 후 MID_A 상태 복원, 완료 JSON 기록과 프로세스 종료 | PASS |
| Production 보존 | 보호한 153개 파일 해시 일치 | PASS |

최종 RunID: `20261102T122937_53BACDE8`.

- 검증 결과 JSON
- Runtime 로그
- 실제 상태·교체·완료 이벤트
- 최종 원본 CSV 폴더
- Capture 전 렌더 확인 PNG
- 원본 보호 대상 해시

## 3. 확정한 CSV 구조와 Metric

각 파일은 첫 Header, 300개의 프레임 행, 끝에 반복된 Header, Metadata 행으로 구성되어 이번 출력은 총 303개 CSV Record였다. 끝의 두 행을 프레임으로 집계하면 안 된다. Column의 위치와 개수는 실행에 따라 달라졌으므로 숫자 위치를 고정하지 않고 **실제 Header 이름으로 찾는 방식**을 사용해야 한다.

| 정확한 Column | 단위·의미 | 이번 12회 Run Median 범위 |
|---|---|---|
| `FrameTime` | ms, 프레임 시간 | 7.4927~8.7390 |
| `GameThreadTime` | ms, Game Thread 시간 | 1.1218~1.2352 |
| `RenderThreadTime` | ms, Draw/Render Thread 시간 | 7.5035~8.8072 |
| `GPUTime` | ms, 엔진 RHI GPU Frame Timing | 1.5705~1.5817 |

위 범위는 Run별 Median의 최솟값과 최댓값이다. 개별 기능의 비용 또는 GPU가 전체 Frame을 결정한다는 뜻이 아니다. `GPU/*` Pass 지표를 합산하거나 CPU 값을 GPU 대신 사용하지 않았다. 이번 진단은 GPU 필수 지표를 확인하는 목적이며 모든 CPU 추가 지표의 제품 지원을 확정하지 않았다.

최종 CSV에 기록된 `[urbtestid]`, `[urbcaptureindex]`, `[urbvariant]`, `[urbactualmaterial]`, `[csvid]`를 파일·이벤트와 대조했다. A/A의 B 라벨에도 실제 MID_A가 기록되어 있으며 오류가 아니다. `[targetframerate]=60` Metadata는 속도 제한 확인 수단이 아니다. `t.MaxFPS=0`·VSync=0을 직접 읽었고 300프레임이 약 2초대에 수집된 것으로 제한 없는 실행을 교차 확인했다.

## 4. 사용한 API와 권장 구조

| 기능 | 실제 사용한 경로 |
|---|---|
| Runtime Material Instance | `UMaterialInstanceDynamic::Create`, `UStaticMeshComponent::SetMaterial/GetMaterial` |
| 프레임 기반 준비·반복 | `UGameInstance` + `FTickableGameObject` 진단 코드 |
| Shader 준비 확인 | `GShaderCompilingManager->IsCompiling()` 확인; PSO 전체 안정성 보장은 아님 |
| 정확한 프레임 수 Capture | `FCsvProfiler::BeginCapture(300, Folder, Filename)` |
| CSV 식별 Metadata | `FCsvProfiler::SetMetadata` |
| 저장 완료 | `OnCSVProfileFinished` 알림을 Game Thread로 전달 |
| 다음 Capture 조건 | `!IsCapturing && !IsWritingFile && !IsEndCapturePending` |
| 종료 | 마지막 저장 완료 후 `FPlatformMisc::RequestExit(false)` |

`csvprofile START/STOP/FRAMES=N` 콘솔 명령은 설치 소스와 공식 문서에서 조사했다. **이번 반복 실행에서는 위 Runtime API를 실측 검증했으며, Blueprint에서 명령 문자열만 사용하는 방식까지 검증했다고 주장하지 않는다.** `-csvGpuStats`와 설정 읽기를 통해 실제 GPU 출력이 생성됨을 확인했다.

권장 제품 구조는 Blueprint Runner·Preset·Details Panel을 유지하고, 저장 완료·Metadata·상태 읽기에 한정한 작은 Runtime Helper를 연결하는 방식이다. 진단 프로젝트에는 별도 Runtime Module 하나만 추가했으며 기존 RTR_Advanced에는 Module이나 Plugin을 추가하지 않았다. Phase 1에서 Helper를 재사용 가능한 형태로 옮기는 작업과 배포·빌드 방식을 정해야 한다. 이 경우 C++ 컴파일 환경이 필요하며 이번 장비의 Visual Studio MSVC 14.50 / Windows SDK 10.0.22621로 빌드가 성공했다. 대형 Profiling Framework를 새로 만들 필요는 확인되지 않았다.

## 5. 제한과 다음 단계

**Feasibility PASS와 성능 등급은 다르다.** 기존 Editor 동시 실행, 단순 Sphere 장면, SM5·Ray Tracing/GI 비활성 진단 조건이므로 Production SM6 장면 또는 Hair PDO 비용을 대표하지 않는다. 이번 결과에는 RELIABLE 또는 Green/Yellow/Red 성능 판정을 부여하지 않는다.

실제로 확인한 것은 Runtime DMI 교체다. 사전에 컴파일한 Static Switch Material Instance Constant 교체, Visible Standalone UI 흐름, Hair/General Preset, CVar·Visibility·Scalar Action, 오류·취소 복원, 제품 Analyzer·등급 정책·HTML 생성은 해당 Phase에서 검증한다. Static Switch를 Runtime DMI에서 변경하는 설계는 사용하지 않는다.

첫 실행에는 독립 진단의 Shader 준비가 수분 걸렸다. 초기에 제한된 실행 환경에서는 그래픽 프로세스 시작이 완료되지 않아 데스크톱 실행 권한으로 독립 프로세스를 시작했다. 일반 숨김 창 시작은 완료 전에 중단한 기록으로 보존했고, 최종 검증은 `-RenderOffscreen` 게임 모드로 완료했다. 빌드의 공용 Accelerator 경로 접근 문제는 진단 작업 폴더의 `-UBARootDir`를 지정해 해결했다. 파일 생성 실패를 정상 수집으로 처리하지 않았다.

**다음 요청 범위 제안:** Phase 1에서 MaterialSwap 최소 Runner, Preset, 별도 Test Level, 상태 표시, 정상·오류·취소 복원을 만든다. Visible Standalone 및 목표 SM6 조건에서 사전 준비 MIC와 실제 A/A·A/B를 검증한다. 현재는 실행하지 않고 사용자 승인을 기다린다.

## 6. 재현과 보관

진단 프로젝트 소스는 `phase0/URBProbe/Source`, 설정은 `phase0/URBProbe/Config`에 있다. 빌드 생성물·Shader Cache·임시 브라우저 Profile은 최종 도구 폴더에서 제외한다. 재현하려면 독립 프로젝트의 `URBProbeEditor Win64 Development` Target을 UE 5.8.3으로 빌드한 뒤 `phase0/evidence/launch.json`의 옵션으로 게임 모드를 실행한다. `Build_MI.log`가 최종 빌드 증거다. 다시 실행하면 고유한 RunID 폴더를 생성하여 기존 CSV를 덮어쓰지 않는다.

`verify_phase0.py`는 이번 진단 증거의 Header·프레임 수·Metric·Metadata·이벤트 순서·보호 파일 해시를 확인하는 전용 검사다. Phase 3의 범용 Analyzer 또는 제품 Report 생성기가 아니다. 일반 사용자가 코드를 편집하지 않는 제품 실행 흐름은 Phase 4 완료 조건이다.

공식 문서와 설치 소스 근거는 [Master Specification 기술 근거](Master_Specification_KO.md#14-기술-근거)에 정리했다.
