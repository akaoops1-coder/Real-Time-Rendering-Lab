# Chapter 05 — Reflection and BRDF

---

**Part I — Reflection Models**

같은 Light 아래에서 거울, 종이, 금속이 서로 다른 모습으로 보이는 이유를 알아본다. 먼저 익숙한 관찰을 방향 관계로 바꾸고, 그 관계를 표현하는 Reflection Model을 하나씩 살펴본다. Chapter 02의 Space, Chapter 03의 Vector 관계, Chapter 04의 Material 입력이 여기서 함께 사용된다.

Chapter 03에서 살펴본 Diffuse/Specular 성분을 실제 Reflection Model로 연결하고, Chapter 04의 Material 입력이 방향 응답을 어떻게 바꾸는지 알아본다. 마지막에는 **BRDF(Bidirectional Reflectance Distribution Function)**, 즉 입사와 출사 두 방향에 따른 Surface의 반사 응답을 정의하는 공통 함수로 이 관계를 묶는다. 이 순서는 학습 순서이며 모든 모델의 엄밀한 역사적 계보를 뜻하지 않는다.

---

## 5.1 Reflection

### Why Reflection Matters

같은 방에서 같은 조명 아래에 놓인 거울과 종이를 떠올려 보자. 거울에는 주변 물체가 선명하게 비치지만, 종이에서는 그런 상을 보기 어렵다. 금속에는 작은 밝은 영역이 생기고 플라스틱에는 부드러운 광택이 보인다. Light가 같아도 결과가 다른 것이다.

이 차이를 표현하려면 Surface에 도착한 Light가 그 뒤에 어디로, 얼마나 나가는지를 알아야 한다. 이것이 이번 Chapter에서 배우는 **Reflection**의 출발점이다. Reflection은 빛이 Material과 상호작용한 뒤 다시 바깥쪽으로 나오는 반사를 말한다. Rendering은 이 반사를 계산하여 Material의 모습을 화면에 표현한다.

Chapter 03에서 미리 살펴본 두 종류의 반사 성분을 여기서 다시 연결한다. 종이처럼 여러 관찰 방향에서 고르게 보이는 성분을 **Diffuse Reflection**이라고 한다. 거울이나 광택처럼 Light와 Camera의 방향 관계에 따라 크게 달라지는 성분을 **Specular Reflection**이라고 한다. 거친 거울의 반사가 넓게 퍼져도 여전히 Specular일 수 있으므로, 퍼져 보인다는 이유만으로 두 성분을 같게 취급하지 않는다. 이 차이는 5.4와 5.5에서 차례로 살펴본다.

Chapter 04에서 Material 입력으로 만난 **Roughness**는 거칠기에 따라 Specular가 퍼지는 정도를 제어한다. 지금은 반사 방향의 분포를 조절하는 Surface의 거칠기 값이라고 이해하면 된다. 하나의 반사 방향, 그 방향 주위의 퍼짐, 여러 방향에서 보이는 Diffuse 성분을 구별하는 것이 중요하다.

---

### Reading a Simple Reflection Example

<p align="center">
    <img src="Figures/Chapter05/Fig5_01.png" width="80%">
</p>

**Figure 5-1. Reflection Overview.** 이상적으로 매끄러운 Surface에서 빛이 거울 반사 방향으로 나가는 예시다. 먼저 빛이 Surface에 도착한 뒤 방향을 바꾸어 나간다는 관계를 읽는다.

> **Figure Reading Note**
>
> 이 그림은 모든 Material의 Reflection이 하나의 방향으로만 나간다는 뜻이 아니다. Roughness와 Diffuse/Specular 모델에 따른 방향 분포는 이후 절에서 구분한다. 하나의 그림으로 모든 반사 성분을 설명하려 하지 않는다.

---

### What Happens to Light at a Surface?

Surface에 도착한 빛이 모두 반사되는 것은 아니다. 일부는 Material 내부에 흡수된다. 이를 **Absorption**이라고 하며, 반사되어 다시 나오는 빛과 구별한다. 또 일부는 Material을 통과할 수 있다. 이처럼 다른 쪽으로 전달되는 현상을 **Transmission**이라고 한다.

우리가 여기서 집중할 것은 다시 바깥으로 나오는 Reflection이다. 이후의 기본 Formula는 주로 빛이 내부를 통과하지 않는 불투명한 Surface의 반사를 다룬다. 흡수와 투과가 존재한다는 것을 알아두면, 반사되는 빛의 양을 Material마다 다르게 정해야 하는 이유도 이해할 수 있다.

같은 조명 아래에서 Material의 모습이 달라지는 것은 반사 방향과 반사되는 양이 다르기 때문이다. 거울은 방향 관계가 잘 맞는 곳에서 주변 환경을 선명하게 보여준다. 종이는 Diffuse 성분으로 넓은 방향에 빛을 전달하고, 금속이나 플라스틱의 광택은 Specular 성분으로 Camera 방향에 따라 달라진다.

> **Material의 모습을 이해하려면 Color뿐 아니라 Light를 반사하는 방식도 알아야 한다.**

---

### Why Use a Reflection Model?

현실의 빛과 Material은 매우 많은 작은 상호작용을 만든다. Surface의 미세한 구조, 내부 산란, 흡수 같은 과정을 모두 그대로 추적하려면 많은 계산이 필요하다. 실시간 Rendering에서는 제한된 시간 안에 화면을 완성해야 하므로, 목적에 필요한 관계를 골라 표현한다.

이렇게 현상의 중요한 특징을 계산 가능한 관계로 단순화한 것을 **Model**이라고 한다. Reflection Model은 Surface와 Light, 관찰 방향이 주어졌을 때 어떤 반사 응답을 만드는지를 표현한다. Model마다 보존하는 특징과 생략하는 현상이 다르다.

예를 들어 Lambert는 방향에 무관한 이상적인 Diffuse 응답을 설명하고, Phong은 관찰 방향에 따라 달라지는 Highlight를 간단한 관계로 만든다. 뒤에서 살펴볼 Microfacet Model은 Surface의 작은 반사 면들이 서로 다른 방향을 가진다는 가정을 이용한다. 모델 이름을 외우기보다 각 모델이 어떤 질문에 답하는지를 따라가면 된다.

---

### A Learning Path through Reflection Models

Chapter 04에서 소개한 **PBR(Physically Based Rendering)**은 물리적 관계와 제약을 바탕으로 Material과 빛을 계산하는 접근이었다. 이름에 Physically Based가 들어간다는 사실만으로 모든 현상을 정확하게 계산한다는 뜻은 아니다. 사용할 Model의 범위와 입력 조건도 함께 알아야 한다.

앞에서 예고한 BRDF로 서로 다른 Reflection Model을 같은 Surface 응답의 질문으로 비교할 수 있다. 먼저 각 모델을 이해한 뒤, 5.16에서 이 공통 정의와 정확한 물리량을 연결한다. 그때 필요한 빛의 양을 읽기 위해, 에너지 전달을 물리량으로 측정하는 체계인 **Radiometry**도 살펴본다.

이번 Chapter의 학습 순서는 다음과 같다.

```text
Reflection
    ↓
Reflection Vector
    ↓
Lambert
    ↓
Phong
    ↓
Blinn-Phong
    ↓
Microfacet
    ↓
Cook-Torrance
    ↓
Radiometry
    ↓
BRDF
```

이 경로는 모든 모델이 앞 모델을 완전히 대체했다는 역사적 계보가 아니다. 반사 방향을 이해하고, Diffuse와 Specular의 차이를 비교하고, 작은 반사 면의 분포를 살펴본 뒤 공통 정의로 묶기 위한 학습 순서다.

> **Surface는 빛을 어떻게 반사하는가?**

이 질문을 계속 유지하며, 각 절이 어떤 답을 더하는지 확인한다.

---

### Key Takeaways

- Reflection은 Material과 상호작용한 빛이 다시 바깥으로 나오는 반사다.
- Material의 모습은 반사되는 양과 방향 관계에 영향을 받는다.
- Diffuse와 Specular는 서로 다른 반사 성분이며, 거친 Specular가 넓게 퍼져도 곧바로 Diffuse가 되는 것은 아니다.
- Reflection Model은 필요한 현상을 계산 가능한 관계로 표현한다.
- 여러 모델을 이해한 뒤 BRDF라는 공통 Surface 응답의 정의로 연결한다.

빛의 반사를 설명하려면 먼저 Surface가 어느 방향을 향하는지 알아야 한다. 다음 절에서는 그 기준이 되는 **Surface Normal**을 살펴본다.

---

## 5.2 Surface Normal

### Why Surface Direction Matters

방 안의 바닥, 벽, 천장을 생각해 보자. 같은 Light가 방을 비추더라도 세 Surface가 받는 빛의 관계는 서로 다르다. 바닥은 위를 향하고, 벽은 옆을 향하며, 천장은 아래를 향하기 때문이다. 사람은 이 차이를 눈으로 이해하지만 계산에는 방향을 나타내는 값이 필요하다.

Chapter 03에서 Vector는 방향과 크기를 나타내는 화살표라는 것을 살펴보았다. Surface 방향도 Vector로 표현하면 Light Direction과 직접 비교할 수 있다. 이때 기준으로 사용하는 Vector가 **Surface Normal**이다.

---

### A Perpendicular Reference Direction

기하학적인 Normal은 **Surface에 수직인 방향**을 나타낸다. 보통 **N**으로 표기한다. 바닥의 앞면을 위로 정했다면 N도 위를 향하고, 벽의 앞면을 방 안쪽으로 정했다면 N은 방 안쪽을 향한다.

왜 Surface 위의 앞뒤 방향 대신 수직 방향을 사용할까? 평평한 바닥에는 앞뒤, 좌우, 대각선처럼 많은 방향이 놓일 수 있다. 이 방향들은 바닥 위를 따라 움직이는 방향이어서 바닥 자체가 어디를 바라보는지 대표하지 못한다. 수직 방향을 기준으로 삼으면 Light가 얼마나 정면으로 들어오는지를 비교할 수 있다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_02.png" width="80%">
</p>

위 그림에서 N은 Surface의 방향을 읽기 위한 기준이다. 뒤의 Reflection과 Lighting 계산은 Light와 View가 이 기준에 대해 어떤 관계를 갖는지를 이용한다.

---

### Choosing an Orientation

평면에 수직인 방향은 서로 반대인 두 방향이다. 바닥에는 위와 아래가 모두 수직이므로, 그중 어느 쪽을 앞면으로 사용할지 정해야 한다. Geometry에서는 Triangle의 Vertex를 연결하는 순서와 앞면 규칙이 이 선택에 관계된다. Vertex를 순서대로 둘러가는 연결 순서를 **Winding**이라고 한다.

이 규칙을 정하지 않으면 같은 평면에서도 N의 방향이 반대로 선택될 수 있다. 이후 N과 Light의 Dot Product 부호가 달라지므로, Normal의 Orientation은 단순한 그림 표기 문제가 아니다. 계산에서 사용할 앞면을 일관되게 정하는 문제다.

Chapter 03에서 구분한 **Geometric Normal**과 **Shading Normal**도 유지한다. Geometric Normal은 실제 Geometry의 수직 기준이다. Shading Normal은 Vertex의 보간이나 Normal Map 등을 거쳐 Lighting에 사용하는 방향이다. Normal Map으로 보이는 세부 방향을 바꾸더라도 실제 Triangle의 Geometry가 같은 방식으로 바뀌는 것은 아니다.

---

### A Reference for Lighting

Surface Normal을 정하면 다음 질문을 Vector 관계로 바꿀 수 있다.

- Light가 Surface를 얼마나 정면으로 비추는가?
- 이상적인 거울 반사는 어디로 나가는가?
- Camera가 어느 방향에 있을 때 Highlight가 보이는가?

여기서 N은 Surface Reflection과 Lighting의 방향 관계를 평가하는 기준이다. 뒤에서 쓰는 **Reflection Vector**는 이 기준을 이용해 빛이 반사되어 나가는 방향을 표현한다. 먼저 N이 있어야 입사와 반사의 각도를 같은 기준으로 비교할 수 있다.

> **Implementation Note — Normal Used in This Chapter**
>
> 아래 Lighting 계산의 N은 같은 Space에서 정규화한 Shading Normal이다. Chapter 02에서 배운 것처럼 방향을 비교하려면 공통 Space가 필요하고, Chapter 03에서 배운 것처럼 Unit Vector를 사용해야 Dot Product를 각도의 Cosine으로 읽을 수 있다. 기하학적인 수직 기준과 실제 Shading에 선택한 Normal을 혼동하지 않는다.

---

### Key Takeaways

- Surface Normal은 Surface의 방향을 비교하기 위한 기준 Vector다.
- 기하학적인 Normal은 Surface에 수직이며, 서로 반대인 두 방향 중 사용할 앞면 방향을 정한다.
- Geometric Normal과 Shading Normal의 역할은 다르다.
- 이 Chapter의 Lighting N은 같은 Space의 Unit Shading Normal이다.

처음의 질문은 같은 빛 아래에서 Material이 왜 다르게 보이는가였다. 이제 Surface 방향의 기준을 준비했으므로, 빛이 Surface에 닿은 뒤 어느 방향으로 나가는지 설명할 수 있다.

---

## 5.3 Reflection Vector

### Where Does a Mirror Send Light?

거울을 조금 돌리면 비치는 물체의 위치도 달라진다. 거울은 빛을 아무 방향으로나 보내는 것이 아니라 Surface 방향과 입사 방향의 관계에 따라 반사한다. Surface Normal을 정했으므로, 이제 이 방향 관계를 계산할 수 있다.

먼저 이상적으로 매끄러운 거울 Surface를 생각한다. 빛이 N을 기준으로 한쪽에서 기울어져 들어오면, 반사되어 나가는 빛도 반대쪽에서 같은 각도로 기울어진다. 이것이 **Reflection Law**, 즉 반사의 법칙이다.

---

### Reflection Law

> **이상적인 거울 반사에서 입사각과 반사각은 같다. 각도는 Surface Normal을 기준으로 측정한다.**

입사각은 빛이 Surface에 도착하기 전 어디에서 오는지를 N과 비교한 각도다. 반사각은 Surface를 떠나는 방향과 N 사이의 각도다. Surface 위의 선을 기준으로 재면 다른 각도가 되므로, 먼저 N을 기준으로 읽는 것이 중요하다.

```
   Incident I          Reflected R
         ↘       N       ↗
           ↘     ↑     ↗
             ↘ θi│θr ↗
────────────────●──────────────── Surface
```

```
θi = θr
```

이 규칙은 여기서 다루는 완전히 매끄러운 거울 반사의 방향을 설명한다. 거친 Surface에서 여러 작은 면이 서로 다른 방향으로 반사하는 분포까지 하나의 방향으로 설명하는 것은 아니다.

---

### From Angles to a Reflection Vector

컴퓨터에서 이후 방향과 비교하려면 각도 두 개보다 하나의 Vector를 준비하는 편이 편리하다. 입사 방향과 N을 이용해 Surface에서 바깥으로 나가는 반사 방향을 Vector로 표현한 것을 **Reflection Vector**라고 하며, **R**로 표기한다.

