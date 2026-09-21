# Foundation Audit — Chapter 07 and Chapter 09

Phase 1A — Text Audit · 2026-09-19

- 범위: **Chapter 07과 Chapter 09만**. 파일명의 `07-09`는 Chapter 08 포함을 의미하지 않는다. Chapter 08 본문은 열람·Audit하지 않았다.
- 기준 루트: `C:\Users\kmcoo\Desktop\PW\ASF_Review`. 첨부의 예전 경로 대신 사용자가 정정한 경로를 적용했다.
- 실제 Foundation 위치는 `00_Foundation`이다. 루트에서 발견한 대상 Markdown은 아래 두 파일이며 전체를 검토했다.
- 대상 A: `00_Foundation/Chapter07_Stylized Rendering.md` — 1,227 lines.
- 대상 B: `00_Foundation/Chapter09_RenderingDebugandOptimization.md` — 8,595 lines.
- `L`은 Audit 당시 원본의 1-based line number이다. 범위 밖 Chapter 번호는 연결 지점이며 해당 Chapter의 새로운 Audit 판정이 아니다.
- 원본·파일명·Figure는 수정하지 않았다. 이미지 Visual Content는 확인하지 않았다. 외부 자료는 조회하지 않았으며 환경·구현에 의존하는 미확인 사항은 `Needs Technical Verification`으로 구분했다.

기준은 `00_Project/ASF/ASF-000_Project_Principles.md`, `ASF-001_Naming_Philosophy.md`, `ASF-002_Rendering Architecture.md`, `ASF-003_Documentation_Standard.md`를 우선 적용했다. `00_Project/ASF_Standard.md`, `00_Project/Project_Management/Roadmap.md`, `DecisionLog.md`는 Source of Truth, 학습 단계와 명칭을 보조 확인했다. 특히 ASF-000의 PBR Foundation·Measurement·Validation·Foundation/Advanced 역할, ASF-002의 Data/Space/Input/Output, ASF-003의 Heading·Reference·중복 관리 원칙을 적용했다.

## 1. Executive Summary

**Chapter 07은 PBR / Lighting Foundation을 Stylized Interpretation으로 확장하는 역할이 명확하다.** 7.1은 기존 Lighting·Reflection·HDR·Tone Mapping을 이해한 뒤 필요한 부분을 의도적으로 바꾼다고 설명한다. PBR을 무시하는 장으로 판정할 근거는 없다. Face·Hair·Outline의 상세 구현을 뒤로 미루므로 현재 본문이 복잡한 Anime Shader Technique 모음집으로 변한 상태도 아니다.

가장 큰 구조적 문제는 **Remap의 공통 Input → Processing → Output이 약한 상태에서 개별 효과가 먼저 나오는 점**이다. Threshold·Ramp의 원리가 7.9에 모여 있고 앞 절에서는 무엇을 Threshold하는지 모호하다. 특히 Diffuse 명암 구분과 실제 Shadow Visibility, Fresnel과 Rim Lighting이 섞이면서 Controlled Deviation의 출발점을 잘못 이해할 수 있다. 이 두 경계는 반드시 수정해야 한다.

**Chapter 09는 Measure → Identify Bottleneck → Analyze Cause → Optimize → Measure Again이라는 Foundation 역할을 충분히 수행한다.** FPS와 ms, Cost와 Bottleneck, Triangle Count의 중요성과 한계, Node Count와 실제 연산 비용, Runtime 0과 Compile-time 제거, Draw Call과 Triangle Count, Culling과 Object Update의 차이를 이미 설명한다. 9.8은 질문별 도구 선택 표까지 제공하므로 단순한 Tool 암기 목록이라는 평가는 부당하다.

가장 큰 구조적 문제는 **9.8–9.9에서 앞의 설명과 진단 흐름을 거의 그대로 다시 펼치는 중복**이다. 그러나 길이보다 원인 추론의 정확성을 먼저 해결해야 한다. 9.7에서 LOD와 Culling을 동시에 바꾼 결과를 Geometry Bottleneck 개선으로 단정하는 예시, 9.5의 잘못된 Lerp 흐름과 Draw Call을 Pixel Cost로 소개하는 문장, 9.3의 겹치는 비용 범주를 독립 시간처럼 취급하는 예시는 우선 수정 대상이다. 9.8의 해석 불가능한 인용 토큰도 검증 가능한 Reference로 복구해야 한다.

Advanced 이동 가능성이 높은 현존 내용은 **9.9 후반의 상세 Test 종류와 Portfolio / Case Study 산출물 설계**이다. 완성된 실측 실험이나 Production Case Study 자체가 들어 있지는 않다. 가상 수치 예제, 기본 도구 사용, Baseline 비교, 간단한 진단 Workflow는 Foundation에 남겨야 한다. Chapter 07의 Face SDF·Hair Algorithm·Custom HLSL은 상세 구현이 추가될 때 Advanced 대상이며, 현재 개념 소개를 일괄 이동할 이유는 없다.

## 2. Shared Issues

| 공통 항목 | 실제 근거 | 판정 / 처리 방향 |
|---|---|---|
| 설명용 모델의 적용 범위 | 7.4–7.5의 물리적 현상, 9.2 Pipeline 및 9.3 시간 예시 | 단순화 전제를 짧게 붙인다. 예제가 보편 법칙으로 읽히지 않게 한다. C07-01/02, C09-01/03 참조. |
| Input / Processing / Output | 7.2–7.9 Remap 대상과 출력, 9.5 Lerp 화살표 | ASF-002에 맞춰 데이터 의미와 방향을 명시한다. 최소 흐름 보강은 상세 구현 추가가 아니다. |
| Unnecessary Duplication | 07 Comparison–Callback–핵심 요약, 09의 9.8–9.9 재요약 | 동일 결론 반복만 Merge / Shorten. 다른 효과·비용 유형에 원칙을 적용하는 Necessary Reinforcement는 Keep. |
| Heading | 07 Major Section이 H1, 09는 9.1·9.2만 H1 | Chapter H1 → Major H2 → Internal H3 기준으로 맞춘다. 기술 수정 이후의 Low 우선순위이다. |
| 미래 학습 단계 연결 | 7.9 다음 Chapter 실험 예고, 9.9 Advanced 예고 | 기본 적용과 상세 검증의 목적지를 구분한다. 예고는 Keep, 상세 심화 설계만 분리한다. |

`Cloth/Outfit`은 Chapter 09의 명칭 문제, 깨진 인용은 9.8의 문제이므로 두 Chapter의 공통 결함으로 확대하지 않는다.

