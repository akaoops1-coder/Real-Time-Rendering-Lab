# ASF-001 Naming Philosophy

> Version : v0.2  
> Status : Draft  
> Scope : Anime Shader Framework Project

---

# Purpose

본 문서는 Anime Shader Framework, 이하 ASF 프로젝트에서 사용하는 Naming의 기본 철학을 정의한다.

ASF Naming의 목적은 모든 Asset 이름을 하나의 복잡한 규칙으로 강제하는 것이 아니다.

Naming을 통해 다음 정보를 빠르게 이해할 수 있도록 하는 것이 목적이다.

```text
이 Asset은 무엇인가?

어떤 역할을 하는가?

어느 System에 속하는가?

다른 Asset과 어떤 관계가 있는가?
```

따라서 ASF Naming은 다음을 우선한다.

```text
Readability
↓
Role Clarity
↓
Consistency
↓
Maintainability
```

---

# Naming Philosophy

ASF에서는 이름 자체가 Documentation의 일부라고 본다.

좋은 이름은 별도의 설명 없이도 Asset의 역할을 어느 정도 추론할 수 있어야 한다.

예를 들어 다음 이름은 역할이 비교적 명확하다.

```text
MF_BaseLighting
MF_Shadow
MF_Specular
MF_RimLight
MF_Emission
```

반대로 의미를 추측하기 어려운 축약이나 개인적인 약어는 피한다.

```text
MF_BL
MF_SHD2
MF_SPX
MF_TMP01
```

Naming은 짧게 만드는 것보다 이해하기 쉽게 만드는 것을 우선한다.

---

# Principle 01. Role Before Description

ASF Asset 이름은 외형적인 설명보다 **역할**을 우선한다.

예를 들어 Material Function이 Character의 Base Lighting을 계산한다면 다음과 같이 작성한다.

```text
MF_BaseLighting
```

다음과 같은 이름은 가능하면 피한다.

```text
MF_CharacterLightThing
MF_LightCalc01
MF_MainFunction
```

이름만 보고 Asset의 기능을 이해할 수 있어야 한다.

---

# Principle 02. Use Established Platform Conventions

ASF는 Platform의 기존 Naming Convention을 불필요하게 대체하지 않는다.

Unreal Engine Asset Naming처럼 이미 널리 사용되는 Convention이 있다면 해당 Convention을 우선한다.

예를 들어 Unreal Engine에서는 Asset Type을 Prefix로 구분할 수 있다.

```text
M_
MI_
MF_
T_
SK_
SM_
```

ASF는 이러한 Platform Convention 위에 Framework-specific Naming Rule을 추가한다.

즉,

```text
Platform Convention
+
ASF Role Naming
```

구조를 따른다.

---

# Principle 03. Type Prefix Identifies Asset Type

Asset Type을 구분할 필요가 있는 경우 명확한 Prefix를 사용한다.

대표적인 Unreal Engine 예시는 다음과 같다.

| Prefix | Asset Type |
|---|---|
| `M_` | Material |
| `MI_` | Material Instance |
| `MF_` | Material Function |
| `T_` | Texture |
| `SK_` | Skeletal Mesh |
| `SM_` | Static Mesh |

ASF-specific Asset에서도 Platform Prefix를 가능하면 유지한다.

예를 들어:

```text
MF_BaseLighting
MF_Shadow
M_AnimeCharacter
MI_AnimeCharacter_Default
```

Prefix는 Asset의 Type을 나타내고, 뒤의 Name은 역할을 나타낸다.

---

# Principle 04. Function Names Describe What They Do

Material Function이나 Utility Function 이름은 내부 구현 방식보다 **기능적 결과**를 설명한다.

예를 들어:

```text
MF_BaseLighting
MF_Shadow
MF_Specular
MF_RimLight
MF_MatCap
MF_Emission
MF_DebugView
```

이러한 이름은 각각의 Module이 어떤 역할을 하는지 바로 이해할 수 있다.

반대로 내부 계산 방식만 표현한 이름은 가능하면 피한다.

