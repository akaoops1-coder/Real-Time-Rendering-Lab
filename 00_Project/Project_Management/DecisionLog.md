# Decision Log

> Architecture Decisions

---

# DEC-001

Date

2026-07-08

Decision

프로젝트의 의상(Cloth) 용어를 Outfit으로 통일한다.

Reason

Outfit은 일반 의상뿐 아니라 갑옷, 메카닉 슈트, 드레스, 교복, 코트 등 모든 외형을 포함할 수 있는 범용적인 표현이다.

Status

Accepted

---

# DEC-002

Date

2026-07-08

Decision

ShaderLibrary를 Library로 변경한다.

Reason

프로젝트에서 사용하는 라이브러리는 Shader뿐 아니라 Mathematics, Rendering, GPU, Texture, Color 등 다양한 공통 지식을 포함한다.

Library가 프로젝트의 역할을 더 정확하게 표현한다.

Status

Accepted

---

# DEC-003

Date

2026-07-08

Decision

ASF_Standard.md는 규격(Index) 문서로 사용한다.

Reason

각 규격을 독립 문서(ASF-001, ASF-002...)로 관리하면 유지보수와 확장성이 크게 향상된다.

Status

Accepted

---

# DEC-004

Date

2026-07-08

Decision

ASF 프로젝트는 세 개의 Layer로 구성한다.

Architecture

Level 1

ASF Standard

↓

Level 2

Library

↓

Level 3

Documentation

Reason

규격(Standard), 공통 지식(Library), 구현(Documentation)을 분리하여 중복을 최소화하고 유지보수를 쉽게 한다.

Status

Accepted

---

## DEC-005

Date

2026-07-08

Title

Flow First Principle

Decision

ASF는 Node 중심이 아닌 Data Flow 중심으로 설계한다.

Reason

Node는 플랫폼마다 구현 방식이 다르지만,

Data Flow는 플랫폼과 관계없이 동일한 Rendering Concept를 표현한다.

Flow를 이해하면 Blender, Unity, Unreal Engine 모두에서 동일한 Rendering Concept를 구현할 수 있다.

ASF는 특정 툴의 사용법을 배우는 프로젝트가 아니라,

Rendering Concept를 이해하고 Data Flow를 설계하는 프로젝트를 목표로 한다.

Impact

- README 프로젝트 철학 수정
- ASF-006 Rendering Architecture 수정
- ASF-007 Documentation Standard 작성 기준 확립

Status

Accepted

---

## DEC-006

Date
2026-07-09

Title
Rendering Stage와 Rendering Module의 역할 분리

Decision

Rendering Stage와 Rendering Module을 서로 다른 개념으로 정의한다.

Reason

Stage는 Rendering Pipeline 안에서의 실행 단계이며,

Module은 하나의 기능(Function)을 수행하는 최소 단위이다.

두 용어를 분리하면 Pipeline 구조를 보다 명확하게 설명할 수 있다.

Status

Accepted

---

## DEC-007

Date
2026-07-09

Title
Documentation Hierarchy

Decision

ASF Documentation는 Book 구조가 아니라 Knowledge Base 구조를 따른다.

Reason

문서는 Volume이나 Chapter보다 주제(Concept) 중심으로 관리하는 것이
검색성과 유지보수성이 높다.

Status

Accepted

---

## DEC-008

Date

2026-07-09

Title

프로젝트 방향의 현실적 고려 (Career First Roadmap)

Decision

ASF 프로젝트의 단기 최우선 목표를
TA 취업을 위한 포트폴리오 구축으로 정의한다.

장기적인 Framework 개발은 지속하되,
프로젝트의 우선순위는 취업에 직접 활용 가능한 결과물을 먼저 완성하는 것으로 한다.

Reason

ASF는 장기적으로 Cross Platform Rendering Framework를 구축하는 것을 목표로 한다.

그러나 현재 가장 중요한 현실적 목표는
2026년 말~2027년 초 TA 포지션으로의 이직이다.

따라서 프로젝트의 우선순위는

포트폴리오 가치가 높은 결과물

↓

Framework 확장

순으로 진행한다.

Target Schedule

2026.07 ~ 2026.09