여기서는 Light 방향을 Chapter 03의 Lighting 규칙과 맞춘다. **L은 Surface에서 Light를 향하는 방향**이다. Surface에 서서 광원 쪽을 가리키는 화살표라고 생각하면 된다. 실제 빛은 광원에서 Surface로 이동하므로 이 화살표와 반대로 움직인다.

실제로 들어오는 빛의 진행 방향을 **I**라고 쓰면 두 표기는 **I = -L** 관계다. Incoming이라는 말이 같은 뜻으로 쓰이더라도, 광원 쪽을 가리키는 계산 방향과 실제 빛의 진행 방향은 구별해야 한다.

- **L** : Surface에서 Light를 향하는 Unit Direction. 빛의 진행 방향은 I = -L
- **N** : Surface Normal
- **R** : Reflection Vector

<p align="center">
    <img src="Figures/Chapter05/Fig5_03.png" width="80%">
</p>

**Figure 5-3. Reflection Vector.** I는 Surface로 향하는 실제 빛의 진행 방향이고, R은 Surface에서 반사되어 나가는 방향이다. 먼저 두 화살표가 N에 대해 대칭이라는 관계를 읽는다.

> **Figure Reading Note — Direction Convention**
>
> 그림의 `I`는 Surface로 들어오는 빛의 진행 방향이며, 본문의 Surface→Light 방향 `L`과 `I = -L` 관계다. 같은 Space의 Unit Normal `|N| = 1`을 사용하면 `R = I - 2(I·N)N = 2(N·L)N - L`이다. 입사각은 `-I`와 `N` 사이의 각도다.

---

### Computing the Reflection Vector

L과 N을 알면 거울 반사의 대칭 관계를 하나의 식으로 표현할 수 있다. Chapter 03의 Dot Product는 두 방향이 얼마나 정렬되는지 알려주었다. 여기서 N·L은 L이 N 방향으로 얼마나 향하는지 나타내고, 이 관계를 이용해 접선 방향의 기울기를 반대쪽으로 바꾼다.

먼저 N과 L을 같은 Space의 Unit Vector로 준비한다. 이 조건 아래에서 Reflection Vector는 다음과 같다.

```text
R = 2(N · L)N - L
// N과 L은 같은 Space의 Unit Vector. reflect(I, N)의 I는 -L이다.
```

이 식의 목적은 반사량이나 Highlight의 최종 밝기를 구하는 것이 아니다. **빛이 반사되어 나가는 방향 R을 만드는 것**이다. 이 R과 Camera 방향을 비교하면 뒤의 Phong Highlight를 구성할 수 있다.

HLSL의 reflect 함수는 실제로 Surface를 향해 들어오는 I를 받으므로, 이 Chapter의 L을 그대로 넣지 않고 I=-L 관계를 사용한다. 함수 이름이 같은 반사를 말하더라도 입력 화살표의 의미를 확인해야 한다.

---

<details>
<summary>Technical Note — Reflection Vector Decomposition</summary>

**Decomposition**은 하나의 Vector를 몇 개의 성분으로 나누어 같은 관계를 다른 방식으로 보는 것을 말한다. Chapter 03의 Dot Product로 L을 N 방향 성분과 Surface를 따라가는 접선 성분으로 나누면 Reflection 식이 왜 이 모양인지 확인할 수 있다.

```text
Lparallel = dot(N, L) * N
Lperpendicular = L - Lparallel
R = Lparallel - Lperpendicular = 2 * dot(N, L) * N - L
```

N 방향 성분은 유지하고 접선 성분의 부호를 바꾼다. N=(0,0,1), L=(0.6,0,0.8)이면 R=(-0.6,0,0.8)이다. 이 부호 규칙은 Chapter 08.4에서도 동일하게 사용한다.

위 이름의 parallel은 N에 평행한 성분, perpendicular는 N에 수직인 접선 성분을 뜻한다. L이 광원 쪽을 향하는 규칙에서 N 성분을 유지하고 접선 성분을 뒤집으면 R이 된다. 실제 진행 방향 I에서 시작하면 같은 반사를 다른 부호의 입력으로 표현한다.

</details>

---

### From Reflection Direction to a Reflection Model

R은 이상적인 거울 반사의 방향을 제공하지만, 그 방향을 계산했다고 모든 Material의 모습이 정해지지는 않는다. Camera가 그 방향에 있을 때 얼마나 강하게 보일지, 반사가 얼마나 퍼질지, Diffuse 성분은 어떻게 나타날지 같은 질문이 남는다.

Phong은 R과 View Direction의 관계를 이용해 Specular Highlight를 구성한다. Blinn-Phong은 이후 L과 V 사이의 중간 방향인 **Half Vector**를 사용한다. Microfacet Model은 작은 반사 면들의 방향 분포를 평가한다. R은 이런 설명으로 들어가기 위한 기본 관계이며, 모든 모델이 R을 직접 계산해야 한다는 뜻은 아니다.

---

### Key Takeaways

- 이상적인 거울 반사에서는 N을 기준으로 입사각과 반사각이 같다.
- L은 Surface→Light이며, 실제 빛의 진행 방향 I는 -L이다.
- R은 반사 방향을 표현하며 반사량이나 최종 Lighting 자체는 아니다.
- 동일 Space의 Unit 조건과 입력 방향의 부호를 맞춰야 식을 올바르게 사용할 수 있다.

거울 반사의 방향은 이해했지만 종이나 벽은 거울처럼 보이지 않는다. 하나의 반사 방향만으로 설명하기 어려운 Diffuse 성분을 다음 절에서 살펴본다.

---

## 5.4 Lambert Reflection

### Why Does Paper Look Different from a Mirror?

거울에서는 Camera 위치를 조금 바꾸면 특정 Light가 보였다가 사라질 수 있다. 반면 같은 조명을 받는 종이나 벽의 한 지점은 관찰 방향을 조금 바꿔도 비슷한 밝기로 보인다. Reflection Vector 하나만으로는 이런 차이를 설명하기 어렵다.

이처럼 다양한 관찰 방향에서 빛이 보이는 Diffuse 성분을 간단하게 표현하려면, 반사 방향뿐 아니라 **Surface가 받는 빛과 나가는 빛의 관계**를 생각해야 한다. Lambert Reflection은 그 관계를 다루는 대표적인 이상적 Diffuse Model이다.

---

### Diffuse and Broad Specular Are Different

Diffuse는 종이·도료 같은 비금속에서 내부 산란 후 빛이 다시 나오는 현상 등을 단순화한 성분이다. Rough Surface에서 Specular가 넓게 퍼지는 현상과는 구분한다. 표면이 거칠다는 이유만으로 그 Reflection을 Diffuse라고 부르지는 않는다. 이처럼 빛이 특정 방향으로 집중되지 않고 다양한 방향으로 퍼지는 반사를 **Diffuse Reflection(난반사)** 이라고 한다.

거친 금속의 넓은 Highlight를 보았다고 그것이 곧 Diffuse가 되는 것은 아니다. 어떤 반사 성분인지 판단하려면 Surface와 Light, View의 관계를 함께 봐야 한다. 이 구분을 유지한 상태에서 이상적인 Lambertian Diffuse를 살펴본다.

---

### What Does a Lambertian Surface Keep the Same?

먼저 Surface가 받는 빛의 양을 정해 보자. 단위 Surface 면적에 단위 시간 동안 얼마나 많은 빛의 에너지가 도착하는지를 나타내는 양을 **Irradiance**라고 한다. 여기서는 같은 Surface 지점이 같은 Irradiance를 받고 있는 상황을 생각한다.

이 Surface에서 특정 관찰 방향으로 나가는 빛을 표현할 때는 **Outgoing Radiance**를 사용한다. Radiance는 방향과, 그 방향에서 보이는 Surface의 투영 면적을 함께 고려하는 물리량이다. 정확한 단위는 5.15에서 비교하지만 지금은 관찰 방향으로 나가는 빛을 측정하는 기준이라고 이해하면 된다.

Lambertian Model의 가정은 다음과 같다.

> **같은 Irradiance를 받는 Surface의 Outgoing Radiance는 관찰 방향에 의존하지 않는다.**

즉, 관찰자가 어느 방향에서 Surface를 바라보더라도 Outgoing Radiance가 같다고 가정한다. 모든 방향으로 나가는 Power가 동일하다는 뜻은 아니다.

여기서 같다는 것은 관찰 방향별 Radiance다. Surface를 비스듬히 보면 투영 면적이 달라지므로, 모든 방향 영역으로 나가는 전체 Power가 같다는 의미는 아니다. 이 차이는 뒤에서 BRDF의 단위를 이해할 때 다시 연결한다.

---

### Why Does Oblique Light Make the Surface Darker?

Camera 방향에는 무관한 응답이라고 했지만, Light가 들어오는 각도까지 무관한 것은 아니다. 같은 빛의 묶음을 Surface에 정면으로 비추면 작은 면적에 모인다. 비스듬히 비추면 같은 빛이 더 넓은 면적에 퍼진다.

그래서 Surface의 일정 면적이 받는 빛은 정면 입사에서 많고 비스듬한 입사에서 적어진다. 바뀌는 것은 먼저 **단위 면적에 도착하는 빛의 양**이다. Material이 이를 반사하면 관찰 방향으로 나가는 빛도 달라진다.

이 관계를 Surface Normal N과 Surface→Light 방향 L로 표현할 수 있다. Chapter 03의 Dot Product처럼 같은 Space의 Unit Direction을 비교하면 N·L은 두 방향 사이 각도의 Cosine이다. 정면에서는 1에 가깝고, 비스듬해질수록 작아진다.

---

### Lambert's Cosine Law

입사 방향 때문에 받는 빛이 줄어드는 관계를 다음 Direction Factor로 준비한다.

```text
DiffuseDirectionFactor = max(0, dot(N, L))
```

- **N** : Surface Normal
- **L** : Light Direction
- **N · L** : N과 L이 같은 Space의 Unit Vector일 때 두 방향 사이의 Cosine 값

입사각이 0°이면 N과 L이 정렬되어 계수가 1이다. 각도가 커지면 Cosine이 감소하여 같은 Light가 Surface에 제공하는 면적당 기여도 줄어든다. 이 식이 무엇을 측정하는지 알고 나면 max가 왜 필요한지도 설명할 수 있다.

여기서는 Surface의 앞면만 반사에 사용하고 내부 투과를 다루지 않는 불투명한 Surface를 생각한다. 앞면만 평가하는 조건을 **One-sided**, 빛이 통과하지 않는 범위를 **Opaque**라고 한다.

빛이 Surface 뒤쪽에서 들어오는 경우에는 여기서 다루는 One-sided Opaque Surface의 앞면에는 직접 기여하지 않으므로 음수는 0으로 처리한다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_04.png" width="80%">
</p>

그림은 N과 L의 각도에 따라 입사 방향 계수가 달라지는 관계를 확인하는 데 사용한다. 밝기 차이를 읽을 때 같은 Light와 Material이라는 조건을 함께 유지한다.

---

### A Direction Factor Is Only One Part of Lighting

NdotL이 같아도 Light가 더 강하거나 Material이 더 많은 빛을 반사하면 결과는 달라진다. 앞면이 다른 Object의 그림자에 가려져 실제 빛이 도착하지 않는 경우도 있다. 따라서 NdotL 하나를 최종 Surface 밝기라고 부르지 않는다.

이 식은 입사 방향에 따른 Cosine Factor이다. BRDF 자체는 아니며 Lambert BRDF의 Reflectance와 1/π는 5.19에서 연결한다.

지금 준비한 것은 입사 방향이 Irradiance에 주는 Cosine 계수다. BRDF와 이 계수를 분리하면 뒤에서 같은 NdotL을 중복 적용하는 오류를 피할 수 있다.

---

### Key Takeaways

- Diffuse와 넓게 퍼지는 Rough Specular는 서로 다른 반사 성분이다.
- Lambertian Model은 같은 Irradiance에서 Outgoing Radiance가 관찰 방향에 무관하다고 가정한다.
- 비스듬한 입사에서는 같은 빛이 더 넓은 면적에 퍼지며 입사 Cosine Factor가 작아진다.
- max(0,N·L)은 여기서 다루는 One-sided Opaque 앞면의 Direction Factor다.
- 실제 Lighting에는 Light와 Material의 응답도 필요하며, NdotL은 Lambert BRDF 자체가 아니다.

Lambert는 Diffuse의 기본 관계를 설명하지만 금속이나 플라스틱의 반짝이는 Highlight를 만들기에는 부족하다. 다음 절에서는 Camera 방향이 함께 필요한 Specular Reflection을 살펴본다.

---

## 5.5 Phong Reflection

### Why Diffuse Alone Cannot Explain a Highlight

같은 플라스틱 물체를 보면서 Camera만 움직여 보자. Surface의 기본 색은 남아 있지만 밝게 반짝이는 영역은 위치와 강도가 달라진다. 자동차 도장이나 물 위에서도 비슷한 변화를 볼 수 있다. 관찰 방향에 무관한 Lambertian Diffuse만으로는 이런 변화를 설명하기 어렵다.

여기서 필요한 것은 Chapter 03에서 미리 구분한 **Specular Reflection**이다. Specular는 Light와 Surface, 관찰 방향의 관계에 따라 달라지는 반사 성분이다. 한쪽 방향에 집중될 수도 있고 Roughness 때문에 넓게 퍼질 수도 있다.

Diffuse와 Specular는 한 Material에서 함께 나타날 수 있다. 플라스틱의 기본 색과 광택이 서로 다른 입력과 관계를 갖는다고 생각하면 이해하기 쉽다. 한 Material을 무조건 둘 중 하나로만 분류하기보다 각 성분의 역할을 구별한다.

---

### A Highlight Is Reflected Light

밝은 **Highlight**는 Surface가 특정 방향으로 반사한 Light가 Camera에서 강하게 보이는 영역이다. 그 Surface가 스스로 빛을 내고 있다는 뜻은 아니다. 우리가 **Gloss**, 즉 광택이라고 부르는 모습도 이런 Specular 관계와 연결된다.

Light는 Surface에 도착하고, Surface는 방향에 따라 다르게 반사하며, Camera는 그중 하나의 방향에서 결과를 본다. 따라서 Highlight를 설명하려면 N과 L뿐 아니라 관찰 방향도 필요하다.

**View Direction V**는 현재 Surface 지점에서 Camera 쪽을 향하는 Vector다. Chapter 02/03에서 준비한 Camera와 Surface의 방향 관계를 사용한다. 여기서는 L과 마찬가지로 Surface에서 바깥쪽을 향하고, 같은 Space의 Unit Vector로 준비한다.

---

### Comparing Reflection and View Directions

앞 절의 R은 이상적인 거울 반사 방향이었다. Camera가 이 R 방향에 있을수록 거울 반사와의 방향 관계가 잘 맞는다. Camera가 R에서 멀어지면 그 관계는 약해진다.

Phong Reflection은 이 관찰을 계산 가능한 Highlight 모양으로 만든다. R과 V가 얼마나 일치하는지를 Dot Product로 비교하고, 그 결과를 조절하여 반사 방향 주변에 밝은 영역을 만든다. 여기서 핵심 질문은 **Camera가 거울 반사 방향과 얼마나 가까운가?**다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_05.png" width="80%">
</p>

