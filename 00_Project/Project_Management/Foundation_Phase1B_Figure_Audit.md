# Foundation Phase 1B — Figure Audit

범위: `C:\Users\kmcoo\Desktop\PW\ASF_Review\00_Foundation`의 Chapter 01–09에서 Markdown이 실제 참조하는 Figure. 사용자가 정정한 루트와 실제 문서 구조를 적용한다. 기준: ASF-000–003 및 ASF_Standard. 원본 Markdown·이미지·Standard·Roadmap·DecisionLog는 수정하지 않는다.

검토 순서: Chapter 01→09, Chapter 내부 Figure 번호 오름차순. 초기 목록은 고유 Figure 154개, 삽입 참조 161건이다. 같은 파일의 재사용은 Figure별 단일 기록에서 모든 삽입 맥락을 함께 평가한다. 미참조 파일은 사용 Figure로 임의 편입하지 않는다. 요청의 Chapter별 주제 예시는 실제 제목과 다를 수 있으므로 현재 Section을 기준으로 비교한다.

검토 방법: 실제 이미지와 삽입 Section의 설명을 함께 읽고 Concept·Data Flow·Label·가독성을 평가한다. 텍스트 감사의 의심 항목은 확정 판정으로 승계하지 않는다. 표시만으로 판단할 수 없는 Engine/Compiler 동작은 Needs Technical Verification로 남긴다. 전체 Summary는 모든 Figure 검토 완료 후에만 추가한다.

## Final Summary

Chapter 01–09에서 실제 사용되는 고유 Figure 154개와 삽입 참조 161건을 모두 검토했다. 재사용된 Figure는 각 삽입 맥락을 하나의 기록에 통합했다. 저장된 Next Figure부터 순차적으로 이어서 완료했다.

Complete는 감사 완료를 뜻하며, Figure 수정 완료 또는 모든 기술 주장 검증 완료를 뜻하지 않는다. 엔진 동작·컴파일·성능을 이미지와 본문만으로 확정할 수 없는 항목은 Needs Technical Verification로 남겼다.

### 전체 Figure 상태

| Chapter | Figure | Match | Minor Mismatch | Major Mismatch |
|---|---:|---:|---:|---:|
| Chapter 01 | 13 | 1 | 9 | 3 |
| Chapter 02 | 16 | 4 | 4 | 8 |
| Chapter 03 | 6 | 1 | 0 | 5 |
| Chapter 04 | 8 | 0 | 4 | 4 |
| Chapter 05 | 14 | 1 | 4 | 9 |
| Chapter 06 | 10 | 0 | 4 | 6 |
| Chapter 07 | 9 | 0 | 6 | 3 |
| Chapter 08 | 69 | 15 | 27 | 27 |
| Chapter 09 | 9 | 0 | 4 | 5 |
| Total | 154 | 22 | 62 | 70 |

Recommended Action 집계:

- Keep : 22
- Minor Revision : 62
- Major Revision : 64
- Replace : 6
- Remove : 0

### Major Mismatch 목록

- Fig1_05: Index→Triangle 대응 오류, Winding 방향 오류, 입력 Vertex Buffer와 처리된 Vertex 결과의 경계 혼동.
- Fig1_06: Backface 판정의 잘못된 Mental Model과 서로 다른 Culling 실행 위치의 과도한 통합.
- Fig1_10: Shadow Map/Visibility 경계 붕괴, Depth 비교 convention 및 Write 조건 생략.
- Fig2_01: View forward 부호 모순, Local 값과 축/점 대응 불명확, 괄호 누락.
- Fig2_03: Transform 조건과 World 좌표값의 수학적 불일치.
- Fig2_04: World 축/위치 불일치와 Local 카드에 World 값의 무표기 재사용.
- Fig2_07: Clip/NDC 범위 혼동, Z convention의 보편화, Screen Origin/축 방향 혼동.
- Fig2_09: 같은 방향과 같은 X offset 혼동, 시선축/좌표값 불일치, NDC 경계 점의 위치 오류.
- Fig2_12: View Origin의 잘못된 시각적 위치, View Frustum/Clip 표현의 혼합, 수치 예시의 기준 부재.
- Fig2_14: Normal Map 저장값과 Decode값의 경계 혼동, 변환 전후 기준축과 곱셈 표기의 불일치.
- Fig2_15: Camera Vector 방향 반전, 데이터 의미를 무시한 비교, Node 출력 의미의 과도한 단순화.
- Fig3_02: 135° 화살표와 음수 값 불일치; 각도 기준선 불일치; 방향 계수와 최종 밝기 혼동; 다음 Section 예고 오류.
- Fig3_03: Flat/Smooth 비교의 Geometry 통제 실패; Vertex Normal 평균 계산의 일반화; 삼각형 Vertex/Edge 라벨 누락 및 중복.
- Fig3_04: Normalize 결과의 수치 오류; Figure 번호 불일치; 잘못된 Normal 패널의 직각 기호.
- Fig3_05: Directional Light 입사 방향과 L의 부호 관계 불일치; Spot Direction 화살표 Convention 불명확; Figure 식별자 누락.
- Fig3_06: View Direction과 Camera 위치 불일치; Position/Normal Transform 구분 누락; Mixed Space 비교의 시각적 증거 부족; Engine 보편성 주장 검증 필요.
- Fig4_02: Normal 방향 변화 미표현; Roughness/Normal 효과 혼합; Emission 1=Glow 조건 생략.
- Fig4_05: Encode/Decode 역전; Roughness 변화 방향 역전; 중복 변환처럼 보이는 Graph.
- Fig4_06: Object/World Space 혼동; 엔진 Convention 검증 필요; Basis 예시 식별성.
- Fig4_08: L/V 화살표 반전; 입력 합류의 직렬화; Sample 값과 Texture 격자 혼동.
- Fig5_04: Brightness 명도 역전.
- Fig5_06: Half Vector 각도 이등분 실패.
- Fig5_07: H 방향 오류; 비용 일반화; 동일 지점 비교 불명확.
- Fig5_08: PBR/모델 동일시; 검증되지 않은 연대; 정확성과 Energy Conservation 무조건 단정.
- Fig5_09: 단일 Facet 반사와 Facet 분포의 반사 확산 혼동.
- Fig5_10: BRDF 응답과 최종 방향 혼동; L 부호 불일치.
- Fig5_12: 정규분포 오역; 임의 h에서 D 감소 일반화; Normal/반사 방향 분포 혼동.
- Fig5_13: 실제 차단 교차점 누락; D 의미 오류.
- Fig5_14: 입사각과 관찰각 혼동; 광선 경로와 반사 법칙 불일치; 문자 손상.
- Fig6_01: 기술/입력/표현 형식의 Stage 혼합.
- Fig6_02: BRDF 적용 위치 오해; Material/BRDF 동일시; 고정 Stage 직렬화.
- Fig6_05: Diffuse IBL과 다중 Bounce 혼동; 고정 Stage 직렬화.
- Fig6_06: BRDF 적용 위치 및 IBL 관계 왜곡; 광선 방향 혼합.
- Fig6_08: 휘도 단위 오류; HDR 데이터와 표시 손실 혼동; 비교 Scene 변화.
- Fig6_10: 입력/기법/값 범위의 혼합; Chapter 범례 불일치.
- Fig7_04: Soft/Hard와 PBR/NPR 동일시; Diffuse와 Cast Shadow 혼동.
- Fig7_05: 각도/dot 축 혼용; 정면 각도 오류; 반사율과 밝기 혼동.
- Fig7_09: Threshold 후 Gradient 복원 오해; Ramp Sample 단계 누락.
- Fig8_03: 동일 파일의 서로 다른 목적 재사용; ⑥ 대상 오류; 필수 설정 증거 누락.
- Fig8_04: Architecture 삽입 목적과 이미지 완전 불일치.
- Fig8_05: 두 문맥 중 Architecture와 완전 불일치; Meshes/Fbx 목록 차이.
- Fig8_08: 잘못된 다음 Chapter 안내가 학습 순서를 왜곡한다. 8.0.5의 포함 여부도 표시되어 있지 않다.
- Fig8_14: 정규화된 입력의 분기가 불일치한다. RGB 색상은 최종 Highlight가 아니다.
- Fig8_15: 본문의 핵심 계산이 화면 출력에 반영되지 않는 연결 상태이다.
- Fig8_19: Response 계산과 엔진 BRDF 조절을 같은 단계로 설명한다.
- Fig8_20: 캡션의 핵심 Data Flow가 부재하며 좌표 시점 표기가 부정확하다.
- Fig8_23: Dot 원값과 Clamp한 조명값의 범위를 혼동하고 오래된 절 번호를 사용한다.
- Fig8_24: 본문에서 핵심으로 구분한 Lighting Data와 Lighting Result의 이중 출력 계약을 검증할 수 없다.
- Fig8_25: Scalar 조명 데이터 검증을 Base Color 합성 검증으로 설명한다.
- Fig8_27: 핵심 입력 의존성이 잘못 표현되어 있으며 Output 예시가 순수 Factor를 분리하지 않는다.
- Fig8_31: Camera-visible P의 배치 및 샘플 좌표 연결이 부정확하다. 모든 Pixel의 Ray 비용이 매우 크다는 단정은 Needs Technical Verification.
- Fig8_32: 거리·투영 조건 일반화, Filtering 설명 누락, Peter Panning 시각화 부정확.
- Fig8_33: 핵심 비교 결과가 수치와 시각적으로 대응하지 않는다.
- Fig8_35: Needs Technical Verification: 실제 활성 Debug Mode와 색상 의미.
- Fig8_36: 이동 실습의 핵심 증거와 맞지 않는 캡처이다.
- Fig8_39: Needs Technical Verification: 차이를 발생시킨 실제 Mesh, Normal, Shadow 해상도/Bias/Filtering 설정.
- Fig8_41: 핵심 Surface 표본과 Camera의 기하 관계가 맞지 않는다.
- Fig8_45: 수식과 곡선 불일치 및 반사 기하 오류. Schlick의 적용 범위/역사 설명은 Needs Technical Verification.
- Fig8_52: World 축 불일치, 가려진 P, Camera 이동과 회전의 혼동.
- Fig8_53: Normal 방향과 Depth 혼동 및 구현 UV 규약과의 연결 부족.
- Fig8_67: 함수 입력 계약 불일치. 비교 결과에 불필요한 색상·형상 차이.
- Fig8_69: 합성 구조 왜곡, Final Color 입력 누락, 그림 번호 오류.
- Fig8_70: Emission 타입/의미 오류 및 데이터 배선 오류.
- Fig8_71: 스크린샷이 본문 최종 타입 계약 이전 상태. 현재 엔진의 암시적 타입 변환 결과는 Needs Technical Verification.
- Fig8_74: Lerp 누락, 함수 입출력 방향 혼동, 브랜드 오류, 계산 범위 과장.
- Fig9_01: 병목 라벨 오류, 그림 번호 충돌, 예시 수치와 실측 구분 누락.
- Fig9_02: Frame 번호/작업 의존 시각화 오류. 실제 엔진 Queue/Thread 타이밍은 Needs Technical Verification.
- Fig9_04: 투명 합성 순서 및 LOD-Pixel 인과 오류, 브랜드 오류. 엔진별 depth/overdraw 집계는 Needs Technical Verification.
- Fig9_07: Frustum Culling 문장 반전이 핵심 오류. LOD의 시각적 표현과 설정 조건 보완.
- Fig9_08: 실행 안내 명령 검증 필요, 예시 화면 출처/버전 누락, 병목 예시의 해석 조건 누락.

### Minor Revision 목록

- Chapter 01: Fig1_01, Fig1_02, Fig1_03, Fig1_04, Fig1_08, Fig1_09, Fig1_11, Fig1_12, Fig1_13.
- Chapter 02: Fig2_06, Fig2_08, Fig2_13, Fig2_16.
- Chapter 04: Fig4_01, Fig4_03, Fig4_04, Fig4_07.
- Chapter 05: Fig5_01, Fig5_03, Fig5_05, Fig5_11.
- Chapter 06: Fig6_03, Fig6_04, Fig6_07, Fig6_09.
- Chapter 07: Fig7_01, Fig7_02, Fig7_03, Fig7_06, Fig7_07, Fig7_08.
- Chapter 08: Fig8_01, Fig8_02, Fig8_10, Fig8_16, Fig8_17, Fig8_18, Fig8_22, Fig8_26, Fig8_28, Fig8_29, Fig8_30, Fig8_34, Fig8_37, Fig8_38, Fig8_40, Fig8_48, Fig8_49, Fig8_50, Fig8_51, Fig8_54, Fig8_55, Fig8_56, Fig8_58, Fig8_59, Fig8_62, Fig8_63, Fig8_73.
- Chapter 09: Fig9_03, Fig9_05, Fig9_06, Fig9_09.

### Replace 후보

- Fig8_03: 동일 파일의 서로 다른 목적 재사용; ⑥ 대상 오류; 필수 설정 증거 누락.
- Fig8_04: Architecture 삽입 목적과 이미지 완전 불일치.
- Fig8_05: 두 문맥 중 Architecture와 완전 불일치; Meshes/Fbx 목록 차이.
- Fig8_20: 캡션의 핵심 Data Flow가 부재하며 좌표 시점 표기가 부정확하다.
- Fig8_24: 본문에서 핵심으로 구분한 Lighting Data와 Lighting Result의 이중 출력 계약을 검증할 수 없다.
- Fig8_36: 이동 실습의 핵심 증거와 맞지 않는 캡처이다.

### Remove 후보

- 없음. 삭제보다 잘못된 내용·연결을 교정하거나 문맥에 맞는 그림으로 교체하는 방안을 권고한다.
- Fig8_03–05는 한 파일을 일괄 교체하면 다른 재사용 맥락이 손상될 수 있으므로, 후속 수정에서 삽입 목적별 그림을 분리할 것.

### New Figure Recommendation

- Chapter 02–03: 동일 Surface Point P 기준의 L/V/N/R/H와 Camera·Light 위치, 벡터 수치·각도를 보여주는 공통 Convention 그림.
- Chapter 05–06: Material Parameter, BRDF, incoming radiance, Visibility, IBL, HDR 및 출력 변환의 실제 데이터 의존 도식. 범주를 임의의 직렬 Stage로 만들지 않는다.
- Chapter 08 Architecture: 준비/폴더 화면과 별개로 함수별 입력·출력 타입, 공유 데이터 분기, 실제 Add/Lerp 합성, Debug 선택을 보여주는 그림.
- Chapter 08 Shadow: 같은 Scene/Camera에서 단일 조건만 바꾼 이동 전후·Bias·Filtering 비교 및 실제 Debug Mode 범례.
- Chapter 08 Debug: Scalar→Vector3 변환과 RGB EmissionResult를 반영한 최종 MF_DebugView 내부 그래프. Fig8_71 교체안과 중복 제작하지 않는다.
- Chapter 09: 동일 조건의 실제 Profiling Before/After와 엔진 버전·해상도·플랫폼·Frame 제한 설정을 함께 기록한 예시. 가상 수치는 Example로 구분한다.

### Terminology 문제

- ASF 확장이 Art · System · Framework, Art Stylized Foliage, ARTIST SURVIVAL GUIDE 등으로 혼재한다. Ari’s Shader Framework로 통일한다.
- Module, Material Function, Rendering Pipeline Stage를 동일시하지 않는다. 열 분류와 실행 의존 관계를 구분한다.
- Position/Direction/Normal, World/View/Clip/NDC/Screen, Normal Map 저장값/Decode값, Texture/Texture Sample 값을 분리한다.
- BRDF와 PBR, Diffuse Response와 Cast Shadow, Emission과 Bloom, MatCap과 실제 환경 반사를 구분한다.
- LightingData/LightingResult, SpecularMask/SpecularResult, EmissionMask/EmissionResult 및 Scalar/Vector3 계약을 통일한다.
- MF_MatCap 대소문자, Figure 내부 번호, Chapter/Section 예고 번호를 실제 문서와 맞춘다. 기술 용어는 English로, 설명 문장은 Korean 중심으로 정리한다.
- NDF의 Normal을 정규분포로 오역한 표현과 글자 손상·오탈자를 교정한다.

### 반복적으로 나타나는 Visual Communication 문제

- 수식·수치·축·화살표·색상 결과가 서로 맞지 않는다. 계산 결과와 기하 배치를 먼저 확정해야 한다.
- 병렬 입력이나 비용 요소를 직렬 Stage로 그리거나 함수 입력을 출력 위치에 두어 Data Flow가 왜곡된다.
- Before/After에서 Scene, Camera, View Mode, Exposure, Geometry가 함께 달라져 단일 원인을 분리하기 어렵다.
- 엔진 화면의 유효 Override, Mode, Parameter, 연결 및 범례가 없거나 너무 작아 주장을 입증하기 어렵다.
- 가상 수치·재구성 UI·열지도가 실측처럼 보인다. Example/실측 여부와 측정 조건을 명시해야 한다.
- Camera에 보이는 P와 실제 가려진 위치가 맞지 않거나 전체 물체 결과와 현재 Pixel 수치가 혼합된다.
- 조밀한 인포그래픽은 핵심 관계 중심으로 줄이고 확대 화면과 연결선으로 추적 가능하게 한다.

### 완료 및 원본 보존 확인

- 고유 Figure 154개: 누락 0, 중복 0, 목록 외 추가 0.
- 모든 Figure 기록에 Chapter / Section, Status, Recommended Action 및 6개 검토·권고 필드가 존재한다.
- 기준 해시의 원본 181개를 비교한 결과 변경 0개. Foundation Markdown과 Figure 이미지를 수정하지 않았다.
- 결과와 Progress는 이 Audit Report에만 저장했다.
- 마지막 완료 Figure: Fig9_09. Next Figure: None. Remaining Chapters: None.

## Fig1_01

Chapter / Section: Chapter 01 / 1.1 What is Rendering?; Markdown L97. File: `00_Foundation/Figures/Chapter01/Fig1_01.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Geometry / Material / Light / Camera를 Rendering의 입력 묶음으로 두고 2D Pixel Image로 연결한다. 본문의 단순화와 일치하며 Material과 Lighting을 동일시하지 않는다.

Text Consistency: L99–112의 입력 목록과 결과가 모두 보인다. Output 예시가 입력 Cube와 다른 풍경인 것은 개념 아이콘으로 읽을 수 있다.

Terminology: 주요 English Term은 정상이다. 그러나 중앙의 완결된 설명문과 하단 Caption까지 모두 English여서 설명은 Korean이라는 규칙과 차이가 있다.

Visual Communication: 좌→우의 Input / Processing / Output과 화살표가 명료하며 글자는 읽을 수 있다.

Issues: 기술 흐름의 오류는 발견하지 않았다. 긴 English 설명을 짧은 Label과 구별하여 언어 기준에 맞출 필요가 있다.

Recommendation: 제목/Technical Label은 유지하고 중앙 설명문·상세 설명·Caption은 Korean 중심으로 정리한다. 본문의 ‘Light가 필수인 모든 Rendering은 아님’이라는 범위를 유지한다.

## Fig1_02

Chapter / Section: Chapter 01 / 1.2 From Model to Screen; Markdown L365. File: `00_Foundation/Figures/Chapter01/Fig1_02.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Vertex Processing→Primitive Assembly→Culling/Clipping→Rasterization 및 Interpolation→Fragment Processing→Depth Test→Framebuffer→Final Image의 개념적 순서는 본문과 일치한다. Caption에 simplified view가 있어 실제 모든 GPU Pass의 고정 순서로 단정하지 않는다.

Text Consistency: 본문 L375–384는 하나의 연속 흐름인데 그림에는 윗줄 끝 Rasterization에서 아랫줄 시작 Interpolation으로 이어지는 연결이 없다.

Terminology: Pipeline 명칭의 오탈자는 보이지 않는다. 짧은 English Label은 허용 범위지만 긴 Caption은 언어 규칙 정리 대상이다.

Visual Communication: 각 줄 안에서는 방향이 명확하다. 줄바꿈 연결 부재 때문에 두 개의 독립 흐름처럼 읽힐 수 있다.

Issues: Rasterization→Interpolation edge가 시각적으로 누락되어 전체 Data Flow가 끊긴다.

Recommendation: 줄을 잇는 명시적 connector나 연속 단계 번호를 추가한다. Depth Test는 단순화된 논리 순서이며 Early Depth 등의 실제 실행 순서를 모두 규정하지 않는다는 범위를 유지한다.

## Fig1_03

Chapter / Section: Chapter 01 / 1.3 Vertex and Vertex Attributes; Markdown L835. File: `00_Foundation/Figures/Chapter01/Fig1_03.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Vertex를 Position/Normal/UV/Tangent/Color 묶음으로 표현하고 같은 Position에 서로 다른 UV 또는 Normal을 가진 Vertex가 필요할 수 있음을 정확히 보여준다. Attribute 관계선은 실행 단계 화살표가 아니다.

Text Consistency: L839–853의 위/아래 설명, 데이터 예시와 두 분리 원인이 일치한다.

Terminology: ‘렌더링’, ‘노멀 맵’, ‘텍스처’, ‘버텍스 컬러’, ‘스키닝’, ‘커스텀 데이터’ 등 Technical Term의 음역이 English Label과 섞인다. 깨진 Korean/Hanja는 발견하지 않았다.

Visual Communication: Attribute 묶음과 UV Seam/Hard Edge 예시가 분리되어 읽기 쉽다. 아래 비교 데이터가 같거나 다른 지점을 직접 확인할 수 있다.

Issues: Concept 오류는 발견하지 않았다. Technical Term 표기의 일관성만 보완 대상이다.

Recommendation: Rendering, Normal Map, Texture, Vertex Color, Skinning 등으로 기술 용어를 정렬하고 설명 문장의 Korean은 유지한다. 같은 위치의 Attribute 분리 사례는 보존한다.


## Fig1_04

Chapter / Section: Chapter 01 / 1.4 Vertex Processing; Markdown L1297. File: `00_Foundation/Figures/Chapter01/Fig1_04.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Vertex Input→Vertex Shader→Output의 방향과 Local→World→View→Clip Position 변환은 본문에 맞는다. Position의 Clip Space를 Normal에도 강제하지 않는다.

Text Consistency: Attribute 전달/가공과 아직 Triangle 내부를 그리지 않는다는 핵심은 L1285–1309와 일치한다. 다만 하단은 ‘Rasterization을 통해 Pixel이 생성되며 … 각 Pixel의 색상’으로 축약하여 본문의 Fragment/최종 Pixel 구분을 약화한다.

Terminology: 주요 Label은 명확하다. 하단의 Pixel을 Fragment/coverage 후보와 구분할 필요가 있다.

Visual Communication: 3열 구조와 다음 Primitive Assembly 연결이 명료하다. 하단 설명과 Caption은 본도식보다 작지만 판독 가능하다.

Issues: 하단 주석이 Rasterization에서 최종 Pixel이 이미 생성된다는 인상을 줄 수 있다.

Recommendation: 하단을 ‘Rasterization은 covered sample/Fragment 후보를 만들고 이후 Shading·Visibility·Output을 거쳐 결과를 저장한다’는 범위로 정리한다. 주 도식은 유지한다.

## Fig1_05

