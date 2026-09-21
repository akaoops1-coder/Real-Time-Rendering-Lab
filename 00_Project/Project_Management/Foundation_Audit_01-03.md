# Foundation Audit — Chapter 01–03

Phase 1A — Text Audit · 2026-09-19

## 1. Executive Summary

Chapter 01의 Rendering Pipeline에서 Chapter 02의 Coordinate System으로 이어지는 연결은 유효하다. Vertex Attribute가 어떤 단계에서 소비되는지 먼저 설명하고, Position과 Direction에 Space라는 기준을 붙이는 방식은 ASF의 Concept First / Flow First 원칙에 부합한다. 특히 Coverage와 Shading, Interpolation과 Texture Sampling, View Depth와 직선거리, Geometry와 Shading Normal을 구분하는 설명은 보존할 가치가 높다.

가장 큰 구조적 문제는 **요청된 학습 흐름과 현재 Chapter 03의 역할이 다르다는 것**이다. 요청과 Roadmap은 Rendering Pipeline → Coordinate → Geometry / Surface Data를 요구하지만, 실제 Chapter 03은 Lighting Mathematics다. Chapter 01~02의 예고도 이 기존 Lighting Mathematics 구성을 따른다. 따라서 제목만 바꿔서는 해결되지 않는다. Geometry / Surface Data의 핵심 설명은 1.3, 1.5, 1.8, 2.13~2.14, 3.4~3.5에 흩어져 있다. 현재 내용을 삭제하기보다 각 장의 설명 책임을 정리해야 한다.

반드시 먼저 수정할 항목은 Matrix의 적용 순서와 수식 표기의 불일치, 같은 광선 방향과 같은 X/Y Offset의 혼동, World 상대 위치와 Local Position의 혼동, 일반적인 Depth 생성과 Pixel Shader의 선택적 Depth 출력의 혼동이다. 텍스트 도식의 Triangle Index 및 Frustum 폭도 본문과 맞춰야 한다. Chapter 01의 1.10은 미완성 문장 뒤에서 같은 절이 다시 시작한다.

Chapter 04 이후로 넘어가기 전에는 Chapter 03의 역할과 개념별 주 설명 위치를 확정하고, 그 결정에 따라 예고 문장과 Cross Reference를 갱신하는 것이 좋다. 그 다음 요약 절의 재설명과 Heading 구조를 정리한다. **원리를 설명하는 긴 문장 자체는 축약 사유가 아니다.** 새로운 Context에서의 반복은 유지하고, 동일한 정의·예시·요약의 재출현만 줄이는 것이 적절하다.

### Scope and Evidence

- 검토 루트: `C:\Users\kmcoo\Desktop\PW\ASF_Review` — 사용자가 정정한 경로를 적용했다.
- 실제 Foundation 경로는 `00_Foundation`이다. 초기 요청의 `Documentation/Foundation`과 다르지만 실제 Chapter 01~03 파일을 기준으로 검토했다.
- 아래 세 Markdown의 본문 전체를 검토했다. Chapter 04 이후 본문은 열어 Audit하지 않았다.
- 기준 우선순위: ASF-000~003 → ASF_Standard → Roadmap / DecisionLog의 관련 맥락. 과거 DecisionLog의 장 번호·규격 번호를 현재 Standard보다 우선하지 않았다.
- 외부 자료 검색, Engine 실행, Figure 이미지 열기·시각 분석은 하지 않았다. 검증이 필요한 Engine 동작과 조건은 `Needs Technical Verification`, 이미지 의존 항목은 `Visual Review Required`로 분리했다.
- 본문에 작성된 ASCII 도식과 수식은 Text Audit 대상이다. 이미지 내부 오류를 확인한 것으로 해석하면 안 된다.
- 아래 행 번호는 이번 Audit 시점의 원본 기준이다. 수정 후에는 Section 이름으로 다시 찾아야 한다.

| ID | 검토 파일 | 범위 |
|---|---|---|
| C01 | `00_Foundation/Chapter01_RnderingPipeline.md` | 1~7754행, 1.1~1.13 및 중복된 1.10 |
| C02 | `00_Foundation/Chapter02_CoodinateSystem.md` | 1~14954행, 2.1~2.16 |
| C03 | `00_Foundation/Chapter03_LightingMathematics.md` | 1~1285행, 3.1~3.7 |

참조 기준: `00_Project/ASF/ASF-000_Project_Principles.md`, `ASF-001_Naming_Philosophy.md`, `ASF-002_Rendering Architecture.md`, `ASF-003_Documentation_Standard.md`, `00_Project/ASF_Standard.md`, `00_Project/Project_Management/Roadmap.md`, `DecisionLog.md`.

### Figure Reference Metadata

| Chapter | 본문 참조 수 | 고유 파일 수 | 번호 / 상대 경로 확인 |
|---|---:|---:|---|
| 01 | 14 | 13 | `Figures/Chapter01/Fig1_01.png`~`Fig1_13.png`; Fig1_10만 두 번 참조 |
| 02 | 16 | 16 | `Figures/Chapter02/Fig2_01.png`~`Fig2_16.png` |
| 03 | 6 | 6 | `Figures/Chapter03/Fig3_01.png`~`Fig3_06.png` |

35개 고유 참조 파일은 모두 해당 Markdown 기준 상대 경로에 존재한다. Chapter 번호와 파일명 규칙이 일치하며 참조 번호의 중간 공백은 없다. 해당 Figure 폴더의 파일 수도 각각 13 / 16 / 6개다. **존재·번호·경로 확인만 완료했으며 이미지의 정확성은 판정하지 않았다.** Chapter 03에 Figure가 6개인 것은 Section이 7개인 것과 별개이며, 3.1에 Figure가 없다는 이유만으로 누락으로 판정하지 않는다.

## 2. Global Issues for Chapter 01~03

### G01 — Chapter 03의 역할 충돌

- Section: C03 전체; C02 2.16 마지막 예고(14954행); C01 도입부; Roadmap의 Foundation 구성.
- Severity: High
- Action: Rewrite, Move, Merge
- Issue: 계획된 Geometry / Surface Data 장과 실제 Lighting Mathematics 장이 일치하지 않는다.
- Reason: Pipeline → Coordinate 이후 Mesh Attribute와 Surface Data를 통합해야 할 위치에서 Lighting Vector 연산으로 바로 넘어간다. 관련 Geometry 설명이 없는 것이 아니라 앞뒤로 분산되어 있다.
- Related Section / Chapter: 1.3, 1.5, 1.8, 2.13, 2.14, 3.4, 3.5.
- Recommendation: Chapter 03을 Geometry / Surface Data의 주 설명 위치로 정리하는 구성을 우선 제안한다. Vertex/Index/UV/Normal/Tangent와 보간된 Surface Data를 연결하고 3.4의 Geometry 대 Shading 구분을 중심에 둔다. 3.2~3.3의 Vector 기초는 필요한 만큼 유지하거나 참조하고, 3.1·3.6·3.7의 Lighting 중심 설명은 향후 Lighting 단원의 배치 후보로 관리한다. 이후 장을 검토하지 않았으므로 확정 이동 위치나 중복 여부는 여기서 단정하지 않는다. 실제 이동·재번호 부여는 이번 단계에서 수행하지 않는다.

