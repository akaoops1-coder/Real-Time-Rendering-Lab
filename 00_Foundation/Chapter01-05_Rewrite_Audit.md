# Chapter 01–05 Teaching Style Rewrite Audit

Date: 2026-10-04

## Scope and Source Authority

Chapter 01–05의 현재 검수본을 Full Teaching Style Rewrite했다. 기준은 `Real-Time-Rendering-Lab`의 현재 main(`686c506645e5c4837aab7c26e046a27e31b43d55`)과 동일한 ASF_Review 원고다. Drive의 현재 Chapter05는 초기 Reference와 동일하여 이후 정확성 보정을 포함하지 않았으므로, 기술적 기준으로 사용하지 않았다. Drive에서 제공된 [Chapter05 Reference](./Chapter05_Reflection_BRDF_ref.md)는 설명 속도·질문·직관·연결 방식의 비교 자료로만 사용했다.

Rewrite를 시작하기 전 같은 경로의 `_backup.md` 다섯 개를 만들었다. 모두 당시 원고의 byte 단위 완전한 사본이며 이후 변경하지 않았다. `_ref.md` 역시 제공된 Reference와 byte 단위로 동일하다. 현재 파일명과 주요 Section 번호를 유지하며 `_v02` 파일을 만들지 않았다.

Chapter 06–09는 Index와 Chapter08.0–8.10을 포함한 15개 원고 전체를 Audit Only로 검토했다. 그 원고와 PNG는 수정하지 않았다. 후속 수정의 범위와 근거는 [Chapter06–09 Style Audit](./Chapter06-09_Style_Audit.md)에 기록했다.

## Teaching Progression and Verification

01은 입력·처리·출력의 연결, 02는 기준의 필요와 Transform, 03은 방향 관계의 계산, 04는 저장된 Data의 해석과 Material 입력, 05는 Surface 응답과 물리량으로 이어진다. 익숙한 문제와 직관 뒤에 용어·관계·Formula를 배치하고, 이미 배운 개념은 짧게 회고했다. 주요 Concept의 끝에만 Key Takeaways를 사용했다. 긴 규약과 수치 확장은 Notes에 보존하고 결과를 바꾸는 핵심 조건은 계산 가까이 남겼다.

보존 대조: 기존 fenced Formula·Code·Data Flow **832개**의 내용과 개수, 주요 Section 순서, 원래 기술 표, 이미지 태그 **57개**와 순서, 연결된 PNG **161개**를 확인했다. 기존 inline 기술 표현도 유지했다. Chapter01의 표시용 한국어 `보간` 표시는 English Technical Term `Interpolation`으로 정리했으며 계산식 변경은 아니다. 새 상대 링크 목적지는 없고 원래 상대 링크 62개는 유효하다.

이 보고서의 L 번호는 1-based Markdown source line이다. 원본 위치는 해당 `_backup.md`, 재작성 위치는 최종 현재 파일을 기준으로 한다. 제목·목록·Figure Caption·Code에서 먼저 보이는 이름도 첫 등장에 포함한다. 첫 등장과 정밀한 정식 설명은 다를 수 있으며, 그 차이를 무조건 정의 누락으로 판정하지 않았다. 마지막 표에서 원본의 기존 설명이 충분했던 경우도 명시했다.

---

## Chapter 01 — Rendering Pipeline

Current: [Chapter01_RnderingPipeline.md](./Chapter01_RnderingPipeline.md) · Backup: [Chapter01_RnderingPipeline_backup.md](./Chapter01_RnderingPipeline_backup.md)

### Major Changes

- 1.1–1.13 전체를 읽고 Stage마다 문제·필요한 Data·처리·출력·다음 입력의 관계를 다시 연결했다. 전체 변경은 [원본 Backup](./Chapter01_RnderingPipeline_backup.md)과 [현재 원고](./Chapter01_RnderingPipeline.md)를 대조할 수 있다.
- 초기 개요의 미정의 Stage 명칭 나열을 Model의 형태가 평평한 Image로 이어지는 문제로 바꿨다. 1.1에서 기초 Data와 Program의 의미를 소개하고, 1.2에서는 Stage 설명 뒤에 전체 명칭 흐름을 배치했다.
- 1.3–1.8은 Position과 Surface 입력의 차이, 기준 변경, 연결, 범위 판정, 화면 후보, 내부 Attribute라는 사고 단계를 강조했다. 1.9–1.13은 계산 결과와 최종 Pixel, 저장과 표시, 준비와 실행의 역할을 구분했다.

### Added Explanation

| Section | Added teaching step |
|---|---|
| 1.1 | 같은 형태가 다른 Material·관찰 조건에서 달라지는 문제; Scene/Pixel, GPU/CPU, Vertex 속성, Texture/UV와 Camera 설정의 목적 |
| 1.2 | 점 처리→연결→유효 범위→화면 위치→속성→Surface 결과→앞뒤→저장→표시를 각 입력/출력으로 설명; 이름 개요와 Figure를 뒤로 이동 |
| 1.3 | Cube의 같은 Corner가 서로 다른 UV/Normal을 필요로 하는 문제; Normal·UV·Mask·Skinning·Seam과 Hard Edge의 즉시 의미 |
| 1.4 | 같은 Mesh를 다른 곳에 둘 때 저장 Position만으로 화면 위치를 결정할 수 없는 이유; Space, Clip 출력, Matrix·Homogeneous preview |
| 1.5 | 점 목록만으로 면의 연결을 알 수 없는 이유; Index의 재사용 목적; Primitive kind와 Winding의 역할 |
| 1.6 | 닫힌 Mesh와 화면 밖 Object의 작업량; 면 방향·공간 범위·가림이 다른 판정인 이유; View 범위는 본문에서 유지 |
| 1.7 | 꼭짓점 세 개만으로 화면 내부를 처리할 수 없는 문제; Sample/Coverage/Fragment와 Color 결정의 차이; screen mapping의 각 역할 |
| 1.8 | 중앙에 저장 Vertex가 없는데 UV가 필요한 문제; 세 입력의 기여 비율→계산값→Sampling; Normalize가 필요한 방향·길이 구분 |
| 1.9 | 같은 형태·위치라도 Surface 결과가 달라지는 이유; 입력 읽기·Material 계산·Pass 출력의 차이; BRDF full name과 목적 preview |
| 1.10 | Depth 값→저장값과 비교→후속 저장; Opaque/LESS 조건을 계산 가까이 유지; Camera와 Light가 다른 관찰 관계인 예 |
| 1.11 | 결과를 기억해야 다음 비교와 Image 처리가 가능한 이유; Color와 Depth 저장, buffering 역할과 표시 조건 구분 |
| 1.12 | 같은 Mesh의 배치·설정을 GPU가 알아야 하는 문제; 생성·업로드·바인딩·제출과 Shader 실행의 차이; Slot/Section/Bottleneck 의미 |
| 1.13 | 최초 질문으로 돌아가 CPU 준비·GPU 계산·저장·표시를 통합; 비용도 서로 다른 Data 단위와 연결 |

### First-Use Terminology Improvements

Vertex/Vertex Attribute, Triangle/Primitive, Stage와 저장 대상을 필요한 문제 안에서 단계적으로 풀었다. GPU/CPU/API/RGB/MSAA/FPS/LOD/BRDF는 Full Name과 역할을 함께 안내했다. Parameter는 1.9 Figure보다 먼저, LOD는 1.12의 첫 예고에서 의미를 제공했다. Texture 이름이 뜻보다 앞서 나오던 짧은 문장을 정리하고, Figure 1-2는 Stage 설명 뒤에서 전체 흐름을 회고하도록 배치했다. 원래 간단히 의미를 설명하던 용어는 그 설명을 살리고 다음 Data 관계를 보강했다.

### Technical Content Preserved

- 182개 fenced block의 문자 내용과 등장 개수를 모두 보존했다. 동일한 내용을 가진 반복 block도 개수를 줄이지 않았다.
- 모든 13개 `<img>` 태그의 원문·순서와 Figure path/number, 1.1–1.13 major section 번호·순서를 보존했다.
- Geometry/Material/Light/Camera, Position/Normal/UV/Tangent/Vertex Color, UV seam·Hard Edge의 수치 사례, Geometric Normal/Shading Normal, Indexed/Non-indexed Draw, Winding/Normal 판정 차이, View/Pass별 선별 범위, Sample/Fragment/Pixel 구분을 유지했다.
- Perspective before Clip / Divide / Viewport 순서, Barycentric vs inverse-distance 구분, Perspective-Correct Interpolation, Normalize 필요, Fragment Output vs Final Pixel, Camera vs Light Visibility, Depth Test vs Write와 LESS/Reversed-Z 조건, 기본 Raster Depth vs Shader Override, 개별 Render Target vs Framebuffer 연결 구조를 유지했다.
- Double Buffering의 표시 보장 제한, CPU/GPU overlap, 생성·업로드·바인딩·제출 구분, Material Section·Pass·Instancing에 따른 Draw 수와 비용의 측정 범위를 유지했다.

### Technical Detail Moved to Notes

| Detail | Location and treatment |
|---|---|
| API/Hardware별 추가 Stage와 실제 실행 순서 | 1.2 Implementation Note; 기본 Data 관계 설명 후 |
| Front-face CW/CCW convention | 1.5 Technical Note; Winding의 역할을 설명한 뒤 |
| Winding vs Vertex Normal 판정과 DCC 표시 관례 | 1.6 Technical Note; 판정 기준 차이는 본문에서도 앞서 설명 |
| Two-Sided Engine 설정과 비용 | 1.6 Implementation Note; 조건을 삭제하지 않고 별도 읽기 영역에 보존 |
| Frustum selection의 CPU/GPU 위치와 Shadow/Reflection Pass 범위 | 1.6 Implementation Note; 해당 View라는 핵심 조건은 본문에 바로 남김 |
| Projection/Divide/Viewport 순서와 뒤 Chapter의 convention detail | 1.7 Technical Note; 각 단계 목적은 본문에서 먼저 설명 |
| Pixel마다 Sample이 하나로 고정되지 않는 MSAA 조건 | 1.7 Technical Note; Sample 뜻과 Anti-Aliasing 목적 뒤 |
| Figure 1-10의 Opaque/LESS/Write 조건과 alternate depth convention | 1.10 Verification/Technical Note; 숫자 예시 직전 기본 LESS 조건 유지 |
| Figure 1-11의 Raster Depth/Shader Override와 독립 Scene 예시 범위 | 1.11 Verification Note |
| Double Buffering vs tearing/Present/synchronization 제한 | 1.11 Implementation Note; buffering 목적 뒤 |
| Figure 1-12의 생성·업로드·바인딩·제출과 반복 업로드 오해 | 1.12 Implementation Note; 기본 준비/지시 연결 후 |
| Batching/Instancing/GPU-driven/Multi Draw의 구현 범위 | 1.12 Implementation Note; 단어의 역할을 함께 설명 |
| Figure 1-13의 Object/Bounds 선별과 Output Bindings 상세 | 1.13 Verification Note; 전체 Data 이동을 먼저 읽게 함 |
| 기존 Early-Z·small triangle·Interpolator cost·CPU/GPU overlap notes | 기존 note와 고유 fenced block 전부 유지 |

### Formula Changes

- Algebraic formula 또는 기존 수치값을 변경하지 않았다. 모든 fenced example/data-flow 내용은 동일하다.
- Chapter01은 완전한 수학 증명보다 수치 입력과 처리 관계 예시가 주를 이룬다. 모든 182개 block을 아래 목록에서 Essential / Explain First / Move to Technical Note로 분류했다.
- 해상도 `1920 × 1080 = 2,073,600 Pixels`는 Essential이다. Pixel 의미를 먼저 설명한다. Position·Normal·UV·Color tuple, Index 번호, 60 FPS와 Vertex/Draw 수 예시는 원문 수치와 범위를 유지한다.
- Local→World→View→Clip 관계, 세 꼭짓점의 Weight와 UV, Depth 0.4/0.2/0.7 비교는 Explain First다. 기준·기여 비율·저장값 비교의 목적을 먼저 이해시킨다.
- `0.2 < 0.4`를 보편적 Depth 규약으로 외우지 말라는 관계는 Move to Technical Note다. Opaque/LESS 예시와 구분하는 alternate convention note에 보존했다.

### Structure Changes

- 파일명, H1, 1.1–1.13 major heading과 기존 하위 주제 순서를 유지한다. Figure 1-2 설명 묶음은 각 Stage의 의미를 배운 뒤로 옮겨 그림의 용어가 본문보다 먼저 학습되던 문제를 줄였다.
- 기존 named Stage overview를 삭제하지 않고 1.2의 Stage 정의 후에 배치했다. 1.3 이후 모든 fenced 사례/flow는 유지한다.
- Callback이라는 고정 제목을 일괄 생성하지 않았다. 이전 결과를 회고하고 다음 문제로 연결하는 역할을 각 절의 자연스러운 본문에 복원했다. 기존 필요한 Key Takeaways와 Chapter Summary를 유지한다.
- `---`으로 Section과 Concept의 시각적 호흡을 유지했고, 긴 관례·실행·검증 조건에는 명시적인 note를 사용한다.

### Figure Review

- Figure 1-1–1-13의 자산은 생성·편집하지 않았다. 모든 태그와 경로·번호·순서가 원본과 동일하다.
- Figure 1-2는 Stage를 설명한 뒤 읽는다. Figure 1-10은 Opaque/LESS/Write 범위, Figure 1-11은 Raster Depth/optional Shader Override 범위, Figure 1-12는 자원 재사용/바인딩/제출 구분, Figure 1-13은 교육용 Group 및 View/Output Scope를 유지한다.
- 실제 GPU/Unreal 실행 검증을 수행했다고 주장하지 않는다. 기존 Concept Illustration 및 대상 환경 확인 범위는 그대로 보존한다.

### Remaining Review Items

- Chapter02–05는 이 Chapter가 먼저 소개한 Vector/Normal/UV/Texture/Space/BRDF 등의 단어를 짧게 회고하고, 각 Chapter의 정밀한 수학·물리량 의미를 확장하는지 대조했다. 이 Chapter의 preview 설명은 뒤 Chapter의 정의·조건을 대체하지 않는다.
- CPU-driven은 기본 학습 흐름이다. GPU-driven 구현, API별 Shader 호출 수, Early-Z 가능 조건, Present 동기화는 기존 문서의 제한처럼 대상 환경 확인이 필요하다. 새 실행 검증은 이번 범위에 포함되지 않는다.
- UV는 좌표축 이름이다. 발명된 English full name을 붙이지 않았다. 새로 쓴 CPU/GPU/API/RGB/RGBA/FPS/DCC/MSAA/LOD/BRDF full names는 역할 설명과 함께 사용했다.
- HTML details와 Markdown의 balance를 확인했다. Formula block·기술 표·수치 예시는 삭제하거나 축약하지 않았다.

### Block Classification Inventory

<details>

<summary>Original 182 blocks: formula, example and data flow classification</summary>



각 ID는 원본 등장 순서이며, 같은 내용의 반복도 별도 항목이다. 위치 이동은 허용하되 내용과 개수는 보존했다.

