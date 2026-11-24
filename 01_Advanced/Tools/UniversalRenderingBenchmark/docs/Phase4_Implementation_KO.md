# RTR Universal Rendering Benchmark Tool V1 Phase 4 구현·최종 검증 보고

작성일: 2026-11-03 KST · 상태: **V1 구현·개발자 검증 완료, 사용자 직접 검증 전**

사용자 승인에 따라 Phase 4의 한국어 Details 설명, 전용 최종 시험 환경과 V1 사용 문서를 완성했다. 기존 Runner의 Action 처리·Warmup·반복·GPU/CPU CSV Capture와 Analyzer의 Parser·통계·정책·저장을 유지한다. Analyzer 0.3.1은 RELIABLE 결과의 판정 근거 문구만 보완했다. 시험 환경을 수정한 뒤 Runtime 19개 사례 모두 첫 실행에서 예상 상태·적용·복원·자료 검증을 통과했다. A~I, 실제 Esc 취소와 복원·원본 보호·HTML 화면의 개발자 검증을 마쳤다. 사용자의 직접 검증은 아직 수행하지 않았으며 아래 안내로 시작할 수 있다. 실제 배포 복사본의 해시 확인은 별도 복사 검증 기록을 기준으로 한다.

## 1. 구현과 배포 버전

| 영역 | 변경 내용 |
|---|---|
| Details | Runner와 Preset에 한국어 ToolTip. Action별 필드 표시 유지. Run Calibration은 Standard에서만 표시 |
| 설정 설명 | Actor/Component Tag 구별, 0부터 시작하는 Slot, Scalar 지원 범위, Visibility/Shadow 범위, CVar Allowlist, 예산 전용 Target FPS |
| Calibration 안내 | A/A의 실제 적용 상태와 라벨 구별, Calibration Reference Run ID는 기록용이며 Analyzer에서 실제 폴더 연결 |
| Native | 1.0.0-V1. 기존 Property·Enum·기본값·직렬화·Runtime 로직 유지 |
| 외부 Analyzer | 0.3.1. RELIABLE 결과의 빈 차단 사유를 통과 조건 설명으로 표시. Parser·통계·판정 정책·저장·CLI 유지 |
| Launcher | 루트 Analyze.pyw가 phase4/analyzer를 사용하며 별도 Console 창 없이 실행. Analyze.cmd는 대체 실행·CLI |
| 전용 Asset | /URBenchmark/Phase4의 23개 Package: Level 2개, Preset 14개, 시험 Material/MIC/Mesh 6개, GameMode Blueprint 1개 |
| 사용자 문서 | 첫 실행, 설치, 새 Preset, 측정 조건, 결과 해석, 오류 대응, Known Limitations |

최종 Native Binary는 `UnrealEditor-URBenchmark-Phase4.dll`이며 SHA256은 `190C110A0B8F9D4F0B8D1BB31C6AE1C503EB2CC11D249359315F5665339D7E87`다. 동일 엔진 Build의 빌드·현재 프로젝트 설치가 확인되었으며 실제 프로세스가 이 Binary를 사용한 증거는 최종 Runtime 검증에 연결한다. 원래 열린 Editor는 이전 Native 모듈을 유지하므로 임의 종료하지 않고 별도 검증 프로세스를 사용한다.

`URBRunner.h`와 `URBTestPreset.h` 두 Header의 Editor Metadata만 변경했다. 나머지 Source는 Phase 3와 바이트가 같고, Header에서 UPROPERTY/UFUNCTION Metadata를 제외한 선언·기본값·함수 선언도 같다. Details_Metadata_Verification.json은 이 범위의 검증 PASS이며 Runtime·UI 전체 시험의 대체 증거는 아니다.

## 2. 실제 시험 환경과 원본 보존

검증 환경은 Unreal Engine 5.8.3 CL58210709, Windows, RTX 5080 Driver 617.42, Ryzen 7 5800X의 DX12·SM6 Standalone이다. 기본 조건은 1920×1080, Screen Percentage 100%, 각 Capture 전 Warmup 120프레임, Capture 300프레임, Variant별 3회다. 정상 A/B 예제는 A/A 6개 뒤 A/B 6개, 독립 A/A 예제는 실제 A 상태 6개를 수집한다.

