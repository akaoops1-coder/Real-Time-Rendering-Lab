# ASF-003 Documentation Standard

> Version : v0.3  
> Status : Draft  
> Scope : Anime Shader Framework Project
> Revision : 2026-10-02

---

# Purpose

본 문서는 Anime Shader Framework, 이하 ASF에서 작성되는 Documentation의 기본 원칙과 구조를 정의한다.

ASF Documentation의 목적은 단순히 정보를 기록하는 것이 아니다.

Rendering Concept를

```text id="uxru3f"
이해하고

구조화하고

연결하고

검증하고

다시 사용할 수 있는 형태로 정리하는 것
```

이 목적이다.

Documentation은 ASF의 학습 결과물이면서 동시에 Knowledge Validation 과정의 일부이다.

---

# Documentation Philosophy

ASF는 문서를 많이 만드는 것을 목표로 하지 않는다.

중요한 것은 독자가 Rendering Concept를 단계적으로 이해하고, 이후 실제 Implementation과 Problem Solving에 사용할 수 있도록 만드는 것이다.

따라서 ASF Documentation은 다음 흐름을 기본으로 한다.

```text id="x1w7a9"
Why
↓
Concept
↓
Relationship
↓
Data Flow
↓
Application
↓
Validation
```

구현 방법을 나열하기 전에 먼저 개념과 이유를 설명한다.

---

# Principle 01. Explain Why First

새로운 개념이나 기능을 설명할 때는 먼저 왜 필요한지를 설명한다.

다음과 같은 구조를 권장한다.

```text id="5gqc37"
Problem
↓
Why It Matters
↓
Concept
↓
How It Works
```

단순히

```text id="f1d0dm"
이 Node를 연결한다.
```

라고 설명하기보다,

```text id="e3s5y0"
왜 이 Data가 필요한가?

어떤 문제를 해결하는가?

Rendering Pipeline에서 어떤 역할을 하는가?
```

를 먼저 이해할 수 있도록 작성한다.

---

# Principle 02. Concept Before Platform

Platform 사용법보다 Rendering Concept를 먼저 설명한다.

예를 들어 Unreal Engine의 특정 Material Node를 소개하기 전에 해당 Node가 어떤 Rendering Concept를 구현하는지 설명한다.

```text id="mt07n1"
Rendering Concept
↓
Data Flow
↓
Platform Implementation
```

Tool이 바뀌어도 Concept를 다시 사용할 수 있어야 한다.

---

# Principle 03. Flow Before Node

ASF Documentation은 Node Graph 자체보다 Data Flow를 우선한다.

예를 들어 다음과 같이 설명한다.

```text id="0uqdaz"
Normal
+
Light Direction
↓
Dot Product
↓
NdotL
↓
Lighting Response
```

그 뒤 실제 Unreal Material Graph를 설명한다.

Node 연결 순서를 외우는 것이 아니라 각 Data가 어떤 의미를 가지는지 이해하도록 한다.

---

# Principle 04. Build Understanding Through Connections

새로운 Concept는 가능하면 이전에 학습한 Concept와 연결한다.

예를 들어 Shadow를 설명할 때 단순히 새로운 기능으로 소개하지 않는다.

다음과 같이 기존 Rendering Pipeline과 연결한다.

```text id="hv55l8"
Light
↓
Visibility
↓
Shadow Information
↓
Lighting Result
```

독자가 다음과 같이 이해할 수 있도록 한다.

> 이전에 배운 Concept가 여기에서 어떻게 사용되는가?

ASF Documentation은 개별 지식을 서로 연결하여 하나의 Rendering System으로 이해하도록 만드는 것을 목표로 한다.

---

# Principle 05. Distinguish Similar Concepts Clearly

서로 혼동하기 쉬운 Concept는 지나치게 압축하지 않는다.

예를 들어:

```text id="b0dy68"
Shadow Map

Visibility

Shadow Mask
```

처럼 서로 연관되어 있지만 역할이 다른 개념은 각각의 역할과 Data Flow를 분리하여 설명한다.

