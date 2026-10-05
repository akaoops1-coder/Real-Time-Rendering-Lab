# Chapter 08 — Building an Anime Shader

## 8.1 Architecture Overview

### Architecture Goals

8.0에서는 ASF Shader를 실제로 구현하기 위한 프로젝트와 개발 환경을 준비했다.

이제부터는 실제 Shader Architecture를 구성한다.

ASF의 핵심 목표는 하나의 거대한 Material Graph를 만드는 것이 아니다.

Shader가 복잡해질수록 하나의 Material에 모든 계산을 직접 연결하는 방식은 구조를 빠르게 복잡하게 만든다.

Lighting, Shadow, Specular, Rim Light 등의 기능이 하나의 Graph 안에 계속 추가되면 각 기능의 경계가 불분명해지고, 특정 기능을 수정했을 때 다른 부분에 영향을 주기 쉬워진다.

ASF는 이러한 문제를 해결하기 위해 Shader를 여러 개의 독립적인 Module로 분리한다.

각 Module은 명확한 역할을 가지고 필요한 데이터를 입력받아 결과를 반환한다. Shared Data의 Space/Type과 결과를 합치는 연산도 Interface의 일부이다.

즉, ASF의 기본 구조는 다음과 같다.

~~~text
Input
  ↓
Rendering Modules
  ↓
Composition
  ↓
Output
~~~

여기서 중요한 것은 각각의 Module이 독립적인 기능을 담당한다는 점이다.

예를 들어 Base Lighting Module은 기본적인 빛의 영향을 계산하고, Shadow Module은 그 결과를 바탕으로 그림자 영역을 처리한다.

이후 Specular Module, Rim Light Module 등의 기능도 동일한 원칙으로 추가할 수 있다.

따라서 ASF의 Architecture는 기능을 계속 추가하면서도 전체 구조가 무너지지 않도록 만드는 것을 목표로 한다.


### From a Single Graph to Modules

일반적인 Shader 제작에서는 하나의 Material Graph 안에 모든 연산을 직접 구성할 수 있다.

처음에는 단순하기 때문에 문제가 없어 보인다.

하지만 기능이 추가되면서 Graph는 점점 커진다.

~~~text
Base Color
   ↓
Lighting
   ↓
Shadow
   ↓
Specular
   ↓
Rim Light
   ↓
Emission
   ↓
Final Color
~~~

각 기능을 계속 연결하다 보면 하나의 Graph 안에 수많은 노드와 연결선이 존재하게 된다.

이 방식의 가장 큰 문제는 기능의 경계가 사라진다는 것이다.

예를 들어 Shadow 계산을 수정하기 위해 Graph의 한 부분을 수정했는데, 그 결과가 Lighting이나 Specular 계산에 영향을 줄 수도 있다.

ASF에서는 이러한 구조 대신 각 기능을 Material Function으로 분리한다.

Index에서 보았듯이 Material Function은 입력을 받아 계산 결과를 돌려주는 재사용 단위다. 여기서는 Shadow의 구현을 바꾸더라도 다른 Module이 사용할 출력의 의미가 유지되도록 경계를 정한다. Graph가 작아지는 것만큼 중요한 것은, 무엇이 들어가고 무엇이 나오는지 읽을 수 있게 되는 것이다.

~~~text
                     ┌─ MF_BaseLighting
                     │
Input Data ──────────┼─ MF_Shadow
                     │
                     ├─ MF_Specular
                     │
                     ├─ MF_RimLight
                     │
                     └─ MF_Emission
                              ↓
                         Composition
                              ↓
                           Output
~~~

각 Material Function은 하나의 기능을 담당한다.

이렇게 하면 전체 Shader의 기능을 작은 단위로 나누어 이해하고 테스트할 수 있다.


### Module Input and Output

ASF의 각 Rendering Module은 기본적으로 다음과 같은 구조를 가진다.

~~~text
Input
  ↓
Processing
  ↓
Result
~~~

Input은 Module이 계산을 수행하기 위해 필요한 데이터를 의미한다.

Processing은 해당 Module이 담당하는 실제 계산이다.

Result는 계산된 결과를 다음 단계로 전달하는 출력이다.