| ID | Original section / heading / line | Kind / preview | Classification |
|---|---|---|---|
| CH01-B001 | 1.3 / Vertex as a Data Unit / 883 | Vertex A / Position     = (1.0, 2.0, 0.5) | Essential |
| CH01-B002 | 1.3 / Position / 941 | Position = (1.0, 2.0, 0.5) / ~~~ | Essential |
| CH01-B003 | 1.3 / Position / 955 | Local Space / → World Space / → View Space | Explain First |
| CH01-B004 | 1.3 / Normal / 985 | Normal = (0.0, 0.0, 1.0) / ~~~ | Essential |
| CH01-B005 | 1.3 / UV / 1015 | UV = (0.25, 0.75) / ~~~ | Essential |
| CH01-B006 | 1.3 / UV / 1027 | Vertex UV / → Interpolation / → Fragment UV | Essential |
| CH01-B007 | 1.3 / Vertex Color / 1078 | Vertex Color = (1.0, 0.0, 0.0, 1.0) / ~~~ | Essential |
| CH01-B008 | 1.3 / Shared Position and Split Vertices / 1154 | Position = (1, 1, 1) / ~~~ | Essential |
| CH01-B009 | 1.3 / Shared Position and Split Vertices / 1164 | Vertex A / Position = (1, 1, 1) | Essential |
| CH01-B010 | 1.3 / Shared Position and Split Vertices / 1171 | Vertex B / Position = (1, 1, 1) | Essential |
| CH01-B011 | 1.3 / Shared Position and Split Vertices / 1200 | Normal = (1, 0, 0) / ~~~ | Essential |
| CH01-B012 | 1.3 / Shared Position and Split Vertices / 1206 | Normal = (0, 1, 0) / ~~~ | Essential |
| CH01-B013 | 1.3 / Vertex Data in the Rendering Pipeline / 1261 | Vertex / ├─ Position | Essential |
| CH01-B014 | 1.4 / Vertex Shader / 1342 | Vertex Input / → Vertex Shader / → Vertex Output | Essential |
| CH01-B015 | 1.4 / Position Processing / 1364 | Position = (10, 25, 5) / ~~~ | Essential |
| CH01-B016 | 1.4 / Position Processing / 1383 | Local Space / → World Space / → View Space | Explain First |
| CH01-B017 | 1.4 / World Space / 1422 | 같은 Mesh / + 서로 다른 Transform / → 서로 다른 World Position | Essential |
| CH01-B018 | 1.4 / Clip Space / 1462 | Local / → World / → View | Essential |
| CH01-B019 | 1.4 / UV Processing / 1550 | UV = (0.25, 0.75) / ~~~ | Essential |
| CH01-B020 | 1.4 / Vertex Color Processing / 1579 | Vertex Color / → Vertex Shader / → Interpolation | Essential |
| CH01-B021 | 1.4 / Vertex Shader Output / 1605 | Vertex Output / Position | Essential |
| CH01-B022 | 1.4 / Per-Vertex Processing / 1627 | Vertex A / Vertex B / Vertex C | Essential |
| CH01-B023 | 1.4 / Per-Vertex Processing / 1637 | Vertex A → Vertex Shader → Output A / Vertex B → Vertex Shader → Output B | Essential |
| CH01-B024 | 1.4 / Vertex Processing Before Pixels / 1667 | Vertex 단위의 Geometry 처리 / ~~~ | Essential |
| CH01-B025 | 1.4 / Vertex Processing Before Pixels / 1673 | Rasterization 이후 Screen 위치 단위의 Surface 처리 / ~~~ | Essential |
| CH01-B026 | 1.4 / Preparing Geometry / 1691 | Position / Normal / UV | Essential |
| CH01-B027 | 1.4 / Preparing Geometry / 1704 | Position Transformation / Attribute Transformation / Attribute Modification | Essential |
| CH01-B028 | 1.4 / Preparing Geometry / 1717 | Vertex Input / → Vertex Shader / → Processed Vertex | Essential |
| CH01-B029 | 1.5 / Why Triangles? / 1812 | Quad / → Triangle A / + Triangle B | Essential |
| CH01-B030 | 1.5 / Vertex Connectivity / 1836 | Vertex 0 / Vertex 1 / Vertex 2 | Essential |
| CH01-B031 | 1.5 / Vertex Connectivity / 1847 | Triangle A = Vertex 0, 1, 2 / Triangle B = Vertex 0, 2, 3 / ~~~ | Essential |
| CH01-B032 | 1.5 / Index / 1870 | Vertex Buffer / Index 0 → Vertex A | Essential |
| CH01-B033 | 1.5 / Index / 1881 | Triangle 0 / [0, 1, 2] | Essential |
| CH01-B034 | 1.5 / Index Buffer / 1901 | Index Buffer / Triangle 0 → [0, 1, 2] | Essential |
| CH01-B035 | 1.5 / Index Buffer / 1910 | Triangle 0 / Vertex 0 / Vertex 1 | Essential |
| CH01-B036 | 1.5 / Shared Vertex / 1934 | 0 ----- 1 / \| \     \| / \|   \   \| | Essential |
| CH01-B037 | 1.5 / Shared Vertex / 1944 | Triangle A = [0, 1, 2] / Triangle B = [0, 2, 3] | Essential |
| CH01-B038 | 1.5 / Primitive Assembly / 1988 | Vertex 0 / Vertex 1 / Vertex 2 | Essential |
| CH01-B039 | 1.5 / Primitive Assembly / 1998 | [0, 1, 2] / [0, 2, 3] / ... | Essential |
| CH01-B040 | 1.5 / Primitive Assembly / 2010 | Vertex Data / + / Index Data | Essential |
| CH01-B041 | 1.5 / Winding Order and Backface Culling / 2067 | Primitive Assembly / ↓ / Triangle 생성 | Essential |
| CH01-B042 | 1.5 / Primitive Assembly Before Pixel Processing / 2110 | Vertex Data / ↓ / Vertex Processing | Essential |
| CH01-B043 | 1.6 / Backface Culling / 2239 | Triangle / ↓ / Front / Back Face 판정 | Essential |
| CH01-B044 | 1.6 / Object Bounds and Frustum Culling / 2385 | Object Bounding Volume / ↓ / View Frustum과 비교 | Essential |
| CH01-B045 | 1.6 / Clipping / 2430 | Triangle 전체 유지 / → Frustum 밖의 영역까지 처리됨 | Essential |
| CH01-B046 | 1.6 / Clip Plane / 2465 | Primitive가 완전히 안쪽 / → 유지 | Essential |
| CH01-B047 | 1.6 / Geometry After Clipping / 2488 | Vertex A / Vertex B / Vertex C | Essential |
| CH01-B048 | 1.6 / Rejection Before Rasterization / 2537 | Geometry Stage에서 제거 / → Rasterization 자체를 하지 않음 / ~~~ | Essential |
| CH01-B049 | 1.6 / View Frustum and Clip Space / 2590 | Local Space / → World Space / → View Space | Explain First |
| CH01-B050 | 1.6 / View Frustum and Clip Space / 2613 | Vertex Data / ↓ / Vertex Processing | Essential |
| CH01-B051 | 1.7 /  / 2675 | Screen-Space Triangle / ↓ / Rasterization | Essential |
| CH01-B052 | 1.7 / Rasterization / 2707 | Triangle / ↓ / Screen 위에 배치 | Essential |
| CH01-B053 | 1.7 / Screen-Space Triangle / 2731 | Local Space / → World Space / → View Space | Explain First |
| CH01-B054 | 1.7 / Screen-Space Triangle / 2746 | 3D Triangle / ↓ / Camera / Projection | Essential |
| CH01-B055 | 1.7 / Screen Pixel Grid / 2780 | □ □ □ □ □ □ / □ □ □ □ □ □ / □ □ □ □ □ □ | Essential |
| CH01-B056 | 1.7 / Sample / 2810 | Pixel / ┌─────────┐ / │    •    │ | Essential |
| CH01-B057 | 1.7 / Coverage / 2836 | Triangle 내부의 Sample / → Covered | Essential |
| CH01-B058 | 1.7 / Coverage Before Color / 2890 | Triangle이 Screen의 어디에 영향을 주는가? / ~~~ | Essential |
| CH01-B059 | 1.7 / Coverage Before Color / 2896 | 그 위치에서 어떤 Surface 결과를 계산할 것인가? / ~~~ | Essential |
| CH01-B060 | 1.7 / Fragment / 2916 | Triangle / ↓ / Rasterization | Essential |
| CH01-B061 | 1.7 / From Candidate to Pixel Contribution / 2968 | Camera / ↓ / Character | Essential |
| CH01-B062 | 1.7 / From Candidate to Pixel Contribution / 2995 | Fragment 생성 / ↓ / 여러 Rendering Test / Processing | Essential |
| CH01-B063 | 1.7 / Multiple Fragments at One Pixel / 3023 | Screen Pixel 위치 / Sphere Fragment | Essential |
| CH01-B064 | 1.7 / From Geometry to Screen Samples / 3044 | Vertex / Triangle / Primitive | Essential |
| CH01-B065 | 1.7 / From Geometry to Screen Samples / 3055 | Fragment / Screen Position / Pixel | Essential |
| CH01-B066 | 1.7 / From Geometry to Screen Samples / 3067 | Geometry Processing / ↓ / Rasterization | Essential |
| CH01-B067 | 1.7 / Triangle Size and Fragment Count / 3087 | 작은 Screen 영역 / → 적은 Fragment / ~~~ | Essential |
| CH01-B068 | 1.7 / Triangle Size and Fragment Count / 3094 | 큰 Screen 영역 / → 많은 Fragment / ~~~ | Essential |
| CH01-B069 | 1.7 / Attributes After Rasterization / 3143 | Vertex A → UV (0, 0) / Vertex B → UV (1, 0) / Vertex C → UV (0, 1) | Essential |
| CH01-B070 | 1.7 / Rasterization Data Flow / 3169 | 유효한 Triangle / ↓ / Screen Space에 배치 | Essential |
| CH01-B071 | 1.8 /  / 3250 | Vertex Attributes / ↓ / Rasterization | Essential |
| CH01-B072 | 1.8 / Interpolation / 3270 | 왼쪽      가운데      오른쪽 / 0    →      5      →    10 / ~~~ | Essential |
| CH01-B073 | 1.8 / Why Interpolation Is Needed / 3301 | Vertex A → UV (0, 0) / Vertex B → UV (1, 0) / Vertex C → UV (0, 1) | Explain First |
| CH01-B074 | 1.8 / Why Interpolation Is Needed / 3317 | Fragment UV = (0.3, 0.4) / ~~~ | Explain First |
| CH01-B075 | 1.8 / Interpolation Weights / 3347 | Fragment가 A에 가까움 / → A의 Attribute 영향이 큼 | Explain First |
| CH01-B076 | 1.8 / Barycentric Coordinate / 3380 | Vertex A 영향 = 0.2 / Vertex B 영향 = 0.3 / Vertex C 영향 = 0.5 | Explain First |
| CH01-B077 | 1.8 / Barycentric Coordinate / 3392 | Vertex A → Red / Vertex B → Green / Vertex C → Blue | Essential |
| CH01-B078 | 1.8 / UV Interpolation / 3416 | Vertex A → UV (0, 0) / Vertex B → UV (1, 0) / Vertex C → UV (0, 1) | Explain First |
| CH01-B079 | 1.8 / UV Interpolation / 3426 | Fragment UV = (0.3, 0.4) / ~~~ | Explain First |
| CH01-B080 | 1.8 / UV Interpolation / 3434 | Vertex UV / ↓ / Fragment 위치에 맞게 값 계산 | Explain First |
| CH01-B081 | 1.8 / Interpolation and Texture Sampling / 3458 | Vertex UV / ↓ / Interpolation | Explain First |
| CH01-B082 | 1.8 / Vertex Color Interpolation / 3486 | Vertex A → Red / Vertex B → Green / Vertex C → Blue | Essential |
| CH01-B083 | 1.8 / Vertex Color as a Mask / 3512 | R → Dirt Mask / G → Wetness Mask / B → Effect Mask | Essential |
| CH01-B084 | 1.8 / Normal Interpolation / 3541 | Vertex Normal / ↓ / Fragment 위치에 맞게 중간 방향 계산 | Essential |
| CH01-B085 | 1.8 / Normalizing Interpolated Normals / 3617 | Vertex Normal / ↓ / Interpolation | Essential |
| CH01-B086 | 1.8 / Interpolating Other Attributes / 3656 | Vertex Shader Output / ↓ / Rasterization | Essential |
| CH01-B087 | 1.8 / Application to ASF Materials / 3738 | Mesh Vertex UV / ↓ / Vertex Processing | Explain First |
| CH01-B088 | 1.8 / From Vertex Attributes to Fragment Inputs / 3764 | Vertex A / Vertex B / Vertex C | Essential |
| CH01-B089 | 1.8 / From Vertex Attributes to Fragment Inputs / 3772 | Fragment 1 / Fragment 2 / Fragment 3 | Essential |
| CH01-B090 | 1.8 / From Vertex Attributes to Fragment Inputs / 3782 | Vertex Attribute / ↓ / Fragment 위치에 맞는 값 계산 | Essential |
| CH01-B091 | 1.8 / Data Flow / 3825 | Triangle의 Vertex / ↓ / Vertex Attributes | Explain First |
| CH01-B092 | 1.9 /  / 3917 | Fragment Input / ↓ / Fragment Shader / Pixel Shader | Essential |
| CH01-B093 | 1.9 / Rasterization and Fragment Processing / 4005 | Rasterization / → Screen 위치 결정 | Essential |
| CH01-B094 | 1.9 / Texture Sampling / 4052 | Vertex UV / ↓ / Interpolation | Essential |
| CH01-B095 | 1.9 / Surface Result / 4188 | UV / Normal / Vertex Color | Essential |
| CH01-B096 | 1.9 / Early Depth Test / 4255 | Fragment Shader / ↓ / Depth Test | Move to Technical Note |
| CH01-B097 | 1.9 / Early Depth Test / 4271 | Depth에서 실패할 Fragment / ↓ / Fragment Shader 실행 생략 가능 | Move to Technical Note |
| CH01-B098 | 1.9 / Vertex and Fragment Shaders / 4329 | Vertex / ↓ / Vertex Shader | Essential |
| CH01-B099 | 1.9 / Vertex and Fragment Shaders / 4349 | Fragment / ↓ / Fragment Shader | Essential |
| CH01-B100 | 1.9 / Shader Invocation Counts / 4377 | Vertex Shader Cost / → Geometry / Vertex 수와 관련 | Essential |
| CH01-B101 | 1.9 / Fragment Processing Data Flow / 4424 | Rasterization / ↓ / Fragment 생성 | Essential |
| CH01-B102 | 1.9 / Coverage and Surface Evaluation / 4471 | Rasterization / → 어디에서 계산할 것인가? | Essential |
| CH01-B103 | 1.10 /  / 4509 | Camera / ↓ / Character | Essential |
| CH01-B104 | 1.10 /  / 4545 | 여러 Fragment / ↓ / Depth Compare | Essential |
| CH01-B105 | 1.10 / Overlapping Fragments / 4589 | Character Fragment / Depth = Near | Explain First |
| CH01-B106 | 1.10 / Depth Test / 4613 | 새 Fragment가 더 가까움 / → Depth Test 통과 | Essential |
| CH01-B107 | 1.10 / Depth Test / 4625 | Current Depth = 0.4 / ~~~ | Explain First |
| CH01-B108 | 1.10 / Depth Test / 4631 | New Fragment Depth = 0.2 / ~~~ | Explain First |
| CH01-B109 | 1.10 / Depth Test / 4641 | New Fragment Depth = 0.7 / ~~~ | Explain First |
| CH01-B110 | 1.10 / Depth Buffer / Z-Buffer / 4667 | Screen Position A / Color = Red / Depth = 0.2 | Explain First |
| CH01-B111 | 1.10 / Surface Visibility / 4745 | 같은 Screen 위치의 여러 Fragment / ↓ / Depth 비교 | Essential |
| CH01-B112 | 1.10 / Camera and Light Visibility / 4787 | Depth Test / → Camera 기준 | Essential |
| CH01-B113 | 1.10 / Fragments as Pixel Candidates / 4842 | Character Fragment / Depth = Near | Explain First |
| CH01-B114 | 1.10 / Fragments as Pixel Candidates / 4856 | Rasterization / ↓ / Fragment 생성 | Essential |
| CH01-B115 | 1.10 / Depth Test Results / 4892 | Fragment / ↓ / Depth Test | Essential |
| CH01-B116 | 1.10 / Depth Write / 4928 | Depth Test / → 비교 | Essential |
| CH01-B117 | 1.10 / Early-Z / 4957 | Depth Test Fail 예상 / ↓ / Fragment Shader 실행 생략 | Move to Technical Note |
| CH01-B118 | 1.10 / Depth Test Data Flow / 5007 | Rasterization / ↓ / Fragment 생성 | Explain First |
| CH01-B119 | 1.10 / Camera and Light Visibility Comparison / 5039 | Depth Test / → Camera 기준 Visibility / → 화면에서 어떤 Surface가 보이는가? | Essential |
| CH01-B120 | 1.11 /  / 5106 | Fragment Result / ↓ / Framebuffer / Render Targets | Essential |
| CH01-B121 | 1.11 / Framebuffer / 5141 | Framebuffer / ├─ Color Buffer / ├─ Depth Buffer | Essential |
| CH01-B122 | 1.11 / Color Buffer / 5161 | Color = (0.8, 0.7, 0.6, 1.0) / ~~~ | Essential |
| CH01-B123 | 1.11 / Color Buffer Layout / 5185 | Color Buffer / [Color][Color][Color][Color]... | Essential |
| CH01-B124 | 1.11 / Depth Buffer / 5210 | Screen Position A / Color Buffer | Essential |
| CH01-B125 | 1.11 / Render Target / 5270 | Fragment Shader Output / ↓ / Render Target | Essential |
| CH01-B126 | 1.11 / Writing Fragment Results / 5362 | Shader Color = (0.8, 0.3, 0.2) / Shader Alpha = 1.0 / Raster Depth = 0.35  // Shader  | Essential |
| CH01-B127 | 1.11 / Writing Fragment Results / 5370 | Color Buffer / ← Color Result 기록 | Essential |
| CH01-B128 | 1.11 / Writing Fragment Results / 5380 | Fragment Shader / ↓ / Depth Test | Essential |
| CH01-B129 | 1.11 / Final Image / 5430 | Frame 1 / Frame 2 / Frame 3 | Essential |
| CH01-B130 | 1.11 / Double Buffering / 5452 | Front Buffer / → 현재 Screen에 표시 중 | Essential |
| CH01-B131 | 1.11 / Double Buffering / 5462 | Back Buffer 완성 / ↓ / Swap | Essential |
| CH01-B132 | 1.11 / Front and Back Buffers / 5482 | Back Buffer / ↓ / Rendering 완료 | Essential |
| CH01-B133 | 1.11 / Present / 5525 | Rendering / ↓ / Framebuffer / Back Buffer | Essential |
| CH01-B134 | 1.11 / Render to Texture / 5576 | Scene Rendering / ↓ / Render Target Texture | Essential |
| CH01-B135 | 1.11 / Storing Rendering Results / 5596 | 3D Model / ↓ / Vertex Processing | Essential |
| CH01-B136 | 1.11 / Data Flow / 5630 | Fragment Shader Result / ↓ / Depth Test | Essential |
| CH01-B137 | 1.12 /  / 5706 | CPU / Engine / ↓ / Rendering Data 준비 | Essential |
| CH01-B138 | 1.12 / GPU Responsibilities / 5767 | Vertex Buffer / ↓ / Vertex Shader | Essential |
| CH01-B139 | 1.12 / CPU and GPU Responsibilities / 5819 | CPU / → 준비 / 명령 | Essential |
| CH01-B140 | 1.12 / Objects and Draw Calls / 5869 | Character / Material 0 → Skin | Essential |
| CH01-B141 | 1.12 / Objects and Draw Calls / 5882 | Character / ↓ / Skin Draw Call | Essential |
| CH01-B142 | 1.12 / Vertex Buffer / 5978 | Vertex Buffer / Vertex 0 | Essential |
| CH01-B143 | 1.12 / Index Buffer / 6009 | Index Buffer / [0, 1, 2] | Essential |
| CH01-B144 | 1.12 / Index Buffer / 6021 | Vertex Buffer / + / Index Buffer | Essential |
| CH01-B145 | 1.12 / Materials and Textures / 6076 | Draw Call / ↓ / Mesh | Essential |
| CH01-B146 | 1.12 / Transform Data / 6112 | Mesh / + / Transform | Essential |
| CH01-B147 | 1.12 / Draw Calls in a Scene / 6155 | Character / Sword / Tree | Essential |
| CH01-B148 | 1.12 / Draw Calls in a Scene / 6169 | Draw Call 1 → Character Skin / Draw Call 2 → Character Hair / Draw Call 3 → Character | Essential |
| CH01-B149 | 1.12 / Draw Submission Cost / 6197 | 많은 Draw Calls / ↓ / CPU Rendering Command 증가 | Essential |
| CH01-B150 | 1.12 / CPU and GPU Bottlenecks / 6237 | CPU Bottleneck / → Draw Calls / Scene Processing / Command Preparation | Essential |
| CH01-B151 | 1.12 / Repeated Mesh Rendering / 6267 | Rock Mesh / ↓ / Draw Call 1 → Transform A | Essential |
| CH01-B152 | 1.12 / Rendering Command / 6292 | Set Render Target / Set Shader / Set Material | Essential |
| CH01-B153 | 1.12 / CPU and GPU Frame Overlap / 6327 | CPU / Frame 1 준비 / → Frame 2 준비 | Move to Technical Note |
| CH01-B154 | 1.12 / From Draw Submission to GPU Processing / 6387 | CPU / Engine / Scene Object 확인 | Essential |
| CH01-B155 | 1.12 / Core Relationship / 6429 | CPU / ↓ / 무엇을 그릴지 준비 | Essential |
| CH01-B156 | 1.12 / Core Relationship / 6448 | 3D Scene / ↓ / Rendering | Essential |
| CH01-B157 | 1.13 /  / 6478 | 3D Scene / ↓ / Rendering | Essential |
| CH01-B158 | 1.13 /  / 6521 | CPU / Engine / ↓ / Draw Call | Essential |
| CH01-B159 | 1.13 / Draw Call / 6640 | Set Vertex Buffer / Set Index Buffer / Set Shader | Essential |
| CH01-B160 | 1.13 / Submission and GPU Execution / 6661 | CPU / ↓ / Rendering 준비 | Essential |
| CH01-B161 | 1.13 / GPU — Geometry Processing / 6687 | Vertex Processing / ↓ / Primitive Assembly | Essential |
| CH01-B162 | 1.13 / Vertex Processing / 6719 | Local Space / ↓ / World Space | Explain First |
| CH01-B163 | 1.13 / Primitive Assembly / 6745 | [0, 1, 2] / ~~~ | Essential |
| CH01-B164 | 1.13 / Primitive Assembly / 6753 | Processed Vertices / + / Index Data | Essential |
| CH01-B165 | 1.13 / Geometry Processing Output / 6800 | Vertex Buffer / Index Buffer / ↓ / Vertex Processing | Essential |
| CH01-B166 | 1.13 / GPU — Screen / Fragment Processing / 6828 | Rasterization / ↓ / Interpolation | Essential |
| CH01-B167 | 1.13 / Rasterization / 6852 | Triangle / ↓ / Rasterization | Essential |
| CH01-B168 | 1.13 / Interpolation / 6884 | Vertex UV / ↓ / Interpolation | Essential |
| CH01-B169 | 1.13 / Fragment / Pixel Processing / 6916 | Fragment Data / ↓ / Fragment Shader | Essential |
| CH01-B170 | 1.13 / Fragment / Pixel Processing / 6928 | Rasterization / → 어디에서 계산할 것인가? | Essential |
| CH01-B171 | 1.13 / Depth Test / 6946 | Fragment / ↓ / Depth Compare | Essential |
| CH01-B172 | 1.13 / Geometry and Screen Processing / 6968 | Vertex Processing / ↓ / Primitive Assembly | Essential |
| CH01-B173 | 1.13 / Geometry and Screen Processing / 6980 | Rasterization / ↓ / Interpolation | Essential |
| CH01-B174 | 1.13 / Framebuffer / 7015 | Fragment Result / ↓ / Framebuffer | Essential |
| CH01-B175 | 1.13 / Color Buffer / 7035 | RGBA / (0.8, 0.2, 0.1, 1.0) / ~~~ | Essential |
| CH01-B176 | 1.13 / Present / 7083 | Framebuffer / Back Buffer / ↓ / Rendering 완료 | Essential |
| CH01-B177 | 1.13 / Final Image / 7101 | 3D Scene / ↓ / Rendering | Essential |
| CH01-B178 | 1.13 / Final Image / 7111 | 3D Scene / ↓ / CPU / Engine Preparation | Essential |
| CH01-B179 | 1.13 / Complete Data Flow / 7133 | 3D Scene / Object / ↓ / CPU / Engine | Essential |
| CH01-B180 | 1.13 / Data Transformations / 7215 | Scene Object / ↓ / Vertex Data | Essential |
| CH01-B181 | 1.13 / Rendering Work and Cost / 7307 | 많은 Vertex / → Geometry / Vertex Processing Cost | Essential |
| CH01-B182 | 1.13 / Complete Rendering Data Flow / 7340 | CPU / Engine / ↓ / Rendering Preparation | Essential |



</details>

---

## Chapter 02 — Coordinate System

Current: [Chapter02_CoodinateSystem.md](./Chapter02_CoodinateSystem.md) · Backup: [Chapter02_CoodinateSystem_backup.md](./Chapter02_CoodinateSystem_backup.md)

### Major Changes

2.1–2.16의 전체 본문을 검토했다. 초기 Chapter05 Reference에서 가져온 것은 익숙한 사례에서 질문을 만들고, 한 관계씩 설명한 뒤 식으로 연결하는 설명 호흡이다. Reference를 Coordinate 기술 내용의 권위로 사용하지 않았다.

기존의 주요 Space 설명과 기술 보정을 유지하면서, 서로 떨어진 짧은 설명을 연결 문단으로 정리했다. Chapter opening에서 Cube의 Mesh 형태·Scene 배치·Camera 관점이라는 세 질문을 먼저 설명했다. 여러 기준을 소개한 뒤 Transform과 Matrix가 필요한 이유를 연결한다. 600개 기존 fenced block과 19개 기술 table은 문자 내용과 개수를 유지했다.

| Section | Teaching change |
|---|---|
| 2.1 | 측정 기준이 필요한 이유를 자·문·방의 기준으로 설명하고, 값보다 Data의 의미와 Space를 먼저 읽도록 연결했다. |
| 2.2 | 종이의 화살표를 이동·회전하는 사례로 Position/Direction 차이를 설명했다. 두 Position의 차이를 목적→변화량→빼는 순서→Vector로 연결했다. |
| 2.3 | 같은 Mesh 형태와 Object 배치를 분리하는 이유를 확장하고, 문이 열려도 Local Point가 같은 곳에 붙어 있는 예로 Rotation을 설명했다. |
| 2.4 | 다른 Object와 Light의 관계에 공통 기준이 필요한 이유를 보강했다. Translation-only 숫자 예는 적용 조건을 먼저 밝힌다. |
| 2.5 | Camera의 자로 Scene을 다시 측정한다는 관점과 Camera Transform을 되돌리는 Inverse 관계를 단계적으로 설명했다. |
| 2.6 | 손의 화면 크기와 설계도 사례로 Perspective/Orthographic 목적을 구분했다. Frustum과 Matrix를 그 역할 이후 정의한다. |
| 2.7 | GPU가 Geometry의 어느 부분을 남길지 먼저 정해야 하는 이유와 w에 의존하는 경계 비교를 식 전에 보강했다. |
| 2.8 | Translation 항에 참여해야 하는 입력과 참여하지 않아야 하는 입력을 구분했다. Cartesian/Projective의 의미를 네 성분의 비율 관계 전에 설명한다. |
| 2.9 | Clip XYZ를 w에 대한 비율로 읽는 목적을 먼저 설명했다. 같은 View X/Y Offset, 고정 Projection, View Depth, Clipping-before-Divide는 본문에 유지하고 긴 규약/수치 확장은 Notes에 재배치했다. |
| 2.10 | 상대 위치를 Viewport의 실제 폭·높이·시작 위치에 대응하는 관계를 수치 예제 앞에서 설명했다. Y 방향과 Pixel index/center의 긴 비교는 Notes로 분리했다. |
| 2.11 | 모든 Vertex에 같은 규칙을 적용해야 하는 문제에서 Matrix로 연결했다. Column/Row Vector 의미와 Transform 순서가 달라지는 결과를 곱 전에 설명했다. |
| 2.12 | 각 Matrix의 출력 Space가 다음 입력과 맞는지 설명했다. MVP의 Full Name, 책임 결합과 실제 Matrix 곱의 차이, Position/Direction 수치 예제의 예상 결과를 보강했다. |
| 2.13 | Translation 제외와 Scale 영향의 차이를 설명했다. Non-uniform Scale과 Normal의 수직 관계를 이름/도구보다 먼저 읽도록 보강했다. |
| 2.14 | Normal Map이 저장한 방향의 Surface 기준과 Lighting 기준의 차이에서 시작한다. Encoding/Decode/Space Transform을 따로 설명하고 T/B/N 성분 조합을 이해한 뒤 기존 TBN 식을 읽는다. |
| 2.15 | Unreal Node 이름보다 Data 의미·Space·계산 목표를 먼저 확인한다. Bounds center/Origin/Pivot과 World Offset/Local Position의 차이를 보강했다. |
| 2.16 | Cube와 Camera의 초기 질문으로 돌아와 Position 경로와 Lighting Direction 경로를 구분했다. 기존 전체 경로/table/checklist/Chapter Summary를 보존했다. |

### Added Explanation

- Object를 이동해도 Mesh 내부의 Local Vertex와 화살표 Direction은 각각 다른 방식으로 유지될 수 있다는 중간 단계를 추가했다.
- Camera 이동과 View 표현의 반대 움직임을 Inverse의 입력·출력 방향으로 연결했다.
- Perspective의 같은 Offset/다른 Depth 비교와 동일 Camera ray 비교를 본문에서 구분한다. Depth가 X로 바뀌는 것이 아니라 분모가 화면 Offset의 비율을 바꾼다는 설명을 보강했다.
- TBN을 Matrix 이름으로 먼저 제시하지 않고, Surface의 세 기준 방향이 어떤 Direction 성분을 읽는지 설명했다. Decode는 저장값 해석이고 TBN은 Space 변환이다.
- Chapter01의 Vector/Normal/UV/Normalize는 짧게 회상하고 본 장의 Space·Transform 목적에 맞게 확장했다. 완성된 Chapter01의 최초 설명을 대조하고 앞 장의 정의를 다시 모두 증명하지 않았다.

### First-Use Terminology Improvements

Coordinate System/Space, Local/World/View/Clip Space, NDC, Matrix/Transform, Homogeneous Coordinate, Basis/Tangent/Bitangent/TBN의 최초 이름과 실제 본문 위치를 확인했다. NDC는 Chapter opening의 첫 diagram보다 먼저 Normalized Device Coordinates와 해상도 전 공통 범위의 목적을 설명한다.

TBN은 첫 preview에서 Tangent, Bitangent, Normal의 머리글자와 세 기준 방향의 역할을 함께 풀었다. 본격 설명은 2.14에서 Surface 방향 문제→Basis→성분→목표 Space→Matrix로 확장한다. 새로 드러나는 DCC, Graphics API, HLSL, MVP도 Full Name과 사용 목적을 설명했다.

최종 최초 위치와 원래 문맥은 이 보고서 마지막 Terminology Audit Table에 기록했다. 2.1의 TBN 예고는 Tangent→Bitangent→Normal→Basis→TBN 순서로 나누었다.

### Technical Content Preserved

- Fenced block: **600 → 600**, 전체 원문 multiset 동일. Code·Formula·Data Flow 내용과 개수를 보존했다. Note 이동에 따른 위치 변화는 허용된 재배치다.
- Technical table: **19개 모두 원문 보존**.
- 기존 inline backtick 내용: **167개 모두 보존**; 추가 설명용 표시만 늘었다.
- Major 번호: **2.1–2.16 원래 순서 유지**.
- Image tag: **16개 원문/순서 유지**. Figure path/number와 PNG를 수정하지 않았다.

Position/Direction의 Translation 차이, Rotation/Scale, Affine 입력의 w=1/0과 Projection 출력 w의 역할 차이, View Depth와 직선거리 차이, 현재 Projection 설정을 반영한 Clipping, Clip/NDC 깊이 규약, Pixel 경계/index/center, Column/Row 곱과 memory storage 차이, Geometric/Shading Normal, Non-uniform Scale의 Normal 전용 변환, orthonormal TBN/Transpose 조건, 이미 Decode한 Sampler의 중복 Decode 금지, ObjectPositionWS bounds center와 World Offset의 의미를 유지했다.

### Technical Detail Moved to Notes

계산 결과를 바꾸는 핵심 조건은 적용 전에 남겼다. 긴 규약 비교·수치 확장·Engine 확인 항목은 삭제하지 않고 펼쳐 읽는 Notes로 분리했다.

- 2.5: Implementation Note — View Axis Convention; 기존 subsection 전체와 수식/수치/조건을 보존했다.
- 2.10: Implementation Note — Screen Origin and Y Direction; 기존 subsection 전체와 수식/수치/조건을 보존했다.
- 2.10: Technical Note — Continuous Coordinates, Pixel Index and Pixel Center; 기존 subsection 전체와 수식/수치/조건을 보존했다.
- 2.14: Implementation Note — Mirrored UV and Handedness; 기존 subsection 전체와 수식/수치/조건을 보존했다.
- 2.14: Implementation Note — Tangent Seams and Vertex Data; 기존 subsection 전체와 수식/수치/조건을 보존했다.
- 2.14: Implementation Note — Tangent Data and Vertex Splits; 기존 subsection 전체와 수식/수치/조건을 보존했다.
- 2.9: Implementation Note — Space Suffixes and Variable Names; 주 계산 이후 펼쳐 읽을 수 있도록 재배치했다.
- 2.9: Numerical Note — View Depth versus Straight-line Camera Distance; 주 계산 이후 펼쳐 읽을 수 있도록 재배치했다.
- 2.9: FOV/Aspect/current Projection의 긴 확장과 60°/90° 예를 계산 이후 Note로 이동; 적용 직전 조건은 본문에 남겼다.
- 2.1: 기존 Key Terms 회상은 선택적 Review Note로 유지하고 용어 정의는 최초 흐름에서 제공했다.

Figure 2-1/4/7/8/9/12/13/14/15에서는 개념을 읽는 목적과 순서를 먼저 두고, 기존 상세 예제 조건·Convention·검증 한계를 Figure 바로 아래 Figure Reading Note에 보존했다. 나머지 Figure의 기존 설명과 짧은 조건은 해당 위치에서 유지한다.

### Formula Changes

기존 Formula의 기호·성분·수치·Code 내용을 변경하거나 삭제하지 않았다. 새로 붙인 설명은 식의 입력, 비교 관계, 출력 의미를 읽도록 돕는 Prose다. 다음은 주요 Formula의 판단이다.

| Formula / relationship | Classification | Treatment |
|---|---|---|
| B − A / Surface → Light / Surface → Camera | Essential | 두 Point 사이 변화량과 같은 Space, 빼는 순서가 방향을 정하는 이유를 먼저 설명한다. |
| Position/Direction의 (x,y,z,1)/(x,y,z,0) | Essential | 위치를 옮길 때 화살표 방향까지 옮기면 안 된다는 문제→Translation 참여→입력 w 순서로 읽는다. |
| Model/View/Projection Transform 및 Matrix 곱 | Explain First | 배치/Camera/Projection 책임과 수치 결과를 먼저 설명하고, Column Vector 조건을 식 바로 앞에 둔다. |
| -w ≤ x/y ≤ w | Explain First | Perspective Frustum의 깊이에 따라 넓어지는 경계를 먼저 설명한 뒤 Clip 성분과 w 조건을 읽는다. |
| Clip XYZ / w_clip → NDC | Essential | 나누는 값은 Projection 출력 Clip 값임을 먼저 구분한다. 같은 Offset/다른 View Depth 조건을 수치 적용 전에 둔다. |
| Homogeneous 동치 Point (2,4,6,2) / (1,2,3,1) | Explain First | 입력 Flag만으로 설명되지 않는 비율 관계를 먼저 설명한다. GPU Clipping에서 임의 부호 반전의 동치로 확대하지 않는 기존 Note를 유지한다. |
| Camera Distance sqrt 및 11.66 수치 예 | Move to Technical Note | View Depth와 직선거리의 차이를 본문에서 먼저 설명하고 전체 수치 계산은 Numerical Note에 보존한다. |
| MVP 곱의 Row/Column vs storage Convention | Move to Technical Note | 실제 입출력 Space와 적용 순서는 본문; HLSL mul 및 storage 규약 비교는 기존 Implementation Note에 유지한다. |
| TBN × N_tangent / Normalize | Explain First | T/B/N의 목표 Space 방향과 성분 조합을 설명한 뒤 기존 식을 읽는다. Decode된 입력, Unit/orthonormal 조건과 Sampler 범위를 유지한다. |
| N · L / dot(N,V) | Essential | 동일 Space의 Direction 관계를 읽는 예고로 사용한다. 정규 직교 기준의 Unit Direction 조건을 유지하고 연산의 상세 원리는 Chapter03에 둔다. |

### Structure Changes

파일명과 2.1–2.16 번호를 바꾸지 않았다. 기존 --- 구분을 유지하고 실제 Note 역할에만 details를 추가했다. 기존 Chapter Summary와 다음 Chapter03 파일 링크는 유지한다. 모든 Subsection에 glossary나 Key Takeaways를 추가하지 않았다.

2.9의 긴 notation/거리/FOV 확장을 주 개념·수치 예제 이후로 이동해, 핵심 Divide 관계 사이에 세부 설명이 끼어드는 정도를 낮췄다. 2.14의 UV Seam/Mirrored UV/Vertex Split은 실제 Normal Map/TBN 연결을 설명한 뒤 펼쳐 보는 구현 Notes다. 기존 Technical/Verification Notes의 정확성 조건은 제거하지 않았다.

### Figure Review

