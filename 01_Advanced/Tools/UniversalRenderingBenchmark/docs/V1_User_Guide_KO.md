# RTR Universal Rendering Benchmark Tool V1 사용 안내

Unreal에서 Test Preset을 선택해 A/B를 반복 측정하고, 완료한 Run 폴더를 분석하여 Summary.csv와 오프라인 Report.html을 만든다. MaterialSwap·ScalarParameter·ActorVisibility·ConsoleVariable을 같은 Runner로 실행한다. 새 테스트마다 Runner 코드나 Blueprint Graph를 수정할 필요가 없다.

V1 구현과 개발자 검증을 완료했다. 사용자는 아래 순서로 직접 실행할 수 있다. A~I 실측·실제 입력·복원·원본 보호·리포트 화면과 오류·제약은 [Phase 4 보고서](Phase4_Implementation_KO.md)를 따른다. 사용자의 직접 검증은 아직 수행하지 않았다.

## 1. 현재 PC에서 시작하기

| 항목 | 위치 |
|---|---|
| Unreal 프로젝트 | `local path withheld` |
| 설치된 Runtime 플러그인 | 위 프로젝트의 `Plugins\URBenchmark\` |
| 도구·문서·예제·증거 | `local path withheld` |
| 분석 시작 | 도구 폴더의 `Analyze.pyw` 더블클릭. `Analyze.cmd`는 대체 실행·명령행용 |
| 측정 결과 | 프로젝트의 `Saved\URBenchmark\<RunID>\` |

검증 대상은 Unreal Engine 5.8.3의 Windows DX12·SM6 Standalone이다. 현재 PC의 Python 3.10.6과 tkinter로 분석 창을 실행하며 별도 Python 패키지는 필요하지 않다. 다른 엔진 Build·운영체제·RHI에 이 결과를 그대로 적용하지 않는다. Native 플러그인 Binary는 엔진 Build와 맞아야 한다.

갱신 전에 켜져 있던 Editor는 이전 플러그인을 계속 사용한다. 미저장 작업을 사용자가 정리한 뒤 Editor를 다시 열거나, 별도 Editor를 열어 Benchmark 전용 Level을 사용한다. Level을 다시 여는 것만으로 Native 코드가 바뀌지 않는다. 원래 Editor를 강제로 닫거나 Production 작업까지 Save All 하지 않는다.

Native 최종 배포본은 도구 폴더의 `phase4\Plugin\`이며 버전은 `1.0.0-V1`이다. 외부 Analyzer는 `phase4\analyzer\`의 `0.3.1`이다. RELIABLE 결과에 판정 차단 사유가 없을 때 통과한 A/A·반복·안정성·Noise Floor 조건을 한국어로 설명하도록 보완했다. Parser·통계·Confidence·등급 정책·저장·CLI는 이전 검증한 구현과 같다. 두 버전은 각각 Native와 외부 분석기를 가리킨다.

다른 PC에 설치할 때는 원본 프로젝트를 복사한 시험용 프로젝트에 `phase4\Plugin` 내용을 `Plugins\URBenchmark`로 옮긴다. 같은 이름의 중첩 폴더가 생기지 않게 한다. 엔진 Build가 다르면 포함된 소스를 그 엔진에서 다시 빌드해야 한다. 기존 `.uproject`나 Rendering Settings를 임의로 바꾸지 않는다. 외부 Analyzer는 별도 도구 폴더에 두고 Python 3.10 이상과 tkinter가 설치돼 있는지 확인한다. 이 다른 PC 설치 절차는 현재 PC의 실측 검증과 구별한다.

Hair 예제의 Parent·MIC·Mesh는 시험용 복사본이지만 Texture와 Material Function은 현재 RTR 프로젝트의 `/Game/ASF/` 원본을 읽기 전용으로 참조한다. Plugin 폴더만 빈 프로젝트로 옮기면 이 의존 Asset은 포함되지 않는다. Hair 예제를 다른 프로젝트로 옮길 때는 사용 권한이 있는 의존 Asset을 함께 준비해야 한다. 공통 Runner와 Generic 시험 환경의 재사용과 이 Hair 예제의 프로젝트 의존성을 구별한다.

## 2. 예제 한 번 실행하기

1. 새 Editor에서 Content Browser의 **Show Plugin Content**를 켠다. `/URBenchmark/Phase4/Maps/L_URB_GenericActions`를 연다. 기본 Preset은 `DA_URB4_Scalar`다. Hair 시험은 아래의 별도 Level을 사용한다.
2. World Outliner에서 `BP_URB_Runner`를 선택한다. Details의 **URB Configuration → Preset**에 실행할 Preset을 넣고 **Auto Run On Begin Play**를 켠다.
3. 변경한 Benchmark Preset과 전용 Level만 저장한다. **Validate Preset**을 눌러 대상·Slot·값의 검증 결과를 확인한다. **Last Message**와 Output Log에서 원인을 읽을 수 있다.
4. 상단 Play 옆 메뉴에서 **Standalone Game** 모드를 선택한 뒤 **초록색 Play 버튼**을 누른다. 메뉴에서 모드만 선택한 경우에는 게임이 아직 시작되지 않는다. 같은 GPU를 사용하는 다른 게임·측정은 끝내고 시작한다.
5. `URB COMPLETED`가 나올 때까지 기다린다. Capture 중에는 측정용 HUD와 화면 메시지가 잠시 숨겨진다. 중단하려면 Standalone 창에서 **Esc**를 한 번 누르고 취소·복원 완료를 기다린다.
6. `Saved\URBenchmark`에서 이번 Run 폴더를 연다. `Completion.json`의 `status`가 `COMPLETED`이고 `restoration`의 `action`, `camera`, `cvarsAndPriorities`, `resolution`이 모두 true인지 확인한다.
7. 측정이 끝난 게임을 닫고 도구의 `Analyze.pyw`를 더블클릭한다. 별도 Console 창 없이 폴더 선택 창이 열린다. `Raw`, `Manifest.json`, `Completion.json`이 있는 **Run 폴더 하나**를 고른다. CSV 한 파일이나 Raw 폴더를 선택하지 않는다.
8. 같은 Run에 A/A를 함께 수집했다면 Calibration 질문에 **아니요**를 선택한다. 별도로 수집한 A/A를 연결하려면 **예**를 누르고 해당 A/A Run 폴더를 고른다.
9. 자동으로 열린 `Report.html`에서 Measurement Status, Performance Impact, Frame Budget, Confidence를 각각 확인한다. 완료 창에는 저장 위치가 표시된다.

복원 후 원래 Camera와 창 크기로 돌아가므로 완료 화면이 측정 화면과 달라질 수 있다. 파일이 생겼다는 사실만으로 성공으로 판단하지 않는다. `FAILED`, `CANCELLED`, `UNSUPPORTED`는 정상 성능 비교 자료로 사용하지 않는다.

개발자 검증에서는 위 순서를 실제 새 Editor·Standalone·Explorer 더블클릭·폴더 선택으로 완주했다. 실제 HTML 예제는 [Hair Report](../phase4/examples/ActualHairReport/Report.html)에 있다. 실제 Escape 입력의 취소·CSV 쓰기 완료·복원도 확인했으며, 성능 대표값에는 취소된 자료를 포함하지 않는다.

### Phase 4 예제 선택

Preset 경로는 `/URBenchmark/Phase4/Presets/`다. 일반 예제는 `/URBenchmark/Phase4/Maps/L_URB_GenericActions`, Hair는 `/URBenchmark/Phase4/Maps/L_URB_HairIsolation`에서 실행한다. 정상 A/B 예제는 같은 Run에 A/A를 먼저 수집하도록 준비되어 있으므로 분석 때 별도 Calibration 질문에 **아니요**를 선택한다.

| Preset | 내용 |
|---|---|
| DA_URB4_AA | 실제 A 상태만 반복하는 독립 A/A |
| DA_URB4_General | Character와 무관한 Static Mesh Material A/B |
| DA_URB4_Scalar | URB_Blend 0/1, 종료 시 원래 0.35 복원 |
| DA_URB4_VisibilityActor / VisibilityComponent | Actor 또는 Component 표시 상태와 복원 |
| DA_URB4_VisibilityNoShadows / VisibilityNoHiddenShadows | 각 Shadow 정책과 복원 |
| DA_URB4_ConsoleVariable / ConsoleBloom | 허용 Sharpen 또는 BloomQuality A/B |
| DA_URB4_Reuse | 새 Preset으로 같은 Runner 재사용 |
| DA_URB4_HairPDO | 격리한 Hair 복사본에서 Use_HairPDO A=OFF / B=ON |
| DA_URB4_MissingTarget / InvalidSlot / UnsupportedCVar | 오류 진단용. 정상 성능 측정에 사용하지 않음 |

Hair 예제는 Production Hair Parent·MIC·Static Mesh를 `/URBenchmark/Phase4/`로 복사하여 시험한다. A/B는 Static Switch `Use_HairPDO`만 다르며 `PDO_Strength=0.1`, Texture·Scalar·Vector 값은 유지한다. 고정된 Hair 단독 장면이며 실제 Character Scene 전체나 Hair/Skin/Eye 전체 비용 시험이 아니다. 다른 예제와 카메라·부하가 다르므로 순위를 비교하지 않는다.

두 Phase 4 Level은 기본 Pawn을 만들지 않는 `/URBenchmark/Phase4/Blueprints/BP_URB4_GameMode`를 사용한다. 새 시험 Level에서도 같은 구성이 필요하면 World Settings의 GameMode Override에 이 Blueprint를 지정한다. Hair Camera는 FOV 48로 전체 Mesh를 담는다. 측정 전 실제 Standalone 화면에서 시험 대상이 보이고 다른 물체에 가려지지 않는지 확인한다. 외부 CameraActor로 View Target을 바꾸면 기본 Pawn의 구체가 화면에 나타날 수 있으므로, Camera 경로·Mesh Bounds·View Target 기록만으로 대상이 실제 보인다고 판단하지 않는다.

## 3. 새 Preset 만들기

가장 간단한 방법은 사용할 Action의 예제 Preset을 `/URBenchmark/` 아래 새 폴더로 복제하는 것이다. 새 Data Asset을 만들 경우 `URBTestPreset` 클래스를 고른다. Production Material·Level 자체를 시험용으로 저장하지 않는다.

| 순서 | 설정 |
|---|---|
| 01 Test | 고유한 Test ID, 읽기 쉬운 Test Name, Scene Type, Run Mode, Action Type |
| 02 Target | 대상 Actor·Component Tag, Material Slot, Camera Tag |
| 03 Action | 선택한 Action의 A/B 상태·값·Material·정책 |
| 04 Capture | Warmup 120, Capture 300, Repeat 3, 1920×1080, Screen Percentage 100, Target FPS 60 |

Actor Tag는 Actor Details의 Actor Tags, Component Tag는 해당 Component의 Component Tags에 넣는다. 이름이 비슷해도 서로 다른 목록이다. 대상 Actor·Component·Camera는 각각 하나만 일치해야 하며 Camera Tag는 CameraActor에 지정한다. Material Slot은 0부터 시작한다. ConsoleVariable은 대상 Mesh Tag와 Material Slot을 사용하지 않는다.

**Scene State Declared Static**은 애니메이션·시간 의존 Material·조명·외부 설정 변화를 통제했을 때만 켠다. 체크 자체가 정지 장면의 증명은 아니다. Runner의 전후 Camera·Actor Transform·Scalability·환경 검사 외에 사용자가 장면의 시간 변화를 통제해야 한다. 확정 판정을 받기 위해 근거 없이 켜지 않는다.

Preset을 Runner에 연결하고 **Validate Preset**으로 오류를 고친 뒤 Benchmark Asset과 전용 Level만 저장한다. 새로운 Preset·Asset을 모두 준비한 뒤 Calibration과 본 측정을 실행한다. 내용 해시가 프로젝트 Content·Config·uproject와 Benchmark Content를 넓게 포함하므로, 중간에 관련 없는 Asset 하나를 저장해도 기존 A/A와 환경 일치를 보류할 수 있다.

새 시험 환경의 GameMode·Camera·조명·표시 상태는 코드 검증과 별개로 실제 Standalone에서 먼저 확인한다. 가려진 대상이나 잘못된 구도의 측정도 CSV 자체는 정상일 수 있다. 화면 문제가 발견돼 Asset을 고쳤다면 기존 수치를 최종 성능으로 사용하지 않고, 준비를 마친 같은 새 조건에서 A/A와 A/B를 다시 수집한다.

## 4. Action별 A/B 설정

| Action | 설정과 실행 | 복원 |
|---|---|---|
| MaterialSwap | 대상 Slot과 사전 준비한 Material/MIC A·B. Static Switch는 컴파일한 MIC 두 개로 준비 | 원래 Slot Material |
| ScalarParameter | 원래 Slot Material에 하나만 있는 Global Scalar 이름과 A·B 실수. 하나의 transient DMI를 전체 Capture에 재사용 | 원래 Scalar 값·Slot Material, DMI 안의 원래 값 |
| ActorVisibility | Scope=Actor는 Hidden In Game, Scope=Component는 Visible·Hidden In Game. Shadow Policy를 함께 지정 | 변경한 Actor·Component의 각 원래 Flag |
| ConsoleVariable | 허용 목록에서 CVar를 선택하고 A·B 값 지정. 적용 후 값·우선순위 읽기 확인 | 원래 값·설정 우선순위·태그 |

Scalar는 Vector·Static Switch·Layer Parameter·Custom Primitive Data 연결 Scalar를 지원하지 않는다. Material Instance에 같은 이름의 Global Scalar가 있는지 실제 대상 Slot에서 확인한다.

Visibility의 `Visible=true`와 `Hidden In Game=false`는 별도 조건이다. Actor가 숨겨져 있으면 Component의 Visible만 켜도 게임에 나타나지 않을 수 있다. Component Scope는 지정 Component 하나에 적용하며 자식으로 전파하지 않는다. Actor Scope의 Shadow 정책은 그 Actor가 소유한 Primitive Component에만 적용한다. Child Actor 대상은 지원하지 않는다. Hidden In Game만으로 모든 Shadow 비용이 사라진다고 해석하지 않는다.

| Shadow Policy | 동작 |
|---|---|
| PreserveOriginal | 각 Component의 원래 Cast Shadow·Cast Hidden Shadow 유지 |
| DisableShadows | 선택 범위의 Cast Shadow 비활성화 |
| DisableHiddenShadows | 선택 범위의 Cast Hidden Shadow 비활성화 |

허용 Runtime CVar는 `r.Tonemapper.Sharpen`의 유한한 0~10 실수와 `r.BloomQuality`의 0~5 정수다. 목록 밖 항목과 범위 밖 값은 UNSUPPORTED다. 런타임 Flags가 지원 조건과 다르면 목록에 있는 이름도 거부한다. CVar가 화면이나 비용에 미치는 실제 영향은 장면과 Post Process 설정에 달려 있다.

## 5. A/A와 측정 조건

**Standard Benchmark**는 기본 A → B → B → A → A → B 순서로 6회 수집한다. 각 Capture마다 120 Warmup 뒤 300프레임을 수집한다. Repeat Count=3은 Variant별 3회다. Target FPS=60은 16.667ms 예산 계산에 사용하며 측정 속도를 60FPS로 제한하지 않는다.

**Run Calibration=true**면 같은 실행 안에서 A/A 6회와 A/B 6회를 순서대로 수집한다. 별도 파일을 고르지 않고 같은 Run을 분석하면 된다. **Calibration Validation**은 A/B 라벨 순서를 유지하되 실제로는 모두 Action A를 적용한다. 라벨 B를 실제 B 적용으로 읽지 않는다.

별도 A/A를 쓰려면 같은 A 상태·Camera·장면·측정 조건의 Preset을 복제하고 Run Mode를 Calibration Validation으로 지정한다. **Calibration Reference Run ID**는 기록용 필드다. Analyzer에서 실제 A/A Run 폴더를 선택하여 연결해야 하며, ID 입력만으로 결과가 자동 연결되지는 않는다.

Runner는 Shader·Resource·PSO 준비와 교체 프레임을 Capture에서 제외한다. VSync·Frame Limit·Dynamic Resolution과 수집 CVar를 임시 적용한 뒤 복원한다. 측정 중 다른 Blueprint·Console·외부 도구로 상태를 바꾸지 않는다. 마우스·키보드·게임패드 입력으로 기본 Pawn이 이동할 수 있으므로 게임 조작을 하지 않고 기다린다. 중단할 때만 Esc로 안전 취소한다. 프레임 Outlier를 자동 삭제하지 않으므로 백그라운드 부하·온도·Clock 변화도 사용자가 관리한다.

## 6. 결과와 등급 읽기

분석 결과는 기본적으로 `<Run>\Analysis\<분석 버전>_<AnalysisID>\`에 저장된다. 같은 입력·정책·분석 구현은 기존 결과의 바이트를 확인하고 재사용한다. 기존 결과가 수정돼 있으면 덮어쓰지 않는다.

| 결과 | 의미 |
|---|---|
| Report.html | 오프라인 화면, 실제 RunID와 환경, GPU·CPU·변동·판정 이유 |
| Summary.csv | Metric별 대표·Pooled 통계, Delta, 유효 Run/Sample 수, 상태 |
| Analysis.json | 상세 통계·Run별 값·적용 정책·원본 해시 |
| AnalysisManifest.json | 분석 ID와 입력·출력 해시 |
| Sources | 분석한 Benchmark·선택 Calibration의 해시가 일치하는 복사본 |

HTML만 옮겨도 화면은 열리지만 원본 링크를 유지하려면 결과 폴더 전체를 복사한다. 인터넷·서버·외부 폰트·CDN은 필요하지 않다.

**Measurement Status**는 자료의 완전성이다. PASS·WARNING은 GREEN과 같은 의미가 아니다. **Performance Impact**는 신뢰할 수 있는 GPU 차이 B−A를 목표 프레임 예산과 비교한다. 양의 차이가 예산의 2% 이하 GREEN, 2% 초과~5% 이하 YELLOW, 5% 초과 RED다. 신뢰할 수 있는 음의 차이만 IMPROVED다. Baseline 대비 %와 Budget 대비 %는 서로 다른 수치다.

**Frame Budget**은 A·B의 전체 GPU 대표값 각각을 예산과 비교한다. 70% 이하 GREEN, 70% 초과~100% 이하 YELLOW, 100% 초과 RED다. 전체 GPU 시간이므로 특정 Material만의 절대 비용으로 소개하지 않는다. GPU Budget만으로 시스템 전체가 목표 FPS에 도달한다고 확정하지 않는다.

**Confidence=INCONCLUSIVE**면 실제 이유를 읽는다. A/A 부재·환경 불일치·반복 부족·큰 변동·Noise Floor 안의 차이 등으로 확정 비교를 보류했다는 뜻이다. 차이가 0이라는 판정은 아니다. GPU 누락·무효는 UNAVAILABLE이며 CPU나 GPU Pass로 채우지 않는다. CPU/Frame 보조 값은 GPU에 합산하지 않는다.

대표 A/B는 Capture별 Median의 Median이다. Pooled 통계와 반복별 P95의 Median을 구분한다. P95는 정렬한 N개에서 `ceil(0.95×N)`번째 값이다. 무효·짧은 Capture는 정상 집계에서 제외하고 사유를 남긴다. Outlier를 지우거나 결측을 0으로 바꾸지 않는다.

기본 Noise Floor 후보는 `max(RangeAA, RangeA, RangeB, 0.05ms)`, 그룹별 Median 변동 상한 후보는 5%다. 정책 파일에 있는 RTR V1 기준이며 엔진 공식 기준·장비 공식 오차·통계적 유의성 검정이 아니다. 정책을 바꾸면 버전과 결과를 구별한다.

## 7. 오류 해결

| 표시·상황 | 확인할 내용 |
|---|---|
| Preset is missing | Runner의 Preset 지정 여부 |
| TargetActorTag … matched 0 / 2 actors | Actor Tags의 철자·Tag가 지정된 Actor 수. 정확히 하나로 맞춤 |
| TargetComponentTag … matched … | Actor 아래 대상 Component의 Component Tags·지원 Component 종류·중복 |
| CameraTag … one CameraActor required | CameraActor의 Actor Tags와 일치 수 |
| Material Slot is out of range | 0부터 시작하는 대상 Mesh의 Slot Index |
| Variant Material could not be loaded | A/B Asset 경로·참조, B가 필요한 Standard 여부 |
| Scalar Parameter must exist exactly once … | 원래 Slot Material의 Global Scalar 이름·중복·Layer 여부 |
| UNSUPPORTED: … CVar … | Allowlist·범위·정수 여부·Runtime Flags |
| Action changed during Warmup/Capture | 다른 Blueprint·애니메이션·Console이 대상 상태를 바꾸는지 |
| Declared static scene, Camera or Scalability changed | Camera·Actor Transform·Scalability 등의 전후 불변조건이 달라진 경우. 장면 시간 변화·Pawn 이동 입력도 확인. 현재 오류는 바뀐 개별 필드까지 표시하지 않음 |
| CSV Profiler already busy | 다른 수집을 정상 종료한 뒤 새 Run 실행. 외부 Capture를 강제로 건드리지 않음 |
| Shader/resource preparation timed out | Shader Compile·Streaming·PSO 준비와 실패 Log 확인 |
| Requested resolution was not applied | Standalone 창·실제 해상도·다른 해상도 제어 설정 확인 |
| FAILED / 복원 readback failed | Completion의 실패 항목과 Execution 확인. Production을 저장하지 않은 채 원인 점검 |
| Analyze.pyw가 실행되지 않음 | Python 3.10 이상·tkinter·.pyw 파일 연결 확인. Analyze.cmd 대체 실행 가능 |
| Launcher 폴더 선택이 안 보임 | 뒤쪽 창·tkinter 확인. 아래 경로 지정 실행으로도 분석 가능 |
| GPU UNAVAILABLE | 원본 GPUTime 열·양의 유효 값·Capture 프레임·자료 상태 확인 |
| INCONCLUSIVE / 환경 불일치 | 실제 이유 확인. 모든 Asset 준비 후 같은 조건 A/A·A/B 다시 실행 |
| 기존 분석 결과 변경 감지 | 기존 결과를 보존하고 수정 원인 확인. 새 출력 위치로 분석 |

개발·재현용으로 `Analyze.cmd "<Run 폴더>" --open`, 별도 A/A 연결은 `Analyze.cmd "<AB Run>" --calibration "<AA Run>" --open`을 사용할 수 있다. 출력 보관 위치는 `--output-root "<폴더>"`, 정책은 `--policy "<policy.json>"`으로 지정한다. 경로는 큰따옴표로 감싼다.

## 8. 지원 범위와 보존 원칙

현재 지원은 한 Preset·한 Action·한 Camera·한 Level의 Windows UE 5.8.3 DX12·SM6 측정이다. Multi-Action·자동 Level Batch·모바일·GPU Pass 비용 분석·Unreal Insights 자동 해석·시각 품질 자동 비교·온라인 Dashboard는 V1 범위에 없다. HTML은 GPU 성능·자료 진단 Report이며 시각 품질 평가가 아니다.

Fingerprint는 기록한 Camera·환경·Actor Transform·원본 파일 상태를 비교한다. 모든 Component 애니메이션·WPO·시간 의존 Shader·실행 중 Light·열·Clock·백그라운드 상태를 증명하지 않는다. Declared Static은 이 한계를 이해한 사용자의 선언이다. 불변조건이 달라지면 측정을 거부하지만 현재 Log는 어떤 개별 필드가 달라졌는지까지 기록하지 않으므로 일반 오류 문구만으로 원인을 확정하지 않는다. Phase 1~2의 이전 자료에는 새 Fingerprint와 Native Raw 해시가 없으므로 추정해서 채우지 않고 확정 비교를 보류한다.

정상·지원되는 오류·취소 경로에서 복원을 확인한다. 강제 종료·전원 종료에는 복원을 보장하지 않는다. 실제 Hair 복사본의 기능 시험과 합성 General 장면은 목적이 다르며, Hair 시험을 실제 PBR Character Scene 전체의 Hair·Skin·Eye 비용으로 일반화하지 않는다. V1 이후 실제 Character Scene 측정은 같은 절차로 별도로 수행한다.

Production Material·Instance·Function·Level·Rendering Settings를 수정하지 않는다. 새 Asset은 `/URBenchmark/`에 만들고 보호한 원본 해시와 추가 Asset 목록을 검증 보고서에 남긴다. 도구 전체 경로는 사용자 요청으로 `.gitignore`에 등록돼 있다. GitHub 업로드·Commit·Push·포트폴리오 자동 복사는 하지 않는다. 필요한 문서·결과만 사용자가 별도 경로로 복사한다.