다음 질문에 답할 수 있어야 한다.

```text id="axr4hp"
무엇인가?

어디에서 생성되는가?

어떤 값을 가지는가?

어디에서 사용되는가?

다른 Concept와 어떤 관계인가?
```

문장이 조금 길어지더라도 이해에 필요한 구분을 생략하지 않는다.

---

# Principle 06. One Section, One Primary Topic

하나의 Section은 가능한 한 하나의 중심 주제를 가진다.

관련 Concept를 설명할 수는 있지만 Section의 핵심 목적이 모호해질 정도로 범위를 넓히지 않는다.

예를 들어:

```text id="h74msw"
Geometry Cost
```

Section에서는 Triangle, Vertex, Skinning, Triangle Size 등을 설명할 수 있다.

하지만 Draw Call 전체 설명까지 같은 Section에 포함하지 않는다.

필요하면 별도의 Section으로 분리하고 서로 연결한다.

---

# Principle 07. Avoid Unnecessary Duplication

이미 충분히 설명한 Concept를 이후 Chapter에서 처음부터 다시 설명하지 않는다.

필요한 경우 핵심만 짧게 복습하고 기존 Section과 연결한다.

```text id="b51n3n"
Previous Concept
↓
Short Reminder
↓
New Application
```

그러나 학습상 필요한 반복까지 무조건 제거하지 않는다.

특히 새로운 Context에서 기존 Concept의 역할이 달라지거나 이해를 위해 관계 설명이 필요한 경우에는 다시 설명할 수 있다.

중복 제거의 목적은 문서를 짧게 만드는 것이 아니라 **불필요한 반복을 줄이는 것**이다.

---

# Principle 08. Do Not Over-compress Concepts

ASF Foundation은 단순 요약집이 아니다.

중요한 Rendering Concept를 지나치게 압축하여 결과만 전달하지 않는다.

다음 내용이 필요한 경우 충분히 설명한다.

```text id="hvwe9j"
Cause

Process

Relationship

Data Transformation

Visual Result

Performance Meaning
```

독자가 설명을 읽고 원리를 따라갈 수 있어야 한다.

---

# Principle 09. Separate Fact, Simplification, and Practical Model

Rendering Documentation에서는 실제 Engine이나 GPU 내부 구조가 매우 복잡할 수 있다.

Foundation에서는 이해를 위해 단순화된 Model을 사용할 수 있다.

이 경우 단순화된 설명을 실제 내부 구현 전체와 동일한 것으로 표현하지 않는다.

예를 들어:

```text id="tq4w5m"
개념적으로

단순화하면

Foundation 수준에서는
```

등의 표현을 사용해 설명 범위를 명확하게 한다.

필요 이상으로 내부 구현을 확대해서 설명하지 않는다.

---

# Principle 10. Foundation and Advanced Serve Different Roles

ASF Documentation은 Foundation과 Advanced의 역할을 구분한다.

---

## Foundation

Foundation은 Rendering을 이해하기 위한 기본 사고 구조를 만든다.

주요 내용은 다음과 같다.

```text id="vgn9zw"
Why

Concept

Principle

Relationship

Data Flow

Basic Engine Verification
```

Foundation에서는 개념을 충분히 이해하는 것이 우선이다.

모든 Concept를 Production 수준의 복잡한 Experiment까지 확장하지 않는다.

---

## Advanced

Advanced는 Foundation의 Concept를 실제 Rendering Problem에 적용한다.

다음 흐름을 기본으로 한다.

```text id="bk4np8"
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

Advanced에서는 실제 Unreal Engine Scene과 Character Asset을 이용한 Experiment를 적극적으로 사용한다.

---

# Principle 11. Foundation Is Not a Tutorial Collection

Foundation은 특정 Tool 사용법이나 Node 연결 방법만을 설명하는 Tutorial Collection이 아니다.

다음 질문에 답할 수 있도록 작성한다.

```text id="je74r2"
왜 필요한가?