Chapter / Section: Chapter 01 / 1.5 Primitive Assembly; Markdown L1737, Index 설명 L1833–1845 및 Winding 설명. File: `00_Foundation/Figures/Chapter01/Fig1_05.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 우측 Triangle 0 [0,1,2]는 위쪽 전체 Triangle이어야 하지만 좌측 위 절반만 색칠되어 있다. Triangle 1 [0,2,3]는 좌측 영역인데 우측 아래 영역에 라벨이 놓인다. 표시되지 않은 중심 교차점을 Vertex처럼 사용하는 영역 분할이다. 하단 CCW의 왼쪽 edge와 CW의 오른쪽 edge 화살표는 각 Index 순서와 일치하지 않는다.

Text Consistency: 본문은 Index가 어떤 Vertex를 연결하는지 결정한다고 설명하지만 실제 도형은 그 Index를 따르지 않는다. ‘Vertex Shader 이후 데이터가 Vertex Buffer에 저장’이라는 그림의 추가 단정도 입력 자원과 처리 결과를 혼동할 수 있다.

Terminology: CCW=Front/CW=Back를 조건 없이 고정하고 ‘일반적으로’만 덧붙인다. Front-face convention은 예제 설정으로 제한해야 한다. Vertex Buffer 출력 저장 설명은 Needs Technical Verification.

Visual Communication: 표→연결 결과라는 비교 구조는 유용하지만 잘못된 색 영역과 순환하지 않는 화살표가 핵심 학습을 방해한다.

Issues: Index→Triangle 대응 오류, Winding 방향 오류, 입력 Vertex Buffer와 처리된 Vertex 결과의 경계 혼동.

Recommendation: 각 Index triplet에 맞는 세 꼭짓점을 연결하고 필요 시 겹치는 Triangle을 별도 패널로 나눈다. [0,1,2]와 [0,2,1]의 세 edge 화살표를 모두 실제 순환 방향으로 맞춘다. ‘이 예제는 CCW를 Front로 설정’이라고 한정하고 Vertex Input Buffer / processed outputs / Index source를 구분한다.

## Fig1_06

Chapter / Section: Chapter 01 / 1.6 Culling and Clipping; Markdown L2164, 특히 L2233–2245. File: `00_Foundation/Figures/Chapter01/Fig1_06.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Culling의 전체 제외와 Clipping의 경계 절단 비교는 맞는다. 그러나 Backface 패널은 ‘면의 법선이 카메라의 반대 방향’만으로 제거를 설명하고 설정 조건을 생략한다.

Text Consistency: 본문은 Vertex Normal을 Camera Direction과 직접 비교하는 것이 기본 판정이 아니며 투영된 Triangle의 Winding/rasterizer 설정을 쓴다고 명시한다. 그림은 그 구분을 보여주지 않는다.

Terminology: Face Normal의 직관과 실제 Front/Back 판정이 구분되지 않는다. Camera 등의 English/음역 병기는 부차적인 일관성 정리 대상이다.

Visual Communication: 좌우 비교와 Clipping Before/After는 읽기 쉽다. 하단 단일 Stage 도식은 Frustum Culling까지 모두 Primitive Assembly 이후 같은 GPU 단계에서 수행되는 것으로 읽힐 수 있다.

Issues: Backface 판정의 잘못된 Mental Model과 서로 다른 Culling 실행 위치의 과도한 통합.

Recommendation: Backface 그림에 Winding 및 cull-mode 조건을 표시하고 Normal 화살표는 방향 직관임을 명시한다. Frustum Culling은 Scene/Object 선별의 개념 예시로 구분한다. Clipping 비교는 유지하되 한쪽이 유효 영역이라는 표기를 더 명확히 한다.


## Fig1_07

Chapter / Section: Chapter 01 / 1.7 Rasterization; Markdown L2640. File: `00_Foundation/Figures/Chapter01/Fig1_07.png`.

Status: Match

Recommended Action: Keep

Technical Accuracy: Screen-space Triangle→Coverage→Fragment 후보의 전환을 보여주고 최종 색은 아직 계산하지 않는다고 명시한다. Binary Coverage는 기초 예시로 읽히며 모든 Sampling 방식의 완전한 표현을 주장하지 않는다.

Text Consistency: L2644–2698의 흐름 및 Triangle≠Fragment≠Pixel 설명이 시각적으로 유지된다.

Terminology: Coverage, Fragment, Pixel Candidate, Interpolation의 역할이 일치한다. 판독을 방해하는 오탈자나 깨진 Korean은 발견하지 않았다.

Visual Communication: 세 패널의 같은 Triangle과 Grid, 범례, 연결 방향을 따라 결과를 비교하기 쉽다.

Issues: 해당 본문 맥락에서 수정이 필요한 Concept 불일치는 발견하지 않았다.

Recommendation: 현재 구조를 유지한다. 후속 고급 Sampling 설명을 이 기본 Figure에 과도하게 추가할 필요는 없다.

## Fig1_08

Chapter / Section: Chapter 01 / 1.8 Interpolation; Markdown L3252. File: `00_Foundation/Figures/Chapter01/Fig1_08.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 세 Vertex의 Attribute를 Fragment 위치에서 보간하고 UV를 별도 Texture Sampling에 쓰는 흐름이 맞다. Texture 전체와 Sample 값을 직접 동일시하지 않는다.

Text Consistency: UV A(0,0), B(1,0), C(0,1) 및 Fragment UV 예시 (0.3,0.4)가 본문에 대응한다. 색 Gradient는 원리를 위한 예시이며 정량 보간 검증 그림으로 보기 어렵다.

Terminology: ‘프래그먼트 셰이더’, ‘텍스처 샘플링’, ‘바리센트릭 좌표’ 등 기술 용어 음역이 English 제목과 혼재한다.

Visual Communication: Input / Interpolation / 사용처가 분리되어 명료하다. 중앙의 노란 선택점은 선택 표시이며 그 점의 실제 interpolated color라는 오해를 줄이는 범례가 있다.

Issues: 언어 기준 불일치. RGB 세 꼭짓점의 Gradient는 정확한 가중합보다는 장식적 색 변화로 보이므로 수치 설명의 근거로 사용해서는 안 된다.

Recommendation: 기술 용어는 Fragment Shader, Texture Sampling, Barycentric Coordinate로 통일한다. 색 그림은 개념 예시라고 제한하거나 실제 가중합 색으로 정렬한다. Perspective-correct 조건은 본문 참조로 연결하고 도식의 기본 범위는 유지한다.

## Fig1_09

Chapter / Section: Chapter 01 / 1.9 Fragment / Pixel Processing; Markdown L3953. File: `00_Foundation/Figures/Chapter01/Fig1_09.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Fragment 입력을 이용해 Surface 결과를 계산하고 아직 화면 출력 전이라는 구분은 타당하다. 다만 중앙에서 Material Parameter(입력), Texture Sample(조회), Lighting/Emission(계산)을 같은 형태로 배치하여 정확한 의존성 도식인지 기능 목록인지 모호하다.

Text Consistency: 본문 L3971–3973은 이후 Depth/Blending에 따라 결과가 제거될 수 있다고 명시한다. 상단 출력 전 주석은 일치하지만 하단 ‘각 화면 위치의 픽셀 색상을 결정’은 이를 다시 단정적으로 축약한다.

Terminology: Interpolated UV 아래 checker Texture 이미지가 UV 좌표와 Texture 데이터를 혼동시킬 수 있다. ‘월드/뷰 위치’도 어느 Space인지 예제를 제한해야 한다.

Visual Communication: 3열 Input/Processing/Output 구분은 좋다. 중앙 화살표가 Shader에서 Parameter를 생성하는 것으로 읽히지 않도록 목록과 Data Flow를 구분할 필요가 있다.

Issues: UV와 Texture 아이콘의 경계, 입력/계산 분류, 최종 Pixel에 대한 하단 표현이 불명확하다.

Recommendation: UV는 좌표/UV gradient로 표시하고 Texture Resource→Sample←UV 관계를 짧게 보여준다. 중앙은 ‘계산 예시’ 목록으로 표시하거나 실제 입력 방향으로 연결한다. 하단은 Fragment 결과를 계산한다고 맞춘다.


## Fig1_10

Chapter / Section: Chapter 01 / 1.10 Depth Test and Surface Visibility; Markdown L4590 및 L4808의 두 삽입 맥락 모두 확인. File: `00_Foundation/Figures/Chapter01/Fig1_10.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Camera 기준 가까운 불투명 Surface 선택 예시는 맞다. 하지만 ‘Depth 값이 더 작은 것을 선택’을 보편 규칙으로 제시하고, 하단에서 `Shadow Map = Light 기준 Visibility`로 자원과 판정 결과를 등치한다.

Text Consistency: 본문은 비교 조건이 Depth Function/설정에 따라 달라지고 Depth Write가 별도임을 설명한다. 그림에는 그 조건이 없고 Depth Buffer 갱신이 항상 이어지는 듯 보인다. 두 참조는 같은 Section 내용의 재사용이며 서로 다른 Figure 충돌은 아니다.

Terminology: Shadow Map은 Depth 자원이고 Light Visibility는 조회/비교로 얻는 판단이다. 본문의 ‘Shadow Map을 이용한 Visibility’라는 설명도 그림에서는 단계 구분이 필요하다.

Visual Communication: Character/Wall, Near/Far와 Camera ray는 명료하다. 반면 `Depth Buffer→Visible Surface`는 Depth 값 자체가 최종 색을 만든다고 오해할 여지가 있다.

Issues: Shadow Map/Visibility 경계 붕괴, Depth 비교 convention 및 Write 조건 생략.

Recommendation: 하단을 `Light-space Depth(Shadow Map)→Depth comparison→Light Visibility`로 정리한다. 본 예시는 불투명·작을수록 가까움·해당 Depth Test/Write 설정이라고 제한한다. 통과한 Color 기여와 Depth Write를 분기해 표시한다.

## Fig1_11

Chapter / Section: Chapter 01 / 1.11 Framebuffer and Final Image; Markdown L5379 및 Buffer Write/Post Process/Present 설명. File: `00_Foundation/Figures/Chapter01/Fig1_11.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Color/Depth/기타 Render Target을 분리하고 Depth는 화면에 직접 표시하지 않는다고 명시한 점은 맞다. Shader Output의 Depth 0.35가 항상 명시적으로 계산·출력되는 것으로 읽히며, 일반 Depth와 선택적 Shader depth override의 차이는 없다(Needs Technical Verification).

Text Consistency: 본문은 Depth Test 이후의 기록과 추가 Post Process/Final Processing을 설명하지만 그림은 Write→Present로 바로 이어진다. 전체 Sphere 출력에서 산 풍경 Buffer로 바뀌어 같은 데이터의 추적이 끊긴다.

Terminology: Framebuffer의 묶음과 개별 Render Target은 하단 설명에서 구별된다. 기술 Label은 읽을 수 있다.

Visual Communication: 저장 대상의 분리는 유용하다. 상이한 Scene 이미지와 생략된 Write 조건 때문에 하나의 결과가 어떻게 전달되는지 불명확해진다.

Issues: 입력/출력 예시 불연속, Depth 공급/Write 조건과 최종 처리의 생략 범위 불명확.

Recommendation: 같은 Scene을 Output/Buffer/Final에 사용하거나 각각 독립 예시임을 표시한다. Depth Test/Write 조건 및 필요 시 Post Process→Display target→Present라는 축약 표기를 추가한다. 필수 Depth 계산이 Shader에 있다는 일반화는 피한다.


## Fig1_12

Chapter / Section: Chapter 01 / 1.12 CPU, GPU and Draw Calls; Markdown L6010. File: `00_Foundation/Figures/Chapter01/Fig1_12.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: CPU/Engine의 준비와 GPU의 병렬 실행을 구별한다. 한 Object가 여러 Draw Call로 나뉠 수 있음을 명시하여 Object/Triangle/Draw Call을 등치하지 않는다.

Text Consistency: L6014–6038의 기초 관계와 일치한다. 다만 Geometry Data·Shader State·Constant Data를 Draw Call 상자 안에 넣고 ‘Buffer와 State를 함께 전달’이라고 하여 매 Draw마다 자원 전체를 복사하는 것으로 읽힐 수 있다.

Terminology: Draw Call과 해당 Draw에서 사용하는 자원/State binding을 구분하면 더 정확하다. Scene·Mesh·Material 등 주요 Label은 명료하다.

Visual Communication: CPU→요청→GPU→결과의 진행은 읽기 쉽다. 작은 목록은 많지만 분류가 있어 추적 가능하다.

Issues: Draw 명령과 사전에 준비/바인딩한 자원 참조의 범위가 모호하다. Material 0/1별 Draw는 예시라는 제한이 필요하다.

Recommendation: 중앙을 ‘Draw가 참조하는 Data/State’로 제한하고 실제 명령 전달과 Buffer 전체 업로드를 구별한다. 예시의 Draw 개수를 모든 Pass/Instancing 조건에 적용되는 공식으로 만들지 않는다. 기본 CPU/GPU 관계는 유지한다.

## Fig1_13

Chapter / Section: Chapter 01 / 1.13 Complete Rendering Pipeline; Markdown L6838. File: `00_Foundation/Figures/Chapter01/Fig1_13.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: CPU 준비→Draw→GPU Geometry/Screen 처리→Output이라는 큰 흐름은 일치한다. GPU Geometry/Screen Stage는 여러 처리를 묶은 설명용 범주이지 별도의 단일 Hardware Stage라고 읽지 않도록 제한이 필요하다. Frustum Culling을 GPU의 post-assembly 목록에 고정한 표기도 Fig1_06과 같은 구분이 필요하다.

Text Consistency: 본문에는 Object 선별/LOD가 CPU 준비에도 포함되고 필요 Render Pass 조건을 명시한다. 그림은 CPU Culling과 GPU Culling의 대상/구현 차이를 생략한다. 하단 Post Process/Tone Mapping/UI 추가 처리 안내는 본문의 범위를 잘 보존한다.

Terminology: Framebuffer 아래 `(Render Target)` 단수 병기는 묶음과 개별 저장 대상의 차이를 축약한다. 3.3 Culling 설명 일부 글자와 4.4 삽화 하단 작은 문자열은 겹치거나 뭉개져 정확히 판독하기 어렵다. 읽히지 않는 문자열을 임의로 복원하지 않았다.

Visual Communication: 전체를 한 장에 연결한 목적은 좋으나 세부 열의 폭이 좁고 작은 글씨·중복 하단 요약이 밀집되어 있다. 상세 Label을 읽으려면 확대가 필요하다.

Issues: 범주명과 실제 Stage 경계, Culling 실행 위치의 제한, Framebuffer/Render Target 표기, 일부 글자 가독성.

Recommendation: 개념적 Raster Pipeline 개요라고 명시하고 Geometry/Screen은 Processing group으로 표시한다. CPU Object 선별과 GPU primitive 처리를 구별한다. 작은 중복 설명을 줄여 핵심 입출력 Label을 키우고 판독 불가능한 문자열은 원문을 확인해 교정한다. Framebuffer와 Render Target의 관계는 Fig1_11 기준으로 정렬한다.


## Fig2_01

Chapter / Section: Chapter 02 / 2.1 Why Coordinate Systems Matter; Markdown L102. File: `00_Foundation/Figures/Chapter02/Fig2_01.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 같은 Point의 좌표가 기준에 따라 달라진다는 목적은 맞다. 그러나 View 패널은 Z축을 ‘카메라가 바라보는 방향’이라 정의하면서 앞쪽 5의 좌표를 z=−5로 쓴다. +Z 전방인지 −Z 전방인지 그림 내부 convention이 충돌한다.

Text Consistency: 본문은 Local (1,0,0)→World (6,2,0)의 예시와 같은 Point라는 점을 설명한다. 그림은 명확한 Local Origin에서 X축만큼 떨어진 점을 보이지 않고 Cube 윗꼭짓점을 표시하여 좌표 예시를 재현하기 어렵다.

Terminology: Local 설명의 `Origin` 괄호가 닫히지 않는다. ‘Origin은 보통 객체 중심’은 임의 Pivot 가능성을 약화한다. Technical Term의 음역과 English가 혼재한다.

Visual Communication: 세 Space의 색상 구분은 좋지만 축 원점/Point/값 사이의 대응이 정확하지 않다.

Issues: View forward 부호 모순, Local 값과 축/점 대응 불명확, 괄호 누락.

Recommendation: 한 convention을 선택해 Camera forward와 z값을 정렬한다. Origin과 모든 축의 출발점을 같게 하고 (1,0,0) 점을 +X 위에 표시한다. Local→World Translation과 Camera Transform을 예제 조건으로 명시한다. Origin은 Object의 기준점이며 중심과 같을 필요가 없다고 제한한다.

## Fig2_02

Chapter / Section: Chapter 02 / 2.2 Position, Direction and Vector; Markdown L934. File: `00_Foundation/Figures/Chapter02/Fig2_02.png`.

Status: Match

Recommended Action: Keep

Technical Accuracy: Position의 기준 Origin, 위치와 무관한 Direction, A→B displacement를 구별한다. B(4,3,2)−A(1,1,0)=(3,2,2)의 계산이 맞고 Translation의 Position/Direction 차이도 본문과 일치한다.

Text Consistency: L918–928의 의미 구분과 동일한 XYZ라도 의미/Space를 봐야 한다는 설명을 뒷받침한다.

Terminology: Direction/Magnitude와 Vector의 관계가 명확하다. ‘두 Point 사이’는 제시한 displacement 예시로 읽히며 모든 Vector의 유일한 정의로 확장할 필요가 없다.

Visual Communication: 세 패널의 Point·화살표·수치를 쉽게 비교할 수 있다. 도식은 좌표계의 개념 예시이며 눈금에 의한 수치 검증용 그래프는 아니다.

Issues: 본문과 비교했을 때 필수 수정이 필요한 불일치는 발견하지 않았다.

Recommendation: 유지한다. 이후 정규화/Transform 설명에서 이 의미 구분을 그대로 사용한다.

## Fig2_03

Chapter / Section: Chapter 02 / 2.3 Local Space / Object Space; Markdown L1625, L1727–1733의 무회전 예시. File: `00_Foundation/Figures/Chapter02/Fig2_03.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Local 값 유지와 World Transform 적용의 구분은 맞다. 하지만 위 Transform은 Translation=(5,2,1), Rotation=(0,45,0), Scale=(1,1,1)인데 아래 World Position=(6,3,2)는 Rotation 없는 단순 덧셈 결과다. 같은 연속 예제로 제시된 조건과 결과가 불일치한다.

Text Consistency: 본문은 (6,3,2) 계산을 Rotation/Scale이 없다고 명시적으로 제한한다. 그림은 회전된 Object까지 함께 보여주면서 그 조건을 누락한다.

Terminology: Local/Object Space와 Object/Edit Mode 차이는 전달된다. Rotation 숫자는 단위/축 순서가 명시되어야 한다.

Visual Communication: 4개 패널의 학습 흐름은 좋으나 상단 Transform과 하단 결과가 같은 사례처럼 연결된다.

Issues: Transform 조건과 World 좌표값의 수학적 불일치.

Recommendation: 단순 Translation 예시라면 Rotation=0과 해당 축 배치로 맞춘다. 45도 회전을 유지한다면 정의한 축/convention으로 변환값을 계산해 수정한다. 서로 다른 예시라면 패널별 조건을 분명히 분리한다.


## Fig2_04

Chapter / Section: Chapter 02 / 2.4 World Space; Markdown L2250. File: `00_Foundation/Figures/Chapter02/Fig2_04.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 하단 Translation-only (1,1,1)+(5,2,0)=(6,3,1)은 정확하고 조건도 명시한다. 그러나 상단 World 좌표 그림에서 A=(5,2,0)가 +X와 반대인 Origin 왼쪽에 놓여 좌표값/축 대응이 맞지 않는다. B/C 역시 좌표별 위치를 신뢰성 있게 추적할 수 없다.

Text Consistency: 본문은 공통 World 기준에서 Object 위치를 비교하는 것이 목적이다. 우상단 Local Space 카드에 동일 World 좌표를 Space 표시 없이 재기입하여 각 Object의 Local 값처럼 읽힐 수 있다.

Terminology: World Position과 Object Local Origin의 Label 범위가 혼재한다. 회전한 Cube B의 Local Axis와 World Axis 차이도 충분히 드러나지 않는다.

Visual Communication: 공통 좌표계와 개별 좌표계를 비교하는 구성은 좋지만 핵심 숫자가 실제 도형 배치를 설명하지 못한다.

Issues: World 축/위치 불일치와 Local 카드에 World 값의 무표기 재사용.

Recommendation: 지정 좌표에 맞춰 Object Origin을 배치하고 눈금/보조선을 둔다. Local 카드 수치는 `Object Origin in World Space`라고 구분하거나 Local Origin=(0,0,0)로 표시한다. 하단의 올바른 단순 Translation 사례는 유지한다.

## Fig2_05

Chapter / Section: Chapter 02 / 2.5 View Space / Camera Space; Markdown L2953. File: `00_Foundation/Figures/Chapter02/Fig2_05.png`.

Status: Match

Recommended Action: Keep

Technical Accuracy: World 기준에서 Camera 기준의 3D 표현으로 바뀐다는 핵심과 Camera Origin=(0,0,0)이 맞다. 하단에서 전방 Z 부호와 Axis convention이 API/Engine에 따라 다를 수 있다고 명시한다.

Text Consistency: L2943–3062의 설명처럼 실제 Object를 옮기는 것과 기준 변환을 구별하고 View Space가 여전히 3D임을 강조한다.

Terminology: World/View/Camera Space의 관계가 일치한다. World Z-up 도식과 View Y-up 도식은 명시된 서로 다른 기준이므로 그 자체를 오류로 판정하지 않는다.

Visual Communication: 두 기준과 View Transform 화살표를 따라 읽기 쉽다. 숫자 검증용이 아닌 개념적 배치 그림으로 충분하다.

Issues: 해당 설명 범위에서 필수 수정 사항을 발견하지 않았다.

Recommendation: 유지한다. 다른 Figure의 전방 부호도 이와 같이 convention을 명시하도록 정렬한다.

## Fig2_06

Chapter / Section: Chapter 02 / 2.6 Projection; Markdown L3541. File: `00_Foundation/Figures/Chapter02/Fig2_06.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 같은 크기 Object의 Near/Far에 따른 화면 크기 차이와 Depth 보존 개념은 타당하다. View→Projection→Screen으로 크게 단순화한 도식은 세부 Clip/NDC 변환을 포함한 전체 효과로 읽어야 한다.

Text Consistency: 본문은 Screen 표현을 위한 형태로 변환한다고 설명한다. 그림은 ‘3D→2D’ 뒤 ‘투영된 결과는 이후 Clip Space→NDC→Screen’이라고 적어 2D 결과 다음에 Clip Space가 생기는 것처럼 순서가 모호하다.

Terminology: Perspective Projection 효과와 Projection Matrix 출력의 구분이 필요하다. Axis convention 주석은 적절하다.

Visual Communication: Near/Far와 Screen Result 비교는 명료하지만 동일 Camera ray 위 배치가 출력에서 옆으로 나열되는 등 비교용 배치라는 표기가 필요하다.

Issues: 개념적 투영 효과와 실제 좌표 변환 출력 순서의 혼합.

Recommendation: 큰 화살표는 ‘전체 투영/화면 변환의 효과’라고 제한하고 작은 흐름을 View→Projection Matrix→Clip→Divide→NDC→Viewport→Screen으로 정렬한다. 크기 비교는 가림을 제외한 독립 비교 예시라고 표시한다.


## Fig2_07

