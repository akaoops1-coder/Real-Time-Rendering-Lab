# Chapter 04 — Material Architecture

Rendering에서 최종적으로 보이는 Surface의 모습은 Geometry와 Light만으로 결정되지 않는다.

같은 Geometry에 같은 Light를 사용하더라도 Surface가 금속인지, 플라스틱인지, 거친 재질인지에 따라 결과는 크게 달라진다.

이 차이를 만드는 것이 `Material`이다.

Material은 단순히 Texture를 보여주는 기능이 아니다.

Rendering에서 Material은 Surface가 어떤 색을 가지고 있는지, Reflection이 얼마나 퍼지는지, 금속처럼 반응하는지, 어떤 방향을 향하는지와 같은 여러 Surface Property를 Shader에 제공한다.

이 값들은 Lighting 계산과 결합되어 최종적인 Appearance를 만든다.

즉,

`Geometry`

→ Surface의 형태와 위치

`Material`

→ Surface의 물리적·시각적 특성

`Lighting`

→ Surface와 Light의 관계

이 세 요소가 함께 작동해야 최종 Shading 결과가 만들어진다.

Chapter 03에서는 Lighting 계산에 필요한 Position, Normal, Light Direction, View Direction을 살펴봤다.

이번 Chapter에서는 그 Lighting 계산에 사용되는 또 다른 중요한 입력인 **Material Data가 어떻게 구성되고 Shader에 전달되는지**를 살펴본다.

특히 다음 흐름을 이해하는 것이 Chapter 04의 핵심이다.

`Material Input`

→ `Texture / Parameter`

→ `Surface Property`

→ `Shader`

→ `Lighting`

→ `Final Appearance`

---

## 4.1 What Is a Material?

Material을 처음 접하면 Texture와 비슷한 개념으로 생각하기 쉽다.

하지만 Texture와 Material은 같은 것이 아니다.

Texture는 Surface에 사용할 데이터를 저장하는 하나의 방법이고, Material은 그 데이터를 포함해 **Surface가 Rendering에서 어떻게 동작할지를 정의하는 전체 구조**다.

<img src="Figures/Chapter04/Fig4_01.png" width="90%">

### Same Geometry, Different Appearance

같은 Sphere Geometry에 같은 Light를 비춘다고 생각해보자.

Geometry와 Light가 완전히 같더라도 Material이 달라지면 결과는 전혀 다르게 보일 수 있다.

예를 들어 하나의 Sphere를 다음과 같이 표현할 수 있다.

- Plastic
- Metal
- Rough Surface
- Emissive Surface

Geometry는 모두 동일하다.

Light의 Direction과 Intensity도 동일하다.

달라지는 것은 Surface가 가진 Material Data다.

Plastic은 비교적 부드러운 Reflection과 Diffuse Color를 가질 수 있고, Metal은 주변 환경을 강하게 반사할 수 있다.

Rough Surface는 Reflection이 넓게 퍼져 Highlight가 흐려질 수 있으며, Emissive Surface는 외부 Light와 별개로 스스로 빛을 내는 것처럼 표현할 수 있다.

즉 최종 Appearance의 차이는 Geometry가 아니라 **Surface Property의 차이**에서 만들어진다.

---

### Material Describes Surface Properties

Material은 Surface가 어떤 특성을 가지고 있는지를 여러 값으로 표현한다.

대표적으로 다음과 같은 Material Input이 사용된다.

- `Base Color`
- `Roughness`
- `Metallic`
- `Normal`
- `Emissive`

각 Input은 서로 다른 Surface Property를 담당한다.

`Base Color`는 Surface의 기본적인 색 정보를 제공한다.

`Roughness`는 Reflection이 얼마나 넓게 퍼지는지를 조절한다.

`Metallic`은 Surface가 금속성 재질로 동작하는지를 결정하는 데 사용된다.

`Normal`은 Lighting 계산에 사용할 Surface 방향을 조정한다.

`Emissive`는 외부 Lighting과 별개로 Surface 자체에서 방출되는 Color 값을 제공한다.

이러한 값들은 각각 독립된 역할을 가지지만, 최종 Rendering에서는 서로 함께 사용된다.

---

### Material Is Not the Final Lighting

여기서 Material과 Lighting의 역할을 구분할 필요가 있다.

Material 자체가 최종 밝기를 직접 결정하는 것은 아니다.

Material은 우선 Shader에 Surface의 특성을 전달한다.

예를 들어 Roughness가 낮다고 해서 Surface가 무조건 밝아지는 것은 아니다.

낮은 Roughness는 Reflection이 더 집중되는 Surface 특성을 의미하고, 실제로 어떻게 보이는지는 Light Direction, View Direction, Reflection 환경과 같은 다른 Rendering Data와 함께 계산해야 한다.

즉 Material은,

**Surface가 Light에 어떻게 반응할 수 있는지를 정의하는 입력 데이터**

라고 이해하는 것이 좋다.

그리고 Lighting Model은 이 Material Data와 Lighting Data를 이용해 최종 Shading 결과를 계산한다.

---

### Material and Shader

Material과 Shader 역시 완전히 같은 의미는 아니다.

Shader는 GPU에서 실행되어 실제 Rendering 계산을 수행하는 Program이다.

Material은 그 Shader가 Surface를 계산할 때 사용할 Data와 설정을 제공한다.

개념적으로 보면 다음과 같다.

`Material Data`

→ `Shader`

→ `Lighting Calculation`

→ `Final Appearance`

하나의 Shader 구조를 여러 Material이 공유하면서 서로 다른 Parameter와 Texture를 사용할 수도 있다.

이 구조를 이용하면 같은 Rendering Logic을 유지하면서도 여러 종류의 Surface를 표현할 수 있다.

---

### Material as Data

Material을 이해할 때 중요한 관점은 Material을 하나의 완성된 이미지로 보는 것이 아니라 **Surface Data의 집합으로 보는 것**이다.

예를 들어 Character Material은 단순히 Character Texture 한 장을 사용하는 것이 아니다.

Surface 위치에 따라 서로 다른 값이 필요할 수 있다.

어떤 Pixel에서는 피부색이 필요하고, 다른 Pixel에서는 머리카락이나 의상의 색이 필요하다.

Roughness 역시 모든 Surface에서 같은 값일 필요가 없다.

Metallic, Normal, Emissive 같은 값도 Surface 위치마다 달라질 수 있다.

따라서 Material System은 이러한 값을 Constant, Parameter, Texture 등의 형태로 Shader에 전달한다.

그리고 Shader는 현재 Rendering하고 있는 Pixel에서 필요한 Material Data를 읽어 Lighting 계산에 사용한다.

---

### Material in the Rendering Flow

Chapter 03까지의 Lighting Data와 Material Data를 함께 보면 전체 구조를 다음과 같이 정리할 수 있다.

`Geometry`

→ Position / Normal / UV

`Material`

→ Base Color / Roughness / Metallic / Normal / Emissive

`Lighting`

→ Light Direction / View Direction / Light Color

이 Data들이 Shader에서 결합된다.

`Geometry Data`

+

`Material Data`

+

`Lighting Data`

→ `Shading Calculation`

→ `Final Appearance`

따라서 Material은 Texture 하나를 Surface에 붙이는 기능이 아니라,

**Surface가 Rendering 과정에서 어떤 특성을 가지는지를 Shader에 전달하는 데이터 구조**

라고 이해할 수 있다.

다음 Section에서는 Material이 사용하는 대표적인 Surface Property들을 하나씩 살펴보고, 각각의 값이 Rendering에서 어떤 역할을 하는지 정리한다.

---

## 4.2 Material Inputs and Surface Properties

앞 Section에서는 `Material`이 단순한 Texture가 아니라 Surface의 특성을 정의하는 Data Structure라는 점을 살펴봤다.

그렇다면 Material은 실제로 어떤 정보를 가지고 있어야 할까?

Surface의 색, 반사 특성, 금속성, 방향, 자체 발광 여부는 서로 다른 성질이다.

따라서 하나의 값만으로 Material 전체를 표현할 수는 없다.

Rendering에서는 이러한 Surface의 성질을 여러 개의 `Material Input`으로 나누어 표현한다.

각 Input은 서로 다른 역할을 담당하며, Shader는 이 값들을 함께 사용해 최종 Surface의 Appearance를 계산한다.

<img src="Figures/Chapter04/Fig4_02.png" width="90%">

### Material Input and Surface Property

`Material Input`은 Shader에 전달되는 값이다.

그리고 그 값은 Surface의 특정한 `Surface Property`를 표현한다.

예를 들어,

`Base Color`

는 Surface의 기본적인 색 정보를 제공하고,

`Roughness`

는 Reflection이 얼마나 넓게 퍼지는지를 결정하는 데 사용된다.

즉 Material Input은 단순한 숫자나 Texture가 아니라,

**Surface가 어떤 성질을 가지는지를 Shader에게 전달하기 위한 Data**

라고 볼 수 있다.

Material의 여러 Input은 서로 독립된 역할을 가지지만 최종 Rendering에서는 함께 사용된다.

---

### Base Color

`Base Color`는 Surface가 가지는 기본적인 Color 정보를 제공한다.

예를 들어 같은 Material 구조에서 Base Color만 변경하면 Surface를 빨간색, 파란색, 초록색 등으로 표현할 수 있다.

하지만 Base Color를 단순히 최종 Pixel Color라고 생각해서는 안 된다.

Base Color는 Lighting 계산에 사용되는 Material Data 중 하나다. Metallic workflow에서 dielectric의 Base Color는 주로 Diffuse 반사색을, metal의 Base Color는 주로 Specular 반사색을 제어한다. 하나의 입력이 항상 Diffuse Color와 같은 뜻은 아니다. 이 연결은 Chapter 05의 BRDF/F0에서 자세히 살펴본다.

따라서 같은 Base Color를 사용하더라도 Light의 방향과 밝기, Material의 다른 Property에 따라 화면에 나타나는 최종 Color는 달라질 수 있다.

즉,

**Base Color는 최종 밝기를 포함한 결과가 아니라 Surface가 가진 기본적인 색 정보다.**

이 값이 이후 Lighting Calculation과 결합되어 최종 Appearance를 만든다.

---

### Roughness

`Roughness`는 Surface의 미세한 구조가 얼마나 거친지를 나타내는 Property다.

Rendering 결과에서는 주로 Reflection과 Highlight의 형태에 영향을 준다.

Roughness가 낮으면 Surface가 비교적 매끄럽기 때문에 Reflection이 한 방향에 집중된다.

그 결과 Highlight가 작고 선명하게 나타날 수 있다.

반대로 Roughness가 높으면 Surface의 미세한 방향이 다양해지고 Reflection이 넓은 방향으로 퍼진다.

그 결과 Highlight는 넓고 흐릿하게 보인다.

개념적으로는 다음과 같이 생각할 수 있다.

`Low Roughness`

→ Reflection이 집중됨

→ Sharp Highlight

`High Roughness`

→ Reflection이 넓게 퍼짐

→ Broad / Soft Highlight

여기서 Roughness가 단순히 Surface를 밝거나 어둡게 만드는 값은 아니라는 점이 중요하다.

Roughness는 **빛이 반사되는 분포의 형태**를 바꾸는 Property다.

---

### Metallic

`Metallic`은 Surface가 Metal의 특성을 가지는지 판단하는 데 사용되는 Material Input이다.

