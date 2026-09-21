# Foundation Phase 2 — Figure Revision Log

작업 루트: `C:\Users\kmcoo\Desktop\PW\ASF_Review`.
판단 순서: Current Markdown > Current Architecture / Standard > Refactoring Log > Figure Audit.
Documentation Figure만 필요에 따라 수정. 실제 Unreal Screenshot은 합성·재생성하지 않으며 현재 본문과 맞지 않으면 재촬영 Queue에 기록한다. 현재 본문 참조 대상은 고유 Figure 154개이다.

## Fig1_01

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.1 What is Rendering?

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
입력→Rendering→Image 관계는 본문과 일치하나 설명 문장의 언어 규칙 보완이 필요.

Changes:
기존 패널·아이콘·화살표·색상·배치를 유지하고 설명 문장을 Korean으로 수정. Light 사용 여부는 Rendering 방식에 따른다는 주석 추가. 기존 Filename/Path 유지.

Technical Verification:
현재 1.1 본문의 Geometry/Material/Light/Camera와 2D Pixel 관계 대조. Light를 모든 Rendering의 필수조건으로 단정하지 않음. Type A이며 실제 Engine Evidence 아님.

Text Verification:
출력 이미지의 Geometry/Material/Light/Camera/Rendering/Pixels 설명 및 Caption/주석을 모두 육안 확인. 한글 깨짐·오탈자·잘림 발견 없음.

Final Status:
Complete

Generation Method:
Built-in image_gen edit. 기존 이미지 참조, Minor text localization, 구조 보존.

Prompt Specification:
기존 English Technical Labels 유지; Geometry=형태를 구성하는 Mesh, Vertex, Triangle; Material=Surface의 특성(예: Color, Texture, Roughness); Light=조명에 사용하는 정보(예: Directional, Point, Spot); Camera=관찰 위치와 투영 설정(예: FOV, Aspect Ratio); Rendering=3D Scene 정보를 처리하여 2D Pixel 값을 계산한다.; Pixels=색상 값이 배열된 2D 격자(예: RGB 또는 RGBA); Caption=Fig1_01. Rendering은 3D Scene 정보로 최종 2D Image를 만든다.; Note=Light 사용 여부는 Rendering 방식에 따라 다르다.

## Fig1_02

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.2 From Model to Screen

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Rasterization과 Interpolation 사이 줄 연결이 누락됨. 설명 언어와 논리적 순서의 적용 범위를 명확히 할 필요.

Changes:
10개 카드와 아이콘 유지. 1–10 연속 번호 및 5→6 연결 추가. 설명문 Korean 교정. Depth Test를 저장값 비교로 표현, 실행/기록 조건 주석 추가.

Technical Verification:
현재 1.2의 10단계 흐름과 대조. Early Depth 등 실제 순서의 조건을 명시. 연결 방향 5→6 및 나머지 좌→우 확인.

Text Verification:
10개 카드의 Korean 문구와 하단 Caption/주석 모두 육안 확인. 오탈자·깨짐·잘림 발견 없음.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit. 기존 카드/아이콘/배치 유지, 단계 번호와 5→6 connector 추가, 각 카드 역할을 Korean으로 설명, 논리적 단순화 및 Early Depth 조건 명시.

## Fig1_03

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.3 Vertex and Vertex Attributes

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Rendering/Normal Map/Texture/Vertex Color/Skinning/Custom Data 표기 혼용.

Changes:
해당 Technical Term을 English로 통일. 원래 Attribute 관계선과 UV Seam/Hard Edge 비교, 숫자 예시 유지. Figure 식별자 Fig1_03 정렬.

Technical Verification:
현재 1.3의 Attribute 묶음과 같은 Position에서 UV/Normal 차이에 따른 Vertex 분리를 대조. Position/UV/Normal 숫자 보존 확인.

Text Verification:
모든 패널과 하단 설명 육안 검수. Korean 조사, 숫자, English 표기 및 잘림 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit; 기존 배치·아이콘·선·수치 유지, Technical Term 음역을 English로 교정.

## Fig1_04

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.4 Vertex Processing

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Rasterization 이후 후보와 최종 Pixel 기록의 구분 필요.

Changes:
3열 주 도식 유지. 하단 설명을 Coverage/Fragment 후보→Shading·Visibility·Output 조건→Buffer 기록으로 교정. Caption Korean 정리.

Technical Verification:
현재 1.4의 Vertex 단위 처리 및 다음 Primitive Assembly 흐름과 대조. Position Clip Space와 다른 Attribute 구분 유지.

Text Verification:
출력 전체와 변경한 하단 2문장/Caption 육안 확인. 문구 잘림·오타 발견 없음.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit. 하단 두 문장 및 Caption만 교정, 나머지 도식 보존.

## Fig1_05

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.5 Primitive Assembly

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Index와 Triangle 색 영역 불일치, Winding 화살표 오류, 입력 Buffer와 처리 결과 혼동.

Changes:
4개 Corner로 구성한 Quad의 A[0,1,2]/B[0,2,3] 및 공유 대각선 0–2를 정확히 표시. CCW/CW 순환 화살표 수정. Front=CCW는 예제 설정으로 한정. Vertex Input→Shader→Processed Outputs와 별도 Index 입력 구분.

Technical Verification:
현재 1.5 본문 Index/Shared Vertex/Winding 설명과 대조. 표의 좌표와 Corner 위치, 두 Triangle의 꼭짓점, 각 순환 Arrow 확인. Shader 결과를 Input Vertex Buffer에 저장한다는 잘못된 문장은 2차 교정으로 제거.

Text Verification:
수치 표·Korean 설명·Caption·Chapter 이름 모두 육안 확인. 한글 오타·잘림 없음.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen, 기존 Style를 참고한 Major Revision 및 1회 후속 텍스트 교정. Quad 표와 Winding 비교 및 두 입력 Data Flow로 재구성.

## Fig1_06

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.6 Culling and Clipping

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Normal 기반 Backface 판정 및 모든 Culling을 같은 Stage로 표현한 오류.

Changes:
Object Bounds/Frustum과 Triangle Backface를 분리. Front=CCW/Cull=Back 조건과 꼭짓점 순서 명시. Clipping의 유효 Half-plane 및 두 교점으로 남는 사각형 표현. Pass별 필요성과 실행 단계 차이 주석 추가.

Technical Verification:
현재 1.6의 Winding/Rasterizer 판정 및 Vertex Normal과의 구분 대조. 처음 생성된 곡선 화살표의 방향 오류는 제거하고 정확한 Vertex 순서로 교정. Outside 한 꼭짓점과 Inside 두 꼭짓점의 Clipping 결과 확인.

Text Verification:
모든 Korean 문구·Inside/Outside·CCW/CW 순서 및 Footer 육안 확인. 글자 깨짐·잘림 없음.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 서로 다른 Culling 예제와 Clip Plane Before/After를 구분하고 1회 후속 Winding 교정.

## Fig1_07

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.7 Rasterization

Previous Audit Status:
Match / Keep

Action:
Keep

Reason:
현재 본문의 Screen-space Triangle→Coverage→Fragment 후보 및 최종 Pixel과의 구분에 맞음.

Changes:
None. 이미지 원본 유지.

Technical Verification:
실제 이미지와 현재 1.7의 삽입 맥락 대조. 후보 생성과 최종 색 계산을 구분하는 문구 확인. 기본 Coverage 예시의 범위 유지.

Text Verification:
패널별 Label, Korean 설명 및 핵심 요약 판독. 수정이 필요한 내용 불일치 발견 없음.

Final Status:
Complete

## Fig1_08

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.8 Interpolation

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Technical Term 음역 혼재 및 개념용 Gradient의 정량적 해석 위험.

Changes:
Fragment Shader/Texture Sampling/Barycentric Coordinate 및 Fragment 표기 정리. 색 Gradient는 개념 예시임을 표시하고 Perspective-correct 조건을 본문으로 연결. 기존 배치, Vertex/UV 값 유지.

Technical Verification:
현재 1.8의 Attribute→Fragment 보간→UV Sample 흐름 대조. 선택점은 Marker이며 실제 색값으로 해석하지 않음. UV 수치 보존 확인.

Text Verification:
첫 결과의 남은 음역은 후속 교정. 최종본 전체 Korean/English 설명, 수치와 Footer 육안 검수.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit; 배치와 수치 유지, 용어 및 설명문 교정, Gradient 범위 주석 추가.

## Fig1_09

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.9 Fragment / Pixel Processing

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
UV와 Texture, Parameter 입력과 계산 목록, Fragment Output과 최종 Pixel의 경계 불명확.

Changes:
3열 주 구조 유지. UV를 좌표 아이콘으로 수정. 중앙은 실행 순서가 아닌 입력/계산 예시 목록으로 명시하고 잘못된 분기 연결 제거. Texture Resource+UV→Sample→현재 값 별도 표시. World Position 예시 및 최종 Pixel 미확정 명시.

Technical Verification:
현재 1.9 본문 입력/계산/출력과 후속 Depth/Blending 관계 대조. Parameter를 Shader가 생성한다는 흐름 제거 확인.

Text Verification:
전체 문구와 하단 요약 육안 확인. 한글 깨짐·내용상 오류 발견 없음.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit; 기존 패널 유지, 모호한 Label/연결/UV 아이콘 및 요약 교정.

## Fig1_10

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.10 Depth Test and Surface Visibility

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Depth 비교 규약/Write 조건 누락, Depth→Color 오해, Shadow Map=Visibility 등치.

Changes:
Opaque/LESS/작은 값이 가까움/Write On 조건 명시. 저장 0.4와 새 0.2/0.7 비교 예시. Pass의 Color/Depth 기록 분리. Shadow Map+Receiver Depth→Compare→Light Visibility 표현. Reversed-Z 조건 주석.

Technical Verification:
현재 1.10의 비교·Depth Write 및 Shadow 관련 경계 대조. 0.2<0.4 True, 0.7<0.4 False 확인. Color와 Depth Buffer 사이 잘못된 생성 의존성 제거.

Text Verification:
모든 수치·부등식·Korean 문구 확인. 후속 교정으로 Depth 용도의 불필요한 절대화 문장을 제거.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 예제 조건과 기록 분기, Shadow 자원/판정 관계를 재구성하고 1회 문구 교정.

## Fig1_11

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 01 / 1.11 Framebuffer and Final Image

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
기본 Depth를 Shader 필수 출력처럼 표현, 서로 다른 Scene 예시의 불연속, 최종 처리/기록 조건 누락.

Changes:
기존 3열/삽화 유지. Color Output와 Raster Depth 구분 및 선택적 Override 표시. 서로 다른 삽화를 독립 설명 예시로 한정. Write 조건, 필요 Post Process→Display Target→Present 추가.

Technical Verification:
현재 1.11의 기본 Depth와 Shader override 및 Buffer/표시 관계 대조. 이 이미지는 실제 실행을 검증하는 Screenshot이 아닌 개념 합성 도식으로 분류.

Text Verification:
전체 Korean 설명·수치·변경 Label 육안 확인. 본문의 과거 Figure 한계 안내 한 문장을 새 Figure와 맞추어 갱신.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit; 도식과 기존 삽화는 보존 요청, Label/주석/하단 Flow만 교정.

## Fig1_12

Type:
Unreal Screenshot / Verification Evidence

Classification Note:
전체 구성은 Infographic이지만 Character Scene/Rendering 패널의 캡처 출처를 현재 자료만으로 확정할 수 없어 Screenshot 포함 복합 이미지로 보수적으로 보호한다. 실제 Unreal 실행 증거임을 새로 인증한 것은 아니다.

Chapter / Section:
Chapter 01 / 1.12 CPU, GPU and Draw Calls

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Caption / Reference Revision

Evidence Purpose:
기존 Character Scene/결과 패널 보존. 문서에서는 CPU 준비와 GPU 실행의 개념 예시로만 사용.

Current Text Consistency:
현재 1.12의 기본 관계와 일치. 중앙은 Draw가 참조하는 Data/State이고 Buffer 전체 반복 업로드가 아님을 삽입 문단에서 명시. Pass/Section/Instancing에 따른 Draw 수 차이와 CPU-driven 예시 범위 추가.

Issue:
기존 이미지의 자원 전달 표현이 모호하며 Character 화면의 Engine/Version/출처가 명시되지 않음.

Required Follow-up:
실제 구현 Evidence로 재사용할 때 캡처 출처·Engine·설정을 먼저 확인. 현재는 개념 설명용 기존 자료로 한정하므로 재촬영을 필수로 판정하지 않음. 이미지 AI 편집 없음.

Final Status:
Keep

## Fig1_13

Type:
Unreal Screenshot / Verification Evidence

Classification Note:
개념 도식 안에 Editor/Character Rendering 화면이 포함된 복합 이미지. 실제 캡처일 가능성을 배제할 수 없어 원본을 보수적으로 보호. Unreal 실행을 새로 검증했다는 의미 아님.

Chapter / Section:
Chapter 01 / 1.13 Complete Rendering Pipeline

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Caption / Reference Revision

Evidence Purpose:
기존 Scene/Editor/Rendering 패널 보존. 현재는 Pipeline 개요의 참고 삽화로 한정.

Current Text Consistency:
본문에 Geometry/Screen Processing Group, Frustum Object 선별과 Primitive 처리 구분, Framebuffer/Render Target 구분을 명시하여 오래된 이미지 Label의 해석을 교정.

Issue:
일부 작은 글자가 뭉개져 있으며 캡처 출처와 설정 미상. 개념 도식과 실제 화면이 혼합됨.

Required Follow-up:
향후 편집 가능한 원본으로 도식 영역을 수정할 경우 캡처 패널은 그대로 보존하고 분리 배치 권장. 작은 Label은 본문을 기준으로 읽도록 안내. 현재는 실제 구현 완료의 Evidence로 사용하지 않음. 원본 Screenshot을 새로 요구할 근거가 없어 재촬영 필수로 판정하지 않음.

Final Status:
Keep

## Fig2_01

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 02 / 2.1 Why Coordinate Systems Matter

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
View Forward와 Z 부호 충돌, Local Point와 축 대응 불명확.

Changes:
Local (1,0,0)을 +X 위에 표시. Rotation Identity/Scale 1/T=(5,2,0)에서 World (6,2,0), Camera C=(4,1,5), Identity에서 View (2,1,-5)의 계산 예시를 명시. View Forward=-Z 및 Origin≠필수 중심 조건 추가.

Technical Verification:
현재 2.1 본문 Local/World 값과 같은 Point의 기준 변경 대조. Translation 합과 Camera 차 계산 확인. 초기 편집 결과의 잘못된 양방향 T 화살표가 반복되어 채택하지 않고 해당 중간 도식을 수식 카드로 재구성한 최종본 사용.

Text Verification:
전체 Korean·좌표·수식·방향 Label 육안 검수. 부호/계산식/화살표 일치.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen. Major Revision 최종본은 세 Space 카드와 정확한 Transform 조건/계산식으로 재생성. 잘못된 중간 결과는 Project에 저장하지 않음.

## Fig2_02

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 02 / 2.2 Position, Direction and Vector

Previous Audit Status:
Match / Keep

Action:
Keep

Reason:
현재 본문의 Position/Direction/Vector 및 Translation 차이와 일치.

Changes:
None.

Technical Verification:
실제 이미지와 현재 2.2 대조. B(4,3,2)-A(1,1,0)=(3,2,2) 및 Direction의 Translation 불변 확인. 도식은 축척 없는 관계 예시로 해석.

Text Verification:
Label/좌표값/Korean 설명 판독. 필수 수정 사항 발견 없음.

Final Status:
Complete

## Fig2_03

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 02 / 2.3 Local Space / Object Space

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Rotation=45도 조건과 Rotation 없는 World 결과가 충돌.

Changes:
계산 예시는 Translation=(5,2,1), Rotation=(0,0,0), Scale=(1,1,1)로 통일. 대응 Cube의 회전 제거. Local(1,1,1)+Translation=(6,3,2) 식 추가. Object/Edit Mode 설명 구조 유지.

Technical Verification:
현재 2.3의 Rotation/Scale 없는 예제와 대조. 조건과 수식 일치 확인. 일반 Transform 설명과 특정 계산 예제 조건 구분.

Text Verification:
Transform 숫자, Korean 설명, Local/World Label 육안 검수.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen edit. 목적과 4개 패널을 유지하면서 잘못된 회전 조건·Object 방향·계산 대응을 교정.

## Fig2_04

Type:
Documentation Figure / Infographic

Chapter / Section:
Chapter 02 / 2.4 World Space

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Object 배치와 World 좌표 부호 불일치, Local 카드에 World 좌표를 무표기로 재사용.

Changes:
오류가 있는 공간 배치 도식을 명시적인 Object Origin in World 표로 교체. 각 Local Origin=(0,0,0)과 World 위치를 별도 카드로 분리. 정확한 Translation-only 예제 유지.

Technical Verification:
현재 2.4의 공통 World 기준/개별 Local 기준 관계 대조. A/B/C 값의 Space 명시, (1,1,1)+(5,2,0)=(6,3,1) 확인.

Text Verification:
표·수식·Korean 설명·음수 부호 육안 검수. 기존 파일명/경로 유지.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 4개 패널/색상 구조를 유지하고 오해를 만드는 좌표 배치를 명확한 기준별 값 비교로 변경.

## Fig2_05

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.5 View Space

Previous Audit Status:
Match / Keep

Action:
Keep

Reason:
World와 Camera 기준의 차이를 설명하며, View Space도 3D라는 현재 본문 및 Forward 축 부호의 Engine/API별 차이와 일치함.

Changes:
없음. 기존 이미지 유지.

Technical Verification:
World/View의 기준점, Camera 기준 변환 및 축 관례 주석을 실제 이미지와 현재 본문으로 대조함.

Text Verification:
제목, World/View 좌표계 라벨 및 Forward 부호 주석 육안 확인.

Final Status:
Complete

## Fig2_06

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.6 Projection

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Projection Matrix 출력과 전체 화면 변환 효과를 구분할 필요가 있음.

Changes:
기존 3개 패널과 크기 비교 구성을 유지하고 View → Projection Matrix → Clip → Perspective Divide → NDC → Viewport → Screen 흐름 명시. 가림을 제외한 독립적 크기 비교임을 표시.

Technical Verification:
현재 본문의 View 3D, Clip 출력, Divide/Viewport 단계 및 Depth 유지 설명과 대조. 축 관례 주석 유지.

Text Verification:
전체 Korean 문장과 단계 라벨 육안 확인. 첫 생성의 상단 글자 겹침을 재수정하고 최종본에서 해소 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen, 기존 그림 기반 최소 수정. 좌표 변환 흐름과 독립 비교 조건 교정 후 상단 부제만 추가 교정.

## Fig2_07

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.7 Clip Space

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Clip/NDC 혼동과 보편적인 Z 범위 단정을 제거해야 함.

Changes:
Clip Cube 대신 (x,y,z,w)와 clipping inequalities 표시. Z=0~w 관례 및 대안 명시. Divide 예시와 NDC 범위를 정렬하고 Screen Origin/축 방향, 연속 경계와 Pixel index를 구별.

Technical Verification:
(2,1,3,4)/4=(0.5,0.25,0.75), Clip 조건, Clipping → Divide → NDC → Viewport 순서 확인. Screen 수식은 Top-left/+Y Down 예시와 일치.

Text Verification:
각 패널의 Korean 문장, 수식, 부등호 및 전체 흐름 육안 검수. 원래 파일명과 참조 유지.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 네 패널 구조 유지, 잘못된 Cube를 좌표/수식 카드로 교체하고 관례를 명시.

## Fig2_08

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.8 Homogeneous Coordinate and W

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Translation의 Matrix 적용과 직접 덧셈을 구별하고 NDC/Screen 혼용을 해소해야 함.

Changes:
Translation Matrix와 열벡터 곱 표기. 혼동되는 작은 투영 삽화를 같은 Clip x/y, 서로 다른 양의 w의 수치 예시로 변경.

Technical Verification:
Position w=1 / Direction w=0의 affine 입력 역할과 Projection 이후 w 역할 구분 유지. Near/Far Divide 결과를 계산하여 확인.

Text Verification:
Korean 문장, Matrix 곱, 전치 표기 및 수치 육안 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 네 패널 유지, Translation 표기 및 부수적인 Perspective 예시만 교정.

## Fig2_09

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.9 Perspective Divide and NDC

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
같은 Camera Ray와 같은 X Offset 혼동, NDC 경계 밖 좌표 표시 오류.

Changes:
Vertex A/B, 명시적 View/Clip 가정 및 계산 카드로 정렬. NDC A를 +1 경계에 배치하고 B에 0.2 눈금 추가. 같은 Camera Ray의 투영 위치는 같다는 제한 명시.

Technical Verification:
x_clip=x_view, w_clip=z_view 예시에서 2/2=1, 2/10=0.2 확인. NDC plot의 대응 눈금 및 경계 위치 확인. Z 출력은 생략임을 명시.

Text Verification:
모든 Korean 설명, 좌표 첨자, 수치 육안 검수. B 위치는 추가 수정 후 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 3개 패널 유지, 오류가 있는 공간 삽화를 데이터 카드로 교체하고 정확한 NDC 눈금으로 보완.

## Fig2_10

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.10 Viewport Transform and Screen Space

Previous Audit Status:
Match / Keep

Action:
Keep

Reason:
현재 본문의 좌표 변환과 Viewport 개념에 일치함.

Changes:
없음.

Technical Verification:
1920×1080, Top-left Origin, Y Down에서 NDC (0.5,0.5) → (1440,270), 중심 (960,540) 계산 확인. Screen 전체와 Viewport 구분 확인.

Text Verification:
실제 이미지의 좌표 라벨, 축 방향과 Korean 설명 육안 확인.

Final Status:
Complete

## Fig2_11

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.11 Matrix Transform Basics

Previous Audit Status:
Match / Keep

Action:
Keep

Reason:
현재 본문의 Matrix 기초 역할과 열벡터 convention에 일치함.

Changes:
없음.

Technical Verification:
4×4 Matrix × Column Vector, affine Position/Direction w 구분, Model → World / View → View Space / Projection → Clip 대응을 본문과 확인.

Text Verification:
실제 이미지의 수식과 Korean 설명 및 주요 Label 육안 확인.

Final Status:
Complete

## Fig2_12

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.12 Model / View / Projection Matrix

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
기준점과 변환 조건 없는 공간 삽화가 수치 예시와 불일치함.

Changes:
Local (1,0,0), Model Translation (4,3,2), World (5,3,2), Camera (3,2,10), View (2,1,-8)의 일관된 계산 표시. Identity Rotation, Scale=1, View Forward=-Z 명시. Clip은 Frustum 대신 Homogeneous 출력으로 표현.

Technical Verification:
열벡터 및 P×V×M 순서, View 역변환과 산술 확인. 생성 초안의 불필요한 전치 기호를 제거한 최종본 확인. Projection 수치는 설정 없으므로 기호 유지.

Text Verification:
전체 Korean 문장, 좌표값 및 열벡터 표기 육안 검수. Local Origin과 Vertex 위치를 별도로 명시함.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 네 단계와 역할 표 유지, 모호한 공간 그림을 변환 조건/좌표 카드로 교체.

## Fig2_13

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.13 Position Transform vs Direction Transform

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Transform 구성 목록의 +가 Matrix 덧셈으로 오해될 수 있음.

Changes:
구성 목록을 쉼표로 변경. 열벡터 M=T·R·S와 실제 적용 순서 명시. Normal 관련 참조를 현재 절과 다음 Tangent Space로 구체화.

Technical Verification:
Position/Direction의 Translation 차이와 Normal Inverse Transpose 주의 유지. 열벡터 적용 순서 확인.

Text Verification:
전체 Korean 문장, 수식 및 표 육안 검수.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 레이아웃과 비교 도식 유지, 구성/연산 기호와 절 참조만 교정.

## Fig2_14

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.14 Tangent Space

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
RGB Encoding과 Decode된 방향 성분 및 변환 출력 기준을 구별해야 함.

Changes:
Texture + UV → Sample → Decode → Tangent Normal 흐름, 0~1 RGB와 Decode 예시 및 중복 Decode 금지 조건 명시. World Basis 열벡터 TBN과 World XYZ 출력으로 정렬.

Technical Verification:
정규직교 Basis 가정, normalize(TBN × n_tangent), 평면 예시 (0.5,0.5,1) → (0,0,1) 확인. Sampler 동작은 조건부 설명으로 제한, 실제 Engine 검증을 주장하지 않음.

Text Verification:
전체 Korean 문장과 수식 육안 검수. Mirrored UV/Seam/Normalize 주의 유지.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 8개 구역 유지, Sample/Decode와 Basis 변환의 경계를 보완.

## Fig2_15

Type:
Type A — Documentation Figure (개념 도식, Unreal Screenshot 아님)

Chapter / Section:
Chapter 02 / 2.15 Coordinate Space Conversion in Unreal

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Camera Vector 반전, Position/Direction 혼동 및 Node 출력의 과도한 단정.

