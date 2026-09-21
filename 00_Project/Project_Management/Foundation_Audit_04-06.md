# Foundation Audit — Chapter 04–06

Phase 1A — Text Audit · 2026-09-19

## 1. Executive Summary

Chapter 04의 **Texture / Parameter → Surface Property** 설명은 비교적 잘 완성되어 있다. Texture 전체와 현재 위치의 Sample 결과를 구분하고, Roughness를 단순 밝기 조절값으로 보지 않으며, Normal Map의 Encoding / Decode / Space 변환을 단계별로 연결한다. 이 부분은 보존해야 한다.

그러나 **Material → Lighting → PBR이라는 세 장의 연결은 아직 완결되지 않았다.** 실제 구성은 Chapter 04 Material Architecture → Chapter 05 Reflection / BRDF → Chapter 06 Modern Real-Time Rendering이다. 요청과 Roadmap의 Chapter 05 Lighting Fundamentals / Chapter 06 PBR Fundamentals와 다르다. PBR의 D/G/F를 먼저 소개한 뒤 Direct / Indirect Lighting을 설명하며, Chapter 04에서 예고한 Metallic의 반사 특성 변화와 Base Color의 역할은 이후 두 장에서 구체적으로 이어지지 않는다.

가장 큰 기술적 문제는 다음 세 가지다. 첫째, Chapter 05가 **BRDF의 값과 반사된 빛의 양을 혼동**하고 Lambert의 Cosine Factor와 Lambert BRDF를 연결하지 않는다. 둘째, Chapter 06의 최종 흐름도가 **Reflection / IBL → BRDF → HDR**를 서로 독립적인 순차 처리 단계처럼 배치한다. 셋째, Direct / Indirect라는 Light Path 분류와 IBL이라는 입력·평가 방식, Reflection이라는 현상의 관계가 섞여 있다. 이 상태로는 Property를 바꾸면 어떤 계산을 통해 결과가 달라지는지 설명하기 어렵다.

Chapter 07의 Stylized Rendering으로 넘어가기 전에는 BRDF와 Lighting 결과의 경계를 바로잡고, Metallic / Base Color / F0 / Diffuse·Specular 에너지 배분의 최소 연결을 보완해야 한다. PBR의 기준을 먼저 알아야 어떤 관계를 의도적으로 변형하는지 설명할 수 있다. 수학적 유도나 Engine 구현을 크게 늘릴 필요는 없다. 핵심 식의 입력·출력과 간단한 검증 예시를 넣는 것이 우선이다.

**보존할 강점:** 4.1~4.4의 Data 구분, 4.5의 Color / Numeric Data 구분, 4.6의 Normal Map과 Height / Geometry 구분, 5.9~5.14의 D/G/F가 필요한 이유, 6.6의 HDR Environment Map과 HDR 계산의 역할 구분이다. 이 Audit은 문서 길이를 줄이는 작업이 아니다. 개념적 연결이 새로 생기는 반복은 유지하고 같은 정의·예고·요약을 반복하는 부분만 축약한다.

### Scope and Evidence

- 검토 루트: `C:\Users\kmcoo\Desktop\PW\ASF_Review`. 이번 첨부에도 이전 경로 표기가 있었지만, 직전 대화에서 사용자가 정정한 실제 경로를 적용했다.
- 실제 Foundation 위치: `00_Foundation`. 해당 위치의 Chapter 04~06 Markdown 세 파일 전체를 읽었다. Chapter 01~03 및 07~09는 이번 Audit에서 읽거나 재평가하지 않았다.
- 판단 기준: 사용자 지시에 따라 ASF-000~003을 최우선으로 적용하고 `ASF_Standard.md`, Roadmap의 Chapter 계획을 참고했다. 같은 대화에서 확인한 DecisionLog의 과거 구성은 현재 요청을 대체하지 않는다.
- 기준 파일: `00_Project/ASF/ASF-000_Project_Principles.md`, `ASF-001_Naming_Philosophy.md`, `ASF-002_Rendering Architecture.md`, `ASF-003_Documentation_Standard.md`, `00_Project/ASF_Standard.md`, `00_Project/Project_Management/Roadmap.md`.
- 원본 수정, 파일명 변경, Figure 수정, 자동 Refactoring은 수행하지 않았다. Figure의 파일명·참조·경로·존재 여부만 확인했다.
- 외부 자료 검색, Engine 실행, 이미지 열기는 하지 않았다. 근거는 지정 루트의 문서이며 이 보고서의 기술 판단은 Text Audit이다. 확인이 필요한 플랫폼 사양·성능·역사적 단정은 `Needs Technical Verification`으로 남겼다.
- 행 번호는 Audit 시점 원본의 행이다. 아래 C04 / C05 / C06은 파일 식별자이며, Issue ID와 함께 후속 편집 대조에 사용한다.

| ID | 검토 파일 | 전체 범위 |
|---|---|---|
| C04 | `00_Foundation/Chapter04_MaterialArchitecture.md` | 1~2739행, 4.1~4.8 |
| C05 | `00_Foundation/Chapter05_Reflection_BRDF.md` | 1~3450행, 5.1~5.19 및 Part / Summary |
| C06 | `00_Foundation/Chapter06_ModernRealtimeRendering.md` | 1~916행, 6.1~6.9 |

### Figure Reference Metadata

| Chapter | 본문 참조 / 고유 파일 | 범위 | 경로·번호 확인 |
|---|---:|---|---|
| 04 | 8 / 8 | `Figures/Chapter04/Fig4_01.png`~`Fig4_08.png` | 모두 존재, 중복·번호 공백 없음 |
| 05 | 14 / 14 | `Figures/Chapter05/Fig5_01.png`~`Fig5_14.png` | 모두 존재, 중복·번호 공백 없음 |
| 06 | 10 / 10 | `Figures/Chapter06/Fig6_01.png`~`Fig6_10.png` | 모두 존재, 중복·번호 공백 없음 |

총 32개 참조가 Markdown 기준 상대 경로에 존재하며 ASF-003의 `Fig<Chapter>_<NN>.png` 형식과 Chapter 번호 관계를 지킨다. Chapter 05 Figure 폴더에는 `Fig5_15.png`도 존재하지만 해당 본문에는 참조가 없다. 이것만으로 반드시 삽입해야 한다고 판정하지 않는다(C5-12). Section 수와 Figure 수가 같아야 한다는 규칙도 적용하지 않는다. 시각적 정확성은 확인하지 않았다.

## 2. Global Issues for Chapter 04~06

### G01 — 계획과 실제 Chapter 역할이 다름

- Section: C04~C06 전체; Roadmap 193~203행.
- Severity: High
- Action: Move, Merge, Rewrite
- Issue: Material → Lighting → PBR 계획과 달리, PBR Reflection 이론이 C05에 집중되고 기본 Direct / Indirect Lighting은 C06에서 뒤늦게 등장한다.
- Reason: 용어를 준비하는 순서와 Chapter별 책임이 어긋나며 C04의 Metallic 설명 예고가 완결되지 않는다. 단순한 제목 차이보다 학습 연결의 문제다.
- Related Section / Chapter: 4.2, 4.8; 5.8~5.19; 6.1~6.5; G03.
- Recommendation: 후속 편집에서 C04는 Material Data, C05는 Light 입력·방향·Diffuse / Specular·Visibility 및 기본 Lighting, C06은 BRDF·Microfacet·PBR Property 연결과 Direct / Environment 평가의 통합을 맡는 구성을 우선 검토한다. C05의 D/G/F 설명은 C06의 후보, C06의 Direct / Indirect 기본 정의는 C05의 후보가 된다. HDR / Tone Mapping / Output은 PBR 계산 결과를 화면으로 연결하는 마무리로 보존한다. 이것은 Foundation 내부 재배치 제안이며 실제 이동은 수행하지 않았다.

### G02 — BRDF, Lighting Response, 화면 결과의 Data 경계

- Section: C05 5.17~5.19; C06 6.1, 6.9.
- Severity: High
- Action: Rewrite, Expand
- Issue: BRDF가 반사된 빛 자체를 출력하는 것으로 설명되고, 계산된 Reflection에 나중에 BRDF를 적용하는 것처럼 이어진다.
- Reason: BRDF는 Surface의 방향별 반사 응답을 나타내며 입사광·기하학적 가중과 결합되어야 Outgoing Radiance를 얻는다. Tone Mapping 이후 Display Color는 또 다른 값이다.
- Related Section / Chapter: C5-01, C5-02, C6-01; ASF-000 Flow Before Implementation, ASF-002 Rendering Data.
- Recommendation: `Material Property → BRDF 값`, `입사광 + BRDF + 각도 / 가시성 → Lighting Contribution`, `Contribution 합 + Emission → Linear HDR Result`, `Output Transform → Display Color`의 Data 경계를 세 장에 공통으로 적용한다. BRDF / Reflection을 새 GPU Stage 이름으로 만들지 않는다.