일반적인 PBR Material에서는 크게 다음 두 종류의 Surface를 구분한다.

- `Dielectric`
- `Metal`

Plastic, Wood, Skin, Stone과 같은 대부분의 비금속 재질은 `Dielectric`에 해당한다.

Iron, Gold, Copper와 같은 금속 재질은 `Metal`에 해당한다.

Metallic 값은 일반적으로 다음과 같이 사용된다.

`0`

→ Dielectric

`1`

→ Metal

실제 Material에서는 Mask나 Transition 영역 때문에 중간값이 존재할 수도 있지만, 물리적인 Material의 기본적인 구분은 Metal과 Non-Metal에 가깝다.

Metallic이 변하면 단순히 Reflection의 양만 달라지는 것이 아니라 **Surface가 Light를 반사하는 방식 자체가 달라진다.**

이 차이는 이후 PBR과 BRDF를 다룰 때 더 자세히 살펴본다.

---

### Normal

`Normal` Input은 Lighting 계산에 사용할 Surface Direction을 조절하는 데 사용된다.

Chapter 03에서 살펴봤듯이 Surface Normal은 Light Direction과의 관계를 계산하는 기준 Vector다.

하지만 실제 Geometry의 Polygon만으로 모든 작은 Surface Detail을 표현하려면 매우 많은 Geometry가 필요하다.

대신 Normal Map과 같은 데이터를 사용하면 Geometry 자체를 변경하지 않고도 Pixel마다 Lighting에 사용할 Normal 방향을 바꿀 수 있다.

즉,

**Normal Input은 Geometry의 실제 Silhouette를 변경하는 것이 아니라 Lighting Calculation에서 사용하는 Surface Direction을 변경한다.**

그 결과 작은 홈, 주름, 돌기와 같은 Detail이 실제 Geometry가 존재하는 것처럼 보일 수 있다.

Normal Map의 구조와 Tangent Space에 대해서는 이후 관련 Section에서 더 자세히 다룬다.

---

### Emissive

`Emissive`는 Surface가 외부 Light와 별개로 스스로 빛을 내는 것처럼 보이도록 하는 Color 값을 제공한다.

일반적인 Surface는 Light를 받아야 밝게 보인다.

하지만 Emissive는 Lighting 결과와 별도로 Surface Color에 값을 추가할 수 있다.

예를 들어,

- LED
- Display
- Neon Sign
- Magic Effect

등을 표현할 때 사용할 수 있다.

여기서 주의할 점은 Emissive Material이 밝게 보인다고 해서 반드시 주변 Geometry를 실제로 비추는 것은 아니라는 점이다.

Emissive가 Scene Lighting에 영향을 주는지는 Rendering System과 Lighting 방식에 따라 달라질 수 있다.

따라서 Foundation 단계에서는 Emissive를,

**Surface 자체의 발광 Color를 제공하는 Material Input**

으로 이해하면 충분하다.

---

### Each Input Controls a Different Property

Material Input을 이해할 때 중요한 것은 각각의 값을 단순한 옵션 목록으로 외우는 것이 아니다.

각 Input은 서로 다른 Surface Property를 표현한다.

예를 들어,

`Base Color`

→ Surface Color

`Roughness`

→ Reflection Distribution

`Metallic`

→ Metal / Dielectric Response

`Normal`

→ Lighting에 사용할 Surface Direction

`Emissive`

→ Self-Illumination Color

와 같이 서로 다른 역할을 가진다.

이 값들은 따로 존재하지만 최종 Rendering에서는 동시에 사용된다.

즉 하나의 Material은 여러 Surface Property를 모아 하나의 Surface 특성을 정의한다.

---

### Material Values Are Not Always Constants

Material Input이 반드시 하나의 고정된 값일 필요는 없다.

예를 들어 Sphere 전체의 Roughness를 `0.5`로 설정하면 Surface 전체가 같은 Roughness를 가진다.

하지만 실제 Asset에서는 Surface 위치마다 다른 값이 필요한 경우가 많다.

예를 들어 Character Face에서는,

- Skin
- Lip
- Eyebrow
- Makeup
- Sweat

등의 영역이 서로 다른 Roughness를 가질 수 있다.

이 경우 하나의 Constant Value만으로는 Surface 전체의 차이를 표현할 수 없다.

그래서 Material Input은 다음과 같은 다양한 형태로 제공될 수 있다.

- Constant
- Parameter
- Texture
- 계산된 Shader Value

즉 `Roughness`는 하나의 특정 Texture를 의미하는 것이 아니라 **Shader가 현재 Surface에서 사용할 Roughness 값 자체**를 의미한다.

이 값이 어디에서 오는지는 Material 구조에 따라 달라질 수 있다.

---

### From Input to Final Appearance

Material Input은 각각 Surface의 다른 성질을 정의한다.

하지만 화면에 보이는 최종 결과는 어느 하나의 Input만으로 결정되지 않는다.

예를 들어,

`Base Color`

`Roughness`

`Metallic`

`Normal`

과 같은 Material Data가 Lighting Data와 함께 Shader에 전달된다.

이를 단순화하면 다음과 같이 볼 수 있다.

`Material Inputs`

→ `Surface Properties`

→ `Lighting Calculation`

→ `Final Appearance`

즉 Material Input은 최종 Color 그 자체가 아니라,

**Shader가 Surface를 어떻게 계산해야 하는지를 결정하기 위한 입력 데이터**다.

다음 Section에서는 이러한 Material Input 값이 Surface 위치마다 달라질 수 있도록 데이터를 저장하는 대표적인 방법인 `Texture`를 살펴본다.

---

## 4.3 Texture as Material Data

앞 Section에서는 Material Input이 Surface의 서로 다른 Property를 정의한다는 점을 살펴봤다.

하지만 실제 Asset에서는 하나의 값이 Surface 전체에 동일하게 적용되는 경우보다, 위치마다 다른 값이 필요한 경우가 훨씬 많다.

예를 들어 하나의 Character Face만 보더라도,

- 피부
- 입술
- 눈썹
- 메이크업
- 땀이나 유분이 많은 영역

은 서로 다른 Base Color와 Roughness를 가질 수 있다.

즉 Material은 Surface 전체에 하나의 값을 적용하는 것만으로는 충분하지 않다.

**Surface의 위치마다 서로 다른 Material Data를 제공할 수 있어야 한다.**

이 역할을 가장 대표적으로 담당하는 것이 `Texture`다.

<img src="Figures/Chapter04/Fig4_03.png" width="90%">

### Texture Is Data, Not Just an Image

Texture를 단순히 Surface에 붙이는 이미지라고 생각하기 쉽다.

하지만 Shader 관점에서 Texture는 이미지라기보다,

**2D 공간에 Material Data를 저장해 둔 Data Map**

에 가깝다.

Texture의 각 Pixel에는 특정 값이 저장되어 있다.

그 값은 Texture의 목적에 따라 전혀 다른 의미를 가질 수 있다.

예를 들어 Base Color Texture라면 각 Pixel의 RGB 값이 Surface Color를 나타낸다.

Roughness Texture라면 각 Pixel의 값은 현재 위치의 Roughness를 나타낸다.

Metallic Texture라면 해당 위치가 Metal인지 Dielectric인지에 대한 값을 저장할 수 있다.

즉 같은 Texture 형식을 사용하더라도,

**그 안에 저장된 값이 무엇을 의미하는지는 Material에서 어떻게 해석하는가에 따라 달라진다.**

---

### Base Color Texture

`Base Color Texture`는 Surface 위치마다 서로 다른 Color를 제공한다.

각 Pixel에는 일반적으로 RGB 값이 저장된다.

예를 들어 어떤 Pixel의 값이 다음과 같다고 하자.

`RGB = (0.42, 0.28, 0.24)`

Shader는 이 값을 현재 Surface 위치의 Base Color로 사용할 수 있다.

Texture 전체를 하나의 Color로 사용하는 것이 아니라,

**현재 Rendering 중인 Surface 위치에 대응하는 Texture Pixel의 값을 가져와 사용한다.**

따라서 하나의 Texture 안에서도 Surface 위치마다 전혀 다른 Base Color를 표현할 수 있다.

---

### Grayscale Data Textures

모든 Material Property가 RGB Color를 필요로 하는 것은 아니다.

`Roughness`나 `Metallic`처럼 하나의 Scalar 값만 필요한 Property도 많다.

이 경우 Texture의 한 Channel만으로도 값을 표현할 수 있다.

예를 들어 Roughness Texture에서,

`0`

은 매우 Smooth한 Surface,

`1`

은 매우 Rough한 Surface를 의미하도록 사용할 수 있다.

중간값인,

`0.5`

는 그 사이의 Roughness를 나타낸다.

화면에서는 흑백 이미지처럼 보이지만 Shader 입장에서는 중요한 것이 밝고 어두운 이미지 자체가 아니다.

각 Pixel에 저장된,

**0~1 범위의 Scalar Data**

가 중요하다.

Metallic Texture도 비슷한 방식으로 사용할 수 있다.

예를 들어,

`0`

→ Dielectric

`1`

→ Metal

처럼 해석할 수 있다.

---

### Normal Texture

`Normal Texture`는 다른 Material Texture와 조금 다른 성격을 가진다.

Base Color가 Color를 저장하고 Roughness가 Scalar 값을 저장한다면, Normal Texture는 Surface Direction을 표현하기 위한 Vector Data를 저장한다.

일반적인 Tangent Space Normal Map에서는 Normal의 X, Y, Z 성분을 RGB Channel에 Encoding한다.

그래서 Normal Map이 특유의 파란색이나 보라색 계열로 보인다.

하지만 Shader에서 중요한 것은 그 색 자체가 아니다.

RGB Channel에 저장된 값을 다시 Direction Vector로 해석해 Lighting에 사용할 Normal을 구성하는 것이다.

즉 Normal Texture 역시,

**이미지가 아니라 Surface Direction Data를 저장하는 Texture**

라고 볼 수 있다.

---

### Emissive Texture

`Emissive Texture`는 Surface 위치마다 서로 다른 Emissive Color를 제공한다.

예를 들어 벽돌 Material에서 Mortar나 특정 Pattern만 빛나게 만들고 싶다면, Emissive Texture를 이용해 해당 위치에만 밝은 값을 저장할 수 있다.

검은색 영역은 Emissive가 거의 없는 영역으로 사용하고,

밝은 영역은 더 강한 Emissive 값을 가지도록 설정할 수 있다.

이처럼 Texture를 사용하면 하나의 Material 안에서도 특정 영역만 선택적으로 다른 Property를 가지게 만들 수 있다.

---

### A Texture Provides a Value at the Current Surface Position

여기서 가장 중요한 개념이 하나 있다.

Shader가 Texture를 사용할 때 Texture 전체를 한 번에 Material Input으로 사용하는 것은 아니다.

현재 Rendering 중인 Pixel이 Surface의 어느 위치에 있는지를 기준으로 Texture를 Sample하고, 그 위치에 해당하는 값만 가져온다.

예를 들어 현재 Pixel의 UV가 다음과 같다고 하자.

`UV = (0.34, 0.62)`

Shader는 이 UV 위치에서 각각의 Texture를 Sample할 수 있다.

그 결과 예를 들어 다음과 같은 값을 얻을 수 있다.

`Base Color = (0.42, 0.28, 0.24)`

`Roughness = 0.65`