Changes:
Surface → Camera 화살표 교정. Space 목록의 직렬 화살표 제거. World Normal과 World View Direction의 Dot Product 예시로 정렬. Object Position/PixelNormalWS/ScreenPosition의 출력 조건 확인 명시.

Technical Verification:
현재 본문의 Node별 의미 제한과 World N/V 비교에 일치. Node 구현 및 Engine 동작의 실제 검증 완료를 주장하지 않음.

Text Verification:
상단 글자 겹침은 재생성으로 교정. 전체 Korean 문장 및 양쪽 Camera Vector 방향 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 네 구역 유지, 방향·Data 의미·출력 조건 수정.

## Fig2_16

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 02 / 2.16 Complete Coordinate Flow

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Position 차원, Viewport 관례 및 TBN 입력 관계 보완 필요.

Changes:
float4(localPos,1), 열벡터 4×4 변환 명시. Clip 출력은 동차 좌표로 표시. Top-left/+Y Down Viewport 식 명시. Normal Map/UV → Sample/Decode와 Surface Basis를 별도 입력으로 구성. Direction Space의 필수 직렬 흐름 제거.

Technical Verification:
Position과 Direction 흐름, Sample과 TBN 의존 관계, Divide 식, Viewport 식 대조. Viewport 원점 Offset=0인 예시임을 확인.

Text Verification:
전체 Korean 문장, 차원 및 화살표 육안 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 상단 9단계 및 하단 구역 유지, 표기와 입력 연결 수정.

## Fig3_01

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 03 / 3.2 Vector and Normalize

Previous Audit Status:
Match / Keep

Action:
Minor Revision

Reason:
계산과 도식은 유지 가능하나 현재 명칭 기준 Anime Shader Framework와 하단 Ari's 표기가 불일치. 현재 Standard를 Audit보다 우선 적용.

Changes:
프로젝트명, Vector/Normalize 용어 표기 및 Nonzero 조건만 수정. 기존 예시와 도식 유지.

Technical Verification:
|A|≈4.47, |B|≈2.24 및 두 Normalize 결과≈(0.894,0.447,0) 확인.

Text Verification:
한글 설명, 수치, 프로젝트명 육안 검수.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 구성 유지, 현재 명칭·용어와 입력 조건 교정.

## Fig3_02

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 03 / 3.3 Dot Product

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
135° 방향 오류 및 Dot Product를 최종 밝기로 해석하는 문제.

Changes:
135° L을 아래 오른쪽으로 교정. 구체 밝기 대신 한 Surface Point의 방향 계수 표시. 같은 Space/Unit Vector 조건 및 다음 절 참조, 프로젝트명 교정.

Technical Verification:
각 방향의 cos 값과 max(N·L,0) 확인. 0°의 잘못된 각도 호 제거. 최종 Lighting에는 재질/세기/Visibility가 필요함을 명시.

Text Verification:
첫 생성에 남은 밝기 표현 제거 후 전체 Korean 설명과 값 육안 검수.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision 및 잔여 표현 교정. 기존 5개 각도 비교와 수식 구역 유지.

## Fig3_03

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 03 / 3.4 Surface Normal

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Smooth/Flat의 Geometry 비교 조건과 Face Normal Edge 라벨 오류.

Changes:
동일 실루엣 비교, 편집 가능한 Vertex Normal/Hard Edge 명시. p0에서 출발하는 e1/e2와 +Z Cross Product 도식으로 교체. 축 색상과 Normal 표시 색상 구분, 프로젝트명 교정.

Technical Verification:
cross(+X,+Y)=+Z 및 Winding 반전 확인. N/L 같은 Space/Unit 조건과 θ 정의 확인. 비교 이미지는 개념 예시이며 실제 Engine Evidence가 아님.

Text Verification:
전체 Korean 설명, Edge/Vertex 라벨 확인. 잘못된 각도 부채꼴은 추가 수정으로 제거.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 6구역 목적 유지, 오류가 있는 비교와 수학 삽화 수정.

## Fig3_04

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 03 / 3.5 Normal Transformation

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Normalize 결과와 비단위 방향 값 혼동, 잘못된 방법의 직각 기호 및 Figure 번호 오류.

Changes:
Raw (-0.5,1), Unit ≈(-0.447,0.894), 같은 방향 (-1,2)를 구분. 가역 선형 Transform의 Inverse Transpose 명시. 잘못된 직각 표시 제거, Figure 3-4 및 프로젝트명 수정. Engine 자동 처리 단정 제한.

Technical Verification:
T'=(2,1), Nwrong=(-2,1)의 Dot=-3과 올바른 방향의 Dot=0 확인. X Scale=2/Y Scale=1 및 Normalize 계산 대조.

Text Verification:
한글 설명, 수치, 번호, 수식 육안 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 6구역 비교 유지, 수치·행렬 조건·직각 기호 교정 및 자동 처리 문장 추가 정리.

## Fig3_05

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 03 / 3.6 Light and View Direction

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Directional의 입사 방향과 L 부호가 불일치하고 Spot Axis/반각이 불명확함.

Changes:
D를 아래, L을 위로 표시하고 L=normalize(-D) 명시. Spot Axis s는 광원에서 아래로, L은 Surface에서 광원으로 정렬. Cone 반각 α 및 dot(s,-L) 조건 표시. Figure 3-5/Section 3.6 구분.

Technical Verification:
Point/Spot의 Position 차이와 View Direction 식, Nonzero/같은 Space/Unit 조건 확인. Cone 반각은 축과 한쪽 경계 사이임을 확인.

Text Verification:
전체 Korean 문장, 식, Surface→Light/Camera 화살표 확인. 생성 후 Point/Spot 화살표를 추가 정리.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 병렬 비교 유지, 방향 convention과 각도 조건 교정.

## Fig3_06

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 03 / 3.7 Coordinate Space for Lighting

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
V의 방향, Position/Normal Transform 구분 및 Mixed Space 비교가 부정확함.

Changes:
동일 P에서 N/L/V 시작, V는 Camera 방향. 회전 Basis의 명시적 수치 예시로 Mixed Space 오류 표시. Position/Normal/L/V의 Input-Processing-Output 표로 의존성 분리. World/View를 선택 가능한 기준으로 제한, Figure 번호 교정.

Technical Verification:
World +X가 View (0,-1,0)인 Basis에서 올바른 Dot=1, 잘못 섞은 Dot=0 확인. Normal의 가역 선형 부분 Inverse Transpose와 Position 차이 확인.

Text Verification:
전체 Korean 문장과 표/수식 검수. 생성 중 잘못 연결된 선을 제거하고 명시적인 표로 정리.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 5구역 유지, 수치/방향 교정 및 입력-처리-출력 표로 변경.

## Fig4_01

Type:
Type A — Documentation Figure (Material 개념 비교)

Chapter / Section:
Chapter 04 / 4.1 What Is a Material?

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Emission과 반사의 배타적 표현 및 Bloom/주변 조명 조건 누락.

Changes:
Emission은 추가 방출 성분이고 반사와 병존함을 명시. Bloom/주변 조명은 별도 설정과 Rendering 경로에 의존. Roughness와 요철 입력 구분, Chapter 명칭 수정.

Technical Verification:
현재 본문의 동일 Geometry/Light와 다른 Material Data 비교에 일치. 실제 Unreal 검증 결과를 주장하지 않는 개념 예시.

Text Verification:
전체 Korean 설명, Chapter/Figure 명칭 육안 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 비교 구성 유지, Caption과 명칭 중심 수정.

## Fig4_02

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 04 / 4.2 Material Inputs and Surface Properties

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Normal 방향 변화와 Geometry 변화 혼동, Roughness 요철 혼합 및 Emission 이진 해석.

Changes:
동일 평면에서 Shading Normal 방향만 변경. Roughness 비교의 요철 제거. Emission 연속 강도와 별도 Bloom 조건 표시. Base Color의 Dielectric/Metal 역할 및 비금속 Specular 명시.

Technical Verification:
Geometry 고정/방향 변화와 Roughness의 Reflection 분포 변화 구별. Emission=Color×Intensity에서 0의 출력 검정 표시. 수치적 Render 검증을 주장하지 않는 개념 예시.

Text Verification:
생성 중 새로 생긴 비금속 무반사 표현을 수정한 후 전체 Korean 문장/화살표/값 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 5개 Property 구역 유지, 비교 조건과 방향 도식 교정.

## Fig4_03

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 04 / 4.3 Texture as Material Data

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Normal Encoding 상태와 손상 문자, Packed Channel 영역 표현 보완.

Changes:
Raw RGB (0.5,0.5,1) → Decode (0,0,1) 예시 및 중복 Decode 금지 조건. 설명문 Korean 정렬. Packed Channel을 동일 UV 영역의 겹친 Layer로 표시.

Technical Verification:
Texture 전체가 아닌 현재 Pixel UV의 Sample 값 사용 확인. Linear Base Color와 Normal Decode 상태 구분, 수치는 관계 설명 예시임을 표시.

Text Verification:
Korean 문장 및 수치 검수. 생성 중 G Layer의 잘못된 R 라벨은 수정 후 R/G/B 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 Texture/Runtime/Result 구역 유지, 설명과 수치 상태 및 Packing 도식 보완.

## Fig4_04

Type:
Type B — 보호 대상 Character / UV 자료를 포함한 합성 이미지 (실제 Unreal Capture 여부는 미확인)

Chapter / Section:
Chapter 04 / 4.4 UV and Texture Sampling

Action:
Caption / Reference Revision

Evidence Purpose:
Character Mesh/UV Layout과 Texture의 관계를 보여주는 자료. 현재 출처만으로 실제 Engine 검증 Evidence임을 인증하지 않음.

Current Text Consistency:
Sample/현재 UV 설명은 일치. UV 표시 위치, Mip 거리 단순화, Encoded Normal 표시, Address Mode 비교와 서문 오타는 보완 필요.

Issue:
Character/UV 패널의 원본 출처가 확인되지 않아 전체 AI 편집 시 실제 제작 자료를 바꿀 위험이 있음.

Required Follow-up:
본문에 정확한 affine 가중치 (0.35,0.03,0.62), footprint, Encoded RGB, 비대칭 Address Mode 비교 조건과 오타를 명시함. 이미지 원본 유지. 출처/편집 원본 확보 후 Character/UV 자료를 그대로 보존하는 부분 편집으로 위치·라벨·비교 패턴 정정 필요. 실제 구현 불일치가 입증되지 않아 Unreal 재촬영 대상으로 임의 분류하지 않음.

Final Status:
Presentation Revision Required

## Fig4_05

Type:
Type B — Unreal Graph / Rendering Evidence로 제시된 합성 이미지 (원본 Capture 출처 미확인, 보호 처리)

Chapter / Section:
Chapter 04 / 4.5 Color Space for Material Data

Action:
Retake Screenshot

Evidence Purpose:
Texture sRGB 설정에 따른 Sample 값 및 Roughness 결과와 실제 Graph 확인.

Current Text Consistency:
0.50 → 0.73 Decode 표기, Roughness 비교, 자동/수동 Decode 연결이 현재 본문과 불일치.

Issue:
Actual Rendering 표방과 Graph의 검증 신뢰성을 확인할 수 없으며 수치/방향 오류가 존재함. AI 이미지 교체 금지.

Required Follow-up:
Retake Screenshot in Unreal Engine. 동일 Mesh/Normal/Light/Exposure에서 0.5 Data Texture의 sRGB Off/On을 비교. Texture Editor sRGB 설정, Sample 출력 검증, 중복 Decode 없는 실제 Material Graph, 비교 Rendering을 함께 캡처. Encode/Decode 곡선은 축/방향/정확한 transfer 또는 근사를 구분. 본문에 기존 Figure의 Evidence 사용 제한과 올바른 해석을 추가함.

Final Status:
Retake Required

## Fig4_06

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 04 / 4.6 Normal Map and Normal Encoding

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Object/World Space 혼동과 Engine convention 단정, Decode/Basis 도식 오류.

Changes:
Object Space는 Object 기준이며 World Normal 변환 필요. Surface별 Tangent Basis 구별. Raw Decode/Normalize와 Sampler 중복 Decode 금지 조건, TBN 뒤 Normalize 명시. +Y/+Z 방향 분리. Engine/도구 설정 확인으로 제한.

Technical Verification:
RGB 예시와 XYZ 방향, Object 회전에 따른 World 방향 변화 확인. N·L은 방향 관계이며 최종 Lighting이 아님을 명시.

Text Verification:
Korean 문장과 라벨/흐름 육안 확인. 생성 중 생긴 순환 연결선을 추가 제거함.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 구역 유지, Space/Decode/좌표축 오류 교정.

## Fig4_07

Type:
Type B — Material Graph / Instance 화면을 포함한 보호 대상 합성 이미지

Chapter / Section:
Chapter 04 / 4.7 Material Parameters and Material Instances

Action:
Caption / Reference Revision

Evidence Purpose:
Parameter 입력과 Parent Material / Instance의 관계 및 조절 화면 예시.

Current Text Consistency:
기본 관계와 보이는 비정적 값 예시는 일치. 전체 Parameter의 Runtime 조절/구조 불변 일반화는 조건 보완 필요.

Issue:
Static Switch/Static Component Mask와 Runtime 값 변경의 구분이 그림 요약에서 생략됨. 실제 Engine 버전/Runtime 실행 Evidence는 미확인.

Required Follow-up:
본문 Caption에 비정적 Parameter/지원되는 Instance 사용 조건과 Static Variant 구분을 추가함. Graph/UI/Rendering 이미지는 수정하지 않음. 현재 화면의 Node/Parameter 불일치가 입증되지 않아 재촬영은 요구하지 않음.

Final Status:
Keep

## Fig4_08

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 04 / 4.8 Material Data Flow

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
L/V 방향 반전과 독립 입력의 직렬화, Texture와 Sample 값 혼동.

Changes:
L/V를 Surface에서 출발하도록 교정. Texture와 현재 UV의 입력 및 단일 RGBA 출력 표시. Normal Decode/Basis/Normalize를 명시적 수식으로 분리. 하단은 병렬 입력의 Input-Processing-Output 표로 변경.

Technical Verification:
Sample 값/Parameter/Normal Basis/Lighting Data의 관계와 Raw Decode 조건, Material/Lighting의 합류 확인.

Text Verification:
전체 Korean 설명과 수식/입력 표 확인. 생성 중 잘못된 Basis 연결선은 수식 카드로 교체하여 해소.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 8구역 유지, 입력 관계와 화살표 교정.

## Fig5_01

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 05 / 5.1 Reflection

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision (Caption)

Reason:
이상적인 거울 반사의 조건만 추가하면 기존 도식 유지 가능.

Changes:
현재 Markdown의 Figure Caption에 이상적인 매끄러운 Surface의 반사 예시임을 명시. 이미지 수정 없음.

Technical Verification:
Incoming → Surface → Outgoing 및 Normal 기준 대칭 관계 확인. 모든 Material의 반사 분포로 일반화하지 않도록 한정.

Text Verification:
원본 라벨과 추가 Korean Caption 확인.

Final Status:
Complete

## Fig5_02

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 05 / 5.2 Surface Normal

Previous Audit Status:
Match / Keep

Action:
Keep

Reason:
현재 본문의 Surface 방향 기준 설명과 일치.

Changes:
없음.

Technical Verification:
Surface Point에서 수직인 Normal 방향 확인.

Text Verification:
Normal (N), Surface 라벨 육안 확인.

Final Status:
Complete

## Fig5_03

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 05 / 5.3 Reflection Vector

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision (Caption)

Reason:
그림 I와 본문 L의 부호 및 Unit Normal 조건을 연결하면 기존 도식 유지 가능.

Changes:
Caption에 I=-L, |N|=1, 두 Reflection 식의 동치 및 입사각 정의 명시. 이미지 유지.

Technical Verification:
R=I-2(I·N)N에 I=-L 대입 시 본문 식과 일치. Incoming/Outgoing 방향 확인.

Text Verification:
원본 수식과 Caption의 부호/한글 확인.

Final Status:
Complete

## Fig5_04

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 05 / 5.4 Lambert Reflection

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
계수의 크기와 명도 표현이 역전되어 있었음.

Changes:
단일 색상의 막대 길이로 방향 계수를 표현. N/L Unit·같은 Space 조건 및 최종 Lighting과 방향 계수 구분.

Technical Verification:
cos 값 1,0.87,0.71,0.50,0.26,0 및 max(0,N·L) 확인. 앞면 직접 기여의 범위 명시.

Text Verification:
전체 Korean 문장/수식 확인. 하단 정의의 손상 글자를 추가 수정.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 도식과 표 유지, 명도 역전과 계수 정의 교정.

## Fig5_05

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 05 / 5.5 Phong Reflection

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Incoming L 부호와 서로 다른 R/V 시작점 문제.

Changes:
입사 화살표를 I=-L로 표시. R/V를 같은 Surface Point에서 시작. Unit R/V, n>0 및 One-sided Reflection의 조건 추가.

Technical Verification:
pow(max(0,R·V),n)와 현재 본문 계약 대조. Surface→Camera V 및 Incoming I 구별 확인.

Text Verification:
전체 Korean 설명/수식/부호 육안 확인.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Minor Revision. 기존 단일 도식 유지, 라벨/시작점 및 조건 교정.

## Fig5_06

Type:
Type A — Documentation Figure

Chapter / Section:
Chapter 05 / 5.6 Half Vector

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
H가 L/V 사이 이등분선에 놓이지 않았음.

Changes:
대칭 L/V와 중앙 H의 예시 및 좌표값 추가. Unit L/V와 L+V≠0 명시. H=N은 이 예시의 정렬 조건임을 구분.

Technical Verification:
L=(-1/√2,1/√2,0), V=(1/√2,1/√2,0) 합의 Normalize=(0,1,0) 확인. 두 방향 대칭과 H의 이등분 확인.

Text Verification:
Korean 설명/수식/입력 조건 육안 검수.

Final Status:
Complete

Generation Method / Prompt Specification:
Built-in image_gen Major Revision. 기존 단일 개념 도식 유지, 대칭 좌표 예시로 Half Vector 교정.

## Fig5_07

Chapter / Section:
Chapter 05 / Blinn-Phong Reflection

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
기존 H가 L/V 이등분선에 있지 않고 비교 Diagram의 원점이 다르며 계산 비용 우위를 단정함.

Changes:
공통 Surface P에서 대칭 Unit L/V와 H=N 예시를 구성. 일반적으로 H≠N일 수 있음을 명시. Phong/Blinn-Phong 수식과 서로 다른 Exponent를 구분하고 동일 Exponent의 폭 차이 및 비용의 구현 의존성을 설명. 공통 Space, L+V≠0, 양의 Exponent 조건 추가.

Technical Verification:
생성 결과의 공통 원점, 이등분 방향, 수식, Korean 글자와 조건을 시각 검수함. 현재 본문과 개념 정합성 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; 기존 PNG를 편집 대상으로 사용. White academic layout, Korean prose/English terms, symmetric unit L/V and shared H=N, separate formula cards, conditional performance claim, Anime Shader Framework footer.

Final Status:
Complete


## Fig5_08

Chapter / Section:
Chapter 05 / 5.8 Reflection Model 한계

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
검증되지 않은 연대와 단일 진화/대체 구도, PBR과 Cook-Torrance 동일시 및 정확성/보존의 무조건 단정을 제거해야 함.

Changes:
역사 연표를 역할/한계 비교표로 교체. PBR 접근 방식 안의 Diffuse/Specular 모델을 구분하고 Cook-Torrance를 모델 예로 표시. Energy Conservation의 정규화·Parameter·결합 조건과 Microfacet의 근사 한계를 명시.

Technical Verification:
현재 본문의 경험적 모델 한계와 대조. Korean 가독성, 모델 구분 및 연대/무조건 성능 주장 제거를 생성 이미지에서 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; 기존 이미지 편집. Korean comparative table, no dates or replacement arrows, PBR approach containing separate Diffuse/Specular examples, explicit conservation conditions and approximation limits.

Final Status:
Complete


## Fig5_09

Chapter / Section:
Chapter 05 / 5.9 Microfacet Theory

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
단일 Facet 입사점에서 여러 반사 방향을 방출해 거울 반사 가정을 혼동함.

Changes:
서로 다른 기울기의 Facet A/B/C를 분리하고 각각 하나의 입사/반사 쌍과 Unit Normal을 표시. 수직 입사 I=(0,-1)에 대한 정확한 m/R 수치 및 R=I−2(I·m)m 명시. 개별 반사와 Facet 방향의 통계적 분포를 구분.

Technical Verification:
세 Facet의 반사식 수치 일치, 한 입사점/한 반사 방향, Korean 문장 및 도식 방향을 시각 검수. 중간 생성본의 중복 근삿값 표기를 수정한 최종본 사용.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; three separated ideal mirror facet examples, slopes +30/0/−30 degrees, unit normals and reflected vectors with exact radical values, one incoming/reflected pair per facet, Korean explanation and Anime Shader Framework footer.

Final Status:
Complete


## Fig5_10

Chapter / Section:
Chapter 05 / 5.10 Cook-Torrance

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
BRDF 응답을 Final Reflected Direction으로 오인시키고 L 입사 진행 방향과 outward Convention을 혼용함.

Changes:
N/L/V 및 Material Parameter → D/G/F와 분모 → Specular BRDF 구조로 재구성. 별도 기하 도식에서 L은 Surface→Light, V는 Surface→Camera로 통일. BRDF 단위 sr⁻¹, 반구 조건, Radiance 추가 계산 및 단일 산란 근사 한계를 표시.

Technical Verification:
생성 이미지에서 방향·공통 원점·분모·출력 의미·Korean 문장을 확인. 현재 본문 D/G/F 설명 및 BRDF/Radiance 구분과 일치함.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; isolated geometry inset, Input/Calculation/Output panels, full Cook-Torrance formula, outward vectors, domain conditions, no final direction funnel or unconditional physical guarantee.

Final Status:
Complete


## Fig5_11

Chapter / Section:
Chapter 05 / 5.11 Roughness

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Low Roughness의 급경사 Facet과 반사 광선이 좁은 Normal 분포 설명과 불일치함.

Changes:
Facet/Ray 도식을 Normal 표본과 정성적 분포 비교로 교체. Low/High 방향 분포 폭과 Highlight 폭의 관계를 유지하며 Geometry 높이와 구분. Peak 변화 가능성과 Light/View/Material 조건을 명시.

Technical Verification:
Normal 표본의 좁은/넓은 분포, 정량 NDF Plot이 아님이라는 표시, Korean 문장과 본문 개념의 일치를 시각 검수함. 초기 생성본의 불일치 Facet/각도 표시는 최종본에서 제거함.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; low/high Roughness side-by-side normal samples, qualitative distribution curves, illustrative highlight width, no inconsistent incident/reflected ray geometry.

Final Status:
Complete


## Fig5_12

Chapter / Section:
Chapter 05 / 5.12 Normal Distribution Function

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
정규분포 오역, 밀도/확률 혼용, 모든 H에서 Roughness 증가로 D가 감소한다는 일반화.

Changes:
Normal 방향 밀도로 용어 통일. 중심/꼬리의 변화 차이를 동일 축 개념 곡선으로 제시하고 정량 Plot과 구분. D(H)>1 가능성 및 projected solid angle 정규화 식, NDF와 반사광/최종 Highlight의 차이를 명시.

Technical Verification:
현재 본문의 밀도/확률 구분 및 반구 정규화와 대조. 최종 생성본의 Korean, 적분식, 중심/꼬리 관계, 방향 표기를 시각 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; shared-axis narrow/wide conceptual NDF curves, Surface Normal terminology, density not probability, normalization integral, no reflected ray plot. Follow-up changed axis end labels to N에서 멀어진 방향.

Final Status:
Complete


## Fig5_13

Chapter / Section:
Chapter 05 / 5.13 Geometry Function

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
기존 경로가 장애물과 교차하지 않아 Shadowing/Masking을 입증하지 못하며 D를 빛의 수로 잘못 설명함.

Changes:
입사/관찰 경로를 별도 단면으로 표시. 차폐 Facet의 교차점에서 실선 종료, 차단되지 않았을 경우의 경로만 점선 표시. D를 Normal 방향 분포로 고치고 G와 Scene Visibility의 규모/역할을 구분.

Technical Verification:
생성 후 여러 차례 수정하여 경로 굴절처럼 보이는 꺾임, 차단점과 Facet 불일치, 부유 목표점 및 텍스트 중복을 제거. 최종 이미지에서 차단점 교차, 목표점 연결 및 Korean 가독성 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; two occlusion cross-sections, solid path stops at red X on blocker, hypothetical continuation dashed. Final left path horizontal, target P on blue facet. Separate D/G/Scene Visibility explanations.

Final Status:
Complete


## Fig5_14

Chapter / Section:
Chapter 05 / 5.14 Fresnel

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
입사각/View Angle 혼동, 고정 입사광에서 View만 바꿔 광선 방향을 변경한 오류 및 Reflectance 글자 손상.