### G02 — 개념별 주 설명 위치와 반복의 목적이 불명확함

- Section: C01 1.13, C02 2.16, C03 3.5~3.7 및 각 절의 반복 Summary.
- Severity: Medium
- Action: Shorten, Merge, Keep
- Issue: 동일한 정의를 다시 설명하는 부분과 새로운 단계에서 재사용하는 부분이 함께 반복된다.
- Reason: 긴 분량 자체보다 독자가 새로 배워야 하는 차이가 잘 드러나지 않는 것이 문제다. ASF의 원리 중심 설명을 보존하면서 중복된 유지보수 지점을 줄여야 한다.
- Related Section / Chapter: Section 4의 Duplication Map.
- Recommendation: 정의는 주 설명 위치에 두고 나머지는 정확한 Section 참조와 새로운 Input / Output 차이로 연결한다. 1.8→3.4의 Normal 보간 재사용, 2.13→Lighting의 같은 Space 적용은 Necessary Reinforcement로 유지한다. 전체 흐름 요약에서 정의·수치 예시까지 재시작하는 부분은 Unnecessary Duplication으로 축약한다.

### G03 — Heading 계층이 Standard와 불일치

- Section: C01 전체; C02 전체, 특히 2.16의 14258행 이후.
- Severity: Low
- Action: Rewrite
- Issue: C01은 `##`가 243개, C02는 368개여서 주요 절과 내부 소제목이 같은 깊이에 섞여 있다. C02에는 `#`가 14개이며 2.16 내부의 제목들이 Chapter와 같은 깊이다.
- Reason: ASF-003의 `# Chapter / ## n.n Major Section / ### Internal Heading` 구분이 무너져 목차와 탐색이 불안정하다. 이는 기술 오류와 별개인 Heading 문제다.
- Related Section / Chapter: C03은 `#` 1개, `##` 7개로 기본 계층을 잘 지킨다.
- Recommendation: 주요 절만 `##`로 유지하고 내부 제목을 `###` 중심으로 재배치한다. 2.16의 `## 1. Local Space` 같은 내부 번호는 장 번호로 오인되지 않게 제거한다. 단순 일괄 치환보다 실제 소속을 확인한다.

### G04 — 이전 학습을 전제하는 예고와 과거 장 번호

- Section: C01 1.1(186행), 1.8(3742행), 1.9(4188~4190행), 1.10(5036행), 1.11(5623행); C03 3.4(581행), 3.5(818행).
- Severity: Medium
- Action: Rewrite
- Issue: 뒤에서 배울 내용을 이미 배웠다고 표현하거나 다음 절이 실제로 다루지 않는 Diffuse Lighting을 예고한다.
- Reason: Foundation의 순차 학습 전제를 깨며, 과거 Chapter 구성의 표현이 현재 구성에 남아 있을 가능성이 있다.
- Related Section / Chapter: G01; C03의 실제 다음 절은 각각 Normal Transformation과 Light and View Direction이다.
- Recommendation: C01의 Material 실습 경험 전제는 예시 또는 향후 연결로 바꾸고, Chapter06/08 같은 참조는 대상 제목과 번호를 후속 정리 단계에서 대조한다. 이번에는 이후 본문을 확인하지 않았으므로 링크 대상이 틀렸다고 확정하지 않는다. C03의 두 예고는 실제 바로 다음 Section의 학습 목표로 교체한다.

### G05 — Basic Verification이 구체적인 확인 질문으로 연결되지 않음

- Section: C01~03 전체, 특히 1.8, 2.12~2.15, 3.2~3.5.
- Severity: Medium
- Action: Expand
- Issue: 개념과 오류 증상은 충분히 설명하지만, 독자가 이해 여부를 확인할 작은 입력·예상 결과 쌍은 일부 수치 예시에 한정된다.
- Reason: ASF Foundation의 Basic Verification은 대규모 실험이나 구현 보고서 없이도 충족할 수 있다. 기존 설명을 검증 가능한 형태로 끝맺으면 효과적이다.
- Related Section / Chapter: ASF-000, ASF-003; DecisionLog DEC-016의 Theory / Experiment 분리.
- Recommendation: Position에는 Translation이 적용되고 Direction에는 적용되지 않는 예, Matrix 순서를 바꾼 두 결과, Normal 보간 후 길이 변화 등 1~2개의 짧은 계산 확인을 배치한다. Engine 구현 절차·측정 결과·실험 보고서 추가는 요구하지 않는다.

### Terminology and Scope Assessment — Keep

설명은 대체로 Korean, 기술 용어는 English라는 기준을 지킨다. 불필요한 Hanja가 반복되는 문제는 발견하지 못했다. Pixel Shader와 Fragment Shader의 명칭 차이는 1.9에서 설명하므로 무조건 한쪽을 제거할 필요가 없다. Local / Object Space도 동의어 관계를 명시하면 유지 가능하다. `Non-uniform` / `Non-Uniform` 같은 대소문자는 후순위 편집 사항이다.

1.12의 Draw Call·비용 관계와 2.15의 Unreal Material 적용은 개념을 실제 입력 의미에 연결하는 Foundation 내용이다. 이번 범위에는 상세 구현, 통제 실험, Profiling Case Study가 과도하게 들어간 것으로 확정할 만한 절이 없다. **Move to Advanced를 일괄 적용하지 않는다.** G01의 이동 제안은 Foundation 내부의 설명 책임 조정이다.

## 3. Chapter-by-Chapter Audit

### Chapter 01 — Rendering Pipeline

**Overall Assessment**

Data가 화면 결과로 이어지는 원인과 단계를 설명하는 골격은 좋다. 1.1~1.4는 필요성과 입력, 1.5~1.11은 처리 단계, 1.12~1.13은 실행과 전체 연결이라는 흐름을 가진다. 다만 1.10의 중복 원고, Stage·외부 실행 흐름의 혼합, Depth 생성 설명을 우선 정리해야 한다. 1.13은 새로운 통합 관점은 유지하되 본문을 다시 쓰는 수준의 재설명은 줄일 수 있다.

**Issues**

#### C1-01 — 1.10의 중복과 미완성 문장