16개의 Figure를 본문 설명과 함께 검토했다. Figure와 본문의 기술 조건을 가리지 않으면서 학습 목적을 먼저 읽는 문장을 추가했다. 기존 Clip 깊이·Forward 부호·Column Vector·View Depth 비교·Viewport Top-left/Down-Y·TBN orthonormal/Decode·Engine schematic 조건은 Figure Reading Note 또는 기존 Note에 남는다.

새 Figure를 만들거나 PNG를 고치지 않았다. Figure2-15는 Engine 실행 screenshot으로 간주하지 않는다. 기존 대상 Engine 검증 요구는 그대로 유지한다.

### Remaining Review Items

- Unreal 대상 버전에서 ObjectPositionWS의 bounds center, VertexNormalWS의 실행 context, PixelNormalWS의 현재 Normal 반영 경로, ScreenPosition mode, Transform/TransformPosition 지원 범위와 Non-uniform Scale 제한을 실제로 확인해야 한다. 문서 보존검사는 Engine 실행 검증이 아니다.
- Figure의 Forward/Z/Viewport 규약은 해당 예의 조건이며 모든 Engine에 일반화하지 않는다. 이 한계 문구를 기존 원문과 함께 보존했다.
- 최종 01–05의 연결과 실제 첫 사용 위치를 대조했다.  Chapter03의 정식 Normalize/Dot/Normal 유도를 Chapter02로 복제하지 않았다.
- 기존 600개 block을 그대로 보존했으므로 반복되는 Data Flow/수치 예가 남는다. 이번에는 기술 보존과 중간 설명 강화를 우선했으며 임의로 중복 block을 삭제하지 않았다.

---

## Chapter 03 — Lighting Mathematics

Current: [Chapter03_LightingMathematics.md](./Chapter03_LightingMathematics.md) · Backup: [Chapter03_LightingMathematics_backup.md](./Chapter03_LightingMathematics_backup.md)

### Major Changes

3.1–3.7 전체를 확인했다. 이미 개선된 Normalize → Dot Product → Normal 종류 → Non-Uniform Scale → Inverse Transpose → 방향 생성 → 공통 Space 흐름은 그대로 유지했다. 종이를 Light 아래에서 돌리는 문제로 시작하고, 위치·Surface 방향·광원 방향·관찰 방향을 별도 입력으로 준비해야 하는 이유를 연결했다. 기존에 잘 설명된 개념을 다시 압축하거나 새로운 증명으로 대체하지 않았다.

### Added Explanation

3.1의 Point/Directional Light와 Diffuse/Specular preview를 독자가 실제 현상으로 읽도록 풀었다. 3.2에서는 Vector의 길이가 Light의 세기라는 뜻이 아니라 방향 비교의 조건이라는 점을 추가했다. 3.3에서는 Scalar가 필요한 이유를 숫자 하나로 관계를 전달하는 문제로 설명했다. 3.4의 Vertex Normal → Interpolation → Pixel Normal 연결은 앞 Chapter의 보간을 회고한 뒤 이어간다. 3.5는 2D 예제를 유지하면서 Position 변환과 수직 관계를 지켜야 하는 Normal 변환의 차이를 연결했다. 3.6의 방향 규약은 같은 두 지점에 반대 화살표 두 개를 그릴 수 있다는 직관으로 시작한다. 3.7의 혼합 Space 오류는 서로 다른 방향으로 놓인 기준축을 비교하는 문제로 설명했다.

### First-Use Terminology Improvements

Magnitude와 Normalize는 원문에서도 의미를 설명했다. 이번에는 앞 Chapter에서 소개한 Vector를 짧게 회고하고 길이의 의미를 현재 질문에 연결했다. 도입에서 먼저 사용되던 Normalize/Dot Product/NdotL에는 각 연산의 목적을 붙였다. Scalar는 숫자 하나라는 의미를 첫 사용에 추가했다. One-sided/Opaque/Clamp/Winding/Front-Face는 사용하는 문맥 안에서 뜻을 풀었다. Inverse와 Transpose의 기존 정의는 유지하고 Row/Column의 의미를 덧붙였다. DCC/API/RGB는 Chapter 01–02의 최초 정의를 반복하지 않고 현재 사용 역할을 짧게 회고했다.

### Technical Content Preserved

같은 Space와 Unit Length 조건, Signed NdotL과 Clamped Factor의 차이, max와 saturate의 범위 차이, Geometric/Shading Normal 구분, Cross Product 순서와 Winding/Front-Face 구분을 유지했다. Non-Uniform Scale의 T/N 예제와 잘못된 Normal을 Normalize해도 방향은 고쳐지지 않는다는 설명을 유지했다. Matrix 표기 규약·Zero Scale·Degenerate Geometry·Orthographic V·Directional L·보간 후 Normalize·Camera 이동 검증의 동일 Surface 위치 조건도 유지했다.

### Technical Detail Moved to Notes

기존 Zero-Length Vector, Degenerate Geometry, Matrix Convention and Zero Scale Notes를 유지했다. Main Flow의 Non-Uniform Scale 직관은 원래부터 충분히 분리되어 있어 증명이나 핵심 조건을 추가로 숨기지 않았다. Winding과 API 방향 규약은 잘못된 계산을 막는 즉시 적용 조건이므로 본문 가까이에 남겼다.

### Formula Changes

기존 수식·inline 계산 예시·기술 표를 모두 유지했다. 새 수학적 모델이나 Engine 수식을 도입하지 않았다.

| Formula Group | Classification | Treatment |
|---|---|---|
| normalize(Vector), N/L Normalize | Essential | 같은 방향·다른 길이 예제 뒤에 유지 |
| dot(N,L), NdotL, max/saturate | Essential | Scalar가 필요한 이유와 앞면의 처리 범위 후 계산 |
| dot(N,L)=cosθ | Explain First | 방향 관계 표와 Cosine의 의미 뒤에 유지 |
| FaceNormal의 Cross Product | Essential | 두 Edge가 만드는 면과 수직 방향을 먼저 설명 |
| Non-Uniform Scale의 T/N 계산·Dot 검사 | Explain First | Surface를 가로로 늘리는 예제를 단계별로 유지 |
| transpose(inverse(M)), Nworld | Explain First | 역방향 Scale 보정과 수직 관계를 설명한 뒤 일반화 |
| 위치 차이로 L/V 생성 | Essential | 출발점·목적지·방향 규약을 먼저 설명 |
| Zero-Length, Zero Scale, Matrix Convention | Move to Technical Note | 기존 Notes 유지; 계산의 유효 범위 보존 |

### Structure Changes

주요 번호 3.1–3.7, 기존 표와 수식, 6개 Figure 순서를 유지했다. 각 절의 중간 연결을 늘렸으며 이미 자연스러운 Key Takeaways와 Chapter Summary는 역할에 맞게 유지했다. 획일적인 항목 묶음을 모든 Subsection에 추가하지 않았다.

### Figure Review

6개 이미지의 태그·경로·번호·순서는 변경하지 않았다. 수치 예제와 Geometry/Shading 구분, Perspective/Orthographic 방향 경로를 원문 기준으로 유지했다. 이미지 내부 용어는 이번 작업에서 재생성하지 않았으며, 본문에서 해당 의미를 먼저 소개하도록 보강했다.

### Remaining Review Items

대상 Engine/API가 제공하는 방향 부호와 Matrix 곱셈 규약은 실제 구현을 옮길 때 확인해야 한다. 이는 기존 조건을 보존한 항목이며 이번에 Engine 실행을 완료했다는 뜻이 아니다. 이미 concept-first로 개선된 Chapter 03의 설명 속도는 독자 검수에서 앞뒤 Chapter와 함께 확인할 수 있다.

---

## Chapter 04 — Material Architecture

Current: [Chapter04_MaterialArchitecture.md](./Chapter04_MaterialArchitecture.md) · Backup: [Chapter04_MaterialArchitecture_backup.md](./Chapter04_MaterialArchitecture_backup.md)

### Major Changes

4.1–4.8 전체에서 Source → 현재 Surface의 값 → 입력 해석 → Shader 합류의 흐름을 검토했다. 기존 Texture/UV/Color Space/Normal Map/Parameter의 좋은 문제 중심 구조를 유지하며, 도입과 최초 용어가 독자의 이해를 앞질러 가는 부분을 풀었다. Texture Sampling, Color Decode, Direction Decode와 Space 변환은 서로 다른 문제를 해결하는 단계로 연결했다.

### Added Explanation

Material Property를 단순한 옵션이 아니라 Surface의 성질로 소개했다. Constant/Parameter/Texture의 선택 이유, Material Graph/Compile의 역할, 같은 Architecture와 실제 Program 구성의 차이를 단계적으로 설명했다. 4.3에서 Color Space·Linear·sRGB·Raw·Encoding/Decode·Sampler/Filtering이 뒤의 전문 Section보다 먼저 등장하므로 짧은 의미를 그 위치에 붙였다. 4.4의 UV는 앞 Chapter의 주소 역할을 회고한 뒤 Vertex에서 처리 위치까지 추적한다. Bilinear의 두 축 보간, Mip Level과 Aliasing/Shimmering의 문제를 연결했다. 4.5는 같은 0.5라도 Color 저장값과 Roughness 숫자는 다른 목적이라는 점에서 시작한다. 4.6은 signed/unsigned 범위와 TBN의 기존 Basis 의미를 연결했다. 4.7은 Parent/Instance/Override/Interface, Compile Time/Runtime을 개별 단계로 소개했다.

### First-Use Terminology Improvements

Texel은 원문 4.3에서도 저장 단위로 설명했고 4.4에서 Texture Element를 풀었다. 이번에는 Full Name을 최초 사용에 붙이고 Pixel과 저장 대상의 차이를 설명했다. UV/Texture Sampling은 앞 Chapter와 원문에 이미 설명이 있어 재정의 대신 사용 범위를 연결했다. Filtering/Sampler, Linear/sRGB, Encode/Decode는 정식 설명 이전에 쓰였던 위치에서 역할을 먼저 소개했다. Normal Map은 4.2의 첫 preview에서 Direction Texture라는 뜻을 설명했다. Parameter는 도입에서, Material Instance는 4.7의 문제 해결 시점에서 의미를 밝혔다. Runtime/Compile Time/Static Switch/Static Component Mask/Variant/Permutation의 범위를 분리했다. 추가 약어 PBR/HDR/AO/LED도 이름만 남지 않도록 뜻을 풀었다. TBN은 Chapter 02의 Tangent/Bitangent/Normal 회고로 연결했다.

### Technical Content Preserved

Color Texture와 Numeric Data Texture의 저장 목적, 자동 Decode와 중복 Decode 방지, sRGB Off가 모든 Format/Filtering/Normal 복원을 없애지 않는다는 조건을 유지했다. Roughness의 잘못된 해석은 `0.50 → sRGB Decode → 약 0.214 → 낮은 Roughness → 더 Glossy한 경향`을 유지했다. 반대 변환인 Linear 0.50 → sRGB 약 0.735와 혼동하지 않는다. Normal sampler가 이미 복원한 Direction과 raw RGB의 처리 범위를 유지했다. Tangent Basis/목표 Space/Unit Normal, MIC Editor 조절, MID의 지원되는 Non-Static Runtime 변경, Static 선택의 Compile Time Variant/Permutation 구분을 모두 유지했다.

### Technical Detail Moved to Notes

Color Space의 Transfer Function/Primaries/White Point/Working Color Space는 개념 설명 뒤의 details로 분리했다. Filtering과 Decode의 실제 처리 순서는 Implementation Note로 표시했다. UV의 Perspective-correct 보간, Basis의 handedness, 합류 시 Direction 입력 범위를 named Note로 구분했다. Figure 4-6의 패널별 숫자·중복 Decode·Basis 조건은 짧은 Caption 뒤 Figure Reading Note로 옮겼다. raw RGB/이미 Decode된 Direction 분기와 Runtime/Static 구분은 실행 결과를 바꾸는 조건이므로 본문에서도 유지했다.

### Formula Changes

기존 31개 fenced block, inline 예제와 기술 표를 보존했다. 새 핵심 수식을 추가하거나 숫자 예제를 다른 모델로 바꾸지 않았다.

| Formula Group | Classification | Treatment |
|---|---|---|
| UV/Texture/Sampler → Sample → 현재 Input | Essential | 주소·Resource·읽기 규칙을 먼저 설명 |
| Bilinear 네 Texel의 관계와 Mip 해상도 표 | Explain First | Texel 사이 위치와 화면에서 과도한 Detail 문제 후 제시 |
| sRGB Encode/Decode 흐름 | Essential | 저장값과 계산값의 목적을 먼저 구분 |
| sRGB의 0.50 → 약 0.214 수치·반대 Encode 0.735 | Move to Technical Note | 기존 수치/방향 그대로; 핵심 Roughness 경향은 본문에도 유지 |
| Encoded = Normal × 0.5 + 0.5 | Explain First | signed 방향을 unsigned 저장 범위로 옮기는 이유 후 유지 |
| Normal = RGB × 2 - 1 | Explain First | 저장 범위를 되돌리는 직관 후 유지; raw RGB 범위 명시 |
| TBN → 목표 Lighting Space → Normalize | Essential | 기존 Basis의 성분 기여와 공통 Space 필요성을 먼저 회고 |
| Runtime Non-Static / Static Compile 구성 흐름 | Essential | 실행할 값과 실행할 Program 구성의 차이를 먼저 설명 |

### Structure Changes

주요 번호 4.1–4.8을 유지했다. 용어를 별도의 사전 목록으로 모으지 않고 쓰이는 문제 안에서 설명한다. 4.3의 preview와 4.5/4.6의 정식 확장은 역할을 나누었다. 4.7의 Editor/Runtime/Static 세 경로와 4.8의 합류 구조를 유지했다. 기존 Key Takeaways는 주요 개념 단위에만 사용한다.

### Figure Review

8개 이미지 태그·경로·번호·순서는 유지했다. Figure 4-5의 Roughness Decode 방향과 Figure 4-7의 변경 범위를 수정 전의 정확한 상태로 보존했다. Figure 4-6의 긴 Caption을 Reading Note로 분리했으며 이미지 자체는 변경하지 않았다. 이미지의 개념 비교를 실제 Engine 측정이나 Screenshot으로 취급하지 않았다.

### Remaining Review Items

Normal sampler output/Compression/Format과 TBN 목표 Space·Basis 조건, MIC/MID 조작 및 Static Compile 결과는 대상 Unreal Engine Version의 기존 검증 항목으로 남긴다. 이번 작업에서 Engine 실행을 완료했다고 표시하지 않았다. sRGB 이름을 풀어도 전체 Color Space가 Transfer Function 하나만이라는 오해가 생기지 않도록 Note를 함께 유지했다.

---

## Chapter 05 — Reflection and BRDF

Current: [Chapter05_Reflection_BRDF.md](./Chapter05_Reflection_BRDF.md) · Backup: [Chapter05_Reflection_BRDF_backup.md](./Chapter05_Reflection_BRDF_backup.md)

### Major Changes

5.1–5.19 전체를 교수 흐름으로 다시 작성했다. Current의 친숙한 예시와 보강된 정확성을 함께 사용하면서, 첫 질문 → 필요한 관계 → 용어의 뜻 → 계산 입력 → Formula → Rendering 의미 → 앞 내용 회상과 다음 질문 순서를 복원했다. Source 39,920자에서 Rewrite 63,420자로 설명이 늘었다. 줄 수 자체를 목표로 삼지 않고, 기존 한 문단에 모였던 개념들을 이해 단계별로 분리했다.

특히 5.6의 Half Vector는 정의보다 먼저 나온 Formula를 중간 방향과 Normalize의 직관 뒤로 옮겼다. 5.15의 물리량 리스트는 총량·면적·방향·투영 면적이라는 서로 다른 질문으로 풀었다. 5.16–5.19는 Reference의 친절한 공통 질문과 회상을 현재의 BRDF 정의로 새로 작성했다.

### Added Explanation

- 5.1: 같은 조명의 거울/종이/플라스틱 관찰, Reflection과 흡수·투과의 관계, 현실을 Model로 단순화하는 이유, 실제 학습 경로의 목적을 나눠 설명했다.
- 5.2: 바닥/벽/천장 → 수직 기준 → ± 방향 중 Orientation → Winding → Geometric/Shading Normal → Unit/Space의 계산 조건을 단계적으로 연결했다.
- 5.3: N 기준 입사·반사각 → L과 실제 진행 I의 차이 → 방향 R의 목적 → Formula → 함수 입력/성분 분해를 연결했다.
- 5.4: 거울과 종이 관찰 → Diffuse와 Rough Specular의 차이 → 입사 Irradiance와 Outgoing Radiance → 비스듬한 빛의 면적 분산 → Cosine Factor → BRDF의 다른 역할을 설명했다.
- 5.5–5.7: Camera 이동으로 Highlight가 달라지는 이유, Highlight가 Emission이 아닌 이유, 지수 n의 목적, 중간 H를 만드는 방법, 최대 정렬과 전체 Lobe의 차이를 설명했다.
- 5.8–5.10: 현재 Shading Point와 Mesh 전체의 범위를 구별하고, 작은 거울의 방향/분포/경로/반사율을 각 질문으로 연결했다.
- 5.11–5.14: Roughness의 분포 역할, Density와 영역 전체 비율, D와 G의 차이, 두 차폐 경로, F0와 Angle의 의미, H 기준의 Fresnel, Material 입력과 표시 밝기의 관계를 분리했다.
- 5.15: Energy/Power 구분을 먼저 준비하고 Flux/Irradiance/Intensity/Radiance를 각자 필요한 측정 질문에서 설명했다. 마지막에 기존 정확한 정의와 단위를 비교한다.
- 5.16–5.17: 서로 다른 Reflection Model에 공통 정의가 필요한 이유, 두 Direction과 입력 범위, BRDF response와 Light amount의 차이, Anisotropic Model의 선택적 Tangent Basis 필요를 표 전에 설명했다.
- 5.18: 작은 방향 범위 한 개의 기여 → dEi/dLo → 모든 입사 방향의 합 → Emission → Rendering Equation 순서로 기호와 Formula를 준비했다. Visibility의 입력 상태와 물리 조건을 이해한 뒤 정밀 Note로 연결했다.
- 5.19: 처음의 Lambert 질문을 되짚고 ρ, 1/π, Ei의 Cosine 포함 여부를 Formula 전에 이해하게 했다. 기존 수치 검산과 교육용 Base Lighting의 범위를 유지했다.

### First-Use Terminology Improvements

Chapter 01–04에서 이미 소개된 Vector/Normalize/Dot Product/Space/Normal/Material 입력은 짧은 회상으로 연결했다. Diffuse/Specular는 Chapter 03, PBR/Roughness/Dielectric은 Chapter 04의 소개와 연결한다. 새 설명을 모두 Chapter 05가 최초의 학습이라고 주장하지 않는다.

반면 Chapter 05의 BRDF, Reflection Vector, I/L 방향, Half Vector, Microfacet, NDF, Geometry Function, Shadowing/Masking, Fresnel, Radiometry, Flux/Irradiance/Radiance/Intensity, Density, Solid Angle, Single Scattering, Anisotropy, Reciprocity 등은 해당 개념이 필요한 문제에서 뜻을 풀었다. 중요한 Full Name과 물리 단위는 유지한다.

### Technical Content Preserved

19개 fenced block의 문자내용과 개수를 모두 보존했다. 중복되어 있는 R/V 및 N/H 비교 block도 원래 개수대로 남겼다. 기존 Input Table을 그대로 유지했고, 14개 Figure 태그의 문자내용·경로·번호·순서를 보존했다. 원문 inline code expression도 모두 보존했다. Reference/Source/Backup/다른 Chapter/실제 작업 폴더/Figure는 이 담당 작업에서 수정하지 않았다.

핵심 기술 구분과 고유 값도 보존했다.

- Normal ± Orientation, Winding, Geometric/Shading Normal, 같은 Space Unit 조건.
- L=Surface→Light, I=-L, reflect 입력 방향, -I/N 입사각, R 성분 분해와 N=(0,0,1), L=(0.6,0,0.8), R=(-0.6,0,0.8) 검산.
- Diffuse/Rough Specular, Lambert의 같은 Ei에서 관찰 방향에 무관한 Lo, Power와 Radiance 구분, One-sided Opaque 범위.
- NdotL 입사 계수와 BRDF의 역할 차이, ρ/π, Ei의 Cosine 포함으로 인한 중복 곱셈 방지.
- Phong/Blinn-Phong의 Unit/앞면/지수/경계/전체 Lobe와 최대 정렬 차이, 구현 성능 측정 조건, 정규화 Response 변형의 범위.
- Shading Point와 Mesh 전체의 구분, H에 정렬되는 Facet만 기여하며 모든 Facet이 H를 향하지 않는다는 조건.
- Single-scattering Microfacet BRDF의 분모, 양의 Dot/0분모 조건, D density와 확률의 차이, D 정규화, 분포/Parameter/G 선택 조건.
- Microfacet G와 Scene Visibility Vis, Shadowing/Masking 방향, V/Vis 표기 및 차폐 중복 방지.
- Microfacet Fresnel의 H 기준과 N·V 구분, F0 광학식/η1≈1/η2≈1.5/0.04/0.07 검산, Schlick 근사 범위, Metal/Dielectric Base Color 역할과 pure Metal Diffuse 없음.
- Energy와 Power, Flux W=J/s, Irradiance W/m², Radiance W/(m²·sr), Intensity W/sr.
- BRDF 응답 sr⁻¹과 최종 RGB/0–1 비율의 차이, RGB 근사 범위, Material 입력과 Light Intensity의 분리, Tangent Basis/Anisotropic 범위.
- dLo/dEi 정의, 입사 Cosine/dω, Opaque 반구 적분, Emission, 비음수·에너지 보존·상호성, Diffuse/Specular 합성의 조건.
- 선형 Radiance의 Light 배율 검산과 Exposure/Tone Mapping 후 표시 RGB의 차이.
- ρ=0.5, Ei=π W/m², Lo=0.5 W/(m²·sr) 검산과 같은 Surface/Specular 없음/View만 변화 조건.
- Chapter 08.2/08.4의 교육용 응답과 완성된 물리 BRDF Lighting의 범위 차이.

### Technical Detail Moved to Notes

핵심 조건을 숨기지 않았다. Formula를 바르게 쓰는 최소 조건은 계산 옆에 유지하고, 긴 유도·경계·범위 비교는 뒤의 Note로 나눴다.

- 5.2 Implementation Note: 실제 Lighting N의 Shading/Unit/Space 범위.
- 5.3 Figure Reading Note: I/L/입사각/reflect 표기. Technical Note: Normal/접선 성분 분해와 원래 수치 예시.
- 5.5 Implementation Note: 실제 성능과 교육용 Response 범위. Unit/One-sided/에너지 조건은 본문에도 남겼다.
- 5.6 Implementation Notes: L+V=0 처리 정책, 동일 n의 Lobe 폭 차이, 실제 Normalize 비용 측정.
- 5.10 Implementation Note: 0분모/앞면/Scene Vis와 G의 역할.
- 5.12 Technical Note: Solid Angle과 NDF projected-area 정규화. Model 선택 Note: Roughness 변환과 G 조합.
- 5.13 Implementation Note: G/Scene Vis/최종 Reflection의 차이.
- 5.14 Technical Note: F0의 η 관계와 수치 검산. Display Note: Schlick 근사·입사 Light·Visibility·Roughness·표시 변환·Artistic Rim의 범위.
- 5.18 Technical Note: 에너지 보존의 출사 반구 조건, 상호성, Model 합성·Parameter 범위, Multiple Scattering 보정의 Advanced 범위.

### Formula Changes

Formula의 문자내용은 바꾸지 않았다. 설명과 배치만 바꾸었다. 아래 19개 block은 원문 개수 그대로다. 동일한 비교식이 반복된 block도 삭제하지 않았다.

| Original Block | Role | Classification | Treatment |
|---|---|---|---|
| 1: 5.1 학습 경로 | Reading Flow | Essential data flow | Model 필요와 각 이름의 의미 뒤에 배치 |
| 2: 5.3 반사 ASCII 그림 | Direction Relationship | Essential | Reflection Law와 각도 기준 설명 뒤 |
| 3: 5.3 θi=θr | Reflection Law | Essential | 그림과 의미 뒤 |
| 4: 5.3 R 식/Unit 주석 | Reflection Vector | Explain First | I/L/대칭 목적을 먼저 준비 |
| 5: 5.3 성분 분해 | Vector Decomposition | Move to Technical Note | 원래 식/수치 예시 보존 |
| 6: 5.4 DiffuseDirectionFactor | Incident Cosine | Essential | 면적 분산/Unit/One-sided 관계 뒤 |
| 7: 5.5 Phong Response | Empirical Highlight | Explain First | R/V 비교와 n의 역할 뒤 |
| 8: 5.6 R 처리 흐름 | Data Flow | Essential | H가 필요한 질문 앞에서 회상 |
| 9: 5.6 H/BlinnPhongResponse | Half Vector and Response | Explain First | H 뜻·Normalize·N/H 정렬 뒤로 이동 |
| 10–11: 5.6 R≈V / N≈H | Alignment Comparison | Essential | 두 질문의 차이를 보여준 뒤 H 계산 |
| 12–13: 5.7 R≈V / N≈H | Model Comparison | Essential | 원래 반복 개수 보존, peak/lobe 구분 |
| 14: 5.10 Microfacet BRDF | D·G·F and Denominator | Explain First | 세 질문/Single Scattering/조건 뒤 |
| 15: 5.14 Schlick | Angle-dependent Reflectance | Explain First | F0/Angle/근사의 뜻 뒤 |
| 16: 5.17 BRDF Lighting Flow | Surface Response to Lighting | Essential data flow | 입력/출력/Light 비교 뒤 |
| 17: 5.18 dLo/dEi | BRDF Definition | Explain First | 미소 방향 기여/물리량을 먼저 준비 |
| 18: 5.18 Rendering Equation | Directional Contribution Sum | Explain First | 반구/적분/Emission 관계 뒤 |
| 19: 5.19 ρ/π, Lo=(ρ/π)Ei | Lambertian BRDF | Explain First | 입사 계수/반사율/정규화 필요 뒤 |

정밀 NDF 정규화, F0 optical relation, 에너지 보존 적분 조건은 원래 inline 관계를 유지하며 Notes에서 의미를 풀었다. 핵심 BRDF/Rendering Equation 자체를 제거하거나 새 Formula로 대체하지 않았다.

### Structure Changes

- Chapter H1 한 개, 5.1–5.19의 원래 H2 제목/번호/순서를 유지했다.
- English Section Title, Korean Explanation, `---`의 Concept 구분을 유지했다.
- 설명 단계를 역할이 명확한 Subsection으로 분리했다. 용어 사전의 나열을 별도 본문 구조로 만들지 않았다.
- Formula-first인 H 정의와 후반 BRDF 구간을 관계 설명 뒤로 옮겼다.
- Reflection Vector/NDF/F0/물리 제약의 정밀 설명은 네 `<details>` Technical Notes로 나눴으며 태그 균형을 확인했다.
- Reference의 Callback 기능은 이전 질문을 되짚고 남은 문제를 다음 절로 연결하는 문단으로 복원했다. 모든 소절에 generic Callback 제목을 강제하지 않았다.
- 실제 주요 개념 종료에 Key Takeaways를 사용한다. 여러 구성 요소를 묶는 Part III Summary와 전체 Chapter Summary의 역할도 유지했다.
- Chapter 06의 실제 파일 링크와 현재 Direct/Indirect/HDR/표시 범위로 다음 안내를 유지했다.