시험 전 Production Content·Config·uproject 보호 파일 153개의 해시와 기존 Plugin/도구 배포본 해시를 기록했다. 새 Asset은 `/URBenchmark/Phase4/`에만 만들고 기존 Production·Phase 1~3 Asset은 저장하지 않았다. 수정 후 19개 시험의 독립 검증에서 Production 보호 153개와 기존 Benchmark Content 42개가 모두 불변이고, 예상한 새 Phase 4 Package 23개만 추가된 것을 확인했다. 현재 Benchmark Content는 65개, 각 정상 측정의 Source Content Index는 218개다. Phase4_Native_Verification.json에 목록·해시·검사 결과를 기록했다.

공통 Action Level은 `/URBenchmark/Phase4/Maps/L_URB_GenericActions`, Hair Level은 `/URBenchmark/Phase4/Maps/L_URB_HairIsolation`이다. 두 Level 모두 고정 Camera·수동 Exposure와 `/URBenchmark/Phase4/Blueprints/BP_URB4_GameMode`를 사용하며 장면의 애니메이션을 시험하지 않는다. GameMode의 Default Pawn Class는 None이다. Hair Camera는 FOV 48로 전체 Mesh를 담도록 수정했다. Fixture_Correction.json에 두 Level의 설정·CDO·변경 파일을 기록했고 새 프로세스의 AssetReload_Verification.json에서 저장된 설정을 다시 읽어 확인했다.

수정 후 실제 Standalone에서 Hair 전체가 구도 안에 있고 기본 Pawn 구체에 가려지지 않는 것을 확인했다. 추가 표시 확인 Run `20261103T113456_URB4_HairPDO_369D4B28`은 12 Capture 완료와 복원 true를 기록했다. 아래 화면과 Hair_Visible_Preview.json은 **표시·구도 진단 증거**다. 최종 성능 표는 별도로 다시 실행한 19개 사례의 독립 Hair Run을 사용하며 이 추가 Run의 수치를 대신 넣지 않는다.

수정 후 실제 Standalone Hair — 기본 Pawn 가림 없이 전체 Mesh 표시, FOV 48

화면은 실제 Standalone 표시 확인이며 성능 차이·시각 품질 점수·PDO 효과 비교 화면으로 해석하지 않는다. 수정 후 19개 Runtime 시험은 독립 검증을 통과했고 I 사용자 흐름도 별도 Run으로 완주했다. Fixture_Runtime_Verification.json은 저장된 NoPawn CDO·Level, 실제 GameMode Log와 사람이 확인한 Standalone 화면을 연결한다.

Hair Parent·MIC A/B·Static Mesh는 Production 원본에서 시험 전용 경로로 복사했다. `Use_HairPDO`는 A=OFF, B=ON이고 `PDO_Strength=0.1`과 다른 Scalar·Texture·Vector 값은 같다. 새 MIC의 Switch 값·Override Flag를 읽어 확인했다. Texture와 Material Function은 현재 프로젝트의 원본을 읽기 전용 참조한다. Hair 단독 시험이며 실제 Character Scene 전체·Skin·Eye·PDO Pass 절대 비용의 측정은 아니다.

## 3. A~I 최종 합격 기준과 현재 상태

수정한 시험 환경에서 Runtime 19개 전체를 다시 실행했고 예상 실패·취소 사례가 올바르게 거부·복원되는지를 별도로 확인했다. 19개 사례 모두 첫 실행에서 계약한 상태를 만족했다. Run의 FAILED와 시험의 FAIL은 같은 뜻이 아니다. 수정 전 Suite와 Hair 숫자는 최종 합격·성능 표에 사용하지 않았다. A~H의 상세 근거는 Native 검증, 독립 검토를 따른다.