그림에서 R과 V의 관계를 읽는다. N과 L을 그대로 두고 Camera를 움직이면 V가 바뀌므로 Specular 응답도 바뀐다. Lambertian Diffuse가 같은 Irradiance에서 View에 무관하다는 설명과 비교할 수 있다.

---

### From Alignment to a Phong Response

Dot Product만 사용하면 R에서 멀어질수록 응답이 넓게 줄어든다. Highlight를 더 좁게 집중시키려면 이 정렬 값을 거듭제곱한다. 지수 **n**은 이 경험적 Highlight 모양을 조절하는 값이며, n>0인 범위를 사용한다.

여기서 **Response**는 입력 방향에 대해 계산한 응답값을 말한다. **Empirical**, 즉 경험적 모델이라는 말은 현상을 간단한 제어 관계로 근사한다는 뜻이다. 이 값의 모양을 제어하는 것과 물리적인 반사율을 완성하는 것은 구별해야 한다.

R과 V를 같은 Space의 Unit Vector로 준비한 뒤 응답을 다음과 같이 계산한다.

```text
SpecularResponse = pow(max(0, dot(R, V)), n)  // n > 0
```

정렬이 잘 맞아 Dot Product가 1이면 거듭제곱 뒤에도 큰 응답을 유지한다. 1보다 작은 값은 n에 따라 더 빠르게 줄어들므로, 반사 방향 주변으로 Highlight가 집중된다. 이 식은 R과 V의 방향 관계를 Highlight로 바꾸는 최종 표현이다.

---

### What This Response Does and Does Not Guarantee

물리적인 수동 Material은 받은 빛보다 더 많은 빛을 새로 반사해서 만들어 낼 수 없다. 이런 제약을 **Energy Conservation**, 즉 에너지 보존이라고 한다. 보기 좋은 Highlight 형태를 만든 식이 자동으로 이 조건까지 충족하는 것은 아니다.

R과 V는 같은 Space의 Unit Vector이며 V는 Surface→Camera이다. One-sided Reflection에는 dot(N,L)>0, dot(N,V)>0 조건도 필요하다. 이 경험적 Response에 Color와 Intensity를 곱하는 것만으로 Energy-conserving BRDF가 되지는 않는다. Chapter 08.4는 이 Response의 교육용 구현을 다룬다.

One-sided Reflection의 Light와 Camera는 평가하는 앞면 쪽에 있어야 한다. 반대쪽 Light나 Camera에서 같은 응답을 그대로 사용하면 여기서 설명한 앞면 반사 범위를 벗어난다. 이 조건과 응답의 정규화, Diffuse/Specular 에너지 배분은 별도로 확인한다.

> **Implementation Note — Cost and Scope**
>
> Reflection Vector와 View Direction의 관계를 사용하며, 실제 계산 비용은 구현·컴파일 결과·Hardware에 따라 달라진다. Phong이라는 이름만으로 일정한 비용이나 성능 우열을 보장하지 않는다. Chapter 08.4는 이 Response의 제어 가능한 교육용 구현을 다룬다.

---

### Key Takeaways

- Specular Highlight는 Light, Surface, View의 방향 관계에 따라 달라진다.
- Highlight는 반사된 빛이며 Surface 자체의 Emission과 다르다.
- Phong은 R과 V의 정렬을 응답값으로 바꾸고 지수로 모양을 조절한다.
- 단순한 경험적 Response를 계산했다고 완성된 Energy-conserving BRDF가 되는 것은 아니다.
- Unit/Space와 One-sided 조건을 지킨 상태에서 모델의 범위를 이해한다.

Lambert에 View Direction이 더해지면서 Reflection을 설명하는 질문이 넓어졌다. 다음에는 R과 V를 직접 비교하는 대신, L과 V 사이의 중간 방향을 사용하면 어떤 관계를 볼 수 있는지 살펴본다. 이 중간 방향이 **Half Vector**다.

---

## 5.6 Half Vector

### Can the Same Alignment Be Described Another Way?

Phong에서는 L과 N으로 R을 계산한 다음 R과 V를 비교했다. Highlight가 강한 방향을 판단하기 위해 Light가 어디에 있고 Camera가 어디에 있는지를 두 단계로 연결한 것이다.

```text
Light Direction
        │
        ▼
Reflection Vector 계산
        │
        ▼
View Direction과 비교
        │
        ▼
Highlight 계산
```

이 관계를 Surface의 N과 직접 비교할 수 있는 다른 Vector로 표현할 방법은 없을까? L과 V를 알고 있다면 그 사이에 있는 방향을 생각할 수 있다. James F. Blinn의 아이디어는 Reflection Vector 대신 이 중간 방향을 활용하는 것이다.

여기서 새로운 관점을 도입하는 이유는 계산 구조를 다른 방향 관계로 표현하기 위해서다. R 대신 H를 쓴다는 사실만으로 실제 구현이 언제나 더 빠르다고 결론 내리지는 않는다. 먼저 무엇을 비교하는지 이해한다.

---

### Understanding the Half Vector Before Computing It

Surface에서 Light를 향하는 Unit Vector L과 Camera를 향하는 Unit Vector V를 그려 보자. 두 화살표의 길이가 같으면, 두 방향을 더한 Vector는 그 사이를 가리킨다. 이 Vector의 길이를 제거하고 방향만 남기면 중간 방향을 얻는다.

Chapter 03에서 **Normalize**는 Vector의 길이 영향을 제거하여 Unit Direction을 만드는 연산이었다. 여기서는 더한 L+V를 Normalize하여 중간 방향을 준비한다.

**Half Vector**, 또는 Halfway Vector는 L과 V가 이루는 각도를 절반으로 나누는 방향이다. 보통 **H**로 표기한다. Half라는 이름은 밝기를 절반으로 줄인다는 뜻이 아니라 두 방향 사이의 중간이라는 뜻이다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_06.png" width="80%">
</p>

그림은 Light와 View 사이에 H가 놓이는 관계를 보여준다. H를 구했다고 Surface가 이미 그 방향을 향하는 것은 아니다. 다음에는 Surface의 N이 H와 얼마나 가까운지 비교해야 한다.

---

### Why Compare N with H?

이상적인 거울 반사가 Camera 방향으로 정확히 향할 때, Surface Normal은 Light와 View 사이의 중간 방향에 정렬된다. 반사각과 입사각이 N을 기준으로 같다는 Reflection Law를 다른 방식으로 본 것이다.

Phong은 다음 관계를 비교했다.

```text
Reflection Vector ≈ View Direction
```

Half Vector를 사용하는 관점에서는 다음 관계를 비교한다.

```text
Surface Normal ≈ Half Vector
```

R과 V가 정렬되는 최대 조건을 N과 H의 정렬 관계로 읽을 수 있다. 하지만 정렬되는 중심이 같다는 사실이 중심 주변의 모든 응답값까지 같다는 뜻은 아니다. Highlight 주위 전체 방향의 퍼짐을 **Lobe**라고 부르며, Phong과 Blinn-Phong의 Lobe는 일반적으로 다르다.

---

### Computing H and Using Its Alignment

먼저 L과 V를 같은 Space에서 Surface 바깥쪽을 향하는 Unit Vector로 준비한다. 앞에서 이해한 관계를 식으로 쓰면 H는 normalize(L+V)다. 그 뒤 N과 H를 비교하여 Highlight 응답을 구성한다.

```text
H = normalize(L + V)
BlinnPhongResponse = pow(max(0, dot(N, H)), n)
```

첫 줄은 중간 방향을 만든다. 둘째 줄은 그 방향과 Surface Normal의 정렬을 응답값으로 바꾼다. 방향 H 자체와 H를 이용한 Reflection Response는 서로 다른 단계다. 두 번째 단계가 다음 절의 Blinn-Phong Reflection이다.

> **Implementation Note — Degenerate Direction and Lobe Width**
>
> L과 V는 같은 Space에서 Surface 바깥쪽을 향하는 Unit Vector이다. L+V가 0이면 H가 정의되지 않으므로 해당 경계에서는 Response를 0으로 처리하는 등의 명시적인 정책이 필요하다. Phong과 같은 n을 사용해도 Highlight 폭은 일반적으로 같지 않다.

---

### Why H Matters Beyond Blinn-Phong

5.1에서 예고한 **Microfacet**은 아주 작은 반사 면 하나였다. 여기서는 작은 거울 하나라고 생각하면 된다. Surface 전체의 작은 면들은 여러 방향을 향할 수 있다.

Microfacet Theory에서는 주어진 L과 V 사이에 완전한 거울 Reflection을 만드는 Microfacet의 Normal이 H와 정렬된다. 모든 Microfacet이 H를 향하는 것이 아니라, 그 방향의 분포 밀도를 D(H)로 평가한다.

이 문장의 D(H)는 그 H 방향에 작은 면들이 얼마나 모이는지를 평가하는 함수라는 뜻이다. 아직 분포 식을 외울 필요는 없다. **빛을 Camera로 돌려 줄 작은 거울의 방향이 H**라는 관계를 기억하면 5.9의 Microfacet Model과 자연스럽게 이어진다.

> **Implementation Note — Measured Cost**
>
> Half Vector는 Reflection Vector를 직접 계산하지 않아도 되므로 R 대신 H를 사용하는 구조가 된다. Normalize 비용을 포함한 실제 성능 우열은 별도로 측정해야 한다.

---

### Key Takeaways

- H는 같은 Space의 Unit L과 V 사이 중간 방향이다.
- 먼저 중간 방향을 만들고, 그다음 N과 H의 정렬로 응답을 구성한다.
- Phong과 Blinn-Phong은 최대 정렬 관계를 다르게 표현하지만 전체 Lobe가 같지는 않다.
- L+V=0 경계는 명시적으로 처리해야 하며 실제 성능은 구현 조건에 따라 측정한다.
- 고정된 L,V 사이에 거울 반사를 만드는 Microfacet의 Normal도 H와 정렬된다.

이제 Half Vector의 뜻을 알았으므로, 다음 절에서는 이 방향을 실제 Highlight 모델로 사용하는 Blinn-Phong Reflection을 정리한다.

---

## 5.7 Blinn-Phong Reflection

### Turning the Half Vector into a Reflection Response

앞 절의 H는 Light와 View 사이의 중간 방향이었다. 방향 하나를 준비했으니 이제 Surface가 그 방향과 얼마나 정렬되는지를 응답값으로 바꿀 차례다. 이것이 Blinn-Phong Reflection의 핵심이다.

N과 H가 가까우면 Light를 Camera 쪽으로 반사하는 정렬 관계가 잘 맞는다. 두 방향이 멀어지면 응답을 줄인다. Chapter 03의 Dot Product와 앞 절의 지수 제어가 이 관계를 계산 가능한 Highlight로 만든다.

---

### Comparing the Two Questions

Phong은 **반사 방향이 Camera 방향과 얼마나 가까운가?**를 묻는다.

```text
Reflection Vector ≈ View Direction
```

Blinn-Phong은 **Surface Normal이 Light와 Camera 사이의 중간 방향과 얼마나 가까운가?**를 묻는다.

```text
Surface Normal ≈ Half Vector
```

같은 Light와 View를 두고 비교하는 대상이 R/V에서 N/H로 바뀐 것이다. 비교 대상을 분리해 보면 두 모델의 Formula를 각각 외우기보다 공통된 정렬 질문으로 이해할 수 있다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_07.png" width="80%">
</p>

그림에서는 두 비교의 중심 관계를 읽는다. H는 Surface Normal을 자동으로 바꾸는 값이 아니다. 정해진 N과 새로 계산한 H가 어떤 관계를 갖는지 평가한다.

---

### Peak Alignment Does Not Make the Whole Lobe Identical

이상적인 거울 반사가 Camera를 향할 때 N과 H의 정렬은 R과 V의 정렬과 연결된다. 그래서 두 모델은 비슷한 위치에서 강한 Highlight를 만들 수 있다.

그러나 Camera가 그 중심에서 벗어났을 때 응답이 얼마나 빠르게 줄어드는지는 비교식에 따라 달라진다. 같은 n을 사용해도 Highlight 폭이 일반적으로 같지 않다는 5.6의 조건을 기억한다. 최대 정렬 조건과 전체 응답 모양을 구별해야 한다.

Blinn-Phong은 Reflection Vector 대신 Half Vector와 Surface Normal의 비교로 Highlight를 구성한다. 실제 계산 비용은 5.6에서 설명한 Normalize, 구현·컴파일 결과·Hardware 조건에 따라 평가한다. 게임과 실시간 Rendering에서 널리 사용되어 온 방식이지만, 그 사실이 모든 구현의 성능이나 물리적 정확성을 보장하는 것은 아니다.

---

### What Is Still Missing?

Blinn-Phong도 여기서 소개한 형태는 경험적 Highlight 모델이다. 몇 개의 방향과 지수로 보기 좋은 반사를 근사할 수 있지만, 작은 반사 면의 방향 분포와 차폐를 따로 계산하는 물리적 모델까지 포함한 것은 아니다.

또 같은 Material이라도 입사각에 따라 반사율이 달라지는 관계가 있다. 이를 **Fresnel**이라고 부른다. Fresnel은 약어가 아니라 물리학자 Augustin-Jean Fresnel의 이름에서 온 명칭이다. 5.14에서 이 관계와 계산 근사를 자세히 다룬다.

여기서 소개한 단순 Response의 한계를 다음과 같이 구분한다.

- Material마다 다른 Reflection 특성을 충분히 표현하기 어렵다.
- 여기서 소개한 정규화되지 않은 Response는 Energy Conservation을 보장하지 않는다. 별도의 정규화와 에너지 배분을 적용한 변형과 구분한다.
- Surface의 미세한 구조(Micro Geometry)를 명시적인 분포·차폐 모델로 결합하지 않는다.
- 입사각에 따른 Fresnel Reflectance를 이 Response 자체가 표현하는 것은 아니다.

**Micro Geometry**는 화면에서 하나의 Surface로 보이는 영역 안에 있는 작은 구조를 말한다. 이 문제는 Mesh 전체가 하나의 평면이라고 가정했다는 뜻과 다르다. 현재 Surface 응답을 평가하는 지점을 **Shading Point**라고 한다. 다음 Part에서는 이 지점의 작은 구조를 어떻게 별도의 Model로 반영하는지 살펴본다.

---

### Key Takeaways

- Phong은 R과 V, Blinn-Phong은 N과 H의 관계로 Highlight를 만든다.
- 강한 정렬 위치가 연결되어도 두 모델의 Lobe 전체는 같지 않다.
- 여기서 소개한 경험적 Response와 에너지 보존을 적용한 BRDF 변형을 구별한다.
- 미세 구조의 분포·차폐와 입사각에 따른 반사율은 별도의 물리적 관계다.

Lambert에서 시작해 View Direction과 Highlight까지 질문을 넓혀 왔다. 다음에는 그 모델들이 아직 명시적으로 다루지 않은 Surface의 미세 구조와 빛의 전달을 정리한다.

---

**Part II — Physically Based Rendering**

먼저 5.8에서 단순 Reflection Model이 무엇을 생략하는지 확인한다. 이어지는 5.9에서는 Surface를 작은 거울들의 집합으로 바라보는 Microfacet 관점을 준비하고, 5.10에서 이를 하나의 Reflection Model로 결합한다.