### Figure Review

Figure 5-1–5-14 태그/경로/순서/번호를 모두 보존했다. 이미지를 재생성하거나 수정하지 않았다.

- Figure 5-1: 본문에서 Diffuse/Specular/Roughness 의미를 먼저 준비한 뒤 이상적 거울 예시와 모델의 범위를 Reading Note로 구분했다.
- Figure 5-3: 그림 전 L/I 화살표를 설명했다. 기존 Caption의 I=-L/Unit N/R 식/입사각 조건을 삭제하지 않고 방향 확인 Note에 보존했다.
- Figure 5-4: 입사각 비교가 Light/Material 조건과 Direction Factor를 확인하는 그림임을 연결했다.
- Figure 5-5–5-7: Camera와 비교 방향/peak 정렬을 본문으로 연결하고 전체 Lobe가 같다는 인상을 방지했다.
- Figure 5-8–5-13: Model 범위, 큰 N과 작은 Facet Normal, 세 항의 질문, Roughness, D, Light/View 경로라는 독해 기준을 붙였다.
- Figure 5-14: Angle의 반사율 관계와 최종 화면 밝기를 구별한다.

이번 검수는 본문/Caption과 태그 보존을 확인한 것이며, 기존 PNG의 픽셀 내용이나 실제 Engine Render Capture를 새로 검증한 것은 아니다. Figure 관련 불확실성을 새 이미지로 임의 대체하지 않았다.

### Remaining Review Items

- 완성된 Chapter 01–05의 실제 최초 사용 순서를 최종 대조했다. Chapter 03/04의 preview/정식 설명을 근거로 05의 회상을 맞췄으며, 현재 Term Map에는 Chapter 05 로컬 최초 위치와 앞장 회상을 함께 기록한다.
- 독립 내용 검수에서 Main Flow와 Notes의 위치 및 즉시 반복되는 새 설명을 확인했다. Notes에 옮긴 기술 조건은 펼쳐 읽을 수 있고, 계산의 최소 조건은 본문 가까이에 남겼다.
- 기존 PNG의 시각적 정확성과 Unreal 실제 실행은 이번 작업에서 추가 검증하지 않았다.
- Smith/Schlick-GGX의 구체적 근사식이나 Parameter 변환 비교를 새로 추가하지 않았다. 정확한 구현 비교가 필요하면 선택한 Engine/Model 기준의 별도 기술 검토 범위다.
- GGX의 acronym Full Name은 확인한 원전에서 검증되지 않았으므로 만들어 쓰지 않았다. 알려진 Trowbridge–Reitz 분포 이름과 역할을 설명한다.

### Reference vs Current Technical Authority

Reference의 익숙한 현상, 질문형 progression, 한 개념씩의 설명, Formula 이후의 의미, 앞 질문 회상과 회고를 복원했다. 한국어 제목, 단어별 줄바꿈, 오래된 다음 Chapter 안내, 반복 종료 구조는 복원하지 않았다.

복원하지 않은 옛 기술 주장에는 수직 방향이 하나라는 설명, L을 실제 입사 진행과 혼동하는 Formula, Rough Specular를 Diffuse로 설명하는 방식, Lambert가 모든 방향의 Power를 동일하게 낸다는 설명, NdotL=BRDF/최종 밝기, Half Vector가 무조건 더 빠르거나 전체 Lobe가 동일하다는 단정, Mesh 전체가 하나의 Normal이라는 가정, 모든 Facet이 H를 향함, D=단일 방향의 0–1 확률, D·G·F만이 전체 BRDF, G=Scene Vis/최종 반사, Fresnel=화면 가장자리의 무조건적 밝기 증가, Flux=전체 Energy, BRDF 출력=최종 빛/0–1 비율, 단순 Highlight Response=완성된 Energy-conserving BRDF 등이 있다.

Current의 정밀 방향/단위/Model scope/에너지 조건이 Reference보다 우선한다. 비교 기준은 [초기 Reference](./Chapter05_Reflection_BRDF_ref.md), [현재 정확성의 원본 Backup](./Chapter05_Reflection_BRDF_backup.md), [재작성 원고](./Chapter05_Reflection_BRDF.md)다.

### Verified Naming Exceptions

