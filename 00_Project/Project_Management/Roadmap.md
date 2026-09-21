# ASF Roadmap

> Version : v0.2  
> Status : Active  
> Scope : Anime Shader Framework Project

---

# Purpose

본 문서는 Anime Shader Framework, 이하 ASF 프로젝트의 현재 진행 상태와 향후 개발 방향을 정의한다.

ASF Roadmap의 목적은 세부 Daily Task를 관리하는 것이 아니다.

프로젝트가

```text
현재 어디까지 진행되었는가?

다음에 무엇을 검증해야 하는가?

Foundation 이후 어떤 단계로 확장되는가?
```

를 명확하게 관리하는 것이 목적이다.

세부 일정과 Task 관리는 `Project_Management` 문서에서 별도로 관리한다.

---

# Project Direction

ASF는 단순히 Anime Shader 하나를 제작하는 프로젝트가 아니다.

전체 방향은 다음과 같다.

```text
Modern Real-Time Rendering Foundation
            ↓
Production PBR Character Rendering
            ↓
Stylized / Anime Rendering
            ↓
Character Application
            ↓
Debug / Profiling / Optimization
            ↓
Advanced Experiments
            ↓
Portfolio Case Studies
```

Foundation에서 Rendering Concept를 학습하고,

Implementation 단계에서 이를 Unreal Engine과 실제 Character Asset에 적용하며,

Advanced 단계에서는 Profiling, Optimization, Controlled Experiment를 통해 실제 Technical Art 문제 해결 과정으로 확장한다.

---

# Project Phases

ASF 프로젝트는 크게 다음 단계로 진행한다.

```text
Phase 00
Project Standards

Phase 01
Foundation

Phase 02
Foundation Audit / Refactoring

Phase 03
Production PBR Character Rendering

Phase 04
Anime Shader Framework

Phase 05
Character Rendering Expansion

Phase 06
Debug / Profiling / Optimization

Phase 07
Advanced Experiments

Phase 08
Portfolio Case Studies
```

각 Phase는 이전 단계에서 구축한 Concept와 Implementation을 기반으로 확장한다.

---

# Phase 00 - Project Standards

## Goal

ASF 프로젝트 전체에서 사용하는 철학과 공통 기준을 정의한다.

---

## Current Standards

현재 ASF Standard는 다음 네 문서로 구성한다.

```text
ASF-000 Project Principles

ASF-001 Naming Philosophy

ASF-002 Rendering Architecture

ASF-003 Documentation Standard
```

각 Standard의 역할은 다음과 같다.

```text
ASF-000
→ Project Direction / Philosophy

ASF-001
→ Naming

ASF-002
→ Rendering Architecture

ASF-003
→ Documentation
```

---

## Status

```text
Project Principles        Complete
Naming Philosophy         Complete
Rendering Architecture    Complete
Documentation Standard    Complete
Standard Structure        Refactored
Decision Log              Updated
```

Project Standard는 이후 Foundation Audit과 Advanced Development의 기준으로 사용한다.

---

# Phase 01 - Foundation

## Goal

Modern Real-Time Rendering을 이해하기 위한 기본 Concept와 사고 구조를 구축한다.

Foundation은 특정 Tool의 사용법이나 Shader Technique 목록을 학습하는 단계가 아니다.

다음 질문에 답할 수 있는 기반을 만드는 것이 목적이다.

```text
Rendering Data는 어디에서 오는가?

어떤 과정을 거쳐 Pixel이 만들어지는가?

Lighting은 어떤 Data를 사용하는가?

Material은 Rendering에 어떤 영향을 주는가?

Performance Cost는 어디에서 발생하는가?

문제를 어떻게 관찰하고 분석하는가?
```

---

# Foundation Chapters

Foundation은 현재 Chapter 01~09로 구성한다.

```text
Chapter 01
Rendering Foundations

Chapter 02
Coordinate Systems and Transformations

Chapter 03
Geometry and Surface Data

Chapter 04
Texture and Material Data

Chapter 05
Lighting Fundamentals

Chapter 06
PBR Fundamentals

Chapter 07
Stylized Rendering Fundamentals

Chapter 08
Building an Anime Shader

Chapter 09
Rendering Debug and Optimization
```

