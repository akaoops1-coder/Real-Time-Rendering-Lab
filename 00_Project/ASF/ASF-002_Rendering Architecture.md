# ASF-002 Rendering Architecture

> Version : v0.2  
> Status : Draft  
> Scope : Anime Shader Framework Project

---

# Purpose

본 문서는 Anime Shader Framework, 이하 ASF의 Rendering Architecture를 정의한다.

ASF Rendering Architecture의 목적은 특정 Shader Effect의 구현 순서를 나열하는 것이 아니다.

다음 개념을 명확하게 구분하고 서로 어떻게 연결되는지를 정의하는 것이 목적이다.

```text
Rendering Pipeline Stage

Rendering Data

Rendering Module

Character Rendering Feature

Debug / Profiling
```

ASF는 이 구조를 기준으로 Rendering Concept를 이해하고, Unreal Engine에서 실제 Framework를 구현한다.

---

# Architecture Principle

ASF Rendering Architecture는 다음 원칙을 따른다.

```text
Rendering Pipeline
        ↓
Rendering Data
        ↓
Rendering Module
        ↓
Character Application
        ↓
Debug / Validation
        ↓
Profiling / Optimization
```

Rendering Pipeline은 전체 Rendering Process의 기준이 된다.

Rendering Data는 Pipeline 과정에서 생성되거나 사용되는 정보이다.

Rendering Module은 해당 Data를 이용하여 특정 Rendering Function을 수행한다.

Character Application은 Module을 실제 Character Surface에 적용한다.

Debug와 Profiling은 결과와 Cost를 검증한다.

---

# Rendering Pipeline Is the Foundation

ASF의 Rendering Architecture는 GPU Rendering Pipeline을 기준으로 이해한다.

개념적으로 다음과 같이 볼 수 있다.

```text
Application / CPU
        ↓
Geometry Data
        ↓
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

실제 Modern Rendering Engine은 이보다 훨씬 복잡하며 여러 Pass와 Intermediate Buffer를 사용한다.

하지만 Foundation에서는 이 기본 구조를 중심으로 Rendering Data가 어디에서 생성되고 사용되는지를 이해한다.

---

# Rendering Stage and Rendering Feature Are Different

ASF에서는 Rendering Pipeline의 **Stage**와 Shader의 **Feature**를 명확하게 구분한다.

Rendering Stage는 Rendering Pipeline 안에서 수행되는 처리 단계이다.

예를 들면 다음과 같다.

```text
Vertex Processing

Primitive Processing

Rasterization

Pixel Processing

Output
```

반면 다음은 Rendering Stage가 아니다.

```text
Base Lighting

Shadow

Specular

Rim Light

MatCap

Emission

Face SDF
```

이들은 특정 Rendering Goal을 수행하는 **Rendering Module 또는 Feature**이다.

따라서 다음과 같은 구조는 사용하지 않는다.

```text
Lighting Stage
↓
Shadow Stage
↓
Face SDF Stage
↓
Specular Stage
↓
Rim Light Stage
```

이는 GPU Pipeline Stage와 Shader Feature를 혼합하기 때문이다.

ASF에서는 대신 다음처럼 이해한다.

```text
Rendering Pipeline
        ↓
Pixel Processing
        ↓
Rendering Modules
        ↓
Final Surface Result
```

---

# Rendering Data

Rendering Module은 Rendering Data를 입력받아 동작한다.

ASF에서 자주 사용하는 주요 Rendering Data는 다음과 같다.

```text
Position

Normal

Tangent

UV

View Direction

Light Direction

Depth

Color

Material Parameters

Texture Sample

Mask

Shadow Information
```

각 Data는 어떤 Space에 존재하는지와 어떤 범위를 가지는지를 명확하게 이해해야 한다.

예를 들어 Normal 하나만 보더라도 다음과 같은 차이가 존재할 수 있다.

```text
Tangent Space Normal

Object Space Normal

World Space Normal

View Space Normal
```

따라서 Rendering Data는 값 자체뿐 아니라 **Meaning과 Space**까지 함께 이해해야 한다.

---

# Data Flow Principle

ASF에서는 Rendering Module을 Node Graph 형태보다 Data Flow 형태로 먼저 이해한다.

예를 들어 기본 Lighting은 다음처럼 표현할 수 있다.

```text
Surface Normal
      +
Light Direction
      ↓
Dot Product
      ↓
