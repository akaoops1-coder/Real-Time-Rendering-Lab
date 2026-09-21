# ASF Standard

> Version : v0.3  
> Status : Draft  
> Scope : Anime Shader Framework Project

---

# Purpose

본 문서는 Anime Shader Framework, 이하 ASF 프로젝트에서 사용하는 Standard 문서 체계와 각 Standard의 역할을 정의한다.

ASF Standard는 Rendering Concept 자체를 상세히 설명하기 위한 문서가 아니다.

프로젝트 전체에서 반복적으로 사용되는

- Project Principle
- Naming Rule
- Rendering Architecture
- Documentation Rule

등의 기준을 정의하고, 각 기준의 책임 범위를 명확하게 유지하는 것이 목적이다.

---

# Standard Philosophy

ASF Standard는 많은 규칙을 만드는 것을 목표로 하지 않는다.

필요한 기준만 유지한다.

Standard가 지나치게 많아지면 실제 Documentation과 중복되는 내용이 증가하고, 동일한 개념을 여러 위치에서 수정해야 하는 문제가 발생할 수 있다.

따라서 ASF에서는 다음 원칙을 따른다.

```text
Create Standards Only When Necessary
              ↓
Keep One Source of Truth
              ↓
Avoid Duplicate Definitions
              ↓
Refactor When the Project Evolves
```

현재 ASF에서는 실제로 필요한 Standard만 유지하며, 사용하지 않는 번호를 채우기 위해 새로운 Standard를 만들지 않는다.

---

# Standard Hierarchy

ASF 프로젝트의 기준은 다음 순서로 적용한다.

```text
ASF-000 Project Principles
          ↓
Accepted Decision Log
          ↓
ASF Standards
          ↓
Documentation
          ↓
Implementation
```

상위 기준과 하위 문서가 충돌하는 경우 상위 기준을 우선한다.

단, 새로운 Implementation이나 Experiment를 통해 기존 기준이 잘못되었거나 더 이상 적절하지 않다는 사실이 확인되면 상위 Standard 자체를 다시 검토할 수 있다.

---

# Active Standards

현재 ASF에서 사용하는 Standard는 다음 네 개이다.

| ID | Document | Role | Status |
|---|---|---|---|
| ASF-000 | Project Principles | ASF 프로젝트의 최상위 철학과 판단 기준 | Active |
| ASF-001 | Naming Philosophy | Naming의 기본 철학과 ASF-specific Naming 기준 | Active |
| ASF-002 | Rendering Architecture | Rendering Pipeline, Rendering Data, Module Architecture 정의 | Active |
| ASF-003 | Documentation Standard | ASF 문서의 작성 원칙과 구조 정의 | Active |

현재 Standard 번호는 `ASF-000`부터 `ASF-003`까지 연속적으로 구성한다.

---

# ASF-000 Project Principles

`ASF-000 Project Principles`는 ASF 프로젝트의 최상위 기준이다.

다음 내용을 정의한다.

```text
Project Definition

Project Goals

Core Principles

Foundation / Advanced Roles

Validation Philosophy

Optimization Philosophy

Portfolio Direction
```

다른 Standard를 수정하거나 새로운 규칙을 추가할 때는 먼저 ASF-000과 충돌하지 않는지 확인한다.

ASF 프로젝트의 방향이 변경될 경우 가장 먼저 검토해야 하는 문서이다.

---

# ASF-001 Naming Philosophy

`ASF-001 Naming Philosophy`는 ASF 프로젝트에서 사용하는 Naming의 기본 철학을 정의한다.

이 문서는 모든 Engine Asset 이름을 세부적으로 강제하는 Naming Convention 문서가 아니다.

각 Platform이 제공하는 Naming Convention을 우선하며, ASF에서는 Framework의 구조와 역할을 명확하게 표현하기 위해 필요한 Naming 원칙을 정의한다.

주요 범위는 다음과 같다.

```text
Readable Names

Role-based Naming

Consistent Prefixes

Framework Module Naming

Debug Asset Naming

Test Asset Naming
```

Unreal Engine의 일반 Asset Naming Convention과 중복되는 세부 내용은 Implementation Documentation에서 관리한다.

---

# ASF-002 Rendering Architecture

`ASF-002 Rendering Architecture`는 ASF Rendering System의 구조를 정의한다.

이 문서에서는 다음 개념을 구분한다.

```text
Rendering Pipeline Stage

Rendering Data

Rendering Module

Material Function

Character Rendering Feature

Debug / Validation

Profiling / Optimization
```