---

## 5.8 Limits of Simple Reflection Models

### Why Review the Assumptions?

Lambert는 이상적인 Diffuse를 설명했고, Phong은 R과 V로 Highlight를 만들었다. Blinn-Phong은 N과 H로 다른 Highlight Response를 구성했다. 같은 Reflection을 배우고 있지만, 각 모델이 답하는 질문은 조금씩 다르다.

이 모델들을 사용할 때는 원하는 모습을 만들 수 있는지뿐 아니라 어떤 관계를 생략했는지도 알아야 한다. 생략한 부분을 모르면 입력을 조절해 해결할 수 없는 문제까지 Parameter 문제라고 생각하기 쉽다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_08.png" width="80%">
</p>

아래에서는 단순 모델의 범위를 현재 Shading Point와 Material response라는 관점에서 정리한다. 이것은 모든 초기 모델이 하나의 가정으로 묶이거나 뒤의 모델이 모든 재질에서 무조건 더 정확하다는 비교가 아니다.

---

### A Shading Point Is Not the Whole Mesh

**Shading Point**는 지금 Surface 응답을 평가하는 한 지점을 뜻한다. Chapter 01의 Pixel 처리와 Chapter 03의 Normal 계산을 떠올리면, 화면에 보이는 Surface 전체가 하나의 N을 가진다는 뜻이 아님을 알 수 있다.

기존의 단순한 Phong/Blinn-Phong 설명은 각 Shading Point의 N과 경험적 지수로 Highlight를 조절한다. Mesh 전체가 하나의 Normal을 갖는다는 뜻은 아니다. 부족한 것은 Pixel보다 작은 Microfacet 방향 분포와 차폐·Fresnel을 결합한 명시적인 물리 모델이다. 하지만 현실의 Material은 현미경으로 확대하면 수많은 미세한 요철로 이루어져 있다.

Normal Map으로 화면에서 쓰는 N을 바꾸는 것과, 그보다 작은 면들의 방향 분포와 서로 가리는 관계를 통계적으로 평가하는 것도 다르다. 실제 Material의 작은 구조를 직접 모두 Geometry로 만들기 어려우므로, 이런 관계를 Model로 요약할 필요가 있다.

---

### One Highlight Control Cannot Represent Every Material

금속, 플라스틱, 세라믹, 천은 같은 기본 색을 갖더라도 다른 반사를 만든다. Highlight의 크기와 세기만 바꾸면 일부 차이를 근사할 수 있지만, 모든 Material의 방향별 반사율과 미세 구조가 같은 방식으로 표현되는 것은 아니다.

Chapter 04에서 Material Parameter를 구별한 이유가 여기에도 연결된다. Color, Roughness, Metallic 같은 입력은 단순히 모두 밝기를 조절하는 Slider가 아니다. 각 입력이 어떤 Material 관계를 제어하는지 Model이 정해 주어야 한다.

---

### Light Must Also Reach the Reflecting Surface

적절한 반사 방향을 향하는 작은 면이 있다고 해서 빛이 반드시 Camera까지 전달되는 것은 아니다. 이웃의 작은 면이 Light 쪽 길을 막을 수 있고, 반사된 빛이 View 쪽에서 가려질 수도 있다.

또 빛이 도착한 뒤 Material이 반사하는 비율은 입사각에 따라 달라질 수 있다. 앞서 이름을 붙인 Fresnel 관계다. 분포, 차폐, 반사율을 별도의 역할로 구별하면 한 지수나 한 밝기 값으로 모두 대신하려는 오류를 피할 수 있다.

---

### A New Question for the Next Model

단순 모델의 한계를 확인하면 다음 질문이 생긴다.

> **Surface 안에 서로 다른 방향의 작은 반사 면들이 있다면, 그 전체의 응답을 어떻게 계산할까?**

이 문제에서 출발하는 관점이 Microfacet Theory다. Surface의 작은 구조를 하나씩 저장하기보다, 어떤 방향의 면이 얼마나 존재하는지와 그 면이 보이는지를 Model로 표현한다. 다음 절에서는 먼저 작은 거울들이 모였다는 직관을 준비한다.

---

### Key Takeaways

- 단순 Reflection Model은 서로 다른 질문과 가정을 가진다.
- 현재 Shading Point의 N을 사용하는 것과 Mesh 전체가 하나의 평면이라는 가정은 다르다.
- Microfacet 분포·차폐·Fresnel을 명시적으로 결합하려면 더 많은 관계가 필요하다.
- Model의 한계를 아는 것은 Material Parameter로 바꿀 수 있는 범위를 이해하는 데도 도움이 된다.

---

## 5.9 Microfacet Theory

### Is a Smooth-looking Surface Smooth at Every Scale?

눈으로 보면 매끄러운 금속도 더 작은 규모에서는 요철과 방향 변화가 있을 수 있다. 반대로 Surface 전체의 Geometry를 아주 많이 늘려 이런 작은 구조를 하나씩 표현하기는 어렵다. 화면에서 보이는 Reflection에 필요한 것은 그 구조를 모두 저장하는 일보다 전체 방향 응답을 설명하는 일이다.

Microfacet Theory는 Surface를 많은 작은 반사 면의 집합으로 바라보는 Model이다. 한 작은 면을 Microfacet이라고 하며, 이 Chapter에서는 각 면을 이상적인 작은 거울로 생각한다. 실제 Material의 모든 미세 현상을 그대로 복제했다는 뜻은 아니며, 반사를 계산하기 위한 가정이다.

---

### Many Small Mirrors, Many Orientations

모든 작은 거울이 같은 방향을 향하면 같은 Light를 비슷한 방향으로 보낸다. 거울들의 방향이 서로 다르면, 각 면이 보내는 거울 반사 방향도 달라진다. 이 방향들이 모여 우리가 보는 넓은 Specular 응답을 만든다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_09.png" width="80%">
</p>

그림에서 먼저 큰 Surface의 기준 N과 작은 면 각각의 Normal을 구별한다. 큰 기준이 같아도 작은 면들의 방향은 다양할 수 있다. Roughness는 이 방향들의 퍼짐과 관계된다.

연마한 금속처럼 작은 면의 방향 변화가 적으면 반사가 좁게 집중될 수 있다. 거친 Surface처럼 방향 변화가 크면 더 넓은 방향으로 Specular가 퍼진다. 이 퍼짐이 곧 Diffuse라는 뜻은 아니라는 5.4의 구분을 유지한다.

---

### Which Facets Can Send Light to the Camera?

Light와 Camera가 고정되어 있다고 생각해 보자. 많은 작은 거울 중 Camera로 빛을 반사할 수 있는 것은 특정 방향을 향하는 면들이다. 방향이 맞지 않는 작은 거울은 다른 방향으로 빛을 보낸다.

5.6의 Half Vector H는 바로 이 반사 관계에 필요한 면의 Normal 방향이었다. 주어진 L과 V 사이에 이상적인 거울 반사를 만드는 Microfacet Normal이 H에 정렬된다. 모든 Microfacet이 H를 바라본다는 뜻이 아니다.

이렇게 생각하면 Highlight를 만드는 질문이 바뀐다. Surface 전체의 Normal이 H와 가까운지만 볼 것이 아니라, **H 방향을 향한 작은 면이 얼마나 존재하는가?**를 물을 수 있다.

---

### Why Use a Distribution Instead of Storing Every Facet?

한 Surface에 있는 작은 면을 모두 별도의 Geometry로 만들지 않고도 방향 응답을 근사할 수 있다. 방향별로 얼마나 많은 면적이 모이는지를 함수로 표현하는 것이다. 이런 여러 면의 전체적 관계를 다루는 접근을 **Statistical Model**, 즉 통계적 모델이라고 한다.

여기서 **Distribution**은 작은 면들이 방향별로 어떻게 퍼져 있는지를 나타내는 분포다. 특정 방향 하나의 면을 골라 추적하는 대신, 그 방향 부근의 면이 전체 응답에 얼마나 기여하는지 평가한다.

Cook-Torrance 계열 Microfacet Reflection은 이 분포에 차폐와 반사율 관계를 결합한다. 아직 그 식부터 외울 필요는 없다. 먼저 작은 거울들, 서로 다른 방향, Camera로 보내는 면의 H라는 세 관계를 연결한다.

---

### Key Takeaways

- Microfacet Model은 Surface의 미세 구조를 작은 반사 면들의 집합으로 단순화한다.
- 작은 면들의 방향 변화는 Specular가 퍼지는 모양에 영향을 준다.
- 고정된 L,V 사이에 거울 반사를 만드는 면의 Normal은 H와 정렬된다.
- 모든 Facet이 H를 향하는 것은 아니므로, 그 방향의 분포를 평가해야 한다.
- 방향 분포만으로는 아직 차폐와 반사율까지 계산되지 않는다.

Surface를 작은 거울들의 집합으로 바라보는 관점을 준비했다. 다음 절에서는 어느 면이 있는가, 그 면이 보이는가, 얼마나 반사하는가를 하나의 Reflection Model로 묶는다.

---

## 5.10 Cook-Torrance Reflection

### Why a Distribution Is Not Yet a Reflection Result

Microfacet 관점에서 Surface를 작은 거울들의 집합으로 보았다. 주어진 L과 V 사이에 반사를 만드는 면의 방향도 H로 준비했다. 하지만 H 방향의 면이 존재한다는 사실만으로 Camera에 도달하는 빛의 양까지 정해지지는 않는다.

그 면에 Light가 실제로 도달해야 하고, 반사된 빛이 Camera 쪽에서도 가려지지 않아야 한다. Material이 현재 입사각에서 빛을 얼마나 반사하는지도 필요하다. **Cook-Torrance Reflection**은 Microfacet 관점을 바탕으로 이런 서로 다른 역할을 결합하는 Reflection Model이다.

현대 PBR에서 널리 사용하는 Microfacet Specular BRDF의 구조를 이해하기 위한 기준 모델로 볼 수 있다. 이름만으로 모든 구현이 같거나 모든 물리적 현상을 포함한다고 생각하지 않는다. 여기서 사용하는 기본 관계와 범위를 차례로 확인한다.

---

### Three Different Questions

먼저 분포를 묻는다.

> **Light를 Camera 쪽으로 반사할 방향의 Microfacet이 얼마나 존재하는가?**

이 방향 분포를 나타내는 함수가 **NDF(Normal Distribution Function)**다. 여기서 Normal은 정규분포라는 통계 용어가 아니라 작은 면의 Normal을 뜻한다. 함수는 **D**라는 기호로 표기하며, 해당 방향의 분포 밀도를 평가한다. 5.12에서 밀도와 확률의 차이를 자세히 확인한다.

다음에는 길이 열려 있는지 묻는다.

> **그 작은 면에 Light가 도달하고, 반사된 빛이 Camera로 나갈 수 있는가?**

이웃 Microfacet이 Light 쪽 길을 막는 것을 **Shadowing**, Camera 쪽에서 반사 면을 가리는 것을 **Masking**이라고 한다. 이런 미세 차폐를 반영하는 항이 **Geometry Function G**다. G는 Surface 주변의 다른 큰 Object가 만드는 Scene Shadow와 구별한다.

마지막에는 Material의 반사율을 묻는다.

> **같은 Material이라도 현재 입사각에서 얼마나 많은 빛을 반사하는가?**

앞서 소개한 **Fresnel F**가 이 입사각에 따른 반사율 관계를 담당한다. 분포 D, 미세 차폐 G, 반사율 F는 각각 다른 질문에 답한다. 하나의 항을 바꿔 나머지 모든 관계를 대신하려 하지 않는다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_10.png" width="80%">
</p>

그림에서는 세 역할을 먼저 구별한다. 분포가 있다고 빛이 항상 보이는 것도 아니고, 길이 열려 있다고 모든 Material이 같은 반사율을 가지는 것도 아니다.

---

### Combining the Terms into a BRDF

여기서는 빛이 하나의 Microfacet에서 한 번 반사되는 기본 기여를 다룬다. 이 범위를 **Single Scattering**이라고 한다. 작은 면들 사이에서 여러 번 반사되는 모든 경로를 그대로 계산하는 Model은 아니다.

D·G·F는 핵심 역할을 나누지만, 세 값의 곱만으로 완성된 BRDF가 되지는 않는다. 큰 Surface 기준의 방향과 면적 관계를 함께 반영하는 분모도 필요하다. 먼저 양의 N·L과 N·V를 갖는 앞면 관계, 같은 Space의 Unit Direction을 준비한다.

대표적인 Single-scattering Microfacet Specular BRDF는 다음 구조를 가진다.

```text
fr_specular = D(H) * F(dot(V,H)) * G(L,V) / (4 * dot(N,L) * dot(N,V))
H = normalize(L + V)
```

첫 줄의 D(H)는 현재 L,V 사이에 반사를 만들 Facet 방향의 분포를 평가한다. F는 그 Facet의 입사각에 따른 반사율을, G는 Light와 View 양쪽 미세 차폐를 반영한다. 분모를 포함해 하나의 Surface 응답으로 결합한 값이 fr_specular다.

이 식은 아직 Incoming Light를 곱해 최종 Radiance를 만든 결과가 아니다. BRDF의 정확한 입출력은 5.16–5.18에서 연결한다. 지금은 역할이 다른 항을 결합해 Material의 방향 응답을 준비한다는 관계를 이해한다.

---

### Microfacet Occlusion and Scene Visibility

Surface 위의 작은 면끼리 가리는 관계와, 장면에 있는 다른 Object가 광원을 가리는 관계는 다르다. 뒤의 경우를 **Scene Visibility**라고 한다. Light에서 현재 Surface까지 길이 열려 있는지를 나타내며, 표기는 View Vector V와 구별하기 위해 **Vis**를 사용한다.

G는 Microfacet의 미세 차폐를 반영한다. Scene Visibility를 G로 대신하거나, 이미 G를 계산했다는 이유로 다른 Object의 그림자를 생략하지 않는다. 반대로 입력 Light가 이미 차폐된 값이라면 같은 Scene 차폐를 다시 곱하지 않아야 한다. 입사 방향들의 Light 기여를 모아 나가는 빛을 계산하는 관계가 Rendering Equation이다. 이 조건은 5.18에서 다시 확인한다.

> **Implementation Note — Evaluation Conditions**
>
> 같은 Space의 Unit Vector와 양의 dot(N,L), dot(N,V)를 전제로 한다. 경계의 0 분모를 그대로 계산하지 않는다. D·G·F만 곱한 값은 이 BRDF 전체가 아니다. G는 Microfacet 사이의 차폐이며, 다른 Object가 Light를 가리는 Scene Visibility와 다르다. Chapter 08.3의 Vis를 G와 중복 또는 대체 관계로 취급하지 않는다.

---

### Key Takeaways

- Cook-Torrance 계열 Microfacet Model은 방향 분포, 미세 차폐, 반사율을 결합한다.
- D는 Normal 방향 분포, G는 Shadowing/Masking, F는 입사각에 따른 반사율이다.
- 전체 BRDF에는 D·G·F뿐 아니라 분모와 방향 조건도 포함된다.
- 여기서 다루는 기본 식은 Single-scattering 범위다.
- Microfacet G와 Scene Visibility Vis는 서로 다른 역할이다.