포트폴리오 제작

2026.10 ~

구직 활동

이후

ASF 장기 개발 지속

Impact

- Roadmap 재구성
- Portfolio 폴더 추가
- TODO 우선순위 변경
- 구현 순서를 Portfolio 중심으로 조정

Status

Accepted

---

## DEC-009

Date

2026-07-09

Title

검증 기록을 남겨야 함

Decision

ASF의 모든 Prototype은 Validation.md를 반드시 가진다.

Reason

구현과 검증을 분리한다.
재현 가능한 테스트 기록을 남긴다.
Blender, Unity, Unreal 간 검증 기준을 통일한다.
포트폴리오에서 "구현했다"가 아니라 "검증했다"는 근거를 보여준다.

Status

Accepted

---

## DEC-010

Date

2026-07-11

Title

Library Documentation Philosophy

Decision

ASF Library는 용어를 정의하는 사전(Dictionary)이 아니라,
Rendering Concept의 사고 흐름(Thinking Flow)을 연결하는 Knowledge Base로 작성한다.

Reason

단순한 용어 정의는 암기로 이어질 가능성이 높다.

ASF는 Reality부터 Platform Implementation까지
하나의 흐름으로 이해하는 것을 목표로 한다.

모든 Library 문서는
용어의 정의보다 개념 간의 연결을 우선하여 작성한다.

Expected Structure

Reality

↓

Concept

↓

Rendering Model

↓

Rendering Flow

↓

Platform Implementation

↓

Related Concepts

Status

Accepted

---

## DEC-011

Date

2026-07-15

Title

ASF Learning Flow Revision

Decision

ASF의 기본 학습 흐름을 다음과 같이 수정한다.

Reality
↓
Question
↓
Observation
↓
Concept
↓
Model
↓
Math
↓
Implementation

Reason

기존 Reality → Concept 구조는
모델이 탄생한 사고 과정을 충분히 설명하지 못했다.

ASF는 기술 자체보다
기술이 만들어진 사고 과정을 이해하는 것을 목표로 한다.

Impact

- README Philosophy 수정
- Documentation Guideline 수정
- Library 작성 기준 수정

Status

Accepted

---

## DEC-012

Title

Research-first Documentation

Decision

ASF는 그래픽스 기술을 설명하는 프로젝트가 아니라,
그래픽스 기술이 탄생한 사고 과정을 기록하는 프로젝트로 정의한다.

Reason

기술을 암기하는 방식보다
현실 → 질문 → 관찰 → 모델 생성의 과정을 따라갈 때
개념의 연결성과 이해도가 크게 향상되었다.

Impact

Reflection 이후 모든 Library 문서 작성 기준으로 사용한다.

Status

Accepted

---

## DEC-013

Date

2026-07-28

Title

Problem-driven Documentation Philosophy

Decision

ASF의 모든 Documentation와 Library는
정의(Definition) 중심이 아니라
문제 해결(Problem-driven) 중심으로 작성한다.

모든 개념은 가능한 한 다음 사고 흐름을 따른다.

Reality

↓

Problem

↓

Observation

↓

Idea

↓

Generalization

↓

Model

↓

Math

↓

Implementation

수학적 정의와 공식은 가능한 한 마지막에 소개하며,
먼저 "왜 이 개념이 필요했는가?"를 이해시키는 것을 우선한다.

Reason

기존의 그래픽스 문서는 용어와 정의를 먼저 설명하는 경우가 많다.

하지만 이러한 방식은 개념의 연결성을 이해하기보다
정의를 암기하게 만들 가능성이 높다.

ASF는 연구자들이 실제로 문제를 발견하고,
관찰하고,
새로운 개념을 만들고,
이를 수학적으로 일반화하는 사고 과정을 따라가는 것을 목표로 한다.

모든 개념은

"무엇인가?"

보다

"왜 필요했는가?"

를 먼저 설명한다.

예를 들어

Reflection Model은

Lambert

↓

Phong

↓

Cook-Torrance

로 발전하며 이전 모델의 한계를 해결한다.

Radiometry는

Radiant Flux

↓

Radiant Intensity

↓

Irradiance

↓

Radiance