각 Chapter는 개별 지식으로 끝나는 것이 아니라 하나의 Rendering System으로 연결된다.

---

# Foundation Status

현재 Foundation Chapter 01~09의 Draft 작성은 완료되었다.

```text
Chapter 01    Draft Complete
Chapter 02    Draft Complete
Chapter 03    Draft Complete
Chapter 04    Draft Complete
Chapter 05    Draft Complete
Chapter 06    Draft Complete
Chapter 07    Draft Complete
Chapter 08    Draft Complete
Chapter 09    Draft Complete
```

다만 Draft Complete는 Released 상태를 의미하지 않는다.

전체 구조와 내용에 대한 Audit과 Refactoring이 필요하다.

---

# Phase 02 - Foundation Audit and Refactoring

## Goal

Chapter 01~09를 개별 문서가 아니라 하나의 Foundation System으로 다시 검토한다.

이 단계에서는 문서의 양을 단순히 줄이는 것이 목적이 아니다.

다음을 확인한다.

```text
Technical Accuracy

Concept Clarity

Chapter Flow

Duplication

Missing Explanation

Terminology Consistency

Cross Reference

Heading Structure

Figure Accuracy

Foundation / Advanced Boundary
```

---

# Audit Stage

Foundation Refactoring은 두 단계로 진행한다.

---

## Stage 1 - Audit

먼저 문서를 수정하지 않고 전체 문제를 확인한다.

각 Section은 필요에 따라 다음과 같이 분류한다.

```text
Keep

Rewrite

Shorten

Expand

Merge

Move

Remove
```

특히 다음을 중점적으로 확인한다.

```text
같은 Concept가 여러 Chapter에서 반복되는가?

이전 Chapter와 모순되는 설명이 있는가?

중요한 Data Flow가 생략되어 있는가?

불필요하게 깊은 내용이 Foundation에 들어가 있는가?

Advanced에서 다루는 것이 더 적절한 내용이 있는가?
```

---

## Stage 2 - Refactoring

Audit 결과가 확정되면 실제 Markdown Document를 수정한다.

주요 작업은 다음과 같다.

```text
중복 축약

설명 보강

Chapter 간 연결 정리

Terminology 통일

Heading 구조 통일

Cross Reference 추가

Figure Path / Naming 검증

오래된 표현 수정

Foundation Scope 정리
```

---

# Foundation Release Criteria

Foundation은 다음 조건을 만족한 이후 Released 상태로 전환한다.

```text
Chapter 01~09 구조 검증

Technical Accuracy 검토

Major Duplication 제거

Terminology 통일

Figure 검증

Cross Reference 검토

Foundation / Advanced Boundary 확정

전체 문서 Final Review
```

Foundation Released 이후에도 필요하면 Revision을 진행할 수 있다.

---

# Phase 03 - Production PBR Character Rendering

## Goal

Foundation에서 학습한 Rendering Concept를 실제 Character Rendering에 적용한다.

Anime Shader를 바로 구현하기 전에 Production PBR Character Material을 구성하여 Modern Character Rendering의 기본 구조를 직접 검증한다.

---

# Main Scope

```text
Master Material Architecture

Material Function

Material Instance

Texture / Mask

Skin

Hair

Eye

Outfit

Parameter Structure

Debug View
```

Character Asset 하나를 중심으로 전체 Material System을 구축한다.

---

# PBR Character Material

PBR Character Rendering에서는 다음 요소를 실제 Asset에 적용한다.

```text
Base Color

Normal

Roughness

Metallic

Specular

AO

Subsurface-related Response

Hair Response

Eye Material

Mask Control
```

목표는 단순히 보기 좋은 Character를 만드는 것이 아니다.

Foundation에서 학습한 Rendering Data가 실제 Material에서 어떻게 사용되는지 확인한다.

---