어떤 원리인가?

어떤 Data를 사용하는가?

Rendering Pipeline과 어떻게 연결되는가?
```

Platform-specific Implementation은 Concept를 확인하기 위한 보조 수단으로 사용한다.

---

# Principle 12. Advanced Is Result-driven

Advanced Documentation은 Foundation과 동일한 방식으로 모든 이론을 다시 길게 설명하지 않는다.

이미 Foundation에서 설명한 Concept를 기반으로 실제 문제 해결 과정에 집중한다.

권장 구조는 다음과 같다.

```text id="41vx00"
Concept

Problem

Implementation

Verification

Debugging

Optimization

Result
```

필요한 경우 다음까지 포함한다.

```text id="cvazrb"
Before / After

Performance Metrics

Visual Comparison

Technical Decision
```

---

# Principle 13. Documentation Must Be Verifiable

가능한 경우 설명한 Concept를 실제 Engine이나 Debug View에서 확인할 수 있어야 한다.

예를 들어:

```text id="0l5mrh"
Normal
→ Buffer Visualization

LOD
→ LOD Visualization

Shader Cost
→ Shader Complexity

GPU Cost
→ ProfileGPU
```

Documentation은 단순한 설명에서 끝나는 것이 아니라 실제 Rendering Result와 연결되어야 한다.

---

# Principle 14. Screenshots Are Part of Documentation

실제 Implementation이나 Verification 과정에서 Portfolio 또는 Documentation에 도움이 되는 화면은 작업 과정에서 미리 Capture한다.

필요한 Capture Point를 작업이 끝난 뒤 기억에 의존해 다시 만들지 않는다.

예를 들어 다음 단계에서 Capture를 고려할 수 있다.

```text id="eyz40i"
Before

Implementation

Debug View

Problem State

Fixed State

Before / After

Final Result
```

특히 Debugging과 Optimization 과정에서는 중간 상태가 중요한 Documentation 자료가 될 수 있다.

---

# Principle 15. Explain What the Reader Is Looking At

Screenshot이나 Figure를 삽입하는 것만으로 설명을 끝내지 않는다.

독자가 이미지에서 무엇을 확인해야 하는지 본문에서 설명한다.

예를 들어:

```text id="igzb0u"
Figure에서 붉은 영역이 많다는 사실만 보는 것이 아니라,
왜 해당 영역의 Shader Cost가 증가했는지 확인한다.
```

Figure는 설명을 대체하는 것이 아니라 설명을 보조한다.

---

# Language Standard

ASF Documentation은 기술적 정확성과 읽기 편의성을 위해 다음 언어 규칙을 사용한다.

---

## Technical Terms

Rendering, Engine, Shader 관련 전문 용어는 기본적으로 English를 유지한다.

예:

```text id="bhxp79"
Rendering Pipeline

Rasterization

Normal

Texture Sample

Material Function

Shadow Map

Draw Call

Profiling
```

억지로 번역하여 의미가 불명확해지는 표현을 만들지 않는다.

---

## Section Titles

Chapter와 Section Title은 English를 기본으로 한다.

예:

```text id="s3wvd2"
## 9.3 Geometry Cost

### Triangle Count

### Small Triangle Problem
```

---

## Explanatory Text

설명 문장은 Korean을 기본으로 하고, 문체는 `…다`로 통일한다. 원문 인용, 실제 UI 문구와 Code는 원래 표현을 유지한다.

예:

```text id="cl6qnx"
Triangle Count는 Geometry Complexity를 판단할 때 가장 기본적으로 확인하는 지표이다.
```

---

## Avoid Unnecessary Hanja

설명 문장에서는 불필요한 Hanja 표현을 사용하지 않는다.

가능한 한 자연스러운 Korean과 필요한 English Technical Term을 사용한다.

---

# Heading Standard

ASF Chapter Documentation은 Heading Level을 단순하게 유지한다.

---

## Chapter

Chapter Title에는 `#`을 사용한다.

