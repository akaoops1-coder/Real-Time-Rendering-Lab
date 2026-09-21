# Foundation Audit — Chapter 08

Phase 1A — Text Audit · 2026-09-20

범위: `C:\Users\kmcoo\Desktop\PW\ASF_Review` 내부 Chapter 08 Markdown 12개(개요와 8.0–8.10). 실제 위치는 `00_Foundation/Chapter08_BuildingAnAnimeShader/`이다. 이전에 사용자가 정정한 루트를 적용했다. 원문·Figure·Implementation은 변경하지 않는다. 이미지 내용은 열람하지 않는다. Section 단위로 결과를 저장하며 맨 아래 Progress만 현재 상태로 갱신한다.

기준: `00_Project/ASF/`의 ASF-000 Project Principles, ASF-001 Naming Philosophy, ASF-002 Rendering Architecture, ASF-003 Documentation Standard를 최우선 적용한다. `00_Project/ASF_Standard.md`, Project Management의 Roadmap / DecisionLog는 보조 기준이다. 이전 감사 결과를 현재 원문에 대한 판정으로 자동 승계하지 않는다. 외부 조회·Engine 실행 검증은 이번 범위에 없으며 확인이 필요한 구현 동작은 Needs Technical Verification로 남긴다.

## 1. Executive Summary

Chapter 08은 Foundation 개념을 실제 Function 계약·Master 합성·MI 제어·Debug로 연결하는 구현 Chapter로서 방향이 적절하다. Input / Processing / Output을 먼저 소개하는 부분과 재사용 가능한 Scalar Mask 설계가 있어 단순 Node Tutorial이나 Effect 목록으로만 볼 수 없다. 다만 동일 이론·UI 절차·요약의 반복이 길고, 최종 도식이 실제 함수 계약을 따르지 않아 Architecture의 신뢰도를 떨어뜨린다.

가장 잘 된 부분은 8.3의 Shadow Map / Visibility 구분과 미구현 범위 고지, 8.7의 현재 UV 위치 Sample → 채널 Scalar → MF_Emission 입력 설명, 8.8의 함수 복제 없는 Region 제어, 8.9의 기존 계산 결과 재사용이다. Emission이 Texture 전체를 Scalar로 바꾼다고 잘못 설명한다는 지적은 해당하지 않는다. 기본 구현·Debug·MI·Module 통합은 Foundation에 유지해야 한다.

반드시 먼저 정리할 사항은 (1) Deferred 환경과 Forward Light 입력의 재현 조건, (2) Module / MF / GPU Stage 구분 및 실제 분기 Data Flow, (3) Base Multiply / MatCap Lerp / Emission Add 합성 계약, (4) Rim 경계값과 MatCap 비활성 조건, (5) Debug Mode 5의 타입·의미 및 화면색과 선형 데이터의 차이이다. Shadow는 전역 Scalar 적용 검증, Region은 독립 테스트까지이며 Renderer Shadow 생성이나 Region 최종 통합이 완료된 것으로 확대하면 안 된다.

이번 판정은 로컬 문서의 Text Audit이다. 이미지 내용·Engine 실행·Compiler·성능은 검증하지 않았다. 불확실한 Engine 동작은 Needs Technical Verification로 남겼다. 8.0–8.10 개별 결과를 순차 저장한 뒤 아래 종합 결과를 추가했다. 수치 점수나 등급은 부여하지 않는다.

## 2. Global Chapter 08 Issues

| 영역 | Severity / Action | 근거와 종합 판단 | 후속 권고 |
|---|---|---|---|
| Architecture | High / Rewrite | 08-01-A/B, 08-10-A. Master를 전체 Rendering Pipeline으로 부르거나 독립 함수들을 직렬 Stage처럼 연결한다. | GPU Stage ≠ 기능 Module ≠ MF 구현 단위를 명시하고 공유 입력 분기와 합성 연산을 그린다. |
| Data Flow / Composition | High / Rewrite | 08-06-C/D, 08-07-E, 08-08-A, 08-10-B. + 표기, Lerp, 함수 안팎의 Intensity 위치가 실제 계약과 다르다. | 최종 합성식을 기준으로 모든 중간 도식을 정렬한다. 학습 순서와 계산 의존성을 구별한다. |
| 재현 환경 / 검증 | High / Expand / Needs Technical Verification | 08-02-B/C, 08-07-B/C, 08-09-B, 08-10-C. Renderer·Material 설정과 Exposure 조건이 흩어져 있다. | 공통 환경표와 테스트별 변경값을 두고 Unlit 선행 설정, Light 방향·Space, 고정 노출을 명시한다. |
| 계약·경계값 | High / Expand | 08-05-C, 08-06-D, 08-09-A/C. Smoothstep 경계, MatCap off, Debug Scalar/Vector3가 일관되지 않는다. | 타입·단위·Space·범위·기본값·비활성값·예외 입력 동작을 최종 계약표로 통합한다. |
| 완료 범위 / Responsibility | Medium / Expand | 8.3, 8.8, 8.9에는 Shadow/Region 한계가 명시되어 있으나 중간 요약에서 유지되지 않는다. | 현재 지원/테스트 전용/미통합을 전 절에서 동일하게 표시한다. Specular 차폐 정책은 물리 기반과 의도적 스타일 편차로 구분한다. |
| Continuous → Stylized 연결 | Medium / Expand | 7.2 ASF Implementation은 Lambert 뒤 Threshold/Ramp를 예고한다. 8.2는 연속 응답이고 8.3의 실제 구현은 Visibility Multiply이다. | 아래 종합 보충 08-G-01처럼 구현 범위를 연결한다. Rim의 Smoothstep을 Diffuse remap 구현으로 간주하지 않는다. |
| Duplication / Implementation Density | Medium / Shorten / Merge / Keep | 8.0 준비 원칙, 8.3 Bias/PCF, 8.5 Fresnel, 8.7 HDR/Mask, 8.9–8.10 목록·요약 반복. | 첫 구현·핵심 검증은 유지하고 정의·원칙·중복 UI 안내는 Primary Source로 모은다. 분량 자체를 결함으로 삼지 않는다. |
| Naming / Heading / Cross Reference | Medium 또는 Low / Rewrite | MF_Lighting과 MF_BaseLighting, MaterialLayer와 실제 Region 범위, copy/Framwork, 내부 번호와 다수 H1, 구 Roadmap 링크. | 기준 권위는 ASF-001/003에 두고 실제 파일·역할·Roadmap으로 맞춘다. Outfit 결정은 부위명에 적용한다. |
| Foundation 경계 | Medium / Keep / Move | 구현·MI·Debug를 Advanced로 옮길 근거는 없다. 실제 제작 최적화·대량 변형·Renderer 내부 구현은 별도 범위이다. | 아래 경계표대로 기본 검증을 남기고 심화 실행 과제만 이동 후보로 둔다. |

### 종합 보충 08-G-01 — Stylized Diffuse 범위 연결

- Section: 8.2 Overall Assessment에 대한 최종 교차 확인; 8.3 실제 구현; 8.10 지원 범위.
- Severity: Medium.
- Action: Expand / Rewrite.
- Issue: 8.2의 연속 Lighting을 뒤에서 어떤 Stylized 응답으로 전환하는지 최종 범위가 충분히 연결되지 않는다. 앞선 개별 평가의 ‘8.3 연결을 위한 의도적 범위’는 최종 구현 완료를 의미하지 않는다.
- Reason: Chapter 07.2의 ASF Implementation은 Lambert 뒤 Threshold/Ramp를 소개하지만 현재 8.3은 Visibility 적용이다. 차폐와 Lighting Response remap은 서로 다른 계산이다.
- Related Section: Chapter 07.2 / 07.9; 08-02-D; 08-03-A; 8.10.
- Recommendation: 이번 Chapter의 Base는 연속 응답 기반의 Framework 검증이라는 범위를 명시하고, Stylized remap의 삽입 위치와 후속 연결을 짧게 설명한다. 직접 구현을 목표로 유지한다면 최소 Threshold/Smoothstep 비교와 기본 검증을 Foundation에 보강한다. 완전한 제작용 Toon 시스템을 의무화하지 않는다.

Action 보조 표현의 의미: 개별 기록의 Clarify / Align / Correct는 Rewrite 또는 Expand, Condense는 Shorten / Merge, Verify는 Needs Technical Verification에 해당한다. 이들은 원문 수정 실행 기록이 아니라 후속 권고이다.


## 3. Section-by-Section Audit

### 8.0 Preparing the ASF Project

**Overall Assessment**

대상: `Chapter08.0_PreparingTheASFProject.md` 전체 및 `Chapter08_BuildingAnAnimeShader.md` 개요. 동일 프로젝트에서 구현을 누적하고 환경을 먼저 확인하는 방향은 Keep이다. Framework / Test 분리, Git의 작은 변경 단위, Checkpoint는 기본 구현 재현성에 필요하므로 Advanced로 보낼 이유가 없다. 다만 Production 일반론과 동일 규칙을 반복하는 비중이 높다.

#### 08-00-A — 학습 순서와 현 Roadmap 충돌

- Section: 8.0.1 Development Workflow; 8.0 마지막 Next Chapter; 개요 Summary / Expected Result.
- Severity: High.
- Action: Rewrite.
- Issue: Chapter 9를 Character Rendering 또는 핵심 구현 시작, Chapter 10을 Optimization으로 소개한다. 같은 8.0 파일 내부에서도 다음 단계 목적이 다르다.
- Reason: 현재 로컬 Roadmap의 Chapter 09는 Rendering Debug and Optimization이며 8.1–8.10이 실제 구현이다. 이후 Section을 찾는 학습 경로를 오도한다.
- Related Section: 8.1–8.10; Roadmap Foundation Chapters.
- Recommendation: 8.0 다음은 8.1, Framework 구현은 Chapter 08 내부, 측정·최적화 Foundation 연결은 Chapter 09로 바로잡는다. 별도 Character Application / Advanced 목적지는 현재 Roadmap의 이름으로 연결한다. 새 Chapter 10을 가정하지 않는다.

#### 08-00-B — Standard와 별개인 고정 Naming / 구조 규칙

- Section: 8.0.5–8.0.7; 8.0.9 Development Principles.
- Severity: Medium.
- Action: Rewrite / Merge.
- Issue: 초기 폴더·이름을 변경하지 않는 규칙을 반복하고 Prefix + PascalCase를 모든 Asset의 유일 형식으로 선언한다. 특수문자 금지와 예시의 underscore 관계도 설명하지 않는다.
- Reason: ASF-001은 역할·Architecture에 따라 이름을 개선하며 의미 있는 Debug / Experimental Context를 허용한다. Foundation이 새 Source of Truth가 되면 기준이 분산된다.
- Related Section: ASF-001 Naming Must Survive Refactoring / Naming Is Refactored with Architecture; ASF-003.
- Recommendation: 초기 규칙은 재현을 위한 예제 구성으로 제시하고 Naming의 권위는 ASF-001로 연결한다. 무계획 변경을 피하되 필요한 Refactoring은 Reference 확인과 함께 가능하다고 정리한다. Prefix 구분용 underscore는 허용된 형식임을 명시한다.

#### 08-00-C — Engine 환경과 실험 관찰 조건

- Section: 8.0.1–8.0.4; 개요 Development Rules.
- Severity: Medium.
- Action: Expand / Needs Technical Verification.
- Issue: UE 5.8 / DX12 / SM6 / Lumen / VSM / TSR을 기준으로 하고 대부분 기본값이라고 쓰지만 정확한 Build·Template 조건과 후속 Custom Lighting 관찰 조건이 없다.
- Reason: 버전 명시 자체는 좋지만 UI·기본값·지원 기능이 실제 환경과 같은지는 본문만으로 검증되지 않는다. Exposure·Post Process·Scene Light가 구현 결과에 미치는 영향도 분리해야 한다.
- Related Section: 8.2 이후 Material Output / Debug 검증.
- Recommendation: 프로젝트에서 실제 확인한 Engine Build와 Renderer / Material 설정을 기록한다. 기본값을 신뢰하는 대신 현재 표의 체크를 유지한다. 이후 Unlit / Lit 선택과 Exposure의 관계를 해당 구현 절로 연결한다. 5.8의 가용성이나 기본값을 외부 근거 없이 맞다/틀리다로 확정하지 않는다.

#### 08-00-D — 폴더 분리와 Dependency 제거를 동일시