Chapter / Section: Chapter 02 / 2.7 Clip Space; Markdown L4391 및 Clip Range / Z Range 설명. File: `00_Foundation/Figures/Chapter02/Fig2_07.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Divide 식과 Viewport의 Y-down 예시 식은 맞다. 그러나 Clip Space를 ‘정규화된 단위 큐브/3D 공간’으로 설명하고 NDC x/y/z가 모두 항상 −1~+1이라고 단정한다. 본문은 Homogeneous 중간 표현과 API에 따른 Z 범위를 구분한다.

Text Consistency: 본문 Clip Space Is Not an Ordinary 3D Space 및 What About the Z Range?의 제한이 그림에서 사라졌다. 모서리 Label도 동일한 +Z 면의 점과 −Z 면의 점을 위/아래로만 바꾸어 입체 축 대응이 불명확하다.

Terminology: `Normalized Device Coordinate`는 본문의 Coordinates와 정렬할 수 있다. Screen 설명의 ‘DirectX는 위, OpenGL은 아래’는 y 증가 방향인지 Origin인지 불명확하며 바로 아래 Y Down 예시와 혼동된다.

Visual Communication: 네 단계 구분은 유용하나 Clip/NDC를 같은 Cube 형태로 놓고 서로 다른 의미를 충분히 표시하지 않는다.

Issues: Clip/NDC 범위 혼동, Z convention의 보편화, Screen Origin/축 방향 혼동.

Recommendation: Clip은 (x,y,z,w)와 clipping inequalities로, NDC는 Divide 뒤 좌표로 구분한다. Z는 선택한 convention을 명시하고 다른 범위 가능성을 본문 참조로 둔다. Cube는 고정 w 단면/개념도임을 한정하거나 제거하고 정확한 축·꼭짓점 값을 사용한다. Screen 예시는 Origin=top-left, +Y=down이라고 직접 쓴다.

## Fig2_08

Chapter / Section: Chapter 02 / 2.8 Homogeneous Coordinate and W; Markdown L5172. File: `00_Foundation/Figures/Chapter02/Fig2_08.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: affine 입력의 Position w=1 / Direction w=0과 Translation 차이를 구별하고 Projection 후 w의 역할이 다르다고 명시한다. 상단의 주된 개념은 정확하다.

Text Consistency: 본문의 중요한 두 w 역할 구분은 보존한다. 하단 Perspective 삽화는 ‘먼 점이 더 화면 중심에 가깝게 투영’의 전제인 같은 X/Y offset을 표시하지 않는다.

Terminology: `Screen (NDC Space)`는 NDC와 Screen Space를 같은 것으로 읽히게 한다. `Direction + Translation`은 직접 벡터 덧셈인지 affine Matrix 적용인지 모호하다.

Visual Communication: Position/Direction 비교는 명료하다. 하단 작은 삽화에서 점의 연결선과 전후 위치를 정확히 추적하기 어렵다.

Issues: 부수적인 Perspective 도식의 조건 누락과 NDC/Screen 명칭 혼합.

Recommendation: Translation 표기를 affine Transform 적용으로 명시한다. Perspective 예시에 동일 X/Y offset 조건을 적고 출력 면을 NDC로만 표시한다. 핵심 w=1/0 및 Projection 후 역할 차이 패널은 유지한다.

## Fig2_09

Chapter / Section: Chapter 02 / 2.9 Perspective Divide and NDC; Markdown L6119 및 How Depth Affects Perspective Divide. File: `00_Foundation/Figures/Chapter02/Fig2_09.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 2/2=1, 2/10=0.2 계산은 맞다. 하지만 ‘같은 방향의 Point라도 멀수록 중심에 더 가깝게 배치’는 틀린 조건이다. 같은 Camera ray 방향이면 x/z 비가 같아 같은 화면 위치에 투영된다. 왼쪽 점들은 시선축 위에 놓여 x_clip=2라는 예시와도 맞지 않는다.

Text Consistency: 현재 본문은 같은 좌우 Offset, 다른 View Depth라고 명시하고 Near/Far Plane과 혼동하지 않도록 Vertex A/B를 사용한다. 그림은 이전 Near/Far Point와 ‘같은 방향’ 설명을 유지한다.

Terminology: 식의 x/y/z에는 _clip, 결과에는 _ndc를 붙여 본문의 표기 규칙과 정렬할 필요가 있다. z=?는 X 변화만 보는 예시임을 명시해야 한다.

Visual Communication: NDC=(1,0) 점이 +1 경계 바깥에 그려져 있다. 왼쪽 공간 배치·중앙 계산·오른쪽 위치가 일관되지 않는다.

Issues: 같은 방향과 같은 X offset 혼동, 시선축/좌표값 불일치, NDC 경계 점의 위치 오류.

Recommendation: 동일 X offset을 가진 서로 다른 Depth의 두 점을 Camera 축 옆에 표시하고 대응 projection ray를 그린다. Vertex A/B와 Clip/NDC 표기를 본문에 맞춘다. (1,0)은 경계 위, (0.2,0)은 해당 눈금에 정확히 둔다. 같은 ray의 점은 동일 화면 위치라는 비교를 짧게 덧붙인다.


## Fig2_10

Chapter / Section: Chapter 02 / 2.10 Viewport Transform and Screen Space; Markdown L7588. File: `00_Foundation/Figures/Chapter02/Fig2_10.png`.

Status: Match

Recommended Action: Keep

Technical Accuracy: NDC (0.5,0.5)를 좌상단 Origin / Y-down / 1920×1080 Viewport의 (1440,270)으로 대응시키는 계산이 정확하다. 중심 (960,540)도 일치한다.

Text Consistency: 본문의 Scale+Offset, Resolution-independent NDC와 Viewport 크기/위치의 관계를 유지한다. Screen 전체와 Viewport가 항상 같지 않다는 별도 예시도 적절하다.

Terminology: NDC, Viewport Transform, Screen Space의 구분과 축 증가 방향이 명확하다. 숫자 표기의 충돌이나 깨진 글자는 발견하지 않았다.

Visual Communication: 동일한 빨간 점을 세 패널에서 추적할 수 있고 원점/중심/축 방향을 비교하기 쉽다.

Issues: 본문과 비교하여 필수 수정이 필요한 불일치를 발견하지 않았다.

Recommendation: 유지한다. 이 Figure의 명시적인 Origin/축/해상도 표기를 다른 Screen 변환 예시의 기준으로 사용할 수 있다.

## Fig2_11

Chapter / Section: Chapter 02 / 2.11 Matrix Transform Basics; Markdown L8448. File: `00_Foundation/Figures/Chapter02/Fig2_11.png`.

Status: Match

Recommended Action: Keep

Technical Accuracy: M×column vector의 4×4 곱셈 표기와 homogeneous 입력의 Position w=1 / Direction w=0이 일관된다. Model→World, View→View Space, Projection→Clip의 대응이 맞다.

Text Consistency: 본문의 Transform 규칙·Input/Output·Scale/Rotation/Translation 소개와 일치한다. 위의 XYZ 개념도는 바로 옆 homogeneous 상세와 함께 읽을 수 있다.

Terminology: Matrix/Coordinate/Position/Direction을 일관되게 사용한다. 주요 Label에서 오류를 발견하지 않았다.

Visual Communication: 기초 역할, 수식, 변환 예시, Pipeline 적용을 네 구역으로 나누어 읽기 쉽다. 실제 곱셈 convention이 수식에 드러난다.

Issues: 현재 기초 설명 목적에서 필수 수정 사항을 발견하지 않았다.

Recommendation: 유지한다. 추후 행벡터 예시를 추가할 때에는 이 그림의 열벡터 convention과 구별한다.

## Fig2_12

Chapter / Section: Chapter 02 / 2.12 Model / View / Projection Matrix; Markdown L9319. File: `00_Foundation/Figures/Chapter02/Fig2_12.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Matrix와 Space의 순서 및 View Matrix의 inverse 설명은 맞다. 그러나 View Space 패널의 좌표축이 Camera가 아닌 Cube 쪽에 놓여 Camera 기준 Origin을 잘못 보여준다. Clip 패널은 View Frustum 자체를 Clip Space의 공간 그림처럼 제시한다.

Text Consistency: 본문은 같은 Vertex를 Camera 기준 좌표로 바꾸고 Projection 결과가 Clip Position이라고 설명한다. 그림의 Camera/축 배치와 Frustum 표시는 이 구분을 약화한다. Local (1,0,0) 점도 축 공통 Origin과 +X 위의 관계를 명확히 확인할 수 없다.

Terminology: Clip Position의 4성분 표기는 적절하다. View Position (2,1,−8)은 전방 −Z convention과 Camera Transform 조건이 있어야 해석 가능하다.

Visual Communication: 네 단계와 하단 계약표는 유용하지만 각 공간 그림의 Origin과 점을 따라 수치 변환을 재현하기 어렵다.

Issues: View Origin의 잘못된 시각적 위치, View Frustum/Clip 표현의 혼합, 수치 예시의 기준 부재.

Recommendation: View 축의 공통 Origin을 Camera에 두고 전방 부호를 표시한다. Clip 패널의 Frustum은 Projection 입력 범위 예시라고 분리하고 출력은 homogeneous 좌표로 표현한다. Local/World/View 수치가 동일한 Transform 조건 아래 이어지도록 기준을 명시한다.

## Fig2_13

Chapter / Section: Chapter 02 / 2.13 Position Transform vs Direction Transform; Markdown L10400. File: `00_Foundation/Figures/Chapter02/Fig2_13.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Translation이 Position에만 적용되고 Direction에는 제외되는 차이, Normal의 Non-uniform Scale/Inverse Transpose 주의는 본문에 맞다. 다만 `Transform = Scale + Rotation + Translation`은 실제 행렬 합으로 읽힐 수 있다.

Text Consistency: 하단의 T·R·S는 앞서 사용한 열벡터 convention과 연결된다. ‘Normal 상세는 다음 절’이라는 안내는 현재 절에 이미 있는 Normal Transform 설명보다 모호하다.

Terminology: Normal과 일반 Direction의 구분은 보존된다. + 표기를 기능 구성과 수학적 연산에서 구별할 필요가 있다.

Visual Communication: Position/Direction/Normal의 비교와 Translation 전후가 잘 분리되어 있다.

Issues: Transform 구성의 덧셈 기호와 실제 곱셈 표기의 혼재.

Recommendation: +를 구성 목록으로 바꾸고 열벡터 기준 T·R·S 적용 순서를 짧게 명시한다. Normal 관련 참조는 현재 절의 해당 설명 및 다음 Tangent Space로 정확히 연결한다. 핵심 비교는 유지한다.

## Fig2_14

Chapter / Section: Chapter 02 / 2.14 Tangent Space; Markdown L11335, Normal Map Encoding 설명. File: `00_Foundation/Figures/Chapter02/Fig2_14.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Surface별 TBN과 Normal 변환 목적은 맞다. 그러나 ‘Texture의 RGB 값은 [−1,1] 범위의 Tangent Space Normal’이라는 설명이 저장된 RGB와 Decode된 Direction을 구분하지 않는다. 본문은 Texture Encoding을 0–1로 명시한다.

Text Consistency: 본문의 저장 표현과 방향 의미 구분이 그림에서는 빠진다. 우측 변환 후에도 축이 T/B/N으로 표시되어 World 기준 성분으로 바뀌었다는 관계를 확인하기 어렵다.

Terminology: Formula는 TBN×N이고 큰 화살표에는 ×TBN이라고 써서 곱셈 convention이 모호하다. Technical Term의 음역도 혼재한다.

Visual Communication: TBN/UV/Mirrored UV/Normal Map 활용을 한 장에 연결한 장점이 있으나 8개 패널이 밀집되어 작은 Label이 많다.

Issues: Normal Map 저장값과 Decode값의 경계 혼동, 변환 전후 기준축과 곱셈 표기의 불일치.

Recommendation: Texture Sample→Normal Decode→Tangent-space Direction→TBN Transform→World Normal을 명시한다. Engine Normal sampler가 이미 Decode한다면 중복 Decode하지 않는다는 조건을 둔다(구체 동작은 Needs Technical Verification). 출력은 World XYZ 기준으로 표시하고 열벡터 식과 화살표를 정렬한다. Mirrored UV와 정규화 주의는 유지한다.

## Fig2_15

Chapter / Section: Chapter 02 / 2.15 Coordinate Space Conversion in Unreal; Markdown L12383 및 Camera Vector / PixelNormalWS 설명. File: `00_Foundation/Figures/Chapter02/Fig2_15.png`.

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Camera Vector 그림의 화살표가 Camera→Surface로 향하여 ‘현재 Pixel에서 Camera를 향하는 방향’이라는 자체 Label과 본문에 반대다. 하단 World Position+Camera Vector를 같은 Space이므로 바로 비교/연산 가능하다고 하는 예시는 Position과 Direction의 의미 차이를 지운다.

Text Consistency: 본문의 같은 Space 비교 예시는 World Normal과 Camera Direction이다. 그림에서는 World Position으로 바뀌었다. PixelNormalWS를 단순 보간 법선으로 설명하여 본문의 Normal Map/최종 Surface Normal 구분도 축약한다.

Terminology: Object Position을 Pivot이라고 특정하는 것은 본문의 ‘Object 기준 위치’보다 강한 주장이다. 실제 선택한 Node의 bounds center/pivot 의미와 ScreenPosition의 출력 모드/범위는 Needs Technical Verification.

Visual Communication: 상단 Space 목록이 Tangent→Local→World→View→Screen의 필수 직렬 변환처럼 보인다. 이는 실제 변환 선택 목록과 다르다.

Issues: Camera Vector 방향 반전, 데이터 의미를 무시한 비교, Node 출력 의미의 과도한 단순화.

Recommendation: Camera Vector 화살표를 Surface→Camera로 수정할 대상으로 기록한다. 비교 예시는 World Normal·World View Direction으로 맞춘다. 상단은 Space 목록 또는 선택 가능한 변환 관계로 표현한다. 정확한 Node 이름/출력 설정/의미를 확인해 Object Position·PixelNormalWS·ScreenPosition 라벨을 제한한다.

## Fig2_16

Chapter / Section: Chapter 02 / 2.16 Complete Coordinate Flow; Markdown L13690. File: `00_Foundation/Figures/Chapter02/Fig2_16.png`.

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Position의 Model→View→Projection→Clipping→Divide→Viewport 순서는 맞고 Direction은 필요한 Space까지만 변환한다고 구분한다. 다만 `float3 localPos`를 그대로 Model/Projection 행렬에 곱하는 표기는 앞선 homogeneous 4×4 계약과 맞지 않는다.

Text Consistency: 본문의 연산 순서는 잘 보존된다. 하단 Surface Tangent Space→Normal Map Sample 직렬 도식은 Surface basis가 Texture Sample을 생성하는 것으로 읽힐 수 있다. TBN은 Sample된 Direction을 변환할 때 별도 입력으로 필요하다.

Terminology: Clip 패널의 Frustum은 입력 가시 영역의 개념도라고 제한할 필요가 있다. Viewport 식은 Y-up 예시이며 앞선 Y-down 사례와 convention이 다름을 명시해야 한다.

Visual Communication: Position/Direction 두 흐름 구분은 유용하다. 좁은 상단 열과 작은 수식은 상세 검토 시 확대가 필요하다.

Issues: 코드형 표기의 차원 생략, Viewport Y convention 부재, Normal Sample과 basis의 의존성 축약.

Recommendation: Position 입력을 float4(localPos,1)로 명시하거나 식 전체를 개념식으로 표시한다. Viewport의 Origin/+Y를 선언한다. Normal Map+UV→Sample/Decode와 Surface TBN을 분기 입력으로 받아 World/View Normal로 합류하게 한다.

## Fig3_01

Chapter / Section: Chapter 03 / 3.2 Vector and Normalize — Chapter03_LightingMathematics.md L130. Figure: Figures/Chapter03/Fig3_01.png

Status: Match

Recommended Action: Keep

Technical Accuracy: A=(4,2,0), B=(2,1,0)의 길이와 Normalize 결과가 반올림 오차 범위에서 정확하다. 방향을 유지하면서 길이를 1로 만드는 관계가 올바르다.

Text Consistency: 본문의 동일 방향·다른 길이 예시와 Lighting의 방향 비교 준비 과정을 그대로 전달한다.

Terminology: Normalize, Magnitude, Unit Vector 및 Normal/Light/View Direction의 의미가 일관된다.

Visual Communication: 전후 패널과 겹쳐진 결과 화살표로 두 Vector가 같은 Unit Vector가 됨을 명확히 보여준다.

Issues: 본 예시에서 확인된 실질적인 불일치 없음.

Recommendation: 유지한다.

## Fig3_02

Chapter / Section: Chapter 03 / 3.3 Dot Product — Chapter03_LightingMathematics.md L233. Figure: Figures/Chapter03/Fig3_02.png

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 수치 표의 cos 값은 맞지만 135° 패널의 N은 위쪽, L은 왼쪽 위쪽을 향해 실제 두 방향은 약 45°이다. 따라서 그림의 방향으로는 Dot Product가 양수이며 -0.707이 아니다. saturate와 max의 등식은 앞서 선언한 Unit Vector 조건에서 성립한다.

Text Consistency: 본문은 N과 L 사이의 각도를 정의하고 NdotL이 최종 밝기가 아님을 구분한다. Figure의 45°/135° 각도 호는 N 대신 오른쪽 수평 보조선을 기준으로 표시하고, 구체 렌더를 최대 밝기/약 70%의 빛으로 직접 연결해 이 구분을 약화한다. 다음 Section이 Lambert라는 예고도 실제 3.4 Surface Normal과 다르다.

Terminology: N, L, Dot Product의 명칭은 적절하나 밝기 표현은 단일 지점의 Lambert 방향 계수로 한정해야 한다.

Visual Communication: 다섯 각도 비교 구조는 유용하지만 135° 방향 오류가 음수 Dot Product 이해를 직접 방해한다. 구 전체에는 위치별로 다른 Normal이 있으므로 하나의 고정 NdotL 결과를 대표하는 데 설명이 필요하다.

Issues: 135° 화살표와 음수 값 불일치; 각도 기준선 불일치; 방향 계수와 최종 밝기 혼동; 다음 Section 예고 오류.

Recommendation: 공통 원점에서 N과 L 사이에 각도 호를 그리고 135°의 L을 N과 실제 135°가 되는 방향으로 수정한다. 구체 대신 고정 Normal의 Surface 패치를 쓰거나 특정 지점을 표시하고, 수치를 max(NdotL,0) 방향 계수로 명시한다. 다음 Section 안내를 3.4 Surface Normal에 맞춘다.

## Fig3_03

Chapter / Section: Chapter 03 / 3.4 Surface Normal — Chapter03_LightingMathematics.md L427. Figure: Figures/Chapter03/Fig3_03.png

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Normal의 표면 방향 및 Face Normal의 Cross Product 식은 타당하다. 다만 Vertex Normal을 인접 Polygon 평균으로 항상 계산한다고 단정하며, Flat/Smooth 비교에서 실루엣과 Mesh 분할까지 달라 보인다. Vertex Normal은 제작자가 조정할 수도 있다.

Text Consistency: 본문 L503–505의 동일 Geometry에서 Shading만 달라지고 실루엣은 바뀌지 않는다는 설명과 비교 그림이 충돌한다. 본문에 있는 Vertex Normal 조정 가능성도 그림의 단정적인 설명에 반영되지 않았다.

Terminology: Surface/Vertex/Face Normal의 구분은 유지된다. Normal 표시 패널의 RGB는 좌표축 색 관례이므로 Normal 화살표의 필수 색상 규칙으로 읽히지 않도록 구분이 필요하다.

Visual Communication: 개념별 패널은 읽기 쉽다. 삼각형 계산 삽화는 p1 위치가 표시되지 않고 e2가 두 변에 반복되어 e1=p1-p0, e2=p2-p0와 도형 대응이 불명확하다.

Issues: Flat/Smooth 비교의 Geometry 통제 실패; Vertex Normal 평균 계산의 일반화; 삼각형 Vertex/Edge 라벨 누락 및 중복.

Recommendation: 동일 Mesh와 동일 카메라로 Flat/Smooth를 비교해 실루엣을 일치시킨다. Vertex Normal 설명을 대표적인 생성 방법으로 한정하고 사용자 편집 가능성을 추가한다. 삼각형의 p0,p1,p2를 모두 표시하고 p0에서 출발하는 두 Edge를 e1,e2로 각각 한 번씩 표시한다.

## Fig3_04

Chapter / Section: Chapter 03 / 3.5 Normal Transformation — Chapter03_LightingMathematics.md L599. Figure: Figures/Chapter03/Fig3_04.png

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: T=(1,1), N=(-1,1), X Scale=2의 예시에서 T′=(2,1), Nwrong=(-2,1), Dot=-3은 정확하다. 그러나 올바른 방법 패널은 normalize(NormalMatrix × Nlocal)의 결과를 Ncorrect=(-1,2)로 적는다. 이 값은 올바른 방향의 비단위 Vector이며 Normalize 결과는 (-1/sqrt(5),2/sqrt(5))이다. Inverse Transpose를 바로 적용한 값은 (-0.5,1)이다.

Text Consistency: Non-Uniform Scale 자체가 Normal을 망가뜨리는 것이 아니라 잘못된 Transform이 수직 관계를 깨뜨린다는 본문의 핵심은 잘 반영했다. 반면 Normalize 결과 표기는 본문의 Unit Vector 준비 설명과 충돌한다.

Terminology: Inverse Transpose와 Normal Matrix의 의미는 적절하다. M은 Translation을 제외한 선형 Transform으로 명시하면 Position/Normal 구분이 더 정확해진다. 이미지의 '그림 3.5'는 파일의 Fig3_04와 다르며 Section 3.5와 Figure 번호를 혼동한다.

Visual Communication: 원래 상태→변형→잘못된 방법/올바른 방법 비교는 유용하다. 잘못된 방법 패널에도 직각 표시처럼 보이는 작은 사각 기호가 남아 있어 '수직 아님'과 시각적으로 충돌한다.

Issues: Normalize 결과의 수치 오류; Figure 번호 불일치; 잘못된 Normal 패널의 직각 기호.

Recommendation: Inverse Transpose 결과 (-0.5,1), 같은 방향의 예시 (-1,2), 최종 Unit Normal (-0.447,0.894)을 구분한다. 잘못된 방법의 직각 기호를 제거하고 각도 불일치만 표시한다. 파일명과 경로는 유지하며 추후 이미지 내부 Figure 번호를 3.4로 수정한다.

## Fig3_05

Chapter / Section: Chapter 03 / 3.6 Light and View Direction — Chapter03_LightingMathematics.md L832. Figure: Figures/Chapter03/Fig3_05.png

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Point/Spot Light 및 View Direction의 Position 차이와 Normalize 식은 정확하다. Directional Light 패널은 L=normalize(-LightDirection)을 제시하지만 파란 입사 방향이 오른쪽 아래, 빨간 L은 오른쪽 위로 그려져 서로 반대 방향이 아니다. Spot Direction을 가리키는 중앙 점선은 광원 쪽으로 향해 빛의 조사 축 Convention을 명확히 하지 못한다.

Text Consistency: Light Type별 차이, Spot Cone 검사, Surface→Camera 방향, 같은 Space 및 Normalize 조건은 본문과 맞는다. 본문이 강조한 부호 Convention 확인을 Directional 패널의 실제 화살표가 충족하지 못한다.

Terminology: LightDirection을 '고정된 방향'으로만 설명하여 빛의 진행 방향인지 Surface→Light 방향인지 모호하다. 상단 3.6은 Section 번호로 읽을 수 있으나 별도 Figure 3.5 식별자가 없어 Figure/Section 번호 구분이 필요하다.

Visual Communication: 네 유형의 병렬 비교와 Position 차이 도식은 명확하다. Directional의 파란 화살표와 L의 관계가 핵심 수정 대상이다. Cone Angle은 전체 각도인지 반각인지 선언하면 추후 구현 오해를 줄일 수 있다.

Issues: Directional Light 입사 방향과 L의 부호 관계 불일치; Spot Direction 화살표 Convention 불명확; Figure 식별자 누락.

Recommendation: 파란 화살표를 Light Propagation Direction으로 명시하고 빨간 L을 정확한 반대 방향으로 그린다. Spot Direction을 광원에서 조사 영역으로 향하게 하고 L과 구분한다. Section 3.6 표기는 유지하되 Figure 3.5를 별도로 표시한다.

## Fig3_06