### G03 — Metallic / Base Color / Reflectance 연결이 종료되지 않음

- Section: C04 4.2(266~347행), 4.5(1251~1264 / 1393~1397행); C05 5.11~5.14; C06 전체.
- Severity: High
- Action: Expand, Rewrite
- Issue: Metallic 0/1은 소개하지만 실제 Diffuse / Specular 응답 변화, F0, Base Color의 금속·비금속별 의미를 세 장 안에서 연결하지 않는다. Base Color / Albedo / Diffuse Color도 관계 설명 없이 묶인다.
- Reason: Roughness와 D/G/F만으로 Metallic-Roughness Workflow를 이해했다고 볼 수 없다. Metallic을 단순 반사 강도, Base Color를 항상 Diffuse Color로 해석할 위험이 크다.
- Related Section / Chapter: 4.2의 “이후 PBR과 BRDF” 예고; C5-06~08.
- Recommendation: 기본적인 불투명 Metallic-Roughness 모델을 범위로 선언한다. 비금속에서는 Base Color가 주로 Diffuse 색에, 금속에서는 주로 Specular의 색을 가진 Reflectance에 쓰이며 금속의 Diffuse 성분은 억제된다는 연결을 둔다. F0는 정면 입사 반사율, Roughness는 분포를 제어하는 별도 입력으로 구분한다. 에너지 배분을 한 개념도로 설명하되 특정 Engine의 고정 상수나 모든 재질에 대한 보편 법칙으로 확대하지 않는다. Albedo가 이 문서에서 뜻하는 Reflectance와 Base Color의 관계를 최초 사용에 명시한다.

### G04 — 반복의 목적과 주 설명 위치가 불분명함

- Section: C04 4.1~4.3 / 4.8; C05의 Callback / 핵심 요약 및 5.16~5.19; C06 6.8.
- Severity: Medium
- Action: Shorten, Merge, Keep
- Issue: 동일 정의와 모델 목록이 반복되는 부분에 비해 장 사이에서 새롭게 연결할 계산 관계는 약하다.
- Reason: 반복된 단어 수보다 새 Context에서 무엇이 달라지는지 드러나지 않는 것이 문제다. ASF-003은 필요한 원리 설명을 길이만으로 줄이지 않도록 한다.
- Related Section / Chapter: Section 4 Duplication Map.
- Recommendation: Color 입력 해석은 4.5, Roughness의 Material 역할은 4.2, 분포와의 관계는 PBR 절처럼 설명 책임을 나눈다. 동일 정의의 재시작은 참조로 줄이고 Material → BRDF → Environment Response처럼 역할이 바뀌는 반복은 유지한다.

### G05 — Heading과 Chapter / Section 참조가 혼재함

- Section: C05 전체; C06 전체; C04 4.3의 788행.
- Severity: Low
- Action: Rewrite
- Issue: C05에는 H1 25개, H2 137개, H3 7개가 있고 C06에는 H1 9개, H2 55개, H3 1개가 있다. C05 / C06은 표준 Chapter 제목 없이 Part 또는 개별 절이 H1이다. 내부 제목은 Korean 중심이며 같은 Chapter의 다음 Section을 “다음 장 / Chapter”라고 부르는 표현이 반복된다.
- Reason: ASF-003의 Chapter / Major Section / Internal Heading 역할 및 English Section Title 기본 원칙과 다르다.
- Related Section / Chapter: C04는 H1 1개, H2 8개, H3 86개로 기본 계층을 지킨다.
- Recommendation: 각 파일에 Chapter H1을 두고 `## 5.x / 6.x`, 내부 `###`로 맞춘다. Part는 탐색용 구분으로 유지하되 Chapter와 같은 깊이를 남발하지 않는다. “다음 절 5.9”처럼 정확한 범위를 쓴다. `### 4.1.1`식 내부 번호나 H4 이상 남용은 발견하지 못했으므로 별도 오류로 만들지 않는다.

### G06 — 학습 예고와 실제 다음 내용의 불일치

- Section: C05 1147~1151행, 3430~3440행; C06 5행 / 828행; C04 788행.
- Severity: Medium
- Action: Rewrite
- Issue: 5.7은 바로 다음을 Microfacet Theory라고 예고하지만 다음 절은 5.8 Reflection Model의 한계다. C05 끝은 다음 Chapter에서 PBR Material 구성을 다룬다고 하지만 C06은 Rendering Pipeline·환경·출력 중심이다. C06은 이전 학습의 순서를 바꾸어 요약하거나 HDR을 앞선 Chapter에서 배운 것처럼 서술한다.
- Reason: 독자가 기대한 다음 질문의 답을 찾기 어렵다. G01의 구조 차이가 실제 참조 문장에도 반영되어 있다.
- Related Section / Chapter: G01; C04의 Color Space는 바로 4.5에 있다.
- Recommendation: 현재 Section 또는 후속 재구성의 실제 학습 목표로 예고를 맞춘다. 4.3은 4.5를 직접 가리킨다. Chapter09 최적화·Chapter07 NPR 예고는 기능상 자연스럽지만 대상 본문은 이번 범위 밖이므로 참조 내용의 충족 여부는 판정하지 않는다.

### Foundation / Advanced Boundary — Keep

4.7의 Parameter / Instance 구조와 4.4의 Sampling 비용 주의는 Foundation에 적절하다. 짧은 Production 맥락을 소개했다는 이유만으로 Advanced로 이동할 필요는 없다. 세 파일에는 상세 HLSL 최적화, 통제 성능 실험, Character별 Production Case Study가 과도하게 포함되어 있지 않다. **Move to Advanced로 확정한 절은 없다.** 오히려 BRDF 입력·출력 관계에 필요한 최소 수학은 보완 대상이다. GGX / Smith의 상세 유도나 Engine 구현은 별도의 심화 범위로 남길 수 있다.

## 3. Chapter-by-Chapter Audit

### Chapter 04 — Material Architecture

**Overall Assessment**

4.1~4.2의 Material 역할 → 4.3~4.4의 값 저장·Sampling → 4.5의 해석 → 4.6의 Direction 복원 → 4.7의 조절 Interface → 4.8의 종합 흐름은 자연스럽다. Texture가 현재 Surface 위치의 값을 제공한다는 핵심은 충분히 설명되어 있으므로 “Texture Sample과 Scalar 관계가 전혀 없다”고 판정하지 않는다. 보완할 부분은 Mask의 소비 방식, Static Parameter의 예외, TBN과 Engine 자동 처리의 조건, 다음 Lighting 절로의 구체적인 연결이다.

**Issues**

#### C4-01 — Mask를 Scalar의 역할로 설명하는 연결 부족

- Section: 4.3, 733~764행; 4.7, 1990~2001행; 4.8, 2533~2547행.
- Severity: Medium
- Action: Expand
- Issue: Mask가 Packing 채널·Threshold·Material Input 목록에 등장하지만 0/1 및 중간값의 소비 의미는 설명되지 않는다.
- Reason: Scalar / Vector는 값의 형식이고 Mask는 그 값을 제어·선택에 사용하는 역할이다. Texture 전체와 한 위치의 Mask Value를 구분한 뒤 실제 어디에 쓰는지까지 이어져야 한다.
- Related Section / Chapter: ASF-002 Mask Architecture; 4.2 Metallic Transition.
- Recommendation: `RGBA Sample → Channel 선택 → 현재 Pixel의 Scalar Mask → Blend / 강도 조절 / Threshold` 예시 하나를 넣는다. 예를 들어 `lerp(A,B,m)`에서 m=0/1/0.5의 의미를 설명하되 Mask가 항상 이진값이거나 독립적인 물리 Surface Property인 것처럼 정의하지 않는다.

#### C4-02 — Normal Decode의 범위와 TBN Basis Space