- Section: 8.0.2 Starter Content; 8.0.6 Separation of Responsibilities.
- Severity: Medium.
- Action: Rewrite / Expand.
- Issue: ASF / StarterContent 폴더를 나누면 Starter Content를 제거해도 ASF에 영향이 없다고 단정한다. ASF의 Maps / Meshes / Debug에는 테스트 Asset도 포함된다.
- Reason: 파일 위치의 분리와 참조 의존성의 분리는 다르다. ASF 안의 Demo Map이 Starter Mesh 등을 참조할 수 있다.
- Related Section: 8.0.5 Framework and Test Assets; 이후 Test Scene.
- Recommendation: 재사용 Core와 Demo / Test의 참조 방향을 구분한다. Core가 StarterContent를 참조하지 않는지 확인한 경우에만 독립 배포를 주장한다. 폴더 이름만으로 독립성을 보장하지 않는다.

#### 08-00-E — 환경 준비 설명의 반복 밀도

- Section: 8.0.1–8.0.3 환경 표; 8.0.2/5/6 프로젝트 구조; 8.0.9와 Chapter Summary.
- Severity: Medium.
- Action: Merge / Shorten / Keep.
- Issue: 하나의 프로젝트, Production-Oriented, 폴더 불변, Starter 분리가 Purpose / Tip / Checkpoint / Summary에서 같은 결론으로 반복된다.
- Reason: 새로운 조작·판단이 없는 Unnecessary Duplication이다. 필요한 실제 생성·설정 확인 Step은 중복과 다르다.
- Related Section: ASF-000 Concept Before Tool; ASF-003 Duplication.
- Recommendation: 환경 표 한 곳, 구조 표 한 곳, 실제 생성·검증 절차와 최종 Checkpoint를 유지한다. 기능 안정화 후에만 최적화한다는 일반론은 기본 비용 관찰과 상세 최적화를 구별하도록 제한한다. Git 기초는 Keep하며 Production 자동화로 확장하지 않는다.

#### 08-00-F — Heading / 임시 Figure 표기 / 명칭

- Section: 개요 전체; 8.0.1–8.0.9 H1; 개요 Figure 8-1 placeholder와 Cloth.
- Severity: Low.
- Action: Rewrite / Expand.
- Issue: 내부 8.0.n이 H1이며 개요도 다수 H1이다. 개요 Figure 8-1은 이미지 경로 없는 설명 placeholder이다. Character 부위에 Cloth를 쓴다.
- Reason: 요청의 Chapter H1 / Major H2 / Internal H3 체계 및 ASF-003, Outfit 명칭 결정과 맞지 않는다.
- Related Section: ASF-003; DecisionLog DEC-001; 8.1 Figure 참조와 후속 대조 필요.
- Recommendation: Major 8.0 아래 내부 무번호 Heading으로 정리한다. 개요 Diagram이 기존 Figure 참조인지 미작성 항목인지 명시한다. 의상 부위는 Outfit으로 맞추되 Cloth Simulation / 직물 의미는 별개이다.

### 8.1 Architecture Overview

**Overall Assessment**

`Chapter08.1_ArchitectureOverview copy.md` 436 lines 전체 검토. Input → Processing → Result, Master의 Composition 책임, 독립 검증, 내부 구현과 외부 인터페이스 분리는 Keep이다. Node 목록 이상의 Architecture 설명이 이미 있다. 다만 Stage와 Module의 언어적 경계와 다이어그램의 데이터 의존 관계가 일치하지 않는다.

#### 08-01-A — Material Composition을 Rendering Pipeline으로 표현

- Section: 8.1.5 / 8.1.6.
- Severity: High.
- Action: Rewrite / Expand.
- Issue: Master Material이 ‘전체 Rendering Pipeline’을 조합한다고 하고 Module 사이 전달을 Pipeline의 앞 단계→다음 단계로 소개한다.
- Reason: ASF-002에서 GPU Stage, Rendering Module, Material Function은 별개이다. MF는 기능 구현 단위이며 Master가 Rasterization 등 Engine Pipeline을 조립하는 것은 아니다.
- Related Section: ASF-002 Stage / Module / Material Function; 8.10.
- Recommendation: Master는 Material 내부의 Function Composition과 최종 Material Output을 구성한다고 명시한다. MF는 Module의 Unreal 구현 수단이며 GPU 실행 Stage나 독립 Draw / Pass라는 뜻이 아니라고 구분한다.

#### 08-01-B — 병렬 입력과 직렬 의존 화살표 혼재

- Section: 8.1.2, 8.1.3, 8.1.6, 8.1.7.
- Severity: Medium.
- Action: Rewrite / Expand.
- Issue: 공통 Input에서 Module로 분기하는 구조와 Base Lighting→Shadow→Specular 직렬 구조가 혼재한다. Surface Data→Lighting Data 그림은 후자가 전자에서 생성되는 듯 보인다. 본문은 Specular가 N/L/V로 별도 계산된다고 설명한다.
- Reason: 모든 Module이 같은 순서를 따르지 않는다는 주의는 좋지만 실제 의존성과 표현 순서가 여전히 다르다.
- Related Section: 8.2–8.7의 실제 Input / Output; 8.10 통합.
- Recommendation: Surface·Light·View를 공통 입력 묶음으로 놓고 각 Module의 실제 의존 edge를 표시한다. Base Lighting / Shadow가 Scalar를 반환할지 Color를 반환할지는 후속 구현과 대조해 계약을 확정한다. 개요 예시와 최종 계약이 다르면 명시적으로 구분한다.

#### 08-01-C — Figure 식별자 재사용 충돌

- Section: 8.1.5 Fig8_03; 8.1.6 Fig8_04; 8.1.7 Fig8_05.
- Severity: Medium.
- Action: Rewrite / Visual Review Required.
- Issue: 동일 상대 경로가 8.0에서는 Project Creation / Settings / Content Structure를, 여기서는 Architecture / MF-Master 관계 / Data Flow를 뜻한다.
- Reason: 하나의 파일을 서로 다른 설명에 연결한다. 이미지 자체는 열지 않았으므로 어느 Caption이 맞는지 확정하지 않는다.
- Related Section: 8.0.3/4/6; Figure Review Queue.
- Recommendation: Figure Registry에서 번호·파일·Caption·사용 위치를 대조하고 각 개념의 올바른 참조를 지정한다. 후속 Visual Review에서 실제 Figure와 Caption을 확인한다.

#### 08-01-D — 문서명과 Heading / 중복

- Section: 파일명 `ArchitectureOverview copy.md`; 8.1.1–8.1.9; 8.1.8 번호 목록; Summary.
- Severity: Low.
- Action: Rewrite / Merge / Keep.
- Issue: 파일명에 copy가 남고 내부 Heading에 8.1.n 및 추가 번호가 있다. Module 분리 장점과 같은 구조 요약이 여러 차례 반복된다.
- Reason: 최종 Source와 작업 사본이 모호하고 요청 Heading 원칙과 다르다. 같은 원칙 재서술은 Unnecessary Duplication이지만 Data Flow 예제는 Necessary Reinforcement이다.
- Related Section: ASF-001/003; 8.0 및 8.10.
- Recommendation: 실제 canonical 파일을 확정한 뒤 이름과 링크를 정리할 대상으로 기록한다. 원본은 이번에 변경하지 않는다. Module / Master / 계약 설명을 유지하고 반복 결론만 통합한다. Material Instance와 Debug 통합은 후속 절 완료 후 전체 누락 여부를 판정한다.

### 8.2 Base Lighting

**Overall Assessment**

`Chapter08.2_BaseLighting.md` 976 lines 전체 검토. 역할·Interface를 먼저 정의한 뒤 Normalize → Dot → Saturate → Base Color 적용을 구현하고 테스트 입력을 실제 Light 입력으로 교체하는 순서는 Keep이다. Scalar Lighting Data와 RGB Lighting Result 구분도 좋은 계약이다. Threshold / Smoothstep을 이 절에서 구현하지 않는 것은 8.3의 Stylization 연결을 위한 의도적 범위이며 자체 누락으로 판정하지 않는다.

#### 08-02-A — Light Direction의 부호·Space 계약

- Section: 8.2.1 L83–115; 8.2.2 Normalize / Dot; 8.2.3 Direction 연결.
- Severity: High.
- Action: Rewrite / Expand / Needs Technical Verification.
- Issue: 도식은 Light에서 Surface로 향하는 화살표인데 본문은 N과 L이 같으면 정면 조명이라고 설명한다. PixelNormalWS와 연결할 Light 출력의 Space·방향 convention도 명시하지 않는다.
- Reason: dot(N,L)에서 보통 L은 Surface→Light 방향이어야 한다. Normalize는 길이만 맞추며 반대 부호나 다른 Space를 고치지 않는다.
- Related Section: 8.3 Shadow; 8.4 Specular; ASF-002 Rendering Data / Space.
- Recommendation: `NormalWS`, `SurfaceToLightDirectionWS`, nonzero / normalized 전제를 계약에 명시한다. 실제 Engine 노드 출력의 방향·Space는 대상 버전에서 확인하고 필요한 경우 경계에서만 변환한다. N=(0,0,1), L=(0,0,1) / (1,0,0) / (0,0,-1)의 결과 1/0/0을 Basic Verification으로 둔다.

#### 08-02-B — Deferred 기준과 Forward Light 접근 조건의 미해결 의존성

- Section: 8.2.3 L625–677; 8.2.4 L897–921.
- Severity: High.
- Action: Expand / Needs Technical Verification.
- Issue: 8.0은 Deferred Rendering 기준인데 여기서는 Forward Shading의 `Forward Selected Directional Light`를 곧바로 실제 연결 경로로 사용한다. 지원 Domain / Shading Model / Renderer 조건과 재현 근거가 없다.
- Reason: 뒤 Module이 이 데이터 접근에 의존하므로 해당 구성에서 Node가 제공되고 올바른 값을 내는지 확인되지 않으면 구현 전체를 재현할 수 없다. 노드 이름만으로 Deferred에서 불가능하다고 확정하지는 않는다.
- Related Section: 8.0.4; 8.3 Shadow Visibility; 8.10.
- Recommendation: 실제 UE Build·Project Renderer·Material Domain / Blend / Shading Model·Main Light 선택 조건을 함께 기록한다. 동일 조건에서 컴파일·Light 회전·복수/무광원 결과를 검증한다. 역사적 ‘예전에는 없고 현재 가능’ 일반론은 축약하고 실제 지원 범위에 집중한다.

#### 08-02-C — Emissive 출력만으로 Engine Lighting 제거 단정

- Section: 8.2.2 L528–563; 8.2.1 L53–61.
- Severity: High.
- Action: Rewrite / Expand / Needs Technical Verification.
- Issue: Lighting Result를 Emissive Color에 연결한 뒤 실제 Directional Light 영향이 제거된다는 설명에 Material Shading Model 등 설정이 없다. Base Color만 출력하면 동일색이라는 표현도 출력 경로 조건이 빠져 있다.
- Reason: Emissive 연결 자체가 다른 Lit 경로를 비활성화하는 것은 아니다. 결과색과 실제 관찰색에는 Exposure / Tone Mapping도 개입한다.
- Related Section: 8.0 Renderer; 8.9 Debug; 8.10 Final Output.
- Recommendation: 격리 검증용 Material의 Domain·Shading Model·다른 Output·Exposure 조건을 명시한다. 단일 구의 밝기만으로 검증 완료를 단정하지 말고 Scalar Data와 Color Result를 각각 관찰한다. 최종 Framework 경로와 테스트 경로를 구별한다.

#### 08-02-D — 각도 계수를 실제 조명량으로 확대하고 Interface를 중복 집계

- Section: 8.2.2 Lighting Data; 8.2.4 L830–839, L878–881.
- Severity: Medium.
- Action: Rewrite / Expand.
- Issue: saturate(N·L)을 직접 조명의 양이라고 표현하고 Light Direction과 그 출처인 Directional Light 정보를 네 번째 독립 Input으로 다시 센다.
- Reason: 구현에는 Light Color / Intensity / Visibility 등이 없으므로 방향 기반의 단위 계수이지 완전한 조명량이 아니다. 데이터 출처와 Function Input은 다른 수준이다.
- Related Section: 8.1 계약; 8.3 / 8.4 / 8.10의 Light 데이터 재사용.
- Recommendation: 입력은 N,L,BaseColor의 실제 3개로 정리한다. Lighting Data는 0–1 방향 계수, Result는 BaseColor×계수인 단순화된 기본 응답이라고 정의한다. Color / Intensity를 생략한 의도와 후속 통합 위치를 명시한다.

#### 08-02-E — 텍스트 도식의 연결 방향과 반복 요약