- Section: 1.10, 4560~4776행 및 4778행 이후; Fig1_10 참조 4590 / 4808행.
- Severity: Medium
- Action: Merge, Remove
- Issue: 1.10이 두 번 시작하며 첫 블록은 4774행의 “Depth Test가 없다면 단순히 나중에 Rendering된 Surface”에서 문장이 끝나지 않는다.
- Reason: 의도적인 복습이 아니라 이어 붙인 원고처럼 읽히고 Figure도 중복된다.
- Related Section / Chapter: 1.11, 1.13의 Depth 요약.
- Recommendation: 두 블록의 고유 설명을 비교해 완성된 한 절로 합친다. 첫 블록을 일괄 삭제하기 전에 고유 내용 보존 여부를 확인하고, Figure 참조는 설명 흐름에 맞춰 하나로 정리한다.

#### C1-02 — Index 예시와 ASCII Triangle 대각선 불일치

- Section: 1.5, 1919~1932행.
- Severity: High
- Action: Rewrite
- Issue: 텍스트 사각형의 Vertex 배치와 대각선은 1–3 연결로 읽히지만 Index 예시는 `[0,1,2]`, `[0,2,3]`으로 0–2를 공유한다.
- Reason: Index가 Primitive를 조립한다는 핵심 예시가 서로 다른 두 Triangle 분할을 나타낸다.
- Related Section / Chapter: 1.3의 Vertex 공유; 1.6의 Winding.
- Recommendation: Vertex 번호, 대각선, 두 Triangle의 Index를 하나의 분할에 맞춘다. Winding까지 확인한다. 이 문제는 이미지가 아닌 본문 ASCII와 배열 비교로 확인된다.

#### C1-03 — Depth의 생성 주체를 Pixel Shader로 일반화

- Section: 1.11, 5369~5385행 및 5643~5650행.
- Severity: High
- Action: Rewrite, Expand
- Issue: Fragment / Pixel Shader가 Color와 Depth를 계산한다는 표현이 기본 Pipeline의 Depth 생성과 선택적 Shader Depth 출력을 구분하지 않는다.
- Reason: 기본 Depth는 투영된 Geometry로부터 Rasterization 과정에서 만들어지는 값과 연결된다. Shader가 매번 새 Depth를 산출해야 하는 것으로 읽히면 앞선 Coordinate Flow와 단계별 역할이 혼동된다.
- Related Section / Chapter: 1.7, 1.9, 1.10; 2.9~2.10.
- Recommendation: 기본 Depth 전달 경로와 Shader에서 Depth를 명시적으로 변경하는 경우를 구분한다. Color 결과, Depth Test, Depth Write를 별도 역할로 연결한다. API별 실행 세부는 확대하지 않는다.

#### C1-04 — Engine 처리와 GPU Stage를 같은 단계 목록으로 표시

- Section: 1.6의 Culling 설명; 1.13, 7006~7106행 및 전체 Stage 목록.
- Severity: Medium
- Action: Rewrite
- Issue: Object 수준 Frustum Culling과 Primitive 처리, CPU 준비·Draw Call·Framebuffer가 같은 종류의 Stage처럼 이어진다.
- Reason: 1.6 내부에는 실행 위치가 다를 수 있다는 설명이 있지만 전체 요약에서는 이 구분이 약해진다. Framebuffer는 Resource이고 Draw Call은 작업 제출 단위이므로 GPU 처리 Stage와 설명 단위가 다르다.
- Related Section / Chapter: 1.12; ASF-002의 Stage 정의.
- Recommendation: 상위 Engine 흐름과 내부 GPU Pipeline을 두 층으로 표시한다. Object 후보 선택과 Primitive Clipping / Back-face Culling을 구분하고 Framebuffer는 Output Stage가 기록하는 대상으로 표현한다. 모든 실제 Renderer의 실행 순서를 하나로 강제하지 않는다.

#### C1-05 — Index 사용을 모든 Draw의 필수 조건처럼 설명

- Section: 1.5, 1828~1845행 및 1967행 이후.
- Severity: Medium
- Action: Rewrite, Expand
- Issue: Index를 통한 조립 설명의 적용 범위가 명시되지 않아 모든 Geometry가 반드시 Index Buffer를 필요로 하는 것으로 읽힌다.
- Reason: Indexed Mesh를 대표 모델로 설명하는 것은 적절하지만 Primitive 구성 원리와 특정 데이터 제공 방식을 동일시하면 안 된다.
- Related Section / Chapter: 1.3, 1.12.
- Recommendation: “여기서는 Indexed Triangle Mesh를 기준으로 설명한다”는 범위를 먼저 둔다. 순서대로 제공된 Vertex로도 Primitive를 구성할 수 있다는 짧은 예외만 추가하고 API 사용법은 확장하지 않는다.

#### C1-06 — 전체 요약과 같은 예시의 재시작

- Section: 1.8의 UV 예시(3311~3345 / 3422~3456행); 1.13 전체, 특히 7454행 이후 여러 요약.
- Severity: Medium
- Action: Shorten, Merge, Keep
- Issue: 같은 예시와 단계 정의가 새 조건 없이 반복된다.
- Reason: 1.13의 통합 기능은 필요하지만 개별 절의 설명을 다시 시작하면 연결보다 분량이 전면에 나온다.
- Related Section / Chapter: 1.2, 1.5~1.12; G02.
- Recommendation: 1.13은 Input → Processing → Output 표와 하나의 Mesh가 통과하는 흐름을 유지한다. 세부 정의는 해당 절을 참조하고 같은 UV 예시는 한 번만 사용한다. 1.2의 초기 개요는 학습 전 지도이므로 유지한다.

#### C1-07 — 잔여 문자와 파일명 오타

- Section: 1.12 말미 6779행; 파일명 `Chapter01_RnderingPipeline.md`.
- Severity: Low
- Action: Remove, Rewrite
- Issue: 단독 `s`가 남아 있고 파일명 Rendering 철자에 누락이 있다.
- Reason: 편집 잔여물과 검색상의 불편이다. 특정 파일명 규약 위반으로 확대 판정하지 않는다.
- Related Section / Chapter: C02 파일명 `CoodinateSystem`의 철자.
- Recommendation: 후속 편집에서 잔여 문자를 제거한다. 파일명 수정은 관련 링크 전체를 함께 점검하는 별도 변경으로 처리한다. 이번 Audit에서는 이름을 바꾸지 않는다.

**Important Keep Sections**

