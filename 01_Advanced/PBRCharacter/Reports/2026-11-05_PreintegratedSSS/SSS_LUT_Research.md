# RTR / ASF Advanced — Preintegrated SSS LUT Research

> Updated: 2026-11-05 (KST)
> Environment: Unreal Engine 5.8.3 / CL 58210709 / Android Vulkan High Preview / Mobile Forward
> Status: Numerical LUT R&D / Production integration pending

## 프로젝트 확인과 산출물 배치

요청서의 `local path withheld`는 README, Chapter01–06, Figures, Captures, Reports, MasterMaterial을 관리하는 **문서 저장소**다. 이 위치에 `.uproject`나 Content가 없음을 확인했다. 기존 Chapter06의 Evidence and Project Identity와 실제 파일을 대조했다.

실제 대상은 `local path withheld`다. EngineAssociation은 5.8이며 설치 Engine `Build.version`은 5.8.3 / CL 58210709다. 기존 `Content\ASF\PBR`에는 `Textures`(복수형), Mobile, Masters, Instances, Profile이 있다. 요청한 **`Texture`(단수형)**는 별도 신규 폴더다. 문서 폴더에 가짜 Content를 만들지 않는다.

* 최종 canonical PNG 및 Import된 `.uasset`: 실제 UE 프로젝트 `Content\ASF\PBR\Texture`.
* 이 문서, generator, 검증 결과, float 원본, RGB16 및 도표: 문서 저장소 `Reports\2026-11-05_PreintegratedSSS`.
* 기존 Desktop / Mobile Material, Mesh, Engine Source 및 프로젝트 설정은 수정하지 않는다.

## 1. 채택 모델과 출처 간 차이

선택은 **Penner Appendix A의 normalized 1D ring approximation**이다. 새로운 BSSRDF를 측정한 결과나 3D 광수송의 정답으로 해석하지 않는다. 곡률로 바뀌는 clamped-cosine direct diffuse 응답을 Gaussian skin profile로 수치 적분한다. LUT는 albedo, light color/intensity, specular, environment lighting, external shadow visibility를 포함하지 않는다.

추적용 원래 profile은 d'Eon / Luebke의 [GPU Gems 3 Chapter 14 §14.4.7](https://developer.nvidia.com/gpugems/gpugems3/part-iii-rendering/chapter-14-advanced-techniques-realistic-real-time-skin), 특히 [Figure 14-13](https://developer.download.nvidia.com/books/gpugems3/14fig13.jpg)이다. Donner / Jensen 2005 three-layer skin diffusion의 six-Gaussian fit이다. 모든 피부색·피부 두께의 공통 측정값은 아니다.

| i | Original variance v, mm² | Red weight | Green weight | Blue weight |
|---|---:|---:|---:|---:|
| 1 | 0.0064 | 0.233 | 0.455 | 0.649 |
| 2 | 0.0484 | 0.100 | 0.336 | 0.344 |
| 3 | 0.1870 | 0.118 | 0.198 | 0.000 |
| 4 | 0.5670 | 0.113 | 0.007 | 0.007 |
| 5 | 1.9900 | 0.358 | 0.004 | 0.000 |
| 6 | 7.4100 | 0.078 | 0.000 | 0.000 |

RGB 각각 가중치 합은 1이다. 원래 **2D radial Gaussian**은 `G2(d,v) = exp(-d²/(2v))/(2πv)`이다. 이 연구의 ring에는 다음 **1D Gaussian**을 쓴다. 두 식은 정규화 차원이 다르다. 2D 식에 단순히 ring 좌표만 대입해서 같은 모델이라고 부르지 않는다.

