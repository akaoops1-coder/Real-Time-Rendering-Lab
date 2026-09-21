# Chapter 03 — Lighting Mathematics

Rendering Pipeline은 최종적으로 각 Pixel이 어떤 색을 가져야 하는지를 계산하는 과정이다.

Geometry의 위치와 형태가 결정되고 Rasterization을 거쳐 covered sample과 Fragment 입력이 준비되면, Shader는 해당 Surface가 빛을 어떻게 받는지 계산한다. 이 계산 결과가 곧바로 최종 화면 Pixel과 같은 것은 아니다.

이때 Lighting은 단순히 Light의 밝기를 Surface에 더하는 과정이 아니다.

같은 Light 아래에서도 Surface가 Light를 정면으로 바라보는지, 비스듬히 놓여 있는지에 따라 받는 빛의 양이 달라진다. 또한 Specular Reflection처럼 Camera의 위치에 따라 결과가 달라지는 Lighting도 존재한다.

이러한 관계를 계산하기 위해 Rendering에서는 여러 Position과 Direction을 Vector로 표현한다.

대표적으로 다음과 같은 값들이 사용된다.

- Surface Position
- Surface Normal
- Light Direction
- View Direction

Chapter 02에서 살펴본 Coordinate System은 이러한 데이터를 **어떤 공간에서 표현할 것인가**에 대한 문제였다면, 이번 Chapter에서는 그 데이터를 이용해 **Surface와 Light의 관계를 어떻게 계산하는가**를 살펴본다.

특히 가장 기본적인 Lighting 계산인 `NdotL`을 중심으로 Vector, Normalize, Dot Product가 실제 Rendering에서 어떤 의미를 가지는지 이해하는 것이 이번 Chapter의 핵심이다.

---

## 3.1 Lighting Inputs

### From Geometry to Surface Data

Chapter 01의 1.3 Vertex and Vertex Attributes에서 Vertex는 Position만이 아니라 Normal, Tangent, UV 같은 Attribute를 함께 전달하는 단위였다. Triangle의 연결 관계는 Geometry를 정의하고, 그 위에서 보간되는 Attribute는 현재 Surface의 계산 입력을 준비한다.

| Data | Geometry / Surface 역할 | Lighting 연결 |
|---|---|---|
| Vertex Position / Triangle | 위치·연결·실제 Silhouette | 현재 Surface Position과 Geometric Normal |
| Vertex Normal | Artist 편집 또는 생성된 Shading 방향 | 보간·변환·Normalize 뒤 N |
| Tangent / UV | Surface basis와 Texture 좌표 | Chapter 02의 TBN 및 Chapter 04의 Sample/Normal Map |
| Texture Sample / Material Parameter | 현재 위치에서의 재질 데이터 | Chapter 04 이후 반사 응답의 입력 |

같은 Geometry라도 Shading Normal이나 Texture 데이터가 다르면 Lighting 결과가 달라질 수 있다. 이 Chapter는 이 입력들 가운데 방향 관계의 Primary Explanation을 제공하고, 저장·Sampling과 반사 모델은 Chapter 04–05로 연결한다.

### Required Lighting Data

Lighting을 계산하려면 먼저 현재 Pixel의 Surface가 어디에 있고, 어느 방향을 향하고 있으며, Light와 Camera가 어느 방향에 있는지를 알아야 한다.

가장 기본적으로 사용되는 입력은 다음 네 가지다.

### Surface Position

`Surface Position`은 현재 Lighting을 계산하고 있는 Surface의 위치다.

Rasterization 이후 Pixel Shader 단계에서는 각 Pixel이 Geometry 위의 어느 위치에 해당하는지를 알 수 있으며, 이 위치를 기준으로 Light나 Camera까지의 방향을 계산할 수 있다.

예를 들어 Point Light의 위치가 주어졌다면 다음과 같이 Surface에서 Light를 향하는 Vector를 구할 수 있다.

`Light Position - Surface Position`

즉, Surface Position은 단순한 좌표 정보에 그치지 않고 다른 Lighting Vector를 계산하기 위한 기준점 역할을 한다.

---

### Surface Normal

`Surface Normal`은 Surface가 어느 방향을 향하고 있는지를 나타내는 Direction Vector다.

Lighting에서는 Light가 Surface의 앞쪽에서 들어오는지, 옆에서 들어오는지, 또는 뒤쪽에 있는지를 판단할 때 Normal을 사용한다.

Surface가 Light를 정면으로 향할수록 더 많은 빛을 받고, Light와 평행에 가까워질수록 받는 빛의 양은 줄어든다.

이 관계를 수치로 계산하는 것이 이후 다룰 `Dot Product`다.

따라서 Normal은 Lighting 계산에서 가장 중요한 입력 중 하나다.

---

### Light Direction

`Light Direction`은 현재 Surface를 기준으로 Light가 어느 방향에 있는지를 나타낸다.

Lighting 계산에서는 일반적으로 Normal과 Light Direction의 관계를 비교하여 Surface가 Light를 얼마나 직접적으로 받고 있는지를 계산한다.

Light의 종류에 따라 Light Direction을 얻는 방식은 달라질 수 있다.

`Directional Light`처럼 모든 위치에서 동일한 방향을 사용하는 Light도 있고, `Point Light`처럼 Surface Position에 따라 방향이 달라지는 Light도 있다.

하지만 어떤 방식으로 얻었든 이후 Lighting 계산에서는 최종적으로 하나의 Direction Vector로 사용된다.

---

### View Direction

`View Direction`은 현재 Surface에서 Camera를 향하는 방향이다.

Diffuse Lighting처럼 Surface와 Light의 관계만으로 계산할 수 있는 경우에는 View Direction이 필요하지 않을 수 있다.

반면 Specular Reflection은 Surface가 Light를 받는 방향뿐 아니라 Camera가 어느 방향에 있는지에 따라서도 결과가 달라진다.

따라서 View Direction은 이후 Reflection과 Specular Lighting을 계산할 때 중요한 입력이 된다.

---

Lighting 계산에서 이 값들의 관계를 단순화하면 다음과 같이 볼 수 있다.

`Surface Position`

→ Light와 Camera의 상대적인 Direction 계산

`Surface Normal + Light Direction`

→ Surface가 Light를 얼마나 직접적으로 받는지 계산

`Surface Normal + Light Direction + View Direction`

→ Reflection과 Specular 관계 계산

이번 Chapter에서는 먼저 이 중 가장 기본적인 관계인 **Surface Normal과 Light Direction**부터 살펴본다.

---

## 3.2 Vector and Normalize

Lighting 계산에서는 여러 종류의 Direction Vector를 사용한다.

대표적으로 다음과 같은 값들이 있다.

- Surface Normal
- Light Direction
- View Direction

이 값들은 모두 특정한 **방향**을 표현하기 위해 사용된다.