Changes:
반사에 기여하는 H 기준 대칭 Unit L/V 도식과 Schlick 식으로 재구성. F0=0.04 예에서 cosθ=1/0.5/0의 F=0.04/0.07/1을 구분. Interface Normal과 H 기준, F0 조건, 근사 및 최종 밝기와의 차이를 명시.

Technical Verification:
현재 본문 Schlick 수치 예시와 대조. 외향 L/V 단일 화살촉, H 이등분선, 수식/수치 및 Korean 가독성 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; H-based Microfacet inset, Schlick formula and numeric cards, no View-only reflection change, no universal F0 or brightness guarantee. Follow-up removed inward arrowheads and corrected incidence heading.

Final Status:
Complete


## Fig6_01

Chapter / Section:
Chapter 06 / 6.1 Rendering Pipeline

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Lighting 기법과 HDR 값 표현을 의무적인 직렬 Stage로 혼합함.

Changes:
Geometry/Material/Light/Environment 입력에서 Direct·환경/간접·Emission 기여를 평가하고 Scene-linear HDR로 합성하는 분기/합류 구조. BRDF는 Lighting 평가의 Material Response로 배치. IBL/GI/Reflection 중복 합산 방지와 Renderer별 Pass 차이를 표시.

Technical Verification:
현재 본문 고정 실행 순서가 아니라는 계약과 일치. 생성본에서 분기 합류, HDR 설명, 출력 변환 및 Korean 가독성 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; conceptual contributions diagram, sibling lighting contributions, HDR accumulation and exposure/tone mapping/output transform, no serial IBL/reflection stages.

Final Status:
Complete


## Fig6_02

Chapter / Section:
Chapter 06 / 6.1 BRDF의 역할

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Material과 BRDF 동일시 및 Lighting 전 독립 실행 Stage로 오인시키는 직렬 구조.

Changes:
Chapter 05 BRDF를 방향별 반사 응답으로 강조하고 입사광/Geometry/Visibility와 함께 Direct 및 환경/간접 평가에 사용하는 구조. 반사 기여와 Emission 합성 및 출력 경로를 분리.

Technical Verification:
현재 본문과 비교해 고정 Stage 주장 제거 확인. 생성본의 평가 입력, 두 Lighting 기여, 합류, Korean 글자 확인. 생성 시 추가된 굴절 항목을 제거해 BRDF 범위 유지.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; Chapter05 orange BRDF response, Chapter06 blue parallel Lighting evaluations, shared evaluation inputs, HDR reflection plus Emission, output transforms.

Final Status:
Complete


## Fig6_03

Chapter / Section:
Chapter 06 / 6.2 Direct Lighting

Type:
Documentation Figure / Infographic (Type A)

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
환경/IBL 무조건 제외, Material/BRDF 혼용 및 다중 Bounce 경로 미표현.

Changes:
Direct 경로 정의에 중간 Surface 반사 여부를 명시. Environment는 Chapter의 설명상 별도 분류이며 경로에 따라 Direct 여부가 달라짐을 표시. Indirect 예를 Light→벽→대상 및 Light→벽→바닥→대상으로 표기. 공통 Surface P, I=−L, N 및 V와 BRDF 반사 응답을 구분.

Technical Verification:
현재 Direct/Indirect 본문과 대조. 초기 생성본의 잘못된 f_r(−L,V,N)을 f_r(L,V)로 수정하고 평면 Surface와 수직 Normal으로 정리. 최종 Korean 가독성과 공통 P 확인.

Text Verification:
현재 해당 Section 본문과 비교했으며 최종 생성 이미지의 Korean 문장과 Technical Term을 시각 검수함.

Generation Method / Prompt Specification:
Built-in image_gen; direct Light-to-Surface concept, common P on flat surface, corrected outward BRDF convention, Environment classification note and explicit indirect path notation.

Final Status:
Complete


## Fig6_04

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 06 / 6.3 Direct vs Indirect Lighting

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
실내 개념도의 입사 경로가 창문/첫 Surface와 맞지 않고 바닥 반사 화살표가 바닥을 따라 진행함.

Changes:
기존 실내 구도 및 비교 목적 유지. 창문 개구부를 통과해 Floor에 도달하는 Direct 경로, Floor→Wall→주변 Surface의 Indirect 경로를 연결. 경로 설명용 개념도 표시.

Technical Verification:
현재 본문의 다른 Surface 반사에 의한 Indirect 정의와 일치. 첫 Floor 점에서 벽 위로 향하는 반사 및 연속된 경로를 시각 확인. 실제 Unreal 구현 Evidence 용도가 아닌 본문 개념 설명 자료로 분류함.

Text Verification:
Direct/Indirect 설명, 번호와 Surface 관계, Korean 문장을 확인함.

Generation Method / Prompt Specification:
Built-in image_gen; preserve room/layout, correct overlay through window to floor, then upward to wall and onward surface, remove horizontal floor rays.

Final Status:
Complete


## Fig6_05

Type:
Unreal Screenshot / Verification Evidence (Type B, 보호 대상 혼합 Figure — 실제 Unreal 출처 미확인)

Chapter / Section:
Chapter 06 / 6.4 Image Based Lighting

Action:
Caption / Reference Revision

Evidence Purpose:
IBL 적용 결과로 제시된 Rendering 영역을 포함. 실제 Unreal 캡처인지는 확인되지 않아 결과 영역을 보수적으로 보호함.

Current Text Consistency:
Environment Map의 Diffuse/Specular 역할은 일치하나 다중 Bounce 단정 및 직렬 Pipeline은 현재 본문과 불일치.

Issue:
Diffuse IBL과 다중 Bounce 혼동, 입사/출력 양방향 화살표, Direct→Indirect→IBL→Reflection 고정 Stage 도식. Rendering 결과 출처 미확인.

Required Follow-up:
결과 이미지 영역을 보존한 상태에서 설명/화살표만 부분 수정. Environment Map→Diffuse/Specular 기여를 병렬로 표현. 실제 Unreal Evidence로 사용할 경우 출처와 설정을 확보해야 함. 본문 Caption에 개념 정정과 검증 미확인 상태를 기록했으며 이미지 파일은 변경하지 않음.

Final Status:
Presentation Revision Required


## Fig6_06

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 06 / 6.5 Reflection

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Reflection 이후 BRDF를 별도 적용하는 직렬 Stage와 입사/반사 화살표 혼용.

Changes:
Environment Sample/사전 적분 데이터 및 Material BRDF/Normal/View/Roughness를 Specular IBL 평가의 입력으로 배치. 환경 Specular 기여를 HDR 조명 합성에 전달. 다른 Reflection 기법 및 중복 기여 문제를 명시. Roughness 이미지는 정량 검증이 아닌 개념 비교로 표시.

Technical Verification:
현재 본문 Specular IBL은 Reflection 구현 방법 중 하나라는 설명과 일치. 잘못된 광선 제거 및 데이터 입력/평가/출력 연결 확인. 본문 환경 반사 개념 설명 목적이며 Unreal 검증 화면이나 구현 결과 주장에 사용하지 않음.

Text Verification:
Korean 설명과 Technical Term, 정량 검증 아님 표시를 시각 확인.

Generation Method / Prompt Specification:
Built-in image_gen; preserve conceptual reflection comparison, replace ray/serial stage logic with environment/material inputs → Specular IBL → HDR contribution flow.

Final Status:
Complete


## Fig6_07

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 06 / 6.6 HDR Rendering

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
HDR 계산 범위와 후속 Stage의 중복, 고정 수치 범위 오해 및 다른 Scene의 최종 출력 예시.

Changes:
기존 입력/계산/출력 Column 유지. HDR 고정 10000 상한을 제거하고 1 초과 값 유지로 설명. 하단을 Scene-linear HDR 계산 영역→출력 변환→Display로 정리. 출력 Monitor를 동일 Sphere Scene으로 맞추고 SDR 0–1을 신호값 예시로 한정.

Technical Verification:
현재 본문의 HDR 입력 데이터/계산 구분과 일치. 개념 곡선, 출력 변환, SDR 예시 범위와 동일 Scene을 시각 확인.

Text Verification:
중복 출력 문구를 교정하고 최종 Korean 설명 및 Technical Term을 확인함.

Generation Method / Prompt Specification:
Built-in image_gen; preserve five-column structure, remove fixed HDR upper range and duplicated HDR stage, same-scene monitor illustration, explicit normalized SDR signal example.

Final Status:
Complete


## Fig6_08

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 06 / 6.7 Tone Mapping

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
정규화된 SDR 신호와 cd/m² 혼동, HDR 데이터 자체 손실 오인 및 서로 다른 Scene의 전후 비교.

Changes:
동일 Scalar HDR 입력 x=0,1,4,9에 Clipping과 예시 Tone Mapping x/(1+x)를 적용한 비교표로 교체. Exposure 배율 1, Reinhard 형태의 단순 예시, SDR 신호와 물리 휘도 구분, 이미 손실된 정보 복원 불가를 명시.

Technical Verification:
표의 0/0.5/0.8/0.9 계산과 Clipping 0/1/1/1 확인. 현재 본문 HDR 계산/출력 변환 구분과 일치. 실제 Engine 측정값으로 주장하지 않음.

Text Verification:
Figure 번호, Korean 설명, 단위 구분 및 예시 범위 표시를 최종 이미지에서 확인.

Generation Method / Prompt Specification:
Built-in image_gen; replace mismatched scene/histograms with same-input numerical comparison, input-processing-output cards, explicit unit and clipping distinctions.

Final Status:
Complete


## Fig6_09

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 06 / 6.8 Color Space

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
HDR/출력 변환 Grouping 혼동, Import 오류 원인 단정 및 Color Texture/출력의 무조건적 sRGB 처리.

Changes:
기존 세 Column 구조 유지. 저장 Encoding에 따른 Color Decode와 Data/Normal Vector Decode 구분. Engine 설정 단정 표를 Import 의도/추가 확인 표로 수정. SDR sRGB 출력 예시로 한정하고 HDR 계산/출력 변환 구분.

Technical Verification:
현재 본문의 Linear Color 중복 Decode 금지, Data Texture Color Decode 없음, Normal Vector Decode 필요 계약과 일치. Engine/Importer/버전 설정은 확인 대상으로 남김.

Text Verification:
잘못 생성된 축 예시와 제목의 글자 손상을 제거하고 최종 Korean 설명 및 Technical Term 확인.

Generation Method / Prompt Specification:
Built-in image_gen; preserve color/data, output flow and table columns; conditional decode by encoding, SDR output example, remove universal import claims and serial lighting chain.

Final Status:
Complete


## Fig6_10

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 06 / 6.9 Summary

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Lighting/Reflection/BRDF/HDR를 고정 직렬 Stage로 표시하며 Chapter 범례도 불일치.

Changes:
Geometry/Material/Light 입력 준비, BRDF 및 입사광/Visibility, Surface Lighting과 Emission의 HDR 합성을 구분. 출력 변환을 별도 Group으로 표시. Color 입력에만 필요한 Decode 적용 및 중복 기여 방지 명시.

Technical Verification:
현재 Data Flow 본문과 대조하여 BRDF 적용 위치, HDR 영역, 출력 경로 확인. 생성본의 Geometry Color Decode 오해, GGX를 완전 BRDF로 지칭한 예 및 LDR 출력 고정 표기를 수정.

Text Verification:
Figure 번호와 Korean 설명, 개념 흐름/Renderer별 Pass 차이 및 출력 조건 표시 확인.

Generation Method / Prompt Specification:
Built-in image_gen; grouped Scene-linear HDR evaluation and separate output transforms, joint inputs, BRDF/incident-light evaluation, Lighting+Emission composition, no fixed serial technique stages.

Final Status:
Complete


## Fig7_01

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.1 Rendering 목표

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Keep

Reason:
현재 Refactoring 본문의 Figure 직후 Caption이 두 범주의 비배타성을 명시하고 Connection to Rendering Foundations가 Lighting/Reflection/HDR/Tone Mapping/Color Space 공유 기반을 이미 설명함. 기존 이미지의 Anime Shader Framework 명칭은 현재 Standard와 일치하므로 이전 Audit의 Ari’s 명칭 제안은 적용하지 않음.

Changes:
이미지 및 본문 추가 변경 없음. 기존 Caption/본문을 포함한 현재 설명 유지.

Technical Verification:
표현 목표 비교이며 PBR 제거 구조가 아님. 공통 기반과 필요한 요소만 변형한다는 현재 본문 연결 확인.

Text Verification:
Figure 번호와 Korean 설명, 현재 ASF 명칭 확인. 관계 의미는 현재 Caption/연결 본문에서 설명됨.

Final Status:
Complete


## Fig7_02

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.2 Diffuse

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
구 전체에 단일 Light-Normal 각도를 부여하고 이진 응답 예시에 Gradient가 남아 있음. Lambert 재사용 관계 불명확.

Changes:
기존 두 Column과 응답 Graph 유지. 특정 Shading Point P, 외향 Unit L/N 및 각도 정의 추가. 구 예시를 지점별 수치 Card로 변경. D→선택적 Threshold/Ramp 흐름과 Chapter08.2 기본 연속 구현 범위를 명시.

Technical Verification:
D=max(0,N·L), T=step(0.5,D), 60° 경계 및 예시 값 검산. 최종 L은 Surface→Light 방향이며 최종 Pixel 밝기와 구분함.

Text Verification:
Korean 문장, 근삿값 표시 및 Chapter08 구현 범위 설명 확인.

Generation Method / Prompt Specification:
Built-in image_gen; preserve comparison columns/graphs, point-response geometry and numeric cards, optional remap flow. Follow-up reversed incorrect generated incoming L arrows to outward.

Final Status:
Complete


## Fig7_03

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.3 Specular

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
개념 곡선의 축/정량 기준과 View 화살표 Convention을 보완해야 함.

Changes:
기존 비교 Figure는 유지하고 Caption에 정성적 응답 곡선, 고정 Unit L/V와 N–H 각도 단면, 상대 세로값 및 Sphere 지점 응답 차이를 명시. Camera→Surface 관찰 경로와 반대 방향의 계산 V를 구분.

Technical Verification:
현재 본문의 연속 Specular 응답을 재해석하는 목적과 일치. Curve를 정확한 Cook-Torrance Plot이나 BRDF 상한으로 사용하지 않도록 조건을 한정.

Text Verification:
Caption 및 기존 Figure의 표현 목적과 번호 확인. 이미지 변경 없이 필요한 기술적 한계를 문서에 추가함.

Final Status:
Complete


## Fig7_04

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.4 Shadow

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
PBR=Soft/NPR=Hard 단정 및 NdotL Surface Shading과 Cast Shadow Visibility 혼동.

Changes:
동일 Light/Geometry의 Vis와 선택적 Remap을 비교. Direction Factor·Vis·Art-directed Mask를 구분. ASF 기본 B=BaseColor×D, B×Vis 및 수동 Test Input/Renderer 실제 Vis 연결 구분.

Technical Verification:
Step(0.5,Vis) 예시 표 검산. N·L Remap만으로 다른 Object의 Cast Shadow를 계산하지 못한다는 현재 본문과 일치. 잘못 생성된 LightColor 항을 제거함.

Text Verification:
Soft/Hard 구분 문장의 손상과 부자연스러운 문장을 반복 수정한 후 최종 Korean 텍스트 확인. Graph를 개념 예시로 명시.

Generation Method / Prompt Specification:
Built-in image_gen; Visibility input vs remap numeric table, three separate concepts, current ASF Base Lighting/Vis contract, no PBR-soft equivalence.

Final Status:
Complete


## Fig7_05

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.5 Rim

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
각도와 N·V Scalar 축 혼용, 정면 -90° 오류 및 Fresnel/Artistic Rim Mask/최종 밝기 혼동.

Changes:
물리 Edge Highlight의 복합 조건과 ASF Light-independent Rim을 분리. 공통 P의 N/V, r=1−saturate(N·V), 수치 표 및 Width/Softness→Mask→Color·Intensity 흐름. Screen-space Silhouette 검출과 구분.

Technical Verification:
현재 ASF Rim 계약 및 1/.5/0 Dot에 대한 0/.5/1 r 검산. Sphere 지점 Normal 오해를 제거해 평면 Point 도식 사용. 물리 Fresnel의 H 기준과 최종 밝기 조건 확인.

Text Verification:
불필요하게 생성된 용어를 교정하고 최종 Korean 설명, Figure 번호와 Technical Term 확인.

Generation Method / Prompt Specification:
Built-in image_gen; separate physical Edge Highlight dependencies and artistic N/V Mask, point geometry, numerical response table, explicit Light-independent and non-silhouette constraints.

Final Status:
Complete


## Fig7_06

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.6 Hair

Previous Audit Status:
Minor Mismatch / Minor Revision

Action:
Minor Revision

Reason:
Fiber inset의 광경로 및 Graph 각도/정량 기준이 불명확.

Changes:
이미지 유지. Caption에 현상 아이콘과 실제 연속 광경로의 차이, 고정 Light/View에서 기준 Strand 상대 각도, 비교용 상대 응답과 정량 Hair 모델의 차이를 명시. ASF Hair 구현 완료 Evidence가 아님을 표시.

Technical Verification:
현재 본문의 Hair 설계 방향과 Chapter08 기본 Framework 범위 확인. 기존 비교 목적을 유지하면서 과도한 물리/구현 주장 방지.

Text Verification:
Figure 번호와 본문, 추가 Caption의 Korean 설명 확인.

Final Status:
Complete


## Fig7_07

Type:
Unreal Screenshot / Verification Evidence (Type B, 보호 대상 Character 결과 혼합 Figure — 실제 Unreal 출처 미확인)

Chapter / Section:
Chapter 07 / 7.7 Face

Action:
Caption / Reference Revision

Evidence Purpose:
Character Rendering, Yaw 비교 및 Diffuse/Specular/SSS 성분 결과처럼 제시된 영역을 보수적으로 보호함.

Current Text Consistency:
표현 목표 비교와 Face Shadow 제어 개념은 현재 본문과 맞으나 동일 조건/분리 Pass/실제 ASF 구현 증명은 미확인.

Issue:
서로 다른 Geometry, Light 기준 Space 불명확, 피부 성분 분해 증거 부족. 실제 Unreal 캡처 여부도 확인되지 않음.

Required Follow-up:
원본 Character 영역을 보존해 동일 조건 및 분리 Pass처럼 읽히는 Label을 표현 예시로 정정. 실제 검증용으로 사용할 경우 World/Head-relative Light 기준, Camera/Exposure와 Geometry/Parameter를 기록하고 실제 성분별 출력을 확보. 현재 Caption에 한계와 구현 미검증 상태 기록, 이미지 파일 변경 없음.

Final Status:
Presentation Revision Required


## Fig7_08

Type:
Unreal Screenshot / Verification Evidence (Type B, 보호 대상 Character OFF/ON 혼합 Figure — 실제 Unreal 출처 미확인)

Chapter / Section:
Chapter 07 / 7.8 Outline

Action:
Caption / Reference Revision

Evidence Purpose:
동일 조건 Outline OFF/ON Character 결과처럼 제시된 영역 보존.

Current Text Consistency:
Outline 목적은 일치하나 네 기술의 동일 층위와 PBR/Outline 배타성은 Refactoring 본문과 불일치.

Issue:
Inverted Hull/Normal Expansion 및 Screen-space/Edge Detection 중첩. Depth→Normal처럼 보이는 화살표. OFF 이미지의 선과 추가 Outline 효과의 차이 및 실제 구현 출처 미확인.

Required Follow-up:
Character 결과를 보존하고 두 Technique Family로 Grouping/Label을 정정. PBR 결합 가능성을 표시. 실제 검증 시 추가 Outline Pass만 토글한 동일 조건 캡처 필요. Caption에 정정/검증 한계 기록, 이미지 원본 유지.

Final Status:
Presentation Revision Required


## Fig7_09

Type:
Documentation Figure / Infographic (Type A)

Chapter / Section:
Chapter 07 / 7.9 Core Stylization Techniques

Previous Audit Status:
Major Mismatch / Major Revision

Action:
Major Revision

Reason:
Threshold 이후 Smoothstep이 잃은 Gradient를 복원하는 흐름과 Ramp Sampling 단계 누락.

Changes:
같은 연속 Scalar에서 Step/Smoothstep/Ramp를 병렬 평가. Step 경계와 Smoothstep e0<e1 조건, Ramp UV와 별도 Texture Resource→Sample→현재 값 흐름 명시. 적용 영역은 설계 예시로 한정하고 실제 구현 계약 확인을 표시.

Technical Verification:
Step 경계 포함 조건, Smoothstep 식과 연속성, Texture 생성과 Sampling의 차이 확인. 생성본이 임의 추가한 Module 입력 표를 제거해 현재 ASF 계약 혼동 방지. 본문 응용 예시 목적의 Type A로 분류.

Text Verification:
Figure 번호, Korean 설명, Shadow의 N·L/Vis 구분 및 다음 Chapter 구현 범위 문장 확인.

Generation Method / Prompt Specification:
Built-in image_gen; parallel same-input functions, explicit Ramp resource and UV sampling, application examples without invented implementation contracts.

Final Status:
Complete


## Fig8_01
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.0
Previous Audit Status:
Minor Revision
Action:
Minor Revision
Reason:
기존 카드 구성을 유지하면서 현재 본문에 없는 기능과 누락된 개발 순서 연결을 정정.
Changes:
Base의 D/B, 수동 Vis, Phong Shininess, Rim Width/Softness, MatCap Lookup, Emission 외부 Bloom 범위로 교체. 8→9 연결 추가. GPU 실행 단계와 개발 순서 구분.
Technical Verification:
현재 Chapter 08 계약과 대조. Renderer Shadow 연동 또는 Unreal 검증 완료를 주장하지 않음.
Text Verification:
한글 설명과 수식, Chapter 8.0~8.10 순서 및 화살표 육안 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Edit this existing documentation infographic, preserve its white background, eight colored upper cards, icons, lower three cards, title and overall visual identity. Correct contents to actual Chapter08 scope. Title Anime Shader Framework Development Workflow. Subtitle Korean 'Chapter 08 내부 개발 순서'. Small note '개발 순서이며 GPU 실행 단계가 아님'. Card headings/numbers and chapter references unchanged. Replace body bullets with exactly these concise texts: 1 '프로젝트 설정' '폴더 구성' '테스트 장면'; 2 '모듈 구성' '입출력 계약' '데이터 흐름'; 3 'D = saturate(N·L)' 'B = BaseColor × D'; 4 '수동 Visibility 입력' 'B × Vis' 'Renderer 연동은 별도'; 5 'Phong Mask' 'Shininess' 'Color · Intensity'; 6 'N·V 기반 Mask' 'Width · Softness' 'Color · Intensity'; 7 'World → View Normal' 'Texture Lookup' 'Blend · Intensity'; 8 'Color × Intensity' '× Mask' 'Bloom은 외부 효과'. Keep English card titles. All explanations Korean. Bottom 9 Material Layer Ch.8.8;10 Debug View Ch.8.9;11 Final Framework Ch.8.10. Connect 8 to9 using a clear routed arrow through white gap under upper chapter labels, unobstructed;9→10→11. Replace Complete! terminal with '기본 Framework 통합' and smaller '검증 절차 수행'. No claim of tested implementation. No additional bullets or invented features. Crisp readable Korean, no clipped text. Remove old English body bullets entirely.


## Fig8_02
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.0
Previous Audit Status:
Minor Mismatch
Action:
Minor Revision
Reason:
Content/와 StarterContent/의 잘못된 동급 표현 및 과거 Chapter 확장 예고.
Changes:
Content/ 공통 부모 아래 ASF/와 StarterContent/ 형제 구조. 환경을 문서 목표로 표시. Chapter 09 Debug/Optimization과 향후 Advanced Character 확장 구분. 설명 한국어화.
Technical Verification:
현재 본문의 8개 ASF 하위 폴더와 환경 표 대조. 실제 Engine 지원 또는 실행 완료 주장 없음.
Text Verification:
경로, 폴더명, 한국어, 화살표 포함 관계 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Edit existing infographic preserving header environment five icons, green ASF folders block with eight columns and yellow StarterContent block. Fix parent hierarchy explicitly: ASF_Demo at top → small common parent box Content/ → two sibling children ASF/ green left and StarterContent/ yellow right. Existing green top ProjectContent Content/ box should become ASF/ explanatory box, leading into existing eight folders; do NOT put Content/ and StarterContent/ as siblings. Technical environment unchanged Engine Unreal Engine 5.8, Deferred Rendering, DirectX12, MaterialEditor, Git. Add '문서의 목표 환경 · 실제 지원 여부는 별도 확인' under top bar. Translate body explanations Korean and remove Chapter10 roadmap. Green ASF text 'Framework Asset 관리'. Eight folders unchanged Materials/, MaterialFunctions/, MaterialInstances/, Meshes/, Textures/, Maps/, Debug/, Utilities/; descriptions short Korean respectively 'Master Material','재사용 함수','Parameter 변형','테스트 Mesh','Texture · LUT · Mask','테스트 Map','시각화 · 디버깅','보조 도구'. Yellow 'StarterContent/' description '테스트와 디버깅용 Asset' 'Framework의 필수 의존성 아님'. Retain yellow asset icons labels. Bottom principles only 'Chapter 08 구현 → Chapter 09 Debug / Optimization' and 'Character Rendering은 향후 Advanced 확장' and 'Framework Asset은 Content/ASF/ 아래에서 관리' and 'Starter Content와 분리하여 관리'. Title Figure8-2 ASF Development Environment. No invented folders/verifiedstatus. Clean readable Korean.