예를 들어 입력에 Normal이 있다는 것만으로는 충분하지 않다. 그 Normal의 Space와 길이 조건을 알아야 다음 계산에서 Dot Product를 올바르게 사용할 수 있다. 출력도 Scalar Mask인지 RGB Contribution인지 먼저 정해야 Master에서 곱할 값과 더할 값을 구분할 수 있다. 이처럼 Interface는 Pin 이름에 더해 Data의 의미를 약속하는 경계다.

예를 들어 Base Lighting Module은 다음과 같은 형태가 된다.

~~~text
Base Color
Light Direction
Normal
     ↓
Base Lighting
     ↓
Lighting Result
~~~

여기서 중요한 것은 Base Lighting Module이 최종 Material을 직접 완성하는 것이 아니라는 점이다.

Module은 자신의 역할에 필요한 계산만 수행하고 결과를 반환한다.

이러한 구조를 유지하면 각각의 Module을 독립적으로 테스트할 수 있고, 필요한 경우 Module 내부의 구현을 변경하더라도 외부 구조에 미치는 영향을 최소화할 수 있다.


### Material Function as an Implementation Unit

앞에서는 어떤 기능을 나눌지 정했다. 이제는 그 기능을 Unreal의 Asset으로 어디에 담을지 결정한다. Index의 Master Material이 최종 조합 위치라면, Material Function은 그 조합에 사용할 계산 단위다.

Rendering Module은 논리적인 책임이고 Material Function은 그 계산을 Unreal에서 재사용하는 구현 단위이다. 하나의 Module이 여러 Function을 쓰거나 일부 결합 연산을 Master Material에서 수행할 수 있다. Rendering Stage/Pass와도 구분한다.

Material Function은 Material Graph 내부의 복잡한 연산을 하나의 기능 단위로 묶어 재사용할 수 있게 해준다.

예를 들어 다음과 같은 Module을 각각 독립적으로 만들 수 있다.

~~~text
MF_BaseLighting
MF_Shadow
MF_Specular
MF_RimLight
MF_MatCap
MF_Emission
~~~

각 Module은 자신이 담당하는 계산을 내부에 가지고 있으며, 외부에서는 정의된 Input과 Output을 통해서만 데이터를 주고받는다.

따라서 Master Material에서는 복잡한 내부 계산을 직접 볼 필요가 없다.

~~~text
M_ASF_Master

    ├── MF_BaseLighting
    ├── MF_Shadow
    ├── MF_Specular
    ├── MF_RimLight
    ├── MF_MatCap
    └── MF_Emission
~~~

Master Material은 각 Module을 조합하는 역할을 담당하고, 실제 계산은 각각의 Material Function 내부에서 수행한다.


### Modules and Master Material

ASF의 구조에서는 Master Material과 Material Function의 역할을 명확하게 구분한다.

Master Material은 현재 Material의 입력과 Module 결과를 결합한다. Renderer 전체의 Geometry/Shadow/Post Process Pass를 구성하는 것은 아니다.

Material Function은 개별 Rendering 기능을 구현한다.

이를 구조적으로 표현하면 다음과 같다.

~~~text
                     M_ASF_Master
                           │
          ┌────────────────┼────────────────┐
          │                │                │
          ▼                ▼                ▼
 MF_BaseLighting       MF_Shadow       MF_Specular
          │                │                │
          └────────────────┼────────────────┘
                           │
                           ▼
                       Composition
                           │
                           ▼
                      Final Output
~~~

Master Material이 Module 내부의 계산까지 직접 담당하지 않기 때문에 전체 구조를 한눈에 파악하기 쉬워진다.

반대로 각각의 Material Function은 자신의 기능을 독립적으로 확인할 수 있다.

이 관계는 ASF Architecture에서 가장 중요한 기본 원칙 중 하나다.


프로젝트 생성 화면인 Figure 8-3은 8.0절에서 다룬다. 이 절의 Architecture 관계는 아래 Module 간 Data Flow 설명을 기준으로 확인한다.


### Data Flow between Modules

Module을 분리한다고 해서 각각의 Module이 완전히 독립된 데이터를 사용하는 것은 아니다.