하지만 Vector는 방향뿐 아니라 길이인 `Magnitude`도 함께 가진다.

예를 들어 다음 두 Vector를 생각해보자.

`A = (4, 2, 0)`

`B = (2, 1, 0)`

두 Vector는 서로 다른 길이를 가지지만 같은 방향을 가리킨다.

즉, Lighting에서 방향만 비교하려는 상황이라면 두 Vector는 사실상 동일한 Direction을 의미한다.

이때 사용하는 과정이 `Normalize`다.

<img src="Figures/Chapter03/Fig3_01.png" width="90%">

### Vector Magnitude

Vector의 길이는 `Magnitude`라고 부른다.

3D Vector `v = (x, y, z)`의 Magnitude는 다음과 같이 계산할 수 있다.

`|v| = √(x² + y² + z²)`

예를 들어,

`A = (4, 2, 0)`

이라면 Magnitude는 다음과 같다.

`|A| = √(4² + 2² + 0²)`

`|A| ≈ 4.47`

반면,

`B = (2, 1, 0)`

의 Magnitude는 약 `2.24`다.

두 Vector는 길이는 다르지만 방향은 같다.

---

### Normalize

`Normalize`는 Vector의 방향은 유지하면서 Magnitude를 `1`로 만드는 과정이다.

계산식은 다음과 같다.

`normalize(v) = v / |v|`, 단 `|v| > 0`.

Zero Vector에는 방향이 없으므로 이 식을 적용할 수 없다. 매우 작은 길이도 수치적으로 불안정할 수 있다. 구현에서는 유효한 입력을 보장하거나 길이 검사를 거쳐 명시한 fallback을 사용한다. 예를 들어 Point Light와 Surface Position이 완전히 같다면 방향을 임의로 Normalize하는 대신 그 특수 경우를 따로 처리한다.

Vector를 자신의 Magnitude로 나누면 길이가 `1`인 Vector가 된다.

이렇게 Magnitude가 `1`인 Vector를 `Unit Vector`라고 한다.

앞의 예시를 Normalize하면 다음과 같다.

`normalize(A) = (0.894, 0.447, 0)`

`normalize(B) = (0.894, 0.447, 0)`

두 Vector는 원래 Magnitude가 달랐지만 Normalize 이후에는 완전히 같은 값이 된다.

즉,

**Normalize는 Vector의 길이 정보를 제거하고 방향 정보만 남기는 과정이라고 볼 수 있다.**

---

### Why Normalize Matters in Lighting

Lighting에서는 대부분 Vector의 길이보다 **두 방향 사이의 관계**가 중요하다.

예를 들어 Surface가 Light를 얼마나 정면으로 바라보고 있는지를 계산할 때는 다음 두 Vector를 비교한다.

- Surface Normal
- Light Direction

이때 한 Vector의 Magnitude가 `1`이고 다른 Vector의 Magnitude가 `5`라면, 두 Vector의 방향이 같더라도 이후 계산 결과에는 길이의 영향이 포함될 수 있다.

그러면 우리가 원하는 **순수한 방향 관계**를 정확하게 비교할 수 없다.

따라서 Lighting 계산에서는 일반적으로 방향을 나타내는 Vector를 먼저 Normalize한 뒤 사용한다.

`N = normalize(Normal)`

`L = normalize(LightDirection)`

이렇게 두 Vector를 모두 Unit Vector로 만들어두면 이후 계산에서는 Vector의 길이가 아니라 방향 관계만 사용할 수 있다.

다음 Section에서는 이 두 Unit Vector를 이용해 Surface와 Light 사이의 각도 관계를 하나의 값으로 계산하는 `Dot Product`를 살펴본다.

---

## 3.3 Dot Product

Lighting을 계산할 때 가장 먼저 알고 싶은 것은 생각보다 단순하다.

**현재 Surface는 Light를 어느 정도 정면으로 바라보고 있는가?**

Surface가 Light를 정면으로 바라보고 있다면 많은 빛을 받을 수 있고, 옆으로 기울어질수록 직접 받는 빛은 줄어든다. 반대로 Light가 Surface의 뒤쪽에 있다면 해당 Light는 Surface 앞면의 Diffuse Lighting에 거의 기여하지 않는다.

사람은 그림을 보면 이 관계를 바로 이해할 수 있다.

하지만 Shader는 두 방향이 얼마나 비슷한지 눈으로 판단할 수 없다.

따라서 Rendering에서는 두 Direction Vector의 관계를 **하나의 Scalar 값으로 변환**해야 한다.

우리가 원하는 결과를 먼저 생각해보면 다음과 같다.

- 두 Vector가 같은 방향이면 큰 값
- 두 Vector가 수직이면 `0`
- 두 Vector가 반대 방향이면 음수

이처럼 **두 방향 사이의 관계를 하나의 값으로 표현하는 연산**이 `Dot Product`다.

<img src="Figures/Chapter03/Fig3_02.png" width="90%">

### Comparing Two Directions

Lighting에서는 대표적으로 다음 두 Direction Vector를 비교한다.

- `N` : Surface Normal
- `L` : Light Direction

두 Vector가 완전히 같은 방향을 가리킨다고 생각해보자.

이 경우 Surface는 Light를 정면으로 바라보고 있는 상태이며, 두 방향의 관계는 가장 강하다.

Dot Product의 결과는 다음과 같다.

`dot(N, L) = 1`

이번에는 Light Direction이 점점 옆으로 이동한다고 생각해보자.

두 Vector 사이의 각도가 커질수록 Dot Product 값은 점점 작아진다.

예를 들어,

`45° → 약 0.707`

`90° → 0`

이 된다.

두 Vector가 `90°`를 이루면 서로 수직이다.

이 상태에서는 Normal이 바라보는 방향과 Light Direction 사이에 더 이상 앞쪽 방향의 공통 성분이 없다고 볼 수 있다.

Light가 Surface 뒤쪽으로 넘어가면 Dot Product 값은 음수가 된다.

`135° → 약 -0.707`

그리고 완전히 반대 방향이라면,

`180° → -1`

이 된다.

즉 Dot Product를 사용하면 각도를 직접 저장하지 않아도 두 Direction이 얼마나 같은 방향을 향하고 있는지 하나의 값만으로 판단할 수 있다.

---

### Why Normalize Comes First

여기서 중요한 조건이 하나 있다.

우리가 비교하려는 것은 Vector의 **길이**가 아니라 **방향**이다.

만약 Light Direction의 길이가 매우 크고 Normal의 길이는 작다면, Vector의 Magnitude가 결과에 영향을 줄 수 있다.

그러면 같은 방향 관계를 가지고 있더라도 Vector의 길이에 따라 Dot Product 값이 달라질 수 있다.

그래서 앞 Section에서 살펴본 것처럼 Lighting에 사용하는 Direction Vector는 일반적으로 먼저 Normalize한다.

`N = normalize(N)`