- Section: 4.6, 1642~1650행, 1762~1832행, 1902~1924행; 4.8, 2493~2519행.
- Severity: Medium
- Action: Expand, Rewrite, Needs Technical Verification
- Issue: RGB Encoding / Decode 설명은 있지만 “R=x”의 개념적 대응과 저장값 대응이 잠시 섞이고, TBN의 Basis가 어떤 Space로 표현되어야 하는지 명시되지 않는다. Engine의 Normal Sample이 이미 Decode한 경우의 경계도 없다.
- Reason: 이 장의 Decode 식은 일반적인 RGB Encoding 예시로 유효하다. 그러나 모든 Normal Texture 포맷·Sampler 출력에 수동 `2*RGB-1`을 다시 적용하면 안 된다. TBN 출력 Space는 Basis의 Space에 달려 있다.
- Related Section / Chapter: 4.5의 자동 Color Decode; 4.8 Normal Data Flow.
- Recommendation: R/G/B는 성분을 Encoding한 값이라는 표현을 일관되게 사용한다. World Normal 예시에서는 T/B/N도 World Space임을 명시하고 재정규화 흐름을 보존한다. 특정 Engine의 Decode·채널 복원 여부는 Technical Verification 후 작성한다. Basis 및 G Channel Convention의 일치가 필요하다는 짧은 조건을 더하되 TBN 생성 알고리즘 전체는 확장하지 않는다.

#### C4-03 — 일반 Parameter 요약이 Static Switch 설명과 충돌

- Section: 4.7, 2069~2098행, 2130~2134행, 2166~2170행; 4.8, 2611~2633행.
- Severity: Medium
- Action: Rewrite, Expand
- Issue: Static Switch는 Logic의 포함 여부와 Permutation을 바꾼다고 설명한 뒤, Parameter는 Logic을 바꾸지 않고 Instance는 항상 같은 Shader 구조를 그대로 사용한다고 일반화한다.
- Reason: 같은 Parent Graph 재사용과 동일하게 Compile된 Shader 코드 재사용은 다르다. 같은 장의 예외가 요약에서 사라진다.
- Related Section / Chapter: 4.7 Real-Time Adjustment.
- Recommendation: Scalar / Vector / Texture Override와 Static 기능 선택을 구분한다. 같은 Parent 구조를 공유하되 Static 설정에 따라 Shader Variant가 달라질 수 있음을 Instance 요약에도 유지한다. “빠르게 조절”을 모든 Parameter의 Runtime 변경 가능성으로 읽지 않도록 범위를 명시한다. 특정 Engine 버전의 Compile / Runtime 동작은 별도 검증 대상으로 남긴다.

#### C4-04 — Sampling / sRGB Decode 도식의 해석 범위

- Section: 4.4, 1001~1051행; 4.5, 1239~1247행, 1335~1341행; 4.8, 2465~2471행.
- Severity: Medium
- Action: Rewrite, Needs Technical Verification
- Issue: Filtering 설명과 `Texture Sampling → sRGB Decode` 도식을 함께 읽으면 Encoding된 색을 먼저 보간한 뒤 Decode하는 실제 연산 순서로 오해할 수 있다.
- Reason: “Shader가 받아 사용하는 값의 의미”를 나타내는 개념도인지 Sampler 내부 순서인지 구분해야 한다. Engine 자동 Decode 여부와 수동 변환은 다른 문제다.
- Related Section / Chapter: 6.8 Color Space.
- Recommendation: 도식이 의미적 단계임을 밝히고 sRGB 처리가 포함된 Sample 결과는 Linear Color로 공급된다고 표현한다. Decode와 Filtering의 정확한 순서를 서술하려면 대상 Texture Format / Sampler 사양을 검증한다. 미검증 Hardware 동작을 확정하지 않는다.

#### C4-05 — Mip 선택 기준이 Object 화면 크기로만 설명됨

- Section: 4.4, 1055~1083행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: Mip Level이 Surface의 화면 크기에 따라 정해진다는 설명만 있어 UV Tiling과 방향에 따른 Texture Footprint가 빠진다.
- Reason: Camera 거리 설명은 좋은 출발점이지만 같은 화면 크기에서도 UV 변화량이 다르면 필요한 Sampling 범위가 달라진다. 뒤의 UV Tiling Parameter와도 연결된다.
- Related Section / Chapter: 4.7 UV Tiling.
- Recommendation: 핵심 기준은 한 Screen Pixel이 Texture에서 덮는 범위라고 한 문장 추가한다. 거리·해상도·UV Tiling·기울기가 그 범위에 영향을 준다는 정도면 충분하다. Derivative 계산이나 Anisotropic Filtering 구현까지 확장할 필요는 없다.

#### C4-06 — 종합 절에서 데이터가 합쳐지는 지점이 약함

- Section: 도입부 37~47행; 4.8, 2557~2605행 및 2695~2739행.
- Severity: Medium
- Action: Rewrite, Shorten, Expand
- Issue: 처음 도식은 Material Input→Texture/Parameter로, 후반은 Texture/Parameter→Material Input으로 표현한다. N은 Material Normal에서 복원되었는데 Lighting Inputs Come from the Scene 목록에도 다시 나타나며 합쳐지는 지점이 약하다. 종합 절은 속성별 설명을 재소개한 뒤 다음 Lighting 모델의 입력 계약으로 끝나지 않는다.
- Reason: Material Input이 Graph 소켓인지 현재 Pixel의 평가된 Property인지 일관되어야 한다. N은 Scene에서 독립적으로 새로 받는 값이 아니라 Geometry와 Material 처리로 준비된 Shading Normal이다.
- Related Section / Chapter: 4.1의 Geometry / Material / Lighting 분류; C05 5.2~5.4.
- Recommendation: Texture / Parameter Source → 평가된 Surface Property로 방향을 통일한다. Geometry Normal과 Normal Map 경로가 하나의 Shading N으로 합쳐지고 Light / Camera에서 L/V가 준비되는 모습을 보인다. 4.8은 이 합류와 다음 계산에 집중하고 이미 설명한 Property 정의는 참조로 축약한다.

**Important Keep Sections**

| Section | 보존할 설명 |
|---|---|
| 4.1 | Texture / Material / Shader 구분; 같은 Geometry·Light에서 Property 변화의 의미 |
| 4.2 | Base Color≠최종 Pixel Color, Roughness≠단순 밝기, Emissive가 반드시 주변을 비추지는 않는다는 조건 |
| 4.3 | Texture 전체가 아니라 현재 UV의 Sample 결과를 사용하는 설명, 채널별 Scalar Packing과 비용의 조건부 표현 |
| 4.4 | Vertex UV→Interpolated UV→Sample, Texel과 Pixel 구분, Filtering과 Addressing, 비용≠개수만으로 판단 |
| 4.5 | Color / Numeric Data 의미에 따른 해석, Import Setting으로 값이 달라지는 원인 |
| 4.6 | Normal Map≠Height Map, Encoding 수치 예시, Silhouette·Collision·Shadow Geometry 불변, Normalize까지의 흐름 |
| 4.7 | Logic과 조절 가능한 Data의 분리, Parent / Instance 관계, 필요한 Parameter만 노출하는 이유 |
| 4.8 | 여러 Source가 평가된 Material Input으로 모인다는 통합 목적 — 반복 재정의만 축약 |

### Chapter 05 — Reflection / BRDF

**Overall Assessment**

현실의 관찰과 질문을 출발점으로 모델을 소개하려는 방식은 ASF와 잘 맞는다. 하지만 왜 필요한지 반복해서 강조하는 데 비해 모델이 실제로 무엇을 계산하는지 확인할 최소 정의가 부족하다. 5.15~5.19에서 BRDF를 정확히 정리하지 못해 앞의 Cosine / D/G/F 설명도 하나의 계산으로 닫히지 않는다. 모델 선택의 학습 순서를 역사적 발전 계보나 계산 비용의 보편 법칙으로 단정하는 표현도 완화해야 한다.

**Issues**

#### C5-01 — BRDF 출력을 빛의 양 또는 단순 비율로 정의

- Section: 5.17, 2958~3008 / 3068~3070행; 5.18, 3127~3163행.
- Severity: High
- Action: Rewrite, Expand
- Issue: BRDF의 출력은 “관찰자 방향으로 반사되는 빛의 양”이라고 하고, 다시 “특정 방향으로 반사되는 빛의 비율”이라고 한다. 빛의 세기와 Material 속성이 함수 표기에서 생략되는 이유도 함께 묶는다.
- Reason: BRDF 값은 반사 Radiance 자체가 아니며 단순 0~1 비율도 아니다. 입사 Irradiance의 미소 기여에 대한 반사 Radiance의 응답으로, 단위는 sr^-1이다. Material 속성은 함수의 형상을 결정하는 Parameter이고 Light 세기는 별도의 Lighting 입력이다.
- Related Section / Chapter: 5.15 Radiometry, 5.19 Lambert; G02; 6.1.
- Recommendation: `f_r = dL_o / dE_i`의 의미와 단위를 짧게 소개한다. 방향·Material을 주면 BRDF 값을 얻고, 입사광과 결합해야 L_o 기여가 나온다는 입력·출력 표를 둔다. Material / 위치 / 파장 의존성을 표기 편의상 생략할 수 있다는 점과 Light 세기를 BRDF 값에 포함하지 않는다는 점을 구분한다. BRDF 값 자체가 1보다 클 수 있는 것과 에너지 보존 위반을 혼동하지 않도록 한다.