Rendering Pipeline의 실제 Stage와 ASF 내부 Shader Feature를 동일한 개념으로 다루지 않는다.

예를 들어 다음은 Rendering Pipeline Stage에 해당한다.

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

반면 다음은 ASF Rendering Module에 해당한다.

```text
Base Lighting
Shadow
Specular
Rim Light
MatCap
Emission
Debug View
```

ASF-002는 Rendering Pipeline, Rendering Data, Rendering Module, Character Application이 어떤 관계를 가지는지를 정의하는 Architecture Standard이다.

---

# ASF-003 Documentation Standard

`ASF-003 Documentation Standard`는 ASF에서 작성되는 Documentation의 구성과 작성 원칙을 정의한다.

주요 범위는 다음과 같다.

```text
Documentation Philosophy

Language Standard

Heading Structure

Concept Explanation

Data Flow Explanation

Figure Rules

Cross Reference

Foundation / Advanced Documentation

Validation

Audit / Refactoring
```

Rendering Concept 자체에 대한 상세 설명은 ASF-003에 포함하지 않는다.

그 내용은 Foundation 또는 Advanced Documentation에서 관리한다.

---

# Current Standard Structure

현재 ASF Standard 구조는 다음과 같다.

```text
ASF Standard
│
├─ ASF-000 Project Principles
│
├─ ASF-001 Naming Philosophy
│
├─ ASF-002 Rendering Architecture
│
└─ ASF-003 Documentation Standard
```

각 Standard는 서로 다른 책임을 가진다.

```text
ASF-000
→ Why / Direction

ASF-001
→ Naming

ASF-002
→ Rendering System Structure

ASF-003
→ Documentation
```

하나의 Standard가 다른 Standard의 역할을 불필요하게 반복하지 않는다.

---

# Previous Standard Structure

초기 ASF 설계에서는 다음과 같은 Standard 체계가 계획되어 있었다.

```text
ASF-001 Naming Philosophy
ASF-002 Folder Structure
ASF-003 Coordinate Convention
ASF-004 Texture Standard
ASF-005 Material Standard
ASF-006 Rendering Architecture
ASF-007 Documentation Standard
ASF-008 Validation Standard
```

프로젝트가 진행되면서 실제 필요성과 Documentation 구조가 명확해졌고, 일부 Planned Standard는 별도의 독립 문서로 유지할 필요가 없다고 판단했다.

또한 기존 `ASF-006`과 `ASF-007`만 유지할 경우 불필요한 번호 공백이 발생하므로 현재 Standard 체계를 재구성했다.

---

# Standard Renumbering

기존 Standard는 다음과 같이 변경한다.

```text
ASF-000 Project Principles
→ ASF-000 Project Principles

ASF-001 Naming Philosophy
→ ASF-001 Naming Philosophy

ASF-006 Rendering Architecture
→ ASF-002 Rendering Architecture

ASF-007 Documentation Standard
→ ASF-003 Documentation Standard
```

기존 `ASF-002`, `ASF-003`, `ASF-004`, `ASF-005`, `ASF-008` Planned Standard는 현재 독립 Standard로 사용하지 않는다.

---

# Retired Planned Standards

초기 계획에 존재했던 다음 Standard는 현재 구조에서 제거한다.

```text
ASF-002 Folder Structure

ASF-003 Coordinate Convention

ASF-004 Texture Standard

ASF-005 Material Standard

ASF-008 Validation Standard
```

각 항목은 아래와 같은 이유로 별도 Standard로 유지하지 않는다.

---

# Folder Structure

Folder Structure는 Platform과 Implementation 환경에 따라 달라질 수 있다.

예를 들어 Unreal Engine Content Browser 구조는 Unreal Implementation Documentation에서 관리한다.

따라서 ASF 전체에 적용되는 독립 Standard로 유지하지 않는다.

필요한 Project Structure는 해당 Implementation 문서에서 정의한다.

---

# Coordinate Convention

Coordinate System은 매우 중요한 Rendering Concept이지만 ASF-specific Standard는 아니다.

다음 내용은 Foundation Documentation에서 설명한다.

```text
Coordinate Space

Object Space

World Space

View Space

Tangent Space

Transformation
```

각 Engine의 좌표계 차이는 해당 Platform Implementation에서 다룬다.

따라서 별도의 Coordinate Standard를 유지하지 않는다.

---

# Texture Standard

Texture와 Texture Data는 Foundation에서 Rendering Data의 일부로 설명한다.

다음 요소는 실제 Production 조건에 따라 달라질 수 있다.

```text
Resolution

Compression

Channel Packing

Color Space

Import Setting
```