| Source / difference | 이번 구현의 결정 |
|---|---|
| Penner / Borshukov 본문 Eq. 5.1의 full-ring 범위와 unclamped cosine은 Appendix Listing 5.1 코드와 다르다. | Appendix의 `[-π/2, π/2]` 및 clamped cosine을 따른다. |
| 공식 SIGGRAPH 2011 slides 29 / 92는 sphere 또는 ring 적분을 설명하며 slide 92는 cosine clamp 정정을 포함한다. | `max(0, cos(...))`를 적용한다. |
| Appendix 코드는 variance에 1.414를 곱한다. | 출판된 구현과의 호환 계수로 보존한다. 물리 단위 변환이나 엄밀한 2D→1D 유도라고 주장하지 않는다. |
| 2018 reprint Table 5.1의 두 번째 Green은 .366, Appendix와 NVIDIA 원본은 .336이다. | 원본 그림 및 Appendix와 일치하는 .336을 채택한다. .366이면 Green 합이 1.03이 된다. |

즉, 기본 effective variance는 원본의 1.414배이고 sigma는 원본의 `sqrt(1.414) ≈ 1.1891`배다. `sigma × 1.414`가 아니다. mm 범위는 이 선택에 종속된다. 임상적 조직 반경 보정값으로 해석하지 않는다.

## 2. 명시적 적분

`mu = clamp(NdotL, -1, 1)`, `theta = acos(mu)`, `R > 0` (mm)로 둔다. `alpha`는 관측점에서 ring 이웃까지의 각도다.

```text
v_eff[i] = 1.414 * v[i]                         # mm²
g(d,v)   = exp(-d*d/(2*v)) / sqrt(2*pi*v)        # 1/mm
P_c(d)   = sum_i weight[i,c] * g(d,v_eff[i])
d(R,a)   = abs(2*R*sin(a/2))                    # chord distance, mm
E(mu,a)  = max(0, cos(acos(mu)+a))

             integral[-pi/2,pi/2] E(mu,a)*P_c(d(R,a)) da
D_c(mu,R) = ------------------------------------------------
             integral[-pi/2,pi/2] P_c(d(R,a)) da
```

거리는 arc `R*abs(alpha)`가 아니라 chord다. line measure를 `ds=R da`로 써도 분자·분모의 일정한 R은 상쇄된다. 면적 적분의 Jacobian, 다른 principal curvature 축이나 full-sphere transmission을 추가하지 않는다. 정규화는 각 채널별이며, 유한 구간의 kernel 질량을 1로 맞춘다. 입력 irradiance가 상수 1이면 출력도 1이다. 양의 kernel의 가중 평균이므로 D는 수학적으로 [0,1] 안이다.

실제 구현은 float64 composite midpoint rule이다. 기본 8192개 등간격 스텝, `delta_alpha=π/8192`, `alpha_k=-π/2+(k+0.5)*delta_alpha`를 쓴다. 무작위 샘플이나 이미지 생성 모델은 사용하지 않는다. 검증 시 스텝을 두 배로 늘리고 별도 quadrature reference와 비교한다. 상세 수치는 `SSS_LUT_Validation.md`와 `sss_lut_validation.json`에 기록한다. Generator의 cumulative cosine/sine sum은 같은 midpoint 표본의 clamped cosine 합을 가속하는 계산이며, 별도 직접 합과도 대조한다.

이 결과는 complete diffuse response다. Lambert에 추가할 독립적인 scattering-only 색상이 아니다. half-ring 정의에서 `mu=-1`은 0이고, mu=0 부근에는 RGB별 terminator spread가 나타난다. 큰 R에서는 Lambert로 수렴한다. Ear transmission과 occluder를 넘어오는 빛은 별도 모델이 필요하다.

## 3. LUT 좌표 계약

256×256 RGB, row-major, 왼쪽→오른쪽 U 증가, PNG 첫 행→마지막 행 V 증가다. 위쪽이 R=100 mm, 아래쪽이 R=1 mm다. UE에서 V를 뒤집지 않는다.

```text
U = (NdotL + 1)/2
V = log(100/R_mm) / log(100)       # logarithmic inverse-radius axis
R_mm = 100 * 0.01**V
curvature k = 1/R_mm              # mm^-1, convex magnitude only
```

| V | R (mm) | k (mm⁻¹) |
|---:|---:|---:|
| 0 | 100 | 0.01 |
| 0.25 | 31.6228 | 0.0316228 |
| 0.5 | 10 | 0.1 |
| 0.75 | 3.16228 | 0.316228 |
| 1 | 1 | 1 |