Foundation의 Chapter Title은 두 자리 Chapter Number와 `—` 구분자를 사용한다. Chapter 08처럼 여러 파일에 걸친 장은 같은 Chapter Title을 사용하고, 각 파일의 Module 번호와 이름을 `##`로 구분한다. 기존 파일명은 유지한다.

예:

```text id="t426xg"
# Chapter 09 — Rendering Debug and Optimization
```

---

## Numbered Major Section

주요 Section에는 `##`를 사용하고 Chapter Section Number를 포함한다.

Chapter 목차와 안내만 제공하는 index 문서는 동등한 안내 항목을 번호 없는 `##`로 구분한다. 개별 Module 본문에는 기존 `## 8.x`와 그 아래의 `###` 학습 단계를 유지한다.

예:

```text id="w7y4vc"
## 9.1 Why Optimization Starts with Measurement

## 9.2 CPU vs GPU Bottleneck

## 9.3 Geometry Cost
```

---

## Internal Heading

Section 내부 Heading에는 `###`를 사용한다.

내부 Heading에는 별도의 Section Number를 붙이지 않는다.

권장:

```text id="hj4dse"
### Game Thread

### Render Thread

### GPU Bottleneck
```

사용하지 않는 형식:

```text id="lmvfd5"
### 9.2.1 Game Thread

### 9.2.2 Render Thread
```

내용상 번호가 반드시 필요한 특별한 경우를 제외하면 내부 Heading Numbering을 사용하지 않는다.

---

## Lower Heading

`####`는 추가 구조가 정말 필요한 경우에만 사용한다.

Heading Depth가 지나치게 깊어지지 않도록 한다.

기본 구조는 다음 수준을 목표로 한다.

```text id="g0ddpq"
#
##
###
```

---

# Section Flow and Closing Roles

Section의 도입, 본문, 요약, 다음 주제 연결은 서로 다른 역할을 가진다. 이 역할을 문서 전체에서 일관되게 유지하되, 모든 Section에 같은 제목이나 같은 수의 항목을 넣지 않는다.

## Opening and Concept Development

도입은 직전 내용에서 준비된 Data나 남은 질문을 현재 주제와 연결한다. 새로운 Concept가 왜 필요한지를 먼저 설명하고, 관계와 처리 흐름을 따라 정의·수식·예시·적용 조건으로 이어간다.

개념 설명, Module 구현, 측정·진단은 각각의 목적에 맞게 전개한다. Chapter 08의 프로젝트 준비에 계산 Module의 Interface 양식을 강제로 적용하거나, Profiling 설명에 PBR/Stylized 비교 양식을 반복하지 않는다.

## Explanation and Validation Before Review

새 개념, 수치 예시, 기술 조건, 실제 검증 절차는 본문에서 설명한다. Summary나 Key Takeaways로 해당 학습 단위를 닫은 뒤 새 본문 설명을 다시 시작하지 않는다.

비교표, Data Flow, 용어표는 관계를 설명하거나 빠르게 참조하는 역할이 있다. 요약과 표현 형식이 다르다는 이유로 모두 중복으로 취급하지 않는다. 같은 결론을 다시 진술하는 문단은 합치고, 서로 다른 입력·조건·판단을 보여주는 사례는 유지한다.

## Section and Module Review

핵심 관계와 판단 조건을 다시 묶을 필요가 있는 Section이나 Module에 선택적으로 `Key Takeaways`를 둔다. 모든 짧은 Section에 요약을 추가하지 않는다.

요약은 본문에서 설명한 관계와 범위를 유지한다. 현재 구현, 교육용 예제, 설계 방향, 향후 확장을 모두 구현 완료로 바꾸지 않는다. 요약을 짧게 만들기 위해 Unit Vector, Coordinate Space, View/Pass, Format, 비교 조건 등의 중요한 전제를 제거하지 않는다.