NdotL
      ↓
Lighting Response
```

Stylized Lighting이라면 여기에 추가적인 변환이 들어갈 수 있다.

```text
NdotL
↓
Remap
↓
Threshold / SmoothStep
↓
Stylized Lighting
```

이 구조를 먼저 이해한 뒤 Unreal Material Node로 구현한다.

---

# Rendering Module

Rendering Module은 하나의 Rendering Function을 수행하는 독립적인 기능 단위이다.

Module은 가능한 한 다음 조건을 만족해야 한다.

```text
Clear Responsibility

Clear Input

Clear Output

Reusable Structure

Debuggable Result
```

하나의 Module이 지나치게 많은 역할을 담당하지 않도록 한다.

---

# Module Responsibility

각 Module은 하나의 주요 Rendering Responsibility를 가진다.

예를 들어:

```text
MF_BaseLighting
→ 기본 Lighting Response 계산

MF_Shadow
→ Shadow 관련 Lighting Control

MF_Specular
→ Specular Response 계산

MF_RimLight
→ Rim Lighting 계산

MF_MatCap
→ View-based MatCap 표현

MF_Emission
→ Emission Contribution 계산

MF_DebugView
→ Internal Rendering Data 시각화
```

Module의 이름과 실제 Responsibility가 일치해야 한다.

---

# Module Input and Output

각 Rendering Module은 Input과 Output을 명확하게 정의한다.

예를 들어 Base Lighting Module은 개념적으로 다음과 같은 구조를 가질 수 있다.

```text
Input

Normal
Light Direction
Lighting Parameters

        ↓

Base Lighting Module

        ↓

Output

Lighting Value
```

Shadow Module은 다음처럼 구성될 수 있다.

```text
Input

Lighting Value
Shadow Data
Shadow Parameters

        ↓

Shadow Module

        ↓

Output

Shadow-adjusted Lighting
```

Module이 어떤 Data를 소비하고 어떤 Data를 생성하는지 설명할 수 있어야 한다.

---

# Module Composition

ASF의 최종 Material은 여러 Module을 조합하여 구성한다.

개념적으로 다음과 같은 흐름을 사용할 수 있다.

```text
Surface Data
      ↓
Base Lighting
      ↓
Shadow Control
      ↓
Specular
      ↓
Rim Light
      ↓
Additional Features
      ↓
Emission
      ↓
Final Surface Result
```

단, 이 순서는 GPU Rendering Pipeline Stage를 의미하지 않는다.

이는 **ASF 내부 Shader Logic의 Data Composition Flow**이다.

이 차이를 반드시 유지한다.

---

# Composition Order Is Functional, Not Pipeline Order

Module의 순서는 Rendering Pipeline의 Stage 순서와 다르다.

예를 들어 다음 구조:

```text
Base Lighting
↓
Shadow
↓
Specular
↓
Rim Light
```

는

```text
Vertex
↓
Rasterization
↓
Pixel
```

같은 Hardware Pipeline 구조가 아니다.

Module Composition은 최종 Surface Result를 만들기 위한 **Function Composition**이다.

따라서 Module 순서는 Visual Goal이나 Calculation Dependency에 따라 변경될 수 있다.

---

# Shared Data

여러 Module에서 반복적으로 필요한 Data는 가능한 한 공통적으로 계산하고 재사용한다.

예를 들어 다음 Data가 여러 Module에서 사용될 수 있다.

```text
World Normal

View Direction

Light Direction

NdotL

Depth

Character Mask
```

같은 계산을 여러 Module에서 반복하지 않도록 Data Flow를 설계한다.

단, 재사용을 위해 지나치게 복잡한 Global Structure를 만드는 것도 피한다.

---

# Character Rendering Layer

Rendering Module은 실제 Character Surface에 적용된다.

ASF에서는 주요 Character Rendering 영역을 다음처럼 구분한다.

```text
Skin

Hair

Eye

Face

Outfit

Accessory
```

각 영역은 같은 Rendering Pipeline을 사용하지만 요구하는 Material Response는 다를 수 있다.

---

# Shared Rendering Foundation

Character Part마다 완전히 다른 Shader를 만드는 것을 기본 전략으로 사용하지 않는다.

가능한 경우 공통 Rendering Foundation을 공유한다.

예를 들어:

```text
Common

Base Lighting
Shadow
Specular
Rim Light
Debug

        ↓

Character-specific Extension