| Test | 실제 확인할 내용 | 최종 결과 | 증거 |
|---|---|---|---|
| A — A/A | 실제 A만 반복, 변동·Noise·Calibration 진단 | PASS · 6 Capture, Range 0.02790ms | AA Run AA392308 |
| B — Hair | 격리 Hair의 PDO OFF/ON 적용·측정·복원 | PASS · 실제 표시·12 Capture·복원, 비교 RELIABLE | HairPDO Run 6D992167·실제 HTML |
| C — General | Character와 무관한 Static Mesh Material 교체·복원 | PASS · 12 Capture·복원. 작은 차이는 INCONCLUSIVE | General Run 4643E86B |
| D — Scalar | URB_Blend 0/1과 원래 0.35·Slot 복원, 단일 DMI 재사용 | PASS · 적용·같은 DMI·원래 값·Material 복원 | Scalar Run FE874915 |
| E — Visibility | Actor/Component 및 Shadow 정책별 적용·복원 | PASS · 4개 Preset 모두 적용·복원 | Visibility 4개 Run |
| F — Runtime CVar | Allowlist Sharpen/BloomQuality의 값·우선순위·태그 복원 | PASS · 2개 Preset 모두 적용·복원 | Sharpen 84D11908·Bloom 21B210A1 |
| G — Error | 누락 대상·Slot·미지원 CVar·적용 실패·중간 변경·Capture Busy·취소. 수집 자료의 복사본으로 GPU 열 누락 진단 | PASS · 8개 예상 오류·취소, GPU 누락·변조는 무등급 | 오류 Suite·MissingGPU 검증 |
| H — Reuse | 새 Preset만 추가하여 같은 Runner 실행 | PASS · 새 Preset으로 12 Capture·복원 | Reuse Run DE57B2C2·변경 범위 |
| I — User Workflow | 새 Editor Preset 선택 → 기본 Standalone → 완료·복원 → Explorer 더블클릭 → Run 선택 → HTML | PASS · 실제 입력 완주, 12 Capture·복원, 분석 PASS | UI_Workflow·30CCDBF0·화면·리포트 |

I는 새 Editor에서 Runner Preset 선택·Validate, Play 메뉴의 Standalone Game 모드 선택 후 초록색 Play, 게임 완료·복원 확인과 종료, Explorer에서 `Analyze.pyw` 실제 더블클릭, Run 폴더 선택·별도 A/A 연결 안 함, 분석 PASS와 브라우저 Report 열림까지 실제 입력으로 수행했다. UI_Workflow.json과 완료 화면, 분석 완료 화면을 남겼다. Production·Asset 저장은 하지 않았고 원래 Editor는 보존했다.

실제 UI Run `20261103T114935_URB4_Scalar_30CCDBF0`은 12 Capture·원본 안정·네 항목 복원 true였다. GUI에서 만든 `0.3.1_C8B6BCA5E40C` 묶음의 파일 20개를 독립 재생성 결과와 비교해 모두 바이트 일치를 확인했다. Additional_Native_Verification.json에 추가 표시 확인·UI Run의 24 Capture·7,200프레임과 원본 보호를 별도로 검증했다. 이 추가 자료를 19개 주 시험의 대표 성능 표에 합치지 않았다. 브라우저의 실제 Report 제목·열림을 관찰했고 본문은 독립 오프라인 Render로 검증했다. 사용자 Chrome 세션의 본문 입력 조작을 수행한 것으로 기록하지 않는다.

실제 게임 창의 **Esc** 입력은 별도 Run `20261103T115753_URB4_Scalar_26708295`에서 검증했다. CANCEL_REQUESTED 뒤 Capture Index 2의 부분 CSV 35프레임 쓰기를 마치고 CANCELLED·네 항목 복원 true·원본 안정 true를 확인했다. UI_Escape_Input.json, 독립 취소 검증과 실제 취소 화면을 남겼다. 그 전에 빠른 Run이 이미 끝난 뒤 Esc가 도착한 시도는 COMPLETED로 보존하고 취소 시험으로 세지 않았다. 정상 성능 통계에 부분·취소 자료를 섞지 않는다.

## 4. 통계·등급·리포트 검증

Capture마다 Raw SHA256·Fingerprint 체인·정확한 Metric·유효 프레임을 확인하고, Manifest·Completion·Execution의 적용값·전후 읽기·복원 상태를 비교한다. Mean·Median·nearest-rank P95와 대표값·Delta는 별도 계산으로 검산한다. 동일 입력·정책·구현의 재분석이 같은 AnalysisID·경로·바이트를 재사용하고 원본 해시가 유지되는지도 확인한다.

수정 후 정상 Run 11개가 126 Capture·37,800개의 유효 프레임을 수집했다. Capture마다 FrameTime·GameThreadTime·RenderThreadTime·GPUTime과 300프레임을 검증했다. 모든 Metric의 통계·P95·대표값·Delta가 독립 계산과 일치했고 입력 원본 해시는 변하지 않았다. 같은 입력·정책·구현의 분석 재실행은 동일 AnalysisID·경로·바이트를 재사용했다.