endpoint grid는 `U=i/255`, `V=j/255`다. GPU bilinear lookup이 이 grid에 정확히 대응하도록 sample UV에는 다음 보정을 한 번 적용한다.

```text
UV_sample = (saturate(float2(U,V))*255 + 0.5)/256
          = saturate(float2(U,V))*0.99609375 + 0.001953125
```

물리 의미의 U,V는 변하지 않고 Texture의 texel center로만 옮긴다. U=V=.5는 중앙 두 texel 사이의 보간값이다. 보정을 빼도 대략적인 디버그는 가능하지만 정확한 수치 비교에는 보정한다. Radius는 [1,100] mm에서 clamp하며, 그 밖 영역을 측정했다고 주장하지 않는다. UE 기본 cm 단위의 radius를 쓴다면 `R_mm=10*R_cm`; curvature가 cm⁻¹라면 `k_mm^-1=k_cm^-1/10`이다.

Marmoset 일반 Convex/Concave bake는 remap, scale, smoothing, bake distance, mesh 크기에 의존하는 artist mask다. gray=.5를 10 mm로 곧바로 해석하지 않는다. 알려진 1/3/10/30/100 mm sphere를 같은 단위·옵션으로 bake하고 monotonic 대응을 검증하거나, mesh 위치와 normal에서 물리 curvature를 별도 계산하여 R로 변환한다. concave, saddle 및 비균일 scaling은 단일 convex ring 가정의 범위 밖이다. deformation 이후의 bake 유효성도 별도 검증한다.

## 4. 파일 표현과 Unreal Import

8-bit RGB PNG에는 선형 응답값 자체를 `round(D*255)`로 저장한다. gamma encoding과 sRGB/gAMA/iCCP chunk를 넣지 않는다. 화면에서 보이는 PNG 밝기와 데이터의 물리적 해석은 다를 수 있다. float64로 계산하고 float32 `.npy`와 16-bit RGB PNG를 보고서 폴더에 보관한다. 정규화를 제외한 creative gain, 색상 grading, gamma, tonemap은 없다. 출력 clipping은 정상 계산을 가리지 않도록 검증 전에 금지한다; 이번 구현에는 clipping 연산이 없으며 범위 검증을 통과해야 파일을 저장한다.