## 3. Chapter 07 Audit

### Overall Assessment

7.1의 방향을 유지하며 `공통 입력과 Remap → 효과별 목적과 변형 → 기본 검증 → 구현 학습 연결`을 보강하는 것이 적절하다. PBR과 Stylized를 상호 배타적 체계로 재정의하거나 모든 예제를 Advanced로 옮기지 않는다.

### Important Keeps

| 위치 | Action | 이유 |
|---|---|---|
| 7.1 L57–77 | Keep | 기존 Foundation의 유지·변경·추가 구분은 Controlled Deviation의 핵심이다. |
| 7.2 L179–191, 7.3 L295–305 | Keep / Expand | Lambert·Specular 재해석 연결은 유효하다. 입력값만 보강한다. |
| 7.6 L719–721, 7.7 L881–885, 7.8 L1018–1024 | Keep | 상세 구현을 분리하려는 경계가 이미 있다. |
| 7.8 L930–932 | Keep | Outline을 물리적 반응과 구별되는 그래픽 표현으로 설명한다. |
| 7.9 Threshold / Smoothstep / Ramp | Keep | 기본 연산이다. Technique라는 제목만으로 Advanced로 보내지 않는다. |

### Issues

#### C07-01 — Diffuse 명암 경계와 Shadow Visibility 혼합

- Section: 7.4 PBR Shadow / Comparison / ASF Implementation, L353–363, L403–433.
- Severity: High.
- Action: Rewrite / Expand.
- Issue: Area Light나 Indirect Lighting 때문에 Shadow 경계가 부드러워진다는 설명과 Diffuse를 Threshold해 Shadow를 만든다는 설명이 하나의 Shadow 개념으로 이어진다. PBR Shadow는 부드러운 연속 변화라는 대비도 과도하다.
- Reason: 표면 방향에 따른 명암과 물체가 빛을 가리는 Visibility는 다르다. Indirect Lighting이 어두운 영역을 채우는 것과 광원 크기에 따른 Penumbra는 같은 원인이 아니다. 물리적 조명에서도 선명한 Cast Shadow가 가능하다.
- Related Section / Chapter: 7.2 Diffuse; 7.7 Face; ASF-002 Lighting / Shadow Data.
- Recommendation: `Angular Response → Tone Band`와 `Light Visibility → Cast / Self Shadow`를 먼저 분리한다. 두 결과를 결합·재해석하는 최소 흐름을 제시한다. Diffuse Threshold 예제는 Keep하되 Tone Band 또는 Shading Terminator 제어라고 범위를 밝힌다. Shadow Algorithm 구현은 추가하지 않는다.

#### C07-02 — Fresnel을 Rim Lighting의 단일 원인으로 설명

- Section: 7.5 L487–505, L537, L597–604.
- Severity: High.
- Action: Rewrite / Expand.
- Issue: 물리적 Rim을 Fresnel에 의해 자연스럽게 생기는 가장자리 밝기로 설명하고 Stylized Rim의 직접적 원형처럼 취급한다.
- Reason: Fresnel은 각도에 따른 반사 비율이며 빛을 스스로 만들지 않는다. Rim은 광원 배치·입사광·표면 및 시선 방향 등이 만드는 결과일 수 있다. View-angle Mask를 더하는 방식도 실제 Fresnel 반사와 동일하지 않다.
- Related Section / Chapter: 7.3 Specular; 7.9 Remap; Chapter 08은 참조 문장만 검토.
- Recommendation: 물리적 반사 성질, 역광 등의 외곽 조명, 스타일용 Rim 합성을 구별한다. `N·V 기반 Mask → Width / Shape → Color / Intensity`는 제어 예시임을 밝힌다. N과 V는 같은 Space의 정규화된 방향이라는 전제를 연결한다.

#### C07-03 — Controlled Deviation의 데이터 의미 부족

- Section: 7.2 L135–191; 7.3 L295–305; 7.4 L425–433; 7.9 L1068–1135.
- Severity: Medium.
- Action: Expand.
- Issue: Lambert 결과·Specular·밝기를 재해석하지만 입력이 각도 Scalar인지 조명 세기가 포함된 값인지 RGB인지 불분명하다. 출력도 Mask와 최종 Color 사이를 오간다.
- Reason: 어떤 값을 바꾸는지 모르면 Intensity·Exposure 변화까지 형상 제어로 이해할 수 있다. ASF-002의 Data Meaning / Input / Output 연결이 필요하다.
- Related Section / Chapter: ASF-002 Space / Module Input and Output; 앞선 Lighting·HDR·Color 학습.
- Recommendation: 하나의 예제에 `동일 Space의 N,L → x = saturate(dot(N,L)) → Threshold 또는 Ramp → Mask / Tone Color`를 명시한다. x는 전체 PBR Lighting이나 최종 화면 밝기가 아니다. HDR 값을 직접 Remap할 때는 범위·정규화·적용 시점이 별도 선택임을 짧게 설명한다.

#### C07-04 — 공통 연산 설명이 사용보다 늦음

- Section: 7.2–7.5 Threshold / Ramp 사용; 7.9 L1068–1135.
- Severity: Medium.
- Action: Move / Merge / Expand.
- Issue: 개별 효과를 읽은 뒤에야 공통 연산이 한곳에 정리된다.
- Reason: 기법별 용어를 먼저 외우게 되고 같은 연산의 재사용 구조가 약해진다.
- Related Section / Chapter: 7.1 → 7.2; C07-03.
- Recommendation: Threshold는 경계 분류, Smoothstep은 전이 구간, Ramp는 입력과 출력 표현의 대응이라는 최소 정의를 7.2 이전에 둔다. 7.9는 여러 효과가 같은 연산을 다른 입력·목적으로 사용한다는 종합으로 유지한다.

#### C07-05 — PBR / Stylized 대비를 보편 분류처럼 사용

- Section: 7.1 L21–51; 7.2–7.7 Comparison.
- Severity: Medium.
- Action: Rewrite.
- Issue: 현실적·연속적 반응과 단순화·선명한 형태를 반복적으로 양분한다. 7.1의 재해석 설명과 달리 개별 대비는 상호 배타적으로 읽힐 수 있다.
- Reason: PBR 기반도 Stylized Art Direction에 사용할 수 있고 Stylized 표현도 부드러울 수 있다. Lambert 예시는 모든 PBR의 정의가 아니다.
- Related Section / Chapter: ASF-000 Principle 06; 7.4.
- Recommendation: 이 장에서 선택한 대표 표현 비교라는 전제를 둔다. Diffuse부터 다루는 순서도 보편 중요도 순위가 아니라 학습 순서로 표현한다. PBR 기반 설명은 유지한다.