따라서 하나의 범용 ASF Texture Standard로 강제하지 않는다.

반복적으로 사용하는 Production Rule이 확정될 경우 별도 Standard 생성 여부를 다시 검토할 수 있다.

---

# Material Standard

Material Structure는 Engine과 Rendering Goal에 따라 달라질 수 있다.

공통 Architecture는 `ASF-002 Rendering Architecture`에서 정의하고, 실제 Material 구현은 Implementation Documentation에서 관리한다.

따라서 독립적인 범용 Material Standard는 유지하지 않는다.

---

# Validation Standard

Validation은 독립된 마지막 단계가 아니다.

ASF에서는 다음 전체 과정에 포함된다.

```text
Implementation
↓
Observation
↓
Validation
↓
Debugging
↓
Optimization
```

Validation Philosophy는 `ASF-000 Project Principles`에서 정의하고, 실제 Validation Method는 Foundation, Advanced, Experiment 또는 Case Study에서 관리한다.

따라서 별도의 Validation Standard는 유지하지 않는다.

---

# Standard vs Documentation

Standard와 Documentation의 역할을 구분한다.

```text
Standard
→ 무엇을 기준으로 사용할 것인가

Documentation
→ Concept가 왜, 어떻게 동작하는가

Implementation
→ 실제 Engine에서 어떻게 구현하는가
```

예를 들어 Normal에 대해 다음처럼 역할을 나눈다.

```text
ASF Standard
→ 필요한 경우 Naming / Architecture Rule 정의

Foundation
→ Normal의 의미와 Rendering 역할 설명

Unreal Implementation
→ Unreal Material에서 실제 사용 방법 구현
```

Standard 문서가 Foundation 내용을 다시 상세하게 설명하지 않는다.

---

# Standard vs Decision Log

Standard와 Decision Log는 서로 다른 목적을 가진다.

Decision Log는 다음을 기록한다.

```text
왜 이 기준을 선택했는가?
```

Standard는 다음을 정의한다.

```text
현재 어떤 기준을 사용하는가?
```

예를 들어 다음 Decision이 있다고 가정한다.

```text
Decision

ASF는 Node 중심이 아니라 Data Flow 중심으로 설명한다.

Reason

Node는 Platform마다 다르지만
Rendering Data Flow는 Concept 수준에서 재사용할 수 있기 때문이다.
```

이 Decision이 승인되면 관련 Principle은 `ASF-000`, `ASF-002`, `ASF-003` 등에 반영할 수 있다.

현재 Standard를 이해하기 위해 Decision Log 전체를 먼저 읽어야 하는 구조는 만들지 않는다.

---

# Source of Truth

ASF에서는 하나의 주제에 가능한 한 하나의 Source of Truth를 유지한다.

현재 Source of Truth는 다음과 같다.

```text
Project Philosophy
→ ASF-000 Project Principles

Naming
→ ASF-001 Naming Philosophy

Rendering Architecture
→ ASF-002 Rendering Architecture

Documentation Rules
→ ASF-003 Documentation Standard
```

Foundation이나 Implementation에서 관련 내용을 설명할 수는 있지만 새로운 Project Rule을 독립적으로 정의하지 않는다.

공통 Rule이 변경되면 먼저 해당 Standard를 수정한 뒤 관련 Documentation을 업데이트한다.

---

# Cross Reference Principle

이미 다른 Standard 또는 Documentation에서 정의된 내용을 다시 길게 설명하지 않는다.

필요한 경우 Source를 명확하게 연결한다.

```text
Project Principle
→ ASF-000

Naming
→ ASF-001

Rendering Architecture
→ ASF-002

Documentation Rule
→ ASF-003
```

Cross Reference는 중복을 줄이고 Source of Truth가 여러 곳에서 서로 다르게 변하는 문제를 방지한다.

---

# Standard Lifecycle

ASF Standard는 다음 Lifecycle을 따른다.

```text
Draft
↓
Review
↓
Active
↓
Revision
```

필요한 경우 다음 상태를 사용할 수 있다.

```text
Deprecated
```

Deprecated Standard는 더 이상 현재 Project Rule로 사용하지 않음을 의미한다.

과거 프로젝트 History와 Decision 기록을 위해 파일 자체는 보존할 수 있다.

---

# Creating a New Standard

새로운 Standard는 다음 조건 중 하나 이상을 만족할 때만 생성한다.

### Repeated Rule

여러 Documentation이나 Implementation에서 동일한 Rule을 반복해서 정의하고 있다.

### Cross-document Consistency

