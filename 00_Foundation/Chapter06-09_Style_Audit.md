# Chapter 06–09 Style Audit

Date: 2026-10-04

Chapter06/07/09와 Chapter08 Index+8.0–8.10, 총 15개 원고를 읽고 감사했다. 후반 원고·구현 Asset·Figure는 수정하지 않았다. 현재 Chapter01–05의 완성된 최초 용어 설명을 근거로 새 정의가 필요한 경우와 회상이 적절한 경우를 구별했다.

## Scope and Evidence Method

이번 감사는 사용자 요청의 Chapter 06–09 Audit Only 기준을 적용했다. Chapter 06의 6.1–6.9, Chapter 07의 7.1–7.9, Chapter 09의 Introduction 및 9.1–9.9와 마지막 Advanced 안내까지 본문·표·Figure 주석·Data Flow·수식·구현 예시를 모두 읽었다. 예전 Style Audit의 판정을 복사하지 않고 이번 작업의 불변 원본 세 문서를 근거로 판단했다. 아래 L 번호는 각 불변 원본 파일의 실제 1-based line이다. Cross-Chapter Reuse에서 명시한 Chapter 05 L 번호만 최종 재작성 원고 기준이다. 줄 수의 차이는 정보량 판단 근거로 사용하지 않았다.

이 보고서는 감사 대상 15개 원고와 Figure를 수정하지 않는다. 검증 문구의 이동은 후속 수정 제안이며, 현재 정확한 Caveat의 삭제를 뜻하지 않는다. 이전 장에서 정의된 Term은 다시 처음부터 정의하라고 요구하지 않고 짧은 recall과 현재 장의 확장이 자연스러운지 판정했다. Figure 안의 새 용어/Label 전체를 OCR하여 새 이미지 감사를 실시한 것은 아니다. 현재 본문의 caption/reading note가 알려 주는 그림의 범위와 본문 대비 선행 위치를 검토했다.

### Cross-Chapter Reuse Basis

- 완성된 Chapter01의 최초 설명과 현재 원고를 대조했다. CPU/GPU, Shader/Rasterization/Fragment/Depth/Buffer/GBuffer/Deferred, Coordinate Space, Normalize/Unit Vector, Draw Call은 이미 소개된다. 재작성 원고에는 FPS(1.2), Overdraw(1.10), LOD(1.12)의 의미도 있다. LOD의 최초 예고 보완은 최종 보완까지 포함해 최종 원고에서 확인했다. Chapter 09에서 이 용어들의 Full Name/정의를 다시 요구하는 것은 중복이다.
- 완성된 Chapter04의 최초 설명과 현재 원고에서 Texture Sampling/Filtering/sRGB/Linear/Encoding/Decode, Parameter/Material Instance/Runtime/Static Switch/Variant/Permutation, PBR/HDR/AO와 Aliasing의 풀이를 확인했다. 06의 HDR/MSAA/AO와 07의 Scalar/UV/Sampling/Encoding/Aliasing은 새 영어 용어의 정의 누락으로 분류하지 않는다. MSAA는 새 01.8에서 설명된다.
- 완성된 최초 용어 대조 결과와 최종 Chapter05 원고를 대조했다. BRDF의 Full Name/역할은 도입 L9, Roughness recall은 5.1 L23, PBR recall은 L65, Radiometry의 의미 예고는 L67에 있다. Fresnel은 5.7, Scene Visibility/Vis는 5.10, Anisotropic은 5.17에서 의미를 설명한다. Lambert Direction Factor/ρ/π, Incoming/Outgoing 방향, Diffuse/Specular와 Radiance는 후속 장의 recall/적용 대상으로 판단했다. 5.14의 Display Interpretation Note는 Exposure와 Tone Mapping의 표시 목적을 이미 예고하므로 06에서 새 정의 누락으로 분류하지 않는다.
- IOR는 개념과 영어 이름을 구별해 대조했다. 최종 05.14의 Technical Note는 **굴절률**의 광학 입력 의미와 η1/η2·Dielectric F0 관계를 설명한다. 다만 `IOR` 및 `Index of Refraction`이라는 영어 이름은 최종 05 본문에 없으며, 최종 최초 용어 대조도 사용하지 않는 IOR 약어를 미리 도입하지 않는 처리를 명시한다. 따라서 07.5 L321의 굴절률/F0 연결은 앞 장 recall이지만 **IOR라는 약어 자체는 이곳의 첫 사용**이다. 후속 정리에서는 이름을 `IOR(Index of Refraction, 굴절률)`로 풀고 05.14의 관계를 짧게 회상하면 충분하다. 광학 설명/Formula를 07에서 전면 재정의할 필요는 없다.

### Recommendation Summary

| Chapter | Recommendation | Priority | Concrete Scope |
|---|---|---|---|
| 06 | **Light Style Pass Recommended** | P1: 첫 예고 연결 및 Figure 6-5 / P2: Engine·Exposure Note 분리 | Why→개념 연결은 유지하고 6.1/6.4/6.6의 밀도만 낮춘다. |
| 07 | **Partial Rewrite Recommended** | P1: 7.2의 도구 도입과 7.4 Shadow 관계 / P2: 7.6–7.8 및 Figure Notes | 전체 장의 비교 구조를 유지하며 특정 개념 설명 순서를 다시 쓴다. |
| 08 | **Targeted Cleanup Recommended** | P1: 진입 용어·검증 증거 경계 / P2: 긴 Figure Notes | I/O·구현 Step을 유지한다. 8.2/8.4의 Graph·Figure 검증 구간만 부분 재구성 후보이다. |
| 09 | **Light Style Pass Recommended** | P1: 도입 recall·Measurement Protocol 읽기 순서 / P2: 긴 caption·9.8 Quad 설명 | 측정→원인 분리→한 변수 비교→재측정 구조와 정밀도를 유지한 국소 정리이다. |

P1은 핵심 개념/Workflow를 처음 읽을 때의 이해, P2는 설명 호흡과 상세 조건의 배치이다. 이번 감사로 Full Rewrite가 필요한 장은 확인되지 않았다. 06–09 전체를 Chapter 05의 이론 설명 형식으로 강제 통일하지 않는다.

---

## Chapter 06 — Modern Real-time Rendering

### Strengths to Preserve

6.1 L7–17은 앞 장의 BRDF를 회상한 뒤 “BRDF를 만들었는데, 왜 아직 화면은 만들어지지 않을까?”(L13)로 시작한다. 이 질문은 Surface 반사 응답만으로 최종 화면을 만들 수 없다는 새로운 필요를 명확하게 제시한다. L31/L39는 학습 순서≠고정 Hardware Stage, Material≠독립 Hardware Stage라는 현재 정확한 범위를 유지한다. 이 핵심 경계는 간단한 본문으로 남기는 것이 좋다.

6.2 L129–149는 Light 입력이 필요한 이유→직접 전달되는 Light→태양/전구/손전등 예시로 이어진다. 6.3 L213–227은 Direct만 있을 때 어두운 영역의 문제를 먼저 설명하고 벽/바닥의 반사광을 통해 Indirect를 이해시킨다. 6.4 L282–300은 주변 환경을 입력으로 사용할 이유를 설명한다. 6.5 L361–396은 이전 물리 Reflection과 현재 환경 Reflection의 역할을 연결한다. 6.6 L428–445는 Environment Map이라는 Input과 HDR Rendering이라는 Process를 구별하고, 6.7은 높은 밝기 계산과 출력 범위의 문제를 먼저 제시한다. 6.8은 Texture 입력/Working/Display의 목적을 연결하며 6.9 L704–730은 여러 기여의 결합과 IBL Specular의 중복 가산 방지를 정리한다. 이 구조를 전체 Rewrite로 바꿀 이유는 약하다.

### First-Use Terminology Evidence

| Term | Actual First Appearance in This Chapter | Source Evidence | Assessment / Specific Recommendation |
|---|---|---|---|
| Rendering Pipeline | 6.1 From BRDF to the Rendering Pipeline; L3 | ## 6.1 From BRDF to the Rendering Pipeline | 01에서 정의됨. 첫 제목 뒤 L7–23은 BRDF→최종 Image 질문으로 역할을 확장하고 L29에 뜻을 회상한다. 재정의 누락으로 판정하지 않는다. |
| BRDF | 6.1 From BRDF to the Rendering Pipeline; L3 | ## 6.1 From BRDF to the Rendering Pipeline | 01/05에서 정의됨. 6.1 L7–17의 이전 학습 회상과 질문이 충분하다. 재정의 대신 현재 연결을 유지한다. |
| HDR | 6.1 From BRDF to the Rendering Pipeline; L19 | 게임 엔진은 Material 평가와 여러 Lighting 기여를 결합하고 HDR 결과를 출력 장치에 맞게 변환한다. Direct/Indirect Lighting과 Reflection은 반드시 하나의 직렬 단계씩 실행되는 관계가 아니다. | 새 04.5에서 High Dynamic Range와 넓은 밝기 범위를 설명했다. 6.1은 짧은 04 회상으로 연결하고 6.4 L302의 입력/Buffer/Display 구분과 6.6의 확장은 유지한다. Full Name 누락으로 재정의를 요구하지 않는다. |
| Direct / Indirect Lighting | 6.1 From BRDF to the Rendering Pipeline; L19 | 게임 엔진은 Material 평가와 여러 Lighting 기여를 결합하고 HDR 결과를 출력 장치에 맞게 변환한다. Direct/Indirect Lighting과 Reflection은 반드시 하나의 직렬 단계씩 실행되는 관계가 아니다. | 역할을 먼저 예고하면 좋다. 직접 전달되는 빛/다른 Surface를 경유한 빛이라는 짧은 연결 후 6.2 L137, 6.3 L227의 본 설명로 이어 간다. 기존 정의가 없는 것으로 판정하지 않는다. |
| Forward / Deferred Rendering | 6.1 From BRDF to the Rendering Pipeline; L75 | ### Forward and Deferred Rendering | 제목 바로 아래 L77의 목적과 L81–82의 비교가 명확하다. Deferred/GBuffer는 새 01에서 정의되었고 Forward는 01의 예고를 여기서 확장한다. 두 이름을 다시 사전식으로 설명할 필요가 없다. |
| GBuffer | 6.1 From BRDF to the Rendering Pipeline; L82 | \| Deferred \| Geometry Pass에서 GBuffer에 Normal·Material 등 필요한 데이터를 기록한 뒤 Lighting 평가 \| Buffer 저장·대역폭·Shading Model 표현 및 별도 경로의 비용을 확인 \| | 01.2/1.11의 Geometry Buffer 회상으로 충분하다. L84의 Surface Data와 최종 Lighting 구분은 본문에 유지하고 뒤의 경로 예외를 Note로 나눈다. |
| MSAA | 6.1 From BRDF to the Rendering Pipeline; L84 | GBuffer는 완성된 Lighting 이미지가 아니라 후속 평가에 필요한 Screen-space Surface Data이다. 모든 Material이 같은 경로를 따르지는 않는다. Translucency 등은 별도 Pass/Path를 사용할 수 있다. MSAA, 지원 Shading Model, 실제 Buffer 구성과 기능 제한은 Engine 설정에 따라 확인한다. | 새 01.8에서 Multisample Anti-Aliasing과 역할을 설명했다. 06에서는 재정의가 아닌 짧은 recall 또는 Engine Path Note의 참조로 처리한다. |
| Exposure | 6.1 From BRDF to the Rendering Pipeline; L92 | 동일한 Material이라도 Direct Light와 Environment가 달라지면 결과가 바뀐다. 반대로 같은 조명에서 Roughness만 바꾸면 Highlight의 분포 변화를 확인할 수 있다. 이때 Exposure를 고정하고 한 변수씩 비교한다. | 최종 05.14의 Display Interpretation Note에서 표시를 위한 노출 관계라고 이미 예고한다. 06 L92는 표시 밝기 기준을 고정하는 목적을 짧게 recall하고 6.6 L477에서 Scale/Stop 및 검증 조건으로 확장한다. 신규 정의 누락으로 판정하지 않는다. 고정 Exposure 조건은 본문에서 빠지면 안 된다. |
| IBL | 6.1 From BRDF to the Rendering Pipeline; L100 | - Image Based Lighting (IBL) | 6.1 L100에 Image Based Lighting Full Name은 있으나 환경 이미지의 밝기/색상을 입력으로 쓴다는 역할은 6.4 L290–300에서 나온다. Overview에 짧은 역할을 붙이면 예고만 보고도 목적을 안다. |
| Tone Mapping | 6.1 From BRDF to the Rendering Pipeline; L103 | - Tone Mapping | 최종 05.14의 Display Interpretation Note에서 계산한 밝기 범위를 표시 가능한 범위로 다루는 과정이라고 예고한다. 06의 첫 사용은 Overview 명칭이며, 여기에 앞 장의 출력 목적을 짧게 recall하면 된다. 6.7 L501–525의 문제→출력 범위→정의 확장은 좋다. |
| Color Bleeding | 6.3 Indirect Lighting; L259 | 벽과 바닥 사이의 Color Bleeding과 반사광이 채우는 실내 밝기는 Indirect Lighting의 예이다. Shadow 경계의 부드러움인 Penumbra는 주로 Light의 크기와 차폐 Geometry의 관계로 생긴다. Indirect Light가 Shadow 내부를 밝히는 효과와 구분한다. | 6.3 L259에서 벽/바닥 반사광 예시와 함께 나와 의미를 추론할 수 있다. 주변 Surface의 색이 반사광으로 번지는 효과라는 짧은 풀이가 있으면 더 명확하다. |
| Penumbra | 6.3 Indirect Lighting; L259 | 벽과 바닥 사이의 Color Bleeding과 반사광이 채우는 실내 밝기는 Indirect Lighting의 예이다. Shadow 경계의 부드러움인 Penumbra는 주로 Light의 크기와 차폐 Geometry의 관계로 생긴다. Indirect Light가 Shadow 내부를 밝히는 효과와 구분한다. | 첫 문장에 Shadow 경계의 부드러움이라는 풀이가 있다. Light 크기/차폐 Geometry와 indirect fill 구분을 유지한다. |
| Environment Map | 6.2 Direct Lighting; L170 | 반대로, 다른 Surface에서 한 번 이상 반사되어 들어오는 기여는 Indirect Lighting이다. 환경 이미지로 표현했다는 이유만으로 항상 Indirect가 되는 것은 아니다. Environment Map에는 직접 보이는 하늘·광원과 반사된 환경이 함께 들어갈 수 있다. | 첫 사용은 6.2 L170의 Direct/Indirect 경로 구분 Caveat이고 입력 목적의 본 설명은 6.4에 있다. L170에서는 주변 환경의 방향별 밝기/색상을 담는 입력이라는 의미를 짧게 붙이고 6.4에서 확장한다. 특정 파일 형식이라는 오해를 피하는 L302를 유지한다. |
| Bloom | 6.6 HDR Rendering; L469 | 이를 통해 Reflection, Image Based Lighting, Bloom, Exposure와 같은 Rendering 효과도 더욱 자연스럽게 동작한다. | 6.6 L469에서 효과 목록에만 나온다. 이번 장의 이해에 필요하면 어떤 역할인지 한 문장을 붙이고, 필요 없으면 심화 효과의 예라는 범위를 밝힌다. 전체 Bloom 이론 추가를 요구하지 않는다. |