장 전체의 연결과 학습 결과를 합성하는 회고에는 `Chapter Summary`를 사용한다. 여러 Section을 묶는 `Part Summary`는 개별 절의 요약을 다시 나열하는 대신 그 관계를 합성할 때 사용한다. Function 계약, 데이터 흐름, 용어 비교가 목적이라면 해당 역할이 드러나는 제목을 사용한다.

## Connections and Navigation

`Callback`을 반복되는 독립 소제목으로 사용하지 않는다. 이전 Concept를 현재 설명에 다시 사용하는 내용은 도입이나 해당 본문에 자연스러운 연결 문단으로 둔다. 다음 주제가 필요한 이유는 해당 학습 단위의 마무리 뒤에 한 번 설명한다.

다음 Section의 도입이 이미 직전 내용을 받아주면 같은 연결을 앞뒤에 반복하지 않는다. 같은 Chapter 안에서는 앞 절과 다음 절을 구분하고, 실제 순서와 다른 주제를 예고할 경우 거쳐 가는 학습 경로를 밝힌다.

문서 내부의 참조는 실제 Heading 이름이나 Anchor에 맞춘다. 본문에 없는 세부 번호를 만들어 이동 대상으로 표시하지 않는다. 다른 파일로 이동하는 안내는 하단에 실제 상대 경로의 Markdown 링크로 제공한다. 파일명, 주요 Section 번호, Figure 경로는 형식을 정리한다는 이유로 변경하지 않는다.

현재 존재하지 않는 다음 문서에 가짜 링크를 만들지 않는다. 향후 실습·Advanced·Case Study 계획은 다음 단계의 계획으로 구분하며, 현재 Chapter의 새 기술 설명이나 완료된 실측 결과처럼 표시하지 않는다.

## Notes and Verification Scope

짧은 국소적인 구현 조건과 읽기 조건은 해당 주장 가까이에 Note로 둔다. 실제 실습 순서, 기대값, 관찰과 확인 절차는 독립적인 검증 본문으로 유지한다. 긴 Architecture 책임이나 Production 논의도 그 설명 역할에 맞는 본문에 둔다.

캡션은 Figure에서 무엇을 읽을지 안내한다. 긴 정정 이력이나 구현별 조건은 Figure 바로 뒤의 Reading 또는 Implementation Note로 구분할 수 있다. 오독을 막는 조건, 개념도의 범위, 실행 미검증 상태를 삭제하거나 검증 완료로 바꾸지 않는다.

## Heading Scope and Narrative Paragraphs

같은 파일에서 큰 학습 단계와 그 단계의 세부 설명을 Heading 수준으로 구분한다. 문서 전체의 요약을 마지막 Function 설명의 하위 항목처럼 표시하지 않는다. 소단위의 요약은 그 학습 단계 아래에 둔다.

연속된 원인과 결과는 자연스러운 문단으로 연결한다. 질문·수식·도식에 필요한 여백은 유지하되, 하나의 문장을 단어마다 별도 문단으로 나누지 않는다.

---

# Markdown Standard

ASF Documentation은 Markdown 원문을 직접 관리할 수 있는 형태로 작성한다.

---

## Do Not Wrap the Entire Document

문서 전체를 하나의 Triple Backtick Code Fence로 감싸지 않는다.

Markdown 문서에 그대로 붙여넣어 사용할 수 있어야 한다.

---

## Code and Data Flow Blocks

Data Flow, Formula, Console Command 등 블록 표현이 필요한 부분에서만 Code Fence를 사용한다.

예:

```text id="e9i9gm"
Normal
+
Light Direction
↓
NdotL
```

---

## Tables

비교나 구조를 명확하게 표현할 수 있을 때 Table을 사용한다.

예:

| Cost | Primary Concern |
|---|---|
| Geometry | Triangle / Vertex Processing |
| Pixel | Screen Coverage / Overdraw |
| Shader | Per-pixel Calculation |
| Draw Call | CPU Rendering Submission |

Table이 긴 본문 설명을 무조건 대체하지는 않는다.

---

# Figure Standard