`Metallic = 0.0`

`Normal = encoded RGB value`

`Emissive = (0.0, 0.0, 0.0)`

즉 현재 Pixel 하나에 대해 필요한 Material Data가 각각의 Texture에서 읽혀 온다.

이 값들이 Shader의 Material Input으로 전달되고, 이후 Lighting 계산에 사용된다. Normal의 encoded RGB는 아직 방향이 아니므로 4.6의 Decode/Space 변환을 거친다. Mask는 Sample 결과의 필요한 Channel을 선택한 현재 Surface 위치의 Scalar이며 Texture 전체가 하나의 Scalar로 바뀌는 것이 아니다.

따라서 Texture를 이해할 때는,

**Texture 전체가 Material에 들어간다**

라고 생각하기보다,

**현재 Surface 위치에서 필요한 값을 Texture에서 Sample한다**

라고 이해하는 것이 더 정확하다.

---

### Texture Sampling

Texture에서 현재 Surface 위치의 값을 가져오는 과정을 `Texture Sampling`이라고 한다.

기본적인 흐름은 다음과 같다.

`Surface Position`

→ `UV`

→ `Texture Sample`

→ `Material Value`

실제 Shader에서는 UV Coordinate를 이용해 Texture의 특정 위치를 찾는다.

그리고 그 위치에 저장된 Pixel Data를 읽어온다.

이렇게 얻은 Sample 결과는 Texture 종류에 따라 서로 다른 Material Property로 해석된다.

예를 들어 같은 Sample 과정이라도,

Base Color Texture에서는 RGB Color,

Roughness Texture에서는 Scalar,

Normal Texture에서는 Direction Data

로 사용될 수 있다.

---

### One Texture Can Store Multiple Values

Texture는 여러 Channel을 가진다.

일반적인 RGBA Texture라면 다음 Channel을 사용할 수 있다.

- `R`
- `G`
- `B`
- `A`

Base Color처럼 RGB 전체가 필요한 경우도 있지만, Roughness나 Metallic처럼 하나의 Scalar만 필요한 데이터라면 Channel 하나만 사용해도 충분하다.

따라서 여러 Material Property를 하나의 Texture에 Packing할 수 있다.

예를 들어 다음과 같은 구성이 가능하다.

`R` → Ambient Occlusion

`G` → Roughness

`B` → Metallic

`A` → Mask 또는 다른 Scalar Data

이러한 구조를 흔히 `Channel Packing`이라고 한다.

Channel Packing을 사용하면 여러 개의 별도 Texture 대신 하나의 Texture에서 여러 Material Data를 가져올 수 있다.

이는 Memory Usage와 Texture Sampling Cost를 줄이는 데 도움이 될 수 있다.

다만 어떤 Data를 어느 Channel에 저장할지는 Project나 Engine Pipeline에 따라 달라질 수 있다.

---

### Texture Data Needs the Correct Interpretation

Texture에 저장된 숫자는 그 자체만으로 의미가 정해지는 것은 아니다.

같은 RGB 값이라도,

Base Color로 사용할 때와 Normal Data로 사용할 때는 전혀 다르게 해석된다.

또한 Color Texture와 Data Texture는 Color Space 처리 방식도 다를 수 있다.

예를 들어 Base Color는 일반적으로 사람이 보는 Color를 표현하기 위한 Texture지만, Roughness나 Metallic은 수치 데이터를 저장한다.

따라서 Texture를 Import하고 Material에 연결할 때는,

**이 Texture가 Color를 저장하는지, Material Data를 저장하는지**

를 구분해야 한다.

잘못된 방식으로 해석하면 Texture의 값 자체는 정상이어도 Material 결과가 달라질 수 있다.

Color Space와 Linear / sRGB 처리에 대해서는 이후 관련 Chapter에서 다시 연결한다.

---

### From Texture to Material

Texture가 Material에 사용되는 흐름을 정리하면 다음과 같다.

`Texture`

→ Material Property Data 저장

`UV`

→ 현재 Surface 위치 결정

`Texture Sample`

→ 현재 Pixel의 값 읽기

`Sampled Value`

→ Material Input에 전달

`Material Inputs`

→ Lighting Calculation

→ `Final Appearance`

즉 Texture는 완성된 Material 자체가 아니다.

Texture는 Material이 Surface 위치마다 서로 다른 Property를 가질 수 있도록 필요한 데이터를 제공한다.

Material은 이 Texture Data와 Parameter, Shader Logic을 함께 사용해 Surface의 최종 특성을 정의한다.

다음 Section에서는 Texture의 어느 위치에서 값을 가져올지를 결정하는 `UV`와 `Texture Sampling`의 관계를 조금 더 구체적으로 살펴본다.

---

## 4.4 UV and Texture Sampling

앞 Section에서는 Texture가 단순한 Image가 아니라 Surface 위치마다 다른 Material Data를 저장하는 Data Map이라는 점을 살펴봤다.

그렇다면 Shader는 3D Surface의 현재 위치에서 Texture의 어느 부분을 읽어야 하는지 어떻게 알 수 있을까?

이 역할을 하는 것이 `UV Coordinate`다.

`UV`는 3D Surface를 2D Texture Space에 대응시키는 좌표이며, Shader는 현재 Pixel의 UV를 이용해 Texture에서 필요한 값을 읽는다.

즉 Texture Sampling의 기본 흐름은 다음과 같다.

`3D Surface`

→ `UV Coordinate`

→ `Texture Sample`

→ `Material Data`

<img src="Figures/Chapter04/Fig4_04.png" width="90%">

**Figure 4-4 읽기 주의.** Character/UV 자료가 포함된 기존 합성 이미지는 원본 보존을 위해 유지한다. 그림의 선택 지점과 비교 이미지를 정량 검증 자료로 사용하지 않는다. 3번의 Vertex UV를 affine 보간하면 UV `(0.34, 0.62)`의 가중치는 왼쪽 아래 `0.35`, 오른쪽 아래 `0.03`, 위쪽 `0.62`이며, 표시점은 그림의 중앙이 아니라 왼쪽 위쪽 경계 가까이에 있어야 한다. 실제 Rasterization의 UV는 Perspective-correct 보간 조건을 확인한다. 7번의 Mip 선택은 거리만이 아니라 Texture footprint에 따른다. 8번 Normal `(0.52, 0.47, 1.00)`은 **Encoded RGB 예시**이며 Decode된 Unit Normal이 아니다. 9번의 대칭 Checker는 Wrap과 Mirror의 차이를 식별하기 어려우므로, 실제 비교에는 비대칭 패턴을 사용한다. 서문의 중복된 “값을”은 표기 오류다.

### UV Maps 3D Surface to 2D Texture Space

3D Mesh의 Surface는 3차원 공간에 존재한다.

하지만 대부분의 Texture는 2D Image 형태로 저장된다.

따라서 3D Surface의 각 위치가 2D Texture의 어느 위치에 대응되는지를 정의해야 한다.

이 대응 관계를 만드는 것이 `UV Mapping`이다.

Mesh의 Vertex에는 일반적으로 Position이나 Normal뿐 아니라 UV Coordinate도 저장할 수 있다.

예를 들어 어떤 Vertex의 UV가 다음과 같다고 하자.

`UV = (0.25, 0.75)`

이 값은 해당 Vertex가 Texture Space에서 어느 위치에 대응되는지를 나타낸다.

여기서 `U`와 `V`는 각각 2D Texture Space의 두 Axis다.

일반적으로,

- `U`는 가로 방향
- `V`는 세로 방향

을 나타낸다.

---

### UV Coordinate Range

기본적인 UV Coordinate는 일반적으로 `0~1` 범위를 사용한다.

예를 들어 Texture의 네 모서리는 개념적으로 다음과 같이 표현할 수 있다.

`(0, 0)`

`(1, 0)`

`(0, 1)`

`(1, 1)`

즉 UV는 Pixel 개수 자체를 직접 나타내는 것이 아니라 Texture 전체를 `0~1` 범위로 정규화한 좌표다.

이 방식의 장점은 Texture Resolution과 관계없이 같은 UV Coordinate를 사용할 수 있다는 점이다.

예를 들어,

`UV = (0.5, 0.5)`

는 Texture가 `1024 × 1024`이든 `4096 × 4096`이든 중앙 위치를 의미한다.

---

### UV Is Stored on the Mesh

UV는 Texture 안에 존재하는 정보가 아니다.

이 예제의 UV는 Mesh에 저장되는 Surface Attribute다. UV가 반드시 Mesh에서만 와야 하는 것은 아니다. Shader가 Position이나 방향으로 만든 좌표도 Sampling에 사용할 수 있으며, Chapter 08의 MatCap은 View Space Normal에서 UV를 만든다.

하나의 Vertex는 다음과 같은 여러 Data를 가질 수 있다.

- Position
- Normal
- Tangent
- UV
- Vertex Color

Rasterization 과정에서는 이러한 Vertex Attribute가 Triangle 내부의 Pixel 위치에 맞게 Interpolation된다.

따라서 Pixel Shader 단계에서는 현재 Pixel에 대응되는 UV Coordinate를 얻을 수 있다.

즉 흐름은 다음과 같다.

`Vertex UV`

→ `Rasterization`

→ `Interpolated UV`

→ `Current Pixel UV`

그리고 이 UV가 Texture Sampling에 사용된다.

---

### Texture Sampling

현재 Pixel의 UV를 얻었다면 Shader는 그 좌표를 이용해 Texture에서 값을 읽을 수 있다.

이 과정을 `Texture Sampling`이라고 한다.

예를 들어 현재 Pixel의 UV가,

`UV = (0.34, 0.62)`

라고 하자.

Base Color Texture를 이 UV에서 Sample하면 해당 위치의 Color를 얻을 수 있다.

예를 들어 결과가 다음과 같을 수 있다.

`Base Color = (0.82, 0.68, 0.61)`

같은 UV를 Roughness Texture에서 Sample하면,

`Roughness = 0.58`

과 같은 Scalar 값을 얻을 수 있다.

Normal Texture에서는 같은 위치에서 Normal Direction을 표현하는 RGB Data를 얻을 수 있다.

즉 UV는 동일하지만 어떤 Texture를 Sample하느냐에 따라 전혀 다른 Material Data를 얻는다.

---

### One UV Can Sample Multiple Textures

하나의 Surface Pixel에서는 보통 하나의 Texture만 사용하는 것이 아니다.

같은 UV Coordinate를 이용해 여러 Texture를 Sample할 수 있다.

예를 들어 현재 Pixel에서 다음 Texture를 각각 Sample한다고 하자.

- Base Color
- Roughness
- Metallic
- Normal
- Emissive

그러면 같은 Surface 위치에 대해 각각 다른 Material Property 값을 얻을 수 있다.

예를 들어,

`Base Color = (0.82, 0.68, 0.61)`

`Roughness = 0.58`

`Metallic = 0.0`

`Normal = encoded direction`

`Emissive = (0.0, 0.0, 0.0)`

처럼 하나의 Pixel에 필요한 Material Data를 구성할 수 있다.

이 값들은 이후 Material Input으로 전달되고 Lighting Calculation에 사용된다.

---

### Texture Sampling Does Not Always Read a Single Texel

Texture Sampling을 단순하게 생각하면 현재 UV와 가장 가까운 Texture Pixel 하나를 읽는 것처럼 보일 수 있다.