- Section: 8.2.2 L442–454, L487–518; 8.2.3 L696–714; 8.2.4 전체; 내부 Heading.
- Severity: Medium.
- Action: Rewrite / Merge / Keep.
- Issue: 도식에서 Normal 아래에 Saturate가 이어지거나 Multiply 결과 대신 Lighting Data / Base Color에서 Result로 화살표가 이어져 실제 수식과 다르게 읽힌다. 전체 과정과 Engine 접근 설명이 반복된다.
- Reason: Data Flow 우선 원칙에서 도식은 실제 의존성을 보여야 한다. 단순 결론 반복은 Unnecessary Duplication이다.
- Related Section: 8.1 Flow; ASF-003 Heading.
- Recommendation: `Dot(normalize(N),normalize(L)) → Saturate → Data`, `Data + BaseColor → Multiply → Result` 연결을 명확히 한다. 첫 구현 Step은 Keep, 후반은 계약·기대값·다음 절 연결로 줄인다. 8.2.n 번호와 H4 혼재는 Low 수준 Heading 정리 대상으로 함께 기록한다.

### 8.3 Shadow System

**Overall Assessment**

`Chapter08.3_Shadow.md` 5,370 lines 전체 검토. N·L과 Visibility, Shadow Map의 Depth와 비교 결과, Shadow Map과 Lightmap, PCF의 비교 후 평균과 물리적 Soft Shadow를 구분한 설명은 Keep이다. 특히 L4905–4953은 MF_Shadow가 Map을 생성하지 않는 Visibility Application Module이라고 정확히 제한한다. L5114–5145는 Unlit Material에 Renderer Visibility가 자동 공급되지 않으며 실제 통합은 미완료임을 명시한다. 따라서 ‘실제 Shadow 연결을 이미 구현했다고 거짓 설명한다’는 판정은 하지 않는다. Scalar 1/0.5/0 테스트는 Foundation에 적합하다.

후속 확인: 8.3 L5118에서 Unlit 구조가 처음 명확해졌다. 08-02-C는 Chapter 전체에서 Unlit이 없다는 뜻이 아니라 8.2 최초 테스트 Step에서 선행 설정/참조가 부족하다는 문제로 범위를 제한한다.

#### 08-03-A — Shadow Module의 구현 완료 범위와 후속 계약

- Section: 8.3.7 L4957–5145, L5189–5237.
- Severity: Medium.
- Action: Expand / Keep.
- Issue: Visibility를 곱하는 계약과 실제 Renderer 연결의 미완료는 명확하지만 이후 통합에서 어떤 입력을 쓸지 전달 규칙이 부족하다. ShadowedLighting에 Specular를 단순 더하는 예시에는 동일 Light Visibility 적용 정책이 없다.
- Reason: 실제 Direct Specular도 같은 Light의 차폐 조건을 고려해야 한다. 가독성을 위한 비차폐 Highlight를 허용한다면 의도적 Deviation이어야 한다. Runtime 전역 Scalar는 공간적으로 다른 Cast Shadow를 제공하지 않는다.
- Related Section: 8.4 Specular; 8.10 Final Framework; 08-02-B.
- Recommendation: 이 단계는 Visibility Application 검증 완료 / Renderer Integration 미완료로 표시한다. 최종 통합에서 테스트 Scalar와 실제 Surface별 Visibility를 명시적으로 구분한다. 동일 Light Direct Contribution에 Visibility를 어디서 적용하는지 계약에 적고 이중 적용을 피한다. Renderer Integration 상세는 Advanced 후보이나 현재 한계 설명은 Foundation에 반드시 남긴다.

#### 08-03-B — Shadow Mask의 이름 범위와 Artistic Mask

- Section: 8.3.7 L4532–4566, L5285–5290, L5342–5347.
- Severity: Medium.
- Action: Expand.
- Issue: Shadow Mask를 Depth 비교의 Visibility 결과라고 정의하지만 Artist-authored Mask와 구별하는 명칭이 없다.
- Reason: 여기의 Engine Shadow Mask는 Visibility를 저장/전달하는 표현이므로 별개의 물리량이라고 강제로 분리할 필요는 없다. 다만 후속 스타일용 Mask와 같다고 읽히면 출처·의미가 혼합된다.
- Related Section: 8.7 Mask Value; 8.8 Layer Mask; 8.9 Debug.
- Recommendation: Shadow Map=Depth resource, Visibility=특정 Light/Surface 관계의 값, Renderer Shadow Mask=그 결과의 표현, Artistic Mask=별도 저작 제어라는 역할 표를 둔다. 모든 Shadow Mask가 Shadow Map으로만 생성된다는 보편 정의로 확대하지 않는다.

#### 08-03-C — Depth 비교와 Ray 수식의 전제

- Section: 8.3.3 L933–940; 8.3.4 Light Space / Depth Comparison; 8.3.5 Bias L2981, L3550.
- Severity: Medium.
- Action: Expand / Rewrite.
- Issue: t를 거리로 정의하면서 D의 단위 길이 전제를 밝히지 않는다. Light-space Depth를 거리처럼 설명하고 비교 부등호를 일반식처럼 제시한다.
- Reason: t가 실제 거리이려면 D가 정규화되어야 한다. 비교 양쪽은 같은 Projection / Encoding이어야 하며 깊이 저장 convention에 따라 부등호가 달라질 수 있다. Light View 변환만으로 Sample 좌표까지 완성되는 것도 아니다.
- Related Section: ASF-002 Space; 8.3.4 L1791–1889.
- Recommendation: Ray의 단위 방향 전제, World Position → Light View/Projection → 조회 좌표와 비교 Depth라는 최소 흐름을 보강한다. 예제는 ‘멀수록 큰 깊이, 같은 표현과 범위’라고 제한한다. Reversed Depth·Bias 구현은 기술 검증/심화에 남기고 행렬 코드까지 추가하지 않는다.

#### 08-03-D — Debug View 재현 정보와 Artifact 원인

- Section: 8.3.7 L4428–4451, L4570–4580, L4689–4722.
- Severity: Medium.
- Action: Expand / Needs Technical Verification / Visual Review Required.
- Issue: Shadow Debug가 어떤 모드·명령인지 명시하지 않고 색 변화만으로 Depth/Shadow 정보를 관찰했다고 설명한다. 해상도 부족 뒤에 Acne·Peter Panning까지 한 목록으로 이어진다.
- Reason: 실제 모드는 Depth·Visibility·Page/Cache 등 서로 다른 정보를 보여줄 수 있다. 8.0의 VSM 설정과 일반 Shadow Map 이론을 연결할 재현 조건이 필요하다. Artifact의 후보 원인들은 동일하지 않다.
- Related Section: 8.0.4 VSM; 8.3.5 Bias / Filtering; 8.9.
- Recommendation: 실제 사용 모드·버전·Light Mobility·Cast Shadow·관찰 데이터와 범례를 기록한다. Aliasing / Depth·Slope 오차 / 과도한 Bias를 별도 원인 후보로 둔다. Fig8_35와 Fig8_39/40은 이미지 검토 없이는 표시 데이터와 원인을 확정하지 않는다.

#### 08-03-E — 이론 재설명과 동일 절 안의 반복

- Section: 8.3.1–8.3.6; 특히 8.3.5 L2878–3066과 L3494–3629; 8.3.7 후반 재요약.
- Severity: Medium.
- Action: Merge / Shorten / Keep / Move.
- Issue: N·L/Visibility, Ray/Map, Map/Lightmap 비교를 여러 번 다시 전개한다. Acne→Bias→Peter Panning은 같은 절 안에서 두 번 설명한다. Texture / Texel 기초도 긴 독립 강의로 재시작한다.
- Reason: 기본 연결은 Necessary Reinforcement이나 동일 정의·수치·결론 반복은 Unnecessary Duplication이다. Module 구현의 계약과 관찰 방법이 긴 이론 뒤로 밀린다.
- Related Section: 앞 Foundation Rendering Data / Texture / Shadow 개념; 8.3.7 MF_Shadow.
- Recommendation: Visibility→Depth compare→Application의 핵심 설명과 PCF 작은 예제는 Keep한다. Texture 정의는 앞 Foundation으로 연결하고 Shadow Texel에 필요한 차이만 남긴다. 상세 Engine Shadow 최적화·통제 성능 실험이 추가되면 Advanced로 이동하되 현재 기초 원리와 Sphere 관찰 자체는 이동하지 않는다.

#### 08-03-F — 학습 단계 표현과 기호 일관성

- Section: 8.3.6 L4257–4277; 8.3.7 기술적 한계 예고; 내부 8.3.n H1; L3862.
- Severity: Low.
- Action: Rewrite / Expand.
- Issue: 이미 설명한 Bias / Filtering을 이후에 처음 다룰 것처럼 예고한다. Li가 이미 차폐를 반영한 입사 Radiance인지 차폐 전 Light contribution인지 기호 전제가 약하다. H1 내부 번호와 문장 끝 잔여 hyphen이 있다.
- Reason: 반복 예고는 기준 위치를 흐리고 Visibility를 이중 곱하는 해석을 피할 필요가 있다.
- Related Section: 8.3.5; 이전 Rendering Equation; ASF-003.
- Recommendation: 기초 원인은 8.3.5를 참조하고 상세 Engine 설정만 후속 대상으로 둔다. 식은 차폐 전 직접광 항에 Visibility를 한 번 적용하는 개념 예제라고 제한한다. cos 항도 유효 입사 반구의 비음수 계수임을 명시한다. Heading은 Major 아래 무번호 내부 제목으로 정리한다.

### 8.4 Specular

**Overall Assessment**

`Chapter08.4_Specular.md` 1,733 lines 전체 검토. L=Surface→Light, V=Surface→Camera, 같은 Space, 정규화, R=2(N·L)N−L을 명시한 점은 Keep이다. 후반 MF_Specular가 Scalar Mask만 출력하고 Master가 Color / Intensity를 적용하는 분리는 명확하다. 8.2의 방향 계약은 이 절을 최초 사용 위치로 앞당겨 연결하면 개선된다.

#### 08-04-A — Phong Response와 Unreal Specular 입력의 혼동

- Section: 8.4.6 L1136; 8.4.7 L1154–1269; MF_Specular L1374–1410.
- Severity: High.
- Action: Rewrite / Needs Technical Verification / Visual Review Required.
- Issue: 계산한 Phong Response를 Material의 Specular 입력에 넣으면 해당 Highlight가 출력된다고 설명한다. 후반은 Mask×Color×Intensity를 별도 Contribution으로 합성한다.
- Reason: Unreal Lit Material의 Specular 입력은 일반적으로 반사율 제어용 Material 속성이며 이미 계산한 조명 결과를 그대로 출력하는 포트가 아니다. 8.3의 Unlit Emissive 구조와도 맞지 않는다. 정확한 Pin 사용은 대상 Shading Model에서 검증해야 한다.
- Related Section: 8.3 L5118; 8.10 Final Output; Fig8_19/49.
- Recommendation: Lit의 반사율 제어 실험과 ASF Unlit의 Custom Specular 합성을 분리한다. 최종 ASF 경로는 Mask→Color/Intensity→Composition으로 일치시킨다. Fig8_19의 실제 Output 연결은 Visual Review Required이다.

#### 08-04-B — Power 입력 범위가 후반에만 교정됨

- Section: 8.4.5–8.4.7의 (R·V)^n; MF_Specular L1526–1534.
- Severity: High.
- Action: Rewrite / Expand.
- Issue: 앞 구현은 R·V→Power를 직접 제시하고 0–1 범위를 가정한다. 후반 Module에는 Saturate가 존재한다.
- Reason: 정규화된 방향의 Dot도 음수가 가능하다. 비정수 지수에 음수 입력을 주는 수식은 안전한 정의가 아니며 앞뒤 구현이 다르다.
- Related Section: 8.2 Dot 범위; 8.5 Rim Power.
- Recommendation: 최초 구현부터 Pow(saturate(dot(R,V)), Shininess)를 동일하게 사용한다. Shininess의 양수 하한을 정의하고 0·음수·0^0 경계 처리 정책을 둔다. 후반에 Clamp가 없다는 판정은 하지 않는다.

#### 08-04-C — Direct Light의 유효 조건과 PBR 경계

- Section: MF_Specular Input / Output 및 Master Composition; 8.4 Summary.
- Severity: Medium.
- Action: Expand.
- Issue: Phong 방향 Mask를 Direct Specular로 쓸 때 N·L의 앞면 조건과 Visibility, Light Color / Intensity의 적용 위치가 정의되지 않는다. Phong을 선택한 이유와 PBR Specular와의 차이도 짧게 연결할 필요가 있다.
- Reason: 방향 일치만으로 빛이 표면에 도달하는 것은 아니다. Phong lobe는 PBR BRDF 전체가 아니며 Shininess를 Unreal Roughness와 같은 값으로 다뤄서는 안 된다.
- Related Section: 8.3 Visibility; 8.10 Integration; 앞 Foundation Reflection.
- Recommendation: 교육용/스타일용 lobe라는 범위를 밝히고 동일 Light의 N·L 유효 조건과 Visibility를 어디서 적용할지 Master 계약에 둔다. 의도적 비차폐 Highlight라면 Controlled Deviation으로 명시한다. 물리 모델 전체를 다시 유도할 필요는 없다.