Figure는 Concept를 빠르게 이해하거나 복잡한 Data Flow를 시각화하는 데 사용한다.

모든 Section에 Figure가 필요한 것은 아니다.

---

## When to Use a Figure

다음과 같은 경우 Figure 사용을 권장한다.

```text id="9pb48x"
Pipeline Flow

Data Relationship

Concept Comparison

Architecture

Before / After

Profiling Workflow

Complex Spatial Relationship
```

단순한 정의나 짧은 개념 설명은 Text만으로 충분할 수 있다.

---

# Figure Naming

Figure File은 Chapter 번호와 순번을 기준으로 관리한다.

기본 Naming 형태는 다음과 같다.

```text id="ar5gza"
Fig<Chapter>_<NN>.png
```

예:

```text id="0q4rxd"
Fig1_01.png

Fig3_04.png

Fig8_20.png

Fig9_09.png
```

Chapter Number 앞에 불필요한 `0`을 추가하지 않는다.

예:

```text id="gjnq26"
Fig8_01.png
```

를 사용하고,

```text id="sv7r36"
Fig08_01.png
```

는 사용하지 않는다.

---

# Figure Path

Figure Path는 해당 Documentation의 실제 Folder Structure에 따른 상대 경로를 사용한다.

Folder Structure를 임의로 변경하지 않는다.

예를 들어 Chapter가 다음 구조를 사용하는 경우:

```text id="t2pcmq"
Figures/Chapter03/Fig3_01.png
```

해당 경로를 그대로 유지한다.

다른 Chapter에서 Document 위치 때문에 다음 경로가 필요한 경우:

```text id="l82zk9"
../Figures/Chapter08/Fig8_01.png
```

실제 Folder Structure에 맞는 상대 경로를 사용한다.

즉, 모든 Chapter에 동일한 `../` 규칙을 강제로 적용하지 않는다.

---

# Figure Embedding

기본 Figure 삽입은 HTML Image Tag를 사용한다.

예:

```html
<p align="center">
<img src="Figures/Chapter09/Fig9_09.png" width="90%">
</p>
```

단, 실제 Relative Path는 해당 Chapter Folder Structure를 따른다.

기존 Chapter의 Image Path를 Refactoring 과정에서 임의로 변경하지 않는다.

---

# Figure Content Language

Figure 내부에서도 다음 원칙을 따른다.

```text id="yr2a1f"
Technical Term
→ English

Explanation
→ Korean
```

다만 Figure의 가독성을 위해 짧은 English Label을 사용할 수 있다.

Korean 설명을 사용할 경우 오탈자와 깨진 글자가 없는지 반드시 확인한다.

---

# Cross Reference

이미 설명한 Concept가 있다면 가능한 한 해당 Chapter 또는 Section과 연결한다.

예:

```text id="ub97vs"
Normal과 Coordinate Space의 기본 개념은 Chapter 03에서 설명했다.
```

Cross Reference의 목적은 독자에게 필요한 배경 위치를 알려주는 것이다.

본문을 이해하기 위해 계속 다른 문서로 이동해야 할 정도로 지나치게 의존하지 않는다.

---

# Terminology Consistency

동일한 Concept는 문서 전체에서 가능한 한 동일한 Term을 사용한다.

예를 들어 하나의 문서에서는:

```text id="eiw0ja"
Pixel Shader
```

다른 문서에서는:

```text id="mqlg8s"
Fragment Shader
```

처럼 이유 없이 Term을 변경하지 않는다.

Platform에 따라 다른 용어를 설명할 필요가 있다면 관계를 먼저 설명한다.

---

# Concept Boundary

서로 다른 Concept를 하나의 용어로 합치지 않는다.

예를 들어:

```text id="c3k1mx"
Rendering Pipeline Stage
≠
Rendering Module
```

```text id="mm68pm"
Shadow Map
≠
Shadow Mask
```

```text id="npux80"
Triangle Count
≠
Geometry Cost 전체
```

문서 전체에서 이러한 Concept Boundary를 일관되게 유지한다.