```text
MF_DotProduct01
MF_Lerp02
MF_MultiplyMask
```

물론 특정 Math Utility가 실제 목적이라면 예외가 될 수 있다.

예:

```text
MF_Remap
MF_SafeNormalize
MF_LinearStep
```

---

# Principle 05. Naming Should Reflect Architecture

ASF는 Module 기반 Architecture를 사용하므로 Naming도 해당 구조를 반영한다.

예를 들어 Base Lighting과 Shadow가 독립 Module이라면 각각 독립된 이름을 사용한다.

```text
MF_BaseLighting
MF_Shadow
```

두 기능을 하나의 이름으로 모호하게 표현하지 않는다.

```text
MF_MainLightingStuff
```

Architecture가 분리되어 있다면 Naming도 분리되어야 한다.

---

# Principle 06. Avoid Redundant Context

이미 Folder, Asset Type, Parent System에서 알 수 있는 정보를 이름에 반복해서 넣지 않는다.

예를 들어 모든 Material Function이 이미 다음 위치에 있다고 가정한다.

```text
Content/ASF/Materials/Functions/
```

이 경우 다음처럼 지나치게 긴 이름은 필요하지 않다.

```text
MF_ASF_MaterialFunction_Character_BaseLighting
```

다음 정도면 충분하다.

```text
MF_BaseLighting
```

필요한 정보만 이름에 포함한다.

---

# Principle 07. Add Context Only When Ambiguity Exists

같은 기능이 여러 영역에서 사용되어 충돌할 가능성이 있을 때만 Context를 추가한다.

예를 들어 Shadow Function이 하나뿐이라면:

```text
MF_Shadow
```

로 충분하다.

하지만 서로 다른 종류의 Shadow System이 존재한다면:

```text
MF_SurfaceShadow
MF_HairShadow
MF_FaceShadow
```

처럼 역할을 구분한다.

Context는 필요할 때 추가한다.

---

# Principle 08. Prefer Full Words Over Ambiguous Abbreviations

명확하지 않은 축약은 피한다.

예를 들어:

```text
MF_Specular
```

를 다음처럼 불필요하게 줄이지 않는다.

```text
MF_Spec
MF_Spc
```

다만 업계에서 일반적으로 통용되고 의미가 명확한 약어는 사용할 수 있다.

예:

```text
UV
LOD
SDF
PBR
HDR
GPU
CPU
```

축약 여부의 기준은 길이가 아니라 **오해 가능성**이다.

---

# Principle 09. Numbering Is Not Meaning

Asset 이름의 핵심 식별자로 숫자만 사용하지 않는다.

예를 들어 다음은 피한다.

```text
MF_Shadow01
MF_Shadow02
MF_Shadow03
```

각 Asset이 다른 역할을 한다면 역할을 이름으로 표현한다.

```text
MF_SurfaceShadow
MF_FaceShadow
MF_HairShadow
```

숫자는 다음과 같은 경우에만 사용한다.

```text
Version
Test Variant
Temporary Comparison
Sequential Capture
```

단, 최종 Production Asset에서는 의미 있는 이름으로 정리한다.

---

# Principle 10. Temporary Assets Must Be Obvious

Test나 Experiment용 Asset은 Production Asset과 혼동되지 않도록 명확하게 구분한다.

예를 들어:

```text
M_Test_ShaderComplexity
M_Test_Overdraw
SK_Test_LODCharacter
```

또는 별도의 Test Folder에서 관리할 수 있다.

```text
Content/ASF/Tests/
```

Temporary Asset이 Production Asset처럼 보이지 않게 한다.

---

# Principle 11. Debug Assets Must Be Explicit

Debug 목적의 Asset이나 Function은 이름에서 역할을 명확하게 드러낸다.

예를 들어:

```text
MF_DebugView
M_DebugCharacter
MI_DebugNormals
```

Debug Asset은 최종 Rendering Asset과 구분되어야 한다.

---

# Principle 12. Experimental Variants Need Clear Labels