---

**Part III — Cook-Torrance Components**

이제 각 요소가 실제 Material의 모습에 어떻게 영향을 주는지 살펴본다. 먼저 Chapter 04에서 Material 입력으로 만났던 Roughness를 미세한 반사 면의 방향과 연결하고, D, G, F의 질문을 하나씩 풀어간다.

---

## 5.11 Roughness

### Why Does the Same Material Have Different Highlights?

같은 금속이라도 연마한 부분과 긁힌 부분은 다르게 보인다. 연마한 부분은 반사가 좁고 선명하며, 긁힌 부분은 넓고 부드럽게 퍼질 수 있다. 새 플라스틱과 오래 사용한 플라스틱에서도 비슷한 차이를 볼 수 있다.

이 차이를 이해하려면 Material의 종류뿐 아니라 작은 반사 면들의 방향이 얼마나 다양하게 퍼져 있는지를 보아야 한다. Chapter 04에서 소개한 **Roughness**는 이 Surface 거칠기 관계를 제어하는 입력이다. 여기서는 그 값을 Microfacet 분포와 연결한다.

---

### Roughness Changes the Distribution

작은 면들이 비슷한 방향을 바라보면 반사 방향도 좁게 모인다. 여러 방향을 바라보면 반사되는 방향도 넓게 퍼진다. Roughness는 이런 분포의 퍼짐을 조절하는 Material Parameter다.

일반적인 0–1 입력 범위에서는 다음과 같이 이해한다.

- Roughness = 0 에 가까울수록 매우 매끄러운 Surface
- Roughness = 1 에 가까울수록 매우 거친 Surface

실제 분포의 계산 Parameter로 어떻게 변환하는지는 Model과 구현에서 확인한다. 표시되는 Roughness Slider와 분포 식의 Parameter가 항상 같은 값이라고 가정하지 않는다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_11.png" width="80%">
</p>

그림은 반사 응답이 좁게 집중되거나 넓게 퍼지는 차이를 읽는 데 사용한다. 같은 Light와 Material 조건에서 Roughness를 바꾸어 방향 응답이 어떻게 달라지는지 비교한다.

---

### Spread, Peak, and Reflectance Are Different

Roughness가 작으면 작은 면의 방향 변화가 적어 좁은 방향에 반사가 모일 수 있다. Roughness가 크면 더 다양한 방향으로 분포하여 Highlight가 넓어진다. 따라서 Camera가 있는 한 방향의 Peak와 밝기도 바뀔 수 있다.

그러나 Roughness를 Material의 반사율을 직접 늘리고 줄이는 독립적인 강도 Slider로 생각하지 않는다. 입력의 주된 역할은 분포를 제어하는 것이다. **반사가 퍼지는 정도**와 **Material이 입사각에서 반사하는 비율**은 서로 다른 관계이며, 뒤의 Fresnel F와도 구별한다.

> **Roughness는 방향 분포를 바꾼다. 분포가 바뀌면 관찰 방향의 응답도 달라지지만, 이것을 모든 반사 관계를 한꺼번에 제어하는 밝기 값으로 취급하지 않는다.**

이렇게 역할을 나누면 같은 Base Color의 Surface가 Roughness 변화만으로 다른 모습이 되는 이유도 설명할 수 있다. Color가 같은데 반사 방향의 퍼짐이 달라진 것이다.

---

### From a Material Input to a Distribution Function

Roughness라는 값만으로 어느 방향의 Microfacet이 얼마나 존재하는지가 계산되는 것은 아니다. 그 입력을 어떤 분포 함수에 적용할지 정해야 한다.

예를 들어 같은 Roughness 입력이라도 선택한 분포의 모양과 Parameter 변환이 다르면 방향 응답은 달라질 수 있다. Roughness는 조절할 입력이고, D는 그 입력을 사용해 필요한 방향의 분포 밀도를 평가하는 함수다.

---

### Key Takeaways

- Roughness는 Surface 미세 방향의 퍼짐과 관계되는 Material 입력이다.
- 작은 Roughness는 좁은 반사 응답, 큰 Roughness는 넓은 반사 응답과 연결된다.
- 분포가 바뀌면 관찰 방향의 Peak도 달라질 수 있지만, Roughness를 독립적인 Reflectance 강도 Slider로 보지 않는다.
- 실제 분포는 선택한 함수와 Parameter 변환을 함께 확인해야 한다.

반사가 넓거나 좁다는 직관을 준비했다. 다음에는 **현재 H 방향에 필요한 작은 면이 얼마나 모여 있는가?**를 계산하는 D를 살펴본다.

---

## 5.12 Normal Distribution Function (D)

### Why Roughness Alone Is Not Enough

Roughness가 큰 Surface는 작은 면들의 방향이 넓게 퍼질 수 있다. 하지만 넓게 퍼진다는 말만으로는 현재 Light와 Camera에 필요한 방향의 응답을 계산할 수 없다. 어떤 방향에 많이 모이고 어떤 방향에는 적게 모이는지를 알아야 한다.

5.9에서 고정된 L과 V 사이에 거울 반사를 만드는 Facet 방향은 H였다. 이제 질문은 그 방향 부근에 얼마나 많은 작은 면이 존재하는가다. 이 질문에 답하는 함수가 **NDF(Normal Distribution Function)**이며, 기호는 **D**다.

---

### What Is Being Distributed?

여기서 Normal은 정규분포라는 통계 모델 이름이 아니다. 각각의 Microfacet이 어느 방향을 향하는지를 나타내는 Normal이다. NDF는 **작은 면의 Normal들이 방향별로 어떻게 분포하는지** 나타낸다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_12.png" width="80%">
</p>

큰 Surface의 기준 N은 같더라도 작은 면의 Normal은 여러 방향으로 퍼질 수 있다. D(H)를 평가한다는 것은 이 분포에서 현재 Reflection 관계에 필요한 H 방향을 확인한다는 뜻이다. 모든 면을 H로 돌린다는 뜻은 아니다.

---

### Density Is Not a Probability at One Direction

방향 분포를 말할 때는 한 방향의 함수 값과 넓은 방향 영역에 포함된 전체 비율을 구별해야 한다. 아주 좁은 방향 영역에 많은 작은 면이 모이면, 그 방향 부근의 **Density**, 즉 밀도는 높을 수 있다.

밀도는 일정한 방향 범위당 얼마나 모였는지를 나타내므로, 단일 방향의 D 값을 곧바로 0–1 확률이라고 읽지 않는다. 구간 전체의 양을 보려면 밀도를 해당 범위에 대해 더해야 한다. 좁고 높은 분포가 가능하다는 직관을 먼저 준비한다.

<details>
<summary>Technical Note — NDF Normalization and Solid Angle</summary>

**Solid Angle**은 방향들이 차지하는 입체적인 범위다. 평면에서 각도가 방향의 범위를 나타내듯, 3차원에서도 작은 방향 묶음의 범위를 측정할 수 있다. 단위 **sr**는 **Steradian**을 뜻한다.

여기서 말하는 "Normal"은 정규분포(Normal Distribution)가 아니라 **Surface Normal**을 의미한다. 따라서 Normal Distribution Function은 Surface Normal의 방향 분포 밀도를 나타내는 함수라고 이해하면 된다. D(H)는 단일 방향의 0–1 확률이 아니며 1보다 클 수 있다. 일반적인 Microfacet NDF는 반구에서 D(m)·max(0,N·m)을 Solid Angle에 대해 적분한 값이 1이 되도록 정규화한다.

이 정규화는 작은 면들의 투영 면적이 큰 Surface의 면적 관계와 맞도록 한다. 이때 적분은 반구 전체 방향의 기여를 더하는 연산이다. Density라는 직관은 본문에서 사용하고, 계산 모델을 검토할 때는 이 정밀 조건도 확인한다.

</details>

---

### Roughness Is an Input, D Is the Evaluation

Roughness는 얼마나 넓게 퍼진 Surface를 나타낼지 조절하는 입력이다. D는 선택한 분포와 그 입력을 이용해 현재 방향의 밀도를 계산한다. 두 역할을 구별하면 Roughness 값만을 그대로 반사량으로 곱하는 이유가 없다는 것을 알 수 있다.

또 D(H)가 크더라도 그것만으로 최종 Reflection이 정해지지 않는다. 반사 면이 Light와 Camera에서 보이는지, 입사각에서 얼마나 반사하는지, 전체 BRDF의 방향 조건이 무엇인지도 필요하다. 이 관계는 5.10에서 확인한 D·G·F와 분모에 연결된다.

---

### Common Distributions and Their Names

대표적인 분포에는 다음이 있다.

- Beckmann Distribution
- GGX (Trowbridge-Reitz Distribution)

**GGX**는 **Trowbridge–Reitz Distribution**이라고도 부르는 Microfacet 방향 분포의 이름이다. 앞에서 준비한 작은 면의 방향 밀도를 계산하는 분포 중 하나다.

분포의 중심에서 멀어진 방향에도 낮은 응답이 남는 바깥 부분을 **Tail**, 즉 꼬리라고 한다.

Beckmann과 GGX는 서로 다른 분포 모양을 가진다. GGX의 긴 Tail은 Highlight 바깥으로 퍼지는 응답을 표현하는 데 유용하다. 어떤 분포가 모든 Material에 항상 더 정확한 것은 아니다. Roughness에서 분포 Parameter로의 변환과 선택한 G는 구현별로 확인한다.

> **Implementation Note — Model Choice**
>
> Foundation에서는 D가 방향 분포 밀도라는 관계를 이해한다. 구체적인 분포 유도와 비교 실험은 Advanced로 남긴다. 사용할 Model의 Roughness 변환과 G를 함께 확인하며, Distribution 이름만 보고 구현이 같다고 판단하지 않는다.

---

### Key Takeaways

- NDF는 Microfacet Normal의 방향 분포를 나타내는 함수이며 D로 표기한다.
- D(H)는 현재 Light와 View 사이에 반사를 만들 방향의 밀도다.
- D 값은 단일 방향의 0–1 확률이 아니며, 정규화는 투영 면적과 방향 영역을 함께 고려한다.
- Roughness 입력, 분포 선택, Parameter 변환, G의 조합을 구별한다.
- GGX와 Beckmann은 서로 다른 분포 모양을 제공한다.

H 방향의 면이 있어도 빛의 경로가 가려질 수 있다. 다음 절에서는 **존재하는 면이 실제로 Light와 Camera에서 보이는가?**라는 질문을 G로 연결한다.

---

## 5.13 Geometry Function (G)

### Why an Existing Facet May Not Contribute

작은 거울 하나가 Light를 Camera 쪽으로 반사할 방향을 가지고 있다고 생각해 보자. 방향 관계는 맞지만 그 옆의 높은 요철이 Light를 막으면 이 거울에 빛이 도착하지 못한다. 반대로 Light는 도착했어도 Camera 쪽에서 다른 면에 가려지면 그 반사를 볼 수 없다.

D는 이런 경로가 열려 있는지까지 평가하는 함수가 아니다. D로 반사에 필요한 방향의 면이 얼마나 존재하는지 확인했다면, 이제 **그 면이 양쪽 방향에서 실제로 보이는가?**를 확인해야 한다. 이 역할을 Geometry Function G가 담당한다.

---

### Shadowing on the Light Side

**Shadowing**은 Light가 들어오는 쪽에서 다른 Microfacet이 길을 막는 현상이다. 원하는 작은 면이 분포에 포함되어 있어도, Light 방향에서 가려져 있으면 빛을 받지 못한다.

여기서 말하는 Shadowing은 Surface의 미세 구조 사이에서 발생한다. 장면의 큰 Object가 다른 Object에 드리우는 그림자와 같은 계산 입력이라고 가정하지 않는다. 5.10에서 구분한 Scene Visibility와 평가하는 규모가 다르다.

---

### Masking on the View Side

**Masking**은 Camera 쪽에서 다른 Microfacet이 반사 면을 가리는 현상이다. 빛을 받고 반사할 수 있는 면도 관찰 방향에서 보이지 않으면 그 방향의 응답에 그대로 포함할 수 없다.

두 현상은 모두 작은 면끼리 가리는 관계지만, Shadowing은 Light 쪽 경로를 보고 Masking은 View 쪽 경로를 본다. 한쪽만 열려 있어도 최종 반사 관계가 완성되는 것은 아니므로 둘을 함께 고려한다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_13.png" width="80%">
</p>

그림에서는 Light가 들어오는 길과 반사된 빛이 View 쪽으로 나가는 길을 따로 읽는다. 이것이 G가 L과 V를 함께 사용하는 이유다.

---

### The Role of G

G는 Microfacet 사이의 Shadowing과 Masking 때문에 줄어드는 기여를 반영한다. D가 평가한 방향 분포가 모두 자유롭게 빛을 주고받는 것처럼 계산하지 않도록 하는 항이다.

Surface의 방향 분포가 같아도 선택한 차폐 모델과 Light/View의 관계에 따라 응답이 달라질 수 있다. 따라서 G는 D의 밀도와 같은 값도 아니고, Camera로 나가는 최종 Radiance 자체도 아니다. 전체 Model 안에서 미세 차폐를 반영하는 역할이다.

> **Implementation Note — G and Scene Visibility**
>
> G는 Microfacet 차폐에 따른 감쇠를 반영하며, 그 자체가 최종 Reflection 결과나 Scene Visibility인 것은 아니다. 다른 Object가 Light를 가리는 Vis를 G로 대체하거나 같은 차폐를 두 번 반영하지 않는다.

---

### Named Geometry Functions

Rendering에서는 선택한 분포와 차폐 가정을 계산 가능한 함수로 표현한다. 다음 이름들이 등장한다.

- Smith Geometry Function
- Schlick-GGX Geometry Function

Smith는 Microfacet의 차폐를 통계적으로 다루는 접근의 이름이며, Schlick-GGX는 실시간 구현에서 등장하는 근사 표현의 이름이다. 이런 이름을 보았다고 모든 구현이 같은 수식이나 Parameter 변환을 사용한다고 생각하지 않는다. 선택한 GGX 분포와 G의 계산 방식을 함께 확인한다.

오늘날 대부분의 PBR에서는 Smith 기반 Geometry Function을 사용하며, GGX Distribution과 함께 사용하는 경우가 많다. 이번 Chapter에서는 정밀 유도보다 왜 차폐 항이 필요한지와 어디에 적용되는지를 이해한다. 구체적인 근사식의 선택과 차이는 해당 구현을 검토할 때 확인한다.

---

### Key Takeaways

- Shadowing은 Light 쪽, Masking은 View 쪽의 Microfacet 차폐다.
- D로 방향 분포를 평가해도 그 면이 양쪽에서 보이는지는 별도 관계다.
- G는 이 차폐에 따른 감쇠를 반영하는 항이다.
- G, D, 최종 Reflection, Scene Visibility는 서로 다른 역할이다.

분포와 경로를 확인했다. 이제 같은 면이라도 입사각에 따라 얼마나 반사하는지가 달라지는 관계를 살펴본다. 이것이 Fresnel F의 질문이다.

---

## 5.14 Fresnel (F)

### Why Can a Surface Reflect More at an Oblique Angle?