Chapter / Section: Chapter 03 / 3.7 Coordinate Space for Lighting — Chapter03_LightingMathematics.md L1075. Figure: Figures/Chapter03/Fig3_06.png

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: N/L/V를 같은 Coordinate Space로 맞추는 원칙과 View Space 대안은 타당하다. 그러나 중앙 패널에서 Camera는 구의 왼쪽 아래에 있고 V는 오른쪽 아래를 향해 Surface→Camera 정의와 모순된다. 하단 Transform (Model Matrix) 하나로 Position과 Normal 모두를 처리하는 흐름은 Non-Uniform Scale에서 Normal Matrix가 필요하다는 직전 Section의 구분을 생략한다.

Text Consistency: 본문은 World Space를 흔한 선택으로 설명하고 같은 Space의 일관성을 핵심으로 둔다. Figure의 '대부분의 Engine' 및 Forward Rendering 일반화는 본문보다 강한 주장이다. 해당 보편성은 Needs Technical Verification이며 이 로컬 문서 대조만으로 확정하지 않는다.

Terminology: World/View/Local Space와 N/L/V 라벨은 일관된다. 상단 3.7은 Section 번호이며 Figure 3.6 식별자는 따로 필요하다. 장문의 영어 상·하단 설명은 한국어 설명문 중심의 문서 규칙에 맞추는 것이 좋다.

Visual Communication: Correct/Incorrect 패널이 같은 화살표와 같은 구체 결과를 반복하고 L의 Space 라벨만 바꿔 실제 기준축 차이나 잘못된 결과를 보여주지 못한다. 중앙 N/L/V도 서로 다른 표면 지점에서 시작해 한 Shading Point의 입력 관계로 읽기 어렵다.

Issues: View Direction과 Camera 위치 불일치; Position/Normal Transform 구분 누락; Mixed Space 비교의 시각적 증거 부족; Engine 보편성 주장 검증 필요.

Recommendation: 하나의 Surface Point에서 N/L/V를 표시하고 V를 실제 Camera로 향하게 한다. Position Transform과 Normal Matrix를 분기해서 보여준다. Mixed Space 패널에는 회전된 기준축 또는 명시적인 수치 예시를 추가한다. World Space를 이 예시의 선택으로 표현하고 Figure 3.6과 Section 3.7을 구분한다.

## Fig4_01

Chapter / Section: Chapter 04 / 4.1 — Chapter04_MaterialArchitecture.md L59

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Geometry/Light/Material의 결합은 정확하다. Emissive를 반사가 아닌 것으로 단정하면 발광과 반사의 병행을 배제한다.

Text Consistency: 동일 Geometry/Light에서 다른 Material 결과를 비교하는 본문과 맞는다.

Terminology: Chapter 명칭 Rendering Fundamentals를 Material Architecture로 통일한다.

Visual Communication: 발광 구의 바닥 조명은 Emission 입력만으로 항상 생기는 결과로 오해될 수 있다.

Issues: Emission과 반사의 배타적 표현; 간접 조명 조건 누락.

Recommendation: Emission은 추가 가능한 자체 방출 성분으로 설명하고 바닥 조명/Bloom의 별도 조건을 표시한다.

## Fig4_02

Chapter / Section: Chapter 04 / 4.2 — Chapter04_MaterialArchitecture.md L238

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Normal Map 비교에서 모든 화살표가 같은 수직 방향이고 표면은 돌출 Geometry처럼 보인다. Roughness 비교에도 요철 변화가 섞여 있다.

Text Consistency: Geometry를 바꾸지 않고 Surface 방향을 조정한다는 설명과 도식이 충돌한다.

Terminology: Base Color=Diffuse Color 요약은 Metallic의 반사 색 역할을 놓친다. Emissive는 0/1 이진 속성이 아니다.

Visual Communication: Property 병렬 구분은 좋으나 각 입력의 효과를 분리한 비교가 필요하다.

Issues: Normal 방향 변화 미표현; Roughness/Normal 효과 혼합; Emission 1=Glow 조건 생략.

Recommendation: 동일 Geometry에서 Normal 화살표 방향만 변경하고, Roughness 비교에서는 Normal을 동일하게 유지한다. Emission 예시 강도와 후처리 조건을 표시한다.

## Fig4_03

Chapter / Section: Chapter 04 / 4.3 — Chapter04_MaterialArchitecture.md L527

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 현재 Pixel UV에서 Sample하는 구조가 명확하다. Normal (0.12,0.85,0.51)이 Encoded RGB인지 Decode된 방향인지 불명확하다.

Text Consistency: Texture를 저장 데이터로 설명하고 현재 지점의 값을 사용하는 본문과 맞는다.

Terminology: 상단 Metallic 부근 문자 손상과 영어 설명문 위주 구성이 있다.

Visual Communication: 저장 데이터→선택 지점→런타임 Sample 대응은 유용하다. Packed Channel은 동일 UV 영역에 겹쳐 저장됨을 보완하면 좋다.

Issues: Normal Encoding 상태 불명확; 문자 손상.

Recommendation: Sample RGB→Decode→Normal의 수치를 구분하고 손상 문자를 수정한다. 한국어 설명과 영어 Technical Term 원칙에 맞춘다.

## Fig4_04

Chapter / Section: Chapter 04 / 4.4 — Chapter04_MaterialArchitecture.md L848

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: UV→Sample→현재 Material Value 및 Filtering의 가중합은 맞다. Mip 선택을 거리만으로 설명해 화면상 Texture footprint 조건이 빠졌다.

Text Consistency: 본문의 현재 Pixel UV와 Texture/Sample 구분을 잘 반영한다.

Terminology: 서문 '값을 값을' 오타와 Normal Sample의 Encoded RGB 표시 누락이 있다.

Visual Communication: Wrap/Mirror에 대칭 Checker를 사용해 차이가 거의 보이지 않는다. 삼각형 UV(0.34,0.62)의 표시는 중앙 아래에 있어 제시된 Vertex UV의 단순 보간 위치와 맞지 않는다.

Issues: UV 예시 지점 대응 부정확; Address Mode 비교 식별성; Mip 조건 단순화.

Recommendation: 삼각형을 affine 예시로 명시하고 UV 지점을 좌측 상단에 맞춰 표시한다. Wrap/Mirror에는 비대칭 패턴을 사용하고 Mip은 footprint에 따른 선택으로 설명한다.

## Fig4_05

Chapter / Section: Chapter 04 / 4.5 — Chapter04_MaterialArchitecture.md L1176

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: sRGB Decode가 Data 0.50을 0.73으로 바꾼다는 도식은 Encode/Decode 방향을 뒤집었다. 또한 Roughness 0.73을 0.50보다 매끄럽게 그린 결과도 Roughness 정의와 반대다.

Text Consistency: 본문의 sRGB Sampling 시 Decode 설명과 패널의 수치 변화가 충돌한다.

Terminology: 곡선의 Encode/Decode 구분과 Input/Output Space를 명시해야 한다. 정확한 sRGB와 Gamma 2.2 근사는 구분한다.

Visual Communication: 잘못된 수치와 렌더 비교가 같은 오류를 강화한다. sRGB On Sample 뒤 SRGBToLinear 연결은 중복 Decode로 읽힐 수 있다.

Issues: Encode/Decode 역전; Roughness 변화 방향 역전; 중복 변환처럼 보이는 Graph.

Recommendation: sRGB로 잘못 읽은 Data는 Decode 후 원래 0.5보다 작아지는 예시로 수정한다. Encode/Decode 곡선을 분리하고 자동 Decode 후 수동 Decode를 반복하지 않는 흐름으로 고친다.

## Fig4_06

Chapter / Section: Chapter 04 / 4.6 — Chapter04_MaterialArchitecture.md L1524

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: RGB×2−1과 Flat Normal 예시는 맞다. Object Space를 World 방향 및 Mesh 회전 시 고정으로 설명해 Object/World Space를 혼동한다. TBN 변환 뒤 Normalize가 생략되어 있다.

Text Consistency: 본문의 Surface마다 구성되는 Tangent Space를 'Mesh Local 방향'으로 줄여 Object Local과 혼동시킨다.

Terminology: Unreal의 기본을 OpenGL 방식이라고 단정하는 표는 Needs Technical Verification. 본문 근거 없이 엔진 Convention을 확정하지 않는다. TBNTrasform 오타와 T/B 중복 라벨이 있다.

Visual Communication: +Y와 +Z 예시 화살표가 모두 위쪽이라 방향 차이를 보여주지 못한다.

Issues: Object/World Space 혼동; 엔진 Convention 검증 필요; Basis 예시 식별성.

Recommendation: Object Space는 Object 기준 방향이며 World 변환이 필요함을 명시한다. 엔진/제작 도구 Convention은 확인된 설정으로 표시한다. 동일 3축 위에 +X/+Y/+Z를 구분하고 Normalize 단계를 추가한다.

## Fig4_07

Chapter / Section: Chapter 04 / 4.7 — Chapter04_MaterialArchitecture.md L1956

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Parent Logic과 Instance Override 구분은 맞다. Static Switch를 포함한 모든 Parameter가 구조를 바꾸지 않고 실시간 변경 가능하다는 요약은 컴파일 시 분기라는 같은 Figure 설명과 충돌한다.

Text Consistency: 재사용 및 Logic/Data 분리의 본문 목적과 일치하나 Static/Runtime 예외를 분리해야 한다.

Terminology: Scalar/Vector/Texture/Static Switch 표기는 명확하다.

Visual Communication: Parent→세 Instance 분기는 이해하기 쉽고 Graph의 Texture×Tint 흐름도 적절하다.

Issues: Runtime 조절 가능 범위와 Static Parameter의 일반화.

Recommendation: 실시간 변경 설명을 비정적 Parameter 및 지원되는 Instance 사용으로 한정하고 Static Switch는 별도 Variant/컴파일 조건임을 명시한다.

## Fig4_08

Chapter / Section: Chapter 04 / 4.8 — Chapter04_MaterialArchitecture.md L2373

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Lighting Inputs의 L과 V가 각각 Light/Camera에서 Surface를 향하여 본문의 Surface→Light/Camera 정의와 반대다.

Text Consistency: 상단 독립 입력 합류는 맞지만 하단 요약은 Mesh→Texture/Parameters→Normal Decode→Material→Lighting Inputs라는 단일 직렬 흐름으로 만들어 독립 입력 관계를 뒤집는다.

Terminology: Normal Map Path는 Height와 구분되지만 Sample/Normalize 및 TBN의 Mesh Basis 입력이 생략되어 있다.

Visual Communication: Sampled Value RGBA를 여러 Texel 색 격자로 그려 하나의 현재 Pixel 값인지 모호하다.

Issues: L/V 화살표 반전; 입력 합류의 직렬화; Sample 값과 Texture 격자 혼동.

Recommendation: L/V를 Surface에서 출발시키고 Mesh UV+Texture→Sample, Parameter→Property, Normal Sample+Basis→Lighting Normal의 분기를 구성한다. Lighting Data는 별도 입력으로 합류시킨다. Sample 결과는 단일 RGBA tuple로 표시한다.

## Fig5_01

Chapter / Section: Chapter 05 / 5.1 Reflection — Chapter05_Reflection_BRDF.md L32

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 입사→표면→반사의 화살표는 이상적인 거울 반사 예시로 타당하다.

Text Consistency: 여러 Material의 Reflection 개요에 삽입되어 있으나 단일 방향 반사만 보여준다.

Terminology: Incoming/Outgoing/Normal은 명확하다.

Visual Communication: 읽기 순서와 화살표는 좋지만 모든 Reflection이 하나의 방향으로만 나간다는 인상을 줄 수 있다.

Issues: Specular 이상화 조건 누락.

Recommendation: 이상적인 매끄러운 Surface의 반사 예시라는 캡션을 추가한다.

## Fig5_02

Chapter / Section: Chapter 05 / 5.2 Surface Normal — Chapter05_Reflection_BRDF.md L168

Status: Match

Recommended Action: Keep

Technical Accuracy: 표면 지점에서 수직으로 향하는 N을 정확히 나타낸다.

Text Consistency: Surface 방향 기준인 Normal 설명에 직접 대응한다.

Terminology: Normal(N), Surface 표기가 일치한다.

Visual Communication: 한 개념만 보여주는 간결한 도식으로 판독이 명확하다.

Issues: 확인된 실질적 불일치 없음.

Recommendation: 유지한다.

## Fig5_03

Chapter / Section: Chapter 05 / 5.3 Reflection Vector — Chapter05_Reflection_BRDF.md L345

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 표면으로 향하는 I에 대해 R=I−2(I·N)N은 Unit N 조건에서 맞고 화살표도 일치한다.

Text Consistency: 본문은 L과 R=2(N·L)N−L을 사용하므로 I=−L 관계 없이는 부호가 다른 두 식으로 읽힌다. 본문의 Incoming Light Direction 용어도 함께 주의해야 한다.

Terminology: Incident I와 Surface→Light L의 Convention 구분 필요.

Visual Communication: Normal 기준 입사/반사 각도 대칭은 명확하다.

Issues: 본문 L과 그림 I의 대응 및 Unit N 조건 누락.

Recommendation: I는 빛의 진행 방향, L=−I는 Surface→Light임을 표시하고 |N|=1을 명시한다.

## Fig5_04

Chapter / Section: Chapter 05 / 5.4 Lambert — Chapter05_Reflection_BRDF.md L559

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 각도별 cos 수치와 clamp 식은 맞으나 Brightness 표의 1.0 막대가 가장 검고 낮은 값일수록 밝아져 밝기 표현이 역전된다.

Text Consistency: 정면일수록 밝다는 본문과 색상 표가 충돌한다.

Terminology: N/L은 Unit Vector, Ld는 다른 인자를 생략한 방향 계수임을 명시하면 정확하다.

Visual Communication: 막대 길이는 감소하지만 명도는 증가해 서로 반대 신호를 준다.

Issues: Brightness 명도 역전.

Recommendation: 값 1은 흰색, 0은 검정으로 통일하거나 일정 색의 길이 막대만 사용한다.

## Fig5_05

Chapter / Section: Chapter 05 / 5.5 Phong — Chapter05_Reflection_BRDF.md L743

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: R·V의 거듭제곱과 Highlight 관계는 맞다. L이 표면으로 향해 앞의 Lambert L과 부호 Convention이 달라진다.

Text Consistency: View에 따른 Specular 설명을 반영한다.

Terminology: 입사 방향을 I=−L로 구분하고 Unit R/V 조건을 명시해야 한다.

Visual Communication: V가 다른 Surface Point에서 출발해 R과 같은 지점의 방향 비교로 읽기 어렵다.

Issues: L Convention 및 Shading Point 불일치.

Recommendation: L은 Surface→Light로 표시하거나 입사 화살표를 I로 바꾸고 R/V를 같은 점에서 시작시킨다.

## Fig5_06

Chapter / Section: Chapter 05 / 5.6 Half Vector — Chapter05_Reflection_BRDF.md L876

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: H=normalize(L+V) 식은 Unit L/V 조건에서 맞지만 H 화살표가 각도의 이등분선이 아니다. 그림에서는 L-H 간격이 H-V보다 훨씬 크다.

Text Consistency: 정확히 중간 방향이라는 본문과 도식이 직접 충돌한다.

Terminology: Half Vector 명칭은 맞고 입력 Unit Vector 조건 보완이 필요하다.

Visual Communication: 각도 호가 동일 각도처럼 표시되지만 화살표가 이를 지지하지 않는다.

Issues: Half Vector 각도 이등분 실패.

Recommendation: L/V를 동일 길이 Unit Vector로 그리고 두 방향의 실제 이등분선에 H를 배치한다.

## Fig5_07

Chapter / Section: Chapter 05 / 5.7 Blinn-Phong — Chapter05_Reflection_BRDF.md L1071

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: N·H 식은 맞지만 H가 L/V의 이등분 방향에 놓이지 않는다. Phong 대비 비용 우위는 구현/입력 조건 없이 보장할 수 없어 Needs Technical Verification.

Text Consistency: N과 H의 일치가 핵심이라는 본문은 반영되지만 잘못된 H 위치가 계산 이해를 방해한다.

Terminology: Shininess 증가의 집중 효과는 적절하다. 동일 exponent의 두 모델이 동일 결과라는 의미는 피해야 한다.

Visual Communication: 비교 삽화의 N/H도 다른 원점에서 시작하고 Highlight 위치가 별도 지점이다.

Issues: H 방향 오류; 비용 일반화; 동일 지점 비교 불명확.

Recommendation: Unit L/V 이등분선으로 H를 수정하고 모든 방향을 같은 지점에 배치한다. 비용은 조건부로 설명한다.

## Fig5_08

Chapter / Section: Chapter 05 / 5.8 Reflection Model 한계 — Chapter05_Reflection_BRDF.md L1205

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: PBR을 Cook-Torrance라는 단일 모델과 동일시하며 모든 현실 Material을 정확하게 표현한다고 단정한다. Lambert(1970), Microfacet(1980s) 연대는 본문 근거가 없으며 Needs Technical Verification.

Text Consistency: 본문의 학습 순서를 실제 역사 연표로 확장했다. 초기 모델의 한계라는 방향은 맞지만 PBR의 한계를 지운다.

Terminology: PBR은 접근 방식이며 Cook-Torrance는 그 안에서 사용하는 반사 모델로 구분해야 한다.

Visual Communication: 연속 화살표가 이전 모델의 완전 폐기/대체로 읽힌다.

Issues: PBR/모델 동일시; 검증되지 않은 연대; 정확성과 Energy Conservation 무조건 단정.

Recommendation: 연대를 제거한 개념 학습 순서로 표시한다. PBR 안의 Diffuse/Specular 모델 관계를 보여주고 보존 조건과 근사 한계를 명시한다.

## Fig5_09

Chapter / Section: Chapter 05 / 5.9 Microfacet Theory — Chapter05_Reflection_BRDF.md L1420

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 통계적 Microfacet 개념은 맞으나 하나의 평평한 Facet 입사점에서 여러 반사 화살표를 방출해 각 Facet의 거울 반사 가정을 위반하는 듯 보인다.

Text Consistency: 각 Microfacet이 작은 거울이라는 본문과 국소 다방향 방출 도식이 충돌한다.

Terminology: Macro Surface와 Microfacet 구분은 명확하다.

Visual Communication: 확대 구조는 좋지만 반사 화살표가 Facet 기울기/Normal에 대응하지 않는다.

Issues: 단일 Facet 반사와 Facet 분포의 반사 확산 혼동.

Recommendation: 각 Facet마다 하나의 입사/반사 쌍과 Normal을 표시하고 서로 다른 Facet의 방향 분포가 전체 반사 확산을 만든다고 연결한다.

## Fig5_10

Chapter / Section: Chapter 05 / 5.10 Cook-Torrance — Chapter05_Reflection_BRDF.md L1606

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: BRDF는 주어진 입출사 방향의 반사 응답인데 여러 반사를 하나의 Final Reflected Direction으로 합치는 도식은 평균 방향 계산으로 오해시킨다. 입사 진행 방향을 L로 그려 h=(L+V)/|L+V|의 outward Convention과 충돌한다.

Text Consistency: D/G/F의 역할을 소개하는 본문에 비해 실제 각 역할의 연결은 약하고 방향 합성 그림이 중심이다.

Terminology: Final Reflected Direction을 Specular BRDF/반사 기여로 바꾸어야 한다.

Visual Communication: Facet 아래로 모이는 깔때기와 위쪽 화살표는 데이터 출력과 광선 경로를 혼합한다.

Issues: BRDF 응답과 최종 방향 혼동; L 부호 불일치.

Recommendation: L/V를 입력으로 받아 D/G/F 및 분모를 거쳐 Specular BRDF를 얻는 흐름으로 재구성한다. 광선 도식은 별도 inset으로 분리한다.

## Fig5_11

Chapter / Section: Chapter 05 / 5.11 Roughness — Chapter05_Reflection_BRDF.md L1816

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Roughness가 높이보다 방향 분포 폭과 연결된다는 설명은 맞다. Low Roughness에 급경사 삼각형의 양쪽 면을 반복해 좁은 Normal 분포로 읽기 어렵다.

Text Consistency: 좁고 선명한 반사와 넓고 부드러운 반사 비교는 본문과 일치한다.

Terminology: Roughness/Orientation Spread/Highlight Size는 명확하다.

Visual Communication: 반사 화살표가 표시된 Facet 기울기와 대응하지 않아 상단 설명을 기하적으로 뒷받침하지 못한다.

Issues: Facet 방향 분포와 반사 광선의 대응 부족.

Recommendation: Low Roughness에는 거의 같은 방향의 평평한 Facet을 그리고 Normal과 반사 쌍을 대응시킨다.

## Fig5_12

Chapter / Section: Chapter 05 / 5.12 NDF — Chapter05_Reflection_BRDF.md L1999

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 좁고 높은 분포/넓고 낮은 분포 비교는 개념적으로 유용하다. 그러나 Roughness 증가 시 특정 h에서 D가 항상 작아진다는 설명은 중심부 밖에서는 성립하지 않는다.

Text Consistency: 본문은 Normal이 정규분포를 의미하지 않는다고 명시하지만 범례는 '정규분포 함수'라고 번역한다.

Terminology: Normal Distribution Function은 Microfacet Normal 방향 분포이며 정규분포와 다르다. 밀도와 확률을 같은 것으로 쓰지 않는다.

Visual Communication: 위쪽의 반사광 분포와 아래 Normal 분포를 직접 동일시할 수 있어 대상 구분이 필요하다.

Issues: 정규분포 오역; 임의 h에서 D 감소 일반화; Normal/반사 방향 분포 혼동.

Recommendation: 범례를 Normal 방향 분포 함수로 수정한다. h가 N에 가까운 경우의 peak 비교임을 명시하고 개념 곡선임을 표시한다.

## Fig5_13

Chapter / Section: Chapter 05 / 5.13 Geometry Function — Chapter05_Reflection_BRDF.md L2238

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Shadowing=입사 경로, Masking=관찰 경로 구분은 맞지만 차단 경로가 실제 장애물에 닿아 멈추는 모습을 보여주지 않는다. 일부 Shadowed 점선은 입사 반대 방향으로 향한다.

Text Consistency: 다른 Facet 때문에 차단된다는 본문을 화살표가 입증하지 못한다.

Terminology: 하단 D를 '빛의 수'로 표현한 것은 Microfacet 방향 분포와 다르다.

Visual Communication: 확대와 색 구분은 좋으나 Masked 점선이 Facet 위로 빠져나가 가려짐이 보이지 않는다.

Issues: 실제 차단 교차점 누락; D 의미 오류.

Recommendation: 목표 Facet과 차폐 Facet을 구분하고 경로 교차점에서 광선을 끊어 차단 표시를 넣는다. D는 Normal 방향 분포로 수정한다.

## Fig5_14

Chapter / Section: Chapter 05 / 5.14 Fresnel — Chapter05_Reflection_BRDF.md L2387

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 입사각에 따른 반사율이라는 원리는 맞지만 두 패널의 입사광 각도가 같은데 View만 바꾸고 입사각 증가로 설명한다. Microfacet Fresnel의 기준인 h와 macro N도 구분되지 않는다.

Text Consistency: 본문의 Fresnel 원리를 View 변경만으로 반사 광선이 바뀌는 도식으로 단순화했다.

Terminology: 입사각(View Angle) 동의어 처리는 조건 없이 부정확하다. 상단 Reflectance 문자에 중첩/깨짐이 있다.

Visual Communication: Normal/Grazing 비교에서 실제 입사/반사 대칭이 유지되지 않는다.

Issues: 입사각과 관찰각 혼동; 광선 경로와 반사 법칙 불일치; 문자 손상.

Recommendation: 매끄러운 경계면 예시에서는 입사각과 대칭 반사 방향을 함께 바꾼다. Microfacet 예시에는 h와 L·h 또는 V·h를 표시하고 반사율과 최종 밝기를 구분한다.

## Fig6_01