#### C07-06 — Hair 모델과 산란 범주 확인 필요

- Section: 7.6 PBR Hair Lighting, L627–651.
- Severity: Medium.
- Action: Rewrite / Needs Technical Verification.
- Issue: 방향성, BRDF, Marschner, Dual Scattering, Multiple Scattering이 같은 수준의 모델 목록처럼 연결된다.
- Reason: Fiber의 방향 의존 반응과 여러 Fiber 사이 산란은 범위가 다르다. 모델명만으로 어떤 성질을 단순화하는지 알기 어렵다. 정확한 모델 분류는 로컬 근거만으로 확정하지 않는다.
- Related Section / Chapter: 7.3 Specular; 7.6 Stylized Hair.
- Recommendation: Strand·관찰·조명 방향에 따른 Highlight 원리를 남긴다. 모델명은 목적이 있는 것만 유지하고 단일 Fiber / 다중 Fiber 산란 관계는 후속 검증한다. 유도식과 Character-specific 구현은 Advanced에 둔다.

#### C07-07 — Face 제어 선택 사항이 일반 원칙처럼 보임

- Section: 7.7 L803–821, L865–885.
- Severity: Medium.
- Action: Rewrite / Expand / Needs Technical Verification.
- Issue: 고정 Mask·Light Direction·Face Forward·SDF를 나열한 후 일반 Lighting과 독립적으로 제어한다고 정리한다. 독립의 의미와 Face Forward 역할이 부족하다.
- Reason: 가독성을 별도로 제어한다는 목적과 Light와 무관한 결과는 다르다. SDF와 일반 Artist-authored Face Shadow Map도 같은 데이터라고 단정할 수 없다.
- Related Section / Chapter: 7.4; ASF-002 Shared Foundation / Character-specific Module.
- Recommendation: 공통 Lighting 입력을 사용하며 형태를 제어하는 경우와 고정 Mask 방식을 선택지로 구분한다. Face Forward는 얼굴 기준 방향이며 Light와 비교하려면 Space를 맞춘다는 수준만 보강한다. SDF 데이터 의미는 후속 구현 단계에서 검증한다.

#### C07-08 — Outline 분류 축과 ASF 적용 상태 혼합

- Section: 7.8 L972–1024.
- Severity: Medium.
- Action: Rewrite / Expand.
- Issue: Inverted Hull, Normal Expansion, Screen Space, Edge Detection을 동급 기법처럼 나열하고 독립 Rendering Pass를 ASF의 확정 구현처럼 소개한다.
- Reason: Normal Expansion은 Hull 방식의 요소일 수 있고 Edge Detection은 Screen-space 처리일 수 있다. 기능 Module과 Pass 배치는 다르며 Foundation에서 새 Architecture 규칙을 독립 선언하면 기준이 분산된다.
- Related Section / Chapter: ASF-002 Stage / Module / Composition; ASF_Standard Source of Truth.
- Recommendation: Geometry 기반과 Screen-space 기반 아래 처리를 배치한다. `Position / Normal → 외곽 Geometry`, `Depth / Normal → Edge Mask` 정도만 설명한다. 독립 Pass는 예시·설계 의도인지 밝히고 확정 규칙이면 기준 문서에 연결한다. 구현 존재 여부는 확인하지 않았다.

#### C07-09 — Smoothstep과 Anti-aliasing의 관계 제한

- Section: 7.9 Smoothstep, L1086–1105.
- Severity: Medium.
- Action: Rewrite / Expand.
- Issue: 경계를 부드럽게 해 Aliasing을 줄인다는 설명에 전이 폭과 화면 샘플링 조건이 빠져 있다.
- Reason: 입력값의 부드러운 전이가 모든 해상도·거리·움직임에서 Aliasing을 해결하지는 않는다.
- Related Section / Chapter: 7.2 Threshold; 7.4 Shadow; 7.5 Rim.
- Recommendation: 값의 전이를 부드럽게 하는 연산으로 정의한다. Camera / Light 이동 시 경계 안정성을 확인한다는 Basic Verification을 덧붙인다. 미분 기반 폭 제어나 AA 구현 강의까지 확장하지 않는다.

#### C07-10 — 반복 요약과 확인 기준의 불균형

- Section: 7.2–7.8 Comparison / Callback / 핵심 요약; 7.9 L1177–1227.
- Severity: Medium.
- Action: Merge / Shorten / Expand.
- Issue: 물리적 정확성보다 형태·가독성을 선택한다는 결론은 반복되지만 변형이 목적에 맞는지 확인할 기준은 적다.
- Reason: 같은 목표를 재서술하는 Unnecessary Duplication보다 입력 변화에 따른 반응을 확인하는 짧은 예제가 유용하다.
- Related Section / Chapter: ASF-000 Validation; C07-03/09.
- Recommendation: 입력·변형·목적·확인 조건을 간단히 정리한다. Light 회전의 Tone Band, View 변화의 Rim, 얼굴 회전의 Mask 방향 등을 확인한다. Hair·Face·Outline의 서로 다른 목적을 설명하는 Necessary Reinforcement는 유지한다.

#### C07-11 — Chapter 08 참조와 실험 예고 범위

- Section: 7.5 L499; 7.7 L777; 7.9 L1159–1189 및 Chapter 7 End.
- Severity: Low.
- Action: Rewrite / Expand.
- Issue: IOR·SSS의 후속 참조와 다음 Chapter의 Shader 구성·시각적 차이·Performance 실험 예고가 섞인다. Foundation 이론 준비가 모두 끝났다는 표현도 현 Chapter 범위를 넘는다.
- Reason: 현재 설명에 필요한 용어를 모두 뒤로 미루면 이해가 어렵다. 기본 적용과 상세 성능 실험은 역할이 다르다.
- Related Section / Chapter: Chapter 08 참조 문장; Roadmap; ASF-000 Foundation / Advanced.
- Recommendation: IOR·SSS 역할만 짧게 제공하고 후속 구현 참조를 둔다. 다음 Chapter는 기본 적용, 상세 실험은 Advanced로 구분한다. Chapter 08 본문과 실제 절 일치 여부는 검증하지 않았으므로 잘못된 참조라고 확정하지 않는다.

#### C07-12 — Heading 구조