Module은 일부 중간 결과를 전달하고 공통 N/L/V를 공유한다. 서로 다른 Branch가 합류하므로 모든 Function을 직렬 연결하지 않는다.

따라서 ASF에서는 Module 사이의 데이터 흐름을 명확하게 정의해야 한다.

기본적인 흐름은 다음과 같이 구성된다.

아래 흐름은 하나의 직렬 줄이 아니라 여러 계산 Branch가 합류하는 구조다. Base Lighting과 Shadow는 앞 결과를 이어받고, Specular와 Rim은 필요한 방향에서 각자 Mask를 만든다. Master는 그 결과의 의미에 맞춰 곱하거나 더하거나 섞는다.

~~~text
Surface / Material / Light / View Inputs
  ├─ Base Lighting → Shadow application ─┐
  ├─ Specular Mask → Color × Intensity ──┤
  ├─ Rim Mask → Color × Intensity ───────┤→ Add → A
  ├─ MatCap Sample × Intensity ───────────────→ Lerp(A, MatCap, Blend)
  └─ Emission Result ─────────────────────────→ Add → Final Color
Actual intermediate outputs + Final Color → Debug selection
~~~

여기서 모든 Module이 반드시 이 순서를 그대로 따라야 하는 것은 아니다.

중요한 것은 각 Module이 어떤 데이터를 입력으로 받고 어떤 결과를 반환하는지 명확하게 정의하는 것이다.

예를 들어 Shadow Module은 Base Lighting의 결과를 입력으로 받아 그림자의 영향을 적용할 수 있다.

Specular Module은 Surface Normal, Light Direction, View Direction 등의 데이터를 이용해 별도의 Specular 결과를 계산할 수 있다.

즉, Module의 독립성은 기능을 완전히 고립시키는 것이 아니라 **데이터의 경계를 명확하게 정의하는 것**에 가깝다.


Project Settings 화면인 Figure 8-4는 8.0절에서 다룬다. Material Function과 Master Material의 관계는 이 절의 입출력 계약과 합성 설명을 기준으로 확인한다.


### Shared Inputs and Data Flow

ASF에서는 Shader의 계산을 단순히 노드의 연결 순서로만 이해하지 않는다.

각 단계에서 어떤 데이터가 들어오고, 어떤 의미의 결과가 만들어지는지를 기준으로 전체 흐름을 이해한다.

기본적인 Rendering Data Flow는 다음과 같다.

~~~text
Surface Data: Normal / Position / Tangent Basis
Material Data: Base Color / Parameters / Sampled Texture Values
Light Data: Light Direction / per-Light Visibility
View Data: Camera Direction / View Basis
    │
    └── Required inputs join at each Function
    ▼
Rendering Modules
    │
    ├── Base Lighting
    ├── Shadow
    ├── Specular
    ├── Rim Light
    └── 기타 Shading Modules
    │
    ▼
Composition
    │
    ▼
Final Material Output
~~~

이 구조를 사용하면 특정 결과가 이상하게 나타났을 때 어느 단계에서 문제가 발생했는지 추적하기 쉬워진다.

예를 들어 Base Lighting 자체가 잘못된 것인지, Shadow가 Lighting Result를 잘못 변경한 것인지, 또는 마지막 Composition 과정에서 문제가 발생한 것인지를 단계별로 확인할 수 있다.


Figure 8-5는 8.0절의 Asset 폴더 구조를 보여준다. 폴더 포함 관계를 Runtime Rendering Data Flow로 해석하지 않는다.


### Architecture Principles

ASF의 Architecture는 단순히 Material Function을 여러 개 사용하는 것이 목적이 아니다.

중요한 것은 **각 기능의 책임과 데이터 흐름을 분리하는 것**이다.

이를 몇 가지 원칙으로 정리할 수 있다.

#### One Responsibility per Module

Base Lighting은 Base Lighting을 담당하고, Shadow는 Shadow를 담당한다.

서로 다른 기능을 하나의 Module에 무리하게 포함하지 않는다.


#### Separate Implementation and Interface

Module 내부에서는 필요한 만큼 복잡한 계산을 수행할 수 있다.

하지만 외부에서는 명확하게 정의된 Input과 Output을 통해서만 데이터를 주고받는다.

~~~text
External
   │
   ▼