#### 08-04-D — Summary가 구현되지 않은 제어를 완료로 서술

- Section: L1705–1719; MF_Specular L1414–1438, L1529–1534.
- Severity: Medium.
- Action: Rewrite / Expand.
- Issue: Summary는 Threshold / Smoothstep으로 Anime 형태를 만들었다고 쓰지만 실제 Function Input은 N/L/V/Shininess이며 계산은 Saturate와 Power이다.
- Reason: 구현 계약과 완료한 기능 목록이 직접 불일치한다. Color / Intensity도 Function 내부가 아니라 Master 책임이다.
- Related Section: 8.7 이후 통합; 8.10.
- Recommendation: 현재 완료는 Phong Mask라고 정확히 요약한다. Threshold / Smoothstep을 기본 예제로 추가할 경우 실제 Data Flow·Parameter·출력 변화와 검증을 제공하고, 그렇지 않으면 후속 확장으로 표시한다.

#### 08-04-E — 필요한 벡터 연결과 과도한 재유도 분리

- Section: 8.4.2–8.4.7, Module화 후 전체 흐름; M_ASF_Base / M_ASF_Master 명칭.
- Severity: Medium.
- Action: Merge / Shorten / Keep.
- Issue: L/N, Dot, Normalize, Reflection, Power를 여러 도식과 요약으로 반복하며 앞 Theory와 같은 강의를 다시 시작하는 구간이 있다. 테스트 M_ASF_Base와 Master의 관계가 명시적이지 않다.
- Reason: 방향 부호와 실제 Node 대응은 Necessary Reinforcement이나 같은 식의 반복 유도는 구현 목적을 흐린다.
- Related Section: 8.2; 앞 Foundation Reflection; ASF-001/003.
- Recommendation: 방향 convention, 정확한 식, Node 대응, 기대값 검증, MF 추출은 Keep한다. 반복 유도·완료 흐름을 통합하고 테스트 Material과 최종 Master를 역할로 구분한다. 내부 8.4.n / H4 구조도 Low 우선순위로 정리한다.

### 8.5 Rim Light

**Overall Assessment:** View-dependent Mask와 실제 화면 윤곽선을 구분하고, Fresnel과 Rim의 목적을 분리한 설명이 좋다. Unlit·Emissive 테스트, Mask만 반환하는 함수, Master의 Color·Intensity 적용은 유지한다. Power에서 Width·Softness로 전환하는 이유와 지각되는 폭의 한계도 유용하다. 실제 Renderer Shadow 연결이 미완성임을 명시한 부분은 정확한 제한 설명이다.

#### 08-05-A
- Section: 8.5.4, 약 L849–1389
- Severity: Medium — Needs Technical Verification
- Action: Clarify
- Issue: Schlick의 N·V 식을 일반적인 물리 기반 Fresnel 설명으로 확장한다.
- Reason: 매끄러운 표면의 거시 Normal 기준 입사각 설명과 Microfacet BRDF에서 사용하는 각도 계약을 구분해야 한다. Rim과 Fresnel의 목적 구분 자체는 적절하다.
- Related Section: Chapter 07의 BRDF/Fresnel 설명; 8.4 Specular
- Recommendation: 여기서는 View-angle falloff 비교에 필요한 가정과 범위를 명시하고, 일반 BRDF의 Fresnel 입력 각도는 기존 이론 문서와 기술적으로 대조한다. 공통 이론을 다시 정의하지 않는다.

#### 08-05-B
- Section: 8.5.2, 8.5.5–8.5.6
- Severity: Medium
- Action: Clarify
- Issue: 재사용 함수의 Normal·ViewDirection에 동일 좌표계·단위 벡터 계약이 명시적으로 고정되지 않는다.
- Reason: Engine Node를 직접 사용한 예제와 외부 입력을 받는 MF의 보장은 다르다. PixelNormalWS 기반 Mask는 Normal Map에 의해 내부에도 나타날 수 있으며, 음수 N·V를 Saturate하면 뒷면은 최대 Rim이 된다.
- Related Section: 8.2 vector contract; 8.10 shared inputs
- Recommendation: World Space/unit-length와 정규화 책임, shading normal 선택, Two-sided 동작을 명시한다. 기본 단위 벡터·정면·접선·뒷면 테스트를 Foundation에 유지한다.

#### 08-05-C
- Section: 8.5.6, 약 L2054–2175
- Severity: High
- Action: Clarify / Verify
- Issue: Min=1−Width, Max=Min+Softness의 유효 범위와 경계값 처리가 없다.
- Reason: Softness=0이면 두 Smoothstep 경계가 같아지므로 안정적인 Step 결과를 보장할 수 없다. Width=0.2, Softness=0.4이면 Max=1.2여서 BaseRim=1에서도 결과는 0.5이다. 이때 Softness는 전이뿐 아니라 최대 세기에도 영향을 준다.
- Related Section: 8.5.6 Shape/Brightness separation; 8.10 parameter defaults
- Recommendation: Width·Softness 범위와 기본값, Width=0 비활성, Softness=0의 별도 Step 처리 또는 양수 최소값을 정의한다. Softness≤Width 제한이나 대체 경계 설계 중 의도에 맞는 정책을 선택한다. 전이 시작점과 중간값 위치를 구분한다.

#### 08-05-D
- Section: 8.5.6, 8.5.8, 약 L2248–2258 / L3351 부근
- Severity: Medium
- Action: Clarify
- Issue: Binary Mask를 사용하면 밝기에 따른 시각적 폭 변화가 완전히 사라지는 것으로 읽힌다.
- Reason: 수학적 Mask support가 고정되는 것과 Bloom·노출·Tone Mapping·AA 이후의 지각되는 폭은 별개다. 앞서 제시한 지각과 수학의 구분을 결론에서도 유지해야 한다.
- Related Section: 8.5.6 perceived width; 8.9 Debug
- Recommendation: Binary Mask가 고정하는 것은 Mask 경계라고 한정하고, 최종 화면의 폭을 보장하지 않는다고 설명한다. 기본 확인 환경의 후처리 조건을 기록한다.

#### 08-05-E
- Section: 8.5.7, 약 L2627–2658
- Severity: Medium
- Action: Rewrite diagram
- Issue: 합성 도식에서 Lighting Result가 MF Specular로, 합성 결과가 MF Rim으로 흐르는 것처럼 보인다.
- Reason: 실제 함수 입력은 Normal·Light/View와 제어값이며 이전 모듈의 색상 결과를 처리하는 직렬 단계가 아니다.
- Related Section: 8.1 architecture; 8.2 diagram; 8.10 Master
- Recommendation: 공유 입력에서 함수로 분기하고 각 Mask가 Master의 Color·Intensity 처리와 Add로 모이는 실제 데이터 의존성을 그린다.

#### 08-05-F
- Section: 8.5.4, 8.5.8
- Severity: Medium
- Action: Condense / Cross-reference
- Issue: Fresnel의 F0·거듭제곱 설명과 후반 Summary가 동일한 원리와 합성 설명을 반복한다.
- Reason: 도입 비교와 구현 확인은 Necessary Reinforcement이나, 공통 이론의 긴 재전개와 완료된 설명의 재서술은 별도 기준점이 된다.
- Related Section: Fresnel primary theory; 8.5.5–8.5.7
- Recommendation: 목적 비교·한 개의 대표식·정면/접선 사례·현재 Width/Softness 인터페이스를 남기고 이론은 원문을 참조한다. 기본 MF·MI 테스트는 Keep in Foundation, Light-aware/부위별 실제 제작 확장은 Advanced 후속으로 유지한다.

### 8.6 MatCap

**Overall Assessment:** Direction→View Space→UV→Texture Lookup 순서가 구현보다 먼저 제시된다. World Space 입력 계약, Texture Object와 Sample 결과의 차이, 함수의 Lookup과 Master의 Composition 책임 분리가 특히 명확하다. V 보정과 Alpha 단계별 검증은 Foundation에 유지한다. 다만 반복되는 이론 설명과 좌표계 가정, 통합 상태 표기를 정리해야 한다.

#### 08-06-A
- Section: 8.6.3 L1189–1195; 8.6.4–8.6.5
- Severity: Medium
- Action: Clarify
- Issue: Camera의 이동 자체가 같은 방향 Vector의 View Space 성분을 바꾸는 것처럼 설명한다. XY 투영을 Perspective에서도 일반적인 표면별 View 관계와 동일시하기 쉽다.
- Reason: 방향 변환에는 평행이동이 작용하지 않는다. 회전이 고정된 Camera의 위치 이동과, 대상을 바라보며 회전하는 이동은 다르다. 고정 Camera basis의 Normal XY 방식과 표면별 View Direction은 Perspective에서 동일하지 않다.
- Related Section: 8.5 N·V; 8.6.2 sphere correspondence
- Recommendation: 회전 없는 이동과 Orbit을 구분한다. 현재 구현을 기본 View-space normal projection으로 명시하고, 직교/중앙 근사 및 화면 외곽·뒷면에서의 한계를 짧게 설명한다. Perspective 보정 구현 자체는 후속 확장으로 남길 수 있다.

#### 08-06-B
- Section: 8.6.4–8.6.6, L1754 / L2863 / L3703 부근
- Severity: Medium — Needs Technical Verification / Visual Review Required
- Action: Clarify / Verify
- Issue: UV 범위를 일반적인 사용 제한처럼 표현하고, V Flip의 필수성을 현재 축·Texture 제작 규약 밖으로 일반화할 여지가 있다. 함수 입력의 unit-length 조건도 빠져 있다.
- Reason: UV는 0–1 밖의 값도 허용하며 Addressing이 결과를 결정한다. 현재 수식의 0–1 보장은 정규화된 Normal을 전제로 한다. 상하 보정은 정의한 Camera basis와 Texture 방향에 종속된다.
- Related Section: Fig8_52–56; 8.10 shared inputs
- Recommendation: World Space unit Normal, 현재 View 축, 위쪽 Highlight 기준 Texture 방향, Sampler/경계 설정을 계약으로 명시한다. 정확한 Unreal TransformVector 축과 그림 대응은 별도 확인한다. Normalize와 Remap 구분은 유지한다.

#### 08-06-C
- Section: 8.6.7 L4381–4417 / L4889–4896 / L5155–5166
- Severity: High
- Action: Clarify / Correct diagram
- Issue: 8.5에서 미연결로 명시한 Shadow가 여기서는 기존 Master의 완성된 Shadowed Lighting처럼 등장한다. 한 도식은 Shadow를 Add 항으로 표시한다.
- Reason: MF_Shadow가 있는 것과 Renderer Visibility가 공급되는 것은 다르다. Visibility는 색상에 더하는 별도 발광 기여가 아니다.
- Related Section: 08-03-A; 8.5.7; 8.10 Final Framework
- Recommendation: 테스트 Visibility/미연결 상태를 도식에 표시하고 Base×Visibility 의존성을 보인다. Renderer 통합 완료 근거 없이 실제 Scene Shadow 지원을 암시하지 않는다.

#### 08-06-D
- Section: 8.6.7–8.6.8
- Severity: Medium
- Action: Clarify
- Issue: Lerp가 Base·Specular·Rim·Shadow 전체를 함께 희석하는 정책의 결과와 비활성 값이 충분히 고정되지 않는다.
- Reason: Alpha=1은 기존 Lighting을 대체한다는 본문 설명은 정확하다. 그러나 Intensity=0, Alpha>0은 MatCap 비활성이 아니라 기존 결과를 어둡게 만든다. Alpha가 0–1을 벗어나면 보간이 아니라 외삽이다.
- Related Section: 8.10 MI controls; 8.8 Layer
- Recommendation: 공식 C=(1−Blend)×ASF+Blend×Intensity×MatCap과 함께 비활성은 Blend=0, 기본값·허용 범위를 명시한다. Shadow 보존 여부는 Master의 의도적 Composition 정책으로 기록한다.

#### 08-06-E
- Section: 8.6.1–8.6.8
- Severity: Medium
- Action: Condense / Cross-reference
- Issue: 일반 UV와 Lookup의 차이, XY 선택, Remap 산술, V 반전, Lerp의 0/0.5/1 설명이 여러 절과 Summary에서 완전히 재전개된다.
- Reason: 개념→구현→관찰은 Necessary Reinforcement지만 같은 유도와 정의의 반복은 Primary Source를 흐린다.
- Related Section: 8.6.4 / 8.6.5 / 8.6.7; 8.8 Lerp
- Recommendation: 좌표식은 8.6.4–5, 함수 계약은 8.6.6, Blend 정책은 8.6.7을 기준으로 삼고 Summary는 최종 인터페이스와 한 개의 Flow로 줄인다. Texture Object 오류 해결과 기본 테스트는 유지한다.

