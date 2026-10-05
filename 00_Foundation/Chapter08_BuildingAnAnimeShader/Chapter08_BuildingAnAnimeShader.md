# Chapter 08 — Building an Anime Shader

> *"Theory becomes implementation."*

---

## Overview

지금까지의 장에서는 실시간 렌더링과 NPR(Non-Photorealistic Rendering)의 핵심 개념을 학습하였다.

우리는 Light가 어떻게 표면에 도달하는지, BRDF가 어떻게 빛의 반사를 모델링하는지, 그리고 NPR이 현실적인 렌더링과 어떤 차이를 가지는지 단계적으로 살펴보았다.

Chapter 8부터는 이러한 이론을 실제 프로젝트에 적용하여 **Anime Shader Framework(ASF)** 를 구현한다.

본 장은 하나의 셰이더를 만드는 방법을 설명하는 것이 아니라, **재사용 가능하고 확장 가능한 Anime Shader Framework를 설계하고 구현하는 과정**을 다룬다.

---

## Learning Objectives

이 장을 완료하면 다음 내용을 이해할 수 있다.

- Anime Shader Framework의 전체 구조
- 입력과 출력이 있는 재사용 계산 단위인 **Material Function**을 이용한 셰이더 아키텍처
- 셀 셰이딩을 구성하는 주요 렌더링 모듈
- 모듈 간의 데이터 흐름(Data Flow)
- 유지보수와 확장을 고려한 셰이더 설계 방법

또한 본 장에서 구축한 Framework는 이후 Character Rendering과 Optimization 장에서 그대로 재사용된다.

---

## Why a Framework?

애니메이션 셰이더를 구현하는 가장 단순한 방법은 하나의 Material 안에서 모든 기능을 작성하는 것이다.

그러나 이러한 방식은 기능이 추가될수록 Material Graph가 복잡해지고, 재사용성과 유지보수성이 급격히 저하된다.

ASF는 이러한 문제를 해결하기 위해 **Material Function 기반의 모듈형 아키텍처**를 사용한다.

예를 들어 Rim의 폭만 바꾸고 싶은데 하나의 큰 Graph에서 Lighting과 Rim의 연결을 함께 따라가야 한다면 수정 범위를 판단하기 어렵다. 기능별로 입력과 출력을 정해두면, Rim을 만드는 계산 안에서 바꿀 부분과 다른 기능에 전달되는 값을 구분할 수 있다.

각 **Module**은 이러한 논리적 책임을 맡는다. 그 계산을 재사용할 수 있도록 묶은 구현 단위가 앞서 소개한 Material Function이다. 여러 Module은 앞에서 배운 Normal·Light Direction·View Direction(N/L/V)과 Material Data를 공유하므로, 별도 Function으로 나누어도 필요한 Data의 관계는 이어진다.

**Master Material**은 필요한 Function을 호출하고 그 결과를 최종 Material 출력으로 모으는 조합 위치다. Multiply는 값을 곱하고 Add는 기여를 더하며, **Lerp(Linear Interpolation)**는 두 값을 비율에 따라 섞는다. Chapter 01의 Interpolation에서 Vertex 사이의 값을 준비했다면, 여기서는 두 Shader 결과 사이의 중간값을 만드는 데 사용한다.

<details>
<summary>Architecture Scope Note</summary>

Material Function을 분리하는 것만으로 실행 비용이나 Renderer 데이터 접근 문제가 해결되지는 않는다. Module은 논리적 책임이고 Function은 구현 단위이므로 Renderer Stage/Pass와 일대일 관계로 해석하지 않는다.

</details>

이러한 구조는 기능 추가와 수정이 용이하며, 프로젝트 규모가 커져도 일관된 구조를 유지할 수 있다.

---

## Development Workflow

Chapter 8부터는 하나의 Unreal Engine 프로젝트를 기반으로 모든 실습을 진행한다.

새로운 프로젝트를 반복해서 생성하지 않고, 하나의 프로젝트를 지속적으로 확장하는 방식을 사용한다.