로 발전하며
각 물리량으로 설명할 수 없었던 문제를 해결한다.

BRDF 역시 이러한 문제 해결 과정 속에서
Surface Reflection을 일반화하기 위해 등장한다.

ASF는 개념의 정의보다
개념이 탄생한 이유와
이전 개념의 한계를 중심으로 설명한다.

Impact

- Documentation Guideline 수정
- README Philosophy 수정
- Reflection 이후 모든 Documentation 및 Library 작성 기준 적용
- Radiometry, BRDF, Rendering Equation 문서를 Problem-driven 구조로 재구성

Status

Accepted

---

## DEC-014

Date

2026-07-29

Title

Modern Real-Time Rendering을 Stylized Rendering보다 먼저 학습한다.

Decision

ASF의 학습 흐름에서 Reflection & BRDF 이후 바로 Stylized Rendering으로 넘어가지 않는다.

Modern Real-Time Rendering을 먼저 학습하여 현대 실시간 렌더링의 전체 Pipeline과 핵심 개념을 이해한 후, 그 기반 위에서 Stylized Rendering과 Anime Shader Framework를 진행한다.

Reason

Anime Shader는 독립적인 Rendering 기법이 아니라,
현대 PBR 기반 Rendering Pipeline 위에서 Stylization을 수행하는 Rendering 기법이다.

BRDF를 학습한 이후에도 다음과 같은 핵심 개념들이 필요하다.

- Modern Rendering Pipeline
- Image Based Lighting (IBL)
- Environment Lighting
- Reflection Probe
- HDR
- Tone Mapping
- Linear Color Space
- Gamma
- Metallic / Roughness Workflow

이러한 개념을 먼저 이해해야 Stylized Rendering이 기존 Rendering Pipeline의 어느 단계에서 어떠한 방식으로 동작하는지 자연스럽게 설명할 수 있다.

ASF의 목표는 Toon Shader를 구현하는 것이 아니라,
현대 실시간 렌더링을 이해한 뒤 그 기반 위에서 Stylized Rendering을 설계하는 것이다.

Impact

- Chapter06의 방향을 Modern Real-Time Rendering으로 변경
- Stylized Rendering은 이후 Chapter로 이동
- Reflection & BRDF 이후 Modern Rendering 학습 흐름 추가
- ASF Documentation의 학습 범위를 Modern Real-Time Rendering까지 확장

Status

Accepted

---

## DEC-015

Date

2026-07-30

Title

ASF Scope Expansion: From Anime Shader to Comprehensive Real-Time Rendering Framework

Decision

ASF는 Anime Shader Framework라는 이름을 유지하되, 프로젝트의 범위를 Anime Shader 구현에 한정하지 않는다.

ASF의 목표는 현대 Real-Time Rendering을 체계적으로 이해하고, Physically Based Rendering(PBR)과 Stylized Rendering(NPR)을 동일한 수준으로 학습·비교·구현할 수 있는 Rendering Framework를 구축하는 것으로 확장한다.

Anime Shader는 프로젝트의 최종 목표가 아니라, PBR과 NPR를 이해한 뒤 이를 실제로 응용하는 대표적인 사례(Case Study)로 정의한다.

모든 Rendering 요소는 가능한 한 다음 구조를 따른다.

PBR Theory
Stylized Rendering
Comparison
ASF Implementation

이를 통해 특정 스타일의 구현 방법이 아니라, Rendering Concept 자체를 이해하고 플랫폼에 관계없이 구현할 수 있는 능력을 목표로 한다.

Reason

기존 ASF는 Anime Shader 구현을 중심으로 프로젝트를 시작하였다.

그러나 프로젝트가 진행되면서 Lambert, BRDF, Modern Real-Time Rendering, HDR, Tone Mapping, Color Space 등 현대 Rendering Pipeline 전반을 학습하게 되었고, Stylized Rendering 역시 이러한 기반 위에서 이해하는 것이 가장 자연스럽다는 결론에 도달하였다.

또한 현실적인 Rendering 기술을 충분히 이해해야 Stylized Rendering이 기존 Rendering Pipeline의 어떤 부분을 유지하고, 어떤 부분을 단순화하거나 의도적으로 변형하는지 설명할 수 있다.