### 8.7 Emission

**Overall Assessment:** 중요한 검수 항목인 `현재 UV에서 Texture Sample → R Channel → Pixel별 Scalar → MF_Emission`을 명시적으로, 정확하게 설명한다(L4254–4348). Texture 전체가 하나의 Scalar로 변환된다고 설명하지 않는다. Sampling을 외부로 분리하여 Texture·Vertex Color·Procedural Mask를 재사용하는 설계와 MatCap Blend 뒤에 Emission을 Add하는 이유도 명확하다. 기본 Bloom·Exposure 비교, Mask Asset 설정, 함수 추출과 Master 통합은 Foundation에 유지한다.

#### 08-07-A
- Section: 8.7.1 L100–171 / L351–359; 8.7.8
- Severity: High — Needs Technical Verification
- Action: Clarify
- Issue: Output Path와 작가가 의도한 Emission Effect를 구분하는 설명이 Renderer가 두 기여값을 별도로 식별한다는 인상을 줄 수 있다.
- Reason: 최종 Emissive 입력에는 합성된 값이 들어간다. Base·Specular를 넣었다는 의미만으로 그 부분이 Bloom이나 지원되는 GI 경로의 Emissive 처리에서 자동 제외되지는 않는다. 본문은 Bloom과 실제 Light의 차이를 올바르게 설명하지만 이 합성 결과의 부수 효과는 별개다.
- Related Section: 8.0 Lumen; 8.6 Unlit; 8.9 Debug
- Recommendation: 이 구분은 ASF 내부의 책임/의도 구분임을 명시한다. Bloom은 최종 밝기에 반응하며, Lumen 등에서 Unlit/Emissive가 GI에 참여하는 조건은 사용 Engine·Renderer 설정으로 별도 검증한다. 이 검수에서는 그 동작을 확정하지 않는다.

#### 08-07-B
- Section: 8.7.4 L2420–2453 / L2519–2555
- Severity: Medium — Needs Technical Verification
- Action: Verify / Clarify
- Issue: Auto Exposure가 Compensation으로 바뀐 최종 화면을 다시 측정하여 보정한다는 인과 설명은 근거가 부족하다. Manual 비교의 물리 Camera 노출·Viewport override 조건도 빠져 있다.
- Reason: Scene luminance metering과 Compensation의 적용 위치를 구분해야 한다. Manual 선택은 타당하지만 그것만으로 재현 가능한 단일 변수 비교 조건이 완성되지는 않는다.
- Related Section: Fig8_62–63; Chapter 09 exposure/debug
- Recommendation: 현재 Engine의 metering 대상과 Compensation 관계를 확인하고 미확인 feedback 설명을 단정하지 않는다. Manual physical-camera 적용 여부, 고정 EV/카메라 설정, Game Settings/Viewport override를 기록한다. 초기 비교와 최종 검증을 구분한 구성은 유지한다.

#### 08-07-C
- Section: 8.7.2–8.7.3; 8.7.7 L5137–5175
- Severity: Medium
- Action: Clarify
- Issue: 앞선 Intensity·Bloom 비교는 기존 Post Process를 유지하지만, 후반에 Auto Exposure가 변수임을 설명하고 통합 화면은 다시 Auto Exposure + Compensation 3을 사용한다.
- Reason: 후반 통합 화면은 기능 존재 확인에 유용하지만 앞선 고정 노출 비교와 밝기 기준이 같지 않다. Intensity만 바꿔도 적응 노출이 달라질 수 있다.
- Related Section: 8.7.4; 8.9 Debug; 8.10 validation
- Recommendation: 기본 검증용 고정 노출 조건과 작업/표현용 Auto 조건을 별도 이름으로 기록한다. 앞의 Figure에는 실제 사용한 노출·Bloom 조건을 붙이고, 설정 복귀 후 결과를 정량 비교의 증거로 사용하지 않는다.

#### 08-07-D
- Section: 8.7.5–8.7.6
- Severity: Medium
- Action: Clarify
- Issue: sRGB Off가 저장값을 그대로 보장한다는 설명과 흑백 Pixel→정확한 0/1 설명에 Sampling 조건이 빠져 있다.
- Reason: sRGB 변환을 배제해도 Compression·Filtering·Mip·UV 위치가 값을 바꿀 수 있다. 현재 Pixel별 Scalar 설명은 정확하며 수정 대상은 그 값의 정확도 보장 범위다.
- Related Section: 8.6 Texture Object/Sample; 8.8 Layer Mask
- Recommendation: 선택 UV Channel, 채널, Sampler Type 일치와 Filtering/Mip 영향, 0–1 Mask 및 음수 Intensity 허용 여부를 계약으로 명시한다. 0/0.5/1의 기본 확인은 유지하고 복잡한 플랫폼 압축 실험은 후속으로 둔다.

#### 08-07-E
- Section: 8.7.1 L62–74; 8.7.6 L4093; 8.7.7 L4795–4811 / L5221–5224
- Severity: Medium
- Action: Correct diagram / Naming
- Issue: Shadow·MatCap을 단순 Add 목록으로 표시하거나 Base→Shadow→Specular→Rim을 함수 간 직렬 의존처럼 표시한다. MF_Lighting 명칭과 MatCap의 View Direction 기반 표현도 현재 구현과 어긋난다.
- Reason: 실제 구조는 Base에 Visibility 적용, 독립 Spec/Rim Add, MatCap Lerp, Emission Add이다. 현재 MatCap은 World Normal을 View Space로 변환하며 ViewDirection 입력을 받지 않는다.
- Related Section: 08-01-B; 08-06-C; 8.10
- Recommendation: 합성 순서와 함수 입력 의존성을 분리하고 MF_BaseLighting으로 통일한다. MatCap은 View-space Normal 기반 Lookup으로 명시한다.

#### 08-07-F
- Section: 8.7.1–8.7.8
- Severity: Medium
- Action: Condense / Cross-reference
- Issue: Output/Effect 구분, 같은 HDR 수치 예제, Bloom/Glow 정의, Mask 0/1, Texture→Scalar 설명이 반복 유도되고 내부 제목이 다수 H1/H2로 올라간다.
- Reason: 샘플링 위치와 Scalar의 의미는 핵심이므로 제거하면 안 된다. 다만 8.7.6의 완결된 설명을 통합/요약에서 그대로 다시 전개할 필요는 없다.
- Related Section: ASF-003; 8.7.3 / 8.7.4 / 8.7.6
- Recommendation: 각각의 Primary Source를 지정하고 후반은 연결 계약·결과·참조만 남긴다. Exposure 기본 테스트는 Foundation, Tone Mapper 알고리즘 변경과 실제 제작 VFX 확장은 Advanced 후속으로 유지한다.

### 8.8 Region-based Parameter Control

**Overall Assessment:** 실제 제목은 Region-based Parameter Control이며, 복잡한 Material Layer System을 구현하지 않는다고 명시한다. 단일 SpecularIntensity의 Mask 기반 보간, 함수 복제 없는 재사용, 테스트용 Shininess=2와 최종값의 구분은 적절하다. L1675–1719에서 Master에 통합하지 않은 이유도 명시한다. 따라서 구현되지 않은 MF_MaterialLayer를 요구하거나 기능 누락으로 단정하지 않는다. 다만 Chapter 목차와 최종 Framework의 지원 범위가 이 결정을 따라야 한다.

#### 08-08-A
- Section: 8.8.1 L573–594; 8.8.2 L664–679; 8.8.4 L1333–1348
- Severity: High
- Action: Correct Data Flow
- Issue: 보간한 SpecularIntensity를 MF_Specular 입력에 전달한다고 반복 설명하지만, 실제 구현 L924–944 / L1265–1275는 함수의 Mask 출력에 외부에서 Multiply한다.
- Reason: 8.4의 MF_Specular는 Normal·Light·View·Shininess로 Mask를 반환하며 Intensity를 입력받지 않는다. 개념 도식이 실제 인터페이스 변경을 암시한다.
- Related Section: 8.4 function contract; 8.10 Specular controls
- Recommendation: `Lerp(SpecA,SpecB,Mask) → Master/test contribution Multiply ← MF_Specular.SpecularMask`로 일치시킨다. 함수 입력과 출력에 적용하는 제어값을 구분한다.

#### 08-08-B
- Section: 8.8 title/file; 8.8.4 L1675–1719
- Severity: Medium
- Action: Align scope / Cross-reference
- Issue: 파일명 MaterialLayer와 개요에서 예고하는 Layer 구조에 비해 실제 범위는 미통합 Region Parameter 테스트다.
- Reason: 기능 Module과 독립 MF 구현은 동일하지 않으며, Layer라는 용어는 Unreal Material Layers 기능과 혼동될 수 있다.
- Related Section: Chapter08 overview; 8.1 module list; 8.10 supported scope
- Recommendation: 목차·Architecture 표에서 `Material Layer / Region Control: 기본 원리 및 독립 테스트, Master 미통합`으로 명시한다. 파일명 변경은 후속 리팩터링 시 참조와 함께 검토하며 이번 Audit에서는 변경하지 않는다.

#### 08-08-C
- Section: 8.8.1 / 8.8.4 Material separation criteria
- Severity: Medium
- Action: Clarify
- Issue: 큰 재질 차이→Material Slot 분리를 거의 보편적 판단 규칙처럼 반복한다.
- Reason: Material Asset·Instance·Slot은 서로 다른 개념이다. Shader model/feature 차이와 Parameter 값 차이를 구분해야 하며, 표면 이름만으로 분리 여부가 결정되지는 않는다.
- Related Section: ASF-002 character-specific modules; 8.10 MI
- Recommendation: 제시한 분리를 이번 기초 예제의 선택으로 한정하고, 모델·Blend Mode·기능 호환성·관리 비용을 짧은 기준으로 제시한다. 일반 천을 의미하는 Cloth는 유지 가능하나 프로젝트 부위명/자산명은 Decision Log의 Outfit과 맞춘다.

#### 08-08-D
- Section: 8.8.1–8.8.4
- Severity: Medium
- Action: Condense / Clarify
- Issue: Material 분리와 Region Control, Multiply와 Lerp, Mask→Scalar가 각 절에서 반복된다. Region Texture의 Data 설정은 8.7에 의존하지만 재사용 조건이 명시적이지 않다.
- Reason: 단일 값→Texture→기존 함수 결과 적용은 필요한 검증 흐름이다. 같은 정의를 반복하는 부분과 실제 연결 검증을 구분해야 한다.
- Related Section: 8.7.5–8.7.6; 8.6.7 Lerp
- Recommendation: Lerp 기본 정의와 Sampling 설명을 참조하고 Region 테스트의 결과·유효 Mask 범위·sRGB Off/UV 계약만 남긴다. A=0일 때 Multiply와 Lerp가 같아지는 특수 관계를 짧게 덧붙이면 과도한 이분법을 피할 수 있다. 복잡한 Character Layer/Branch/대량 Variation 구현만 Advanced 후보로 분리한다.

### 8.9 Debug View

**Overall Assessment:** 기존 계산 결과를 분기하여 관찰하고 다시 계산하지 않는 원칙, 진단 목적에 따른 Data 선택, Mode 0에서 FinalResult를 보존하는 조건이 강점이다. ShadowVisibility가 전역 Scalar임과 Region Control 미통합을 여기서는 정확하게 명시한다(L797–872). Debug 구현·MI 전환·기본 테스트와 간단한 비용 주의는 Foundation에 유지한다.

#### 08-09-A
- Section: 도입 L51–57; 8.9.2 L667–748; 8.9.3 L983–1245; 8.9.4–8.9.8
- Severity: High
- Action: Align interface
- Issue: 도입과 Architecture 절은 EmissionMask/Scalar를 사용하지만, 선정·구현·통합·검증은 EmissionResult/Vector3를 Mode 5로 사용한다.
- Reason: 동일 모드의 의미·타입·연결 원본이 서로 달라 독자가 설계대로 만들면 후반 구현과 불일치한다.
- Related Section: 8.7 MF_Emission; 8.10 DebugMode table; Fig8_69–72
- Recommendation: 실제 후반 계약인 EmissionResult/Vector3를 기준으로 도입·8.9.3 표와 도식을 정렬한다. Mask 단독 진단은 선택적 확장으로 구분한다. 그림의 실제 라벨은 Visual Review Required다.

