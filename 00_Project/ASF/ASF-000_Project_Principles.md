# ASF-000 Project Principles

> Version : v0.1  
> Status : Draft  
> Scope : Anime Shader Framework Project

---

# Purpose

본 문서는 Anime Shader Framework, 이하 ASF 프로젝트의 최상위 원칙을 정의한다.

ASF에서 작성되는 Standard, Library, Documentation, Implementation, Experiment, Portfolio는 본 문서에서 정의한 Project Principles를 기준으로 설계한다.

본 문서는 세부 Naming Rule이나 Folder Structure를 정의하기 위한 문서가 아니다.

ASF가

- 무엇을 학습하는 프로젝트인지
- 어떤 방식으로 지식을 구조화하는지
- 어떤 기준으로 구현과 검증을 진행하는지
- 최종적으로 어떤 역량을 증명하려는지

를 정의하는 것이 목적이다.

---

# Project Definition

ASF는 단순히 Anime Shader 하나를 만드는 프로젝트가 아니다.

ASF의 핵심 목적은 **Modern Real-Time Rendering의 기본 원리를 이해하고, 이를 실제 Character Rendering과 Stylized Rendering에 적용할 수 있는 Technical Art 역량을 구축하는 것**이다.

프로젝트의 전체 흐름은 다음과 같다.

```text
Modern Real-Time Rendering Foundation
            ↓
PBR Rendering
            ↓
Stylized Rendering
            ↓
Anime Shader Framework
            ↓
Character Rendering
            ↓
Profiling / Optimization
            ↓
Production Validation
```

Anime Shader는 프로젝트의 최종 목적이라기보다,

> **Rendering Pipeline과 PBR 원리를 이해한 뒤 Stylized Rendering으로 확장하는 대표적인 Case Study**

로 정의한다.

---

# Project Goals

ASF의 주요 목표는 다음과 같다.

### 1. Rendering Concept Understanding

Rendering Pipeline을 Node나 Tool 사용법 중심으로 외우지 않고, 데이터가 어떤 과정을 거쳐 최종 Pixel이 되는지 이해한다.

### 2. Character Rendering Application

Rendering Theory를 실제 Character Asset에 적용한다.

Skin, Hair, Eye, Face, Outfit 등 Character Rendering에서 자주 발생하는 문제를 Rendering Concept와 연결하여 분석한다.

### 3. Reusable Rendering Architecture

개별 효과를 독립적인 Material Function이나 Rendering Module로 구성하여 재사용 가능하고 확장 가능한 Architecture를 만든다.

### 4. Profiling and Optimization

Visual Result만 확인하는 것이 아니라 실제 Performance를 측정하고 Bottleneck을 분석한다.

### 5. Production-oriented Technical Art

기능 구현 자체보다

- 재사용성
- 유지보수성
- Debug 가능성
- Performance
- Production Workflow

까지 고려하는 것을 목표로 한다.

### 6. Portfolio Evidence

최종 결과만 보여주는 것이 아니라

```text
Problem
↓
Analysis
↓
Implementation
↓
Validation
↓
Optimization
↓
Result
```

과정을 통해 Technical Art 문제 해결 능력을 증명한다.

---

# Core Principles

## Principle 01. Concept Before Tool

Tool보다 Concept를 먼저 이해한다.

Unreal Engine, Unity, Blender는 Rendering Concept를 구현하기 위한 수단이다.

특정 Node 이름이나 Editor UI를 외우는 것보다,

```text
Input
↓
Processing
↓
Output
```

구조와 데이터의 의미를 이해하는 것을 우선한다.

Tool이 바뀌어도 Concept는 유지되어야 한다.

---

## Principle 02. Flow Before Implementation

ASF는 Node 중심이 아니라 **Data Flow 중심**으로 설명한다.

기능을 구현하기 전에 다음을 먼저 확인한다.

```text
어떤 Data가 들어오는가?
↓
어떤 계산이 수행되는가?
↓
어떤 Data로 변환되는가?
↓
다음 단계에서 어떻게 사용되는가?
```

Implementation은 Flow를 표현하기 위한 결과이다.

---

## Principle 03. Why Before How

구현 방법보다 먼저 왜 필요한지를 설명한다.

새로운 기능을 다룰 때는 다음 순서를 기본으로 한다.

```text
Problem
↓
Why
↓
Concept
↓
Flow
↓
Implementation
↓
Validation
```