## Fig8_03
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.0 프로젝트 생성; 8.1 중복 오참조 정정
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
실제 프로젝트 생성 설정 확인.
Current Text Consistency:
Blank/Blueprint/Desktop/Maximum/ASF_Demo는 보이나 Starter Content와 Ray Tracing 및 실제 버전은 증명되지 않음.
Issue:
⑥ Project Location을 Starter Content로 설명. Architecture 설명 위치에 동일 화면 오참조.
Required Follow-up:
원본 이미지 보존. 8.0 Caption에 증거 한계/번호 오류 명시. 8.1의 잘못된 이미지 삽입 및 Architecture Caption 제거. 실제 버전과 생성 설정 및 생성 후 StarterContent/Rendering 설정을 실제 Unreal에서 캡처.
Final Status:
Retake Required


## Fig8_04
Type:
Unreal Screenshot / Verification Evidence (Type B; UI 영역 보존, 원본 캡처 출처/버전 미확인)
Chapter / Section:
Chapter 08 / 8.0; 8.1 오참조 정정
Action:
Caption / Reference Revision
Evidence Purpose:
Project Settings 항목과 목표 값 확인.
Current Text Consistency:
목표 값은 본문 표와 일치. 기본값 또는 검증 완료 주장은 현재 본문과 불일치.
Issue:
이미지 표의 기본값 단정, Desktop TSR/Mobile TAA 대상 구분, 8.1 Architecture 오참조.
Required Follow-up:
Caption에 목표 환경 및 AA 대상 명시. 8.1 오삽입 제거 완료. UI 픽셀을 보존한 상태에서 외부 표의 기본값을 목표 값으로 정정할 부분 Presentation 편집이 남음.
Final Status:
Presentation Revision Required


## Fig8_05
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.0 폴더 구조; 8.1 오참조 수정
Previous Audit Status:
Major Mismatch / Replace
Action:
Minor Revision
Reason:
주 삽입 목적의 폴더 구조는 유지 가능. Fbx/Meshes 불일치와 Data Flow 오참조를 국소 수정.
Changes:
Fbx를 Meshes로 정정하고 원본 FBX/Import된 Mesh Asset 구분. 폴더 변경 절대 금지를 Reference 확인 원칙으로 수정. 8.1의 잘못된 Rendering Data Flow 이미지 삽입/Caption을 폴더 구조 참조 설명으로 변경.
Technical Verification:
현재 본문의 8개 하위 폴더와 일치. Runtime Module 구조로 재해석하지 않음.
Text Verification:
폴더명, 한국어 설명 및 두 삽입 문맥 대조.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Edit the supplied existing Figure8-5 infographic precisely, preserving layout, all other folders, Korean text, blue header and icons. Replace Fbx folder label with Meshes in BOTH left tree and right table. Left corresponding description '테스트와 예제용 Mesh Asset' with second line '(Import된 Static / Skeletal Mesh 등)'. Right corresponding row replace its bullets with '테스트와 예제용 Mesh Asset을 보관' and '원본 FBX 파일과 Import된 Mesh Asset은 구분'. Bottom structure principle replace '프로젝트가 커져도 폴더 구조는 변경하지 않는다.' with '폴더 구조 변경 시 Asset Reference를 확인한다.' and replace '새로운 기능이 추가되더라도 기존 구조를 유지한다.' with '일관된 구조를 유지하며 필요한 경우 확장한다.' Everything else unchanged. No Unreal UI; this is documentation tree. Crisp accurate Korean. Do not introduce new folders.


## Fig8_06
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.0 Naming
Previous Audit Status:
Match / Keep
Action:
Minor Revision
Reason:
현재 본문과 ASF-001은 의미 있는 Underscore 및 Full Words를 허용/우선함. 과거 Audit의 Keep보다 현재 기준 적용.
Changes:
특수문자 전면 금지 문장을 의미 있는 Underscore 허용으로 수정. GlobalParams→GlobalParameters. Role/기능적 결과 중심 문구와 Platform Prefix/ASF Role Naming 관계 정정.
Technical Verification:
ASF-001 Naming Philosophy 및 현재 8.0 Naming 문단 대조. 예시는 구현 완료 Asset 목록이 아님.
Text Verification:
Prefix/예시 이름 및 한국어 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Precise local text edit of existing Figure8-6. Preserve all layout, icons, colors, table and examples except specified edits. Header info sentence replace with 'Asset 이름은 Type Prefix와 역할을 드러내는 Full Words를 사용한다. 의미 있는 Underscore는 허용한다.' Table last example MPC_GlobalParams replace MPC_GlobalParameters (widen badge/text if needed). Bottom Naming Principles third item currently UnrealEngine generic prefix claim replace with 'Platform의 Type Prefix와 ASF Role Naming을 함께 적용한다.' Bottom fourth item currently 기능이아닌역할 replace with '외형보다 역할과 기능적 결과를 드러내는 이름을 사용한다.' GoodExamples PascalCase sentence replace '단어 구분과 Full Words로 가독성을 높인다'. Do not change any other text, icons or examples. Accurate Korean and English.


## Fig8_07
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.0 Repository Organization
Previous Audit Status:
Match / Keep
Action:
Keep
Reason:
논리적 Repository 예시 및 현재 본문의 변경 확인→Commit→Push→이력 관리 흐름과 일치.
Changes:
없음.
Technical Verification:
실제 폴더 경로와 다른 논리 구조임이 표시되어 있으며 Source/Plugins는 선택 사항. .gitignore 목록은 본문의 기본 프로젝트 예시 범위로 읽음.
Text Verification:
한국어 설명, 경로 예시, 단계 순서 확인.
Final Status:
Complete


## Fig8_08
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.0 준비 요약
Previous Audit Status:
Major Mismatch
Action:
Minor Revision
Reason:
기존 준비 카드 구성을 유지하여 순서/범위/완료 단정 문구를 국소 정정 가능.
Changes:
8.0.5–8.0.6 통합 범위 명시. 다음 8.1 Architecture/8.2 구현과 Chapter 09 Debug/Profiling/Optimization 구분. 완료 체크를 독자 확인용 빈 체크로 변경. 기본 설정→목표 설정.
Technical Verification:
현재 Next Section 및 개발 환경의 목표/검증 구분과 일치. 실제 프로젝트 준비 완료를 주장하지 않음.
Text Verification:
절 번호, 한글 문장 및 체크 항목 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Edit Figure8-8 preserving existing six cards, colors, icons and bottom VersionControl/Ready layout. Specific text corrections: first top sentence replace 'ASF 구현을 시작하기 전에 아래 준비 항목을 확인한다.' second top sentence '모든 항목을 실제 프로젝트에서 확인한 뒤 구현을 시작한다.' Fifth card badge8.0.6→'8.0.5–8.0.6' to cover ProjectOrganization andContentBrowserStructure. Fourth card secondbullet '기본 설정 확인'→'목표 설정 확인'. Replace all green completed checks within sixcards andVersionControl with EMPTY checkboxes to show checklist notclaimedverification. Ready bottomright heading '8.0.9 Ready to Build ASF' preserved but body '모든 준비 항목을 확인했는가?' '프로젝트 구조와 규칙이 정의되었는가?' '확인 후 Shader Framework 구현을 시작한다.' Replace celebration check with checklist icon. Bottom What’s Next text: '다음 Section 8.1에서 Architecture를 확인하고, 8.2부터 기본 Rendering Module을 구현한다.' secondline 'Chapter 09에서는 Debug / Profiling / Optimization을 다룬다.' Keep Anime Shader Framework naming elsewhere. Readable Korean, no added claims. Documentation concept not Unreal evidence.


## Fig8_10
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 Reflection Vector의 L·N
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
동일 공간 Unit L/N의 부호 있는 Dot 계산.
Current Text Consistency:
현재 본문은 양쪽 Normalize 및 Reflection용 원값. 화면은 PixelNormalWS 직접 연결, Saturate 뒤 Emissive와 Lit 결과.
Issue:
[-1,1] Dot와 [0,1] 시각화 값 혼동 및 Lit 화면 수치 검증 한계.
Required Follow-up:
원본 보존, Caption에 실제 연결과 원값/표시값 구분 완료. 양 입력 Normalize, signed Dot 분기, 별도 Debug 시각화, 고정 Exposure/Unlit 조건을 실제 Graph에서 재촬영.
Final Status:
Retake Required


## Fig8_14
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 Reflection Vector
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
R=2(L·N)N−L 실제 구현.
Current Text Consistency:
Dot과 −L 항의 입력 정규화가 다름.
Issue:
Unit L 대신 원래 길이의 L을 빼므로 비단위 입력에서 방향 오류. 마지막 Normalize로 일반 복구 불가. RGB remap/Lit 표시와 계산 혼합.
Required Follow-up:
원본 유지 및 Caption 경고 완료. 동일 Normalize L 출력에서 Dot/−L로 분기, Unit N 준비, Debug 표시 분리 후 실제 재촬영.
Final Status:
Retake Required


## Fig8_15
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 R·V
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
Reflection Vector와 View Direction의 Dot 계산.
Current Text Consistency:
이미지 재확인 결과 Dot 출력은 Base Color로 연결됨. 기존 Audit의 미연결 판정은 채택하지 않음. 0.5R+0.5 Add 출력은 비연결.
Issue:
R 계산에 정규화 전/후 L 혼용 오류가 여전히 있음. Lit BaseColor는 signed Scalar 수치의 직접 표시가 아님.
Required Follow-up:
Caption 실제 연결 정정 완료. 동일 Unit L의 Reflection 계산과 Unit V, signed Dot/Debug 표시 분리 후 실제 재촬영.
Final Status:
Retake Required


## Fig8_16
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 Exponent 8
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
Exponent만 변화시킨 Specular Response 비교.
Current Text Consistency:
Saturate→Power(8) 계산은 맞지만 Lit BaseColor 표시. R 생성부가 잘려 입력 정확성 확인 불가.
Issue:
추가 Lighting과 화면 변환이 Mask를 가림. 앞선 R 연결 오류 수정 여부 및 비교 조건 미확인.
Required Follow-up:
Caption에서 실제 표시 경로 명시. Unit 입력/Reflection 계산 수정 확인 후 8/32/128 비교를 동일 Camera/Exposure/Unlit 출력으로 촬영.
Final Status:
Retake Required


## Fig8_17
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 Exponent 32
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
Exponent 32의 Response 집중도 비교.
Current Text Consistency:
Saturate→Power(32)는 일치하나 Lit BaseColor이며 별도 Specular 반응 포함 가능.
Issue:
R 입력 잘림, 비교 통제 조건 미확인, 순수 Mask와 Lit 결과 혼동.
Required Follow-up:
Caption 정정 완료. Fig8_16/18과 동일 조건의 Unlit Mask 출력 비교 및 R 입력 정확성 확인 후 재촬영.
Final Status:
Retake Required


## Fig8_18
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 Exponent 128
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
Exponent 128의 좁은 Specular Mask 비교.
Current Text Consistency:
Saturate→Power(128)는 일치. Lit BaseColor 출력과 기존 Specular 반응은 Mask 단독 결과가 아님.
Issue:
통제된 비교 및 잘린 R 입력의 정확성 확인 불가.
Required Follow-up:
Caption 보완 완료. Fig8_16/17과 동일 조건으로 실제 Mask Debug 재촬영.
Final Status:
Retake Required


## Fig8_19
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 최종 Specular 합성
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
사용자 Phong Mask를 현재 ASF Color 합성에 통합.
Current Text Consistency:
현재 본문은 Unlit Color 합성. 기존 이미지는 Lit Specular Pin 입력.
Issue:
출력 계약 불일치 및 Unit L/원래 L 혼용.
Required Follow-up:
원본 보존, Caption 정정 완료. 올바른 Reflection 입력과 Mask×Color×Intensity→FinalColor→Unlit Emissive 연결을 실제 캡처.
Final Status:
Retake Required


## Fig8_20
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.4 Phong 기본 Data Flow
Previous Audit Status:
Major Mismatch / Replace
Action:
Replace
Reason:
원본은 L/N 설명만 있으며 캡션이 요구하는 R/V/Power 흐름 부재. Top View 투영도 부정확.
Changes:
Input→Reflection→R·V/Saturate→Power→Scalar Mask와 외부 RGB 합성으로 교체. 단일 평면 P의 L/N/R/V 방향 예시. 같은 Unit L, n>0, 최대값 1 유지 및 교육용 Mask/PBR BRDF 구분.
Technical Verification:
현재 Phong Mask 계약 및 외부 Color/Intensity 합성과 대조. I=−L, R=2(N·L)N−L, Unit 입력, 단계별 분기 확인.
Text Verification:
한국어, 수식, 벡터 방향 검수. 생성본의 Exponent 증가=세기 증가 문구를 삭제/정정 후 최종 저장.
Final Status:
Complete
Generation Method:
Built-in image_gen edit, two iterations.
Prompt Specification:
Replace the supplied inaccurate infographic with a correct documentation diagram for same Figure8-20. Preserve white/blue educational visual language. Title 'Fig 8-20  Phong Specular Data Flow'. Korean prose English technical labels. Three clearly organized Input / Processing / Output panels. Inputs: 'N · L · V' '같은 공간의 Unit Vector' '0이 아닌 입력을 Normalize' and 'Shininess n > 0'. Define N surface normal, L Surface→Light, V Surface→Camera. Center processing EXACT numbered formulas:
1 'R = 2(N·L)N − L' with note '두 항에서 같은 Unit L 사용'
2 's = saturate(R·V)' with note 'R과 V의 방향 비교'
3 'Mask = pow(s, n)' with note 'Shininess로 집중도 조절'
Use one downward arrow between formulas. Show L,N branch to1, V as a side input to2, n side inputto3, or simple input table listing dependence to avoid misleading all-input serial flow. Right output 'Specular Mask' 'Scalar 0–1'; next optional external composition 'Mask × Color × Intensity' 'RGB 기여분 → Final Color'. These are calculations, not GPU stages. Bottom small accurate geometric inset flat horizontal Surface single point P. N verticalup fromP, L up-left fromP, R up-right fromP symmetric aboutN, V a separate up-right steeper fromP. All four arrows point OUTWARD fromsameP. Label 'I = −L' as text only (noextraarrow). '방향 관계 예시' inset caption. Footer '교육용 Phong Mask이며 정규화된 PBR BRDF가 아님' and 'Unlit Emissive 출력에도 Exposure / Tone Mapping이 적용될 수 있음'. No sphere, no topview, no Unreal UI, no claims of validation.
Correction prompt:
Exponent 증가 시 최대값 1 유지, L/R 대칭 및 Output의 ③ Mask 참조 명시.


## Fig8_21
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.4 Light Direction Convention
Previous Audit Status:
Match / Keep
Action:
Keep
Reason:
빛의 입사 진행 방향과 계산용 Surface→Light L을 정확히 구분.
Changes:
없음.
Technical Verification:
현재 Vector Convention과 화살표 방향 일치.
Text Verification:
한국어 설명과 범례 확인.
Final Status:
Complete


## Fig8_22
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.4 L과 N
Previous Audit Status:
Minor Mismatch
Action:
Minor Revision
Reason:
90도 예시의 Light 위치/L 방향 불일치 및 전체 밝기로 읽히는 비교.
Changes:
광원을 수평 L 끝으로 이동. 주 Surface를 평면으로 명확화. Unit N/L, 고정 조건 및 Direct Diffuse 계수 1/감소/0 명시.
Technical Verification:
공통 P의 Surface→Light L과 수직 N, D=saturate(N·L), 90도 계수0 일치.
Text Verification:
한국어 설명과 각도별 광원 위치 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Precise local edit of Figure8-22 preserve composition, all callouts, colors, directions. Main gray wavy surface replace with a flat gray plane through P perpendicular to vertical N; preserve P,N,L and light icon. Lower-right θ=90 example light icon relocate onto horizontal L ray at its far right end; leave N vertical. Lower-left '(최대 밝기)' replace '(Direct Diffuse 계수 1)'. Lower-middle '(밝기 감소)' replace '(Direct Diffuse 계수 감소)'. Lower-right '(Diffuse 0)' replace '(Direct Diffuse 계수 0)'. Lower three example surfaces can stay small tangent humps or flat; all normals at top. Add small readable note at bottom '같은 공간의 Unit N/L · 다른 조건 고정 · D = saturate(N·L)'. No other changes, clear Korean, no invented diagrams.


## Fig8_23
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.4 Dot Product
Previous Audit Status:
Major Mismatch
Action:
Major Revision
Reason:
Unit Vector의 Dot 원값을 0–1로 표시한 주요 범위 오류.
Changes:
Dot 원값 −1~1과 Saturate0~1 구분, 180도 음수 예시. Section8.4.2/8.4.4 정정. Nonzero Normalize, cosθ/acos 구분. 기존 패널 구성 유지.
Technical Verification:
Unit L/N의 Dot 범위 및 Reflection에 signed 원값 사용 확인.
Text Verification:
수식, 부호, 한국어 설명 및 절 번호 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Edit Figure8-23 preserve original sections and layout. Correct raw Dot range without a full redesign. Top subtitle '같은 공간의 Unit Vector L과 N에 대해 L·N = cos θ이며, 결과는 Scalar이다.' Reference 8.1.2→8.4.2. Section1 introductory sentence add '아래 세 그림은 0°≤θ≤90°의 예시이다.' Right 핵심요약 replace entirely with 'Unit Vector의 Dot 원값 범위: −1 ≤ L·N ≤ 1' and bullets '1 → 같은 방향 (0°)' '0.5 → 60°' '0 → 수직 (90°)' '−1 → 반대 방향 (180°)' and bottom 'saturate(L·N)의 범위는 0–1'. Section2 scalar badge0~1→'−1 ~ 1'; its two input vectors separated by AND not plus, label both Unit Vector. Section3 Normalize input labels '(임의 길이)'→'(0이 아닌 입력)'. Section4 next ref8.1.4→8.4.4, keep signed projection2(L·N)N correct and no Saturate inserted. Bottom keypoint replace with 'Unit Vector의 Dot는 cos θ를 반환한다. 각도가 필요하면 θ = acos(clamp(L·N, −1, 1))로 구한다.' second line 'Reflection 계산에는 Saturate 이전의 부호 있는 Dot 원값을 사용한다.' Preserve other meaningful text, clear Korean. First zeroangle L andN arrows may be offset for visibility but label '겹침 방지로 나란히 표시'.


## Fig8_24
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.2 Function Interface
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
MF_BaseLighting의 세 입력과 두 출력 계약.
Current Text Consistency:
Lighting Data 출력 누락. Light Direction/Normal 미연결. Master/Shadow/Lit 결과는 본 절의 Interface 단계와 다름.
Issue:
현재 Scalar D와 RGB B의 이중 출력 계약을 확인할 수 없음.
Required Follow-up:
Caption 한계 명시 완료. MF_BaseLighting 세 입력과 두 출력의 실제 Interface, 입력 타입/기본값을 읽을 수 있게 재촬영.
Final Status:
Retake Required


## Fig8_25
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.2 Base Lighting 테스트
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
BaseColor×D인 Lighting Result 출력 검증.
Current Text Consistency:
실제 연결은 Scalar Lighting Data→Emissive. RGB Lighting Result 미연결.
Issue:
흰색 Scalar 표시로 색상 적용 검증을 주장할 수 없음. Unlit/Exposure 조건도 미확인.
Required Follow-up:
Caption 및 Figure 바로 뒤의 검증 주장 범위 정정. Lighting Result 연결, Material Unlit 설정, 고정 Exposure 및 RGB 결과를 실제 재촬영.
Final Status:
Retake Required


## Fig8_26
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.2 Scene Light Adapter
Action:
Keep Screenshot
Evidence Purpose:
기존 Engine Direction 입력 및 Lighting Result→Emissive 연결 예시.
Current Text Consistency:
현재 본문은 기본 명시적 Vector 입력과 별도 Scene Light Adapter를 구분하고 이 화면을 기존 연결 예시로 한정함.
Issue:
정지 화면만으로 Deferred 지원, Node 부호/Main Light 선택, Light 회전 동작, Unlit 설정을 검증할 수 없음. 현재 Caption이 해당 한계를 명시함.
Required Follow-up:
이번 수정 없음. 실제 지원/동작을 주장할 때만 버전·Rendering Path·부호 및 통제된 Light/Camera 회전 비교 기록 필요.
Final Status:
Keep


## Fig8_27
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.2 전체 Data Flow
Previous Audit Status:
Major Mismatch
Action:
Major Revision
Reason:
독립 L/N Normalize를 직렬화한 잘못된 연결 및 범위 밖 Highlight 출력 예시.
Changes:
독립 Normalize→Dot→Saturate D의 분기와 BaseColor×D=B 경로. 명시적 World Vector/검증된 Adapter 입력 구분. 구 대신 Scalar/RGB 수치 예시.
Technical Verification:
Unit L/N, Dot −1~1, D0~1, B=(0.5,0.1,0.05) 계산 확인. 광량/Shadow/Specular 및 Irradiance와 구분.
Text Verification:
연결과 입력 ② 태그, 수식, 한글 확인. 생성본의 Normal→Dot 우회 경로 제거 후 저장.
Final Status:
Complete
Generation Method:
Built-in image_gen edit, two iterations.
Prompt Specification:
Revise existing TypeA MF_BaseLighting dataflow diagram, preserve three-column Input/Processing/Output and blue green orange purple colors. Title 'Fig 8-27  MF_BaseLighting 데이터 흐름'. Left INPUT three boxes: Light Direction '명시적 World Vector 또는 검증된 Scene Light Adapter' 'Surface → Light'; Normal 'World Space Surface Normal'; Base Color 'Linear RGB'. No Forward-only node claim, no actual Unreal UI. Center MF_BaseLighting: top two SIDE BY SIDE boxes Normalize(L input) and Normalize(N input), with independent direct arrows from respective left inputs. NO arrow between Normalize boxes. Both outputs labeled Unit L and Unit N converge into two pins of Dot Product, then arrow→Saturate. Dot output label 'd = N·L · Scalar −1~1'. Saturate 'D = saturate(d) · Scalar 0~1'. D branches: right output Lighting Data and downward Multiply with BaseColor independentlyinputfromleft. Multiply 'B = BaseColor × D' leads to right output Lighting Result. Rightoutputs ONLY flat numeric swatches (no spheres or highlights): LightingData 'Scalar D' example 'D = 0.5'; LightingResult 'Vector3 B' example 'BaseColor = (1, 0.2, 0.1)' 'B = (0.5, 0.1, 0.05)'. Footer constraints 'N/L은 같은 공간의 0이 아닌 입력' '광량 · 거리 감쇠 · Shadow · Specular는 이 계산에 포함되지 않음' 'D는 Direction Factor이며 Irradiance가 아님'. This is concept flow not executionstage not verified graph. Ensure every external arrow reaches correct operation and no serial L→N. Korean crisp.
Correction prompt:
외부 Normal→Dot 선 제거, 입력 ② 태그로 Normalize(N)에 연결. BaseColor의 B 오표기 제거.


## Fig8_28
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.3 방향 관계와 Visibility
Previous Audit Status:
Minor Mismatch
Action:
Minor Revision
Reason:
입사 진행 방향과 L 혼동 및 단순 계수를 최종 기여로 단정.
Changes:
I=−L과 Surface→Light L 구분. D=saturate(N·L), D×Visibility는 방향·가시성 계수이며 광량/재질항 별도. 기존 차단 비교 구성 유지.
Technical Verification:
입사 화살표는 Occluder에서 종료. N/L Unit 조건과 Saturate 포함. Shadow/방향 관계 구분.
Text Verification:
화살표, 한국어, 수식 확인. 생성본의 잘못된 Cube 횡단 L 선 제거 후 저장.
Final Status:
Complete
Generation Method:
Built-in image_gen edit, two iterations.
Prompt Specification:
Edit existing Shadow infographic with minimal changes, preserve two main comparison panels, objects, layout and colors. In BOTH white light-direction label boxes replace '빛의 방향 (Light Direction)' with '빛의 진행 방향 (I = −L)'. Existing yellow arrows travel from light toward surface/occluder unchanged. Add small blue L arrow from each selected Surface point (base of N) toward its own light, labeled 'L: Surface → Light'; in right occluded panel use dashed blue line toward light to denote direction not transmission, must not bend; left goes up-left fromP. Right yellow travel arrow MUST stop at occluder. Lower left heading '1. N · L (Light Orientation)' replace '1. D = saturate(N·L)' with '방향 계수'. Lower middle Visibility heading preserved. Lower right heading '직접광의 최종 기여' replace '단순화한 방향·가시성 계수', English subtitle 'Direct Factor', formula 'D × Visibility' and small '광량·재질항은 별도'. Lower mini circles remove mislabeled L at inward arrow on Visibility icon or relabel I. Bottom summary replace 'N · L은 빛의 방향을 판단하고' with 'N · L은 두 방향의 관계를 나타내고'. Add 'N/L은 같은 공간의 Unit Vector' in lowerleft note. Do not imply ShadowMap isVisibility or show fabricatedUE. Korean crisp.
Correction prompt:
오른쪽 잘못된 L 선 제거 후 방향 정의 문구만 유지. D 정의 및 단순 계수 제목 정정.