| Section | 보존할 내용 / 이유 |
|---|---|
| 1.1~1.2 | 현실의 Scene과 Pixel 결과 사이에 Pipeline이 필요한 이유, 최초 전체 개요 |
| 1.3~1.4 | Vertex를 Attribute 묶음으로 이해시키는 설명과 Vertex 처리 역할; UV Seam / Hard Edge에 따른 Vertex 분리 |
| 1.6 | Back-face Culling을 Vertex Normal이 아니라 Winding과 연결한 설명(2233~2245행), Object Bounds 구분 |
| 1.7 | Coverage / Fragment / Pixel 구분, MSAA 단서, 작은 Triangle의 비용을 조건부로 설명한 부분 |
| 1.8 | Interpolation과 Texture Sampling 구분, Perspective-correct 보간과 Normal 재정규화 |
| 1.9 | Pixel / Fragment Shader 명칭 관계, Early Depth 조건, Forward / Deferred의 범위 단서 |
| 1.10 | Depth와 실제 거리 구분, Camera Visibility와 Light Visibility 구분, Depth Test와 Write 구분 |
| 1.11 | Color / Depth Buffer의 역할 구분 — C1-03 수정 후 유지 |
| 1.12 | Draw Call을 비용 가능성과 연결하면서 무조건적인 최적화 법칙으로 단정하지 않는 설명 |
| 1.13 | 개별 Stage를 한 흐름으로 연결하는 목적 — 중복 정의만 축약 |

### Chapter 02 — Coordinate System

**Overall Assessment**

Space를 숨은 Label로 보라는 설명, Position과 Direction의 구분, Clip Space와 NDC의 분리, View Depth와 Euclidean Distance의 구분이 강점이다. 2.1~2.10의 공간 전개 자체는 유효하다. 2.11~2.12는 앞에서 사용한 변환을 수학적으로 묶는 역할이지만 수식 Convention을 고정해야 한다. 2.13~2.15는 Surface Data에 연결되는 좋은 소재이며 G01 정리 시 설명 책임을 나눌 수 있다. 2.16은 전체 흐름을 반복해서 여러 번 제시하는 비중이 크다.

**Issues**

#### C2-01 — Matrix 적용 순서와 곱 표기 불일치

- Section: 2.11, 8757행 및 8809~8836행; 2.12, 9929~9971행.
- Severity: High
- Action: Rewrite, Expand
- Issue: `M × v = v′`와 Column Vector식 표현을 쓰면서 Scale → Rotation → Translation 적용 순서를 `Scale × Rotation × Translation`으로 표시한다. `Model × View × Projection`과 `P × V × M × Position`도 구분 없이 등장한다.
- Reason: Matrix 곱은 순서를 바꾸면 결과가 달라진다. Convention마다 다르다는 후속 단서만으로 서로 다른 식의 의미를 복원하기 어렵다. Row/Column Vector Convention과 Memory Storage Layout도 별개다.
- Related Section / Chapter: 2.3~2.9; 3.5의 Normal Matrix.
- Recommendation: 본문 예시는 한 Convention으로 고정한다. Column Vector라면 `p_world = T R S p_local`, `p_clip = P V M p_local`로 맞춘다. 단순 처리 순서는 곱셈 기호 대신 화살표로 쓴다. Storage Layout은 계산 순서와 별개라고 명시한다. 예를 들어 x=1에 Scale 2 후 Translation 5를 적용하면 7, 역순이면 12라는 확인 예시를 둔다.

#### C2-02 — 같은 광선 방향과 같은 X/Y Offset 혼동

- Section: 2.6, 4086~4088행; 2.8, 5675행 주변.
- Severity: High
- Action: Rewrite
- Issue: 방향 관계가 같아도 멀어지면 화면 중심에 가까워진다는 식으로 설명한다.
- Reason: 같은 Camera Ray 위에서 모든 View 좌표를 같은 비율로 키우면 x/z와 y/z는 일정하다. 반면 X/Y Offset을 고정하고 View Depth만 증가시키면 화면 중심으로 가까워진다. 두 조건은 다르다.
- Related Section / Chapter: 2.9, 6371~6498행과 6502~6618행; 2.16, 14063~14095행.
- Recommendation: 뒤의 정확한 설명처럼 “View X/Y를 고정하고 Depth만 증가”라는 조건을 앞에도 명시한다. 같은 Ray의 (1,0,2)와 (2,0,4), 같은 X의 (1,0,2)와 (1,0,4)를 비교하면 차이를 짧게 검증할 수 있다. 특정 Projection의 부호·축 Convention은 예시 조건으로 밝힌다.

#### C2-03 — Frustum ASCII 도식의 Near / Far 폭 역전

- Section: 2.6, 3657~3670행; 2.7, 4607~4616행.
- Severity: High
- Action: Rewrite
- Issue: Camera가 아래에 있는 텍스트 도식에서 Far 쪽 폭이 Near 쪽보다 좁게 그려져, 멀어질수록 넓어진다는 설명과 충돌한다.
- Reason: Perspective Frustum의 핵심 형태를 반대로 이해시킬 수 있다.
- Related Section / Chapter: Fig2_06, Fig2_07은 별도 Visual Review Required.
- Recommendation: Camera 위치·Near / Far Label·폭을 일치시킨다. 같은 ASCII가 반복되므로 두 위치를 함께 수정한다. 이미지 내부에도 같은 오류가 있다고 단정하지 않는다.

#### C2-04 — FOV와 Perspective Compression의 조건

- Section: 2.6, 3763~3783행; 2.9의 FOV 재설명.
- Severity: Medium
- Action: Needs Technical Verification, Rewrite
- Issue: 작은 FOV의 압축감을 Camera 위치 변화와 분리하지 않은 채 설명한다.
- Reason: 같은 Camera 위치에서 FOV만 바꾸는 비교와, Subject의 화면 크기를 유지하려고 Camera 거리까지 바꾸는 비교는 다르다.
- Related Section / Chapter: 2.5, 2.9; Fig2_06.
- Recommendation: 설명과 그림이 어떤 조건을 고정했는지 확인한다. FOV 자체의 화면 배율·시야 범위 변화와 Camera 위치 변화에 따른 상대 원근 차이를 분리해서 기술한다. 현재 자료의 이미지·실험 조건은 검증하지 않았다.

#### C2-05 — Homogeneous Coordinate의 동치 관계 연결 부족

- Section: 2.8, 5739~5743행의 예고; 2.9.
- Severity: Medium
- Action: Expand
- Issue: Homogeneous 좌표의 배수 관계를 뒤에서 연결하겠다고 예고하지만 같은 결과로 Divide되는 쌍의 설명이 약하다.
- Reason: w를 단순 추가 슬롯이나 거리 그 자체로 기억하지 않으려면 4성분 표현과 3D 결과의 관계를 확인할 필요가 있다.
- Related Section / Chapter: 2.7~2.9.
- Recommendation: `(1,2,3,1)`과 `(2,4,6,2)`가 Divide 후 같은 `(1,2,3)`이 된다는 짧은 예를 넣는다. w=0에서는 같은 방식으로 유한 Position을 얻을 수 없음을 덧붙인다. Projective Geometry의 일반 이론까지 확장하지 않는다.