19개 자료의 분석 상태는 PASS 11개, 예상 FAIL 5개, UNSUPPORTED 1개, CANCELLED 2개다. 오류·취소·미지원 자료는 정상 GPU 등급을 받지 않는다. MissingGPU_Diagnostic_Verification.json은 실제 Scalar 자료의 **복사본만** 수정해 GPUTime 열 누락과 Native Raw 해시 불일치를 함께 검증했다. 원본 Manifest·Completion의 해시를 위조하지 않았고 원본도 불변이었다. GPU Confidence·Impact·양쪽 Budget은 모두 UNAVAILABLE이며 사용할 수 있는 CPU Sample도 무결성 신뢰가 없는 진단 자료로 남겼다.

| 실제 자료 | GPU A ms | GPU B ms | Delta ms | Noise Floor ms | Impact / Confidence / Budget |
|---|---:|---:|---:|---:|---|
| HairPDO | 3.34795 | 3.46875 | +0.12080 | 0.05000 | GREEN / RELIABLE / A·B GREEN |
| General | 2.50430 | 2.50570 | +0.00140 | 0.05000 | INCONCLUSIVE / INCONCLUSIVE / A·B GREEN |
| Scalar | 2.52435 | 2.50510 | −0.01925 | 0.05000 | INCONCLUSIVE / INCONCLUSIVE / A·B GREEN |
| BloomQuality | 2.44630 | 2.51735 | +0.07105 | 0.05000 | GREEN / RELIABLE / A·B GREEN |

Hair의 동일 조건 A/A Range는 0.03935ms, Relative Spread는 약 1.167%였고 A/B Range는 각각 0.00720/0.01975ms였다. Delta +0.12080ms는 0.05ms Floor보다 크고 60FPS 예산의 0.7248%여서 초기 정책의 RELIABLE·GREEN으로 표시했다. Baseline 대비 증가는 약 3.6082%로 예산 대비 비율과 다르다. GREEN이어도 추가 GPU 비용은 관측됐다. 이 값은 해당 Hair 단독 장면의 전체 GPU 차이이며 모든 Character나 PDO Pass의 고정 비용이 아니다.

10개 정상 A/B의 양쪽 절대 GPU Budget은 모두 GREEN이다. Hair와 Bloom을 제외한 작은 차이는 INCONCLUSIVE로 보류했다. A/A 단독은 안정성 진단이며 A/B Impact·Budget을 제공하지 않는다. 특히 Scalar의 작은 음수는 IMPROVED로 오인하지 않았다.

등급은 기존 정책을 유지한다. Impact는 신뢰할 수 있는 GPU B−A를 Target FPS 예산과 비교하며 2%·5% 경계를 사용한다. Budget은 전체 GPU 대표값을 70%·100% 경계로 비교한다. Confidence는 같은 조건 A/A와 반복 변동·Noise Floor를 함께 확인한다. Noise 안의 작은 음수를 IMPROVED로 표시하지 않으며, GPU 누락을 0ms·CPU 대체값으로 처리하지 않는다. Outlier와 Capture 첫 프레임은 임의로 삭제하지 않는다.

최종 실제 Hair HTML은 원본 Run `20261103T113641_URB4_HairPDO_6D992167`을 Analyzer 0.3.1로 분석한 `0.3.1_F579D50BBBA6`이다. [바로 보는 실제 Hair Report](../phase4/examples/ActualHairReport/Report.html)는 같은 독립 Sources 묶음이다. 이전 0.3.0 리포트와 검증 Receipt는 `BeforeReportReasonFix`에 보존했다. Report_Version_Migration_Verification.json에서 19개 모두 통계·Calibration·정책·상태·경고·오류가 이전 분석과 정확히 같고 Report 설명·버전·구현 ID만 달라졌음을 확인했다.

현재 0.3.1 Hair Report의 Desktop 1440px와 실제 좁은 Viewport 500px 화면을 독립 Chrome Render로 만들고 사람이 확인했다. 로컬 링크 18개가 모두 존재하며 외부 자원·Script는 없고 명시한 최소 글자 크기는 12px다. VisualQA.json, Desktop, 500px을 남겼다. 이 화면 검사는 Unreal 성능 수치나 시각 품질 자체의 검증을 대신하지 않는다.

## 5. 오류·제약과 미검증 범위