**GGX:** 원논문은 GGX라는 이름과 분포를 제시하지만 확인된 acronym 확장명을 제공하지 않는다. PBRT는 Trowbridge–Reitz와 GGX의 이름 관계를 확인한다. 따라서 GGX(Trowbridge–Reitz Distribution)는 다른 분포 이름의 설명이며 가짜 Full Name이 아니다. [Walter et al.](https://www.graphics.cornell.edu/~bjw/microfacetbsdf.pdf), [PBRT Microfacet Theory](https://pbr-book.org/4ed/Reflection_Models/Roughness_Using_Microfacet_Theory)

**Fresnel:** 사람의 성에서 온 명칭이며 acronym이 아니다. 입사각과 광학 성질에 따른 Reflectance를 먼저 설명하고 eponym을 짧게 안내했다. [Greg A. Smith, Fresnel Equations](https://webs.optics.arizona.edu/gsmith/Fresnel.html), [PBRT Specular Reflection](https://pbr-book.org/4ed/Reflection_Models/Specular_Reflection_and_Transmission)

---

## Final Self Review

- 01–05의 개념 역할과 앞장 회상, 실제 첫 용어 노출을 대조했다. 새 용어는 필요한 문제 안에서 설명하고 Formula의 입력·목적·출력 의미를 먼저 제공했다. Reference의 한국어 제목이나 낡은 기술 주장으로 되돌리지 않았다.

- Chapter03의 개선된 Normalize/Dot/Inverse Transpose 흐름, Chapter04의 Roughness Decode 방향과 Editor/Runtime/Static 범위, Chapter05의 방향·단위·공간·BRDF/Lighting/Display 경계를 유지했다.

- 06/07은 Concept 연결, 08은 I/O·Implementation·Verification, 09는 측정 Workflow와 Precision을 기준으로 별도 평가했다. 후반 15개 원고와 Figure는 byte 단위로 동일하다.

- 남은 확인은 각 장의 대상 Engine/API 구현 조건과 기존 Figure의 실행 증거 범위다. 문서 보존 검사와 이론 예제 대조를 실제 Unreal 실행 결과로 기록하지 않았다. 독자의 연속 읽기 피드백은 다음 편집 판단에 사용할 수 있다.

## Terminology Audit Table

주요 진입 장벽 용어 163개 항목을 기록했다. 묶음 항목은 같은 설명 관계의 Term을 함께 검토한 것이다. First Appearance는 원본 Backup의 실제 위치와 문장이고, Rewrite Treatment의 최종 최초는 완성된 재작성 파일의 실제 위치다. 제목에서 첫 등장한 경우 바로 뒤 본문의 안내를 함께 확인했다.

| Chapter | Term | First Appearance | Original Problem | Rewrite Treatment |
|---|---|---|---|---|
| 01 | Rendering Pipeline | Introduction L1 — # Chapter 01 — Rendering Pipeline | 도입의 질문과 Stage 목록은 있었으나 전체 Data 연결의 의미를 더 일찍 풀 수 있었다. | 이처럼 서로 다른 문제를 맡은 처리 단계가 Data를 주고받으며 이어지는 흐름이 **Rendering Pipeline**이다. 여기서 Pipeline은 어떤 Data가 한 단계의 입력이 되고, 처리 결과가 다음 단계의 입력으로 이어지는 구조를 뜻한다. 최종 최초: Introduction L1 — # Chapter 01 — Rendering Pipeline |
| 01 | Rendering | Introduction L1 — # Chapter 01 — Rendering Pipeline | 제목에서 시작했으며 처음의 정의를 Image를 만드는 문제와 더 직접 연결할 수 있었다. | 이 Image를 만드는 일을 **Rendering**이라고 한다. 여러 물체와 관찰·조명 정보가 함께 배치된 공간은 **Scene**이다. Scene의 정보를 사용해 2D Image를 만드는 과정은 하나의 계산으로 끝나지 않는다. 형태를 준비하고, 화면 위치를 찾고, 그 위치의 표면 결과를 계산한 뒤 결과를 저장해야 한다. 최종 최초: Introduction L1 — # Chapter 01 — Rendering Pipeline |
| 01 | GPU | Introduction L5 — 실제 화면에 최종 Image를 만들려면 이러한 정보들이 연결되어야 한다. Renderer가 필요한 Data와 작업을 준비하고, GPU는 그 Data를 일정한 규칙에 따라 처리해 화면에 사용할 결과를 만든다. | 도입에서 장치 이름이 먼저 나오고 역할의 구체적인 해설까지 거리가 있었다. | 컴퓨터는 이 입력 Data를 실제 계산으로 처리한다. **GPU(Graphics Processing Unit)**는 많은 Geometry와 화면 위치의 계산을 병렬로 처리하도록 설계된 Processor, 즉 계산 장치다. GPU는 Character라는 의미를 이해하기보다, 전달된 점과 면의 Data를 정해진 Program으로 처리한다. 최종 최초: 1.1 What is Rendering? L104 — 컴퓨터는 이 입력 Data를 실제 계산으로 처리한다. **GPU(Graphics Processing Unit)**는 많은 Geometry와 화면 위치의 계산을 병렬로 처리하도록 설계된 Processor, 즉 계산 장치다. GPU는 Character라는… |
| 01 | CPU | 1.6 L2357 — Object 단위 선별은 CPU 또는 GPU에서 구현할 수 있다. 따라서 Frustum Culling이라는 이름이 Primitive Clipping처럼 하나의 고정 실행 위치를 뜻하지는 않는다. | Culling 위치의 예외 조건에서 이름이 먼저 나왔다. | 그 계산이 수행되도록 프로그램의 상태와 작업 지시를 관리하는 장치가 **CPU(Central Processing Unit)**다. Rendering에서는 CPU와 Engine이 필요한 Data와 명령을 준비하고 GPU가 전달된 작업을 수행하는 기본 관계를 생각할 수 있다. 두 장치의 연결은 1.12에서 다시 살펴본다. 최종 최초: 1.1 What is Rendering? L106 — 그 계산이 수행되도록 프로그램의 상태와 작업 지시를 관리하는 장치가 **CPU(Central Processing Unit)**다. Rendering에서는 CPU와 Engine이 필요한 Data와 명령을 준비하고 GPU가 전달된 작업을 수행하는 기본 관… |
| 01 | Vertex | Introduction L11 — Vertex는 어떻게 처리되는가, Triangle은 언제 만들어지는가, 화면 밖의 Geometry는 어떻게 제거되는가, Triangle은 어떤 과정을 통해 Pixel 후보로 바뀌는가, 그리고 최종적으로 어떤 Surface가 화면에 남는가는 모두 Ren… | 도입 질문에 이름이 먼저 등장했다. 뒤쪽 위치 Data 설명은 유지할 가치가 있었다. | Mesh의 형태를 표현하려면 먼저 꼭짓점의 위치를 저장해야 한다. 이 꼭짓점을 **Vertex**라고 한다. 세 Vertex를 연결해 만든 삼각형 면이 **Triangle**이며, Mesh는 일반적으로 여러 Vertex와 Triangle의 연결로 구성된다. 최종 최초: 1.1 What is Rendering? L102 — Mesh의 형태를 표현하려면 먼저 꼭짓점의 위치를 저장해야 한다. 이 꼭짓점을 **Vertex**라고 한다. 세 Vertex를 연결해 만든 삼각형 면이 **Triangle**이며, Mesh는 일반적으로 여러 Vertex와 Triangle의 연결로 구성… |
| 01 | Vertex Attribute | 1.1 L136 — 이러한 Vertex Data의 구조는 이후 **1.3 Vertex and Vertex Attributes**에서 자세히 살펴본다. | 1.1의 후속 Section 안내가 첫 명칭이다. Position 외 속성이 필요한 이유를 더 일찍 설명할 수 있었다. | Position 외에 어떤 색/계산 Data를 사용하는지 연결하는 개별 속성이라는 필요와 뜻을 함께 제공했다. 최종 최초: 1.1 What is Rendering? L114 — Vertex가 어디에 있는지 나타내는 값은 **Position**이다. 하지만 Position만으로는 그 위치에 어떤 색이나 데이터를 사용할지, 빛을 어느 방향으로 받을지 알 수 없다. 이러한 목적을 위해 Vertex에 함께 연결하는 속성 Data를 … |
| 01 | Triangle | Introduction L11 — Vertex는 어떻게 처리되는가, Triangle은 언제 만들어지는가, 화면 밖의 Geometry는 어떻게 제거되는가, Triangle은 어떤 과정을 통해 Pixel 후보로 바뀌는가, 그리고 최종적으로 어떤 Surface가 화면에 남는가는 모두 Ren… | 도입 질문에 명칭이 먼저 나오며 Vertex 연결의 뜻은 뒤에서 확장했다. | Mesh의 형태를 표현하려면 먼저 꼭짓점의 위치를 저장해야 한다. 이 꼭짓점을 **Vertex**라고 한다. 세 Vertex를 연결해 만든 삼각형 면이 **Triangle**이며, Mesh는 일반적으로 여러 Vertex와 Triangle의 연결로 구성된다. 최종 최초: 1.1 What is Rendering? L102 — Mesh의 형태를 표현하려면 먼저 꼭짓점의 위치를 저장해야 한다. 이 꼭짓점을 **Vertex**라고 한다. 세 Vertex를 연결해 만든 삼각형 면이 **Triangle**이며, Mesh는 일반적으로 여러 Vertex와 Triangle의 연결로 구성… |
| 01 | Primitive | Introduction L27 — → Primitive Assembly | 초기 Stage flow의 이름이 먼저였고 기본 도형 단위의 뜻은 뒤에 있었다. | 이 기본 도형 단위를 **Primitive**라고 한다. Point, Line, Triangle이 대표적인 예이며, 여기서는 Surface를 표현하는 Triangle을 중심으로 살펴본다. GPU는 Vertex와 Index Data를 이용하여 여러 Vertex를 묶고 Primitive를 구성한다. 최종 최초: 1.2 From Model to Screen L412 — ### Primitive Assembly |
| 01 | Vertex Shader | 1.3 L1283 — 다음 절에서는 Vertex Shader가 각 Vertex를 어떻게 처리하고, 특히 Vertex Position이 Rendering Pipeline 안에서 어떤 변환을 시작하는지 살펴본다. | 다음 Section 예고가 첫 명칭이다. Program과 처리 입력을 앞서 연결할 수 있었다. | 먼저 Vertex의 위치와 Attribute를 뒤의 처리에서 사용할 수 있도록 준비한다. 이 과정이 **Vertex Processing**이다. GPU에서 특정 Rendering 계산을 수행하는 Program을 **Shader**라고 하며, Vertex 입력을 처리하는 Program이 **Vertex Shader**다. 최종 최초: 1.1 What is Rendering? L304 — 먼저 Vertex의 위치와 Attribute를 뒤의 처리에서 사용할 수 있도록 준비한다. 이 과정이 **Vertex Processing**이다. GPU에서 특정 Rendering 계산을 수행하는 Program을 **Shader**라고 하며, Verte… |
| 01 | Rasterization | Introduction L17 — Chapter 01에서는 우선 기본적인 **Rasterization-based Rendering Pipeline**에 집중한다. | 도입의 Rendering 방식 이름이 먼저였다. 화면 위치를 찾는 문제는 뒤에서 설명했다. | Vertex를 연결한 Triangle의 화면 위치를 알더라도 내부 전체를 바로 색칠할 수는 없다. 화면의 어떤 위치가 그 Triangle에 의해 덮이는지 찾아야 한다. 이 판정 과정을 **Rasterization**이라고 한다. 최종 최초: 1.1 What is Rendering? L306 — Vertex를 연결한 Triangle의 화면 위치를 알더라도 내부 전체를 바로 색칠할 수는 없다. 화면의 어떤 위치가 그 Triangle에 의해 덮이는지 찾아야 한다. 이 판정 과정을 **Rasterization**이라고 한다. |
| 01 | Fragment | Introduction L31 — → Fragment / Pixel Processing | 초기 flow에서 Pixel과 병기되어 후보 Data와 최종 Pixel의 차이를 추측해야 했다. | 이렇게 찾은 위치에서 이후 Surface 계산에 사용할 후보 Data가 **Fragment**다. Fragment는 아직 Image에 남을 Pixel이 아니다. 해당 후보에서 Texture와 Material 등을 이용해 Surface 결과를 계산하는 작업이 **Fragment Processing**이다. 최종 최초: 1.1 What is Rendering? L308 — 이렇게 찾은 위치에서 이후 Surface 계산에 사용할 후보 Data가 **Fragment**다. Fragment는 아직 Image에 남을 Pixel이 아니다. 해당 후보에서 Texture와 Material 등을 이용해 Surface 결과를 계산하는 … |
| 01 | Pixel Shader | 1.2 L616 — - Pixel Shader | Stage 목록에서 이름이 먼저 보이며 API 명칭 관계를 더 일찍 연결할 수 있었다. | 이 입력을 계산하는 Program이 **Fragment Shader**다. 프로그램이 Graphics 기능을 요청하는 정해진 인터페이스를 **API(Application Programming Interface)**라고 한다. Direct3D API에서는 같은 역할의 Stage를 **Pixel Shader**라고 부른다. Pixel Processing이라는 표현도 이 화면 위치의 Surface 계산과 연결해서 사용된다. 최종 최초: 1.2 From Model to Screen L571 — 이 입력을 계산하는 Program이 **Fragment Shader**다. 프로그램이 Graphics 기능을 요청하는 정해진 인터페이스를 **API(Application Programming Interface)**라고 한다. Direct3D API에서… |
| 01 | Depth | Introduction L32 — → Depth Test | 초기 flow의 Depth Test 명칭이 먼저였고 값의 역할·거리와의 차이는 뒤에 있었다. | 이러한 앞뒤 관계를 판단하기 위해 **Depth** 정보를 사용한다. Depth는 같은 Screen 위치에서 Surface가 Camera 기준으로 앞인지 뒤인지 판단하는 값이며, 단순한 World Space 거리와 반드시 같은 값은 아니다. 최종 최초: 1.2 From Model to Screen L595 — ### Depth Test |
| 01 | Buffer | 1.2 L664 — 이 과정에서 사용하는 대표적인 Buffer가 **Depth Buffer**, 또는 **Z-Buffer**다. | Depth 저장 대상에서 명칭이 먼저 나왔다. 일반 저장 역할을 먼저 설명하면 여러 Buffer가 연결된다. | 여기서 연결 관계를 저장한 Data는 어디에 있는가? 이후 작업이 읽을 Data를 담아두는 저장 공간을 **Buffer**라고 한다. **Vertex Buffer**에는 Vertex와 Attribute Data가, **Index Buffer**에는 Vertex를 선택할 번호들이 저장된다. 이 저장 역할과 Indexed / Non-indexed Draw의 차이는 1.5에서 자세히 확인한다. 최종 최초: 1.2 From Model to Screen L433 — 여기서 연결 관계를 저장한 Data는 어디에 있는가? 이후 작업이 읽을 Data를 담아두는 저장 공간을 **Buffer**라고 한다. **Vertex Buffer**에는 Vertex와 Attribute Data가, **Index Buffer**에는 V… |
| 01 | Framebuffer | Introduction L33 — → Framebuffer | 초기 flow의 이름이 먼저였다. 개별 Color와 저장 대상 구성의 차이는 뒤에 있었다. | 이러한 여러 저장 대상을 함께 사용하도록 구성한 집합 또는 연결 구조가 **Framebuffer**다. Framebuffer는 하나의 Color 값이나 개별 Texture 이름이 아니라, 현재 Rendering 작업이 어떤 저장 대상을 사용할지 연결하는 관계다. 최종 최초: 1.2 From Model to Screen L626 — ### Framebuffer |
| 01 | Draw Call | 1.11 L5665 — 지금까지는 GPU가 Geometry를 처리해 Final Image로 연결하는 흐름을 살펴보았다. 그렇다면 GPU는 어떤 Mesh를 그릴지 어떻게 알까? CPU와 Game Engine은 Scene의 Object, Material, Shader, Buff… | 첫 문장에 요청 역할은 이미 있었다. 명령 단위와 GPU 실행의 연결을 더 분명히 할 수 있었다. | 지금까지는 GPU가 Geometry를 처리해 Final Image로 연결하는 흐름을 살펴보았다. 그렇다면 GPU는 어떤 Mesh를 그릴지 어떻게 알까? CPU와 Game Engine은 Scene의 Object, Material, Shader, Buffer 정보를 준비한다. 준비된 Geometry와 설정으로 Primitive를 그리라고 요청하는 명령 단위가 **Draw Call**이다. 다음 절에서는 CPU의 Rendering 준비와 G 최종 최초: 1.11 Framebuffer and Final Image L5668 — 지금까지는 GPU가 Geometry를 처리해 Final Image로 연결하는 흐름을 살펴보았다. 그렇다면 GPU는 어떤 Mesh를 그릴지 어떻게 알까? CPU와 Game Engine은 Scene의 Object, Material, Shader, Buff… |
| 01 | Vector | Introduction L19 — Coordinate Transformation에 필요한 수학은 Chapter 02에서, Lighting에 필요한 Vector Mathematics는 Chapter 03에서, Material과 Shader 구조는 Chapter 04에서 이어서 다룬다. | 다음 Chapter 안내에서 이름이 먼저였다. 방향 Data의 직관을 본 장에서도 사용할 필요가 있었다. | 방향을 이야기하려면 **Vector**라는 표현이 필요하다. Vector는 방향과 길이를 함께 가진 화살표로 생각할 수 있다. 표면이 어느 방향을 향하는지 나타내는 대표적인 방향 Data가 **Normal**이다. 여기서 Vertex에 저장한 Normal은 표면 표현에 사용할 방향이며, 실제 Triangle 평면에 수직인 방향과의 구분은 1.3에서 확인한다. 최종 최초: 1.1 What is Rendering? L116 — 방향을 이야기하려면 **Vector**라는 표현이 필요하다. Vector는 방향과 길이를 함께 가진 화살표로 생각할 수 있다. 표면이 어느 방향을 향하는지 나타내는 대표적인 방향 Data가 **Normal**이다. 여기서 Vertex에 저장한 Norm… |
| 01 | Normal | 1.1 L134 — Position 외에도 Normal, UV, Tangent, Vertex Color 등 여러 정보가 함께 전달될 수 있다. | Vertex 입력 목록에서 이름을 나열했다. Surface 방향 역할을 먼저 연결할 수 있었다. | 방향을 이야기하려면 **Vector**라는 표현이 필요하다. Vector는 방향과 길이를 함께 가진 화살표로 생각할 수 있다. 표면이 어느 방향을 향하는지 나타내는 대표적인 방향 Data가 **Normal**이다. 여기서 Vertex에 저장한 Normal은 표면 표현에 사용할 방향이며, 실제 Triangle 평면에 수직인 방향과의 구분은 1.3에서 확인한다. 최종 최초: 1.1 What is Rendering? L116 — 방향을 이야기하려면 **Vector**라는 표현이 필요하다. Vector는 방향과 길이를 함께 가진 화살표로 생각할 수 있다. 표면이 어느 방향을 향하는지 나타내는 대표적인 방향 Data가 **Normal**이다. 여기서 Vertex에 저장한 Norm… |
| 01 | UV | 1.1 L134 — Position 외에도 Normal, UV, Tangent, Vertex Color 등 여러 정보가 함께 전달될 수 있다. | Vertex 입력 목록에서 이름을 나열했다. Texture 위치용 두 좌표의 목적이 뒤에 있었다. | Surface의 위치에 따라 다른 색이나 값을 사용하려면 **Texture**가 필요하다. Texture는 위치별 Color 또는 계산용 Data를 저장해 두고, 필요한 위치에서 값을 읽는 자원이다. 그중 2D Texture의 어느 위치를 사용할지 나타내는 두 좌표가 **UV**다. U와 V는 두 좌표축의 이름이며 약어를 풀어 만든 명칭이 아니다. 최종 최초: 1.1 What is Rendering? L118 — Surface의 위치에 따라 다른 색이나 값을 사용하려면 **Texture**가 필요하다. Texture는 위치별 Color 또는 계산용 Data를 저장해 두고, 필요한 위치에서 값을 읽는 자원이다. 그중 2D Texture의 어느 위치를 사용할지 나… |
| 01 | Texture | 1.1 L150 — - Texture | Material Data 목록에서 이름이 먼저였다. 위치별 데이터를 읽는 목적을 미리 풀 수 있었다. | 위치별 Color/계산 Data를 저장하고 읽는 자원으로 설명했다. 의미가 먼저 나오도록 앞 Vertex Attribute 문장을 정리했다. 최종 최초: 1.1 What is Rendering? L118 — Surface의 위치에 따라 다른 색이나 값을 사용하려면 **Texture**가 필요하다. Texture는 위치별 Color 또는 계산용 Data를 저장해 두고, 필요한 위치에서 값을 읽는 자원이다. 그중 2D Texture의 어느 위치를 사용할지 나… |
| 01 | Shader | Introduction L19 — Coordinate Transformation에 필요한 수학은 Chapter 02에서, Lighting에 필요한 Vector Mathematics는 Chapter 03에서, Material과 Shader 구조는 Chapter 04에서 이어서 다룬다. | 다음 Chapter 안내에 이름이 있었다. GPU Program의 역할은 뒤에서 설명했다. | 먼저 Vertex의 위치와 Attribute를 뒤의 처리에서 사용할 수 있도록 준비한다. 이 과정이 **Vertex Processing**이다. GPU에서 특정 Rendering 계산을 수행하는 Program을 **Shader**라고 하며, Vertex 입력을 처리하는 Program이 **Vertex Shader**다. 최종 최초: 1.1 What is Rendering? L144 — ASF, 즉 이 문서에서 구축할 Anime Shader Framework의 표면 표현도 이 역할과 연결된다. Anime Shader는 Anime의 표현 의도에 맞게 Surface 결과를 계산하는 Program이며, 뒤쪽 Chapter에서 반사 모델과 … |
| 01 | Index | 1.2 L418 — - Index Data | Vertex 연결 Data의 이름이 먼저 보였다. 선택 번호의 재사용 목적을 더 일찍 연결할 수 있었다. | - **Index Data** — 특정 Vertex를 가리키는 번호들의 연결 정보 최종 최초: 1.2 From Model to Screen L368 — - **Index Data** — 특정 Vertex를 가리키는 번호들의 연결 정보 |
| 01 | Coordinate Space | 1.2 L440 — 대표적으로 Vertex Position은 여러 Coordinate Space를 거치면서 최종적으로 Camera와 Screen을 기준으로 사용할 수 있는 형태로 변환된다. | 기준 변환의 예고였다. 숫자가 어느 기준에 속하는지 먼저 설명할 수 있었다. | Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Space**이며, Camera의 관찰 기준으로 표현하는 공간은 **View Space**다. 하나씩 기준을 바꾸며 같은 Vertex를 화면에 사용할 형태로 표현한다. 최종 최초: 1.2 From Model to Screen L392 — Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Spa… |
| 01 | Local Space | 1.2 L442 — 예를 들어 처음 Mesh 안에 저장되어 있던 Vertex Position은 Object 자체의 Local Space를 기준으로 표현될 수 있다. | 기준 목록에서 처음 보였다. Object의 형태와 Scene 배치를 분리하는 뜻을 미리 풀 수 있었다. | Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Space**이며, Camera의 관찰 기준으로 표현하는 공간은 **View Space**다. 하나씩 기준을 바꾸며 같은 Vertex를 화면에 사용할 형태로 표현한다. 최종 최초: 1.2 From Model to Screen L392 — Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Spa… |
| 01 | World Space | 1.3 L947 — 다만 여기서 중요한 점은 이 Position이 항상 World Space의 위치를 의미하는 것은 아니라는 것이다. | 기준 목록에서 처음 보였다. 공통 Scene 기준의 필요를 함께 안내할 수 있었다. | Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Space**이며, Camera의 관찰 기준으로 표현하는 공간은 **View Space**다. 하나씩 기준을 바꾸며 같은 Vertex를 화면에 사용할 형태로 표현한다. 최종 최초: 1.2 From Model to Screen L392 — Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Spa… |
| 01 | View Space | 1.3 L958 — → View Space | 기준 목록에서 처음 보였다. Camera 기준의 역할을 함께 안내할 수 있었다. | Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Space**이며, Camera의 관찰 기준으로 표현하는 공간은 **View Space**다. 하나씩 기준을 바꾸며 같은 Vertex를 화면에 사용할 형태로 표현한다. 최종 최초: 1.2 From Model to Screen L392 — Position을 어떤 기준에서 표현하는지 정하는 공간이 **Coordinate Space**다. Mesh 내부 위치처럼 Object 자체를 기준으로 한 표현은 **Local Space**라고 한다. Scene 전체의 공통 기준은 **World Spa… |
| 01 | Clip Space | 1.3 L959 — → Clip Space | 기준/Stage 이름이 먼저였다. 범위 판정용 표현이라는 역할을 미리 알려줄 수 있었다. | Camera가 고려할 영역의 경계에서 Geometry를 자르려면 그 판정에 사용할 좌표 형태가 필요하다. 이 목적의 표현이 **Clip Space**다. 이후 화면 위치로 대응하기 전에 거치는 표현이며, Clip Space가 최종 Pixel 좌표라는 뜻은 아니다. 최종 최초: 1.3 Vertex and Vertex Attributes L938 — Camera가 고려할 영역의 경계에서 Geometry를 자르려면 그 판정에 사용할 좌표 형태가 필요하다. 이 목적의 표현이 **Clip Space**다. 이후 화면 위치로 대응하기 전에 거치는 표현이며, Clip Space가 최종 Pixel 좌표라는 … |
| 01 | Transform | Introduction L19 — Coordinate Transformation에 필요한 수학은 Chapter 02에서, Lighting에 필요한 Vector Mathematics는 Chapter 03에서, Material과 Shader 구조는 Chapter 04에서 이어서 다룬다. | 다음 Chapter의 변환 수학 예고가 먼저였다. 기준을 바꿔 표현하는 목적을 연결할 수 있었다. | 이처럼 위치·회전·크기와 표현 기준의 관계를 반영해 값을 바꾸는 처리가 **Transform**이다. **Coordinate Transformation**은 서로 다른 Coordinate Space 사이에서 값을 변환하는 과정을 뜻한다. Vertex Shader는 필요한 이러한 처리를 수행해 다음 단계의 Position을 준비한다. 최종 최초: 1.2 From Model to Screen L394 — 이처럼 위치·회전·크기와 표현 기준의 관계를 반영해 값을 바꾸는 처리가 **Transform**이다. **Coordinate Transformation**은 서로 다른 Coordinate Space 사이에서 값을 변환하는 과정을 뜻한다. Vertex … |
| 01 | Projection | 1.1 L213 — - Perspective Projection | Camera 입력/변환 이름이 먼저 보였다. 관찰 범위와 투영 크기의 문제를 미리 연결할 수 있었다. | 여기서 **Projection**은 Camera가 관찰하는 공간 정보를 화면에 사용할 좌표 형태로 대응시키는 처리를 뜻한다. 두 방식의 수학적 관계는 Chapter 02에서 다룬다. 최종 최초: 1.1 What is Rendering? L203 — - **Perspective Projection**은 가까운 부분을 크게, 먼 부분을 작게 보이도록 공간을 화면에 대응시키는 방식이다. |
| 01 | Matrix | 1.4 L1392 — 각 Space의 정확한 의미와 Matrix Transformation은 Chapter 02에서 자세히 다룬다. | Position 변환 도구의 이름이 먼저였다. 규칙을 반복 적용하는 목적을 짧게 준비할 수 있었다. | 각 Space의 정확한 의미와 **Matrix Transformation**은 Chapter 02에서 자세히 다룬다. Matrix는 변환에 사용할 여러 수를 행과 열로 배열한 구조이며, Matrix Transformation은 이 수들의 관계를 이용해 Position이나 Direction을 바꾸는 계산이다. 여기서는 변환이 필요한 목적부터 이해하고, Matrix의 구성과 계산은 다음 Chapter에서 연결한다. 최종 최초: 1.4 Vertex Processing L1381 — 각 Space의 정확한 의미와 **Matrix Transformation**은 Chapter 02에서 자세히 다룬다. Matrix는 변환에 사용할 여러 수를 행과 열로 배열한 구조이며, Matrix Transformation은 이 수들의 관계를 이용해… |
| 01 | Homogeneous Coordinate | 1.4 L1458 — Perspective Projection과 Homogeneous Coordinate까지 연결되기 때문에 자세한 내용은 Chapter 02에서 별도로 다룬다. | 변환/Clip 표현의 전문 명칭이 먼저였다. w를 사용하는 이유를 예고할 수 있었다. | **Homogeneous Coordinate**는 위치의 XYZ와 함께 W 성분을 사용하는 좌표 표현이다. 이 표현은 위치를 옮기는 변환과 Projection을 연결하는 데 사용된다. Chapter 01에서는 W로 어떤 계산을 하는지보다 Clip Space가 아직 화면 Pixel 좌표가 아니라는 점을 먼저 이해한다. 최종 최초: 1.4 Vertex Processing L1447 — **Homogeneous Coordinate**는 위치의 XYZ와 함께 W 성분을 사용하는 좌표 표현이다. 이 표현은 위치를 옮기는 변환과 Projection을 연결하는 데 사용된다. Chapter 01에서는 W로 어떤 계산을 하는지보다 Clip Sp… |
| 01 | Dot Product | 1.3 L997 — Normal의 정확한 의미와 Dot Product를 이용한 Lighting 계산은 뒤쪽 Chapter에서 더 자세히 다룬다. | 방향 관계에서 계산 이름이 먼저였다. 정렬 정도를 숫자로 비교하는 목적을 붙일 수 있었다. | 두 방향이 얼마나 같은 쪽을 향하는지 숫자로 나타내는 계산이 **Dot Product**다. Normal의 정확한 의미와 Dot Product를 이용한 Lighting 계산은 Chapter 03에서 더 자세히 다룬다. 최종 최초: 1.3 Vertex and Vertex Attributes L986 — 두 방향이 얼마나 같은 쪽을 향하는지 숫자로 나타내는 계산이 **Dot Product**다. Normal의 정확한 의미와 Dot Product를 이용한 Lighting 계산은 Chapter 03에서 더 자세히 다룬다. |
| 01 | Tangent | 1.1 L134 — Position 외에도 Normal, UV, Tangent, Vertex Color 등 여러 정보가 함께 전달될 수 있다. | Vertex 속성 목록에서 이름이 먼저였다. Surface 위의 기준 방향을 먼저 풀 수 있었다. | **Tangent**는 Surface 위를 따라가는 기준 방향이고, **Vertex Color**는 Vertex마다 Color나 특정 효과에 사용할 Data를 저장하는 Attribute다. 이처럼 Position 외에도 Normal, UV, Tangent, Vertex Color 등 여러 정보가 함께 전달될 수 있다. 최종 최초: 1.1 What is Rendering? L120 — **Tangent**는 Surface 위를 따라가는 기준 방향이고, **Vertex Color**는 Vertex마다 Color나 특정 효과에 사용할 Data를 저장하는 Attribute다. 이처럼 Position 외에도 Normal, UV, Tange… |
| 01 | Normal Mapping | 1.3 L918 — - Tangent는 Normal Mapping에 필요한 기준 방향을 제공하며, | Normal 입력 예외에서 이름을 사용했다. Texture로 Shading 방향을 바꾸는 역할을 먼저 설명할 수 있었다. | **Normal Mapping**은 Geometry를 더 늘리지 않고 Texture에 저장한 방향 Data를 이용해 Lighting에 사용할 Normal을 세밀하게 바꾸는 방법이다. 이 방향 Data를 담은 Texture가 **Normal Map**이다. 최종 최초: 1.3 Vertex and Vertex Attributes L1037 — **Normal Mapping**은 Geometry를 더 늘리지 않고 Texture에 저장한 방향 Data를 이용해 Lighting에 사용할 Normal을 세밀하게 바꾸는 방법이다. 이 방향 Data를 담은 Texture가 **Normal Map**이… |
| 01 | Tangent Space | 1.3 L1048 — 대신 Surface를 기준으로 한 **Tangent Space**에서 표현되는 경우가 많다. | Normal 입력에서 이름이 먼저였다. Surface에 붙은 방향 기준의 뜻을 미리 풀 수 있었다. | Normal Map의 방향은 Surface를 기준으로 한 **Tangent Space**에서 표현되는 경우가 많다. Tangent Space는 표면을 따라가는 기준 방향과 Normal 방향으로 구성한 지역적인 좌표 기준이다. 같은 Texture Data라도 Surface가 Scene에서 어느 방향으로 놓였는지에 맞게 해석해야 Lighting 방향으로 사용할 수 있다. 최종 최초: 1.3 Vertex and Vertex Attributes L1041 — Normal Map의 방향은 Surface를 기준으로 한 **Tangent Space**에서 표현되는 경우가 많다. Tangent Space는 표면을 따라가는 기준 방향과 Normal 방향으로 구성한 지역적인 좌표 기준이다. 같은 Texture Dat… |
| 01 | Barycentric Coordinate | 1.8 L3364 — ### Barycentric Coordinate | Interpolation 설명에서 전문 이름이 나왔다. 세 꼭짓점의 기여 비율로 연결하면 쉬워진다. | 여기서 등장하는 용어가 **Barycentric Coordinate**다. 최종 최초: 1.8 Interpolation L3320 — 어떤 Vertex 쪽에 가까운 위치를 표현한다면 그 Vertex의 값이 더 많이 기여한다고 생각할 수 있다. 이렇게 Triangle 내부의 위치를 세 꼭짓점의 기여 비율로 표현하는 Weight가 **Barycentric Weight**다. 같은 의미를… |
| 01 | Unit Vector | 해당 English 명칭은 원본에 없음 | 방향 처리 조건에서 이름이 나왔다. 길이 1이 필요한 비교 목적을 먼저 연결할 수 있었다. | 방향만 비교하려면 Vector의 길이가 계산에 섞이지 않도록 기준 길이를 정할 필요가 있다. **Unit Vector**는 길이가 1인 Vector다. **Normalize**는 방향을 유지하면서 Vector의 길이를 1로 맞추는 처리다. 최종 최초: 1.8 Interpolation L3594 — 방향만 비교하려면 Vector의 길이가 계산에 섞이지 않도록 기준 길이를 정할 필요가 있다. **Unit Vector**는 길이가 1인 Vector다. **Normalize**는 방향을 유지하면서 Vector의 길이를 1로 맞추는 처리다. |
| 01 | Normalize | 1.8 L3613 — 따라서 Lighting 계산 전에 다시 **Normalize**할 수 있다. | Normal 처리에서 연산 이름이 먼저였다. 방향을 유지하고 길이를 맞추는 목적을 붙일 수 있었다. | 방향만 비교하려면 Vector의 길이가 계산에 섞이지 않도록 기준 길이를 정할 필요가 있다. **Unit Vector**는 길이가 1인 Vector다. **Normalize**는 방향을 유지하면서 Vector의 길이를 1로 맞추는 처리다. 최종 최초: 1.8 Interpolation L3594 — 방향만 비교하려면 Vector의 길이가 계산에 섞이지 않도록 기준 길이를 정할 필요가 있다. **Unit Vector**는 길이가 1인 Vector다. **Normalize**는 방향을 유지하면서 Vector의 길이를 1로 맞추는 처리다. |
| 01 | Sample | 1.2 L544 — Rasterization은 Screen에 투영된 Triangle을 기준으로, 해당 Triangle이 화면의 어떤 Sample 또는 Pixel 영역을 덮고 있는지 판단한다. | 화면 후보와 Coverage 관계에서 이름을 사용했다. Pixel 안 평가 위치의 역할을 더 일찍 풀 수 있었다. | Rasterization은 Screen에 투영된 Triangle을 기준으로, 해당 Triangle이 화면의 어떤 위치를 덮고 있는지 판단한다. 여기서 판정에 사용할 대표 위치가 **Sample**이며, Triangle이 그 위치를 덮는가에 대한 결과를 **Coverage**라고 한다. 최종 최초: 1.2 From Model to Screen L500 — Rasterization은 Screen에 투영된 Triangle을 기준으로, 해당 Triangle이 화면의 어떤 위치를 덮고 있는지 판단한다. 여기서 판정에 사용할 대표 위치가 **Sample**이며, Triangle이 그 위치를 덮는가에 대한 결과를… |
| 01 | Coverage | 1.7 L2680 — Coverage 판정 | Rasterization 판정에서 이름이 나왔다. Primitive가 평가 위치를 덮는가라는 뜻을 더 명확히 풀 수 있었다. | Rasterization은 Screen에 투영된 Triangle을 기준으로, 해당 Triangle이 화면의 어떤 위치를 덮고 있는지 판단한다. 여기서 판정에 사용할 대표 위치가 **Sample**이며, Triangle이 그 위치를 덮는가에 대한 결과를 **Coverage**라고 한다. 최종 최초: 1.2 From Model to Screen L500 — Rasterization은 Screen에 투영된 Triangle을 기준으로, 해당 Triangle이 화면의 어떤 위치를 덮고 있는지 판단한다. 여기서 판정에 사용할 대표 위치가 **Sample**이며, Triangle이 그 위치를 덮는가에 대한 결과를… |
| 01 | GBuffer | 1.2 L682 — 실제 Modern Rendering에서는 여러 Render Target, Depth Buffer, GBuffer 등 더 복잡한 구조가 사용될 수 있다. | 후속 Lighting 저장 경로에서 명칭을 사용했다. Full Name과 최종 Lighting이 아닌 입력 저장을 먼저 연결할 수 있었다. | 어떤 작업은 최종 Lighting Color 대신 Normal이나 Material Data를 먼저 기록한다. 이 Surface 정보를 뒤의 Lighting 계산에서 소비하는 방식이 **Deferred Rendering**이다. 이때 후속 계산에 필요한 Geometry / Surface 정보를 저장하는 Buffer 묶음을 **GBuffer(Geometry Buffer)**라고 한다. 지금은 계산 결과가 다음 계산의 입력으로 저장될 수 있 최종 최초: 1.2 From Model to Screen L640 — 어떤 작업은 최종 Lighting Color 대신 Normal이나 Material Data를 먼저 기록한다. 이 Surface 정보를 뒤의 Lighting 계산에서 소비하는 방식이 **Deferred Rendering**이다. 이때 후속 계산에 필요한… |
| 01 | BRDF | 1.1 L156 — ASF에서 뒤쪽 Chapter에서 다루는 BRDF나 Anime Shader 역시 결국 이 Surface Appearance를 계산하는 Rendering 영역과 연결된다. | Lighting 경로의 정밀 용어가 먼저였다. Full Name과 Surface 응답 역할을 preview할 수 있었다. | 서로 다른 반사 모델을 공통된 방향 관계로 표현하는 함수가 **BRDF(Bidirectional Reflectance Distribution Function)**다. BRDF는 들어오는 빛의 방향과 나가는 관찰 방향에 따라 Surface가 빛을 얼마나 반사하는지 표현한다. 이후 Chapter의 Lambert Lighting, Phong Specular, BRDF 설명도 이 Surface Shading 계산과 연결된다. 최종 최초: 1.9 Fragment / Pixel Processing L4121 — 서로 다른 반사 모델을 공통된 방향 관계로 표현하는 함수가 **BRDF(Bidirectional Reflectance Distribution Function)**다. BRDF는 들어오는 빛의 방향과 나가는 관찰 방향에 따라 Surface가 빛을 얼마나… |
| 01 | MSAA | 1.7 L2820 — Anti-Aliasing에서 사용하는 **MSAA**처럼 하나의 Pixel에 여러 Sample을 사용하는 경우도 있지만, 이 부분은 Chapter 01의 범위를 넘어가므로 여기서는 기본 개념만 알아둔다. | Sample/Pixel 예외 조건에서 약어를 사용했다. Full Name과 여러 Coverage Sample의 목적을 미리 풀 수 있었다. | 화면의 유한한 Pixel 격자 때문에 경계가 계단처럼 보이는 현상을 줄이는 처리가 **Anti-Aliasing**이다. **MSAA(Multisample Anti-Aliasing)**는 하나의 Pixel에 여러 Sample을 사용해 이러한 경계 표현을 개선하는 방식과 연결된다. 최종 최초: 1.7 Rasterization L2806 — 화면의 유한한 Pixel 격자 때문에 경계가 계단처럼 보이는 현상을 줄이는 처리가 **Anti-Aliasing**이다. **MSAA(Multisample Anti-Aliasing)**는 하나의 Pixel에 여러 Sample을 사용해 이러한 경계 표현을… |
| 01 | Winding Order | 1.5 L2028 — ### Winding Order | 면 방향 규칙에서 이름이 먼저였다. Vertex 연결 순서를 뜻한다는 말을 먼저 제공할 수 있었다. | 이러한 Vertex의 순서를 **Winding Order**라고 한다. 최종 최초: 1.5 Primitive Assembly L2013 — ### Winding Order |
| 01 | DCC | 1.5 L2043 — 일반적으로 DCC Tool에서는 다음과 같은 기능을 이용해 Surface 방향을 시각적으로 확인한다. | Asset/Normal 관련 도구 범위에서 약어를 사용했다. 제작 도구의 역할을 설명할 수 있었다. | 일반적으로 **DCC(Digital Content Creation) Tool**, 즉 모델링과 콘텐츠 제작 도구에서는 다음과 같은 기능을 이용해 Surface 방향을 시각적으로 확인한다. 최종 최초: 1.5 Primitive Assembly L2028 — 일반적으로 **DCC(Digital Content Creation) Tool**, 즉 모델링과 콘텐츠 제작 도구에서는 다음과 같은 기능을 이용해 Surface 방향을 시각적으로 확인한다. |
| 01 | LOD | 1.12 L6377 — 이 관계는 Chapter 09의 9.6 Draw Call Cost와 9.7 LOD and Culling에서 다시 연결한다. | 비용 예고에서 약어가 먼저였다. 상세도 선택의 목적을 예고 위치에 붙일 수 있었다. | 1.12의 최초 비용 예고에서 Level of Detail과 Geometry 상세도를 조절하는 목적을 함께 설명했다. 최종 최초: 1.12 CPU, GPU and Draw Calls L6384 — 뒤에서는 관찰 조건에 맞는 Geometry의 세부 수준을 선택하는 LOD(Level of Detail)도 살펴본다. 여기서는 준비할 Geometry가 달라지면 GPU에 전달할 작업도 달라질 수 있다는 연결만 확인한다. 이 관계는 Chapter 09의 … |
| 01 | Overdraw | 1.10 L4997 — Transparency와 Overdraw의 자세한 내용은 **Chapter 09 - Rendering Debug and Optimization**에서 다시 다룬다. | 반복 처리 비용에서 명칭이 나왔다. 동일 화면 위치가 여러 번 처리되는 의미를 붙일 수 있었다. | 같은 화면 위치가 여러 Surface의 계산을 반복해 받는 현상이 **Overdraw**다. Transparency와 Overdraw의 자세한 내용은 **Chapter 09 - Rendering Debug and Optimization**에서 다시 다룬다. 최종 최초: 1.10 Depth Test and Surface Visibility L4986 — 같은 화면 위치가 여러 Surface의 계산을 반복해 받는 현상이 **Overdraw**다. Transparency와 Overdraw의 자세한 내용은 **Chapter 09 - Rendering Debug and Optimization**에서 다시 다… |
| 01 | Bottleneck | 1.12 L6193 — 따라서 Draw Call이 지나치게 많아지면 GPU가 충분히 빠르더라도 CPU 쪽 Rendering Preparation이 Bottleneck이 될 수 있다. | 최적화/처리 비용에서 이름을 사용했다. 전체 진행을 제한하는 작업이라는 의미를 연결할 수 있었다. | 어떤 계산이 빨라도 그 작업을 지시하는 준비가 늦으면 Frame 전체가 늦어질 수 있다. 이처럼 현재 전체 진행을 제한하는 작업을 **Bottleneck**이라고 한다. Draw Call의 제출 작업은 GPU가 Vertex와 Fragment를 계산하는 비용과는 조금 다른 종류의 Cost를 가진다. 최종 최초: 1.12 CPU, GPU and Draw Calls L6193 — 어떤 계산이 빨라도 그 작업을 지시하는 준비가 늦으면 Frame 전체가 늦어질 수 있다. 이처럼 현재 전체 진행을 제한하는 작업을 **Bottleneck**이라고 한다. Draw Call의 제출 작업은 GPU가 Vertex와 Fragment를 계산하는… |
| 01 | Parameter | 1.9 L3913 — Figure 1-9는 Rasterization과 Interpolation을 거친 Fragment Data가 Fragment Shader에 입력되고, Texture Sampling, Material Parameter, Lighting, Emission … | 1.9 Figure 설명이 첫 명칭이며 이름보다 의미가 늦었다. | 1.9의 Figure 앞에서 조절 가능한 이름 붙은 입력값이라는 뜻을 제공했다. 최종 최초: 1.9 Fragment / Pixel Processing L3878 — 이번 절에서는 입력을 읽는 일, Material의 특성을 계산하는 일, 출력 Data를 다음 작업에 넘기는 일을 나누어 살펴본다. Texture에서 위치마다 값을 읽을 수도 있고, 외부에서 조절할 값을 입력으로 제공할 수도 있다. 이렇게 외부에 노출한… |
| 01 | Scalar | 1.9 L4095 — 예를 들어 Roughness를 Texture에서 읽지 않고 Scalar Parameter 하나로 지정할 수도 있다. | 계산 입력에서 이름을 사용했다. 숫자 하나라는 Data 형식을 먼저 풀 수 있었다. | 예를 들어 Roughness를 Texture에서 읽지 않고 **Scalar Parameter** 하나로 지정할 수도 있다. Parameter는 외부에서 설정해 계산에 사용하는 입력이고, **Scalar**는 하나의 숫자 값이다. 여러 위치에 같은 Roughness를 쓰고 싶다면 이런 한 값의 입력을 사용할 수 있다. 최종 최초: 1.9 Fragment / Pixel Processing L4070 — 예를 들어 Roughness를 Texture에서 읽지 않고 **Scalar Parameter** 하나로 지정할 수도 있다. Parameter는 외부에서 설정해 계산에 사용하는 입력이고, **Scalar**는 하나의 숫자 값이다. 여러 위치에 같은 Ro… |
| 02 | Coordinate System | Chapter opening L1 — # Chapter 02 — Coordinate System | 제목에서 시작하며 기존 기준 설명은 있었다. 도입을 기준이 필요한 현실 문제로 더 천천히 연결할 수 있었다. | Origin/Axis로 숫자의 측정 기준을 정해야 한다는 문제와 함께 짧게 의미를 제공한다. 최종 최초: Introduction L1 — # Chapter 02 — Coordinate System |
| 02 | Coordinate Space | Chapter opening L3 — Chapter 01에서는 Geometry Data가 Rendering Pipeline을 거쳐 2D Image가 되는 흐름을 살펴보았다. 이번 Chapter에서는 그 과정에서 사용하는 Coordinate Space와 변환을 자세히 다룬다. | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | 같은 Data를 어떤 기준으로 표현했는지 나타내는 말로 설명하고 Space별 목적을 하나씩 전개한다. 최종 최초: Introduction L9 — 이 Data가 현재 어떤 기준으로 표현되어 있는지 나타내는 말이 **Coordinate Space**다. Chapter 01에서 본 Local Space는 Object 자체의 기준이고, World Space는 Scene 안의 관계를 비교하는 공통 기준… |
| 02 | Local Space | Chapter opening L8 — Local Space → World Space → View Space → Clip Space → NDC → Screen Space | 도입 flow에 이름이 먼저였다. 앞 Chapter의 정의와 원래 2.3의 목적 설명을 회고해 연결할 수 있었다. | Chapter01의 Object 기준을 짧게 연결하고 Mesh 형태와 Scene 배치를 분리하는 이유로 확장한다. 최종 최초: Introduction L9 — 이 Data가 현재 어떤 기준으로 표현되어 있는지 나타내는 말이 **Coordinate Space**다. Chapter 01에서 본 Local Space는 Object 자체의 기준이고, World Space는 Scene 안의 관계를 비교하는 공통 기준… |
| 02 | World Space | Chapter opening L8 — Local Space → World Space → View Space → Clip Space → NDC → Screen Space | 도입 flow에 이름이 먼저였다. 앞 Chapter의 공통 기준 설명과 원래 2.4의 목적을 유지할 가치가 있었다. | 서로 다른 Object/Light/Camera의 관계를 공통 기준에서 비교해야 하는 문제로 설명한다. 최종 최초: Introduction L9 — 이 Data가 현재 어떤 기준으로 표현되어 있는지 나타내는 말이 **Coordinate Space**다. Chapter 01에서 본 Local Space는 Object 자체의 기준이고, World Space는 Scene 안의 관계를 비교하는 공통 기준… |
| 02 | View Space | Chapter opening L8 — Local Space → World Space → View Space → Clip Space → NDC → Screen Space | 도입 flow에 이름이 먼저였다. 앞 Chapter의 Camera 기준을 회고하고 현재 변환 목적을 연결할 수 있었다. | Camera에서 본 상대적인 3D 위치를 만들기 위한 기준임을 밝힌다. 최종 최초: Introduction L9 — 이 Data가 현재 어떤 기준으로 표현되어 있는지 나타내는 말이 **Coordinate Space**다. Chapter 01에서 본 Local Space는 Object 자체의 기준이고, World Space는 Scene 안의 관계를 비교하는 공통 기준… |
| 02 | Clip Space | Chapter opening L8 — Local Space → World Space → View Space → Clip Space → NDC → Screen Space | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | 화면 좌표 전에 Camera 범위 밖 Geometry를 정리하는 표현으로 짧게 안내한 뒤 w 의존 경계를 설명한다. 최종 최초: Introduction L11 — Camera의 3D 위치를 실제 화면과 연결할 때는 중간 단계가 더 필요하다. **Clip Space**는 투영 결과를 Camera 범위와 비교해 Geometry를 잘라내기 위한 표현이다. 그다음 **NDC(Normalized Device Coordi… |
| 02 | NDC | Chapter opening L8 — Local Space → World Space → View Space → Clip Space → NDC → Screen Space | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | Normalized Device Coordinates와 해상도 전 공통 범위라는 목적을 최초 Pipeline diagram 앞에서 설명한다. 최종 최초: Introduction L11 — Camera의 3D 위치를 실제 화면과 연결할 때는 중간 단계가 더 필요하다. **Clip Space**는 투영 결과를 Camera 범위와 비교해 Geometry를 잘라내기 위한 표현이다. 그다음 **NDC(Normalized Device Coordi… |
| 02 | Homogeneous Coordinate | 2.2 L1073 — 이 차이는 이후 Homogeneous Coordinate와 Matrix Transform을 배울 때 다음과 연결된다. | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | w를 더한 표현으로 Translation의 참여와 투영 이후 비율을 연결하는 도구라고 첫 언급에서 풀어 설명한다. 최종 최초: 2.2 Position, Direction and Vector L941 — 이 차이는 이후 Homogeneous Coordinate와 Matrix Transform을 배울 때 다음과 연결된다. Homogeneous Coordinate는 XYZ에 w를 더해 변환을 이어가는 좌표 표현이다. 여기서는 같은 Matrix에서 Tran… |
| 02 | Matrix | Chapter opening L11 — 이 흐름을 따라 Position이 변환되는 이유와 Matrix의 역할을 살펴보고, Direction / Normal의 변환 차이와 Tangent Space를 연결한다. 목표는 공식을 외우는 것이 아니라 각 Data의 기준과 변환 목적을 이해하는 것이다… | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | 여러 Vertex에 같은 변환 규칙을 반복 적용하는 도구로 소개하고 문제/수치 결과를 본 뒤 배열과 곱으로 연결한다. 최종 최초: Introduction L17 — 기준을 바꾸거나 Object의 위치·방향·크기를 바꾸는 과정을 **Transform(변환)**이라고 한다. **Matrix**는 그 변환 규칙을 숫자로 담아 여러 입력에 일관되게 적용하는 도구다. Matrix의 모양부터 외우기보다, 먼저 변환 전후에 … |
| 02 | Transform | Chapter opening L11 — 이 흐름을 따라 Position이 변환되는 이유와 Matrix의 역할을 살펴보고, Direction / Normal의 변환 차이와 Tangent Space를 연결한다. 목표는 공식을 외우는 것이 아니라 각 Data의 기준과 변환 목적을 이해하는 것이다… | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | 위치/방향/크기를 바꾸거나 다른 기준으로 표현하는 변환이며 무엇을 유지/변경하는지가 먼저라고 설명한다. 최종 최초: Introduction L17 — 기준을 바꾸거나 Object의 위치·방향·크기를 바꾸는 과정을 **Transform(변환)**이라고 한다. **Matrix**는 그 변환 규칙을 숫자로 담아 여러 입력에 일관되게 적용하는 도구다. Matrix의 모양부터 외우기보다, 먼저 변환 전후에 … |
| 02 | Basis | 2.14 L9896 — ### TBN Basis | TBN 소제목에서 이름이 먼저였다. 성분을 해석할 기준 방향의 필요를 일찍 예고할 수 있었다. | 성분이 어느 방향을 얼마나 사용하는지 읽기 위한 기준 방향들의 묶음으로 즉시 설명한다. 최종 최초: 2.1 Why Coordinate Systems Matter L143 — 이렇게 방향 성분을 해석하는 기준 방향의 묶음을 Basis라고 한다. 세 방향의 머리글자를 묶은 TBN(Tangent, Bitangent, Normal)은 이후 Normal Map의 방향을 다른 Space로 옮기는 데 사용한다. 자세한 구성과 변환은 … |
| 02 | Tangent | Chapter opening L11 — 이 흐름을 따라 Position이 변환되는 이유와 Matrix의 역할을 살펴보고, Direction / Normal의 변환 차이와 Tangent Space를 연결한다. 목표는 공식을 외우는 것이 아니라 각 Data의 기준과 변환 목적을 이해하는 것이다… | 앞 Chapter에서 Surface 기준 방향을 소개했다. 원문에서는 후속 이름 예고와 방향 목록이 먼저 보였다. | Surface 위의 기준 방향임을 미리 풀고 Normal Map의 Surface 기준 문제에서 T/B/N로 확장한다. 최종 최초: Introduction L19 — Position은 “어디에 있는가”, Direction은 “어느 쪽을 향하는가”에 답한다. 두 값이 모두 XYZ여도 필요한 변환은 다를 수 있다. Surface에 붙은 방향 기준인 Tangent Space까지 연결한 뒤, Unreal Material의… |
| 02 | Bitangent | 2.2 L1182 — Bitangent | 방향 목록의 이름이 먼저였고 Surface 위의 두 번째 기준 역할은 뒤에 있었다. | Surface 위에서 Tangent와 구분되는 두 번째 기준 방향을 먼저 밝힌다. 최종 최초: 2.1 Why Coordinate Systems Matter L141 — Chapter 01의 Tangent는 Surface를 따라가는 기준 방향이었다. 그와 구분되는 Surface 위의 두 번째 기준 방향이 Bitangent다. 여기에 Surface가 기본적으로 향하는 Normal을 더하면 방향을 읽을 세 기준이 준비된다… |
| 02 | TBN | 2.14 L9862 — 이 절에서는 Surface의 T/B/N 기준부터 읽고, Normal Map의 Encoding을 분리해서 이해한 뒤 **TBN**을 변환 도구로 연결한다. Geometric Normal과 Shading Normal의 구분은 2.13을 그대로 유지한다. | 원문 2.14 도입에 약어가 먼저였다. 앞선 Space 예고에서 각 방향을 단계적으로 준비할 수 있었다. | Tangent, Bitangent, Normal의 머리글자와 세 방향이 왜 필요하며 변환에 어떻게 쓰이는지 설명한다. 최종 최초: 2.1 Why Coordinate Systems Matter L143 — 이렇게 방향 성분을 해석하는 기준 방향의 묶음을 Basis라고 한다. 세 방향의 머리글자를 묶은 TBN(Tangent, Bitangent, Normal)은 이후 Normal Map의 방향을 다른 Space로 옮기는 데 사용한다. 자세한 구성과 변환은 … |
| 02 | Position | Chapter opening L11 — 이 흐름을 따라 Position이 변환되는 이유와 Matrix의 역할을 살펴보고, Direction / Normal의 변환 차이와 Tangent Space를 연결한다. 목표는 공식을 외우는 것이 아니라 각 Data의 기준과 변환 목적을 이해하는 것이다… | 앞 Chapter에서 소개되었고 본 장의 정의도 있었다. Translation과 Direction 차이의 사례를 더 연결할 수 있었다. | Origin에서 측정한 위치와 붙어 있는 화살표 방향의 차이를 예로 설명한다. 최종 최초: Introduction L19 — Position은 “어디에 있는가”, Direction은 “어느 쪽을 향하는가”에 답한다. 두 값이 모두 XYZ여도 필요한 변환은 다를 수 있다. Surface에 붙은 방향 기준인 Tangent Space까지 연결한 뒤, Unreal Material의… |
| 02 | Direction | Chapter opening L11 — 이 흐름을 따라 Position이 변환되는 이유와 Matrix의 역할을 살펴보고, Direction / Normal의 변환 차이와 Tangent Space를 연결한다. 목표는 공식을 외우는 것이 아니라 각 Data의 기준과 변환 목적을 이해하는 것이다… | 앞 Chapter에서 소개되었고 본 장의 정의도 있었다. 같은 방향·다른 위치의 의미를 사례로 연결할 수 있었다. | Translation은 위치를 바꾸지만 방향 화살표는 돌리지 않는 이유를 설명한다. 최종 최초: Introduction L19 — Position은 “어디에 있는가”, Direction은 “어느 쪽을 향하는가”에 답한다. 두 값이 모두 XYZ여도 필요한 변환은 다를 수 있다. Surface에 붙은 방향 기준인 Tangent Space까지 연결한 뒤, Unreal Material의… |
| 02 | Normalize | 2.2 L899 — 방향만 필요한 경우에는 Magnitude를 1로 맞춰 사용한다. 같은 Point끼리의 차이는 Zero Vector여서 고유한 방향이 없으므로, 그 처리 조건은 Chapter 03의 Normalize 설명에서 확인한다. | 앞 Chapter에서 소개된 연산이다. 길이의 영향 제거와 본 장의 방향 입력을 더 분명히 연결할 수 있었다. | 방향을 유지하면서 길이를 1로 맞추는 연산의 목적을 그림/식 앞에 추가한다. 최종 최초: 2.2 Position, Direction and Vector L781 — 이 Vector의 Direction은 A에서 B로 향한다. Magnitude는 두 Point 사이의 거리와 연결된다. 즉, Vector는 단순한 위치나 방향의 별칭이 아니라 **방향과 크기를 함께 다룰 수 있는 값**이다. 방향만 필요한 경우에는 Ch… |
| 02 | Non-uniform Scale | 2.13 L9444 — 특히 **Non-uniform Scale**에서는 이러한 현상이 더 중요해진다. | 첫 언급에서 축별 Scale 차이의 의미를 바로 풀지 않았다. | 축마다 다른 비율로 늘리는 Scale이며 방향과 수직 관계를 따로 점검해야 하는 이유로 연결한다. 최종 최초: 2.13 Position Transform vs Direction Transform L8433 — Translation을 제외했다고 Direction의 모든 성분이 그대로인 것은 아니다. X 쪽만 늘리면 대각선 화살표의 X 변화량이 Y 변화량보다 더 커진다. 축마다 다른 비율로 늘리는 **Non-uniform Scale**에서는 길이뿐 아니라 방향… |
| 02 | FOV | 2.6 L3292 — Perspective Camera에서 중요한 또 하나의 값이 **Field of View**, 줄여서 **FOV**다. | 원문 첫 문장에 Full Name과 Camera 값 설명이 있었다. 시야각 변경과 Camera 이동의 차이를 더 풀었다. | Field of View를 Camera 시야각으로 풀고 Camera 위치 변경과 구별한다. 최종 최초: 2.6 Projection L2854 — Perspective Camera에서 중요한 또 하나의 값이 **Field of View**, 줄여서 **FOV**다. FOV는 Camera가 얼마나 넓은 범위를 바라보는지를 결정한다. 쉽게 말하면, |
| 02 | UV | 2.10 L7102 — Screen UV | 앞 Chapter에서 Texture 좌표로 소개되었다. 본 장의 Screen/Surface 주소와 방향 기준을 구별해 회고할 수 있었다. | Chapter01의 Texture 위치용 두 좌표 U/V를 짧게 회상하고 Surface 위의 방향과 연결한다. 최종 최초: 2.2 Position, Direction and Vector L1027 — Surface 위에 작은 화살표를 그리면 바깥쪽을 가리키는 Normal과 Surface를 따라가는 화살표를 구분할 수 있다. Surface 위의 기준 방향이 **Tangent**다. Chapter 01에서 Texture 위치를 나타내던 UV의 두 좌표… |
| 02 | Encoding | 2.14 L9862 — 이 절에서는 Surface의 T/B/N 기준부터 읽고, Normal Map의 Encoding을 분리해서 이해한 뒤 **TBN**을 변환 도구로 연결한다. Geometric Normal과 Shading Normal의 구분은 2.13을 그대로 유지한다. | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | Direction의 부호 있는 성분을 저장 가능한 RGB 범위로 바꿔 기록하는 과정을 의미와 함께 먼저 설명한다. 최종 최초: 2.14 Tangent Space L8838 — 이 절에서는 Surface의 T/B/N 기준부터 읽는다. **Encoding**은 Direction을 Texture가 저장할 수 있는 값으로 바꿔 기록하는 과정이다. 그 저장값을 Direction 성분으로 되돌리는 과정은 **Decode**다. 이를 … |
| 02 | Decode | 2.14 L10121 — 이 색은 Material을 보라색으로 칠하라는 값이 아니다. **Surface 기준 Direction을 RGB 형태로 저장했을 때 보이는 모습**이다. 실제 저장 형식과 Decode 과정은 Chapter 04의 Normal Map 설명에서 이어진다. | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | 저장 범위의 값을 방향 성분으로 되돌리는 일이며 Space 변환과 다름을 분리한다. 최종 최초: 2.14 Tangent Space L8838 — 이 절에서는 Surface의 T/B/N 기준부터 읽는다. **Encoding**은 Direction을 Texture가 저장할 수 있는 값으로 바꿔 기록하는 과정이다. 그 저장값을 Direction 성분으로 되돌리는 과정은 **Decode**다. 이를 … |
| 02 | Inverse Transpose | 2.13 L9667 — Normal Matrix는 변환의 **Inverse Transpose**와 연결된다. 이 변환과 재정규화의 관계는 [NVIDIA GPU Gems의 Normal 변환 설명](https://developer.nvidia.com/gpugems/gpugems… | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | Inverse는 Transform을 되돌림, Transpose는 Row/Column 교환이며 본장에서는 필요와 역할/다음장 유도로 구분한다. 최종 최초: 2.13 Position Transform vs Direction Transform L8654 — 여기서 필요한 것은 “같은 방향 성분에 같은 Scale을 적용하기”가 아니라 “변형 뒤에도 필요한 Surface 관계를 지키기”다. **Inverse**는 Transform을 되돌리는 관계이고 **Transpose**는 Matrix의 행(Row)과 열… |
| 02 | MVP | 2.12 L8675 — 이렇게 결합된 Transform을 흔히 **MVP - Model View Projection**과 연결해서 설명한다. | 첫 preview/제목/코드에서 뜻보다 이름이 먼저이거나, 상세 정의까지 중간 설명이 부족했다. | Model View Projection의 책임을 묶어 부르는 말이며 실제 결합은 Matrix 곱이라는 점을 첫 약어 문장에 명시한다. 최종 최초: 2.12 Model / View / Projection Matrix L7732 — 앞의 세 규칙을 한 번에 적용하고 싶다면 입력부터 출력까지의 연결을 하나의 규칙으로 미리 묶을 수 있다. **MVP(Model View Projection)**는 이 세 Transform을 결합해 Local Position을 Clip Position으… |
| 02 | Sampler | 2.14 Tangent Space L10257 — Engine의 Normal Sampler가 이미 Direction을 Decode했다면 첫 단계를 반복하지 않는다. 다음 절의 TBN은 **Decode가 끝난 Direction을 다른 Space로 표현하는 도구**다. | Normal Direction 복원 조건에서 이름이 먼저였다. 읽기 규칙이라는 일반 역할은 뒤 Chapter에서 설명했다. | Texture에서 값을 읽는 규칙이라는 뜻을 최초 Normal Sampler 언급에 붙였다. 최종 최초: 2.14 Tangent Space L9185 — Texture에서 값을 읽는 규칙을 담당하는 것이 Sampler다. Engine의 Normal Sampler가 이미 Direction을 Decode했다면 첫 단계를 반복하지 않는다. 다음 절의 TBN은 **Decode가 끝난 Direction을 다른 … |
| 03 | Vector | Introduction L17 — Rendering에서는 이러한 위치와 방향의 관계를 Vector로 표현하고 계산한다. | 앞 Chapter에서 배운 입력 형식이다. 원문은 도입에서 사용하고 3.2에서 길이 관계를 설명한다. | Chapter 02의 방향 표현을 회고하고 화살표의 길이와 현재 비교 목적을 연결했다. 최종 최초: Introduction L21 — Rendering에서는 이러한 위치와 방향의 관계를 Vector로 표현하고 계산한다. |
| 03 | Magnitude | 3.2 Vector and Normalize L132 — ### Direction and Magnitude | 원문 3.2에서도 길이라는 뜻을 설명했다. | 정의 유지; Light의 세기가 아니라 방향 Vector의 길이라는 관계를 보강했다. 최종 최초: 3.2 Vector and Normalize L140 — ### Direction and Magnitude |
| 03 | Normalize | Introduction L25 — 수식은 이 과정을 이해한 뒤, Shader가 수행하는 계산을 짧게 표현하는 용도로 사용한다. 특히 Normalize, Dot Product, NdotL이 각각 어떤 문제를 해결하는지 이해하는 것이 중요하다. | 도입의 연산명 예고가 3.2의 의미 설명보다 먼저였다. | 도입에 길이 통일의 목적을 붙이고 기존 방향→길이→Normalize 흐름을 유지했다. 최종 최초: Introduction L29 — 수식은 이 과정을 이해한 뒤, Shader가 수행하는 계산을 짧게 표현하는 용도로 사용한다. 먼저 방향만 비교할 수 있도록 화살표의 길이를 통일한다. 이 처리가 Normalize다. 그 다음 두 방향이 얼마나 나란한지를 숫자 하나로 비교한다. 이 연산… |
| 03 | Unit Vector | 3.2 Vector and Normalize L164 — 이렇게 길이가 1인 Vector를 Unit Vector라고 한다. | 원문 3.2에서 길이 1이라는 의미를 이미 설명했다. | 정의와 두 Vector 예제 유지; 비교의 공통 조건이라는 의미를 보강했다. 최종 최초: 3.2 Vector and Normalize L174 — 이렇게 길이가 1인 Vector를 Unit Vector라고 한다. |
| 03 | Dot Product | Introduction L25 — 수식은 이 과정을 이해한 뒤, Shader가 수행하는 계산을 짧게 표현하는 용도로 사용한다. 특히 Normalize, Dot Product, NdotL이 각각 어떤 문제를 해결하는지 이해하는 것이 중요하다. | 도입의 명칭 예고가 3.3의 관계 설명보다 먼저였다. | 도입에 나란한 정도를 숫자로 비교하는 목적을 붙였다. 최종 최초: Introduction L29 — 수식은 이 과정을 이해한 뒤, Shader가 수행하는 계산을 짧게 표현하는 용도로 사용한다. 먼저 방향만 비교할 수 있도록 화살표의 길이를 통일한다. 이 처리가 Normalize다. 그 다음 두 방향이 얼마나 나란한지를 숫자 하나로 비교한다. 이 연산… |
| 03 | Scalar | 3.3 Dot Product L262 — 따라서 Surface Normal과 Light Direction의 관계를 하나의 Scalar 값으로 표현해야 한다. | 3.3에서 관계를 하나의 Scalar 값으로 표현한다고 쓰지만 숫자 하나의 의미는 암묵적이었다. | 여러 성분의 Vector와 대비해 하나의 수라는 뜻을 먼저 설명했다. 최종 최초: 3.3 Dot Product L274 — 따라서 Surface Normal과 Light Direction의 관계를 숫자 하나로 표현해야 한다. 여러 성분으로 방향을 나타내는 Vector와 달리, 이런 하나의 수를 Scalar라고 한다. |
| 03 | Surface Normal | 3.1 Lighting Inputs L33 — Chapter 01에서 Vertex는 Position만 전달하는 것이 아니라 Normal, Tangent, UV와 같은 Attribute도 함께 전달하는 단위였다. | 앞 Chapter의 Attribute를 회고한 뒤 정의를 확장하는 구조였다. | 기존 입력 표와 Surface 방향 의미 유지; Geometry/Shading의 차이는 3.4에서 확장했다. 최종 최초: Introduction L29 — 수식은 이 과정을 이해한 뒤, Shader가 수행하는 계산을 짧게 표현하는 용도로 사용한다. 먼저 방향만 비교할 수 있도록 화살표의 길이를 통일한다. 이 처리가 Normalize다. 그 다음 두 방향이 얼마나 나란한지를 숫자 하나로 비교한다. 이 연산… |
| 03 | Geometric Normal | 3.4 Surface Normal L501 — 이 구분을 위해 Geometry의 실제 방향을 나타내는 Normal을 Geometric Normal, Shading 계산에 사용하는 방향을 Shading Normal이라고 부른다. | 원문 3.4는 실제 Geometry 방향과 Shading 방향의 구분을 이미 제공했다. | 구분 유지; Surface 수직 예제와 Artist 조정 방향의 범위를 보존했다. 최종 최초: 3.4 Surface Normal L519 — 이 구분을 위해 Geometry의 실제 방향을 나타내는 Normal을 Geometric Normal, Shading 계산에 사용하는 방향을 Shading Normal이라고 부른다. |
| 03 | Shading Normal | 3.4 Surface Normal L501 — 이 구분을 위해 Geometry의 실제 방향을 나타내는 Normal을 Geometric Normal, Shading 계산에 사용하는 방향을 Shading Normal이라고 부른다. | 원문 3.4에서 Geometric과 대비해 의미를 설명했다. | 기존 정의와 Smooth Shading/Normal Map 연결을 유지했다. 최종 최초: 3.4 Surface Normal L519 — 이 구분을 위해 Geometry의 실제 방향을 나타내는 Normal을 Geometric Normal, Shading 계산에 사용하는 방향을 Shading Normal이라고 부른다. |
| 03 | Non-Uniform Scale | 3.5 Normal Transformation L623 — \\| Non-Uniform Scale \\| 축별로 다른 비율로 늘어남 \\| 변형된 Surface에 맞도록 방향을 별도로 보정 \\| | 3.5 표에서 이름이 먼저 나오고 아래 예제에서 축별 배율 문제를 설명했다. | 표 직전에 축별로 다른 배율이라는 뜻을 회고했다. 최종 최초: 3.5 Normal Transformation L638 — Chapter 02의 Scale은 축 방향으로 크기를 바꾸는 Transform이었다. 모든 축에 같은 양의 배율을 적용하는 경우가 Positive Uniform Scale이고, 가로만 늘리는 것처럼 축별 배율이 다른 경우가 Non-Uniform Sca… |
| 03 | Inverse | 3.5 Normal Transformation L765 — ### From Inverse Scale to Inverse Transpose | 3.5에서 변환을 되돌리는 연산을 이미 설명했다. | 정의와 역방향 Scale 직관 유지; Normal이 반대로 회전한다는 오해 방지 조건 유지. 최종 최초: 3.5 Normal Transformation L787 — ### From Inverse Scale to Inverse Transpose |
| 03 | Transpose | 3.5 Normal Transformation L765 — ### From Inverse Scale to Inverse Transpose | 3.5에서 행과 열을 바꾸는 연산을 이미 설명했다. | Row/Column 의미를 덧붙이고 수직 관계라는 목적에 다시 연결했다. 최종 최초: 3.5 Normal Transformation L787 — ### From Inverse Scale to Inverse Transpose |
| 03 | Inverse Transpose | 3.5 Normal Transformation L765 — ### From Inverse Scale to Inverse Transpose | 원문은 Non-Uniform Scale 예제 후 일반화하는 개선된 흐름이었다. | 개선된 순서 유지; 선형 3×3 부분과 Translation 제외의 이유를 보강했다. 최종 최초: 3.5 Normal Transformation L787 — ### From Inverse Scale to Inverse Transpose |
| 03 | Direction Convention | 3.6 Light and View Direction L889 — ### Start with a Direction Convention | 3.6 제목과 출발점/도착점 규칙을 설명했지만 용어 의미는 명시하지 않았다. | 같은 두 지점의 반대 화살표 문제에서 방향 표기 규약이라는 뜻을 밝혔다. 최종 최초: 3.6 Light and View Direction L915 — ### Start with a Direction Convention |
| 03 | Winding / Front-Face | 3.4 Surface Normal L472 — 따라서 Face Normal의 방향은 Vertex가 나열되는 순서인 Winding과 연결되며, Renderer의 Front-Face 규칙도 함께 확인해야 한다. | Winding은 Vertex 순서로 설명했으나 Front-Face 규칙이 한 문장에 함께 등장했다. | Vertex 순서와 Renderer의 앞면 판단을 두 단계로 분리했다. 최종 최초: 3.4 Surface Normal L488 — 따라서 Face Normal의 방향은 Vertex가 나열되는 순서인 Winding과 연결된다. 같은 세 점도 순서를 뒤집으면 수직 화살표의 방향이 바뀐다. |
| 03 | DCC / API / RGB | 3.4 Surface Normal L493 — Vertex Normal은 주변 Face의 방향을 바탕으로 생성되거나, DCC Tool에서 Artist가 조정한 방향을 사용할 수 있다. | 원문 Chapter 03은 제작 도구/접점/표시에 이름을 사용했다. 새 Chapter 01–02에서 의미와 Full Name을 먼저 소개했다. | 앞 Chapter의 최초 정의를 반복하지 않고 현재 사용 역할을 짧게 회고했다. 최종 최초: 3.4 Surface Normal L511 — Vertex Normal은 주변 Face의 방향을 바탕으로 생성될 수 있다. 또는 Chapter 02에서 살펴본 모델 제작 도구인 DCC Tool에서 Artist가 조정한 방향을 사용할 수도 있다. |
| 04 | Texel | 4.3 Texture as Material Data L509 — Texture를 구성하는 각 저장 단위를 Texel이라고 한다. 화면의 Pixel과 구분하기 위한 이름이며, 자세한 Sampling 관계는 4.4에서 살펴본다. | 4.3에서 저장 단위는 설명했지만 Texture Element의 확장은 4.4였다. | 뜻은 유지하고 Full Name을 실제 최초 사용에 함께 적었다. 최종 최초: 4.3 Texture as Material Data L527 — Texture를 구성하는 각 저장 단위를 Texel이라고 한다. Texture Element를 줄인 이름이다. 화면의 Pixel은 화면에서 다루는 위치이고, Texel은 Texture 자원에 저장된 위치의 단위다. 서로 저장하고 처리하는 대상이 다르므… |
| 04 | UV | 4.1 What Is a Material? L172 — → Position / Normal / UV | 앞 Chapter의 Attribute와 4.3의 Texture 주소 설명을 거쳐 4.4에서 확장했다. | 앞 정의를 회고; U/V는 축 이름이며 Acronym이 아니라는 점을 밝혔다. 최종 최초: 4.1 What Is a Material? L186 — → Position / Normal / UV |
| 04 | Texture Sampling | 4.3 Texture as Material Data L601 — ### Texture Sampling | 도입과 앞 Chapter 회고에서 명칭을 쓰고 4.3/4.4에서 설명했다. | Sample을 실제 첫 사용에서 값을 얻는 처리로 연결; UV/Resource 별도 입력 유지. 최종 최초: 4.3 Texture as Material Data L631 — ### Texture Sampling |
| 04 | Sampler | 4.3 Texture as Material Data L592 — \\| Normal Sample \\| Encoded RGB 또는 sampler-decoded Direction \\| 4.6의 방향 복원 경로로 전달 \\| | 4.3에서 주변 Texel을 계산할 수 있다고 쓰지만 읽기 규칙의 의미는 암묵적이었다. | Chapter02의 읽기 규칙 설명을 회고하고, 4.3 표보다 먼저 이미 복원된 Direction과 저장 RGB의 차이를 연결했다. Filtering은 별도 역할로 이어 설명했다. 최종 최초: 4.3 Texture as Material Data L613 — Chapter 02에서 살펴본 Sampler는 Texture에서 값을 읽는 규칙을 담당한다. Engine의 Normal Sampler가 Direction을 이미 복원해 반환하는 경우도 있으므로, 저장된 RGB와 현재 읽은 값을 구분한다. |
| 04 | Filtering | 4.3 Texture as Material Data L618 — 실제 Sampler는 주변 Texel을 이용해 값을 계산할 수도 있다. 따라서 Sample 결과를 반드시 특정 Texel 하나의 원래 값과 같다고 가정하지 않는다. 이 과정은 다음 Section의 Filtering에서 살펴본다. | 4.3에서는 뒤 절의 명칭을 예고했고 자세한 문제 설명은 4.4였다. | 최초 예고에 주변 Texel로 현재 값을 계산한다는 의미를 붙였다. 최종 최초: 4.3 Texture as Material Data L648 — Sampler는 어떤 Texel을 선택하거나 섞을지에 대한 설정을 사용한다. 주변 Texel을 이용해 값을 계산하는 처리는 Filtering이라고 한다. |
| 04 | Bilinear | 4.4 UV and Texture Sampling L787 — 이처럼 Sampling Point 주변의 Data로 현재 값을 계산하는 것이 Filtering의 역할이다. 2D Texture에서 대표적으로 사용하는 방식이 Bilinear Filtering이다. | 4.4에서 네 Texel을 사용하는 동작은 설명했다. | 두 축으로 값을 이어 계산한다는 이름의 의미를 보강했다. 최종 최초: 4.4 UV and Texture Sampling L823 — 이처럼 Sampling Point 주변의 Data로 현재 값을 계산하는 것이 Filtering의 역할이다. 2D Texture에서 대표적으로 사용하는 방식이 Bilinear Filtering이다. |
| 04 | Mipmap / Mip Level | 4.4 UV and Texture Sampling L741 — 이 숫자는 설명용 예시다. 실제 결과는 Texture에 저장된 Data, Filtering, Mip Level과 입력 해석에 따라 달라진다. | 4.4 Sampling 결과 조건에 Mip Level이 먼저 등장하고 Mipmapping 문제는 뒤에 나왔다. | 미리 만든 해상도 단계라는 짧은 의미를 실제 첫 사용에 추가했다. 최종 최초: 4.4 UV and Texture Sampling L777 — 앞에서 본 Filtering 외에도, 미리 만든 여러 Texture 해상도 중 어느 단계를 읽는지가 영향을 준다. 이 해상도 단계가 Mip Level이다. 아래에서는 많은 Texture Detail을 작은 화면 영역에서 읽는 문제와 연결해 설명한다. … |
| 04 | Color Space | 4.3 Texture as Material Data L529 — 각 Texel에는 일반적으로 RGB 값이 저장된다. Shader는 현재 Surface에 대응하는 위치를 Sample하고, Color Space를 올바르게 해석한 결과를 Base Color로 사용한다. | 4.3 Base Color Texture에서 입력 해석 조건으로 먼저 사용하고 정식 의미는 4.5였다. | 첫 사용에서 숫자를 해석하는 Color 기준이라는 뜻을 소개했다. 최종 최초: 4.3 Texture as Material Data L551 — 읽은 숫자를 어떤 기준의 Color로 해석할지도 필요하다. 그 기준이 Color Space다. Shader는 위치를 Sample하고, Color Space를 올바르게 해석한 결과를 Base Color로 사용한다. |
| 04 | sRGB | 4.3 Texture as Material Data L537 — sRGB로 저장한 파일의 Raw RGB와 Shader가 사용할 Linear RGB가 언제나 같지는 않다는 점도 기억한다. 이 차이는 4.5에서 설명한다. | 4.3에서 Raw/Linear 비교에 등장하며 Full Name이 없었다. | 첫 사용에 standard Red Green Blue와 저장 표현 의미를 붙였고 4.5에서 처리 방향을 확장했다. 최종 최초: 4.3 Texture as Material Data L561 — 사람이 볼 Color를 저장할 때 흔히 사용하는 sRGB(standard Red Green Blue)는 Color 표현의 표준이다. 저장용으로 비선형 변환한 RGB와 Lighting 계산에 사용할 Linear RGB가 같지 않을 수 있다. Raw RG… |
| 04 | Linear | 4.3 Texture as Material Data L531 — 예를 들어 입력 해석까지 끝난 현재 Surface의 Linear Base Color가 다음과 같을 수 있다. | 4.3의 입력 예시가 Linear라고 표시되지만 계산값의 의미는 4.5에서 설명했다. | 예시 전에 Light 비례 관계를 유지하는 계산값이라고 설명했다. 최종 최초: 4.3 Texture as Material Data L553 — Lighting에서 더하기와 비율 계산을 하려면 Light 값 사이의 비례 관계가 유지되어야 한다. 이런 계산에 사용할 값이 Linear 값이다. |
| 04 | Decode | 4.3 Texture as Material Data L521 — **Figure 4-3. Texture as Material Data.** 위쪽 Texture들은 같은 Surface 영역에 대응하는 서로 다른 Property를 저장한다. 가운데 선택된 위치에서는 각 Texture가 현재 Pixel에 필요한 값을 제… | 4.3 Figure/Normal 설명에서 복원 작업 이름이 먼저 등장했다. | 첫 Normal preview에서 Direction 복원 의미를 소개; 4.5 Color Decode와 구분했다. 최종 최초: 4.3 Texture as Material Data L541 — **Figure 4-3. Texture as Material Data.** 위쪽 Texture들은 같은 Surface 영역에 대응하는 서로 다른 Property를 저장한다. 가운데 선택된 위치에서는 각 Texture가 현재 Pixel에 필요한 값을 제… |
| 04 | Encode / Encoding | 4.3 Texture as Material Data L561 — 일반적인 Tangent Space Normal Map은 Direction의 X, Y, Z 성분을 RGB에 Encoding하므로 파란색이나 보라색 계열로 보인다. 이 색을 Base Color로 사용할 목적은 아니다. | 4.3 Normal Texture의 RGB Encoding 이름을 정식 설명 전에 사용했다. | 저장 범위로 바꾸어 기록하는 의미를 최초 사용에 붙였다. 최종 최초: 4.3 Texture as Material Data L587 — Direction의 성분을 Texture가 저장할 수 있는 RGB 범위로 바꾸어 기록하는 과정을 Encoding이라고 한다. X, Y, Z 성분을 RGB에 Encoding하면 파란색이나 보라색 계열로 보일 수 있다. 이 색을 Base Color로 사용… |
| 04 | Normal Map | 4.2 Material Inputs and Surface Properties L345 — 대신 Normal Map과 같은 데이터를 사용하면 Geometry 자체를 변경하지 않고도 Pixel마다 Lighting에 사용할 Normal 방향을 바꿀 수 있다. | 4.2에서 Geometry를 늘리지 않고 방향을 바꾸는 데이터를 예고했다. | 첫 preview에서 Direction을 Texture에 저장하는 의미를 명시했다. 최종 최초: 4.2 Material Inputs and Surface Properties L363 — 대신 위치마다 다른 Normal Direction을 Texture에 저장할 수 있다. 이 Direction Data가 Normal Map이다. Geometry 자체를 변경하지 않고도 Pixel마다 Lighting에 사용할 Normal 방향을 바꿀 수 … |
| 04 | Tangent Space / TBN | 4.2 Material Inputs and Surface Properties L353 — Normal Map의 구조와 Tangent Space에 대해서는 이후 관련 Section에서 더 자세히 다룬다. | 앞 Chapter에서 배운 Space를 4.2부터 예고하고 4.6에서 실제 복원을 설명했다. | 앞 정의를 회고하고 Tangent/Bitangent/Normal 성분 기여와 목표 Space를 연결했다. 최종 최초: 4.2 Material Inputs and Surface Properties L371 — Normal Map의 구조와 Tangent Space에 대해서는 이후 관련 Section에서 더 자세히 다룬다. |
| 04 | Parameter | Introduction L18 — 먼저 Input이 어떤 Property를 표현하는지 이해한다. 그 뒤 Constant, Texture와 Parameter가 그 값을 제공하는 방법을 살펴보고, 마지막에 Lighting Data와 합류하는 흐름을 연결한다. | 도입에서 Constant/Texture와 함께 이름을 나열했고 실제 Interface 의미는 4.7이었다. | 도입에서 외부에서 조절할 입력이라는 짧은 의미를 붙였다. 최종 최초: Introduction L20 — 고정된 값을 Constant, 조절 가능한 입력을 Parameter라고 부른다. 이후에는 이 Source가 왜 필요한지 하나씩 살펴보고, 마지막에 Lighting Data와 합류하는 흐름을 연결한다. |
| 04 | Material Instance | 4.7 Material Parameters and Material Instances L1433 — ## 4.7 Material Parameters and Material Instances | 4.7 문제 해결 시 Parent/Parameter/Interface/Instance를 함께 소개했다. | Parent→노출 Input→Instance→Override를 순서대로 풀었다. 최종 최초: 4.7 Material Parameters and Material Instances L1493 — ## 4.7 Material Parameters and Material Instances |
| 04 | Dynamic Material Instance / MID | 4.7 Material Parameters and Material Instances L1588 — 이 경우 실행 중에 조절할 수 있는 Instance가 필요하다. Unreal Engine에서는 일반적으로 Material Instance Dynamic, 즉 MID 또는 Dynamic Material Instance를 사용한다. | 원문 Runtime Adjustment에서 Material Instance Dynamic과 MID를 이미 소개했다. | 기존 Full Name/지원 Non-Static 범위 유지; Runtime 뜻을 Section 도입에서 먼저 설명했다. 최종 최초: 4.7 Material Parameters and Material Instances L1654 — 이 경우 실행 중에 조절할 수 있는 Instance가 필요하다. Unreal Engine에서는 일반적으로 Material Instance Dynamic, 즉 MID 또는 Dynamic Material Instance를 사용한다. |
| 04 | Static Switch | 4.7 Material Parameters and Material Instances L1466 — 그 다음 Compile Time에 기능이나 Channel 구성을 선택하는 Static Parameter를 구분한다. Static Switch와 Static Component Mask가 여기에 해당한다. | 4.7 Parameter 표 전에 이름을 소개하나 역할의 상세 설명은 아래였다. | 기능 포함 여부를 Compile Time에 선택한다는 의미를 표 앞에 붙였다. 최종 최초: 4.7 Material Parameters and Material Instances L1532 — 그 다음 Compile Time에 기능이나 Channel 구성을 선택하는 Static Parameter를 구분한다. Static Switch는 기능을 포함할지 선택하고, Static Component Mask는 사용할 성분이나 Channel을 선택한다… |
| 04 | Static Component Mask | 4.7 Material Parameters and Material Instances L1466 — 그 다음 Compile Time에 기능이나 Channel 구성을 선택하는 Static Parameter를 구분한다. Static Switch와 Static Component Mask가 여기에 해당한다. | 4.7 표에서 Channel 선택과 함께 소개했다. | 사용 성분 선택 의미를 표 직전에 설명하고 Static 범위를 유지했다. 최종 최초: 4.7 Material Parameters and Material Instances L1532 — 그 다음 Compile Time에 기능이나 Channel 구성을 선택하는 Static Parameter를 구분한다. Static Switch는 기능을 포함할지 선택하고, Static Component Mask는 사용할 성분이나 Channel을 선택한다… |
| 04 | Shader Variant | 4.1 What Is a Material? L140 — 하나의 Shader Architecture를 여러 Material이 공유하면서 서로 다른 Parameter와 Texture를 사용할 수도 있다. Architecture 재사용과 동일한 Compiled Shader Variant의 조건은 4.7에서 구분… | 4.1에서 Architecture 재사용의 caveat로 이름을 먼저 사용했다. | 실제로 Compile한 Program의 한 구성이라는 의미를 즉시 붙였다. 최종 최초: 4.1 What Is a Material? L154 — 공통 구조를 공유하더라도 기능 선택에 따라 실제로 Compile한 Program이 달라질 수 있다. 이렇게 준비된 Program의 한 구성이 Compiled Shader Variant다. 이 구분은 4.7에서 Editor의 조절과 Program이 실행… |
| 04 | Shader Permutation | 4.7 Material Parameters and Material Instances L1620 — Static Parameter가 많고 실제로 사용하는 조합이 다양하면 Shader Permutation 수와 Compile 부담이 증가할 수 있다. 반대로 Switch 개수만 보고 모든 이론적인 조합이 현재 Project에서 쓰인다고 가정하지 않는다.… | 4.7 후반에서 수/Compile 부담은 설명하지만 조합이라는 의미는 암묵적이었다. | Static 기능 선택 조합 등에 따른 Variant 구성이라는 뜻을 먼저 설명했다. 최종 최초: 4.7 Material Parameters and Material Instances L1686 — Static 기능 선택의 조합 등에 따라 서로 다른 Shader Variant가 만들어지는 구성을 Shader Permutation이라고 부른다. 여러 선택이 결합되면 필요한 Program의 종류도 늘어날 수 있다. |
| 04 | Runtime / Compile Time | 4.1 What Is a Material? L128 — Engine의 Material Graph는 이 입력을 준비하는 Logic도 표현하며, 필요한 Shader Program으로 Compile될 수 있다. 개념을 구분할 때는 Material이 정의하는 Surface 구조와 GPU에서 실제 실행되는 Shad… | 4.1 Compile과 4.7의 시점 구분이 짧고 전문 이름 중심이었다. | Graph를 Program으로 준비하는 과정→준비 시점→실행 시점 순서로 분리했다. 최종 최초: 4.1 What Is a Material? L138 — Graph가 실행되려면 GPU가 수행할 Program으로 준비되어야 한다. 이 번역·준비 과정이 Compile이다. Material Graph는 입력을 준비하는 Logic도 표현하며, 필요한 Shader Program으로 Compile될 수 있다. |
| 04 | PBR / HDR / AO | 4.2 Material Inputs and Surface Properties L306 — 일반적인 PBR Material에서는 크게 다음 두 종류의 Surface를 구분한다. | PBR은 Material 분류에, HDR은 Decode 예외에, AO는 Data 예시에 쓰였고 뜻이 암묵적이었다. | 각 첫 사용에 Full Name과 현재 입력/저장 목적에 필요한 뜻을 붙였다. 최종 최초: 4.2 Material Inputs and Surface Properties L322 — 일반적인 PBR(Physically Based Rendering) Material에서는 크게 다음 두 종류의 Surface를 구분한다. |
| 04 | signed / unsigned | 4.6 Normal Mapping and Tangent Space L1197 — Normal의 Component는 음수와 양수를 가지므로 -1~1 범위를 사용한다. 반면 여기서 설명하는 일반적인 unsigned RGB 저장은 0~1 범위다. 음수 Direction을 저장하려면 이 범위에 맞게 Encoding해야 한다. | Normal 저장 범위에서 unsigned를 사용하나 이름 자체는 설명하지 않았다. | 부호 있는 방향과 부호 없는 저장 범위 문제 안에서 뜻을 풀었다. 최종 최초: 4.6 Normal Mapping and Tangent Space L1248 — 방향은 기준축의 양쪽을 가리킬 수 있으므로 성분에도 부호가 필요하다. 부호가 있는 값을 signed 값이라고 한다. Normal의 Component는 음수와 양수를 가지므로 -1~1 범위를 사용한다. 반면 여기서 설명하는 일반적인 unsigned RG… |
| 04 | Bloom / Glossy / Aliasing / Shimmering | 4.1 What Is a Material? L66 — **Figure 4-1. What Is a Material?** 같은 Geometry와 Light 조건에 서로 다른 Material Data를 사용한 개념 비교다. Roughness가 Reflection 분포를 바꾸는 효과와 Normal이 만드는 표면… | 효과 이름/Appearance 경향/Texture 오류를 전문 이름으로 소개했다. | 각 현상의 관찰 의미를 해당 문제와 연결했다. 최종 최초: 4.1 What Is a Material? L72 — **Figure 4-1. What Is a Material?** 같은 Geometry와 Light 조건에 서로 다른 Material Data를 사용한 개념 비교다. Roughness가 Reflection 분포를 바꾸는 효과와 Normal이 만드는 표면… |
| 04 | Texture Footprint | 4.4 UV and Texture Sampling L829 — **Technical Note — Texture Footprint.** 실제 Mip 선택은 Texture에서 차지하는 footprint와 관련된다. 거리뿐 아니라 UV Scale, Surface 기울기, 화면 해상도와 좌표 변화율도 영향을 준다. Ob… | 화면 Pixel이 Texture에서 차지하는 범위의 직관은 이미 있었다. Note의 영어 이름과 이 범위를 직접 연결할 수 있었다. | Note 첫 문장에서 현재 화면 Pixel이 Texture에서 덮는 범위라는 뜻을 붙이고 Mip 선택 조건을 유지했다. 최종 최초: 4.4 UV and Texture Sampling L867 — **Technical Note — Texture Footprint.** Texture Footprint는 앞에서 설명한 현재 화면 Pixel이 Texture에서 덮는 범위를 말하며, 실제 Mip 선택은 이 범위와 관련된다. 거리뿐 아니라 UV Scal… |
| 05 | Reflection | Chapter Introduction L1 — # Chapter 05 — Reflection and BRDF | 친숙한 거울·종이 예시가 이미 있었다. | 예시를 유지하고 Surface 이후 어디로 얼마나 나가는가라는 계산 질문으로 연결한다. 최종 최초: Introduction L1 — # Chapter 05 — Reflection and BRDF |
| 05 | Diffuse | Chapter Introduction L8 — > Lambert의 Diffuse와 Phong/Blinn-Phong의 Specular를 비교한 뒤 Microfacet과 BRDF로 연결한다. 이 순서는 학습 순서이며 모든 모델의 엄밀한 역사적 계보를 뜻하지 않는다. | 원문 5.4는 이미 친숙한 Surface 예와 Rough Specular 구분을 포함했다. 도입에서는 다음 Model 경로의 명칭이 먼저 보였다. | Chapter03의 방향에 넓게 보이는 반사 성분을 회고하고 5.4에서 내부 산란의 이상화, Rough Specular와의 차이, Lambert의 관찰 방향 가정을 연결했다. 최종 최초: Introduction L9 — Chapter 03에서 살펴본 Diffuse/Specular 성분을 실제 Reflection Model로 연결하고, Chapter 04의 Material 입력이 방향 응답을 어떻게 바꾸는지 알아본다. 마지막에는 **BRDF(Bidirectional R… |
| 05 | Specular | Chapter Introduction L8 — > Lambert의 Diffuse와 Phong/Blinn-Phong의 Specular를 비교한 뒤 Microfacet과 BRDF로 연결한다. 이 순서는 학습 순서이며 모든 모델의 엄밀한 역사적 계보를 뜻하지 않는다. | 앞장과 원문에 반짝임의 방향 관계가 있었다. 도입 Model 경로와 관찰 방향 입력을 더 부드럽게 연결할 수 있었다. | 앞장 반사 성분을 회고하고 Camera를 움직였을 때 Highlight가 바뀌는 문제에서 R/V와 H의 비교로 확장했다. 최종 최초: Introduction L9 — Chapter 03에서 살펴본 Diffuse/Specular 성분을 실제 Reflection Model로 연결하고, Chapter 04의 Material 입력이 방향 응답을 어떻게 바꾸는지 알아본다. 마지막에는 **BRDF(Bidirectional R… |
| 05 | Roughness | 5.1 Reflection L31 — **Figure 5-1. Reflection Overview.** 이상적으로 매끄러운 Surface의 거울 반사 방향을 보여주는 예시다. 모든 Material의 Reflection이 하나의 방향으로만 나간다는 뜻은 아니며, Roughness와 Diff… | Chapter04의 Material 입력이다. 원문 5.9에서 Highlight 분포로 설명했고 앞장에서의 뜻을 회고할 수 있었다. | Chapter04 입력을 회고해 반사 응답이 퍼지는 형태와 연결했다. 모든 방향 응답의 단순 감소나 단순 Diffuse 전환으로 일반화하지 않았다. 최종 최초: 5.1 Reflection L23 — Chapter 04에서 Material 입력으로 만난 **Roughness**는 거칠기에 따라 Specular가 퍼지는 정도를 제어한다. 지금은 반사 방향의 분포를 조절하는 Surface의 거칠기 값이라고 이해하면 된다. 하나의 반사 방향, 그 방향 … |
| 05 | PBR | 5.1 Reflection L76 — 이후 더 현실적인 결과를 얻기 위해 다양한 Reflection Model이 등장했고, 오늘날 대부분의 Rendering Engine은 물리 기반(Physically Based Rendering, PBR)의 Reflection Model을 사용한다. | Full Name은 있었지만 의미는 짧았다. 이미 Chapter 04에서 소개되는 용어다. | Chapter 04 회상으로 연결하고 물리 관계/제약이라는 뜻과 Model 범위를 짧게 확인한다. 최종 최초: 5.1 Reflection L65 — Chapter 04에서 소개한 **PBR(Physically Based Rendering)**은 물리적 관계와 제약을 바탕으로 Material과 빛을 계산하는 접근이었다. 이름에 Physically Based가 들어간다는 사실만으로 모든 현상을 정확하… |
| 05 | BRDF | Chapter Introduction L1 — # Chapter 05 — Reflection and BRDF | 제목/학습 경로의 이름을 보고 공통 함수의 역할을 추측해야 했다. | Part 도입에서 Full Name과 입사·출사 Surface 응답을 짧게 안내. 5.16에서 필요와 두 Direction의 뜻, 5.17–5.18에서 정확한 출력/정의를 전개한다. 최종 최초: Introduction L1 — # Chapter 05 — Reflection and BRDF |
| 05 | Absorption | 5.1 Reflection L39 — 일부는 물체 내부로 흡수(Absorption)되고, | 원문은 처음 목록에서 이미 빛이 Surface에 흡수됨을 풀었다. 현상과 남은 반사량의 질문을 이어 연결했다. | 빛이 Surface에 흡수되어 반사 기여로 돌아오지 않는 경우의 의미를 익숙한 Material 관찰에서 유지했다. 최종 최초: 5.1 Reflection L43 — Surface에 도착한 빛이 모두 반사되는 것은 아니다. 일부는 Material 내부에 흡수된다. 이를 **Absorption**이라고 하며, 반사되어 다시 나오는 빛과 구별한다. 또 일부는 Material을 통과할 수 있다. 이처럼 다른 쪽으로 전달… |
| 05 | Transmission | 5.1 Reflection L40 — 일부는 내부를 통과(Transmission)하며, | 원문은 처음 목록에서 이미 내부로 통과하는 빛을 풀었다. 이번 Surface 반사 Model 범위를 연결했다. | 빛이 Surface 내부로 통과하는 경우의 의미를 설명하고 여기서 다룰 Reflection 응답과 구별했다. 최종 최초: 5.1 Reflection L43 — Surface에 도착한 빛이 모두 반사되는 것은 아니다. 일부는 Material 내부에 흡수된다. 이를 **Absorption**이라고 하며, 반사되어 다시 나오는 빛과 구별한다. 또 일부는 Material을 통과할 수 있다. 이처럼 다른 쪽으로 전달… |
| 05 | Winding | 5.2 Surface Normal L155 — 대각선 등 수많은 방향을 정의할 수 있다. 하지만 이러한 방향들은 모두 표면 위에 존재하는 방향일 뿐, 표면 자체가 어느 방향을 향하고 있는지는 알려주지 않는다. 반면, 평면의 수직 방향은 서로 반대인 두 방향이다. Geometry의 Winding과 … | 앞면 선택 조건에 뜻 없이 삽입되었다. | Triangle Vertex 연결 순서와 앞면 규칙의 관계를 처음 사용에서 풀어준다. 최종 최초: 5.2 Surface Normal L137 — 평면에 수직인 방향은 서로 반대인 두 방향이다. 바닥에는 위와 아래가 모두 수직이므로, 그중 어느 쪽을 앞면으로 사용할지 정해야 한다. Geometry에서는 Triangle의 Vertex를 연결하는 순서와 앞면 규칙이 이 선택에 관계된다. Vertex… |
| 05 | Reflection Vector | 5.1 Reflection L83 — Reflection Vector | 수정된 부호는 정확하지만 Caption에 여러 식·각도 조건이 모였다. | Surface→Light 화살표와 실제 입사 진행을 본문에서 먼저 구별하고 I=-L/Caption 정밀 조건을 유지한다. 최종 최초: 5.1 Reflection L74 — Reflection Vector |
| 05 | Incoming Direction / I / L | 5.3 Reflection Vector L243 — - **L** : Surface에서 Light를 향하는 Unit Direction. 빛의 진행 방향은 I = -L | 수정된 부호는 정확하지만 Caption에 여러 식·각도 조건이 모였다. | Surface→Light 화살표와 실제 입사 진행을 본문에서 먼저 구별하고 I=-L/Caption 정밀 조건을 유지한다. 최종 최초: 5.3 Reflection Vector L210 — 실제로 들어오는 빛의 진행 방향을 **I**라고 쓰면 두 표기는 **I = -L** 관계다. Incoming이라는 말이 같은 뜻으로 쓰이더라도, 광원 쪽을 가리키는 계산 방향과 실제 빛의 진행 방향은 구별해야 한다. |
| 05 | Decomposition | 5.3 Reflection Vector L281 — ### Reflection Vector Decomposition | 성분 식은 있으나 이름의 뜻을 앞에서 설명하지 않았다. | 한 Vector를 Normal/접선 성분으로 나누는 의미를 Technical Note 앞에 붙인다. 최종 최초: 5.3 Reflection Vector L246 — <summary>Technical Note — Reflection Vector Decomposition</summary> |
| 05 | Irradiance | 5.4 Lambert Reflection L349 — > **같은 Irradiance를 받는 Surface의 Outgoing Radiance는 관찰 방향에 의존하지 않는다.** | 5.15 단위 정의 전에 정밀 가정에서 먼저 쓰였다. | 5.4에서 Surface 면적당 시간당 도착하는 빛의 양을 설명. 5.15에서 단위와 다른 물리량을 비교한다. 최종 최초: 5.4 Lambert Reflection L303 — 먼저 Surface가 받는 빛의 양을 정해 보자. 단위 Surface 면적에 단위 시간 동안 얼마나 많은 빛의 에너지가 도착하는지를 나타내는 양을 **Irradiance**라고 한다. 여기서는 같은 Surface 지점이 같은 Irradiance를 받고… |
| 05 | Outgoing Radiance | 5.4 Lambert Reflection L349 — > **같은 Irradiance를 받는 Surface의 Outgoing Radiance는 관찰 방향에 의존하지 않는다.** | 정확한 가정이지만 독자가 물리량을 알기 전에 등장했다. | 관찰 방향으로 나가는 빛을 측정하는 기준을 짧게 소개하고 투영 면적과 단위는 5.15에서 확장한다. 최종 최초: 5.4 Lambert Reflection L305 — 이 Surface에서 특정 관찰 방향으로 나가는 빛을 표현할 때는 **Outgoing Radiance**를 사용한다. Radiance는 방향과, 그 방향에서 보이는 Surface의 투영 면적을 함께 고려하는 물리량이다. 정확한 단위는 5.15에서 비교… |
| 05 | One-sided / Opaque | 5.4 Lambert Reflection L389 — 빛이 Surface 뒤쪽에서 들어오는 경우에는 여기서 다루는 One-sided Opaque Surface의 앞면에는 직접 기여하지 않으므로 음수는 0으로 처리한다. | 기술 범위는 보존해야 하나 이름의 뜻은 암묵적이었다. | 앞면만 평가/투과를 다루지 않는 Surface라는 뜻을 clamp의 이유와 연결한다. 최종 최초: 5.4 Lambert Reflection L341 — 여기서는 Surface의 앞면만 반사에 사용하고 내부 투과를 다루지 않는 불투명한 Surface를 생각한다. 앞면만 평가하는 조건을 **One-sided**, 빛이 통과하지 않는 범위를 **Opaque**라고 한다. |
| 05 | View Direction | 5.3 Reflection Vector L299 — - Phong Reflection은 Reflection Vector와 View Direction의 관계를 이용하여 Specular Reflection을 계산한다. | 5.3의 Model 사용 예고에 이름이 먼저 나오며 5.5에서 L/N/V를 비교한다. 앞장 Camera 방향 정의를 회상할 수 있다. | 5.3에서는 앞장 View 방향을 사용한다. 5.5의 Camera 이동 문제에서 V의 역할과 방향을 다시 연결한다. 최종 최초: 5.3 Reflection Vector L268 — Phong은 R과 View Direction의 관계를 이용해 Specular Highlight를 구성한다. Blinn-Phong은 이후 L과 V 사이의 중간 방향인 **Half Vector**를 사용한다. Microfacet Model은 작은 반사 면… |
| 05 | Highlight / Gloss | 5.2 Surface Normal L168 — - Specular Highlight는 어디에 생기는가? | 원문 Highlight Formation은 밝은 영역과 Camera 방향의 관계를 설명했다. 이미 존재한 현상 설명을 계산 질문으로 연결할 수 있었다. | 밝은 방향성 반사 영역이 Highlight이며 Gloss는 그 광택 모습이라고 풀었다. 스스로 빛을 내는 Emission과 구별했다. 최종 최초: 5.1 Reflection L59 — 예를 들어 Lambert는 방향에 무관한 이상적인 Diffuse 응답을 설명하고, Phong은 관찰 방향에 따라 달라지는 Highlight를 간단한 관계로 만든다. 뒤에서 살펴볼 Microfacet Model은 Surface의 작은 반사 면들이 서로 … |
| 05 | Empirical / Response | 5.5 Phong Reflection L520 — SpecularResponse = pow(max(0, dot(R, V)), n) // n > 0 | 원문은 경험적 Model과 완성 BRDF의 차이를 구별했다. English 명칭을 따로 배워야 하는 간격을 줄일 수 있었다. | Response는 입력 방향에 대한 계산 응답, Empirical은 현상을 간단한 제어 관계로 근사하는 경험적 Model이라고 풀었다. 완성된 물리 BRDF와 구별했다. 최종 최초: 5.5 Phong Reflection L415 — 여기서 **Response**는 입력 방향에 대해 계산한 응답값을 말한다. **Empirical**, 즉 경험적 모델이라는 말은 현상을 간단한 제어 관계로 근사한다는 뜻이다. 이 값의 모양을 제어하는 것과 물리적인 반사율을 완성하는 것은 구별해야 한다… |
| 05 | Half Vector | 5.3 Reflection Vector L300 — - Blinn-Phong은 Reflection Vector 계산을 단순화하기 위해 Half Vector를 도입한다. | 예고에서는 이름 중심이며 정식 정의 소제목은 H/Response 식과 경계 조건으로 시작했다. | 5.3 최초 예고에서 중간 방향이라는 뜻을 붙이고 5.6에서 같은 길이의 L/V → 합 → Normalize → H → N/H 정렬 → 보존 Formula 순서로 전개한다. 최종 최초: 5.3 Reflection Vector L268 — Phong은 R과 View Direction의 관계를 이용해 Specular Highlight를 구성한다. Blinn-Phong은 이후 L과 V 사이의 중간 방향인 **Half Vector**를 사용한다. Microfacet Model은 작은 반사 면… |
| 05 | Lobe | 5.7 Blinn-Phong Reflection L702 — ### Peak Alignment and Lobe Differences | 원문의 peak/width 구분은 정확했다. 영어 Lobe가 응답의 퍼지는 형태를 뜻함을 더 직접 연결할 수 있었다. | 응답이 퍼지는 형태를 뜻한다고 설명하고 정렬 위치와 전체 폭/형태를 구분했다. 같은 지수의 Phong/Blinn-Phong 폭이 같다고 단정하지 않았다. 최종 최초: 5.6 Half Vector L510 — R과 V가 정렬되는 최대 조건을 N과 H의 정렬 관계로 읽을 수 있다. 하지만 정렬되는 중심이 같다는 사실이 중심 주변의 모든 응답값까지 같다는 뜻은 아니다. Highlight 주위 전체 방향의 퍼짐을 **Lobe**라고 부르며, Phong과 Blin… |
| 05 | Microfacet | Chapter Introduction L8 — > Lambert의 Diffuse와 Phong/Blinn-Phong의 Specular를 비교한 뒤 Microfacet과 BRDF로 연결한다. 이 순서는 학습 순서이며 모든 모델의 엄밀한 역사적 계보를 뜻하지 않는다. | 경로의 이름이 먼저 나오며 5.6에서는 H/모든 Facet 구분과 D(H)가 함께 등장했다. | 5.1 Model 필요에서 Surface의 작은 반사 면이라는 뜻을 예고하고 5.6에서 H의 작은 거울 관계를 설명한다. 5.9에서 Model과 분포, 5.10에서 각 항으로 연결한다. 최종 최초: 5.1 Reflection L59 — 예를 들어 Lambert는 방향에 무관한 이상적인 Diffuse 응답을 설명하고, Phong은 관찰 방향에 따라 달라지는 Highlight를 간단한 관계로 만든다. 뒤에서 살펴볼 Microfacet Model은 Surface의 작은 반사 면들이 서로 … |
| 05 | Fresnel | 5.7 Blinn-Phong Reflection L735 — - Fresnel Effect를 표현하지 못한다. | 5.14 전까지 명칭 중심이며 acronym처럼 처리하면 오류가 생긴다. | 첫 사용에서 입사각에 따른 반사율 관계와 eponym을 설명한다. 5.14에서는 F0/경계/Facet 기준으로 천천히 확장한다. 최종 최초: 5.7 Blinn-Phong Reflection L605 — 또 같은 Material이라도 입사각에 따라 반사율이 달라지는 관계가 있다. 이를 **Fresnel**이라고 부른다. Fresnel은 약어가 아니라 물리학자 Augustin-Jean Fresnel의 이름에서 온 명칭이다. 5.14에서 이 관계와 계산 … |
| 05 | Energy Conservation | 5.7 Blinn-Phong Reflection L733 — - 여기서 소개한 정규화되지 않은 Response는 Energy Conservation을 보장하지 않는다. 별도의 정규화와 에너지 배분을 적용한 변형과 구분한다. | 정확한 정밀 조건이 하나의 문단이었다. | 음수 없음/추가 Energy 없음/해당 Material의 방향 교환 관계를 각각 설명하고 원래 정밀 제약을 Technical Note에 보존한다. 최종 최초: 5.5 Phong Reflection L429 — 물리적인 수동 Material은 받은 빛보다 더 많은 빛을 새로 반사해서 만들어 낼 수 없다. 이런 제약을 **Energy Conservation**, 즉 에너지 보존이라고 한다. 보기 좋은 Highlight 형태를 만든 식이 자동으로 이 조건까지 충… |
| 05 | NDF | 5.12 Normal Distribution Function (D) L1144 — Normal Distribution Function(NDF)은 특정 방향을 향하고 있는 Microfacet이 얼마나 존재하는지를 계산하는 함수이다. | 약어가 뒤에 나오고 density/normalization이 한 문단에 모였다. | 5.10에서 NDF Full Name과 Normal 방향 분포의 뜻을 함께 소개. 5.12에서 밀도와 정규화를 나눈다. 최종 최초: 5.10 Cook-Torrance Reflection L770 — 이 방향 분포를 나타내는 함수가 **NDF(Normal Distribution Function)**다. 여기서 Normal은 정규분포라는 통계 용어가 아니라 작은 면의 Normal을 뜻한다. 함수는 **D**라는 기호로 표기하며, 해당 방향의 분포 밀… |
| 05 | Geometry Function | 5.10 Cook-Torrance Reflection L960 — #### G (Geometry Function) | 역할은 있었으나 G를 최종 Reflection 자체로 받아들일 가능성이 남았다. | 처음 세 질문에서 Light/View 미세 차폐를 각각 정의. 5.13에서 예시와 Scene Vis/최종 Radiance 구분을 확장한다. 최종 최초: 5.10 Cook-Torrance Reflection L776 — 이웃 Microfacet이 Light 쪽 길을 막는 것을 **Shadowing**, Camera 쪽에서 반사 면을 가리는 것을 **Masking**이라고 한다. 이런 미세 차폐를 반영하는 항이 **Geometry Function G**다. G는 Sur… |
| 05 | Shadowing / Masking | 5.10 Cook-Torrance Reflection L964 — 즉, Self Shadowing과 Masking 효과를 계산한다. | 역할은 있었으나 G를 최종 Reflection 자체로 받아들일 가능성이 남았다. | 처음 세 질문에서 Light/View 미세 차폐를 각각 정의. 5.13에서 예시와 Scene Vis/최종 Radiance 구분을 확장한다. 최종 최초: 5.10 Cook-Torrance Reflection L776 — 이웃 Microfacet이 Light 쪽 길을 막는 것을 **Shadowing**, Camera 쪽에서 반사 면을 가리는 것을 **Masking**이라고 한다. 이런 미세 차폐를 반영하는 항이 **Geometry Function G**다. G는 Sur… |
| 05 | Single Scattering | 5.10 Cook-Torrance Reflection L978 — 대표적인 Single-scattering Microfacet Specular BRDF는 다음 구조를 가진다. | 원문 Microfacet BRDF에 단일 산란 범위가 정확히 있었다. English 이름의 뜻을 식보다 먼저 준비할 수 있었다. | 빛이 하나의 Microfacet에서 한 번 반사되는 기여를 계산하는 범위라고 식 전에 풀었다. 여러 미세면 사이 다중 반사와 구별했다. 최종 최초: 5.10 Cook-Torrance Reflection L794 — 여기서는 빛이 하나의 Microfacet에서 한 번 반사되는 기본 기여를 다룬다. 이 범위를 **Single Scattering**이라고 한다. 작은 면들 사이에서 여러 번 반사되는 모든 경로를 그대로 계산하는 Model은 아니다. |
| 05 | Scene Visibility / Vis | 5.10 Cook-Torrance Reflection L985 — 같은 Space의 Unit Vector와 양의 dot(N,L), dot(N,V)를 전제로 한다. 경계의 0 분모를 그대로 계산하지 않는다. D·G·F만 곱한 값은 이 BRDF 전체가 아니다. G는 Microfacet 사이의 차폐이며, 다른 Object… | 원문은 G와 Scene Vis를 이미 구분했다. 장면 Object 차폐와 미세면 차폐의 두 질문을 분리해 설명할 수 있었다. | Light에서 현재 Surface까지 경로가 열려 있는지를 먼저 풀고 Vis 표기를 View V와 구별했다. 미세 차폐 G와 장면 차폐의 역할 및 중복 적용 조건을 유지했다. 최종 최초: 5.10 Cook-Torrance Reflection L811 — ### Microfacet Occlusion and Scene Visibility |
| 05 | Distribution Density | 5.6 Half Vector L647 — Microfacet Theory에서는 주어진 L과 V 사이에 완전한 거울 Reflection을 만드는 Microfacet의 Normal이 H와 정렬된다. 모든 Microfacet이 H를 향하는 것이 아니라, 그 방향의 분포 밀도를 D(H)로 평가한다. | 밀도는 정확하나 정식 설명에서 1보다 큼·반구·Solid Angle·적분이 한 번에 등장했다. | 5.6에서는 지정 방향의 면들이 얼마나 모이는지 짧게 연결한다. 5.12에서 밀도와 영역 전체 비율을 먼저 설명. Note에서 방향의 입체 범위와 sr(Steradian)을 설명한 뒤 기존 정규화를 보존한다. 최종 최초: 5.6 Half Vector L535 — Microfacet Theory에서는 주어진 L과 V 사이에 완전한 거울 Reflection을 만드는 Microfacet의 Normal이 H와 정렬된다. 모든 Microfacet이 H를 향하는 것이 아니라, 그 방향의 분포 밀도를 D(H)로 평가한다. |
| 05 | Solid Angle / sr | 5.12 Normal Distribution Function (D) L1148 — 여기서 말하는 "Normal"은 정규분포(Normal Distribution)가 아니라 **Surface Normal**을 의미한다. 따라서 Normal Distribution Function은 Surface Normal의 방향 분포 밀도를 나타내는 … | 밀도는 정확하나 정식 설명에서 1보다 큼·반구·Solid Angle·적분이 한 번에 등장했다. | 5.6에서는 지정 방향의 면들이 얼마나 모이는지 짧게 연결한다. 5.12에서 밀도와 영역 전체 비율을 먼저 설명. Note에서 방향의 입체 범위와 sr(Steradian)을 설명한 뒤 기존 정규화를 보존한다. 최종 최초: 5.12 Normal Distribution Function (D) L928 — <summary>Technical Note — NDF Normalization and Solid Angle</summary> |
| 05 | GGX | 5.12 Normal Distribution Function (D) L1169 — - GGX (Trowbridge-Reitz Distribution) | 대체 분포 이름만 병기했다. Full Name 추측은 위험하다. | 알려진 Trowbridge–Reitz 이름과 긴 Tail의 역할을 풀고 확인되지 않은 확장명은 만들지 않는다. 최종 최초: 5.12 Normal Distribution Function (D) L953 — - GGX (Trowbridge-Reitz Distribution) |
| 05 | Tail | 5.12 Normal Distribution Function (D) L1171 — Beckmann과 GGX는 서로 다른 분포 모양을 가진다. GGX의 긴 Tail은 Highlight 바깥으로 퍼지는 응답을 표현하는 데 유용하다. 어떤 분포가 모든 Material에 항상 더 정확한 것은 아니다. Roughness에서 분포 Parame… | 원문 GGX의 긴 꼬리 설명은 있었다. 분포 중심에서 먼 방향 응답이 이어지는 의미를 영문 명칭과 연결했다. | 분포 중심에서 멀어진 방향에도 응답이 이어지는 부분의 의미를 GGX의 긴 Tail과 연결했다. 최종 최초: 5.12 Normal Distribution Function (D) L957 — 분포의 중심에서 멀어진 방향에도 낮은 응답이 남는 바깥 부분을 **Tail**, 즉 꼬리라고 한다. |
| 05 | Smith / Schlick-GGX | 5.13 Geometry Function (G) L1259 — - Smith Geometry Function | 원문은 구현별 G 근사 범위를 정확히 제한했다. 새 공식이나 정확도 단정을 더하지 않고 Model/근사 이름을 짧게 연결했다. | G를 평가하는 Model/근사 이름으로 짧게 연결하고 구체적인 식과 Parameter 대응은 선택한 구현에서 확인해야 한다는 기존 범위를 유지했다. 최종 최초: 5.13 Geometry Function (G) L1027 — - Smith Geometry Function |
| 05 | Reflectance / F0 | 5.14 Fresnel (F) L1335 — F = F0 + (1 - F0) * pow(1 - cosTheta, 5) | 여러 정의·광학식·수치·Metallic·표시 조건이 몰려 있었다. | 정면 기준값 → 근사의 목적 → Angle의 기준 → 보존식 → 광학 수치 Note → Material input → 표시 Note로 분리한다. Dielectric은 Chapter 04를 회상한다. 최종 최초: 5.14 Fresnel (F) L1073 — 각도에 따라 반사율을 계산하려면 먼저 기준값이 필요하다. **F0**는 빛이 경계면에 정면으로 들어올 때의 Reflectance다. 이 기준값을 알고 현재 Angle을 알면 반사율 변화의 근사를 만들 수 있다. |
| 05 | Interface / Dielectric / IOR | 5.14 Fresnel (F) L1338 — F0는 정면 입사 Reflectance이다. 매끄러운 Interface에서는 cosTheta가 입사 방향과 Interface Normal의 Dot Product이며, Microfacet Specular에서는 반사에 기여하는 Facet Normal H를… | 여러 정의·광학식·수치·Metallic·표시 조건이 몰려 있었다. | 정면 기준값 → 근사의 목적 → Angle의 기준 → 보존식 → 광학 수치 Note → Material input → 표시 Note로 분리한다. Dielectric은 Chapter 04를 회상한다. 5.14의 굴절률/η는 유지하며 원문에 없는 IOR 약어를 새로 도입하지 않았다. IOR의 이름 풀이는 07 후속 감사 항목이다. 최종 최초: 5.14 Fresnel (F) L1059 — 일반적인 반사 관계에서 비스듬한 입사각은 정면 입사보다 높은 Reflectance와 연결될 수 있다. 그래서 매끄러운 Interface를 낮은 각도에서 볼 때 반사가 강하게 보이는 사례가 있다. **Interface**는 빛이 만나는 서로 다른 매질의… |
| 05 | Schlick Approximation | 5.14 Fresnel (F) L1330 — ### Schlick Approximation | 여러 정의·광학식·수치·Metallic·표시 조건이 몰려 있었다. | 정면 기준값 → 근사의 목적 → Angle의 기준 → 보존식 → 광학 수치 Note → Material input → 표시 Note로 분리한다. Dielectric은 Chapter 04를 회상한다. 최종 최초: 5.14 Fresnel (F) L1079 — ### Schlick Approximation |
| 05 | Radiometry / Energy / Power | 5.1 Reflection L78 — 이번 Chapter에서는 각 모델의 가정과 한계를 비교하고, Microfacet 관점을 Cook-Torrance로 연결한 뒤 Radiometry와 BRDF를 살펴본다. 아래 흐름은 이 Chapter의 학습 순서다. | 학습 경로에는 이름만 있고, 정식 목록에는 단위 정의로 물리량이 동시에 등장했다. | 5.1 예고에서 물리량을 측정하는 체계라는 뜻을 짧게 설명한다. 5.15에서 서로 다른 측정 질문을 개별 Subsection으로 준비하고 정확한 네 정의/단위를 마지막에 비교한다. 최종 최초: 5.1 Reflection L67 — 앞에서 예고한 BRDF로 서로 다른 Reflection Model을 같은 Surface 응답의 질문으로 비교할 수 있다. 먼저 각 모델을 이해한 뒤, 5.16에서 이 공통 정의와 정확한 물리량을 연결한다. 그때 필요한 빛의 양을 읽기 위해, 에너지 전… |
| 05 | Radiant Flux | 5.15 Radiometry L1413 — - **Radiant Flux(Φ)** : 단위 시간당 전달되는 Radiant Energy, 단위 W (= J/s). | 학습 경로에는 이름만 있고, 정식 목록에는 단위 정의로 물리량이 동시에 등장했다. | 시간당 전달되는 전체 Radiant Energy의 흐름이라고 질문에서 시작하고 W 단위와 Power/Energy 차이를 유지했다. 최종 최초: 5.15 Radiometry L1184 — ### Radiant Flux: How Much Light Is Transferred per Time? |
| 05 | Radiance | 5.4 Lambert Reflection L349 — > **같은 Irradiance를 받는 Surface의 Outgoing Radiance는 관찰 방향에 의존하지 않는다.** | 정확한 가정이지만 독자가 물리량을 알기 전에 등장했다. | 관찰 방향으로 나가는 빛을 측정하는 기준을 짧게 소개하고 투영 면적과 단위는 5.15에서 확장한다. 최종 최초: 5.4 Lambert Reflection L305 — 이 Surface에서 특정 관찰 방향으로 나가는 빛을 표현할 때는 **Outgoing Radiance**를 사용한다. Radiance는 방향과, 그 방향에서 보이는 Surface의 투영 면적을 함께 고려하는 물리량이다. 정확한 단위는 5.15에서 비교… |
| 05 | Radiant Intensity | 5.15 Radiometry L1416 — - **Radiant Intensity(I)** : 광원이 단위 Solid Angle로 방출하는 Flux, 단위 W/sr. | 학습 경로에는 이름만 있고, 정식 목록에는 단위 정의로 물리량이 동시에 등장했다. | 광원이 특정 방향 범위로 내보내는 출력의 밀도를 설명하고 W/sr 단위를 Irradiance/Radiance와 비교했다. 최종 최초: 5.15 Radiometry L1200 — ### Radiant Intensity: How Much Is Sent into a Directional Range? |
| 05 | Anisotropic | 5.17 BRDF Inputs and Output L1475 — \\| Tangent Basis \\| Anisotropic Model처럼 접선 방향이 필요한 경우의 기준 \\| | 표에 예외 입력이 먼저 나왔다. | 결 방향에 따라 분포가 달라지는 문제와 접선 기준의 필요를 표 전에 설명한다. 최종 최초: 5.17 BRDF Inputs and Output L1327 — 어떤 Material은 Surface를 따라가는 방향에 따라서도 반사 분포가 달라진다. 한 방향으로 결이 있는 금속을 떠올리면 된다. 이런 방향 의존 분포를 **Anisotropic**, 즉 이방성이라고 한다. |
| 05 | Rendering Equation / d / integral | 5.18 BRDF Definition and Rendering Equation L1498 — ## 5.18 BRDF Definition and Rendering Equation | 기호의 의미를 Formula 뒤에서 파악해야 했다. | 작은 방향 기여를 설명하고 dEi/dLo/방향 합/Emission의 뜻을 준비한 뒤 정확한 Formula를 제시한다. 최종 최초: 5.10 Cook-Torrance Reflection L815 — G는 Microfacet의 미세 차폐를 반영한다. Scene Visibility를 G로 대신하거나, 이미 G를 계산했다는 이유로 다른 Object의 그림자를 생략하지 않는다. 반대로 입력 Light가 이미 차폐된 값이라면 같은 Scene 차폐를 다시 … |
| 05 | Non-negativity / Reciprocity | 5.18 BRDF Definition and Rendering Equation L1526 — 일반적인 수동 반사 Material에는 Non-negativity와 Energy Conservation이 필요하다. 고정된 입사 방향에 대해 fr·max(0,N·ωo)를 출사 반구 전체에서 적분한 값이 1을 넘지 않아야 한다. 일반적인 Reciproc… | 정확한 정밀 조건이 하나의 문단이었다. | 음수 없음/추가 Energy 없음/해당 Material의 방향 교환 관계를 각각 설명하고 원래 정밀 제약을 Technical Note에 보존한다. 최종 최초: 5.18 BRDF Definition and Rendering Equation L1476 — 보기 좋은 응답이라고 해서 수동 Material의 물리적 조건을 자동으로 만족하는 것은 아니다. 먼저 반사 응답이 음수가 되면 안 된다. 이를 **Non-negativity**, 즉 비음수 조건이라고 한다. |
| 05 | Diffuse Reflectance / rho / pi | 5.19 Lambertian BRDF L1543 — fr_diffuse = ρ / π | 원문 5.19에 ρ/π·단위·수치 검산이 정확했다. ρ와 정규화, Ei의 Cosine 포함 여부를 식 전에 준비할 수 있었다. | ρ의 반사율 의미와 1/π 정규화, Ei의 Cosine 포함 여부를 Formula 전에 설명했다. 기존 식·단위·수치 검산과 교육용 Lighting 범위를 유지했다. 최종 최초: 5.18 BRDF Definition and Rendering Equation L1516 — 이제 5.4의 Lambert를 같은 BRDF 정의로 다시 볼 수 있다. 마지막 절에서는 NdotL과 Material 응답 ρ/π가 왜 다른 역할인지 확인한다. |
| 05 | Surface Normal / Geometric Normal / Shading Normal | 5.2 Surface Normal L117 — ## 5.2 Surface Normal | 바닥/벽/천장 직관은 좋으나 정확성 조건이 한 문단에 모였다. | 수직 기준의 필요를 먼저 설명하고 Orientation/Normal 종류/Unit 조건을 나눈다. 최종 최초: 5.1 Reflection L107 — 빛의 반사를 설명하려면 먼저 Surface가 어느 방향을 향하는지 알아야 한다. 다음 절에서는 그 기준이 되는 **Surface Normal**을 살펴본다. |
| 05 | Shading Point | 5.7 Blinn-Phong Reflection L741 — 앞서 비교한 모델은 각 Shading Point의 Response에 Microfacet 분포·차폐·Fresnel을 명시적으로 결합하지 않았다. 현미경으로 보이는 Surface의 미세한 구조를 반영하려면 다른 관점이 필요하다. | 원문은 Microfacet 설명에서 이미 현재 평가 지점의 범위를 밝혔다. 재작성한 앞쪽 예고에 이름이 먼저 드러나 설명 위치를 맞출 필요가 있었다. | 5.7의 첫 예고에서 현재 Surface 응답을 평가하는 지점이라는 뜻을 붙였다. 최종 최초: 5.7 Blinn-Phong Reflection L614 — **Micro Geometry**는 화면에서 하나의 Surface로 보이는 영역 안에 있는 작은 구조를 말한다. 이 문제는 Mesh 전체가 하나의 평면이라고 가정했다는 뜻과 다르다. 현재 Surface 응답을 평가하는 지점을 **Shading Poin… |