#### C2-06 — Normal의 수직 조건을 Shading Normal 전체에 일반화

- Section: 2.13, 10889~10983행; 2.16, 14388~14414행.
- Severity: Medium
- Action: Rewrite, Expand
- Issue: Normal은 Surface에 수직이어야 한다는 설명에서 어떤 Surface / Normal을 뜻하는지 구분이 부족하다.
- Reason: Geometric Normal의 수직 관계는 Normal Transform의 원리를 설명하지만 Smooth / Authored Vertex Normal이 실제 Triangle 면에 항상 수직인 것은 아니다. 3.4에서는 이 차이를 이미 잘 설명한다.
- Related Section / Chapter: 1.8; 3.4, 477~505행; 3.5.
- Recommendation: 수직 관계의 도입 예시는 Geometric Normal과 Tangent Plane 기준임을 밝힌다. Shading Normal은 별도의 방향장임을 3.4로 연결하고, 역전치 변환을 하면 모든 Authored Normal이 실제 Polygon에 수직이 된다는 의미가 아님을 명시한다.

#### C2-07 — Tangent Normal의 Decode와 TBN 출력 Space가 생략됨

- Section: 2.14, 11625~11659행, 11781~11858행; 2.16, 14451~14483행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: Normal Map Sample에서 Tangent Normal로 넘어가는 중간 과정과 T/B/N이 어느 Space로 표현되어 있어야 하는지가 약하다.
- Reason: `TBN × N_tangent`의 결과는 Basis가 표현된 Space에 달려 있다. Texture의 색 성분을 곧바로 Direction으로 Dot하는 오해도 생길 수 있다.
- Related Section / Chapter: 1.8의 Sampling; 2.13; 3.2~3.3.
- Recommendation: Sample → 필요한 Decode → Tangent Direction → 목표 Space의 TBN → Normalize 흐름을 둔다. 일반적인 RGB 매핑 예시는 `2*rgb-1`로 설명하되 Engine의 Normal Sample이 이미 Decode했는지 확인해야 한다고 구분한다. World 출력 예시에서는 T/B/N도 World Space라는 조건을 적는다. Basis의 정규직교성 및 Mirrored UV의 방향 Convention은 짧은 전제로 연결하고 상세 생성 알고리즘은 추가하지 않는다.

#### C2-08 — Object 기준 Offset을 Local Position처럼 연결

- Section: 2.15, 13185~13244행.
- Severity: High
- Action: Rewrite
- Issue: `World Position - Object Position`을 Object / Local 기준 효과와 연결하면서 원점 이동과 축 변환을 구분하지 않는다.
- Reason: World 좌표 두 개를 뺀 결과는 Object 기준의 상대 Offset이지만 성분은 여전히 World 축 기준이다. 회전·Scale이 있는 Object의 Local 좌표와 같지 않다.
- Related Section / Chapter: 2.3~2.4; 2.11~2.12.
- Recommendation: “Object 기준점에서 측정한 World Space Offset”으로 명시한다. Local 좌표가 필요한 경우 기준점의 의미를 먼저 고정하고 Rotation / Scale의 역변환까지 포함하는 World→Local 변환과 구분한다. 이동만 있는 제한된 예시라면 그 조건을 밝힌다.

#### C2-09 — Unreal Node의 정확한 의미와 사용 조건

- Section: 2.15의 Object Position(12574~12610행), Normal / Camera / Transform Node 설명; 2.16의 Node 요약.
- Severity: Medium
- Action: Needs Technical Verification, Rewrite
- Issue: Node의 개념적 별칭만으로 기준점, 출력 Space, 사용 가능한 Stage / 입력 조건을 충분히 특정하기 어렵다.
- Reason: Object 기준점이 Pivot인지 Bounds Center인지에 따라 C2-08의 계산도 달라진다. VertexNormalWS / PixelNormalWS 등의 의미와 사용 위치는 이름만으로 동일하게 취급할 수 없다.
- Related Section / Chapter: 2.13~2.14; C2-08.
- Recommendation: 대상 Unreal 버전과 실제 Node 설정으로 ObjectPositionWS / ActorPositionWS의 기준점, Camera Vector의 방향, Screen Position 출력 모드, Normal Node 사용 조건을 확인한다. 확인 전에는 설명을 확정된 Engine 사양처럼 쓰지 않는다. 이번 Audit은 Engine 실행·외부 문서 조회를 하지 않았으므로 특정 Node 동작 오류로 확정하지 않는다.

#### C2-10 — 같은 예시와 전체 흐름의 과도한 반복

- Section: 2.1~2.4, 2.9의 6502~6618 / 7288~7366행, 2.16 전체.
- Severity: Medium
- Action: Shorten, Merge, Keep
- Issue: Position / Space 기본 정의, 동일 Perspective Divide 예시, Local→Screen 흐름이 여러 번 처음부터 반복된다.
- Reason: 2.16에는 Position 흐름뿐 아니라 Direction과 분리하는 중요한 종합 관점이 있으나 반복된 정의 사이에 묻힌다.
- Related Section / Chapter: 2.2, 2.6~2.10, 2.13~2.14; G02.
- Recommendation: 2.16은 Position Flow와 Direction Flow의 대비, Space / Transform 표, 최종 확인 질문을 중심으로 남긴다. 각 Space의 재정의와 반복된 전체 화살표는 합친다. 2.9의 동일 수치 예시는 한 번만 유지하고 FOV 상세는 2.6을 참조한다.

**Important Keep Sections**

| Section | 보존할 내용 / 이유 |
|---|---|
| 2.1~2.2 | 같은 숫자라도 Data 의미와 Space가 다르면 다른 값이라는 출발점; Position / Direction 구분 |
| 2.3~2.4 | Mesh Local Data와 Scene 배치의 분리; 같은 Mesh 재사용 |
| 2.5 | View Space를 Camera 기준의 3D 공간으로 설명하고 Screen과 구분 |
| 2.6~2.8 | Projection → Clip → Divide의 목적 분리; 단 C2-02~05 수정 필요 |
| 2.9 | View Depth와 Euclidean Distance의 구분, NDC가 여전히 3D라는 설명 |
| 2.10 | Viewport와 전체 Screen의 차이, Depth 유지, 1920 경계와 마지막 Pixel Index 구분(8100~8130행) |
| 2.11~2.12 | Matrix를 숫자 암기보다 Space 변환 도구로 설명하는 목적; Convention은 수정 |
| 2.13 | Non-uniform Scale에서 Normal을 일반 Direction과 구분하는 이유 |
| 2.14 | UV와 Tangent Space, Local과 Tangent의 구분; Seam의 새 Context 연결 |
| 2.15 | Node의 숫자보다 Data 의미와 Space부터 확인하는 적용 관점; Advanced로 일괄 이동하지 않음 |
| 2.16 | Position은 화면 위치까지, Direction은 필요한 계산 Space까지라는 대비 |