물이나 유리의 Surface를 정면에서 볼 때와 낮은 각도에서 볼 때를 비교해 보자. 비스듬한 각도에서는 주변 환경의 반사가 더 잘 보일 수 있다. 같은 Material이라도 관찰 관계에 따라 반사의 모습이 달라지는 것이다.

여기서는 화면의 최종 밝기부터 계산하려 하지 않고, Material이 입사한 빛 중 얼마를 반사하는지 묻는다. 이 반사되는 비율을 **Reflectance**, 즉 반사율이라고 한다. Fresnel은 입사각과 Material의 광학 성질에 따라 이 Reflectance가 달라지는 관계다.

---

### Reflectance and Final Brightness Are Different

일반적인 반사 관계에서 비스듬한 입사각은 정면 입사보다 높은 Reflectance와 연결될 수 있다. 그래서 매끄러운 Interface를 낮은 각도에서 볼 때 반사가 강하게 보이는 사례가 있다. **Interface**는 빛이 만나는 서로 다른 매질의 경계면을 말한다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_14.png" width="80%">
</p>

그림은 Angle에 따라 반사율이 바뀌는 관계를 이해하는 데 사용한다. 그러나 반사율이 커졌다는 이유만으로 화면의 모든 가장자리가 더 밝아진다고 결론 내리지 않는다. 그 방향에서 실제 도착하는 Light, 차폐, Roughness, 화면 표시 과정도 결과에 영향을 준다.

뒤에서 Artistic Rim을 만들 때도 N과 V의 각도 관계를 사용하지만, 원하는 테두리를 만드는 Mask와 물리적 Reflectance는 목적이 다르다. 각도에 반응한다는 공통점만으로 둘을 같은 계산이라고 부르지 않는다.

---

### A Normal-incidence Reference Value

각도에 따라 반사율을 계산하려면 먼저 기준값이 필요하다. **F0**는 빛이 경계면에 정면으로 들어올 때의 Reflectance다. 이 기준값을 알고 현재 Angle을 알면 반사율 변화의 근사를 만들 수 있다.

Chapter 04에서 소개한 **Dielectric**과 Metal의 반사 특성도 이 기준값에 연결된다. Dielectric은 여기서 유리나 물처럼 비금속 절연체에 해당하는 범위이고, Metal은 그와 다른 광학 성질을 갖는다. 모든 Material에 하나의 F0를 넣는다고 같은 물리적 의미가 되는 것은 아니다.

---

### Schlick Approximation

정밀한 Fresnel 평가 대신 실시간 Rendering에서 쓰는 대표적인 근사를 **Schlick Approximation**이라고 한다. Approximation은 원하는 관계를 적은 계산으로 비슷하게 표현하는 근사다. 이 근사는 F0를 기준으로 현재 Angle에서의 Reflectance를 계산한다.

각도 입력 **cosTheta**는 어느 면을 기준으로 입사하는지를 나타낸다. cosTheta가 정면 관계에 가까우면 F0 쪽 응답을 갖고, 비스듬한 관계로 갈수록 반사율을 크게 만든다. 이 관계를 식으로 쓰면 다음과 같다.

```text
F = F0 + (1 - F0) * pow(1 - cosTheta, 5)
```

식에서 F0는 정면의 기준이고, 거듭제곱 부분은 비스듬한 입사에 따른 변화를 만든다. 이 값은 반사율 응답이며 Light의 실제 세기나 화면의 표시 RGB를 직접 출력하는 값이 아니다.

---

### Which Normal Defines the Angle?

매끄러운 경계에서는 그 Interface Normal을 기준으로 입사각을 측정한다. Microfacet Reflection에서는 반사에 기여하는 작은 면의 Normal을 기준으로 평가해야 한다. 고정된 L과 V의 반사에 필요한 Facet Normal이 H였으므로, 여기서는 H와의 관계를 사용한다.

F0는 정면 입사 Reflectance이다. 매끄러운 Interface에서는 cosTheta가 입사 방향과 Interface Normal의 Dot Product이며, Microfacet Specular에서는 반사에 기여하는 Facet Normal H를 사용해 cosTheta=clamp(dot(V,H),0,1)로 평가한다. 이를 항상 N·V로 대체하지 않는다.

큰 Surface의 N과 작은 Facet의 H가 다를 수 있으므로, 항상 N·V를 쓰면 같은 Fresnel을 평가한 것이 아니다. 5.6의 Half Vector가 Model의 여러 부분에 연결된다는 점을 다시 확인할 수 있다.

---

<details>
<summary>Technical Note — F0, Optical Parameters, and a Numerical Check</summary>

굴절률은 Material 안에서 빛의 진행 관계를 나타내는 광학 입력이다. 아래 η1과 η2는 경계 양쪽의 굴절률이다. 비흡수 Dielectric의 정면 관계에서는 이 두 값으로 F0를 계산할 수 있다. 이것을 모든 재질의 고정된 0.04라는 규칙으로 바꾸지 않는다.

비흡수 Dielectric의 정면 입사에서는 F0=((η1-η2)/(η1+η2))²이다. 공기 η1≈1, 유리 계열 η2≈1.5의 예는 F0≈0.04가 된다. 이는 모든 Material의 고정값이 아니다. F0=0.04, cosTheta=0.5이면 Schlick 값은 약 0.07이다.

이 수치 예시는 Formula와 기호의 관계를 확인하는 검산이다. Material의 범위와 cosTheta의 의미를 고정한 상태에서 읽는다. Metal이나 다른 광학 상황에 동일한 고정값을 적용한다는 뜻은 아니다.

</details>

---

### Connecting F to Material Inputs

Chapter 04의 Metallic 입력은 단순한 Highlight 세기 Slider가 아니었다. Material을 Dielectric과 Metal의 응답으로 구별하면서 Base Color가 제어하는 역할도 달라진다. 이 관점을 Fresnel Reflectance와 연결하면 왜 같은 Color 입력을 모든 재질에서 똑같이 해석하지 않는지 알 수 있다.

Metallic Workflow에서는 Dielectric의 Base Color가 주로 Diffuse를, Metal의 Base Color가 주로 RGB Specular Reflectance를 제어한다. 순수 Metal은 이 Model에서 Diffuse 성분을 두지 않는다. Roughness는 분포를 조절하는 값이며 Metallic은 단순한 Highlight 강도 Slider가 아니다.

Roughness는 방향 분포, Metallic과 Base Color는 선택한 Material Model의 성분과 반사율 관계에 연결된다. 서로 다른 역할의 입력을 한 번에 모두 밝기 조절이라고 설명하지 않는다.

---

> **Implementation Note — Approximation and Display**
>
> Schlick은 근사이며 모든 광학 현상을 재현하지 않는다. 입사각에 따른 Reflectance 증가가 화면 가장자리의 최종 밝기 증가를 항상 보장하지도 않는다. Incoming Light, Visibility, Roughness, 표시 변환을 함께 고려한다. Chapter 07/08의 Artistic Rim과도 구분한다.

여기서 표시 변환은 계산한 Light를 화면에 표시할 값으로 바꾸는 과정이다. **Exposure**는 표시를 위한 노출 관계이고, **Tone Mapping**은 계산한 밝기 범위를 표시 가능한 범위로 다루는 과정이다. 입력 빛과 이런 표시 과정에 따라 화면의 결과가 달라질 수 있다. 이 과정은 Chapter 06에서 연결한다. Fresnel과 Artistic Rim의 목적 차이는 Chapter 07/08에서도 유지한다.

---

### Key Takeaways

- Fresnel은 입사각과 Material의 광학 성질에 따라 Reflectance가 달라지는 관계다.
- F0는 정면 입사 반사율의 기준값이며 모든 재질에서 같은 고정값이 아니다.
- Microfacet Specular에서는 반사에 기여하는 Facet Normal H를 기준으로 평가한다.
- Schlick은 실시간 평가에 사용하는 근사이며 최종 화면 밝기를 직접 보장하지 않는다.
- Roughness, Metallic, Scene Visibility, Artistic Rim은 F와 역할을 구별한다.

---

### Part III Summary

세 질문을 다시 연결해 보자. Roughness와 D는 작은 면의 방향이 어떻게 퍼지고 현재 H에 얼마나 모이는지를 다룬다. G는 그 면이 Light와 View에서 미세 구조에 가려지지 않는지를 반영한다. F는 현재 입사각에서 Material이 얼마를 반사하는지 평가한다.

- **Normal Distribution Function(D)** 는 반사에 기여하는 Microfacet의 방향 분포를 평가한다.
- **Geometry Function(G)** 는 Microfacet 사이의 Shadowing과 Masking을 고려한다.
- **Fresnel(F)** 은 입사각에 따른 Reflectance 변화를 평가한다.

세 요소는 하나의 Model 안에서 함께 작동한다. 전체 BRDF에는 5.10에서 설명한 분모와 방향 조건도 포함되므로 D·G·F의 곱만을 완성된 BRDF로 취급하지 않는다.

---

**Part IV — Light and BRDF**

Reflection의 방향과 Material 응답을 설명했지만, 아직 이 Model들이 반사하는 빛의 양을 정확히 정의하지 않았다. 다음에는 **Rendering이 빛을 어떤 기준으로 측정하는가?**를 살펴본다. Radiometry로 입사·출사 물리량을 준비한 뒤 BRDF의 공통 정의를 이해한다.

---

## 5.15 Radiometry

### What Is a Reflection Model Reflecting?

지금까지는 반사가 어느 방향으로 나가고, 얼마나 퍼지고, 어느 면이 가려지는지를 살펴보았다. 그런데 이 모델은 정확히 무엇을 반사하고 있을까? 일상적으로는 빛이라고 말하지만, 계산에서는 어떤 빛의 양을 입력하고 어떤 양을 출력하는지 정해야 한다.

같은 밝다는 말도 다른 상황을 가리킬 수 있다. 광원이 전체로 얼마나 많은 에너지를 보내는지, 작은 Surface 면적에 얼마나 도착하는지, Camera 방향으로 얼마나 나가는지는 서로 다른 질문이다. 이들을 하나의 이름으로 부르면 비교와 단위를 맞추기 어렵다.

빛을 에너지 전달의 관점에서 측정하는 체계를 **Radiometry**라고 한다. 여기서는 여러 이름을 암기하기보다 각 물리량이 어떤 질문에 답하는지를 먼저 살펴본다.

---

### Energy and Power Answer Different Questions

**Energy**는 에너지의 양이다. 일정 시간 동안 빛이 전달한 전체 Energy를 말할 수 있다. 하지만 Rendering에서 광원의 출력을 비교할 때는 **얼마나 빠르게 Energy를 보내는가?**도 필요하다.

단위 시간당 전달되는 Energy를 **Power**라고 한다. 더 많은 Energy를 더 짧은 시간에 보내면 Power가 커진다. 그래서 빛의 총 Energy와 빛이 전달되는 시간당 양을 같은 물리량으로 취급하지 않는다.

Energy의 단위 J는 **Joule**, Power의 단위 W는 **Watt**다. W=J/s라는 관계는 단위 시간당 Energy라는 뜻을 그대로 나타낸다. 이제 Power를 어디에 대해 나누어 측정하는지에 따라 다른 물리량을 준비한다.

---

### Radiant Flux: How Much Light Is Transferred per Time?

**Radiant Flux Φ**는 전달되는 Radiant Energy의 시간당 양이다. 광원이 전체로 얼마나 많은 빛을 보내는지 같은 총량 질문에 사용한다. 아직 Surface 면적이나 한 방향의 범위로 나누지 않은 Power다.

따라서 Flux는 광원에 저장된 전체 Energy 자체가 아니다. 단위가 W라는 사실이 시간당 전달량이라는 구분을 보여준다. 전체 Flux가 같아도 어느 방향으로 얼마나 분배되는지에 따라 Surface가 받는 빛은 달라질 수 있다.

---

### Irradiance: How Much Reaches a Surface Area?

**Irradiance E**는 Surface의 단위 면적에 도착하는 입사 Flux다. 같은 빛의 묶음이 작은 면적에 모이면 E가 크고, 더 넓은 면적에 퍼지면 E가 작아진다. 5.4에서 비스듬한 Light가 넓은 면적에 퍼진다고 설명한 관계가 여기에 연결된다.

단위는 W/m²이다. 시간당 전달되는 빛을 Surface 면적으로 나누는 것이다. 이것은 광원의 전체 Flux와 다른 질문이며, Surface에서 특정 방향으로 나가는 응답인 Radiance와도 구별한다.

---

### Radiant Intensity: How Much Is Sent into a Directional Range?

광원이 전체로 같은 Flux를 보내도 넓은 방향에 퍼뜨리는지 좁은 방향에 집중하는지에 따라 결과는 다르다. **Radiant Intensity I**는 광원이 단위 Solid Angle에 방출하는 Flux다. 방향별로 얼마나 보내는지를 표현한다.

5.12의 Solid Angle은 입체적인 방향 범위였고, 단위 sr는 Steradian이었다. Intensity의 단위 W/sr는 시간당 빛을 그 방향 범위로 나눈다는 뜻이다. Surface에 도착한 면적당 양 E와 광원이 특정 방향에 보내는 양 I를 구별한다.

여기서 I는 Radiant Intensity의 기호다. 5.3에서 실제 입사 진행 방향을 쓴 Vector I와 같은 글자지만 서로 다른 물리량이다. 단위와 현재 문맥으로 구별한다.

---

### Radiance: What Travels in a Particular Direction?

Camera는 Surface에서 여러 방향으로 나가는 빛 중 관찰 방향의 빛을 본다. 이 방향별 전달을 다루는 물리량이 **Radiance L**이다. 5.4의 Outgoing Radiance는 Surface에서 특정 방향으로 나가는 Radiance였다.

Radiance는 Flux를 방향 범위뿐 아니라 그 진행 방향에서 보이는 **Projected Area**, 즉 투영 면적으로도 나누어 표현한다. Surface를 비스듬히 보면 방향에서 보이는 면적이 줄어든다는 관계를 떠올리면 된다.

그래서 Radiance의 단위는 W/(m²·sr)이다. Irradiance의 면적당 입사 양이나 Intensity의 광원 방향당 출력과 역할이 다르다. 입사 Radiance와 출사 Radiance를 구별하면 BRDF가 Surface의 응답을 어떻게 연결하는지 정의할 수 있다.

여기서 L은 Radiance의 물리량 기호다. 앞의 Light Direction L은 Unit Vector였다. Radiance L에는 물리 단위가 있으므로, 같은 글자를 보았다고 같은 데이터로 해석하지 않는다.

---

### Comparing the Four Quantities

앞에서 나눈 측정 질문을 정확한 정의와 단위로 비교한다. 전체 Power, 면적, 방향 범위가 각 정의에서 어떻게 다른지 확인한다.

- **Radiant Flux(Φ)** : 단위 시간당 전달되는 Radiant Energy, 단위 W (= J/s).
- **Irradiance(E)** : Surface의 단위 면적당 입사 Flux, 단위 W/m².
- **Radiance(L)** : 진행 방향에 수직인 투영 면적과 Solid Angle당 Flux, 단위 W/(m²·sr).
- **Radiant Intensity(I)** : 광원이 단위 Solid Angle로 방출하는 Flux, 단위 W/sr.