`L = normalize(L)`

이렇게 두 Vector를 모두 Unit Vector로 만들면 Magnitude는 모두 `1`이 되고, Dot Product 결과는 순수하게 두 방향의 관계만 나타내게 된다.

즉,

**Normalize는 길이의 영향을 제거하고, Dot Product는 그 이후 방향의 관계를 비교한다.**

이 두 과정은 Lighting 계산에서 매우 자주 함께 사용된다.

---

### Connecting the Result to the Formula

지금까지는 Dot Product가 어떤 결과를 만들어야 하는지 먼저 살펴봤다.

이 관계를 수학적으로 표현하면 다음과 같다.

`dot(a, b) = a.x*b.x + a.y*b.y + a.z*b.z = |a||b|cosθ`

예를 들어 a=(1,0,0), b=(0.6,0.8,0)은 모두 Unit Vector이므로 dot(a,b)=0.6이다. 성분 계산과 방향 관계가 같은 값으로 연결된다.

여기서,

- `|a|`, `|b|`는 각 Vector의 Magnitude
- `θ`는 두 Vector 사이의 각도

를 의미한다.

두 Vector가 Normalize되어 있다면,

`|a| = 1`

`|b| = 1`

이므로 식은 다음과 같이 단순해진다.

`dot(a, b) = cosθ`

그래서 Dot Product는 두 Unit Vector 사이의 각도에 따라 다음과 같은 값을 만든다.

`0° → 1`

`90° → 0`

`180° → -1`

즉 앞에서 그림으로 확인한 방향 관계가 그대로 수식으로 연결된다.

---

### NdotL

Lighting에서는 Surface Normal과 Light Direction의 Dot Product를 매우 자주 사용한다.

이를 일반적으로 `NdotL`이라고 부른다.

`NdotL = dot(N, L)`

`NdotL`은 현재 Surface Normal과 Light Direction이 어느 정도 같은 방향을 향하고 있는지를 나타내는 값이다.

예를 들어,

`NdotL = 1`

이면 두 방향이 거의 완전히 일치하고,

`NdotL = 0`

이면 두 방향이 서로 수직이며,

`NdotL < 0`

이면 Light가 Surface Normal의 반대쪽에 있다는 의미다.

여기서 중요한 점은 아직 `NdotL`을 곧바로 "최종 밝기"라고 생각하지 않는 것이다.

`NdotL`은 먼저 **Surface와 Light의 방향 관계를 나타내는 기본 입력값**이다.

이 값을 실제 Diffuse Lighting에 어떻게 사용하는지는 이후 Lighting Model에서 다시 연결해서 살펴본다.

---

### Removing Negative Values

두 입력이 Unit Vector이면 Dot Product는 `-1`에서 `1` 범위다. 일반 Vector의 범위는 Magnitude에 따라 달라진다. 이 절의 N/L은 같은 Space의 Unit Vector로 준비한다.

하지만 Surface 앞면의 Lighting만 계산하려는 경우에는 음수 값이 필요하지 않은 경우가 많다.

Light가 Surface 뒤쪽에 있다면 해당 방향 관계를 음수 밝기로 사용할 이유가 없기 때문이다.

그래서 일반적인 Lighting 계산에서는 다음과 같이 음수를 `0`으로 제한한다.

`max(dot(N, L), 0)`

Shader에서는 다음과 같은 형태도 자주 사용한다.

`saturate(dot(N, L))`

`saturate()`는 값을 `0~1` 범위로 제한한다. Unit N/L에서는 max(dot(N,L),0)과 같은 방향 계수를 얻지만, 길이 조건을 지키지 않은 입력에서는 두 식이 같다고 보장할 수 없다. signed NdotL과 clamped diffuse factor는 별도 값이며 Chapter 07의 Remap에서도 구분한다.

예를 들어,

`dot(N, L) = -0.5`

라면,

`saturate(-0.5) = 0`

이 된다.

이렇게 하면 Surface 앞쪽에 있는 Light 방향만 이후 Lighting 계산에 사용할 수 있다.

---

Dot Product의 핵심은 복잡한 수식 자체가 아니다.

**두 Direction 사이의 관계를 Shader가 사용할 수 있는 하나의 값으로 바꾸는 것**이 핵심이다.

다음 Section에서는 이 계산에서 기준이 되는 `Surface Normal`이 실제 Rendering Pipeline에서 어떤 형태로 만들어지고 Pixel Lighting에 사용되는지 살펴본다.

---

## 3.4 Surface Normal

앞 Section에서 `NdotL`은 Surface Normal과 Light Direction의 관계를 비교하는 값이라고 설명했다.

그렇다면 여기서 가장 먼저 분명히 해야 할 것은 `Surface Normal`이 정확히 무엇인가 하는 점이다.

Surface Normal은 한마디로 말하면,

**현재 Surface가 어느 방향을 향하고 있는지를 나타내는 Direction Vector**다.

Lighting에서는 이 Normal을 기준으로 Light가 Surface의 앞쪽에 있는지, 옆에 있는지, 뒤쪽에 있는지를 판단한다.

<img src="Figures/Chapter03/Fig3_03.png" width="90%">

### What Is a Surface Normal?

어떤 Surface 위의 한 점을 생각해보자.

그 점에서 Surface에 수직으로 바깥쪽을 향하는 방향을 Vector로 표현하면 그것이 Surface Normal이다.

평평한 Plane이라면 모든 위치에서 거의 같은 방향의 Normal을 가질 수 있다.

반대로 Sphere처럼 휘어진 Surface에서는 위치마다 Surface가 향하는 방향이 다르기 때문에 Normal도 계속 달라진다.

예를 들어 Sphere의 위쪽에서는 Normal이 위를 향하고, 옆쪽에서는 바깥쪽을 향하며, 아래쪽에서는 아래 방향을 향한다.

즉, Normal은 단순히 Object 전체의 방향이 아니라 **Surface의 각 위치에서 로컬하게 정의되는 방향 정보**다.

Lighting은 바로 이 방향을 기준으로 계산된다.

---

### Face Normal

Polygon은 하나의 평면으로 볼 수 있다.

퇴화하지 않은 평면에는 서로 반대인 두 수직 방향이 있다. Face Normal은 Vertex의 Winding과 선택한 orientation convention에 따라 그중 한 방향을 정한다. 임의의 non-planar Polygon은 먼저 Triangle 단위로 해석해야 한다.

이 방향을 `Face Normal`이라고 한다.

Triangle을 예로 들면, 세 Vertex가 만드는 면을 기준으로 그 면에 수직인 방향을 계산할 수 있다.

개념적으로는 Triangle의 두 Edge Vector를 이용해 Cross Product를 수행하고, 그 결과를 Normalize해서 Face Normal을 얻을 수 있다.