### Density and Condition Placement

| Evidence | Current Reading Difficulty | Specific Recommendation | Core Condition to Keep in Main Flow |
|---|---|---|---|
| 6.1 L77–86, Forward/Deferred table와 바로 뒤 문단 | Surface 저장/Lighting 평가를 막 구별한 뒤 Translucency, MSAA, Shading Model, 실제 Buffer 및 자동 Light/Shadow 접근 제한이 연속된다. 일부는 기학습 이름이어도 새로운 관계가 한꺼번에 생긴다. | **P2.** L84의 첫 문장을 본문에 유지하고 별도 경로/지원 기능/실제 설정은 `Engine Path Note`로 묶는다. L86의 측정 안내와 08 Interface 범위는 관련 장을 연결한 Scope Note로 분리한다. | GBuffer는 최종 Lighting 이미지가 아닌 Surface Data; Path마다 실제 평가/저장 범위가 다르고 항상 빠른 Path는 없다. |
| 6.1 L90–92, Material Response | Roughness 분포, Metal/Dielectric Base Color 용도, 동일 Light 비교, Exposure 조건을 한꺼번에 묶는다. 정의는 이전 장에 있어도 세 관계를 동시에 떠올려야 한다. | **P2.** 04 입력→05 응답 회상 후 Roughness 비교와 Metallic Workflow 비교를 한 문단씩 나눈다. 새로운 glossary는 추가하지 않는다. | Roughness 증가≠모든 방향 응답의 단순 감소; Metal/Dielectric 입력 역할 차이; 비교 시 한 변수와 고정 Exposure. |
| 6.3 L259, Indirect role | Color Bleeding→Penumbra→Light 크기/차폐→fill 구분이 한 문단이다. 첫 용어와 개념 구분이 동시에 나온다. | **P2.** 반사광으로 어두운 곳이 밝아지는 예시를 먼저 마친 뒤 Penumbra와 구별하는 짧은 문단으로 나눈다. 심화 광원/차폐 사례만 Note로 둔다. | Indirect fill≠Shadow 경계의 부드러움. |
| 6.6 L477–481, Exposure | Scale/Stop/Pre-exposure/Camera→Auto Exposure→Fixed 조건→Scene 값 1/4→SDR Screenshot 한계가 빠르게 이어진다. | **P2.** 표시 기준을 바꾸는 Exposure 목적→1과 4 예시→왜 고정해 비교하는지→Engine Pre-exposure/Camera Note 순서를 제안한다. | Auto Exposure의 상쇄 가능성, Fixed Exposure/Camera/Post Process 비교, Buffer 값과 표시 결과 구분. |
| 6.7 L517와 6.8 L620–626 | SDR 예시/HDR Display 예외와 입력 Decode/Filtering/Compression/Normal Decode는 범위 조건이다. 현재 단락이 짧고 사용 위치에 붙어 있다. | **유지 우선.** 모든 Caveat를 Note로 밀지 않는다. Color/Data 구분 후 실제 UI/Compression 설정만 `Texture Import Implementation Note`로 둘 수 있다. | HDR≠동일 Display Encoding; 이미 Linear에는 중복 sRGB Decode 금지; Data Texture에는 Color Decode 금지; Normal의 Vector Decode 별도. |

### Figure Reading Note Review

Figure 6-5의 6.4 L312는 한 blockquote에 Diffuse/Specular 입력, Diffuse≠필수 다중 반사, 병렬 기여, 고정 순서 오류, 양방향 화살표 한계, 이미지 출처/Unreal 일치 미확인, 후속 이미지 수정 필요를 함께 담는다. 본문은 L316에서야 Diffuse/Specular IBL의 두 역할을 설명한다. 따라서 이 Figure Note가 본 개념보다 앞서 개념과 검증 문제를 모두 처리한다.

**P1 제안:** 그림의 독자 목적을 “환경 입력이 Diffuse와 Specular 응답에 사용됨을 비교한다”처럼 한 문장으로 먼저 알려 주고, 두 기여가 독립적으로 평가되어 합쳐지며 고정 직렬 순서가 아니라는 핵심 조건을 남긴다. 원문의 전체 화살표/출처/실행 검증 보정은 삭제하지 않고 `Figure 6-5 Verification Note` 또는 `<details>`로 분리한다. 현재 이미지가 검증 결과가 아니라는 표시 자체는 caption에서 읽을 수 있어야 한다. 이 감사에서는 Figure를 수정하지 않는다.

다른 Figure의 본문 캡션은 비교적 짧다. 6.1 L33–49의 그림은 Pipeline/BRDF 역할을 읽기 위한 범위가 주변 본문에 있다. 경로/기여/입출력을 Figure의 고정 실행 순서로 되돌리는 제안은 하지 않는다.

### Final Recommendation and Remaining Review

**Light Style Pass Recommended.** 6.1의 Overview에는 새 용어를 모두 정의하는 표 대신 각 입력/변환의 짧은 역할을 붙인다. 6.4 Figure Note와 6.6 Exposure의 상세 조건을 나누고, 현재 Why-first 구조·기여 중복 방지·Linear/Decode 방향을 유지한다. 최종 05 map 및 실제 정의 위치의 교차 확인은 완료했다. 사용 Engine에서의 실제 Path/UI와 미확인 Figure 출처는 후속 검증 항목이다. 이번 문체 감사로 실제 Unreal 실행 일치를 확인한 것은 아니다.

---

## Chapter 07 — Stylized Rendering

### Strengths to Preserve

7.1은 원하는 표현을 위해 현실을 단순화/변형하는 이유를 설명하고 PBR/NPR의 Full Name과 목적을 제시한다. L31–39는 물리적 일관성과 표현 의도를 두 축으로 구별하여 함께 쓸 수 있다고 설명한다. 이 관계를 배타적 두 기술로 되돌리지 않는다.

7.2–7.8은 각 요소의 시각적 역할→물리 응답의 의미→Stylized 제어→Comparison→ASF 현재 구현 또는 Extension 범위를 반복한다. 7.3 L211, 7.4 L286, 7.5 L363, 7.6 L450–462, 7.7 L551–563, 7.8 L636–653은 교육용 Phong, 연속적인 Base Lighting, Manual Visibility, Artistic Rim, Hair/Face/Outline의 향후 확장을 실제 완료 구현과 구별한다. 이 역할에 맞는 비교/Scope 구조와 7.9의 공통 도구 정리는 유지할 가치가 있다. 7.9는 단순 반복이 아니라 앞에서 사용한 세 제어를 종합하는 절이다.

### First-Use Terminology Evidence

| Term | Actual First Appearance in This Chapter | Source Evidence | Assessment / Specific Recommendation |
|---|---|---|---|
| PBR | 7.1 Why Stylized Rendering?; L11 | 이러한 접근은 오늘날 **Physically Based Rendering(PBR)** 으로 발전하였으며, 대부분의 Modern Rendering Engine에서 표준 Rendering 방식으로 사용되고 있다. | 새 04/05에서 정의됨. 7.1 L31의 물리적 일관성 vs 표현 의도 두 축은 자연스러운 확장이다. 재정의보다 회상을 유지한다. |
| NPR | 7.1 Why Stylized Rendering?; L17 | 이처럼 현실을 의도적으로 단순화하거나 변형하여 원하는 시각적 표현을 만드는 Rendering 기법을 **Stylized Rendering** 또는 **Non-Photorealistic Rendering(NPR)** 이라고 한다. | 06 마지막 연결에서 Full Name과 표현 목표를 이미 설명했고 7.1 L17은 즉시 의미까지 설명한다. 충분하다. |
| Lambert Diffuse | 7.2 Diffuse Lighting; L78 | 이번 절에서는 PBR에서 사용하는 Lambert Diffuse를 다시 살펴보고, Stylized Rendering에서는 이것이 어떻게 변화하는지 비교해 보자. | 05에서 정의됨. 이 장의 Lambertian BRDF 명칭/ρ/π는 L86에서 처음 회상한다. 이 정확성 회상 자체는 적절하나 L88의 정면/측면 직관보다 먼저 긴 식/조건이 나온다. 직관을 먼저 회상하고 Direction Factor/BRDF 구분을 사용 직전에 유지한다. |
| Threshold | 7.2 Diffuse Lighting; L98 | - **Threshold**: 기준 t에서 입력 x를 두 영역으로 나눈다. 예를 들어 x<t는 0, x≥t는 1이다. | 7.2 L98에 즉시 의미와 x/t 관계가 있다. 문제는 정의 부재가 아니라 세 새 도구의 동시 도입이다. D=0.4/0.6 예시와 명암 두 단계 목적을 먼저 연결한다. |
| Smoothstep | 7.2 Diffuse Lighting; L99 | - **Smoothstep**: e0<e1 구간에서 0→1을 부드럽게 연결한다. 경계값이 같거나 뒤집히지 않도록 한다. | 7.2 L99에 함수의 역할과 e0<e1 조건이 있다. 단단한 경계를 부드럽게 연결하려는 문제를 먼저 소개하고 조건은 적용 직전에 남긴다. |
| Ramp Texture | 7.2 Diffuse Lighting; L100 | - **Ramp Texture**: Scalar 입력을 UV 좌표로 사용해 원하는 Scalar 또는 Color를 Sample한다. 입력 Data와 출력 Color Encoding을 구분한다. | 7.2 L100에 Scalar→UV→Sample→Color Encoding을 한 줄로 모았다. Scalar/UV/Sampling/Encoding은 03/04 기학습 용어다. 원하는 명암/색을 고른다는 목적을 먼저 설명하고 입력 Data/출력 Color 구분은 본문에 유지한다. |
| IOR | 7.5 Rim Lighting; L321 | IOR는 매질의 굴절률이며 Dielectric F0와의 기본 관계는 Chapter 05.14에서 설명했다. Chapter 08.5의 Artistic Rim Mask는 이 물리적인 Fresnel 계산과 구분한다. | 최종 05.14의 Fresnel 관계 설명는 굴절률과 η/F0 관계를 설명하지만 IOR/Index of Refraction이라는 영어 이름은 사용하지 않는다. 따라서 광학 개념은 recall이고 영어 약어는 07의 첫 사용이다. 후속 정리에서 IOR(Index of Refraction, 굴절률) 이름만 즉시 풀고 05.14 연결을 유지한다. 광학 Formula/관계를 07에서 전면 재정의할 필요는 없다. |
| Hair Fiber | 7.6 Hair Lighting; L400 | 머리카락은 수많은 Hair Fiber가 모여 이루어진 구조이므로, 빛은 표면에서 한 번만 반사되지 않고, 반사와 굴절, 내부 산란이 함께 발생한다. | 7.6 L400에서 구조 설명에 사용한다. 머리카락 한 가닥이라는 짧은 의미를 붙이고 Reflection/Transmission은 05 recall로 연결하면 좋다. |
| Marschner / Dual Scattering / Hair Strand | 7.6 Hair Lighting; L404 | 대표적으로 Marschner Model이나 Dual Scattering과 같은 Hair Model이 사용되며, Hair Strand의 방향에 따라 Specular Highlight가 길게 형성되는 것이 특징이다. | 7.6 L404에 모델 이름과 Strand가 묶여 나온다. 이름을 암기시키기보다 Fiber 내부/여러 Fiber 사이의 범위를 구분한 L402/L408 설명을 먼저 연결하고 모델 분류는 named Hair Model Note에 둔다. |
| SSS | 7.7 Face Rendering; L497 | 또한 피부의 특성을 표현하기 위해 **Subsurface Scattering (SSS)** 를 적용하여, 빛이 피부 내부에서 부드럽게 퍼지는 효과를 표현하기도 한다. | 7.7 L497–499에서 Full Name과 피부 내부 빛의 퍼짐/출사 의미를 즉시 설명한다. 충분하다. Advanced 구현 범위 문장은 현상 설명 뒤의 Scope Note로 나눌 수 있다. |
| Face SDF | 7.7 Face Rendering; L515 | 따라서 얼굴의 Shadow를 단순화하거나, 얼굴 전용 Shadow Mask를 사용하여 의도한 명암 패턴을 유지하도록 제어한다. 고정 Mask와 Light 방향에 따라 Threshold를 바꾸는 Face SDF 방식은 다르며, Face SDF가 항상 Light-independent한 것은 아니다. | 7.7 L515에서 먼저 쓰이고 L523에 Signed Distance Field Full Name과 용도가 나온다. 얼굴 Shadow 경계를 제어한다는 목적만으로 distance/signed 이름은 풀리지 않는다. 첫 예고에서 뜻을 짧게 연결하고 구체 인코딩/알고리즘은 심화로 남긴다. 고정 Mask와 Light-dependent SDF의 구분을 삭제하지 않는다. |
| Face Forward Vector | 7.7 Face Rendering; L519 | 대표적으로 Face Shadow Mask, Face SDF, Face Forward Vector 등을 이용하여 얼굴의 Shadow를 안정적으로 제어하기도 한다. | 7.7 L519에서 이름만 나열된다. 머리/얼굴이 향하는 기준 방향이라는 역할을 바로 붙인다. World/Head-relative Light 구분은 실제 구현/검증에 계속 남긴다. |
| Inverted Hull / Normal Expansion / Edge Detection | 7.8 Outline; L607 | > **Figure 7-8 읽기 보정:** 하단 네 항목은 독립된 네 기술이 아니다. Geometry-based 계열에서는 Inverted Hull에 Normal Expansion을 사용할 수 있고, Screen-space 계열에서는 Depth/Normal 등의 Buffer에 Edge Detection을 적용한다. Depth가 Normal을 생성한다는 뜻으로 화살표를 읽지 않는다. Outline은 PBR Material과도 결합할 수 있는 별도 표현 효과이다. 위 Character OFF/ON 이미지의 출처와 통제 조건은 확인되지 않았으며, OFF에도 기존 Texture/Geometry의 선이 보일 수 있으므로 추가 Outline Pass만의 효과를 검증한 비교로 인용하지 않는다. 이미지 영역을 보존한 Grouping/Label 정정이 필요하다. | 7.8 Figure Note L607이 본 설명 L621–632보다 먼저 이름을 낸다. 가족별 원리를 먼저 설명한 뒤 전체 보정 Note를 읽게 한다. Geometry 방식의 관계와 Buffer→Edge 검출 방향은 본문에서도 간단히 유지한다. |
| Spatial / Temporal Aliasing / Pixel Footprint | 7.9 Core Stylization Techniques; L707 | 이를 이용하면 Toon 스타일은 유지하면서도 값의 전환을 완화할 수 있다. 고정 Width Smoothstep만으로 모든 Spatial/Temporal Aliasing을 해결하지는 못하며 화면상 Pixel Footprint와 Sampling도 확인한다. | Aliasing 자체는 새 04.4에서 설명됨. 7.9 L707에서 공간/시간 구분과 Pixel Footprint가 갑자기 묶인다. 04 Sampling 문제를 짧게 회상한 뒤 Sampling Validation Note로 상세 조건을 분리한다. Smoothstep 하나가 모든 aliasing을 해결한다는 의미가 되면 안 된다. |