Solid Angle은 방향들이 차지하는 입체적인 범위이며 단위는 sr이다. Energy와 Power, 면적당 값과 방향당 값을 구분하면 BRDF의 단위를 이해할 수 있다.

| Question | Quantity | What Is Being Distinguished? |
|---|---|---|
| 시간당 전체로 얼마나 전달되는가? | Radiant Flux | Energy와 Energy/time |
| Surface의 일정 면적에 얼마나 들어오는가? | Irradiance | 전체 Power와 입사 면적당 Power |
| 광원이 일정 방향 범위에 얼마나 보내는가? | Radiant Intensity | 전체 출력과 광원의 방향별 출력 |
| Surface와 방향을 함께 고려해 얼마나 전달되는가? | Radiance | 투영 면적과 방향 범위를 가진 전달량 |

표의 질문은 서로 바꿔 써도 되는 동의어가 아니다. 전체 Flux, Surface 면적당 Irradiance, 방향별 Radiance를 구별해야 다음 BRDF 식의 입출력과 단위가 맞는다.

---

### Key Takeaways

- Radiometry는 빛을 에너지 전달의 관점에서 측정하는 체계다.
- Flux는 Energy 자체가 아니라 시간당 전달되는 Energy이며 W 단위를 갖는다.
- Irradiance는 Surface 면적당 입사 Flux다.
- Intensity는 광원의 방향 범위당 출력이고 Radiance는 투영 면적과 방향 범위를 함께 고려한다.
- Reflection Model과 Light의 입력 물리량을 구별하면 BRDF의 응답과 최종 Lighting을 분리할 수 있다.

다음에는 Reflection Model마다 다른 식을 쓰더라도 같은 입사·출사 질문으로 묶을 수 있는지 살펴본다. 처음에 예고한 BRDF가 이 공통 Surface 응답을 정의한다.

---

## 5.16 BRDF Framework

### Why Do Different Models Need a Common Description?

Lambert, Phong, Blinn-Phong, Cook-Torrance는 계산 방식이 다르다. 그렇지만 Surface가 빛에 응답하는 방식을 설명한다는 목적은 같다. Model마다 별도의 질문으로 외우면 서로 무엇이 다른지 비교하기 어렵다. 같은 입사·출사 관계를 기준으로 묶을 방법이 필요하다.

먼저 Material과 Surface의 상태를 고정하고 특정 방향에서 빛을 보낸다고 생각해 보자. 그중 특정 관찰 방향으로 나가는 빛에 Surface가 얼마나 기여하는지 묻는다. 이 공통 Surface 응답을 정의하는 것이 **BRDF(Bidirectional Reflectance Distribution Function)**다.

Bidirectional은 입사와 출사라는 **두 방향**을 뜻한다. Reflectance는 반사 특성, Distribution은 방향에 따른 분포, Function은 입력 관계를 응답으로 평가하는 함수라는 뜻이다. Full Name을 외우기보다 **어느 쪽에서 오는 빛이 어느 쪽으로 나가는 빛에 어떻게 연결되는가?**라는 질문을 기억한다.

---

### Two Directions Describe One Surface Relationship

BRDF를 읽을 때도 5.3에서 정한 방향 규칙을 사용한다. 두 Direction이 빛의 진행을 같은 부호로 나타낸다고 생각하지 말고, 현재 Surface에서 어느 쪽을 가리키는지 확인한다.

여기서 두 Vector는 모두 Surface에서 바깥을 향하도록 정의한다. Incoming Direction L은 광원 쪽을 가리키며 빛의 실제 진행 방향은 -L이다.

---

### Material Response and Light Amount Are Different

같은 Material에 같은 방향으로 더 강한 Light를 비추면 더 많은 빛이 나갈 수 있다. 그러나 Light가 강해졌다고 Material 자체의 반사 관계가 바뀐 것은 아니다. BRDF는 이 두 역할을 분리해 Surface의 응답을 정의한다.

Radiometry에서 Surface에 도착하는 면적당 빛의 양은 Irradiance였다. 관찰 방향으로 나가는 빛은 Outgoing Radiance였다. BRDF는 작은 입사 방향의 Irradiance 기여가 특정 방향의 Outgoing Radiance에 얼마나 기여하는지 나타낸다.

이 관계를 간단히 질문으로 쓰면 다음과 같다.

> **특정 방향에서 도달한 Irradiance가 특정 방향의 Outgoing Radiance에 얼마나 기여하는가?**

이제 용어만으로 추측하지 않아도 된다. 앞 절에서 준비한 두 물리량의 차이를 Surface 응답으로 연결한 질문이다. 정확한 출력 단위와 Formula는 다음 절에서 차례로 확인한다.

---

### A Framework, Not One Algorithm

Lambertian BRDF는 이상적인 Diffuse 응답을 표현한다. Microfacet BRDF는 작은 반사 면의 분포·차폐·반사율로 Specular 응답을 표현한다. 서로 다른 Model이지만, 각 Surface의 입사·출사 응답을 BRDF라는 같은 정의로 평가할 수 있다.

BRDF는 특정 Algorithm 이름이 아니다. Lambertian BRDF와 Microfacet BRDF는 이 정의를 만족시키는 서로 다른 Model이다. 앞에서 소개한 단순 Phong/Blinn-Phong Highlight Response를 그대로 Energy-conserving BRDF라고 부르지는 않는다. 정규화와 Diffuse/Specular 에너지 배분을 함께 확인해야 한다.

여기서 단순 Phong/Blinn-Phong Response와 정규화·에너지 배분을 갖춘 BRDF 변형을 구별한다. 방향을 입력받는 식이라는 이유만으로 모든 응답을 완성된 물리 BRDF라고 부르지는 않는다.

Chapter 08의 Artistic Mask도 방향과 Material 입력을 사용할 수 있다. Mask는 원하는 모양을 제어하는 값이고 BRDF는 물리량 사이의 Surface response를 정의한다. 교육용 Highlight나 Rim이 BRDF와 같은 입력 일부를 사용해도 목적과 출력은 다를 수 있다.

---

### Key Takeaways

- BRDF는 여러 Reflection Model을 입사·출사 Surface 응답이라는 공통 질문으로 묶는다.
- 두 Direction은 Surface에서 바깥으로 향하도록 정의하며 실제 입사 진행 방향은 -L이다.
- BRDF는 Material response이며 Incoming Light의 양이나 최종 Lighting Result와 구별한다.
- 이름이 붙은 Highlight Response나 Artistic Mask가 자동으로 완성된 물리 BRDF가 되는 것은 아니다.

공통 정의가 왜 필요한지 이해했다. 다음에는 이 응답을 실제로 평가하려면 어떤 입력이 필요하고, 계산 결과가 정확히 무엇인지 살펴본다.

---

## 5.17 BRDF Inputs and Output

### What Must Be Fixed Before Evaluating a Response?

같은 Light Direction을 사용해도 Surface가 회전하면 응답이 달라질 수 있다. 같은 Surface 방향에서도 Camera가 움직이면 Specular 관계가 달라진다. 방향이 같아도 Material의 Roughness나 반사율 입력이 바뀌면 다른 응답이 나온다.

따라서 BRDF를 평가할 때는 지금 계산하는 Shading Point의 **Material과 방향 기준**을 정해야 한다. L과 V만 공중에 있는 방향으로 준비하는 것이 아니라, 그 방향이 현재 Surface의 N과 어떤 관계인지 함께 평가한다.

N과 Direction은 같은 Space에서 비교한다. Unit Direction 조건도 유지한다. Chapter 02/03에서 서로 다른 Space나 길이를 섞으면 방향 비교의 의미가 바뀐다고 설명한 이유가 여기서 그대로 적용된다.

---

### Why Some Models Need a Tangent Basis

어떤 Material은 Surface를 따라가는 방향에 따라서도 반사 분포가 달라진다. 한 방향으로 결이 있는 금속을 떠올리면 된다. 이런 방향 의존 분포를 **Anisotropic**, 즉 이방성이라고 한다.

이 경우 Surface Normal만으로는 Surface 위에서 어느 쪽이 결 방향인지 정할 수 없다. Chapter 02/04에서 배운 **Tangent Basis**, 즉 Surface를 따라가는 기준 방향들이 추가로 필요하다. 모든 BRDF가 이 입력을 같은 방식으로 요구한다는 뜻은 아니며, 선택한 Model에 필요한 입력을 확인한다.

---

### Inputs at the Current Shading Point

앞에서 필요한 이유를 살펴본 입력을 표로 확인한다. 각 입력의 방향, 단위 조건, Material 역할을 따로 읽는다.

| Input | Meaning |
|---|---|
| L / ωi | Surface에서 입사 광원을 향하는 Unit Direction |
| V / ωo | Surface에서 출사 방향을 향하는 Unit Direction |
| N | 같은 Space의 Unit Shading Normal |
| Material | Base Color, Roughness, Metallic 등 선택한 Model의 Parameter |
| Tangent Basis | Anisotropic Model처럼 접선 방향이 필요한 경우의 기준 |

N과 Material은 간결한 기호 fr(ωi,ωo)에서 생략될 수 있지만 실제 평가에는 포함된다. Light Intensity를 Material Property와 혼동하지 않는다.

간단한 기호에서 생략했다는 것은 계산에 필요 없다는 뜻이 아니다. Surface와 Material을 고정한 함수로 쓸 때 두 방향을 드러내는 것이다. 광원이 얼마나 강한지는 이 Surface 입력과 구별한다.

---

### What Does the BRDF Output Mean?

어떤 방향에서 작은 입사 빛의 기여가 들어왔을 때, 특정 출사 방향으로 나가는 빛의 기여를 얼마나 만드는지 응답을 평가한다. 그 응답이 **fr**다. fr 자체가 모든 Light를 더한 최종 Surface 밝기는 아니다.

BRDF의 출력 fr은 **단위 입사 Irradiance당 특정 방향의 Outgoing Radiance 응답**이다. 단위는 sr⁻¹이며 최종 RGB 밝기나 0–1 비율 자체가 아니다. RGB Rendering에서는 파장별 특성을 RGB 세 성분으로 근사한다.

Irradiance의 단위 W/m²로 Radiance의 단위 W/(m²·sr)를 나누면 sr⁻¹가 남는다. 그래서 BRDF 값은 단위가 있는 방향 응답이며, 하나의 0–1 비율로만 제한되는 값이라고 읽지 않는다. Reflectance의 전체 Energy 관계와 한 방향의 BRDF 값은 서로 다른 질문이다.

---

### Two Small Changes Reveal the Difference

Material과 Light 중 하나의 입력만 바꾸면 어느 단계가 변하는지 분리해 확인할 수 있다. 같은 Material의 입력과 방향을 유지하는 경우와, Roughness 같은 Material 입력을 바꾸는 경우를 비교한다.

빛의 세기가 바뀌면 같은 Material의 BRDF는 그대로여도 최종 Radiance는 바뀐다. Roughness를 바꾸면 BRDF의 방향 분포가 달라져 Highlight가 변한다. 따라서 Shader에서 Material Response와 Incoming Light를 별도 입력으로 유지한다.

---

### Following the Light Contribution

Surface의 응답을 준비한 뒤 실제 들어오는 Light를 결합한다. 입사 방향 때문에 Surface가 받는 면적당 기여가 달라지는 Cosine도 포함한다. 여러 방향의 기여를 모으면 반사된 Radiance가 되고, Surface 자체의 Emission이 있으면 이를 더한다.

```text
Directions + Surface Basis + Material Properties → BRDF
Incoming Radiance + BRDF + Incident Cosine       → Reflected Contribution
Contributions over Incoming Directions          → Reflected Radiance
Reflected Radiance + Emitted Radiance           → Outgoing Radiance
```

여기서 **Contribution**은 하나의 입력 방향이나 Light가 결과에 더하는 기여를 뜻한다. 방향별 기여를 모으는 것과 하나의 BRDF 값을 평가하는 것은 서로 다른 단계다. **Emitted Radiance**는 Surface가 자체적으로 내보내는 빛으로, Highlight처럼 반사된 Light와 구별한다.

이것은 하나의 Surface에서 평가하는 관계이다. Light에서 직접 오는 기여를 **Direct Lighting**, 다른 Surface 등과 상호작용한 뒤 도착하는 기여를 **Indirect Lighting**이라고 한다. Chapter 06은 이 Direct/Indirect Lighting이 Incoming Radiance를 어떻게 제공하는지 연결한다. 그 전에 다음 절에서 이 Data Flow를 기호와 Formula로 확인한다.

---

### Key Takeaways

- BRDF는 현재 Shading Point의 방향 기준과 Material 입력을 사용한다.
- 간단한 기호에서 N과 Material이 생략되어도 실제 평가에서는 필요하다.
- fr은 sr⁻¹ 단위의 응답이며 최종 RGB 밝기나 0–1 비율 자체가 아니다.
- Light 세기 변화와 Material 입력 변화는 서로 다른 단계에서 결과를 바꾼다.
- BRDF, Incoming Radiance, 입사 Cosine, 방향별 합, Emission을 역할별로 나누어 계산한다.

---

## 5.18 BRDF Definition and Rendering Equation

### Start with One Small Incoming Directional Range

앞 절의 Data Flow를 식으로 표현할 차례다. 처음부터 전체 방향의 빛을 한꺼번에 생각하면 복잡해지므로, 작은 입사 방향 범위 하나만 선택해 보자.

그 범위에서 Li라는 Incoming Radiance가 Surface로 도착한다. Li는 방향을 가진 빛의 전달량이다. 이를 Surface 면적에 실제로 들어오는 기여로 바꾸려면, 빛이 N에 대해 얼마나 기울어져 있는지도 필요하다. 이것이 5.4의 입사 Cosine 관계다.

작은 방향 범위의 크기는 **dωi**로 쓴다. 여기서 d는 아주 작은 범위나 미소 기여를 나타내는 기호다. 이 범위가 만드는 작은 Irradiance 기여를 **dEi**, 그 기여가 특정 출사 방향에 만드는 작은 Outgoing Radiance를 **dLo**라고 한다.

이제 질문은 간단해진다. 작은 dEi가 들어왔을 때 특정 방향의 dLo가 얼마나 생기는가? 그 관계를 정의한 함수가 fr다.

---

### The BRDF Definition

현재 Surface 위치와 Material을 고정한다. 두 방향의 관계에 대한 정의는 다음과 같다.

```text
fr(ωi, ωo) = dLo(ωo) / dEi(ωi)
dEi(ωi)   = Li(ωi) * max(0, dot(N, ωi)) * dωi
```

첫 줄은 출사 Radiance의 작은 기여를 입사 Irradiance의 작은 기여와 연결한다. 둘째 줄은 입사 Radiance를 Surface가 받는 Irradiance 기여로 바꿀 때 Cosine과 방향 범위가 필요하다는 관계다.

Li와 Lo는 Radiance이며 E는 Irradiance이다. d는 작은 방향 영역이 만드는 미소 기여를 나타낸다. 입사각의 Cosine은 빛이 Surface의 실제 면적에 얼마나 분산되는지를 반영한다. fr 안에 Light Intensity를 넣는 것이 아니라 이 입사 기여와 곱해 사용한다.