하지만 실제 Rendering에서는 항상 그렇게 동작하는 것은 아니다.

UV 위치가 정확히 하나의 Texel 중심에 놓이지 않는 경우가 많기 때문이다.

예를 들어 현재 UV가 네 개의 Texel 사이에 위치한다면, 하나의 Texel만 선택하면 Surface가 이동하거나 Camera가 움직일 때 Color가 갑자기 바뀌는 현상이 발생할 수 있다.

이를 줄이기 위해 주변 Texel의 값을 함께 사용해 중간값을 계산할 수 있다.

대표적인 방식이 `Bilinear Filtering`이다.

---

### Texel

Texel은 Texture Element의 줄임말로, Texture를 구성하는 가장 작은 단위다.

화면을 구성하는 최소 단위를 Pixel이라고 부른다면, Texture Image를 구성하는 최소 단위를 Texel이라고 부른다.

예를 들어 4096 × 4096 Texture는 가로 4096개, 세로 4096개의 Texel로 구성된다.

Shader가 Texture를 Sample할 때는 UV Coordinate를 이용해 Texture 안의 특정 Texel 또는 주변 Texel의 값을 읽는다.

---

### Bilinear Filtering

`Bilinear Filtering`은 현재 UV 주변의 네 개 Texel을 이용해 중간값을 계산한다.

개념적으로는,

`4 Neighboring Texels`

→ 위치에 따른 가중치 적용

→ `Interpolated Value`

의 과정으로 동작한다.

그 결과 Texel 경계가 그대로 드러나는 대신 더 부드러운 Texture 결과를 얻을 수 있다.

이 과정은 Base Color뿐 아니라 여러 Texture Sampling에 적용될 수 있다.

따라서 Shader가 Texture를 Sample한다는 것은 단순히 특정 Pixel 하나를 가져온다는 의미보다,

**Sampling Setting에 따라 주변 Texture Data를 이용해 현재 UV의 값을 계산하는 과정**

이라고 이해하는 것이 더 정확하다.

---

### Mipmapping

Texture Sampling에서 또 하나 중요한 개념이 `Mipmap`이다.

Camera에 가까운 Object는 많은 Screen Pixel을 차지하기 때문에 높은 해상도의 Texture Detail을 표현할 수 있다.

반대로 멀리 있는 Object는 화면에서 매우 작게 보인다.

이때 원본 고해상도 Texture를 그대로 Sampling하면 매우 많은 Texel이 적은 Screen Pixel에 압축되어 들어가게 된다.

그 결과 Shimmering이나 Aliasing 같은 문제가 발생할 수 있다.

이를 줄이기 위해 Texture의 해상도를 단계적으로 낮춘 여러 Version을 미리 만들어 둘 수 있다.

예를 들어,

`Mip 0` → Original Resolution

`Mip 1` → 1/2 Resolution

`Mip 2` → 1/4 Resolution

`Mip 3` → 1/8 Resolution

과 같은 구조다.

Mip 선택은 화면의 한 Pixel/sample 영역이 Texture에서 차지하는 footprint와 관련된다. 거리뿐 아니라 UV scale, Surface 기울기, 화면 해상도와 좌표 변화율도 영향을 준다. Object 전체의 화면 크기 하나로만 결정되는 것은 아니다.

이렇게 하면 멀리 있는 Object에서는 불필요하게 높은 Texture Detail을 읽지 않아도 되고, Aliasing도 줄일 수 있다.

---

### UV Outside the 0–1 Range

UV는 반드시 `0~1` 범위 안에만 있어야 하는 것은 아니다.

UV가 이 범위를 벗어났을 때 Texture를 어떻게 처리할지는 Sampling Setting에 따라 달라질 수 있다.

대표적인 방식은 다음과 같다.

- `Wrap`
- `Clamp`
- `Mirror`

`Wrap`은 Texture를 반복해서 사용한다.

예를 들어 U가 `1.2`라면 다시 Texture의 앞쪽 영역을 Sample하는 방식이다.

이 방식은 Tile Texture를 반복할 때 자주 사용된다.

`Clamp`는 범위를 벗어난 UV를 Texture의 가장자리 값으로 제한한다.

`Mirror`는 반복할 때 Texture 방향을 번갈아 뒤집어 사용할 수 있다.

즉 UV Coordinate와 Texture Sampling은 Texture 자체뿐 아니라 Sampler Setting과도 함께 동작한다.

---

### Texture Sampling Cost

Shader에서 Texture를 Sample하는 것은 무료 연산이 아니다.

각 Texture Sample은 GPU가 Texture Memory에서 Data를 가져와야 하는 작업이다.

따라서 Material이 많은 Texture를 사용하면 Texture Sampling Cost도 증가할 수 있다.

이 때문에 여러 Scalar Data를 하나의 Texture Channel에 Packing하거나, 필요하지 않은 Texture Sample을 줄이는 방식이 Optimization에 사용된다.

앞 Section에서 살펴본 `Channel Packing`이 실무에서 중요한 이유도 여기에 있다.

다만 Texture Sampling Cost는 Texture 개수만으로 단순하게 판단할 수 있는 문제는 아니며, Cache, Resolution, Filtering, Platform 등의 영향을 함께 받는다.

Optimization에 대해서는 Chapter 09에서 다시 다룬다.

---

### From UV to Material Data

Texture Sampling의 전체 흐름을 정리하면 다음과 같다.

`Mesh Vertex`

→ `UV Coordinate`

→ `Rasterization / Interpolation`

→ `Current Pixel UV`

→ `Texture Sampling`

→ `Sampled Material Value`

→ `Material Input`

→ `Lighting Calculation`

→ `Final Appearance`

즉 Texture는 Surface에 자동으로 붙는 Image가 아니다.

Mesh가 가진 UV를 통해 3D Surface와 2D Texture 사이의 대응 관계를 만들고, Shader가 현재 Pixel의 UV 위치에서 필요한 Data를 Sample함으로써 Material에 사용된다.

다음 Section에서는 이렇게 Sample된 Texture Data가 모두 같은 방식으로 해석되지 않는 이유와, `sRGB`와 `Linear Space`가 Material Data 처리에서 어떤 차이를 만드는지 살펴본다.

---

## 4.5 Color Space for Material Data

앞 Section에서는 Texture가 Surface의 위치마다 Material Data를 저장하고, Shader가 UV를 이용해 필요한 값을 Sample한다는 점을 살펴봤다.

그런데 Texture에서 읽은 RGB 값이 항상 그대로 Shader 계산에 사용되는 것은 아니다.

같은 `RGB = (0.5, 0.5, 0.5)`라도 어떤 Color Space로 해석하느냐에 따라 실제 계산에 사용되는 값은 달라질 수 있다.

이 차이를 이해하려면 먼저 Texture가 두 가지 성격의 Data를 저장할 수 있다는 점을 구분해야 한다.

- 사람이 보는 Color
- Shader 계산에 사용하는 Numeric Data

이 둘은 같은 RGB 형식을 사용하더라도 같은 방식으로 처리하면 안 된다.

<img src="Figures/Chapter04/Fig4_05.png" width="90%">

**Figure 4-5 검증 상태: 재촬영 필요.** 기존 이미지의 “Actual Rendering”과 Graph는 현재 설명의 검증 Evidence로 사용하지 않는다. sRGB Decode는 중간값 `0.5`를 더 작은 Linear 값으로 변환하므로, 그림의 `0.50 → 0.73`은 Decode 방향과 맞지 않는다. Roughness를 잘못 sRGB로 읽으면 의도보다 작은 값이 되어 Reflection이 더 날카로워질 수 있다. 자동 sRGB Decode 이후 수동 Decode를 다시 연결하지 않는다. `sRGB Off`는 모든 변환이 없다는 뜻이 아니라 sRGB transfer Decode를 하지 않는다는 뜻이다. 정확한 Sample 값과 동일 조건의 비교 Rendering, 실제 Texture 설정 및 Material Graph는 Unreal에서 다시 캡처해야 한다.

### What Is Color Space?

`Color Space`는 Color 값을 어떤 기준으로 저장하고 해석할지를 정의하는 체계다.

Material에서 가장 자주 접하게 되는 것은 다음 두 가지다.

- `sRGB`
- `Linear Space`

둘 다 RGB 값을 사용하지만, 값이 의미하는 밝기 관계가 다르다.

`Linear Space`에서는 값의 크기와 실제 Light Energy의 관계가 선형적이다.

예를 들어 개념적으로,

`0.5`

는

`1.0`

의 절반에 해당하는 값을 의미한다.

이 절에서 Linear와 sRGB를 대비할 때 주로 설명하는 것은 light-linear 값과 비선형 transfer encoding의 차이다. sRGB라는 Color Space는 transfer function뿐 아니라 primaries와 white point도 포함한다. Linear라는 말만으로 전체 색공간이 정해지는 것은 아니다.

사람의 눈은 물리적인 Light Intensity 변화에 완전히 선형적으로 반응하지 않는다.

따라서 Color를 저장하고 표시할 때는 Linear 값을 그대로 사용하는 것보다 `sRGB`와 같은 비선형 Encoding을 사용하는 것이 효율적이다.

---

### Why sRGB Exists

사람의 시각은 어두운 영역의 변화에는 비교적 민감하고, 매우 밝은 영역의 변화에는 상대적으로 덜 민감하다.

따라서 동일한 Bit Depth를 사용한다면 인간의 시각 특성에 맞게 값을 분배하는 편이 Color를 저장하는 데 유리하다.

`sRGB`는 이러한 특성을 고려해 Color 값을 비선형적으로 Encoding한다.

그 결과 Texture File에 저장된 sRGB Color 값은 실제 Lighting Calculation에 바로 사용할 Linear Light Value와는 다르다.

즉,

**sRGB는 Color를 저장하고 표시하기 위한 표현 방식이고, Linear Space는 Lighting을 계산하기 위한 수치 공간이라고 볼 수 있다.**

---

### Lighting Calculation Needs Linear Values

Lighting은 Light의 양을 수학적으로 계산하는 과정이다.

예를 들어 두 개의 Light Contribution을 더하거나, Surface에 도달한 Light의 비율을 곱하는 계산은 실제 값의 비례 관계가 유지되어야 한다.

따라서 Lighting Calculation은 일반적으로 `Linear Space`에서 수행된다.

만약 sRGB 값에 직접 Lighting 연산을 수행하면 값의 관계가 이미 비선형적으로 Encoding되어 있기 때문에 물리적인 Light 관계와 맞지 않는 결과가 발생할 수 있다.

그래서 Color Texture를 sRGB로 저장했더라도 Shader에서 Lighting Calculation에 사용하기 전에는 Linear 값으로 변환해야 한다.

개념적으로는 다음 흐름이다.

`sRGB Texture`

→ `Texture Sampling`

→ `sRGB Decode`

→ `Linear Color`

→ `Lighting Calculation`

---

### Color Texture and Data Texture

Material Texture는 크게 두 종류로 생각할 수 있다.

첫 번째는 실제 Color를 표현하기 위한 `Color Texture`다.

대표적인 예는 다음과 같다.

- Base Color
- Albedo
- Diffuse Color
- Emissive Color

일반적인 sRGB-encoded Color Texture는 sRGB로 해석해 Linear 값으로 Decode한다. 그러나 HDR/linear Color Texture처럼 이미 Linear로 저장된 자원도 있으므로, Color라는 이유만으로 항상 sRGB On을 적용하지 않는다.