---

# Simplification Standard

Foundation에서는 이해를 위해 실제 Rendering System을 단순화할 수 있다.

하지만 중요한 관계를 왜곡해서는 안 된다.

좋은 Simplification은 핵심 원리를 유지한다.

```text id="mu41ue"
복잡한 실제 구조
↓
핵심 관계만 추출
↓
이해 가능한 Concept Model
```

잘못된 Simplification은 서로 다른 Concept를 하나로 합치거나 잘못된 Cause / Effect 관계를 만든다.

---

# Performance Documentation

Performance 관련 설명에서는 다음 두 개념을 반드시 구분한다.

```text id="6fqtuv"
Cost가 존재한다.

Cost가 현재 Bottleneck이다.
```

예를 들어 Triangle Count가 높으면 Geometry Cost가 증가할 가능성이 있지만, 그것만으로 현재 Frame의 Bottleneck이 Geometry라고 단정하지 않는다.

가능하면 Profiling 결과를 통해 확인한다.

---

# Optimization Documentation

Optimization은 다음 Workflow를 기본으로 설명한다.

```text id="gx91d6"
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

단순히

```text id="7u38nt"
Triangle을 줄인다.

Texture를 줄인다.

Shader를 단순화한다.
```

처럼 Technique 목록만 작성하지 않는다.

왜 해당 Optimization이 필요한지 설명한다.

---

# Experiment Documentation

Advanced Experiment에서는 가능한 한 하나의 주요 Variable만 변경한다.

Documentation에서도 다음 정보를 명확히 기록한다.

```text id="22rt61"
Baseline

Changed Variable

Measurement Condition

Result

Interpretation
```

이를 통해 Cause와 Result의 관계를 설명할 수 있어야 한다.

---

# Before and After

Optimization이나 Technical Change를 설명할 때 가능하면 Before / After 비교를 사용한다.

예:

```text id="4hu7q8"
Before

GPU : 18.2 ms
Triangles : 150K

After

GPU : 12.4 ms
Triangles : 70K
```

단순한 수치 비교뿐 아니라 Visual Quality 변화도 함께 확인한다.

---

# Portfolio Documentation

Portfolio용 Documentation은 결과보다 Decision Process를 보여준다.

권장 흐름은 다음과 같다.

```text id="90v4cr"
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
Result
```

최종 Image만 보여주는 것이 아니라 왜 해당 Solution을 선택했는지 설명한다.

---

# Documentation Lifecycle

ASF Documentation은 다음 Lifecycle을 따른다.

```text id="yqngzm"
Draft
↓
Review
↓
Verified
↓
Released
↓
Refactoring
```

Documentation은 Released 이후에도 필요하면 다시 Refactoring할 수 있다.

---

# Audit and Refactoring

전체 Documentation을 검토할 때는 다음 항목을 확인한다.

```text id="of27nr"
Technical Accuracy

Concept Clarity

Logical Flow

Duplication

Missing Explanation

Terminology Consistency

Heading Consistency

Figure Accuracy

Cross Reference

Foundation / Advanced Scope
```

---

# Refactoring Decisions

각 내용은 다음 중 하나로 처리할 수 있다.

```text id="kwtqu3"
Keep

Rewrite

Shorten

Expand

Merge

Move

Remove
```

문장이 길다는 이유만으로 Shorten하지 않는다.

반대로 이전에 작성한 내용이라는 이유만으로 유지하지도 않는다.

현재 ASF의 목적과 독자의 이해에 필요한지를 기준으로 판단한다.

---

# Shortening Rule

다음과 같은 경우 축약을 고려한다.

```text id="0i2jex"
같은 설명이 여러 번 반복됨

앞에서 충분히 설명한 내용을 그대로 다시 설명함

핵심 Concept와 관계없는 Side Topic이 지나치게 길어짐

같은 의미의 문장이 여러 형태로 반복됨
```

---

# Expansion Rule

다음과 같은 경우 설명을 보강한다.

```text id="8tjmym"
Cause와 Result 사이의 과정이 생략됨