왜 Light Intensity를 fr 안에 넣지 않는지도 알 수 있다. fr은 Surface의 응답이고, 실제 들어오는 빛의 기여는 dEi 또는 Li 쪽에서 제공한다. 같은 Light를 중복해서 넣거나 NdotL을 다른 의미로 반복 적용하지 않도록 역할을 구별한다.

---

### From One Contribution to All Incoming Directions

한 방향 범위의 기여를 이해했으므로 이제 Surface로 들어올 수 있는 여러 방향을 모아 보자. 여기서는 불투명한 Surface의 앞쪽 반사를 다루기 때문에, 앞면 위의 반구 방향을 사용한다. 이 방향 영역을 **Ω+**로 표기한다.

각 방향에서 들어오는 Li에 Surface 응답 fr과 입사 Cosine을 적용하고 그 기여들을 더한다. Formula에서 **∫**, 즉 적분은 이렇게 연속된 방향 영역의 작은 기여를 모두 모으는 연산이다. 먼저 합한다는 의미를 알고 기호를 읽으면 된다.

Surface가 자체적으로 빛을 내는 Emission이 있으면 이를 별도로 더한다. 반사된 빛과 자체 방출된 빛을 합쳐 특정 방향의 Outgoing Radiance를 만드는 관계가 **Rendering Equation**이다.

---

### Rendering Equation

Opaque Reflective Surface의 반구 Ω+에 대한 기본 관계는 다음과 같다.

```text
Lo(ωo) = Le(ωo)
       + ∫Ω+ fr(ωi, ωo) * Li(ωi) * max(0, dot(N,ωi)) dωi
```

Lo는 우리가 구하려는 출사 방향의 Radiance다. Le는 Surface 자체의 Emission이고, 적분 안의 항은 각 입사 방향에서 제공하는 반사 기여다. 입사 방향이 바뀌면 Li와 fr이 달라질 수 있으므로 여러 방향을 함께 평가한다.

이 식을 보면 BRDF 하나로 최종 Surface Color가 나오는 것이 아니라는 것을 다시 확인할 수 있다. Surface 응답 fr과 빛의 입력 Li가 따로 있으며, 면적당 입사 관계의 Cosine과 방향별 합이 결과를 만든다.

---

### Visibility Must Be Applied at the Right Stage

Light가 다른 Object에 가려져 현재 Surface에 도달하지 못한다면 입사 기여도 달라진다. 그런데 입력 Li가 이미 그 차폐를 반영한 값인지, 차폐 전 Light 기여인지에 따라 구현에서 Vis를 적용하는 위치가 달라진다.

Le는 Surface 자체의 Emission이다. Li는 해당 Surface에 실제 도달하는 Radiance이므로 이미 차폐된 값이라면 Visibility를 다시 곱하지 않는다. 차폐 전 Light 기여를 별도로 평가하는 구현에서는 해당 Light의 Vis를 한 번 적용한다. V는 View Direction, Vis는 Visibility로 표기를 구분한다.

같은 Visibility를 두 번 곱하면 한 번만 반영해야 할 차폐를 중복 처리할 수 있다. 반대로 차폐 전 입력인데 아무 처리도 하지 않으면 실제 도착하지 않는 Light가 포함될 수 있다. 따라서 **어떤 상태의 Light를 입력받는가?**가 먼저 정해져야 한다.

V는 관찰 방향 Vector이고 Vis는 빛의 경로 차폐다. 이름이 비슷하다고 같은 값으로 사용하지 않는다. G도 Microfacet의 미세 차폐라는 다른 역할이므로 이 구분을 함께 유지한다.

---

### Why Real-time Rendering Uses Approximations

매 Pixel에서 모든 입사 방향을 정밀하게 평가하려면 많은 계산이 필요하다. 실제로는 몇 개 Light의 기여를 평가하거나, 주변 환경을 선택한 방향에서 읽거나, 미리 준비한 조명 정보를 사용하는 방식으로 근사한다.

**Sampling**은 필요한 입력을 특정 위치나 방향에서 골라 평가하는 과정이다. **Probe**는 장면의 일부 위치에 준비한 조명 정보를 활용하는 구조를 말한다. 구체적인 Direct/Indirect 방식은 Chapter 06에서 연결하고, 여기서는 Surface response와 입력 Light를 제공하는 방식이 서로 다른 문제임을 이해한다.

BRDF는 Surface의 응답이며 어떤 Light를 어떻게 Sample할지는 별개의 문제이다.

---

### What Makes a Physical Reflection Model Valid?

보기 좋은 응답이라고 해서 수동 Material의 물리적 조건을 자동으로 만족하는 것은 아니다. 먼저 반사 응답이 음수가 되면 안 된다. 이를 **Non-negativity**, 즉 비음수 조건이라고 한다.

또 Surface가 입력받은 빛보다 더 많은 반사 Energy를 새로 만들지 않아야 한다. 5.5에서 소개한 Energy Conservation이다. 하나의 출사 방향 값만 볼 것이 아니라 모든 출사 방향의 기여를 모아 이 조건을 판단해야 한다.

일반적인 **Reciprocal Material**에서는 입사와 출사 방향을 교환해도 같은 BRDF를 갖는 관계가 성립한다. 이 방향 교환 관계를 **Reciprocity**, 즉 상호성이라고 한다. 모든 광학 상황을 무조건 이 한 조건으로 설명하지 않고 적용하는 Material 범위를 유지한다.

<details>
<summary>Technical Note — Physical Constraints and Model Composition</summary>

일반적인 수동 반사 Material에는 Non-negativity와 Energy Conservation이 필요하다. 고정된 입사 방향에 대해 fr·max(0,N·ωo)를 출사 반구 전체에서 적분한 값이 1을 넘지 않아야 한다. 일반적인 Reciprocal Material은 입사·출사 방향을 교환해도 같은 BRDF를 가진다.

이 조건은 식에 PBR 또는 Cook-Torrance라는 이름을 붙이는 것만으로 충족되지 않는다. Diffuse와 Specular를 합칠 때의 에너지 배분, Model의 정규화, Parameter 범위를 함께 확인한다. Multiple Scattering 보정 등 정밀한 Model 비교는 Advanced에서 다룰 수 있지만 기본 조건은 Foundation에 남긴다.

여기서 출사 반구 적분은 입력 방향을 고정하고 Surface가 여러 출사 방향으로 보내는 전체 반사 관계를 확인한다. 입력 방향을 모아 Lighting을 만드는 Rendering Equation의 용도와 구별해 읽는다.

**Multiple Scattering**은 작은 면들 사이에서 여러 번 반사되는 기여를 포함하는 관계다. 기본 Single-scattering Model과 구별하며, 정밀 보정의 비교는 Advanced의 범위로 남긴다. 기본 에너지 조건과 Model 합성의 범위는 Foundation에서도 유지한다.

</details>

---

### A Basic Validation

Formula가 의미하는 관계를 작은 변화로 확인할 수 있다. Material과 방향을 고정하고 입력만 바꾸면 어느 단계가 변하는지 구별하기 쉽다.

Light Intensity만 두 배로 바꾸면, 선형 연산과 같은 Visibility 조건에서 반사 Radiance는 두 배가 된다. BRDF 자체가 두 배가 되는 것은 아니다. 화면의 표시 RGB는 Exposure와 Tone Mapping을 거치므로 이 선형 관계를 그대로 보장하지 않는다. Chapter 06에서 그 차이를 연결한다.

검산에서는 5.14에서 구분한 계산 Radiance와 표시 결과의 차이를 유지한다. 화면의 밝기만 보고 Surface 응답이 바뀌었다고 판단하지 않는다.

---

### Key Takeaways

- fr은 작은 입사 Irradiance 기여가 특정 출사 Radiance에 만드는 응답을 정의한다.
- Li를 면적당 입사 기여로 바꿀 때 입사 Cosine과 방향 범위가 필요하다.
- Rendering Equation은 방향별 반사 기여를 모으고 Emission을 더한다.
- 입력 Li의 차폐 상태를 확인하여 Scene Visibility를 한 번 적용한다.
- 물리적 응답에는 비음수, 에너지 보존, 해당 Material의 상호성 조건이 필요하다.
- 계산 Radiance와 화면 표시 RGB는 다른 단계의 값이다.

이제 5.4의 Lambert를 같은 BRDF 정의로 다시 볼 수 있다. 마지막 절에서는 NdotL과 Material 응답 ρ/π가 왜 다른 역할인지 확인한다.

---

## 5.19 Lambertian BRDF

### Return to the First Diffuse Question

5.4에서는 종이나 벽처럼 관찰 방향을 바꾸어도 비슷하게 보이는 Diffuse를 살펴보았다. 같은 Surface가 같은 Irradiance를 받으면 Lambertian Outgoing Radiance는 관찰 방향에 무관하다고 가정했다.

또 입사각이 비스듬해지면 같은 빛이 더 넓은 면적에 퍼져 단위 면적당 기여가 작아진다는 것을 NdotL로 표현했다. 이제 이 방향 계수와 Surface가 반사하는 Material 응답을 분리해 볼 수 있다.

> **Surface가 받는 입사 빛이 같을 때, Lambertian Material은 그 빛을 어떻게 출사 방향에 배분하는가?**

이 질문이 Lambertian BRDF의 역할이다. NdotL은 입사 빛을 Surface 면적당 기여로 바꾸는 계수였고, BRDF는 그 기여에 대한 Material 응답이다.

---

### Diffuse Reflectance and the Need for Normalization

**Diffuse Reflectance ρ**는 입사한 Flux 중 Diffuse로 반사되는 비율이다. 물리적인 기본 Model에서는 각 Color 성분이 0–1 범위다. 반사 가능한 양을 정하는 것과 그 양이 출사 방향에 어떻게 분포하는지를 함께 맞춰야 한다.

Lambertian Lo는 관찰 방향에 무관하지만, 각 방향으로 나가는 Power를 모을 때는 Surface의 투영 면적 관계가 들어간다. 따라서 단순히 모든 방향에 ρ를 그대로 사용하면 전체 반사량의 정규화가 맞지 않을 수 있다.

출사 반구에서 Cosine을 가중하여 전체 방향 기여를 모으면 π라는 값이 나온다. ρ를 π로 나누면 전체 반사 Flux가 입사 Flux의 ρ배가 되도록 맞출 수 있다. **1/π는 원하는 화면 밝기로 조정하는 임의 상수가 아니라 전체 반사 관계를 맞추는 정규화**다.

---

### Lambertian BRDF and Diffuse Radiance

왜 ρ/π가 필요한지 이해했으므로 Formula를 확인한다. 5.4의 max(0,N·L)은 입사 방향의 Cosine Factor였고, Lambertian BRDF 자체는 다음과 같다.

```text
fr_diffuse = ρ / π
Lo_diffuse = (ρ / π) * Ei
```

첫 줄은 방향에 무관한 Material 응답 fr_diffuse다. 둘째 줄은 Surface가 받은 전체 Irradiance Ei를 사용해 Diffuse Outgoing Radiance를 계산한다. Ei가 어떤 상태의 값인지 알아야 중복 Cosine을 피할 수 있다.

ρ는 Diffuse Reflectance이며 각 Color 성분은 물리적인 기본 Model에서 0–1 범위이다. Ei는 이미 입사 Cosine을 포함해 Surface에 도달한 전체 Irradiance이다. 따라서 두 번째 식에 N·L을 다시 곱하지 않는다. 반대로 방향별 Incoming Radiance로부터 시작하면 5.18처럼 입사 Cosine과 방향 영역을 포함해 적분한다.

1/π는 단순한 밝기 조절 상수가 아니다. 출사 반구의 Cosine 적분이 π이므로, 이를 나눠 반사 Flux가 입사 Flux의 ρ배가 되도록 만든다. 고정된 Ei에서 Lo는 관찰 방향에 의존하지 않는다.

---

### A Numerical Check

Material의 Diffuse Reflectance와 입사 Irradiance를 고정하여 수치로 관계를 확인한다.

ρ=0.5, Ei=π W/m²이면 Lo=0.5 W/(m²·sr)이다. Ei를 두 배로 하면 Lo도 두 배가 되고, Camera 방향만 바꾸면 이상적인 Lambertian Lo는 유지된다. 이 검사는 Specular가 없는 동일 Surface 위치를 가정한다.

여기서 Camera 방향만 바꾸는 실험은 같은 Surface 지점, 같은 Ei, Specular가 없는 이상적 Lambertian 조건을 유지한다. Material이나 Light까지 동시에 바꾸고 관찰 방향의 효과라고 판단하지 않는다.

Ei를 두 배로 하면 BRDF가 두 배가 되는 것이 아니라 Surface에 들어오는 빛이 두 배가 되어 Lo가 두 배가 된다. 이 결과는 5.17의 Material response와 Light input 분리, 5.18의 선형 검산과 같은 관계다.

---

### Connecting Back to Educational Base Lighting

Chapter 08에서 Anime Shader의 Base Lighting을 만들 때는 제어 가능한 모양과 입력 흐름이 중요하다. 같은 NdotL을 사용하더라도 물리 단위와 정규화를 포함한 BRDF Lighting인지, 교육용 방향 응답인지 역할을 구별해야 한다.

Chapter 08.2의 BaseColor·max(0,N·L)은 제어 가능한 교육용 Base Lighting이다. 별도 광량 및 단위·정규화 없이 이를 완성된 PBR Lighting으로 취급하지 않는다.

이 구분은 교육용 계산이 쓸모없다는 뜻이 아니다. 원하는 표현을 만들기 위한 Model의 목적과, 물리적 Light quantity를 연결한 계산의 목적을 정확히 이해하는 것이다. 같은 방향 관계가 여러 구현에서 쓰이더라도 출력의 의미를 유지한다.

---

### Chapter Summary

처음에는 같은 Light 아래에서 거울, 종이, 금속이 왜 다르게 보이는지를 물었다. Surface Normal과 방향 규칙을 정하고, 거울 반사의 R을 계산한 뒤, Diffuse와 View-dependent Highlight를 비교했다. Microfacet 관점은 작은 반사 면의 분포·차폐·반사율을 나누어 설명했다.

마지막에는 빛의 물리량과 Surface response를 분리했다. 이 과정에서 NdotL, BRDF, Incoming Light, Outgoing Radiance, 화면의 표시 밝기가 서로 다른 역할이라는 것을 확인했다. Formula는 이 관계를 대신 설명하는 이름이 아니라 이미 이해한 관계의 최종 표현이다.

- N, L, V의 Space와 방향 규칙이 Reflection 계산의 출발점이다.
- Phong/Blinn-Phong은 방향 관계로 Highlight를 구성하는 방법을 보여준다.
- Microfacet Model은 Roughness와 D·G·F를 통해 Specular 분포와 차폐·반사율을 연결한다.
- BRDF와 Incoming Radiance를 결합해야 Lighting Result를 얻는다.
- BRDF 값, Diffuse Cosine Factor, 최종 표시 밝기는 서로 다른 값이다.

다음 [Chapter 06 — Modern Real-time Rendering](Chapter06_ModernRealtimeRendering.md)에서는 이 Surface Response에 Direct/Indirect Lighting과 Environment Reflection이 합쳐지는 과정, 그리고 HDR·Exposure·Tone Mapping·Color Output을 살펴본다. Chapter 04의 Material Property가 실제 Rendering 결과에 어떻게 연결되는지 이어서 확인한다.