Chapter / Section: Chapter 06 / 6.1 — Chapter06_ModernRealtimeRendering.md L34

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Direct→Indirect→IBL→Reflection→HDR를 의무적인 연속 실행 Stage로 그려 중첩되는 조명 기법과 HDR 값 표현을 동일 층위로 취급한다. BRDF는 Lighting 평가에 사용되며 별도 선행 실행 Stage가 아니다.

Text Consistency: 본문의 단순화된 순서를 그대로 반영하지만 기술별 의존 관계를 오해하게 한다.

Terminology: Rendering Pipeline Stage와 Technique/Data Representation을 구분해야 한다.

Visual Communication: 단일 세로 흐름이 모든 Scene에서 같은 처리 순서로 읽힌다.

Issues: 기술/입력/표현 형식의 Stage 혼합.

Recommendation: Material/Geometry/Light 입력→Direct 및 환경/간접 기여 평가→HDR 합성→Tone Mapping/출력 변환으로 분기와 합류를 표현한다.

## Fig6_02

Chapter / Section: Chapter 06 / 6.1 — Chapter06_ModernRealtimeRendering.md L42

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: BRDF를 전체 Pipeline의 일부로 강조하는 목적은 맞지만 Material(BRDF)을 Direct/Indirect Lighting 이전에 끝나는 Stage로 표현한다.

Text Consistency: Chapter 05와 06의 연결은 전달되나 본문의 직렬화 문제를 반복한다.

Terminology: Material 전체와 BRDF는 동의어가 아니다.

Visual Communication: 주황색 강조는 명확하나 BRDF가 각 Lighting 기여 계산에 사용되는 연결이 없다.

Issues: BRDF 적용 위치 오해; Material/BRDF 동일시; 고정 Stage 직렬화.

Recommendation: BRDF를 Material이 제공하는 반사 응답으로 표시하고 Lighting 평가로 들어가는 연결을 그린다. Chapter 범위 강조는 유지한다.

## Fig6_03

Chapter / Section: Chapter 06 / 6.2 Direct Lighting — Chapter06_ModernRealtimeRendering.md L183

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Light→Surface의 직접 경로는 정확하다. 환경광/IBL을 정의상 무조건 Direct에서 제외하는 것은 조명 경로와 표현 기법을 혼동한다.

Text Consistency: 해당 본문의 분류와는 일치하나 이 Chapter의 편의상 분류임을 밝혀야 한다.

Terminology: BRDF를 재질 전체와 같게 쓰는 Surface 목록은 범위를 좁히는 것이 좋다.

Visual Communication: 다중 Bounce 예시는 Surface에서 밖으로 나가는 두 화살표만 있어 여러 번 반사되어 도달하는 경로를 보여주지 않는다.

Issues: 환경광의 무조건적 간접 분류; 다중 Bounce 경로 미표현.

Recommendation: 환경/IBL은 별도 취급하는 이 문서의 구성임을 표시한다. Bounce 예시는 Light→벽→바닥→대상처럼 중간 Surface를 그린다.

## Fig6_04

Chapter / Section: Chapter 06 / 6.3 — Chapter06_ModernRealtimeRendering.md L281

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 다른 Surface를 거쳐 오는 간접광의 핵심은 맞다. Direct 경로가 창문이 아닌 불투명한 벽을 통과하는 듯 보이며 Floor에서 나가는 화살표 일부가 바닥과 평행하다.

Text Consistency: 벽→바닥→주변의 Bounce 개념을 반영한다.

Terminology: Direct/Indirect 구분은 명확하다.

Visual Communication: 실내 사진 위 경로가 창문/벽의 실제 위치와 맞지 않아 광선 경로 추적이 어렵다.

Issues: Direct 경로와 개구부의 대응 부족.

Recommendation: 광선을 열린 창문을 통해 첫 Surface에 도달하도록 옮기고 Floor의 반사 방향은 표면 위 반구로 표시한다.

## Fig6_05

Chapter / Section: Chapter 06 / 6.4 IBL — Chapter06_ModernRealtimeRendering.md L359

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Environment Map이 Diffuse/Specular 조명에 쓰이는 구분은 맞다. Diffuse IBL을 반드시 여러 번 반사된 빛으로 설명하고 Direct→Indirect→IBL→Reflection을 직렬 Stage로 그린 것은 부정확하다.

Text Consistency: 두 IBL 역할은 본문과 맞지만 본문 이상의 다중 Bounce 조건을 추가했다.

Terminology: IBL은 조명 데이터/계산 기법이며 다중 Bounce와 동의어가 아니다.

Visual Communication: 중앙 양방향 화살표가 입력 환경 빛과 출력 반사를 구분하지 않는다.

Issues: Diffuse IBL과 다중 Bounce 혼동; 고정 Stage 직렬화.

Recommendation: Environment Map→Diffuse/Specular IBL의 병렬 기여로 표현하고 입사와 출력은 다른 범례로 구분한다.

## Fig6_06

Chapter / Section: Chapter 06 / 6.5 Reflection — Chapter06_ModernRealtimeRendering.md L441

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Roughness 증가에 따른 반사 선명도 변화는 맞다. Reflection을 계산한 뒤 BRDF Shading을 별도 수행하는 고정 단계는 Specular IBL에서 BRDF를 사용한다는 관계를 왜곡한다.

Text Consistency: 이 Section의 환경 반사 범위와는 일치한다.

Terminology: Reflection(Specular IBL)은 이 그림의 구현 예시로 한정해야 한다.

Visual Communication: 입사 화살표 일부가 환경 방향으로 되돌아가 범례와 다르고 모든 반사 화살표가 Viewer에 연결되지 않는다.

Issues: BRDF 적용 위치 및 IBL 관계 왜곡; 광선 방향 혼합.

Recommendation: 환경 Sample과 Material BRDF로 반사 기여를 계산해 HDR 조명 합성에 넣는 흐름으로 바꾸고 입사 화살표를 Surface 방향으로 통일한다.

## Fig6_07

Chapter / Section: Chapter 06 / 6.6 HDR — Chapter06_ModernRealtimeRendering.md L527

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: HDR Environment Map=입력, HDR Rendering=계산, Tone Mapping=출력 변환 구분은 정확하다. 하단은 HDR을 별도 후속 단계로 중복 배치한다.

Text Consistency: 본문 핵심 구분을 잘 전달한다.

Terminology: 0~10000+는 고정 HDR 정의가 아닌 예시 수치로 표시해야 한다.

Visual Communication: 구체를 렌더한 다음 모니터에는 원래 환경 사진이 나와 계산 결과 전달 관계가 약하다.

Issues: HDR 계산 범위와 별도 단계 중복; 결과 이미지 연속성.

Recommendation: HDR은 조명 계산 영역 전체를 감싸는 표기로 통일하고 최종 화면은 같은 Scene 결과로 맞춘다.

## Fig6_08

Chapter / Section: Chapter 06 / 6.7 Tone Mapping — Chapter06_ModernRealtimeRendering.md L625

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: SDR 0~1 정규화 값에 cd/m² 단위를 붙여 실제 휘도와 혼동한다. HDR 데이터 자체가 포화되어 손실된 것처럼 설명하지만 손실은 잘못된 표시/클리핑 단계와 구분해야 한다.

Text Consistency: 넓은 범위를 표시 가능 범위로 압축한다는 본문 방향은 맞다.

Terminology: SDR은 1 cd/m² 이하라는 의미가 아니며 상대 코드 값과 물리 단위를 분리해야 한다.

Visual Communication: 전후 풍경의 구름/광원 형상까지 달라져 동일 HDR 데이터의 Tone Mapping 전후 비교로 신뢰하기 어렵다.

Issues: 휘도 단위 오류; HDR 데이터와 표시 손실 혼동; 비교 Scene 변화.

Recommendation: 출력 축을 Normalized SDR Value로 수정하고 같은 HDR 원본의 변환만 비교한다. 클리핑 전 데이터 보존과 화면 표시를 분리한다.

## Fig6_09

Chapter / Section: Chapter 06 / 6.8 Color Space — Chapter06_ModernRealtimeRendering.md L706

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Color/Data Texture 구분과 Linear 계산→Tone Mapping→sRGB 출력은 SDR 예시로 적절하다. 하단 HDR Rendering까지 밝기 변환으로 묶은 표기는 HDR 계산과 출력 압축을 혼동한다.

Text Consistency: 본문 Texture 설정 표와 일치한다. '대부분의 Rendering 문제는 Texture Import'라는 주장은 본문보다 강하고 근거가 없다.

Terminology: 엔진 설정 표는 해당 버전/Importer 조건에 대한 Needs Technical Verification으로 남긴다.

Visual Communication: 중앙 4단계와 좌측 데이터 분류는 명확하지만 전체 하단 직렬 Pipeline은 앞선 문제를 반복한다.

Issues: HDR/출력 변환 grouping; 근거 없는 문제 원인 일반화.

Recommendation: 밝기 범위 변환 괄호는 Tone Mapping에만 적용하고 Import 설정은 확인할 원인 중 하나로 표현한다. SDR 출력 예시임을 명시한다.

## Fig6_10

Chapter / Section: Chapter 06 / 6.9 Summary — Chapter06_ModernRealtimeRendering.md L851

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Lighting→Reflection/IBL→BRDF→HDR 순서를 의무 Stage로 반복해 BRDF 평가와 HDR 계산의 범위를 왜곡한다.

Text Consistency: 해당 Summary와 일치하지만 Fig6_01/02의 BRDF 선행 순서와도 달라 Chapter 안의 처리 순서가 일관되지 않는다.

Terminology: Lighting은 이 Chapter 내용인데 범례 Previous Chapters 색상이며 BRDF는 반대로 This Chapter 색상이다.

Visual Communication: 세로 읽기 순서는 명확하지만 잘못된 층위와 범위 분류가 강하게 전달된다.

Issues: 입력/기법/값 범위의 혼합; Chapter 범례 불일치.

Recommendation: Geometry/Material/Lighting 입력과 기여 평가를 HDR 영역 안에서 합류시키고 출력 변환만 후단에 둔다. Chapter 범례를 실제 범위와 맞춘다.

## Fig7_01

Chapter / Section: Chapter 07 / 7.1 — Chapter07_Stylized Rendering.md L44

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 표현 목표의 차이를 설명하는 비교는 타당하며 PBR 폐기를 요구하지 않는다.

Text Consistency: 본문의 공유 Pipeline과 필요한 요소만 변형한다는 연결이 그림에는 빠져 분리된 기술처럼 읽힐 수 있다.

Terminology: 푸터 ASF가 Anime Shader Framework로 표기되어 현재 Ari’s Shader Framework와 다르다.

Visual Communication: 양방향 점선에 관계 이름이 없다.

Issues: 이전 ASF 명칭; 공통 기반 관계 미표시.

Recommendation: 공유 Lighting/HDR/Color Space 기반을 명시하고 푸터 명칭을 통일한다.

## Fig7_02

Chapter / Section: Chapter 07 / 7.2 Diffuse — Chapter07_Stylized Rendering.md L152

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: clamped cosine과 Threshold의 연속/단계 응답 비교는 맞다. 구 전체를 하나의 Light-Normal 각도로 표시한 예시는 지점별 Normal 차이를 생략한다.

Text Consistency: Lambert 결과를 재사용하는 ASF 흐름이 그림에는 직접 연결되지 않았다.

Terminology: 각도는 Surface→Light와 N 사이임을 명시하면 입사 화살표와 혼동을 줄인다.

Visual Communication: Toon 구의 띠 안에도 Gradient가 남아 이진 응답 그래프와 정확히 대응하지 않는다.

Issues: 지점 응답과 구 전체 결과 혼동; Threshold 결과 내 Gradient.

Recommendation: 특정 Shading Point를 표시하고 Lambert→Threshold/Ramp 경로를 추가한다. 예시의 추가 조명 성분을 밝히거나 순수 이진 결과를 사용한다.

## Fig7_03

Chapter / Section: Chapter 07 / 7.3 Specular — Chapter07_Stylized Rendering.md L246

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 연속 Specular를 명확한 Highlight 영역으로 변형하는 비교는 적절하다. 곡선은 전체 Cook-Torrance의 정확한 결과보다 개념 곡선으로 보아야 한다.

Text Consistency: Specular를 버리지 않고 응답을 재해석하는 본문을 보완하는 비교다.

Terminology: '하프 벡터와의 각도'는 어떤 Vector와 H인지 빠져 있다. N-H 각도라면 명시해야 한다.

Visual Communication: 크기 변화 예시는 이해하기 쉽다. View 화살표는 Camera→Surface이므로 V Convention을 표시하면 좋다.

Issues: 곡선 축 정의 및 정규화 기준 누락.

Recommendation: 개념 응답 곡선으로 표시하고 N-H 각도, 고정 Light/View 조건, 밝기 정규화 여부를 명시한다.

## Fig7_04

Chapter / Section: Chapter 07 / 7.4 Shadow — Chapter07_Stylized Rendering.md L390

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: PBR=Soft Shadow, Stylized=Hard Shadow라는 구분은 물리 기반 조명도 작은 광원에서 선명한 그림자를 만들 수 있다는 점을 배제한다. NdotL 명암과 Cast Shadow Visibility가 섞여 있다.

Text Consistency: 본문의 일반화를 반복하며 ASF의 Diffuse 재구성으로 바닥 Cast Shadow까지 생성되는 듯 보인다.

Terminology: Light 감쇠, Visibility, Shadow 경계는 별도 개념이다.

Visual Communication: 구 표면 명암과 바닥 그림자를 함께 바꾸어 제어 대상이 불명확하다.

Issues: Soft/Hard와 PBR/NPR 동일시; Diffuse와 Cast Shadow 혼동.

Recommendation: 고정된 광원 크기의 Visibility 예시와 그 결과의 Stylized Remap을 비교한다. NdotL 기반 Shading Band는 별도 그림으로 구분한다.

## Fig7_05

Chapter / Section: Chapter 07 / 7.5 Rim — Chapter07_Stylized Rendering.md L532

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 그래프 x축이 시야각(N·V)인데 degree와 -90° 정면을 사용한다. N·V는 Scalar이고 정면 각도는 0°이다. Fresnel만으로 무조건 밝은 Rim이 생긴다는 표현도 입사 조명 조건을 생략한다.

Text Consistency: 형태 강조용 Rim 제어는 본문과 맞지만 물리 Fresnel과 인위적 Rim Mask의 차이가 흐려진다.

Terminology: 각도 θ와 dot(N,V)를 구분해야 한다.

Visual Communication: 구 전체를 하나의 시야각으로 나열해 지점별 Normal 차이를 생략한다.

Issues: 각도/dot 축 혼용; 정면 각도 오류; 반사율과 밝기 혼동.

Recommendation: θ=0~90° 또는 N·V=1~0 중 하나로 축을 통일하고, Fresnel 반사율과 Rim Mask→Color/Intensity의 역할을 분리한다.

## Fig7_06

Chapter / Section: Chapter 07 / 7.6 Hair — Chapter07_Stylized Rendering.md L674

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 물리적 Fiber 상호작용과 제어된 Highlight 비교는 목적에 맞다. 단면 inset의 굴절/산란 화살표는 실제 연속 광경로가 아니라 분리된 표식이다.

Text Consistency: 개념 비교에 집중하고 심화 구현을 별도 장으로 넘기는 본문 범위와 일치한다.

Terminology: 밝기 그래프의 Strand 방향 각도는 Light/View 중 기준 대상이 명시되지 않았다.

Visual Communication: Hair Clump 결과와 Highlight 확대 비교는 유용하다.

Issues: 단면 광경로의 의미 및 곡선 기준 불명확.

Recommendation: 물리 모델의 실제 곡선이 아닌 개념 비교임을 표시하고 각도 기준을 정의한다. 굴절/내부 반사/출사 경로를 연결하거나 현상 아이콘으로 명시한다.

## Fig7_07

Chapter / Section: Chapter 07 / 7.7 Face — Chapter07_Stylized Rendering.md L826

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 얼굴 전용 Mask와 Light 정보를 이용한 Shadow 제어는 타당하다. PBR Diffuse/Specular/SSS를 분리한 듯한 확대 사진은 성분별 렌더가 아닌 일반 피부 이미지로 보인다.

Text Consistency: 캐릭터 인상을 유지하도록 Shadow를 제어한다는 본문을 반영한다.

Terminology: 캐릭터 기준 광원 고정과 Yaw만 변경이라는 조건은 World 고정인지 Head 상대 고정인지 명확히 해야 한다.

Visual Communication: 두 쪽 Geometry/얼굴 비례가 달라 순수 Lighting 비교보다는 스타일 결과 예시다.

Issues: 통제 조건 모호; 성분 분해 이미지 근거 부족.

Recommendation: 스타일 예시임을 명시하고 광원 기준 Space를 지정한다. 성분 inset은 실제 분리 출력 또는 개념 설명으로 교체한다.

## Fig7_08

Chapter / Section: Chapter 07 / 7.8 Outline — Chapter07_Stylized Rendering.md L957

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 확장 Mesh의 Back Face 및 Depth/Normal 기반 검출 설명은 타당하다. Normal Expansion은 Inverted Hull 구현 방식과 겹치며 Edge Detection은 Screen Space Outline에서 사용하는 연산이다.

Text Consistency: 본문의 네 항목 목록을 따르나 독립된 네 기술로 보이는 층위 문제를 반복한다.

Terminology: PBR에서는 Outline을 쓰지 않는다는 문장은 물리 기반 Material과 추가 Outline의 병행을 배제한다.

Visual Communication: OFF 예시에도 내부/외곽 선이 남아 추가 Outline 효과가 약하게 보인다.

Issues: 중첩 기술의 동일 층위; PBR/Outline 배타성.

Recommendation: Geometry 방식→Normal Expansion/Inverted Hull, Screen Space 방식→Depth/Normal Edge Detection으로 묶는다. PBR과 결합 가능한 별도 표현 효과로 설명한다.

## Fig7_09

Chapter / Section: Chapter 07 / 7.9 Core Techniques — Chapter07_Stylized Rendering.md L1122

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 이미 이진화된 Threshold 결과를 Smoothstep에 넣어 부드러운 Gradient를 복원하는 듯한 화살표는 잘못된 흐름이다. Smoothstep은 원래 연속 입력과 두 Edge 값에 적용해야 한다.

Text Consistency: 본문의 Threshold 주변을 부드럽게 전환한다는 목적은 맞지만 그림은 사후 Blur처럼 보인다.

Terminology: Ramp Texture는 입력 밝기를 좌표로 Sample하는 저장 자원이며 입력값으로 Texture 자체를 만드는 것은 아니다.

Visual Communication: 적용 예시 분류는 좋지만 Ramp의 Input→Texture 화살표에 Sampling이 없다.

Issues: Threshold 후 Gradient 복원 오해; Ramp Sample 단계 누락.

Recommendation: 같은 연속 입력을 Step와 Smoothstep에 각각 넣는 병렬 비교로 수정한다. Scalar→Ramp UV, Ramp Texture→Sample→현재 Color를 표시한다.

## Fig8_01

Chapter / Section: Chapter 08 / 8.0.1 — Chapter08.0_PreparingTheASFProject.md L34

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 개발 순서 도식으로 Module 실행 Stage와 구분되며 구성 흐름은 적절하다.

Text Consistency: 본문은 Ch8~10 개발 로드맵을 소개하지만 Figure는 Ch8 내부 8.0~8.10만 표시한다. 현재 Foundation Ch9의 실제 주제와도 본문의 예고가 다르다.

Terminology: Anime Shader Framework를 현행 ASF 명칭과 통일할 필요가 있다.

Visual Communication: Emission에서 다음 줄 Material Layer로 이어지는 연결이 없다.

Issues: 본문 로드맵 범위와 Figure 범위 불일치; 줄 연결 누락.

Recommendation: Ch8 내부 개발 순서임을 캡션에 명시하고 8→9 연결을 추가한다. 현행 Foundation 목차 기준으로 로드맵 설명을 정리한다.

## Fig8_02

Chapter / Section: Chapter 08 / 8.0.2 — Chapter08.0_PreparingTheASFProject.md L95

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Framework Asset과 StarterContent를 분리하는 구조는 타당하며 폴더 목록은 본문과 맞는다.

Text Consistency: UE5.8/Deferred/DX12 등은 문서의 지정 환경과 일치한다. 실제 지원 설정은 이 Figure만으로 확인하지 않는다.

Terminology: 영어 설명문을 한국어 중심으로 통일하고 Ch8~10 확장 예고는 현행 목차와 맞춰야 한다.

Visual Communication: Content/와 Content/StarterContent/를 형제 범주처럼 배치해 StarterContent가 Content 하위라는 포함 관계가 흐려진다.

Issues: 폴더 포함 관계 및 오래된 Chapter 예고.

Recommendation: Content를 공통 부모로 두고 ASF/와 StarterContent/를 형제 폴더로 표시한다.

## Fig8_03

Chapter / Section: Chapter 08 / Chapter08.0_PreparingTheASFProject.md L225 및 Chapter08.1_ArchitectureOverview copy.md L199

Status: Major Mismatch

Recommended Action: Replace

Technical Accuracy: 프로젝트 생성 설정 이미지다. Blank/Blueprint/Desktop/Maximum/ASF_Demo는 8.0 본문과 맞지만 ⑥은 Project Location을 가리키면서 설명은 Starter Content다.

Text Consistency: 8.1 삽입 위치는 Shader Architecture Overview를 요구하므로 완전히 다른 Figure가 참조되고 있다. 두 삽입 위치 모두 확인했다.

Terminology: Starter Content Enabled와 Ray Tracing Disabled를 실제 화면에서 확인할 수 없다. 해당 UI/버전 설정은 Needs Technical Verification.

Visual Communication: 오버레이 번호와 설정의 대응이 틀리며 Architecture/Module 관계는 전혀 없다.

Issues: 동일 파일의 서로 다른 목적 재사용; ⑥ 대상 오류; 필수 설정 증거 누락.

Recommendation: 후속 수정 단계에서 8.0에는 검증된 생성 화면을, 8.1에는 Master/Module/Composition 도식을 각각 사용한다. 이번 Audit에서는 원본/경로를 변경하지 않는다.

## Fig8_04

Chapter / Section: Chapter 08 / Chapter08.0_PreparingTheASFProject.md L387; Chapter08.1_ArchitectureOverview copy.md L241

Status: Major Mismatch

Recommended Action: Replace

Technical Accuracy: Project Settings 값은 8.0 본문 표와 맞는다. 모든 항목의 '기본값' 확정은 버전/템플릿에 대한 Needs Technical Verification.

Text Consistency: 8.1은 Material Function/Master 관계를 설명하지만 실제 이미지는 엔진 설정이다. 두 위치 모두 대조했다.

Terminology: Rendering 설정은 ASF Module이나 Material Function이 아니다.

Visual Communication: 설정 번호/값 대응은 명확하지만 Mobile TAA와 Desktop TSR이 함께 표시되어 대상 구분 보완이 필요하다.

Issues: Architecture 삽입 목적과 이미지 완전 불일치.

Recommendation: 8.0 설정 도식은 유지 가능하나 8.1에는 Master와 MF의 입출력/합성 관계를 나타내는 별도 도식이 필요하다.

## Fig8_05

Chapter / Section: Chapter 08 / Chapter08.0_PreparingTheASFProject.md L587; Chapter08.1_ArchitectureOverview copy.md L289

Status: Major Mismatch

Recommended Action: Replace

Technical Accuracy: Content/ASF 하위 폴더 도식이나 본문의 Meshes가 빠지고 Fbx가 추가되었다. FBX 원본 파일과 Import된 Mesh Asset의 구분이 필요하다.

Text Consistency: 8.0 폴더 표와 일부 불일치하며 8.1의 Rendering Data Flow와는 전혀 다른 이미지다.

Terminology: 폴더 관리 구조와 Rendering Module Data Flow를 구분해야 한다.

Visual Communication: 폴더 도식 자체는 읽기 쉬우나 Runtime 데이터 입력/처리/출력이 없다.