- Section: L1, L103, L217, L333, L467, L607, L745, L914, L1054, L1206 및 내부 Heading.
- Severity: Low.
- Action: Rewrite / Merge.
- Issue: 각 7.n과 Chapter 7 End가 H1이고 내부 제목은 H2이다. Korean / English 제목도 혼재한다.
- Reason: ASF-003 및 요청의 Chapter H1 / Major H2 / Internal H3 체계와 다르다.
- Related Section / Chapter: ASF-003 Heading / Language; C09-16.
- Recommendation: Chapter H1 하나, 7.n H2, 내부 H3로 맞추고 끝 요약을 통합한다. 제목은 English 중심, 설명은 Korean으로 유지한다. 불필요한 7.n.n 내부 번호는 추가하지 않는다.

## 4. Chapter 09 Audit

### Overall Assessment

핵심 개념 대부분은 이미 정확한 방향이다. 리팩터링은 지표의 의미를 약화시키거나 Workflow 예제를 삭제하는 작업이 아니라 **진단 단서와 원인 확정을 구별하고 기준 설명 위치를 정하는 작업**이어야 한다. RHI는 9.8에 설명이 있으므로 누락으로 판정하지 않는다.

### Important Keeps

| 위치 | Action | 이유 |
|---|---|---|
| 9.1 FPS / Frame Time, Baseline, Average / Spike | Keep | ms 비교와 동일 조건 측정이 명확하다. Spike를 누락한 문서가 아니다. |
| 9.2 L609–676 | Keep / Expand | 시간을 합하지 않고 Frame 간 Overlap으로 설명한다. 전제만 보강한다. |
| 9.3 Triangle·Vertex·Skinning·Silhouette / Deformation | Keep | Triangle 중요성을 지키며 비용과 품질의 다른 요인을 연결한다. |
| 9.4 Opaque / Early Z | Keep | 모든 Surface가 항상 같은 비용으로 반복 계산된다는 단정을 피한다. |
| 9.5 Node / Instruction / Texture / Branch / Custom HLSL | Keep | Node 수나 HLSL 사용 자체로 비용을 단정하지 않는다. Runtime 0과 Static 선택도 구별한다. |
| 9.9 L7999 Unconnected Node | Keep | 활성 Output 의존 경로에 연결되지 않은 계산이 최종 Runtime 연산에 포함되지 않는다는 취지는 타당하다. 필요하면 ‘컴파일 대상 Output에 기여하지 않는 경로’로 정밀화한다. |
| 9.6 Slots / Sections / Passes와 병합 Trade-off | Keep | Triangle↔Draw 등식이 없으며 Section·Pass·Culling 영향을 고려한다. ‘Slot 하나가 항상 Draw 하나’라고 단정한 문서로 판정하지 않는다. |
| 9.7 L5553–5579, L5845–5871, L5896–5973 | Keep | LOD는 Geometry만이 아니며 Culling과 AI·Physics·Animation Update 중단이 다름을 명시한다. |
| 9.8 L7195–7212, L6991–7011 | Keep | 질문별 Tool 선택과 Shader Complexity ≠ 실제 GPU Time을 명시한다. |
| 9.9 품질·Bottleneck 이동·재측정 | Keep | 무조건 비용을 제거하는 최적화관을 피한다. |

### Issues

#### C09-01 — Pipeline Timing과 측정 전제 보강

- Section: 9.1 Baseline; 9.2 L609–678; 9.8 L6520–6607, L6769–6797, L7411–7458.
- Severity: Medium.
- Action: Expand / Rewrite / Needs Technical Verification.
- Issue: Overlap과 Queue / Synchronization은 언급하지만 가장 큰 Game / Draw / GPU를 찾는 요약이 원인 확정 규칙처럼 읽힐 수 있다. 동일 조건에 Frame Cap / VSync·내부 해상도·Warm-up 상태가 명확하지 않다.
- Reason: Timing에는 기다림·동기화 영향이 있을 수 있다. 제한된 FPS나 자동 해상도 조절 상태에서 값만 비교해 Bottleneck을 판단하기 어렵다. RHI는 후반에 있지만 초반 분기와 연결이 약하다.
- Related Section / Chapter: 9.2 stat unit; 9.8 RHI / Insights; 9.9 Baseline.
- Recommendation: 최대값 비교는 안정된 조건에서의 첫 가설이며 원인은 Timeline·Pass 분석으로 확인한다고 연결한다. Baseline에 Hardware / Build, Frame 제한, 내부 Resolution / Dynamic Resolution 정책, Compile / Streaming 안정화 상태를 기록한다. RHIT·작업 Thread·Wait는 9.8로 참조한다. Timing 항목·해석은 프로젝트 UE 버전과 플랫폼에서 후속 검증한다.

#### C09-02 — Triangle과 Vertex를 고정 서열화

- Section: 9.3 L1437–1451, L1555–1557.
- Severity: Medium.
- Action: Rewrite.
- Issue: Triangle은 기본 규모, Vertex는 추가 비용의 보조 지표라는 서열을 일반화한다. Camera 거리와 Screen Size를 ‘즉’으로 연결한다.
- Reason: Triangle은 중요한 기본 지표지만 Vertex / Skinning이 주요 제한인 상황도 함께 설명할 수 있어야 한다. Screen Size는 거리 외에 Object 크기·투영 조건에도 좌우된다.
- Related Section / Chapter: 9.3 Skinning; 9.7 L5478–5500.
- Recommendation: Triangle의 중요성은 유지하며 Vertex·Influence·Pass 재처리는 작업에 따라 함께 중요하다고 설명한다. ‘거리, 즉 Screen Size’를 ‘거리 등에 따라 달라지는 Screen Size’로 고치고 9.7에 연결한다.

#### C09-03 — 비용 종류와 Pass 시간을 독립 항목처럼 취급

- Section: 9.3 L1836–1869.
- Severity: High.
- Action: Rewrite.
- Issue: Geometry·Shadow·Transparency·Post Process를 같은 시간 분해표에 놓고 Geometry 1.5→0.9 ms가 전체 Frame 0.6 ms 감소로 이어진다고 단정한다.
- Reason: Geometry는 여러 Pass 안에서 발생하는 처리 종류라 Shadow·Transparency와 배타적이지 않다. 구간 중첩·CPU 제한에 따라 GPU 감소가 Frame에 그대로 반영되지 않는다.
- Related Section / Chapter: 9.2 Overlap / Bottleneck; 9.8 ProfileGPU.
- Recommendation: Cost Type과 Pass Timing을 구분한다. 산술 예제를 유지하려면 ‘겹치지 않는 가상 구간, GPU가 Frame을 제한하며 다른 조건은 동일’이라는 전제를 둔다. 실제 Frame 감소는 재측정한다. 가상 예제를 실측 Case로 이동할 필요는 없다.