# Phase 04 - Anime Shader Framework

## Goal

PBR Rendering에서 이해한 Lighting과 Material Data를 Stylized Rendering으로 재해석한다.

Anime Shader는 ASF의 대표적인 Application Case이다.

---

# Core Modules

현재 ASF Anime Shader의 주요 Module은 다음과 같다.

```text
MF_BaseLighting

MF_Shadow

MF_Specular

MF_RimLight

MF_MatCap

MF_Emission

MF_DebugView
```

필요에 따라 Character-specific Extension을 추가한다.

---

# Character-specific Extensions

```text
Face SDF

Hair Shadow

Hair Highlight

Eye Highlight

Skin-specific Stylization
```

이 기능들은 Rendering Pipeline Stage가 아니라 ASF 내부 Rendering Module 또는 Character Feature로 관리한다.

---

# Framework Goals

Anime Shader Framework에서는 다음을 검증한다.

```text
Reusable Architecture

Clear Data Flow

Material Instance Control

Mask System

Texture Packing

Debuggability

Character Variation

Maintainability
```

---

# Phase 05 - Character Rendering Expansion

## Goal

Framework를 실제 Character Part에 적용하고 Production Character Material 구조를 완성한다.

---

# Target Areas

```text
Skin

Hair

Eye

Face

Outfit

Accessory
```

각 영역의 Rendering Requirement를 분석한다.

---

# Character Integration

Character 전체에서 다음 요소를 함께 검증한다.

```text
Consistent Lighting

Material Balance

Shadow

Highlight

Transparency

Silhouette

Deformation

LOD
```

개별 Material Feature보다 전체 Character의 일관성을 우선한다.

---

# Phase 06 - Debug, Profiling and Optimization

## Goal

Character Rendering을 실제 Performance 관점에서 분석한다.

Foundation Chapter 09에서 학습한 Concept를 실제 Scene에서 검증한다.

---

# Profiling Areas

```text
CPU vs GPU Bottleneck

Geometry Cost

Pixel Cost

Overdraw

Material / Shader Cost

Draw Call

LOD

Culling
```

---

# Tools

Unreal Engine에서 다음 Tool을 사용한다.

```text
stat unit

Unreal Insights

ProfileGPU

Shader Complexity

Quad Overdraw

LOD Visualization

Buffer Visualization
```

Tool 자체를 학습하는 것이 목적이 아니라 실제 문제에 맞는 Tool을 선택하는 능력을 기른다.

---

# Optimization Workflow

Optimization은 다음 Workflow를 따른다.

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

Performance와 Visual Quality를 함께 확인한다.

---

# Phase 07 - Advanced Experiments

## Goal

Foundation에서 학습한 Rendering Cost와 Architecture Concept를 Controlled Experiment로 직접 검증한다.

---

# Experiment Philosophy

Advanced에서는 의도적으로 특정 Bottleneck을 발생시킨다.

한 번에 하나의 주요 Variable만 변경한다.

```text
Baseline
↓
Single Variable Change
↓
Profiling
↓
Result
↓
Interpretation
```

---

# Planned Experiments

대표적으로 다음 Experiment를 진행한다.

```text
CPU Bottleneck Test

Geometry Bottleneck Test

Small Triangle / Quad Overdraw Test

Transparency Overdraw Test

Shader Cost Test

Draw Call Test

LOD Test

Character Count Scaling Test
```

실제 필요에 따라 Experiment를 추가하거나 통합한다.

---

# Phase 08 - Portfolio Case Studies

## Goal

ASF에서 학습하고 구현한 내용을 Technical Artist Portfolio로 정리한다.

최종 Result만 보여주는 것이 아니라 문제 해결 과정을 보여준다.

---

# Case Study Structure

Portfolio Case Study는 다음 구조를 기본으로 한다.

```text
Problem
↓
Requirement
↓
Hypothesis
↓
Profiling / Analysis
↓
Technical Decision
↓
Implementation
↓
Validation
↓
Optimization
↓
Before / After
↓
Final Result
```

---

# Main Portfolio Targets