~~~text
e1 = p1 - p0
e2 = p2 - p0
cross(e1,e2) = (e1.y*e2.z-e1.z*e2.y,
                e1.z*e2.x-e1.x*e2.z,
                e1.x*e2.y-e1.y*e2.x)
FaceNormal = normalize(cross(e1,e2))
~~~

이 식은 여기서 선언한 Cross Product convention을 사용한다. 두 Edge의 순서를 바꾸면 방향이 반대가 되므로 p0,p1,p2의 Winding과 front-face 규칙을 함께 확인한다. 세 점이 일직선이거나 중복되어 Cross가 0이면 유효한 Face Normal을 만들 수 없다.

여기서 중요한 것은 수식 자체를 외우는 것이 아니라,

**Face Normal은 Polygon 하나의 방향을 나타내는 값**이라는 점이다.

만약 Rendering이 각 Polygon의 Face Normal을 그대로 사용한다면 Polygon 경계가 그대로 드러나는 `Flat Shading` 형태로 보일 수 있다.

---

### Vertex Normal

실제 Character나 일반적인 Game Asset에서는 모든 Polygon이 각진 형태로 보이길 원하지 않는다.

곡면처럼 부드럽게 보이게 만들기 위해 각 Vertex에는 `Vertex Normal`을 저장할 수 있다.

Vertex Normal은 일반적으로 그 Vertex 주변의 여러 Face 방향을 바탕으로 계산되거나, DCC Tool에서 Artist가 조정한 방향 정보를 사용한다.

중요한 점은 Vertex Normal이 단순히 Geometry의 실제 면 방향과 항상 동일한 것은 아니라는 것이다.

같은 Polygon Mesh라도 Vertex Normal을 어떻게 설정하느냐에 따라 Surface가 부드럽게 보이기도 하고 각져 보이기도 한다.

즉,

**Geometry의 형태와 Shading에서 사용되는 방향 정보는 서로 완전히 같은 개념이 아니다.**

---

### Smooth Shading and Flat Shading

같은 Low Poly Sphere를 생각해보자.

각 Polygon이 자신의 Face Normal을 그대로 사용하면 Polygon마다 Lighting 방향이 달라지기 때문에 각 면의 경계가 눈에 띄게 된다.

이것이 `Flat Shading`이다.

반대로 Vertex Normal을 주변 Surface 흐름에 맞게 부드럽게 설정하면, 실제 Geometry는 그대로여도 Lighting 계산에 사용되는 방향이 자연스럽게 이어진다.

이 결과 Surface는 실제 Polygon 수보다 훨씬 부드러운 곡면처럼 보일 수 있다.

이것이 `Smooth Shading`의 기본 원리다.

여기서 중요한 점은,

**Smooth Shading이 Geometry 자체를 부드럽게 만드는 것은 아니라는 것**이다.

Silhouette는 여전히 실제 Polygon Geometry에 의해 결정된다.

달라지는 것은 각 위치에서 Lighting 계산에 사용하는 Normal 방향이다.

---

### From Vertex Normal to Pixel Normal

Rendering에서는 최종 Lighting을 Vertex 단위가 아니라 Pixel 단위로 계산하는 경우가 많다.

그렇다면 Vertex에 저장된 Normal은 어떻게 Pixel까지 전달될까?

Rasterization 과정에서 Triangle의 세 Vertex가 가진 Attribute는 Triangle 내부의 Pixel 위치에 맞게 Interpolation된다.

Normal 역시 이 과정에서 Pixel 위치별로 보간될 수 있다.

즉,

`Vertex Normal`

→ `Interpolation`

→ `Pixel에서 사용할 Normal`

의 흐름으로 전달된다.

그래서 Vertex 수가 적은 Mesh에서도 Pixel마다 조금씩 다른 Normal 방향을 사용할 수 있고, 그 결과 Surface가 부드럽게 보이게 된다.

다만 Interpolation된 Vector의 길이는 정확히 `1`이 아닐 수 있다.

따라서 Lighting 계산 전에 다시 Normalize해서 사용하는 경우가 많다.

`N = normalize(InterpolatedNormal)`

이 부분은 앞 Section에서 다룬 Normalize와 직접 연결된다.

---

### Normal as the Reference for Lighting

Lighting에서 Surface Normal이 중요한 이유는 이 Vector가 Surface 방향의 기준이 되기 때문이다.

예를 들어 Light Direction `L`과 Surface Normal `N`을 비교하면,

`dot(N, L)`

을 통해 Light가 Surface를 어느 정도 정면으로 비추고 있는지 판단할 수 있다.

즉,

- Position은 Surface가 **어디에 있는지**
- Normal은 Surface가 **어느 방향을 향하는지**

를 나타낸다.

그리고 Lighting은 이 두 정보와 Light Direction을 조합해서 계산된다.

Normal이 잘못되어 있으면 Geometry 자체는 정상이어도 Lighting 결과는 이상하게 보일 수 있다.

대표적으로 다음과 같은 문제가 발생할 수 있다.

- Surface가 의도와 반대로 밝아짐
- Polygon 경계가 예상보다 강하게 보임
- 곡면이 울퉁불퉁하게 보임
- 좌우 또는 특정 영역에서 Lighting 방향이 깨짐

따라서 Lighting 문제를 Debug할 때는 Material 값만 보는 것이 아니라 Normal 방향이 올바른지도 함께 확인해야 한다.

---

Surface Normal의 핵심은 복잡하지 않다.

**Normal은 Surface가 어느 방향을 향하고 있는지를 나타내고, Lighting은 그 방향을 기준으로 계산된다.**

그리고 Rendering Pipeline에서는 이 Normal이 Vertex에서 Pixel로 전달되고, Pixel마다 Light Direction과 비교되면서 최종 Lighting의 기초 데이터로 사용된다.

다음 3.5에서는 Normal을 필요한 Space로 변환하는 원리를 살펴본다. 준비된 N/L의 방향 계수가 Diffuse 응답과 결합되는 과정은 Chapter 05의 5.4 Lambert에서 연결한다.

---

## 3.5 Normal Transformation

앞 Section에서는 `Surface Normal`이 Surface가 어느 방향을 향하고 있는지를 나타내는 Direction Vector라는 점을 살펴봤다.

하지만 실제 Rendering에서는 Normal이 저장된 Coordinate Space와 Lighting을 계산하는 Coordinate Space가 항상 같지는 않다.

예를 들어 Mesh의 Vertex Normal은 일반적으로 `Local Space`를 기준으로 저장되지만, Lighting 계산은 `World Space`에서 이루어질 수 있다.

따라서 Normal 역시 Lighting 계산에 사용하기 전에 적절한 Coordinate Space로 변환해야 한다.

여기서 중요한 점은 다음과 같다.

**Normal은 Position과 같은 방식으로 변환할 수 있는 데이터가 아니다.**

<img src="Figures/Chapter03/Fig3_04.png" width="90%">

### Normal Starts in Local Space