#### C09-04 — Masked / Translucent Hair 구분 부족

- Section: 9.4 Transparency / Hair; 9.6 L4689 전후; 9.8 L7063–7099.
- Severity: Medium.
- Action: Expand / Needs Technical Verification.
- Issue: Hair Card 겹침을 반복 설명하지만 Masked와 Alpha-blended Translucency의 경로 구분은 약하다.
- Reason: 외형만으로 모든 Hair가 Translucency Pass에서 동일하게 처리된다고 추론할 수 있다. Masked의 Coverage / Depth와 Translucent의 혼합·정렬은 구별해야 한다.
- Related Section / Chapter: 9.4 Early Z; 9.8 ProfileGPU → Hair 예시.
- Recommendation: Opaque / Masked / Translucent의 기본 역할만 보강하고 실제 Blend Mode / Pass를 먼저 확인하게 한다. Masked 비용을 Translucent와 같은 원인으로 단정하지 않는다. Early Depth 및 Debug View 지원은 실제 UE 설정·플랫폼에서 검증한다.

#### C09-05 — Quad와 일반 Overdraw 설명의 모호성

- Section: 9.8 L7015–7059; 9.3 Very Small Triangles; 9.4 Overdraw.
- Severity: Medium.
- Action: Expand / Rewrite / Needs Technical Verification.
- Issue: 작은 Triangle 비효율이라는 방향은 맞지만 4×4 문자 블록만 있고 Quad 단위와 실제 출력 Pixel을 구별하지 않는다.
- Reason: Quad를 4×4로 오해하거나 덮지 않은 Pixel에도 최종 Color를 쓴다고 이해할 수 있다. Surface 중첩과 작은 Primitive의 Quad 활용 비효율은 같은 현상이 아니다.
- Related Section / Chapter: 9.4 Pixel; 9.8 Shader Complexity / Quad Overdraw; 9.9 L7922–7924.
- Recommendation: 기본 설명은 2×2 Pixel Quad로 제시하고 Covered Pixel과 출력에 기여하지 않는 Helper 실행을 구별한다. 이를 GPU 전체 실행 그룹 크기의 정의로 확대하지 않는다. 중첩 반복과 Quad 활용 부족을 나란히 비교한다. Unreal View의 카운트·색상·지원 경로는 버전별 검증 대상으로 남긴다.

#### C09-06 — Lerp의 입력과 출력 화살표 역전

- Section: 9.5 Masks and Blends, L3432–3446.
- Severity: High.
- Action: Rewrite.
- Issue: `Base Value → Lerp → Mask → Second Value`를 Blend 흐름으로 제시한다.
- Reason: 두 값과 Mask는 Lerp 입력이며 Second Value가 Lerp 이후 생성되는 출력은 아니다. ASF-002 Input / Output과 직접 충돌한다.
- Related Section / Chapter: 9.5 Material Graph; ASF-002.
- Recommendation: `Base Value(A), Second Value(B), Mask(alpha) → Lerp → Blended Value`로 고친다. 텍스트만으로 판정 가능하므로 Figure 확인을 기다릴 필요가 없다.

#### C09-07 — Draw Call을 Pixel Cost로 소개

- Section: 9.5 L4160 → 9.6 L4164–4200.
- Severity: High.
- Action: Rewrite / Remove.
- Issue: Draw Call / Rendering State가 Transparency와 함께 높은 Pixel Cost를 만들기 쉽다고 소개하며 ‘또는 Chapter 구성에 따라’라는 편집 문구도 남아 있다.
- Reason: 다음 절은 작업 준비·분할·제출의 CPU 비용을 설명한다. Submission과 Pixel 작업량을 혼합하면 비용 분류가 왜곡된다.
- Related Section / Chapter: 9.6 Draw Call; 9.2 Render Thread.
- Recommendation: 다음 절은 Rendering 작업의 분할·준비·제출 비용이라고 연결한다. Pixel Work가 함께 증가하는 경우는 조건을 분리한다. 편집용 대체 문구는 제거한다.

#### C09-08 — CPU-driven 예제를 보편 법칙으로 표현

- Section: 9.6 L4210–4225.
- Severity: Medium.
- Action: Rewrite.
- Issue: GPU는 무엇을 그릴지 스스로 결정하지 않는다고 단정한 뒤 CPU가 작업을 구성하는 모델을 소개한다.
- Reason: 기초 설명은 유효하지만 GPU에서 Visibility·간접 Draw 관련 작업을 수행하는 경우까지 부정하는 문장은 과도하다.
- Related Section / Chapter: 9.6 Instancing / Batching; 9.7 Culling.
- Recommendation: CPU가 Draw를 준비·제출하는 기본 모델이라는 범위를 둔다. GPU-driven 처리 가능성은 한 문장이면 충분하며 구현과 Indirect Command 구조를 새 Topic으로 추가하지 않는다.

#### C09-09 — Culling의 View / Pass 범위 부족

- Section: 9.7 L5641–5705, L5815–5831, L6391–6399.
- Severity: Medium.
- Action: Expand / Rewrite.
- Issue: Camera 밖이거나 가려진 Object는 최종 화면에 기여하지 않아 Rendering하지 않는다는 설명에 View / Pass 구분이 없다. Shadow 감소는 가능성으로 쓰지만 전제가 부족하다.
- Reason: Camera에 직접 안 보여도 Shadow 등 다른 작업에 기여할 수 있다. CPU Update와의 구분은 이미 정확하지만 모든 Pass 제거는 별도 문제다.
- Related Section / Chapter: 9.6 Multiple Passes; 9.7 Culling Does Not Mean Object Removal.
- Recommendation: 해당 View / Pass의 Visibility 판단으로 범위를 밝히고 Camera Cull 후 Shadow 작업이 남을 수 있음을 보강한다. 실제 제거 작업은 Profiling으로 확인한다. Game Logic 구분은 Keep한다.

#### C09-10 — 복합 변경으로 Geometry 원인 확정