#### 08-09-B
- Section: 8.9.1 L145–199; 8.9.5 L2470–2502; 8.9.6
- Severity: High
- Action: Clarify validation contract
- Issue: Emissive로 직접 출력하면 원래 Scalar/RGB를 그대로 화면에서 확인할 수 있다는 설명에 노출·Bloom·Tone Mapping의 영향이 빠져 있다.
- Reason: Unlit은 표면 Lighting을 배제하지만 Display 변환을 우회하지 않는다. 8.7의 Auto Exposure 복귀 후에는 Mode 전환 자체가 적응 노출을 바꿀 수 있다. HDR Emission 색이 연해지는 것도 타입 손실과 구분해야 한다.
- Related Section: 08-07-B/C; 8.9.4 L1948; Fig8_72
- Recommendation: 시각적 분포 검증과 수치 검증을 구분한다. 고정 노출·Bloom 조건과 동일 Camera를 정하고, 필요 시 선형값/버퍼 확인 경로를 별도 명시한다. RGB가 회색처럼 보인다는 이유만으로 타입 오류를 확정하지 않는다.

#### 08-09-C
- Section: 8.9.4 L1555–1916; 8.9.5 L2368–2402
- Severity: Medium — Needs Technical Verification
- Action: Clarify / Verify
- Issue: Scalar DebugMode의 범위를 0–5로 관리하지만 정수 제약은 사용 규칙에만 있다. If의 equality threshold 설정이 설명되지 않는다.
- Reason: 본문은 6 이상이 Emission으로 가는 fallback과 소수 사용 금지를 명시하므로 완전 누락은 아니다. 다만 음수·소수 역시 fallback이며 Slider 범위는 입력값 자체의 유효성을 보장하지 않는다. Engine If 비교가 수학적 정확한 ==와 같은지도 확인해야 한다.
- Related Section: 8.10 Debug default / MI
- Recommendation: 허용 집합 {0,1,2,3,4,5}, 비정상 값의 동작, If threshold를 기록한다. 의도에 따라 Round/Clamp 또는 명시적 invalid fallback을 선택하고 0–5 및 음수·소수·범위 초과의 최소 테스트를 제시한다.

#### 08-09-D
- Section: 8.9.1 L273; 8.9.4 If Chain; 8.9.7 L3264–3298
- Severity: Medium — Needs Technical Verification
- Action: Clarify
- Issue: 선택한 데이터만 출력한다는 기능적 설명이 선택하지 않은 계산을 실행하지 않는다는 비용 보장으로 읽힐 수 있다. Production 대안 중 Debug 전용 MI만으로 경로가 제거되는 것처럼 오해할 여지도 있다.
- Reason: Material Graph의 If 선택과 실제 GPU 분기/최적화는 같지 않다. Scalar 값을 0으로 바꾸는 것과 Static Switch를 통해 컴파일 경로를 제거하는 것은 다르다.
- Related Section: ASF-002 Stage/Module distinction; Chapter 09; 8.10 MI
- Recommendation: 출력 선택과 실행 비용을 구분하고, 일반 MI는 제거 보장이 없다고 명시한다. 기본 비용 주의는 유지하되 실제 생성 Shader·플랫폼별 측정과 Shipping 배제 구현은 Advanced 후속으로 둔다.

#### 08-09-E
- Section: 8.9.1 / 8.9.3 / 8.9.6–8.9.8
- Severity: Medium
- Action: Condense / Correct diagrams
- Issue: Feature 직렬 도식과 단순 Add 도식이 실제 Master 의존성을 축약하며, MI/Debug 역할·재계산 금지·Mode 목록·원인 추적 예제가 반복된다.
- Reason: DebugMode=0 보존 및 Scalar/RGB 검증은 필요한 재확인이지만, 동일한 목록과 예제의 반복은 계약 변경 시 08-09-A 같은 불일치를 유발한다.
- Related Section: 08-01-B; 8.9.2 authoritative mode table; ASF-003
- Recommendation: Mode 표는 한 곳을 기준으로 삼고 구현·검증은 그 표를 참조한다. 기존 계산 분기 도식은 유지하고 Feature 간 입력 연결은 실제대로 그린다. 내부 번호와 H4 중심 구조를 표준에 맞춰 정리하고 L3504의 `확인했다.s`를 Minor Editing 대상으로 기록한다. Fig8_72 재사용은 같은 검증 결과의 반복이며 번호 충돌과 구분한다.

**Cross-section clarification:** 8.9.2는 현재 Shadow가 전역 Scalar이고 Region은 미통합임을 명시한다. 따라서 앞선 08-03-A/08-06-C는 Chapter 전체에 한계 설명이 없다는 지적이 아니라, 중간 통합 설명에 그 상태가 일관되게 전달되지 않는다는 지적이다.

### 8.10 Final Framework

**Overall Assessment:** 함수 책임 표, Specular/Rim의 Mask와 Master 표현 분리, Texture Resource와 Sample Result, MI와 Debug의 역할을 한데 정리한다. Shadow는 Visibility 적용만 구현했고 Pixel별 Mask 검증은 포함하지 않는다고 최종 검증에서 명시한다. 학습용 구조와 Production Renderer를 구분하는 범위 설명도 적절하다. 그러나 최종 기준이 되어야 할 Data Flow가 실제 계산과 충돌하고, 완료 선언이 재현 조건·경계값 근거보다 강하다.

#### 08-10-A
- Section: 8.10.1 L80–104; 8.10.4 L1691 / L1866; 8.10.8 L4495–4512
- Severity: High
- Action: Rewrite architecture diagram
- Issue: MF_BaseLighting→MF_Shadow→MF_Specular→MF_RimLight→MF_MatCap→MF_Emission을 실제 함수 간 Data Flow로 설명한다.
- Reason: Base→Shadow 의존성은 실제지만 Specular·Rim·MatCap·Emission은 공유/개별 입력으로 독립 계산한다. Core Lighting 출력이 이들 함수의 입력이라는 계약은 없다. 학습 순서, Master 합성 순서, GPU Stage도 다르다.
- Related Section: ASF-002; 08-01-A/B; 8.10.2; Fig8_73–74
- Recommendation: 공유 입력에서 함수별 분기와 Multiply/Add/Lerp 합류를 표시한다. 학습 순서는 그렇게 라벨링한다. Module은 책임 단위, MF는 이번 구현 수단이며 일대일 대응이 일반 원칙은 아님을 명시한다.

#### 08-10-B
- Section: 8.10.2 L776–792; 8.10.3 L1108–1113; 8.10.4 L1770–1775 / L2054–2072; 8.10.7 L3938–3949
- Severity: High
- Action: Correct composition contract
- Issue: BaseColor와 LightingData를 +로, MatCap을 다른 기여값과 단순 Add로 표기한다. 정확한 수식보다 개념적 합성으로 보라는 설명이 실제 연산 차이를 지운다.
- Reason: 8.2의 Base는 Multiply이고 8.6–8.7의 MatCap은 전체 ASF 결과와 Lerp한 뒤 Emission을 Add한다. Add와 Lerp는 비활성·기존 Shadow/Specular/Rim 보존 동작이 다르다.
- Related Section: 08-06-D; 8.7.7; Fig8_73–74
- Recommendation: 최종 기준식을 `B=BaseColor*saturate(dot(N,L)); S=B*Visibility+SpecMask*SpecColor*SpecIntensity+RimMask*RimColor*RimIntensity; Final=lerp(S,MatCapResult*MatCapIntensity,MatCapBlend)+EmissionResult`처럼 현재 구현 범위로 명시한다. 개념적 입력 집합에는 + 대신 목록/분기선을 사용한다. 실제 Light intensity/color와 Specular visibility 정책은 별도 계약으로 남긴다.

#### 08-10-C
- Section: 8.10.2 L501–522; 8.10.7 checklist
- Severity: High — Needs Technical Verification
- Action: Add reproducible baseline / Qualify completion
- Issue: 8.0 Deferred 설정과 Forward Selected Directional Light 의존성 검증이 해결되지 않은 채 전체 기능을 Complete로 선언한다. Node의 Illumination 정보 설명도 함수의 Direction-only 계약보다 넓다.
- Reason: 문서 속 화면과 확인했다는 서술만으로 Engine·Renderer·Shading Model 호환성이나 모든 입력 조건의 정확성을 확정할 수 없다. 본 Audit는 실제 프로젝트 실행을 하지 않았다.
- Related Section: 08-02-B; 8.0; Fig8_73
- Recommendation: UE build, Renderer, Material Domain/Shading Model, Light source/sign/space, Level·MI와 고정 노출 조건을 기록한다. Complete는 기초 테스트 완료로 한정하고 Renderer integration/경계값/플랫폼 미검증은 별도 표기한다.

#### 08-10-D
- Section: 8.10.5 L2627–2642 / L2804–2833; 8.10.7 L4035–4071
- Severity: Medium
- Action: Complete user-control contract
- Issue: 최종 Parameter 표에 범위·기본값·비활성 값이 없고, MatCap Blend와 Emission Mask Texture의 외부 제어 상태가 정리되지 않는다.
- Reason: 8.6에서는 Blend Alpha를 Constant 테스트 후 필요 시 Parameter화한다고 한다. 현재 표는 Intensity만 있어 Blend의 MI 제어 여부가 불명확하다. Rim 경계값과 DebugMode 정수 제약도 최종 계약에 이어지지 않는다.
- Related Section: 08-05-C; 08-06-D; 08-09-C
- Recommendation: 노출 Parameter/고정 테스트값/미구현 제어를 나누고 기본값·범위·비활성·Texture source를 추가한다. MatCapBlend가 Constant라면 그대로 명시한다. 기본 MI 제어는 Foundation에 유지한다.

#### 08-10-E
- Section: 8.10.7 L4001–4031; 8.10.8 L4308–4319
- Severity: Medium — Needs Technical Verification / Visual Review Required
- Action: Qualify diagnosis
- Issue: Scalar와 Vector3의 If Chain 혼합이 Color 손실 원인이라고 재현 가능한 연결 정보 없이 확정한다.
- Reason: 명시적 Vector3 통일은 읽기 쉬운 선택이지만 Scalar broadcast 자체가 일반적으로 RGB 손실을 뜻하지는 않는다. Input/Output type, 채널, 실제 If 연결과 Display 변환을 확인해야 한다.
- Related Section: 08-09-B; 8.9.4; Fig8_71–73
- Recommendation: 오류 당시와 수정 후 타입/연결을 기록하여 원인을 제한한다. Vector3 통일은 이 구현의 계약으로 설명하고 모든 Scalar/Vector 혼합이 오류라는 일반화는 피한다.

#### 08-10-F
- Section: 8.10.1–8.10.8; filename FinalFramwork
- Severity: Medium
- Action: Condense / Align scope
- Issue: Overview·Architecture·Responsibilities·Data Flow·Verification·Summary가 같은 인터페이스와 학습 목적을 재서술한다. Built-in 우선 논의와 ASF 전체 프로젝트/이번 학습 구현의 범위도 섞인다.
- Reason: 최종 책임 표·합성 계약·제한·검증은 필요하지만 반복 전개는 잘못된 도식과 오래된 상태를 누적시킨다.
- Related Section: ASF-000/002/003; Roadmap; 8.8
- Recommendation: 함수 계약 표·정확한 Flow·지원/미지원 표·최소 검증표를 기준으로 두고 앞 절을 참조한다. Region은 테스트 완료/미통합, Shadow는 전역 Scalar 적용만 완료라고 명시한다. Built-in/Custom 판단 원칙은 Foundation에 남기고 실제 Substrate/HLSL/Renderer 제작은 후속 단계로 둔다. 파일명 FinalFramwork, L4631의 `Foundation이다.s`, Heading 정리는 후순위다.

**Cross-section clarification:** 최종 Rim 인터페이스는 Width/Softness이므로 8.5의 Power 전환은 최종 계약과 일치한다. Mode 5는 EmissionResult이며 8.9 도입/Architecture에 이전 설명이 남은 것이다. 8.10.7은 Shadow의 전역 Scalar 한계를 명시하므로 실제 Shadow 생성 완료로 해석하지 않는다.

## 4. Module Architecture Review

다음 계약은 현재 본문 구현 기준이며 실행 검증 결과가 아니다. Normal / Light / View의 Space와 단위 길이는 입력 경계에서 통일해야 한다. 재사용은 함수 자산 분리만이 아니라 입력 의미·출력 타입·외부 의존성이 유지되는지를 뜻한다.

### Base Lighting
- Module: MF_BaseLighting.
- Responsibility: 방향 기반 기본 응답과 Base Color 적용.
- Input: Normal, Light Direction, BaseColor. N/L은 같은 World Space, L은 Surface→Light convention 확인 필요.
- Processing: Normalize → Dot → Saturate; BaseColor Multiply.
- Output: LightingData Scalar 0–1; LightingResult RGB.
- Dependency: Master가 제공하는 Normal과 실제 Light 접근 경로. Color/Intensity/Visibility는 현재 방향 계수에 포함되지 않는다.
- Reuse: Data와 Result를 분리하여 Shadow 적용과 Debug에서 재사용.
- Issue: 방향 도식·Renderer 접근·최초 Unlit 설정·Stylized remap 연결이 불완전하다.
- Recommendation: 08-02-A–E, 08-G-01의 입력/환경/범위 계약을 보강한다.