#### C5-02 — Lambert Cosine Factor와 Lambert BRDF를 동일시할 가능성

- Section: 5.4, 524~554 / 614~620행; 5.19, 3270~3328행.
- Severity: High
- Action: Rewrite, Expand
- Issue: 제시한 식은 `Diffuse=max(0,N·L)`뿐인데 뒤에서는 이 Lambert Reflection이 BRDF라고 선언한다. Material의 Diffuse Reflectance와 1/π 관계가 없다.
- Reason: Cosine은 입사광의 투영면적 가중이고 Lambert BRDF는 `ρ_d/π`이다. 앞의 식을 BRDF 자체로 기억하면 Rendering Equation에서 Cosine을 중복 곱하거나 Material Color를 잃는다.
- Related Section / Chapter: 4.2 Base Color; 5.18 Rendering Equation 관계.
- Recommendation: 앞 식의 이름을 Diffuse Angular Factor로 한정하고 Unit N/L, 같은 Space, Surface→Light Convention을 명시한다. 이후 `f_d=ρ_d/π`, `반사 기여=BRDF×입사광 기여×Cosine`을 연결한다. View 방향에 무관한 것은 Lambertian Radiance / BRDF라는 조건을 쓰고, 모든 방향에 같은 에너지 양을 보낸다는 표현은 피한다.

#### C5-03 — L의 방향 Convention과 Reflection 텍스트 도식

- Section: 5.3, 285~318 / 340~372행; 5.6의 Half Vector.
- Severity: High
- Action: Rewrite, Expand
- Issue: L을 Incoming Light Direction이라고만 부르면서 `R=2(N·L)N-L`을 사용한다. ASCII 도식은 Incoming Light를 Surface 아래에 배치하고 각도를 정의하는 입사·반사 Ray가 불분명하다.
- Reason: 해당 식은 L을 Surface→Light로 정의할 때 반사 출사 방향과 맞는다. 빛의 진행 방향 I를 쓸 경우 식은 `I-2(N·I)N`이다. 부호가 뒤집히면 이후 NdotL / H도 잘못된다.
- Related Section / Chapter: 5.4~5.7; Fig5_03.
- Recommendation: 이 장에서 N/L/V는 같은 Space의 Unit Vector, L/V는 Surface에서 바깥으로 향하는 방향이라고 먼저 고정한다. 빛의 진행 방향은 -L로 구별한다. ASCII의 Surface·Normal·두 Ray와 각도 Label을 같은 정의로 수정한다. 반사 법칙의 설명은 이상적인 Specular 반사 또는 개별 Microfacet에 적용한다고 범위를 유지한다.

#### C5-04 — Normal의 유일성과 Shading Normal의 범위

- Section: 5.2, 157~203 / 226행.
- Severity: Medium
- Action: Rewrite, Shorten
- Issue: “표면에 수직인 방향은 하나만 존재”한다고 하고 모든 방향 계산의 기준이라고 일반화한다.
- Reason: 평면에는 ± 두 법선 방향이 있으며 Orientation으로 하나를 선택한다. Material Normal이 조정한 Shading 방향을 실제 Polygon에 수직인 방향과 동일시하면 4.6과 연결되지 않는다.
- Related Section / Chapter: 4.6 Normal Mapping; 5.3 Reflection.
- Recommendation: Surface의 앞면 / 바깥쪽 Convention으로 선택한 법선이라고 표현한다. 실제 Geometry Normal과 Lighting용 Shading Normal을 구분하고, 4.6에서 준비한 N을 이 장에서 소비한다는 연결만 남긴다. Normal의 필요성을 처음부터 길게 재정의할 필요는 없다.

#### C5-05 — Half Vector 조건과 Phong / Blinn-Phong 비교가 부족함

- Section: 5.5, 716~768행; 5.6, 861~949행; 5.7, 1014~1084행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: H가 정확한 중간 방향이라고 하지만 생성식과 조건이 없다. “왜 같은 결과가 나올까?”는 Highlight의 Peak 조건과 전체 Lobe의 동일성을 혼동시킨다. 모든 Microfacet의 Normal이 H라고 읽힐 표현도 있다(949행).
- Reason: H는 Unit L/V에 대해 `normalize(L+V)`이며 L=-V이면 정의할 수 없다. R≈V와 N≈H는 Peak 방향의 연결을 설명하지만 지수와 각도 응답이 같다는 뜻은 아니다. Microfacet 전체가 아니라 해당 L/V 쌍에 기여하는 방향이 H다.
- Related Section / Chapter: 5.9, 1461~1485행의 더 정확한 설명.
- Recommendation: H 식과 예외를 추가한다. Phong의 `max(R·V,0)^n`, Blinn-Phong의 `max(N·H,0)^m`을 개념적 Specular Lobe로 비교하여 지수가 폭을 조절함을 보인다. 전체 BRDF 정규화까지 이 식이 완료한 것으로 표현하지 않는다. “같은 결과”는 “비슷한 Highlight와 같은 이상적 Peak 조건”으로 고친다.

#### C5-06 — 거친 Specular와 Diffuse를 같은 원인으로 설명

- Section: 5.4, 468~492행; 5.8, 1210~1234행; 5.9, 1363~1417행.
- Severity: High
- Action: Rewrite, Expand
- Issue: 미세 구조 때문에 여러 방향으로 퍼지는 것을 Diffuse라고 정의한 뒤 같은 미세 구조로 Rough Specular를 설명한다. Lambert / Phong / Blinn-Phong을 모두 완전히 매끄러운 한 평면의 모델이라고 묶는다.
- Reason: 분포가 넓다는 이유만으로 Diffuse가 되는 것은 아니다. 거친 금속도 넓은 Specular를 가질 수 있다. 경험적인 방향 응답 모델이 Microfacet 통계를 명시적으로 계산하지 않는 것과 Surface 전체가 하나의 평면이라는 주장은 다르다.
- Related Section / Chapter: 4.2 Roughness / Metallic; 5.11~5.12.
- Recommendation: 일반적인 불투명 Dielectric의 Diffuse를 내부 산란 후 재출사하는 성분으로 개념적으로 구분하고, Microfacet Roughness가 바꾸는 Specular 방향 분포와 분리한다. 복잡한 Subsurface 유도는 필요 없다. 기존 모델의 한계는 명시적 Microfacet·Fresnel·에너지 배분 등의 부재로 설명하되 “모두 매끄러운 한 평면”이라는 일반화를 제거한다.

#### C5-07 — D/G/F가 BRDF로 합쳐지는 최소 관계 부재

- Section: 5.10, 1587~1679행; 5.12, 1968~2054행; 5.13, 2219~2235행; 5.14, 2422~2446행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: 각 요소의 역할은 설명하지만 어떤 입력으로 평가하고 무엇으로 합쳐지는지 보여주지 않는다. D는 Microfacet “개수 / 확률”, G는 실제 보이는 “Reflection의 양”, F는 “Reflection의 양 자체”로 표현되어 출력 형식이 섞인다.
- Reason: 분포 밀도·기하학적 감쇠·Fresnel Reflectance를 최종 빛의 양과 구분해야 한다. D는 단순 0~1 확률이나 정수 개수가 아니다.
- Related Section / Chapter: C5-01; 5.11 Roughness; 6.4 IBL.
- Recommendation: 기본 Single-scattering Microfacet Specular 모델의 `f_s = D(H) G(L,V) F(V·H) / [4(N·L)(N·V)]`를 NdotL/NdotV가 양수인 조건과 함께 한 번 보여준다. D에는 Roughness / 분포, G에는 L/V와 가림 모델, F에는 F0와 Microfacet 입사각이 들어간다는 표를 둔다. 분모·단위를 포함한 연결이 목적이며 GGX 유도나 HLSL 구현은 필요 없다. G는 Scene 전체의 Shadow Visibility와도 구별한다.

#### C5-08 — Fresnel의 각도·F0·화면 밝기 조건이 약함

