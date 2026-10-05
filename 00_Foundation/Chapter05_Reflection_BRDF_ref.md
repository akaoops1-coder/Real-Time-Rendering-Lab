## Reflection Chapter Status

---

# PART I

# Reflection Models

> Reflection을 설명하기 위해 제안된 대표적인 Reflection Model을 살펴본다.
> Reflection은 Lambert에서 시작하여 Blinn-Phong까지 점차 발전해 왔다.

---

# 5.1 Reflection

## 왜 Reflection을 배우는가?

우리는 매일 수많은 물체를 바라보며 살아간다.

거울은 주변 환경을 선명하게 비추고,
종이는 어느 방향에서 보아도 비슷한 밝기를 유지하며,
금속은 강한 하이라이트를 만들고,
플라스틱은 은은한 광택을 가진다.

이처럼 같은 빛을 받아도 물체마다 서로 다른 모습으로 보이는 이유는 **빛을 반사(Reflection)하는 방식이 서로 다르기 때문**이다.

컴퓨터 그래픽스(Rendering)의 중요한 목표 중 하나는 이러한 Reflection을 최대한 현실과 가깝게 재현하는 것이다.

---

<p align="center">
    <img src="Figures/Chapter05/Fig5_01.png" width="80%">
</p>

---

## Reflection이란?

빛(Light)이 물체 표면(Surface)에 도달하면 여러 가지 현상이 동시에 발생한다.

일부는 물체 내부로 흡수(Absorption)되고,
일부는 내부를 통과(Transmission)하며,
일부는 다시 외부로 되돌아간다.

이때 표면에서 다시 외부로 방출되는 빛을 **Reflection(반사)** 이라고 한다.

Reflection은 우리가 물체를 인식하는 데 가장 중요한 광학 현상 중 하나이며, 재질(Material)의 특성을 결정하는 핵심 요소이기도 하다.

---

## Reflection은 재질의 특징을 만든다.

같은 조명 아래에서도 재질마다 전혀 다른 모습을 보이는 이유는 Reflection 방식이 서로 다르기 때문이다.

예를 들어,

- 거울은 대부분의 빛을 일정한 방향으로 반사한다.
- 종이는 빛을 여러 방향으로 고르게 퍼뜨린다.
- 금속은 강한 하이라이트를 만든다.
- 거친 표면은 반사가 넓게 퍼지고 부드러운 표면은 반사가 집중된다.

즉,

> **재질(Material)의 차이는 Reflection 방식의 차이에서 비롯된다.**

Rendering은 바로 이러한 차이를 수학적으로 표현하는 과정이라고 볼 수 있다.

---

## 현실의 Reflection을 그대로 계산할 수 있을까?

현실에서는 수많은 광자가 표면과 상호작용하며 매우 복잡한 반사 현상을 만들어 낸다.

하지만 이러한 현상을 모두 계산하는 것은 현재의 컴퓨터에서도 매우 큰 비용이 필요하다.

따라서 컴퓨터 그래픽스에서는 현실을 그대로 계산하는 대신,

**Reflection의 중요한 특징만 추출하여 단순화된 모델(Model)** 을 만든다.

이러한 모델을 사용하면 현실과 비슷한 결과를 훨씬 적은 계산량으로 표현할 수 있다.

---

## Reflection Model의 발전

Reflection을 표현하는 방법은 오랜 시간 동안 계속 발전해 왔다.

초기의 모델은 단순하고 계산이 빨랐지만 현실과 차이가 컸다.

이후 더 현실적인 결과를 얻기 위해 다양한 Reflection Model이 등장했고,

오늘날 대부분의 Rendering Engine은 물리 기반(Physically Based Rendering, PBR)의 Reflection Model을 사용한다.

이번 Chapter에서는 이러한 발전 과정을 순서대로 살펴본다.

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
Cook-Torrance
    ↓
Microfacet
    ↓
Radiometry
    ↓
BRDF
```

각 모델은 이전 모델의 한계를 해결하기 위해 등장했으며,

결국 하나의 질문을 해결하기 위한 과정이다.

> **Surface는 빛을 어떻게 반사하는가?**

이 질문에 대한 답을 찾는 것이 이번 Chapter의 목표이다.

---

## 핵심 요약

- Reflection은 표면에서 다시 외부로 나오는 빛이다.
- 재질의 차이는 Reflection 방식의 차이에서 비롯된다.
- 현실의 Reflection은 매우 복잡하기 때문에 단순화된 Reflection Model을 사용한다.
- 이번 Chapter에서는 Reflection Model이 BRDF까지 발전하는 과정을 학습한다.

---

# 5.2 Surface Normal

## 왜 Surface Normal이 필요할까?

우리는 물체의 표면을 바라볼 때 흔히 "어느 방향을 향하고 있는가?"라는 표현을 사용한다.

예를 들어,

- 바닥은 위를 향하고 있고,
- 벽은 옆을 향하며,
- 천장은 아래를 향한다.

사람은 이러한 방향을 직관적으로 이해할 수 있지만,

컴퓨터는 "표면이 어느 방향을 향하고 있는지"를 알 수 없다.

따라서 Rendering에서는 표면의 방향을 수학적으로 표현할 방법이 필요하다.

이때 사용하는 벡터가 **Surface Normal**이다.

---

## Surface Normal이란?

Surface Normal은

> **표면에 수직(Perpendicular)인 방향을 나타내는 벡터(Vector)** 이다.

보통 **N**으로 표기하며,

Rendering에서는 가장 기본이 되는 방향 벡터이다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_02.png" width="80%">
</p>



Surface Normal은

표면이 어느 방향을 향하고 있는지를 정의하는 기준축(Reference Direction) 역할을 한다.

---

## 왜 '수직' 방향일까?

표면에는 무한히 많은 방향이 존재한다.

예를 들어 평평한 바닥 위에서는

앞뒤,
좌우,
대각선 등

수많은 방향을 정의할 수 있다.

하지만 이러한 방향들은 모두 표면 위에 존재하는 방향일 뿐,

표면 자체가 어느 방향을 향하고 있는지는 알려주지 않는다.

반면,

표면에 수직인 방향은 하나만 존재한다.

따라서 컴퓨터 그래픽스에서는

표면의 방향을 표현하는 기준으로

Surface Normal을 사용한다.

---

## Surface Normal은 Rendering의 기준이 된다.

Rendering에서 계산하는 대부분의 값은

Surface Normal을 기준으로 이루어진다.

예를 들어,

- 빛이 어느 각도로 들어오는가?
- Reflection은 어느 방향으로 발생하는가?
- Surface는 얼마나 밝게 보이는가?
- Specular Highlight는 어디에 생기는가?

이 모든 계산은

Surface Normal을 기준으로 수행된다.

즉,

> **Surface Normal은 Rendering에서 모든 방향 계산의 기준축이다.**

---

## Callback

Chapter의 처음에서 우리는

> **왜 같은 빛을 받아도 물체마다 다르게 보일까?**

라는 질문을 던졌다.

이 질문에 답하기 위해서는

먼저 표면의 방향을 정의해야 한다.

왜냐하면

빛이 어느 방향으로 들어오고,

어느 방향으로 반사되는지는

모두 Surface Normal을 기준으로 결정되기 때문이다.

다음 장에서는

Surface Normal을 이용하여

빛이 어떤 방향으로 반사되는지 나타내는

**Reflection Vector**를 살펴본다.

---

## 핵심 요약

- Surface Normal은 표면에 수직인 방향을 나타내는 벡터이다.
- 보통 **N**으로 표기한다.
- Surface Normal은 표면의 방향을 정의하는 기준축이다.
- Rendering의 대부분의 방향 계산은 Surface Normal을 기준으로 이루어진다.

---

# 5.3 Reflection Vector

## Reflection은 어떤 방향으로 진행될까?

Surface Normal을 이용하면 이제 빛이 표면과 어떤 관계를 가지는지 설명할 수 있다.

그렇다면 새로운 질문이 생긴다.

> **빛은 표면에 닿은 뒤 어떤 방향으로 반사될까?**

빛은 임의의 방향으로 반사되지 않는다.

Reflection에는 항상 일정한 규칙이 존재한다.

---

## Reflection Law

Reflection은 **Reflection Law(반사의 법칙)** 를 따른다.

이 법칙은 매우 단순하다.

> **입사각(Angle of Incidence)과 반사각(Angle of Reflection)은 항상 같다.**

여기서 중요한 점은

각도를 **Surface 자체가 아니라 Surface Normal을 기준으로 측정한다**는 것이다.

```
           Reflection
                ↑
              θr│
                │
                │ N
───────────────●────────────── Surface
                │
              θi│
                ↓
            Incoming Light