### Shadow
- Module: MF_Shadow.
- Responsibility: 이미 얻은 Visibility를 LightingResult에 적용한다. Shadow Map 생성기가 아니다.
- Input: LightingResult RGB, Visibility Scalar 0–1.
- Processing: Multiply.
- Output: ShadowedLighting RGB.
- Dependency: Visibility 공급자. 현재 전역 테스트 Scalar이며 실제 Surface별 Renderer Visibility 연결은 미완료.
- Reuse: 같은 의미의 Visibility를 공급하는 경우 재사용 가능. Artistic Mask를 넣을 때에는 의미 변경을 명시해야 한다.
- Issue: 중간 통합 설명의 완료 범위와 Direct Specular 차폐 정책이 불명확하다.
- Recommendation: Depth resource / Visibility / Renderer Mask / Artistic Mask를 구별하고 중복 차폐를 피한다. 1/0.5/0 테스트는 유지한다.

### Specular
- Module: MF_Specular.
- Responsibility: N/L/V 관계에서 Phong 계열 Highlight Mask를 계산한다.
- Input: 같은 Space의 Normal, SurfaceToLight, SurfaceToCamera, Shininess.
- Processing: 정규화 전제 아래 Reflection 방향 계산 → saturate(R·V) → Power.
- Output: SpecularMask Scalar. Color와 Intensity는 Master에서 적용.
- Dependency: Light/View 공급자; N·L 전면 조건과 Visibility 적용 여부는 별도 정책.
- Reuse: 동일 Mask를 Debug와 기여색 계산에 사용. Region Intensity는 출력 이후 외부 Multiply에 재사용.
- Issue: 초기 Specular pin 안내가 Unlit Emissive 구현과 충돌하고 Summary는 미구현 Threshold/Smoothstep을 포함한다.
- Recommendation: PBR Specular와 단순 Phong 학습 응답의 차이를 제한하고 실제 입력/출력 계약으로 정렬한다. Engine pin 동작은 Needs Technical Verification.

### Rim Light
- Module: MF_RimLight.
- Responsibility: View-dependent Fresnel-like 응답을 스타일용 폭/전이로 제어한다. 독립 Light Stage나 Screen-space Outline이 아니다.
- Input: Normal, ViewDirection, RimWidth, RimSoftness. N/V의 같은 Space·단위 길이 전제.
- Processing: 1−saturate(N·V) → Smoothstep(1−Width, 1−Width+Softness, response).
- Output: RimMask Scalar; Color/Intensity는 Master 적용.
- Dependency: 선택한 Shading Normal과 View 방향; 관찰 폭에는 Exposure/Bloom/AA도 영향.
- Reuse: Light 입력과 무관하게 같은 View/Normal 데이터로 재사용.
- Issue: Softness=0과 상한이 1을 넘는 경우의 동작/허용 범위가 정의되지 않는다.
- Recommendation: 08-05-C의 경계값을 정의한다. Power에서 Width/Softness로의 전환은 의도적 최종 인터페이스로 유지한다.

### MatCap
- Module: MF_MatCap.
- Responsibility: View-space Normal 기반 UV 생성과 MatCap Lookup.
- Input: World Normal, MatCap Texture Object.
- Processing: World→View 방향 변환 → XY Remap → convention에 맞는 V 처리 → Sample.
- Output: MatCapResult RGB.
- Dependency: Camera 회전 기준·Normal 길이·Texture/Sampler/색공간. Camera translation 자체는 방향 벡터 변환에 영향을 주지 않는다.
- Reuse: 조명 시뮬레이션이나 실시간 Reflection 없이 Lookup 결과를 Master에서 사용.
- Issue: Camera 이동 설명, V flip의 보편화, UV 범위 전제, Intensity=0의 비활성 해석이 부정확하다.
- Recommendation: Master에서 Intensity Multiply 후 Lerp한다. 원래 결과 보존을 위한 off는 Blend=0이다. 기준 축·그림 방향은 Needs Technical Verification / Visual Review Required.

### Emission
- Module: MF_Emission.
- Responsibility: 현재 Surface의 Mask 값으로 자체 발광 기여색을 만든다.
- Input: EmissionMask Scalar, EmissionColor RGB, EmissionIntensity Scalar.
- Processing: Mask × Color × Intensity.
- Output: EmissionResult RGB, HDR 값 가능.
- Dependency: Mask 공급자가 Texture 사용 시 UV Sample·채널 선택·Data 설정을 책임진다. 함수 자체는 Texture 전체나 Camera를 요구하지 않는다.
- Reuse: Texture뿐 아니라 Procedural/Vertex 등 같은 Scalar 계약을 갖는 입력으로 교체 가능.
- Issue: Mask 흐름은 정확하다. sRGB Off의 값 보장 범위, 최종 Emissive 경로와 특정 Module 효과의 구분, Exposure 설명은 보강 필요.
- Recommendation: Sample 조건과 Intensity 범위를 명시한다. MatCap 합성 뒤 Add하는 의도는 유지한다. Bloom/GI는 함수 이름이 아니라 최종 출력과 Engine 조건에 의존함을 구분한다.

### Region-based Parameter Control
- Module: 8.8의 테스트 구조. MF_MaterialLayer 구현을 가정하지 않는다.
- Responsibility: 한 Parameter를 Surface 영역에 따라 보간한다.
- Input: Sample된 RegionMask Scalar 0–1, 두 SpecularIntensity 값.
- Processing: Lerp(A,B,Mask), 이후 SpecularMask에 외부 Multiply.
- Output: 영역별 Intensity Scalar 및 테스트 기여색.
- Dependency: Mask Sampling 계약과 기존 MF_Specular 출력. 현재 Master 미통합.
- Reuse: 함수 복제 없이 같은 Parameter 제어 원리를 재사용.
- Issue: 도식은 Intensity를 MF_Specular 내부 입력처럼 표현한다. Material Slot/Asset/Instance와 Unreal Material Layers의 구분이 필요하다.
- Recommendation: 출력 이후 적용 위치와 테스트 전용 상태를 명시한다. 복잡한 Layer System으로 확대하지 않는다.

### Debug View
- Module: MF_DebugView.
- Responsibility: 이미 계산한 내부 결과를 선택하여 관찰한다.
- Input: DebugMode 및 FinalResult, LightingData, ShadowVisibility, SpecularMask, RimMask, EmissionResult. Scalar 관찰값은 표시용 RGB로 맞춘다.
- Processing: Mode 0–5 선택. Mode 0은 원래 FinalResult 보존.
- Output: 선택된 DebugColor RGB.
- Dependency: 원래 계산 결과와 같은 연결, 정수 Mode 규칙, Exposure/Bloom/Tone Mapping 조건.
- Reuse: 재계산 없이 Master에서 분기한 값 재사용.
- Issue: Mode 5의 초기 Scalar Mask/후반 RGB Result 불일치, 잘못된 Mode fallback, 화면색=수치 가정, 출력 선택=실행 생략 오해.
- Recommendation: 최종 Mode 표를 기준으로 정렬한다. Normal/Light Vector/EmissionMask 자체는 현재 Mode에 없으므로 진단 가능 범위를 밝히고 필요 시 임시 직접 출력으로 확인한다. 모든 진단 Mode 추가를 필수로 요구하지 않는다.

### Final Master / Material Instance
- Module: Master Composition과 MI 외부 제어. GPU Rendering Stage를 조립하는 시스템이 아니다.
- Responsibility: 공통 입력 공급, 독립 기여값 합성, Parameter 노출, Debug 선택과 Material Output 연결.
- Input: 공통 Surface/Light/View, Texture/Mask, 함수 결과, 외부 제어값.
- Processing: Base Multiply → Visibility 적용; 독립 Spec/Rim Add → MatCap Lerp → Emission Add → Debug 선택.
- Output: 선택 RGB를 현재 Unlit 학습 Material의 Emissive Color로 출력.
- Dependency: Renderer/Material 설정, Light 접근, Camera·노출 조건. MI는 노출값을 조절하며 함수 계약이나 GPU Stage를 새로 정의하지 않는다.
- Reuse: 공유 입력과 실제 계산 결과를 함수/Debug가 재사용한다. Character Application은 이 계약의 후속 소비자이다.
- Issue: 직렬 함수 도식·단순 Add 요약·Parameter 표의 누락과 완료 선언이 실제 범위를 넘는다.
- Recommendation: 아래 식과 지원 범위표를 최종 기준으로 삼는다. 범위·기본값·off값·고정 Constant/노출 Parameter를 구분한다.

현재 구현을 설명하는 기준식 제안(변수명은 설명용이며 자산명 변경 지시가 아님):

```text
D = saturate(dot(normalize(N), normalize(L)))
B = BaseColor * D
S = B * Visibility
    + SpecularMask * SpecularColor * SpecularIntensity
    + RimMask * RimColor * RimIntensity
F = lerp(S, MatCapResult * MatCapIntensity, MatCapBlend) + EmissionResult
Output = DebugSelect(DebugMode, F, D, Visibility, SpecularMask, RimMask, EmissionResult)
```

이는 현재 단순화된 합성의 기술이며 물리적으로 완전한 조명식이 아니다. 실제 Light Color/Intensity, Direct Specular Visibility, Renderer Shadow 연결은 별도 지원 계약이 필요하다. MatCapBlend=1이면 S가 가려지며 Emission은 그 뒤에 남는다.

## 5. Cross-section Duplication Map

Chapter 01–07은 개념의 참조 위치 확인에 사용했으며 이번 감사 대상에 편입하지 않았다. Primary Source Candidate는 후속 편집 기준 후보이다.

| Concept | Appears In | Primary Source Candidate | Recommended Action |
|---|---|---|---|
| GPU Stage와 Material 계산 | 8.1, 8.7, 8.9, 8.10 | ASF-002; Chapter 01 | Necessary Reinforcement: 구분 문장 유지. Unnecessary Duplication: 잘못된 직렬 도식을 재생산하는 요약은 Rewrite/Merge. |
| Coordinate / Normal / View | 8.2, 8.4–8.6, 8.10 | Chapter 02; 8.2 입력 계약, 8.6 변환 적용 | Normalize/같은 Space를 짧게 재연결하는 것은 Keep. 좌표계 기초 전체의 재유도는 Shorten/Cross Reference. |
| Dot / Reflection / Power | 8.2, 8.4, 8.5 | Chapter 03; 구현별 최초 계산 절 | 수식과 Node 대응·기대값은 Necessary Reinforcement. 같은 벡터 직관과 요약 반복은 Shorten. |
| MF / Master / MI 역할 | 8.0–8.1, 모든 생성 절, 8.9–8.10 | ASF-002; Chapter 04; 8.1 계약 소개 | 첫 생성 절차와 특수 설정은 Keep. 동일 생성 클릭 안내·장점 나열은 공통 절 참조. |
| Fresnel / PBR Reflection | 8.4–8.5 | Chapter 05 Reflection / BRDF; Chapter 07.5 Rim 맥락 | 광학 기초의 Primary Source는 Chapter 05이다. 기존 08-05-A의 Chapter 07 관련 표기는 스타일 연결로 읽는다. 장문 기초 재설명은 Shorten, 물리 Fresnel과 스타일 Rim의 차이는 Keep. |
| Continuous → Stylized | 8.2, 8.4–8.5, 8.10 | Chapter 07.2 / 07.3 / 07.5 / 07.9 | Necessary Reinforcement: 기존 응답을 어떻게 제어하는지 연결. 미구현 remap을 완료로 요약하지 않는다. |
| Shadow / Bias / PCF | 8.3 내부, 8.6 이후 통합 | 8.3의 Depth→Visibility 설명; Chapter 07.4 스타일 맥락 | 8.3 L2878–3066과 L3494–3629 Bias/Artifact 설명 통합. 최소 Depth/비교/필터 원리와 Scalar 적용 검증은 Keep. |
| HDR / Exposure / Tone Mapping | 8.7.2–8.7.4, 8.9, 8.10 | Chapter 06.6–06.8; 8.7 고정 노출 테스트 | 일반 이론은 참조, 실제 관찰 조건과 수치/화면색 차이는 Necessary Reinforcement. 같은 밝기 예제 반복은 Shorten. |
| Texture Sample → 채널 Scalar | 8.7.5–8.7.6, 8.8, 8.10 | Chapter 01 Sampling 맥락; Chapter 06.8 Data 설정; 8.7.6 구현 계약 | 현재 Surface 값 설명은 Keep. 뒤에서는 UV/채널/범위/색공간 차이만 명시하여 Unnecessary Duplication 축소. |
| Multiply / Lerp | 8.6.7, 8.8, 8.10 | 8.6 합성 계약; 8.8은 Region 적용 | 기본 정의를 반복하지 않고 Alpha 양끝·off 동작·적용 위치를 각각 검증한다. A=0 특수 관계는 짧게 연결. |
| DebugMode / 재계산 금지 | 8.9.1–8.9.8, 8.10 | 정렬된 8.9 Mode 표 및 최소 테스트 | Mode 0 보존 재확인은 Necessary Reinforcement. 표·목록·원인 추적 예제 반복은 Merge. |
| Final Flow / Production 원칙 | 개요, 8.0, 8.1, 8.10 여러 절 | ASF-000/002; 8.10 정확한 계약·지원표 | 이론/책임/Flow/요약에서 같은 문장 재유도는 Shorten. 마지막 통합 체크는 Keep. |