Issues: 두 문맥 중 Architecture와 완전 불일치; Meshes/Fbx 목록 차이.

Recommendation: 폴더 구조는 본문 목록과 맞추고 Source FBX의 보관 위치를 별도로 정의한다. Architecture에는 Surface/Lighting 입력→Module→Composition 도식을 사용한다.

## Fig8_06

Chapter / Section: Chapter 08 / 8.0.7 — Chapter08.0_PreparingTheASFProject.md L695

Status: Match

Recommended Action: Keep

Technical Accuracy: Asset 유형별 Prefix와 PascalCase 조합이 본문의 명명 규칙에 부합한다.

Text Consistency: 예시 이름 일부는 본문과 다르지만 동일한 규칙을 설명하므로 의미상의 불일치는 없다.

Terminology: Material, Material Function, Material Instance 및 Texture Prefix 구분이 일관된다.

Visual Communication: 유형별 표와 올바른/잘못된 예시를 함께 제공하여 규칙을 비교하기 쉽다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다.

## Fig8_07

Chapter / Section: Chapter 08 / 8.0.8 — Chapter08.0_PreparingTheASFProject.md L826

Status: Match

Recommended Action: Keep

Technical Accuracy: 문서와 Unreal 프로젝트의 논리적 분리, 생성 폴더 제외 및 Commit/Push 흐름이 본문과 일치한다.

Text Consistency: 실제 물리 경로와 다를 수 있는 논리 구조임을 그림에서 명시한다.

Terminology: Content, Config, Source, Plugins 및 버전 관리 용어가 역할에 맞게 사용된다.

Visual Communication: 포함할 폴더, 제외할 폴더와 작업 흐름이 구분되어 있다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다.

## Fig8_08

Chapter / Section: Chapter 08 / 8.0.9 — Chapter08.0_PreparingTheASFProject.md L942

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 준비 단계 요약 자체는 타당하지만 다음 구현 단계의 Chapter 번호가 실제 문서 구성과 다르다.

Text Consistency: What's Next가 Chapter 9부터 핵심 기능을 구현한다고 안내한다. 실제 다음 단계는 8.1 Architecture 및 Chapter 08의 구현 절이며 Chapter 09는 최적화이다.

Terminology: 이전 명칭 Anime Shader Framework가 남아 있어 Ari’s Shader Framework와 통일이 필요하다.

Visual Communication: 준비 단계 카드 구조는 명확하지만 8.0.5가 생략되어 완료 체크 범위가 불명확하다.

Issues: 잘못된 다음 Chapter 안내가 학습 순서를 왜곡한다. 8.0.5의 포함 여부도 표시되어 있지 않다.

Recommendation: 다음 단계를 8.1 Architecture와 Chapter 08 구현 절로 고치고 현재 프로젝트 명칭을 적용한다. 8.0.5를 표시하거나 통합된 카드의 범위를 명시한다.

## Fig8_10

Chapter / Section: Chapter 08 / 8.4.3 — Chapter08.4_Specular.md L400

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: LightDirection Normalize와 Dot 계산은 보인다. PixelNormalWS에는 본문에서 설명한 별도 Normalize가 없고 Dot 이후 Saturate가 추가되어 표시값은 원래 [-1,1] Scalar와 다르다.

Text Consistency: 본문의 두 입력 Normalize→Dot 설명과 실제 그래프의 입력 준비 및 출력 시각화 단계를 구분해야 한다.

Terminology: 노드 용어는 적절하다.

Visual Communication: 노드와 구를 함께 보이나 계산값과 Lit 화면의 차이를 설명하지 않는다.

Issues: Saturate 및 Emissive 연결의 목적과 시각화 조건이 누락되었다.

Recommendation: 실제 입력의 정규화 전제를 명시하고 Dot 원값, Saturate 결과, 화면 표시 경로를 구분한다.

## Fig8_14

Chapter / Section: Chapter 08 / 8.4.4 — Chapter08.4_Specular.md L705

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Dot에는 Normalize한 L을 쓰지만 -L 항에는 Normalize 이전 LightDirection을 사용한다. 입력 길이가 1이 아니면 2(L·N)N-L의 방향이 달라지며 마지막 Normalize로 복구할 수 없다.

Text Consistency: 본문은 같은 Unit L로 반사 방향을 구성하지만 그림은 서로 다른 L을 사용한다.

Terminology: R 명칭 자체는 적절하다.

Visual Communication: RGB 시각화를 위한 ×0.5+0.5와 Base Color 연결이 실제 반사 계산과 섞여 있다.

Issues: 정규화된 입력의 분기가 불일치한다. RGB 색상은 최종 Highlight가 아니다.

Recommendation: Normalize 출력에서 Dot과 -1 Multiply로 함께 분기한다. 계산부와 디버그 표시부를 구분하고 표시 조건을 명시한다.

## Fig8_15

Chapter / Section: Chapter 08 / 8.4.5 — Chapter08.4_Specular.md L860

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Camera Vector와 R의 Dot 노드는 있으나 Dot 출력은 연결되지 않았다. Base Color는 R의 ×0.5+0.5 경로에서 공급되어 R·V 시각화 경로와 다르다. -L 분기의 정규화 불일치도 남아 있다.

Text Consistency: 캡션의 R·V 계산 노드는 존재하지만 오른쪽 결과를 해당 Scalar의 결과로 연결해 읽을 근거가 없다.

Terminology: R과 V 표기는 명확하다.

Visual Communication: 사용되지 않는 Dot 출력과 표시 경로가 혼재하여 단계별 구현을 오해하게 한다.

Issues: 본문의 핵심 계산이 화면 출력에 반영되지 않는 연결 상태이다.

Recommendation: 정규화된 L 분기를 통일하고 R·V Scalar를 명시적 디버그 출력에 연결한 상태와 결과를 다시 캡처한다.

## Fig8_16

Chapter / Section: Chapter 08 / 8.4.6 — Chapter08.4_Specular.md L1052

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Saturate(R·V)→Power(8)로 낮은 Exponent의 넓은 Response를 보여준다. 결과는 Base Color로 연결되어 있어 Lit 재질의 다른 조명 반응도 화면에 포함될 수 있다.

Text Consistency: 본문의 단순 (R·V)^n 표기와 달리 그림은 음수 처리용 Saturate를 포함한다.

Terminology: Exponent 값 8이 표시되어 있다.

Visual Communication: 넓은 Highlight는 관찰되지만 배경 및 재질 조명의 영향이 분리되지 않는다.

Issues: Response 시각화와 최종 Specular 출력의 구분 및 Clamp 전제가 부족하다.

Recommendation: max(R·V,0)^n의 정의를 명시하고 Base Color 디버그 표시임을 밝힌다. 동일 조건으로 Exponent만 비교한다.

## Fig8_17

Chapter / Section: Chapter 08 / 8.4.6 — Chapter08.4_Specular.md L1064

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Saturate→Power(32)로 Exponent 증가 시 Response가 좁아지는 관계는 맞다. Base Color 연결과 기존 Specular 0.5가 함께 존재한다.

Text Consistency: Medium Exponent 설명과 관찰되는 집중도는 일치하나 순수 Phong 출력과 Lit 표시를 구분하지 않는다.

Terminology: Power와 Exponent 표기는 적절하다.

Visual Communication: 수치와 결과를 비교할 수 있으나 사용하지 않는 RGB 표시 노드가 남아 있다.

Issues: 표시 조건과 Clamp 전제가 빠져 있어 Highlight를 Power만의 결과로 단정하기 어렵다.

Recommendation: Exponent 8/32/128을 같은 조건에서 비교하고 디버그 출력 경로 및 Saturate를 설명한다.

## Fig8_18

Chapter / Section: Chapter 08 / 8.4.6 — Chapter08.4_Specular.md L1076

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Power(128)의 좁은 Response 방향은 타당하다. 다만 Base Color로 출력하고 기존 재질 Specular를 유지하므로 화면 전체가 순수 Phong Response는 아니다.

Text Consistency: High Exponent의 집중도 설명과 부합한다.

Terminology: Exponent 수치는 읽을 수 있다.

Visual Communication: 좁은 밝은 영역 주변에 넓은 재질 반응이 남아 비교를 혼동시킬 수 있다.

Issues: 동일 조건 및 출력 방식의 설명이 부족하다.

Recommendation: 순수 Scalar 표시와 최종 Lit 화면을 구분하고 세 Exponent 비교의 조명·노출·재질 조건을 명시한다.

## Fig8_19

Chapter / Section: Chapter 08 / 8.4.7 — Chapter08.4_Specular.md L1226

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Phong Response를 Material Specular 핀에 연결한 상태이다. 이것을 엔진의 최종 Specular 모델을 Phong으로 교체한 결과로 해석할 수는 없다. -L 경로의 Normalize 이전 입력 사용도 남아 있다. Needs Technical Verification: 해당 엔진 버전/재질 설정의 Specular 핀 해석과 실제 합성 경로.

Text Consistency: 본문과 연결 위치는 일치하지만 본문과 그림이 함께 사용자 계산 Response와 엔진 Shading 입력의 역할을 혼동시킨다.

Terminology: Material Specular 입력과 Phong Specular Response를 구별해야 한다.

Visual Communication: 어두운 구의 Highlight만으로 최종 모델을 검증할 수 없다.

Issues: Response 계산과 엔진 BRDF 조절을 같은 단계로 설명한다.

Recommendation: 정규화된 L을 통일하고 ASF의 실제 합성/출력 경로를 확인한 뒤 이를 보여준다. Specular 핀을 사용할 경우 그 제한과 엔진 계산의 추가 영향을 명시한다.

## Fig8_20

Chapter / Section: Chapter 08 / 8.4.1 — Chapter08.4_Specular.md L46

Status: Major Mismatch

Recommended Action: Replace

Technical Accuracy: 같은 좌표 공간의 L/N 설명은 타당하지만 +Y 방향에서 본 Top View에서 Y 방향 N을 화면 위쪽 벡터로 그대로 그려 투영 관계가 맞지 않는다.

Text Consistency: 캡션은 Phong Specular 기본 Data Flow이나 그림에는 R·V 비교 및 Highlight 출력 흐름이 없고 L·N 관계를 설명한다.

Terminology: L=Surface→Light는 본문과 일치한다.

Visual Communication: 구 표면 P의 위치와 수직 N의 관계가 모호하고 Top View가 실제 투영과 다르다.

Issues: 캡션의 핵심 Data Flow가 부재하며 좌표 시점 표기가 부정확하다.

Recommendation: L,N→R 및 R,V→Dot→Clamp/Power→Response의 입력 분기를 보여주는 도식으로 교체한다. 현 도식은 L/N 설명에 사용할 경우 시점과 P를 수정한다.

## Fig8_21

Chapter / Section: Chapter 08 / 8.4.2 — Chapter08.4_Specular.md L113

Status: Match

Recommended Action: Keep

Technical Accuracy: 실제 입사 진행 방향과 계산용 L=Surface→Light를 반대 방향으로 정확히 구분한다.

Text Consistency: 본문과 캡션의 Vector Convention을 직접 설명한다.

Terminology: Light Direction과 Surface Point가 일관된다.

Visual Communication: 두 패널의 화살표와 범례가 명확하다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다.

## Fig8_22

Chapter / Section: Chapter 08 / 8.4.2 — Chapter08.4_Specular.md L161

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: L/N 및 각도 관계는 맞다. 하단 θ=90° 예시의 Light 아이콘은 수평 L 방향 위쪽에 있어 점광원 위치와 방향이 일치하지 않는다.

Text Consistency: 본문의 Surface→Light 정의와 주 도식은 일치한다.

Terminology: 하단 '최대 밝기'와 'Diffuse 0'는 해당 Direct Diffuse 항의 비교임을 한정하면 더 정확하다.

Visual Communication: 주 도식은 이해하기 쉽지만 하단 아이콘의 위치가 방향 설명을 약화한다.

Issues: θ=90°에서 광원 위치와 L 화살표가 불일치한다.

Recommendation: 광원 아이콘을 L 방향에 맞추고 밝기 비교가 다른 조건을 고정한 Direct Diffuse임을 표시한다.

## Fig8_23

Chapter / Section: Chapter 08 / 8.4.3 — Chapter08.4_Specular.md L300

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 정규화된 두 Vector의 Dot 범위를 일반적으로 0~1로 표시했으나 실제 범위는 -1~1이다. 그림의 0~90° 예시에만 0~1이 적용된다.

Text Consistency: 절 참조가 8.1.2 및 8.1.4로 남아 실제 8.4.2/8.4.4와 다르다.

Terminology: Scalar 구분과 Normalize의 목적은 적절하다.

Visual Communication: 출력 상자와 요약에 0~1이 반복되어 음수 결과가 없다는 오해를 강화한다.

Issues: Dot 원값과 Clamp한 조명값의 범위를 혼동하고 오래된 절 번호를 사용한다.

Recommendation: Dot 원값은 -1~1, 앞면 예시는 0~1로 구분한다. 음수 예시 또는 Saturate 후 범위를 추가하고 절 번호를 맞춘다.

## Fig8_24

Chapter / Section: Chapter 08 / 8.2.1 — Chapter08.2_BaseLighting.md L240

Status: Major Mismatch

Recommended Action: Replace

Technical Accuracy: MF_BaseLighting 입력 세 개는 보이나 출력은 Lighting Result 하나뿐이다. 정의된 Lighting Data 출력이 없다.

Text Consistency: 본문은 MF_BaseLighting Interface를 제시하는 단계인데 그림은 MF_Shadow까지 연결된 Master Material과 결과 화면이다.

Terminology: Module의 역할과 실제 MF Interface를 구분하는 설명이 필요하다.

Visual Communication: MF_Shadow가 선택 강조되어 이 단계의 주 대상이 흐려진다. Light Direction/Normal 입력도 미연결이다.

Issues: 본문에서 핵심으로 구분한 Lighting Data와 Lighting Result의 이중 출력 계약을 검증할 수 없다.

Recommendation: 정의한 세 입력과 두 출력을 모두 표시한 MF_BaseLighting Interface 캡처로 교체한다. 기본 입력값 사용 여부도 명시한다.

## Fig8_25

Chapter / Section: Chapter 08 / 8.2.2 — Chapter08.2_BaseLighting.md L552

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Emissive에 연결된 것은 Lighting Data이며 Lighting Result 출력은 미연결이다. 화면의 흰색 Scalar 표시도 이 연결과 부합한다.

Text Consistency: 본문은 Lighting Result를 연결하여 Base Color 적용까지 검증했다고 설명하지만 그림은 색상 적용 결과를 보여주지 않는다.

Terminology: 두 Output의 명칭은 선명하므로 차이를 직접 확인할 수 있다.

Visual Communication: 분홍색 Base Color 입력과 흰색 출력의 차이에 설명이 없다.

Issues: Scalar 조명 데이터 검증을 Base Color 합성 검증으로 설명한다.

Recommendation: Lighting Data 디버그 캡처로 설명을 한정하거나 Lighting Result를 Emissive에 연결한 색상 결과를 별도로 제시한다.

## Fig8_26

Chapter / Section: Chapter 08 / 8.2.3 — Chapter08.2_BaseLighting.md L744

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Direction→MF_BaseLighting, PixelNormalWS 및 Lighting Result→Emissive 연결은 설명과 일치한다. Needs Technical Verification: 해당 노드의 엔진 버전, 지원 경로, Direction 부호 및 Main Light 선택 조건.

Text Consistency: 하나의 정지 화면으로 회전 시 결과가 함께 이동한다는 동작 전체를 입증하지는 못한다.

Terminology: 입력 출처와 출력 역할이 구별된다.

Visual Communication: 조명 방향과 구 결과를 함께 보이지만 전후 비교가 없다.

Issues: 동적 동작을 입증하는 비교 및 실행 조건이 부족하다.

Recommendation: 동일 조건의 두 Light Rotation과 결과를 병기하고 지원 엔진/설정을 명시한다.

## Fig8_27

Chapter / Section: Chapter 08 / 8.2.4 — Chapter08.2_BaseLighting.md L843

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: L Normalize→N Normalize→Dot의 직렬 화살표가 두 독립 입력을 순차 변환하는 것으로 보인다. Direction과 PixelNormalWS의 외부 화살표도 해당 입력으로 직접 연결되지 않는다.

Text Consistency: 본문의 각각 Normalize한 L/N을 Dot에서 결합한다는 설명과 도식의 연결 관계가 다르다.

Terminology: Lighting Data/Result 구분은 적절하나 조명량이라는 말은 방향 기반 Factor의 범위로 한정해야 한다.

Visual Communication: Output 구에는 Specular처럼 보이는 흰 점이 포함되어 현재 범위에서 제외한 Highlight와 혼동된다.

Issues: 핵심 입력 의존성이 잘못 표현되어 있으며 Output 예시가 순수 Factor를 분리하지 않는다.

Recommendation: L과 N을 각각 Normalize→Dot 두 입력으로 연결하고 외부 데이터 경로를 해당 핀까지 표시한다. Output은 Scalar/Color만 보여주는 통제된 예시를 사용한다.

## Fig8_28

Chapter / Section: Chapter 08 / 8.3 — Chapter08.3_Shadow.md L128

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 방향 관계와 Visibility를 구분하는 개념은 맞다. 최종 기여=(N·L)×Visibility 표기는 Clamp, 광원 세기와 재질항을 생략한 개념식임을 밝혀야 한다.

Text Consistency: 같은 방향 조건에서도 Occluder가 직접광을 차단한다는 본문과 일치한다.

Terminology: 입사 진행 화살표를 Light Direction이라고 표기하여 ASF의 L=Surface→Light와 혼동된다.

Visual Communication: 차단 전후 비교는 명확하나 N·L에 쓰이는 L 화살표와 입사 진행 방향을 별도로 표시하지 않는다.

Issues: L 부호와 빛의 진행 방향의 구분이 부족하다.

Recommendation: 입사 화살표는 Light Travel Direction=-L로 표기하고 계산용 L을 분리한다. 식은 단순화된 Direct Diffuse Factor라고 한정하고 saturate를 명시한다.

## Fig8_29

Chapter / Section: Chapter 08 / 8.3.2 — Chapter08.3_Shadow.md L534

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 이진 Visibility와 Occlusion 관계는 맞다. Direct Lighting=(N·L)×Visibility는 다른 조명/재질항과 Clamp를 생략한 개념식이다.

Text Consistency: 본문이 강조한 경로 개방 여부와 관점의 차이를 포함한다.

Terminology: Shadow를 Visibility=0으로만 요약한 문장은 가장 단순한 불투명 단일 광원 표본의 경우로 한정해야 한다.

Visual Communication: Occluded 패널의 Light–Occluder–P 경로가 꺾여 보여 직선 Visibility Test와 불일치한다.

Issues: 일반식으로 보이는 단순화와 꺾인 검사 경로.

Recommendation: Light–P 직선을 Occluder가 가로막도록 배치하고 이진 Visibility 및 단순화된 조명 Factor의 전제를 명시한다.

## Fig8_30

Chapter / Section: Chapter 08 / 8.3.3 — Chapter08.3_Shadow.md L1073

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Light 이전 교차 유무로 판단하는 흐름은 타당하다. '모든 Geometry' 검사 및 '가장 가까운 Intersection만' 결정한다는 단정은 불투명 차폐의 교차 유무 확인과 구현 방식을 혼동한다.

Text Consistency: 본문의 Light 이전 Occluder 유무라는 핵심은 맞지만 그림은 반드시 전수 검사/최근접 교차가 필요한 것처럼 좁힌다.

Terminology: Ray의 수학적 정의와 Shadow Ray 검사 구간은 구분되어 있다.

Visual Communication: Visible 예시의 P가 구의 접촉부처럼 보여 자기 차폐 여부가 모호하다.

Issues: 불필요한 최근접/전수 검사 단정과 P 위치의 모호함.

Recommendation: 불투명 물체에 대해 P–Light 구간의 유효 차폐 교차가 있는지 검사한다고 표현한다. P와 시작점 Offset의 개념을 간단히 명시한다.

## Fig8_31

Chapter / Section: Chapter 08 / 8.3.4 — Chapter08.3_Shadow.md L1784

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Depth 비교 부등식은 일반적인 near-small 규약에서 타당하나 규약을 밝혀야 한다. 같은 Light-space 좌표의 저장 Depth를 샘플링한다는 핵심 의존성이 도식에 없다.

Text Consistency: Shadow Ray와 '동일한 효과'라는 문구는 해상도/정밀도에 따른 근사 한계를 고려하면 정확한 동등성으로 읽히지 않도록 해야 한다.

Terminology: Depth와 Light까지의 일반 거리 표현을 투영 Depth와 구분해야 한다.

Visual Communication: Camera 패널은 P까지의 점선을 상자 내부를 통과하도록 그려 Camera에서 보이는 P라는 전제와 충돌한다. 비교 패널도 P와 저장 Depth의 공통 Light Ray가 보이지 않는다.

Issues: Camera-visible P의 배치 및 샘플 좌표 연결이 부정확하다. 모든 Pixel의 Ray 비용이 매우 크다는 단정은 Needs Technical Verification.

Recommendation: Camera에 실제로 보이면서 Light에는 가려진 P를 배치한다. P→Light projection/UV→해당 Texel Depth Sample→동일 규약 Depth 비교를 보여준다.

## Fig8_32

Chapter / Section: Chapter 08 / 8.3.5 — Chapter08.3_Shadow.md L2871

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 해상도/Bias의 기본 효과는 맞으나 Camera에서 멀수록 Shadow Map Texel의 실제 공간이 무조건 커진다는 설명은 투영 방식과 분할 조건을 생략한다.

Text Consistency: 캡션은 Filtering 개선까지 요약한다고 하나 본체 행에는 Filtering의 계산이나 비교 예시가 없다.

Terminology: Shadow Acne는 잘못된 Self-shadowing 판정이라는 점을 실제 자기 그림자와 구별해야 한다.

Visual Communication: Peter Panning 예시는 Shadow만 떨어지는 대신 상자 자체가 떠 있는 것처럼 그려져 원인이 혼동된다.

Issues: 거리·투영 조건 일반화, Filtering 설명 누락, Peter Panning 시각화 부정확.

Recommendation: Camera/Light 투영 및 Cascade 조건을 분리해 설명한다. 동일한 접지 Geometry를 유지한 채 Shadow의 분리만 보여주고 Filtering 행을 추가하거나 캡션 범위를 줄인다.

## Fig8_33

Chapter / Section: Chapter 08 / 8.3.6 — Chapter08.3_Shadow.md L3967

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Light Contribution×Visibility와 다른 조명 합산 구조는 맞다. 하지만 중간값은 현재 P에서 면광원 표본 또는 필터 비교의 결과임을 밝혀야 하며 구 전체로 도달하는 광선의 개수와 혼동하면 안 된다.

Text Consistency: 본문은 Visibility=0에서 해당 Light 기여가 0이라고 설명한다. 그림의 0 패널은 1 패널과 유사한 밝은 Highlight를 유지하면서 완전히 어두운 영역이라고 표기한다.

Terminology: Visibility를 V로 쓰면 이 Chapter의 View Direction V와 충돌하므로 구분이 필요하다.

Visual Communication: 1/0.5/0 세 구의 실제 밝기 변화가 라벨과 맞지 않고 비교 대상 P도 없다.

Issues: 핵심 비교 결과가 수치와 시각적으로 대응하지 않는다.

Recommendation: 같은 P 또는 동일한 Scalar/RGB 패치의 1/0.5/0 선형 기여를 표시한다. 다른 조명 유지 여부를 명시하고 Visibility 기호를 별도로 사용한다.

## Fig8_34

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4451

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Sphere와 Plane에 직접광과 Cast Shadow가 나타나는 기본 관찰 예시이다. 화면만으로 실제 Shadow Map 방식이나 Depth 저장 경로를 확인할 수는 없다.