두 번째는 Shader 계산에 사용할 숫자를 저장하는 `Data Texture`다.

대표적인 예는 다음과 같다.

- Roughness
- Metallic
- Ambient Occlusion
- Mask
- Height
- Normal

이 Texture들은 겉으로는 Grayscale 또는 RGB Image처럼 보이지만, 실제 목적은 Color를 표현하는 것이 아니다.

각 Pixel의 숫자 자체가 Material Parameter로 사용된다.

따라서 일반적으로 `Linear` Data로 읽어야 한다.

---

### Why Roughness Should Not Use sRGB

Roughness Texture의 Pixel 값이 다음과 같다고 하자.

`Roughness = 0.5`

이 값은 Shader가 그대로 `0.5`라는 Material Parameter로 사용해야 한다.

그런데 이 Texture를 실수로 sRGB Texture로 설정하면 Sampling 과정에서 sRGB Decode가 적용된다.

그러면 원래 저장했던 `0.5`가 Shader에서 다른 Linear 값으로 변환된다.

즉 Artist가 의도한 Roughness 값과 실제 Shader가 사용하는 값이 달라진다.

그 결과 Surface가 예상보다 더 매끄럽거나 더 거칠게 보일 수 있다.

중요한 점은,

**Texture Image 자체가 깨진 것이 아니라 Texture Data를 잘못 해석한 것**이라는 점이다.

이 원리는 Metallic, AO, Mask 등 다른 Data Texture에도 동일하게 적용된다.

---

### Normal Texture Is Also Data

Normal Map은 RGB Texture처럼 보이지만 Color Texture가 아니다.

R, G, B Channel에는 Color가 아니라 Surface Direction을 표현하기 위한 Vector Data가 저장되어 있다.

따라서 Normal Texture에 sRGB 변환이 적용되면 각 Channel의 값이 왜곡되고, Shader가 복원하는 Normal Direction도 잘못된다.

즉 Normal Map은 시각적으로 파란색 계열 Image처럼 보이지만,

**Shader 관점에서는 Color가 아니라 Direction Data다.**

따라서 일반적으로 Linear Data로 처리해야 한다.

Normal Map의 RGB 값이 실제 Surface Direction으로 어떻게 해석되는지는 다음 Section에서 자세히 살펴본다.

---

### What the Engine Does

실제 Engine에서는 Texture Import Setting에 따라 Color Space 처리를 자동으로 수행하는 경우가 많다.

예를 들어 Texture가 `sRGB On`으로 설정되어 있다면 Sampling 과정에서 sRGB 값을 Linear 값으로 Decode한 뒤 Shader에 전달할 수 있다.

개념적으로는 다음과 같다.

`sRGB Texture`

→ Sample

→ Automatic sRGB Decode

→ Linear Value

`sRGB Off`는 sRGB transfer Decode를 하지 않는다는 뜻이다. Filtering, compression, format conversion이나 Normal의 reconstruction/Decode까지 없어진다는 뜻은 아니다. Numeric Data의 의미와 실제 sampler output을 함께 확인한다.

`Linear Data Texture`

→ Sample

→ No sRGB Decode

→ Material Data

따라서 Material Graph에서는 단순히 Texture Sample 결과만 보는 것보다,

**해당 Texture가 어떤 Import Setting과 Color Space를 사용하고 있는지**

확인하는 것이 중요하다.

---

### Same RGB Value, Different Meaning

같은 숫자라고 해서 항상 같은 의미를 가지는 것은 아니다.

예를 들어 Texture에 다음 값이 저장되어 있다고 하자.

`RGB = (0.5, 0.5, 0.5)`

이 값을 Base Color로 사용한다면 sRGB Color로 해석한 뒤 Linear Color로 변환해 Lighting에 사용할 수 있다.

반면 Roughness Texture의 `0.5`는 그 자체가 Roughness Parameter이므로 별도의 sRGB Decode가 없어야 한다.

즉 Texture를 볼 때 중요한 질문은,

**이 Pixel이 어떤 색을 표현하는가?**

가 아니라,

**이 Pixel의 숫자가 무엇을 의미하는가?**

이다.

Color를 의미한다면 sRGB 처리가 필요할 수 있고,

Material Parameter를 의미한다면 일반적으로 Linear Data로 사용해야 한다.

---

### Common Material Texture Settings

Foundation 단계에서는 다음과 같이 기억하면 충분하다.

`Base Color / Albedo`

→ Color Data

→ 일반적으로 `sRGB On`

`Roughness`

→ Numeric Data

→ 일반적으로 `sRGB Off`

`Metallic`

→ Numeric Data

→ 일반적으로 `sRGB Off`

`Ambient Occlusion`

→ Numeric Data

→ 일반적으로 `sRGB Off`

`Mask`

→ Numeric Data

→ 일반적으로 `sRGB Off`

`Normal`

→ Direction Data

→ 일반적으로 `sRGB Off`

다만 실제 Texture Import Setting과 Format은 Engine이나 Project Pipeline에 따라 다를 수 있다.

중요한 것은 특정 Checkbox를 외우는 것이 아니라,

**Texture가 저장하는 Data의 의미에 따라 Color Space를 결정해야 한다는 원칙**이다.

---

### Color Space in the Material Flow

Texture Sampling까지 포함한 Material Data 흐름을 정리하면 다음과 같다.

Color Texture의 경우,

`sRGB Texture`

→ `UV`

→ `Texture Sampling`

→ `sRGB to Linear`

→ `Linear Material Color`

→ `Lighting Calculation`

Data Texture의 경우,

`Linear Data Texture`

→ `UV`

→ `Texture Sampling`

→ `Material Parameter`

→ `Lighting Calculation`

두 경우 모두 Texture Sampling을 사용하지만, Sample된 값을 해석하는 방식은 다르다.

---

### Why This Matters in Production

Color Space 문제는 Geometry나 UV처럼 화면에서 구조가 직접 보이는 문제가 아니기 때문에 원인을 찾기 어려운 경우가 많다.

Texture 자체는 정상적으로 보이고 Material 연결도 맞는데,

- Roughness가 예상과 다르게 보임
- Mask 경계가 이상하게 변함
- Normal Map 결과가 틀어짐
- Base Color가 지나치게 어둡거나 밝아짐

같은 문제가 발생할 수 있다.

이런 경우 Texture Data 자체뿐 아니라 `sRGB` 설정과 Color Space 해석이 올바른지도 확인해야 한다.

즉 Material Debugging에서는,

**Texture가 어떤 값을 저장하고 있는가**

와 함께,

**Engine이 그 값을 어떤 Color Space로 읽고 있는가**

를 확인해야 한다.

---

Color Space의 핵심은 특정 Gamma 수식을 외우는 것이 아니다.

**사람에게 보여주기 위한 Color와 Shader 계산에 사용할 Data는 같은 방식으로 해석해서는 안 된다.**

Color Texture는 일반적으로 sRGB로 저장하고 Shader에서 Linear로 변환해 계산하며, Roughness나 Metallic 같은 Data Texture는 저장된 Numeric Value가 왜곡되지 않도록 Linear Data로 사용한다.

다음 Section에서는 이러한 Data Texture 중에서도 조금 특별한 구조를 가지는 `Normal Map`이 RGB Channel에 Surface Direction을 어떻게 저장하고, Shader에서 이를 어떻게 Lighting Normal로 사용하는지 살펴본다.

---

## 4.6 Normal Mapping and Tangent Space

앞 Section에서는 Texture가 단순한 Color Image가 아니라 Shader가 사용할 Material Data를 저장하는 구조라는 점을 살펴봤다.

그중 `Normal Map`은 다른 Texture와 조금 다른 성격을 가진다.

Base Color Texture는 Color를 저장하고, Roughness Texture는 Scalar 값을 저장한다.

반면 Normal Map은 각 Texture Pixel에 **Surface Direction 정보**를 저장한다.

이 Direction을 Lighting 계산에 사용하면 실제 Geometry를 추가하지 않고도 작은 홈, 주름, 돌기 같은 Surface Detail을 표현할 수 있다.

즉 Normal Mapping의 핵심은 다음과 같다.

**Geometry는 그대로 두고, Lighting 계산에 사용하는 Normal Direction만 Pixel 단위로 바꾼다.**

<img src="Figures/Chapter04/Fig4_06.png" width="90%">

### Why Normal Mapping Works

Chapter 03에서 살펴봤듯이 Lighting은 Surface Normal과 Light Direction의 관계를 이용해 계산된다.

같은 위치라도 Normal Direction이 달라지면 Light를 바라보는 각도도 달라진다.

그 결과,

- Diffuse Lighting
- Specular Highlight
- Reflection

의 결과도 달라질 수 있다.

Normal Map은 바로 이 점을 이용한다.

실제 Polygon Geometry를 세밀하게 추가하지 않고도 Pixel마다 서로 다른 Normal을 사용하면, Shader는 Surface가 작은 굴곡을 가진 것처럼 Lighting을 계산한다.

따라서 화면에서는 실제 Geometry Detail이 존재하는 것처럼 보일 수 있다.

하지만 중요한 점이 하나 있다.

**Normal Map은 실제 Geometry를 변경하지 않는다.**

따라서 Silhouette 자체는 변하지 않는다.

Normal Map이 만드는 Detail은 어디까지나 Lighting 결과를 통해 보이는 Detail이다.

---

### Normal Map Does Not Store Height

Normal Map을 처음 보면 밝고 어두운 색의 패턴 때문에 Height Map과 비슷하게 생각하기 쉽다.

하지만 Normal Map의 밝은 값이 튀어나온 부분을 의미하고, 어두운 값이 들어간 부분을 의미하는 것은 아니다.

Normal Map은 Height를 직접 저장하지 않는다.

각 Pixel에는,

**현재 Surface Normal이 어느 방향으로 기울어져 있는가**

라는 Direction 정보가 저장된다.

즉 Height Map은,

`높고 낮음`

을 저장하는 Scalar Data이고,

Normal Map은,

`어느 방향을 향하는가`

를 저장하는 Vector Data다.

이 차이가 Normal Map을 이해하는 데 가장 중요하다.

---

### Tangent Space Basis

일반적인 Character나 Game Asset의 Normal Map은 대부분 `Tangent Space`를 기준으로 저장된다.

Tangent Space는 Surface의 각 위치에서 만들어지는 Local Coordinate System이라고 볼 수 있다.

기본 Axis는 다음 세 방향으로 구성된다.

- `T` : Tangent
- `B` : Bitangent
- `N` : Normal

`Tangent`는 일반적으로 UV의 `U` 방향과 연결된다.

`Bitangent`는 UV의 `V` 방향과 연결된다.

`Normal`은 Surface가 기본적으로 향하고 있는 방향이다.

즉 Tangent Space는 Surface의 한 점에서,

**옆 방향, 위아래 방향, 바깥쪽 방향**

을 정의하는 작은 Coordinate System이라고 이해할 수 있다.

Normal Map은 이 Coordinate System을 기준으로 현재 Pixel의 Normal Direction을 저장한다.

---

### RGB Channels Store Direction Components

Normal Map의 RGB Channel은 단순한 Color를 저장하는 것이 아니다.

각 Channel은 Tangent Space Normal의 방향 성분을 저장한다.

개념적으로는 다음과 같다.

`R`

→ Tangent 방향 성분

`G`