단순히 "이 Node를 연결한다"가 아니라,

> 왜 이 계산이 필요하며 Rendering Pipeline에서 어떤 역할을 하는가

를 이해하는 것이 우선이다.

---

## Principle 04. Rendering Pipeline Is the Reference

ASF의 모든 Rendering Feature는 Rendering Pipeline을 기준으로 설명한다.

각 기능을 독립된 Trick으로 보지 않는다.

예를 들어 다음 기능들은 각각 독립적인 효과가 아니라 Rendering Pipeline의 특정 단계나 데이터와 연결된다.

```text
Normal
Lighting
Shadow
Specular
Rim Light
Emission
Transparency
Post Process
```

따라서 새로운 기능을 구현할 때는 항상 다음 질문을 한다.

```text
이 기능은 Rendering Pipeline의 어디에서 동작하는가?

어떤 Input Data를 사용하는가?

어떤 Output에 영향을 주는가?
```

---

## Principle 05. Rendering Stage and Rendering Module Are Different

Rendering Pipeline의 **Stage**와 ASF 내부의 **Module**을 구분한다.

Rendering Stage는 GPU Rendering Pipeline의 처리 단계이다.

예를 들면 다음과 같다.

```text
Vertex Processing
↓
Primitive Processing
↓
Rasterization
↓
Pixel Processing
↓
Output
```

Rendering Module은 특정 Rendering Feature를 구현하는 기능 단위이다.

예를 들면 다음과 같다.

```text
Base Lighting
Shadow
Specular
Rim Light
MatCap
Emission
Debug View
```

Module은 Pipeline Stage가 아니다.

Module은 특정 Stage 안에서 사용되는 Rendering Logic이다.

이 구분을 유지함으로써 Engine Architecture와 Shader Feature를 혼동하지 않는다.

---

## Principle 06. PBR Is the Foundation

ASF는 Stylized Rendering을 PBR과 분리된 별도의 Rendering 방식으로 다루지 않는다.

Stylized Rendering 역시

- Light
- Normal
- View Direction
- Material Property
- Shadow
- Reflection

같은 동일한 Rendering Data를 사용한다.

차이는 주로 **그 데이터를 어떻게 변환하고 표현하는가**에 있다.

따라서 ASF에서는 먼저 PBR Rendering을 이해하고, 그 원리를 기반으로 Stylized Rendering을 분석한다.

```text
Rendering Fundamentals
↓
PBR
↓
Stylized Interpretation
```

---

## Principle 07. Stylization Is Controlled Deviation

Stylized Rendering은 물리 기반 Rendering을 단순히 무시하는 것이 아니다.

필요한 Rendering Principle을 이해한 뒤, 의도적으로 표현을 변경하는 과정이다.

예를 들어

```text
Continuous Lighting
↓
Threshold
↓
Discrete Lighting Band
```

처럼 실제 Lighting Data를 Stylized Rule로 변환할 수 있다.

따라서 Stylization은

> **Rendering Principle을 이해한 상태에서 Visual Goal을 위해 의도적으로 데이터를 재해석하는 과정**

으로 정의한다.

---

## Principle 08. Character Rendering Is the Primary Application

ASF는 범용 Rendering Theory를 학습하지만, 주요 적용 대상은 Character Rendering이다.

따라서 다음 요소들을 중요하게 다룬다.

```text
Skin
Hair
Eye
Face
Outfit
Accessory
Transparency
Deformation
LOD
```

Rendering Theory는 실제 Character Asset에서 발생하는 문제와 연결하여 검증한다.

---

## Principle 09. Visual Result Alone Is Not Enough

화면에서 보기 좋은 결과가 나왔다고 구현이 완료된 것은 아니다.

각 Rendering Feature는 가능한 범위에서 다음 항목을 확인한다.

```text
Visual Result

Rendering Data

Debug View

Edge Case

Performance

Maintainability
```

결과가 맞는 이유를 설명할 수 있어야 한다.

---

## Principle 10. Measurement Before Optimization

Optimization은 추측으로 진행하지 않는다.

먼저 Performance를 측정하고 Bottleneck을 확인한다.

기본 Workflow는 다음과 같다.

```text
Measure
↓
Identify Bottleneck
↓
Analyze Cause
↓
Optimize
↓
Measure Again
```

Triangle Count, Shader Complexity, Draw Call 등 특정 수치가 높다는 이유만으로 무조건 수정하지 않는다.