동일 기능의 여러 실험 버전을 비교할 경우 차이를 이름에 명확하게 남긴다.

예를 들어:

```text
MF_Shadow_Threshold
MF_Shadow_SmoothStep
```

또는 Test Folder에서:

```text
M_Test_Shadow_Hard
M_Test_Shadow_Soft
```

처럼 비교 기준을 이름으로 표시한다.

다음처럼 의미 없는 숫자 Variant는 피한다.

```text
M_Test_Shadow01
M_Test_Shadow02
```

---

# Principle 13. Character-specific Assets Use Context Only When Needed

범용 ASF Module은 Character 이름을 포함하지 않는다.

예를 들어:

```text
MF_BaseLighting
MF_Specular
```

처럼 재사용 가능한 이름을 사용한다.

반면 특정 Character 전용 Asset이라면 Character Context를 포함할 수 있다.

예:

```text
MI_Aira_Body
MI_Aira_Hair
T_Aira_FaceMask
```

이 경우에도 Asset Type과 역할이 명확하게 보여야 한다.

---

# Principle 14. Avoid Over-encoding Metadata

Asset 이름에 모든 정보를 넣으려고 하지 않는다.

예를 들어 다음처럼 지나치게 많은 정보를 조합하는 방식은 피한다.

```text
T_Player_Aira_Face_BaseColor_4K_sRGB_V01_Final
```

이런 정보 중 상당수는 Asset Setting, Folder Structure, Source Control, Metadata에서 관리할 수 있다.

Naming에는 실제 식별에 필요한 정보만 남긴다.

---

# Principle 15. Folder Structure and Naming Work Together

Naming은 Folder Structure와 함께 사용한다.

예를 들어:

```text
Content/
└─ ASF/
   ├─ Materials/
   │  ├─ Functions/
   │  ├─ Instances/
   │  └─ Debug/
   ├─ Textures/
   ├─ Characters/
   └─ Tests/
```

처럼 구조가 명확하다면 Asset Name을 지나치게 길게 만들 필요가 없다.

Naming과 Folder Structure는 서로 부족한 정보를 보완한다.

---

# Principle 16. Naming Must Survive Refactoring

Asset 이름은 현재 구현 방식에 지나치게 의존하지 않아야 한다.

예를 들어 현재 Shadow Function이 Dot Product를 사용한다고 해서:

```text
MF_Shadow_DotProduct
```

처럼 이름을 고정하면 나중에 내부 구현이 변경되었을 때 이름과 실제 역할이 어긋날 수 있다.

기능의 목적이 변하지 않는다면:

```text
MF_Shadow
```

같은 역할 중심 이름이 더 안정적이다.

---

# Principle 17. Public Framework Assets Need Stronger Naming Discipline

ASF Framework에서 반복적으로 사용되거나 다른 Module에서 참조되는 Asset은 Naming을 더 엄격하게 관리한다.

예:

```text
MF_BaseLighting
MF_Shadow
MF_Specular
MF_RimLight
MF_MatCap
MF_Emission
```

반면 단기 Experiment Asset은 비교적 자유롭게 만들 수 있다.

단, Experiment가 Framework에 편입될 경우 Naming을 Production 기준으로 정리한다.

---

# Principle 18. Naming Is Refactored with Architecture

Architecture가 변경되면 Naming도 함께 검토한다.

예를 들어 기존 하나의 Function이 다음처럼 분리되었다면:

```text
MF_Lighting
```

에서

```text
MF_BaseLighting
MF_Specular
MF_RimLight
```

로 Architecture가 변경될 수 있다.

이 경우 기존 이름을 그대로 유지하는 것이 아니라 새로운 책임 구조에 맞춰 Naming을 Refactor한다.

---

# ASF Module Naming

현재 ASF Rendering Module의 기본 Naming은 다음 형태를 사용한다.

```text
MF_<Role>
```

예:

```text
MF_BaseLighting
MF_Shadow
MF_Specular
MF_RimLight
MF_MatCap
MF_Emission
MF_DebugView
```