### Sections Requiring Partial Recomposition

| Evidence | Finding | Specific Recommendation | Technical Content to Preserve |
|---|---|---|---|
| 7.2 L84–90 | Lambert를 회상한 직후 L86에 ρ/π, max(0,N·L), 같은 Space/Unit, D, Remap, Irradiance/BRDF 구분이 먼저 나온다. 정면과 측면의 친숙한 현상은 L88에 뒤따른다. | **P1.** 05의 연속적인 방향 밝기를 먼저 회상→왜 명암을 단순화하는지→현재 입력 D의 의미→Unit/Space 조건→식과 BRDF 구분 순서로 연결한다. ρ/π 상세 회상은 `Lambert Reference Note`에 둘 수 있으나 D≠BRDF 설명은 입력을 정할 때 본문에 남긴다. | ρ/π, one-sided max, 동일 Space/Unit N/L, D는 방향 계수이며 Irradiance나 BRDF가 아님. |
| 7.2 L96–110 | Threshold/Smoothstep/Ramp 정의 세 개와 기호·구간·Sample·Encoding을 먼저 읽고 L104에서야 “연속 변화가 항상 필요하지 않음”이라는 Why를 읽는다. 정의는 존재한다. | **P1.** 명암을 두 단계로 보이고 싶은 문제→D=0.4/0.6과 t=0.5 예시→Threshold→경계 부드럽게 만들 필요/Smoothstep→원하는 Palette/Ramp 순서로 한 도구씩 설명한다. 기존 예시와 입력/출력 범위는 삭제하지 않는다. | e0<e1, Threshold 경계 관계, Scalar 입력과 Color 출력 Encoding, 이 변환이 Scene Visibility를 제공하지 않음. |
| 7.4 L242–260, L278–286 | Shadow의 Light Visibility와 NdotL/감쇠/Penumbra/Indirect fill 차이를 한 문단에서 정리한 뒤 Threshold/Ramp를 다시 사전식 정의한다. | **P1.** 다른 Object가 Light 경로를 가리는 친숙한 상황→Visibility와 방향 명암이 다른 이유→Shadow 입력을 Stylize하는 관계 순서로 나눈다. Threshold/Ramp는 “7.2의 도구를 여기서는 Shadow 입력에 적용”하는 recall로 바꿀 것을 제안한다. Light 크기별 예시만 추가 Note로 옮긴다. | Scene Shadow≠NdotL; 날카로운 경계도 물리적 Shadow 가능; Penumbra≠Indirect fill; Manual Visibility는 자동 Engine Shadow 읽기가 아님. |
| 7.5 L335–337, 7.9 L683–732 | 7.2에서 정의한 Threshold/Ramp를 7.4/7.5에서 다시 “후반에 자세히 설명”하고 7.9에서 정리한다. | **P2.** 7.4/7.5의 사전식 정의만 짧은 적용 회상으로 정리한다. 7.9는 세 도구의 차이/조합을 비교하는 요약 역할로 유지한다. | 각 요소에 어떤 입력을 Remap하는지, Rim은 Light-independent Artistic Mask일 수 있다는 현재 범위. |
| 7.6 L398–410 | Hair가 여러 Fiber로 이루어진 직관은 좋으나 모델 명칭/Strand/Simulation까지 이어져 새 관계가 많다. | **P2.** 한 가닥과 여러 가닥 사이의 빛 문제를 먼저 구별한다. 모델 분류·Marschner/Dual/Multiple 범위·향후 전용 구현은 named `Hair Model and Scope Note`로 분리할 수 있다. | 한 번의 Surface 반사로 끝나지 않는 범위, Fiber 내부와 Fiber 사이 산란의 차이, 현재 ASF 전용 구현 미완료. |
| 7.7 L497–523 | SSS는 즉시 풀이되나 Advanced Scope가 정의와 섞인다. Face SDF/Forward Vector는 실제 목적/용어 뜻의 연결을 더할 여지가 있다. | **P2.** 현상→얼굴 명암을 의도대로 유지하고 싶은 필요→Mask/SDF/기준 방향을 하나씩 소개→Extension 범위 순서를 제안한다. 구체 SDF Encoding/구현 수식은 현재 근거 없이 새로 단정하지 않는다. | 고정 Mask≠Light-dependent Face SDF; 전용 Skin/Face는 Advanced 범위; World/Head-relative Light 기준 구분. |
| 7.8 L607–632 | Figure Note의 Inverted Hull/Normal Expansion/Edge Detection이 가족별 원리 설명보다 앞서 나온다. | **P2.** 그림의 역할을 짧게 안내하고 Geometry 확장/Screen Buffer 경계 검출의 두 가족을 먼저 설명한 뒤 전체 Figure 보정을 제시한다. | Inverted Hull과 Normal Expansion의 포함 관계, Depth/Normal Buffer→Edge 검출, Depth→Normal 생성으로 읽지 않음. |
| 7.9 L703–707 | 부드러운 경계의 Why는 좋은데 Aliasing/Footprint/Sampling 검증을 한 문단에 덧붙인다. | **P2.** 부드러운 전환 설명을 끝낸 후 04의 Sampling 문제를 짧게 회상하고 `Sampling Validation Note`에 실제 확인 대상을 나눈다. | 고정 Width Smoothstep만으로 모든 공간/시간 aliasing이 해결되지 않음; 화면상의 Footprint/Sampling 검증 필요. |

### Figure Note Separation Plan

| Figure / Evidence | Short Caption or Main Explanation to Keep | Details to Move, Without Deletion |
|---|---|---|
| 7-3; 7.3 L179 | Specular 응답 폭/형태의 정성 비교; 상대값을 실제 밝기/BRDF 상한으로 읽지 않는다는 표시; V는 Surface→Camera. | 고정 Unit L/V, H 생성, N을 바꾼 단면의 부호 있는 각도, Sphere와 Graph의 비일대일 관계를 `Figure 7-3 Reading Note`로 분리한다. |
| 7-6; 7.6 L430 | Fiber/Clump와 Highlight의 표현 목표 비교이며 실제 ASF Hair Shader 검증 결과가 아니라는 범위. | 상대 Strand 회전의 기준, 0°와 최대 응답 비동일, 0–1 상대값, inset 화살표는 실제 연결 광경로/정량 해가 아니라는 조건을 전체 Note에 보존한다. |
| 7-7; 7.7 L531 | 서로 다른 얼굴 표현 예시이며 통제된 Lighting 실험/현재 ASF 완료 증거가 아님. | World/Head-relative Light, Camera/Exposure, Geometry/Parameter 통제, 실제 분리 Pass 미확인, 출처 확인 요구를 `Figure 7-7 Verification Note`로 묶는다. 조건을 없애지 않는다. |
| 7-8; 7.8 L607 | Outline 역할 및 Geometry/Screen-space 두 가족; OFF/ON이 추가 Pass만의 통제된 효과 검증이 아님. | 기존 선/Texture/Geometry, 독립 네 기법이 아닌 grouping, 잘못 읽을 수 있는 화살표, 이미지 출처와 후속 Label 정정을 Note에 보존한다. 가족 관계 자체는 본문에도 남긴다. |

이 네 Note는 본래의 정확성 보강으로 필요하다. 문장만 줄여 의미를 버리는 제안은 하지 않는다. 그림을 단순 학습 도식으로 읽기 전에 실제 구현/실측 증거가 아님을 알 수 있어야 한다. Caption과 Note를 분리해도 그 범위는 첫 화면에 유지하는 것이 좋다.

### Formula Classification and Final Recommendation

7.2의 Direction Factor/Threshold 예시는 **Essential**이며 의미 설명 후 유지한다. Lambert ρ/π 회상과 Stylized 입력의 관계는 **Explain First**로, 새 수식이나 물리적 주장으로 바꾸지 않는다. Figure의 전체 각도/상대값/모델 convention은 **Move to Technical Note** 후보이다. Unit/Space, e0<e1, Visibility와 D의 구분 및 Encoding 조건은 적용 직전의 핵심 조건이다.

**Partial Rewrite Recommended.** 우선 7.2와 7.4를 질문/예시/단일 도구 순서로 다시 연결하고, 반복 사전 정의를 recall로 줄인다. 7.6–7.8은 새로운 개념의 짧은 의미와 Figure Note 배치를 다듬는다. 기존 Role→Comparison→Implementation/Extension 구조와 현재 Scope는 유지한다. 최종 05와 대조해 IOR의 개념 recall/새 영어 약어 구분까지 확인했다. 후속 정리에서 07의 IOR Full Name을 붙이면 되며, 전용 Hair/Face/Outline 실제 구현과 Figure 출처/통제 조건은 별도 검증 항목이다.

---

## Chapter 08 — Building an Anime Shader

### Overall Recommendation

**Targeted Cleanup Recommended**

Chapter 08은 이론을 처음 소개하는 Chapter 05와 역할이 다르다. 문제를 설명하고, 필요한 Data를 정하고, Material Function Interface와 Graph를 만들고, 결과를 확인하는 현재 구조가 적합하다. 전 Chapter를 Chapter 05의 설명 순서나 소제목으로 바꾸는 작업은 권장하지 않는다.

전체 정리의 우선 대상은 새 개념의 진입 문장, 여러 조건이 한꺼번에 쌓인 Figure 설명, 구현 절차와 검증 증거의 경계이다. 8.2와 8.4에서는 아래에 지정한 **Figure를 읽고 Graph를 검증하는 일부 구간**을 다시 구성하는 편이 좋다. 다른 절의 친절한 Why 설명이나 I/O·Data Flow·단계별 구현을 통째로 다시 쓰는 이유는 없다.

### Scope and Review Method

- 기준: 2026-10-04 작업의 Rewrite 직전 Backup에 보관된 현재 검수본. 아래 line은 해당 원본의 1-based source line이다.
- 검토 범위: Index와 8.0–8.10의 총 12개 Markdown 파일. 각 파일의 본문 Section, 개념 설명, I/O, fenced Formula·Data Flow·Graph 설명, Figure 설명, 구현 단계, 검증, Reference와 마지막 연결을 대상으로 확인했다.
- 판정 기준: Concept이 구현보다 먼저 설명되는지, 새 Unreal 용어의 첫 등장이 풀리는지, Caveat가 구현 단계의 사고 흐름을 끊는지, 반복이 역할을 갖는지, 검증 절차와 검증 결과의 범위가 구별되는지.
- 이전 Chapter에서 배운 Vector, Normal, Space, UV, Sampling, BRDF, Static Parameter 등은 재정의 대상이 아니다. 구현에서 달라지는 역할을 짧게 회고하는 방향으로 판단했다.
- 이번 결과는 **Audit Only**이다. Chapter 08 문서, Figure, 구현 Asset을 수정하지 않았고 Unreal Engine을 실행해 Compile·Runtime 결과를 새로 검증하지 않았다.
- 이전 구조 검수 이후 이미 정리된 사항은 다시 문제로 기록하지 않았다. 현재의 Index Chapter 번호, 8.8의 실제 제목·링크, Implementation Reference 명칭, 마지막 Key Takeaways/Next, 8.10의 Overview와 뒤쪽 Expected Calculation Checks 배치를 유지하는 것이 적절하다.

### Review of All 12 Files