### Chapter 03 — Lighting Mathematics (현재 파일 기준)

**Overall Assessment**

현재 제목의 학습 목표만 보면 Vector → Normalize → Dot Product → Normal → Light / View Direction의 흐름은 이해하기 쉽다. 3.3은 필요한 결과를 먼저 생각하고 수식으로 연결해 ASF의 원리 중심 방향과 잘 맞는다. 그러나 요청된 Geometry / Surface Data 역할과는 다르므로 G01의 구조 판단이 선행되어야 한다. 3.4는 새 Chapter 03의 중심 재료로 특히 유용하다. Chapter 02에서 이미 충분히 설명한 Normal Transform과 Same Space Rule은 새로운 Lighting Context만 남기는 방향이 적절하다.

**Issues**

#### C3-01 — Normalize의 정의역과 Dot 범위 조건 누락

- Section: 3.2, 162~168행; 3.3, 377행; 3.6의 Position 차이 Normalize.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: `normalize(v)=v/|v|`에 0이 아닌 Vector라는 전제가 없고 “Dot Product 자체는 -1~1”이라는 요약은 Unit Vector 조건을 생략한다.
- Reason: 앞부분에서 Unit Vector를 충분히 설명했더라도 요약 문장을 일반 Dot Product의 성질로 읽을 수 있다. 같은 Position의 차이는 Zero Vector여서 식에 그대로 넣을 수 없다.
- Related Section / Chapter: 2.13~2.14의 재정규화; 3.6.
- Recommendation: `|v|>0`을 명시하고 “여기서 사용하는 두 Unit Vector의 Dot”으로 범위를 한정한다. 예외 처리 방식은 구현마다 다름을 짧게 밝히고 구체적인 epsilon 정책까지 확대하지 않는다. `max(dot,0)`와 `saturate(dot)`가 같은 역할을 하는 것도 현재 Unit Vector 조건 안에서 설명한다.

#### C3-02 — Dot / Cross Product의 계산 연결과 Winding 조건 부족

- Section: 3.3, 306~339행; 3.4, 449~459행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: Dot의 각도식은 있으나 성분 계산식이 없고, Cross Product가 Face Normal 식에서 처음 등장한다. Polygon 전체를 하나의 평면으로 보는 표현도 조건이 없다.
- Reason: 독자가 이미 가진 좌표로 결과를 확인하기 어렵고 Edge 순서가 Normal 방향을 뒤집는 이유가 1.6의 Winding과 연결되지 않는다. 임의의 Polygon은 반드시 평면이라는 보장이 없다.
- Related Section / Chapter: 1.5~1.6; 3.2.
- Recommendation: Dot에 `ax*bx + ay*by + az*bz`와 작은 예시를 추가한다. Cross는 두 Edge에 수직인 방향이며 순서를 바꾸면 반대가 된다는 정도만 설명하고 Triangle 예시로 범위를 제한한다. 퇴화 Triangle의 Cross가 0이면 Normalize할 수 없다는 조건도 짧게 붙인다. 별도의 Vector Algebra 장은 필요 없다.

#### C3-03 — Normal Matrix의 M과 차원이 정의되지 않음

- Section: 3.5, 701~737행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: `transpose(inverse(M))`에서 M의 출발·도착 Space, 선형 부분, 역행렬 존재 조건이 명시되지 않는다.
- Reason: Chapter 02의 4×4 Position Transform과 연결하면 독자가 3성분 Normal에 무엇을 곱하는지 모호하다. 수직 관계의 설명도 3.4의 Shading Normal 구분을 다시 잃을 수 있다.
- Related Section / Chapter: C2-01, C2-06; 2.13; 3.4.
- Recommendation: Column Vector 예시에서 Local→World 변환의 가역적인 3×3 선형 부분 A를 정하고 `N_world=normalize((A^-1)^T N_local)`로 표현한다. Zero Scale 등 역행렬이 없는 경우는 이 식의 적용 밖임을 짧게 밝힌다. 수직 관계 증명은 Geometric Normal 기준으로 설명하고 Authored Normal과 구분한다.

#### C3-04 — Surface Position과 View Direction의 적용 조건

- Section: 3.1, 34~40행; 3.6, 913~923행.
- Severity: Medium
- Action: Expand, Rewrite
- Issue: Pixel Shader가 Surface Position을 알 수 있다는 설명에서 준비 경로가 생략되고, CameraPosition−SurfacePosition을 모든 Camera의 View Direction처럼 제시한다.
- Reason: Screen Position과 Lighting용 World / View Position은 구분해야 한다. Camera 위치로 수렴하는 방향 계산은 Perspective Camera 모델에 맞으며 Orthographic의 평행 시선에는 같은 식을 일반화하면 안 된다.
- Related Section / Chapter: 1.8~1.9; 2.5~2.10; 3.7.
- Recommendation: Forward의 예에서는 원하는 Space의 Position을 전달·보간해 사용한다고 연결한다. Depth에서 재구성하는 다른 경로는 존재만 언급하고 구현하지 않는다. View Direction 식에는 Perspective Camera 조건을 붙이고 Orthographic은 일정한 시선 방향을 사용한다고 구분한다.

#### C3-05 — Same Space 설명이 독립 재정의로 반복됨

- Section: 3.5, 767~790행; 3.6, 1001~1023행; 3.7 전체.
- Severity: Medium
- Action: Shorten, Merge, Keep
- Issue: N / L / V를 같은 Space로 맞춰야 한다는 동일 목록과 원리가 연속해서 다시 소개된다.
- Reason: 3.7의 Debugging 및 World / View 대안은 새 Context지만 기본 원칙은 Chapter 02와 직전 절에서도 이미 충분히 설명됐다.
- Related Section / Chapter: 2.13~2.16; G02.
- Recommendation: 일반 원칙은 Chapter 02를 참조하고, 3.5·3.6은 각 입력을 준비하는 역할에 집중한다. 3.7에는 완성된 N/L/V 데이터 흐름과 Space 혼합 시 증상만 유지한다. G01에 따라 장 역할을 바꾸면 이 통합 흐름도 Lighting 단원 배치 후보로 관리한다.

**Important Keep Sections**