canonical PNG 하나와 같은 basename의 `.uasset`만 Content에 둔다. PNG는 source data이며 `.uasset` 등록을 대체하지 않는다. 보고서·RGB16·diagnostic PNG를 Content에 놓으면 Auto Reimport의 Auto Create Assets가 불필요한 추가 에셋을 만들 수 있으므로 밖에 둔다. [Epic Auto Reimport](https://dev.epicgames.com/documentation/en-us/unreal-engine/reimporting-assets-automatically-in-unreal-engine)의 source와 asset 동거 방식을 따른다.

목표 설정은 sRGB OFF, VectorDisplacementmap (RGBA8, 비압축 선형 기준), NoMipmaps, Clamp U/V, Bilinear, Virtual Texture OFF다. Masks는 RGB block 압축 오차를 만들 수 있어 이번 reference에서는 쓰지 않는다. 모바일 production compression 변경은 실기기 sample error와 메모리 검증 후 결정한다. 실제 적용·재로드 확인 여부는 Validation 문서가 구분한다.

## 5. Production 통합 판단

일반 Material Graph의 수동 Light direction은 엔진의 per-light shadow / attenuation / GI를 가져오지 않는다. [Epic LightVector 문서](https://dev.epicgames.com/documentation/en-us/unreal-engine/vector-material-expressions-in-unreal-engine)도 해당 표현식의 Domain 제약을 명시한다. `Unlit + Emissive = LUT`는 입사각/곡률 응답의 독립 디버그다. Scene 차폐를 자동 수신하는 Production skin shading이 아니다.

* 기존 Default Lit / Subsurface 응답에 전체 LUT를 Add하면 diffuse가 중복된다. emissive 덧셈은 그림자에서 발광하는 shadow leak을 만들 수 있다.
* `D-Lambert` 차분도 signed 값, light color/intensity, attenuation 및 같은 visibility가 필요하다. 단순 Saturate 후 Add는 에너지 균형을 깨뜨린다. BaseColor에 D 또는 D/Lambert를 넣으면 엔진이 다시 NdotL과 여러 광원을 적용한다; terminator 부근 나눗셈도 불안정하다.
* 엔진 수정 금지 조건에서 현실적인 첫 단계는 이 LUT를 독립 Debug로 검증하고, 대상 Mobile Forward / Substrate에서 실제 지원되는 native shading 경로를 유지하는 것이다. full per-light diffuse 교체는 일반 Surface Graph만으로 보장되지 않는다.
* 제한된 단일 수동 광원 Unlit renderer를 선택할 경우 shadow/occlusion, specular, indirect light, intensity 단위까지 직접 설계해야 한다. 이는 별도 연구 범위이며 이번 결과를 무조건 Add하는 통합이 아니다.
* 별도 shadow-penumbra LUT와 channel별 normal prefilter는 Penner의 다른 구성요소다. 이번 curvature LUT만으로 재현하지 않았다. [MJP](https://therealmjp.github.io/posts/sss-intro/)의 curvature deformation / triangle discontinuity / shadow 및 indirect lighting 한계를 함께 따른다.

Android Vulkan High Preview는 Windows에서 대상 feature 수준을 확인하는 수단이다. 실제 Android GPU frame time, texture format, driver, 발열, 대역폭 측정이 아니다.

## Source References

1. Eric Penner, *Pre-Integrated Skin Shading*, SIGGRAPH 2011 Advances in Real-Time Rendering. [공식 course](https://www.advances.realtimerendering.com/s2011/index.html), [공식 PPTX](https://advances.realtimerendering.com/s2011/Penner%20-%20Pre-Integrated%20Skin%20Rendering%20%28Siggraph%202011%20Advances%20in%20Real-Time%20Rendering%20Course%29.pptx). Slides 29, 46–47, 92 및 cosine 정정 확인.
2. Eric Penner / George Borshukov, *Pre-Integrated Skin Shading*, GPU Pro 2, 2011, pp.41–55; 같은 저자 재수록 GPU Pro 360: Guide to Rendering, 2018, Chapter5, Appendix A / Listing5.1 pp.92–93. 출판본 본문/표/Appendix의 불일치는 위 결정표에 보존. [출판사 chapter record](https://uat-preview85.sspbloomsbury.co.uk/encyclopedia-chapter?docid=&tocid=b-9781351261524-chapter5)에 해당하는 PDF endpoint의 cached text extraction으로 Appendix를 교차 확인했다. 별도의 live PDF endpoint 요청은 HTTP200/0 bytes였으므로 현재 PDF 다운로드나 페이지 이미지 검증에 성공한 것으로 기록하지 않는다. 공식 PPTX와 NVIDIA table image는 실제 다운로드하여 확인했다. 정확한 PDF endpoint는 `SSS_LUT_SourceVerification.json`에 보존한다.
3. Eugene d'Eon / David Luebke, [GPU Gems 3 Chapter14](https://developer.nvidia.com/gpugems/gpugems3/part-iii-rendering/chapter-14-advanced-techniques-realistic-real-time-skin), 2007, §14.4.7, Fig14-13. 원본 Gaussian table와 variance mm² 기준.
4. Matt Pettineo, [An Introduction To Real-Time Subsurface Scattering](https://therealmjp.github.io/posts/sss-intro/), 2019-10-06. Pre-integrated SSS 설명과 실무 한계.
5. Epic Games, [Python Editor scripting](https://dev.epicgames.com/documentation/en-us/unreal-engine/scripting-the-unreal-editor-using-python), [Auto Reimport](https://dev.epicgames.com/documentation/en-us/unreal-engine/reimporting-assets-automatically-in-unreal-engine), [Vector Material Expressions](https://dev.epicgames.com/documentation/en-us/unreal-engine/vector-material-expressions-in-unreal-engine). API와 현재 설치 UE 5.8.3 header를 대조했다.

자료 접근일: 2026-11-05 KST. 제공되지 않은 측정 skin profile이나 기기 성능 수치는 추정으로 채우지 않는다.