- Section: 9.7 L6280–6319; 9.4 Practical 비교; 9.8 L7328–7368; 9.9 L8191–8228.
- Severity: High.
- Action: Rewrite / Expand.
- Issue: LOD Disabled / All Objects Rendering에서 LOD Enabled / Culling Enabled로 함께 바꾸고 GPU가 크게 줄면 Geometry Bottleneck 개선이라고 결론낸다. Hair Off / Card Count도 단일 비용만 바꾸는 듯 읽힐 여지가 있다.
- Reason: Geometry 외에 Pixel·Shadow·Draw·Material도 함께 변한다. 한 설정 변경과 한 비용 원인의 분리는 다르다. 9.7이 설명한 LOD의 다중 비용 영향과도 충돌한다.
- Related Section / Chapter: 9.7 L5553–5579, L5896–5973; 9.8 One Variable; ASF-000 Validation.
- Recommendation: LOD와 Culling을 우선 별도로 비교한다. GPU 감소는 변경 효과이지 Geometry 원인 확정은 아니라고 명시한다. Hair Off는 진단 Probe로 Keep하고 이후 Pass / 작업을 확인한다. 상세 통제 실험은 Advanced에 둔다.

#### C09-11 — 사용 불가능한 내부 인용 토큰

- Section: 9.8 L6530, L6643, L6789, L6841, L6949, L6957, L6993, L7059, L7083, L7109, L7442.
- Severity: Medium.
- Action: Rewrite / Needs Technical Verification.
- Issue: 11개 위치의 출처가 `turn...search...` 형태 내부 토큰이며 사용할 링크가 없다. ‘현재 Unreal Engine’에도 버전 범위가 없다.
- Reason: 출처 재현이 막혀 현재성·플랫폼 조건을 확정할 수 없다. Tool 설명 전부가 틀렸다는 판정은 아니다.
- Related Section / Chapter: ASF-003 Reference; 9.8 RHI / Debug View / ProfileGPU.
- Recommendation: 후속 검증에서 프로젝트 UE 버전·Renderer / Platform·문서 제목·URL을 기록하고 유효한 Markdown Reference로 복구한다. 이번에는 루트 내부 자료만 사용하므로 URL을 추측하지 않았다. 확정 전 ‘현재’를 제거하거나 검증 대기로 표시한다.

#### C09-12 — 도구 선택 흐름과 전체 요약의 중복

- Section: 9.8 L6477–6502, L7195–7212, L7488–7686; 9.9 L7724–8187, L8351–8428.
- Severity: Medium.
- Action: Merge / Shorten.
- Issue: CPU→Insights / GPU→ProfileGPU→Debug View와 Cost 정의를 표·화살표·Key Point·최종 요약으로 반복한다. 9.9는 앞 절을 다시 가르친 뒤 Workflow를 재요약한다.
- Reason: 새 조건이나 판단이 없는 반복은 Source of Truth를 분산시킨다.
- Related Section / Chapter: 9.1 Baseline; 9.2 CPU/GPU; 9.3–9.7 Cost.
- Recommendation: 9.8은 질문 / 도구 / 관찰 값 / 확정할 수 없는 것 / 다음 행동과 기본 예제에 집중한다. 9.9는 통합 Workflow, Quality, Bottleneck 이동, 절별 Reference로 구성한다. Coverage를 Shader에 적용하고 Culling을 Draw에 연결하는 Necessary Reinforcement는 Keep한다.

#### C09-13 — Advanced 예고가 Portfolio 설계까지 확장

- Section: 9.9 L8432–8499, L8503–8561.
- Severity: Medium.
- Action: Keep / Shorten / Move to Advanced.
- Issue: 심화 필요성 예고를 넘어 Test 종류와 Portfolio 산출물을 상세히 안내한다.
- Reason: 완성된 실험이 들어 있지는 않지만 다음 단계 산출물 설계는 Advanced 계획에 더 가깝다.
- Related Section / Chapter: ASF-000 Foundation / Advanced; Roadmap.
- Recommendation: 통제된 Bottleneck 재현과 실측 Before / After로 확장한다는 짧은 연결은 Keep한다. Test Matrix·재현 조건·측정 프로토콜·Portfolio 목록은 Advanced 이동 후보로 둔다. 가상 Timing과 기본 진단은 이동하지 않는다.

#### C09-14 — 기준 설명 위치와 Cross Reference

- Section: 9.1 측정; 9.2 L676; 9.3 Small Triangles; 9.4–9.7 확인 절차; 9.8 Tools; 9.9 Summary.
- Severity: Low.
- Action: Expand / Merge.
- Issue: 측정·Tool을 재설명하지만 기준 설명으로 돌아가는 연결이 일정하지 않다. RHI와 Quad는 늦게 설명된다.
- Reason: 내용 누락보다 최초 설명과 재사용 지점을 찾기 어려운 문제다.
- Related Section / Chapter: C09-01/05/12.
- Recommendation: 측정은 9.1, Thread는 9.2와 9.8 RHI, 비용은 9.3–9.7, Tool은 9.8을 기준으로 삼는다. 필요한 한두 문장과 절 링크를 추가하고 변경 후 Heading Anchor를 검증한다.

#### C09-15 — 의상 명칭과 작은 수치

- Section: 9.7 L5940–5949 등의 Part 목록; 9.5 L3717–3721.
- Severity: Low.
- Action: Rewrite.
- Issue: Character 부위로 `Cloth`를 쓰는 부분이 Outfit 결정과 다르다. Full-screen Quad를 `2~3 Triangles`로 표현한다.
- Reason: DEC-001과 ASF-002는 의상 부위 명칭을 Outfit으로 정한다. 기본 Quad는 보통 2 Triangles이며 Full-screen Triangle은 1 Triangle이다.
- Related Section / Chapter: DEC-001; ASF-001; 9.4 Full-screen 예시.
- Recommendation: 부위 명칭은 Outfit으로 맞추되 직물 재질·Cloth Simulation까지 치환하지 않는다. 수치는 ‘소수의 Triangle’ 또는 1 Triangle / 2-Triangle Quad로 고친다. Pixel Cost 설명은 유지한다.

#### C09-16 — Heading과 LOD 표현

- Section: L1, L43, L439, L1187 이후; 9.9 L8071–8076.
- Severity: Low.
- Action: Rewrite.
- Issue: 9.1·9.2만 H1이고 나머지는 H2이다. High LOD / Low LOD는 높은 Detail과 큰 Index 사이 의미가 모호하다.
- Reason: 탐색 계층이 불일치하며 LOD 0이 높은 Detail이라는 앞 예제와 해석이 엇갈릴 수 있다.
- Related Section / Chapter: ASF-003 Heading; 9.7 LOD 0–3.
- Recommendation: Chapter H1, 9.n H2, 내부 H3로 맞춘다. High / Low Detail 또는 명시적 LOD Index를 사용한다. 내부 번호는 새로 추가하지 않는다.