- Section: 5.14, 2338~2384 / 2422~2476행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: “비스듬히 바라볼수록 Reflection은 강해진다”에서 Reflectance와 최종 밝기를 구분하지 않고, Cook-Torrance의 F가 어떤 Normal과 이루는 각도를 사용하는지 설명하지 않는다. Schlick 이름은 있지만 F0가 없다.
- Reason: 화면 가장자리의 밝기는 반사율뿐 아니라 해당 방향의 환경 Radiance·D/G 등에 달려 있다. Microfacet F는 선택된 Microfacet Normal H와 L/V의 관계를 사용한다.
- Related Section / Chapter: 4.1, 4.2의 Property≠결과 원칙; G03; C5-07.
- Recommendation: 정면 입사 반사율 F0와 Grazing 방향의 경향을 설명하고, Smooth Surface의 N 기반 직관과 Microfacet의 H 기반 평가를 구분한다. 필요하면 `F=F0+(1-F0)(1-V·H)^5`를 근사식으로 제시한다. 화면 가장자리가 항상 더 밝아진다는 보장은 하지 않는다. 금속·비금속의 F0 차이를 G03과 연결한다.

#### C5-09 — Radiometry 단위와 물리량 구분 부족

- Section: 5.15, 2647~2696행.
- Severity: High
- Action: Rewrite, Expand
- Issue: Radiant Flux를 “전체 빛의 에너지”라고 정의하며 Irradiance / Radiance / Intensity를 모두 빛의 양·세기로만 설명한다.
- Reason: Flux는 Energy 자체가 아니라 단위 시간당 Energy다. 면적·입체각·투영면적 구분이 없어 뒤의 BRDF 출력 정의를 검증할 수 없다.
- Related Section / Chapter: C5-01; 6.2 Light Intensity.
- Recommendation: Flux는 Power(W), Irradiance는 입사 Power/면적(W/m²), Intensity는 Power/입체각(W/sr), Radiance는 Power/(투영면적·입체각)(W/(m²·sr))로 간단한 표를 둔다. Radiant Energy(J)와 Flux의 차이 및 Solid Angle의 의미를 한 문장씩 보완한다. 광도학이나 상세 미분 유도는 추가하지 않는다.

#### C5-10 — PBR의 물리 조건과 모델의 변형 범위

- Section: 5.7, 1100~1119행; 5.10; 5.16~5.19의 모델 목록.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: 기존 모델은 Energy Conservation을 만족하지 않는다고 단정하지만 보존의 뜻이나 PBR에서 Diffuse / Specular를 어떻게 함께 제한하는지 설명하지 않는다. 모든 Phong 계열 표현을 조건 없이 물리적으로 타당한 BRDF와 같은 것으로 읽게 한다.
- Reason: 원래 경험적 조명식, 정규화된 변형, BRDF 형태의 응답 모델은 구분해야 한다. PBR도 특정 이름이나 D/G/F를 사용했다는 이유만으로 모든 물리 조건이 자동 보장되는 것은 아니다.
- Related Section / Chapter: G03; C5-02, C5-07.
- Recommendation: 수동적 비발광 표면에서 반사 Energy가 입사 Energy를 초과하지 않는다는 조건과 Reciprocity의 의미를 짧게 설명한다. 앞서 소개한 경험식의 범위를 밝히고, 정규화·에너지 배분을 고려한 변형이 가능함을 구분한다. 실제 모델별 보존 증명과 고급 다중 산란 보정은 심화 대상으로 남긴다.

#### C5-11 — 역사·성능을 확정한 학습 서사

- Section: 5.1, 84~116행; 5.3, 388~396행; 5.5~5.7의 비용 설명; 5.12, 2071~2089행.
- Severity: Medium
- Action: Needs Technical Verification, Rewrite
- Issue: Reflection Vector→Lambert→Phong→Blinn-Phong→Cook-Torrance→Microfacet→Radiometry→BRDF를 발전 계보처럼 제시하고, Half Vector가 항상 더 단순·효율적이라는 설명을 반복한다. “현대 대부분 Engine의 표준”도 구현 조건 없이 단정한다.
- Reason: 학습 순서와 역사·이론적 의존 관계는 다르다. 실제 본문도 Microfacet이 Cook-Torrance의 기반이라고 설명한다. 실행 비용은 정규화·재사용·Hardware 등 조건을 빼고 단정할 수 없다.
- Related Section / Chapter: ASF-000 Measurement Before Optimization; 4.4의 조건부 Sampling 비용 설명.
- Recommendation: 화살표를 “이번 문서의 학습 순서”로 명시하고 기반 관계를 분리한다. 역사·성능·보급도 주장을 유지하려면 후속 Technical Verification에서 출처나 대상 조건을 확인한다. 이번에는 외부 조사·측정을 수행하지 않았으므로 역사적 사실이나 속도 우열을 새로 확정하지 않는다.

#### C5-12 — BRDF 반복 절과 미사용 Figure / Status 흔적

- Section: 5.16~5.19, 2735~3450행; 파일 첫 1행; Figure 폴더의 `Fig5_15.png`.
- Severity: Low
- Action: Merge, Shorten, Remove
- Issue: 모델 목록과 “BRDF는 공통 Framework”라는 결론이 반복되고, Reflection Chapter Status 제목에 상태 내용이 없다. Figure 파일 하나가 본문에 사용되지 않는다.
- Reason: BRDF 개념·입력·수학·Lambert 예시를 나누는 목적은 좋지만 각 절이 같은 결론을 재시작한다. 미사용 Figure는 참조 누락 또는 미채택 Asset일 수 있다.
- Related Section / Chapter: C5-01~02; Figure Metadata.
- Recommendation: 5.16 정의→5.17 입력·출력→5.18 최소 식→5.19 Lambert 검증으로 각 절의 새 정보를 분명히 하거나 병합한다. Status는 실제 의미 있는 상태를 채우거나 제목을 제거한다. Fig5_15는 작성 의도를 확인하기 전 삭제·삽입·내용 추정을 하지 않는다. Figure 15가 반드시 5.15용이라고 가정하지 않는다.

**Important Keep Sections**

| Section | 보존할 내용과 조건 |
|---|---|
| 5.1 | 같은 Light 아래 Material이 다르게 보이는 질문 — 역사 서사와 분리 |
| 5.2~5.3 | N을 기준으로 반사 방향을 계산하는 연결 — Convention과 도식 수정 필요 |
| 5.4 | 입사각에 따른 투영면적의 직관 — Cosine과 BRDF를 구별 |
| 5.5~5.7 | View 방향이 Specular에 필요한 이유, R/V와 N/H의 비교 관점 |
| 5.8~5.9 | 기존 모델의 한계를 묻고 미세 방향 분포로 이동하는 학습 목적 — 매끄러운 평면 일반화는 수정 |
| 5.10 | D/G/F가 각각 다른 문제를 해결한다는 개념 구분 |
| 5.11 | Roughness는 단순 Specular Intensity가 아니라 분포의 형태를 제어한다는 핵심 |
| 5.12 | Normal Distribution의 Normal이 정규분포가 아니라 Surface Normal이라는 명시 |
| 5.13 | 입사 경로 Shadowing과 출사 경로 Masking 구분 — Scene Shadow와 경계 추가 |
| 5.14 | 각도에 따라 Reflectance가 달라지는 관찰 — 최종 밝기와 구분 |
| 5.15 | 빛의 수량화가 필요한 이유 — 단위는 보완 |
| 5.16~5.19 | 모델을 공통 BRDF 관점에서 비교하는 목표 — 정의를 수정하고 중복은 정리 |

### Chapter 06 — Modern Real-Time Rendering

**Overall Assessment**

BRDF 하나만으로 이미지를 만들 수 없다는 출발점은 좋다. Direct / Indirect / Environment와 HDR / Tone Mapping / Output이 필요하다는 범위도 유효하다. 다만 이들을 단계마다 독립적으로 결과를 만들고 다음으로 넘기는 단일 Pipeline으로 설명하면 잘못된 Data Flow가 된다. 6.6의 Input과 Process 구분은 이 장 전체에 확대 적용할 수 있는 좋은 기준이다.

**Issues**

#### C6-01 — 학습 순서를 실제 Pipeline 순서로 일반화

- Section: 6.1, 17~47 / 85~108행; 6.2, 119~151 / 190~200행; 6.9, 832~902행.
- Severity: High
- Action: Rewrite
- Issue: Direct Lighting을 Pipeline의 첫 Stage로, BRDF를 Material Stage로 표현한다. 최종 도식은 Direct/Indirect→Reflection/IBL→BRDF→HDR 순서다.
- Reason: BRDF는 Direct와 Environment / Indirect 반사 기여를 평가할 때 사용된다. IBL Reflection을 계산한 뒤 별도 BRDF를 한 번 더 적용하는 구조가 아니다. HDR은 이 계산·누적의 값 범위이며 끝에 붙이는 독립 효과가 아니다. ASF-002의 GPU Stage 정의와도 설명 단위가 다르다.
- Related Section / Chapter: G02; C05 5.17~5.18; 6.6.
- Recommendation: Light Source / Environment Data와 Material Property가 각각 입력되어 BRDF 평가와 Contribution 누적으로 합쳐지는 구조로 바꾼다. HDR은 Lighting 누적 전체를 감싸는 조건으로 표시하고 Output Transform만 결과 이후로 둔다. 학습 순서와 실제 Render Pass / GPU Stage 순서를 구분한다.