| File | Concept before Implementation / Preserve | First-use / Caveat / Repetition / Validation Finding | Recommendation and Concrete Cleanup Unit |
|---|---|---|---|
| `Chapter08_BuildingAnAnimeShader.md` | Why a Framework의 큰 Graph 유지보수 문제 → Module 책임 → Chapter Structure 연결이 자연스럽다. Index의 학습 목표와 실제 하위 Chapter 링크를 유지한다. | Material Function은 L24 학습 목표에서 먼저 나오고, Master Material·Lerp는 L41에서 합성 및 비용 Caveat와 함께 나온다. L101의 Module/Function/Stage 구분은 유용하지만 명칭을 풀어주는 첫 문장이 조금 늦다. | **Targeted Cleanup Recommended** — Why a Framework의 L39–41을 Function의 재사용 목적 → Master의 조합 역할 → 결합 연산의 짧은 의미로 나누고, 실행 비용·Renderer 접근 범위는 짧은 Scope Note로 묶는다. Index를 자세한 용어 사전으로 늘리지는 않는다. |
| `Chapter08.0_PreparingTheASFProject.md` | 환경을 왜 고정하는지, Blank Project 선택 이유, 폴더·Naming·Version Control의 이유가 설명되어 있다. 실제 목표 환경 확인과 단계별 Checkpoint가 구현 시작 전 필요하다. | Blueprint 표 L191과 Project Type L215–219, Settings 표 L353–358에서 UI 이름이 의미보다 먼저 나온다. SM6의 풀이는 L384, TSR은 Figure 설명 L347에서 먼저 나온 뒤 L357/L383에서 풀린다. RHI는 이 파일에서 풀리지 않는다. 반복되는 Organization/Content Structure의 책임 설명과 마지막 준비 완료 표는 역할을 조금 더 분명히 할 수 있다. | **Targeted Cleanup Recommended** — Project Type 앞에 Blueprint의 이 실습 역할 한 문장, Recommended Settings 표 앞에 필요한 설정 이름의 목적과 acronym을 짧게 연결한다. Settings의 실제값 확인 조건은 표 옆에 유지한다. L418–613의 Organization와 Content Browser는 원칙/실제 폴더 만들기 역할을 나누고, L909–919의 완료 표는 독자가 확인할 체크 상태로 읽히게 한다. |
| `Chapter08.1_ArchitectureOverview copy.md` | Single Graph가 커지는 문제, Module Input/Processing/Result, Function 재사용, Master 조합, Shared Inputs가 충분히 설명된다. 특히 논리적 Module과 Renderer Stage/Pass 구분, 공유 N/L/V Branch의 합류를 유지한다. | Material Function의 구체적인 의미가 L134–136에 잘 설명되지만 첫 실사용 L72와 떨어져 있다. Master의 역할은 L164/L171에 충분하다. Data Flow와 마지막 Key Takeaways의 반복은 Architecture 설명/회고 역할이 구분되어 있다. 긴 Figure Caption도 없고 Caveat가 Step을 크게 끊지 않는다. | **Targeted Cleanup Recommended** — L72 바로 뒤에 L136의 재사용 목적을 짧게 앞당기고, 첫 Master 등장 L134에서 조합 위치를 한 문장으로 먼저 설명한다. Index에서 이 두 개념을 설명한다면 여기서는 짧은 회고만 필요하다. Architecture 전체 Rewrite는 불필요하다. |
| `Chapter08.2_BaseLighting.md` | 방향에 따라 같은 Color의 밝기가 달라지는 문제 → Normal/Light 관계 → Direction Factor → I/O → Normalize/Dot/Saturate → Color 적용이 잘 이어진다. Scalar `LightingData`와 Vector3 `LightingResult`를 분리하는 계약을 유지한다. | L245와 L547 Figure 교정이 배선 상태·출력 종류·Unlit·Exposure·재촬영 증거를 한꺼번에 설명한다. L539는 Material Unlit/Emissive 출력과 Viewport Lit/화면 밝기의 구분을 한 문단에 몰아서 구현 확인 사이에 넣는다. Conditional Engine Expression L606–608은 기본 경로와 별도로 잘 배치되어 있으나 조건 목록이 길다. | **Specific Section Rewrite Recommended** — `Creating the Function Interface` L233–251와 `Basic Implementation Validation` L521–570을 짧은 Step → 예상 출력 → Figure에서 확인 가능한 항목 → Verification Note 순서로 다시 구성한다. Unlit/Emissive는 이미 배운 용어의 **이 실습 출력 역할**을 회고한다. LightDirection 기본 입력과 조건부 Engine Adapter는 합치지 않는다. |
| `Chapter08.3_Shadow.md` | 빛을 향한 표면도 왜 어두울 수 있는가 → Visibility/Occlusion → Ray → Shadow Map → Bias/Filtering → Lighting 적용 → Engine 관찰 → `MF_Shadow` 흐름이 충분하다. PCF의 Full Name과 Depth 비교 후 Visibility 평균의 구분이 명확하다. | L1815–1837은 좌표·Depth Encoding·비교 방향·수치 예제 조건을 많이 묶지만 핵심 조건은 비교 직전에 있어야 한다. Bias가 L1837 주의문에서 정의 L2957보다 먼저 등장한다. Texture/Texel/Pixel 회고 L2389–2567과 Shadow Map/Lightmap 구분이 여러 번 나온다. 긴 Figure 8-32(L2871)와 Engine Figure Reading Notes(L4440/L4542/L4569)가 설명 흐름을 끊는다. | **Targeted Cleanup Recommended** — Depth 비교 직전 조건은 유지하고 Convention 상세만 Note로 분리한다. 첫 Bias 언급에 목적 한 문장을 붙인다. Texture의 기존 정의는 짧은 회고로 연결하고 Shadow Map의 실제 Texel Footprint 설명을 본문에 남긴다. Figure마다 관찰 내용/미확인 설정/재촬영 제안을 구분한다. 수동 Visibility 적용과 실제 Renderer Shadow 관찰을 합치지 않는다. |
| `Chapter08.4_Specular.md` | Highlight의 친숙한 문제 → Light 방향 → Normal projection → Reflection 방향 → View 방향 → Power로 집중도 조절 → Function Interface의 개념 순서가 좋다. Phong의 교육용 응답과 물리적 BRDF 구분도 유지해야 한다. | L5의 모델·Space·Unit 조건이 Highlight 문제보다 먼저 길게 나온다. Fig8-10(L406), 8-14(L711), 8-15(L866), 8-16–18(L1058/1070/1082), 8-19(L1234) 교정이 Graph 단계 사이에서 반복된다. 동일한 Normalized L 재사용과 RGB Debug/정량 검증 조건은 기술적으로 중요하다. | **Specific Section Rewrite Recommended** — Figure 기반 Graph 검증 구간을 재구성한다. 각 Caption은 지금 보이는 것 한두 문장으로 두고, 현재 계약과 다른 배선/미확인 출력/재촬영 필요는 해당 Step의 Verification Note로 묶는다. 지수 비교 세 Figure는 공통 고정 조건을 한 번 설명하고 차이만 각각 남긴다. 방향 계산과 Reflection 직관 자체는 유지한다. |
| `Chapter08.5_RimLight.md` | Silhouette의 강조 문제 → N·V와 경계 관계 → Prototype Power → Width/Softness 필요 → 최종 Interface 변경이 단계적으로 설명된다. Prototype과 최종 구현을 모두 보존할 가치가 있다. | L5에서 최종 Interface·정규화 조건·Prototype 변경이 Why보다 먼저 나온다. L2052의 유효 범위/Off/Step/Smoothstep 경계 조건은 첫 Parameter 연결에 필요하지만 한꺼번에 길다. Figure 8-42(L309), 8-48(L2139), 8-50(L2823)의 Scope 교정은 출력 확인과 구현 이력을 섞는다. Implementation Reference의 반복은 최종 계약 빠른 조회 역할이다. | **Targeted Cleanup Recommended** — Opening에는 Prototype에서 최종 Width/Softness로 발전한다는 안내만 짧게 두고, 구체적 계약은 해당 I/O에 둔다. `0<Softness≤Width≤1` 같은 정상 입력 조건은 구현 Step 곁에 유지하고 Width=0/Softness=0 등 경계 정책은 Implementation Note로 분리한다. Figure는 Prototype/중간/최종 계약 중 어느 상태를 보여주는지 먼저 표시한다. |
| `Chapter08.6_MatCap.md` | 저장된 Appearance를 왜 읽는지 → Normal 기반 Lookup → View Space → XY → UV Remap → TextureObject/Sampling → 합성의 Concept 설명이 풍부하다. Translation/Rotation 구분, Intensity와 Blend의 차이를 유지한다. | L5에서 MatCap, Camera Basis 근사, TextureObject, Linear RGB 계약이 함께 나온다. MatCap의 Full Name은 L474, TextureObject의 본격 설명은 L3817 이후라 진입에서 늦다. Unit Disk/hemisphere/Filtering/Address Mode 조건 L2129, Figure 8-54/55/56/58 설명은 한 단위에 많다. L5054의 Blend Off 조건은 합성 바로 옆에서 반드시 유지해야 한다. | **Targeted Cleanup Recommended** — 첫 Why 문장 가까이에 MatCap의 Full Name과 재사용되는 Appearance 의미를 둔다. TextureObject는 첫 Function resource 입력에서 Chapter04의 Resource/값 구분을 회고한다. UV의 본 계산 설명 뒤에 edge/address/basis 상세를 Note로 묶되 정확한 입력 계약을 가리지 않는다. Figure의 Raw RGB, UV 범위, 축 방향, Perspective 비교 조건을 관찰/검증별로 나눈다. |
| `Chapter08.7_Emission.md` | Unlit Final Color 전부를 Emission이라고 불러도 되는가라는 질문이 매우 좋다. 출력 pin과 논리적 Emission Contribution → Color/Intensity → HDR/Bloom/Exposure → Mask → I/O → 합성으로 순차 설명한다. | Emissive 출력의 Bloom/GI 범위가 L128과 L543에 반복되지만 하나는 개념 구분, 하나는 구현 주의라는 역할이 있다. Exposure 실험의 조건과 L2664/L5065 Figure 설명이 길다. L5134는 Presentation Exposure, 정량 검증은 Fixed Exposure임을 분명히 구분한다. Mask=0이 Emission Module만 0이라는 조건 L5343은 꼭 그 자리에서 유지한다. | **Targeted Cleanup Recommended** — Engine 출력 범위의 공통 설명은 한 위치를 기준으로 짧게 회고하고 긴 설정 조건은 실험의 Verification Note로 묶는다. Figure Caption은 비교 변수와 보이는 차이를 먼저 적는다. Bloom/Exposure 자체의 단계적 설명과 Mask 실습은 재작성할 필요가 없다. |
| `Chapter08.8_MaterialLayer.md` | 같은 Surface의 다른 영역에 다른 Parameter가 필요한 문제 → Region Mask → Parameter 선택 → Specular 적용 → Material 경계 판단이 잘 이어진다. Parameter Lerp와 Result Lerp가 일반적으로 같지 않은 이유를 설명한다. | L5가 Unreal Material Layers와의 구분, 독립 예제, Slot/Pass 비용 기준을 Why보다 앞서 묶는다. Figure 8-67(L256)/8-68(L1043)의 Graph 교정과 비격리 비교 조건이 길다. L468의 비선형 Shininess/선형 Intensity 차이는 바로 옆에 필요하다. 후반 ASF Application/Material Boundaries와 Key Takeaways는 이미 역할에 맞게 정리되어 있다. | **Targeted Cleanup Recommended** — Opening에는 이 절이 Region Parameter Mask 실습이라는 범위만 두고 실제 Material 경계 선택 기준은 후반 해당 절에 둔다. Caption의 기존 배선/현재 계산 차이를 Verification Note로 나눈다. 독립 예제를 Master에 자동 통합하는 변경은 권장하지 않는다. |
| `Chapter08.9_DebugView.md` | 최종 Look만 보면 어디가 잘못됐는지 알기 어렵다는 문제 → 실제 중간 값 선택 → Mode Interface → Selector → Display/검증 → Master 연결이 충분히 설명된다. 재계산 대신 실제 결과를 분기해서 보는 원칙을 유지한다. | 기존 Normal/Scalar/RGB 설명은 목적 있는 회고다. L2502의 Display 조건은 Unlit/Exposure/Tone Mapping/Bloom/출력 Encoding/Scalar Type을 한꺼번에 묶는다. L1872 Fig8-71은 현재 계약을 반영한 증거가 아니라는 안내가 있고, 이후 L2954 등의 확인 완료 문구와 독자가 혼동할 여지가 있다. L3274–3278의 If/Static Switch 비용 범위는 유용한 Implementation Note다. | **Targeted Cleanup Recommended** — Display 해석을 ‘정성적 분포 확인’과 ‘수치/Type 확인’ 두 단위로 나누되 확인 조건은 Debug Step 옆에 남긴다. 이전 화면에서 관찰한 결과와 현재 계약의 실행 확인 여부를 Validation에서 명확히 나눈다. Mode 0–5 계약, fallback, Scalar→RGB, Shipping 비용 주의는 유지한다. |
| `Chapter08.10_FinalFramwork.md` | Architecture 통합을 왜 확인하는지 → Canonical Interface → 조합 순서 → MI/Debug → Expected Checks → Chapter Summary의 역할이 맞다. Overview 앞에 검증을 두던 과거 문제는 현재 해결되어 있다. | L84–110의 계약·합성 Scope는 빠른 조회에 유용하지만 길다. Fig8_73의 동일한 교정 문단이 L438과 L4099에 반복된다. L3742–3755는 예상값과 Engine 실행을 명확히 구분하는 좋은 구간이다. 그러나 각 Validation의 ‘확인했다’ 문장과 L4115 Complete 표를 읽은 뒤 L4132에서 이번 실행 없음/기본 범위 제한이 나와 증거 범위를 늦게 이해할 수 있다. | **Targeted Cleanup Recommended** — Canonical Interface 뒤 긴 Scope를 명시적 Reference/Scope Note로 묶는다. 같은 Figure 재등장에서는 원래 Reading Note를 회고하고 해당 절의 목적만 새로 설명한다. Validation 시작에 예상 계산/기존 관찰 기록/현재 Engine 실행 증거의 범위를 먼저 밝히고 Complete 표의 한계를 표 앞에도 짧게 둔다. Chapter Summary는 최종 회고로 유지한다. |