현재 예상하는 주요 Portfolio Case Study는 다음과 같다.

```text
Production PBR Character Material

Anime Shader Framework

Character Rendering Integration

Rendering Debug System

Performance Profiling and Optimization
```

필요하면 여러 항목을 하나의 Character Rendering Project로 통합할 수 있다.

---

# Portfolio Evidence

다음 자료를 작업 과정에서 지속적으로 확보한다.

```text
Final Render

Material Graph

Architecture Diagram

Debug View

Profiling Result

Before / After

Performance Metrics

Technical Decision

Failure / Fix Example
```

필요한 Screenshot은 해당 작업 단계에서 바로 Capture한다.

---

# Current Project Status

현재 ASF의 위치는 다음과 같다.

```text
Project Standards
        ↓
      Complete

Foundation 01~09
        ↓
    Draft Complete

Current
        ↓
Foundation Audit
        ↓
Foundation Refactoring
        ↓
Foundation Release
```

즉, 현재 가장 중요한 작업은 새로운 Feature 추가가 아니다.

**Foundation 전체를 하나의 문서 시스템으로 검토하고 정리하는 것**이다.

---

# Immediate Next Steps

현재 단계에서 다음 순서로 진행한다.

```text
1. Project Standard Final Check

2. Foundation Chapter 01~09 Audit

3. Audit Report Review

4. Foundation Refactoring

5. Figure / Cross Reference Validation

6. Foundation Final Review

7. Foundation Release
```

Foundation Release 이후 실제 Character Implementation 단계로 이동한다.

---

# Post-Foundation Development

Foundation 이후의 큰 흐름은 다음과 같다.

```text
Foundation Release
        ↓
PBR Character Material
        ↓
Anime Shader Framework
        ↓
Character Application
        ↓
Debug / Profiling
        ↓
Optimization
        ↓
Advanced Experiments
        ↓
Portfolio Case Studies
```

각 단계는 완전히 독립되어 있지 않다.

Implementation 과정에서 발견한 문제는 다시 Documentation과 Standard를 개선하는 데 사용할 수 있다.

---

# Iterative Development

ASF는 직선적인 Waterfall Project가 아니다.

다음 Cycle을 반복한다.

```text
Learn
↓
Implement
↓
Observe
↓
Validate
↓
Refactor
↓
Document
↓
Learn Again
```

필요하면 이전 Phase로 돌아가 Concept나 Architecture를 수정한다.

---

# Priority Principle

ASF에서 작업 우선순위는 다음 기준으로 판단한다.

```text
Foundation Accuracy

Architecture Consistency

Character Application Value

Debuggability

Performance Validation

Portfolio Value
```

기능 수를 늘리는 것보다 전체 System을 이해하고 검증할 수 있는 상태를 우선한다.

---

# Scope Control

ASF가 커지면서 새로운 Topic이 계속 추가될 수 있다.

하지만 모든 Rendering Technique를 다루는 것이 목표는 아니다.

새로운 Topic은 다음 질문을 기준으로 추가한다.

```text
Character Rendering에 중요한가?

Rendering Foundation 이해에 필요한가?

Technical Artist Workflow에 도움이 되는가?

실제로 구현하거나 검증할 수 있는가?

Portfolio에서 의미 있는 결과로 연결되는가?
```

이 기준에 맞지 않는 Topic은 필요 이상으로 확장하지 않는다.

---

# Final Direction

ASF의 최종 목표는 많은 Shader Technique를 모아놓는 것이 아니다.

프로젝트를 통해 다음 능력을 구축하는 것이 목적이다.

```text
Understand Rendering

Design Data Flow

Build Rendering Systems

Debug Problems

Profile Performance

Optimize Bottlenecks

Apply to Characters

Explain Technical Decisions
```

> **ASF Roadmap의 최종 목적은 Anime Shader 하나를 완성하는 것이 아니라, Modern Real-Time Character Rendering을 이해하고 구현하고 검증할 수 있는 Technical Artist Workflow를 구축하는 것이다.**