#### C6-02 — 환경 입력을 무조건 Indirect로 분류

- Section: 6.2, 168~174행; 6.4, 344~373행; 6.5, 450~459행.
- Severity: High
- Action: Rewrite, Expand
- Issue: 주변 환경에서 오는 빛은 Direct Lighting에 포함되지 않는다고 하고, Diffuse IBL을 곧 간접 조명으로 설명한다.
- Reason: Direct / Indirect는 Light Path 분류이고 IBL은 방향별 입사광을 이미지로 제공·평가하는 방식이다. Environment가 직접 광원 역할을 하는 경우와 다른 Surface의 반사를 담은 Probe는 같은 경로 분류가 아니다.
- Related Section / Chapter: 6.3의 한 번 이상 반사 정의; 6.4.
- Recommendation: “다른 Surface에서 반사된 뒤 도달”이라는 Indirect 정의를 유지한다. IBL / Probe에 어떤 입사광이 담겼는지와 Engine의 용어를 구분하고, IBL=Indirect라는 등식을 피한다. Direct / Indirect와 Diffuse / Specular가 서로 다른 분류 축이라는 작은 표를 추가한다.

#### C6-03 — Reflection을 Specular IBL 효과로 한정

- Section: 6.5, 430~459 / 475행; 6.9, 897행.
- Severity: High
- Action: Rewrite
- Issue: Reflection을 주변 환경이 보이는 효과로 재정의하고 Specular IBL을 통해 구현되는 것으로 한정한다.
- Reason: C05의 Reflection은 Diffuse / Specular를 포함한 Surface 반사 현상이다. Specular 환경 반사는 그중 한 Context이며 환경 정보를 얻는 방법도 IBL만 존재하는 것은 아니다.
- Related Section / Chapter: 5.1, 5.5; 6.4.
- Recommendation: 이 절의 범위를 Environment Specular Reflection으로 명시한다. Specular IBL은 그 구현·근사 방식 중 하나라고 표현하고, 다른 Scene Reflection 경로가 존재함만 짧게 밝힌다. SSR / Ray Tracing 구현을 새 단원으로 확장할 필요는 없다.

#### C6-04 — 부드러운 그림자의 원인을 Indirect로 연결

- Section: 6.3, 286~296행.
- Severity: High
- Action: Rewrite
- Issue: 부드러운 그림자·Color Bleeding·실내 밝기를 대부분 Indirect Lighting이 만든다고 함께 묶는다.
- Reason: Soft Shadow의 Penumbra는 유한한 크기의 Direct Light에서도 생긴다. Indirect의 그림자 영역 밝기 보충과 그림자 경계의 부드러움은 다른 원인이다.
- Related Section / Chapter: 6.2 Direct Light; Fig6_04.
- Recommendation: Indirect 예시는 Color Bleeding과 그림자 영역으로 전달되는 반사광으로 한정한다. 경계의 부드러움은 Light의 각 크기·Visibility 변화와 별개로 설명한다. Shadow 알고리즘의 구현은 추가하지 않는다.

#### C6-05 — Light / BRDF가 결과로 결합되는 최소식과 Visibility 부족

- Section: 6.2, 155~166행; 6.4, 364~373행; 6.9.
- Severity: Medium
- Action: Expand
- Issue: 입력 목록은 있으나 Light 세기·거리·Visibility·Cosine·BRDF가 한 기여로 합쳐지는 설명이 없고, IBL은 두 결과 이름을 열거하는 데 머문다.
- Reason: Light Direction과 Surface Property를 준비해도 어떤 값이 곱해지고 합쳐지는지 알 수 없다. BRDF의 G가 Scene 전체 그림자를 해결하는 것처럼 오해할 여지도 남는다.
- Related Section / Chapter: C5-01, C5-07; G02.
- Recommendation: 점광원 예시는 해당 모델의 거리 감쇠, Visibility, 각도, BRDF가 필요함을 한 흐름으로 보인다. Environment는 여러 입사 방향의 Radiance를 BRDF와 Cosine으로 가중해 누적한다고 설명하고 Roughness가 Specular IBL의 방향 분포에 연결됨을 밝힌다. 정밀 적분·Sampling / Prefilter 구현은 요구하지 않는다.

#### C6-06 — SDR / sRGB 예시를 모든 출력의 필수 경로로 일반화

- Section: 6.4, 350행; 6.6, 518 / 558~570행; 6.7, 602~638행; 6.8, 713~720 / 766~820행.
- Severity: Medium
- Action: Rewrite, Expand
- Issue: HDR을 하나의 이미지 형식처럼 소개하고 Tone Mapping→SDR→sRGB를 보편적인 출력 경로로 제시한다. Color Space를 마지막 단계의 역할로만 요약한다.
- Reason: HDR은 넓은 Dynamic Range의 속성이고 이를 저장하는 여러 형식이 있다. SDR / sRGB는 유효한 예시지만 모든 출력 장치·작업 Color Space에 강제할 수 없다. C04에서 이미 입력 Color Decode가 Lighting 이전에 필요하다고 설명했다.
- Related Section / Chapter: 4.5; 6.6의 Input / Process 구분.
- Recommendation: “이 절은 SDR / sRGB 출력 예시”로 범위를 고정한다. 입력 Encoding 해석→공통 Linear Working Space→HDR 누적→Exposure / Tone Mapping 등 Output Transform→대상 Encoding의 관계를 보인다. Tone Mapping과 비선형 Encoding의 역할을 분리한다. HDR Output 설정의 구현 세부나 현재 모니터 보급률 조사는 추가하지 않는다.

#### C6-07 — Base Color Decode 누락의 밝기 방향 예시

- Section: 6.8, 781~789행.
- Severity: High
- Action: Rewrite
- Issue: sRGB Base Color를 Non-Color로 읽으면 더 어두워질 수 있다는 예시가 제시된다.
- Reason: 저장값 0.5를 예로 들면 정상 sRGB Decode 값은 약 0.214 Linear이고, Decode를 생략하면 0.5를 Linear로 사용한다. 다른 조건이 같은 단순 비교에서는 더 큰 값을 전달한다. 현재 예시는 Cause / Effect를 반대로 기억시키기 쉽다.
- Related Section / Chapter: 4.5, 1285~1305 / 1361~1385행.
- Recommendation: Encoding된 sRGB 파일이라는 전제와 동일 Lighting / Exposure / Output 조건을 명시해 숫자로 비교한다. 일반적인 Decode 누락은 의도보다 높은 Linear 값을 전달한다고 설명하고, 실제 화면 밝기는 추가 변환 조건과 함께 판단한다. Roughness 0.5에 잘못 Decode를 적용하는 반대 사례도 같은 표로 확인할 수 있다.

#### C6-08 — 플랫폼 설정 표의 조건과 Emissive 예외

- Section: 6.8, 734~762행; 6.1, 99행; 6.2, 121행.
- Severity: Medium
- Action: Needs Technical Verification, Rewrite
- Issue: 플랫폼별 sRGB / Normal Import 설정을 고정 규칙처럼 표기하고, “빛이 없다면 아무것도 보이지 않는다”는 요약에는 4.2의 Emissive 예외가 없다.
- Reason: 설정은 입력 파일 Encoding과 Texture Type / Pipeline 조건에 달려 있다. 반사 성분에 입사광이 필요하다는 설명은 옳지만 Emission까지 일반화하면 장 사이 정의가 충돌한다.
- Related Section / Chapter: 4.2, 371~396행; 4.5, 1429~1433행.
- Recommendation: 표는 일반적인 sRGB Color Texture / Numeric Data를 전제로 한 예시로 명시하고 대상 Blender / Unreal / Unity 버전과 Texture Type을 후속 검증한다. “입사광이 없으면 반사 성분은 0”으로 범위를 한정하고 Emissive는 별도 기여라고 연결한다. Emissive가 주변을 실제로 비추는지는 Render System에 달린다는 4.2의 조건도 유지한다.

**Important Keep Sections**