| Section | 보존할 내용 / 이유 |
|---|---|
| 3.1 | Position에서 L/V를 만든다는 Input 관계; G01에 따른 위치 조정 가능 |
| 3.2 | 길이가 다른 같은 방향 Vector를 Normalize하는 수치 예시 |
| 3.3 | 원하는 방향 관계 → Dot → 각도식의 설명 순서; NdotL은 최종 밝기 자체가 아니라는 명시(367~371행) |
| 3.4 | Face / Vertex / Pixel Normal 구분, Smooth Shading과 Silhouette 구분 — Geometry / Surface Data의 핵심 재료 |
| 3.5 | Non-uniform Scale 자체가 오류를 만드는 것이 아니라 잘못된 변환이 문제라는 설명; 보간 후 재정규화 |
| 3.6 | Surface→Light와 Light→Surface의 부호 Convention, Point / Directional 차이, Spot의 방향과 Cone 조건 분리 |
| 3.7 | 같은 Space 원칙을 잘못된 Lighting 증상과 연결한 Debugging 관점, World만 유일한 계산 Space가 아니라는 설명 |

## 4. Cross-Chapter Duplication Map

주 설명 위치는 후속 Refactoring을 위한 후보이다. G01에 따라 위치가 바뀌더라도 같은 개념을 여러 곳에서 독립적으로 재정의하지 않는 것이 목적이다.

| Concept | Appears In | Primary Source Candidate | Other Sections | Recommended Action |
|---|---|---|---|---|
| Vertex와 Attribute 묶음 | 1.3, 1.5, 1.8, 3.4 | 현재 1.3; 재구성 시 Ch03 Geometry / Surface Data | 1.5는 Index 소비, 1.8은 보간, 3.4는 Shading 방향 | Necessary Reinforcement: 소비 단계 차이는 Keep. Attribute 전체 목록의 재소개만 Shorten |
| Geometry와 Shading Normal | 1.8, 2.13, 3.4~3.5 | 3.4 | 1.8 보간, 2.13 Transform 조건 | Keep / Cross Reference. 다른 Context의 반복이므로 삭제 대상 아님 |
| Position / Direction / Translation | 1.4, 2.2, 2.8, 2.13, 2.16, 3.5 | 2.2; w 표현은 2.8 | 2.13과 3.5는 Normal의 추가 조건만 | 기존 정의 재시작은 Unnecessary Duplication: Shorten. Normal 예외는 Keep |
| Normal의 Non-uniform Scale / 역전치 | 2.13, 2.16, 3.5 | 2.13의 변환 원리 | 3.5는 Lighting 입력 준비; 2.16은 요약 | Merge 주 설명, 3.5의 적용은 Necessary Reinforcement. 같은 원리의 장문 재설명만 Shorten |
| 보간 후 Normalize | 1.8, 2.14, 3.2, 3.4, 3.5 | 연산 정의 3.2; 발생 원인 1.8 | 3.4 / 3.5는 실제 Normal 흐름 | 역할이 달라 Keep. 정의를 다시 유도하기보다 참조 |
| Same Space Rule | 2.13~2.16, 3.5~3.7 | Chapter 02의 Space 의미와 공통 계산 원칙 | 3.7은 N/L/V 완성 및 Debugging | 같은 목록 반복은 Unnecessary Duplication. Lighting 오류 증상은 Necessary Reinforcement |
| Surface Position으로 L/V 생성 | 2.15, 3.1, 3.6, 3.7 | 3.6의 방향 생성 | 3.1은 입력 개요, 3.7은 합성 흐름 | 개요와 종합은 Keep, 같은 뺄셈을 매번 상세 설명하지 않음 |
| Depth / Screen / Visibility | 1.10~1.11, 2.9~2.10 | 값의 의미는 Ch02, Test / Write는 1.10 | 1.11 Output 관계 | Necessary Reinforcement. Geometry→Depth 값→비교/기록의 서로 다른 역할이므로 Merge로 뭉개지 않음 |
| Pipeline 전체와 Coordinate 전체 | 1.13, 2.16 | 각각의 장 Summary | Ch03은 입력 데이터 연결만 | 요약 자체 Keep. 각각의 Summary 내부에서 같은 흐름이 여러 번 반복되는 부분만 Shorten |
| Tangent / UV / Seam | 1.3, 2.14, 3.4 | 재구성 Ch03의 Surface Data 후보 | 1.3 GPU Vertex 분리, 2.14 좌표 변환 | Necessary Reinforcement. 데이터 불연속과 Space의 역할 차이를 보존 |

## 5. Missing / Weak Concept Map

| Concept | 현재 약한 연결 | 필요한 최소 보완 | 연결 Issue |
|---|---|---|---|
| Geometry → Surface Data 계약 | Position/Index/UV/Normal/Tangent가 여러 장에 분산 | 어떤 Data가 Mesh에 저장되고 어떤 값이 보간·Sampling·변환되는지 한 표와 흐름으로 통합 | G01 |
| Matrix Convention | 처리 순서와 곱 표기가 혼용 | 한 Convention, Input / Output Space, 작은 비가환 예시 | C2-01 |
| Perspective의 비교 조건 | 같은 Ray와 고정 X/Y Offset 혼용 | 두 좌표 쌍의 Divide 결과 비교 | C2-02 |
| Homogeneous 동치 | w의 역할과 Divide 결과 연결 약함 | 동치 좌표 한 쌍과 w=0 조건 | C2-05 |
| Geometric / Shading Normal | 수직 관계를 모든 Normal에 일반화 | 실제 Triangle 면과 Shading 방향의 차이를 변환 절에도 유지 | C2-06, C3-03 |
| Tangent Normal의 입력·출력 의미 | Sample→Direction, TBN→World의 조건 생략 | Decode 여부와 Basis Space, Normalize 순서 | C2-07 |
| World Offset / Local Position | 원점 이동을 축 변환처럼 취급 | 상대 Offset의 Space Label 및 역변환 범위 | C2-08 |
| Normalize / Dot의 조건 | Zero Vector와 Unit Vector 범위 단서 부족 | 정의역·범위 한 문장, 성분식 예시 | C3-01~02 |
| Cross와 Face 방향 | 처음 나온 연산이 Winding과 연결되지 않음 | Edge 두 개, 수직 방향, 순서 반전, 퇴화 조건 | C3-02 |
| Lighting용 Position의 출처 | Screen 위치와 Surface 위치 사이 경로 약함 | 보간되는 World / View Position 경로, 다른 경로는 존재만 명시 | C3-04 |
| Basic Verification | 설명을 스스로 확인할 종료 조건 약함 | 짧은 입력·예상 결과 확인 1~2개씩 | G05 |

새로운 BRDF 전개, Radiometry, GPU 최적화 실험, 플랫폼별 TBN 생성 알고리즘, Engine 구현 Tutorial은 이 표의 보완 범위에 포함하지 않는다. 현재 본문을 이해하는 데 필요한 연결만 제안했다.

## 6. Refactoring Priority

### Priority 1 — Technical Accuracy