Role은 해당 Module이 수행하는 기능을 명확하게 표현해야 한다.

---

# Material Naming

ASF Material은 목적에 따라 다음 구조를 사용할 수 있다.

```text
M_<Role>
```

예:

```text
M_AnimeCharacter
M_PBRCharacter
M_DebugCharacter
```

Material Instance는 다음과 같이 구분한다.

```text
MI_<Role>
```

또는 Character-specific Context가 필요한 경우:

```text
MI_<Character>_<Part>
```

예:

```text
MI_Aira_Body
MI_Aira_Hair
MI_Aira_Eye
```

---

# Texture Naming

Texture는 Platform Convention과 실제 역할을 함께 표현한다.

예:

```text
T_Aira_BaseColor
T_Aira_Normal
T_Aira_Masks
T_Aira_EmissionMask
```

Texture Packing이 적용된 경우 실제 Channel의 의미는 Documentation이나 Asset Metadata에서 명확하게 관리한다.

이름에 모든 Channel 정보를 반드시 포함하지는 않는다.

필요한 경우에만 다음처럼 표현할 수 있다.

```text
T_Aira_Masks_RMA
```

단, Packing Convention이 프로젝트 전체에서 고정되었다면 별도 반복 표기는 생략할 수 있다.

---

# Test Naming

Profiling과 Optimization Test Asset은 목적을 명확히 표현한다.

예:

```text
M_Test_ShaderCost
M_Test_Overdraw
SK_Test_GeometryLOD
SM_Test_DrawCalls
```

이름만 보고 어떤 Bottleneck이나 Rendering Cost를 검증하기 위한 Asset인지 알 수 있어야 한다.

---

# Figure Naming

Documentation Figure의 Naming Rule은 `ASF-003 Documentation Standard`에서 관리한다.

Naming Philosophy에서는 Figure가 다음 원칙을 따르는 것만 요구한다.

```text
Chapter Identity

Sequential Number

Stable File Name
```

실제 경로와 파일명 형식은 Documentation Standard를 Source of Truth로 사용한다.

---

# Naming Review Checklist

Asset이나 Module을 최종 구조에 편입하기 전에 다음 항목을 확인한다.

```text
Does the name describe its role?

Can another person understand it?

Is unnecessary metadata included?

Does the name match the architecture?

Is the abbreviation clear?

Can the name survive internal implementation changes?

Does another Asset already use the same concept differently?
```

필요하다면 이름을 Refactor한다.

---

# What ASF Naming Does Not Define

ASF-001은 다음 항목을 상세하게 규정하지 않는다.

```text
Complete Unreal Engine Asset Naming Convention

Folder Structure

File System Structure

Texture Import Settings

Version Control Naming

Source File Naming

Platform-specific Engine Rules
```

이러한 규칙은 해당 Platform 또는 Implementation Documentation에서 관리한다.

ASF-001의 역할은 **ASF 전체에서 유지할 Naming Philosophy를 정의하는 것**이다.

---

# Relationship with Other Standards

ASF Naming은 다른 Standard와 다음 관계를 가진다.

```text
ASF-000 Project Principles
        ↓
ASF-001 Naming Philosophy
        ↓
ASF-002 Rendering Architecture
        ↓
Implementation Naming
```

Rendering Module의 책임은 `ASF-002 Rendering Architecture`에서 정의하고,

그 Module을 어떤 이름으로 표현할지는 ASF-001의 Naming Philosophy를 따른다.

Documentation Heading이나 Figure Naming의 세부 규칙은 `ASF-003 Documentation Standard`에서 관리한다.

---

# Final Principle

ASF Naming의 목표는 복잡한 이름을 만드는 것이 아니다.

좋은 이름은

```text
짧고

명확하며

역할을 설명하고

Architecture와 일치하며

다른 사람이 이해할 수 있어야 한다.
```

따라서 ASF에서는 다음 원칙을 사용한다.

> **이름은 Asset이 어떻게 만들어졌는지가 아니라, 무엇을 위해 존재하는지를 설명해야 한다.**