→ Bitangent 방향 성분

`B`

→ Normal 방향 성분

즉 Tangent Space Normal을,

`Nt = (x, y, z)`

라고 한다면,

각 성분이 RGB Channel에 대응한다.

`R = x`

`G = y`

`B = z`

다만 실제 Texture에는 일반적으로 `0~1` 범위의 값을 저장한다.

Normal Vector의 성분은 `-1~1` 범위를 사용하므로, 저장할 때는 값을 `0~1` 범위로 Encoding한다.

---

### Why a Flat Normal Map Looks Blue

완전히 평평한 Surface를 생각해보자.

이 경우 Normal은 Tangent나 Bitangent 방향으로 기울어지지 않고, 기본 Surface Normal 방향만 가리킨다.

Tangent Space에서는 다음과 같이 표현할 수 있다.

`N = (0, 0, 1)`

하지만 Texture에는 `-1~1` 범위를 직접 저장하지 않고 `0~1` 범위로 Encoding한다.

개념적으로 다음과 같이 변환할 수 있다.

`Encoded = Normal × 0.5 + 0.5`

그러면,

`(0, 0, 1)`

은,

`(0.5, 0.5, 1.0)`

이 된다.

8-bit RGB 값으로 보면 대략,

`(128, 128, 255)`

에 해당한다.

그래서 평평한 Tangent Space Normal Map은 일반적으로 파란색 또는 보라색 계열로 보인다.

즉 Normal Map이 파란색인 이유는 Surface가 파란색이기 때문이 아니라,

**기본 Normal Direction `(0, 0, 1)`을 RGB로 Encoding한 결과**다.

---

### R Channel and Tangent Direction

R Channel은 Normal이 Tangent 방향으로 얼마나 기울어져 있는지를 나타낸다.

예를 들어 Surface Normal이 `+Tangent` 방향으로 기울면 X 성분이 양수가 된다.

그러면 R 값은 `0.5`보다 밝아진다.

반대로 `-Tangent` 방향으로 기울면 X 성분이 음수가 되고, R 값은 `0.5`보다 어두워진다.

따라서 R Channel만 따로 보면 다음처럼 이해할 수 있다.

`R > 0.5`

→ `+Tangent` 방향으로 기울어짐

`R = 0.5`

→ Tangent 방향 기울기 없음

`R < 0.5`

→ `-Tangent` 방향으로 기울어짐

즉 R Channel의 밝고 어두움은 높낮이가 아니라 **Tangent 방향의 기울기**를 의미한다.

---

### G Channel and Bitangent Direction

G Channel은 같은 방식으로 Bitangent 방향의 성분을 저장한다.

`G > 0.5`

→ `+Bitangent` 방향으로 기울어짐

`G = 0.5`

→ Bitangent 방향 기울기 없음

`G < 0.5`

→ `-Bitangent` 방향으로 기울어짐

따라서 Surface의 위아래 방향으로 Normal이 기울어질수록 G Channel의 값이 변한다.

이 때문에 볼록한 Bump를 Normal Map으로 표현하면 R과 G Channel에서 서로 다른 방향성 있는 Gradient가 나타난다.

다시 말해 Normal Map의 밝고 어두운 패턴은,

**Surface가 어디에서 높고 낮은지를 직접 보여주는 것이 아니라, 각 위치에서 Normal이 어느 방향으로 기울어져 있는지를 보여주는 것**이다.

---

### B Channel and Surface Normal Direction

B Channel은 Tangent Space의 기본 Normal 방향 성분을 나타낸다.

대부분의 일반적인 Tangent Space Normal Map에서는 Surface Normal이 전체적으로 바깥쪽을 향하고 있기 때문에 B 값이 높은 경우가 많다.

그래서 Normal Map 전체가 파란색 계열로 보이는 것이다.

하지만 B Channel 역시 단순한 장식용 Color가 아니다.

현재 Pixel의 Normal이 기본 Surface Normal 방향을 얼마나 유지하고 있는지를 나타내는 Direction Component다.

---

### Decoding the Normal Map

Shader는 Texture에서 읽어온 RGB 값을 그대로 Direction Vector로 사용할 수 없다.

Texture에는 `0~1` 범위로 Encoding된 값이 저장되어 있기 때문이다.

따라서 Sample한 RGB 값을 다시 `-1~1` 범위로 변환해야 한다.

개념적으로 다음과 같이 표현할 수 있다.

`Normal = RGB × 2 - 1`

이 식은 0–1에 저장된 raw encoded RGB를 직접 읽는 개념 예제다. Engine의 Normal sampler가 이미 signed 방향을 반환하거나 압축된 채널에서 Normal을 복원했다면 이 식을 다시 적용하지 않는다. 정확한 sampler type·format·출력은 대상 Engine에서 확인한다(Needs Technical Verification).

예를 들어,

`RGB = (0.5, 0.5, 1.0)`

이라면,

`Normal = (0, 0, 1)`

이 된다.

즉 평평한 Surface Normal이 복원된다.

또한,

`RGB = (1.0, 0.5, 0.5)`

라면,

`Normal = (1, 0, 0)`

이 된다.

이는 Tangent 방향으로 완전히 기울어진 Normal을 의미한다.

중요한 것은 RGB Color를 보는 것이 아니라,

**RGB 값이 Decode된 이후 어떤 Direction Vector가 되는지를 이해하는 것**이다.

---

### From Tangent Space to Lighting Space

Normal Map에서 Decode한 Normal은 일반적으로 `Tangent Space` 기준이다.

하지만 실제 Lighting Calculation은 `World Space` 또는 `View Space`에서 이루어질 수 있다.

따라서 Tangent Space Normal을 Lighting에 사용하는 Coordinate Space로 변환해야 한다.

이때 사용하는 기준이 다음 세 Vector다.

- Tangent
- Bitangent
- Normal

이 세 Vector를 묶어 `TBN Basis`라고 부른다. Basis 자체의 Primary Explanation은 Chapter 02의 2.14 Tangent Space다. T/B/N이 목표 Lighting Space에 있는지, UV handedness와 orthonormal 조건이 맞는지 확인하고 변환 뒤에는 유효한 Unit Normal을 준비한다.

개념적인 흐름은 다음과 같다.

`Normal Map RGB`

→ `Tangent Space Normal`

→ `TBN Transform`

→ `World Space Normal`

→ `Lighting Calculation`

즉 Normal Map은 최종 Lighting Normal을 직접 World Space로 저장하는 것이 아니라, Surface마다 존재하는 Tangent Space 기준으로 Direction을 저장하고 필요할 때 변환해 사용한다.

이 방식 덕분에 같은 Normal Map을 Object가 회전하거나 움직여도 Surface 기준 Detail로 사용할 수 있다.

---

### Why Tangent Space Is Useful

만약 Normal Map에 World Space Direction을 직접 저장한다면 Object가 회전할 때 Texture에 저장된 Normal Direction과 실제 Surface 방향이 맞지 않게 된다.

Tangent Space Normal은 Surface 자체를 기준으로 저장되어 있기 때문에 Object Transform에 더 유연하게 대응할 수 있다.

즉,

`+X`

가 World의 고정된 X 방향을 의미하는 것이 아니라,

**현재 Surface의 Tangent 방향**

을 의미한다.

이 때문에 Character Animation이나 움직이는 Object에서도 Tangent Space Normal Map을 일반적으로 사용할 수 있다.

---

### DirectX and OpenGL Normal Maps

Normal Map을 다른 DCC Tool이나 Engine 사이에서 이동하다 보면 Surface의 굴곡이 반대로 보이는 경우가 있다.

대표적인 원인이 `G Channel`, 즉 Bitangent 방향 Convention의 차이다.

일반적으로 다음 두 방식이 자주 사용된다.

- `DirectX` Style
- `OpenGL` Style

두 방식의 대표적인 차이는 Y Direction, 즉 G Channel의 방향이다.

한 방식에서는 `+Y`를 사용하고, 다른 방식에서는 반대 방향을 사용하는 경우가 있다.

따라서 Normal Map Convention이 Engine과 맞지 않으면 G Channel을 반전해야 정상적인 Lighting 결과가 나올 수 있다.

여기서 중요한 것은 특정 Tool의 설정을 외우는 것이 아니라,

**Normal Map의 G Channel이 Bitangent Direction을 표현하기 때문에 Coordinate Convention이 다르면 방향도 반전될 수 있다는 원리**다.

---

### Normal Map Does Not Change the Silhouette

Normal Mapping의 한계도 분명하다.

Normal Map은 Lighting Normal만 변경한다.

실제 Vertex Position이나 Polygon Geometry는 변경하지 않는다.

따라서 다음과 같은 요소는 바뀌지 않는다.

- Silhouette
- 실제 Surface Depth
- Geometry Collision
- 실제 Shadow Geometry

Camera에 가까운 강한 돌출이나 큰 형태 변화를 Normal Map만으로 표현하면 Lighting은 Detail이 있는 것처럼 보이지만 Silhouette는 여전히 평평하게 남는다.

따라서 큰 형태는 Geometry로 만들고, 작은 Surface Detail은 Normal Map으로 표현하는 것이 일반적인 방식이다.

---

### Normal Map in the Material Flow

Normal Map이 실제 Lighting에 사용되는 흐름을 정리하면 다음과 같다.

`Normal Texture`

→ `UV`

→ `Texture Sampling`

→ `RGB Data`

→ `raw RGB인 경우 Decode; sampler-decoded 방향은 중복 Decode하지 않음`

→ `Tangent Space Normal`

→ `TBN Transform`

→ `Lighting Space Normal`

→ `Normalize`

→ `Lighting Calculation`

이 과정에서 중요한 것은 Normal Map이 Color Texture처럼 보이더라도 실제로는 Color를 저장하는 것이 아니라는 점이다.

**각 Pixel의 RGB 값은 Surface가 어느 방향을 향하도록 Lighting Normal을 변경할지를 나타내는 Vector Data다.**

따라서 Normal Map의 밝고 어두운 값은 단순한 높낮이가 아니라 Surface Direction의 변화이며, 이 Direction 변화가 Light와의 관계를 바꾸면서 화면에서는 실제 굴곡이 존재하는 것처럼 보이게 된다.

다음 Section에서는 이러한 Material Data를 고정된 값으로만 사용하는 것이 아니라 외부에서 조절하고 재사용할 수 있도록 만드는 `Material Parameter` 구조를 살펴본다.

---

## 4.7 Material Parameters and Material Instances

앞 Section까지는 Material이 Texture와 여러 Surface Property를 통해 Shader에 Data를 제공하는 구조를 살펴봤다.

하지만 Material 안의 모든 값을 고정된 값으로 작성하면 작은 수정 하나를 위해서도 Material Graph 자체를 다시 열고 수정해야 한다.

예를 들어 같은 Shader 구조를 사용하는 여러 Asset에서 다음 값만 다르게 사용하고 싶다고 하자.

- Base Color
- Roughness
- Metallic
- Texture
- UV Tiling

이때 Material Logic 자체를 매번 복사해서 새로 만드는 것은 비효율적이다.

이 문제를 해결하는 것이 `Material Parameter`와 `Material Instance`다.

`Material Parameter`는 Shader에서 사용할 값을 외부에서 조절할 수 있도록 만든 Input이고, `Material Instance`는 같은 Material 구조를 유지한 채 Parameter 값만 다르게 설정한 Material Variation이라고 볼 수 있다.