### Priority Cleanup Units

#### 1. Introduce the Architecture Terms at the Entry

**정리 단위:** Index `Why a Framework?` L39–41 → 8.1 `From a Single Graph to Modules` L72 → `Material Function as an Implementation Unit` L134–164.

현재도 뒤쪽에서 설명은 충분하다. 문제는 독자가 이름을 먼저 만나고 의미를 나중에 확인한다는 점이다. 하나의 큰 Graph를 수정하기 어려운 문제 뒤에, 계산 일부를 입력·출력이 있는 재사용 단위로 묶는 것이 Material Function이라고 설명한다. 그 결과를 모아 최종 Material 출력으로 연결하는 Master Material의 역할을 이어 설명한다. Module은 논리적 책임이고 Function은 구현 단위라는 현재 구분을 그대로 유지한다.

Multiply/Add/Lerp의 자세한 수학을 Index에 늘리지 않는다. Lerp가 두 결과를 비율로 섞는 합성 연산이라는 짧은 뜻만 먼저 주고 실제 계산은 MatCap/Region 구현에서 설명한다. 앞선 Chapter의 Interpolation 개념과 연결할 수 있지만 Lerp라는 Node 이름을 이미 풀었다고 가정하지 않는다.

#### 2. Separate Figure Reading from Implementation Verification

**정리 단위:** 8.2 `Creating the Function Interface`와 `Basic Implementation Validation`, 8.4의 Reflection Graph/Exponent 비교 Figure 구간. 관련 후속 Caption 정리는 8.3, 8.5–8.10에서도 같은 원칙을 적용한다.

현재 긴 Caption에는 서로 다른 정보가 들어 있다.

1. 원래 Figure에서 실제로 보이는 배선·변수·화면 결과.
2. 현재 문서 계약과 다른 부분 또는 Figure만으로 확인할 수 없는 조건.
3. 독자가 현재 계산을 확인할 Step와 예상값.
4. 이후 재촬영할 때 보여줘야 하는 항목.

이 정보는 모두 필요하지만 한 문단에 합쳐지면 새로 연결할 Node보다 검수 이력이 먼저 눈에 들어온다. Caption에는 1의 관찰을 먼저 두고, 2–4는 **Verification Note**에서 분리한다. Note의 첫 문장은 지금 Figure로 확정 가능한 범위를 말하고, 이어 현재 Step의 확인 항목을 적는다. 불완전한 Figure를 현재 계약의 검증 결과처럼 바꾸거나, 재촬영 필요 안내를 지우는 것은 권장하지 않는다.

8.4의 Exponent 8/32/128 비교는 각 Figure마다 고정 조건을 모두 반복하는 대신 비교 직전에 공통 조건을 한 번 쓰고 각 Caption에서는 해당 지수와 관찰되는 차이를 설명한다. 입력 Normal/Light/View, Material 출력 경로, Camera/Exposure를 고정해야 한다는 조건은 비교 바로 옆에 남긴다.

#### 3. Keep Preconditions Near the Operation

**정리 단위:** 8.3 Depth Comparison, 8.4 Reflection 계산, 8.5 Width/Softness, 8.6 UV/Blend, 8.7 Texture Mask, 8.8 Parameter Lerp, 8.9 Debug Display.

조건을 전부 뒤로 밀면 정확성이 떨어진다. 다음은 본문 또는 Step 직전에 유지한다.

| Operation | Essential Condition to Keep Nearby | Detail Suitable for a Note |
|---|---|---|
| Base Lighting / Specular / Rim | 같은 Space의 nonzero Direction, Unit 조건, Surface→Light/View 방향 규칙 | 다른 Engine 경로의 Node 지원, 예외 입력 자동 보정 여부, 물리적 모델의 긴 범위 설명 |
| Shadow Depth Comparison | 같은 Light Projection·Depth Encoding으로 비교, 수치 예제의 비교 Convention | Reversed-Z의 추가 Convention 설명, Engine Shadow View 명칭의 버전 차이 |
| Rim Smoothstep | 정상 범위 `0<Softness≤Width≤1`, edge 순서 | Width=0/Softness=0 정책과 자동 보정 구현의 미검증 상태 |
| MatCap UV | Normal의 기준/정규화, 현재 Texture와 맞는 축 방향, 여기서 선택한 UV 경로 | Unit Disk의 의미와 Hemisphere 손실, Address Mode·padding·filter 경계 사례 |
| MatCap Blend | Off는 Blend=0, Intensity=0만으로 Off 판정하지 않음, Emission을 Blend 이후 Add | 추가 MI 노출 정책과 다른 합성 정책의 확장 |
| Emission Mask | 현재 Texture Sample의 Scalar Channel, Color/Intensity/Mask 입력 계약 | Compression/Filtering/Mip의 저장값 영향 상세, GI의 조건부 영향 |
| Region Lerp | Parameter 선택과 계산 결과 선택의 구분, 비선형 Parameter의 차이 | Unreal Material Layers 시스템과 실제 Material/Slot 경계 비용 판단 |
| Debug Display | 실제 중간 결과를 분기, Scalar/Vector3 의도, 비교 시 고정 Exposure와 display 변환 범위 | Shipping 제거/branch 비용의 자세한 구현 선택 |

#### 4. Clarify the Evidence in Validation

**정리 단위:** 8.9의 Mode 검증, 8.10 `Final Verification` 및 `Final Verification Checklist`.

8.10 L3742는 ‘식에서 도출한 예상 결과이며 Engine 실행 결과가 아니다’라고 분명하게 말한다. L4132도 Complete는 기본 문서 구현 범위이며 이번 Text Refactoring에서 Engine을 실행하지 않았다고 밝힌다. 이 구분은 이미 있어 보존해야 한다.

다만 그 사이 Module별 설명은 ‘직접 확인했다’, ‘정상적으로 동작한다’라는 완료 문장을 사용하고, 현재 Figure는 재촬영이 필요하다고 안내한다. 새로운 작업의 검증 결과로 오해하지 않게 Validation 시작에서 **예상 계산값**, **기존 구현에서 기록한 관찰**, **현재 계약으로 새로 실행해야 할 확인**을 구분하면 좋다. Complete를 삭제하는 제안이 아니라 Complete의 대상과 근거를 먼저 읽도록 하는 제안이다. 현재 Engine 구현이 틀렸다고 판정한 것은 아니다.

8.0의 준비 완료 표도 동일한 원칙을 적용할 수 있다. 표에 이미 표시된 체크를 독자의 프로젝트가 실제 준비되었다는 결과로 읽히게 하지 않고, 독자가 완료 여부를 확인할 체크리스트임을 명시하면 된다.

### First-use Terminology Evidence

다음 Table은 실제 원본 첫 등장과 설명 위치의 간격을 근거로 한다. Chapter 08에서 새로운 Unreal 구현 역할을 맡는 용어와 acronym을 우선했다. ‘첫 등장’은 제목·목표 목록·Figure 설명도 포함하며, 뒤에 등장하는 충분한 설명은 삭제 대상이 아니다.

| Term | First Appearance and Source Wording | Existing Explanation / Finding | Recommended Treatment |
|---|---|---|---|
| Material Function | `Chapter08_BuildingAnAnimeShader.md` / **Index** L24: - Material Function 기반의 셰이더 아키텍처 | 8.1 L134–136에서 입력·출력이 있는 재사용 단위의 의미를 충분히 설명한다. Index/8.0에서는 이름이 먼저 나온다. | Index Why 문맥에서 재사용 계산 단위의 목적을 한 문장 먼저 설명하고 8.1은 회고→Interface로 이어간다. |
| Master Material | `Chapter08_BuildingAnAnimeShader.md` / **Index** L41: 각 Module은 명확한 책임을 가진다. 여러 Module이 N/L/V와 Material Data를 공유하고, Master Material은 필요한 계산 결과를 Multiply·Add·Lerp로 결합한다. Material Function을 분리하는 것만으로 실행 비용이나 Renderer 데이터 접근 문제가 해결되지는 않는다. | 8.1 L164/L171에서 Module 결과 조합 역할을 설명한다. 첫 문장은 N/L/V·Multiply·Add·Lerp·비용 Caveat를 함께 쓴다. | 처음 등장하는 문장을 조합 역할과 비용 Scope Note로 나눈다. |
| Lerp | `Chapter08_BuildingAnAnimeShader.md` / **Index** L41: 각 Module은 명확한 책임을 가진다. 여러 Module이 N/L/V와 Material Data를 공유하고, Master Material은 필요한 계산 결과를 Multiply·Add·Lerp로 결합한다. Material Function을 분리하는 것만으로 실행 비용이나 Renderer 데이터 접근 문제가 해결되지는 않는다. | 8.6 L4742에는 Linear Interpolation과 A/B/Alpha 역할 설명이 있다. 8.1 Data Flow L219에서 이미 연산명이 쓰인다. | 첫 합성 흐름에서 Full Name과 두 결과를 비율로 섞는 역할을 짧게 먼저 알려준다. 앞선 Interpolation 설명과는 회고로 연결한다. |
| Blueprint | `Chapter08.0_PreparingTheASFProject.md` / **Creating the Project / Creating a New Project** L191: \| Project Type \| Blueprint \| | 8.0 L217에서 테스트 환경/Utility에만 쓴다는 역할을 밝히지만 UI Project Type 표가 먼저다. Chapter04에서는 Runtime Data Flow의 이름으로도 나온다. | 새 사전 정의보다 이 Project Type이 실습에서 쓰이는 역할을 선택 Step 전에 짧게 설명한다. |
| RHI | `Chapter08.0_PreparingTheASFProject.md` / **Project Settings Verification / Recommended Settings** L353: \| Platforms → Windows \| Default RHI \| DirectX 12 \| | Recommended Settings와 Checkpoint에 acronym이 반복되며 이 파일에는 Full Name/목적을 푸는 문장이 없다. | 공식 UI 명칭과 Full Name을 확인한 뒤 설정 표 앞에서 Engine와 Graphics API 선택의 관계를 간단히 설명한다. Audit 단계에서 지원 범위를 새로 단정하지 않는다. |
| SM6 | `Chapter08.0_PreparingTheASFProject.md` / **Project Settings Verification / Recommended Settings** L358: \| Platforms → Windows \| D3D12 Targeted Shader Formats \| SM6 Enabled \| | 8.0 L384의 Shader Model 6 설명은 첫 Settings 표 뒤에 있다. | L384의 Full Name/목적을 표 처음 등장 옆에 짧게 앞당긴다. |
| TSR | `Chapter08.0_PreparingTheASFProject.md` / **Project Settings Verification / Recommended Settings** L347: *Figure 8-4. 문서가 목표로 하는 Project Settings. 하단 표의 “기본값”은 보편적인 Engine 기본값이나 현재 프로젝트의 검증 결과를 뜻하지 않는다. 실제 버전과 Template에서 값을 확인한다. ④의 Mobile TAA와 Default Settings의 Desktop TSR은 서로 다른 대상이며, 본 실습의 목표는 후자이다. 이 설정 화면은 ASF Module 구현이나 Material Function 합성의 증거가 아니다.* | Figure Reading Note의 Desktop TSR이 먼저이고 L357/L383에 Temporal Super-Resolution과 역할이 나온다. | 본문 표에서 먼저 이름과 용도를 설명한 다음 Figure의 대상 차이를 회고한다. |
| Material Parameter Collection | `Chapter08.0_PreparingTheASFProject.md` / **Asset Naming Convention / Standard Prefix** L686: \| Material Parameter Collection \| `MPC_` \| `MPC_GlobalParameters` \| | Naming Prefix 표에서 Asset Type과 MPC_를 처음 보며 실제 Light Adapter 사용은 8.2 L604의 조건부 구현 설명에 나온다. | Naming 표에서는 공용 Parameter 묶음이라는 역할만 짧게 설명하고 실제 사용 조건은 8.2에 남긴다. 특정 Asset이 생성·검증되었다고 추가하지 않는다. |
| MatCap | `Chapter08_BuildingAnAnimeShader.md` / **Index** L85: \| 8.6 \| [MatCap](<./Chapter08.6_MatCap.md>) \| | Index Chapter Structure의 링크에서 먼저 만난다. 8.6 첫 본문 L5는 여러 계약 조건을 함께 쓰고, Full Name Material Capture는 L474에서 풀린다. | Index/8.1에서는 후속 Module임을 preview하고 8.6 첫 Why에서 Full Name과 저장된 Appearance를 Normal로 조회하는 목적을 즉시 설명한다. |
| Texture Object | `Chapter08.6_MatCap.md` / **8.6** L5: MatCap은 View-space Normal 기반 Appearance Lookup이며 실제 Environment Reflection/IBL 계산과 다르다. 이 예제는 Camera Basis를 공유하는 투영 근사로, Perspective 화면의 모든 Pixel View Ray를 정확하게 사용하는 구면 Reflection Mapping과 같지 않다. Function Input은 World-space Normal과 Texture Object이고 Output은 Linear RGB MatCapResult이다. | 첫 문단은 Function Input 계약으로 쓰고 본격 Resource/샘플값 구분은 L3817 이후에 나온다. | 처음 resource 입력을 설명할 때 Chapter04의 Texture Resource와 읽은 값의 차이를 회고한다. UV 계산 앞에 긴 Node 사전을 넣지 않는다. |
| HLSL | `Chapter08.10_FinalFramwork.md` / **Final Framework Overview / Extension Direction** L324: Custom HLSL | 이 파일의 첫 등장은 후속 학습 범위를 표시한 fenced Data Flow의 Custom HLSL이다. 이번 Chapter02 Rewrite의 2.11 L6840에는 HLSL의 Full Name과 GPU Shader를 작성하는 언어라는 역할이 이미 정의되어 있다. | 새 acronym으로 재정의하지 않는다. Chapter02의 Shader 언어를 후속 학습에서 직접 사용할 수 있다는 관계만 짧게 회고한다. 사용자가 당장 구현해야 할 Step처럼 보이게 하지 않는다. |
| Substrate | `Chapter08.10_FinalFramwork.md` / **Final Master Material Architecture / Architecture Scope** L1006: 이 기반이 있기 때문에 이후 Unreal의 기본 Material System, Shading Model, Substrate, Custom HLSL 등을 다룰 때도 단순히 기능 사용법만 아는 것이 아니라, 그 내부에서 어떤 Data와 역할이 연결되는지를 더 명확하게 해석할 수 있다. | 향후 학습 범위에서 이름을 먼저 열거하고, L3442 이후 Evaluation Scope에서 자세히 연결한다. 현재 교육용 Graph의 필수 지식은 아니다. | 첫 preview에 이론을 늘리지 않고 후속 Unreal Material 학습의 대상임을 짧게 설명하거나 뒤의 Evaluation Scope로 연결한다. |