Skin
Hair
Eye
Face
Outfit
```

이를 통해 Framework의 중복을 줄이고 유지보수성을 높인다.

---

# Character-specific Features

모든 Feature를 범용 Module로 만들 필요는 없다.

특정 Character Part에서만 필요한 기능은 별도의 Extension으로 분리할 수 있다.

예를 들어:

```text
Face SDF

Hair Anisotropy

Hair Shadow

Eye Highlight

Skin-specific Response
```

이러한 기능은 Character-specific Module로 취급한다.

---

# PBR and Stylized Rendering

ASF Architecture는 PBR과 Stylized Rendering을 완전히 분리된 System으로 보지 않는다.

둘은 대부분 동일한 Rendering Data를 사용한다.

예를 들어:

```text
Normal

Light Direction

View Direction

Roughness

Metallic

Shadow

Reflection
```

차이는 주로 Response Function에 존재한다.

---

# PBR Response

PBR에서는 Lighting Input을 물리적으로 타당한 방식으로 평가한다.

개념적으로:

```text
Surface Data
+
Light Data
+
View Data
↓
BRDF
↓
PBR Lighting Result
```

---

# Stylized Response

Stylized Rendering에서는 같은 Data를 Visual Goal에 맞게 재해석할 수 있다.

예를 들어:

```text
NdotL
↓
Threshold
↓
Two-tone Lighting
```

또는:

```text
Specular Response
↓
Shape Control
↓
Stylized Highlight
```

따라서 ASF에서 Stylized Rendering은 Rendering Data를 무시하는 것이 아니라 **의도적으로 변환하는 과정**이다.

---

# Material Architecture

Unreal Engine 구현에서는 Material과 Material Function을 역할에 따라 분리한다.

개념적으로 다음과 같은 구조를 사용할 수 있다.

```text
Master Material
       │
       ├─ MF_BaseLighting
       ├─ MF_Shadow
       ├─ MF_Specular
       ├─ MF_RimLight
       ├─ MF_MatCap
       ├─ MF_Emission
       └─ MF_DebugView
```

Master Material은 각 Module을 조합하는 역할을 담당한다.

각 Material Function은 가능한 한 하나의 주요 기능을 담당한다.

---

# Material Function Is an Implementation Unit

Material Function은 ASF Architecture에서 Module을 구현하기 위한 대표적인 방법이다.

하지만 다음 두 개념을 동일하게 보지는 않는다.

```text
Rendering Module
≠
Material Function
```

Rendering Module은 Architecture Concept이다.

Material Function은 Unreal Engine에서 이를 구현하는 방법 중 하나이다.

향후 다른 Engine이나 Custom Shader에서 구현할 경우 같은 Module이 다른 형태로 구현될 수 있다.

---

# Parameter Architecture

ASF Rendering Module은 가능한 한 필요한 Parameter를 외부에서 제어할 수 있도록 설계한다.

예를 들어:

```text
Threshold

Softness

Intensity

Color

Mask

Range
```

하지만 모든 내부 값을 Parameter로 노출하지 않는다.

Parameter는 다음 목적이 있을 때 제공한다.

```text
Art Direction

Character Variation

Material Instance Control

Debugging

Production Adjustment
```

---

# Material Instance

Material Instance는 동일한 Shader Architecture를 유지하면서 Character나 Material별 Variation을 제공하는 역할을 한다.

개념적으로:

```text
Master Material
      ↓
Material Instance
      ↓
Character-specific Parameters
```

Material Instance는 새로운 Shader Architecture를 만드는 것이 아니다.

동일한 Architecture 안에서 Parameter Variation을 제공한다.

---

# Mask Architecture

ASF에서는 Character-specific Control을 위해 Mask를 사용할 수 있다.

Mask는 다음과 같은 기능을 제어할 수 있다.

```text
Lighting Region

Shadow Region

Specular Region

Rim Light Region

Emission Region

Material Layer
```

Mask는 Texture 전체가 하나의 Scalar로 변환되는 것이 아니다.

Texture를 현재 Pixel의 UV 위치에서 Sample한 뒤, 해당 Pixel에서 얻은 Channel Value가 현재 Surface 위치의 Scalar 값으로 사용된다.

예를 들어:

```text
Texture
↓
UV Sample
↓
Current Pixel R Channel
↓
Scalar 0–1
↓
Rendering Module Input
```

Material Function이 Texture 자체를 반드시 직접 Sample해야 하는 것은 아니다.

필요한 경우 Texture Sample은 Function 밖에서 수행하고 현재 Surface 위치의 Mask Value만 Module에 전달할 수 있다.

---

# Texture Packing

여러 Mask를 하나의 Texture Channel에 Packing할 수 있다.

예:

```text
R → Specular Mask