## 6. Foundation / Advanced Boundary Review

| Content | Current Section | Keep in Foundation or Move to Advanced | Reason |
|---|---|---|---|
| 프로젝트 생성·기본 Git·환경 기록 | 8.0 | Keep in Foundation | 후속 구현 재현에 필요하다. Production이라는 단어만으로 이동하지 않는다. |
| N/L/V·Function Input/Output·기본 구현 | 8.2, 8.4–8.7 | Keep in Foundation | Concept→Data→Module→Implementation의 핵심이다. |
| Depth/Visibility 구분·PCF 기본·Bias 직관 | 8.3 | Keep in Foundation / Shorten | Visibility 입력의 의미를 이해하는 데 필요하다. 반복 이론을 정리하되 전부 Advanced로 보내지 않는다. |
| Renderer Shadow 취득·내부 렌더러 제작 | 8.3 한계 및 후속 안내 | 현재 한계/입력 계약은 Keep; 실제 심화 구현은 Move to Advanced 후보 | 본문은 아직 연결하지 않았다. 미구현 내용을 이미 이동 가능한 구현 덩어리처럼 취급하지 않는다. |
| Mask Sample·Region Lerp·Specular 외부 Multiply | 8.7–8.8 | Keep in Foundation | 기본 Data Flow 검증이며 대규모 Layer System이 아니다. |
| Unlit·고정 노출·0/0.5/1·Mode 0–5 확인 | 8.2–8.10 | Keep in Foundation | 기본 기능 검증이다. 단순히 변수를 고정한다는 이유로 Controlled Profiling으로 분류하지 않는다. |
| MI Parameter·Debug·최종 합성·최소 비용 주의 | 8.9–8.10 | Keep in Foundation | 재사용과 Debuggability의 필수 요소다. |
| 실제 생성 Shader·플랫폼별 성능 실험·복잡한 HLSL 최적화 | 8.9 성능 주의, 8.10 후속 논의 | 일반 주의는 Keep; 상세 실행은 Move to Advanced | 이번 본문에 완성된 Profiling Case Study가 있는 것으로 단정하지 않는다. Chapter 09의 기본 측정과도 구분한다. |
| 대규모 Character Variation·자동화·Production Layer System | 8.8, 8.10 확장 방향 | 간단한 연결은 Keep; 실제 구축은 Move to Advanced | Character별 기본 적용은 Foundation 목적과 연결되지만 대량 관리·자동화는 별도 책임이다. |
| Built-in / Custom 선택 원칙 | 8.10 | Keep in Foundation / Shorten | 도구 선택 이유는 필요하다. 실제 Substrate/Renderer/HLSL 제작은 후속 과제로 분리한다. |

## 7. Figure Review Queue

**모든 아래 항목의 상태: Visual Review Required. 이미지 파일을 열거나 내용·정확성을 판정하지 않았다.** 상대 경로 존재 여부와 Markdown의 설명/번호만 확인했다.

메타데이터 결과: 이미지 참조 75건, 고유 상대 경로 69개, 존재하지 않는 경로 0개. 참조 경로의 Chapter08 / Fig8 접두사는 일치한다. 중복 경로는 Fig8_03/04/05/72/73/74의 6개이며 각 2회이다. 03–05는 본문 설명이 충돌하지만 72–74는 같은 검증/최종 구조의 재사용으로 구분한다.

| Figure | Section | Reason | What must be visually verified | Priority |
|---|---|---|---|---|
| Fig8_03–05 | 8.0 L225/387/587; 8.1 L199/241/289 | 환경/폴더 설명과 Architecture 설명이 같은 경로 사용 | 실제 이미지가 어느 설명에 해당하는지, 정확한 Caption과 참조 대상 | High |
| Fig8_24–27 | 8.2 | Light 입력과 최초 검증의 재현 전제 | 실제 Node 이름·방향·Space·Material 설정·연결·Scalar/Color 결과 | High |
| Fig8_19, Fig8_49 | 8.4 | Specular pin 설명과 최종 Unlit 구성 차이 | 실제 출력 pin, Saturate/Power 연결, Master 외부 Color/Intensity | High |
| Fig8_48 | 8.5 | Width/Softness 경계 계약 | Smoothstep Min/Max 배선과 테스트값, 상한 초과 및 Softness=0 설명과의 일치 | High |
| Fig8_58, Fig8_66, Fig8_73–74 | 8.6, 8.7, 8.10 | 합성식과 도식의 충돌 | Base Multiply, Shadow 적용, 독립 Spec/Rim, MatCap Lerp, 이후 Emission Add와 Debug 연결 | High |
| Fig8_69–72 | 8.9 | Mode 5 타입·표시값 불일치 | 실제 Function Input 타입/라벨, If threshold·fallback, 각 Mode 원본과 고정 노출 조건 | High |
| Fig8_28–40 | 8.3 | Depth/Visibility와 Engine Debug 해석 | 그림의 값이 Depth인지 Visibility인지, PCF 비교 후 평균, Bias와 실제 Debug 모드 설명의 대응 | Medium |
| Fig8_41–47, Fig8_50 | 8.5 | Fresnel-like 원리와 인터페이스 전환 | N/V convention, Power 예제에서 Width/Softness로 바뀐 단계, 결과 관찰 조건 | Medium |
| Fig8_51–57 | 8.6 | View-space Lookup·V flip·Blend | 좌표축과 Texture 방향, Remap/V flip, Intensity와 Blend의 위치·테스트 조건 | Medium |
| Fig8_59–64 | 8.7 | HDR/Bloom/Exposure와 Mask Data | 화면별 노출·Bloom 조건, Texture 설정·채널·UV Sample, Scalar 입력 위치 | Medium |
| Fig8_67–68 | 8.8 | 함수 입력과 외부 제어 도식 불일치 | Region Sample→Lerp→SpecularMask 외부 Multiply, 테스트 Material의 실제 연결 | Medium |
| Fig8_10, Fig8_14–18, Fig8_20–23 | 8.4 | Reflection / Power 원리와 구현 대응 | N/L/V 방향, clamp 전제, 예제값과 Caption, 초기/최종 구현 차이 | Medium |
| Fig8_01–02, Fig8_06–08 | 8.0 | 환경·자산 구성의 재현성 | 기록된 UE Build/설정과 UI 일치, 자산명·폴더와 본문 대응 | Low |
| 개요 Figure 8-1 placeholder | Chapter08 개요 L120 | 실제 이미지 경로 없음 | 새 도식이 필요한지 기존 Architecture Figure를 가리키는지 편집 의도 확인 | Medium |
| Fig8_09/11/12/13/65 및 비번호 이미지 파일 | Chapter08 Figure 폴더 | 파일은 있으나 이 Chapter의 Markdown 참조 없음 | 의도적 미사용/다른 용도인지 확인. 번호 공백만으로 누락이나 삭제 대상으로 판정하지 않음 | Low |

8.4의 참조 순서는 20–23 다음 10/14–19/49로 이어진다. 비연속 번호 자체는 이미지 내용 오류의 증거가 아니다. 후속 Registry 정리에서 최초 등장 순서와 번호 정책을 확인하며 이번에는 번호·파일·Caption을 변경하지 않는다. Fig8_72의 두 참조와 Fig8_73/74의 두 참조는 같은 자료의 재사용 필요성을 편집 관점에서 판단한다.

## 8. Refactoring Priority

### Priority 1 — Technical Accuracy / Architecture Conflict

08-02-A/B/C, 08-04-A/B, 08-05-C, 08-06-D, 08-09-A/B, 08-10-A/B/C를 먼저 처리한다. 실제 UE Build/Renderer/Material 조건에서 Light 입력을 확인하고 Stage/Module/MF, 합성식, Rim 경계값, MatCap off, Debug 타입을 정렬한다. Fresnel·Camera 변환·Exposure 인과·If/Compiler 동작의 불확실성은 검증 없이 확정 문장으로 바꾸지 않는다.

### Priority 2 — Data Flow

공통 N/L/V에서 독립 계산으로 분기하고 정확한 Multiply/Add/Lerp로 합류하는 최종 도식을 만든다. Texture→현재 UV Sample→선택 채널 Scalar는 기존의 정확한 설명을 보존한다. 8.8의 Intensity는 함수 출력 이후에 적용하고 Mode 5는 EmissionResult로 일치시킨다. 08-G-01의 Continuous→Stylized 연결을 명시한다.

### Priority 3 — Module Responsibility

Section 4의 계약을 기준으로 Input/Output 타입·Space·범위·Dependency·Reuse를 정리한다. Shadow는 Visibility 소비자, Region은 미통합 테스트, Master는 표현 합성, MI는 노출값 제어임을 명확히 한다. 지원/미지원과 Parameter 기본값·off값을 최종 표에 기록한다.

### Priority 4 — Foundation / Advanced Boundary

최소 구현·Mask 검증·Debug·MI·통합을 남긴다. 상세 Renderer 연결, 복잡한 HLSL/플랫폼 성능 연구, 대량 Variation/자동화는 실제 후속 범위로 분리한다. 현재 본문에 없는 심화 구현을 있는 것처럼 이동 대상으로 만들지 않는다.

### Priority 5 — Duplication / Cross Reference

Section 5의 Primary Source 후보를 정하고 이론·UI·목록·요약의 중복을 줄인다. 실제 구현에 필요한 연결 설명과 검증 Step은 보존한다. 구 Chapter 9/10 안내는 현재 Roadmap으로 수정할 대상으로 삼는다. Figure 03–05의 상충 참조를 해결한다.

### Priority 6 — Naming / Heading

ASF-001/003 기준으로 MF_BaseLighting 등 역할 이름을 통일하고 MaterialLayer/Region 상태, copy 및 FinalFramwork 파일명을 참조와 함께 정리한다. Chapter H1 / Major H2 / 무번호 Internal H3, 영어 Heading·한국어 본문 원칙을 적용한다. 프로젝트 부위명은 Outfit 결정과 정렬한다.

### Priority 7 — Minor Editing

8.9 L3504와 8.10 L4631의 잔여 `.s`, 문장 끝 잔여 기호, 형식과 Figure 번호 정책을 정리한다. 상위 계약이 바뀐 후 최종 Caption·표·요약이 같은 내용을 말하는지 점검한다.

### 후속 구현 검증의 최소 완료 조건 — 이번 Audit에서 실행하지 않음

- 같은 N/L Space·방향에서 정면/접선/후면의 LightingData 기대값 1/0/0 확인.
- Visibility 1/0.5/0 및 실제 Renderer Visibility 미연결 상태 구분.
- Specular clamp·전면/차폐 정책과 Rim 폭/전이의 유효 경계 확인.
- MatCapBlend 0에서 기존 합성 보존, 1에서 Lookup 선택, Intensity 0의 동작 구분.
- Emission Mask 0/0.5/1의 현재 Surface 값과 Region 외부 Multiply 확인.
- 고정 관찰 조건에서 DebugMode 0 보존 및 1–5 타입/원본 확인; 음수·소수·범위 초과 동작 기록.
- Compiler 분기·Static Switch·성능 주장은 해당 구현/측정 증거가 있을 때만 확정.

검수 완료 범위: 개요와 8.0–8.10 Markdown 12개 전체 Text Audit, 기준 문서 대조, Figure 경로 메타데이터 점검. 원본 Markdown 12개의 시작/종료 SHA-256이 모두 일치하여 변경 없음이 확인되었다. 이미지 내용 평가와 실제 Engine 검증은 별도 후속 작업이다.


# Audit Progress

Completed:
- 8.0
- 8.1
- 8.2
- 8.3
- 8.4
- 8.5
- 8.6
- 8.7
- 8.8
- 8.9
- 8.10

Next:
- None

Status:
Complete