ASF는 특정 스타일을 구현하는 방법을 설명하는 프로젝트가 아니라,

"왜 이러한 Rendering Model이 만들어졌으며, 어떤 문제를 해결하고, 어떤 상황에서 선택되는가"

를 이해하는 것을 목표로 한다.

Impact

프로젝트 철학(Project Philosophy) 확장
README 부제 및 프로젝트 소개 수정
Chapter 7을 PBR ↔ Stylized Rendering 비교 구조로 재설계
Hair, Specular, Shadow, Rim Lighting 등 주요 Rendering 요소를 PBR과 NPR를 동일한 수준으로 설명
Anime Shader를 Rendering Concept의 응용 사례(Case Study)로 재정의
플랫폼 독립적인 Rendering 사고 체계를 강화

Status

Accepted

---

# DEC-016 Theory and Experiment Separation

- **Status**: Accepted
- **Date**: 2026-07-31

---

## Context

ASF 프로젝트 초기에는 Rendering 이론을 학습한 뒤,

즉시 Unreal Engine에서 테스트를 수행하고,

결과를 분석하여 문서화하는 Research 중심의 진행 방식을 계획하였다.

하지만 프로젝트가 진행되면서 Foundation 문서를 먼저 완성하는 것이

전체적인 학습 흐름과 문서 구조에 더 적합하다는 결론에 도달하였다.

---

## Decision

Theory와 Experiment를 분리한다.

### Phase 1

Rendering Theory

- Rendering Fundamentals
- Physically Based Rendering
- Stylized Rendering

위 내용을 먼저 완성한다.

이 단계에서는 개념을 이해하고,

PBR과 Stylized Rendering의 차이를 설명하는 데 집중한다.

구현 과정이나 테스트 결과는 포함하지 않는다.

---

### Phase 2

Theory가 완료된 이후,

Rendering Experiments를 진행한다.

모든 구현은 다음 과정을 따른다.

Theory

↓

Hypothesis

↓

Implementation

↓

Experiment

↓

Observation

↓

Problem

↓

Analysis

↓

Solution

↓

Documentation

실험 과정과 실패 사례 역시 ASF의 중요한 학습 자료로 기록한다.

---

## Consequences

### 장점

- Foundation 문서의 흐름이 끊기지 않는다.
- Rendering 개념을 먼저 체계적으로 이해할 수 있다.
- 실험 결과를 이론과 명확하게 연결할 수 있다.
- 구현 과정과 문제 해결 과정을 독립적으로 기록할 수 있다.

### 향후 계획

Chapter 8부터는 단순한 Implementation이 아니라,

Theory를 실제 Rendering으로 검증하는

**Rendering Experiments**를 진행한다.

실험이 완료되면,

현재 AI 기반으로 제작한 Figure들은

동일한 Scene과 동일한 Camera,

동일한 Directional Light 환경에서

직접 캡처한 결과 이미지로 순차적으로 교체한다.

이를 통해 ASF의 Figure는 실제 구현 결과를 기반으로 한

검증 가능한 자료로 발전시킨다.

---

## Rationale

ASF는 단순한 Shader 제작 문서가 아니라,

Rendering Theory를 이해하고,

직접 구현하고,

검증하며,

문제를 해결하는 과정을 기록하는 Framework를 목표로 한다.

Theory와 Experiment를 분리함으로써

학습 흐름과 연구 흐름을 모두 유지할 수 있다.

---

DEC-XXX

Title
ASF Standard Renumbering

Decision

기존 ASF-006 Rendering Architecture를 ASF-002로 변경한다.

기존 ASF-007 Documentation Standard를 ASF-003으로 변경한다.

초기 계획에 존재했던 ASF-002~005, ASF-008은
현재 프로젝트 구조에서 독립 Standard가 필요하지 않아 폐기한다.

Reason

초기 Standard 계획과 실제 프로젝트 구조가 달라졌으며,
불필요한 번호 공백은 문서 체계를 이해하는 데 혼란을 줄 수 있다.

현재 유지되는 Standard만 연속 번호로 재구성하여
Document Architecture를 단순화한다.