## Fig8_29
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.3 Visibility/Occlusion
Previous Audit Status:
Minor Mismatch
Action:
Minor Revision
Reason:
꺾인 Visibility 검사 경로 및 이진 Visibility 전제/단순식 범위 누락.
Changes:
Occluded 패널을 Light–Occluder–P 직선 검사로 정정. 불투명 단일 광원 표본의 이진 예시 명시. saturate(N·L)×Visibility를 단순 Direct Factor로 한정.
Technical Verification:
검사 경로와 실제 전달광 구분, 이진 Vis0/1 조건, 광량/재질항 별도 확인.
Text Verification:
한국어, 직선 경로의 P 끝점 및 수식 확인. 생성본의 N 끝점 연결 오류를 제거하여 P에 직접 연결.
Final Status:
Complete
Generation Method:
Built-in image_gen edit, two iterations.
Prompt Specification:
Local revision existing Figure8-29 preserve all panels/layout/icons and Korean visual style. Top right Occluded illustration ONLY replace with simple side-view: Light at left, SurfacePointP right, both exactly same vertical height, a vertical rectangular Occluder centered between them. ONE straight horizontal dotted line from Light through blocktoP; yellow before block, gray afterblock. Line is geometric visibility test NOT actual transmitted light. Label '직선 경로 검사' and keep N fromP vertical. No bends or lines around block. Add top subtitle secondline '불투명 차폐물 · 단일 광원 표본의 이진 Visibility 예시'. Bottommiddle heading '5. Direct Lighting과의 관계'→'5. 단순화한 Direct Factor'; formula 'saturate(N·L) × Visibility'; subtitle '광량·재질항은 별도'. Right summary last 'Shadow는 Occlusion으로 인해 Visibility가0이된결과다' replace '이 이진 예시에서 가려진 광원 표본의 Visibility는 0이다.' Middle camera/light mini diagrams annotate '기하학적 검사 경로' so dashed line not transmitted light. All other text preserve. No actual Unreal or synthetic UI. Crisp Korean.
Correction prompt:
Occluded 패널의 N/Surface 제거, 직선 검사 끝에 Surface Point P를 직접 배치.


## Fig8_30
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.3 Shadow Ray
Previous Audit Status:
Minor Mismatch
Action:
Minor Revision
Reason:
전수/최근접 교차가 필수라는 단정 및 Surface P의 자기 차폐 모호성.
Changes:
불투명 차폐/유한 거리 광원 표본 전제. 유효 구간에 차폐 교차 존재 여부를 검사하고 Offset/t_min 설명. Visible 패널 구 제거. Visibility는 직접광의 한 조건으로 명시.
Technical Verification:
수학적 Ray t≥0와 유효 Shadow 구간 구분, any valid occlusion 판단 및 직선 검사 경로 확인.
Text Verification:
한국어, 0/1 분기, Ray 정의 및 종점 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Edit existing Figure8-30 with local corrections preserve layout and colors. Add subtitle '불투명 차폐물과 유한 거리의 광원 표본을 가정한다.' Top visible illustration remove sphere completely, leave SurfacePointP on flatplane and unobstructed straight dotted P→Light. Top occluded illustration keep straight dotted P→Light blockedcube. Dotted lines depict geometric tests. In section3 first description replace with 'P에서 Light까지의 유효 구간에 차폐 교차가 있는지 검사한다.' Replace bullet '가장 가까운 Intersection만이 Shadow를 결정한다.' with '유효한 차폐 교차를 하나 찾으면 가림을 판단할 수 있다.' Replace bottomred label '가장 가까운 Intersection (= Occluder)' with '유효한 차폐 교차 → Visibility = 0'. Replace '모든 Geometry' wherever present with '차폐 Geometry 후보'. Add section3 short '시작점 Offset 또는 t_min으로 자기 교차 오차를 줄인다.' Section4 decision use '유효 구간에 불투명 차폐 교차가 있는가?' with '(광원 표본 이전)' and final blue box 'Visibility를 Direct Lighting 계산에 반영'. Section5 lastsummary replace 'Visibility 결과가 Direct Lighting의 존재여부를결정...' with 'Visibility는 직접광 기여의 한 조건이며 방향·광량·재질항도 함께 고려한다.' Keep mathRay Origin+tDirection t≥0, no claiming ray alwaysfinite: distinguish shadowtestsegment. Clear Korean.


## Fig8_31
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.3 Shadow Map
Previous Audit Status:
Major Mismatch
Action:
Major Revision
Reason:
같은 Light-space UV의 Depth Sample 의존성 누락, Camera-visible P 배치 오류, Ray 동등성/비용 단정.
Changes:
Light Depth 저장→P의 Light Projection/Divide/규약 적용→동일 UV Sample/Depth 비교→Visibility 적용 흐름. near-small와 bias 비교 명시. Depth 자료/Visibility/단순 Lighting Factor 분리.
Technical Verification:
0.4−0.01≤0.4와 0.7−0.01>0.4 예시 확인. Reversed-Z/UV 규약은 실제 저장 방식과 일치해야 함. Renderer 구현과 MF 수동 Vis 예제 구분.
Text Verification:
한국어, 부등식, 표의 수치, 입력 분기 확인. 생성본의 고정 UV 변환 가정과 bias 없는 요약 문장 정정 후 저장.
Final Status:
Complete
Generation Method:
Built-in image_gen edit, two iterations.
Prompt Specification:
Replace inaccurate Figure8-31 with technically exact Shadow Map educational infographic, white background blue/green/orange/purple headers consistent with input. Title 'Figure 8-31  Shadow Map의 원리'. Four panels plus footer. Top-left '① Light View에서 Depth 저장' show Geometry → Light Projection → Shadow Map texture with note '각 Texel에 가장 가까운 Surface의 Depth 저장'. This depth texture is DATA notVisibility. Top-right '② Camera에 보이는 P를 Light Space로 변환' show World positionP → Light View/Projection → Perspective Divide → (UV, zP). Note 'UV와 zP는 같은 Light Projection에서 계산'. Avoid geometry camera line, use dataflow only. Bottomleft '③ 같은 UV에서 Depth 비교' show two INPUT arrows: (UV,zP) and ShadowMap depthtexture; use exact numbered calculation list 'zMap = sampleDepth(ShadowMap, UV)' then 'Vis = 1 if zP − bias ≤ zMap, else 0'. Note '이 그림은 가까울수록 작은 Depth 규약' '실제 구현의 Reversed-Z 등 규약에 맞춰 비교 방향을 적용'. Show simple table columns zP,zMap,bias,Vis: rows0.4,0.4,0.01,1;0.7,0.4,0.01,0. Do NOT physically distance label projectedDepth. Bottomright '④ Visibility를 조명에 적용' show 'Shadow Map (Depth 자료) ≠ Visibility (비교 결과)' then 'D = saturate(N·L)' '단순 Direct Factor = D × Vis' '광량·재질항은 별도'. Footer '해상도·Depth 정밀도·Bias·Filtering에 따른 근사 오차가 있음' 'Ray 방식과 정확히 동일한 결과 또는 항상 더 빠른 성능을 보장하지 않음' 'MF_Shadow의 수동 Visibility 예제와 Renderer Shadow Map 구현은 별도'. Short crisp Korean, no fakeUnreal screenshot, no lit result sphere, no 3D rays needed. Correct branchingnotserialUVtoTexture. Alltextreadable.
Correction prompt:
UV/Depth 규약 적용으로 특정 변환 가정 제거. zP−bias>zMap 조건으로 표 설명 정정. Visibility thumbnail 개념 예시 표시.


## Fig8_32
Type:
Unreal Screenshot / Verification Evidence (Type B 보호 처리; Rendering 비교 영역의 실제 캡처 여부/출처 미확인인 복합 Figure)
Chapter / Section:
Chapter 08 / 8.3 Shadow 품질
Action:
Caption / Reference Revision
Evidence Purpose:
Aliasing/Acne/Bias 비교 결과로 제시된 영역 보존.
Current Text Consistency:
Camera 거리와 Texel 범위의 무조건적 관계, Acne=자기 그림자 표현, Filtering 포함 캡션은 부정확.
Issue:
결과 이미지 출처/통제 조건 미확인. Peter Panning 예시는 Geometry도 떠 보이므로 Shadow만 분리된 비교로 사용할 수 없음.
Required Follow-up:
Caption에서 조건/용어/Filtering 범위 정정 완료. 원본 결과 영역은 AI 재생성하지 않음. 출처 확인 후 결과 픽셀 보존 Label 수정; 실제 검증 자료로 사용할 경우 동일 접지 Geometry/Camera/Exposure에서 Bias만 바꾼 캡처 확보. 현재는 재촬영 확정 대신 보호 부분 수정 대기.
Final Status:
Presentation Revision Required


## Fig8_33
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.3 Visibility의 기여 제한
Previous Audit Status:
Major Mismatch
Action:
Major Revision
Reason:
Vis0/0.5/1의 구 밝기가 수치와 불일치, V 기호 충돌 및 중간값 의미 모호.
Changes:
같은 P의 C=(1,0.4,0.2)에 Vis1/0.5/0 적용한 수치/막대 비교. 다른 조명/Emission 합산과 화면 밝기 구분. Vis/V 및 단일 표본/Filtering 집계 구분.
Technical Verification:
C×Vis 수치 확인 및 Visibility 한 번 적용. Vis0이어도 다른 기여가 남을 수 있음. MF_Shadow 수동 Vis 범위 명시.
Text Verification:
숫자/한글/분기/합성 범위 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Replace inaccurate Figure8-33 concept comparison with precise educational infographic keeping white bluegreenorangepurple style. Title 'Figure 8-33  Visibility와 Light Contribution'. No spheres or simulated engine results. Top broad flow '차폐가 없다고 가정한 한 Light의 RGB 기여 C' and separate '현재 표면점 P의 Visibility Vis' both arrowsinto Multiply→'Cshadow = C × Vis'→'다른 Light 및 Indirect 기여와 합산'. Note 'Visibility는 한 번 적용한다'. Middle 3 equal cards compare SAME point and C=(1,0.4,0.2): 'Vis = 1' output '(1,0.4,0.2)'; 'Vis = 0.5' output '(0.5,0.2,0.1)'; 'Vis = 0' output '(0,0,0)'. Use flat colored patches plus exact numbers and proportional bars full/half/zero. All patches schematic not measurement. Below '선형 RGB 기여 비교 · 최종 화면 밝기 비교가 아님'. Rightsmall note 'Vis=0이어도 다른 Light·Indirect·Emission이 있으면 최종 표면은 검정이 아닐 수 있다'. Bottom definitions two boxes: 'Visibility (Vis)' '단일 불투명 광원 표본의 검사는 0 또는 1'; '중간값' '면광원 표본의 집계 또는 PCF 비교 결과의 Filtering 등에서 얻는다' '구 전체에 도달한 광선 수의 비율이 아님'. Technicalfooter 'Vis는 Visibility, V는 View Direction으로 구분' 'Shadow Map은 Depth 자료이며 비교/Filtering 후 Visibility를 얻는다' 'MF_Shadow 기본 예제는 수동 Vis를 입력받는다'. Short exact Korean, no serial GPU stage claim.


## Fig8_34
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.3 Basic Shadow Observation
Action:
Caption / Reference Revision
Evidence Purpose:
Sphere의 명암과 Plane의 Cast Shadow 기본 관찰.
Current Text Consistency:
관찰 목적과 화면은 일치.
Issue:
실제 Shadow 방식/버전/Mobility는 화면만으로 확인 불가.
Required Follow-up:
Caption에 두 관찰 대상 및 내부 Shadow Map 검증 한계 명시 완료. 원본 유지.
Final Status:
Keep


## Fig8_35
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.3 Shadow Debug View
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
특정 Shadow 중간 Buffer의 의미를 관찰.
Current Text Consistency:
본문은 정확한 Mode/Buffer 확인을 요구하나 화면에 표시 없음.
Issue:
Depth/Vis/ShadowMask 식별 불가. 색조만으로 데이터 종류 판정 불가.
Required Follow-up:
Alt/Caption의 확정적 ShadowMap Debug 명칭 정정. 실제 Mode 선택 또는 Command, Engine/ShadowMethod, 범례/값 범위를 포함해 재촬영.
Final Status:
Retake Required


## Fig8_36
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.3 Object Motion
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
Sphere 이동에 따른 Shadow 갱신 확인.
Current Text Consistency:
본문의 한계 문구는 있으나 그림은 Light 선택 상태이고 Sphere 전후 비교가 없음.
Issue:
변경 대상/위치값/Debug 의미를 확인할 수 없음.
Required Follow-up:
Alt/Caption 정정 완료. Camera/Light 고정, Sphere 위치만 변경한 전후 실제 캡처와 Mobility/Cache/Method/Mode 기록.
Final Status:
Retake Required


## Fig8_37
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.3 Mobility
Action:
Caption / Reference Revision
Evidence Purpose:
Sphere Mobility=Movable 및 현재 Transform 확인.
Current Text Consistency:
설정 자체는 명확. 이동/갱신까지 주장하던 Alt 범위를 축소.
Issue:
단일 화면으로 동적 동작 확인 불가.
Required Follow-up:
설정 확인 Caption/Alt 정정 완료. 원본 유지. 이동 전후는 Fig8_36 Queue에 통합.
Final Status:
Keep


## Fig8_38
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.3 Object Scale
Action:
Caption / Reference Revision
Evidence Purpose:
비균일 Scale(1,1,2) 설정과 Geometry 변화 확인.
Current Text Consistency:
값과 길어진 Geometry는 확인 가능.
Issue:
표면 계단형 Artifact와 잘린 바닥 Shadow는 전체 Shadow 비교를 제한.
Required Follow-up:
Caption/Alt에 관찰 범위와 Artifact 분리 명시 완료. 원본 유지. 향후 전체 Shadow 비교가 필요할 때 동일 Camera/Light와 전체 Shadow 프레임으로 보완.
Final Status:
Keep


## Fig8_39
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.3 Shadow 품질 관찰
Action:
Retake Screenshot / Caption / Reference Revision
Evidence Purpose:
Shadow 해상도가 품질에 미치는 영향의 통제된 비교.
Current Text Consistency:
화면에 해상도값 및 동일 조건/변경 변수 정보 없음.
Issue:
Mesh/Normal/Material/Bias/Filtering 차이를 배제할 수 없음.
Required Follow-up:
Alt/Caption에 한계 명시 완료. 같은 조건에서 해상도 관련 변수 하나만 바꾼 실제 값/라벨 포함 비교 캡처.
Final Status:
Retake Required


## Fig8_40
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.3 Artifact 진단 가이드
Previous Audit Status:
Minor Mismatch
Action:
Minor Revision
Reason:
오래된 번호와 개선 여부만으로 단일 원인을 확정하는 분기.
Changes:
8-40 번호 정정, 한 변수 변경 후 영향 가능성으로 표현. Direct Shadow/GI/Reflection 경로 및 버전 지원 구분. MissingShadow 예시의 입증 한계, 개념 그림임을 명시.
Technical Verification:
진단은 후보를 좁히는 절차이며 단독 원인 증명 아님. 설정/Mode는 버전과 Path별 확인. 기존 흐름 유지.
Text Verification:
한국어, 분기 결과 및 용어 확인.
Final Status:
Complete
Generation Method:
Built-in image_gen edit.
Prompt Specification:
Precise text-only edit of Figure39 Shadow Artifact diagnosis infographic, preserving layout and all small illustrative thumbnails. Change top badge39→'8-40'. Add smallsubtitle '예시 이미지는 개념 설명용이며 실제 원인을 확정하는 증거가 아님'. Change ALL five Yes outcome labels from definite causes to possibilities: 'Geometry / Normal 영향 가능성', '해상도 / Filtering 영향 가능성', 'Bias 영향 가능성', 'Distance / VSM 설정 영향 가능성', '설정 영향 가능성'. All five '개선되는가?' labels→'한 변수 변경 시 개선되는가?'. Section3 replace bullet 'Lumen / HWRT Shadow / SSG 등' with 'Direct Shadow와 GI / Reflection 경로 구분'; replace 'Shadow Type (VSM / Ray Traced / CSM)' with '현재 Shadow Method와 지원 조건 확인'; replace icons label Lumen with 'GI / Reflection' while retaining icon. At section3 add note '버전·Rendering Path에 따라 조절 항목이 다름'. Right last MissingShadow bullet replace with '기준 화면과 비교해 누락 여부 확인' and secondline '이 예시만으로 누락을 입증하지 않음'. Right SelfShadowingNoise bullet replace 'Bias / Depth 비교 오차 등 원인 확인'. Right PeterPanning '그림자가 물체에서 떨어짐' canstay. Preserve footer one-variabletesting, beforeafter/record. No fake Unreal UI. All changes Korean readable; shrink only if needed.


## Fig8_41
Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.5 Rim 기초
Previous Audit Status:
Major Mismatch
Action:
Major Revision
Reason:
Scene Setup의 Camera/정면점/실루엣 표본 위치가 모순.
Changes:
직교 투영 측면 단면에서 A를 왼쪽 정면 Surface, B를 위 접선 지점으로 배치. N/V 공통 P 방향 및 N·V1/0 명시. 화면 구 표시와 단면 구분.
Technical Verification:
V는 Camera 쪽, A에서 N/V 일치, B에서 수직. r=1−saturate(N·V). 정확한 Screen-space 외곽선 검출 및 물리 Fresnel과 구분.
Text Verification:
한국어, P 위치와 화살표 확인. 생성본의 두 P/잘못된 평면을 추상 벡터 도식으로 정정 후 저장.
Final Status:
Complete
Generation Method:
Built-in image_gen edit, two iterations.
Prompt Specification:
Correct existing Figure8-41 Rim infographic preserve three-panel layout and blue/green/red style, gray circle appearance. Title 'Fig 8-41  Rim Mask의 기초: N·V'. Subtitle '같은 공간의 Unit N과 V로 표면의 시선 방향 관계를 계산한다'. Firstpanel heading '1. 측면 단면 (직교 투영 예시)'. Circle is sphere SIDE CROSS SECTION. Camera on farleft, viewing parallel left-to-right. PointA MUST be LEFTMOST point on circle boundary (not center), pointB MUST be TOPMOST point on circleboundary. AtA greenV andblueN arrowsboth pointLEFT fromsameA, mayoffsetwithnote. AtB blueN arrowUP fromB, greenV arrowLEFT fromB. All areoutwardfromSurface. Small note '직교 투영 예시: V는 모두 Camera 쪽(왼쪽)' and 'A: 정면 중심 / B: 접선 지점'. No rightmost silhouette point. Centerpanel heading '2. 같은 지점의 N과 V'. Two mini vector diagrams: A flat P with coincidentleftwardN,V, N·V=1; B P withNup,Vleft,N·V=0. No sphere shading neededhere. Thirdpanel heading '3. 화면에서 본 s = saturate(N·V)' retain smooth brightcenter blackedge sphere as CONCEPT visualization only '매끈한 구의 개념적 표시'. footer important 'Shading Normal 기반 View-dependent Mask이며 정확한 Screen-space 외곽선 검출이 아님' and '실제 Mesh의 Normal과 Camera 투영에 따라 분포가 달라짐'. Nextstep 'r = 1 − saturate(N·V)' '정면에서 0, 접선에서 1' for basicRim. No light direction or physicalFresnel. NoPerspectivecamera mislabeled.
Correction prompt:
중앙 A는 단일 P와 겹치는 N,V 화살표, B는 단일 P의 수직 벡터. 중앙 오해 가능한 Surface 제거, 겹침 방지 Offset 설명.


## Fig8_42
Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5 N·V Debug
Action:
Caption / Reference Revision
Evidence Purpose:
PixelNormalWS/CameraVector→Dot→Saturate→Emissive 연결과 정성적 분포.
Current Text Consistency:
현재 단계의 연결 및 정면/접선 분포와 일치.
Issue:
화면 밝기의 수치 해석 및 바닥 Cast Shadow를 Rim 결과로 오인할 여지.
Required Follow-up:
Caption에 Unit 입력, 화면 변환 및 바닥 Shadow 분리 명시 완료. 원본 유지.
Final Status:
Keep


## Fig8_43

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5.2
Action:
Keep Screenshot
Evidence Purpose:
One Minus로 1 - saturate(N·V) Rim Mask를 만드는 기본 Graph와 정성적 결과.
Current Text Consistency:
PixelNormalWS와 Camera Vector의 Dot → Saturate → OneMinus → Emissive 연결, 중앙이 어둡고 가장자리가 밝은 Sphere가 현재 본문과 일치한다.
Issue:
수정 필수 사항 없음. 화면 밝기를 Mask의 수치로 해석하지 않으며 바닥 Cast Shadow는 Rim 결과와 구분한다.
Required Follow-up:
없음. 실제 Unreal 재실행 검증을 수행한 것은 아니다.
Final Status:
Keep



## Fig8_44

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5.3
Action:
Keep Screenshot
Evidence Purpose:
같은 Rim 기본 Mask에 Power의 Exponent 1과 4를 적용한 형태 비교.
Current Text Consistency:
위쪽 RimPower 1, 아래쪽 4가 실제 Parameter와 일치하며, 4에서 중간 Gray 영역이 감소한다. 뒤의 Width/Softness 방식에 앞선 Power 학습 단계로 적절하다.
Issue:
수정 필수 사항 없음. Power는 중간 값을 줄이며 최대값 1을 높이지 않는다. 화면 결과는 정성적 비교이며 수치 측정 증거가 아니다.
Required Follow-up:
없음. Screenshot 원본 보존.
Final Status:
Keep



## Fig8_45

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.5.4
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
기존 Schlick 곡선이 수식과 불일치하고 Camera에서 발사되는 듯한 광선 및 반사각이 잘못되었다.
Changes:
광선 대신 Surface→Camera 시선 V와 Normal 도식으로 정리. 잘못된 곡선을 계산값 표로 교체. 매끄러운 Interface의 N·V 설명과 Microfacet의 V·H를 구분하고 반사율/화면 밝기/Rim Mask의 역할을 분리.
Technical Verification:
F0=0.04에서 c=0/0.25/0.5/0.75/1에 대해 F=1/0.2678125/0.07/0.0409375/0.04 일치. Rim은 1-saturate(N·V)의 양의 거듭제곱, 동일 공간 Unit Vector 조건 확인.
Text Verification:
현재 8.5.4의 Schlick 적용 범위와 Prototype Rim 비교에 일치. 수식 및 표의 숫자, Korean Label을 시각 검토.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Edit this conceptual educational infographic Fig8_45. Retain polished Korean textbook infographic style, white background navy blue numbered section headers, blue green orange accents, large readable text. Major technical correction, four clear horizontal sections. Title "Fresnel, Schlick Approximation, 그리고 Rim Light".
1 "관찰각과 반사율": two flat horizontal surface diagrams with black P on surface and dashed N upward. Left blue V arrow FROM P nearly vertically upward labelled "정면: N·V ≈ 1". Right green V arrow FROM P nearly horizontally upward right labelled "Grazing: N·V ≈ 0". These are ONLY viewing direction arrows, no incident/reflected ray arrows, no camera-emitted rays. Explain "V: Surface → Camera, 단위 벡터" and "반사율 증가는 최종 화면 밝기와 다르다".
2 "Schlick Approximation": compact flow "Fresnel Equation" → "반사율을 간단한 식으로 근사" → "Schlick Approximation". Note "매질과 적용 조건에 따른 근사".
3 "수식과 수치 예": large F = F0 + (1 − F0)(1 − c)^5 ; c = saturate(N·V). Label "매끄러운 Interface의 관찰각 설명". Instead of erroneous curve, use exact numeric table with columns c / 0 / 0.25 / 0.5 / 0.75 / 1 and F(F0=0.04) / 1 / 0.2678125 / 0.07 / 0.0409375 / 0.04. Clear monotonic horizontal bars optional, NO smooth curve needed. Formula note "F0: 정면 반사율" "Microfacet BRDF: 기여 Facet의 Fresnel 각도는 V·H".
4 "Rim Mask와의 차이": two cards Schlick "F0 + (1 − F0)(1 − c)^5" "물리 반사율의 근사" versus Rim "r = 1 − saturate(N·V)" "Mask = r^p, p > 0" "스타일 표현을 위한 Mask". Footer "공통점: 관찰각에 의존 / 차이점: 반사율과 연출 Mask는 역할이 다르다". N,V unit same space. No fake Unreal UI. Preserve purpose comparison, use exact formulas and values. No equation using unsaturated negative dot for Rim, no claims actual measurement or engine verification.