새로운 Technical Term이 설명 없이 등장함

서로 다른 Concept가 혼동될 가능성이 있음

Data Flow가 명확하지 않음

Rendering Pipeline과의 관계가 빠져 있음
```

---

# Do Not Optimize Documentation for Length

ASF Documentation의 목표는 최소한의 문장 수가 아니다.

문서의 적절한 길이는 Topic의 난이도에 따라 달라진다.

따라서 다음 기준을 우선한다.

```text id="yphkqr"
Correct

Understandable

Connected

Necessary
```

그 다음에 Concise한지를 판단한다.

---

# Source of Truth

Documentation 작성 규칙의 Source of Truth는 본 문서이다.

```text id="g9jhjm"
ASF-003 Documentation Standard
```

개별 Chapter에서 새로운 Formatting Rule이나 Documentation Rule이 필요해진 경우 반복적으로 사용되는 기준인지 확인한다.

공통 Rule이라면 ASF-003을 업데이트한다.

Chapter-specific Requirement라면 해당 Chapter 내에서만 관리한다.

---

# Relationship with Other Standards

ASF Documentation Standard는 다음 구조 안에서 사용된다.

```text id="swqrou"
ASF-000 Project Principles
        ↓
ASF-001 Naming Philosophy
        ↓
ASF-002 Rendering Architecture
        ↓
ASF-003 Documentation Standard
        ↓
Foundation / Advanced Documentation
```

`ASF-000`은 프로젝트의 철학을 정의한다.

`ASF-001`은 Naming 원칙을 정의한다.

`ASF-002`는 Rendering Architecture를 정의한다.

`ASF-003`은 이러한 내용을 어떤 방식으로 설명하고 기록할지를 정의한다.

---

# Documentation Review Checklist

새로운 Chapter나 전체 Documentation을 Review할 때 다음 질문을 확인한다.

### Purpose

```text id="dkj79p"
이 Section의 목적이 명확한가?
```

### Concept

```text id="dr6lmi"
Technical Concept가 정확한가?

유사한 Concept와 구분되어 있는가?
```

### Flow

```text id="w102ed"
설명의 순서가 자연스러운가?

원인에서 결과까지 연결되는가?
```

### Context

```text id="mgdtz1"
Rendering Pipeline과 어떤 관계인지 이해할 수 있는가?
```

### Duplication

```text id="dd1sac"
앞에서 이미 충분히 설명한 내용을 불필요하게 반복하고 있지 않은가?
```

### Depth

```text id="o8q983"
Foundation 수준에서 지나치게 깊은가?

반대로 이해에 필요한 설명이 빠져 있는가?
```

### Terminology

```text id="33a6pe"
같은 Concept에 같은 Term을 사용하고 있는가?
```

### Figure

```text id="xttz8j"
Figure가 실제 설명과 일치하는가?

File Name과 Path가 올바른가?
```

### Validation

```text id="uzhg8l"
설명한 내용을 실제 결과나 Debug Tool을 통해 확인할 수 있는가?
```

---

# Final Principle

ASF Documentation은 정보를 많이 저장하기 위한 문서가 아니다.

독자가 Rendering Problem을 만났을 때

```text id="4rfmjj"
무엇이 일어나고 있는가?

왜 그런 결과가 발생하는가?

어떤 Data를 확인해야 하는가?

어디에서 문제를 찾아야 하는가?

어떻게 검증할 수 있는가?
```

를 스스로 생각할 수 있도록 만드는 것이 목표이다.

따라서 ASF Documentation은 다음 원칙을 유지한다.

```text id="0rtj0w"
Explain Why

Build Connections

Follow Data Flow

Separate Concepts Clearly

Verify Results

Refactor Continuously
```

> **좋은 ASF Documentation은 단순히 답을 알려주는 문서가 아니라, Rendering 문제를 스스로 분석할 수 있는 사고 구조를 만들어 주는 문서이다.**