사전 분석기 회귀 검사는 82개 중 80개 통과, 이 Windows 계정의 심볼릭 링크 생성 권한이 필요한 두 개는 건너뛰었다. Analyzer 0.3.1에서 기존 82개와 판정 설명 검사 3개를 실행해 총 85개 중 83개 통과·같은 권한 검사 2개 Skip을 확인했다. RELIABLE의 빈 사유는 통과 조건으로 표시하고, INCONCLUSIVE 또는 실패 자료는 통과 설명을 표시하지 않는지 검사했다. Skip을 통과로 세지 않는다. Runtime 정상·오류·취소 시험 결과와 소프트웨어 회귀 검사를 구별한다. 회귀 Log와 변경 범위·구현 해시를 기록했다.

실제 RELIABLE Hair Report에서 `reasons=[]`가 차단 사유 없음이라는 뜻인데도 “판정 이유가 제공되지 않았습니다”라고 표시되는 사용성 문제를 발견했다. 0.3.1은 유효한 RELIABLE일 때 “기록한 조건이 일치하는 A/A 연결, 필요한 반복 수와 반복 안정성 검사를 통과했고, 실제 A/B 차이의 절댓값이 Noise Floor보다 큽니다”로 설명한다. 판정·숫자를 변경하지 않고 `report.py`와 `__init__.py` 버전만 바꿨다. Implementation SHA256은 `FD77F2DA1C478A65DBBC075FEDE56E870BFCC4643868F6912E73CE26BF03B1E5`이며 이전 분석기 Source·배포본은 보존한다.

설정한 A/B의 적용값을 읽어 확인해도 모든 장면·시간·온도·GPU Clock·백그라운드 부하가 같다는 증명은 아니다. Scene State Declared Static은 장면을 통제한 사용자의 선언이며 기록한 Camera·Actor Transform·Scalability·환경·원본 상태에 대한 검사만 수행한다. 모든 WPO·시간 의존 Shader·Component 상태·동적 Light를 추적하지 않는다.

첫 ConsoleVariable 시험 `20261103T112323_URB4_ConsoleVariable_8B9242C3`은 다섯 번째 Capture 전에 불변환경 검사에서 거부되어 FAILED로 종료됐다. 원본 내용 해시는 안정적이었고 Action·Camera·CVar·해상도 복원은 모두 true였다. 현재 Log는 Camera·Actor Transform·Scalability 등에서 정확히 어떤 개별 필드가 달라졌는지 남기지 않으므로 원인은 확정하지 않았다. 게임 조작으로 Pawn이 움직일 수 있다는 사용상 주의와 이 실패의 실제 원인을 같은 사실로 단정하지 않는다. 초기 실행 증거와 Log를 보존하며 실패한 Run에는 정상 성능 등급을 주지 않는다. 수정한 환경의 최종 독립 재실행 `20261103T114100_URB4_ConsoleVariable_84D11908`은 첫 실행에서 12 Capture·전후 검사·복원을 모두 통과했다. 이 성공을 초기 거부 원인의 증명으로 해석하지 않는다.

실제 Hair 화면을 확인하는 과정에서 별도 CameraActor에 기본 DefaultPawn의 구체가 보이며 Hair를 가리는 시험 환경 오류를 발견했다. Camera View Target과 Bounds의 투영만으로 실제 Hair 표시를 증명할 수 없었다. 초기 실행은 최종 Hair 기능 측정으로 채택하지 않고 이전 19개 사례·재시험·리포트·증거 402개 파일을 BeforePawnFixtureFix에 해시 Manifest와 함께 보존했다. Benchmark 전용 NoPawn GameMode를 새로 만들어 두 시험 Level에만 적용하고 Hair FOV를 48로 수정했다. Runtime C++ 로직과 Production은 변경하지 않는다. 수정 후 실제 화면과 저장·Runtime GameMode를 검증하고 전체 19개 사례를 새 조건에서 다시 수집해 독립 검사 PASS를 확인했다. 초기 수치·실패·재시험을 새 통계에 섞지 않았다.

측정 중에는 마우스·키보드·게임패드로 게임을 조작하지 않고 중단할 때만 Esc로 취소한다. 불변조건 거부는 정상 비교 자료에 포함하지 않는다. 현재의 개별 필드 진단 부족은 Known Limitation으로 남긴다.

원본 내용 해시는 프로젝트 Content·Config·uproject와 Benchmark Content를 넓게 포함한다. Calibration과 본 시험 사이에 관계없는 Asset을 저장해도 환경 일치를 보류할 수 있다. 모든 Asset 준비를 끝낸 뒤 같은 Run의 A/A+A/B를 권장하며, 별도 A/A는 실제 결과 폴더를 Analyzer에서 연결한다.