## Fig8_46

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5.5
Action:
Keep Screenshot
Evidence Purpose:
Power 기반 Prototype의 MF_RimLight 내부와 테스트 Material 호출부.
Current Text Consistency:
Normal/View Direction/RimPower → Dot/Saturate/OneMinus/Power → RimMask와 Emissive Debug가 본문에 일치. 현 Section 시작의 동일 공간 Unit Vector 입력 전제를 적용한다. 이후 Width/Softness 최종 Interface로 교체되는 중간 단계이다.
Issue:
수정 필수 사항 없음. 현재 최종 Interface의 증거로 확대 해석하지 않는다.
Required Follow-up:
없음. 원본 보존, 실제 Engine 실행 검증은 별도.
Final Status:
Keep



## Fig8_47

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5.6
Action:
Keep Screenshot
Evidence Purpose:
RimMask에 동일 RimColor와 Intensity 1/2를 곱한 정성적 비교.
Current Text Consistency:
상단 1, 하단 2의 Parameter 값과 Emissive 연결이 보이며, 밝아진 Gradient가 더 넓게 지각될 수 있다는 설명과 일치. Mask 계산 영역과 지각 Width를 본문에서 구분한다.
Issue:
수정 필수 사항 없음. 화면 밝기 2배 또는 실제 Mask Threshold 이동을 증명하는 이미지로 사용하지 않는다.
Required Follow-up:
수치 재현 시 Camera/Exposure/Bloom 조건 고정. 현재 정성 예시의 원본은 유지.
Final Status:
Keep



## Fig8_48

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5.6
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
RimWidth/RimSoftness 개별 조절 비교.
Current Text Consistency:
세 값은 본문 비교와 일치하지만 최종 계약에 없는 RimPower=4 입력이 모두 남아 있고 내부 Graph가 보이지 않는다.
Issue:
최종 BaseRim→Smoothstep 계산을 검증할 수 없음. 이전 Audit의 Minor보다 실제 재촬영이 필요.
Required Follow-up:
최종 4개 입력과 내부 계산, 유효 범위 0<Softness≤Width≤1, Width=0 Off/Softness=0 Step 정책을 확인하고 실제 비교 촬영. 원본 유지, 중간 실험임을 Caption에 명시.
Final Status:
Retake Required



## Fig8_49

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.4 Function Integration
Action:
Keep Screenshot + Caption Correction
Evidence Purpose:
Phong Specular 계산을 4개 입력/Scalar Mask 출력의 Function으로 분리한 내부 Graph.
Current Text Consistency:
L과 N Normalize 및 동일 Unit L의 두 분기 사용이 정확하다. ViewDirection은 호출부 Unit Vector 계약으로 허용되며 현재 본문과 일치.
Issue:
이미지 자체에 입력 공간 및 V 정규화 전제가 없어 Caption에 명시. Shininess>0, 외부 Color/Intensity와 교육용 Mask 범위도 설명.
Required Follow-up:
없음. 실제 Graph 재촬영 없이 Caption으로 입력 계약 보완.
Final Status:
Keep



## Fig8_50

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.5 Integration
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
Base Lighting, Specular, Rim의 순차 합성 비교.
Current Text Consistency:
세 Intensity 조합과 Add는 일치하지만 Unlit 설정 및 최종 Emissive 연결이 잘려 있다.
Issue:
통합 출력의 핵심 연결을 확인할 수 없음. Scene Cast Shadow는 MF_Shadow 결과가 아니다.
Required Follow-up:
기존 화면 보존, Caption에 증거 범위 명시. 재촬영 Queue에 최종 연결/설정 및 고정 조건 비교 등록.
Final Status:
Retake Required



## Fig8_51

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.6.2
Previous Audit Status:
Minor Mismatch / Minor Revision
Action:
Minor Revision
Reason:
정면 Normal이 아래 방향으로 표시되고 Camera가 구 아래에 있어 정면 투영과 장면 배치가 혼동되었다.
Changes:
두 중심 Normal을 ⊙ 화면 밖 방향으로 수정. 아래 Camera와 연결선을 방향 범례로 교체. 정쪽 오탈자 수정, Down/Grazing 설명 및 View 축/Texture V 규약 확인 문구 보완.
Technical Verification:
정면/화면 아래/가장자리 방향이 구분된다. MatCap이 Mesh 위치 대신 Camera 기준 Normal로 Appearance를 조회한다는 원리를 유지.
Text Verification:
현재 MatCap Lookup 설명과 일치. Korean Label과 방향 기호 시각 검토.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Edit this existing conceptual MatCap educational infographic with MINOR revisions preserving the three-column layout, Korean explanation, colors and sphere/texture examples. Correct camera coordinate confusion. In BOTH spheres change the central green downward Normal arrow to a green circled dot ⊙ meaning out of screen toward camera. Label both "정면을 향한 Surface (정면 Normal)". Fix typo 정쪽. Remove the camera icon BELOW left sphere and its vertical dashed connection entirely. In its place place a simple legend without arrow: "⊙ 화면 밖 독자를 향함" / "Camera는 화면 정면에 위치". Retain red DOWN Normal arrows at bottom as distinct from Front Normal. Bottom-right explanation row for Down Normal should say "화면 아래 방향 성분을 가진 Normal". Grazing row should say "Camera 시선과 거의 수직인 Normal / Texture 원판의 가장자리". Preserve all other instructional scope. Add compact small note above bottom summary "View 축과 Texture V 방향은 사용한 변환 규약에 맞춰 확인한다." No fake engine UI, no new photoreal render comparison, conceptual diagram only. Clear legible Korean English terms.



## Fig8_52

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.6.3
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
World Y-up, 가려진 P를 지나는 Camera 선, 검증할 기저 없는 숫자, Camera 이동/회전 혼동을 수정.
Changes:
World Z-up 도식 및 명시적 직교 Unit 기저의 두 수치 예로 교체. 방향 변환에 Translation을 적용하지 않음과 순수 평행이동/회전 구분. Normalize→XY→UV→Sample 및 V 반전 규약 확인 추가.
Technical Verification:
Nworld=(0,0,1), A 기저에서 (0,1,0), B 기저에서 (0,0.6,-0.8). 두 기저의 길이 1 및 직교 확인. 예시 기저는 특정 Engine 축 규약으로 단정하지 않는다.
Text Verification:
현재 MatCap의 Camera 기준 방향 변환과 축/V 방향 확인 계약에 부합. 표/수식/화살표 시각 검토.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Revise this conceptual Fig8_52 infographic substantially for correctness while preserving Korean textbook style, blue World panel / green View panel / lower lookup flow, white background. Title "왜 View Space Normal을 사용하는가". Top statement "MatCap은 Camera 기준 Surface Normal 방향으로 Appearance를 조회한다."
Replace confusing sphere/cameras with exact basis diagrams and numeric example. World panel: a single flat surface P with N upward and coordinate triad explicitly "World Z-up", Z upward X right Y diagonal. Text "고정된 Surface: N_world = (0, 0, 1)" and "Camera만 움직여도 같은 지점의 World Normal은 유지".
View panel should be two cards, NOT unverifiable physical camera geometry:
"Camera Orientation A" with explicit basis components expressed in World:
"right = (1, 0, 0)"
"up = (0, 0, 1)"
"forward = (0, 1, 0)"
"N_view = (0, 1, 0)"
"Camera Orientation B" with:
"right = (1, 0, 0)"
"up = (0, 0.8, 0.6)"
"forward = (0, 0.6, −0.8)"
"N_view = (0, 0.6, −0.8)"
Label the whole numerical example "축 변환 계산 예시 — 특정 Engine의 축 규약을 단정하지 않음". No claims P visible from both; no surface visibility example. Show equation "N_view = (dot(N_world,right), dot(N_world,up), dot(N_world,forward))". All vectors unit, basis orthogonal.
A wide distinction strip: "회전: View 기저가 달라져 Normal 성분이 달라질 수 있음" and "순수 평행이동: 같은 World Normal의 방향 성분은 변하지 않음". "방향 벡터이므로 Camera Translation을 더하지 않는다."
Bottom flow: "World Normal" → "World→View 방향 변환" → "Normalize" → "XY 추출" → "UV = 0.5 × N_view.xy + 0.5" → "MatCap Texture Sample". Footer "View 축 부호와 Texture V 방향을 확인하고 필요한 V 반전을 적용한다." "Mesh UV나 Screen Position을 조회 좌표로 사용하지 않는다." Avoid unnecessary camera rays or old false camera Z sign statements. Keep all Korean crisp and formulas exact.



## Fig8_53

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.6.4
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
Normal Z를 Camera 거리/Depth로 설명하고 Range Remap과 최종 Texture 방향을 혼합하였다.
Changes:
Normal은 방향 성분임을 명시하고 모순된 Camera 광선 제거. Unit Normal XY의 원판, raw Remap, V가 아래로 증가하는 Texture의 Flip 예를 분리.
Technical Verification:
Raw -1/0/1→0/0.5/1과 최종 Up→V0, Down→V1, Center→(0.5,0.5) 확인. View 축 가정과 Flip 조건 명시. 위치 Depth를 사용하지 않는다.
Text Verification:
현재 Remap 학습 단계 및 후속 V Flip 구현에 일치. 중심의 Normal XY/UV를 명시적으로 구분해 재검토.
Final Status:
Complete
Generation Method:
Built-in image_gen, original reference and one label clarification pass.
Prompt Specification:
Correct Fig8_53 educational infographic, preserving four-column numbered workflow, Korean text English technical terms, navy blue accents white background. Title "View Space Normal을 MatCap UV로 변환하기". 
Column1 "View Space Normal": replace incorrect camera/sphere/ray diagram with an abstract origin and a direction N arrow, labels "N_view = (Nx, Ny, Nz)", "Unit Vector". Text "X, Y, Z는 방향 성분이다." "Normal의 Z는 Camera 거리나 Position Depth가 아니다." "아래 예시는 화면 오른쪽 +X, 위쪽 +Y인 기저를 가정한다." Do not assert Engine-specific Z sign.
Column2 "XY 추출": keep signed XY plot Xright+, Yup+, percomponent [-1,1]. "N_view.xy = (Nx, Ny)" and "단위 Normal의 XY는 단위 원판 안에 있다." No Screen Position input.
Column3 "Range Remap": "UV_raw = 0.5 × N_view.xy + 0.5". Table percomponent -1→0,0→0.5,1→1. "이 단계는 값 범위 변환이다."
Column4 "Texture 방향 적용": clear formula "U = 0.5Nx + 0.5" "V = 1 − (0.5Ny + 0.5)" and heading "Texture V가 아래로 증가하는 예". A square texture coordinate chart U increases right, V increases DOWN, origin (0,0) at TOP LEFT, top V0 bottom V1. Center(0.5,0.5), Up Ny1 atTOP V0, Down Ny−1 atBOTTOM V1, leftNx−1U0,rightNx1U1. Use simple disk with sampled dots no confusing shaded lighting. Footer "View 축과 MatCap Texture 방향을 확인하여 V Flip 적용 여부를 결정한다." "Range Remap과 Texture 방향 보정은 별도 단계다." Do not represent Normal Z as distance, no camera ray through sphere. Precise Korean and math legible.
Refinement:
Make only text clarification edits preserving this infographic exactly otherwise. In column4 center point label replace ambiguous 'Center (0, 0) (0.5, 0.5)' with 'Center / Normal XY = (0, 0) / UV = (0.5, 0.5)'. In column3 table output heading replace '(U 또는 V)' with '(U_raw 또는 V_raw)' to distinguish remap from final V flip. Do not change any numbers formulas colors arrows or diagrams.



## Fig8_54

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.6.5
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
World→View Normal 변환과 서로 다른 Camera에서의 Debug 비교.
Current Text Consistency:
Raw RGB Graph는 일치하나 Camera 비교 View Mode가 Lit/Unlit로 다르다.
Issue:
Camera 효과 외 표시 조건이 섞이고 Raw 음수 성분을 화면에서 읽을 수 없다.
Required Follow-up:
View Mode와 Exposure/Post Process를 통일한 실제 촬영. 기존 이미지 보존 및 Raw/Remapped Debug 차이와 조건 불일치 Caption 추가.
Final Status:
Retake Required



## Fig8_55

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.6.5
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
V Flip 이후 원본 MatCap과 Lookup 방향의 일치 확인.
Current Text Consistency:
보이는 Remap/V Flip/Texture Sample/Emissive 연결은 맞지만 원본 Texture와 전체 변환 Graph가 누락됨.
Issue:
원본 방향 일치를 직접 확인할 수 없어 본문의 해당 확인 단정을 이미지에서 확인 가능한 범위로 수정.
Required Follow-up:
원본 Texture 방향 표시와 전체 Graph를 포함한 실제 재촬영. 현재 이미지 보존 및 Caption 보완.
Final Status:
Retake Required



## Fig8_56

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.6.6
Action:
Keep Screenshot + Caption Correction
Evidence Purpose:
World Normal과 Texture Object 입력에서 MatCap RGB Lookup 출력을 만드는 내부 Graph.
Current Text Consistency:
World→View, RG, Remap, V Flip, Texture Sample 및 RGB 출력이 현재 책임 분리에 일치.
Issue:
Asset 표기는 MF_Matcap으로 문서 MF_MatCap과 차이. 입력의 World Space Unit Vector 전제를 Caption에 명시.
Required Follow-up:
없음. 원본 Asset/UI를 조작하지 않고 기존 표기 차이를 명시. Texture Object와 RGB 및 외부 Intensity 역할 구분 완료.
Final Status:
Keep



## Fig8_57

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.6.7
Action:
Keep Screenshot
Evidence Purpose:
ASF와 MatCap 사이 Blend Alpha 0/0.25/0.5/1의 정성적 Appearance 비교.
Current Text Consistency:
네 Label과 양 끝점, 중간 혼합 결과가 현재 본문의 Blend Ratio 설명에 일치한다.
Issue:
수정 필수 사항 없음. 표시 밝기에서 선형 수치를 측정하거나 Intensity와 Alpha를 동일시하지 않는다.
Required Follow-up:
없음. 원본 보존. 정량 재현 시 Camera/Exposure 및 MatCapIntensity를 고정한다.
Final Status:
Keep



## Fig8_58

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.6.7
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
MatCap을 포함한 Master 합성 Graph.
Current Text Consistency:
큰 합성 구조는 일치하나 현재 유효 입력 계약과 차이. Alpha=1로 MatCap만 선택하며 Visibility=1은 수동값.
Issue:
이전 Audit 외 추가 확인: RimWidth=.3/RimSoftness=.5가 Softness≤Width 위반. 하단 Normal 배선이 Texture Node와 겹쳐 MF_Matcap.Normal까지의 경로를 명확하게 추적하기 어렵다. 잘못 연결되었다고 확정하지 않는다. Forward Adapter 지원 조건도 별도 확인 필요.
Required Follow-up:
현재 계약의 정확한 배선과 Parameter로 실제 재촬영. Caption에 기존 시험 상태, 오류 및 MF_Matcap 표기 차이 명시.
Final Status:
Retake Required



## Fig8_59

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.7.1
Previous Audit Status:
Minor Mismatch / Minor Revision
Action:
Minor Revision
Reason:
Module 목록의 + 표기가 Shadow 곱셈과 MatCap Lerp를 Add로 오인하게 하며 번짐/출력 후처리 조건이 누락됨.
Changes:
Base×Visibility+Specular+Rim 및 MatCap Lerp를 명시. Emission은 Lerp 후 Add. 화면은 Post Process 영향을 받으며 구의 번짐은 Bloom 포함 개념 예시로 표시.
Technical Verification:
최종 lerp(A,M,Blend)+Emission 계약과 일치. EmissionMask는 현재 UV에서 얻는 Scalar이며 주변 조명 기여를 자동 보장하지 않음.
Text Verification:
Emission Contribution과 Emissive 출력 Slot의 목적 구분 유지. 합성식과 Caption 시각 검토.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Edit existing conceptual infographic Fig8_59, MINOR targeted technical corrections. Preserve two main blue/red panels, diagram layout, illustrative glowing sphere and bottom summary, Korean style.
Replace left additive module list box with three lines:
"A = BaseLighting × Visibility + Specular + Rim"
"M = MatCapRGB × MatCapIntensity"
"ASF Result = lerp(A, M, MatCapBlend)"
Resize this box and adjacent text slightly for legible equations. Next box below should read "ASF Result (Emission 추가 전)" instead of Final ASF Color. Left meaning box "Unlit의 출력 경로. 이후 Exposure / Tone Mapping / Post Process가 적용될 수 있다." This prevents falsely claiming raw screen output.
Right formula "EmissionMask × EmissionColor × EmissionIntensity" → "Emission Contribution" → "ASF Result에 추가 (MatCap Lerp 이후)" → "Emissive Color Output". The illustrative glowing sphere caption "발광 표현 개념 예시 (번짐은 Bloom 포함)" not actual engine verification. Note small "주변 조명 기여나 Bloom을 자동 보장하지 않는다."
Bottom keep ASF Result + Emission Contribution → Final ASF Color → Emissive Color. Bottom definition of ASF Result should explicitly "Shadow 곱셈과 MatCap Lerp를 포함한 기본 합성 결과". Emission Mask here scalar sample at current UV, add tiny line "EmissionMask: 현재 UV에서 얻은 Scalar 값". Keep all original purpose output slot vs added emission distinction. No fake screenshots.



## Fig8_60

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.7.2
Action:
Keep Screenshot
Evidence Purpose:
동일 EmissionColor에 Intensity 0/1/2/5를 곱한 기본 출력 비교.
Current Text Consistency:
Parameter 수치와 Multiply→Emissive 연결이 맞고, 0의 검정 및 증가에 따른 표시 변화가 본문과 일치.
Issue:
수정 필수 사항 없음. 출력 수치와 표시 색 변화, 자동 Bloom이 아님을 본문에서 구분한다.
Required Follow-up:
없음. 정량 재현에는 표시 모드/Exposure 조건 고정 필요. 현재 원본 유지.
Final Status:
Keep



## Fig8_61

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.7.3
Action:
Keep Screenshot
Evidence Purpose:
EmissionIntensity=5를 유지하고 Bloom Intensity 0/10의 표시 차이 비교.
Current Text Consistency:
두 Graph의 동일 Emission과 Bloom 설정값, 아래 Halo가 본문과 일치. 발광 계산과 Post Process 번짐이 구분된다.
Issue:
수정 필수 사항 없음. 주변 조명 기여나 성능을 증명하는 자료로 사용하지 않는다.
Required Follow-up:
없음. 정량 재현 시 Camera/Exposure 고정. 원본 유지.
Final Status:
Keep



## Fig8_62

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.7.4
Action:
Keep Screenshot + Caption Correction
Evidence Purpose:
Compensation -2/0/+2에서 관찰한 초기 화면 밝기 비교.
Current Text Consistency:
수치와 관찰 결과는 일치하며 현재 본문도 통제된 Exposure 테스트가 아니라고 구분한다.
Issue:
Metering Mode Override가 꺼져 있어 최종 Auto Exposure 설정은 확정할 수 없다.
Required Follow-up:
Caption에서 유효 Metering 및 자동 적응 원인 증거로 확대하지 않도록 제한. 초기 관찰 자료로 원본 유지; 실제 동작 검증을 수행한 것은 아니다.
Final Status:
Keep



## Fig8_63

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.7.4
Action:
Keep Screenshot + Caption Correction
Evidence Purpose:
Manual Metering 및 Compensation -2/0/+2의 어두운 출력 비교.
Current Text Consistency:
Manual Override와 세 값이 보이고 본문의 관찰 목적과 일치한다.
Issue:
본문의 Emission5/Bloom0 및 유효 Physical Camera 기준 Exposure가 이미지에 모두 보이지 않음.
Required Follow-up:
Caption에서 본문 기록 조건과 직접 보이는 설정을 구분. Camera 기준값을 추정하지 않음. 원본의 어두움을 보정하지 않고 유지.
Final Status:
Keep



## Fig8_64

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.7.5
Action:
Keep Screenshot
Evidence Purpose:
Heart Texture의 R Sample을 Emission Mask로 사용한 결과와 Data Texture 설정.
Current Text Consistency:
R×Color×Intensity→Emissive 및 Heart 영역, Masks(no sRGB), sRGB Off가 본문에 일치.
Issue:
수정 필수 사항 없음. Texture 전체와 현재 UV에서 얻는 R Scalar를 혼동하지 않는다.
Required Follow-up:
없음. 원본 유지. Fig8_65는 현재 본문/Audit의 참조 대상이 아니므로 다음은 Fig8_66.
Final Status:
Keep



## Fig8_66

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.7 Integration
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
MF_Emission의 세 입력과 MatCap Lerp 후 Add 통합.
Current Text Consistency:
Emission 연결 자체는 맞다. Alpha1/수동Visibility1의 시험 상태이며 현재 전체 계약을 검증하지 않는다.
Issue:
이전 Audit Keep 이후 현재 계약 기준 추가 확인: 전체 Graph의 RimWidth .3/RimSoftness .5는 Softness≤Width 위반. Auto Exposure 및 Compensation3도 기록 필요.
Required Follow-up:
원본 보존, 유효 Parameter로 전체 Graph 실제 재촬영. Caption에 Emission 연결과 전체 검증 범위를 구분.
Final Status:
Retake Required



## Fig8_67

Type:
Unreal Screenshot / Verification Evidence (Type B protection for source-unverified Character/render composite; surrounding infographic requires revision)
Chapter / Section:
Chapter 08 / 8.8.1
Action:
Caption / Reference Revision; Presentation Revision Required
Evidence Purpose:
Material 분리와 Material 내부 Region Parameter 선택 비교.
Current Text Consistency:
의도는 맞으나 Region Intensity를 MF_Specular 입력으로 보내는 도식은 현재 계약과 다르다.
Issue:
Character/렌더 이미지 출처는 확인되지 않아 실제 Unreal 자료라고 단정하지 않으며 보수적으로 보호. Intensity만 바꾸는 설명에 색상·형상도 달라진 결과가 혼합됨.
Required Follow-up:
원본 Character/렌더 영역을 보존하고 주변 도식을 Scalar Mask 출력×Color×선택된 Intensity로 수정. Caption에서 현재 올바른 식과 비교 범위를 명시했으며 이미지 수정은 Pending 목록에 남김.
Final Status:
Presentation Revision Required



## Fig8_68

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.8 Texture Region
Action:
Keep Screenshot + Caption Correction
Evidence Purpose:
Texture R에 의한 Region Intensity Lerp와 Function 외부 Multiply.
Current Text Consistency:
A=.1/B=1, Texture R→Alpha, 선택 Intensity×SpecularMask→Emissive가 현재 본문에 일치한다.
Issue:
Forward Light Node는 현재 기본 지원을 보장하지 않아 조건부 Adapter임을 Caption 보완.
Required Follow-up:
없음. 현재 비교 설정 Shininess2와 정성적 결과 범위 명시. 원본 유지.
Final Status:
Keep