현재 Frame을 실제로 제한하는 Cost를 먼저 찾는다.

---

## Principle 11. One Variable at a Time

Experiment와 Optimization에서는 가능한 한 한 번에 하나의 조건만 변경한다.

예를 들어 Geometry Cost를 검증하면서 동시에 Resolution, Material, Lighting을 변경하면 원인을 구분하기 어렵다.

따라서 다음 방식을 기본으로 한다.

```text
Baseline
↓
Single Variable Change
↓
Measure
↓
Compare
```

이를 통해 Cause와 Result의 관계를 명확하게 만든다.

---

## Principle 12. Theory and Experiment Are Different

개념 설명과 실제 검증 실험을 구분한다.

Foundation 단계에서는 주로

```text
Concept
Principle
Data Flow
Basic Verification
```

을 다룬다.

Advanced 단계에서는

```text
Controlled Experiment
Bottleneck Reproduction
Profiling
Optimization
Before / After
Case Study
```

를 다룬다.

Foundation에서 모든 개념을 깊은 실험까지 확장하지 않는다.

---

## Principle 13. Foundation and Advanced Have Different Roles

ASF Documentation은 크게 Foundation과 Advanced 역할로 나눈다.

### Foundation

Foundation은 Rendering을 이해하기 위한 기준을 만든다.

```text
What
Why
Concept
Flow
Relationship
Basic Verification
```

이 중심이다.

목표는 특정 Technique를 많이 배우는 것이 아니라, Rendering 문제를 이해할 수 있는 사고 구조를 만드는 것이다.

### Advanced

Advanced는 Foundation에서 학습한 Concept를 실제 Production Problem에 적용한다.

```text
Concept
↓
Implementation
↓
Verification
↓
Debugging
↓
Optimization
↓
Case Study
```

실제 Unreal Engine Scene과 Character Asset을 사용해 결과를 검증한다.

---

## Principle 14. Documentation Is Part of the Engineering Process

ASF에서 Documentation은 구현 이후에 결과를 정리하는 부가 작업이 아니다.

다음 과정을 반복한다.

```text
Learn
↓
Implement
↓
Document
↓
Review
↓
Refactor
```

문서를 작성하면서 개념이 명확하지 않은 부분을 찾고, 다시 구현과 검증으로 돌아간다.

Documentation은 Knowledge Validation 과정의 일부이다.

---

## Principle 15. Avoid Duplicate Sources of Truth

같은 개념을 여러 문서에서 각각 다르게 정의하지 않는다.

이미 Foundation에서 충분히 설명한 Concept를 Standard 문서에서 다시 상세하게 설명하지 않는다.

Standard는 원칙을 정의하고,

Documentation은 Concept를 설명하며,

Implementation 문서는 실제 적용 과정을 다룬다.

```text
Standard
→ Rule

Documentation
→ Knowledge

Implementation
→ Application
```

하나의 개념에는 가능한 한 하나의 기준 Source를 유지한다.

---

## Principle 16. Reuse Through Modules

ASF의 Rendering Feature는 가능한 한 독립적인 기능 단위로 설계한다.

예를 들어 Unreal Engine에서는 다음과 같은 형태가 될 수 있다.

```text
MF_BaseLighting

MF_Shadow

MF_Specular

MF_RimLight

MF_MatCap

MF_Emission
```

각 Module은 명확한 Input과 Output을 가져야 한다.

하나의 Module이 지나치게 많은 역할을 담당하지 않도록 한다.

---

## Principle 17. Debuggability Is a Feature

Debug 기능은 최종 구현 이후에 추가하는 옵션이 아니다.

Rendering System은 내부 Data를 확인할 수 있어야 한다.

예를 들어 다음과 같은 정보를 확인할 수 있어야 한다.

```text
Normal

Light Direction

NdotL

Shadow

Mask

Specular

Final Lighting
```

Debugging이 어려운 Architecture는 유지보수와 확장이 어렵다.

따라서 Debug View는 Framework의 일부로 취급한다.

---

## Principle 18. Visual Quality and Performance Are Evaluated Together

Optimization의 목표는 가능한 한 낮은 Cost가 아니다.

Character Rendering에서는 Visual Quality가 중요하다.

따라서 결과는 항상 다음 두 요소를 함께 평가한다.

```text
Visual Quality
+
Performance
```

필요한 품질을 유지하면서 목표 Performance Budget 안에 들어오는 것을 목표로 한다.

---