G → Rim Mask

B → Emission Mask

A → Additional Mask
```

Texture Packing은 Texture Sample 수와 Asset 관리 측면에서 효율적일 수 있다.

다만 다음 조건을 함께 고려해야 한다.

```text
Compression

Resolution

Channel Precision

Sampling Requirement
```

무조건 Packing하는 것이 목표는 아니다.

---

# Debug Architecture

Debug 기능은 ASF Rendering Architecture의 일부이다.

Rendering Module 내부의 Data를 확인할 수 있어야 한다.

대표적인 Debug Data는 다음과 같다.

```text
Normal

NdotL

Lighting Value

Shadow Value

Specular

Mask

UV

Depth
```

개념적으로:

```text
Internal Data
↓
Debug Module
↓
Visual Output
```

형태로 확인할 수 있다.

---

# Debug Before Guessing

Visual Result가 예상과 다를 경우 최종 Color만 보고 원인을 추측하지 않는다.

가능하면 Data를 단계적으로 확인한다.

예를 들어:

```text
Normal
↓
Light Direction
↓
NdotL
↓
Threshold
↓
Shadow
↓
Final Lighting
```

각 단계의 값을 확인하여 어느 지점에서 예상과 달라졌는지 찾는다.

---

# Validation Architecture

ASF Rendering Feature는 가능한 범위에서 다음 기준으로 검증한다.

```text
Correct Input

Expected Data Flow

Expected Visual Result

Debug Verification

Edge Case

Performance Impact
```

Visual Result만 정상이라고 해서 Architecture가 올바른 것은 아니다.

---

# Performance Architecture

Performance는 Framework 완성 이후에 별도로 확인하는 요소가 아니다.

Architecture 단계부터 다음 Cost를 고려한다.

```text
Geometry Cost

Pixel Cost

Shader Cost

Draw Call

Transparency

LOD

Character Count
```

그러나 Optimization은 항상 측정을 기반으로 한다.

---

# Profiling Flow

기본 Profiling Flow는 다음과 같다.

```text
Measure
↓
CPU or GPU
↓
Find Bottleneck
↓
Identify Major Cost
↓
Optimize
↓
Measure Again
```

특정 Module이 복잡해 보인다는 이유만으로 Optimization하지 않는다.

실제 Performance Impact를 확인한 뒤 수정한다.

---

# Architecture and LOD

Character Rendering Architecture는 Camera Distance와 Screen Size 변화도 고려한다.

가까운 Character와 멀리 있는 Character가 항상 동일한 Rendering Detail을 유지할 필요는 없다.

예를 들어 다음 요소들을 줄일 수 있다.

```text
Triangle Count

Material Section

Shader Feature

Transparency Layer

Accessory

Lighting Detail
```

LOD는 Geometry Reduction만을 의미하지 않는다.

---

# Separation of Concept and Platform

ASF Rendering Architecture는 Platform-independent Concept를 우선한다.

예를 들어:

```text
Base Lighting Module
```

이라는 개념은 Unreal Engine의 `Material Function`으로 구현할 수도 있고,

Custom HLSL Function이나 다른 Engine Shader Function으로 구현할 수도 있다.

따라서 Architecture 문서에서는 Concept와 Implementation을 구분한다.

---

# Unreal Engine Implementation

현재 ASF의 주요 Implementation Platform은 Unreal Engine이다.

따라서 실제 구현에서는 다음 요소를 사용한다.

```text
Material

Material Function

Material Instance

Texture

Parameter

Custom HLSL

Debug View
```

하지만 Unreal Engine의 현재 구현 방식이 ASF Rendering Architecture 자체를 정의하지는 않는다.

---

# Architecture Dependency

Module 간 Dependency는 가능한 한 단순하게 유지한다.

좋은 구조는 다음처럼 Data Flow가 명확하다.

```text
Input Data
↓
Module A
↓
Module B
↓
Output
```

다음과 같이 서로 강하게 얽힌 구조는 피한다.

```text
Module A
↔
Module B
↔
Module C
↔
Module A
```

Module 간 Circular Dependency나 불필요한 Hidden Dependency를 만들지 않는다.

---

# Architecture Scalability

새로운 Feature가 추가될 때 전체 Framework를 다시 작성하지 않아도 되어야 한다.

예를 들어:

```text
Current