```text
Project Setup
        │
        ▼
Framework Development
        │
        ▼
Character Rendering
        │
        ▼
Optimization
        │
        ▼
Final Showcase
```

이러한 방식은 실제 프로젝트에서 셰이더를 개발하는 과정과 동일한 워크플로우를 따른다.

---

## Chapter Structure

Chapter 8은 다음과 같은 순서로 진행된다.

앞부분에서는 환경과 공통 Data 경계를 준비한다. 그 다음 방향에서 Lighting·Specular·Rim 값을 만들고, Texture와 Emission을 합성한 뒤 Debug와 최종 통합으로 확인한다. 아래 목록은 기능 이름만 외우는 순서가 아니라, 한 결과가 다음 구현에서 어떤 역할을 맡는지 따라가는 순서다.

| Section | Description |
|---------|-------------|
| 8.0 | [Preparing the ASF Project](<./Chapter08.0_PreparingTheASFProject.md>) |
| 8.1 | [Architecture Overview](<./Chapter08.1_ArchitectureOverview copy.md>) |
| 8.2 | [Base Lighting](<./Chapter08.2_BaseLighting.md>) |
| 8.3 | [Shadow](<./Chapter08.3_Shadow.md>) |
| 8.4 | [Phong Specular — From Reflection to Specular Highlight](<./Chapter08.4_Specular.md>) |
| 8.5 | [Rim Light](<./Chapter08.5_RimLight.md>) |
| 8.6 | [MatCap](<./Chapter08.6_MatCap.md>) |
| 8.7 | [Emission](<./Chapter08.7_Emission.md>) |
| 8.8 | [Region-based Parameter Control](<./Chapter08.8_MaterialLayer.md>) |
| 8.9 | [Debug View](<./Chapter08.9_DebugView.md>) |
| 8.10 | [Final Framework](<./Chapter08.10_FinalFramwork.md>) |

각 절은 이전 절에서 구현한 기능을 기반으로 점진적으로 Framework를 확장하는 방식으로 구성되어 있다.

---

## Development Rules

Chapter 8에서는 다음 원칙을 따른다.

- 문서의 목표 환경은 Unreal Engine 5.8이며 실제 설치 버전·Rendering Path·Node 지원 여부를 기록하고 확인한다. 문서를 읽거나 Graph 예시를 보는 것과 실제 Engine에서 실행하여 검증하는 것은 구분한다.
- 하나의 프로젝트(`ASF_Demo`)를 끝까지 유지한다.
- Rendering Module의 계산을 Material Function으로 구현한다. Module은 논리적 책임, Material Function은 구현 단위이며 Renderer Stage/Pass와 일대일 관계가 아니다.
- 구현보다 Data Flow를 먼저 이해한다.
- 기능 추가보다 Architecture의 일관성을 우선한다.

---

## Expected Result

Chapter 8을 완료하면 다음과 같은 결과를 얻을 수 있다.

- 재사용 가능한 Anime Shader Framework
- Material Function Library
- Debug Scene
- 테스트 가능한 Anime Shader Material

이 Framework는 이후 Character Rendering에서 Skin, Hair, Eye, Face, Outfit 등의 렌더링 기능을 구현하는 기반이 된다.

---

> **Figure 8-1**
>
> *Overall Architecture of the Anime Shader Framework*
>
> *(Architecture Diagram)*

---

## Chapter Overview

Chapter 8은 ASF 프로젝트의 핵심 구현부이다.

지금까지 학습한 렌더링 이론을 바탕으로 재사용 가능하고 확장 가능한 Anime Shader Framework를 구축한다.

모든 기능은 하나의 Unreal Engine 프로젝트 안에서 단계적으로 구현되며, 기본 Framework는 Chapter 09의 Debug/Profiling과 향후 Advanced Character Rendering에서 활용한다. 현재 Foundation에는 Chapter 10이 없다.

---

다음 절에서는 ASF를 구현하기 위한 개발 환경을 준비하고, Unreal Engine 프로젝트를 생성한다.

**Next → [8.0 Preparing the ASF Project](<./Chapter08.0_PreparingTheASFProject.md>)**