Mesh의 Vertex Normal은 일반적으로 해당 Mesh의 `Local Space`를 기준으로 저장된다.

예를 들어 어떤 Surface의 Local Normal이 다음과 같다고 하자.

`Nlocal = (0, 0, 1)`

이 값은 World 전체를 기준으로 한 방향이 아니라, 해당 Mesh의 Local Coordinate System에서 Surface가 어느 방향을 향하고 있는지를 의미한다.

Object가 World에서 회전하면 Surface의 실제 방향 역시 함께 회전한다.

따라서 Lighting을 `World Space`에서 계산한다면 Normal 역시 `World Space` 기준의 방향으로 변환해야 한다.

즉,

`Local Normal`

→ `World Normal`

→ `Lighting Calculation`

과 같은 흐름이 필요하다.

---

### Position and Normal Are Different

Position과 Normal은 모두 Vector 형태로 표현되지만 역할은 다르다.

Position은 Surface가 **어디에 있는가**를 나타낸다.

Normal은 Surface가 **어느 방향을 향하고 있는가**를 나타낸다.

예를 들어 Object를 오른쪽으로 이동시키면 Position은 변한다.

하지만 단순히 Object가 이동했다고 해서 Surface가 바라보는 방향까지 바뀌는 것은 아니다.

따라서 Normal은 Translation의 영향을 받아서는 안 된다.

Rotation은 다르다.

Object가 회전하면 Surface의 방향도 함께 회전하기 때문에 Normal 역시 같은 회전을 따라가야 한다.

이처럼 Normal Transformation에서는 단순히 Position Transform을 그대로 사용하는 것이 아니라, **Surface 방향을 올바르게 유지하는 방식으로 Normal을 변환해야 한다.**

---

### Why Non-Uniform Scale Needs Special Handling

Normal Transformation에서 가장 주의해야 하는 경우가 `Non-Uniform Scale`이다.

예를 들어 Object에 다음과 같은 Scale이 적용되었다고 하자.

`Scale = (2, 1, 1)`

X축 방향으로만 Geometry가 두 배 늘어나는 Transform이다.

이때 중요한 것은,

**Non-Uniform Scale이 Surface Normal 자체를 잘못 만드는 것은 아니라는 점이다.**

변형된 Geometry에도 당연히 새로운 Surface 방향이 존재하고, 그 Surface에 수직인 올바른 Normal 역시 존재한다.

문제는 기존 Normal을 Position과 동일한 방식으로 Transform하려고 할 때 발생한다.

Geometry는 Non-Uniform Scale에 의해 형태와 Surface의 기울기가 변할 수 있다.

그런데 기존 Normal에 Geometry와 동일한 Scale Transform을 그대로 적용하면, 변환된 Vector가 새롭게 변형된 Surface에 더 이상 정확히 수직이 아닐 수 있다.

즉 문제는,

**Surface Normal이 수직이 아니게 되는 것이 아니라, 잘못된 방식으로 변환한 Normal이 실제 Surface Normal과 일치하지 않게 되는 것**이다.

---

### Why This Is Hard to Notice in DCC Tools

Blender, Maya와 같은 DCC Tool에서 Object에 Non-Uniform Scale을 적용해도 Normal이 Surface와 비스듬하게 어긋나는 모습을 직접 보는 경우는 드물다.

이는 DCC Tool이나 Rendering Engine이 Normal Transformation을 내부적으로 올바르게 처리하기 때문이다.

사용자가 보는 최종 결과에서는 이미 변형된 Geometry에 맞는 Normal이 사용되거나, Normal Transformation에 필요한 보정이 적용되어 있다.

따라서 실제 작업에서는,

`Non-Uniform Scale`

→ Normal이 갑자기 잘못됨

과 같은 현상을 직접 경험하지 않을 수 있다.

여기서 다루는 것은 DCC Tool에서 발생하는 사용상의 문제가 아니라,

**Renderer나 Shader 내부에서 Normal을 왜 Position과 다른 방식으로 처리해야 하는가**

에 대한 원리다.

---

### The Perpendicular Relationship Must Be Preserved

여기서는 먼저 Geometry의 Tangent와 Geometric Normal의 수직 관계로 변환 원리를 유도한다. 3.4의 Artist 조정·보간된 Shading Normal이 실제 Triangle Face Normal과 항상 같다는 뜻은 아니다.

Surface를 따라가는 방향을 `Tangent`라고 하면, 올바른 Normal `N`과 Tangent `T`는 서로 수직이어야 한다.

따라서 다음 관계가 성립한다.

`dot(T, N) = 0`

Non-Uniform Scale이 Geometry에 적용되면 Tangent 방향 역시 변할 수 있다.

따라서 새로운 Surface에 맞는 Normal 방향도 함께 달라져야 한다.

하지만 기존 Normal에 Geometry와 동일한 Transform을 그대로 적용하면 이 수직 관계가 깨질 수 있다.

Normal Transformation의 목적은 바로 이 관계를 보존하는 것이다.

**선형 변환에서 Geometric Normal을 올바르게 변환하면 변형된 Tangent와의 수직 관계를 보존할 수 있다.** Shading Normal은 별도의 방향장이라는 의미를 유지하면서 해당 Normal 변환 규약으로 준비한다.

---

### Inverse Transpose

Non-Uniform Scale이 포함된 Transform에서도 Normal과 Surface의 수직 관계를 유지하기 위해 사용하는 것이 `Inverse Transpose Matrix`다.

개념적으로는 다음과 같이 표현할 수 있다.

`Normal Matrix = transpose(inverse(M))`

여기서 M은 Local→World affine transform 중 Translation을 제외한 선형 3×3 부분이며, inverse가 존재한다고 가정한다. Scale이 0인 축처럼 singular한 변환에는 이 식을 그대로 사용할 수 없다. Chapter 02와 같은 Column Vector convention에서 Tangent는 M*T, Normal은 M^(-T)*N으로 변환한다.

수직인 원래 T와 N에 대해 dot(M*T, M^(-T)*N)=dot(T,N)=0이므로 이 변환을 선택한다. 전체 4×4 Position에 Translation을 포함해 Normal을 처리하는 것이 아니다.

그리고 Local Normal을 Normal Matrix로 변환한다.

`Nworld = NormalMatrix × Nlocal`

이후 Lighting에 사용하기 전에 다시 Normalize한다.

`Nworld = normalize(Nworld)`

여기서 중요한 것은 공식을 외우는 것이 아니다.

`Inverse Transpose`를 사용하는 이유는,

**변형된 Geometry의 Surface와 Normal 사이의 수직 관계를 유지하기 위해서다.**

즉 Position Transform은 Geometry를 실제 위치와 형태로 변환하고,

Normal Transform은 그 결과 만들어진 Surface가 어느 방향을 향하고 있는지를 올바르게 표현하도록 Normal을 변환한다.

---

### A Small Non-Uniform Scale Example