<img src="Figures/Chapter04/Fig4_07.png" width="90%">

**Figure 4-7의 Runtime 범위.** 기존 Graph/Instance 화면은 보존한다. 그림의 “실시간 값 변경”은 지원되는 비정적 Parameter와 적절한 Instance 사용에 한정한다. Static Switch와 Static Component Mask는 컴파일 시 Variant를 선택하는 Static Parameter이므로 일반적인 Runtime 값 변경과 구별한다. Parent Logic 재사용은 모든 Static 설정이 같은 Shader Variant를 유지한다는 뜻이 아니다. 화면의 정확한 Engine 버전과 Runtime 변경 경로가 검증된 자료라는 주장은 하지 않는다.

### Why Use Parameters?

Material Graph 안에 값을 직접 입력하면 해당 값은 Material Logic의 일부가 된다.

예를 들어 Roughness를 다음처럼 직접 지정했다고 하자.

`Roughness = 0.5`

이 값을 바꾸려면 Material Graph를 열고 값을 수정해야 한다.

반면 Roughness를 `Scalar Parameter`로 만들면 외부에서 값을 조절할 수 있다.

개념적으로는 다음과 같다.

`Hardcoded Value`

→ Material Graph 내부에 고정

`Parameter`

→ 외부에서 값 변경 가능

즉 Parameter의 목적은 단순히 값을 저장하는 것이 아니라,

**Material Logic과 조절 가능한 Data를 분리하는 것**

이다.

이렇게 하면 Shader 구조는 그대로 유지하면서도 여러 Asset에서 서로 다른 Material 값을 사용할 수 있다.

---

### Scalar Parameter

`Scalar Parameter`는 하나의 숫자 값을 전달한다.

대표적인 예는 다음과 같다.

- Roughness
- Metallic
- Normal Strength
- Emissive Intensity
- UV Tiling
- Mask Threshold

예를 들어 Roughness Parameter를 만든다면,

`Roughness = 0.2`

`Roughness = 0.6`

`Roughness = 0.9`

처럼 같은 Material 구조에서 서로 다른 Surface 특성을 만들 수 있다.

Scalar Parameter는 하나의 값을 사용하기 때문에 `0~1` 범위의 Material Property나 강도 조절에 특히 자주 사용된다.

---

### Vector Parameter

`Vector Parameter`는 여러 Component를 가진 값을 전달한다.

Material에서는 주로 Color 값을 조절하는 데 사용된다.

예를 들어 Base Color Tint를 Vector Parameter로 만들 수 있다.

`BaseColorTint = (R, G, B)`

또는 Alpha까지 포함하면,

`(R, G, B, A)`

형태로 사용할 수 있다.

이를 이용하면 Texture 자체를 수정하지 않고도 Material의 Color Variation을 만들 수 있다.

예를 들어 같은 Base Color Texture를 사용하면서,

- Red Variation
- Blue Variation
- Green Variation

처럼 서로 다른 Material을 만들 수 있다.

---

### Texture Parameter

`Texture Parameter`는 Material에서 사용할 Texture 자체를 외부에서 교체할 수 있도록 만든다.

예를 들어 하나의 Character Material 구조를 여러 Character가 공유한다고 하자.

Shader Logic은 같지만 각 Character가 사용하는 Base Color Texture와 Normal Map은 서로 다를 수 있다.

이 경우 Texture를 Parameter로 만들면 Parent Material 구조를 수정하지 않고도 다른 Texture를 지정할 수 있다.

즉,

`Same Shader Logic`

+

`Different Texture`

를 쉽게 구성할 수 있다.

Texture Parameter는 Asset Variation을 만들 때 매우 자주 사용된다.

---

### Static Switch Parameter

`Static Switch Parameter`는 단순히 숫자 값을 바꾸는 Parameter와 성격이 조금 다르다.

Shader Logic의 특정 Branch를 사용할지 여부를 선택하는 데 사용된다.

예를 들어 다음 기능을 선택적으로 사용할 수 있다.

- Detail Normal 사용
- Emissive 사용
- Clear Coat 사용
- Additional Mask 사용

개념적으로는,

`On`

→ 해당 Shader Logic 포함

`Off`

→ 해당 Shader Logic 제외

와 같은 구조다.

이러한 Parameter는 Shader의 기능 구성을 바꿀 수 있기 때문에 매우 유용하지만, 경우에 따라 Shader Permutation을 증가시킬 수 있다.

따라서 편리하다는 이유만으로 무분별하게 사용하는 것은 좋지 않다.

Static Switch는 compile-time 구성을 선택하며 일반 Scalar/Vector의 runtime 값 조절과 구분한다. Chapter 09의 9.5 Shader Cost에서 runtime 0과 static 선택의 비용 의미를 연결한다. 전체 permutation 관리 실험은 후속 범위다.

---

### Parameter in the Material Graph

Material Parameter는 Material Graph 안에서 Node 형태로 사용된다.

예를 들어 Base Color Tint를 조절하고 싶다면,

`Texture Sample`

과

`Vector Parameter`

를 Multiply한 뒤 Base Color에 연결할 수 있다.

개념적인 흐름은 다음과 같다.

`Base Color Texture + UV → Sampled Linear Color`

+

`BaseColorTint Parameter`

→ `Multiply`

→ `Base Color`

Roughness도 같은 방식으로 Scalar Parameter를 직접 연결하거나 다른 Data와 조합해서 사용할 수 있다.

즉 여기서 사용한 비정적 Scalar/Vector/Texture Parameter는 기존 Shader Logic에 값을 공급하며,

**Shader Logic이 사용할 Data를 외부에서 공급할 수 있도록 만드는 Interface**

라고 볼 수 있다.

---

### Parent Material and Material Instance

`Material Instance`를 이해하려면 먼저 `Parent Material`과의 관계를 보면 쉽다.

Parent Material에는 실제 Shader 구조가 존재한다.

예를 들어 Parent Material에는 다음과 같은 내용이 포함될 수 있다.

- Texture Sampling
- Parameter
- Mask Calculation
- Normal Processing
- Lighting 관련 Material Logic

그리고 이 Material을 기반으로 여러 Material Instance를 만들 수 있다.

예를 들어,

`M_Master`

라는 Parent Material에서 다음 Instance를 만들 수 있다.

`MI_Red`

`MI_Blue`

`MI_Green`

각 Material Instance는 Parent의 Architecture와 노출된 Interface를 재사용한다. 비정적 Parameter는 값을 Override하고, Static Parameter의 다른 조합은 별도 compiled Shader variant를 요구할 수 있다. 모든 Instance가 같은 compiled Shader를 무조건 공유하는 것은 아니다.

즉,

**Material Instance는 새로운 Shader를 처음부터 다시 만드는 것이 아니라 기존 Material 구조를 재사용하면서 Data만 다르게 설정하는 방식**이다.

---

### One Material, Many Variations

Material Instance를 사용하면 하나의 Material 구조에서 많은 Variation을 만들 수 있다.

예를 들어 하나의 Surface Material을 기반으로,

- Metal
- Painted Metal
- Dirty Metal
- Wood
- Stone

같은 Variation을 만들 수 있다.

물론 모든 재질이 완전히 같은 Shader 구조를 공유할 수 있는 것은 아니다.

하지만 구조가 비슷한 Material이라면 Parameter와 Texture를 바꾸는 것만으로 상당히 많은 Variation을 만들 수 있다.

예를 들어 같은 Parent Material에서 다음 값만 변경할 수 있다.

`Base Color Texture`

`Normal Texture`

`Roughness`

`Metallic`

`Color Tint`

`UV Tiling`

이 방식은 Material Graph 복제를 줄이고 Material 관리 구조를 단순하게 만든다.

---

### Real-Time Adjustment

Material Instance의 중요한 장점 중 하나는 Parameter를 빠르게 조절할 수 있다는 점이다.

비정적 Parameter는 Material Graph 구조를 매번 수정하지 않고 지원되는 Instance 경로에서 값을 바꾸어 결과를 확인할 수 있다. Static Switch의 variant 변경·컴파일은 이 runtime 조절과 다르다.

예를 들어 Artist는 다음 값을 조절하면서 Surface 결과를 확인할 수 있다.

- Roughness
- Base Color Tint
- Metallic
- Normal Strength
- Emissive Intensity
- UV Tiling

이 방식은 Look Development 과정에서 특히 효율적이다.

Material Logic을 수정하는 작업과 Surface Appearance를 조절하는 작업을 어느 정도 분리할 수 있기 때문이다.

---

### Material Instance Does Not Mean Completely Free Changes

Material Instance에서 모든 것을 자유롭게 변경할 수 있는 것은 아니다.

Instance는 Parent Material이 미리 Parameter로 노출한 값만 변경할 수 있다.

예를 들어 Parent Material에 Roughness Parameter가 없다면 Instance에서 Roughness를 직접 조절할 수 없다.

또한 Parent Material에 존재하지 않는 새로운 Shader Logic을 Material Instance에서 추가할 수도 없다.

즉 Parent Material은,

**어떤 기능을 제공할 것인가**

를 정의하고,

Material Instance는,

**그 기능을 어떤 값으로 사용할 것인가**

를 정의한다고 볼 수 있다.

---

### Why Material Architecture Matters

Material Parameter와 Material Instance는 단순히 편리한 기능이 아니다.

실제 Production에서는 많은 Asset이 존재하기 때문에 Material 구조를 어떻게 설계하느냐가 작업 효율에 큰 영향을 준다.

예를 들어 모든 Asset이 각각 별도의 Material Graph를 가지고 있다면,

- 수정 사항 반영이 어려워지고
- Material Logic이 중복되며
- Debugging이 복잡해지고
- 유지보수 비용이 증가한다.

반대로 공통된 구조를 Parent Material에 만들고 필요한 값만 Parameter로 노출하면 여러 Asset을 일관된 구조로 관리할 수 있다.

개념적으로는 다음과 같다.

`Shared Shader Logic`

→ `Parent Material`

→ `Material Parameters`

→ `Material Instances`

→ `Asset Variations`

이 구조는 Character, Environment, VFX 등 다양한 Asset Pipeline에서 활용할 수 있다.

---

### Parameter Design

Parameter가 많다고 해서 좋은 Material Architecture가 되는 것은 아니다.

모든 값을 Parameter로 노출하면 Material Instance가 지나치게 복잡해지고, Artist가 어떤 값을 조절해야 하는지 판단하기 어려워질 수 있다.

따라서 Parameter는 실제 Production에서 조절할 필요가 있는 값을 중심으로 설계하는 것이 좋다.

예를 들어 Character Material이라면 다음처럼 Group을 나눌 수 있다.

`Color`

- Base Color Tint
- Skin Tint

`Surface`

- Roughness
- Specular Intensity
- Normal Strength

`Texture`

- Base Color
- Normal
- Mask

`Tiling`

- UV Scale
- Detail Scale

이처럼 Parameter의 역할과 범위를 정리해 두면 Material Instance를 훨씬 쉽게 사용할 수 있다.

---

### Material Parameter Flow

Material Parameter가 최종 Rendering에 사용되는 흐름을 정리하면 다음과 같다.

`Parent Material`

→ Shader Logic 정의

`Material Parameter`

→ 조절 가능한 Input 정의

`Material Instance`

→ Parameter Override

`Material Data`

→ Shader Calculation

`Lighting`