## 5. Missing / Weak Concept Map

### Chapter 07

| 필요한 Concept | 현재 상태 | 최소 보강 / 위치 | Issue |
|---|---|---|---|
| Remap Input의 의미·범위·Space | 어떤 값을 바꾸는지 약함 | 7.2 전에 같은 Space, Scalar 입력, Threshold/Ramp 출력 예제 | C07-03/04 |
| Tone Band / Light Visibility | Shadow에서 혼합 | 7.4에서 방향 기반 명암과 Occlusion 기반 Shadow 분리 | C07-01 |
| Fresnel / 물리적 Rim / View Mask | 인과 구분 약함 | 7.5에서 역할과 입사광 필요성 구분 | C07-02 |
| Hair·Face 방향 기준 | 기법명 대비 입력 역할 약함 | Strand 방향, Face Forward와 Light 비교 의미만 보강 | C07-06/07 |
| Outline 데이터 출처 | 분류 축 혼재 | Geometry / Screen-space의 입력→결과 구분 | C07-08 |
| Basic Verification | 목적 대비 확인 조건 부족 | Camera·Light·얼굴 방향 변화와 경계 안정성 확인 | C07-09/10 |

BRDF 유도, Face SDF 생성, Hair Scattering 수식, Outline Pass 구현, 복잡한 HLSL은 누락 Concept로 추가하지 않는다.

### Chapter 09

| 필요한 Concept | 현재 상태 | 최소 보강 / 위치 | Issue |
|---|---|---|---|
| 측정 전제·Wait / Cap | 반복·Spike는 존재, 제한 상태 부족 | 9.1 환경·제한·내부 해상도·안정화, 9.2 가설/확정 구분 | C09-01 |
| Cost Type / Pass Timing | 항목이 같은 표에 혼재 | 9.3 Geometry가 여러 Pass에 포함됨을 명시 | C09-03 |
| Masked / Translucent | Hair 겹침 대비 구분 약함 | 9.4 Coverage / Blend / Depth 기본 역할 | C09-04 |
| Quad / Helper 처리 | 작은 Triangle 비효율은 존재 | 2×2 개념도, 실제 출력과 Helper 구분 | C09-05 |
| View / Pass별 Visibility | Gameplay Update와는 구분됨 | 9.7 Camera Cull 후 남는 Shadow 등 작업 | C09-09 |
| 설정 변경 / 단일 원인 분리 | One Variable 원칙은 존재 | 9.7·9.8 Probe와 원인 확인의 차이 | C09-10 |
| 도구 검증 범위 | 질문별 선택은 좋음 | 9.8 환경·View 한계·Reference 복구 | C09-11 |

FPS / Frame Time, Baseline, RHI, Unconnected Node, Runtime 0, Draw Call ≠ Triangle, Material LOD, Culling ≠ Update 중단은 이미 있으므로 누락 목록에 넣지 않는다. GPU Architecture 상세나 Production Capture 전체를 새 Topic으로 요구하지 않는다.

## 6. Foundation / Advanced Boundary Review

| Content | Current Chapter / Section | Keep in Foundation or Move to Advanced | Reason |
|---|---|---|---|
| PBR 기반 Remap / Tone Band 예제 | 7.1–7.4 | Keep in Foundation | Controlled Deviation의 최소 예제이다. |
| Threshold / Smoothstep / Ramp | 7.9 및 앞 절 | Keep in Foundation | 공통 원리이므로 설명 순서만 조정한다. |
| Rim / Hair / Face 목적·입력 | 7.5–7.7 | Keep in Foundation | 같은 입력을 다른 목표로 해석하는 사례이다. |
| Detailed Face SDF | 7.7 이름과 예고만 존재 | 소개 Keep in Foundation; 향후 상세 구현 Move to Advanced | 현존 코드·실험의 이동 판정이 아니다. 거리장 제작·방향 판정·얼굴별 보정은 심화이다. |
| Character-specific Hair / Complex HLSL | 7.6·7.9 응용 소개 | 원리 Keep in Foundation; 상세 알고리즘 Move to Advanced | 현재 복잡한 구현은 없다. 목록 전체 삭제는 불필요하다. |
| Outline 방식의 큰 분류 | 7.8 | Keep in Foundation | 입력·출력 비교는 기초이다. Pass 구현·Production 예외는 Advanced이다. |
| 기본 시각적 검증 | 7.2–7.9 보강 제안 | Keep in Foundation | 입력 변화와 결과를 확인하는 Basic Verification이다. |
| ms·Baseline·Thread·Cost / Bottleneck | 9.1–9.3 | Keep in Foundation | Optimization 사고의 출발점이다. |
| 가상 수치와 Before / After | 9.1–9.8 | Keep in Foundation | 계산·진단 예제이다. 실측으로 오인되지 않게 가정을 명시한다. |
| Node / Runtime 0 / Draw / LOD / Culling | 9.5–9.7 | Keep in Foundation | 비용 유형과 제거 조건 구분의 핵심이다. |
| 질문별 Tool 선택 | 9.8 | Keep in Foundation | 기본 도구 인지·진단이다. 목록이라는 이유로 이동하지 않는다. |
| Hair Off·Resolution·LOD 기본 비교 | 9.4–9.8 | Keep in Foundation | 짧은 진단 Probe는 유지하며 특정 원인 증명이라는 단정만 수정한다. |
| Controlled Bottleneck Test / Test Matrix | 9.9 L8432–8499 | 짧은 연결 Keep in Foundation; 상세 계획 Move to Advanced | 변수 통제·재현 조건·수집 설계는 Advanced이다. 현재 실측 실험은 없다. |
| Portfolio / Case Study 구성 목록 | 9.9 L8503–8561 | Move to Advanced 후보; 연결 문단 Keep in Foundation | 가설·Capture·수정·전후 품질과 성능을 증명하는 산출물 설계이다. |
| Target Hardware / Build 인지 | 9.8 L7434–7458 | Keep in Foundation | 상세 실험은 심화여도 측정 환경의 한계는 기초이다. |

이동 기준은 분량이나 Practical이라는 제목이 아니라 **학습 목적과 검증 깊이**이다. 실제 이동·재배치는 수행하지 않았다.

## 7. Refactoring Priority