2D 단면에서 T=(1,1), N=(-1,1), M=diag(2,1)로 두면 원래 dot(T,N)=0이다. T'=(2,1)에 일반 Scale로 만든 Nwrong=(-2,1)을 비교하면 dot=-3이므로 수직이 아니다.

Inverse Transpose 결과는 (-0.5,1)이고 최종 Unit Normal은 (-1/√5,2/√5)≈(-0.447,0.894)이다. (-1,2)는 같은 방향을 나타내지만 Normalize 결과는 아니다. Figure 3-4의 수치 표기도 이 세 상태를 구분해서 읽어야 한다.

### Why Normalize Again?

Normal이 원래 Unit Vector였더라도 Transform 이후 Magnitude가 정확히 `1`이라고 보장할 수는 없다.

또한 Rasterization 과정에서 Vertex Normal이 Pixel 단위로 Interpolation되면 Vector의 길이가 다시 변할 수 있다.

따라서 Lighting 계산 직전에는 Normal을 다시 Normalize하는 것이 일반적이다.

`N = normalize(N)`

이 과정은 앞에서 살펴본 Dot Product와 직접 연결된다.

`dot(N, L)`을 이용해 순수한 방향 관계를 비교하려면 Normal과 Light Direction 모두 Unit Vector 상태여야 하기 때문이다.

---

### Normal and Light Must Use the Same Coordinate Space

Normal Transformation에서 또 하나 중요한 원칙은 Lighting에 사용하는 Vector들이 같은 Coordinate Space에 있어야 한다는 점이다.

예를 들어,

- Normal은 `World Space`
- Light Direction은 `View Space`

에 있다면 두 Vector를 직접 Dot Product하는 것은 의미가 없다.

각 Vector가 서로 다른 Coordinate System을 기준으로 표현되어 있기 때문이다.

따라서 Lighting을 `World Space`에서 계산한다면,

`Nworld`

`Lworld`

`Vworld`

처럼 Normal, Light Direction, View Direction을 모두 같은 Space로 맞춰야 한다.

이 원칙은 단순하지만 Lighting Debugging에서 자주 확인해야 하는 항목 중 하나다.

---

### Normal Transformation Flow

Normal이 실제 Lighting에 사용되기까지의 흐름을 정리하면 다음과 같다.

`Mesh Local Normal`

→ `Normal Transformation`

→ `World Space Normal`

→ `Rasterization / Interpolation`

→ `Normalize`

→ `Light Direction과 비교`

→ `dot(N, L)`

즉 Normal Transformation은 단순한 Coordinate Conversion이 아니다.

**Geometry가 Transform된 이후에도 Surface 방향을 올바르게 표현하도록 Normal을 준비하는 과정**이다.

특히 `Non-Uniform Scale`이 포함된 경우에는 Position과 Normal을 같은 방식으로 변환할 수 없으며, `Inverse Transpose`와 같은 Normal 전용 변환이 필요한 이유도 여기에 있다.

다음 3.6에서는 Surface Position과 Light/Camera 정보를 이용해 L과 V를 준비한다. Normal 변환과 방향 생성이 합류하는 전체 입력 흐름은 3.7에서 확인한다.

---

## 3.6 Light and View Direction

앞 Section까지는 `Surface Normal`을 기준으로 Surface가 어느 방향을 향하고 있는지를 살펴봤다.

이제 Lighting 계산을 위해서는 Surface와 Light, 그리고 Surface와 Camera 사이의 방향도 필요하다.

이때 사용하는 것이 `Light Direction`과 `View Direction`이다.

둘 다 Direction Vector이지만, 어떤 위치를 기준으로 계산하는지에 따라 만들어지는 방식이 다르다.

<img src="Figures/Chapter03/Fig3_05.png" width="90%">

### Light Direction

`Light Direction`은 현재 Surface를 기준으로 Light가 어느 방향에 있는지를 나타내는 Vector다.

Lighting에서는 Surface Normal과 Light Direction의 관계를 비교해 Surface가 Light를 어느 정도 정면으로 바라보고 있는지를 판단한다.

하지만 Light Direction은 모든 Light Type에서 같은 방식으로 만들어지는 것은 아니다.

Light가 위치를 가지는지, 특정 방향만 가지는지에 따라 계산 방식이 달라진다.

---

### Directional Light

`Directional Light`는 매우 멀리 있는 광원을 단순화한 형태로 볼 수 있다.

대표적인 예가 태양이다.

태양은 실제로는 위치를 가지지만 지구와의 거리가 매우 멀기 때문에, 작은 Scene 안에서는 들어오는 빛의 방향이 거의 평행하다고 볼 수 있다.

따라서 Directional Light에서는 Surface Position이 달라져도 기본적인 Light Direction은 동일하다.

즉 Scene의 여러 Surface에서 같은 Direction Vector를 사용할 수 있다.

이 점이 Point Light와 가장 큰 차이다.

Lighting 계산에서는 Engine이나 Shader의 Convention에 따라 Light가 진행하는 방향 또는 Surface에서 Light를 향하는 방향을 사용할 수 있으므로, 실제 구현에서는 Vector의 부호 방향을 확인해야 한다.

중요한 것은 어떤 Convention을 사용하든 이후 계산 전체에서 같은 기준을 유지하는 것이다.

---

### Point Light

`Point Light`는 World 안의 특정 Position에 존재하는 Light다.

따라서 Surface의 위치가 달라지면 Light를 바라보는 방향도 함께 달라진다.

이 경우 Light Direction은 Surface Position과 Light Position의 차이로 만들 수 있다.

`LightPosition - SurfacePosition`

이 Vector는 현재 Surface에서 Light Position을 향한다.

하지만 이 상태의 Vector에는 방향뿐 아니라 두 Position 사이의 거리도 포함되어 있다.

Lighting에서 방향만 비교하려면 Normalize가 필요하다.

`L = normalize(LightPosition - SurfacePosition)`

이렇게 하면 Surface에서 Light를 향하는 Unit Vector를 얻을 수 있다.

즉 Point Light에서는 각 Surface Position마다 서로 다른 Light Direction이 계산된다.

---

### Spot Light

`Spot Light` 역시 특정 Position을 가지기 때문에 기본적인 Light Direction 계산은 Point Light와 비슷하다.

`L = normalize(LightPosition - SurfacePosition)`

하지만 Spot Light에는 추가 조건이 있다.

Spot Light는 모든 방향으로 빛을 방출하는 것이 아니라 특정한 `Spot Direction`과 `Cone Angle`을 가진다.

따라서 Surface가 Light Position을 향하고 있다고 해서 항상 빛을 받는 것은 아니다.

먼저 Surface가 Spot Light의 조사 범위 안에 있는지를 판단해야 한다.

즉 Spot Light에서는 일반적으로 두 가지 관계를 함께 확인한다.