→ `Final Appearance`

즉 Parent Material은 Rendering 구조를 정의하고, Material Instance는 그 구조에 사용할 Data를 결정한다.

이 구조를 이용하면 하나의 Material Logic을 여러 Asset에서 재사용하면서도 각각 다른 Surface Appearance를 만들 수 있다.

다음 Section에서는 Chapter 04에서 살펴본 Texture, UV, Color Space, Normal Map, Parameter가 실제 Material Pipeline에서 어떻게 하나의 흐름으로 연결되는지 정리한다.

---

## 4.8 Material Data Flow

앞 Section까지는 Material을 구성하는 여러 요소를 각각 나누어 살펴봤다.

- Material Input
- Texture
- UV
- Texture Sampling
- Color Space
- Normal Map
- Parameter
- Material Instance

이제 중요한 것은 이 요소들이 실제 Rendering 과정에서 어떻게 하나의 흐름으로 연결되는지를 이해하는 것이다.

Material은 하나의 Texture나 하나의 값으로 완성되지 않는다.

여러 종류의 Data가 Mesh와 Texture, Parameter에서 준비되고, Shader가 이를 해석한 뒤 Lighting Data와 결합하면서 최종 Surface Appearance가 만들어진다.

<img src="Figures/Chapter04/Fig4_08.png" width="90%">

### Material Starts with Mesh Data

Material 계산은 Texture만으로 시작하지 않는다.

먼저 Mesh에서 Surface를 계산하기 위한 기본 Data가 제공된다.

대표적으로 다음과 같은 값이 있다.

- Position
- Normal
- UV
- Tangent

`Position`은 현재 Surface가 어디에 있는지를 나타낸다.

`Normal`은 Surface가 어느 방향을 향하고 있는지를 나타낸다.

`UV`는 Texture의 어느 위치를 Sample할 것인지 결정하는 데 사용된다.

`Tangent`는 Normal Map을 Tangent Space에서 해석할 때 기준 Axis 중 하나로 사용된다.

즉 Mesh Data는 Material과 Lighting Calculation이 동작하기 위한 Surface 기준 정보를 제공한다.

---

### Texture and Parameter Data

Material의 Surface Property는 여러 종류의 Data에서 만들어질 수 있다.

예를 들어 Base Color는 Texture에서 가져올 수도 있고, Vector Parameter 하나로 지정할 수도 있다.

Roughness 역시 다음과 같이 다양한 방식으로 만들 수 있다.

- Constant
- Scalar Parameter
- Texture
- 여러 값의 계산 결과

즉 Material Input은 특정한 Data Source 하나를 의미하지 않는다.

중요한 것은 Shader가 최종적으로 사용할 Surface Property 값을 얻는 것이다.

예를 들어 Roughness가 필요하다면,

Texture에서 Sample했든,

Scalar Parameter에서 가져왔든,

Shader 계산으로 만들었든,

최종적으로는 현재 Pixel에서 사용할 Roughness 값 하나가 준비된다.

---

### Texture Sampling

Texture를 사용하는 경우 Shader는 현재 Pixel의 UV를 이용해 필요한 위치의 Data를 읽는다.

흐름은 다음과 같다.

`UV`

→ `Texture Sampling`

→ `Sampled Value`

예를 들어 같은 UV를 사용해 여러 Texture를 Sample하면 다음과 같은 값을 얻을 수 있다.

`Base Color`

`Roughness`

`Metallic`

`Normal`

`Emissive`

이 값들은 모두 같은 Surface 위치에 대응하지만 서로 다른 Surface Property를 표현한다.

---

### Color Space Interpretation

4.5의 입력 해석 규칙을 이 합류 지점에 적용한다. sRGB-encoded Color는 Linear로 Decode하고, Roughness/Metallic/Mask는 numeric 의미를 보존한다. 이미 Linear인 Color를 중복 Decode하지 않으며 Normal은 다음 절의 방향 복원 경로로 보낸다.

이 흐름은 Shader가 받는 값의 의미를 설명하는 논리적 순서다. 자동 Decode와 Filtering의 세부 실행 순서는 실제 format/sampler에 따라 확인해야 한다.

---

### Normal Map Has an Additional Path

Normal Map은 일반적인 Scalar Texture보다 처리 과정이 조금 더 길다.

Texture에서 Sample된 RGB 값은 바로 Lighting Normal로 사용할 수 없다.

raw encoded RGB를 읽었다면 방향으로 Decode한다. 4.6에서 설명한 것처럼 Engine sampler가 이미 Decode한 경우에는 그 signed 방향을 그대로 다음 단계에 전달한다.

`Normal Map`

→ `Texture Sampling`

→ `RGB`

→ `raw RGB인 경우 Decode; sampler-decoded 방향은 중복 Decode하지 않음`

→ `Tangent Space Normal`

그 다음 `TBN Basis`를 이용해 Lighting Calculation에 사용할 Coordinate Space로 변환한다.

`Tangent Space Normal`

→ `TBN Transform`

→ `World Space / View Space Normal`

그리고 최종적으로 Normalize한 뒤 Lighting에 사용한다.

즉 Normal Map은 단순한 Texture Input이 아니라,

**Texture Data를 Surface Direction으로 복원하는 과정**

을 포함한다.

---

### Material Inputs Are Assembled

Texture와 Parameter에서 필요한 값이 준비되면 Shader는 이 Data를 Material Input으로 구성한다.

예를 들어 다음과 같은 Surface Property가 준비될 수 있다.

- Base Color
- Roughness
- Metallic
- Normal
- Emissive
- Opacity
- Mask

각 값은 서로 다른 역할을 하지만 같은 Surface Pixel을 계산하기 위해 함께 사용된다.

이 단계에서 중요한 점은,

**Material Input은 Texture 자체가 아니라 Texture와 Parameter를 해석한 결과값이라는 것**이다.

예를 들어 Roughness Texture 전체가 Material Input으로 들어가는 것이 아니다.

현재 Pixel의 UV에서 Roughness Texture를 Sample한 결과값이 Roughness Input으로 사용된다.

Normal Map 역시 Texture 전체가 아니라 현재 Pixel에서 복원된 Normal Vector가 Lighting에 사용된다.

---

### Lighting Inputs Come from the Scene

Light에 반응하는 Material의 Appearance를 평가하려면 Material Data와 Lighting Data를 함께 사용한다. Unlit 출력이나 Emission처럼 Scene Light가 없어도 값이 나오는 경로는 구분한다.

Lighting과 관련된 Data도 필요하다.

Chapter 03에서 살펴본 대표적인 Lighting Input은 다음과 같다.

- `N` : Geometry/Normal Map에서 준비한 Surface Normal
- `L` : Surface→Light Direction
- `V` : Surface→Camera Direction
- Light Color
- Light Intensity

Material이 Surface의 성질을 정의한다면 Lighting Data는 그 Surface가 현재 어떤 Light와 Camera 관계에 있는지를 정의한다.

예를 들어 같은 Material이라도 Light Direction이나 View Direction이 달라지면 최종 Appearance는 달라질 수 있다.

---

### Material Data and Lighting Data Meet in the Shader

최종 Shading은 Material Data와 Lighting Data가 Shader 내부에서 함께 계산될 때 만들어진다.

개념적으로는 다음과 같다.

`Material Inputs`

+

`Lighting Inputs`

→ `Shading Calculation`

→ `Final Appearance`

예를 들어 Base Color는 Surface의 기본 Color를 제공한다.

Roughness는 Reflection Distribution에 영향을 준다.

Metallic은 Metal과 Dielectric의 반응 차이에 영향을 준다.

Normal은 Light와 Surface의 방향 관계를 계산하는 기준이 된다.

그리고 Light Direction, View Direction, Light Color 같은 Scene Data가 함께 사용된다.

즉 최종 Pixel Color는 어느 하나의 Texture나 Parameter가 직접 결정하는 것이 아니다.

**여러 Material Property와 Lighting Condition이 함께 계산된 결과**다.

---

### Material Instance Fits into the Same Flow

Material Instance를 사용한다고 해서 Material Data Flow 자체가 달라지는 것은 아니다.

Material Instance는 Parent의 Interface를 재사용한다. 비정적 값 override와 Static Parameter의 compiled variant 차이는 4.7에서 구분한 조건을 따른다.

즉,

`Parent Material`

→ Shader Logic

`Material Instance`

→ Parameter Override

의 관계다.

Instance에서 다른 Texture나 Roughness 값을 설정하더라도 최종적으로는 동일한 Material Input 구조로 전달된다.

따라서 Material Instance는 Data Flow를 바꾸기보다는,

**같은 Data Flow에 서로 다른 Input Data를 공급하는 구조**

라고 이해할 수 있다.

---

### Chapter 03 and Chapter 04 Connection

Chapter 03에서는 Lighting Calculation에 필요한 Direction과 Coordinate Space를 준비했다.

대표적으로 다음과 같은 Data를 살펴봤다.

`Position`

`Normal`

`Light Direction`

`View Direction`

`Dot Product`

Chapter 04에서는 Surface Property를 만드는 Material Data를 살펴봤다.

`Texture`

`UV`

`Color Space`

`Normal Map`

`Parameter`

`Material Instance`

이 두 흐름은 서로 독립적으로 끝나는 것이 아니다.

최종적으로 Shader에서 하나로 합쳐진다.

`Material Data`

+

`Lighting Data`

→ `Shading`

→ `Final Appearance`

즉 Chapter 03이,

**Surface와 Light의 관계를 계산하기 위한 Data를 준비하는 과정**

이었다면,

Chapter 04는,

**그 Surface가 어떤 성질을 가지는지를 정의하는 Data를 준비하는 과정**

이라고 볼 수 있다.

---

### Material Data Flow Summary

전체 흐름을 하나로 정리하면 다음과 같다.

~~~text
Mesh UV / Generated UV + Texture resource
    → Sampling and input interpretation → current Color / Scalar values
Parameters
    → current Material Property values

Mesh Normal / Tangent basis + sampled Normal direction
    → target Space Normal → Normalize → N

Surface Position + Scene Light / Camera data
    → L / V / Light data in the same Space

Material Properties + N / L / V / Light data
    → response evaluation and contribution composition
    → Surface Result → later display processing
~~~

Texture는 UV를 생성하는 이전 Stage가 아니라 Sampling의 별도 입력 자원이다. Parameter도 Texture 뒤를 반드시 통과하는 값이 아니다. N은 Geometry와 Normal Map 경로에서 준비되고, Scene Light/Camera 데이터와 계산 시점에 합류한다. Chapter 08의 Unlit+Emissive 구현은 이 교육용 응답을 명시적으로 합성하는 별도 예제이므로 Lit Material의 Property pin에 완성 Lighting을 그대로 넣는 것으로 해석하지 않는다.

Material Architecture의 핵심은 특정 Texture Format이나 Node를 외우는 것이 아니다.

**Surface를 표현하는 여러 Data가 어디에서 시작하고, 어떻게 해석되고, 어떤 형태로 Shader에 전달되는지를 이해하는 것**이 중요하다.

이 흐름을 이해하면 Material Graph가 복잡해지더라도 각 Node가 어떤 Data를 만들고 다음 단계에 무엇을 전달하는지 추적할 수 있다.

이것이 이후 Production Material, Character Material, Anime Shader와 같은 더 복잡한 Material Structure를 이해하는 기반이 된다.