| Priority | Category | 처리 대상과 완료 기준 |
|---|---|---|
| Priority 1 | Technical Accuracy | C07-01/02의 Shadow·Fresnel·Rim 인과 분리. C09-03/06/07/10의 시간 분해·Lerp·Draw 연결·복합 변경 원인 확정 수정. 이후 Quad·GPU-driven·Visibility 및 Hair·Smoothstep의 적용 범위를 정밀화한다. |
| Priority 2 | Foundation / Advanced Boundary | C09-13과 Boundary Review에 따라 심화 Test / Portfolio 설계만 분리한다. 기본 예제·도구·간단한 전후 비교는 남긴다. C07-11의 다음 단계 예고도 구분한다. |
| Priority 3 | Concept Boundary | C07-03/04/07/08의 입력·처리·출력과 분류. C09-01/02/04/05/09의 측정 전제·지표·Blend Mode·Quad·View별 Visibility를 보강한다. |
| Priority 4 | Duplication / Explanation Density | C07-10, C09-12. 같은 결론만 반복하는 블록은 통합하고 Necessary Reinforcement는 보존한다. 정량적 분량 감축 목표를 두지 않는다. |
| Priority 5 | Cross Reference | C07-11, C09-11/14. 개념 기준 위치를 연결하고 Tool 출처를 복구한다. Chapter 08 본문 검증은 별도 범위이다. |
| Priority 6 | Terminology / Heading | C07-12, C09-15/16. H1/H2/H3, Character Outfit, LOD Index / Detail 표현을 통일한다. |
| Priority 7 | Minor Editing | C09-07 편집 잔여, C09-15 작은 수치, 반복 요약의 문장·표기. 기술 수정 후 Figure 설명·Anchor·번호를 대조한다. |

후속 기술 검증은 미확정 Hair 모델 분류, Face SDF 데이터 의미, UE Timing / Debug View의 환경별 동작을 대상으로 한다. 검증 전 추정을 확정 기술 오류와 동일하게 처리하지 않는다.

## 8. Figure Review Queue

### Text Reference Check

이미지를 열지 않고 Markdown 참조·파일명·존재 여부만 확인했다.

| Chapter | Markdown 참조 | 실제 파일 | 결과 |
|---|---|---|---|
| 07 | `Figures/Chapter07/Fig7_01.png`–`Fig7_09.png`, 9개 | 해당 폴더 PNG 9개 | 모두 존재. 01–09 연속, 각 1회 참조. Chapter 일치. 해당 폴더 내 미참조 PNG 없음. |
| 09 | `Figures/Chapter09/Fig9_01.png`–`Fig9_09.png`, 9개 | 해당 폴더 PNG 9개 | 모두 존재. 01–09 연속, 각 1회 참조. Chapter 일치. 해당 폴더 내 미참조 PNG 없음. |

Markdown 기준 상대 경로가 정상이며 번호·경로 누락이나 중복은 없다. 이는 이미지 내용·레이블·본문 일치의 검증을 의미하지 않는다.

### Visual Review Required

텍스트에서 발견한 개념 경계 때문에 후속 확인이 필요한 항목만 선정했다. Figure 자체의 오류 판정은 아니다. Priority는 시각 검토 순서이며 Issue Severity와 별개이다.

| Figure | Chapter / Section | Reason | What must be visually verified | Priority |
|---|---|---|---|---|
| Fig7_02.png | 07 / 7.2 | C07-03 Remap 입력 | 각도 반응·전체 Lighting·최종 Color 구분, Threshold 입력/출력 방향 | High |
| Fig7_04.png | 07 / 7.4 | C07-01 Tone Band / Shadow | 방향 명암과 Cast Shadow 구분, 광원 크기와 Indirect Lighting의 원인 구분 | High |
| Fig7_05.png | 07 / 7.5 | C07-02 Fresnel / Rim | 반사율 변화·입사광에 의한 밝기·스타일용 View Mask 구분 | High |
| Fig7_06.png | 07 / 7.6 | C07-06 Hair 분류 | Strand·Highlight 방향과 산란 종류 레이블 | Medium |
| Fig7_07.png | 07 / 7.7 | C07-07 Face 방향·Mask | Light / Face 방향 관계, 고정 Mask와 Light-responsive 표현 구분 | Medium |
| Fig7_08.png | 07 / 7.8 | C07-08 Outline 분류 | Geometry·Normal Expansion·Screen-space Edge 처리의 포함 관계와 입력 | Medium |
| Fig7_09.png | 07 / 7.9 | C07-03/09 공통 연산 | 입력 축·범위·출력·전이 폭, Smoothstep의 AA 효과를 보편화하는 표기 여부 | Medium |
| Fig9_02.png | 09 / 9.2 | C09-01 Pipeline | Frame 간 Overlap, 단순 합이나 무조건적 최대값=Frame Time 표기 여부 | High |
| Fig9_03.png | 09 / 9.3 | C09-02/03/05 Geometry | Triangle·Vertex·Screen Size, Cost Type / Pass 범주와 작은 Triangle 표현 | Medium |
| Fig9_04.png | 09 / 9.4 | C09-04/05 중첩과 Quad | Surface Overdraw와 Quad 비효율 구분, Hair Blend Mode 전제 | High |
| Fig9_05.png | 09 / 9.5 | C09-06 및 연산 제거 | Lerp A/B/Mask 입력과 결과, Node 수·Runtime 0·제거의 관계 | High |
| Fig9_06.png | 09 / 9.6 | C09-07/08 작업 분할 | CPU 준비·제출과 GPU 작업, Triangle·Slot·Section·Pass·Draw의 무조건적 일대일 대응 여부 | Medium |
| Fig9_07.png | 09 / 9.7 | C09-09/10 Visibility | LOD Detail / Index, Camera Cull과 다른 Pass·Update, 복합 변경의 단일 원인 단정 여부 | High |
| Fig9_08.png | 09 / 9.8 | C09-05/11 Tool 의미 | Quad 단위·출력 Pixel, 레이블·범례·버전 조건, Debug View가 실제 ms라는 인상 여부 | High |

Fig7_01, Fig7_03, Fig9_01, Fig9_09는 별도의 특정 시각 결함을 의심할 텍스트 근거가 충분하지 않아 Queue에 추가하지 않았다. 해당 이미지의 Visual Content가 승인되었다는 뜻은 아니다.

검토 원본 식별값(SHA-256):

- Chapter 07: `BE46AE19C8E2607BE9979C78BC3463E2D7304CA665B171E112AD5AC2347942B9`
- Chapter 09: `9F93167CDF38E4D1AB896E52168D0C43C476A6C74863416AAE37BDF6DF26E07B`

최종 범위: Chapter 07 / Chapter 09 Text Audit만 수행했다. Chapter 08 Audit, Foundation Refactoring, Figure Visual Review는 수행하지 않았다.