- Surface에서 Light를 향하는 Direction
- Surface가 Spot Cone 내부에 포함되는지 여부

이 때문에 Spot Light는 Point Light보다 추가적인 Direction 비교가 필요하다.

---

### View Direction

`View Direction`은 현재 Surface에서 Camera를 향하는 Direction Vector다.

Perspective Camera에서는 Camera Position과 Surface Position을 이용하면 다음과 같이 만들 수 있다. Orthographic Camera의 V는 평행한 viewing ray의 반대 방향으로 준비한다.

`CameraPosition - SurfacePosition`

이 Vector 역시 거리 정보를 포함하고 있으므로 Direction으로 사용하기 위해 Normalize한다.

`V = normalize(CameraPosition - SurfacePosition)`

따라서 View Direction은,

**현재 Surface에서 Camera가 어느 방향에 있는가**

를 나타낸다.

Diffuse Lighting처럼 Surface Normal과 Light Direction의 관계만으로 계산할 수 있는 경우에는 View Direction이 직접 필요하지 않을 수 있다.

하지만 Specular Reflection과 같이 Camera 위치에 따라 보이는 결과가 달라지는 Lighting에서는 View Direction이 매우 중요한 입력이 된다.

---

### Direction from Two Positions

Point Light의 Light Direction과 Perspective Camera의 View Direction에는 공통된 구조가 있다. Orthographic Camera에서는 Surface마다 Camera Position을 향하는 방향 대신 평행한 viewing ray의 반대 방향을 사용한다.

둘 다 두 Position의 차이에서 Direction Vector를 만든다.

Point Light에서는,

`LightPosition - SurfacePosition`

을 사용한다.

View Direction에서는,

`CameraPosition - SurfacePosition`

을 사용한다.

즉 일반적으로 어떤 위치 `A`에서 다른 위치 `B`를 향하는 Direction을 구하고 싶다면,

`B - A`

형태로 생각할 수 있다.

그 결과를 Normalize하면 두 위치 사이의 거리 정보는 제거되고 방향만 남는다.

`Direction = normalize(TargetPosition - StartPosition)`

이 패턴은 Lighting뿐 아니라 Rendering과 Graphics Programming 전반에서 매우 자주 사용된다.

---

### Vector Direction Convention

Direction Vector를 다룰 때는 한 가지 주의할 점이 있다.

`Light Direction`이라는 이름이 항상 정확히 같은 방향을 의미하는 것은 아니다.

이 Foundation에서는 **Surface → Light** 방향을 `L`로 정의하고, **Surface → Camera** 방향을 `V`로 정의한다. 실제 입사광의 진행 방향은 `-L`이다.

반면 다른 API나 Engine의 특정 데이터에서는 Light가 실제로 진행하는,

**Light → Surface**

방향을 제공할 수도 있다.

두 Vector는 서로 반대 방향이다.

`Surface → Light = -(Light → Surface)`

따라서 단순히 변수 이름만 보고 방향을 판단해서는 안 된다.

중요한 것은,

**현재 사용하고 있는 Vector가 어디에서 시작해서 어디를 향하는지를 명확히 확인하는 것**이다.

Dot Product에서는 이 방향이 반대가 되면 결과의 부호까지 달라질 수 있으므로 특히 중요하다.

---

### Same Coordinate Space

Light Direction과 View Direction 역시 Surface Normal과 같은 Coordinate Space에서 사용해야 한다.

예를 들어 Normal이 `World Space`에 있다면,

`Light Direction`

`View Direction`

역시 `World Space` 기준으로 준비해야 한다.

서로 다른 Coordinate Space의 Vector를 그대로 비교하면 방향 관계가 의미를 잃는다.

따라서 일반적인 Lighting 계산에서는 다음과 같이 같은 Space의 Vector를 준비한다.

`N = World Space Normal`

`L = World Space Light Direction`

`V = World Space View Direction`

그리고 필요한 경우 각각 Normalize한 뒤 Lighting 계산에 사용한다.

---

### Light and View Direction Flow

지금까지의 흐름을 정리하면 다음과 같다.

`Surface Position + Light Information`

→ `Light Direction`

`Surface Position + Camera Position`

→ `View Direction`

그리고 이 값들은 Surface Normal과 함께 이후 Lighting 계산의 기본 입력이 된다.

특히 다음과 같은 관계가 중요하다.

`Normal + Light Direction`

→ Surface와 Light의 방향 관계

`Normal + Light Direction + View Direction`

→ Reflection과 Specular 계산의 기초

즉 `Light Direction`과 `View Direction`은 단순히 Light와 Camera의 위치를 나타내는 값이 아니라, **현재 Surface를 기준으로 Lighting 관계를 계산하기 위해 만들어지는 Direction Vector**다.

다음 Section에서는 지금까지 준비한 Position, Normal, Light Direction, View Direction이 실제 Lighting 계산에서 어떤 흐름으로 연결되는지 정리한다.

---

## 3.7 Coordinate Space for Lighting

앞 Section까지는 Lighting 계산에 필요한 `Normal`, `Light Direction`, `View Direction`을 각각 어떻게 준비하는지 살펴봤다.

이제 중요한 것은 이 Vector들이 **서로 같은 Coordinate Space에 있어야 한다는 점**이다.

Chapter 02에서 정의한 Local/World/View Space는 같은 물리량을 서로 다른 기준축으로 표현한다. 이 절에서는 Space를 다시 정의하기보다 실제 N/L/V를 한 Lighting 계산에 합류시키고 오류를 진단하는 데 집중한다.

따라서 Lighting 계산에 사용하는 Vector가 서로 다른 Coordinate Space에 있다면, 같은 방향을 비교하는 것처럼 보여도 실제로는 올바른 관계를 계산할 수 없다.

<img src="Figures/Chapter03/Fig3_06.png" width="90%">

### Different Coordinate Spaces

Mesh의 Position과 Normal은 일반적으로 `Local Space`에서 시작한다.

이 값들은 Object Transform을 거쳐 `World Space`로 변환될 수 있다.

Camera를 기준으로 계산해야 하는 경우에는 다시 `View Space`로 변환할 수도 있다.

즉 같은 Surface Normal이라도,

`Nlocal`

`Nworld`

`Nview`

처럼 서로 다른 Coordinate Space에서 표현될 수 있다.

이들은 같은 Surface 방향을 나타내지만 값 자체는 서로 다를 수 있다.

왜냐하면 각 Vector가 기준으로 삼는 Coordinate Axis가 다르기 때문이다.

---

### Lighting Needs a Common Space

Lighting에서는 여러 Direction Vector 사이의 관계를 비교한다.

예를 들어,

`dot(N, L)`

을 계산하려면 `N`과 `L`이 같은 Coordinate Space에 있어야 한다.

Surface Normal이 `World Space`에 있는데 Light Direction이 `View Space`에 있다면, 두 Vector는 서로 다른 기준축을 사용하고 있다.