| Section | 보존할 내용과 조건 |
|---|---|
| 6.1 | BRDF만으로 최종 이미지를 만들 수 없다는 질문 |
| 6.2 | 광원과 Surface의 직접 관계라는 출발점 — 실제 첫 GPU Stage로 부르지 않음 |
| 6.3 | 다른 Surface에서 반사되어 전달되는 빛과 Color Bleeding 예시 |
| 6.4 | Environment를 입사광 데이터로 사용하고 Diffuse / Specular 응답을 모두 평가한다는 역할 |
| 6.5 | 원리를 반복 유도하지 않고 Environment 반사에 적용하려는 목적 |
| 6.6 | HDR Environment Map은 Input, HDR Rendering은 계산 방식이라는 명확한 구분 |
| 6.7 | 계산된 밝기 범위와 출력 가능한 범위를 연결하는 이유 |
| 6.8 | Texture 이름보다 저장된 값의 의미를 먼저 확인하는 원칙 — 입력·출력 역할을 분리 |
| 6.9 | NPR 전에 물리 기반 입력과 계산 흐름을 정리하려는 목적 — 최종 도식은 재작성 필요 |

## 4. Cross-Chapter Duplication Map

| Concept | Appears In | Primary Source Candidate | Other Sections | Recommended Action |
|---|---|---|---|---|
| Material Property≠최종 결과 | 4.1, 4.2, 4.8; 5.17; 6.1 | 4.1~4.2 | 5.17은 BRDF 출력, 6.1은 전체 이미지 | Necessary Reinforcement: 단계별 다른 Output을 연결하는 반복은 Keep; 동일 정의 재소개만 Shorten |
| Texture / Sample / 현재 값 | 4.3, 4.4, 4.8; 6.8 | 저장·값 의미는 4.3, Sampling은 4.4 | 4.8은 통합, 6.8은 Decode 맥락 | 4.8의 전체 재설명은 Shorten; 6.8의 출력 Color 변환은 새 Context로 Keep |
| Linear / sRGB / Import 설정 | 4.5, 4.8; 6.8 | 입력 해석은 4.5 | 6.8은 Output 변환과 비교 | Unnecessary Duplication: Texture 설정 원칙의 장문 재설명은 참조로 축약. 입력 Decode 대 출력 Encoding 대비는 Keep |
| Normal / Normal Map | 4.2, 4.3, 4.6, 4.8; 5.2 | 이번 범위의 Normal Map 설명은 4.6 | 5.2는 완성된 Shading N 소비 | 5.2의 최초 정의 재시작은 Shorten. 4.6의 Decode / TBN과 반사 방향 연결은 Necessary Reinforcement |
| Roughness | 4.1~4.2; 5.9, 5.11~5.12; 6.5 | 입력 의미 4.2, 분포 관계 5.11~5.12 | 6.5는 환경 응답 | 역할 변화가 있으므로 Keep. 낮음/높음의 동일 대비를 반복하는 부분만 축약 |
| Diffuse / Specular | 5.4~5.5; 6.4~6.5 | 5.4~5.5 수정 후 | 6.4는 같은 응답의 Environment 평가 | Necessary Reinforcement. IBL에서 새로운 별개 반사 법칙으로 재정의하지 않음 |
| Half Vector / Microfacet | 5.6~5.7, 5.9, 5.12 | H 생성은 5.6, 기여 방향은 5.9 | 5.12는 D(H) 평가 | Keep: 같은 Vector에 새로운 역할을 부여함. 성능 우위·역사 목록 반복만 Shorten |
| Reflection | 5.1~5.19; 6.5 | 일반 현상과 모델은 C05 | 6.5는 Environment Specular Reflection | 재정의가 아니라 적용 범위임을 명시. 동일 원리의 반복 유도는 불필요 |
| BRDF와 모델 관계 | 5.16~5.19; 6.1, 6.9 | 5.16~5.18을 역할별로 통합 | 5.19는 Lambert 검증, 6.1은 Rendering 연결 | 모델 목록·공통 언어 결론 반복은 Unnecessary Duplication. 수치 / Data Flow의 새 연결은 Expand |
| HDR 입력 / 계산 / 출력 | 6.4~6.8 | 6.6은 HDR Input / Process, 6.7은 Output Transform | 6.4는 Environment Data, 6.8은 Encoding | Necessary Reinforcement: 이름이 같아도 다른 역할을 설명하므로 병합 삭제하지 않음 |

Chapter 01~03과의 반복은 이번 범위에서 재검토하지 않았다. 해당 장을 참조해야 할 경우 제목·Section 연결을 후속 편집에서 확인하면 되며, 이 표는 C04~C06 내부의 근거로만 작성했다.

## 5. Missing / Weak Concept Map

| Concept | 실제로 필요한 이유 / 약한 부분 | 최소 보완 | Related Issue |
|---|---|---|---|
| Scalar / Vector / Mask | 값 형식과 제어 역할이 섞이고 Mask 소비 경로가 없음 | Channel Sample → Scalar Mask → Blend / Threshold 예시 | C4-01 |
| Metallic / F0 / Base Color | C04의 Property가 PBR 반사 성분으로 연결되지 않음 | 불투명 Metallic-Roughness 범위에서 금속·비금속별 Base Color 용도와 Diffuse / Specular 배분 | G03 |
| BRDF / Reflectance / Radiance | 핵심 출력 값의 의미가 잘못 연결됨 | 단위·정의·입사광과의 결합, BRDF≠최종 빛 | C5-01, C5-09 |
| Lambert BRDF / Cosine | NdotL을 BRDF 자체로 오인할 수 있음 | ρ_d/π와 Cosine의 역할 분리 | C5-02 |
| L / V / H Convention | 부호와 길이에 따라 Reflection·Half Vector 결과가 달라짐 | Unit·동일 Space·Surface→Light/View, H=normalize(L+V)와 예외 | C5-03, C5-05 |
| Microfacet 평가 연결 | D/G/F의 이름만으로는 BRDF 결과를 만들 수 없음 | 입력과 출력 표, 기본 f_s 식 한 번, D는 분포 밀도라는 조건 | C5-07~08 |
| Energy Conservation | “PBR이 물리적”이라는 설명의 판단 기준이 없음 | 반사 Energy 제한·Reciprocity의 의미, 성분별 배분 | C5-10 |
| Direct / Indirect × Diffuse / Specular | Light Path와 반사 성분을 같은 분류로 오인 | 서로 독립적인 두 분류 축을 보여주는 작은 표 | C6-02 |
| Scene Visibility / 감쇠 / 입사광 누적 | 방향·Light 세기 목록에서 실제 Contribution으로 넘어가지 않음 | 점광원 예시의 조건과 Environment 방향별 가중 누적 | C6-05 |
| Linear HDR Result / Display Color | Property 변화와 출력 변환의 결과가 섞임 | Decode·계산·Exposure / Tone Mapping·Encoding의 경계 | C6-06~07 |
| Basic Verification | 올바른 결과의 기준이 주로 서술에 머묾 | 아래와 같은 작은 계산 확인 | 전체 |

Basic Verification 후보는 다음 정도면 충분하다.

- Flat Normal의 `(0.5,0.5,1)` Decode 결과 `(0,0,1)`를 확인한다. 이미 4.6에 있는 좋은 예이므로 별도 실험을 추가하지 않는다.
- Mask가 0 / 1 / 0.5일 때 두 Property 값의 선택·혼합 결과를 확인한다.
- Material·방향을 고정하고 입사광만 두 배로 바꾸면 BRDF는 그대로이고 Linear 반사 기여가 두 배가 된다는 관계를 확인한다. Tone Mapping 후 화면값까지 두 배라고 결론내리지 않는다.
- 같은 Encoding 값 0.5에 대해 Color Decode와 Numeric Data 읽기의 결과를 비교한다.
- Roughness 비교는 Light / Environment / Camera / Exposure를 고정해야 원인을 분리할 수 있다고 명시한다. 통제 실험 결과를 이번 Foundation 원고에 새로 요구하는 것은 아니다.

고급 BRDF 유도, Importance Sampling 구현, Production Material 최적화, 특정 Character 제작 사례를 새 Topic으로 추가할 필요는 없다. 위 보완은 현재 제시한 개념들의 관계를 닫기 위한 최소 범위다.

## 6. Refactoring Priority

### Priority 1 — Technical Accuracy

1. C5-01 / C5-02 / C5-09의 BRDF·Lambert·Radiometry 정의를 바로잡는다.
2. C5-03 / C5-05의 방향 Convention과 H 조건, C5-06의 Diffuse / Rough Specular 구분을 수정한다.
3. C6-02~04의 Light Path·IBL·Reflection·Soft Shadow 원인을 구분한다.
4. C6-07의 Color Decode 수치 예시를 수정한다.
5. C4-02 / C4-04 / C5-11 / C6-08의 플랫폼·성능·역사 조건은 Technical Verification 후 확정한다. 이번 Audit에서 검증 완료로 표시하지 않는다.