[ Input ]
   │
   ▼
[ Module Internal Processing ]
   │
   ▼
[ Output ]
   │
   ▼
External
~~~


#### Composition in the Master Material

Master Material은 모든 계산을 직접 수행하는 장소가 아니다.

각 Module의 결과를 적절한 순서와 방식으로 조합하여 최종 Material Output을 만드는 역할을 담당한다.


#### Independent Module Validation

각 Module은 Master Material에 연결하기 전에 자체적인 테스트가 가능해야 한다.

이렇게 하면 복잡한 전체 Shader를 한 번에 디버깅하지 않고 각각의 기능을 개별적으로 검증할 수 있다.

검증할 때는 먼저 입력 하나를 바꿨을 때 어떤 출력만 변해야 하는지 예상한다. 예를 들어 RimColor를 바꿀 때 방향에서 만든 RimMask까지 달라진다면, Mask 생성과 Color 합성의 책임이 섞였는지 확인할 수 있다. 이 예상과 실제 중간값을 비교하는 방식이 이후 Module 실습의 공통 기준이 된다.


#### Define Data Meaning First

노드를 연결하기 전에 어떤 데이터가 필요한지 먼저 정의한다.

예를 들어 Base Lighting에서는 다음과 같은 데이터가 필요하다.

~~~text
Base Color
Normal
Light Direction
~~~

그 다음 이 데이터를 이용하여 어떤 결과를 만들어야 하는지를 정의한다.

~~~text
Base Color (Vector3)
    ×
Lighting Factor (Scalar)
    ↓
Lighting Result (Vector3)
~~~

즉, ASF에서는 **노드를 먼저 배치하고 연결하는 것보다 데이터와 역할을 먼저 정의하는 것**을 중요하게 생각한다.


### From Architecture to Implementation

이제 ASF의 전체적인 구조가 정해졌다.

8.1에서는 아직 특정 Lighting Model이나 Shading Model을 구현하지 않았다.

대신 앞으로 구현될 기능을 다음과 같은 Module 구조로 분리할 수 있는 기반을 만들었다.

~~~text
ASF Shader
    │
    ├── Base Lighting
    ├── Shadow
    ├── Specular
    ├── Rim Light
    ├── MatCap
    └── Emission
~~~

이제부터는 각각의 Module이 실제로 어떤 데이터를 필요로 하고, 어떤 계산을 수행하며, 어떤 결과를 반환하는지를 구현한다.

첫 번째 Rendering Module은 **Base Lighting**이다.

Base Lighting에서는 표면이 현재 조명으로부터 얼마나 많은 직접적인 영향을 받고 있는지를 계산하는 것부터 시작한다.

그 과정에서 Surface Normal과 Light Direction의 관계를 사용하게 된다.

따라서 다음 절에서는 ASF의 첫 번째 실제 Rendering Module인 `MF_BaseLighting`을 구현하면서, 이러한 데이터가 실제 Shader 계산으로 어떻게 연결되는지 살펴본다.


### Key Takeaways

8.1에서는 ASF Shader의 전체 Architecture를 정의했다.

핵심은 하나의 거대한 Material Graph를 만드는 것이 아니라, Rendering 기능을 독립적인 Material Function Module로 분리하는 것이다.

전체 구조는 다음과 같이 정리할 수 있다.

~~~text
Material / Surface Data
          ↓
     Rendering Data
          ↓
   ┌──────┴──────┐
   │   Modules   │
   │             │
   │ BaseLighting│
   │ Shadow      │
   │ Specular    │
   │ Rim Light   │
   │ MatCap      │
   │ Emission    │
   └──────┬──────┘
          ↓
     Composition
          ↓
    Final Output
~~~

각 Module은 명확한 역할을 가지고 필요한 데이터를 입력받아 결과를 반환한다.

Master Material은 각각의 Module을 조합하고 최종 결과를 출력한다.

이 구조를 기반으로 이후의 모든 Rendering Module을 추가할 수 있다.

다음 절에서는 이 Architecture의 첫 번째 실제 구현으로 `MF_BaseLighting`을 만든다.

---

**Next → [8.2 Base Lighting](<./Chapter08.2_BaseLighting.md>)**
