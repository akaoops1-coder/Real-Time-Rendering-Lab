# Chapter 02 — Production Skin Shader

> Public edition — 공개 검토를 통과한 자료와 기술 기록을 담았다. [Public Release Scope](Public_Release_Scope.md)

> Module : Production Skin Shader / Subsurface Profile / Thickness-driven SSS
> Document Status : Draft / User Review
> Implementation Status : First Implementation Complete — User Reported
> Updated : 2026-10-16 (KST)
> Environment : Unreal Engine 5.8.3 / Deferred Shading — User Reported
> Scope : `M_PBR_Skin`, `SSP_Skin`, `MI_Character_Head_Skin`, Thickness-driven SSS and Visual Validation

이 문서는 Chapter 02의 Skin 구현 기록이다. 공통 Master 구조는 [Chapter 01 — Production PBR Master Material](Chapter01_ProductionPBRMasterMaterial.md)의 Section 1.1–1.9를 참조한다. 공통 UV, Base Color, Normal, ORM, Detail Normal과 Static Switch의 기본 구조는 기존 문서를 참조하고, 여기서는 얼굴에 적용한 Skin 전용 Shading Model, Profile, Thickness 제어와 검증 결과를 다룬다. Foundation의 PBR 기본 원리는 다시 설명하지 않는다.

현재 Skin은 **1차 구현 완료** 상태다. 사용자는 현재 결과를 Skin의 1차 완료 기준으로 선택하고 Hair Material 작업으로 이동했다. 이 기록은 추가 구현을 기다리지 않고 그 시점의 연결, 관찰과 기술적 판단을 남긴다. 최종 Lookdev와 Production Ready 검증은 Hair Card Material 완성 후 재검증하며, Performance Profiling도 후속 작업이다.

구현과 Parameter 값은 사용자 제공 기록을 기준으로 작성했다. 문서 작성 및 Figure 추가 반영 시 로컬의 `Fig2_01.png`–`Fig2_04.png`를 직접 확인했다. Unreal Editor를 실행하거나 저장된 Material Graph와 Profile Asset을 다시 검사하지 않았다. Figure는 Chapter 02의 번호와 경로를 사용하며, 이미지에서 확인한 비교와 사용자 관찰을 Validation에 구분하여 기록한다.

---

## Contents