#### Terms Already Explained or Correctly Introduced

| Term / Group | Current Evidence | Treatment |
|---|---|---|
| Unlit / Emissive | Chapter01·04에서 의미를 소개한다. 8.2 L539는 `M_ASF_Master`의 Unlit→Emissive 출력과 Viewport Lit의 차이를 한 문단에서 설명한다. 8.7 L21–29는 출력 pin과 논리적 Emission Contribution의 구분을 문제로 먼저 설명한다. | Chapter08의 구현 역할을 회고하면 충분하다. ‘처음 정의가 없다’는 이유로 모든 절에 재정의하지 않는다. 8.2만 출력 연결과 화면 확인을 두 단계로 나누는 편이 좋다. |
| Visibility / Occlusion | 8.3 L128부터 실제 Light 도달 관계를 풀고 L430 이후 Visibility/Occlusion 개념을 분리해 설명한다. Chapter05–07의 Visibility 설명과도 연결된다. | 좋은 Concept-before-Implementation 사례이다. 수동 Scalar 입력과 Renderer의 Pixel별 Visibility를 구분하는 현재 경계를 유지한다. |
| Shadow Map / Shadow Ray / PCF | 8.3은 광선 도달 문제, 저장한 Depth 비교, 비교 결과 평균의 목적을 단계적으로 설명한다. PCF는 L3307에서 Percentage-Closer Filtering으로 풀린다. | 재정의/풀네임을 기계적으로 더하지 않는다. Bias의 첫 주의문만 의미를 보충한다. |
| Normal / View Space / UV / Remap | Chapter01–04의 용어이다. 8.6은 Normal XY와 UV Remap의 목적을 사례와 단계로 설명한다. | 이전 Chapter와 짧게 연결하고 MatCap Lookup에 특유한 입력·출력만 다시 설명한다. |
| HDR / Bloom / Exposure / Tone Mapping | 8.7에서 출력값/보이는 밝기/주변 효과의 문제를 나누고 실제 실험으로 연결한다. 앞선 Rendering Pipeline Chapter와도 연결된다. | 개념별 Why를 유지한다. 검증 조건이 길다는 이유로 설명 자체를 Reference 뒤로 보내지 않는다. |
| Scalar / Vector3 / Unit Vector / Dot / Smoothstep | Chapter03–04와 앞선 구현에서 충분히 배운다. 8.9의 Scalar→RGB 표시와 8.5 Width/Softness 계약은 이 실습에 새로 적용되는 역할이다. | 긴 첫 정의를 반복하지 않고 데이터 의미와 이 연산의 조건을 회고한다. |
| If / Static Switch / Compile Time | 앞선 Material Parameter 설명과 이어지는 8.9 L3274–3278의 구현 비용 구분은 필요한 Note다. | DebugMode=0이 비용을 자동 없앤다는 잘못된 결론을 막는 현재 내용을 보존한다. |

### Repetition and Role Alignment

#### Repetition Worth Preserving

- **Implementation Reference**는 Node를 다시 만들기 위한 두 번째 강의가 아니라 최종 Interface/Formula/계약을 빠르게 확인하는 곳이다. 현재 8.2·8.5–8.7·8.9의 명칭과 배치를 유지한다.
- **Key Takeaways**는 해당 Module에서 배운 관계와 주의점을 회고한다. 모든 Subsection에 추가하거나 모든 Reference를 Key Takeaways로 바꾸지 않는다.
- **Chapter Summary**는 8.10에서 전체 구현이 어떻게 합쳐졌는지를 정리하는 역할이다. Overview나 Canonical Interface와 동일한 내용이 조금 겹친다는 이유로 삭제하지 않는다.
- **Checkpoint/Verification**는 준비 상태나 결과 확인을 위해 필요하다. Why 설명과 같은 형식으로 바꾸지 않는다.
- 같은 I/O가 소개, 구현 연결, 최종 Reference에 다시 나오는 것은 역할이 다르다. 수식과 계약을 줄여야 한다는 결론으로 연결하지 않는다.

#### Repetition Suitable for Cleanup

- 8.0 Organization와 Content Browser에서 반복되는 폴더 분리의 장점은 원칙 설명과 실제 폴더 구성 단계로 구분한다. Asset Reference 조건은 이동/배포 Step 가까이에 남긴다.
- 8.3 Texture/Pixel/Texel의 기존 기초 정의와 Shadow Map/Lightmap 비교는 첫 위치에서 의미를 설명한 뒤, 후속 위치에서는 Shadow Lookup에 필요한 차이만 회고한다.
- 8.4 Exponent 비교의 동일한 검증 조건은 한 번 명시하고 각 Figure에서는 결과 차이를 읽는다.
- 8.7 Emissive pin의 Engine 출력 범위는 처음 설명을 기준으로 후속 구현 Note가 회고한다. Emission만 끄는 것과 최종 화면의 모든 Bloom/GI가 사라지는 것의 구분은 유지한다.
- 8.10 Fig8_73의 동일한 긴 계약 교정은 첫 위치에서 모아 설명하고 Architecture Validation에서는 필요한 항목을 회고한다. 기존 Figure를 현재 실행 증거로 승격하지 않는다.

### Suggested Note Placement

| Chapter | Keep in Main Flow | Note Placement and Reason |
|---|---|---|
| 8.0 | 실습 환경을 고정해야 하는 이유, 실제 Project 생성·Settings 확인 순서 | Target Environment의 지원 조합/현재값 미확인은 설정 확인 앞의 짧은 Scope Note로 유지한다. Settings 값의 목적을 먼저 알 수 있도록 UI acronym 설명과 분리한다. |
| 8.1 | 큰 Graph의 문제, 재사용 Function, Master 조합, Branch Data Flow | Function 분리가 실행 비용이나 Renderer 접근을 보장하지 않는다는 조건은 Architecture Principles 뒤의 Scope Note로 짧게 연결할 수 있다. |
| 8.2 | Normalize/Dot/Saturate/Color 곱의 데이터 흐름, Unlit 출력 테스트 | 기존 Figure 배선 차이와 Exposure·Viewport 해석을 Verification Note로 나눈다. Forward 전용 Adapter 조건은 현재처럼 기본 명시 입력 뒤 별도 경로로 유지한다. |
| 8.3 | Occlusion/Visibility 의미, 같은 Depth 기준의 비교, Bias/Filtering 필요 | Reversed-Z Convention, Engine View 명칭, 촬영 변수의 미확인 범위를 Technical/Verification Note로 분리한다. Numeric Comparison 직전의 전제는 그대로 둔다. |
| 8.4 | 단위 방향, Normal projection과 R의 구성, V와 비교, Power 의미 | 기존 Graph의 raw/normalized L 차이, remapped RGB와 실제 R/Scalar 차이, Lit 화면만으로 확정할 수 없는 점은 Step 옆 Verification Note로 묶는다. |
| 8.5 | Silhouette 관계, Power Prototype의 한계, Width/Softness 최종 구현 | Prototype/최종 버전 구분과 경계 입력 정책, 기존 Capture 계약 차이는 Interface·Parameter Step 옆 Implementation/Verification Note로 나눈다. |
| 8.6 | View Normal→XY→Remap→UV→Sample→Blend | Full Perspective 근사 범위, Texture 축 검증, Unit Disk/Address Mode 세부를 각각 해당 계산 뒤 Note로 둔다. Intensity/Blend Off 조건은 합성 본문에 남긴다. |
| 8.7 | Emission Contribution과 출력 pin의 차이, HDR/Bloom/Exposure/Mask의 실험 | GI 영향의 Engine 조건, Texture 저장/압축/필터 조건, 캡처 설정 미확인은 관련 실험 Step 뒤 Note로 둔다. Mask=0의 계산 의미는 본문에 남긴다. |
| 8.8 | Region Parameter 선택과 실제 결과 차이 | Unreal Material Layers와의 차이, Material/Slot 경계 판단은 후반 Scope/Boundary 구간에 둔다. Specular Intensity를 Function 밖에서 적용하는 계약은 구현 Step에 남긴다. |
| 8.9 | 중간 Data를 그대로 선택하는 Mode와 Selector, 출력 Type | 정성 분포/수치 검증 한계, If와 Compile-Time 제거 비용, 기존 Figure 계약 차이를 목적별 Note로 나눈다. |
| 8.10 | 합성 순서, Canonical Interface, Expected Checks, 최종 회고 | 공통 Scope 계약은 표 뒤에, 완료 표시의 증거 범위는 Validation 시작과 Checklist 직전에 둔다. |

### Figure Review

이번 Audit은 Caption의 학습 흐름과 증거 범위를 검토했다. Figure 이미지 생성, 편집, 교체, 경로 또는 번호 변경은 수행하지 않았다.

현재 Caption의 재촬영 필요·미확인 설정·다른 배선 설명은 정확성을 지키기 위한 중요한 정보이다. 제안은 이 내용을 삭제하는 것이 아니라 관찰/조건/확인/재촬영의 역할로 읽히게 하는 것이다. 긴 Caption 중 일부는 짧은 본문 설명으로 이어지고 그 다음 Verification Note가 나오면 따라가기 쉽다.

실제 Unreal 화면을 새로 준비하는 후속 작업이 진행된다면 다음의 현재 경계를 보존한다.

- 단순한 Color View는 원래 Scalar, Vector, Unit 조건의 정량 검증을 자동 증명하지 않는다.
- 수동 Visibility는 실제 Renderer Shadow를 수집한 결과가 아니다.
- MatCap Blend=1과 Intensity=0의 의미가 다르며, 현재 조합 순서에서 Blend 뒤의 Emission은 유지된다.
- Rim의 현재 유효 입력 범위와 최종 Interface를 캡처한다.
- Debug에서 Scalar Mask와 RGB Contribution, Intensity 적용 전/후의 분기 위치를 구별한다.
- Presentation Exposure와 수치 확인용 Fixed Exposure를 구분한다.

### Remaining Review Items

1. RHI 등 새 Full Name과 Engine-specific 역할을 후속 편집에 추가할 경우 공식 명칭을 확인한다. HLSL은 이번 Chapter02 Rewrite에서 이미 정의되었으므로 Chapter08에서는 회고만 필요하다. 이번 Audit은 구현 지원 조합을 새로 확인한 문서가 아니다.
2. 완성된 Chapter01–05의 첫 용어 설명을 대조했다. 후속 Chapter08 편집은 그 설명을 바탕으로 필요한 회고만 조정한다. Normal/UV/BRDF/Unit Vector를 새 용어처럼 매번 다시 설명하지 않는다.
3. ‘기존 구현에서 확인한 사실’과 ‘현재 계약으로 새로 확인할 실행 결과’의 차이를 8.9–8.10 Validation 편집에서 특히 주의한다. 기존의 완료 기록을 근거 없이 부정하거나 새로운 실행 결과를 만들어 쓰지 않는다.
4. Figure 재촬영은 별도 작업이다. Audit에 기록된 스타일 정리만으로 미확인 Engine 설정/배선/출력 증거가 해결되었다고 판단하지 않는다.

### Preservation Check

총 12개 원본의 SHA-256을 작업 초기 원본 해시 목록과 대조했다. **12/12 동일**이며 Chapter08 파일을 수정하지 않았다. 자세한 대조 결과는 아래 파일별 해시와 보존 대조 결과로 확인했다. 모든 Chapter08 Figure 역시 이번 Audit에서는 읽기 대상으로만 취급했다.


---

## Chapter 09 — Rendering Debug and Optimization

### Strengths and Workflow to Preserve

Introduction L11–25는 현재 Frame을 제한하는 원인을 찾아야 한다는 문제에서 `Measure → Identify Bottleneck → Isolate Cause → Optimize → Measure Again`을 제시한다. 9.1 L111–171은 FPS의 비선형 변화와 Frame Time(ms)을 60→50 FPS, 30→20 FPS의 친숙한 비교로 풀며, Baseline(L189–195)과 동일 조건 비교로 연결한다. 이 측정 중심 흐름은 Chapter 05처럼 이론 모델 중심으로 바꾸면 안 된다.

9.2는 Game/Render/GPU의 작업과 Frame overlap을 설명하고 단순 합산을 금지한다(L605–674). CPU/GPU 판단 후 원인을 더 좁히는 흐름은 L1092–1183까지 유지된다. 9.3은 Triangle/Vertex, Skinning, 작은 Triangle의 효율, Screen Size/LOD를 비교하며 9.4는 화면 면적과 반복 처리, 9.5는 Pixel당 계산, 9.6은 CPU의 준비/제출과 State, 9.7은 Detail/Visibility, 9.8은 질문별 도구, 9.9는 이를 실제 판단 순서로 종합한다. 각 절의 Practical Analysis와 선택적 Key Takeaways는 구별된 Cost를 Workflow에 연결한다.

