# Chapter 01–04 Rewrite Audit

## 1. Rewrite Goal

이번 Rewrite는 Chapter 01–04의 기술적 깊이와 범위를 유지하면서, Chapter 05에서 사용한 설명의 호흡과 독자 안내 방식을 Foundation의 시작부터 이어가는 작업이다.

새로운 Concept을 만나기 전에 해결할 문제와 필요한 입력을 알 수 있도록 하고, Formula는 이미 설명한 관계를 짧게 표현하는 위치에 둔다. Concept의 난이도는 점차 높아져도 독자가 생략된 중간 사고 단계를 추측해야 하는 부담은 줄이는 것이 목표다.

- Chapter 05와 Teaching Style 및 설명 난이도를 일관되게 유지한다.
- 기존 Technical Depth, 예제, 검증 조건, Debugging / Production 정보와 연결을 보존한다.
- Formula Before Explanation과 한 문단 안의 과도한 Concept Density를 개선한다.
- Stage와 Space, Vector, Material Data가 다음 과정에서 어떻게 쓰이는지 연결한다.

### Source and Backup Baseline

Source Repository는 `akaoops1-coder/Real-Time-Rendering-Lab`이며, 작업 시작 시 로컬 작업 저장소와 GitHub `main`의 HEAD가 모두 `0d74f49879918bdd2f4bda40e0b625b068b31961`이었다. 로컬 작업 저장소의 기존 변경 사항이 없는 상태에서 2026-10-01, Asia/Seoul 기준으로 Backup을 생성했다.

비교의 직접 기준은 GitHub의 이전 문서를 다시 가져온 값이 아니라, **실제 Rewrite 직전에 복사한 네 `_backup.md` 파일**이다. Backup을 먼저 생성하고 SHA-256과 Byte Count가 원본과 일치하는지 확인한 뒤 Rewrite를 시작했다. Backup은 이후 수정하지 않았다. 로컬 Checkout의 일부 파일은 CRLF를 사용하므로 Git의 LF Blob과 Byte Count가 다를 수 있지만, 내용은 같은 Commit에 해당한다. 아래 Hash는 로컬 Rewrite 직전 파일의 실제 Byte를 기준으로 한다.

| Backup Source | Original Bytes | SHA-256 |
|---|---:|---|
| `Chapter01_RnderingPipeline_backup.md` | 209169 | `02A4444AE3B6CE81336A60EBFC81EB6022FA1E4F5ECE075B7CCB23ACB546F4A4` |
| `Chapter02_CoodinateSystem_backup.md` | 271790 | `1660ACD06167BD3D6F49526ABD2F9C32529B0E1FD15D7B040D5207BB6B36E48B` |
| `Chapter03_LightingMathematics_backup.md` | 50166 | `30A6A3E0AE810655666B8DB3819BF45C4A8852D5FC45C5CE01F35A51D8569DB5` |
| `Chapter04_MaterialArchitecture_backup.md` | 84339 | `230FBC4C2E4711D19AE622AC59F26D678F07ED32C06FAB409A3D8656D25A5F4A` |

`Chapter05_Reflection_BRDF.md`는 Style Reference로만 읽었다. Chapter 05의 문장을 재사용하거나 Reflection / BRDF Scope를 Chapter 01–04에 새로 추가하지 않았다. `_v02` 파일은 생성하지 않았다.

---

## 2. Global Findings

Backup은 이미 상당 부분 Why와 Data Flow를 설명하고 있었으며, Chapter 03은 최근 Review를 통해 Concept-first 구조가 크게 개선된 상태였다. 따라서 모든 문단을 새 Template으로 바꾸는 방식은 사용하지 않았다. 기존에 설명이 잘 이어지는 부분은 유지하고, 실제 난이도 상승 지점을 기준으로 문장과 배치를 조정했다.

### Concept Density and Intermediate Steps

Pipeline 입력, Position/Direction의 구분, Matrix 역할, Texture Sampling과 Normal Map처럼 여러 입력과 변환이 만나면 한 문장에 새로운 Concept이 겹치는 구간이 있었다. 필요한 값을 먼저 설명하고, 그 값이 어디에서 만들어져 다음 계산으로 전달되는지 나누어 연결했다.

### Formula and Figure Placement

본문은 Concept-first여도 앞에 놓인 Figure 안에서 Matrix, Normalize, Clamp 등의 Formula가 먼저 보이는 경우가 있었다. 이미지의 경로와 순서는 유지하면서 필요한 설명 뒤로 이동하거나 Caption에서 읽는 순서와 적용 범위를 안내했다. Essential Formula는 유지했고, 긴 Component 전개나 Matrix 증명은 새로 추가하지 않았다.

### Main Flow and Technical Conditions

예외조건과 구현 조건은 정확성에 필요하지만, Concept를 처음 소개하는 문장 안에 여러 조건이 동시에 들어가면 중심 관계를 따라가기 어려웠다. 유효한 입력, Matrix Convention, API Depth Range, 특수 Geometry, 실제 Engine 경로 등의 조건을 해당 Concept 설명 뒤의 Note나 `<details>`에 배치했다. 삭제한 정보처럼 처리하지 않도록 Chapter별 이동 근거를 아래에 기록했다.

### Technical Boundaries

Geometric/Shading Normal, Position/Direction, Clip/NDC, Color/Data Texture, sRGB Encode/Decode, Signed/Clamped NdotL, Non-Static/Static Parameter, Editor/Runtime, Parent Architecture/Compiled Shader Variant의 경계를 유지했다. Normalize가 Space 오류나 Normal 방향 오류를 해결한다는 식의 설명도 사용하지 않았다.

### Review Scope

Chapter 01–04의 기존 Figure 43개를 실제 이미지와 본문으로 대조했다. Figure 내부의 문제를 발견하면 이미지에 맞추어 기술 설명을 바꾸지 않고, Caption/Note에서 범위를 알린 뒤 Chapter별 Remaining Review Items에 기록했다. `Verified`는 문서와 이미지의 Concept 관계를 확인했다는 뜻이다. **Unreal Engine 실행, Shader Compilation, Render Capture 또는 GPU 측정은 이번 Rewrite에서 수행하지 않았다.** Engine과 Asset에 따라 확인할 항목은 별도 상태로 남겼다.

문서 작성 기준은 저장소의 `00_Project/ASF/ASF-003_Documentation_Standard.md`와 이번 사용자 요청을 따랐다. English Section Title / Technical Term, Korean Explanation, 기존 Chapter Number와 Figure Path Convention을 유지했다.

---

## 3. Chapter 01 Audit

### Backup Source

`00_Foundation/Chapter01_RnderingPipeline_backup.md`

Rewrite 직전 Backup을 전체 12개 구간으로 나누어 끝까지 읽었다. Backup은 209,169 bytes / 7,537 lines이며 SHA-256은 `02a4444ae3b6ce81336a60ebfc81eb6022fa1e4f5ece075b7ccb23acb546f4a4`다. 설명 Style은 수정하지 않은 Chapter 05의 Reflection / Surface Normal / Reflection Vector 도입부와 ASF-003 Documentation Standard를 참고했다. Chapter 05의 문장은 복사하지 않았다.

### Rewritten File

`00_Foundation/Chapter01_RnderingPipeline.md`

기본 흐름과 주요 Section 1.1–1.13을 유지하면서 34개 변경 단위를 반영했다. 원본이 이미 충분히 친절한 구간은 유지하고, 신규 용어가 한꺼번에 등장하거나 정의와 구현 예외가 붙어 있는 구간을 집중적으로 다시 썼다. 내용을 Summary로 대체하지 않았다.

### Major Changes

- 1.1: Character의 형태, Surface 특성, Light, 관찰 기준이 각각 왜 필요한지 설명한 뒤 Geometry / Material / Light / Camera를 소개했다.
- 1.3–1.4: 위치만으로 Texture와 Lighting을 결정할 수 없는 문제, 같은 Mesh를 다르게 배치했을 때 화면 위치가 달라져야 하는 문제에서 Vertex Attribute와 Vertex Processing으로 연결했다.
- 1.5–1.6: Index, Topology, Indexed / Non-indexed Draw를 짧은 중간 단계로 나눴다. Face Orientation 문제와 Shading Normal 문제의 진단을 분리하고, Frustum Culling의 View 범위와 구현 위치를 별도 문단으로 설명했다.
- 1.7–1.8: Clip Space 이후에 무엇이 남아 있는지, 내부 Attribute를 섞기 위해 왜 Weight가 필요한지 먼저 설명했다. Barycentric 수치보다 20% / 30% / 50%의 기여 의미를 먼저 배치했다.
- 1.9–1.11: Pass의 목적에 따라 Output이 달라지는 이유와 Color / Depth를 기억해야 하는 이유를 먼저 설명했다. 기본 Raster Depth와 선택적인 Shader Override는 별도 Note에 보존했다.
- 1.12–1.13: 기본 CPU-driven 제출 흐름의 범위를 분명히 하고, 복합 Figure의 오해 가능성을 짧은 본문 안내와 상세 Note로 나눴다.

### Added Explanation

| Backup → Rewrite | 추가한 중간 설명 | 이유 |
|---|---|---|
| 1.1 Rendering → 같은 Section | Character의 형태 / 재질 / 조명 / 관찰 기준을 각각 필요한 문제로 연결 | 네 개의 Scene Input이 용어 목록으로만 등장하지 않게 함 |
| 1.3 도입 → 같은 Section | Vertex 위치와 연결 관계로 형태를 설명한 뒤, 아직 알 수 없는 Texture 위치와 Surface 방향 | Attribute의 필요성을 정의 전에 이해하게 함 |
| 1.3 Normal → 같은 Subsection | Geometric Normal과 Shading Normal의 목적 차이 | Vertex Normal이 모든 Triangle 평면에 수직이어야 한다는 오해 예방 |
| 1.4 도입 → 같은 Section | 동일 Mesh의 Object 배치와 Camera 차이 | Position Transform의 필요성과 다음 Primitive 출력 연결 |
| 1.5 Primitive Assembly → 같은 Subsection | Topology가 입력을 어떤 도형으로 묶는지 지정함 | Indexed / Non-indexed 용어를 갑자기 던지지 않음 |
| 1.7 Screen-Space Triangle → 같은 Subsection | Projection → Clip Space 이후 Perspective Divide / Viewport 역할 | Clip Space와 Screen 위치 사이에서 독자가 추측해야 하는 단계 감소 |
| 1.8 Interpolation Weights / Barycentric Coordinate → 같은 Subsections | Weight의 의미, 기여 비율, Perspective 예시 범위 | 비율의 직관을 먼저 만들고 숫자로 연결 |
| 1.9 Surface Result → 같은 Subsection | Render Pass의 목적과 다음 작업이 요구하는 Data | Color Output과 GBuffer Output의 차이를 설명 |
| 1.10 Depth Test → 같은 Subsection | 수치 예시의 LESS 규약을 먼저 선언 | 낮은 Depth가 항상 가까운 것처럼 읽히지 않게 함 |
| 1.11 도입 → 같은 Section | 다음 Fragment와 다음 Image 작업을 위해 Color / Depth를 기억해야 함 | 네 Buffer 용어가 한꺼번에 등장하는 부담 완화 |

### Removed / Moved Details

기술 주제, Figure, 검증 범위 또는 Chapter 연결은 삭제하지 않았다. 중복된 Glossary 형식과 반복 Summary 문장을 Section 끝의 3–5개 Key Takeaways로 바꾸었다. 각 개념의 정의와 연결 관계는 보존했다.

| Backup 위치 | Rewrite 위치 | 보존한 내용 / 이동 이유 |
|---|---|---|
| 1.4 Vertex Shader 실행 설명 | 같은 위치의 Performance Note `<details>` | Vertex 처리 단위와 정확한 Invocation Count의 차이를 선택적으로 읽게 함 |
| 1.7 Small Triangles and Cost | 같은 위치의 Performance Note `<details>` | Micro Triangle / Hardware 처리 단위 / Geometry와 Coverage 비용 구분 유지 |
| 1.8 Interpolation and Performance | 같은 위치의 Implementation Note `<details>` | Interpolator / Varying, 전달 Data의 비용, Chapter 09 연결 전체 유지 |
| 1.9 Early Depth Test | 같은 위치의 Technical Note `<details>` | Early-Z 예시, 사용 가능 조건, Shader / Render State / GPU 구현 주의 전체 유지 |
| 1.10 Early-Z | 같은 위치의 Technical Note `<details>` | 원본의 별도 비용 주의와 Chapter 09 연결 전체 유지 |
| 1.11 첫 문단의 Depth 출처 예외 | 도입 직후 Technical Note `<details>` | Raster Depth와 Shader Override의 구분을 보존하되 저장 목적을 먼저 학습 |
| 1.12 Figure 1-12의 자료 출처 주의 | Figure 직후 Figure / Implementation Note `<details>` | 자원 참조, 업로드 오해, Engine Version / ASF 검증 제한 유지 |
| 1.12 CPU and GPU Frame Overlap | 같은 위치의 Implementation Note `<details>` | 병렬 준비 / 실행, 동기화와 Pipeline 관리의 비용 의미 유지 |
| 1.13 Figure 1-13의 복합 주의 문단 | 짧은 주의 + Figure Review Required `<details>` | 모든 Group / Culling / 저장 대상 / Label / 출처 Caveat 유지 |

### Formula Changes

Chapter 01의 핵심은 Pipeline Data Flow다. 새로운 Matrix 증명, Barycentric Component Derivation, BRDF Formula를 추가하지 않았다.

| Chapter | Formula / Concept | Backup Treatment | Rewritten Treatment | Decision |
|---|---|---|---|---|
| 01 | `1920 × 1080 = 2,073,600 Pixels` | Pixel 정의 뒤 해상도 예시 | 그대로 유지 | Keep |
| 01 | Local → World → View → Clip | 각 Space 역할과 변환 흐름 | 그대로 유지; Clip 이후 Perspective Divide / Viewport를 말로 설명 | Explain First |
| 01 | Index `[0,1,2]`, `[0,2,3]` | Vertex 연결 / 공유 예시 | 숫자 예시 유지; Topology와 Indexed / Non-indexed 의미를 분리 설명 | Keep / Explain First |
| 01 | Barycentric Weights `0.2 / 0.3 / 0.5` | 영향 비율을 수치로 먼저 제시 | 20% / 30% / 50% 직관 뒤 같은 수치 유지; Perspective 보정 적용 범위 명시 | Explain First |
| 01 | Depth: `0.2 < 0.4` passes / `0.7 > 0.4` fails with LESS | 숫자 예시 뒤 일반 비교 조건 주의 | 작은 Depth가 가까운 LESS 예시임을 먼저 선언; Reversed-Z와 GREATER 계열은 이후 Caveat | Explain First |
| 01 | Normal Interpolation → Normalize → Lighting | 중간 Normal 길이 변화 설명 뒤 Flow | 원리와 Flow 그대로 유지; 새 수학 증명 없음 | Keep |

### Structure Changes

Chapter 번호, 주요 Section 번호 / 제목 1.1–1.13, 내부 기술 주제와 Figure 순서는 유지했다. 1.7–1.12의 `Key Concepts` 여섯 곳을 `Key Takeaways`로 바꾸었다. 새 기술 Section을 추가하지 않고, 기존 Caveat를 9개 `<details>` 묶음으로 나눴다. 불필요한 단일 Template을 각 Section에 적용하지 않았다.