Base Lighting
Shadow
Specular

        ↓

Add

Rim Light
```

기존 Module을 크게 변경하지 않고 새로운 Module을 추가할 수 있는 구조를 목표로 한다.

---

# Architecture Refactoring

Architecture는 고정된 것이 아니다.

실제 Implementation과 Character Test를 통해 문제가 확인되면 Refactoring한다.

다음 질문을 기준으로 판단한다.

```text
Is this Module doing too much?

Is the Data Flow clear?

Is the same calculation repeated?

Is the Feature reusable?

Can the result be debugged?

Does the Architecture scale?

Does the current structure create unnecessary Cost?
```

필요하면 Module을 분리하거나 통합한다.

---

# Architecture Review Checklist

Rendering Feature를 Framework에 추가할 때 다음을 확인한다.

### Concept

```text
What problem does it solve?

Which Rendering Data does it use?

Where does it belong in the Rendering Process?
```

### Module

```text
What is its responsibility?

What are its inputs?

What is its output?
```

### Integration

```text
How does it connect to other Modules?

Does it introduce unnecessary dependency?

Can it be reused?
```

### Debug

```text
Can the internal result be visualized?

Can incorrect input be identified?
```

### Performance

```text
What kind of Cost can it introduce?

Can the Cost be measured?
```

---

# Current ASF Rendering Architecture

현재 ASF Rendering Architecture를 간단히 표현하면 다음과 같다.

```text
Rendering Pipeline
        ↓
Surface / Scene Data
        ↓
Common Rendering Data
        ↓
ASF Rendering Modules
        │
        ├─ Base Lighting
        ├─ Shadow
        ├─ Specular
        ├─ Rim Light
        ├─ MatCap
        ├─ Emission
        └─ Debug
        ↓
Character-specific Extensions
        │
        ├─ Skin
        ├─ Hair
        ├─ Eye
        ├─ Face
        └─ Outfit
        ↓
Final Material Result
        ↓
Validation / Profiling
```

이 구조는 특정 Node Graph가 아니라 ASF 전체 Rendering System의 논리적인 관계를 표현한다.

---

# Relationship with Other Standards

ASF Rendering Architecture는 다음 Standard와 연결된다.

```text
ASF-000 Project Principles
        ↓
ASF-001 Naming Philosophy
        ↓
ASF-002 Rendering Architecture
        ↓
ASF-003 Documentation Standard
```

`ASF-000`은 Architecture의 철학을 정의한다.

`ASF-001`은 Architecture 안의 Asset과 Module Naming 원칙을 정의한다.

`ASF-002`는 Rendering System의 구조를 정의한다.

`ASF-003`은 이 Architecture를 Documentation에서 어떻게 설명할지 정의한다.

---

# What ASF-002 Does Not Define

본 문서는 다음 내용을 상세하게 설명하지 않는다.

```text
GPU Architecture의 세부 구현

Unreal Engine Renderer 내부 구조

개별 Material Node 사용법

각 Rendering Equation의 상세 수학

Character별 Shader Tutorial

Profiling Tool 사용법
```

이러한 내용은 Foundation 또는 Advanced Documentation에서 다룬다.

ASF-002는 Rendering System을 설계할 때 유지해야 하는 **Architecture Boundary와 Responsibility**를 정의한다.

---

# Final Principle

ASF Rendering Architecture의 핵심은 많은 Rendering Feature를 하나의 Material에 넣는 것이 아니다.

중요한 것은

```text
Rendering Pipeline을 기준으로 이해하고

Rendering Data의 의미를 파악하며

기능을 독립적인 Module로 분리하고

Data Flow를 명확하게 유지하며

Debug와 Validation이 가능한 구조를 만드는 것
```

이다.

따라서 ASF에서는 다음 관계를 유지한다.

```text
Pipeline
↓
Data
↓
Module
↓
Character Application
↓
Validation
↓
Optimization
```

> **ASF Rendering Architecture는 Shader Effect의 목록이 아니라, Rendering Data가 어떤 구조를 통해 Character의 최종 Pixel Result로 변환되는지를 이해하고 관리하기 위한 Framework이다.**