현재 보강된 정밀도는 특히 좋다. 가장 큰 `stat unit` 값은 첫 조사 대상이라는 조건(9.2 L652/9.8 L6640–6654), GPU Event의 계층/중첩(9.8 L6584), 실제 GPU Timing과 Shader Complexity 색상의 차이(L7053–7071), LOD/Culling을 별도 실험으로 분리(L6351–6365), Hair 전체 Off가 여러 Cost를 동시에 바꾼다는 범위(L7444), 반복 측정/변동/Build 환경(L7433–7442, L7481–7524)이 잘 보존되어 있다. 문체 정리에서 이 정밀도를 줄이지 않는다.

### First-Use Terminology Evidence

| Term | Actual First Appearance in This Chapter | Source Evidence | Assessment / Specific Recommendation |
|---|---|---|---|
| Draw Call | Introduction; L5 | 실제 Rendering Performance는 Geometry, Material, Shader, Transparency, Draw Call, Lighting, Animation, Post Process 등 여러 요소가 동시에 영향을 주면서 결정된다. | 새 01.11에서 정의됨. 09 도입의 명칭은 재정의 누락이 아니라 recall 부재이다. CPU가 그리기 작업을 준비/제출하는 연결을 짧게 회상하고 9.6의 비용 구조 설명은 유지한다. |
| Frame Time | Introduction; L11 | **현재 Frame Time을 실제로 제한하고 있는 원인이 무엇인지 찾는 것** | 한 Frame의 처리 시간이라는 본장 정의는 9.1 L113에 있다. 도입 L11에는 짧은 의미만 붙여 주면 된다. FPS 비교 및 1000/FPS 관계는 현재 순서를 유지한다. |
| FPS | Introduction; L15 | 예를 들어 같은 낮은 FPS라도 원인은 전혀 다를 수 있다. | 새 01.2에서 Frames Per Second와 역할이 정의됨. 09는 짧은 회상 뒤 9.1의 비선형 비교와 ms 중심 분석으로 확장한다. acronym 재정의 누락으로 판정하지 않는다. |
| CPU / GPU | Introduction; L17 | 어떤 경우에는 CPU가 많은 Object와 Draw Call을 처리하느라 늦을 수 있고, 다른 경우에는 GPU가 복잡한 Pixel Shader나 Overdraw를 처리하느라 시간이 오래 걸릴 수 있다. | 새 01.1에서 Full Name/역할이 정의됨. 다시 하드웨어 정의를 추가하지 않는다. 현재 장에서는 어느 작업이 Frame을 제한하는지 의미를 확장한다. |
| Overdraw | Introduction; L17 | 어떤 경우에는 CPU가 많은 Object와 Draw Call을 처리하느라 늦을 수 있고, 다른 경우에는 GPU가 복잡한 Pixel Shader나 Overdraw를 처리하느라 시간이 오래 걸릴 수 있다. | 새 01.10에서 같은 화면 위치의 반복 Surface 계산이라고 정의됨. 09의 상세 정의는 9.4 L2391이다. 도입에는 01의 반복 계산을 짧게 회상하고 실제 실행/Pass/Depth 조건은 9.4에서 유지한다. |
| Bottleneck | Introduction; L19 | 또 Geometry가 매우 많아 보여도 실제 Bottleneck은 Pixel Cost일 수 있고, 반대로 단순한 화면처럼 보여도 Draw Call이나 Shader Cost 때문에 Performance가 떨어질 수 있다. | L11의 현재 Frame을 제한하는 원인이라는 문제 설명과 연결되지만 영어 이름은 L19에 붙는다. L11의 의미와 영어 이름을 함께 연결하면 새로운 사전 항목 없이도 읽힌다. |
| CPU Bound / GPU Bound | Exact label absent | 정확히 이 표현은 본문에 없다. | 이 정확한 명칭은 없다. 본문은 CPU/GPU Bottleneck을 사용한다. 9.2 L688/L742에서 각각 전체 Frame을 제한하는 상태를 정의한다. 영어 동의어를 새로 강제 추가할 필요가 없다. |
| Profiling | 9.1 Why Optimization Starts with Measurement; L173 | 따라서 Profiling과 Optimization에서는 | 9.1 L173에서 먼저 사용하며 9.8까지 도구 목적을 점진적으로 설명한다. 처음에 어떤 작업이 시간을 쓰는지 기록/분석한다는 행위를 한 문장으로 연결하면 초기 용어 진입이 편해진다. |
| Baseline | 9.1 Why Optimization Starts with Measurement; L189 | ### Build a Baseline First | 제목 L189 뒤 L193–195에서 변경 전 Performance 상태라는 의미를 즉시 설명한다. 정의와 Why가 충분하다. 같은 조건의 Before 기록이라는 목적을 현재대로 유지한다. |
| RHI | 9.1 Why Optimization Starts with Measurement; L252 | Engine Version, Build Configuration, Editor/Standalone/Packaged 실행 방식, Hardware, RHI, Scene, Camera를 기록한다. Output Resolution뿐 아니라 Internal Rendering Resolution, Screen Percentage, Dynamic Resolution, Scalability, Anti-Aliasing, Light/Shadow 설정을 고정한다. VSync와 Frame Cap의 상태도 기록하여 대기 시간을 실제 처리 비용으로 오해하지 않도록 한다. | 9.1 L252의 측정 조건에 처음 나오고 Full Name/역할은 9.6 L4502, 9.8 L6841에 있다. 조건 목록 첫 사용에 Engine 명령과 Hardware 사이 연결 계층이라는 짧은 뜻/Full Name을 연결할 수 있다. 깊은 Thread 구조는 9.6/9.8에 남긴다. |
| VSync / Frame Cap | Introduction; L31 | *Figure 9-01. 측정→병목 후보 분리→원인 분석→한 변수 수정→재측정의 기존 합성 도식. 42→120 FPS 등의 수치는 측정 출처가 없는 예시이며 ASF 실측 성과가 아니다. 그래프 후반은 GPU 약 21 ms가 CPU 표시값보다 길므로 CPU 병목 Label은 해당 수치와 맞지 않는다. Thread/GPU 시간은 겹칠 수 있어 단순 합산하지 않으며 실제 병목은 동기화·대기·VSync/Frame Cap을 함께 확인한다. 이미지 내부 하단의 Fig9_02 표기도 이 Figure의 일부를 뜻하는 잘못된 번호다. 장면/Character 이미지 출처 확인 전에는 원본을 보존하며, Before/After 품질 비교의 실증 자료로 사용하지 않는다.* | 첫 사용은 Figure 9-01 L31이다. 실행 지연/제한을 조사해야 하는 이유는 9.1 L252와 9.2 L652에서 나오나 처음 이름 자체는 풀리지 않는다. 대기/표시 제한 관련 조건이라는 즉시 의미와 acronym 뜻을 붙이고 대기≠실제 처리 비용 조건은 본문에 남긴다. |
| Game Thread | 9.1 Why Optimization Starts with Measurement; L81 | 반대로 CPU의 Game Thread가 Bottleneck인 상황에서 Shader Instruction을 줄이더라도 CPU가 계속 Frame을 제한한다면 전체 Performance에는 큰 변화가 없을 수 있다. | 9.1 L81에서 앞서 쓰고 9.2의 역할 설명에서 확장한다. CPU에는 게임 상태 계산과 Rendering 명령 준비가 있다는 짧은 예고를 붙이면 좋다. 01의 CPU/GPU 설명 전체를 반복하지 않는다. |
| Render Thread | 9.2 CPU vs GPU Bottleneck; L469 | Render Thread | 9.2 도입의 CPU 작업 분류에서 이름을 제시하고 L543 이후 Rendering 명령을 준비하는 역할을 풀어 설명한다. Game/Render를 독립 하드웨어라고 읽지 않도록 현재 Thread 관계를 유지한다. |
| LOD | 9.3 Geometry Cost; L1235 | LOD | 새 01.12에서 Level of Detail과 목적을 예고하며 09는 9.3 L1597–1599 및 9.7에서 깊이를 더한다. 9.3 최초 목록에는 이전 장 recall만 붙인다. Full Name 누락으로 재정의를 요구하지 않는다. |
| Screen Coverage | 9.3 Geometry Cost; L1568 | High Screen Coverage | 첫 사용은 9.3 L1568의 Data Flow이며 명시 정의는 9.4 L2208이다. 01의 Raster Coverage와 연결해 화면에서 차지하는 넓이라는 의미를 도식 직전에 짧게 회상한다. Screen Size/거리와 구별한 9.7의 설명은 유지한다. |
| Shader Complexity | 9.4 Pixel Cost and Overdraw; L2335 | Pixel Shader Complexity | 첫 사용은 9.4 L2335의 개념식이다. 9.5 L3204는 계산량의 의미이며 View는 9.5 L3896–3923에서 별도로 설명한다. Shader의 계산 복잡도와 특정 Unreal View Mode를 같은 의미로 읽지 않도록 첫 도구 사용에 구분을 남긴다. |
| State Change | 9.6 Draw Call and Rendering State Cost; L4565 | 처럼 Rendering State가 계속 달라지면 더 많은 State Change와 Resource Binding이 필요할 수 있다. | 9.6 L4565에서 상태 변경 원인과 함께 사용하고 L4573에서 즉시 뜻을 설명한다. 먼저 A→A와 A→B 예시를 제공하는 흐름이 좋으며 큰 변경 필요 없다. |
| Culling | 9.6 Draw Call and Rendering State Cost; L4238 | GPU-driven Rendering에서는 Culling이나 Indirect Draw 준비의 일부가 GPU에서 이루어질 수도 있다. 따라서 아래 흐름은 기본 설명이며 모든 Renderer의 작업 분배를 고정한 규칙은 아니다. | 새 01.6의 Frustum Culling에서 정의됨. 09는 9.6 L4238/9.7로 확장한다. 9.7 L5366에 View/Pass별 제외와 Shadow/Reflection 예외가 핵심으로 들어 있다. 이 범위 조건을 Note로만 숨기면 안 된다. |
| Quad Overdraw | 9.8 Unreal Engine Debug and Profiling Tools; L6544 | Quad Overdraw | 9.8 L6544–6545에서 답하는 질문을 먼저 제시하고 L7077부터 상세 설명한다. 문제→도구→2×2 예시는 좋다. L7079의 Helper Invocation/Wave/Warp를 한꺼번에 소개하는 밀도만 분리한다. |
| Helper Invocation / Wave / Warp | 9.8 Unreal Engine Debug and Profiling Tools; L7079 | 일반적인 Raster Pixel Shading에서는 화면 미분 계산 등을 위해 2×2 Pixel Quad와 Helper Invocation을 사용한다. 이 Quad는 더 큰 실행 단위인 Wave/Warp와 같은 개념이 아니다. | 9.8 L7079에서 함께 처음 나온다. 실제 덮지 않은 Pixel의 계산을 왜 돕는지 2×2 그림으로 먼저 설명하고 보조 계산 이름을 붙인다. Quad≠Wave/Warp 및 Helper가 결과를 기록하지 않는다는 정확한 조건은 보존한다. |

### Measurement Condition Placement