## Principle 19. Production Value Over Technical Novelty

ASF의 목표는 새로운 Rendering Algorithm을 발명하는 것이 아니다.

이미 알려진 Rendering Technique이라도,

```text
왜 사용하는지

어떻게 동작하는지

어떤 문제를 해결하는지

어떻게 검증하는지

Production에서 어떻게 관리하는지
```

를 이해하고 실제로 구현할 수 있다면 충분한 가치가 있다.

Technical Novelty보다 **실제 Production에서 사용할 수 있는 이해와 문제 해결 능력**을 우선한다.

---

## Principle 20. Portfolio Shows Decisions, Not Only Results

Portfolio에서는 최종 Image만 보여주지 않는다.

Technical Artist의 역할을 보여주기 위해 다음 과정을 기록한다.

```text
Problem
↓
Requirement
↓
Analysis
↓
Technical Decision
↓
Implementation
↓
Validation
↓
Optimization
↓
Final Result
```

중요한 것은

> 무엇을 만들었는가

뿐만 아니라,

> 왜 그렇게 설계했는가

를 설명할 수 있는 것이다.

---

# Project Layers

ASF 프로젝트는 역할에 따라 다음 Layer로 구성한다.

```text
Project Principles / Standard
            ↓
Knowledge Documentation
            ↓
Implementation / Experiment
            ↓
Character Application
            ↓
Portfolio Case Study
```

각 Layer는 서로 다른 목적을 가진다.

---

## Project Principles / Standard

프로젝트 전체에서 유지해야 하는 규칙과 기준을 정의한다.

예:

```text
Project Principles
Naming Philosophy
Rendering Architecture
Documentation Standard
```

---

## Knowledge Documentation

Rendering Concept와 원리를 설명한다.

Foundation이 대표적인 Knowledge Documentation이다.

```text
Rendering Pipeline
Coordinate System
Texture and Material
Lighting
Shadow
Optimization
```

---

## Implementation / Experiment

Concept를 실제 Engine에서 구현하고 검증한다.

```text
Material Function
Shader
Debug View
Profiling Test
Optimization Test
```

---

## Character Application

Framework를 실제 Character Asset에 적용한다.

```text
Skin
Hair
Eye
Face
Outfit
```

---

## Portfolio Case Study

실제 문제 해결 과정을 정리한다.

```text
Problem
↓
Analysis
↓
Implementation
↓
Profiling
↓
Optimization
↓
Before / After
↓
Result
```

---

# Decision Priority

Project Rule이나 Documentation Direction이 충돌하는 경우 다음 우선순위를 따른다.

```text
Project Principles
↓
Accepted Decision Log
↓
Current Standard
↓
Documentation
↓
Implementation Detail
```

단, 새로운 실험이나 검증 결과가 기존 Standard와 충돌한다면 Standard 자체를 다시 검토할 수 있다.

ASF Standard는 고정된 규칙집이 아니라 검증 결과에 따라 발전하는 기준이다.

---

# Refactoring Principle

ASF는 지속적으로 Refactoring한다.

Refactoring은 단순히 문장을 줄이는 작업이 아니다.

다음 기준으로 판단한다.

```text
Is it Correct?

Is it Necessary?

Is it Clear?

Is it Duplicated?

Is it Consistent?

Is it Verifiable?
```

필요하다면

```text
Keep

Rewrite

Merge

Move

Remove
```

중 하나를 선택한다.

오래된 문서라는 이유만으로 유지하지 않으며, 새 문서라는 이유만으로 우선하지 않는다.

현재 프로젝트 철학과 검증 결과를 기준으로 판단한다.

---

# Final Principle

ASF에서 가장 중요한 것은 특정 Shader Technique를 많이 구현하는 것이 아니다.

Rendering Problem을 만났을 때

```text
무슨 Data가 필요한가?

어디에서 처리되는가?

왜 이런 결과가 발생하는가?

어떻게 확인할 수 있는가?

어떻게 개선할 수 있는가?
```

를 스스로 분석할 수 있는 능력을 만드는 것이 목표이다.

따라서 ASF는 다음 흐름을 반복한다.

```text
Understand
↓
Build
↓
Observe
↓
Validate
↓
Optimize
↓
Document
↓
Refactor
```

> **ASF는 Anime Shader를 만드는 프로젝트가 아니라, Modern Real-Time Character Rendering을 이해하고 설계하고 검증하는 능력을 구축하는 프로젝트이다.**