```

즉,

```
θi = θr
```

이 항상 성립한다.

이 규칙은 거울과 같은 완전히 매끄러운 표면(Specular Surface)에서 정확하게 성립하며,

이후 등장하는 Reflection Model의 출발점이 된다.

---

## Reflection Direction을 벡터로 표현하기

Reflection Law는 반사의 방향을 설명하지만,

컴퓨터는 "각도"보다 "벡터"를 이용하여 계산하는 것이 훨씬 편하다.

따라서 Rendering에서는

반사 방향을 하나의 벡터로 표현한다.

이 벡터를

**Reflection Vector**라고 한다.

보통 다음과 같이 표기한다.

- **L** : Incoming Light Direction
- **N** : Surface Normal
- **R** : Reflection Vector

<p align="center">
    <img src="Figures/Chapter05/Fig5_03.png" width="80%">
</p>


Reflection Vector는

입사한 빛과 Surface Normal이 주어졌을 때

유일하게 결정되는 반사 방향이다.

---

## Reflection Vector는 어떻게 계산할까?

Reflection Vector는

입사 벡터를 Surface Normal을 기준으로 대칭시킨 결과이다.

수학적으로는 다음과 같이 계산한다.

```text
R = 2(N · L)N - L
```

여기서

- **N · L**은 Light Direction과 Surface Normal 사이의 내적(Dot Product)이다.
- 이 값을 이용하여 입사 벡터를 Normal 기준으로 반사시킨다.

이 공식 자체를 외우는 것이 중요한 것은 아니다.

중요한 것은

> **Reflection Vector는 Reflection Law를 수학적으로 표현한 결과**라는 점이다.

---

## Reflection Vector는 왜 중요할까?

Reflection Vector는

단순히 반사 방향 하나를 구하기 위한 벡터가 아니다.

초기의 Reflection Model 대부분은

Reflection Vector를 중심으로 만들어졌다.

예를 들어

- Phong Reflection은 Reflection Vector와 View Direction의 관계를 이용하여 Specular Reflection을 계산한다.
- Blinn-Phong은 Reflection Vector 계산을 단순화하기 위해 Half Vector를 도입한다.
- Cook-Torrance 역시 Reflection 방향을 기반으로 더욱 현실적인 Reflection을 모델링한다.

즉,

Reflection Vector는

Reflection Model 발전의 출발점이라고 할 수 있다.

---

## Callback

앞에서 우리는

Surface Normal이

Rendering의 기준 방향이라는 사실을 배웠다.

Reflection Vector는

그 기준 방향을 이용하여

빛이 어디로 반사되는지를 계산한다.

하지만 현실의 대부분의 Surface는

거울처럼 완벽하게 매끄럽지 않다.

그렇다면

거친 종이나 벽처럼

빛이 여러 방향으로 퍼지는 Surface는 어떻게 표현할 수 있을까?

다음 장에서는

가장 단순한 Reflection Model인

**Lambert Reflection**을 살펴본다.

---

## 핵심 요약

- Reflection은 Reflection Law를 따른다.
- 입사각과 반사각은 항상 같다.
- Reflection Vector는 반사 방향을 나타내는 벡터이다.
- Reflection Vector는 Reflection Law를 벡터로 표현한 결과이다.
- 이후의 Reflection Model은 Reflection Vector를 기반으로 발전하였다.

---

# 5.4 Lambert Reflection

## Reflection Vector만으로는 현실을 설명할 수 있을까?

Reflection Vector는 거울과 같이 매우 매끄러운 표면에서 빛이 어떻게 반사되는지를 설명한다.

하지만 주변을 둘러보면 대부분의 물체는 거울처럼 보이지 않는다.

종이,
나무,
콘크리트,
벽,
천과 같은 재질은 어느 방향에서 바라보아도 비슷한 밝기를 유지한다.

왜 이런 차이가 생기는 것일까?

Reflection Vector만으로는 이러한 현상을 설명할 수 없다.

---

## Diffuse Reflection

현실의 대부분의 표면은 완벽하게 매끄럽지 않다.

빛은 표면에 도달한 후 미세한 구조(Micro Structure)에 의해 여러 방향으로 퍼져 나간다.

이처럼 빛이 특정 방향으로 집중되지 않고 다양한 방향으로 퍼지는 반사를

**Diffuse Reflection(난반사)** 이라고 한다.

Diffuse Reflection은 우리가 일상에서 가장 많이 보는 Reflection 형태이다.

---

## Lambert의 아이디어

1760년대, Johann Heinrich Lambert는 매우 단순한 가정을 제안했다.

> **Diffuse Reflection은 모든 방향으로 동일하게 퍼진다.**

즉,

관찰자가 어느 방향에서 Surface를 바라보더라도

Diffuse Reflection 자체는 동일하게 방출된다고 가정한 것이다.

이 가정 덕분에 Reflection을 매우 간단한 수학으로 표현할 수 있게 되었다.

---

## Surface가 밝아지는 이유

그렇다면 Surface의 밝기는 무엇으로 결정될까?

Lambert는

빛이 Surface에 얼마나 정면으로 도달하는가가

받는 에너지를 결정한다고 생각했다.

빛이 Surface를 정면으로 비출수록

더 많은 빛이 도달하고,

비스듬히 들어올수록

같은 양의 빛도 더 넓은 면적으로 퍼지게 된다.

따라서 Surface는 더 어둡게 보인다.

즉,

> **Surface의 밝기는 입사각에 따라 달라진다.**

---

## Lambert's Cosine Law

Lambert는 이러한 관계를 다음과 같이 표현하였다.

```text
Diffuse = max(0, N · L)
```

여기서

- **N** : Surface Normal
- **L** : Light Direction
- **N · L** : 두 벡터 사이의 각도의 Cosine 값

입사각이 0°라면

빛은 Surface를 가장 정면으로 비추며

가장 밝게 보인다.

입사각이 커질수록

Cosine 값이 감소하여

Surface도 점차 어두워진다.

빛이 Surface 뒤쪽에서 들어오는 경우에는

Diffuse Reflection이 발생하지 않으므로

음수는 0으로 처리한다.

---

<p align="center">
    <img src="Figures/Chapter05/Fig5_04.png" width="80%">
</p>

---

## Lambert Reflection의 의미

Lambert Reflection은

오늘날 기준으로는 매우 단순한 Reflection Model이다.

Specular Reflection도 없고,

재질에 따른 다양한 특성도 표현하지 못한다.

그럼에도 불구하고

Lambert는 Rendering 역사에서 매우 중요한 의미를 가진다.

왜냐하면

처음으로 Reflection을

수학적인 모델로 표현한 대표적인 Diffuse Reflection Model이기 때문이다.

오늘날의 PBR에서도

Diffuse Lighting의 기본 개념은 Lambert Reflection에서 시작된다.

---

## Callback

Reflection Vector는

거울처럼 빛이 한 방향으로 반사되는 현상을 설명했다.

Lambert는

현실에서 훨씬 흔한

Diffuse Reflection을 설명하기 위해 등장하였다.

하지만 Lambert에는 또 하나의 한계가 있다.

금속이나 플라스틱처럼 반짝이는 Surface를 전혀 표현할 수 없다.

다음 장에서는

이 문제를 해결하기 위해 등장한

**Phong Reflection**을 살펴본다.

---

## 핵심 요약

- Reflection Vector는 Specular Reflection을 설명한다.
- 현실의 대부분의 Surface는 Diffuse Reflection이 지배적이다.
- Lambert는 Diffuse Reflection을 설명하는 가장 대표적인 Reflection Model이다.
- Surface의 밝기는 **N · L**에 의해 결정된다.
- Lambert는 이후 모든 Reflection Model의 출발점이 되었다.

---

# 5.5 Phong Reflection

## Lambert Reflection만으로 충분할까?

Lambert Reflection은 현실에서 가장 흔한 Diffuse Reflection을 매우 간단하게 표현할 수 있는 모델이다.

하지만 Lambert만으로는 설명할 수 없는 Surface가 존재한다.

예를 들어,

- 금속은 밝은 하이라이트(Highlight)가 나타난다.
- 플라스틱은 은은한 광택이 보인다.
- 자동차 도장은 빛을 받으면 반짝인다.
- 물 표면은 시점에 따라 강한 빛을 반사한다.

이러한 현상은 Lambert Reflection만으로는 표현할 수 없다.

---

## Reflection의 두 가지 형태

지금까지 우리는 Reflection이라는 하나의 현상을 설명해 왔다.

하지만 실제 Reflection은 크게 두 가지 성분으로 나눌 수 있다.

### Diffuse Reflection

빛이 Surface에서 여러 방향으로 퍼지는 반사이다.

관찰자의 위치가 달라져도 밝기가 크게 변하지 않는다.

대표적인 예는

- 종이
- 콘크리트
- 벽
- 나무

등이다.

Lambert Reflection은 이러한 Diffuse Reflection을 표현한다.

---

### Specular Reflection

빛이 특정 방향으로 집중되어 반사되는 현상이다.

관찰자의 위치에 따라 밝기가 크게 달라진다.

대표적인 예는

- 금속
- 유리
- 플라스틱
- 물
- 자동차 도장

등이다.

우리가 흔히 말하는 **광택(Gloss)** 또는 **하이라이트(Highlight)** 가 바로 Specular Reflection이다.

---

## 왜 Highlight가 생길까?

Highlight는 Surface 자체가 빛을 내는 것이 아니다.

빛이 특정 방향으로 강하게 반사되기 때문에

관찰자가 그 방향에 위치할 때 밝게 보이는 것이다.

즉,

Highlight는

- Light Direction
- Surface Normal
- View Direction

이 세 방향의 관계에 의해 결정된다.

여기서 처음으로

**View Direction**이라는 새로운 요소가 등장한다.

Lambert Reflection에서는 관찰자의 위치와 관계없이 밝기가 동일했지만,

Specular Reflection은 관찰자의 위치에 따라 계속 변한다.

---

## Phong Reflection

1975년, Bui Tuong Phong은

Specular Reflection을 매우 간단한 수학으로 표현하는 모델을 제안하였다.

Phong Reflection은

Reflection Vector와 View Direction이 얼마나 일치하는지를 이용하여

Highlight의 세기를 계산한다.

즉,

관찰자의 시선이 Reflection Vector와 가까울수록

Highlight는 더욱 강하게 나타난다.

반대로,

Reflection Vector에서 멀어질수록

Highlight는 빠르게 약해진다.

---

<p align="center">
    <img src="Figures/Chapter05/Fig5_05.png" width="80%">
</p>

---

## Phong Reflection의 특징

Phong Reflection은

Lambert가 표현하지 못했던

광택과 Highlight를 표현할 수 있게 만들었다.

덕분에 Surface는 훨씬 현실적으로 보이게 되었다.

하지만 여전히 한계도 존재한다.

Reflection Vector를 먼저 계산해야 하므로 계산량이 비교적 많으며,

Highlight의 모양 역시 현실과는 차이가 있다.

이러한 문제를 해결하기 위해

다음 장에서는

Reflection Vector 대신 **Half Vector**를 사용하는

Blinn의 아이디어를 살펴본다.

---

## Callback

Lambert Reflection은

빛이 Surface에 얼마나 정면으로 들어오는지를 설명하였다.

Phong Reflection은

여기에 관찰자의 위치(View Direction)를 추가하여

Highlight를 표현하였다.

이제 Reflection은

단순히 빛이 들어오는 것만이 아니라

**빛과 시선이 함께 만드는 현상**으로 확장되기 시작한다.

---

## 핵심 요약

- Reflection은 Diffuse Reflection과 Specular Reflection으로 나눌 수 있다.
- Lambert Reflection은 Diffuse Reflection을 표현한다.
- Phong Reflection은 Specular Reflection을 표현한다.
- Phong은 Reflection Vector와 View Direction의 관계를 이용하여 Highlight를 계산한다.
- Specular Reflection은 관찰자의 위치에 따라 달라진다.

---

# 5.6 Half Vector

## Reflection Vector의 한계

Phong Reflection은 Reflection Vector를 이용하여 Highlight를 계산하였다.

Reflection Vector는 Reflection Law를 기반으로 계산되기 때문에

물리적으로도 직관적인 방법이었다.

하지만 한 가지 문제가 있었다.

Highlight를 계산하려면

먼저 Reflection Vector를 계산한 후,

다시 View Direction과 비교해야 한다.

즉,

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

Reflection Model이 복잡해질수록

Reflection Vector를 반복적으로 계산하는 비용은 점점 부담이 되었다.

더 간단한 방법이 필요했다.

---

## Blinn의 아이디어

James F. Blinn은

Reflection Vector를 직접 계산하지 않아도

Highlight를 표현할 수 있는 방법을 제안하였다.

그는 이렇게 생각했다.

> **Reflection Vector를 구하지 말고, Light와 View의 중간 방향을 사용하면 어떨까?**

이것이 Half Vector의 시작이다.

---

## Half Vector란?

Half Vector는

Light Direction과 View Direction의 정확한 중간 방향을 나타내는 벡터이다.

보통 **H**로 표기한다.

즉,

Light와 View가 이루는 각도를 정확히 절반으로 나누는 방향이다.

그래서 Half Vector(Halfway Vector)라는 이름이 붙었다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_06.png" width="80%">
</p>

---

## 왜 Half Vector를 사용할까?

거울처럼 완벽하게 매끄러운 Surface에서는

Highlight가 가장 강하게 나타나는 순간이 있다.

바로

Reflection Vector와 View Direction이 완전히 일치할 때이다.

Blinn은 이 조건을 다른 방식으로 바라보았다.

Reflection Vector를 계산하지 않아도

Surface Normal이 Half Vector와 일치하면

거의 같은 결과를 얻을 수 있다는 사실을 발견한 것이다.

즉,

Phong은

```text
Reflection Vector ≈ View Direction
```

을 비교했다면,

Blinn은

```text
Surface Normal ≈ Half Vector
```

를 비교하였다.

같은 Highlight를

더 간단하게 계산할 수 있게 된 것이다.

---

## Half Vector의 장점

Half Vector는

Reflection Vector를 직접 계산하지 않아도 되므로

계산이 더 단순하다.

또한 Highlight의 모양도

Phong보다 더 자연스럽게 나타나는 경우가 많다.

이러한 이유로

Blinn-Phong Reflection은 오랫동안

실시간 Rendering의 대표적인 Specular Reflection Model로 사용되었다.

하지만 Half Vector의 진정한 가치는

단순히 계산량을 줄인 것이 아니다.

이후 등장하는 Microfacet Theory에서는

각 Microfacet의 Normal이

바로 Half Vector와 같은 방향을 향한다고 가정한다.

즉,

Half Vector는

Cook-Torrance와 PBR을 이해하기 위한 가장 중요한 연결고리가 된다.

---

## Callback

Phong Reflection은

Reflection Vector를 이용하여 Highlight를 계산하였다.

Blinn은

Reflection Vector 대신 Half Vector를 사용하여

같은 현상을 더욱 효율적으로 표현하였다.

그리고 이 Half Vector는

다음 장에서 배우게 될 **Blinn-Phong Reflection**의 핵심 요소가 된다.

더 나아가

Cook-Torrance와 Microfacet Theory에서도

가장 중요한 벡터 중 하나로 사용된다.

---

## 핵심 요약

- Half Vector는 Light Direction과 View Direction의 중간 방향이다.
- Blinn은 Reflection Vector 대신 Half Vector를 사용하였다.
- Half Vector는 계산이 단순하고 Highlight를 효율적으로 표현할 수 있다.
- Half Vector는 이후 Blinn-Phong과 Cook-Torrance의 핵심 개념이 된다.

---

# 5.7 Blinn-Phong Reflection

## Half Vector는 실제로 어떻게 사용할까?

앞 장에서 Half Vector는

Light Direction과 View Direction의 중간 방향을 나타내는 벡터라는 것을 배웠다.

하지만 Half Vector 자체는 단지 하나의 벡터일 뿐이다.

실제로 Rendering에서는

이 벡터를 이용하여 Highlight의 세기를 계산해야 한다.

이를 위해 James F. Blinn은

Phong Reflection을 개선한 새로운 Reflection Model을 제안하였다.

이를 **Blinn-Phong Reflection**이라고 한다.

---

## Phong과 무엇이 다를까?

Phong Reflection은

Reflection Vector와 View Direction이 얼마나 일치하는지를 비교하였다.

즉,

```text
Reflection Vector ≈ View Direction
```

일수록 Highlight가 강해진다.

반면 Blinn-Phong은

Reflection Vector를 계산하지 않는다.

대신

Surface Normal과 Half Vector를 비교한다.

```text
Surface Normal ≈ Half Vector
```

Surface Normal이 Half Vector와 가까울수록

Surface는 더 강한 Highlight를 가진다.

즉,

비교 대상 자체가 달라진 것이다.

---

## 왜 같은 결과가 나올까?

Half Vector는

Light Direction과 View Direction의 정확한 중간 방향이다.

거울과 같은 이상적인 Surface에서는

가장 강한 Reflection이 발생하는 순간

Surface Normal 역시 Half Vector와 거의 같은 방향을 향하게 된다.

따라서

Reflection Vector를 직접 계산하지 않아도

비슷한 Highlight를 얻을 수 있다.

이것이 Blinn-Phong Reflection의 핵심 아이디어이다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_07.png" width="80%">
</p>

---

## Blinn-Phong의 장점

Blinn-Phong Reflection은

Phong Reflection보다 계산이 단순하다.

또한 Highlight의 모양도

보다 자연스럽게 표현되는 경우가 많다.

이러한 이유로

Blinn-Phong은 오랫동안

실시간 Rendering에서 가장 널리 사용된 Specular Reflection Model이었다.

특히 게임 엔진에서는

PBR이 보편화되기 전까지

사실상의 표준 Reflection Model로 사용되었다.

---

## 하지만 여전히 한계가 있다.

Blinn-Phong은

Phong보다 개선된 Reflection Model이지만,

여전히 경험적인(Empirical) 모델이다.

즉,

실제 빛의 물리적인 특성을 기반으로 만들어진 것이 아니라,

현실과 비슷하게 보이도록 설계된 모델이다.

따라서 다음과 같은 문제들이 남아 있었다.

- Material마다 다른 Reflection 특성을 정확하게 표현하기 어렵다.
- Energy Conservation을 만족하지 않는다.
- Surface의 미세한 구조(Micro Geometry)를 고려하지 않는다.
- Fresnel Effect를 표현하지 못한다.

이러한 한계를 해결하기 위해

Rendering은 점점 물리 기반(Physically Based) 모델로 발전하게 된다.

---

## Callback

Reflection의 역사를 살펴보면

Reflection Model은

조금씩 현실에 가까워지는 방향으로 발전해 왔다.

Reflection Vector에서 시작하여

Phong,

Blinn-Phong까지 발전했지만,

여전히 Surface를 하나의 매끄러운 평면으로 가정하고 있다.

하지만 현실의 Surface는

현미경으로 보면 전혀 그렇지 않다.

다음 장에서는

이러한 관점에서 등장한

**Microfacet Theory**를 살펴본다.

Microfacet Theory는

오늘날 PBR의 출발점이 되는 가장 중요한 아이디어이다.

---

## 핵심 요약

- Blinn-Phong은 Half Vector를 이용하여 Highlight를 계산한다.
- Phong은 Reflection Vector와 View Direction을 비교한다.
- Blinn-Phong은 Surface Normal과 Half Vector를 비교한다.
- Blinn-Phong은 계산이 단순하고 실시간 Rendering에 적합하다.
- 하지만 여전히 경험적인 Reflection Model이며 물리적인 정확성에는 한계가 있다.

---

# PART II

# Physically Based Rendering

> 기존 Reflection Model의 한계를 극복하기 위해 등장한
> 현대 Rendering의 핵심 개념을 살펴본다.

---

# 5.8 Reflection Model의 한계

## 지금까지의 Reflection Model

지금까지 우리는

Reflection을 설명하기 위해 다양한 Reflection Model을 살펴보았다.

- Lambert Reflection
- Phong Reflection
- Blinn-Phong Reflection

각 모델은

이전 모델보다 현실에 가까운 Reflection을 표현할 수 있도록 발전해 왔다.

Lambert는 Diffuse Reflection을 설명하였고,

Phong은 Highlight를 표현하였으며,

Blinn-Phong은 이를 더욱 효율적으로 계산하였다.

하지만 이러한 발전에도 불구하고

여전히 해결되지 않은 문제가 남아 있었다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_08.png" width="80%">
</p>

---

## Surface를 너무 단순하게 가정한다.

기존 Reflection Model들은

Surface를 하나의 매끄러운 평면으로 가정한다.

즉,

Surface 전체가 하나의 Normal을 가진다고 생각한다.

하지만 현실의 Material은

현미경으로 확대하면

수많은 미세한 요철로 이루어져 있다.

Surface는 하나의 평면이 아니라,

매우 복잡한 구조를 가진다.

이러한 차이 때문에

기존 Reflection Model은

현실의 Reflection을 완전히 표현할 수 없다.

---

## Material의 특성을 충분히 표현하지 못한다.

현실에는

금속,

플라스틱,

세라믹,

나무,

천,

피부처럼

매우 다양한 Material이 존재한다.

각 Material은

빛을 서로 다른 방식으로 반사한다.

하지만 기존 Reflection Model은

Material의 고유한 Reflection 특성을

충분히 표현하지 못한다.

결국

Highlight의 크기나 밝기를 조절하는 정도에 머무르게 된다.

---

## 빛의 물리적인 특성을 고려하지 않는다.

빛은

입사각에 따라

반사되는 양이 달라진다.

또한

Surface 내부에서 흡수되거나,

다른 Microfacet에 의해 가려질 수도 있다.

하지만 기존 Reflection Model은

이러한 물리적인 현상을 대부분 고려하지 않는다.

즉,

결과는 비슷하게 보일 수 있지만,

빛이 실제로 어떻게 반사되는지는 설명하지 못한다.

---

## 현실적인 Rendering을 위해

Rendering 기술이 발전하면서

단순히 보기 좋은 Reflection보다

실제 빛의 거동을 기반으로 한 Reflection이 필요해졌다.

이를 위해서는

Surface의 미세한 구조,

빛의 진행,

Material의 물리적인 특성을

함께 고려해야 한다.

이러한 요구에서 등장한 것이

**Microfacet Theory**이다.

---

## Callback

Lambert,

Phong,

Blinn-Phong은

각 시대를 대표하는 훌륭한 Reflection Model이었다.

하지만

현실의 Surface와 빛을

보다 정확하게 표현하기에는 한계가 있었다.

다음 장에서는

Surface를 하나의 평면이 아니라

수많은 작은 거울들의 집합으로 바라보는

**Microfacet Theory**를 살펴본다.

이 아이디어는

오늘날 PBR의 가장 중요한 기반이 된다.

---

## 핵심 요약

- 기존 Reflection Model은 Surface를 하나의 평면으로 가정한다.
- Material의 다양한 Reflection 특성을 충분히 표현하지 못한다.
- 빛의 물리적인 거동을 완전히 반영하지 못한다.
- 이러한 한계를 해결하기 위해 Microfacet Theory가 등장하였다.

---

# 5.9 Microfacet Theory

## 매끄러운 Surface는 실제로 존재할까?

지금까지 살펴본 Reflection Model들은

Surface를 하나의 매끄러운 평면이라고 가정하였다.

Lambert도,

Phong도,

Blinn-Phong도 모두 같은 가정을 사용한다.

하지만 현실의 Surface는 정말 완벽하게 매끄러울까?

현미경으로 확대해 보면

대부분의 Material은 수많은 미세한 요철을 가지고 있다.

우리가 눈으로는 매끄럽게 보이는 금속이나 플라스틱도

매우 작은 규모에서는 거친 구조를 가진다.

즉,

Rendering에서 사용하는 이상적인 Surface는

현실을 단순화한 모델일 뿐이다.

---

## Surface는 작은 거울들의 집합이다.

Microfacet Theory는

Surface를 하나의 평면으로 보지 않는다.

대신,

수많은 아주 작은 Surface들의 집합으로 생각한다.

이 작은 Surface 하나를

Microfacet이라고 한다.

각 Microfacet은

작은 거울처럼 빛을 반사한다.

즉,

Surface 전체가 빛을 반사하는 것이 아니라,

수많은 작은 거울들이 각각 빛을 반사한 결과가

우리가 보는 Reflection이 된다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_09.png" width="80%">
</p>

---

## 왜 Reflection이 퍼져 보일까?

모든 Microfacet이

같은 방향을 바라본다면

Reflection은 거울처럼 선명하게 나타난다.

하지만 현실에서는

각 Microfacet이

조금씩 다른 방향을 향하고 있다.

그 결과,

반사광도 여러 방향으로 퍼지게 된다.

이것이

Material마다 Highlight의 크기와 모양이 다른 이유이다.

매끄러운 금속은

Microfacet들의 방향이 거의 일정하므로

Highlight가 작고 선명하다.

거친 Surface는

Microfacet들의 방향이 다양하기 때문에

Highlight가 넓고 흐리게 퍼진다.

---

## Half Vector와의 관계

앞 장에서

Half Vector는

Light Direction과 View Direction의 중간 방향이라고 설명하였다.

Microfacet Theory에서는

이 Half Vector가 새로운 의미를 갖는다.

빛이 눈으로 반사되기 위해서는

Microfacet의 방향이

Half Vector와 거의 일치해야 한다.

즉,

Highlight를 만드는 것은

Surface 전체가 아니라,

Half Vector 방향을 향하고 있는 Microfacet들이다.

이 아이디어는

이후 Cook-Torrance Reflection의 핵심이 된다.

---

## Reflection을 확률로 생각하다

현실의 Surface에는

수많은 Microfacet이 존재한다.

그렇다면

Half Vector를 향하는 Microfacet은

전체 중 얼마나 될까?

Cook-Torrance Reflection은

이 질문을 수학적으로 해결한다.

즉,

Reflection을 하나의 방향으로 계산하는 것이 아니라,

특정 방향을 가진 Microfacet이

얼마나 존재하는지를 확률적으로 계산한다.

이것이

현대 PBR의 출발점이다.

---

## Callback

Lambert,

Phong,

Blinn-Phong은

Surface를 하나의 평면으로 생각하였다.

Microfacet Theory는

Surface를

수많은 작은 거울들의 집합으로 바라본다.

이 관점의 변화는

Reflection을 훨씬 현실적으로 표현할 수 있게 만들었다.

다음 장에서는

이 아이디어를 실제 Reflection Model로 구현한

**Cook-Torrance Reflection**을 살펴본다.

---

## 핵심 요약

- 현실의 Surface는 완벽하게 매끄럽지 않다.
- Surface는 수많은 Microfacet으로 이루어져 있다고 가정한다.
- 각 Microfacet은 작은 거울처럼 빛을 반사한다.
- Highlight는 Half Vector 방향을 향한 Microfacet들이 만든다.
- Microfacet Theory는 Cook-Torrance Reflection의 기반이 된다.

---

# 5.10 Cook-Torrance Reflection

## Reflection을 물리적으로 설명하다

Microfacet Theory는

Surface가 수많은 작은 거울(Microfacet)로 이루어져 있다고 설명하였다.

하지만 이것만으로는 Reflection을 계산할 수 없다.

실제로 Rendering에서는

빛이 얼마나 반사되는지를 수학적으로 계산해야 한다.

Cook-Torrance Reflection은

Microfacet Theory를 기반으로

Reflection을 물리적으로 계산하기 위해 만들어진 Reflection Model이다.

오늘날 대부분의 PBR(Rendering)은

Cook-Torrance BRDF를 기반으로 동작한다.

---

## 무엇을 계산해야 할까?

빛이 눈으로 반사되려면

단순히 Microfacet이 존재하는 것만으로는 충분하지 않다.

다음과 같은 조건들이 모두 만족되어야 한다.

- 적절한 방향을 가진 Microfacet이 존재해야 한다.
- 빛이 다른 Microfacet에 가려지지 않아야 한다.
- Material은 입사각에 따라 서로 다른 양의 빛을 반사한다.

Cook-Torrance는

이 세 가지 요소를 각각 계산하여

최종 Reflection을 구한다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_10.png" width="80%">
</p>

---

## 세 가지 구성 요소

Cook-Torrance Reflection은

세 개의 핵심 요소로 이루어진다.

### D (Normal Distribution Function)

Surface에는

어떤 방향을 가진 Microfacet이

얼마나 많이 존재하는가?

즉,

Microfacet의 방향 분포를 계산한다.

---

### G (Geometry Function)

빛이

Microfacet 사이에서

가려지거나 차단되지 않는가?

즉,

Self Shadowing과 Masking 효과를 계산한다.

---

### F (Fresnel)

Material은

입사각에 따라

반사되는 빛의 양이 달라진다.

이를 Fresnel Effect라고 하며,

Cook-Torrance는 이를 Reflection 계산에 포함한다.

---

## 하나라도 빠지면 현실과 달라진다.

세 요소는

각각 서로 다른 역할을 담당한다.

D가 없다면

Surface의 거칠기를 표현할 수 없다.

G가 없다면

Microfacet 사이의 차폐 효과를 표현할 수 없다.

F가 없다면

현실에서 나타나는 각도에 따른 Reflection 변화를 표현할 수 없다.

즉,

세 요소는 모두 필요하다.


---

## Cook-Torrance의 의미

Cook-Torrance Reflection은

기존 Reflection Model처럼

Highlight를 단순히 그리는 것이 아니다.

대신,

빛이 실제 Surface에서 어떻게 반사되는지를

물리적인 관점에서 계산한다.

이것이

오늘날 PBR이

기존 Reflection Model보다 훨씬 현실적인 이유이다.

---

## Callback

Reflection Model은

Lambert,

Phong,

Blinn-Phong을 거치며

점점 현실에 가까워졌다.

Cook-Torrance는

Microfacet Theory를 기반으로

Reflection을 물리적으로 설명하는 단계에 도달하였다.

하지만

아직 D, G, F 각각이

어떻게 Reflection에 영향을 주는지는 살펴보지 않았다.

다음 장에서는

Material의 가장 중요한 속성 중 하나인

**Roughness**를 먼저 이해한 후,

D, G, F를 자세히 살펴본다.

---

## 핵심 요약

- Cook-Torrance는 Microfacet Theory 기반의 Reflection Model이다.
- Reflection을 물리적으로 계산하기 위해 만들어졌다.
- D는 Microfacet의 방향 분포를 계산한다.
- G는 가려짐과 차폐 효과를 계산한다.
- F는 Fresnel Effect를 계산한다.
- Cook-Torrance는 현대 PBR의 핵심 Reflection Model이다.

---

# PART III

## Cook-Torrance Components

> Cook-Torrance Reflection은 하나의 공식이 아니라,
> 여러 물리적인 요소가 결합되어 만들어진 Reflection Model이다.
>
> 이제부터는 Cook-Torrance를 구성하는 핵심 요소들을 하나씩 살펴본다.

---

# 5.11 Roughness

## 왜 같은 Material도 Highlight가 다를까?

금속은 모두 같은 Highlight를 가질까?

그렇지 않다.

같은 금속이라도

거울처럼 잘 연마된 금속은
선명하고 작은 Highlight를 만들고,

사포로 긁힌 금속은
넓고 흐린 Highlight를 만든다.

플라스틱도 마찬가지이다.

새 제품은 반짝이는 광택을 가지지만,

오랫동안 사용한 플라스틱은
광택이 줄어들고 Reflection이 넓게 퍼져 보인다.

이처럼 같은 Material이라도
Surface 상태에 따라 Reflection은 크게 달라질 수 있다.

---

## Roughness란?

이러한 Surface의 거친 정도를 나타내는 값이

**Roughness**이다.

Roughness는

Surface가 얼마나 매끄러운지,
또는 얼마나 거친지를 나타내는 Material Parameter이다.

보통

- Roughness = 0 에 가까울수록 매우 매끄러운 Surface
- Roughness = 1 에 가까울수록 매우 거친 Surface

를 의미한다.

즉,

Roughness는
Reflection의 강도를 조절하는 값이 아니라,

Reflection이 얼마나 넓게 퍼지는지를 결정하는 값이다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_11.png" width="80%">
</p>

---

## Roughness가 Reflection에 미치는 영향

Surface가 매우 매끄러우면

Microfacet들의 방향이 거의 일정하다.

따라서 Reflection은
하나의 방향으로 집중되고,

Highlight는 작고 선명하게 나타난다.

반대로

Surface가 거칠수록

Microfacet들은
서로 다른 방향을 향하게 된다.

그 결과

Reflection은 여러 방향으로 퍼지고,

Highlight도 넓고 부드럽게 나타난다.

즉,

> **Roughness가 증가할수록 Reflection은 넓게 퍼지고 Highlight는 흐려진다.**

---

## Roughness와 Microfacet

앞 장에서

Surface는 수많은 Microfacet으로 이루어져 있다고 설명하였다.

Roughness는

이 Microfacet들이
얼마나 다양한 방향을 향하고 있는지를 나타낸다.

- Roughness가 작다.
  - Microfacet들의 방향이 거의 비슷하다.
  - Reflection이 집중된다.

- Roughness가 크다.
  - Microfacet들의 방향이 다양하다.
  - Reflection이 넓게 퍼진다.

즉,

Roughness는

Microfacet의 방향 분포를 간접적으로 표현하는 값이라고 볼 수 있다.

---

## 왜 Roughness가 가장 중요한 Material Parameter일까?

오늘날 대부분의 PBR Material에서는

가장 중요한 입력 값으로
Roughness를 사용한다.

왜냐하면

사람이 Material을 구분할 때

가장 먼저 인식하는 특성 중 하나가

Reflection의 퍼짐 정도이기 때문이다.

같은 색(Material Color)을 가진 Surface라도

Roughness가 달라지면

전혀 다른 Material처럼 보일 수 있다.

이러한 이유로

Roughness는

현대 Rendering에서
가장 중요한 Material Parameter 중 하나가 되었다.

---

## Callback

Roughness는

Surface가 얼마나 거친지를 나타내는 값이며,

Reflection의 퍼짐 정도를 결정한다.

하지만 아직 한 가지 질문이 남아 있다.

> **Roughness는 실제 Reflection 계산에 어떻게 사용될까?**

다음 장에서는

Cook-Torrance의 첫 번째 구성 요소인

**Normal Distribution Function(D)** 를 통해

Microfacet의 방향 분포를 어떻게 계산하는지 살펴본다.

---

## 핵심 요약

- Roughness는 Surface의 거친 정도를 나타내는 Material Parameter이다.
- Roughness는 Reflection의 퍼짐 정도를 결정한다.
- Roughness가 작을수록 Highlight는 작고 선명하다.
- Roughness가 클수록 Highlight는 넓고 부드럽다.
- Roughness는 Microfacet의 방향 분포와 밀접한 관계가 있다.

---

# 5.12 Normal Distribution Function (D)

## Roughness만으로는 Reflection을 계산할 수 있을까?

앞 장에서는

Roughness가

Surface의 거친 정도를 나타내며,

Reflection의 퍼짐 정도를 결정한다는 것을 배웠다.

하지만 Roughness 자체만으로는

Reflection을 계산할 수 없다.

왜냐하면

Roughness는

Surface가 거칠다는 사실만 알려줄 뿐,

Microfacet들이

실제로 어떤 방향을 향하고 있는지는 알려주지 않기 때문이다.

---

## 얼마나 많은 Microfacet이 같은 방향을 향하고 있을까?

Microfacet Theory에서는

Surface가

수많은 작은 거울들로 이루어져 있다고 가정한다.

하지만

모든 Microfacet이

같은 방향을 향하고 있는 것은 아니다.

어떤 방향을 향한 Microfacet은 많고,

어떤 방향을 향한 것은 매우 적다.

그렇다면

Highlight를 만들 수 있는

Microfacet은

전체 중 얼마나 존재할까?

이 질문에 답하는 것이

**Normal Distribution Function(D)** 이다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_12.png" width="80%">
</p>

---

## Normal Distribution Function이란?

Normal Distribution Function(NDF)은

특정 방향을 향하고 있는

Microfacet이

얼마나 존재하는지를 계산하는 함수이다.

즉,

Reflection을 만드는

Microfacet의 분포를

확률적으로 표현한 것이다.

여기서 말하는 "Normal"은

정규분포(Normal Distribution)가 아니라

**Surface Normal**을 의미한다.

따라서

Normal Distribution Function은

Surface Normal의 분포를 나타내는 함수라고 이해하면 된다.

---

## Roughness와 D의 관계

Roughness는

Surface가 얼마나 거친지를 나타내는 값이다.

D는

그 Roughness를 이용하여

Microfacet들의 방향 분포를 계산한다.

즉,

Roughness는 입력 값이고,

D는 그 값을 이용해

Reflection 계산에 필요한 분포를 만들어 낸다.

---

## 대표적인 Distribution

Rendering에서는

여러 종류의 Distribution Function이 사용된다.

대표적으로는

- Beckmann Distribution
- GGX (Trowbridge-Reitz Distribution)

등이 있다.

초기의 Rendering에서는

Beckmann Distribution이 많이 사용되었지만,

오늘날 대부분의 PBR Engine은

GGX Distribution을 기본으로 사용한다.

이는

거친 Surface에서도

현실과 더 가까운 Highlight를 만들어 주기 때문이다.

이번 Chapter에서는

Distribution의 수학적 유도보다는

GGX가 현대 Rendering의 표준으로 사용된다는 점을 이해하는 것이 중요하다.

---

## Callback

Cook-Torrance에서

D는

Reflection을 만들 수 있는

Microfacet이 얼마나 존재하는지를 계산한다.

하지만

Microfacet이 존재한다고 해서

항상 Reflection이 눈에 도달하는 것은 아니다.

다른 Microfacet에 의해

빛이 가려질 수도 있기 때문이다.

다음 장에서는

이러한 차폐 효과를 계산하는

**Geometry Function(G)** 를 살펴본다.

---

## 핵심 요약

- D는 Normal Distribution Function이다.
- D는 특정 방향을 가진 Microfacet의 분포를 계산한다.
- Roughness는 D의 입력 값으로 사용된다.
- 현대 PBR에서는 GGX Distribution이 가장 널리 사용된다.
- D는 Cook-Torrance의 첫 번째 구성 요소이다.

---

# 5.13 Geometry Function (G)

## D만으로 Reflection을 계산할 수 있을까?

앞 장에서는

Normal Distribution Function(D)을 통해

특정 방향을 향하고 있는 Microfacet이

얼마나 존재하는지를 계산하였다.

하지만

Reflection을 만들 수 있는 Microfacet이 존재한다고 해서

항상 그 빛이 눈까지 도달하는 것은 아니다.

현실의 Surface에서는

다른 Microfacet이

빛을 가릴 수도 있기 때문이다.

---

## Microfacet끼리 서로 가려진다.

Surface는

수많은 Microfacet으로 이루어져 있다.

Surface가 거칠어질수록

Microfacet들은

서로 다른 방향을 향하게 된다.

이때

일부 Microfacet은

다른 Microfacet 뒤에 가려질 수 있다.

그 결과

빛이 Surface에 도달하지 못하거나,

반사된 빛이 눈까지 전달되지 못하는 현상이 발생한다.

즉,

실제로는 Reflection이 발생할 수 없는 상황이 생기는 것이다.

---

## 두 가지 차폐 현상

Geometry Function은

대표적으로 두 가지 현상을 계산한다.

### Shadowing

빛이 Surface에 들어오는 과정에서

다른 Microfacet에 의해 가려지는 현상이다.

즉,

Light Direction에서 발생하는 차폐이다.

---

### Masking

반사된 빛이

관찰자에게 전달되는 과정에서

다른 Microfacet에 의해 가려지는 현상이다.

즉,

View Direction에서 발생하는 차폐이다.

---

## Geometry Function이란?

Geometry Function(G)은

이러한 Shadowing과 Masking 효과를 고려하여

실제로 관찰자에게 도달할 수 있는 Reflection의 양을 계산하는 함수이다.

즉,

D가

Reflection을 만들 수 있는 Microfacet의 개수를 계산한다면,

G는

그 Reflection이 실제로 보일 수 있는지를 계산한다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_13.png" width="80%">
</p>

---

## 왜 G가 필요할까?

Geometry Function이 없다면

빛은 항상

모든 Microfacet에서

자유롭게 반사되는 것처럼 계산된다.

하지만 현실에서는

Surface가 거칠어질수록

Microfacet끼리 서로 가려지는 현상이 자주 발생한다.

Geometry Function은

이러한 차이를 반영하여

Reflection을 더욱 현실적으로 만든다.

---

## 대표적인 Geometry Function

Rendering에서는

여러 종류의 Geometry Function이 사용된다.

대표적으로

- Smith Geometry Function
- Schlick-GGX Geometry Function

등이 널리 사용된다.

오늘날 대부분의 PBR에서는

Smith 기반 Geometry Function을 사용하며,

GGX Distribution과 함께 사용하는 경우가 많다.

이번 Chapter에서는

Geometry Function의 수학적 유도보다,

왜 이러한 계산이 필요한지를 이해하는 것이 중요하다.

---

## Callback

Cook-Torrance에서

D는

Reflection을 만들 수 있는 Microfacet의 분포를 계산하였다.

G는

그 Reflection이

실제로 관찰자에게 도달할 수 있는지를 계산한다.

하지만

아직도 한 가지 요소가 남아 있다.

같은 Surface라도

빛이 들어오는 각도에 따라

반사되는 양 자체가 달라진다.

다음 장에서는

이 현상을 설명하는

**Fresnel(F)** 을 살펴본다.

---

## 핵심 요약

- G는 Geometry Function이다.
- G는 Shadowing과 Masking 효과를 계산한다.
- D는 Microfacet의 분포를 계산한다.
- G는 실제로 보이는 Reflection의 양을 계산한다.
- 현대 PBR에서는 Smith 기반 Geometry Function이 널리 사용된다.

---

# 5.14 Fresnel (F)

## 같은 Surface인데 왜 가장자리가 더 반짝일까?

금속 공이나 유리컵을 자세히 보면

정면보다 가장자리에서 Reflection이 더욱 강하게 나타나는 것을 볼 수 있다.

자동차 도장,

물 표면,

플라스틱,

심지어 사람 피부도

비슷한 현상을 보인다.

같은 Material인데도

보는 각도에 따라 Reflection의 세기가 달라지는 것이다.

왜 이런 현상이 발생할까?

---

## Fresnel Effect

이러한 현상을

**Fresnel Effect**라고 한다.

Fresnel Effect는

빛이 Surface에 입사하는 각도에 따라

Reflection의 양이 달라지는 현상이다.

빛이 Surface를 정면으로 비출 때보다,

비스듬한 각도로 들어올수록

더 많은 빛이 Reflection된다.

즉,

> **Surface를 비스듬히 바라볼수록 Reflection은 더욱 강해진다.**

이것은 거의 모든 Material에서 나타나는 자연스러운 물리 현상이다.

<p align="center">
    <img src="Figures/Chapter05/Fig5_14.png" width="80%">
</p>

---

## 왜 중요한가?

기존 Reflection Model에서는

Reflection의 세기를

일정한 값으로 계산하는 경우가 많았다.

하지만 현실에서는

같은 Surface라도

입사각에 따라 Reflection의 양이 계속 변한다.

Fresnel을 고려하면

Surface는 훨씬 자연스럽고 현실적으로 보인다.

특히

금속,

유리,

물과 같은 Material에서는

이 차이가 더욱 크게 나타난다.

---

## Cook-Torrance에서의 F

Cook-Torrance Reflection에서

F는

Fresnel Effect를 계산하는 요소이다.

즉,

현재의 입사각에서

얼마나 많은 빛이 Reflection되는지를 계산한다.

D가

Microfacet의 분포를 계산하고,

G가

Reflection이 실제로 보이는지를 계산했다면,

F는

Reflection의 양 자체를 결정한다.

---

## Schlick Approximation

현실의 Fresnel 방정식은

매우 복잡한 수학으로 이루어져 있다.

실시간 Rendering에서는

이를 그대로 계산하기 어렵다.

그래서 대부분의 Rendering Engine에서는

**Schlick Approximation**이라는

근사식을 사용한다.

이 방법은

계산량이 매우 적으면서도

현실과 매우 비슷한 Fresnel 결과를 얻을 수 있다.

오늘날 대부분의 PBR Engine은

Schlick Approximation을 사용하여

Fresnel을 계산한다.

---

## Callback

Cook-Torrance Reflection은

세 가지 핵심 요소로 이루어진다.

- D는 Microfacet의 방향 분포를 계산한다.
- G는 Shadowing과 Masking을 계산한다.
- F는 입사각에 따른 Reflection의 양을 계산한다.

이 세 요소가 함께 동작하여

현실적인 Reflection을 만들어 낸다.

하지만 아직 한 가지 질문이 남아 있다.

> **Reflection은 정확히 무엇을 계산하고 있는 것일까?**

다음 Part에서는

빛의 에너지를 어떻게 표현하는지 살펴보는

**Radiometry**를 알아본다.

---

## 핵심 요약

- Fresnel Effect는 입사각에 따라 Reflection의 양이 달라지는 현상이다.
- Surface를 비스듬히 바라볼수록 Reflection은 강해진다.
- F는 Cook-Torrance에서 Fresnel Effect를 계산하는 요소이다.
- 대부분의 PBR Engine은 Schlick Approximation을 사용한다.
- D, G, F가 함께 현실적인 Reflection을 만든다.

---

---

## PART III 정리

지금까지 Cook-Torrance Reflection을 구성하는 핵심 요소들을 살펴보았다.

Cook-Torrance는 하나의 거대한 공식이 아니라,

각기 다른 역할을 하는 세 가지 요소가 함께 동작하여 현실적인 Reflection을 만들어내는 Reflection Model이다.

- **Normal Distribution Function(D)** 는 Reflection을 만들 수 있는 Microfacet의 분포를 계산한다.
- **Geometry Function(G)** 는 Shadowing과 Masking을 고려하여 실제로 관찰자에게 도달하는 Reflection을 계산한다.
- **Fresnel(F)** 은 입사각에 따라 Reflection의 양이 어떻게 달라지는지를 계산한다.

이 세 요소는 서로 독립적으로 존재하는 것이 아니라, 하나의 Reflection Model 안에서 함께 작동하며 현실적인 Material 표현을 가능하게 한다.

하지만 아직 한 가지 중요한 질문이 남아 있다.

> **Cook-Torrance는 정확히 무엇을 계산하고 있는 것일까?**

지금까지는 Reflection의 형태와 특성을 중심으로 살펴보았다면,

다음 Part에서는 빛을 **에너지(Energy)** 의 관점에서 바라보는 **Radiometry**를 통해 Reflection이 실제로 어떤 물리량을 계산하는지 알아본다.

---

# PART IV

## Light and BRDF

> 지금까지는 Reflection이 어떻게 만들어지는지를 살펴보았다.
>
> 이제부터는 Reflection을 구성하는 **빛(Light)** 을 물리적인 관점에서 이해하고,
> Surface가 빛을 어떻게 반사하는지를 설명하는 **BRDF**를 알아본다.

---

# 5.15 Radiometry

## 왜 빛을 측정해야 할까?

현실의 빛은

밝기도 다르고,

방향도 다르며,

거리와 Surface의 상태에 따라서도

전달되는 양이 달라진다.

Rendering에서는

이러한 빛을 단순히

"밝다", "어둡다"라고 표현하는 것이 아니라,

얼마나 많은 빛의 에너지가 이동하는지를

수학적으로 계산해야 한다.

이를 위해 사용하는 체계가

**Radiometry**이다.

---

## Radiometry란?

Radiometry는

빛을 **에너지(Energy)** 의 관점에서 측정하는 학문이다.

즉,

빛이

얼마나 많이 방출되고,

얼마나 많이 전달되며,

얼마나 많이 Surface에 도달하고,

얼마나 많이 반사되는지를

물리량으로 표현한다.

Rendering에서 사용하는 대부분의 Reflection 계산은

Radiometry를 기반으로 한다.

---

## 왜 Radiometry가 필요한가?

지금까지 살펴본

Lambert,

Phong,

Blinn-Phong,

Cook-Torrance는

모두 Reflection을 계산하는 모델이다.

하지만

이 Reflection들은

무언가를 반사하고 있다.

그 "무언가"가 바로

빛의 에너지이다.

즉,

Reflection Model은

빛의 에너지를 입력으로 받아

Surface에서 어떻게 반사되는지를 계산하는 것이다.

Radiometry는

바로 그 입력이 되는 빛을 정의한다.

---

## Radiometry의 네 가지 핵심 물리량

Rendering에서 가장 자주 등장하는 Radiometry의 물리량은

다음 네 가지이다.

- **Radiant Flux(Φ)** : 광원이 방출하는 전체 빛의 에너지
- **Irradiance(E)** : Surface에 도달한 빛의 양
- **Radiance(L)** : 특정 방향으로 전달되는 빛의 양
- **Radiant Intensity(I)** : 특정 방향으로 방출되는 빛의 세기

이들은 각각

빛이

방출되고,

전달되고,

Surface에 도달하며,

다시 반사되는 과정을 설명한다.

---

## 지금 모두 외울 필요는 없다.

처음 Radiometry를 접하면

용어가 많고 비슷해 보여 어렵게 느껴질 수 있다.

하지만 지금 단계에서는

각 물리량의 정의를 모두 암기할 필요는 없다.

중요한 것은

Rendering이

빛의 에너지를 계산하는 과정이며,

Radiometry는

그 에너지를 표현하기 위한 언어라는 점이다.

각 물리량은

이후 BRDF를 설명하면서

자연스럽게 다시 등장하게 된다.

---

## Callback

지금까지는

빛 자체를 설명하였다.

하지만

Rendering에서 중요한 것은

빛 자체보다

빛이 Surface에서 어떻게 반사되는가이다.

이 관계를 수학적으로 표현한 것이

**BRDF(Bidirectional Reflectance Distribution Function)** 이다.

다음 장에서는

BRDF가 무엇이며,

왜 현대 Rendering의 핵심 개념이 되었는지 알아본다.

---

## 핵심 요약

- Radiometry는 빛을 에너지의 관점에서 측정하는 체계이다.
- Reflection Model은 빛의 에너지를 입력으로 사용한다.
- Rendering은 빛의 이동과 반사를 계산하는 과정이다.
- Radiometry는 BRDF를 이해하기 위한 기초가 된다.

---

# 5.16 BRDF란?

## Reflection Model만으로는 충분할까?

지금까지

Lambert,

Phong,

Blinn-Phong,

Cook-Torrance와 같은 Reflection Model을 살펴보았다.

이들은 모두

Surface가 빛을 어떻게 반사하는지를 설명하는 모델이다.

하지만 여기서 한 가지 질문이 생긴다.

> **Reflection을 수학적으로 표현하는 공통된 방법은 없을까?**

Reflection Model마다 계산 방법은 다르지만,

모두 같은 목적을 가지고 있다.

빛이 Surface에 도달했을 때,

그 빛이 어떤 방향으로 얼마나 반사되는지를 계산하는 것이다.

이러한 관계를 일반적인 형태로 정의한 것이

**BRDF(Bidirectional Reflectance Distribution Function)** 이다.

---

## BRDF란?

BRDF는

Surface에 들어오는 빛과

Surface를 떠나는 빛의 관계를 정의하는 함수이다.

즉,

입사한 빛이

어떤 방향으로,

얼마나 반사되는지를 수학적으로 표현한 것이다.

Reflection Model은

바로 이 BRDF를 구현하는 다양한 방법이라고 볼 수 있다.

---

## Bidirectional의 의미

BRDF에서

**Bidirectional**은

두 개의 방향(Direction)을 의미한다.

첫 번째는

빛이 들어오는 방향(Light Direction)이고,

두 번째는

빛이 나가는 방향(View Direction)이다.

BRDF는

이 두 방향의 관계를 이용하여

Surface의 Reflection을 계산한다.

즉,

BRDF는

"빛이 어디에서 왔는가?"

그리고

"어디로 반사되는가?"

를 동시에 고려하는 함수이다.

---

## Reflection Model과 BRDF의 관계

지금까지 배운 Reflection Model은

모두 서로 다른 계산 방식을 사용한다.

하지만

이들은 모두

BRDF라는 공통된 개념 안에서 이해할 수 있다.

예를 들어,

- Lambert는 Diffuse Reflection을 표현하는 BRDF이다.
- Phong은 Specular Reflection을 근사한 BRDF이다.
- Blinn-Phong은 Half Vector를 이용한 BRDF이다.
- Cook-Torrance는 Microfacet Theory를 기반으로 한 BRDF이다.

즉,

BRDF는 하나의 특정 Reflection Model이 아니라,

Reflection을 표현하는 일반적인 틀(Framework)이라고 할 수 있다.

---

## 왜 BRDF가 중요한가?

현대 Rendering에서는

새로운 Reflection Model을 설계할 때도

BRDF의 형태로 표현하는 경우가 많다.

즉,

BRDF는

특정 알고리즘이 아니라,

Reflection을 설명하는 공통 언어이다.

따라서

BRDF를 이해하면

Lambert부터 Cook-Torrance까지

서로 다른 Reflection Model을

하나의 관점에서 바라볼 수 있게 된다.

---

## Callback

지금까지는

BRDF가 무엇인지 살펴보았다.

하지만 아직

BRDF가 실제로 어떤 값을 입력받고,

어떤 값을 출력하는지는 설명하지 않았다.

다음 장에서는

BRDF의 입력과 출력이 무엇이며,

빛이 어떻게 Surface를 통해 전달되는지를 알아본다.

---

## 핵심 요약

- BRDF는 Surface에 들어오는 빛과 나가는 빛의 관계를 정의하는 함수이다.
- BRDF는 두 방향(Light Direction, View Direction)을 함께 고려한다.
- Reflection Model은 BRDF를 구현하는 다양한 방법이다.
- BRDF는 현대 Rendering에서 Reflection을 설명하는 공통 Framework이다.

---

# 5.17 BRDF의 입력과 출력

## BRDF는 무엇을 계산할까?

앞 장에서는

BRDF가

Surface에 들어오는 빛과

나가는 빛의 관계를 정의하는 함수라는 것을 살펴보았다.

그렇다면

BRDF는 정확히 무엇을 입력받고,

무엇을 출력하는 것일까?

---

## 입력(Input)

BRDF가 Reflection을 계산하기 위해서는

먼저 Surface에 도달한 빛에 대한 정보가 필요하다.

대표적인 입력은 다음과 같다.

- Light Direction(L)
- View Direction(V)
- Surface Normal(N)
- Surface Material

즉,

빛이 어디에서 들어오고,

관찰자가 어디에서 바라보며,

Surface가 어떤 방향을 향하고 있는지를 이용하여

Reflection을 계산한다.

---

## 출력(Output)

BRDF의 출력은

관찰자 방향으로 반사되는 빛의 양이다.

즉,

특정 방향으로 들어온 빛이

현재의 View Direction에서

얼마나 보이는지를 계산하는 것이다.

중요한 점은

BRDF가

Surface 전체의 밝기를 계산하는 것이 아니라,

**특정 방향으로 반사되는 빛의 비율**을 계산한다는 것이다.

---

## 입력과 출력의 관계

간단히 표현하면

BRDF는

다음과 같은 관계를 가진다.

> **Incoming Light → Surface → Outgoing Light**

빛이 Surface에 도달하면

Surface의 Material과 방향에 따라

Reflection이 결정되고,

그 결과가

관찰자 방향으로 전달된다.

즉,

BRDF는

입력된 빛을

Surface의 특성에 맞게 변환하는 함수라고 볼 수 있다.

---

## Reflection Model은 어디에 있을까?

Lambert,

Phong,

Blinn-Phong,

Cook-Torrance는

모두

이 변환 과정을

각기 다른 방식으로 계산한다.

즉,

Reflection Model은

BRDF 내부에서

Reflection의 특성을 정의하는 계산식이라고 이해할 수 있다.

이러한 관점에서 보면

BRDF는 공통 인터페이스이고,

Reflection Model은

그 인터페이스를 구현하는 다양한 알고리즘이라고 볼 수 있다.

---

## Callback

지금까지는

BRDF가

무엇을 입력받고,

무엇을 출력하는지 살펴보았다.

이제 마지막으로

BRDF를 수학적으로 어떻게 표현하는지 알아볼 차례이다.

다음 장에서는

Rendering에서 가장 자주 등장하는 BRDF의 수학적 정의를 살펴본다.

---

## 핵심 요약

- BRDF는 Light Direction, View Direction, Surface Normal 등의 정보를 입력으로 사용한다.
- BRDF는 특정 방향으로 반사되는 빛의 양을 계산한다.
- BRDF는 입력된 빛을 Surface의 특성에 따라 변환하는 함수이다.
- Reflection Model은 BRDF를 구현하는 계산식이다.

---

# 5.18 BRDF의 수학적 정의

## BRDF는 어떻게 표현될까?

앞 장에서는

BRDF가

Surface에 들어오는 빛과

나가는 빛의 관계를 정의하는 함수라는 것을 살펴보았다.

그렇다면

이 관계는 실제로 어떻게 표현될까?

Rendering에서는

BRDF를 일반적으로 다음과 같이 표현한다.

\[
f_r(\omega_i,\omega_o)
\]

이 식은

복잡한 계산식을 의미하는 것이 아니라,

BRDF라는 함수 자체를 나타내는 가장 기본적인 표현이다.

---

## 기호의 의미

각 기호는 다음과 같은 의미를 가진다.

- **f<sub>r</sub>** : BRDF(Bidirectional Reflectance Distribution Function)
- **ω<sub>i</sub>** : Incoming Direction (빛이 들어오는 방향)
- **ω<sub>o</sub>** : Outgoing Direction (빛이 나가는 방향)

즉,

BRDF는

들어오는 방향과

나가는 방향을 입력으로 받아

Reflection의 특성을 계산하는 함수이다.

---

## 왜 Direction만 사용할까?

여기서

조금 이상하게 느껴질 수도 있다.

"빛의 세기는 어디에 있을까?"

"Material은 어디에 있을까?"

실제로는

빛의 세기,

Material의 특성,

Surface Normal 등

여러 요소가 Reflection 계산에 함께 사용된다.

하지만

BRDF 자체는

Surface의 고유한 Reflection 특성을 정의하는 함수이므로,

기본적인 정의에서는

빛이 들어오는 방향과

나가는 방향의 관계에 집중한다.

다른 요소들은

Rendering Equation에서

함께 사용된다.

---

## Reflection Model과 BRDF

Lambert,

Phong,

Blinn-Phong,

Cook-Torrance는

모두 서로 다른 계산식을 사용한다.

하지만

결국 모두

하나의 BRDF를 정의한다는 공통점을 가진다.

즉,

Reflection Model은

각각 다른 형태의 BRDF라고 볼 수 있다.

이러한 관점에서 보면

Reflection Model은

BRDF를 구현한 구체적인 예시이며,

BRDF는

그들을 모두 포함하는 일반적인 개념이다.

---

## Rendering Equation과의 관계

BRDF는

혼자 사용되는 경우는 거의 없다.

실제 Rendering에서는

빛의 에너지(Radiometry)와 함께 사용되어

최종적으로 Surface의 밝기를 계산한다.

이 전체 과정을 표현한 식이

**Rendering Equation**이다.

Chapter 5에서는

BRDF의 개념까지 이해하는 것을 목표로 하며,

Rendering Equation은

이후 Chapter에서 자세히 살펴본다.

---

## Callback

지금까지

Reflection의 기본 개념부터

Lambert,

Phong,

Blinn-Phong,

Cook-Torrance,

그리고 BRDF까지

Reflection을 설명하는 핵심 개념들을 모두 살펴보았다.

마지막으로

Lambert Reflection은

과연 BRDF라고 할 수 있을까?

다음 장에서는

이 질문을 통해

Reflection Model과 BRDF의 관계를 다시 한번 정리해본다.

---

## 핵심 요약

- BRDF는 일반적으로 \(f_r(\omega_i,\omega_o)\)로 표현한다.
- BRDF는 Incoming Direction과 Outgoing Direction의 관계를 정의한다.
- Reflection Model은 각각 다른 형태의 BRDF를 구현한 것이다.
- BRDF는 Rendering Equation의 핵심 구성 요소이다.

---

# 5.19 Lambert는 BRDF인가?

## Lambert Reflection은 BRDF일까?

지금까지

Lambert,

Phong,

Blinn-Phong,

Cook-Torrance를 차례대로 살펴보았다.

그리고

이러한 Reflection Model을

하나의 공통된 관점에서 설명하는 개념이

BRDF라는 것도 배웠다.

그렇다면

가장 오래된 Reflection Model인

Lambert Reflection도

BRDF라고 할 수 있을까?

정답은

> **그렇다. Lambert Reflection 역시 BRDF이다.**

---

## 왜 Lambert도 BRDF일까?

BRDF는

Surface에 들어오는 빛과

나가는 빛의 관계를 정의하는 함수이다.

Lambert Reflection 역시

입사한 빛이

Surface에서 어떻게 반사되는지를 계산한다.

즉,

Lambert는

Diffuse Reflection을 표현하는 하나의 BRDF인 것이다.

비록 계산 방법은 단순하지만,

BRDF의 정의는 충분히 만족한다.

---

## Reflection Model은 모두 BRDF일까?

Lambert만이 아니다.

지금까지 살펴본

- Lambert
- Phong
- Blinn-Phong
- Cook-Torrance

모두

각각의 방식으로 Reflection을 계산하는 BRDF이다.

차이가 있다면

Reflection을 근사하는 방법과

현실을 얼마나 정확하게 표현하는가에 있다.

즉,

BRDF는 하나이고,

Reflection Model은

그 BRDF를 구현하는 다양한 방법이라고 이해할 수 있다.

---

## BRDF는 하나의 공통 언어이다.

그래픽스의 역사를 살펴보면

Reflection Model은 계속 발전해 왔다.

Lambert는

Diffuse Reflection을 간단하게 표현하였고,

Phong과 Blinn-Phong은

Specular Reflection을 추가하였다.

이후

Microfacet Theory를 기반으로

Cook-Torrance가 등장하면서

현실에 더욱 가까운 Reflection을 표현할 수 있게 되었다.

하지만

이 모든 모델은

결국 BRDF라는 공통된 개념 안에서 설명할 수 있다.

즉,

BRDF는

특정 Reflection Model을 의미하는 것이 아니라,

Reflection을 바라보는 공통된 Framework이다.

---

## Chapter 5 정리

이번 Chapter에서는

Reflection의 기본 개념부터

현대 Rendering에서 사용하는 BRDF까지

Reflection을 설명하는 핵심 개념을 순서대로 살펴보았다.

학습의 흐름을 다시 정리하면 다음과 같다.

- Reflection의 기본 원리를 이해한다.
- Reflection Model의 발전 과정을 살펴본다.
- Microfacet Theory와 Cook-Torrance를 통해 현대 PBR의 기반을 이해한다.
- Cook-Torrance를 구성하는 D, G, F 요소를 학습한다.
- Radiometry를 통해 빛을 에너지의 관점에서 이해한다.
- BRDF를 통해 Reflection을 하나의 공통된 Framework로 이해한다.

이 과정을 통해

각각의 Reflection Model을

개별적인 알고리즘으로 암기하는 것이 아니라,

하나의 흐름 속에서 이해할 수 있게 된다.

---

## 다음 Chapter

Chapter 5에서는

빛이 Surface에서 어떻게 반사되는지를 살펴보았다.

다음 Chapter에서는

Material이 이러한 Reflection에 어떤 영향을 주는지,

그리고 실제 PBR Material이 어떻게 구성되는지를 살펴본다.

---

## 핵심 요약

- Lambert Reflection도 BRDF의 한 종류이다.
- Reflection Model은 모두 서로 다른 형태의 BRDF를 구현한다.
- BRDF는 Reflection을 설명하는 공통 Framework이다.
- Reflection Model은 발전해 왔지만, 모두 같은 목표를 가진다.
- Chapter 5는 Reflection부터 BRDF까지의 흐름을 연결하는 과정이었다.