Text Consistency: 기본 그림자 확인이라는 삽입 목적에는 부합한다.

Terminology: 구의 N·L 명암과 Plane의 Cast Shadow를 구분해 표시하면 좋다.

Visual Communication: 두 효과가 함께 보이지만 식별 라벨과 설정 정보가 없다.

Issues: Needs Technical Verification: 사용 엔진 버전, Shadow 방식 및 Light Mobility 설정.

Recommendation: 관찰 대상에 라벨을 붙이고 테스트 설정을 기록한다. 이 이미지 자체를 Shadow Map 내부 데이터의 증거로 사용하지 않는다.

## Fig8_35

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4576

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 색조와 경계 패턴은 보이나 Debug View 이름, 범례, 값 범위가 없어 Depth인지 Shadow Mask인지 판별할 수 없다.

Text Consistency: 본문의 Depth/Shadow 중간 데이터 설명을 이미지에서 특정할 수 없다.

Terminology: Shadow Map Depth와 Shadow Mask를 구분한 직전 설명에 비해 Debug 데이터의 명칭이 모호하다.

Visual Communication: 일반 Lit와 유사한 화면에 색조만 달라져 어떤 데이터를 읽어야 하는지 알기 어렵다.

Issues: Needs Technical Verification: 실제 활성 Debug Mode와 색상 의미.

Recommendation: Debug Mode 선택 상태, 명령/설정 및 범례가 포함된 캡처를 제공하고 시각화 대상 데이터를 하나로 특정한다.

## Fig8_36

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4605

Status: Major Mismatch

Recommended Action: Replace

Technical Accuracy: 한 장의 파란색 Debug 화면만으로 Sphere 이동에 따른 Shadow Map 갱신을 확인할 수 없다.

Text Consistency: 본문과 alt는 Sphere 이동을 설명하지만 선택 Gizmo는 Light에 있고 Sphere의 이동 전후가 제시되지 않는다.

Terminology: 파란 영역이 나타내는 데이터의 정의도 없다.

Visual Communication: 변경 대상과 전후 상태가 식별되지 않는다.

Issues: 이동 실습의 핵심 증거와 맞지 않는 캡처이다.

Recommendation: Camera/Light를 고정하고 Sphere 위치만 바꾼 전후 화면 및 위치값을 제시한다. Debug 색상은 모드와 범례를 함께 표시한다.

## Fig8_37

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4654

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Sphere의 Mobility=Movable 및 위치/Scale 값을 확인할 수 있다. Shadow 갱신 자체는 단일 정지 화면으로 확인되지 않는다.

Text Consistency: Movable 설정 설명에는 부합하나 위치 변화와 갱신까지 주장하는 alt는 증거보다 넓다.

Terminology: UI의 Mobility 용어는 일치한다.

Visual Communication: 설정과 결과가 함께 보여 유용하지만 이전 위치 비교가 없다.

Issues: 설정 확인과 동적 동작 확인의 범위가 다르다.

Recommendation: Movable 설정 캡처로 범위를 한정하거나 동일 Camera에서 이동 전후와 위치값을 추가한다.

## Fig8_38

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4672

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Scale Z=2와 길어진 Sphere를 보여 주므로 비균일 Scale 변화는 확인된다. 표면 경계의 큰 패턴은 Scale에 따른 정상 Shadow 변화와 별도 진단이 필요하다.

Text Consistency: 크기 변화라는 본문 목적에 부합한다.

Terminology: Scale 변화가 비균일 Z Scale임을 명확히 하면 좋다.

Visual Communication: Transform 값은 보이나 바닥 Shadow 일부가 화면 밖으로 잘려 전체 형태 비교가 어렵다.

Issues: Shadow 형태 비교가 불완전하며 Artifact가 함께 포함된다.

Recommendation: Scale 1과 Z=2의 동일 Camera 비교에 Shadow 전체를 포함하고 Artifact는 별도 표기한다.

## Fig8_39

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4697

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 두 Sphere의 명암 경계와 그림자 차이는 보이지만 각 Mesh/Shadow 설정이 없어 Shadow Map 해상도의 영향으로 특정할 수 없다.

Text Consistency: 본문은 해상도와 품질을 설명하지만 이미지에 해상도값이나 통제된 변경 조건이 없다.

Terminology: 어느 쪽이 기준/변경 결과인지 정의되지 않았다.

Visual Communication: 라벨 없는 두 Sphere를 비교하므로 무엇을 관찰해야 하는지 불명확하다.

Issues: Needs Technical Verification: 차이를 발생시킨 실제 Mesh, Normal, Shadow 해상도/Bias/Filtering 설정.

Recommendation: 한 변수만 바꾼 동일 Geometry 비교로 구성하고 설정값, 기준/변경 라벨 및 관찰 영역을 표시한다.

## Fig8_40

Chapter / Section: Chapter 08 / 8.3.7 — Chapter08.3_Shadow.md L4712

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Geometry, 해상도, Bias 및 Rendering Path를 분리해 진단하려는 방향은 타당하다. 다만 개선 여부만으로 단일 원인을 확정하는 분기는 원인 간 상호작용을 생략한다.

Text Consistency: 본문의 단일 원인 단정 금지와는 부합하나 그림의 번호는 39로 남아 있다.

Terminology: VSM, HWRT, SSG 및 Lumen의 관계/약어를 명확히 해야 한다. Needs Technical Verification: 엔진 버전별 지원 설정과 조절 항목.

Visual Communication: 누락 Shadow 예시는 정상 타원처럼 보여 누락 부위가 식별되지 않는다. 여러 Yes/No 선과 가로 화살표가 겹친다.

Issues: 오래된 번호, 일부 예시의 증거 부족 및 진단 결과 단정.

Recommendation: 번호를 8-40으로 맞추고 원인 확정 대신 후보 좁히기로 표현한다. 누락/깜빡임은 기준 결과와 비교하고 엔진별 설정을 확인한다.

## Fig8_41

Chapter / Section: Chapter 08 / 8.5.1 — Chapter08.5_RimLight.md L76

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: N·V의 정면/접선 관계는 맞지만 Scene Setup의 Camera는 구 왼쪽에 있고 B는 구 오른쪽 극점이다. 그 B는 이 Camera의 Silhouette 표본이 아니며 A도 Surface Point인지 불명확하다.

Text Consistency: 본문은 현재 Camera에서 보이는 정면과 실루엣을 비교하므로 Scene Setup이 같은 관점을 유지해야 한다.

Terminology: View-dependent Mask와 외곽선 검출의 구분은 적절하다.

Visual Communication: 왼쪽 Scene 배치와 가운데/오른쪽 Camera 기준이 연결되지 않는다.

Issues: 핵심 Surface 표본과 Camera의 기하 관계가 맞지 않는다.

Recommendation: Camera 앞쪽 표면에 A를, Camera 접선에 B를 놓고 N과 V를 같은 P에서 그린다. Screen View와 측면 단면은 명시적으로 분리한다.

## Fig8_42

Chapter / Section: Chapter 08 / 8.5.2 — Chapter08.5_RimLight.md L313

Status: Match

Recommended Action: Keep

Technical Accuracy: PixelNormalWS와 Camera Vector→Dot→Saturate→Emissive의 연결과 중심 밝음/가장자리 어두움 결과가 대응한다.

Text Consistency: 본문의 N·V Debug 설명과 일치한다.

Terminology: 현재 Pixel의 Normal 및 View 입력이 명확하다.

Visual Communication: 계산 경로와 흑백 구 결과를 함께 확인할 수 있다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다. 정량 비교 시 노출/톤매핑 조건을 함께 기록하면 좋다.

## Fig8_43

Chapter / Section: Chapter 08 / 8.5.2 — Chapter08.5_RimLight.md L411

Status: Match

Recommended Action: Keep

Technical Accuracy: Saturate(N·V) 뒤 One Minus를 적용하여 중심이 0, 외곽이 밝아지는 Mask를 생성한다.

Text Consistency: 본문의 반전 단계와 아직 넓은 기본 Rim Mask라는 설명에 부합한다.

Terminology: One Minus와 Emissive 출력이 식별된다.

Visual Communication: 추가된 노드와 결과 반전이 명확하다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다.

## Fig8_44

Chapter / Section: Chapter 08 / 8.5.3 — Chapter08.5_RimLight.md L647

Status: Match

Recommended Action: Keep

Technical Accuracy: 동일한 Mask에 Power 1/4를 적용하며 값이 커질수록 중간 영역이 줄어드는 결과가 맞다.

Text Consistency: 위 1, 아래 4라는 본문과 이미지가 일치한다.

Terminology: RimPower 명칭이 실제 Exponent 제어와 부합한다.

Visual Communication: 강조된 Parameter 값과 두 결과로 차이를 확인할 수 있다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다.

## Fig8_45

Chapter / Section: Chapter 08 / 8.5.4 — Chapter08.5_RimLight.md L746

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 기재된 F0=0.04 Schlick 식에서 N·V=0.5이면 F=0.07인데 곡선은 약 0.5로 그려져 있다. 정면 반사광의 두 갈래 분기와 Grazing 반사각도 매끈한 평면의 반사 관계에 맞지 않는다.

Text Consistency: Fresnel과 Rim Mask의 목적 차이는 본문과 일치하지만 수식의 예시 곡선이 수치와 충돌한다.

Terminology: N·V 형태는 매끈한 표면의 View-angle 설명으로 한정하고 Microfacet BRDF의 Fresnel 각도와 구분해야 한다.

Visual Communication: Camera에서 광선이 나가는 듯한 도식은 시선과 실제 광선의 역할을 혼동시킨다.

Issues: 수식과 곡선 불일치 및 반사 기하 오류. Schlick의 적용 범위/역사 설명은 Needs Technical Verification.

Recommendation: 식으로 계산한 곡선에 (0,1), (0.5,0.07), (1,0.04)를 표시한다. 시선과 입사/반사광을 구분하고 평면 반사각을 맞춘다.

## Fig8_46

Chapter / Section: Chapter 08 / 8.5.5 — Chapter08.5_RimLight.md L1620

Status: Match

Recommended Action: Keep

Technical Accuracy: Normal/View Vector3, RimPower Scalar 입력과 Dot→Saturate→One Minus→Power→RimMask 출력이 일치한다.

Text Consistency: 위 Function 내부, 아래 호출부와 Emissive Debug라는 본문을 정확히 보여준다.

Terminology: RimMask와 최종 Color Composition을 분리한 Interface가 명확하다.

Visual Communication: 호출 입력 및 결과를 함께 확인할 수 있다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다. 재사용 계약에는 입력이 같은 공간의 Unit Vector라는 전제를 유지한다.

## Fig8_47

Chapter / Section: Chapter 08 / 8.5.6 — Chapter08.5_RimLight.md L1880

Status: Match

Recommended Action: Keep

Technical Accuracy: 동일 RimColor에 Intensity 1/2를 곱하며 밝기 증가로 Soft Gradient가 더 눈에 띄는 결과가 대응한다.

Text Consistency: 계산 영역과 지각되는 Width의 차이라는 본문 설명에 부합한다.

Terminology: RimColor와 RimIntensity의 역할이 구분된다.

Visual Communication: 수치와 결과가 함께 제시되어 체감 변화를 비교할 수 있다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다. 재현용으로 노출/Bloom 조건을 기록하면 좋다.

## Fig8_48

Chapter / Section: Chapter 08 / 8.5.6 — Chapter08.5_RimLight.md L2136

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Width 0.2→0.5와 Softness 0.1→0.3의 개별 변화는 확인된다. 다만 Function 내부가 보이지 않아 본문의 BaseRim→SmoothStep 식과 남아 있는 RimPower=4 입력의 관계를 확인할 수 없다.

Text Consistency: 세 비교의 목적은 일치하지만 최종 재설계식에서 제외한 Power 입력을 화면에서는 계속 제공한다.

Terminology: RimPower를 Advanced Control로 유지한 실험 단계인지 명시해야 한다.

Visual Communication: 세 결과는 식별 가능하지만 이름 없는 Scalar 노드와 작은 입력 글자가 비교를 어렵게 한다.

Issues: 최종 식과 중간 실험 Interface 사이의 구분 부족.

Recommendation: 각 행에 Width/Softness 값을 표기하고 사용한 Function 버전, Power 적용 여부 및 SmoothStep 입력 정의를 명시한다.

## Fig8_49

Chapter / Section: Chapter 08 / 8.4 — Chapter08.4_Specular.md L1649

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: L과 N을 Normalize하고 같은 Unit L을 -L 항에도 사용하므로 앞선 직접 구현 캡처의 L 분기 불일치가 이 그림에서는 해소되어 있다. ViewDirection은 그대로 Dot에 들어가므로 Unit Vector 계약이 필요하다.

Text Consistency: 네 입력과 SpecularMask 출력은 본문과 일치한다.

Terminology: Scalar Shininess 및 Mask 명칭이 적절하다.

Visual Communication: 내부 연산은 읽을 수 있으나 입력의 공간/정규화 전제는 표시되지 않았다.

Issues: 재사용 가능한 Function의 ViewDirection 길이 및 공통 좌표 공간 계약이 불명확하다.

Recommendation: ViewDirection을 내부 Normalize하거나 같은 공간의 Unit Vector 입력임을 Interface에 명시한다. Shininess의 유효 범위도 기록한다.

## Fig8_50

Chapter / Section: Chapter 08 / 8.5 — Chapter08.5_RimLight.md L2818

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Specular/Rim Intensity의 0/0→1/0→1/1 변경과 Add 합성 결과가 대응한다. 그림에는 Shadow Visibility를 합성하는 경로가 없으며 본문도 이를 구분한다.

Text Consistency: 세 단계 비교는 일치하지만 최종 Material 입력이 화면 밖이라 Unlit+Emissive 연결을 직접 검증할 수 없다.

Terminology: MF별 Mask와 Color/Intensity 합성 역할은 구별된다.

Visual Communication: 큰 세로 이미지에서 Parameter 글자가 작고 최종 출력이 잘려 있다.

Issues: 통합 결과의 최종 연결 및 재질 설정 증거가 빠졌다.

Recommendation: 최종 Emissive 연결과 Shading Model을 포함하고 각 행에 활성 Module/Intensity를 표시한다. Scene Cast Shadow는 MF_Shadow 결과가 아님을 유지한다.

## Fig8_51

Chapter / Section: Chapter 08 / 8.6.2 — Chapter08.6_MatCap.md L522

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Camera 기준 Normal 방향을 Texture 위치로 대응시키는 Lookup 개념은 타당하다.

Text Consistency: 방향에 저장된 Appearance를 조회한다는 본문과 일치한다.

Terminology: Front-facing 설명에 '정쪽 Normal'로 보이는 오탈자가 있다.

Visual Communication: 정면 Camera를 구 아래에 배치하고 중심 Normal도 아래로 그려 Down Normal과 Front Normal의 화면 방향이 같아 보인다.

Issues: 정면 투영과 장면 배치가 섞여 Camera 축을 오해할 수 있다.

Recommendation: Camera는 화면 밖 정면에 있음을 표시하고 Front Normal은 화면 밖 방향 기호로 표현한다. 용어 오탈자를 바로잡는다.

## Fig8_52

Chapter / Section: Chapter 08 / 8.6.3 — Chapter08.6_MatCap.md L1008

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: World→View 방향 변환의 필요성은 맞다. Camera 변화가 항상 View Normal 값 변화라는 요약은 순수 평행이동/회전을 구분하지 않는다.

Text Consistency: 본문은 Unreal World Z-up을 설명하지만 World 패널은 Y를 위로 그린다.

Terminology: View Z 부호는 좌표계 규약에 의존하며 그림의 단정은 사용 구현과 함께 확인해야 한다.

Visual Communication: Camera A에서 같은 P까지의 선이 구를 관통하여 현재 보이는 표면의 예시와 맞지 않는다. 숫자 예시도 대응 View 축/회전이 없어 검증 불가능하다.

Issues: World 축 불일치, 가려진 P, Camera 이동과 회전의 혼동.

Recommendation: World Z-up과 구현의 View 축을 맞추고 두 Camera에서 보이는 P를 선택한다. Orientation 변화에 따른 기저 변환을 표시하고 UV의 Y 반전 규약을 명시한다.

## Fig8_53

Chapter / Section: Chapter 08 / 8.6.4 — Chapter08.6_MatCap.md L1654

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: XY×0.5+0.5의 범위 변환은 맞다. 그러나 Normal Z를 Camera로부터의 거리/깊이로 설명한다. Normal의 Z는 방향 성분이며 위치 Depth가 아니다.

Text Consistency: 현재 절의 Remap 소개에는 부합하지만 그림은 V가 위로 증가하는 결과를 완성 MatCap UV로 제시한다. 뒤의 실제 구현은 V Flip을 요구한다.

Terminology: 법선(노멀), 뷰 등과 영어 Normal/View 표기를 통일하고 방향 성분과 위치 좌표를 구분해야 한다.

Visual Communication: Camera 시선이 구를 관통한 먼 표면에 닿고 Z 축 방향 설명도 혼재한다.

Issues: Normal 방향과 Depth 혼동 및 구현 UV 규약과의 연결 부족.

Recommendation: Z를 View 기준 방향 성분으로 고친다. Range Remap 단계와 V Flip을 포함한 최종 UV를 분리하고 축 규약을 표시한다.

## Fig8_54

Chapter / Section: Chapter 08 / 8.6.5 — Chapter08.6_MatCap.md L2728

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: World→View Transform의 Raw RGB 출력 및 음수 영역의 검은 표시가 본문과 대응한다.

Text Consistency: Perspective/CineCamera 두 View를 실제로 포함한다.

Terminology: Raw Normal 데이터이며 일반적인 [0,1] Normal 시각화가 아님을 이미지에도 표시하면 좋다.

Visual Communication: 왼쪽 View는 Lit, 오른쪽은 Unlit로 보여 바닥/반사 차이가 Camera 변화와 함께 나타난다.

Issues: 비교 View Mode가 달라 Camera 효과 외의 화면 차이가 섞인다.

Recommendation: 두 View의 표시 모드와 노출을 통일하고 Raw RGB 채널/음수 표시 범례를 붙인다.

## Fig8_55

Chapter / Section: Chapter 08 / 8.6.5 — Chapter08.6_MatCap.md L3330

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Remap→BreakFloat2→V OneMinus→Append→Texture Sample→Emissive 연결이 맞고 오른쪽 위 Highlight가 보인다.

Text Consistency: 본문의 V 보정 결과와 두 Camera 비교는 대응한다. 다만 원본 MatCap Texture가 읽을 수 있게 함께 제시되지 않아 원본과의 방향 일치를 직접 비교할 수 없다.

Terminology: V Flip과 RGB Lookup 단계는 구분되어 있다.

Visual Communication: Transform 이전 부분은 잘렸고 Texture Sample 미리보기는 검게 보여 원본 방향 증거가 부족하다.

Issues: 원본 Texture와 결과의 방향 비교가 불완전하다.

Recommendation: 원본 Texture의 상하/좌우 라벨 또는 방향 마커를 병기한다. 현재 구현의 V Flip 규약으로 한정해 설명한다.

## Fig8_56

Chapter / Section: Chapter 08 / 8.6.6 — Chapter08.6_MatCap.md L3606

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Normal→World/View 변환→RG→Remap→V Flip→Sample 구조와 Texture2D 입력 분기가 본문과 일치한다.

Text Consistency: Module의 좌표 변환과 Lookup 책임을 실제 Graph에서 확인할 수 있다.

Terminology: 상단 Asset 이름은 MF_Matcap으로 보이며 본문의 MF_MatCap과 대소문자가 다르다. Normal 입력은 World Space/Unit Vector 계약을 표시해야 한다.

Visual Communication: 전체 데이터 경로가 읽히지만 긴 가로 배치라 글자가 작다.

Issues: 명명 표기 및 Normal 입력 계약의 명확성 보완.

Recommendation: 문서의 명칭을 통일하고 입력이 World Space Unit Normal임을 설명한다. Texture 데이터와 Sample 결과 Color의 구분을 유지한다.

## Fig8_57

Chapter / Section: Chapter 08 / 8.6.7 — Chapter08.6_MatCap.md L4942

Status: Match

Recommended Action: Keep

Technical Accuracy: Alpha 0/0.25/0.5/1에서 기존 ASF와 MatCap의 비중이 이동하며 양 끝점과 중간 Appearance가 대응한다.

Text Consistency: 본문의 네 단계와 라벨이 일치한다.

Terminology: Alpha를 밝기가 아닌 Blend Ratio로 설명하는 문맥에 적합하다.

Visual Communication: 네 결과와 값이 명확하고 Highlight/음영의 변화가 관찰된다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다. 비교 조건과 MatCapIntensity 고정값을 함께 기록하면 좋다.

## Fig8_58

Chapter / Section: Chapter 08 / 8.6.7 — Chapter08.6_MatCap.md L5151

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Base/Shadow, Specular, Rim의 합과 MatCap을 Lerp해 Emissive로 출력한다. ShadowVisibility는 엔진 Shadow 입력이 아니라 값 1의 수동 Parameter이고 Lerp Alpha=1이라 현재 최종 출력은 MatCap 쪽이다.

Text Consistency: 전체 구조라는 목적에는 맞지만 Shadowed Lighting이라는 설명만으로 실제 Scene Shadow 통합이 완료된 것으로 읽힐 수 있다.

Terminology: MF_Matcap과 MF_MatCap 명칭 대소문자를 통일해야 한다.

Visual Communication: 전체 연결은 보이나 테스트 Placeholder와 현재 활성 경로에 별도 표시가 없다.

Issues: 수동 Visibility=1 및 Alpha=1 테스트 상태의 의미가 불명확하다.

Recommendation: ShadowVisibility는 임시 입력, Renderer Integration은 별도임을 표시한다. Alpha=1의 출력 의미와 최종 Blend Parameter 계획을 구분한다.

## Fig8_59

Chapter / Section: Chapter 08 / 8.7.1 — Chapter08.7_Emission.md L90

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 출력 Slot과 추가 Emission Contribution의 역할 구분은 적절하다. 다만 Base Lighting+Shadow+Specular+Rim+MatCap이라는 표기는 실제 Shadow 곱셈 및 MatCap Lerp를 모두 Add처럼 단순화한다.

Text Consistency: 본문도 같은 축약을 사용하지만 직전 실제 Master Material의 합성 연산과 구분해야 한다.

Terminology: Emission과 Emissive Output은 명확히 구별된다.

Visual Communication: 빛 번짐이 있는 예시의 Bloom 조건이 표시되지 않았다.

Issues: Module 목록과 합성식의 혼동, 번짐 예시의 Post Process 조건 누락.

Recommendation: 왼쪽은 Module 목록이라고 명시하거나 실제 곱셈/Add/Lerp 관계로 표시한다. 오른쪽 Halo는 Bloom 포함 예시라고 밝힌다.

## Fig8_60

Chapter / Section: Chapter 08 / 8.7.2 — Chapter08.7_Emission.md L973

Status: Match

Recommended Action: Keep

Technical Accuracy: 동일 Color에 Intensity 0/1/2/5를 곱하고 Emissive로 출력하는 연결과 밝아지는 결과가 대응한다.

Text Consistency: 본문이 구분한 출력값 증가와 화면상의 옅어짐, 자동 Bloom 아님이라는 설명에 적합하다.

Terminology: EmissionColor와 EmissionIntensity 역할이 명확하다.

Visual Communication: 네 값은 강조되어 있고 0에서 검정, 증가 시 밝아짐이 확인된다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다. 재현용 노출 및 표시 모드를 기록하면 좋다.

## Fig8_61

Chapter / Section: Chapter 08 / 8.7.3 — Chapter08.7_Emission.md L1735

Status: Match

Recommended Action: Keep

Technical Accuracy: EmissionIntensity=5를 유지한 채 Bloom Intensity 0/10을 비교하고 아래 결과에서 Halo가 나타난다.