| Backup Section | Rewrite Section | 처리 / 이유 |
|---|---|---|
| 1.1 What is Rendering? | 1.1 What is Rendering? | 개념별 필요성 도입 보강; Geometry / Material / Light / Camera / Pixel / Renderer 전체 유지 |
| 1.2 From Model to Screen | 1.2 From Model to Screen | 이미 친절한 전체 개요와 단계별 Input / Output / 화면 의미 유지 |
| 1.3 Vertex and Vertex Attributes | 1.3 Vertex and Vertex Attributes | 도입과 Normal 구분 보강; UV / Tangent / Vertex Color / Skinning Data / Split Vertex 범위 유지 |
| 1.4 Vertex Processing | 1.4 Vertex Processing | 배치 문제 → Shader 역할 순서; Local / World / View / Clip, WPO, Attribute 전달 / 수정 유지 |
| 1.5 Primitive Assembly | 1.5 Primitive Assembly | Indexed / Non-indexed 설명 호흡과 Modeling 진단 개선; Triangle / Sharing / Winding 유지 |
| 1.6 Culling and Clipping | 1.6 Culling and Clipping | Frustum 문단 분리; Two Sided / Bounds / Near–Far / Occlusion / Clipping 재구성 / Pass 기여 유지 |
| 1.7 Rasterization | 1.7 Rasterization | Clip → Screen 관계 보완; Sample / Coverage / Fragment≠Pixel / Overlap / Screen Coverage 유지; Small Triangle Note 이동 |
| 1.8 Interpolation | 1.8 Interpolation | Weight → Barycentric 예시 순서 보강; UV / Sampling / Masks / Smooth Shading / Normalize / Modes / Perspective 유지 |
| 1.9 Fragment / Pixel Processing | 1.9 Fragment / Pixel Processing | Pass 목적의 사전 설명; Texture / Material / Normal / Lighting / Emission / Shader 비교 유지; Early-Z Note 분리 |
| 1.10 Depth Test and Surface Visibility | 1.10 Depth Test and Surface Visibility | 숫자 비교의 조건을 먼저 명시; Z-Buffer / Camera vs Light / Test vs Write / Transparency / Sorting 유지 |
| 1.11 Framebuffer and Final Image | 1.11 Framebuffer and Final Image | 저장 필요성 → 개별 저장 대상 → 연결 구조; MRT / GBuffer / Post Process / Double–Triple Buffering / Swap Chain / Present / Render to Texture 유지 |
| 1.12 CPU, GPU and Draw Calls | 1.12 CPU, GPU and Draw Calls | CPU-driven 모델을 명시; Draw State / Buffers / Material Slots / Pass / Bottleneck / Instancing / GPU Driven / Commands 유지; Overlap Note 분리 |
| 1.13 Complete Rendering Pipeline | 1.13 Complete Rendering Pipeline | 기존 Group와 전체 복습 유지; Figure 오해 명시; Cost와 현재 Bottleneck 구분 |

### Figure Review

모든 Figure를 실제 PNG pixels로 열어 기술 개념과 주변 본문을 비교했다. `Verified`는 **파일의 시각적 내용과 Foundation Concept / 본문 관계를 검토했다는 의미**다. 특정 Engine Version에서 실행하거나 실제 ASF Material / Shader / Frame을 검증했다는 뜻이 아니다. Figure 파일, 경로, 삽입 순서는 모두 유지했고 새 Figure는 만들지 않았다.

| Figure / exact path | Status | Rewrite Action | Reason |
|---|---|---|---|
| `Figures/Chapter01/Fig1_01.png` | Verified | Keep | Geometry / Material / Light / Camera → 2D Pixel Image; Light 사용 여부 Caveat 확인 |
| `Figures/Chapter01/Fig1_02.png` | Verified | Keep | 논리적 단계 개요이며 Early Depth / 실제 실행 순서와 기록 조건 차이를 Figure 하단에서 명시 |
| `Figures/Chapter01/Fig1_03.png` | Verified | Keep | Position과 Attribute 묶음, 같은 Position의 UV / Hard Edge 분리 사례 일치 |
| `Figures/Chapter01/Fig1_04.png` | Verified | Keep | Clip Position과 후속 Attribute, Vertex 처리와 Pixel 처리의 차이를 일치하게 표현 |
| `Figures/Chapter01/Fig1_05.png` | Verified | Keep | `[0,1,2]` / `[0,2,3]` 공유 관계와 예시 CCW Front 설정 일치; Indexed Draw 예시 범위 유지 |
| `Figures/Chapter01/Fig1_06.png` | Verified | Keep | Object Bounds Frustum 선별, 투영 Winding 판정, 경계 교점과 남는 사각형 구분; 다른 Pass Caveat 확인 |
| `Figures/Chapter01/Fig1_07.png` | Verified | Keep | Coverage와 Fragment 후보, Fragment≠Final Pixel 관계 일치; 단순한 grid / sample 교육용 그림으로 읽음 |
| `Figures/Chapter01/Fig1_08.png` | Verified | Keep | Barycentric, 예시 UV, Vertex Color 전달, Perspective 조건을 본문 참조로 명시 |
| `Figures/Chapter01/Fig1_09.png` | Verified | Keep | Input과 계산 예시는 실행 순서가 아님을 명시; 출력이 최종 화면 확정값이 아님을 표현 |
| `Figures/Chapter01/Fig1_10.png` | Verified | Keep Updated Context | Opaque / LESS / Depth Write On, 저장값과 새 값 비교, Camera vs Light, Reversed-Z Caveat 확인; 같은 조건을 본문 수치 예시보다 먼저 설명 |
| `Figures/Chapter01/Fig1_11.png` | Verified | Keep Updated Context | 기본 Raster Depth와 선택적 Override, Test / Write 조건, 별도 Buffer, 독립 Scene 삽화, Post Process → Display Target → Present 확인 |
| `Figures/Chapter01/Fig1_12.png` | Review Required | Keep / Review | Send to GPU와 Data 목록이 업로드 전체로 오해될 가능성; 본문에서 자원 참조 범위를 명시. Character 자료 출처와 실행 설정은 추가 확인 필요 |
| `Figures/Chapter01/Fig1_13.png` | Figure Revision Required | Keep / Review | Frustum Culling의 고정 GPU 배치, Framebuffer(Render Target) 동의어처럼 보이는 표기, 작은 불명확 Label 문제가 남아 있음; 본문과 상세 Note로 명시 |

#### Figure Issues Requiring Follow-Up

| Figure | Problem | Why It Is Incorrect / Misleading | Suggested Correction | Verification Needed |
|---|---|---|---|---|
| `Figures/Chapter01/Fig1_12.png` | `Send to GPU`와 Vertex / Index Buffer 목록의 관계가 실제 Data 재전송처럼 읽힐 수 있음 | Draw는 준비된 자원과 State를 참조하며, 매번 Buffer 전체가 복사된다는 의미가 아님 | 추후 Figure 수정 시 명령 제출과 기존 자원 참조를 따로 표시 | 그림의 의도와 대상 API 자원 바인딩 경로 검토; 실제 전송량은 profiling 필요 |
| `Figures/Chapter01/Fig1_12.png` | 기존 Character / Editor 이미지의 출처와 실행 환경 불명 | 그림만으로 Engine Version이나 현재 ASF 구현의 실행 결과를 확인할 수 없음 | 출처, 재현 환경과 설정을 확인한 경우 별도 캡션에 기록 | 원 자료 소유자 / 프로젝트에서 출처와 실행 설정 확인 |
| `Figures/Chapter01/Fig1_13.png` | `View Frustum Culling`을 Primitive Assembly 이후 Geometry Stage 목록에 고정 배치 | Object / Bounds 선별과 Triangle Backface / Clipping은 대상과 실행 위치가 다르며 Frustum 선별은 CPU / GPU에서 수행 가능 | Object / Bounds 선별을 Preparation 또는 별도 논리 분류로 표시하고 Backface / Clipping과 분리 | 대상 Renderer / Pass의 실제 선별 경로는 추가 확인 |
| `Figures/Chapter01/Fig1_13.png` | `Framebuffer (Render Target)` 표기 | 여러 Buffer를 함께 쓰는 연결 구조와 개별 저장 대상의 차이를 지움 | Framebuffer / output bindings와 개별 Render Target을 구분 | Figure 표현 검토; API별 용어 매핑 확인 |
| `Figures/Chapter01/Fig1_13.png` | 작고 뭉개진 일부 Label 및 여러 처리의 `Stage` 묶음 | Label을 명확히 읽기 어렵고 교육용 Group이 단일 Hardware Stage로 오해될 수 있음 | Label을 읽을 수 있게 재배치하고 Processing Group으로 명시 | 고해상도 원 자료에서 Label / 출처 확인; 본문과 수정 Figure 대조 |

### Technical Notes

이번 Rewrite에서 기술적 표현을 변경한 모든 항목은 아래에 기록한다. 나머지 수정은 설명 순서 / 호흡 / 이동에 해당한다.