## Fig8_69

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.9
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
직렬 Module 흐름, Final Color 입력 누락, 잘못된 Figure 번호와 Mode5 EmissionMask가 현재 계약과 불일치.
Changes:
공유 입력의 독립 계산과 B×Vis+S+R, MatCap Lerp 후 E 합성으로 수정. F→Mode0 연결 및 0~5 계약, SM/RM Scalar와 S/R RGB 분리. Mode5는 Emission Result RGB.
Technical Verification:
0F/1D/2SM/3RM/4MatCapRGB/5EmissionRGB 선택과 현재 Architecture 일치. MatCap은 저장 Appearance Lookup, GPU Stage가 아닌 Shader Module. 표시 후처리 한계 명시.
Text Verification:
숫자/이름/수식/한글 및 화살표를 재검토. 초기 출력의 Mask/RGB Tag 혼동을 추가 수정.
Final Status:
Complete
Generation Method:
Built-in image_gen, original reference and one technical refinement.
Prompt Specification:
Major technical revision of existing conceptual infographic. Title "Fig8_69. Final Rendering과 Debug View의 관계". Preserve blue final path/purple debug path palette white background Korean technical educational style. No serial Base→Shadow→Specular→Rim→MatCap→Emission chain. Use three regions.
Top shared inputs bar "공유 입력: World Normal / LightDirection / ViewDirection / Material Parameter / Texture Sample".
Below LEFT region "공유 계산 결과" five independent rows/cards clearly NOT connected in series:
"Base Lighting: D = saturate(N·L), B = BaseColor × D"
"Specular: S = SpecularMask × SpecularColor × SpecularIntensity"
"Rim: R = RimMask × RimColor × RimIntensity"
"MatCap: T = MatCapRGB, M = T × MatCapIntensity"
"Emission: E = EmissionColor × EmissionIntensity × EmissionMask"
Connect shared bar with branch bus to all five cards. Footer of that area "N/L/V: 같은 공간의 Unit Vector / EmissionMask: 현재 UV의 Scalar".
Middle lower blue region "Final Composition": "A = B × Visibility + S + R" → "F = lerp(A, M, MatCapBlend) + E". Note "Visibility: 수동 시험 입력 / Renderer Adapter는 별도". Module tags B,S,R,M,E copied explicitly; don't draw spaghetti crossing arrows, use matching tags and label "위 계산 결과 재사용".
RIGHT purple region "MF_DebugView": table selector with 6 incoming named data rows linked via common bus into selector, including final:
"0 — F (Final Color RGB)"
"1 — D (Base Lighting Data Scalar)"
"2 — SpecularMask (Scalar)"
"3 — RimMask (Scalar)"
"4 — T (MatCap RGB, Intensity 적용 전)"
"5 — E (Emission Result RGB)"
Explicit blue arrow from F final composition to row0, matching tags suffice other rows with note "동일 계산 데이터의 분기 — 별도 재계산 아님".
Below table arrow to "DebugMode로 하나 선택" → "Unlit Emissive Color" → "화면 표시". Note "Exposure / Tone Mapping / Post Process가 표시값에 영향을 줄 수 있음". Bottom comparison two small boxes Material Instance "Look Parameter 조절" vs Debug View "기존 Intermediate Data 진단". Mode5 is Emission RESULT RGB not Mask. No Shadow Debug mode. MatCap storedappearance not actualenvironmentreflection. Rendering Modules notGPUstages. All text legible.
Refinement:
Correct only data routing and tags in this infographic. Preserve formulas and layout. Right table mode2 tag is wrongly S (which left defines colored Specular RGB); change to "SM" and text "SM = SpecularMask (Scalar)". Mode3 tag change R to "RM" and text "RM = RimMask (Scalar)". In left Specular card use formula "S = SM × SpecularColor × SpecularIntensity" with small "SM = SpecularMask". Left Rim use "R = RM × RimColor × RimIntensity" small "RM = RimMask". Remove the purple branch from top shared raw input bar to right MF_DebugView entirely. Raw inputs feed ONLY left computation blue branch. Add a clear purple label directly above right table "분기 입력: F / D / SM / RM / T / E — 왼쪽 계산 결과 재사용". Draw a single blue arrow routed vertically through the gap between panels from blue Final Color F output box lower left, upward to right table mode0 F input; must end at mode0 only, with a visible arrowhead. Existing other debug row data bus can use named tags. Do not add new raw input path to debug. Keep Korean legible, no S/R tag equivalence with Masks.



## Fig8_70

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.9 Selector Structure
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
입력 배선 혼합, EmissionMask/Result 오류, 각 선택값의 출력 경로 누락.
Changes:
6개 독립 행의 Input/Condition/Selected RGB로 재구성. Scalar→float3(s,s,s), RGB 유지, 공통 선택 출력과 제어/데이터 선 구분.
Technical Verification:
현재 If Chain 0~4 검사 후 else EmissionResult에 일치. 유효 정수0~5/기본0, 범위 밖 값과 소수는 지원 Mode 아님. Collector는 Add가 아니라 하나의 값 선택.
Text Verification:
본문의 Interface와 Data Type, 선택 순서 일치. 전체 한글/수식/독립 행 연결 검수.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Major correction of Fig8_70 conceptual selector infographic, white navy purple style Korean English technical terms. Title "Fig8_70. MF_DebugView 선택 구조". Avoid tangled wire chain. Use 6 horizontal rows, 3 columns Input / Selection condition / Selected RGB. This is conceptual not synthetic Unreal UI.
Top purple bar "DebugMode (Scalar): 정수 0~5 사용, 기본값 0" dashed control arrows from this bar to condition column only.
Row0 "FinalResult (Vector3)" → "DebugMode == 0" → "FinalResult RGB".
Row1 "BaseLightingData (Scalar s)" → "DebugMode == 1" → "float3(s,s,s)".
Row2 "SpecularMask (Scalar s)" → "DebugMode == 2" → "float3(s,s,s)".
Row3 "RimMask (Scalar s)" → "DebugMode == 3" → "float3(s,s,s)".
Row4 "MatCapResult (Vector3)" → "DebugMode == 4" → "MatCapResult RGB".
Row5 "EmissionResult (Vector3)" → "else (유효 Mode 5)" → "EmissionResult RGB".
Each independent row input directly connected to its own RGB branch, no input tied to another. All six right RGB branches with arrows to one vertical collector clearly labeled "조건에 맞는 하나의 값만 선택 (Add 아님)" then arrow to "DebugColor (Vector3)".
Bottom two notes "0~4가 아니면 EmissionResult를 반환하는 현재 If Chain이다. 범위 밖 값과 소수는 지원 Mode로 사용하지 않는다." and "Scalar는 Gray RGB로 복제하고 Vector3는 Color를 그대로 유지한다." Final note "기존 계산 결과를 재사용하며 별도 Lighting을 다시 계산하지 않는다." EmissionResult notEmissionMask. FinalResult RGB preserve. Distinguish dashed control vs soliddata legend. Rows aligned large readable no spaghetti. Do not recreate Unreal nodes or actual engine UI.



## Fig8_71

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.9 MF_DebugView
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
실제 DebugMode If Chain 내부 구현.
Current Text Consistency:
중첩 형태는 맞으나 EmissionMask Scalar와 변환 없는 Scalar 입력이 현재 최종 계약과 다름.
Issue:
EmissionResult Vector3 및 명시적 Gray RGB 변환의 증거가 없음. 암시적 변환 결과를 추정하지 않음.
Required Follow-up:
실제 Graph 수정 후 재촬영 Queue 등록. 원본 보존 및 최종 계약 이전 상태임을 Caption 명시.
Final Status:
Retake Required



## Fig8_72

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.9 Mode Comparison / Mode Validation (two references)
Action:
Keep Screenshot
Evidence Purpose:
Material Instance DebugMode 0~5의 실제 결과 비교.
Current Text Consistency:
0 Final RGB, 1 Base Data Gray, 2 Specular Mask, 3 Rim Mask, 4 MatCap RGB, 5 Emission RGB가 해당 설정값과 함께 보인다. 두 참조 위치 모두 적절하다.
Issue:
수정 필수 사항 없음. Fig8_71의 이전 Graph와 달리 Mode5에서 Color 유지가 확인되며 두 그림의 구현 시점 차이는 앞 Caption에 명시.
Required Follow-up:
없음. 화면은 정성적 확인이며 Scalar 수치 측정이 아니다. 원본 유지.
Final Status:
Keep



## Fig8_73

Type:
Unreal Screenshot / Verification Evidence (Type B)
Chapter / Section:
Chapter 08 / 8.10 Final Architecture (two references)
Action:
Retake Screenshot + Caption Correction
Evidence Purpose:
Module 합성과 DebugView의 전체 Master 연결.
Current Text Consistency:
EmissionResult RGB 입력과 Add/Lerp 큰 구조는 일치. 현재 전체 계약의 검증 화면으로는 부족.
Issue:
RimWidth .3/Softness .5 범위 위반. Alpha1/수동Vis1 시험 상태. MatCap Debug는 Intensity 전 RGB 분기를 명확히 확인해야 한다.
Required Follow-up:
양쪽 참조 Caption 보완. 현재 Parameter와 모든 Module 기여, Debug4의 정확한 RGB 분기 및 Adapter 조건으로 실제 재촬영 Queue 등록. 원본 유지.
Final Status:
Retake Required



## Fig8_74

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 08 / 8.10 Final Data Flow (two references)
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
잘못된 ASF 이름, 직렬 Module 처리, Shadow 입출력 혼동, 단순 Add 및 과도한 Lighting 범위를 수정.
Changes:
Anime Shader Framework로 정정. 공유 입력의 분기, 각 MF 입출력 및 외부 Color/Intensity, 현재 UV Mask Sample, 실제 Add→Lerp→Add, Debug0~5 계약을 명시. 복잡한 교차선 대신 일치하는 Data Tag 사용.
Technical Verification:
D/B/Bs/SM/S/RM/R/T/M/E/F의 의미와 타입 확인. Shadow는 B와 수동 Visibility를 입력받아 Bs 출력. MatCap은 저장 Appearance 조회. Emission은 Lerp 이후 Add. Scalar Mask는 Sample 이후 Function 입력.
Text Verification:
두 참조의 Caption 맥락 및 기존 Graph와의 완료 단정을 정정. 생성 과정의 잘못된 교차 화살표/Shadow D 출력/Emission 우회선을 제거하고 최종본 시각 검수.
Final Status:
Complete
Generation Method:
Built-in image_gen, original reference and two routing corrections.
Prompt Specification:
Major technical revision of Fig8_74 infographic. Keep professional white Korean instructional design six numbered conceptual groups blue green purple orange cyan red, but they are categories not six serial GPU stages. Title "Fig8_74. ASF Final Shader Data Flow", brand exactly "Anime Shader Framework". Remove Art Stylized Foliage and leaf slogans entirely. Landscape high resolution, readable.
Group1 Input Data top horizontal shared bar: "World Normal N / LightDirection L / ViewDirection V / BaseColor / Texture Object / Material Parameters". "N/L/V: 같은 공간의 Unit Vector". Branch bus to Core Lighting and Feature Data as parallel siblings, NEVER CoreLighting→FeatureData arrow.
Group2 Core Lighting panel:
"N,L,BaseColor → MF_BaseLighting"
"D = saturate(N·L) (Scalar LightingData)"
"B = BaseColor × D (RGB LightingResult)"
"B + 수동 Visibility → MF_Shadow → Bs = B × Visibility"
Note "Visibility는 입력이다. Renderer Adapter는 별도."
Group3 Feature Data wider panel four independent compact rows:
"N,L,V,Shininess → MF_Specular → SM (Scalar)"
"외부 합성: S = SM × SpecularColor × SpecularIntensity"
"N,V,Width,Softness → MF_RimLight → RM (Scalar)"
"외부 합성: R = RM × RimColor × RimIntensity"
"World Normal + Texture Object → MF_MatCap → T (RGB)"
"외부 합성: M = T × MatCapIntensity"
"Mask Texture → 현재 UV에서 Sample → R 채널 Scalar Mask"
"Color, Intensity, Mask → MF_Emission → E (RGB)"
Do not merge module rows into serialflow.
Group4 FinalComposition precise equations:
"A = Bs + S + R"
"C = lerp(A, M, MatCapBlend)"
"F = C + E"
arrows A→C→F permitted actual dependencies. "MatCap Off: Blend=0" .
Group5 Debug View:
"기존 데이터 재사용"
"0:F RGB / 1:D Scalar / 2:SM Scalar / 3:RM Scalar / 4:T RGB / 5:E RGB"
"DebugMode → MF_DebugView → DebugColor RGB"
"Scalar는 Gray RGB, RGB는 Color 유지"
Connect F from4 and namedtags D,SM,RM,T,E from2/3 to5 via taginlets or independentarrows no rawinput direct5.
Group6FinalOutput:
"DebugColor → Unlit Emissive Color → 화면 표시"
"Exposure / Tone Mapping / Post Process 영향"
Footer "Rendering Module은 기능 책임, Material Function은 구현 단위. 여섯 그룹은 GPU Pipeline Stage가 아니다." "현재 기본 범위의 구조이며 모든 기능이 실제 Engine에서 검증되었다는 뜻은 아니다." All explanatory sentences Korean technicaltermsEnglish. Exact data types/no genericIndirectLighting/no MatCap actual environmentreflection/no emission texture directly scalarwithoutcurrentUVsample. Aim readable panels, use namedmatchingtags to avoid crosswired arrows.
Refinement 1:
This generated figure has WRONG ARROWS. Correct strictly. Keep six numbered groups and formulas. Remove ALL arrows and wires crossing between panels 2,3,4,5,6. Instead use explicit named data inlet tags. ONLY top Input panel1 arrows to panels2 and3 remain. Remove top arrows/tags to4,5,6 entirely. Remove D→Specular wire, Bs→Emission wire, SM/RM→composition wires, T→Lerp wire, F→DebugColor wire; ALL these crossing lines must vanish.
Panel4 top inlet text: "입력: Bs, S, R, M, E (왼쪽 정의 참조)" and preserve A=Bs+S+R → C=lerp(A,M,MatCapBlend) → F=C+E internal vertical arrows.
Panel5 top inlet: "입력: F, D, SM, RM, T, E + DebugMode". Keep table 0F,1D,2SM,3RM,4T,5E. Change table mode1 description "N·L 결과" to "saturate(N·L)". Belowtable do NOT arrow data→DebugMode; instead single box "MF_DebugView / DebugMode로 데이터 하나 선택" → "DebugColor RGB". DebugMode integer0–5 frominputtag, no extra scalarbox.
Panel6 inlet tag "입력: DebugColor (5번 출력)" → "Unlit Emissive Color" → "화면 표시" internal arrows.
Panel3 replace MatCap Korean subtitle "화면 반사 효과" with "저장 Appearance 조회"; same replace in panel4 Mdescription. Add internal arrow from R채널 ScalarMask box DOWN to Color,Intensity,Mask input box before MF_Emission, since actualSamplemaskinput.
Preserve Specular/Rim external composition formulas S=SM*Color*Intensity,R=RM*Color*Intensity and M=T*Intensity; do not send bareSM/RM/T tocomposition.
Bottom clear legend "패널 사이의 연결은 같은 이름의 입력·출력 Tag로 표시한다." This taggedinterface design intentionally omits cross-panel arrows to avoid false wiring. Check every formulaandKoreanlabel. Render largerifnecessary.
Refinement 2:
Two remaining incorrect arrows must be fixed, otherwise keep image. Panel2 MF_Shadow must have ONLY ONE output arrow to "Bs=B×Visibility". REMOVE the small D(Scalar) box immediately right of Bs and remove its arrow from MF_Shadow. D is already defined above as MF_BaseLighting output and listed in bottom outputtags; it must NEVER appear outputofMF_Shadow. 
Panel3 Emission: REMOVE vertical arrow from R채널 ScalarMask box directly to E RGB. Replace Color,Intensity,Mask input text with "Color, Intensity, Mask*". Add tiny label to sample output "Mask*" (Scalar). Only input ColorIntensityMask* → MF_Emission → E remains; no bypass arrow. Matching Mask* tag explicitly supplies input without line.
Replace bottom second sentence "이 도식은 패널 간의 화살표 연결을 생략하여..." with "Rendering Module은 기능 책임, Material Function은 구현 단위이며 GPU Pipeline Stage와 구분한다." Preserve first taglegend sentence. Do not add new arrows anywhere. All formulas must remain unchanged.



## Fig9_01

Type:
Unreal Screenshot / Verification Evidence (Type B protection for source-unverified render composite; surrounding infographic requires revision)
Chapter / Section:
Chapter 09 / Introduction
Action:
Caption / Reference Revision; Presentation Revision Required
Evidence Purpose:
측정 기반 Optimization Workflow 및 품질/성능 비교.
Current Text Consistency:
Workflow 의도는 맞으나 GPU21ms 구간의 CPU 병목 Label과 출처 없는 Before/After 수치가 부적절.
Issue:
Scene/Character 렌더 영역의 출처 미확인으로 실제 Unreal 증거라고 단정하지 않으며 보호. 내부 Fig9_02 번호도 충돌.
Required Follow-up:
렌더 원본을 유지한 주변 도식/수치 Label 수정 또는 개념 자료라는 출처 확인 후 재생성. Caption에서 가상 수치, 병목 판정 및 실제 검증 한계를 정정. Pending 목록에 저장.
Final Status:
Presentation Revision Required



## Fig9_02

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 09 / 9.2
Previous Audit Status:
Major Mismatch / Major Revision
Action:
Major Revision
Reason:
동일 Frame CPU/GPU 동시 시작처럼 보이는 타임라인과 throughput/latency 혼동, ASF 이름 오류.
Changes:
Game/Render/GPU 3개 Lane에 FrameN/N−1/N−2와 동일 Frame 의존 연결 표시. 병목 후보 수치를 가상 예시로 분리, 시간 단순 합산 및 대기/VSync/Cap 예외 명시.
Technical Verification:
FrameN이 Game→Render→GPU 순서로 전달되면서 서로 다른 Frame이 겹치는 단순화 모델 확인. 가상18/7/9는 Game 후보,6/4/20은 GPU 후보이며 실제 Trace를 주장하지 않음.
Text Verification:
현재 Chapter09의 측정/원인 분리/재측정, 동기화 예외와 일치. Anime Shader Framework 이름, 한글 및 표 검수.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Major correct this conceptual CPU/GPU bottleneck infographic. Preserve polished navy pale blue green two-column Korean technical textbook style. Brand exactly "ASF — Anime Shader Framework". Title "Fig9_02. CPU vs GPU Bottleneck". Every timing is "단순화한 설명용 예시 — 실제 Unreal Trace 아님".
Top left panel "서로 다른 Frame의 작업이 겹친다": aligned 3columns interval①②③ and 3 lanes. Game Thread row: Frame N | Frame N+1 | Frame N+2. Render Thread row: Frame N−1 | Frame N | Frame N+1. GPU row: Frame N−2 | Frame N−1 | Frame N. Dependencies for SAME Frame N: arrow from Game FrameN END atcolumn1 right boundary down-right to Render FrameN START column2; then arrow from RenderFrameN END column2 down-right to GPU FrameN START column3. If geometrically awkward use matching colored FrameN labels and text "동일 Frame N의 의존: Game 준비 → Render 명령 → GPU 실행" rather than false same-startarrow. Shared time increasesright. Note "정상 상태 처리 간격(throughput)과 한 Frame의 지연(latency)은 다르다." "실제 Queue, RHI/Task, 동기화 및 대기는 구현에 따라 다르다."
Topright panel "병목 후보 비교 (ms, 가상 값)" use three table rows cases columns Game / Render / GPU / 후보:
"CPU 제한 예 | 18 | 7 | 9 | Game Thread"
"GPU 제한 예 | 6 | 4 | 20 | GPU"
"비슷한 비용 예 | 10 | 9 | 10 | 추가 분석 필요"
No fake exactFPS, no serialGPUoffsetbars, no blanket guaranteedidle.
Bottomleft "해석 조건": "충분히 겹치는 정상 상태에서는 가장 긴 작업 영역이 처리 간격의 주요 후보가 된다." "Thread/GPU 시간은 단순 합산하지 않는다." "대기·동기화·VSync·Frame Cap이 있으면 시간 비교만으로 원인을 확정하지 않는다." "GPU Idle이나 CPU 대기의 원인은 Trace로 확인한다."
Bottomright process numbered "1 동일 조건 측정" → "2 CPU/GPU 병목 후보 분리" → "3 작업과 대기 원인 분석" → "4 한 변수 수정" → "5 같은 조건 재측정". Small tools supplementary "Stat Unit / Stat GPU / GPU Visualizer / Unreal Insights (버전·환경에 맞게 선택)".
Footer "Frame Time을 제한하는 원인을 줄이고 Visual Quality를 함께 확인한다." No specific unrealversionclaims, no realmeasurementsclaim. AllKoreanaccurate.



## Fig9_03

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 09 / 9.3
Previous Audit Status:
Minor Mismatch / Minor Revision
Action:
Minor Revision
Reason:
Rasterization과 최종 Pixel 출력 혼동, Skinning 위치 단정, LOD/수치 예시 및 ASF 이름 보완.
Changes:
기존 3패널 유지. Coverage/Fragment→Pixel Processing, Skinning 구현 차이, 가상 Mesh/LOD 수치와 Screen Size 조건 추가. LOD 밀도 차이 및 Small Triangle의 효율 저하 가능성 표시.
Technical Verification:
Triangle Count만으로 성능 확정하지 않으며 Cache/Pass/Skinning/Screen Size를 함께 측정. 표시 숫자는 그림의 실제 Mesh 통계가 아님.
Text Verification:
현재 Geometry Cost 범위에 일치. Anime Shader Framework 이름과 한글/레이블 검수.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Make MINOR targeted corrections to existing Geometry Cost infographic. Preserve 3top panels and bottom two panels, bust-based conceptual diagrams and bluewhite style. Brand change ASF ArtSystemFramework→"ASF — Anime Shader Framework". Title add Fig9_03.
Left pipeline: VertexProcessing sublabel "Vertex Shader 등 / Skinning 위치는 구현에 따라 다름". PrimitiveTriangleSetup sublabel "Primitive 구성 / Clipping / Culling". Rasterization sublabel replace "화면 Pixel로 변환" with "Coverage / Fragment 생성". Add small arrowbelow to "Pixel Processing → 후속 테스트·출력". Avoid claimingfinalpixelcolorfromRasterization.
Middle densitypanel label clearly "개념 예시 — 숫자는 가상 값, 그림의 실제 Mesh 통계 아님". Keep current illustrativevertextrianglecounts ifspace but caption "예시". Change increasingvertexcostclaimto "Geometry 처리 비용 증가 가능" and footnote "Cache, Pass, Skinning, Screen Size와 함께 측정".
Right LOD panel keepthreebustdistanceexamplesbutchange visible topology so LOD0 substantiallydensewireframe, LOD1medium,LOD2coarse. Add each "Triangle 예시: 20,000 / 5,000 / 1,000" respectively. State "그림은 개념도, 수치는 예시" and "실제 LOD는 Screen Size와 설정 기준으로 선택". Distance alone doesnotalwaysdecide.
Bottom geometrycostfactors: change smalltriangleline "작은 Triangle: Geometry/Raster 효율 및 Quad 효율 저하 가능". Bottom keypoints remain trianglecountalone notperformance, scopeunitverified notenginebench. KoreanexplanationsEnglishtechnicalterms.



## Fig9_04

Type:
Unreal Screenshot / Verification Evidence (Type B protection for source-unverified Character/heatmap composite; surrounding infographic requires revision)
Chapter / Section:
Chapter 09 / 9.4
Action:
Caption / Reference Revision; Presentation Revision Required
Evidence Purpose:
Pixel Cost와 Overdraw 개념 및 비교.
Current Text Consistency:
Coverage/반복 처리 취지는 맞으나 Hair→Cloth→Opaque Face 실행 순서 및 LOD의 Pixel 감소 단정은 부적절.
Issue:
Character/열지도 실제 출처 및 측정 조건 미확인. 1x~8x의 실측 해석과 ASF 잘못된 이름, Rasterization 표현 수정 필요.
Required Follow-up:
이미지 원본 보존, 주변 도식/Label 수정 Pending. Caption에서 합성 순서/Depth/Material Mode/LOD의 관계와 수치 한계를 명시.
Final Status:
Presentation Revision Required



## Fig9_05

Type:
Unreal Screenshot / Verification Evidence (Type B protection for source-unverified material render composite; surrounding infographic requires revision)
Chapter / Section:
Chapter 09 / 9.5
Action:
Caption / Reference Revision; Presentation Revision Required
Evidence Purpose:
Shader 비용 요소 및 동일 Coverage에서 다른 비용 가능성.
Current Text Consistency:
Node 수≠비용 원칙은 맞으나 Lerp를 Branch로 분류하고 비용 요소를 직렬 실행처럼 그림.
Issue:
렌더 외관과 Faster/Slower 단정, 출처 없는 Instruction/Pixel 수치, Custom HLSL 비용 일반화. 비교 렌더 출처 미확인.
Required Follow-up:
렌더 원본 보존 상태의 Label/도식 수정 Pending. Caption에서 Blend/Branch, 컴파일 결과와 GPU timing 및 가상 수치를 구분.
Final Status:
Presentation Revision Required



## Fig9_06