### Priority 2 — Data Flow / Structural Conflict

1. G01의 Chapter 책임과 이동 후보를 확정한다.
2. G02 / C6-01의 통합 흐름을 다시 작성한다. Material과 Light가 합쳐지는 경로, BRDF를 소비하는 계산, HDR 누적과 출력 변환을 분리한다.
3. C4-06의 Input / Source 방향과 N의 출처를 정리하고 G06의 예고를 맞춘다.

### Priority 3 — PBR Concept Clarity

1. G03의 Metallic / Base Color / F0 / Diffuse·Specular 연결을 완성한다.
2. C5-07~08의 D/G/F 평가 관계와 각도 조건을 보완한다.
3. C5-10의 에너지 보존·모델 범위와 C6-05의 Direct / Environment 기여 연결을 추가한다.

### Priority 4 — Duplication

1. 5.16~5.19의 같은 모델 목록·공통 Framework 결론을 정리한다.
2. 6.8의 Texture Import 재설명은 4.5를 참조하고 Output 역할을 중심으로 재구성한다.
3. 4.8과 각 Callback / Summary는 새 연결을 남기고 기존 정의의 재시작만 줄인다.
4. Roughness의 Property→Microfacet→Environment 재사용은 Necessary Reinforcement로 보존한다.

### Priority 5 — Missing Explanation

1. Mask Channel에서 Scalar 소비까지의 예시, Mip Footprint, TBN 목표 Space를 보완한다.
2. Parameter / Static Switch의 차이와 Normal·Color의 자동 Decode 경계를 명시한다.
3. Section 5의 짧은 Basic Verification을 넣어 결과를 판단할 기준을 만든다.

### Priority 6 — Terminology / Heading

1. G05의 Chapter / Major / Internal Heading을 Standard에 맞춘다.
2. Base Color / Albedo / Diffuse Color의 사용 범위, Reflection / Specular / Highlight의 포함 관계를 명시한다.
3. Roughness와 Smoothness를 단순히 같은 이름처럼 바꾸지 않는다. 현재 본문에 Smoothness Parameter의 혼용 오류는 확인하지 못했으며, 이후 추가 시 변환 Convention을 설명하면 된다.
4. “다음 장”을 실제 Section 또는 Chapter로 정확히 바꾸고 기술 제목의 English 표기를 정리한다. 불필요한 Hanja 남용은 발견하지 못했다.

### Priority 7 — Minor Editing

1. 비어 있는 Reflection Chapter Status 제목과 중복 구분선을 정리한다.
2. Fig5_15의 미사용 의도를 확인하고 필요할 때만 참조를 연결한다.
3. 구조 변경 후 Figure 번호·상대 경로·본문 참조를 다시 확인한다. 모든 Section에 Figure를 강제로 추가하지 않는다.

## 7. Figure Review Queue

다음 항목의 Action은 모두 **Visual Review Required**이다. Priority 1은 핵심 기술 관계, Priority 2는 비교 조건·Data 의미 확인 순서다. 이미지 내용을 보지 않았으므로 아래는 오류 확정 목록이 아니다.

| Figure | Chapter / Section | Reason | What must be visually verified | Priority |
|---|---|---|---|---|
| `Fig4_02.png` | 04 / 4.2 | Property와 최종 결과를 분리해야 함 | Base Color / Roughness / Metallic 비교에서 Lighting·Camera·Exposure가 고정되었는지, Metallic을 단순 밝기 변화로 표시하지 않는지 | 2 |
| `Fig4_05.png` | 04 / 4.5 | Color / Numeric Data Decode 차이 | 같은 저장값의 Linear 해석 결과, sRGB On/Off Label, 밝기 방향이 본문 조건과 일치하는지 | 1 |
| `Fig4_06.png` | 04 / 4.6 | Encoding·Basis·방향 Convention | RGB와 signed Normal의 구분, 평평한 Normal의 값, T/B/N의 Space와 화살표, Height / Silhouette 오해 여부 | 2 |
| `Fig4_08.png` | 04 / 4.8 | 여러 입력의 합류가 핵심 | Texture·UV·Parameter의 Source 관계, 평가된 Property, Geometry/Normal Map에서 N으로 합쳐지는 경로 | 1 |
| `Fig5_03.png`, `Fig5_06.png` | 05 / 5.3, 5.6 | L의 부호와 H 정의가 본문에서 모호함 | L/V가 Surface에서 밖으로 향하는지, 입사 진행 방향과 구분되는지, R과 H 및 각도 Label이 식과 맞는지 | 1 |
| `Fig5_04.png` | 05 / 5.4 | Cosine·Lambert·Diffuse의 관계 | 입사각 기준이 N인지, 같은 빛의 투영면적 변화인지, 모든 출사 방향의 에너지가 동일하다는 오해를 만들지 않는지 | 1 |
| `Fig5_07.png` | 05 / 5.7 | Phong / Blinn-Phong의 전체 결과는 동일하지 않음 | Peak 조건 비교인지 전체 Lobe 동일성 주장인지, 지수 / 입력 조건이 명시되는지 | 2 |
| `Fig5_09.png`, `Fig5_12.png` | 05 / 5.9, 5.12 | 전체 Microfacet과 H 방향 기여·밀도 구분 | 다양한 Normal의 분포, H에 기여하는 집합, D를 단순 개수·0~1 확률로 표시하지 않는지 | 1 |
| `Fig5_10.png`, `Fig5_13.png` | 05 / 5.10, 5.13 | D/G/F와 미세 가림의 범위 | 각 요소를 최종 Color처럼 표시하는지, Shadowing / Masking 방향, Scene Shadow와 Microfacet 가림의 구별 | 1 |
| `Fig5_14.png` | 05 / 5.14 | Fresnel의 각도·결과 조건 | Macro N과 Microfacet H의 사용 범위, Reflectance와 화면 밝기 구분, 비교 Light / Environment 조건 | 1 |
| `Fig6_01.png`, `Fig6_02.png`, `Fig6_10.png` | 06 / 6.1, 6.9 | 본문에 잘못된 순차 Pipeline이 있음 | BRDF가 Direct / IBL 평가 안에서 사용되는지, HDR이 누적 범위인지, Module과 GPU Stage가 혼합되지 않는지 | 1 |
| `Fig6_03.png`, `Fig6_04.png`, `Fig6_05.png` | 06 / 6.2~6.4 | Path와 Environment 표현을 구별해야 함 | 반사 횟수로 Direct / Indirect를 구분하는지, Environment를 무조건 Indirect로 그리는지, Soft Shadow 원인 비교가 맞는지 | 1 |
| `Fig6_06.png` | 06 / 6.5 | Environment Reflection의 적용 범위 | Reflection 전체와 Specular IBL을 동의어로 표시하지 않는지, Roughness 비교 조건이 일치하는지 | 2 |
| `Fig6_08.png`, `Fig6_09.png` | 06 / 6.7~6.8 | Tone Mapping과 Color Encoding의 역할이 다름 | HDR→SDR 예시라는 범위, 밝기 압축과 Encoding의 구분, 입력 Decode와 출력 변환 위치 | 2 |

`Fig5_15.png`는 파일 존재와 미참조 상태만 확인했다. 어느 설명을 위한 Figure인지 본문 근거가 없으므로 시각적 오류나 특정 Section의 누락으로 추정하지 않는다. 먼저 작성 의도를 확인한 뒤 필요한 경우 별도 Visual Review를 배정한다. Queue에 없는 Figure도 정확성을 승인했다는 뜻은 아니다.

---

### Audit Integrity

보고서 작성 과정에서는 Foundation 원본과 Figure를 수정하지 않았다. 아래 SHA-256을 보고서 작성 전후 대조하여 원본 세 파일이 변경되지 않았음을 확인했다.

| File | SHA-256 |
|---|---|
| C04 | `0C1464B9E389F921D01771B639D32168C86C8056B604890758019CF4645CAF59` |
| C05 | `0DBB6ED87ADAE6867F6A5C9701C567E6AD4870228675312B441AF19A5D3BC7E8` |
| C06 | `694F88E542668125DFAC9AD00DF60868BEE19C014E2D496BFB2539010D571FF0` |

이 문서는 Text Audit 결과와 Refactoring 권고이며, Foundation 수정 또는 Engine / Visual Verification 완료 보고서가 아니다.