| Evidence | Reading Assessment | Specific Recommendation | Precision That Must Stay Visible |
|---|---|---|---|
| Introduction L11–25 | Frame Time/Bottleneck/Overdraw 이름이 자세한 절보다 먼저 나오지만 앞 장의 기초와 현재 원인 질문이 있다. 독립 glossary 추가보다 짧은 회상이 적절하다. | **P1.** 처음의 한 문단에 Frame 처리 시간/진행을 제한하는 부분/같은 화면 위치 반복 처리의 목적을 자연스럽게 연결한다. 9.1 및 9.4 상세 설명을 앞으로 모두 이동하지 않는다. | Cost 존재≠Bottleneck; CPU/GPU 구분은 원인 확정이 아닌 분석 시작. |
| 9.1 L252–254, Measurement Conditions | Build/실행 방식/Hardware/RHI/Scene/Camera→Output/Internal Resolution/Screen Percentage/DynRes/Scalability/AA/Light/Shadow→VSync/Cap→Compilation/Streaming/Warm-up/분포/최초 실행/한 변수/Exposure가 두 문단에 들어 있다. 이유는 L256부터 쉽게 설명된다. | **P1.** “비교 기준을 기록하고 한 변수만 바꾸며 준비 후 반복 측정한다”는 목적을 먼저 말한다. Scene/Camera/Resolution/설정 고정, 한 변수, 반복/대기 분리는 본문에 남긴다. 전체 설정 항목/기록 절차를 `Measurement Protocol` 표나 named Note에 나누어 모두 보존하고 본문에서 비교 전에 확인하도록 연결한다. | Output와 Internal Resolution 별도; Frame Cap/VSync 상태 기록; 실제 작업과 대기 분리; 준비/반복/변동; Fixed Exposure 품질 비교. 필수 조건을 모두 접힌 Note 안으로 숨기지 않는다. |
| 9.2 L642–674 | overlap 설명 뒤의 조건이므로 무조건 너무 이르다고 볼 수 없다. 다만 RHI/Queue/의존성/대기/동기화의 새 관계가 한 문단이다. | **P2.** “합산하지 않는다/큰 stat 값은 후보/실제 실행과 대기를 분리”는 본문에 유지한다. 추가 Queue/Thread 배치 예만 `Timing Interpretation Note`로 나눈다. 뒤의 7/8/17 ms 예시 바로 전에 처리 우세 가정을 남긴다. | 대기보다 실제 처리가 우세한 예시 가정; 의존 경로; Frame 진행과 각 값의 관계; 최고값만으로 원인 확정 금지. |
| 9.3 L1455 및 L1852–1873 | UV seam/hard normal/cache/skinning/pass 범위는 실제 cost 해석의 이유이다. Pass 표의 중첩/Geometry 포함 범위 조건은 숫자 적용 전 꼭 필요하다. | **P2.** Vertex 증가/중복 처리의 상세 예만 Note로 분리할 수 있다. Pass 표 앞뒤 조건과 1.5/5 ms, 0.6 ms 비교의 해석은 본문에 유지한다. | 비중첩 Event라는 가정; Shadow/Translucency에도 Geometry 처리 포함; Geometry를 별도 합산 메타 항목으로 오해하지 않음. |
| 9.4 L2421–2470, Opaque/Masked/Translucent | 같은 겹침이라도 실행이 다른 이유를 배우기 위한 핵심 비교이다. 구현 Caveat처럼 보인다는 이유로 전체를 Note로 옮기면 Overdraw 오해가 생긴다. | **유지 우선.** 기본 Blend/Depth/Pass 관계 표와 Layer 예시는 본문에 유지한다. 개별 Renderer의 예외 설정만 Implementation Note 후보이다. | 겹침 수≠실제 Shading 횟수; Early Depth/Depth Test; Opaque/Masked/Translucent 분리; 실제 Pass 확인. |
| 9.5 L3504–3520, L3548–3565 및 L3912–3923 | Static/Dynamic/Branch 조건과 실제 Timing 차이는 개념 설명에 붙어 있으며 반드시 필요한 적용 조건이다. | **유지 우선.** 04의 Static Parameter를 짧게 회상하고, divergence 실행 단위의 세부만 Note로 분리한다. 모든 조건을 뒤로 밀지 않는다. | 출력 0≠자동 연산 제거; Runtime/Static 차이; Branch 이름만으로 비용 판단 금지; Instruction Count/Complexity View≠GPU 시간. |
| 9.6 L4236–4238, L4480–4516 | CPU-driven 기본 모델을 확장하는 GPU-driven/RHI 설명이다. Draw Call 직관 이전에 약간의 범위 예외가 나오나 L4190의 단위 설명은 이미 제공된다. | **P2.** 기본 제출 흐름 뒤 GPU-driven 작업 분배/Platform Thread 구조를 `Command Submission Note`에 배치할 수 있다. RHI의 Full Name/역할은 첫 사용에서 짧게 연결한다. | CPU에도 준비/제출 cost가 존재; Draw 수/Render Thread 값만으로 원인 확정하지 않음; 모든 Renderer의 고정 작업 분배가 아님. |
| 9.7 L5366, L5699–5737 및 L6351–6365 | View/Pass 범위, conservative occlusion, LOD vs Culling 별도 실험은 현재 적용의 핵심이다. | **유지 우선.** Bounds/시간 지연의 상세 구현 설명만 Note 후보이다. Main View 밖의 Shadow/Reflection 기여와 Object CPU update 유지 조건은 본문/요약에 유지한다. | Camera 밖≠모든 Pass 제거; Culling≠Object 삭제/CPU update 중지; LOD 한 변수 비교; GPU 변화≠Geometry 원인 단독 증명. |
| 9.8 L6580–6584, Implementation and Verification Note | named Note가 이미 있으나 첫 `stat unit` 예시보다 앞서 Tool 지원/Version/Build/Platform/RHI/Renderer, Event overlap, MF_DebugView/Runtime 0를 모두 설명한다. 이후 각 도구 본문도 일부 반복한다. | **P2.** 이 절 입구에는 “지원/출력은 사용 환경 확인; 도구는 관찰 범위가 다름”을 짧게 유지하고, Tool별 지원/Trace 상세는 해당 사용 직전에 배치한다. MF_DebugView의 계산 확인/Timing 차이는 Chapter 08 recall Note로 묶을 수 있다. | 명령/실행 검증 미완료 범위; MF_DebugView≠Timing; Mode 0≠Compile-time 제거; GPU Event 무조건 합산 금지. |
| 9.8 L7077–7116, Quad Overdraw | 작은 Triangle의 비효율이라는 문제부터 시작하므로 좋다. L7079에서 2×2/미분/Helper/Wave/Warp 이름을 함께 소개해 밀도가 상승한다. | **P2.** Covered/Helper 2×2 예시로 필요한 보조 계산을 먼저 설명한 뒤 이름을 붙인다. 실행 단위 비교는 `Pixel Quad Note`로 분리한다. | Quad≠Wave/Warp; Helper는 Covered Sample처럼 Render Target 결과를 쓰지 않음; 도식으로 실제 시간 비율을 계산하지 않음. |
| 9.8 L7433–7444와 9.9 L7776–8685 | 기록 표/한 변수/Before-After와 최종 종합은 길지만 실제 행동을 알려 준다. 9.9의 Cost별 회상은 새로운 정의라기보다 판단 질문의 재사용이다. | **유지 우선.** 요약 단계와 판단 질문을 먼저 읽을 수 있게 유지한다. 비용별 장문 회상을 선택적 Reference로 묶는 편집은 가능하나 Data Flow/수치/조건/품질 확인을 삭제하지 않는다. | 실측을 예상값으로 채우지 않음; 새 Shader 준비 후 측정; 여러 비용이 변하는 Hair Off는 영역 분리용; 품질/반복/변동/결론 범위 기록. |

### Figure Caption and Validation Review

| Figure / Source Location | Current Density / Learning Interruption | Specific Recommendation |
|---|---|---|
| 9-01; Introduction L31 | Workflow 소개 직후 FPS 예시·잘못된 CPU Label·GPU21 ms·Thread overlap·동기/대기/VSync/Cap·잘못된 Fig9_02·Character 출처/품질 비교 미검증까지 한 italic caption이다. Frame Time 정의보다 먼저 상세 수치 판정을 읽는다. | **P1.** Workflow를 읽는 목적과 “실측 성과가 아닌 개념 예시”를 짧은 caption에 남긴다. 전체 수치/Label/번호/출처 보정은 `Figure 9-01 Verification Note`로 분리한다. No-sum/대기 고려 원칙은 9.2 본문에 계속 남긴다. |
| 9-04; 9.4 L2160 | 1x–8x 미실측, Hair→Cloth→Face의 비고정 순서, Depth/Blend/Pass, Geometry LOD≠Pixel reduction, Rasterization≠최종색, ASF 명칭 오류, 출처가 함께 있다. Overdraw 본 설명은 L2391 이후이다. | **P2.** Pixel 면적/반복 처리 관계를 읽는 목적과 예시 미검증 범위를 먼저 제시한다. “겹침과 실제 처리는 다름”은 main caption/body에 유지하고 전체 Label/출처/표현 수정은 Note로 둔다. |
| 9-05; 9.5 L3111 | Shader 요소의 비고정 순서, Lerp/If/Custom HLSL 비용 해석, 50/200/600 Instructions와 100×100 Pixels 예시, Coverage/Pass/Hardware 비교까지 Shader cost 개념보다 먼저 읽는다. | **P2.** Shader 계산량을 비교할 때 확인할 요소라는 purpose와 예시≠실측 표시를 caption에 남긴다. 전체 값/Branch/출처 조건은 Note로 나누되 실제 GPU Timing 확인은 본문과 가까이 유지한다. |
| 9-07; 9.7 L5396 | Frustum Label의 반대 오류, 다른 Pass 기여, LOD≠blur/해상도, 예시 비율/성능, Screen Size, 출처, 내부 정정을 한 blockquote에 담는다. | **P2.** LOD와 View/Pass별 제외의 차이와 미검증 그림 범위를 짧게 남긴다. Label 오류/예시비율/출처는 Verification Note로 묶는다. Pass별 Shadow/Reflection 조건과 실제 LOD 기준은 본문에 유지한다. |
| 9-08; 9.8 L6576 | Tool 역할 소개 뒤 미검증 Timeline, Frame16.7와 wait 조사, stat gpu/ProfileGPU 구별, Event overlap, 미검증 r.ViewMode 명령, Quad 해석/색≠GPUtime, 후속 내부 정정을 모두 읽는다. 바로 뒤 Implementation Note L6582–6584에서도 일부 범위를 반복한다. | **P2.** “도구별 질문/관찰 범위 비교이며 검증된 Capture/명령표가 아님”을 caption에 남긴다. 명령/버전/Timeline/Event/출처 검증을 하나의 Note로 묶고 Tool 사용 절에서 필요한 조건을 즉시 연결한다. 색상≠시간/통계≠원인 확정은 각각 본문에도 유지한다. |

이 정리는 Figure 내부 오류를 해결했다는 뜻이 아니다. 실제 엔진 Capture와 조건 기록이 필요하다고 현재 문서가 명시한 부분은 그 상태를 유지한다. 숫자 예시는 실측 성과가 아니며, 긴 검증 문구를 접더라도 caption의 미검증/예시 표시는 지우지 않는다.

### Formula / Measurement Classification

`Frame Time = 1000 / FPS`와 60/30/20 FPS의 ms 예시는 **Essential**이며 현재처럼 시간의 의미를 설명한 후 유지한다. `Processed Pixels × Shader Cost per Pixel`은 **Explain First**인 개념적 관계이며 실제 GPU 내부 비용을 완전히 결정하는 공식으로 바꾸지 않는다. Game/Draw/GPU 예시는 overlap/대기 가정이 함께 있어야 하므로 **Essential Conditions Attached**로 취급한다. Parent/Child GPU Event 중첩, 정확한 Thread/Queue 배치, Version/Build별 Tool 지원, Helper/Wave 상세는 **Move to Technical Note** 후보이나 그 결과인 “합산 금지/후보와 확정 구분/실제 시간 검증”은 본문에 유지한다.

### Final Recommendation and Remaining Review

**Light Style Pass Recommended.** 첫 용어 예고에는 이전 장 recall을 붙이고, 9.1은 비교 조건이 필요한 이유를 먼저 알려 준다. Figure captions와 일부 Engine 실행 세부를 named Notes로 분리한다. Practical Analysis와 9.8/9.9의 단계적 질문/도구/한 변수/재측정 구조는 유지한다. 장 전체를 더 짧은 이론 요약으로 바꾸는 것은 권장하지 않는다.

실제 Engine Version/Build/Platform의 Command/View Mode 지원, Figure의 미확인 수치/출처/Label, 실제 ASF 성능 Capture와 반복 측정 분포는 아직 별도 검증 항목이다. 이번 Audit은 지원 기능이나 벤치마크를 새로 실행하여 입증한 것이 아니다. Source의 측정 정밀도를 읽고 후속 문체 편집에서 무엇을 유지해야 하는지 판단했다.

---

## Read-Only Verification

아래 해시는 감사 시작과 보고서 저장 후 같음을 확인했다. 수정 대상은 이 감사 보고서뿐이며 Chapter 06/07/09 원고 및 Figure는 수정하지 않았다.

| Source | Lines | SHA-256 | Audit Mode |
|---|---:|---|---|
| Chapter06_ModernRealtimeRendering.md | 754 | `c0544e8353371ce8f67f32da991e2e90153ab34e37b3535a51703775e088c3ad` | Read only; full text reviewed |
| Chapter07_Stylized Rendering.md | 777 | `f6c6945a815a220009ffa9e0687d65be24a0ef366b6f5bf1dad3b24d58bef6cb` | Read only; full text reviewed |
| Chapter09_RenderingDebugandOptimization.md | 8687 | `2b9420f2dad44bd9c253d8f4996a698ea87d9866d2225b0f5899036b14aee307` | Read only; full text reviewed |


## Complete Preservation Manifest

감사 대상 15개 원고는 아래 Rewrite 직전 해시와 동일하다. 기존 Figure 161개도 변경되지 않았다.

| Audited File | SHA-256 | Status |
|---|---|---|
| 00_Foundation/Chapter06_ModernRealtimeRendering.md | `c0544e8353371ce8f67f32da991e2e90153ab34e37b3535a51703775e088c3ad` | Byte-identical; Audit Only |
| 00_Foundation/Chapter07_Stylized Rendering.md | `f6c6945a815a220009ffa9e0687d65be24a0ef366b6f5bf1dad3b24d58bef6cb` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.0_PreparingTheASFProject.md | `0e908ece72388063b8feb5d48f33eca951da2b83abb8840ebcb9d3ccf4e24c24` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.10_FinalFramwork.md | `55da2eaa76aa6ddc644b3a33c8bd179968cfc6ea42a72ffc5ba70057af50b491` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.1_ArchitectureOverview copy.md | `7951664b299339804d2859f2dea18c4cba863c9f4b9b989dc8013d17d6cd562a` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.2_BaseLighting.md | `8c5f8dfe65d41a37ec2fbed41c8b22377bfc8688f03a1d74a4c9b72f7f103bfc` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.3_Shadow.md | `fbd9a359ce9a04b9db187e5550fa2e918701788ef9e561f029f120b46df0abe7` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.4_Specular.md | `1a9e567b2cb9721a2c087073c5919fe24d39aab9c84a339b8850598c5bb4a42b` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.5_RimLight.md | `b74a6c582263b0ce3d380b2467c52e7b1ff476bea3e554351b14c4aff0bf7416` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.6_MatCap.md | `5cab66373823f1a10d81e6020359c6488abf20f4f3bdd2744fc6f02c2db5ff28` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.7_Emission.md | `a0250b4ecab5d3564700e0bddb9191a427362759c039d264f69c0827bf7d3f6a` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.8_MaterialLayer.md | `64eb1e556de989ffd760ddc676cadfb2e40ff5a1f57be8595a5c78de469c2e95` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08.9_DebugView.md | `c0ebda10d437f48bc4e20142e5e1a3c4cf6c0036ddfaaa762fdfebfe7ee0bb9c` | Byte-identical; Audit Only |
| 00_Foundation/Chapter08_BuildingAnAnimeShader/Chapter08_BuildingAnAnimeShader.md | `56541701c5ace4200bbfd2dcb3974e5bf520f296836b874b16caa66f20ae76cc` | Byte-identical; Audit Only |
| 00_Foundation/Chapter09_RenderingDebugandOptimization.md | `2b9420f2dad44bd9c253d8f4996a698ea87d9866d2225b0f5899036b14aee307` | Byte-identical; Audit Only |