여러 Chapter와 Module에서 동일한 기준을 유지해야 한다.

### Architecture Impact

Rule이 개별 Asset이 아니라 Framework 전체 Architecture에 영향을 준다.

### Long-term Maintenance

하나의 Source of Truth에서 관리하는 것이 유지보수에 명확한 이점이 있다.

---

# Do Not Create Standards for Everything

다음 이유만으로 새로운 Standard를 생성하지 않는다.

```text
정리해두면 좋을 것 같아서

번호가 비어 있어서

문서 체계를 완성해 보이게 하기 위해서

한 번 사용한 Rule이 있어서
```

Standard 수가 증가할수록 유지해야 하는 Source of Truth도 증가한다.

따라서 새로운 Standard를 만들기 전에 기존 Documentation 또는 Standard 안에서 관리하는 것이 더 적절한지 먼저 판단한다.

---

# Standard Review

Standard는 다음과 같은 시점에 다시 검토한다.

```text
Major Documentation Completion

Architecture Change

Foundation Refactoring

New Platform Implementation

Production Test

Advanced Case Study Completion
```

특히 실제 Implementation이나 Experiment 결과가 Standard의 가정과 다를 경우 반드시 다시 검토한다.

---

# Relationship with Documentation

ASF Standard는 다음 Documentation 구조의 상위 기준으로 사용한다.

```text
ASF Standards
      ↓
Foundation
      ↓
Advanced
      ↓
Implementation / Experiment
      ↓
Character Application
      ↓
Portfolio Case Study
```

각 Layer의 역할은 다르다.

---

# Foundation

Foundation은 Rendering Concept를 이해하기 위한 Knowledge Layer이다.

주요 범위는 다음과 같다.

```text
Rendering Pipeline

Coordinate System

Texture / Material

Lighting

Shadow

Character Rendering Fundamentals

Debug

Profiling

Optimization
```

Foundation은 Standard를 상세하게 다시 설명하지 않는다.

필요한 경우 해당 Standard를 기준으로 작성한다.

---

# Advanced

Advanced는 Foundation에서 이해한 Concept를 실제 문제 해결에 적용한다.

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

실제 Character Asset, Shader, Profiling, Before / After 분석 등을 포함한다.

---

# Implementation

Implementation Documentation은 특정 Platform에서 Concept를 구현하는 방법을 다룬다.

현재 주요 Platform은 Unreal Engine이다.

예:

```text
Material

Material Function

Material Instance

Custom HLSL

Debug View

Profiling Tool
```

Implementation Detail은 Platform 변화에 따라 수정될 수 있다.

---

# Standard Refactoring Principle

Standard 역시 Refactoring 대상이다.

다음 기준으로 검토한다.

```text
Is it still necessary?

Is the responsibility clear?

Is it duplicated elsewhere?

Does it reflect the current project?

Does another document already serve as the Source of Truth?
```

필요하다면 다음 중 하나를 선택한다.

```text
Keep

Rewrite

Merge

Rename

Renumber

Deprecate

Remove
```

오래된 번호나 구조를 유지하는 것보다 현재 Project Architecture를 명확하게 표현하는 것을 우선한다.

---

# Current Standard Summary

현재 ASF Project Standard는 다음 네 문서로 구성한다.

```text
ASF-000 Project Principles

ASF-001 Naming Philosophy

ASF-002 Rendering Architecture

ASF-003 Documentation Standard
```

역할은 다음과 같다.

```text
ASF-000
→ 프로젝트가 무엇을 목표로 하는가

ASF-001
→ 이름을 어떤 원칙으로 정하는가

ASF-002
→ Rendering System을 어떻게 구조화하는가

ASF-003
→ Knowledge를 어떻게 설명하고 기록하는가
```

이 네 문서를 ASF Standard의 현재 Source of Truth로 사용한다.

---

# Final Principle

ASF Standard의 목적은 Project를 복잡하게 만드는 것이 아니다.

좋은 Standard는 다음 역할을 해야 한다.

```text
Decision을 명확하게 만든다.

중복을 줄인다.

Documentation의 일관성을 유지한다.

Implementation의 방향을 잡아준다.

Project가 변화할 때 Refactoring 기준을 제공한다.
```

Standard 자체를 유지하기 위해 불필요한 Documentation과 관리 Cost가 증가한다면 해당 Standard의 필요성을 다시 검토한다.

> **ASF Standard는 많은 규칙을 만들기 위한 시스템이 아니라, 현재 프로젝트에 필요한 최소한의 기준을 명확한 Source of Truth로 유지하기 위한 시스템이다.**ssss