| ID / Section | Backup 표현 또는 위험 | Rewrite 조치 | 근거 / 확인 범위 |
|---|---|---|---|
| T01 / Chapter Opening | Scene 정보의 처리 전체를 `GPU 안에서`로 설명 | Renderer 준비와 GPU 처리로 분리 | 같은 Chapter의 1.12–1.13 CPU / GPU 범위와 일치 |
| T02 / 1.3 Normal | Vertex Normal을 Surface 방향으로 설명하나 Geometric / Shading 역할이 명시적이지 않음 | Triangle 평면의 Geometric Normal과 Lighting Shading Normal을 구분 | 원본 1.8 Smooth Shading 및 Chapter 03의 구분 보존 / 연결 |
| T03 / 1.4 Vertex Shader | Mesh Vertex 수 예시가 Frame의 정확한 Shader 실행 횟수처럼 읽힐 수 있음 | 처리 단위와 Invocation Count를 구분; Index 재사용 / Instance / Pass / 참조 Vertex 조건 명시 | [Microsoft의 Indexed / Non-indexed Buffer 설명](https://learn.microsoft.com/en-us/windows/win32/direct3d9/rendering-from-vertex-and-index-buffers)은 자원 공유와 Vertex Cache를 구분한다. 실제 실행 횟수는 대상 작업에서 측정 필요 |
| T04 / 1.5 Modeling Tools | Face 또는 Normal 문제를 Surface 소실 / 예상 밖 결과와 한 문단으로 연결 | Face Orientation / Culling 문제와 Shading Normal / Lighting 문제를 분리 | Front / Back은 투영 Winding과 설정으로 판정한다. [Microsoft D3D11_RASTERIZER_DESC](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc) |
| T05 / 1.7 Screen-Space Triangle | Clip Space 뒤 `Projection과 Viewport에 관련된 변환`이 이루어진다고 표현 | Projection이 View → Clip에 이미 적용됨을 설명; 이후 Perspective Divide와 Viewport를 연결 | [Microsoft Transformation Pipeline](https://learn.microsoft.com/en-us/windows/win32/dxtecharts/the-direct3d-transformation-pipeline), [Rasterizer Stage](https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage). 수학 증명은 추가하지 않음 |
| T06 / 1.10 Figure / Depth Example | Caption의 살아남은 Depth 저장 문장이 무조건 갱신처럼 읽힐 수 있음; LESS 조건은 숫자 이후에 일반 주의로 제시 | Figure의 Opaque / LESS / Write On 조건을 본문에 명시; Test / Write / Color Write 구분 | [Microsoft Output-Merger Stage](https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-output-merger-stage)는 State와 Shader 결과, 저장 Buffer의 결합을 설명함 |
| T07 / 1.10 Reversed-Z | 숫자 예시 뒤 일반 비교 주의만 존재 | Reversed-Z에서 GREATER 계열 비교 가능성을 명시 | 원 Figure의 하단 Caveat 및 [Microsoft DirectXTK CommonStates](https://github.com/microsoft/DirectXTK/wiki/CommonStates)의 Reverse-Z State 예시. Unreal의 특정 Version 기본값을 단정하지 않음 |
| T08 / 1.11 Color Buffer | `각 Screen 위치의 최종 Color 정보` | 해당 Rendering 작업의 Color 결과로 표현; 이후 Pass / Post Process / Display 구분 | 같은 Backup의 Processing After Buffer Writes, Render to Texture 범위와 일치 |
| T09 / 1.12 CPU Scope | GPU가 스스로 Scene 선별을 하지 않는다는 일반화 | 기본 CPU-driven 설명 범위를 명시 | 원본의 GPU Driven Rendering / Instancing 언급 유지; 실제 GPU-driven 구현을 새로 전개하지 않음 |
| T10 / 1.13 Cost | 비용 위치를 먼저 판단하는 설명에서 측정 / 현재 Bottleneck 차이가 약함 | 비용 존재와 현재 Frame 제한을 구분 | ASF-003 Performance Documentation 및 원본 Chapter 09 측정 관점과 일치 |

Barycentric에서 거리 역수와 Weight를 구분한 원본 Caveat, Perspective-Correct 적용 범위, Geometric / Shading 차이, Non-uniform Normal Transform, Two Sided 비용, Camera 밖 Geometry의 Shadow / Reflection 기여, Transparency의 Sorting / Blending / Write, 기본 Raster Depth / Override, Double Buffering만으로 Tearing을 보장하지 않는 Caveat, 여러 Frame의 CPU / GPU Overlap을 보존했다.

Chapter 08.3의 Light 기준 Visibility와 Camera Depth의 구분, Chapter 09의 Pixel / Shader / Geometry / Draw Call / LOD / Culling 비용 연결, Chapter 06의 GBuffer / Forward–Deferred 연결도 유지했다. 새 Engine 검증 결과, 성능 수치, Engine Version 보장을 추가하지 않았다.

### Remaining Review Items

- Figure 1-13은 파일을 유지했으며 기술 표현 수정이 아직 필요하다. 본문의 명시적 제한으로 읽을 수 있지만 향후 그림을 수정하면 다시 대조해야 한다.
- Figure 1-12 / 1-13의 Character / Editor 자료 출처와 실제 Engine 실행 설정은 원 자료에서 확인해야 한다.
- Early-Z 적용 조건, 실제 Shader Invocation, Instancing / Pass별 Draw 수, 자원 업로드량, Present / Swap Chain 동작은 특정 Engine / API / Hardware 환경에서 검증해야 한다. 이번 작업은 문서와 Figure의 개념 검토이며 Engine 실행 검증은 수행하지 않았다.
- 모든 Stage Input / 처리 / Output / 다음 용도 / 화면 의미를 유지한 채 선택적 Caveat를 접었다. 처음 읽는 독자를 대상으로 실제 독해 테스트는 아직 수행하지 않았다.

### Preservation Checks

- Backup SHA-256은 변경 전과 동일하다.
- 주요 Section 1.1–1.13 제목 / 순서가 동일하다.
- 13개 원 Figure 참조의 정확한 경로 / 삽입 순서가 동일하다.
- `<details>`와 `</details>`는 9쌍이다.
- 최종 Rewrite의 bytes / lines는 통합 후 다시 집계한다. 반복 Glossary를 3–5개 Takeaways로 합치고 Code Fence 안의 설명 문장을 일반 문장으로 바꾼 형식 변화가 있으며, 기술 주제를 줄이지 않았다.
- Desktop 원본, Backup, Chapter 05, Figure PNG, 다른 Chapter 파일은 이 Agent가 변경하지 않았다.

---

## 4. Chapter 02 Audit

### Backup Source

00_Foundation/Chapter02_CoodinateSystem_backup.md

Rewrite 직전 원본의 완전한 복사본을 비교 기준으로 사용했다. 원본의 12,964 lines를 전체 검토했고, 긴 Data Flow와 예제를 포함한 2.1–2.16 범위를 유지했다. 읽기 과정에서는 빈 줄만 화면 출력에서 제외했으며, 본문 내용을 요약해 대체하지 않았다.

### Rewritten File

00_Foundation/Chapter02_CoodinateSystem.md

원본 184,732 characters → Rewrite 197,776 characters. 이는 Line 수가 아니라 Unicode 본문 기준이다. 줄 수 감소는 일부 문장의 과도한 분절을 연결된 문단으로 재작성한 결과이며, 정보량을 줄이기 위한 축약이 아니다. 모든 Numbered Major Section과 기존 내부 Heading을 유지했다. 새 Key Takeaways는 Chapter 마지막에 한 번 추가했다.

### Major Changes

| Backup Section | Rewritten Section | Change and Reason |
|---|---|---|
| 2.1 Why Coordinate Systems Matter | 2.1, Coordinate System, Space, Why Multiple Spaces Are Needed | 숫자 예제에서 시작하던 도입을 Cube 이동·Camera 이동과 Mesh 내부 Data 유지 문제로 바꾸었다. “Mesh의 형태 / Scene의 배치 / Camera의 관점”이 서로 다른 기준을 요구한다는 이유를 먼저 설명한 뒤 Origin·Axis·Space를 소개한다. Local→World→View→Clip→NDC→Screen의 목적을 유지했다. |
| 2.2 Position, Direction and Vector | 2.2, Vector, Figure 2-2 context | XYZ Data 목록보다 순수 Translation이 위치만 바꾸는 현상을 먼저 보여준다. Vector AB의 A=(1,1,0), B=(4,3,2), 결과=(3,2,2)를 유지하고, 도착점−출발점의 성분 변화량을 Formula 전에 풀었다. Direction/Vector/Unit Vector와 Chapter03 연결을 유지했다. |
| 2.3 Local Space / Object Space | 2.3, Local Space in Shader, Figure 2-3 context | 정의보다 Tree Mesh를 여러 위치에서 재사용하는 문제를 먼저 설명한다. Origin/Pivot, Local Axes, Object/Edit Mode, Apply Transform, Local 값이 크다는 이유로 World 값이 되지 않는다는 설명 모두 유지했다. Local 높이 성분 예에는 Axis Convention을 명시했다. |
| 2.4 World Space | 2.4, Translation, Rotation, Scale, Object World Transform | 서로 다른 Object의 Local Position만으로 Character/Tree/Light의 관계를 비교하기 어렵다는 문제를 선행했다. T/R/S를 각각 이동·방향 변경·Origin에서의 간격 변경 문제로 설명하고 기존 숫자 예를 유지했다. Parent/표시 Space 때문에 Panel 값이 항상 World Transform이 아닌 조건을 분리했다. |
| 2.5 View Space / Camera Space | 2.5, View Transform Is the Inverse of Camera Transform | 특정 Camera에서 읽을 위치가 필요하다는 이유를 강화했다. Inverse는 Camera 배치를 되돌리는 관계로 먼저 설명하고 Translation만 빼는 경우와 Rotation까지 되돌려야 하는 경우를 나눴다. View는 여전히 3D이며 Screen과 다르다는 전체 설명을 유지했다. |
| 2.6 Projection | 2.6, What Is a Matrix?, FOV and Perspective Distortion | 두 Cube의 화면 크기를 Depth에 따라 다르게 만들어야 한다는 문제에서 출발한다. Matrix는 Vertex마다 변환을 일관되게 적용하는 도구로 소개한다. Perspective/Orthographic, Frustum, Near/Far, FOV/Aspect Ratio와 Depth 의미를 모두 유지하고 FOV/Camera 이동 구분은 Note로 배치했다. |
| 2.7 Clip Space | 2.7, Clip Position Has Four Components, Clip Range, Z Range, Perspective Divide | 경계에 걸친 Triangle에서 남길 부분을 정해야 한다는 문제를 먼저 제시했다. w를 Frustum 폭과 이후 Divide에 필요한 값으로 설명한 뒤 조건식을 제시한다. 현재 Fig2_07에 맞지 않는 고정 Clip Cube 언급은 실제 Homogeneous 조건 설명으로 수정했다. Vertex outside와 Triangle clipping/culling 차이는 유지했다. |
| 2.8 Homogeneous Coordinate and W | 2.8, Position Uses w=1, Direction Uses w=0, Homogeneous Coordinate Is More Than Position vs Direction | Matrix 하나에서 위치에만 Translation을 참여시키고 Projection까지 연결해야 하는 문제를 먼저 설명한다. w=1/0을 입력 범위로 명시하고 (2,4,6,2)와 (1,2,3,1)의 Divide 동치를 유지했다. Projective 동치와 clipping sign 판정 차이는 Mathematical Note로 옮겼다. |
| 2.9 Perspective Divide and NDC | 2.9, Perspective Divide Applies to Y as Well, Perspective Divide and Depth | 도입부의 x_clip/w_clip 식을 뒤의 개념 설명으로 연결하고 어떤 값을 나누는지 먼저 안내한다. A/B의 2/2=1, 2/10=0.2 예, View Depth vs 직선거리 11.66 예, 동일 ray 조건, FOV/Aspect가 clipping 전에 반영되는 순서, Z range를 유지했다. Depth Precision/Reversed-Z caveat는 Note로 분리했다. |
| 2.10 Viewport Transform and Screen Space | 2.10, Pixel Coordinate and Pixel Center | “같은 NDC 중심이 해상도에 따라 다른 좌표가 된다”는 문제를 선행했다. Scale+Offset, Y 방향, viewport size+position, full/split/editor 예와 Z 유지 설명을 보존했다. 1920/1080은 경계이며 마지막 Pixel index는 1919/1079라는 구분을 보강했다. |
| 2.11 Matrix Transform Basics | 2.11, Matrix as a Transform Rule, Matrix Multiplication Concept | 여러 Vertex의 Position/Direction을 같은 순서로 변환해야 하는 문제를 먼저 제시한다. Scale/Rotation/Translation의 관계를 설명한 뒤 4×4 배열과 M×v=v′를 보여준다. Combine T×R×S와 Transform order 및 Matrix가 항상 Space Conversion은 아니라는 본문을 유지했다. |
| 2.12 Model / View / Projection Matrix | 2.12, A Simple View Transform Example, A Small Matrix Example, Matrix Multiplication Order | Object/Camera/Projection의 책임을 왜 분리하는지 먼저 설명한다. 기존 4×4 M, Position=(5,4,0,1), Direction=(0,2,0,0), Normalize=(0,1,0), Camera 이동 예를 모두 유지했다. 수치 예에서 S→R→T를 문장으로 먼저 계산한 뒤 Matrix를 제시한다. Rigid Camera Inverse와 storage/multiplication 구분은 Implementation Note로 배치했다. |
| 2.13 Position Transform vs Direction Transform | 2.13, Why Normal Becomes a Special Case, Normal Matrix | w 수치보다 Translation이 Direction에 섞이면 방향이 잘못된다는 문제를 먼저 보여준다. Non-uniform Scale→Tangent 변화→일반 Direction으로 Normal 변환하면 수직 관계 손실→역방향 Scale 보정→Inverse Transpose를 연결했다. 증명은 추가하지 않았고 Chapter03 3.5를 Primary Explanation으로 유지했다. |
| 2.14 Tangent Space | 2.14, TBN Basis, Flat Normal Map, Tangent Normal vs World Normal, TBN Matrix, Normalization After Transform | Texture Direction이 어떤 기준에 저장됐는지와 Lighting Space로 어떻게 옮길지를 먼저 묻는다. RGB Encoding, Decode, Tangent Space, TBN Conversion을 별도 단계로 유지했다. 각 Tangent 성분이 목표 Space의 T/B/N을 얼마씩 사용하는지 설명한 뒤 TBN×N 식을 제시한다. Mirrored UV, Handedness, Interpolation, Seam/Vertex Split, Unit/Basis 조건과 비용 연결을 모두 유지했다. |
| 2.15 Coordinate Space Conversion in Unreal | 2.15, Object Position, VertexNormalWS, PixelNormalWS, Camera Vector, Transform, Compare Values, Dot Product | Space mismatch 문제에서 시작해 Concept을 Node 계약으로 연결한다. Bounds center / Actor origin / Pivot 구분, Vertex와 현재 Pixel Normal 구분, Camera Forward와 Surface→Camera Direction 구분을 보강했다. 기존 Offset은 World이며 Local Rotation/Scale을 제거하지 않는다는 수정 사항을 유지했다. 실제 Engine 검증을 완료한 것처럼 쓰지 않는다. |
| 2.16 Complete Coordinate Flow | 2.16 introduction, Matrix Chain, Key Takeaways | 기존 모든 Flow/Table/Checklist/Formula를 유지하면서 Position의 화면 경로와 Direction의 Lighting 경로가 목적이 다르다는 읽기 기준을 선행했다. Matrix Chain의 입력·출력 Space 연결을 설명한 뒤 기존 Formula를 제시하고 마지막 5개 Key Takeaways로 정리했다. |

### Added Explanation

- Origin과 Axis를 정하기 전에 “같은 숫자를 받아도 다른 장소를 찾는 문제”를 설명했다.
- Position/Direction이 같은 XYZ 모양이어도 Translation의 처리 목적이 다르다는 원인과 결과를 연결했다.
- Local/World/View는 Mesh Data 재사용, Scene의 공통 비교, 특정 Camera의 해석이라는 각각의 질문에 답한다.
- Matrix는 숫자 배열보다 “동일 규칙의 반복 적용과 순서 결합”으로 이해하도록 연결했다.
- Homogeneous 입력의 w=1/0과 Projection 출력의 w_clip을 구분하고 각 역할의 이유를 설명했다.
- TBN의 입력 Direction 성분이 World T/B/N을 얼마씩 사용하는지를 Formula 앞에서 설명했다.
- Decode와 Space Conversion이 다른 작업임을 분리했다. 이미 Decode한 Sampler 값에 RGB×2−1을 다시 적용하지 않는 조건을 유지했다.
- Same Space는 Angle 비교의 필요조건이며 직교 Basis/Unit Direction 조건도 확인해야 한다는 Note를 추가했다.
- Figure마다 독자가 확인할 숫자, 축 Convention, 단순화의 범위를 설명했다.

### Removed / Moved Details

내용을 Summary로 줄이거나 원본 기술 예제를 삭제하지 않았다. 기존 설명이 충분한 Local Axes, shared Mesh, DCC mode, clipping primitive, View Depth 계산, viewport 예, mirrored/seam/Vertex Split, World Offset/Local Transform, Shader cost 설명은 그대로 사용했다.

| Detail | Backup Treatment | Rewritten Treatment | Reason |
|---|---|---|---|
| FOV와 Perspective Compression/Camera 이동 조건 | 2.6 FOV 본문 중 한 긴 문장 | 같은 Subsection의 Technical Note | 먼저 FOV에 따른 범위·배율을 이해한 뒤 조건을 확인하도록 분리 |
| Homogeneous Projective 동치와 clipping sign caveat | 2.8 동치 설명의 첫 문장에 함께 등장 | 같은 Subsection Mathematical Note | Divide의 비율 관계를 먼저 이해한 뒤 부호 예외를 확인 |
| Depth Precision/Reversed-Z/저장 형식 caveat | 2.9 마지막 문단에 밀집 | 같은 Subsection Technical Note | Z가 Depth로 연결되는 Main Flow와 구현 조건을 분리 |
| Rigid Camera inverse와 R_c transpose 조건 | 2.12 수치 예 마지막 문장 | 같은 Subsection Implementation Note | Position/Direction 결과를 먼저 추적하도록 분리 |
| Row/Column Vector와 row/column-major storage 구분 | 2.12 곱 순서 설명 중 밀집 | 같은 Subsection Implementation Note | 실제 적용 순서를 먼저 이해하고 구현 Convention 확인 |
| TBN decode/orthonormal/transpose/handedness | 2.14 식 전후 두 긴 문장 | 개념 설명 후 Implementation Note | 변환 목적과 구현 조건을 단계적으로 구분 |
| Object Position Needs Technical Verification | 2.15 첫 문장 | 기준점 설명 뒤 Verification Note | 확정 가능한 Node 정의와 대상 Engine 검증을 구분 |
| “Figure2-7의 고정 Cube” | Backup가 현재 Figure와 불일치 | 현재 Figure의 w 의존 Clip 조건으로 수정 | 그림에 없는 항목을 설명하지 않도록 정정 |

원본 Chapter08 Shadow Map 연결과 Chapter09 Depth/Vertex Split/Shader 비용 관련 네 연결을 모두 유지했다. 원본에 구체적인 Engine 버전이나 실측 데이터는 없었으며 새로운 버전 검증 결과를 만들지 않았다.

### Formula Changes

| Chapter | Formula / Concept | Backup Treatment | Rewritten Treatment | Decision |
|---|---|---|---|---|
| 02 | Vector AB=B−A | Vector 정의 뒤 예제로 제시 | 목적지에 도달할 XYZ 변화량을 먼저 읽은 뒤 동일 A/B/결과 계산 | Essential / Keep |
| 02 | Local→World Translation | Figure 및 본문에서 Translation-only 예 | Local의 재사용과 World 공통 기준을 먼저 설명하고 Identity Rotation/Scale 조건을 명시 | Essential / Keep |
| 02 | Clip −w≤x/y≤w, Z range | 짧은 설명 뒤 조건; Fig2_07의 고정 Cube 언급이 실제 파일과 불일치 | Frustum이 멀수록 넓어지는 이유→w 범위→API Depth 조건, 실제 그림 내용으로 수정 | Explain First |
| 02 | w=1 Position / w=0 Direction | 선언형 소개와 예 | Translation 참여/제외 목적→w 표현→숫자 예, Affine 입력에 한정 | Essential / Keep |
| 02 | Homogeneous equivalent Points | 동치와 clipping caveat가 첫 문장에 함께 있음 | Divide 비율→(2,4,6,2)/(1,2,3,1) 유지→부호 caveat Note | Explain First / Move Caveat |
| 02 | x/y/z_ndc=clip/w_clip | 2.9 도입부에서 식 선행 | Perspective 문제와 input-vs-output w 구분을 선행; 식과 모든 수치 예는 후속 Subsection에 유지 | Explain First |
| 02 | View Depth vs Distance sqrt(6²+10²)≈11.66 | 설명 후 수치 비교 | 원본 설명·예제 유지; Fig2_09에서는 다른 비교 조건을 별도 명시 | Essential / Keep |
| 02 | Viewport Scale+Offset | NDC 범위 설명 뒤 Pixel 수치 예 | 현재 Viewport의 크기·시작 위치를 왜 반영하는지 먼저 설명; 숫자 예 유지 | Essential / Keep |
| 02 | M×v=v′ / 4×4 array | 배열이 먼저 보이는 Matrix Subsection | Transform 규칙과 Data 반복 적용 이유→숫자 배열→곱 관계 | Explain First |
| 02 | M=T×R×S | 개념 설명과 Matrix 수치 예 | S→R→T를 Position/Direction에 먼저 적용해 읽은 뒤 동일 4×4 Matrix와 모든 출력 제시 | Explain First |
| 02 | p_clip=P×V×M×p_local | 곱 순서와 Convention 주의 | 입출력 Space 연결→Column Vector 오른쪽부터 적용→식, HLSL/storage Note | Explain First |
| 02 | Camera inverse R_c transpose | 수치 예 마지막 압축 문장 | Translation/Rotation을 되돌리는 이유→동일 rigid inverse 조건 Note | Explain First / Move |
| 02 | Normal Matrix / Inverse Transpose | Non-uniform 문제 뒤 명칭 | Tangent 변화→수직 관계 목적→역방향 Scale 보정→명칭; 기존 Chapter03 3.5 연결 | Explain First |
| 02 | N_world=normalize(TBN×N_tangent) | 짧은 TBN 정의 뒤 식 | 성분이 목표 Space T/B/N을 얼마씩 쓰는지 설명→식→조건 Note | Explain First |
| 02 | RGB×2−1 | Engine sampler 중복 Decode caveat | 동일 caveat 유지; 저장 Decode와 Space Conversion을 먼저 구분 | Keep / Move to Implementation Note |
| 02 | N·L / dot(N,V) | Unreal 본문과 Fig2_15에서 제시 | 먼저 같은 Calculation Space의 Unit Direction과 비교 목적을 설명한 뒤 표기 | Essential / Keep |

새로운 Cross Product Component 전개, 일반 Matrix inverse 알고리즘이나 Inverse Transpose 증명은 추가하지 않았다.

### Structure Changes

원본 2.1–2.16 numbering과 모든 기존 internal headings를 유지했다. Main Flow 중 조건 설명은 해당 Concept 뒤의 12개 details Notes로 분리했다. Major Section을 획일적인 Why/What/How 형태로 바꾸지 않았다.

Formula를 포함한 Figures 2-1/2/3/4/7/8/9/10/11/12/13/14/15는 **각 원래 Section 안에서** 설명 뒤로 이동했다. Figure2_05/06은 익숙한 Camera/Projection 현상을 보여주므로 도입 위치를 유지했다. Figure2_16은 이전 15개 Section을 연결하는 Figure라서 기존 Summary 위치를 유지했다. 이동해도 Figure path/number와 문서 전체의 Figure 순서는 동일하다.

### Figure Review

16개 실제 PNG를 모두 열어 Pixel/Label/숫자와 본문을 비교했다. 파일 존재만으로 Verified라고 처리하지 않았다. Verified는 정적 그림과 본문/수치 관계 검토가 끝났다는 뜻이며 Unreal Engine 실행 검증을 뜻하지 않는다.

| Figure | Exact Path | Status | Rewrite Action | Reason |
|---|---|---|---|---|
| Fig2_01 | Figures/Chapter02/Fig2_01.png | Verified | Keep; move after Coordinates Relative to the Camera | Identity Rotation, Scale1, Local(1,0,0)+T(5,2,0)=(6,2,0), Camera(4,1,5) subtraction=(2,1,−5), Forward−Z를 직접 확인했다. 계산 전에 조건을 설명한다. |
| Fig2_02 | Figures/Chapter02/Fig2_02.png | Verified | Keep; move after Vector Between Two Positions | Position/같은 Direction 화살표/A→B=(3,2,2)의 의미가 본문과 일치한다. |
| Fig2_03 | Figures/Chapter02/Fig2_03.png | Verified | Keep; move after Object Mode and Edit Mode | Translation-only (1,1,1)+(5,2,1)=(6,3,2), Object/Edit Mode와 Mesh/Transform 분리가 일치한다. |
| Fig2_04 | Figures/Chapter02/Fig2_04.png | Verified | Keep; move after Same Local Position, Different World Position | 공통 World의 Object Origin 위치와 Translation-only (1,1,1)+(5,2,0)=(6,3,1)이 일치한다. |
| Fig2_05 | Figures/Chapter02/Fig2_05.png | Verified | Keep introductory position; add reading context | Camera 기준 3D와 World 공통 기준의 차이를 확인했다. Forward/Depth 부호는 Figure의 예시이며 Convention caveat도 유지한다. |
| Fig2_06 | Figures/Chapter02/Fig2_06.png | Verified | Keep introductory position; add comparison assumptions | 동일 크기 Object의 원근 크기 비교와 View→Clip→Divide→NDC→Viewport→Screen 연결을 확인했다. 가림을 제외한 독립 크기 비교 범위다. |
| Fig2_07 | Figures/Chapter02/Fig2_07.png | Verified | Keep updated context; move after Clip/NDC concepts | 실제 PNG는 이미 고정 Clip Cube를 사용하지 않는다. −w≤x/y≤w,0≤z≤w와 NDC Z0~1, (2,1,3,4)÷4=(.5,.25,.75), continuous screen boundary/index 구분이 맞다. stale Backup 설명만 정정했다. |
| Fig2_08 | Figures/Chapter02/Fig2_08.png | Verified | Keep; move after Homogeneous Coordinate and Matrix | 입력 w=1/0과 Projection 출력 역할이 분리됐다. Near/Far Clip÷w 값이 맞고 같은 XY/다른 양의w 조건이다. Near/Far Plane을 의미하지 않는다는 Context를 추가했다. |
| Fig2_09 | Figures/Chapter02/Fig2_09.png | Verified | Keep updated context; move after XY numerical explanation | +Z Forward, x_clip=x_view, w_clip=z_view 단순화와 2/2=1,2/10=.2, same ray caveat를 실제 PNG에서 확인했다. Z 생략 범위를 명시했다. |
| Fig2_10 | Figures/Chapter02/Fig2_10.png | Verified | Keep; move after Y mapping example | 1920×1080에서 NDC(.5,.5)→(1440,270), Top-left/Down Y와 viewport/전체 screen 구분이 맞다. |
| Fig2_11 | Figures/Chapter02/Fig2_11.png | Review Required | Keep; move after Matrix Multiplication Concept; scope caption | 4×4 Column Vector와 Model/View/Projection 흐름은 맞다. 제목 아래 Matrix=다른 Space 변환 문장은 모든 Matrix의 정의로 읽으면 범위가 좁다. 아래 Problem Table의 문구 검토 필요. |
| Fig2_12 | Figures/Chapter02/Fig2_12.png | Verified | Keep; move after One Vertex, Multiple Coordinates | Model T(4,3,2), Local(1,0,0)→World(5,3,2), Camera(3,2,10)→View(2,1,−8), Column PVM 순서가 맞다. P 값은 설정에 따라 달라진다. |
| Fig2_13 | Figures/Chapter02/Fig2_13.png | Review Required | Keep; move after Normal Matrix; clarify Normal context | Position/Direction Translation 및 M=T·R·S 조건은 맞다. Surface에 수직인 Normal Label은 Geometric Normal의 예로 읽어야 하며 Shading Normal 전체의 정의로 확대하지 않도록 문구 검토를 기록한다. |
| Fig2_14 | Figures/Chapter02/Fig2_14.png | Review Required | Keep updated context; move after TBN Matrix and Decode explanation | Orthonormal/TBN Column convention, raw Decode vs sampler Decode 구분과 flat RGB=(.5,.5,1), Normal=(0,0,1)은 맞다. N=Surface 수직 Label은 Smooth Shading Basis와 Face Normal 구분을 더 표시할 수 있다. |
| Fig2_15 | Figures/Chapter02/Fig2_15.png | Engine Verification Required | Keep updated context; move after Same-Space and Node explanation | Space 목록이 실행 순서가 아니라는 표시, Camera 방향, Object Position caveat, Pixel Normal 조건, Unit N/V가 맞다. Node 출력·Material Domain·Transform 지원 및 실제 graph compile은 대상 Engine에서 확인해야 한다. |
| Fig2_16 | Figures/Chapter02/Fig2_16.png | Verified | Keep closing summary | Position Flow와 Direction의 필요한 Space까지만 변환하는 경로가 분리돼 있다. Column 입력, clipping→divide, top-left screen formula, basis/decode 흐름이 본문과 일치한다. viewport origin(0,0) 예의 scope를 유지했다. |

현재 이미지 자체는 수정하거나 생성하지 않았다. 다음은 눈으로 확인한 범위에서 남긴 Figure 문구 검토 항목이다.

| Figure | Problem | Why It Is Incorrect / Incomplete | Suggested Correction | Verification Needed |
|---|---|---|---|---|
| Fig2_11 | Matrix를 “다른 Space로 변환하는 계산 구조”로만 정의하는 상단 문구 | Rendering에서 흔한 용도지만 동일 Space 안의 Scale/Rotation 등도 Matrix로 표현하므로 일반 정의로는 불완전하다. Backup의 Matrix Is Not Always a Space Conversion과 함께 읽어야 한다. | “Transform 규칙을 표현하는 계산 구조이며 Rendering에서는 Space Conversion에 사용된다”처럼 용도와 일반 범위를 분리한다. | 사람이 Figure 문구와 본문 2.11의 용어 범위를 검토한다. 현재 caption에 범위를 명시했으나 그림 자체는 보존했다. |
| Fig2_13 | Normal을 Surface 수직 방향이라고 일반 표현 | Geometric Normal 도식으로는 맞지만 Shading Normal의 임의 Detail 방향까지 Face Normal과 같아야 한다고 읽으면 틀리다. | Normal panel에 Geometric Normal example을 표시하고 Shading Normal 구분을 짧게 연결한다. | 사람이 Surface Normal 문구와 Chapter03의 Geometric/Shading Normal 설명을 함께 검토한다. |
| Fig2_14 | Basis N을 Surface 수직 방향으로만 표현 | 정규 직교 Basis의 설명은 맞지만 smooth shading의 Basis N은 Vertex Shading Normal에 맞출 수 있어 Face Normal과 다를 수 있다. | Face Normal과 Basis/Shading Normal을 분리하는 qualifier를 추가한다. | 사람이 실제 Asset의 tangent basis 생성 규약과 Figure 설명을 검토한다. |
| Fig2_15 | Node 목록을 구체 Engine 출력 보장으로 읽을 가능성 | 정적 Diagram 확인으로 Material Domain/버전/컴파일 지원을 검증할 수 없다. | 현재 버전에서 확인한 exact Node/output/context를 기록하고 현재의 조건 구분을 유지한다. | Engine에서 VertexNormalWS/PixelNormalWS/CameraVectorWS/ObjectPositionWS/ScreenPosition/Transform compile와 visualization 확인. |

### Technical Notes

| Item | Backup → Rewrite | Evidence / Verification Boundary |
|---|---|---|
| Fig2_07 content mismatch | 실제 PNG에 없는 고정 Cube 언급→현재 Homogeneous inequalities 설명 | 16개 원본 PNG를 열어 확인했다. Clip 조건은 [Microsoft Viewports and Clipping](https://learn.microsoft.com/en-us/windows/win32/direct3d9/viewports-and-clipping)의 Homogeneous 관계와 대조했다. 이는 해당 convention 설명이며 모든 API의 Z 범위로 확대하지 않는다. |
| Local height axis | Local Y 높이 예→Y-up 예이며 Unreal은 Z-up | [Epic Coordinate System and Spaces](https://dev.epicgames.com/documentation/en-us/unreal-engine/coordinate-system-and-spaces-in-unreal-engine)로 Unreal Z-up을 확인했다. Asset의 import/회전 상태와 local convention은 구현에서 따로 확인한다. |
| Normal semantics | 수직을 무조건 모든 Normal 정의로 적용하는 잔여 문구→Geometric/Shading/Basis 구분 | Chapter03과 기존 backup의 구분을 유지했다. Inverse Transpose/re-normalize는 [NVIDIA GPU Gems Normal Transform](https://developer.nvidia.com/gpugems/gpugems/part-vi-beyond-triangles/chapter-42-deformers)와 대조했다. 새 증명은 추가하지 않았다. |
| Camera View example | 가까운 위치라는 모호한 표현→Translation-only X Offset=(5,0,0) | 숫자 계산과 축 정렬 가정을 명시했다. 이 예의 X Offset은 View Depth 또는 Screen 위치를 직접 뜻하지 않는다. |
| Matrix multiplication | PVM 표기/수학 convention 유지→HLSL mul 인수 규칙을 구현 Note에 연결 | [Microsoft HLSL mul](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-mul)은 왼쪽 Vector를 Row, 오른쪽 Vector를 Column으로 읽는다. Storage는 별도 확인한다. |
| TBN basis | 기본 조건을 짧은 문장으로 함께 나열→성분 변환 후 조건 Note | Unit Normalize와 orthogonalization을 구분하고 transpose=inverse는 orthonormal일 때라는 기존 조건을 유지했다. Engine basis/handedness/nonuniform 처리는 실행 검증 전 확정하지 않는다. |
| ObjectPositionWS | generic Object Position Needs Verification→bounds center 정의+기존 exact Node 검증 Note | [Epic Vector Material Expressions](https://dev.epicgames.com/documentation/en-us/unreal-engine/vector-material-expressions-in-unreal-engine)로 bounds center를 확인했다. Actor origin/Pivot과 동일시하지 않았다. |
| VertexNormalWS / PixelNormalWS / CameraVectorWS | Vertex/Pix final/Camera 범위가 압축→Vertex context, current Pixel normal, Surface→Camera 명시 | 같은 Epic 문서의 Node 계약을 대조했다. 실제 Material 경로와 대상 Engine 지원은 Remaining Review Items다. |
| Unreal Transform support | 일반 Position/Direction 개념→특정 Expression의 지원 범위와 Scale caveat 분리 | [Epic Vector Operation Material Expressions](https://dev.epicgames.com/documentation/en-us/unreal-engine/vector-operation-material-expressions-in-unreal-engine)는 Transform 지원 Space와 Non-uniform Scale 제한을 기재한다. 문서만으로 실제 project version 동작을 검증했다고 쓰지 않았다. |
| Same Space and Angle | 어느 Space든 같으면 동일 Angle이라고 과대 해석 가능→직교 기준 Unit Direction 조건 Note | Dot/Angle은 일반적인 Euclidean orthonormal basis를 전제로 한다. Non-uniform Scale이 섞인 Local basis로 단순 변환하면 World Angle 유지가 자동 보장되지 않는다는 범위를 명시했다. |
| Pixel coordinates | Screen 경계=Width/Height 예→경계와 index 및 center 별도 | 1920 Pixel의 index는 0~1919다. 정밀 Sample Center/Screen Y convention은 사용하는 API로 확인하도록 유지했다. |

원본의 실무 정보는 보존했다. Object Origin과 Pivot은 같은 개념으로 합치지 않았고, WorldPosition−ObjectPosition은 World Offset이지 inverse Model이 적용된 Local Position은 아니라는 기존 교정 내용을 유지했다. Normal은 Translation을 받지 않으며 Scale 조건에 따라 일반 Direction과 다른 변환이 필요하다는 관계를 지켰다.

### Remaining Review Items

- 대상 Unreal Engine 버전과 Material Domain에서 ObjectPositionWS의 bounds center와 Actor origin/Pivot을 별도 시각화한다.
- VertexNormalWS와 PixelNormalWS의 Shader Stage/Input 지원, Normal Map 적용 전후 출력과 Compile 결과를 확인한다. Substrate 등 특정 경로의 동작을 이 문서 검토로 확인했다고 주장하지 않는다.
- CameraVectorWS의 Space/Surface→Camera 방향 및 Normalize 조건을 실제 Graph에서 확인한다. Camera Forward Axis와 혼용하지 않는다.
- ScreenPosition의 출력 모드, Range, Viewport/Render Target 기준을 확인한다. Unreal Node의 Screen Data를 연속 Pixel coordinate 예와 자동으로 동일시하지 않는다.
- Transform/TransformPosition의 지원 Source/Destination과 Non-uniform Scale/Normal 처리 제한을 project version에서 검증한다. 일반 수학의 Position/Direction 구분과 특정 Node 구현을 분리한다.
- TBN의 import/bake basis, Mirrored UV Handedness, Seam/Vertex Splits, Interpolation 뒤 Unit/orthogonal 조건을 실제 Asset에서 확인한다.
- API별 Clip/NDC Z Range, current Projection, Near/Far/Reversed-Z와 Depth 저장 형식을 확인한다. 기존 Chapter08 Shadow Map 및 Chapter09 Debug/Cost 연결을 유지한다.
- Figures2_11/13/14의 qualifier와 Fig2_15의 실제 Engine 계약을 사람 검토로 마무리한다. 이미지 내용은 이번 Rewrite에서 수정하지 않았다.
- GitHub Markdown에서 긴 Section/Note가 자연스럽게 읽히는지 마지막으로 사람의 편집 Review를 진행한다. Chapter05 자체는 수정하지 않았다.

### Comparison Summary

**Before:** 이미 충분한 Local/World/View, Projection, numeric example와 practical caveat가 있었지만, 일부 도입에서는 Definition 또는 Formula를 먼저 읽어야 했다. Homogeneous Projective 조건, Matrix storage/inverse, Normal/TBN 조건과 Node 계약이 짧은 문장에 함께 들어 있었다. Formula가 많은 Figure가 Section 앞에 있어 본문의 설명 전에 눈에 들어왔다.

**After:** 원본의 범위와 예제/기술 조건을 유지하면서 각 Major Concept의 필요를 먼저 설명했다. Formula는 필요한 관계를 문장과 Data Flow로 이해한 뒤 읽는다. 조건은 Concept 뒤의 Notes에 두었고, 실제 Figure 내용과 맞지 않는 설명을 Audit에 드러내어 교정했다.

**Expected Reader Experience:** 처음 읽는 독자는 Mesh의 형태를 Local에서 보존하고, World의 공통 기준으로 배치·관계를 계산하고, View에서 Camera 기준으로 읽고, Clip/NDC/Viewport로 화면에 연결하는 목적을 따라갈 수 있다. 방향의 Translation 제외와 Normal의 특별한 변환, Normal Map의 Decode/TBN 관계도 같은 Data 의미·기준 Space의 질문으로 연결한다.

---

## 5. Chapter 03 Audit

### Backup Source

`Chapter03_LightingMathematics_backup.md` — 2026-10-01의 최근 Concept-first Review가 반영된 원본이다.

### Rewritten File

`Chapter03_LightingMathematics.md`

### Major Changes

| Backup Section | Rewritten Treatment | Reason |
|---|---|---|
| Chapter opening / 3.1 From Geometry to Surface Data | Geometry → Rasterization → Shader의 문장을 분리하고 Position, Normal, Tangent, UV를 각각 설명 | 서로 다른 입력 역할이 한 문장에 압축되어 있었다. |
| 3.2 Direction and Magnitude | 같은 방향을 비교하려는 상황을 먼저 제시한 뒤 Vector의 길이 문제로 연결 | Vector 정의보다 Normalize가 필요한 이유를 먼저 알 수 있도록 했다. |
| 3.3 Dot Product | 기존 문제 → 원하는 결과 → NdotL → Cosine → Clamp 순서를 유지 | 최근 개선된 Concept-first 흐름을 되돌리지 않았다. |
| 3.4 What Is a Surface Normal? | 같은 Mesh의 각진 모습과 부드러운 모습의 차이에서 Geometric/Shading Normal 구분으로 연결 | 실제 면 방향과 계산 방향을 구분해야 할 이유를 먼저 설명했다. |
| 3.4 From Vertex Normal to Pixel Normal | 서로 다른 방향의 보간에서 성분이 상쇄될 수 있다는 중간 설명 추가 | 보간 후 Unit Length를 다시 확인해야 하는 이유를 보강했다. |
| 3.5 Normal Transformation | 기존 2D Non-Uniform Scale 예제, 역방향 Scale 보정, 일반 Transform, Inverse Transpose의 순서를 그대로 유지 | 복잡한 Matrix 증명을 다시 추가하지 않았다. |
| 3.6 View Direction | Perspective에서는 하나의 Camera라도 Surface 위치마다 V가 달라진다는 연결 추가 | Camera Forward와 Surface → Camera 방향을 혼동하지 않게 했다. |
| 3.7 Lighting Vector Flow | Chapter 03의 방향 관계 → Chapter 04의 Material Data → Chapter 05의 응답을 분리해 연결 | 다음 Chapter에서 기존 입력이 어떻게 쓰이는지 명확하게 했다. |

### Added Explanation

- Normalize, Dot Product, Clamp의 역할 차이를 3.3의 Key Takeaways에서 정리했다.
- Normal Transform으로 방향을 준비하는 단계와 Normalize로 길이를 맞추는 단계를 3.5에서 다시 구분했다.
- Figure 3-4의 `(-1, 2)`와 본문의 `(-0.5, 1)`이 같은 방향이라는 점을 명시했다.
- Fig3_05의 Camera 식과 Fig3_06의 L/V Position 차이 경로가 각각 Perspective Camera / Point Light 예제라는 적용 범위를 Caption에 명시했다.

### Removed / Moved Details

- Face Normal의 면적 0 Triangle과 비평면 Polygon 조건을 `Technical Note — Degenerate Geometry`로 옮겼다. 정보는 삭제하지 않았다.
- Zero-Length Vector, Matrix Convention, Zero Scale의 기존 Implementation Note를 모두 유지했다.
- DCC Tool에서 자동 처리된 정상적인 결과를 볼 수 있다는 설명과 Debugging / Basic Verification 전체를 유지했다.
- Formula가 들어 있는 Figure는 관련 설명 뒤로 옮겼다. Figure 자체와 Figure 간 순서는 유지했다.

### Formula Changes

| Formula / Concept | Backup Treatment | Rewritten Treatment | Decision |
|---|---|---|---|
| `normalize(Vector)` / N, L Normalize | 이미 길이 통일의 필요성 설명 뒤에 제시 | 방향 비교가 필요한 상황을 도입부에 보강하고 Fig3_01을 계산 의미 설명 뒤로 이동 | Keep / Explain First |
| `NdotL = dot(N, L)` / `dot(N, L) = cosθ` | 같은 Space의 Unit Vector 조건과 원하는 출력 설명 뒤에 제시 | 기존 Formula와 순서 유지; Fig3_02는 Clamp 구분까지 설명한 뒤 배치 | Keep |
| `max(NdotL, 0)` / `saturate(NdotL)` | 연산의 범위 차이와 Signed/Clamped 구분 설명 | One-sided Opaque Surface 앞면의 기본 Diffuse라는 적용 범위를 명시 | Keep / Explain First |
| `normalize(cross(EdgeA, EdgeB))` | 두 Edge → 수직 방향 → Normalize 순서 | 순서 유지; 퇴화 Geometry 조건만 Note로 이동; Component 전개 추가 없음 | Keep / Move |
| `N = normalize(InterpolatedNormal)` | 보간 후 길이가 1이 아닐 수 있음을 설명 | 성분 상쇄의 직관을 보강하고 기존 Formula 유지 | Keep / Explain First |
| `dot(T, N) = 0` 및 2D Scale 수치 예제 | 수직 관계를 확인하는 값으로 사용 | 전부 유지; Geometry의 Normal과 Shading Normal 적용 범위 유지 | Keep |
| `transpose(inverse(M))` / `Nworld` | Scale 역보정의 직관 뒤에 Formula 제시 | 기존 설명과 Formula 유지; Fig3_04를 Formula 의미 설명 뒤로 이동 | Keep / Explain First |
| `normalize(TargetPosition - StartPosition)` / L / V | Position 차이 → Normalize 순서 | 그대로 유지; Perspective / Orthographic, Directional / Point / Spot 구분 유지 | Keep |

### Structure Changes

- 3.1–3.7의 번호와 주요 Section 범위를 유지했다.
- Fig3_01은 How Normalize Works 뒤, Fig3_02는 Signed/Clamped 구분 뒤, Fig3_03은 Vertex Normal 보간 뒤에 배치했다.
- Fig3_04는 Normal Matrix 의미 설명 뒤, Fig3_05는 Light/Camera 입력 비교 뒤, Fig3_06은 World Space 입력 준비 뒤에 배치했다.
- 주요 전환인 3.3, 3.5, Chapter 마지막에만 3–4개 항목의 Key Takeaways를 추가했다.

### Figure Review

아래 평가는 여섯 PNG의 실제 픽셀과 Backup/Rewrite 본문을 함께 확인한 결과다. `Verified`는 이 Concept 관계의 일치 확인이며 Engine에서 재현했다는 뜻은 아니다.

| Figure | Status | Rewrite Action | Reason |
|---|---|---|---|
| `Figures/Chapter03/Fig3_01.png` | Verified | Keep / Move After Explanation | A/B와 약 `(0.894, 0.447, 0)` 결과가 본문과 일치한다. |
| `Figures/Chapter03/Fig3_02.png` | Figure Revision Required | Keep / Add Caption / Move | Unit Vector의 Signed/Clamped 값은 맞지만 Footer가 `3.2 Dot Product`로 이전 번호를 사용한다. |
| `Figures/Chapter03/Fig3_03.png` | Verified | Keep / Add Caption / Move | Face/Vertex Normal, Smooth/Flat Shading과 Silhouette 유지 관계가 본문과 일치한다. |
| `Figures/Chapter03/Fig3_04.png` | Verified | Keep / Add Caption / Move | 잘못된 `(-2,1)`과 보정한 방향의 수직 관계, Inverse Transpose, Normalize 구분이 맞다. |
| `Figures/Chapter03/Fig3_05.png` | Figure Revision Required | Keep / Add Scope Caption / Move | L의 방향 규약은 맞지만 Camera Position 차이의 V가 Perspective Camera 전용임을 이미지 안에서 구분하지 않는다. |
| `Figures/Chapter03/Fig3_06.png` | Figure Revision Required | Keep / Add Scope Caption / Move | 같은 물리 방향의 World/View 성분 비교는 맞지만 입력 표의 Position 차이 경로에 Point Light/Perspective Camera 적용 범위가 생략되어 있다. |

### Technical Notes

- Geometric Normal과 Shading Normal을 합치지 않았다. 3.5의 수직 관계와 2D 예제는 실제 Surface의 Geometric Normal을 기준으로 설명한다.
- Signed NdotL과 Clamped Factor, 방향 계수와 최종 화면 밝기, Normalize와 Space Conversion의 구분을 유지했다.
- `max`와 `saturate`가 Unit Vector 조건 아래 같은 방향 계수를 만들지만 일반 입력에서 같은 연산은 아니라는 설명을 유지했다.
- Perspective / Orthographic의 V 준비, Directional Light의 제공 방향 부호 확인, Spot Cone 추가 조건을 유지했다.
- Column Vector, Translation을 제외한 선형 3×3 Matrix, Inverse가 존재해야 하는 조건을 유지했다.
- 새 Matrix 증명, Cross Product Component 전개, Reflection/BRDF 유도는 추가하지 않았다.
- Zero-Length Normalize의 미정 결과는 [Microsoft HLSL normalize](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-normalize)의 적용 조건과 대조했다. Normal Transform의 수직 관계는 [PBRT — Applying Transformations](https://www.pbr-book.org/3ed-2018/Geometry_and_Transformations/Applying_Transformations)의 Normal 설명과 대조했다.

### Remaining Review Items

| Figure | Problem | Why It Is Incorrect | Suggested Correction | Verification Needed |
|---|---|---|---|---|
| Fig3_02 | Footer의 Section 번호가 3.2이다. | 현재 Chapter에서 Dot Product는 3.3이며, 독자가 다른 Section으로 이동할 수 있다. | 이미지 내부 Footer만 3.3으로 수정한다. | Figure 편집 후 본문 번호와 재대조. PNG는 이번 작업에서 수정하지 않았다. |
| Fig3_05 | V 식의 Perspective 적용 범위가 표시되지 않는다. | Orthographic Camera의 Viewing Ray는 평행하므로 하나의 Camera Position을 향하는 차이를 공통 경로로 사용할 수 없다. | Camera 패널에 Perspective Example Label을 넣고 Orthographic 별도 경로를 표시한다. | Figure Revision 및 사용 중인 Engine Projection 경로 확인. 현재 Caption에서 범위를 명시했다. |
| Fig3_06 | Position 차이로 L/V를 준비하는 입력 표가 범용처럼 보인다. | Directional Light는 Light Position 차이를 쓰지 않으며 Orthographic V도 Camera Position 차이를 쓰지 않는다. | 각 행에 Point Light / Perspective Camera 예제임을 표시한다. | Figure Revision 및 실제 Shader 입력 생성 경로 확인. 현재 Caption에서 범위를 명시했다. |

Engine에서의 Module 입력 검증은 수행하지 않았다. 실제 적용 시 3.7 Basic Verification의 방향 부호, 같은 World Surface 위치의 NdotL 불변, Non-Uniform Scale 수직 관계, 보간 후 길이를 확인한다. 이 검증 경로와 Chapter 08 연결은 원본대로 남겼다.

---

## 6. Chapter 04 Audit

### Backup Source

`00_Foundation/Chapter04_MaterialArchitecture_backup.md`

Rewrite 직전 원본과 동일하다고 확인된 Backup을 실제 비교 기준으로 사용했다. 전체 2,776줄을 잘림 없는 Chunk로 읽은 뒤 현재 파일을 재작성했다. Backup의 SHA-256은 `230fbc4c2e4711d19ae622ac59f26d678f07ed32c06fab409a3d8656d25a5f4a`다.

### Rewritten File

`00_Foundation/Chapter04_MaterialArchitecture.md`

Major Section 4.1–4.8과 원본의 모든 Subsection Topic을 유지했다. 원본의 88개 Topic Heading occurrence가 재작성 문서의 94개 Heading occurrence에 모두 보존된다. 설명은 53,879자에서 65,469자로 늘었다. 파일 크기는 84,339 bytes에서 103,037 bytes로 늘었다. 이는 정보 보존의 보조 지표이며, 아래 Section Mapping과 기술 항목 비교를 보존 근거로 사용한다.

### Major Changes

| Backup Section / Treatment | Rewritten Section / Treatment | Reason / Preserved Scope |
|---|---|---|
| Chapter Introduction: Geometry/Material/Lighting을 설명한 뒤 `Material Input → Texture / Parameter` 형태의 학습 흐름 | 같은 Sphere가 Plastic/Metal로 다르게 보이는 질문으로 시작하고 필요한 Property→Data Source→입력 해석→Shading 순서로 연결 | Input이 Texture를 생성하는 것처럼 읽힐 수 있는 흐름을 학습 순서로 명확히 했다. Geometry의 위치/형태, Material의 Property, Light/Camera 관계와 Chapter 03 연결을 유지했다. |
| 4.1 What Is a Material?: Texture와 Material의 Definition 뒤 Figure/예시 | Color만으로 Plastic/Metal 차이를 설명할 수 있는지 질문→동일 Geometry 예시→Figure→Property/Shader 역할 | 원본의 Plastic/Metal/Rough/Emissive, Material vs Texture, Material vs Shader, Material as Data, Geometry/Material/Lighting 합류를 모두 유지했다. Material Graph의 Data와 Logic, Architecture vs Compiled Variant 구분을 보강했다. |
| 4.2 Base Color에 Metallic workflow의 Dielectric/Diffuse/Metal/Specular/BRDF/F0를 한 문단으로 제시 | Base Color는 먼저 Color 입력 vs 최종 Color를 설명하고, Metallic의 Metal/Dielectric 소개 뒤 Technical Note로 기존 반사색 정보를 연결 | 미소개된 Metal/Dielectric 구분을 미리 알아야 하는 부담을 줄였다. Base Color의 Diffuse/Specular 역할, Chapter 05 BRDF/F0 연결, Roughness/Metallic/Normal/Emissive, Constants/Parameter/Texture/계산값의 범위를 유지했다. |
| 4.3 Texture as Material Data: Image/Data 정의, 종류별 설명, 현재 UV 예시와 Packing | Character의 위치별 Property가 Constant 하나로 표현되지 않는 문제→Texel별 Data→종류별 해석→현재 Sample 결과→Packing | 원본의 Base Color `(0.42, 0.28, 0.24)`, Roughness `0.65`, Metallic `0.0`, UV `(0.34, 0.62)`, Normal/Emissive/Mask 경로, RGBA/AO/Roughness/Metallic/Mask Packing 예시를 유지했다. 저장 RGB와 Linear Color, raw Normal과 decoded Direction을 구분했다. |
| 4.4 UV and Texture Sampling: 3D→2D Definition 뒤 Mesh UV/Interpolation, Sampling/Filtering | Surface의 Texture 주소가 필요한 문제→UV 대응→정규화 좌표→Vertex Attribute→Rasterization→Fragment/Pixel UV→Sample | UV가 Mesh에 저장되고 Triangle 내부로 전달되는 원인을 풀어 설명했다. Position/Normal/Tangent/UV/Vertex Color, Generated UV/Chapter 08 MatCap, 동일 UV의 다중 Texture, Resolution 예시, 모든 Sampler/Mip/Cost 정보를 보존했다. |
| 4.4 Sampling Does Not Always Read a Single Texel → Texel → Bilinear → Mipmap | Texel/Screen Pixel 관계를 먼저 설명하고, Texel Center 사이의 Sampling Point 문제→중간값→Bilinear→많은 Detail이 한 Pixel에 들어오는 문제→Mipmap | 용어가 필요해진 시점에 먼저 소개했다. Bilinear의 네 주변 Texel/위치 가중치, Mip 0–3, 거리뿐 아닌 footprint, Wrap/Clamp/Mirror, Cache/Resolution/Filtering/Platform과 Chapter 09 연결을 유지했다. |
| 4.5 What Is Color Space?→Why sRGB Exists→Linear 계산 | Human Perception→sRGB Storage/Encode→Decode 방향→Color Space 범위→Linear 계산→Color/Data Texture→Roughness 오류 | 저장과 계산의 숫자를 구분한 뒤 Definition을 연결했다. primaries/white point, HDR/이미 Linear Color 예외, sRGB Off의 한계, Numeric/Normal Data, Import/Production Debugging 정보를 유지했다. Roughness `0.50→약 0.214→낮은 Roughness→Glossy tendency`를 본문에 명시했다. |
| 4.6 Surface Direction 뒤 Tangent Basis/Channel Encoding/Decode/TBN | Geometry Detail의 Cost→Shading Direction→Height와 Direction 구분→Direction의 저장 범위 문제→기준 Space 필요→Tangent Basis→Encoding→Channel→Decode→같은 Lighting Space/TBN | 한 번에 RGB/Space/Decode/TBN을 처리하던 사고 단계를 분리했다. 모든 Channel/flat/+T/+B 예시, Encode/Decode 수식, raw/sampler-decoded 구분, Basis 조건, Normalize, DX/OpenGL G Convention, Animation, Silhouette/Depth/Collision/Shadow Geometry 한계를 보존했다. |
| 4.7 Parameters and Instances: 공통 Logic, 모든 Parameter 종류와 Runtime/Static 설명 | Logic 복제 문제→Non-Static/Static을 먼저 나눈 Parameter Interface→각 Type→Parent/Instance→Editor MIC→Runtime MID→Compiled Variant | Scalar/Vector/Texture와 Static Switch/Component Mask, 모든 원본 예시, Damage/Hit/Dissolve/Character State/Gameplay, Look Development, Parameter Groups, Instance 범위와 Chapter 09 연결을 유지했다. MIC와 MID의 차이를 명시했다. |
| 4.8 Material Data Flow: Mesh/Texture/Parameter/해석/Normal/Light 합류 및 Summary | 왜 단일 직렬 Flow로 읽으면 Source를 놓치는지 설명하고 여러 입력 경로의 준비→해석→합류로 구성 | 원본의 Position/Normal/UV/Tangent, 모든 Property Source, Opacity/Mask, N/L/V/Light Color/Intensity, raw Normal caveat, 같은 Space/Normalize, Unlit/Emission, Instance/Static 조건, Chapter 03 및 Chapter 08 Unlit+Emissive 연결을 유지했다. Chapter 05 입력 준비 지점만 연결하며 BRDF 내용을 복제하지 않았다. |

### Added Explanation

- Texture가 현재 Surface 위치에 사용할 Data를 제공하며 Texture 전체가 하나의 Property 값이 되지 않는다는 관계를 종류별 Sample Table과 함께 설명했다.
- UV가 3D Position의 축소 표현이 아니라 Surface/Texture 대응 정보라는 점을 보강했다. Vertex UV→Rasterization/Interpolation→Fragment/Pixel UV가 Chapter 01의 Attribute Flow와 연결된다.
- Fragment와 최종 Screen Pixel이 항상 일대일이 아니라는 범위를 짧게 연결했다. Perspective-correct Interpolation은 유지하되 수학적 전개를 추가하지 않았다.
- Texel Center 사이에서 사용할 중간값이 필요하다는 문제를 Bilinear 이름과 동작보다 먼저 설명했다. 네 Texel은 한 Mip Level의 주변 값임을 명시했다.
- sRGB Encode와 Decode의 목적·방향을 분리하고 Roughness 오류가 “더 매끄럽거나 더 거칠게 보임”으로만 남지 않도록 저장 `0.50`의 구체적인 Decode 결과와 Glossy 방향을 설명했다.
- sRGB Color Decode와 Normal Direction Decode를 서로 다른 작업으로 설명했다. sRGB Off가 Direction reconstruction까지 제거하지 않는다는 기존 주의를 보존했다.
- Normal Encoding 전에 음수 Direction과 unsigned RGB 저장 범위의 불일치를 설명했다. Tangent Space가 필요한 이유와 TBN이 목표 Space의 Axis 기여를 결합한다는 직관을 보강했다.
- Editor에서의 Material Instance Constant/MIC와 Runtime Material Instance Dynamic/MID를 분리했다. MID를 변경했을 때 실제 대상이 해당 MID를 사용해야 한다는 기본 확인점도 추가했다.
- 여러 Static 선택을 공유 Parent의 여러 Compiled Variant로 연결했다. Parent Logic 공유를 모든 Instance의 동일 Compiled Shader 보장으로 설명하지 않는다.
- 4.8의 일반적인 L/V 준비 흐름에 Light Type과 Camera Projection 조건을 연결했다. Directional/Point/Spot Light와 Perspective/Orthographic Camera가 모두 Position 차이로 Direction을 만든다고 해석하지 않도록 Chapter 03 Light/View Direction 범위를 명시했다.
- Key Takeaways는 4.4–4.8의 주요 구분이 끝난 지점에 배치했다. 모든 Subsection에 반복하는 Template은 사용하지 않았다.

### Removed / Moved Details

- 기술적인 Scope나 원본 Subsection Topic을 제거하지 않았다. 원본의 동일 목적 문장은 재서술했고, 일부 줄마다 분리되어 있던 Value/Arrow는 Table 또는 Data Flow Block으로 구성했다.
- Base Color의 Metallic workflow 반사색 구분과 Chapter 05 BRDF/F0 연결은 4.2 Metallic 뒤 Technical Note로 옮겼다. 원본 정보를 유지하되 Dielectric/Metal 소개 이전에 새 반사 개념들이 모이는 것을 피했다.
- Fig4_04의 affine 가중치, Perspective 조건, Mip footprint, encoded RGB, Checker/Wrap/Mirror와 오탈자 항목은 4.4의 Figure Review Note `<details>`로 이동했다. 수치 `0.35/0.03/0.62`, UV `(0.34, 0.62)`, Normal `(0.52, 0.47, 1.00)`를 유지했다.
- Normal sampler가 이미 Decode했을 때 `RGB × 2 - 1`을 다시 적용하지 않는 caveat와 `Needs Technical Verification`은 4.6 Implementation Note로 유지했다. 실제 sampler 검증을 완료했다고 표시하지 않았다.
- sRGB transfer의 구간별 전개를 Main Flow에 추가하지 않았다. `0.50→0.214`를 확인하는 해당 구간의 계산 예시는 접힌 Implementation Note에 배치했다.
- 4.7 마지막의 의미 없는 `Vz` 문자열은 제거했다. 기술적인 문장이 아닌 편집 잔여물이다.

### Formula Changes

- `Encoded = Normal × 0.5 + 0.5`는 유지했다. signed Direction을 unsigned RGB에 저장할 이유와 flat Direction을 먼저 설명한 뒤 제시했다.
- `Normal = RGB × 2 - 1`은 유지했다. 0/0.5/1이 -1/0/+1로 돌아가는 관계를 먼저 설명한 뒤 제시하고, raw RGB에 한정된 조건과 중복 Decode 방지 Note를 연결했다.
- Flat `(0,0,1)↔(0.5,0.5,1)`, raw `(1,0.5,0.5)→(1,0,0)` 예시를 유지했다. +T 경계 예시는 Height가 아닌 Direction이라는 의미를 명시했다.
- Bilinear Formula를 새로 전개하지 않았다. 원본의 네 주변 Texel/위치 가중치 관계를 가로 중간값→세로 중간값 직관으로 먼저 설명하고 기존 Figure의 기여값 구조를 해석하도록 했다.
- `((0.50 + 0.055)/1.055)^2.4≈0.214`를 근거 확인용 Note에 추가했다. 반대 방향 Encode `Linear 0.50→약 0.735`는 Decode와 섞지 않는 비교로만 명시했다. `0.50→0.73→Glossy`로 작성하지 않았다.
- TBN의 새 Matrix 증명이나 Component 전개를 추가하지 않았다. 기존 Basis/Transform/Normalize Flow의 이유를 설명했고 Chapter 02의 기준과 Chapter 03의 Normal Transform 조건을 연결했다.

### Structure Changes

4.1–4.8 Numbering은 동일하다. 원본의 모든 Topic Heading을 보존했으며, 4.4의 Texel을 Filtering 문제 앞에, 4.5의 Why sRGB Exists를 Color Space 정의 앞에 옮겼다. 4.6에 Storing a Direction in a Texture를 추가해 Geometry Detail/Direction 저장/Space/Decode/TBN을 나누었다.

Figure는 여덟 개 모두 정확한 기존 경로와 Fig4_01→Fig4_08 순서를 유지한다. 4.1/4.2의 Figure를 해당 개념 설명 뒤로 옮겼다. 4.4/4.5/4.6/4.7/4.8도 Section 내부에서 관련 Concept와 Formula/Flow 설명 뒤로 옮겼다. Figure Pixel은 편집하지 않았다.

### Figure Review

모든 Figure의 실제 Pixel을 열어 확인했다. 아래 Status는 Figure의 개념·표기 확인과 Engine 동작 검증을 구분한다. 렌더 Sphere를 실제 통제된 Engine Experiment의 측정값으로 취급하지 않았다.

| Figure / Exact Existing Path | Status | Rewrite Action | Reason |
|---|---|---|---|
| Fig4_01 — `Figures/Chapter04/Fig4_01.png` | Verified | Keep / 설명 뒤 배치 / Caption 보강 | Geometry/Light/Material 합류와 Material Variation의 개념이 일치한다. Roughness 요철은 Normal 등 별도 Input의 영향, Emissive의 Bloom/주변 조명은 별도 경로라는 이미지 설명을 본문에서 구분한다. |
| Fig4_02 — `Figures/Chapter04/Fig4_02.png` | Verified | Keep / Property 설명 뒤 배치 | Base Color의 Dielectric Diffuse/Metal Specular, Roughness 분포, Shading Normal과 Emission 설명이 보완된 상태다. Emissive 수치 예시는 정량 Glow 검증이 아니다. |
| Fig4_03 — `Figures/Chapter04/Fig4_03.png` | Verified | Keep / Sample 의미 Caption 보강 | Linear Base Color와 raw RGB Normal→Decode, Sampler가 이미 Decode한 경우의 중복 방지, Packing 규칙이 그림에 구분되어 있다. 숫자는 설명 예시라는 Figure Note를 유지했다. |
| Fig4_04 — `Figures/Chapter04/Fig4_04.png` | Figure Revision Required | Keep / Review Note 유지 / Sampling·Filtering 뒤 배치 | 원본에서 이미 발견한 UV 표시점/affine 가중치, 거리만 강조한 Mip, encoded Normal, 대칭 Checker/Wrap/Mirror, 중복 “값을” 문제를 보존·기록했다. 실제 Perspective UV는 Engine Verification도 필요하다. |
| Fig4_05 — `Figures/Chapter04/Fig4_05.png` | Figure Revision Required | Keep Updated Roughness Context / Other Parts Review | 5/6번 `0.50→약 0.21→더 Glossy` 수정 방향은 실제 Pixel에서 확인했다. 그러나 1번 같은 Stored RGB 비교의 밝기, 2번 Encode-like Curve/Decode 설명, 4번 No Conversion 범위, 7번 Texture Sample sRGB Checkbox/수동 변환 암시가 남아 있다. |
| Fig4_06 — `Figures/Chapter04/Fig4_06.png` | Engine Verification Required | Keep / 설명 뒤 배치 / raw RGB 조건 Caption | raw RGB Decode와 Normalize, Tangent Basis와 TBN, 이미 Decode한 Sampler의 중복 방지가 그림에 구분된다. `(0.52,0.47,1)`은 Encoded RGB다. 실제 Compression/Normal sampler/TBN 준비 결과는 Engine에서 확인해야 한다. |
| Fig4_07 — `Figures/Chapter04/Fig4_07.png` | Verified | Keep Updated Context / Scope 설명 뒤 배치 | 실제 이미지가 Non-Static/Static, Editor/Runtime MID, Compile Time Variant와 Parent Logic 재사용의 한계를 구분한다. MIC/MID의 실제 실행과 Compile 결과 검증은 별도 Remaining Item이다. |
| Fig4_08 — `Figures/Chapter04/Fig4_08.png` | Verified | Keep / 합류 설명 뒤 배치 / N Caption 보강 | Texture와 UV 별도 입력, Normal raw/decoded 분기, N/L/V 및 Material의 병렬 Source, Contribution 합류가 수정된 구조다. N은 Lighting에 쓰는 Shading Normal이라는 문맥을 유지한다. |

기술적으로 잘못된 Figure에 맞추어 본문의 설명을 바꾸지 않았다. 다음 항목은 요청한 Figure Issue Format으로 별도 추적한다.

| Figure | Problem | Why It Is Incorrect | Suggested Correction | Verification Needed |
|---|---|---|---|---|
| Fig4_04 / panel 3 | affine Vertex UV 예시의 표시점과 `(0.34,0.62)`가 불일치 | 해당 Vertex 좌표를 affine 보간하면 weights는 아래 왼쪽 `0.35`, 아래 오른쪽 `0.03`, 위 `0.62`다. 현재 중앙 표시점과 일치하지 않는다. | affine 도식 조건을 명시해 점/가중치를 일치시키거나 실제 Perspective 조건을 포함한 예시로 교체한다. | 그림 좌표의 직접 확인, 대상 Engine의 Perspective-correct UV. |
| Fig4_04 / panels 7–9 | Mip 거리 설명만 강조, Normal Vector/Encoded Data 혼동 가능, Wrap/Mirror 대칭 패턴 | Mip는 footprint, RGB 예시는 아직 Unit Direction이 아니며 대칭 Checker는 두 Address Mode를 분별하기 어렵다. | footprint Label, Encoded RGB Label을 명확히 하고 비대칭 패턴으로 Addressing 비교. | Resolution/UV Scale/Surface 기울기를 통제한 Mip 비교와 Addressing 결과. |
| Fig4_04 / introduction | “값을 값을” 중복 | 표기 오류다. | 중복된 단어 제거. | 이미지 텍스트 교정 Review. |
| Fig4_05 / panel 1 | 같은 Stored RGB `0.5`에서 sRGB 해석 Sphere가 더 밝게 표시 | sRGB Decode의 Linear 값 `0.214`는 Linear Data `0.5`보다 낮다. 동일 조건의 Light-linear 입력 비교라면 현재 밝기 관계가 반대다. | 저장값/계산값/Display Encoding과 통제 조건을 명시하고 같은 기준의 비교를 재작성한다. | 동일 Material/Light/View/Exposure 조건의 Engine 비교. |
| Fig4_05 / panel 2 | 위로 볼록한 Curve와 sRGB→Linear Decode 설명이 같은 문맥에 배치 | Curve는 Linear→sRGB Encode 형태에 가깝다. 단일 Gamma 2.2만으로 정확한 sRGB transfer를 표현할 수도 없다. | Encode와 Decode 방향을 명시한 Axis/Curve Label로 수정한다. | 표준 transfer relationship 확인과 해당 Curve 좌표 검토. |
| Fig4_05 / panel 4 | sRGB Off가 No Conversion으로 표시 | sRGB transfer Decode만 생략하며 다른 Format/Filtering/Compression/Normal reconstruction은 남을 수 있다. | No sRGB Decode로 Label 범위를 제한한다. | 실제 Texture Format/Sampler 경로. |
| Fig4_05 / panel 7 | Texture Sample 안에 sRGB Checkbox와 변환 Node를 그림 | sRGB는 Texture의 저장 Encoding 설정과 연결되며, 이미 자동 Decode한 Color를 다시 Decode하면 잘못된 값이다. 합성 UI는 실제 Node 보증이 아니다. | Texture Asset 설정과 Sampler Type을 정확한 Engine UI로 분리하고 수동 Decode가 필요한 조건을 명시한다. | 대상 Engine Version의 실제 Texture Asset/Material Editor. |

### Technical Notes

| Item | Backup / Figure Finding | Rewritten Treatment / Evidence |
|---|---|---|
| Material vs Shader | Material이 Data/설정만 제공하는 정의가 Graph Logic의 역할을 충분히 설명하지 않음 | Graph가 입력 준비 Logic을 표현하고 필요한 Shader로 Compile될 수 있다는 구분을 추가했다. GPU Program의 역할은 유지했다. |
| Material brightness scope | 4.1의 Material 자체가 최종 밝기를 직접 결정하지 않는다는 말이 넓게 읽힐 수 있음 | Light에 반응하는 Material의 범위로 제한하고 Unlit/Emission 예외는 기존 4.8 정보와 연결했다. |
| Base Color sample numbers | 원본 `(0.42,0.28,0.24)`가 저장 RGB인지 계산 Color인지 쉽게 혼동 | 입력 해석 후 Linear Color 예시라고 명시했다. 수치는 보존하고 임의로 Raw sRGB 수치라고 확정하지 않았다. |
| Pixel vs Texel | Texture의 Pixel이라는 표현이 Screen Pixel과 섞임 | Texel을 소개하고 4.4에서 Screen Pixel과 저장 단위의 관계를 설명했다. |
| Channel Packing cost | Memory/Sample Cost 감소 가능성을 형식 조건 없이 일반화할 가능성 | 한 Sample로 여러 값을 읽는 조건, 실제 Format/구성, 측정과 Bottleneck 조건을 분리했다. 원본 Cache/Resolution/Filtering/Platform과 Chapter 09 연결을 유지했다. |
| sRGB Roughness direction | 본문은 더 매끄럽거나 더 거칠게 보일 수 있다고만 설명; Figure 중간은 0.50→0.21로 이미 수정 | 본문도 저장 0.50→Decode 약 0.214→Roughness 감소→Glossy tendency로 명시했다. [Khronos sRGB conversion specification](https://github.com/KhronosGroup/OpenGL-Registry/blob/main/extensions/ARB/ARB_framebuffer_sRGB.txt) 관계로 수치를 확인했다. |
| sRGB Curve/UI | Fig4_05의 다른 Panel은 수정된 Roughness 예시와 모순 또는 과도한 단순화가 남음 | Pixel을 보존하면서 Figure Review Note에 문제를 명시했다. [Epic Working Color Space documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/working-color-space-in-unreal-engine)은 Working Color Space와 Texture sRGB 저장 Encoding을 구분한다. |
| Normal Channel encoding | 원본에서 `R=x`, `G=y`, `B=z`를 Encoding 조건보다 먼저 제시 | RGB에는 signed 성분 자체가 아니라 Encoding한 성분이 저장된다고 정리하고 raw Encode/Decode Model을 유지했다. |
| Normal basis / geometry | Tangent Space의 Local이라는 표현이 Mesh Object Local Space와 혼동 가능 | Surface 위치마다의 Basis임을 명시했다. Geometric Normal과 Shading Normal, Height와 Direction, Silhouette/Depth/Collision/실제 Shadow Geometry를 유지했다. |
| Engine Normal sampler | `RGB×2−1` 적용 범위에 이미 원본 caveat가 있음 | raw RGB에만 적용하고 sampler-decoded 방향은 중복 Decode하지 않는 조건과 Needs Technical Verification을 보존했다. Compression·Format 경로를 임의로 확정하지 않았다. |
| MIC vs MID / Static | 원본의 Editor/Runtime 구분과 Static Variant 조건은 이미 개선되어 있음 | 해당 방향을 유지하면서 MIC와 MID를 명시했다. [Epic Instanced Materials documentation](https://dev.epicgames.com/documentation/unreal-engine/instanced-materials-in-unreal-engine)에서 Instance 유형과 Static Compile 범위를 확인했다. |
| Architecture vs Compiled Variant | 원본은 Static 조합별 Variant를 이미 구분 | 4.1의 Shader 공유 문장도 Architecture 공유로 표현해 4.7과 모순되지 않게 했다. 4.8에서도 재사용 Interface/지원되는 Non-Static Runtime/Static Variant 조건을 유지했다. |
| Chapter 08/09 | Generated MatCap UV, Unlit+Emissive 합성, Sampling/Permutation Cost 연결이 존재 | 모두 해당 Concept와 연결해 보존했다. 완성된 교육용 Lighting을 Lit Property pin에 넣는 것으로 해석하지 않는 주의도 유지했다. |
| Light / Camera scope | 4.8의 L/V 준비 Flow가 일반적인 Source를 설명하므로 모든 Direction을 Position 차이로 만든다는 해석 가능 | Directional/Point/Spot과 Perspective/Orthographic 조건은 Chapter 03의 구분을 따르고, 모든 L/V에 Position 차이를 적용하지 않는다고 명시했다. 새로운 Formula를 추가하지 않았다. |

### Remaining Review Items

1. Fig4_04와 Fig4_05의 위 Figure Issue Table은 이미지 수정이 필요하다. 이번 Rewrite에서는 기존 Figure Pixel/Path를 보존하고 잘못된 관계에 맞춰 본문을 바꾸지 않았다.
2. 대상 Unreal Engine Version이 지정된 검증 환경에서 Normal sampler의 raw/decoded 출력, Texture Format/Compression, TBN의 handedness와 목표 Space/Unit Normal을 확인해야 한다. Figure 4-6과 원본의 Needs Technical Verification을 완료로 표시하지 않았다.
3. Texture Asset의 sRGB 설정, Sampler Type, 자동 Decode와 Filtering 경로 및 Working Color Space의 UI 위치를 대상 Engine에서 확인해야 한다. 자동 Decode한 Color/Direction에 수동 Decode를 중복 적용하지 않는지 확인한다.
4. Fig4_05의 Roughness 0.50/약 0.214 비교는 계산 관계를 확인한 것이며 실제 Engine Screenshot을 재생성한 검증이 아니다. Material/Light/View/Exposure 조건을 고정해 Appearance tendency를 확인해야 한다.
5. Editor MIC Override, MID 생성과 실제 대상 적용, 지원되는 Scalar/Vector/Texture Runtime 변경, Static 조합별 Compile 결과를 확인해야 한다. Fig4_07의 설명 범위는 Pixel Review로 Verified이며 Engine 실행은 별도 확인 사항이다.
6. Packing의 실제 Memory/Sampling 이득과 Static Permutation 부담은 Project의 Texture Format/사용 구성/Platform에서 측정해야 한다. 문서 Rewrite만으로 Performance를 검증했다고 표시하지 않는다.
7. 한국어 문장과 GitHub Markdown/접힌 Note의 가독성은 사용자 또는 문서 담당자가 최종 Review할 수 있다. 기술 Scope 보존, Heading/이미지 경로/순서, 수식과 기존 caveat에 대한 구조 검사는 완료했다.

### Chapter 04 Formula Audit Table Entries

| Chapter | Formula / Concept | Backup Treatment | Rewritten Treatment | Decision |
|---|---|---|---|---|
| 04 | Vertex UV → Interpolated UV → Sampling | Vertex Attribute 보간 Flow를 짧게 제시, Figure의 UV 점 caveat가 Main Flow 앞에 있음 | 3D→2D 주소 문제와 Vertex/Fragment 연결을 설명한 뒤 Flow, affine/Perspective caveat는 Figure Note | Explain First / Move Caveat |
| 04 | Bilinear neighbor contribution | 네 Texel과 위치 가중치 설명, Figure에 Formula | Texel Center 사이 Sampling 문제→가로/세로 중간값→네 기여 관계, 새 Formula 전개 없음 | Explain First / Keep |
| 04 | sRGB Decode `0.50→≈0.214` | 본문은 결과 방향이 모호, Figure 중간은 약 0.21로 수정됨 | Perception/Storage/Decode/Linear/Data 구분 뒤 정확한 수치와 Glossy tendency; 해당 transfer 구간 계산은 Note | Explain First / Move Numeric Detail |
| 04 | `Encoded = Normal × 0.5 + 0.5` | flat Normal 뒤 Encoding 식 | signed Direction/unsigned 저장 범위 이유와 기준 Space 설명 뒤 식과 flat 예시 | Keep / Explain First |
| 04 | `Normal = RGB × 2 - 1` | signed 범위 복원 설명 뒤 식, inline Engine caveat | 범위 역변환의 직관→식→예시; raw 조건/sampler output/중복 Decode는 Implementation Note | Keep / Explain First / Move Caveat |
| 04 | TBN Transform / Normalize | target Space/Basis 조건과 Normal Flow | 같은 Space가 필요한 이유→목표 Space의 T/B/N 기여→Transform→Normalize; 수학 증명 추가 없음 | Keep / Explain First |

### Chapter 04 Comparison Summary Contributions

**Before.** Backup은 이미 Property 종류, Color/Data, raw Normal caveat, Static/Runtime 구분과 병렬 Data Flow를 상세히 포함한다. 그러나 UV/Color Space/Normal의 Definition·용어·처리 단계가 빠르게 모이고, Figure 4-4의 수치 예외가 Main Flow 앞에 놓이며, Figure 4-5의 수정된 Roughness 방향이 본문에서 구체적인 숫자로 연결되지 않는다.

**After.** 같은 기술 Scope를 유지하며 위치별 Property 문제부터 Data Source와 Sample 결과까지 연결했다. Human Perception과 저장/Decode 방향을 분리하고, Normal의 Direction 저장/기준 Space/복원/Lighting Space를 단계적으로 설명했다. 기존 Verification/Caveat를 삭제하지 않고 필요한 지점의 Note로 옮겼다. MIC/MID와 Static Variant의 범위도 같은 Interface 구조에서 구분했다.

**Expected Reader Experience.** 독자는 새 용어를 만날 때 그 Data가 필요한 이유와 Source를 먼저 이해하고, 이미 설명한 관계를 Formula와 Figure에서 확인한다. Graph를 읽을 때 각 연결선이 Color/Scalar/raw RGB/Direction 중 무엇인지, 어느 Space인지, 현재 Surface 위치의 값인지 추적할 수 있다. Chapter 05로 넘어갈 때 Reflection 모델이 사용할 입력이 이미 준비된 상태임을 이해할 수 있다.

---

# Formula Audit Table

아래 표는 독자의 체감 난이도에 영향을 주는 주요 Formula와 변환 관계를 모은 것이다. `Keep`는 기존의 Concept-first 설명과 Formula를 유지한 경우, `Explain First`는 Formula를 유지하면서 앞의 문제와 관계 설명을 보강하거나 Figure 배치를 조정한 경우, `Move`는 정보가 필요한 Note로 이동한 경우를 뜻한다.

| Chapter | Formula / Concept | Backup Treatment | Rewritten Treatment | Decision |
|---|---|---|---|---|
| 01 | Local → World → View → Clip → Screen | Space 흐름은 있으나 Clip 이후 Projection 표현이 모호함 | Projection은 View → Clip에 적용되며 이후 Divide / Viewport가 이어짐을 설명 | Explain First |
| 01 | Barycentric Weights `0.2 / 0.3 / 0.5` | Weight 의미와 수치 예시가 빠르게 연결됨 | 전체 기여의 비율을 먼저 설명하고 같은 수치 및 Perspective 조건 유지 | Explain First |
| 01 | Depth `0.2 < 0.4` | 숫자 예시 뒤 비교 설정의 차이를 설명 | LESS / 작은 Depth가 가까움 / Write On이라는 예제 조건을 먼저 설명 | Explain First |
| 02 | Position Difference | Position과 Direction의 구분 및 숫자 예시 | 출발 위치를 기준으로 목적지의 상대 차이를 얻는 이유를 보강 | Explain First |
| 02 | Position `w = 1` / Direction `w = 0` | Affine Transform과 Homogeneous 설명 | 이동되어야 할 값과 방향만 옮길 값을 구분하는 문제에서 시작 | Explain First |
| 02 | Matrix Transform / TRS | Matrix의 역할과 기존 예제를 설명 | 여러 Space에서 입력의 의미를 일관되게 옮기는 도구로 연결; 기존 예제 보존 | Explain First |
| 02 | View Transform as Camera Inverse | Camera 기준 표현을 역변환과 연결 | Camera 배치를 되돌리는 이유를 먼저 설명하고 Rigid Inverse의 조건은 Implementation Note로 이동 | Explain First / Move |
| 02 | `p_clip = P × V × M × p_local` | 곱 순서와 Convention 주의가 함께 제시됨 | Object / Camera / Projection의 책임과 각 입출력 Space를 먼저 연결한 뒤 기존 Matrix Chain 유지 | Explain First |
| 02 | Viewport Scale + Offset | NDC 범위 설명 뒤 Pixel 수치 예 | 현재 Viewport의 크기와 시작 위치를 반영하는 이유를 먼저 설명하고 동일 수치 예제 유지 | Explain First |
| 02 | Clip inequalities / NDC Divide | Homogeneous Clip 범위와 Divide, API 조건 | Clip과 고정 NDC Cube를 구분하고 기존 Figure의 실제 표현과 Caption을 대조 | Explain First |
| 02 | TBN / Tangent → Lighting Space | Basis, Normal Map과 Space 변환 설명 | Texture의 Direction이 어떤 기준에 있는지 먼저 묻고 T / B / N의 역할로 연결 | Explain First |
| 03 | `normalize(Vector)` | 길이가 같은 방향 비교를 방해하는 이유를 설명 | 이 흐름을 유지하고 방향 비교의 문제 Context를 먼저 보강 | Keep |
| 03 | `dot(N, L)` / `dot(N, L) = cosθ` | 원하는 관계 → Dot Product → Cosine | 같은 Space의 Unit Vector 조건과 기존 순서 유지; Figure는 설명 뒤로 이동 | Keep |
| 03 | `max(NdotL, 0)` / `saturate(NdotL)` | Signed/Clamped와 연산 범위 차이 설명 | One-sided Opaque 앞면의 기본 Diffuse 적용 범위를 명시; 원래 차이 유지 | Keep |
| 03 | Face Normal / Cross Product | 두 Edge → 수직 방향 → Normalize | Formula 유지; 퇴화 Geometry 조건은 별도 Note로 이동; Component 전개 없음 | Keep |
| 03 | `normalize(InterpolatedNormal)` | 보간 후 길이 조건을 설명 | 성분 상쇄의 직관 뒤 기존 Formula 유지 | Explain First |
| 03 | `dot(T, N) = 0` / Scale 예제 | Geometric 수직 관계를 2D 수치로 확인 | 올바른 방향과 Unit Length를 구분하는 기존 예제를 그대로 유지 | Keep |
| 03 | `transpose(inverse(M))` / `Nworld` | Non-Uniform Scale → 수직 관계 → 역방향 보정 → 일반 Transform | 설명 순서와 Formula 유지; 복잡한 Matrix 증명은 추가하지 않음 | Keep |
| 03 | Light / View Position Difference | 출발점 → 목적지 → 차이 → Normalize | Direction Convention, Light Type, Camera Projection별 입력 경로 유지 | Keep |
| 04 | Bilinear Filtering | Texel / Filtering 설명 | Texel Center 사이의 Sample 문제를 먼저 설명하고 주변 값을 섞는 관계로 연결 | Explain First |
| 04 | sRGB Decode `0.50 → 약 0.214` | 기존 Figure에는 수정된 `0.50 → 0.21` 관계가 있으나 본문은 Roughness 변화 방향이 모호함 | Figure의 올바른 Decode 방향을 유지하고 본문에 수치와 Glossy 방향을 명시; Storage / 계산 / Data Texture의 해석 차이로 연결 | Keep Figure / Explain First in Text |
| 04 | sRGB Numeric Verification | Color Space와 입력 해석 조건을 설명하며 구체적인 Decode 계산식은 없음 | 의미와 결과를 설명한 뒤 한 구간의 수치 확인식만 Implementation Note에 추가; 전체 transfer 전개 없음 | Explain First |
| 04 | Normal RGB Encoding / Decode | 채널과 Tangent Space, Decode 설명 | Direction 저장의 필요성 → 저장 범위 문제 → 기준 Space와 Tangent Basis → Encoding → Decode를 단계적으로 설명 | Explain First |
| 04 | TBN Normal Transformation | Tangent Normal을 Lighting Space로 변환 | Decode와 Space Conversion을 구분하고, Normal Sample 경로의 중복 Decode 주의를 보존 | Explain First |

---

# Figure Audit Table

Figure 파일명, 경로와 번호는 Backup과 동일하다. 아래 표의 상태는 각 Chapter의 상세 Figure Review와 Remaining Review Items를 요약한다. 새 Figure를 만들거나 기존 PNG를 수정하지 않았다.

| Figure | Status | Rewrite Action | Reason |
|---|---|---|---|
| `Figures/Chapter01/Fig1_01.png` | Verified | Keep | Geometry / Material / Light / Camera → 2D Pixel Image; Light 사용 여부 Caveat 확인 |
| `Figures/Chapter01/Fig1_02.png` | Verified | Keep | 논리적 단계 개요이며 Early Depth / 실제 실행 순서와 기록 조건 차이를 Figure 하단에서 명시 |
| `Figures/Chapter01/Fig1_03.png` | Verified | Keep | Position과 Attribute 묶음, 같은 Position의 UV / Hard Edge 분리 사례 일치 |
| `Figures/Chapter01/Fig1_04.png` | Verified | Keep | Clip Position과 후속 Attribute, Vertex 처리와 Pixel 처리의 차이를 일치하게 표현 |
| `Figures/Chapter01/Fig1_05.png` | Verified | Keep | `[0,1,2]` / `[0,2,3]` 공유 관계와 예시 CCW Front 설정 일치; Indexed Draw 예시 범위 유지 |
| `Figures/Chapter01/Fig1_06.png` | Verified | Keep | Object Bounds Frustum 선별, 투영 Winding 판정, 경계 교점과 남는 사각형 구분; 다른 Pass Caveat 확인 |
| `Figures/Chapter01/Fig1_07.png` | Verified | Keep | Coverage와 Fragment 후보, Fragment≠Final Pixel 관계 일치; 단순한 grid / sample 교육용 그림으로 읽음 |
| `Figures/Chapter01/Fig1_08.png` | Verified | Keep | Barycentric, 예시 UV, Vertex Color 전달, Perspective 조건을 본문 참조로 명시 |
| `Figures/Chapter01/Fig1_09.png` | Verified | Keep | Input과 계산 예시는 실행 순서가 아님을 명시; 출력이 최종 화면 확정값이 아님을 표현 |
| `Figures/Chapter01/Fig1_10.png` | Verified | Keep Updated Context | Opaque / LESS / Depth Write On, 저장값과 새 값 비교, Camera vs Light, Reversed-Z Caveat 확인; 같은 조건을 본문 수치 예시보다 먼저 설명 |
| `Figures/Chapter01/Fig1_11.png` | Verified | Keep Updated Context | 기본 Raster Depth와 선택적 Override, Test / Write 조건, 별도 Buffer, 독립 Scene 삽화, Post Process → Display Target → Present 확인 |
| `Figures/Chapter01/Fig1_12.png` | Review Required | Keep / Review | Send to GPU와 Data 목록이 업로드 전체로 오해될 가능성; 본문에서 자원 참조 범위를 명시. Character 자료 출처와 실행 설정은 추가 확인 필요 |
| `Figures/Chapter01/Fig1_13.png` | Figure Revision Required | Keep / Review | Frustum Culling의 고정 GPU 배치, Framebuffer(Render Target) 동의어처럼 보이는 표기, 작은 불명확 Label 문제가 남아 있음; 본문과 상세 Note로 명시 |
| Fig2_01 — `Figures/Chapter02/Fig2_01.png` | Verified | Keep; move after Coordinates Relative to the Camera | Identity Rotation, Scale1, Local(1,0,0)+T(5,2,0)=(6,2,0), Camera(4,1,5) subtraction=(2,1,−5), Forward−Z를 직접 확인했다. 계산 전에 조건을 설명한다. |
| Fig2_02 — `Figures/Chapter02/Fig2_02.png` | Verified | Keep; move after Vector Between Two Positions | Position/같은 Direction 화살표/A→B=(3,2,2)의 의미가 본문과 일치한다. |
| Fig2_03 — `Figures/Chapter02/Fig2_03.png` | Verified | Keep; move after Object Mode and Edit Mode | Translation-only (1,1,1)+(5,2,1)=(6,3,2), Object/Edit Mode와 Mesh/Transform 분리가 일치한다. |
| Fig2_04 — `Figures/Chapter02/Fig2_04.png` | Verified | Keep; move after Same Local Position, Different World Position | 공통 World의 Object Origin 위치와 Translation-only (1,1,1)+(5,2,0)=(6,3,1)이 일치한다. |
| Fig2_05 — `Figures/Chapter02/Fig2_05.png` | Verified | Keep introductory position; add reading context | Camera 기준 3D와 World 공통 기준의 차이를 확인했다. Forward/Depth 부호는 Figure의 예시이며 Convention caveat도 유지한다. |
| Fig2_06 — `Figures/Chapter02/Fig2_06.png` | Verified | Keep introductory position; add comparison assumptions | 동일 크기 Object의 원근 크기 비교와 View→Clip→Divide→NDC→Viewport→Screen 연결을 확인했다. 가림을 제외한 독립 크기 비교 범위다. |
| Fig2_07 — `Figures/Chapter02/Fig2_07.png` | Verified | Keep updated context; move after Clip/NDC concepts | 실제 PNG는 이미 고정 Clip Cube를 사용하지 않는다. −w≤x/y≤w,0≤z≤w와 NDC Z0~1, (2,1,3,4)÷4=(.5,.25,.75), continuous screen boundary/index 구분이 맞다. stale Backup 설명만 정정했다. |
| Fig2_08 — `Figures/Chapter02/Fig2_08.png` | Verified | Keep; move after Homogeneous Coordinate and Matrix | 입력 w=1/0과 Projection 출력 역할이 분리됐다. Near/Far Clip÷w 값이 맞고 같은 XY/다른 양의w 조건이다. Near/Far Plane을 의미하지 않는다는 Context를 추가했다. |
| Fig2_09 — `Figures/Chapter02/Fig2_09.png` | Verified | Keep updated context; move after XY numerical explanation | +Z Forward, x_clip=x_view, w_clip=z_view 단순화와 2/2=1,2/10=.2, same ray caveat를 실제 PNG에서 확인했다. Z 생략 범위를 명시했다. |
| Fig2_10 — `Figures/Chapter02/Fig2_10.png` | Verified | Keep; move after Y mapping example | 1920×1080에서 NDC(.5,.5)→(1440,270), Top-left/Down Y와 viewport/전체 screen 구분이 맞다. |
| Fig2_11 — `Figures/Chapter02/Fig2_11.png` | Review Required | Keep; move after Matrix Multiplication Concept; scope caption | 4×4 Column Vector와 Model/View/Projection 흐름은 맞다. 제목 아래 Matrix=다른 Space 변환 문장은 모든 Matrix의 정의로 읽으면 범위가 좁다. 아래 Problem Table의 문구 검토 필요. |
| Fig2_12 — `Figures/Chapter02/Fig2_12.png` | Verified | Keep; move after One Vertex, Multiple Coordinates | Model T(4,3,2), Local(1,0,0)→World(5,3,2), Camera(3,2,10)→View(2,1,−8), Column PVM 순서가 맞다. P 값은 설정에 따라 달라진다. |
| Fig2_13 — `Figures/Chapter02/Fig2_13.png` | Review Required | Keep; move after Normal Matrix; clarify Normal context | Position/Direction Translation 및 M=T·R·S 조건은 맞다. Surface에 수직인 Normal Label은 Geometric Normal의 예로 읽어야 하며 Shading Normal 전체의 정의로 확대하지 않도록 문구 검토를 기록한다. |
| Fig2_14 — `Figures/Chapter02/Fig2_14.png` | Review Required | Keep updated context; move after TBN Matrix and Decode explanation | Orthonormal/TBN Column convention, raw Decode vs sampler Decode 구분과 flat RGB=(.5,.5,1), Normal=(0,0,1)은 맞다. N=Surface 수직 Label은 Smooth Shading Basis와 Face Normal 구분을 더 표시할 수 있다. |
| Fig2_15 — `Figures/Chapter02/Fig2_15.png` | Engine Verification Required | Keep updated context; move after Same-Space and Node explanation | Space 목록이 실행 순서가 아니라는 표시, Camera 방향, Object Position caveat, Pixel Normal 조건, Unit N/V가 맞다. Node 출력·Material Domain·Transform 지원 및 실제 graph compile은 대상 Engine에서 확인해야 한다. |
| Fig2_16 — `Figures/Chapter02/Fig2_16.png` | Verified | Keep closing summary | Position Flow와 Direction의 필요한 Space까지만 변환하는 경로가 분리돼 있다. Column 입력, clipping→divide, top-left screen formula, basis/decode 흐름이 본문과 일치한다. viewport origin(0,0) 예의 scope를 유지했다. |
| `Figures/Chapter03/Fig3_01.png` | Verified | Keep / Move After Explanation | A/B와 약 `(0.894, 0.447, 0)` 결과가 본문과 일치한다. |
| `Figures/Chapter03/Fig3_02.png` | Figure Revision Required | Keep / Add Caption / Move | Unit Vector의 Signed/Clamped 값은 맞지만 Footer가 `3.2 Dot Product`로 이전 번호를 사용한다. |
| `Figures/Chapter03/Fig3_03.png` | Verified | Keep / Add Caption / Move | Face/Vertex Normal, Smooth/Flat Shading과 Silhouette 유지 관계가 본문과 일치한다. |
| `Figures/Chapter03/Fig3_04.png` | Verified | Keep / Add Caption / Move | 잘못된 `(-2,1)`과 보정한 방향의 수직 관계, Inverse Transpose, Normalize 구분이 맞다. |
| `Figures/Chapter03/Fig3_05.png` | Figure Revision Required | Keep / Add Scope Caption / Move | L의 방향 규약은 맞지만 Camera Position 차이의 V가 Perspective Camera 전용임을 이미지 안에서 구분하지 않는다. |
| `Figures/Chapter03/Fig3_06.png` | Figure Revision Required | Keep / Add Scope Caption / Move | 같은 물리 방향의 World/View 성분 비교는 맞지만 입력 표의 Position 차이 경로에 Point Light/Perspective Camera 적용 범위가 생략되어 있다. |
| Fig4_01 — `Figures/Chapter04/Fig4_01.png` | Verified | Keep / 설명 뒤 배치 / Caption 보강 | Geometry/Light/Material 합류와 Material Variation의 개념이 일치한다. Roughness 요철은 Normal 등 별도 Input의 영향, Emissive의 Bloom/주변 조명은 별도 경로라는 이미지 설명을 본문에서 구분한다. |
| Fig4_02 — `Figures/Chapter04/Fig4_02.png` | Verified | Keep / Property 설명 뒤 배치 | Base Color의 Dielectric Diffuse/Metal Specular, Roughness 분포, Shading Normal과 Emission 설명이 보완된 상태다. Emissive 수치 예시는 정량 Glow 검증이 아니다. |
| Fig4_03 — `Figures/Chapter04/Fig4_03.png` | Verified | Keep / Sample 의미 Caption 보강 | Linear Base Color와 raw RGB Normal→Decode, Sampler가 이미 Decode한 경우의 중복 방지, Packing 규칙이 그림에 구분되어 있다. 숫자는 설명 예시라는 Figure Note를 유지했다. |
| Fig4_04 — `Figures/Chapter04/Fig4_04.png` | Figure Revision Required | Keep / Review Note 유지 / Sampling·Filtering 뒤 배치 | 원본에서 이미 발견한 UV 표시점/affine 가중치, 거리만 강조한 Mip, encoded Normal, 대칭 Checker/Wrap/Mirror, 중복 “값을” 문제를 보존·기록했다. 실제 Perspective UV는 Engine Verification도 필요하다. |
| Fig4_05 — `Figures/Chapter04/Fig4_05.png` | Figure Revision Required | Keep Updated Roughness Context / Other Parts Review | 5/6번 `0.50→약 0.21→더 Glossy` 수정 방향은 실제 Pixel에서 확인했다. 그러나 1번 같은 Stored RGB 비교의 밝기, 2번 Encode-like Curve/Decode 설명, 4번 No Conversion 범위, 7번 Texture Sample sRGB Checkbox/수동 변환 암시가 남아 있다. |
| Fig4_06 — `Figures/Chapter04/Fig4_06.png` | Engine Verification Required | Keep / 설명 뒤 배치 / raw RGB 조건 Caption | raw RGB Decode와 Normalize, Tangent Basis와 TBN, 이미 Decode한 Sampler의 중복 방지가 그림에 구분된다. `(0.52,0.47,1)`은 Encoded RGB다. 실제 Compression/Normal sampler/TBN 준비 결과는 Engine에서 확인해야 한다. |
| Fig4_07 — `Figures/Chapter04/Fig4_07.png` | Verified | Keep Updated Context / Scope 설명 뒤 배치 | 실제 이미지가 Non-Static/Static, Editor/Runtime MID, Compile Time Variant와 Parent Logic 재사용의 한계를 구분한다. MIC/MID의 실제 실행과 Compile 결과 검증은 별도 Remaining Item이다. |
| Fig4_08 — `Figures/Chapter04/Fig4_08.png` | Verified | Keep / 합류 설명 뒤 배치 / N Caption 보강 | Texture와 UV 별도 입력, Normal raw/decoded 분기, N/L/V 및 Material의 병렬 Source, Contribution 합류가 수정된 구조다. N은 Lighting에 쓰는 Shading Normal이라는 문맥을 유지한다. |

---

# Comparison Summary

## Before

`_backup` 기준 문서에는 충분한 기술 범위와 많은 직관적 예제가 있었다. 특히 Chapter 03은 이미 Concept-first로 개선되어 있었다. 다만 여러 입력과 변환이 만나는 부분에서 신규 용어가 겹치거나, Figure의 Formula가 본문보다 먼저 보이거나, 구현 주의가 중심 설명에 붙어 있는 경우가 있었다. 일부 기존 Figure와 Caption 사이에도 적용 범위 또는 표현 불일치가 남아 있었다.

## After

현재 Chapter 01–04는 기존 번호와 Scope를 유지하면서 필요성, 입력의 출처, 변환의 목적, 다음 계산에서의 사용을 더 명시적으로 연결한다. 좋은 기존 설명은 유지하고, 어려운 지점에 필요한 중간 단계만 보강했다. Formula는 기존 관계를 표현하는 도구로 남겼고, Verification / Debugging / Production 조건은 Note 또는 기존 본문에 보존했다.

Material에서는 Data를 얻는 Sampling, Color Data의 Decode, Normal Direction의 Decode와 Space Conversion, Parameter의 변경 경로를 각각 구분했다. 최근 수정한 Roughness Decode 방향과 Runtime / Static Parameter 범위를 되돌리지 않았다.

## Expected Reader Experience

Chapter 01에서 Data가 어디에 있으며 다음에 어디로 가는지 추적한다. Chapter 02에서는 같은 입력에 여러 Space가 필요한 이유를 이해한 뒤 Transform을 읽는다. Chapter 03에서는 방향 비교의 조건과 연산의 역할을 연결하고, Chapter 04에서는 Texture / Parameter가 제공하는 Material Data가 그 입력에 합류하는 흐름을 따라간다. Chapter 05에서 반사 응답을 만날 때 새로운 Concept 자체의 난이도는 높아져도 설명의 안내 방식은 이어지도록 했다.

이는 작성 및 문서 Review 기준의 기대 효과다. 처음 읽는 독자를 대상으로 한 실제 독해 테스트와 Engine 재현 검증은 아직 수행하지 않았다.

## Final Self-Review

| Check | Result | Evidence / Limit |
|---|---|---|
| Chapter 05 teaching style from Chapter 01 | Reviewed | 문제 Context와 필요한 입력에서 Concept를 소개하고 주요 전환에 Takeaways를 사용했다. |
| Why before definitions and formulas | Reviewed | 난이도 상승 구간의 도입을 보강하고 Formula가 포함된 Figure의 위치를 재검토했다. |
| Missing intermediate steps | Reviewed | Stage 입력/출력, Space 변환 이유, UV 보간/샘플링, Decode/TBN 경로를 구분했다. |
| Technical depth and knowledge coverage | Reviewed | 기존 Major Sections, 예제, Technical Boundaries와 Note를 보존하고 Backup과 변경 구간을 대조했다. |
| Formula as compressed relationship | Reviewed | Normalize / Dot / Transform의 의미 설명을 유지하고 새 증명이나 긴 Derivation을 추가하지 않았다. |
| Chapter 01 → 05 learning curve | Reviewed | Pipeline → Space → Direction Comparison → Material Data → Response의 연결을 유지했다. |
| Figures and existing notes | Checked | 43개 Figure의 정확한 경로와 순서, 기존 검증/Debugging/Production 정보의 보존을 확인했다. |
| Questionable technical content | Recorded | Chapter별 Technical Notes / Remaining Review Items와 Figure 상태에 기록했다. |
| Exact backups / unchanged Chapter 05 | Checked | 네 Backup의 SHA-256 및 Chapter 05와 기존 Figure 파일의 Hash를 확인했다. |
| GitHub reviewable working filenames | Prepared | 기존 파일명 네 개, 정확한 Backup 네 개, Audit을 검토용 Branch에 게시할 대상으로 준비했다. 게시 결과는 실제 PR 생성 후 기록한다. |

## Integrity Verification

| Chapter | Backup Bytes | Rewrite Bytes | Major Sections | Figure References | Backup Identity |
|---|---:|---:|---|---|---|
| 01 | 209169 | 210127 | 1.1–1.13 / preserved | 13 / same paths and order | SHA-256 match |
| 02 | 271790 | 295748 | 2.1–2.16 / preserved | 16 / same paths and order | SHA-256 match |
| 03 | 50166 | 55375 | 3.1–3.7 / preserved | 6 / same paths and order | SHA-256 match |
| 04 | 84339 | 103037 | 4.1–4.8 / preserved | 8 / same paths and order | SHA-256 match |
| Reference | — | — | Chapter 05 unchanged | Original Figure bytes unchanged | Hash match |

위 검사는 Byte 보존과 문서 구조의 손실을 찾는 검사다. 정보 보존은 이에 더해 Backup 전체 검토, 변경 구간의 의미 대조, 독립 Review로 확인했다. Figure Revision이나 Engine Verification이 필요한 항목을 완료된 것으로 표시하지 않았다.