1. C2-01의 Matrix Convention과 순서를 확정한다. 3.5의 Normal Matrix 표기도 같은 Convention으로 연결한다.
2. C2-02의 Perspective 비교 조건, C2-08의 World Offset / Local 구분, C1-03의 Depth 생성 경로를 수정한다.
3. C1-02의 Index 도식과 C2-03의 Frustum ASCII를 본문과 일치시킨다.
4. C3-01~04의 수학 조건·Normal 범위·Camera 모델 조건을 보완한다.
5. C2-04, C2-09는 별도 Technical Verification 후 확정 문장을 작성한다. 미검증을 완료 처리하지 않는다.

### Priority 2 — Structural Conflict

1. G01에 따라 Chapter 03의 역할을 확정하고 개념별 주 설명 위치를 정한다.
2. C1-04의 Engine 흐름과 GPU Stage를 구분한다.
3. G04의 Chapter 예고를 새 역할과 맞춘다. 실제 후속 장의 참조 대상 확인은 별도 범위에서 수행한다.

### Priority 3 — Duplication

1. C1-01의 중복 1.10을 고유 내용 보존 후 병합한다.
2. C1-06 / C2-10의 중복 수치 예시와 Summary 재정의를 축약한다.
3. C3-05와 Duplication Map에 따라 주 설명을 참조로 연결한다.
4. Necessary Reinforcement는 남긴다. 삭제량이나 문서 길이를 성공 기준으로 삼지 않는다.

### Priority 4 — Missing Explanation

1. Section 5의 Surface Data 통합 흐름과 TBN 중간 단계를 채운다.
2. Homogeneous 동치, Dot 성분식, Cross / Winding 연결을 최소 예시로 보완한다.
3. G05의 Basic Verification을 계산·질문 수준으로 추가한다.

### Priority 5 — Terminology / Heading

1. G03의 Heading을 Standard 계층으로 정리한다.
2. Node 이름·출력 Space와 기준점을 Technical Verification 결과에 맞춰 표기한다.
3. 동의어 관계는 최초 정의에서 설명하고 파일명 철자 변경이 필요하면 참조 링크와 함께 처리한다.

### Priority 6 — Minor Editing

1. 단독 `s`, 끊어진 문장, 중복 Figure Reference를 정리한다.
2. Cross Reference의 시제·Section 제목과 표기 대소문자를 맞춘다.
3. 구조 변경 후 Figure 번호·경로·참조 수를 다시 검사한다. 이미지 수정 여부는 별도 Visual Review 결과로 결정한다.

## 7. Figure Review Queue

아래 항목의 Action은 모두 **Visual Review Required**이다. 본문에서 드러난 조건·연결을 이미지가 정확히 표현하는지 확인할 필요가 있는 항목만 선정했다. 이미지를 열지 않았으므로 오류 확정 목록이 아니다. Priority는 후속 Visual Review 순서이며 본문의 Severity와 별개다.

| Figure | Chapter / Section | Reason | What must be visually verified | Priority |
|---|---|---|---|---|
| `Fig1_05.png` | 01 / 1.5 | 텍스트 Index와 대각선 충돌 | Vertex 번호, 공유 대각선, 두 Triangle Index, Winding이 같은 분할을 표현하는지 | 1 |
| `Fig1_11.png` | 01 / 1.11 | 기본 Depth와 Shader 출력의 구분 필요 | Color / Depth의 생성·비교·기록 화살표가 모든 Depth를 Pixel Shader가 생성하는 것으로 표시하는지 | 1 |
| `Fig1_13.png` | 01 / 1.13 | Engine 과정과 GPU Stage의 혼합 | CPU 제출, Object Culling, GPU Stage, Framebuffer Resource의 계층이 구분되는지 | 2 |
| `Fig2_06.png` | 02 / 2.6 | Frustum 도식 및 FOV 조건 확인 필요 | Camera·Near·Far와 폭 관계, FOV 비교 시 Camera 위치 / 대상 크기 고정 조건 | 1 |
| `Fig2_07.png` | 02 / 2.7 | Clip Space의 Cube 표현은 개념적 한계가 있음 | 4성분 Clip 좌표와 Divide 후 NDC를 구분하는지, 고정 Cube로 표시했다면 w 의존 조건이나 개념도라는 설명이 있는지 | 1 |
| `Fig2_11.png`, `Fig2_12.png` | 02 / 2.11~2.12 | 본문 곱 표기의 Convention 혼용 | Matrix 곱 방향, Vector 배치, 적용 순서가 수정될 본문 Convention과 일치하는지 | 1 |
| `Fig2_14.png` | 02 / 2.14 | TBN 입력·출력 Space가 중요 | T/B/N의 목표 Space Label, Tangent Normal과 Texture RGB 구분, 축·방향 표시가 서로 맞는지 | 2 |
| `Fig3_03.png` | 03 / 3.4 | Geometry와 Shading 방향 구분을 보존해야 함 | Face / Vertex / Interpolated Normal의 차이, Smooth Shading에서 Silhouette가 바뀌지 않는다는 비교 조건 | 2 |
| `Fig3_04.png` | 03 / 3.5 | Non-uniform Scale 설명은 Surface와 Normal 관계에 의존 | 변형된 Tangent / 면, 일반 변환과 역전치 변환 Normal을 같은 조건으로 비교하는지; Geometric / Authored Normal 구분 | 1 |
| `Fig3_05.png` | 03 / 3.6 | Direction Convention은 화살표 방향에 의존 | L이 Surface→Light인지, 빛의 진행 방향과 반대임을 구분하는지, V의 방향과 Camera 모델이 본문 조건에 맞는지 | 2 |

Fig1_10의 두 번 참조는 이미지 내용 없이 확인된 텍스트 중복이므로 별도의 Visual 오류로 등록하지 않았다. 그 외 Figure도 “정확성 승인” 상태는 아니며, 이번 Text Audit에서 추가 시각 확인 사유를 특정하지 않았다는 의미다.

---

### Audit Integrity

Foundation 원본과 Figure는 수정하지 않았다. 원본 세 파일의 SHA-256을 읽기 작업 전후 대조했으며 동일했다.

| File | SHA-256 |
|---|---|
| C01 | `956DB92C35EA0C361828F22EDF0F8882644E3FC82153FACF5B85BB5EF7970633` |
| C02 | `9EF330CEA66F3383F539B8181EAC90F84CFD9D0FC41FCCA7EE67310B9B00C884` |
| C03 | `86595BF233B51BBA41914EA3217A3A3334C6AB8FCB063FC708568B8484F75F98` |

이 보고서는 수정 제안과 후속 검증 항목을 기록한 Audit 결과이며, Refactoring 또는 Technical / Visual Verification 완료 보고서가 아니다.