Type:
Documentation Figure / Infographic (Type A)
Chapter / Section:
Chapter 09 / 9.6
Previous Audit Status:
Minor Mismatch / Minor Revision
Action:
Minor Revision
Reason:
Section/Draw 1:1 단정 및 Command 생성/CPU 포함 관계 보완.
Changes:
기존 패널 유지, 단일 Pass 비병합 예시와 전체 Frame Draw 차이 명시. CPU 내부 Command 준비·제출, 일반 CPU-driven 범위 및 GPU-driven/Indirect 예외 추가. Slot 수 단정과 Merge/Instancing 설명 보완.
Technical Verification:
추가 Pass/Batching/Instancing/Culling 조건을 함께 확인하며 Triangle Count≠Draw Count 유지. 실제 성능 개선을 보장하지 않음.
Text Verification:
현재 Draw/State Cost 설명과 일치. Figure 번호/ASF 이름 및 한글 검수.
Final Status:
Complete
Generation Method:
Built-in image_gen, original figure referenced.
Prompt Specification:
Minor technical edits preserving existing Fig9_06 sixpanel infographic structure, conceptual lowpoly mannequins and icons. Top left number change "Fig 9.06"→"Fig9_06"; top right brand "Anime Shader Framework".
Panel2 add clear banner "단일 Pass·일반 비병합 Draw의 설명용 예시". The 100K 1Section→1Draw and10Section→10Draw counts are conditional examples notrealmetrics. Add footnote "전체 Frame Draw 수가 아니다. 추가 Pass, Instancing, Batching, Culling에 따라 달라진다."
Panel1 fix commandpreparation containingCPU relationship: MeshSection+MaterialState arrow to one grouped lightblue box titled "CPU: Render Thread / RHI". INSIDE this box "Draw Command 준비·제출". Then arrowtoGPU. No commandcreatedbeforeCPU sequence. Replace absolutebottomdefinitionwith "일반 CPU-driven 경로에서 Mesh Section·Material State를 바탕으로 Draw Command를 준비하고 GPU에 제출한다."
Panel3 MaterialSlots text "Slot 수만으로 Draw 수를 확정하지 않는다. 실제 Section/Pass와 제출 구조를 확인한다."
Panel4 label "일반 CPU-driven 구조 (단순화)" small and note "GPU-driven / Indirect 경로는 다를 수 있다."
Panel6 preserve tips but "Merge Sections" note "Culling 세분성과 품질 영향을 함께 확인한다." Instancing note "지원 조건과 실제 Batching/Draw 수를 확인한다." No promiseuniversalperformancegain.
Keep matchingtemplateandallothercontentlegibleKorean/Englishtechnicalterms.



## Fig9_07
- Type: Type B protection — Character / Scene 비교 영역 출처 미확인 합성 Figure.
- Chapter / Section: Chapter 09 / 9.7.
- Previous Audit Status: Major Mismatch.
- Action: Caption / Reference Fix; 원본 보존, Presentation Revision 보류.
- Evidence Purpose: LOD / Culling 전후 Geometry 및 Scene 비교.
- Current Text Consistency: LOD와 Culling 역할은 일치하나 Frustum 문장 반전과 LOD 흐림 표현은 불일치.
- Issue: “are rendered” 반전; LOD2/3 blur는 Geometry 감소 증거가 아님; 수치/거리 예시를 실측으로 해석할 위험; 영어 중심 설명.
- Changes: Caption에 Pass별 제외, Shadow/Reflection 예외, Screen Size, 수치 예시 및 원본 출처 미확인 명시.
- Required Follow-up: Character/Scene 출처 확인 후 원본 영역 보존 편집 또는 개념 Figure임이 확인되면 재생성.
- Final Status: Presentation Revision Required.

## Fig9_08
- Type: Type B protection — Tool 화면 / Character Debug View 영역 출처 미확인 합성 Figure.
- Chapter / Section: Chapter 09 / 9.8.
- Previous Audit Status: Major Mismatch.
- Action: Caption / Reference Fix; 원본 보존.
- Evidence Purpose: Timing / GPU / Debug View 도구 비교.
- Current Text Consistency: 본문은 병목 후보와 Version 차이를 구분하나 도식은 측정 화면처럼 재구성되어 있음.
- Issue: Frame gap 해석 누락, 명령 표 미검증, ProfileGPU 출력 형태 단정, Quad Overdraw를 겹침만으로 축약.
- Changes: 예시/실측 구분, 대기와 Frame Cap, Event 중첩, Version/Build 조건 및 메뉴 사용을 Caption에 명시.
- Technical Verification: Epic Stat Commands 및 EViewModeIndex 문서 확인. 대상 Unreal 실행 검증은 수행하지 않음.
- Sources: https://dev.epicgames.com/documentation/unreal-engine/stat-commands-in-unreal-engine ; https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/EViewModeIndex
- Required Follow-up: 원본 화면 출처 확인 후 보존 편집; 실제 캡처라면 대상 Version의 도구/명령/범례 재확인.
- Final Status: Presentation Revision Required.

## Fig9_09
- Type: Type A — Documentation Workflow.
- Chapter / Section: Chapter 09 / 9.9.
- Previous Audit Status: Minor Mismatch.
- Action: Minor Revision; 기존 7개 Card와 하단 원칙/확장 구조 유지.
- Reason: 브랜드 확장 오류, Profiling Tools의 사용 시점과 반복 흐름 불명확.
- Changes: Anime Shader Framework로 정정. 도구를 측정·분석·검증 전체에 적용하는 Band 추가. 7→2 반복 화살표, 병목 후보와 대기/제한 조건 구분.
- Technical Verification: 가장 큰 Timing을 원인 확정으로 표현하지 않음. 실행/대기 구분, 한 변수 수정, 동일 조건 성능·품질 재검증을 도식 확인.
- Text Verification: 현재 9.9의 Baseline / 원인 분석 / 재측정 절차와 일치. 한국어 설명과 English 기술 용어 확인.
- Final Status: Complete.
- Generation Method: Built-in image_gen edit; 생성 결과 시각 검수 후 기존 Fig9_09.png로 저장.
- Generated Source: C:\Users\kmcoo\.codex\generated_images\01a0b72c-d198-7553-a37d-8daac7aeb778\exec-06d0da80-e4b3-4ae3-a3b8-b0fa48977410.png
- Prompt Specification:
Edit target: supplied Fig9_09 documentation infographic. Preserve dark navy cyan technical grid visual style, wide landscape composition, seven card workflow and lower principles/advanced workflow. This is a conceptual diagram, no Unreal UI or measured screenshots. Improve Korean typography. Brand must say ASF | Anime Shader Framework (never Art System Framework or Ari). Main title Optimization Workflow Summary, subtitle ASF Chapter 09, badge Fig9_09.
Seven cards:
1 Measure: 동일 조건에서 Baseline 기록 / Frame Time과 품질 기록
2 Find Candidates: Game · Draw · GPU 비교 / 가장 긴 값은 조사 후보 / 대기 · VSync · Frame Cap 확인
3 Trace Bottleneck: 실행과 대기 구분 / Frame 지연 경로 추적
4 Analyze Cost: Geometry / Pixel · Overdraw / Material · Shader / Draw Submission / LOD · Culling
5 Test Hypothesis: 도구로 원인 가설 검증 / Timing과 시각 지표 함께 비교
6 Optimize: 한 번에 하나의 조건 변경 / 변경 내용 기록
7 Measure Again: 동일 조건 재측정 / 성능과 Visual Quality 검증
Arrows sequential 1→2→3→4→5→6→7. Add clear return arrow from card7 back to card2 labelled 목표 미달 또는 새 병목 → 다시 분석.
A horizontal tools band beneath all cards with text Profiling Tools — 측정·분석·검증 전 과정에서 사용 and stat unit · Unreal Insights · GPU Profiling · Debug Views. Do not imply tools start only after cause analysis. Bottom left Key Principles five lines: 먼저 측정 / 원인 가설 검증 / 한 조건씩 변경 / 품질과 성능 함께 확인 / 여러 Frame의 안정된 결과 비교.
Bottom right Advanced Next Step small flow Test Scene → Baseline → 원인 분석 → 한 변수 수정 → Before / After 검증. Footer: 개념 절차 · 실제 성능 수치나 Engine UI가 아님. Korean explanations English technical terms. No real landscape photographic inserts, use subtle geometric terrain only. Keep layout polished legible no extra invented claims.

# Retake Screenshot Queue

## Fig4_05

Chapter / Section:
Chapter 04 / 4.5 Color Space for Material Data

Reason:
Decode 수치/방향, Roughness 결과 및 Graph가 현재 본문과 불일치.

What must be visible:
0.5 Data Texture의 sRGB Off/On 설정, 실제 Sample 결과, 자동 Decode 뒤 중복 수동 Decode가 없는 Graph, 동일 Geometry/Normal/Light/Exposure 비교. Engine 버전과 Texture format/sampler 설정 기록.

Recommended Unreal View / Tool:
Texture Editor, Material Editor, 고정 Exposure의 비교 Viewport 및 Sample 값 확인용 Debug Material/검증 도구.

Current problem:
0.50→0.73을 Decode로 표기하고 Roughness 방향을 뒤집음. Actual Rendering/Graph의 출처 및 현재 구현 일치 미확인. 원본 이미지 유지; AI 재생성하지 않음.

## Fig8_03
Chapter / Section:
Chapter 08 / 8.0
Reason:
필수 생성/Rendering 설정을 현재 캡처로 검증할 수 없음.
What must be visible:
실제 Engine 버전, Blank/Blueprint/Desktop/Maximum/ASF_Demo, 생성 후 StarterContent 포함과 Ray Tracing 비활성화 설정. 서로 다른 화면이면 개별 실제 캡처를 사용하고 번호를 실제 항목에 대응.
Recommended Unreal View / Tool:
Project Browser, Content Browser, Project Settings 및 Engine 버전 표시.
Current problem:
⑥은 Project Location이며 Starter Content와 무관. UI에 없는 설정을 합성해서 추가하지 말 것. 8.1 오참조는 본문에서 제거 완료.

## Fig8_10
Chapter / Section:
Chapter 08 / 8.4
Reason:
Reflection용 signed Dot와 시각화용 Saturate 및 현재 입력 준비 계약을 분명히 보여야 함.
What must be visible:
World Space의 N/L, 두 Normalize, Saturate 이전 Dot의 Reflection 분기와 별도 표시 경로, Unlit/고정 Exposure 조건.
Recommended Unreal View / Tool:
Material Editor 및 Debug Material Viewport
Current problem:
PixelNormalWS Normalize가 없고 Saturate 뒤 출력만 보임. Lit 결과를 Dot 수치로 오인할 수 있음.

## Fig8_14
Chapter / Section:
Chapter 08 / 8.4
Reason:
정규화된 L과 정규화 전 L을 혼합하는 실제 연결 오류.
What must be visible:
동일 Unit L의 Dot/−L 분기, Unit N, signed Dot, R 계산, 별도의 0.5R+0.5 Debug 경로와 고정 Exposure.
Recommended Unreal View / Tool:
Material Editor / Unlit Debug Viewport
Current problem:
Dot만 Normalize L 사용. −L은 원래 입력 사용. Lit BaseColor 결과는 벡터 수치 증거가 아님.

## Fig8_15
Chapter / Section:
Chapter 08 / 8.4
Reason:
R 계산의 L 분기 오류 및 Lit Scalar 표시 조건.
What must be visible:
동일 Unit L 분기와 Unit N/V, R·V Dot, 원값과 별도 표시 변환, 통제된 Unlit Debug 결과.
Recommended Unreal View / Tool:
Material Editor / Debug Viewport
Current problem:
Dot→BaseColor 연결은 존재함. 과거 Audit의 미연결 설명은 오류이며 실제 문제는 R 입력과 표시 조건.

## Fig8_16
Chapter / Section:
Chapter 08 / 8.4 Exponent 비교
Reason:
Mask 단독 비교와 R 입력 정확성의 확인 필요.
What must be visible:
정정된 R 계산, Saturate→Power(8), 다른 Exponent와 동일 Camera/Exposure/출력 조건.
Recommended Unreal View / Tool:
Material Editor / Unlit Debug Viewport
Current problem:
R 입력부 잘림 및 Lit BaseColor 표시. 실제 후속 Exponent 값과 비교 세트를 맞출 것.

## Fig8_17
Chapter / Section:
Chapter 08 / 8.4
Reason:
동일 조건 Exponent 비교 필요.
What must be visible:
정정된 R, Saturate→Power(32), 8/128과 동일 Camera/Exposure/Unlit 출력.
Recommended Unreal View / Tool:
Material Editor / Debug Viewport
Current problem:
Lit BaseColor와 기존 Specular가 혼합되고 R 입력부가 잘림.

## Fig8_18
Chapter / Section:
Chapter 08 / 8.4
Reason:
Exponent 비교 시 다른 조명 반응 분리.
What must be visible:
정정된 R, Saturate→Power(128), 8/32와 동일 Camera/Exposure/Unlit 출력.
Recommended Unreal View / Tool:
Material Editor / Debug Viewport
Current problem:
좁은 Mask 이외의 Lit 반응이 함께 보임. 실제 R 입력부도 보완 필요.

## Fig8_19
Chapter / Section:
Chapter 08 / 8.4
Reason:
현재 Unlit Color 합성과 다른 Lit Specular Pin 연결 및 R 입력 오류.
What must be visible:
같은 Unit L/N의 R, Unit V, 양수 Shininess, Mask×Color×Intensity, FinalColor 합성 및 Unlit Emissive 출력.
Recommended Unreal View / Tool:
Material Editor / 고정 Exposure Viewport
Current problem:
기존 화면은 엔진 Specular Property 조절이며 Phong으로 엔진 BRDF를 교체한 증거가 아님.

## Fig8_24
Chapter / Section:
Chapter 08 / 8.2
Reason:
현재 MF_BaseLighting Interface의 출력 누락.
What must be visible:
LightDirection/Normal/BaseColor 입력3개, LightingData Scalar D와 LightingResult Vector3 B 출력2개, 입력 타입과 기본값/연결 여부.
Recommended Unreal View / Tool:
Material Function Editor / Function Call
Current problem:
기존 Master 화면은 Shadow가 강조되고 Base의 LightingData 출력이 없음.

## Fig8_25
Chapter / Section:
Chapter 08 / 8.2
Reason:
본문의 Lighting Result 검증과 다른 Scalar 출력 연결.
What must be visible:
MF 두 출력 라벨, Lighting Result→Emissive, BaseColor 입력, Unlit ShadingModel, 고정 Exposure 및 색상 결과.
Recommended Unreal View / Tool:
Material Editor Details + Graph / Viewport
Current problem:
LightingData만 연결되어 색상 적용 결과가 없음.

## Fig8_35
Chapter / Section:
Chapter 08 / 8.3 Debug View
Reason:
Debug Mode와 데이터 의미 식별 불가.
What must be visible:
Engine 버전/Shadow Method, 실제 활성 View 이름 또는 Command, 표시 Buffer의 Depth/Visibility/Mask 구분, 범례/값 범위.
Recommended Unreal View / Tool:
지원되는 실제 Shadow Debug View와 선택 UI
Current problem:
일반 Lit와 유사한 색조 화면만 있고 Mode/범례 없음.

## Fig8_36
Chapter / Section:
Chapter 08 / 8.3 Object Motion
Reason:
선택 대상과 비교 내용이 Sphere 이동 실습을 입증하지 못함.
What must be visible:
동일 Camera/Light, Sphere 위치값 전후, 대응 CastShadow, Engine/ShadowMethod/Mobility/Cache 조건; Debug 사용 시 Mode/범례.
Recommended Unreal View / Tool:
Level Viewport / Actor Transform Details
Current problem:
Light Gizmo만 보이며 Sphere 이동 전후 없음. 파란색 의미 미확인.

## Fig8_39
Chapter / Section:
Chapter 08 / 8.3 Shadow 품질
Reason:
원인 변수와 기준/변경 설정 미확인.
What must be visible:
동일 Geometry/Normal/Material/Camera/Light/Exposure 및 Bias/Filtering, 변경한 해상도 관련 설정값, 동일 관찰 영역.
Recommended Unreal View / Tool:
Level Viewport + 해당 Shadow 설정 Details/Command
Current problem:
라벨 없는 두 Sphere 차이만 있어 Shadow 해상도의 효과로 특정 불가.

## Fig8_48
Chapter / Section:
Chapter 08 / 8.5.6
Reason:
중간 RimPower Interface와 최종 Width/Softness 계약 불일치
What must be visible:
Normal/ViewDirection/RimWidth/RimSoftness 입력, BaseRim=1-saturate(N·V), Min=1-Width 및 Max=Min+Softness의 Smoothstep 내부; 동일 Camera/Exposure/Color/Intensity 조건의 세 값 비교; Width=0 및 Softness=0 별도 정책
Recommended Unreal View / Tool:
Unreal Material Editor / Level Viewport
Current problem:
RimPower=4가 남아 있고 내부 계산을 확인할 수 없음. 원본 유지 및 중간 단계 Caption 추가.

## Fig8_50
Chapter / Section:
Chapter 08 / 8.5 Integration
Reason:
Unlit+Emissive 최종 연결 및 Material 설정이 잘림
What must be visible:
세 단계 Intensity 값, MF별 Mask와 외부 Color/Intensity, Add의 최종 Emissive 연결, Unlit 설정, 고정 Camera/Exposure; Scene Shadow와 MF_Shadow 구분
Recommended Unreal View / Tool:
Unreal Material Editor / Viewport
Current problem:
중간 Add 및 결과만 보이고 Material 최종 출력이 화면 밖

## Fig8_54
Chapter / Section:
Chapter 08 / 8.6.5
Reason:
Camera 비교에 Lit/Unlit View Mode 차이가 섞임
What must be visible:
동일 View Mode와 Exposure/Post Process를 적용한 두 Camera, World→View Graph, Raw RGB 음수 표시 한계 범례; 필요시 0.5N+0.5 Debug를 별도 구분
Recommended Unreal View / Tool:
Unreal Material Editor / Viewports
Current problem:
Perspective Lit 및 CineCamera Unlit로 바닥/반사 등 조건이 다름

## Fig8_55
Chapter / Section:
Chapter 08 / 8.6.5
Reason:
원본 Texture와 Lookup 방향 일치 증거 누락
What must be visible:
원본 MatCap Texture 및 상하/좌우 방향, World→View 전체 Graph와 V Flip, 동일 표시 조건 두 Camera 결과
Recommended Unreal View / Tool:
Unreal Texture Editor / Material Editor / Viewports
Current problem:
원본 Texture Preview가 검고 Transform 이전이 잘려 방향 일치 직접 비교 불가

## Fig8_58
Chapter / Section:
Chapter 08 / 8.6.7
Reason:
겹친 배선으로 Normal 입력 경로 확인이 어렵고 Rim Width/Softness가 현재 범위를 위반함
What must be visible:
World Unit Normal→MF_MatCap.Normal, Texture Object→Texture 입력, 0<Softness≤Width≤1, 수동 Visibility 범위, 검증된 LightDirection, Blend Parameter 0/1과 Emissive 전체 연결
Recommended Unreal View / Tool:
Unreal Material Editor
Current problem:
Normal 선이 Texture Node와 겹쳐 MF Normal 입력 경로가 불명확함(오연결 확정 아님). Rim .3/.5 범위 위반. Alpha1 및 수동Vis1 테스트 상태

## Fig8_66
Chapter / Section:
Chapter 08 / 8.7 Integration
Reason:
전체 Graph에 현 Rim 유효 범위 위반이 남음
What must be visible:
현재 유효 RimWidth/Softness, 명확한 Normal 배선, Emission의 Scalar Mask와 Lerp 후 Add, Alpha/수동 Visibility 및 실제 표시 조건
Recommended Unreal View / Tool:
Unreal Material Editor / Viewport
Current problem:
Emission 연결은 맞으나 전체 Master의 Rim .3/.5가 현재 계약과 다름; Alpha1이 해당 경로를 가림

## Fig8_71
Chapter / Section:
Chapter 08 / 8.9 MF_DebugView
Reason:
현재 RGB 입력/출력 계약 이전 Graph
What must be visible:
EmissionResult Vector3 입력, BaseLightingData/SpecularMask/RimMask의 명시적 Gray RGB 변환, If0~4 및 fallback, DebugColor Vector3, 컬러 입력 보존 테스트
Recommended Unreal View / Tool:
Unreal Material Function Editor
Current problem:
EmissionMask Scalar 및 변환 없는 Scalar 직접 If 연결

## Fig8_73
Chapter / Section:
Chapter 08 / 8.10 (two references)
Reason:
최종 Graph의 현재 Parameter/Debug 분기 계약 확인 필요
What must be visible:
유효 RimWidth/Softness, MatCap Intensity 적용 전 RGB→DebugMode4, 모든 기여가 남는 Blend, 수동 Visibility 명시, 최종 RGB Emission 및 Debug Selector, 명확한 World Normal 배선
Recommended Unreal View / Tool:
Unreal Master Material Editor
Current problem:
Rim .3/.5 범위 위반, Alpha1이 기존 Lighting 기여 제거, MatCap Debug의 원본 RGB 분기 불명확, 수동Vis1

# Pending Protected Figure Actions

- Chapter 09 Fig9_08: Tool/Debug View 원본 출처 확인 및 보존; 예시 표시, 명령 표, Frame gap과 Quad Overdraw 설명 정정 필요. Caption 정정 완료.

- Chapter 09 Fig9_07: Character/Scene 영역 출처 확인 및 보존; Frustum 문장 반전, LOD 흐림 표현, 예시/언어 표시 정정 필요. Caption 정정 완료.

- Chapter 09 Fig9_05: Shader Ball/Character 비교 렌더 영역 출처 미확인. 해당 영역 보존 후 비용 요소의 직렬 화살표, Lerp Branching 분류, Faster/Slower 단정 및 가상 수치 Label을 수정해야 함. Caption 보완 완료.

- Chapter 09 Fig9_04: Character/열지도 출처 미확인 영역 보존. Overdraw 합성 순서, LOD→Pixel 감소 단정, ASF 명칭, 수치 범례를 수정해야 함. Opaque/Masked/Translucent와 Coverage/실행 구분 Caption 보완 완료.

- Chapter 09 Fig9_01: Scene/Character Before/After 영역 출처 미확인. 해당 원본 보존 상태에서 잘못된 CPU 병목 Label, 내부 Fig9_02 번호, 실측처럼 보이는 예시 수치/성과 문구를 수정해야 함. 수치/증거 한계 Caption 보완 완료.

- Chapter 08의 현재 참조 Figure 순차 검토 완료. 실제 재촬영 Queue 및 Fig8_04/32/67 원본 보존 Presentation 조치가 남아 Completed Chapters에는 추가하지 않음. Chapter 09까지 순차 검토 완료.

- Chapter 08 Fig8_67: Character/렌더 영역의 출처 미확인으로 원본 보존. 주변 Data Flow를 MF_Specular.SpecularMask × SpecularColor × 외부 Lerp(IntensityA, IntensityB, RegionMask)로 수정하고 비교 범위를 ASF 예시로 한정해야 함. 색상/형상 차이를 Intensity 단독 효과로 주장하지 않도록 Caption 보완 완료.

- Chapter 08 Fig8_32: Rendering 비교 영역 출처 확인 및 원본 보존 설명 수정. Peter Panning 비교는 동일 접지 Geometry인지 검증 필요. Caption 정정 완료.

- Chapter 08 Fig8_04: UI 원본 보존 후 외부 표의 기본값 단정을 목표 값으로 정정. Caption 및 8.1 오참조 수정 완료.

- Chapter 07 전체 9개 검토 완료. Fig7_07/08의 원본 보존 부분 수정이 남아 Completed Chapters에 추가하지 않음.

- Chapter 07 Fig7_08: Character OFF/ON 원본 영역 보존 및 Technique Family Grouping/Label 정정 필요; Caption 보완 완료.

- Chapter 07 Fig7_07: Character 결과 영역 출처와 통제 조건 미확인. 원본 영역 보존 Label 정정 필요; Caption 보완 완료.

- Chapter 06 전체 10개 검토 완료. Fig6_05의 IBL 적용 결과 영역 보존 부분 편집이 남아 Completed Chapters에 추가하지 않음. Caption 정정 완료, 이미지 원본 유지.

- Chapter 04 검토 완료, 미해결 후속 조치: Fig4_04 원본 자료 보존 부분 편집 / Fig4_05 실제 Unreal 재촬영.
- Chapter 04는 위 후속 조치가 남아 Completed Chapters에 추가하지 않음. 후속 Chapter 05~09의 순차 검토도 완료함.

# Figure Revision Progress

Completed Chapters:
- Chapter 01
- Chapter 02
- Chapter 03
- Chapter 05

Current Chapter:
- None — Chapter 01~09 sequential review finished

Last Processed Figure:
- Fig9_09

Next Figure:
- None — sequential review finished; protected presentation actions remain

Retake Screenshot Count:
- 22 (processed figures only)

Status:
Sequential Review Complete — Awaiting Protected Presentation Revision / Actual Screenshot Retakes

Verification:
- Referenced unique Figures: 154
- Main Figure entries: 154; duplicate entries: 0
- Missing referenced image paths: 0
- Referenced Figures without a log entry: 0
- Actual Screenshot Retake Queue: 22
- Protected Presentation Actions: 12 (Fig4_04, Fig6_05, Fig7_07, Fig7_08, Fig8_04, Fig8_32, Fig8_67, Fig9_01, Fig9_04, Fig9_05, Fig9_07, Fig9_08)
- Full revision is not marked Complete: actual captures and source-preserving presentation edits remain.
- Source clarification requested for composite Character / Scene / Debug View areas. No reply recorded; no source or permission inferred.
- Final sequential save: Fig9_09. Continue from the pending action lists after source verification / actual captures, not by restarting Chapter 01.
- Validation date: 2026-09-21.