Text Consistency: 동일 Emission과 다른 Post Process 결과라는 본문의 핵심과 일치한다.

Terminology: EmissionIntensity와 Bloom Intensity가 명확하게 분리되어 있다.

Visual Communication: 설정값과 구 외곽의 번짐을 함께 볼 수 있다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다. 비교용 노출/Camera 조건을 함께 기록하면 좋다.

## Fig8_62

Chapter / Section: Chapter 08 / 8.7.4 — Chapter08.7_Emission.md L2467

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Exposure Compensation -2/0/+2와 화면 변화가 보인다. Metering Mode의 Override가 꺼져 있어 표시된 Auto Exposure Histogram이 최종 적용 상태인지 이 캡처만으로 확정할 수 없다.

Text Consistency: 초기 Auto Exposure 테스트라는 문맥에는 맞지만 자동 적응의 원인과 효과를 직접 분리해 입증하지는 않는다.

Terminology: Exposure Compensation과 Metering Mode의 역할 구분이 필요하다.

Visual Communication: 값은 강조되지만 Auto Exposure 유효 설정과 적응 시간은 보이지 않는다.

Issues: Needs Technical Verification: 유효 Metering Mode 및 본문의 Compensation 이후 재측정/자동 보정 설명.

Recommendation: 활성 Metering 설정과 적응 완료 조건을 기록하고 이 그림은 관찰된 밝기 비교로 한정한다.

## Fig8_63

Chapter / Section: Chapter 08 / 8.7.4 — Chapter08.7_Emission.md L2662

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 세 화면 모두 Manual Override와 Compensation -2/0/+2가 확인되며 밝기 변화 방향이 맞다. 실제 Camera Exposure와 고정 Emission/Bloom 값은 화면에 모두 제시되지 않았다.

Text Consistency: 어두운 검증 이미지도 허용한다는 본문 목적과 부합하므로 어두움 자체는 결함이 아니다.

Terminology: Manual Exposure와 Exposure Compensation 표기는 일치한다.

Visual Communication: Manual 및 값 강조는 좋으나 Camera 기본 노출을 재현할 정보가 부족하다.

Issues: 비교의 기준 노출과 유효 Physical Camera 설정이 불명확하다.

Recommendation: Emission=5, Bloom=0 및 유효 Camera Exposure 설정을 캡션에 기록한다. 현 검증 이미지는 밝게 보정하지 않는다.

## Fig8_64

Chapter / Section: Chapter 08 / 8.7.5 — Chapter08.7_Emission.md L3557

Status: Match

Recommended Action: Keep

Technical Accuracy: Texture R Mask×EmissionColor×Intensity를 Emissive로 출력하며 Heart 영역만 밝게 표시된다. Masks(no sRGB), sRGB Off도 확인된다.

Text Consistency: Texture, 계산 Graph, 결과 및 설정을 함께 보인다는 본문과 일치한다.

Terminology: Mask Data와 Color의 역할이 구별된다.

Visual Communication: 원본 흑백 Mask와 실제 적용 결과가 명확하게 대응한다.

Issues: 확인된 수정 필수 사항 없음.

Recommendation: 현재 그림을 유지한다.

## Fig8_66

Chapter / Section: Chapter 08 / 8.7 — Chapter08.7_Emission.md L5070

Status: Match

Recommended Action: Keep

Technical Accuracy: Emission Color × Intensity × Texture R Mask가 MF_Emission을 거쳐 기존 MatCap 합성 결과에 Add되는 연결이 보인다.

Text Consistency: Master Material 통합 결과 및 Exposure Compensation 설명과 일치한다. 현재 MatCap Alpha=1 및 Shadow Visibility=1이므로 모든 조명 조건을 검증하는 장면은 아니다.

Terminology: Emission Result와 Emissive 출력의 역할이 일치한다.

Visual Communication: 전체 그래프와 Emission 확대 영역, 하트 마스크 결과를 함께 제공한다.

Issues: 검토 범위에서 추가 불일치 없음.

Recommendation: 현재 Emission 통합 설명에 유지.

## Fig8_67

Chapter / Section: Chapter 08 / 8.8.1 — Chapter08.8_MaterialLayer.md L250

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 하단 도식이 Region Mask로 선택한 Specular Intensity를 MF_Specular 입력으로 연결한다. 실제 함수 계약 및 Fig8_68에서는 MF_Specular의 Specular Mask 출력에 선택된 Intensity를 외부 Multiply한다.

Text Consistency: 영역별 Parameter 선택 취지는 맞지만 실제 구현 위치와 함수 인터페이스를 잘못 전달한다.

Terminology: Material Slot 방식과 Mask 방식의 비교는 해당 ASF 예제로 범위를 명시해야 한다.

Visual Communication: Intensity만 바꾸는 예시에서 검정/금색 구역과 절단된 듯한 구체 표현이 재질 색상·형상 차이로 읽힌다.

Issues: 함수 입력 계약 불일치. 비교 결과에 불필요한 색상·형상 차이.

Recommendation: MF_Specular.SpecularMask × Lerp(SpecularA, SpecularB, RegionMask) 연결로 수정하고 동일 형상·색상에서 강도 차이만 비교.

## Fig8_68

Chapter / Section: Chapter 08 / 8.8 — Chapter08.8_MaterialLayer.md L1032

Status: Match

Recommended Action: Keep

Technical Accuracy: Texture R→Lerp Alpha, Specular A/B→Lerp, MF_Specular Mask×선택 Intensity→Emissive의 실제 연결이 확인된다.

Text Consistency: Texture 기반 Region Control 구현과 출력 결과가 본문과 일치한다.

Terminology: Region Mask 및 Specular Intensity의 역할이 구분된다.

Visual Communication: 마스크 구역에 따른 하이라이트 강도 차이와 관련 그래프를 동시에 확인할 수 있다.

Issues: 검토 범위에서 추가 불일치 없음. Shininess=2는 해당 비교 설정이다.

Recommendation: 현재 구현 예시로 유지.

## Fig8_69

Chapter / Section: Chapter 08 / 8.9 — Chapter08.9_DebugView.md L275

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 왼쪽이 Base Lighting→Shadow→Specular→Rim→MatCap→Emission을 직렬 처리로 그려 실제 병렬 계산과 Add/Lerp 합성을 숨긴다. Debug Mode 0=Final Color를 제시하지만 Final Color 입력 연결이 없다.

Text Consistency: 기존 계산 데이터 재사용이라는 본문 요지가 두 경로 간 명시적인 분기·공유 연결로 표현되지 않는다.

Terminology: 그림 내부 번호가 Fig8_21로 잘못 표기된다. MatCap의 '환경 반사 표현'은 저장된 외관 샘플링을 실제 환경 반사로 오해시킨다.

Visual Communication: ASF Shader Data와 각 Mask의 공급 관계 및 최종 색상 선택 경로가 불명확하다.

Issues: 합성 구조 왜곡, Final Color 입력 누락, 그림 번호 오류.

Recommendation: 공유 입력과 각 모듈 출력의 분기를 그리고 실제 Add/Lerp 합성 및 Final Color→Debug Selector 연결을 명시. 번호를 Fig8_69로 수정.

## Fig8_70

Chapter / Section: Chapter 08 / 8.9 — Chapter08.9_DebugView.md L1795

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Default를 EmissionMask(Scalar)로 표시하지만 본문 계약은 EmissionResult(Vector3)이다. MatCap 입력선이 FinalResult로, 여러 Scalar 입력선이 BaseLightingData로 합쳐 보이며 각 선택 결과에서 DebugColor까지의 연결이 없다.

Text Consistency: Mode 번호 순서는 맞지만 RGB Emission 유지 및 Scalar→Vector3 통일 설명과 불일치한다.

Terminology: EmissionMask와 EmissionResult를 혼용한다.

Visual Communication: 조건 흐름과 데이터 흐름이 같은 화살표로 섞여 선택 결과 대신 Default만 출력되는 듯 보인다.

Issues: Emission 타입/의미 오류 및 데이터 배선 오류.

Recommendation: 각 데이터 입력을 해당 선택 항목에 독립 연결하고 Scalar→Vector3 변환과 공통 출력선을 명시. Default는 EmissionResult(Vector3)로 수정.

## Fig8_71

Chapter / Section: Chapter 08 / 8.9 — Chapter08.9_DebugView.md L1868

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 실제 그래프 입력이 EmissionMask(Scalar)이고 BaseLightingData/SpecularMask/RimMask도 변환 없이 If에 직접 연결된다. 본문이 명시한 EmissionResult(Vector3) 및 명시적 Scalar→Vector3 구현을 보여주지 않는다.

Text Consistency: If의 4→0 중첩과 A>B/A<B 공통 fallback은 설명과 일치하지만 '실제 최종 구현'이라는 설명과 입력 계약이 다르다.

Terminology: EmissionMask를 EmissionResult로 교체해야 RGB 결과 재사용 계약과 일치한다.

Visual Communication: 연결은 읽을 수 있으나 검정 Preview만으로 RGB 보존을 확인할 수 없다.

Issues: 스크린샷이 본문 최종 타입 계약 이전 상태. 현재 엔진의 암시적 타입 변환 결과는 Needs Technical Verification.

Recommendation: RGB EmissionResult 입력 및 Scalar의 명시적 Vector3 변환을 반영한 그래프로 교체하고 컬러 보존 예시 추가.

## Fig8_72

Chapter / Section: Chapter 08 / 8.9 — Chapter08.9_DebugView.md L2795, L3500 (2개 참조)

Status: Match

Recommended Action: Keep

Technical Accuracy: Mode 0~5에 Final RGB, Base Lighting 회색조, Specular Mask, Rim Mask, MatCap RGB, Emission RGB가 순서대로 보인다.

Text Consistency: 두 사용 위치 모두 동일한 Debug Mode 비교/최종 검증 목적과 일치한다.

Terminology: 본문 Mode 매핑과 화면 수치가 일치한다.

Visual Communication: 동일 장면의 6개 결과 및 각 DebugMode 값이 보여 비교 가능하다.

Issues: 추가 불일치 없음. Fig8_70/71의 이전 계약과 달리 실제 RGB Emission 결과가 보인다.

Recommendation: 유지. 앞선 구조도와 함수 화면을 이 최종 계약에 맞출 것.

## Fig8_73

Chapter / Section: Chapter 08 / 8.10 — Chapter08.10_FinalFramwork.md L414, L4103 (2개 참조)

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 실제 모듈 출력 분기, Add/Lerp, RGB EmissionResult→DebugView가 확인된다. 다만 ShadowVisibility는 상수 Parameter 1이며 MatCap Lerp Alpha=1로 앞선 조명 합성의 기여가 제거된다.

Text Consistency: 두 위치의 최종 Architecture 설명에는 맞지만 모든 기능의 최종 기여를 검증했다는 주장은 이 설정만으로 뒷받침되지 않는다.

Terminology: MF_Matcap 표기는 본문의 MF_MatCap과 대소문자가 다르다.

Visual Communication: 전체 구조는 유용하나 넓은 그래프의 작은 글씨와 교차 선이 추적을 어렵게 한다.

Issues: 현재 테스트 설정 및 수동 Visibility 계약을 명시할 필요.

Recommendation: Alpha와 Visibility의 현재 값/역할을 주석으로 명시하고 전체 기능 합성 검증은 각 기여가 남는 설정으로 별도 제시.

## Fig8_74

Chapter / Section: Chapter 08 / 8.10 — Chapter08.10_FinalFramwork.md L1676, L4109 (2개 참조)

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Final Composition을 모든 Feature의 단순 Add로 표시하지만 실제 MatCap은 Lerp다. MF_Shadow 아래의 ShadowVisibility/LightingResult가 출력처럼 배치되나 실제 입력이다. MF_BaseLighting의 Direct/Indirect 일반화는 현재 구현을 넘어선다.

Text Consistency: 두 참조에서 주장하는 실제 Graph와 추상 Data Flow 일치가 성립하지 않는다. Core Lighting→모든 Feature의 직렬 흐름도 실제 공유 입력 분기를 숨긴다.

Terminology: 우상단 ASF 확장이 Art Stylized Foliage로 잘못 표기된다. 현재 Ari’s Shader Framework로 통일 필요. MatCap을 화면 반사 효과로 한정하지 말 것.

Visual Communication: 6단계 분류는 읽기 쉽지만 단계 간 굵은 화살표가 실제 데이터 의존 관계로 오해된다.

Issues: Lerp 누락, 함수 입출력 방향 혼동, 브랜드 오류, 계산 범위 과장.

Recommendation: Input의 병렬 분기와 각 함수의 입력/출력을 구분하고 실제 Add→Lerp→Add 연결 및 Debug 데이터 분기를 명시. 브랜드 교정.

## Fig9_01

Chapter / Section: Chapter 09 — Chapter09_RenderingDebugandOptimization.md L39

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 측정 그래프 후반 GPU가 약21ms로 가장 긴데 같은 구간 Render Thread 약7ms에 CPU 병목이라는 라벨을 붙인다. 표시된 값과 병목 판정이 충돌한다.

Text Consistency: 측정→원인 분리→수정→재측정 취지는 맞다. 42→120 FPS 및 비용 절감 수치는 측정 출처 없이 실제 Before/After처럼 표현된다.

Terminology: 단일 이미지 안에 Fig9_01과 Fig9_02를 함께 표기하여 실제 별도 Fig9_02와 충돌한다.

Visual Communication: 두 개의 조밀한 인포그래픽이 한 이미지에 들어가 핵심 그래프와 예시 수치의 의미를 흐린다.

Issues: 병목 라벨 오류, 그림 번호 충돌, 예시 수치와 실측 구분 누락.

Recommendation: 동일 시점의 가장 긴 작업과 판정을 일치시키고 모든 가상 수치에 Illustrative Example 표시. 내부 번호를 실제 참조와 일치시킬 것.

## Fig9_02

Chapter / Section: Chapter 09 / 9.2 — Chapter09_RenderingDebugandOptimization.md L683

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: 좌측 시간축은 CPU Prepare Frame N과 GPU Render Frame N을 거의 동시에 시작시켜 본문의 다른 Frame 간 overlap을 전달하지 못한다. 동일 Frame 전체 준비가 끝나기 전 GPU 전체 작업이 진행되는 듯 보인다.

Text Consistency: 본문은 Game/Render/GPU가 서로 다른 Frame을 처리하는 예시와 동기화 예외를 명시하지만 그림은 CPU 두 Thread를 하나로 묶고 Frame 번호 의존 관계를 생략한다.

Terminology: ASF를 Art · System · Framework로 잘못 확장한다.

Visual Communication: 우측 병목 비교는 유용하나 GPU 작업을 CPU 뒤로 밀어 배치하여 throughput과 단일 Frame latency를 혼동시킬 수 있다.

Issues: Frame 번호/작업 의존 시각화 오류. 실제 엔진 Queue/Thread 타이밍은 Needs Technical Verification.

Recommendation: Game, Render, GPU의 별도 lane에 Frame N/N−1 등의 의존 화살표를 표시하고 steady-state 간격을 Frame Time으로 정의. 브랜드 교정.

## Fig9_03

Chapter / Section: Chapter 09 / 9.3 — Chapter09_RenderingDebugandOptimization.md L1285

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: Vertex→Primitive→Rasterization 요지는 맞으나 Rasterization을 '화면 Pixel로 변환'에서 끝내 최종 Pixel 색상 생성과 혼동할 수 있다. Skinning 위치는 구현에 따라 달라질 수 있다.

Text Consistency: Triangle Count만으로 병목을 판단하지 않는다는 본문과 일치한다. 500/5,000/50,000 Vertex 수치는 예시임을 밝히지 않았다.

Terminology: ASF를 Art · System · Framework로 잘못 표기.

Visual Communication: LOD 예시가 동일한 낮은 밀도의 흉상을 거리별로 축소한 듯 보여 실제 topology 감소가 명확하지 않다.

Issues: 예시 수치, Rasterization 출력 의미, LOD 밀도 변화 설명 보완.

Recommendation: Rasterization→covered samples/fragments→Pixel Processing 연결과 LOD별 실제 Triangle 수를 추가하고 브랜드 교정.

## Fig9_04

Chapter / Section: Chapter 09 / 9.4 — Chapter09_RenderingDebugandOptimization.md L2156

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Overdraw 도식이 같은 Pixel의 순서를 Hair→Cloth→Opaque Face로 명시하여 일반적인 투명 합성 설명으로 부적절하다. 겹침/깊이 테스트/합성 순서를 구분하지 않는다. LOD 설명은 Geometry Detail 감소가 화면 Pixel 수를 줄인다고 단정한다.

Text Consistency: Screen Coverage와 반복 처리라는 본문 요지는 맞지만 같은 화면 크기의 LOD 변경이 coverage를 자동 감소시키지는 않는다.

Terminology: ASF를 ARTIST SURVIVAL GUIDE로 잘못 확장. Opaque/Masked/Translucent 구분 필요.

Visual Communication: 1x~8x 열지도는 실측 도구/조건 없이 정량 결과처럼 보인다. 순수 개념 그림인지 명시가 없다.

Issues: 투명 합성 순서 및 LOD-Pixel 인과 오류, 브랜드 오류. 엔진별 depth/overdraw 집계는 Needs Technical Verification.

Recommendation: 동일 Sample을 덮는 층과 실제 실행/깊이 탈락을 구분. LOD는 Geometry 비용과 별도 설명하고 열지도는 가상 예시로 표기.

## Fig9_05

Chapter / Section: Chapter 09 / 9.5 — Chapter09_RenderingDebugandOptimization.md L3089

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 비용 요소 설명은 대체로 맞으나 If와 Lerp를 함께 Branching으로 분류하여 보간 연산과 실제 동적 실행 분기를 혼동시킨다. Material Graph→Texture→Math→Masks→Lighting 직렬 화살표도 고정 실행 단계처럼 읽힌다.

Text Consistency: Node 수가 실제 비용과 같지 않다는 본문 핵심은 유지한다. 50/200/600 Instruction 수치는 근거 없는 예시 수치로 표시 필요.

Terminology: Branching과 Blending을 분리할 것. Custom HLSL이라는 작성 방식 자체로 비싸다고 판단하지 않도록 범위 명시.

Visual Communication: 단순/복잡 외관과 Faster/Slower를 직접 연결하므로 동일 조건의 측정 예시와 구분 필요.

Issues: 비용 요소와 실제 실행 순서 혼용. 컴파일된 분기 및 성능 효과는 Needs Technical Verification.

Recommendation: Lerp를 Blend로 이동하고 비용 요소를 병렬 목록으로 표시. 수치와 속도 비교는 예시임을 명시하고 실제 GPU timing 조건 추가.

## Fig9_06

Chapter / Section: Chapter 09 / 9.6 — Chapter09_RenderingDebugandOptimization.md L4205

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 100K Triangle의 1/10 Section 비교를 정확히 1/10 Draw Call로 고정한다. 이는 단일 Pass·일반적인 비병합 draw 예시라는 조건이 필요하며 전체 Frame 총 Draw와 같지 않다.

Text Consistency: 본문의 '일반적인 경우', '필요할 수 있다'보다 그림의 1:1 대응이 강하다. 비용 측정 후 최적화 방향은 일치한다.

Terminology: Fig 9.06 표기를 실제 Fig9_06 규칙과 통일 권장.

Visual Communication: Mesh/Material→Command→CPU→GPU 도식은 이해 가능하나 CPU에서 Command를 준비한다는 포함 관계를 표현하면 더 명확하다.

Issues: Section/Slot/Draw의 무조건 1:1 대응을 피할 조건 주석 필요. 실제 batching/instancing 효과는 Needs Technical Verification.

Recommendation: 비교에 '단일 Pass의 단순 예시'를 추가하고 추가 Pass, batching/instancing에 따른 차이를 명시.

## Fig9_07

Chapter / Section: Chapter 09 / 9.7 — Chapter09_RenderingDebugandOptimization.md L5357

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: Frustum Culling 설명이 'Objects outside the camera view are rendered.'로 되어 본문 및 붉은 X 표시와 정반대다.

Text Consistency: LOD/Culling의 역할 구분은 맞지만 거리 기준 0~10/10~30/30~100m와 Triangle 비율은 설정 예시임을 명확히 해야 한다.

Terminology: 전체 문장이 영어여서 한국어 중심 본문 및 앞뒤 Figure의 편집 언어와 일관성이 낮다.

Visual Communication: LOD2/3를 흐림·픽셀화로 표현하여 Geometry 감소보다 해상도 저하로 보인다. 성능 비교는 Example 표기가 있으나 실측 출처는 없다.

Issues: Frustum Culling 문장 반전이 핵심 오류. LOD의 시각적 표현과 설정 조건 보완.

Recommendation: 'are not rendered'로 교정. 동일 화면 크기 Wireframe으로 topology 감소를 보여주고 거리/비율/성능 수치는 가상 설정 예시로 명시.

## Fig9_08

Chapter / Section: Chapter 09 / 9.8 — Chapter09_RenderingDebugandOptimization.md L6515

Status: Major Mismatch

Recommended Action: Major Revision

Technical Accuracy: stat unit 예시의 Frame16.7ms는 Game6.3/Draw5.8/GPU10.2ms보다 크다. 이 예시에서 CPU/GPU 중 하나를 바로 확정할 수 없으며 대기·제한 요인 확인이 필요하다. 명령 표의 r.ViewMode ShaderComplexity, r.ViewMode QuadOverdraw 등의 실제 지원 여부는 Needs Technical Verification.

Text Consistency: 도구별 목적은 본문과 대체로 일치하지만 도식화된 timeline/숫자/뷰를 실제 Unreal 도구 화면처럼 제시한다.

Terminology: GPU Profiler(stat gpu)와 ProfileGPU의 역할 및 실제 명령 표기를 대상 엔진 버전에 맞춰 통일 필요.

Visual Communication: Debug View 범례와 수치가 재구성 예시임이 표시되지 않아 측정 화면으로 오인할 수 있다. Quad Overdraw를 단순 겹침 횟수로만 요약한다.

Issues: 실행 안내 명령 검증 필요, 예시 화면 출처/버전 누락, 병목 예시의 해석 조건 누락.

Recommendation: 대상 Unreal 버전에서 명령과 View Mode 진입법을 확인해 교정하고 검증된 화면/범례 사용. Frame gap의 의미와 예시/실측 구분을 표시.

## Fig9_09

Chapter / Section: Chapter 09 / 9.9 — Chapter09_RenderingDebugandOptimization.md L7719

Status: Minor Mismatch

Recommended Action: Minor Revision

Technical Accuracy: 측정→병목 식별→원인 분석→수정→재측정 원칙은 맞다. Profiling Tools가 원인 분석 다음의 독립 단계로만 배치되어 앞 단계에서도 측정 도구를 사용한다는 관계가 약하다.

Text Consistency: 본문의 최적화 절차 및 한 번에 하나의 조건 변경, 품질과 성능 검증 원칙과 일치한다.

Terminology: ASF를 ART · SYSTEM · FRAMEWORK로 잘못 확장한다.

Visual Communication: 7단계와 하단 확장 흐름은 읽기 쉽다. 재측정에서 분석으로 되돌아가는 반복 연결이 있으면 더 명확하다.

Issues: 브랜드 오류 및 도구 사용/반복 흐름 보완.

Recommendation: 브랜드를 Ari’s Shader Framework로 교정. Profiling Tool을 측정·분석 전반에 연결하고 Measure Again의 반복 화살표 추가.

# Audit Progress

Completed Chapters:
- Chapter 01
- Chapter 02
- Chapter 03
- Chapter 04
- Chapter 05
- Chapter 06
- Chapter 07
- Chapter 08
- Chapter 09

Current Chapter:
- None

Last Completed Figure:
- Fig9_09

Next Figure:
- None

Remaining Chapters:
- None

Status:
Complete