Hair 예제는 현재 RTR 프로젝트의 Texture·Material Function에 의존한다. Plugin 폴더만 새 빈 프로젝트로 옮기는 이식 검증은 하지 않는다. 다른 PC·엔진 Build·RHI·Shipping·패키징·모바일·전체 Character Scene은 이번 시험으로 보증하지 않는다. 한 Preset의 Multi-Action·Multi-Camera·Multi-Level Batch, 자동 GPU Pass 분석·시각 품질 판정은 V1 범위에 없다.

정상·지원 오류·Esc 취소 후 복원을 확인한다. 강제 종료·전원 종료에는 복원을 보장하지 않는다. 실패·취소·무효 자료의 Report는 오류 진단용이며 정상 성능 비교로 사용하지 않는다. INCONCLUSIVE는 고장이나 차이 0의 증명이 아니라 비교 판정 보류다.

이 시험에서 발견한 Pawn 가림은 전용 Fixture 수정과 전체 재시험으로 해결했다. 초기 CVar 거부의 정확한 원인과 개별 불변조건 차이 진단 부족은 위와 같이 공개한다. 독립 검토의 열린 코드 차단 항목은 없다. I의 실제 입력과 최종 Report 화면도 별도 검증을 완료했다. 남아 있는 지원 범위·진단 한계를 감추거나 사용자 검증까지 완료한 것으로 표시하지 않는다.

## 6. 변경 Asset·파일과 저장 위치

| 영역 | 변경 |
|---|---|
| 현재 설치 플러그인 | RTR_Advanced/Plugins/URBenchmark의 Native Source·Descriptor·새 DLL·Module 매핑 |
| Native Source | Header 두 개의 Editor Metadata만 변경. Runtime Action·Capture·Metadata 구현 유지 |
| 새 Asset | /URBenchmark/Phase4/Materials 5, Meshes 1, Maps 2, Presets 14, GameMode Blueprint 1 — 23 Package |
| 도구 보관 | phase4/Plugin, 시험 Script·Raw·Report·화면·검증 JSON·빌드 Log |
| 문서 | Master 1.4, V1 첫 실행·전체 안내, Phase 4 보고, 현재 README |
| Analyzer | phase4/analyzer 0.3.1의 report.py 설명·__init__.py 버전만 변경. 나머지는 Phase 3와 동일. 루트 Analyze.pyw 연결 |

정확한 새 Package 목록과 A/B 값은 AssetCreation.json, 실행 사례 계약은 validation_cases.json을 따른다. 실제 설치·배포 파일과 보호 해시는 최종 검증·Delivery Manifest에 기록한다. 이전 단계 기록과 Production 원본은 보존한다.

도구 전체 `01_Advanced/Tools/UniversalRenderingBenchmark/`는 `.gitignore`로 제외한다. 관련 없는 사용자 Git 변경을 보존하며 Commit·Push·GitHub 업로드·포트폴리오 자동 복사는 수행하지 않는다.

## 7. 완료 판정과 사용자 검증 시작점

V1 구현과 A~I의 개발자 검증을 완료했다. 사용자는 [첫 실행 안내](V1_Quick_Start_KO.md)에 따라 Scalar 예제부터 직접 실행할 수 있다. Play 메뉴에서 Standalone 모드를 고른 뒤 초록색 Play를 눌러 시작한다. 다른 Action은 공통 Level의 Preset만 변경하며 Hair는 별도 Level에서 실행한다. 새 테스트는 예제 Preset을 복제해 만들고 [전체 사용 안내](V1_User_Guide_KO.md)의 Tag·Action·Calibration·결과 해석을 따른다.

전체 검증 항목·결과와 구현 해시는 [Final_Verification.json](../phase4/evidence/Final_Verification.json)을 기준으로 한다. 실제 배포 복사본의 최종 해시 확인은 별도 복사 검증 기록을 따른다. 이 보고서는 그 복사가 이미 검증됐다고 추정하지 않는다.

**V1 개발자 검증 완료·사용자 직접 검증 전**이다. 이번 Hair는 격리된 단독 Mesh의 PDO 시험이며, 실제 PBR Character Scene 전체의 Hair·Skin·Eye 측정은 아직 수행하지 않았다. 전체 Character 측정과 Report는 별도 작업으로 진행하며 이 단계에서 추가 Phase를 시작하지 않는다.