- [2.1 Production Skin Shader Concept](#21-production-skin-shader-concept)
- [2.2 Skin Material Implementation](#22-skin-material-implementation)
- [2.3 Skin Visual Validation](#23-skin-visual-validation)
- [2.4 Skin Technical Decisions](#24-skin-technical-decisions)
- [2.5 Limitations and Next Work](#25-limitations-and-next-work)

---

## 2.1 Production Skin Shader Concept

### Why Subsurface Profile

`M_PBR_Master`의 Default Lit 경로는 공통 Surface 입력을 검증하는 기준선이다. 얼굴에서는 이 구조에 더해 피부 내부의 Scattering이 Surface Lighting에 미치는 영향을 제어해야 한다. Base Color를 붉게 만들거나 Roughness만 바꾸는 것으로는 Scattering의 공간적 퍼짐과 부위별 기여를 독립적으로 조절하기 어렵다.

이번 UE 5.8.3 Deferred Shading 구현은 Engine의 `Subsurface Profile` 경로를 선택했다. Surface의 Base Color, Normal과 Roughness를 유지하면서 Profile로 Scattering의 거리와 RGB별 반응을 조절하고, Material의 `Opacity`로 부위별 SSS contribution을 제어한다. Profile은 별도 Asset이므로 공통 Skin 기준을 Material Graph와 구분하여 조절할 수 있다. 이 입력 계약은 Epic의 [Subsurface Profile Shading Model](https://dev.epicgames.com/documentation/en-us/unreal-engine/subsurface-profile-shading-model-in-unreal-engine)을 따른다.

### Surface Diffusion and Transmission

화면에서 보이는 붉은 영역을 모두 같은 현상으로 판단하지 않는다. 이번 작업의 중심은 얼굴 Surface의 Diffuse Lighting이 주변으로 퍼지는 Surface Diffusion이며, Thickness Texture는 그 기여의 공간적 차이를 조절하는 입력이다.

| Concept | Role | Current Validation Boundary |
|---|---|---|
| Surface Diffusion | Surface 내부의 Scattering으로 주변 Surface에 나타나는 완만한 Lighting 분포를 표현한다. Subsurface Profile은 Screen Space 경로를 사용한다. | Default Lit 대비 얼굴 Appearance와 Profile / Mask 조절을 비교했다. |
| Transmission | 반대편에서 들어온 빛이 얇은 부위를 통과하여 관찰되는 반응이다. Geometry, 두께와 Light 방향의 관계가 중요하다. | Ear / Backlight 등의 독립적인 Transmission 검증은 수행하지 않았다. |
| Thickness-driven SSS Mask | Bake된 Thickness Data를 SSS contribution 조절값으로 변환한다. | Thickness를 `Opacity`에 반영하는 Artist Control을 구현했다. 실제 두께를 측정하거나 물리적 Transmission을 계산한 결과는 아니다. |

현재 Profile에는 별도의 Transmission 관련 설정도 있다. 따라서 이번 Surface Diffusion 검증을 Profile 전체의 Transmission 지원 여부에 대한 결론으로 확장하지 않는다. Profile의 세부 속성은 [FSubsurfaceProfileStruct](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/FSubsurfaceProfileStruct)를 참조한다.

---

## 2.2 Skin Material Implementation

### Material and Asset Responsibilities

공통 PBR 구조를 복제하여 Skin 전용 변경을 분리했다. `M_PBR_Skin`은 `M_PBR_Master`의 Material Instance가 아니라 **복제한 Material**이다. 따라서 이후 `M_PBR_Master`를 수정해도 복제본에 자동 반영되지 않으며, 필요한 공통 변경은 별도로 확인해야 한다.

```text
M_PBR_Master
    └─ Duplicate → M_PBR_Skin
                      ├─ Shading Model: Subsurface Profile
                      ├─ Subsurface Profile Asset: SSP_Skin
                      ├─ Dielectric Skin Intent: Metallic = 0
                      ├─ SSS Contribution Control → Opacity
                      └─ Parent → MI_Character_Head_Skin → Character Head
```

| Asset / Setting | Implementation Record | Responsibility |
|---|---|---|
| `M_PBR_Master` | 기존 공통 PBR Master를 복제 원본으로 사용한다. | 공통 Surface Data Flow의 기준이다. |
| `M_PBR_Skin` | Shading Model을 `Subsurface Profile`로 변경한다. | Skin 전용 Profile 연결과 SSS Mask 계산을 가진다. |
| `Metallic` | Skin의 비금속 설계값을 `0`으로 둔다. | Default Lit의 ORM.B Metallic 제어를 Skin 조절값으로 사용하지 않는다. |
| `SSP_Skin` | `M_PBR_Skin`의 Subsurface Profile 설정에 연결한다. | Surface Albedo와 Scattering 거리 / RGB 반응을 관리한다. |
| `MI_Character_Head_Skin` | `M_PBR_Skin`을 Parent로 사용하고 Character Head에 적용한다. | Texture와 Skin 제어값을 대상에 맞게 조절한다. |

`Subsurface Profile`에서는 Metallic용 GBuffer 공간이 Profile Data에 사용되어 Metallic 입력이 일반 Default Lit과 같은 활성 제어로 제공되지 않는다. 여기서 `Metallic = 0`은 비금속 Skin이라는 설정 의도의 기록이며, Metallic을 조절하여 SSS를 바꾸는 기능을 뜻하지 않는다.

### Subsurface Profile Controls

Profile은 Scattering의 분포를, Material의 `Opacity`는 그 효과를 어느 부위에 얼마나 적용할지를 담당한다. 두 종류의 조절을 구분해야 전체적인 붉은 퍼짐을 Thickness Mask로만 보정하거나, 국소적인 Mask 문제를 Profile 거리로만 해결하는 일을 줄일 수 있다.

| Profile Parameter | Role | Adjustment Guidance |
|---|---|---|
| `Surface Albedo` | Skin Surface의 반사 특성을 Profile에 제공한다. | Material의 Base Color와 가능한 한 일치하도록 조정한다. SSS Strength나 단순한 추가 Tint로 사용하지 않는다. 현재 정확한 Asset 값은 별도 확인 대상이다. |
| `Mean Free Path Color` | R/G/B별 Light 이동 거리의 상대적인 차이를 지정한다. | 단순한 SSS Color Tint로 해석하지 않는다. 붉은 채널의 상대적인 이동 거리가 크면 붉은 퍼짐에 영향을 줄 수 있다. |
| `Mean Free Path Distance` | Mean Free Path Color에 공통 Distance Scale을 적용한다. | 화면에서 보이는 퍼짐을 비교하며 조정한다. 이번 `0.5`는 현재 Asset과 Scene의 임시 Lookdev 기준이다. |
| `World Unit Scale` | World / Unreal Unit과 Profile의 cm Scale 관계를 설정한다. | Mesh Scale과 함께 확인한다. 같은 MFP Distance라도 Scale 계약이 다르면 같은 결과를 보장하지 않는다. 현재 수치는 확인되지 않았다. |

이 항목들은 Profile의 `Burley Normalized` 설정 계열이다. Epic API의 [Profile Property Reference](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/FSubsurfaceProfileStruct)에 따라 실제 `Enable Burley` 상태도 함께 확인해야 한다. 현재 그 Checkbox와 Anti-Aliasing 설정은 기록에서 확정되지 않았으므로 확인 완료로 표시하지 않는다. MFP Distance를 실제 피부 두께나 보편적인 최종 피부 계수로 읽지 않는다.

### Skin SSS Strength

먼저 Scalar Parameter `Skin_SSS_Strength`를 Material의 `Opacity`에 연결해 전체 Skin SSS contribution을 조절했다. Thickness 경로를 추가한 뒤에는 이 Scalar가 최종 Mask의 전체 Scale을 담당한다.

```text
Initial Control:
Skin_SSS_Strength → Opacity

With Thickness Control:
Skin_SSS_Strength × Thickness Contribution → Opacity
```

여기서 `Opacity`는 Surface를 투명하게 만드는 Alpha가 아니다. `Subsurface Profile`에서 SSS contribution을 제어하는 입력이며, `0`은 Scattering 기여 없음, `1`은 전체 기여를 뜻한다. Hair Card의 실루엣을 자르는 `Opacity Mask`와도 역할이 다르다.

### Thickness Input Contract

이번 Substance Painter 원본은 **밝을수록 두꺼운 영역**을 뜻한다. 이 방향은 이번 입력 Texture의 사용자 기록이며, 모든 Thickness Bake의 공통 규칙으로 가정하지 않는다. 다른 Texture로 교체할 때는 Bake Convention을 먼저 확인한다.

Thickness는 Color가 아닌 수치 Mask로 읽는다. Texture의 `sRGB`는 Off로 사용하며, Texture 설정에 맞는 `Masks` 또는 `Linear Color` Sampler Type을 선택한다. Color Space 변환을 거친 값으로 Thickness를 조절하면 중간 회색의 의미가 바뀔 수 있으므로 Import 설정과 Sampler를 함께 맞춰야 한다. 일반적인 Mask 설정은 Epic의 [Using Texture Masks](https://dev.epicgames.com/documentation/unreal-engine/using-texture-masks-in-unreal-engine)를 따른다.

이 문서의 `T`는 Thickness Texture에서 읽은 단일 Scalar 값이다. 실제 Texture Asset 이름, 사용 Channel, Compression과 Sampler의 최종 선택은 Asset 화면에서 추가 확인해야 한다. 확인하지 않은 Channel을 임의로 R로 확정하지 않는다.

### Thickness Data Flow

입력값의 의미를 맞춘 뒤 범위와 Contrast를 조절하고, 마지막에 SSS contribution에 반영한다. 원본 / 반전 선택은 `Invert_ThicknessMask` Static Switch Parameter로 분리한다.

```text
Thickness Texture Scalar T
    ├─ False: T
    └─ True : OneMinus(T)
             ↓ Invert_ThicknessMask
Selected Thickness
    → Multiply(Thickness_Multiplier)
    → Add(Thickness_Bias)
    → Saturate
    → Adjusted Thickness
    → Lerp(A = 1, B = Adjusted Thickness, Alpha = Thickness_MaskInfluence)
    → Multiply(Skin_SSS_Strength)
    → Opacity
```

```text
SelectedThickness = Invert_ThicknessMask ? (1 - T) : T
AdjustedThickness = Saturate(SelectedThickness × Thickness_Multiplier + Thickness_Bias)
ThicknessContribution = Lerp(1, AdjustedThickness, Thickness_MaskInfluence)
FinalOpacity = Skin_SSS_Strength × Lerp(1, AdjustedThickness, Thickness_MaskInfluence)
```

`Invert_ThicknessMask = True`는 원본의 밝은 두꺼운 영역을 낮은 값으로, 어두운 얇은 영역을 높은 값으로 변환한다. 이 선택은 얇은 영역의 SSS contribution을 상대적으로 높이기 위한 현재 Lookdev 해석이다. `OneMinus`만으로 실제 물리적 두께나 Transmission이 만들어지는 것은 아니다.

`Thickness_Multiplier`는 선택한 Mask를 Scale하고, `Thickness_Bias`는 전체 값을 이동한다. 이후 `Saturate`가 adjusted thickness를 `0–1`로 제한한다. 순서는 **반전 선택 → Multiply → Bias → Saturate**다. Saturate를 앞당기거나 Bias 뒤의 Clamp를 생략한 다른 Graph로 기록하지 않는다.

`Thickness_MaskInfluence`는 `Lerp(1, adjusted thickness, influence)`의 Alpha다. `0`에서는 Thickness를 시각적으로 무시하고 전체 SSS Strength를 유지한다. `1`에서는 adjusted thickness를 전부 반영하며, `0.5`에서는 Uniform Contribution과 Mask 사이의 값을 사용한다. 이 Scalar를 `0`으로 두는 것은 Mask의 시각적 기여를 없애는 것이며, Texture Sample이 Compile 결과에서 제거된다는 뜻은 아니다.

### Artist Controls and Current Baseline

다음 값은 사용자가 선택한 **현재 Lookdev 임시 기준값**이다. Material Instance를 조절하거나 비교를 다시 시작할 때의 기준으로 사용하며, 저장된 Master Parameter Default와 Engine Profile Default를 직접 확인한 값으로 혼동하지 않는다.

| Parameter | Type | Current Lookdev Baseline | Artist-facing Role / Working Range |
|---|---|---|---|
| `Mean Free Path Distance` | Profile Scalar | `0.5` | 전체 Scattering Distance Scale이다. 현재 비교 범위는 `0.1 / 0.5 / 1.0`이다. |
| `Skin_SSS_Strength` | Scalar | `0.3` | 전체 SSS contribution의 Scale이다. 작업 범위는 `0–1`이다. |
| `Thickness_MaskInfluence` | Scalar | `0.5` | Uniform Contribution과 Thickness Mask의 혼합 비율이다. 작업 범위는 `0–1`이다. |
| `Thickness_Multiplier` | Scalar | `1.0` | 선택한 Mask의 Scale이다. `1.0`은 Multiply의 중립값이다. |
| `Thickness_Bias` | Scalar | `0.0` | Mask 전체의 Offset이다. `0.0`은 Add의 중립값이다. 최종 Mask 범위는 뒤의 Saturate가 제한한다. |
| `Invert_ThicknessMask` | Static Switch | `True` | True는 `OneMinus`, False는 원본을 사용한다. Bake Convention에 맞춰 선택한다. |
| `Mean Free Path Color` | Profile RGB | White `(1, 1, 1)` — Diagnostic | RGB별 거리 차이를 제거해 원인을 분리한 진단값이다. 최종 Skin Profile Color는 추후 조정한다. |

이 표의 Working Range는 Artist의 조절 기준이다. 실제 Material Instance Slider Min / Max 설정을 확인한 결과는 아니다. 사용자 구현 기록에 명시된 Clamp는 adjusted thickness의 `Saturate`이며, Strength와 Influence에 추가 Saturate가 구현되었다고 기록하지 않는다.

Strength와 Influence가 `0–1`일 때 Mask가 SSS contribution을 억제하는 범위는 다음과 같다.

```text
Skin_SSS_Strength × (1 - Thickness_MaskInfluence)
    ≤ FinalOpacity ≤ Skin_SSS_Strength

Current Baseline:
0.15 ≤ FinalOpacity ≤ 0.3
```

이는 수식에서 도출한 범위이며 Screenshot에서 측정한 Pixel 값이 아니다. Influence `0.5`는 Mask가 가장 어두운 곳에서도 전체 Strength의 절반을 남기므로, Influence `1`보다 부위 간 contribution 차이를 완화한다. Strength `0.3`이 화면 밝기나 체감 SSS의 정확한 30%를 뜻하지는 않는다.

Artist는 Influence를 `0`으로 두어 Profile과 전체 Strength를 먼저 판단하고, 원본 / 반전 방향을 확인한 뒤 Influence를 올려 부위별 차이를 조절할 수 있다. Multiplier `1.0`, Bias `0.0`에서 시작하면 원본의 값 분포를 유지한 채 방향과 Influence를 비교하기 쉽다. Profile의 거리, Color와 Mask 조절을 한 번에 바꾸지 않아야 각 변화의 원인을 읽을 수 있다.

---

## 2.3 Skin Visual Validation

### Evidence and Comparison Conditions

이번 기록은 사용자 제공 구현·관찰과 로컬 Figure 2-1–2-4 확인을 함께 사용한다. Figure는 실제 Character Head 결과이며, Chapter 01의 Sphere / Detail Normal 검증과 대상이 다르다. Engine을 다시 실행한 독립 재현 검증이나 GPU Time 측정은 수행하지 않았다.

| Item | Recorded State | Evidence Boundary |
|---|---|---|
| Engine / Rendering Path | UE `5.8.3` / Deferred Shading | 사용자 기록 기준이다. |
| Skin Assets | `M_PBR_Skin`, `SSP_Skin`, `MI_Character_Head_Skin` | 연결과 값은 사용자 구현 기록 기준이다. 저장된 Asset 재검사는 미수행이다. |
| Validation Target | Character Head | Figure 2-1–2-4에서 얼굴 적용 결과를 확인했다. |
| Lighting / Shadow | VSM 사용, Hair / Beard / Eyebrow가 불투명 Plane 상태 | 큰 Cast Shadow가 비교 결과에 함께 들어간다. |
| Reproduction Conditions | Map, Camera Transform, Light Intensity, Exposure, Resolution, AA, Profile 전체 설정 | 완전한 값 기록이 없어 동일 조건 재현은 후속 확인 대상이다. |
| Performance | Skin / SSS GPU Timing 미측정 | 기존 Master의 Shader Statistics를 Skin 성능 측정으로 전용하지 않는다. |

비교는 한 번에 하나의 변수만 바꾸는 것을 기준으로 해석한다. 다만 저장된 이미지 Label만으로 다른 모든 값이 동일했다는 것을 증명할 수 없으므로, 각 Figure에서 확인한 정보와 사용자 관찰을 구분한다.

### Default Lit and Subsurface Profile

Figure 2-1의 왼쪽 Label은 `Surface + SSS`, 오른쪽은 `Default Lit`이다. 왼쪽에서는 눈 주변과 코 주변의 붉은 반응이 더 두드러지고, 오른쪽과 얼굴 Lighting 분포가 달라진다. 비교는 Skin 전용 Scattering 경로가 Appearance에 영향을 주는지를 보여준다. 왼쪽의 붉은 반응 자체를 최종 Skin 품질의 정답으로 판단하지 않는다.

*Fig2_01 — 공개 사본에서 이미지 생략.*

**Figure 2-1. Default Lit and Subsurface Profile Comparison.** 왼쪽은 Surface + SSS, 오른쪽은 Default Lit이다. Skin Shading 경로에 따른 얼굴 반응의 차이를 비교한다. Hair / Beard / Eyebrow Plane은 아직 실루엣 Mask가 적용되지 않은 상태다.

### Mean Free Path Distance and Color Diagnosis

초기 Profile에서는 `Mean Free Path Distance = 2.6748`과 붉은 MFP Color를 사용했을 때 지나친 적색 번짐을 관찰했다. 초기 MFP Color의 정확한 RGB 수치는 기록되지 않았으므로 임의로 채우지 않는다. Distance와 RGB별 거리 비율이 함께 영향을 줄 수 있어 두 요소를 분리해서 확인했다.

Figure 2-2는 왼쪽 위 `Default Lit`, 오른쪽 위 `Distance 0.1`, 왼쪽 아래 `Distance 0.5`, 오른쪽 아래 `Distance 1.0`의 비교다. 아래 두 결과에서는 눈 주변과 코의 붉은 영역이 더 두드러진다. 이 비교는 거리 조절에 따른 퍼짐과 색 반응을 읽는 자료다. `2.6748` 초기값은 이 Figure의 별도 Panel에 포함되지 않는다.

*Fig2_02 — 공개 사본에서 이미지 생략.*

**Figure 2-2. Mean Free Path Distance Comparison.** Default Lit과 MFP Distance `0.1 / 0.5 / 1.0`을 비교한다. 같은 Profile의 Distance 변화가 얼굴 Appearance에 미치는 영향을 읽으며, 각 Capture의 나머지 Profile 값은 별도 기록 확인이 필요하다.

이후 MFP Color를 White `(1, 1, 1)`로 두어 RGB별 상대적인 거리 차이를 제거했을 때 과도한 적색 번짐이 개선되었다는 사용자 관찰이 있었다. 이 결과는 Profile의 채널별 거리 설정이 원인에 기여했음을 살피는 진단 근거다. Base Color와 Lighting의 색은 여전히 결과에 영향을 주므로 White를 모든 피부의 최종 Profile Color로 확정하지 않는다.

현재는 Distance `0.5`를 임시 기준으로 선택했다. MFP Color White는 진단 상태이며, 최종 Skin Color와 Scattering 반응은 Hair 완성 후 다시 조정한다. Figure 2-2의 모든 Panel이 White 진단 상태에서 촬영되었다고 단정하지 않는다.

### Thickness Invert Comparison

Figure 2-3은 왼쪽 `Invert ON`, 오른쪽 `Invert OFF`다. 같은 입력 Texture의 값 방향을 바꾸었을 때 눈 주변의 어두운 영역과 얼굴 반응이 달라진다. 이 차이를 통해 원본 Thickness의 의미와 SSS contribution Mask의 방향을 구분했다.

*Fig2_03 — 공개 사본에서 이미지 생략.*

**Figure 2-3. Thickness Invert ON and OFF.** 왼쪽은 `Invert_ThicknessMask = True`, 오른쪽은 False다. 원본 / 반전 선택이 얼굴 SSS contribution의 공간적 분포에 미치는 영향을 비교한다.

사용자는 원본의 밝은 두꺼운 영역을 그대로 강한 SSS 영역으로 사용하는 대신, 반전한 Mask를 현시점의 기준으로 선택했다. 이 선택은 현재 Bake Convention과 얼굴 Lookdev에 대한 판단이다. Figure의 눈 주변 경계를 반전 기능만의 Artifact로 확정하지 않으며, 불투명 Card의 Cast Shadow가 함께 보인다는 조건을 유지한다.

### Thickness Mask Influence Comparison

`Thickness_MaskInfluence = 0 / 0.5 / 1`은 Uniform Contribution에서 전체 Thickness 적용까지의 차이를 확인하는 비교다. `0`에서는 전체 SSS Strength가 유지되고, `0.5`에서는 Mask Contrast가 완화되며, `1`에서는 adjusted thickness의 공간적 차이를 전부 반영한다. 이는 구현 수식의 기대 동작이다.

사용자 관찰에서는 Influence를 `0.75–1`까지 강하게 적용할 때 부위별 경계가 두드러졌다. 현재는 `0.5`를 임시 기준으로 선택하여 Thickness 차이를 남기면서 contribution의 차이를 완화했다. 경계의 전체 원인은 Hair Cast Shadow와 함께 재평가해야 한다.

추가된 Figure 2-4는 왼쪽 `0`, 가운데 `0.5`, 오른쪽 `1`의 순서다. 오른쪽 결과에서는 눈 아래와 볼의 어두운 영역 경계가 더 뚜렷하게 드러나며, 가운데 결과에서는 그 차이가 완화되어 보인다. 이 비교는 현재 Influence 선택의 시각적 근거다. Figure에는 `0.75` Panel이 없으므로 해당 값의 관찰은 사용자 기록으로 구분한다.

*Fig2_04 — 공개 사본에서 이미지 생략.*

**Figure 2-4. Thickness Mask Influence Comparison.** 왼쪽부터 `Thickness_MaskInfluence = 0 / 0.5 / 1`이다. Influence `1`에서 눈 아래와 볼의 경계가 더 뚜렷하게 나타나고, `0.5`에서는 차이가 완화된다. Hair / Beard / Eyebrow의 불투명 Plane이 만드는 Cast Shadow가 함께 보이는 조건이다.

### Hair Card Shadow Diagnosis

얼굴에 드리우는 큰 Shadow는 아직 Hair / Beard / Eyebrow Card용 Masked Material이 없어 불투명 Plane이 그대로 가리는 상태에서 발생한다. 사용자는 특히 앞머리 Plane이 얼굴의 큰 Cast Shadow를 만든다고 확인했다. 이를 Skin SSS 오류로만 판단하면 Scattering을 줄이거나 Shadow Bias를 바꾸어 실제 원인과 무관한 보정을 하게 된다.

VSM 조건에서 `Source Angle`, `ResolutionLOD`, `Normal Bias`를 점검했고 `Contact Shadow = 0`도 확인했다. 사용자 기록에는 ResolutionLOD 값을 `0`에서 `-3`까지 바꾸어도 눈에 띄는 차이가 없었고, Normal Bias 변경도 큰 차이가 없었다는 관찰이 있다. Source Angle의 최종 값과 ResolutionLOD의 정확한 Console Variable 이름은 기록에서 확정되지 않아 임의로 적지 않는다.

이 점검은 모든 VSM 문제가 없다는 일반적인 결론이 아니다. 현재 큰 얼굴 Shadow의 원인이 미완성 Card의 불투명 실루엣이라는 점을 분리한 진단 기록이다. Hair / Beard / Eyebrow에 Opacity Texture를 사용하는 Masked Material을 적용한 뒤 같은 Skin 기준값에서 얼굴 Shadow와 SSS를 다시 비교해야 한다. Skin `Opacity`를 줄여 Card의 실루엣 문제를 해결하지 않는다.

### Validation Result

| Check | Observation / Decision | Current Status |
|---|---|---|
| Default Lit vs Subsurface Profile | 얼굴 Scattering 경로에 따른 Appearance 차이를 확인했다. | Figure 2-1 inspected / User Reported |
| MFP Distance | `0.1 / 0.5 / 1.0` 비교 후 `0.5`를 임시 기준으로 선택했다. | Figure 2-2 inspected / User Reported |
| MFP Color White | 과도한 적색 번짐이 개선되었다는 관찰을 기록했다. | Diagnostic / User Reported |
| Thickness Invert | 원본 / 반전을 비교하고 현재 True를 선택했다. | Figure 2-3 inspected / User Reported |
| Thickness Influence | `0 / 0.5 / 1` 비교에서 강한 Influence의 경계가 두드러지며, 현재 `0.5`를 선택했다. | Figure 2-4 inspected / User Reported |
| Large Face Shadow | 앞머리 등 불투명 Card Plane의 Cast Shadow로 원인을 분리했다. | User Confirmed / Hair Material pending |
| Skin Stage | 현재 결과를 기준으로 Skin 1차 구현을 완료했다. | First Implementation Complete |
| Final Lookdev / Production Ready / Performance | Hair 적용 후 재검증과 실제 GPU 측정이 필요하다. | Deferred |

---

## 2.4 Skin Technical Decisions

| Decision | Reason | Evidence / Limit |
|---|---|---|
| `M_PBR_Master`를 복제한 Skin 전용 Material | 공통 Surface 구조를 유지하면서 Shading Model과 SSS 제어를 분리한다. | 자동 상속이 아닌 복제 구조다. 공통 변경은 별도 동기화가 필요하다. |
| `Subsurface Profile`와 `SSP_Skin` 사용 | Deferred Skin의 Scattering 분포를 Profile로 관리한다. | 현재 얼굴 비교 범위의 선택이며 Transmission 검증과 구분한다. |
| 전체 Strength와 Thickness Influence 분리 | 전체 SSS 기여와 부위별 차이를 독립적으로 조절한다. | Influence `0`으로 Profile 기준선을 확인할 수 있다. |
| `Invert_ThicknessMask` Static Switch | Bake Convention에 따른 원본 / 반전 방향을 명시적으로 선택한다. | 현재 True가 선택되었다. Runtime 연속 조절 Scalar와 역할이 다르다. |
| Multiply → Bias → Saturate | Mask의 Scale과 Offset을 조절한 뒤 유효 범위를 유지한다. | 중립값은 `1.0 / 0.0`이다. |
| `Lerp(1, adjusted thickness, influence)` | Thickness를 사용하지 않을 때 전체 Strength를 유지하고 점진적으로 Mask를 반영한다. | Influence `0`에서도 Texture Sample 제거를 보장하지 않는다. |
| MFP Color White를 Diagnostic으로 사용 | RGB별 거리 차이를 제거해 적색 번짐의 원인을 분리한다. | 과학적으로 확정한 Skin 계수나 최종 Profile Color가 아니다. |
| 큰 Shadow의 원인을 Hair Card 상태와 연결 | Skin과 Shadow 조절로 불투명 Plane 문제를 잘못 보정하지 않는다. | Card의 Masked Material 적용 후 재검증한다. |
| Skin 1차 완료를 지금 기록 | 완료된 구현·관찰을 다음 기능 작업과 분리하여 보존한다. | 최종 Production Ready와 Performance 완료 상태는 후속이다. |

---

## 2.5 Limitations and Next Work

### Current Completion Boundary

현재 완료 범위는 Skin 전용 Material 구성, Profile 연결, 전체 SSS Strength, Thickness 원본 / 반전, Multiply / Bias / Saturate, Influence Lerp와 얼굴의 시각적 비교다. 사용자가 선택한 임시 기준을 유지하며 다음 Character Surface 작업으로 진행할 수 있다.

이 상태를 최종 Skin Lookdev, 전체 Character의 Production Ready 검증 또는 성능 검증 완료로 표시하지 않는다. Thickness Mask는 Artist Control이며 실제 두께와 광학 계수를 측정한 모델이 아니다. Screen Space 결과와 현재 조명에서의 비교만으로 모든 Camera 거리, Light 방향과 품질 설정에서의 안정성을 보장하지 않는다.

### Remaining Checks

2026-10-16의 [Chapter 03 — Production Hair Shader](Chapter03_ProductionHairShader.md)에 Scalp Hair의 1차 구현과 비교를 기록했다. 아래 Hair / Beard / Eyebrow 전체 적용 및 Skin 재검증은 별도 후속 작업이며, 기존 Skin 관찰을 소급하여 완료 처리하지 않는다.

1. **Hair Card Material and Shadow.** Hair / Beard / Eyebrow에 Opacity Texture를 `Opacity Mask`에 연결한 Masked Material을 적용한 뒤, 같은 Skin 기준값에서 큰 Cast Shadow와 SSS 경계를 다시 확인한다.
2. **Profile and Texture Settings.** `Enable Burley`, Surface Albedo, World Unit Scale, 최종 MFP Color, AA와 SSS Quality를 기록한다. Thickness Asset의 Channel, sRGB Off, Compression과 Sampler Type, 실제 Instance 값 / Master Default도 함께 확인한다.
3. **Reproducible Lookdev.** Map, Mesh Scale, Camera, Light, Exposure와 Resolution을 고정해 Profile / Strength / Invert / Influence를 한 번에 하나씩 비교한다. 최종 Profile Color와 부위별 경계는 Hair 완성 후 결정한다.
4. **Production Ready Validation.** 목표 거리와 Light 조건에서 Skin Detail, Seam, 시간적 안정성, Shadow와 Surface Diffusion의 관계를 확인한다. Ear / Backlight Transmission을 평가할 경우 별도 조건과 결과로 기록한다.
5. **Performance Profiling.** 실제 Character와 목표 화면 조건에서 Skin / SSS 관련 Pass와 GPU Frame Time을 milliseconds로 측정한다. Shader Statistics와 실제 GPU Timing을 구분하고, 측정 전에는 비용 수치를 채우지 않는다.

후속 Graph, Texture Setting, Hair 적용 전후 또는 최종 Lookdev Figure가 필요하면 Capture 주제만 예약한다. 이 문서에서는 그 Figure의 새 번호나 존재하지 않는 파일 링크를 임의로 확정하지 않는다.

POM은 Separate POM Research에서 관리한다. 이번 Skin / Subsurface Profile / Thickness-driven SSS 구현과 검증 범위에 포함하지 않는다.

---

[PBR Character Contents](README.md) · [Production Hair Shader](Chapter03_ProductionHairShader.md) · [Production PBR Master Material — Sections 1.1–1.9](Chapter01_ProductionPBRMasterMaterial.md) · Separate POM Research