이 상태에서 Dot Product를 계산하면 수학적인 연산 자체는 가능하지만, 그 결과는 우리가 의도한 Surface와 Light 사이의 방향 관계를 의미하지 않는다.

따라서 Lighting 계산 전에는 관련 Vector들을 하나의 공통된 Coordinate Space로 맞춰야 한다.

예를 들어 `World Space`에서 Lighting을 계산한다면,

`N = World Space Normal`

`L = World Space Light Direction`

`V = World Space View Direction`

과 같이 준비한다.

---

### Why World Space Is Common

실시간 Rendering에서는 `World Space`를 Lighting 계산의 기준으로 사용하는 경우가 많다.

World Space에서는 Object, Light, Camera의 위치와 방향을 Scene 전체 기준으로 표현할 수 있기 때문이다.

예를 들어 Point Light의 Light Direction을 계산하려면 다음과 같은 정보가 필요하다.

`LightPosition`

`SurfacePosition`

두 Position이 모두 `World Space`에 있다면,

`LightPosition - SurfacePosition`

을 통해 바로 World Space의 Light Direction을 만들 수 있다.

Camera 역시 같은 방식으로 처리할 수 있다.

`CameraPosition - SurfacePosition`

따라서 World Space에서는 Scene 안의 Object, Light, Camera 관계를 직관적으로 연결하기 쉽다.

---

### Mixed Spaces Produce Wrong Results

잘못된 Lighting의 대표적인 원인 중 하나가 Coordinate Space가 서로 섞이는 경우다.

예를 들어 다음과 같은 상태를 생각해보자.

`N = World Space`

`L = View Space`

`V = World Space`

각 Vector는 개별적으로는 정상적인 Direction Vector일 수 있다.

하지만 서로 다른 Coordinate Space에 있기 때문에 방향 관계를 직접 비교할 수 없다.

특히 `dot(N, L)`처럼 두 Vector 사이의 각도를 이용하는 계산에서는 이 문제가 바로 결과에 영향을 준다.

Surface가 실제로 Light를 정면으로 바라보고 있어도 잘못된 값이 나오거나, Object 또는 Camera가 회전할 때 Lighting 방향이 이상하게 따라 움직이는 현상이 발생할 수 있다.

따라서 Lighting Debugging에서는 Vector의 값만 확인하는 것이 아니라,

**각 Vector가 어떤 Coordinate Space에 있는지**

를 함께 확인해야 한다.

---

### Transforming to a Common Space

일반적인 흐름에서는 Mesh Data를 Lighting 계산에 사용할 Coordinate Space로 변환한다.

예를 들어 Point Light와 Perspective Camera를 World Space에서 평가한다면 다음과 같은 흐름이 된다. Normal은 3.5의 Normal Matrix 경로, Position은 Chapter 02의 Model Transform 경로로 준비한다.

`Local Position`

→ `World Position`

`Local Normal`

→ `World Normal`

Light와 Camera의 정보 역시 같은 World Space 기준으로 준비한다.

이후 다음과 같은 Vector를 만들 수 있다.

`L = normalize(LightPositionWorld - SurfacePositionWorld)`

`V = normalize(CameraPositionWorld - SurfacePositionWorld)`

그리고 World Space Normal과 함께 Lighting 계산에 사용한다.

`Nworld`

`Lworld`

`Vworld`

이 상태가 되면 세 Vector가 모두 동일한 Coordinate System을 기준으로 표현되기 때문에 방향 관계를 올바르게 비교할 수 있다.

---

### View Space Lighting

Lighting을 반드시 World Space에서 계산해야 하는 것은 아니다.

모든 관련 데이터를 `View Space`로 변환한 뒤 Lighting을 계산하는 방식도 가능하다.

예를 들어,

`Nview`

`Lview`

`Vview`

를 모두 준비했다면 View Space에서도 동일한 Dot Product와 Lighting 계산을 수행할 수 있다.

즉 중요한 것은 특정 Coordinate Space 자체가 아니다.

**Lighting에 사용하는 모든 Vector가 같은 Coordinate Space에 있어야 한다는 것**이 핵심이다.

World Space를 사용하든 View Space를 사용하든 일관성만 유지된다면 올바른 계산이 가능하다.

---

### Coordinate Space and Debugging

Lighting 결과가 이상할 때는 다음과 같은 상황을 의심할 수 있다.

- Normal이 다른 Space에 존재함
- Light Direction이 다른 Space에 존재함
- View Direction이 다른 Space에 존재함
- Position과 Direction을 서로 다른 기준으로 계산함
- Transform 과정에서 Space Conversion이 누락됨

이런 문제는 Vector 자체만 보면 찾기 어려울 수 있다.

예를 들어 Normal Vector의 길이가 `1`이고 방향도 정상처럼 보여도, 다른 Coordinate Space에 있다면 Lighting에서는 잘못된 결과를 만들 수 있다.

따라서 Debugging에서는 항상 다음 질문을 함께 해야 한다.

**이 Vector는 어떤 Coordinate Space 기준인가?**

---

### Lighting Vector Flow

지금까지 Chapter 03에서 준비한 Lighting Data의 흐름을 정리하면 다음과 같다.

`Mesh Data`

→ `Position / Normal`

→ `Coordinate Space Transformation`

→ `Light Direction / View Direction 생성`

→ `Normalize`

→ `N`, `L`, `V`를 같은 Coordinate Space로 준비

→ `Dot Product`

→ `Lighting Calculation`

즉 Lighting 계산은 단순히 Vector 값을 준비하는 것에서 끝나지 않는다.

**각 Vector가 같은 기준에서 표현되고 있는지를 확인한 뒤 서로 비교해야 한다.**

이 원칙이 지켜져야 이후 Diffuse, Specular, Reflection 같은 Lighting 계산도 올바르게 동작한다.

### Basic Verification

- Unit N=(0,0,1)에 L=(0,0,1), (1,0,0), (0,0,-1)을 넣으면 signed NdotL은 1,0,-1이고 clamped factor는 1,0,0이다.
- Object와 Light를 고정하고 Camera만 회전할 때 World Space NdotL은 변하지 않아야 한다. View-dependent V는 달라질 수 있으므로 Specular/Rim의 변화와 구분한다.
- 3.5의 Non-uniform Scale 예제에서는 transformed Tangent와 올바른 Normal의 Dot가 0인지, Normalize 뒤 길이가 1인지 확인한다.
- 정상적인 화면만 보지 말고 입력의 Space·길이·부호를 확인한다. RGB로 표시한 Direction은 음수 표현과 표시 변환의 영향을 받으므로 값 확인과 화면 관찰을 구분한다.

이 기본 확인은 Chapter 08의 Module 입력 검증으로 이어진다. 다음 Chapter 04에서는 이렇게 준비한 Surface에 Texture Sample과 Material Parameter가 어떻게 합류하는지 살펴본다.