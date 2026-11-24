# ASF Preintegrated SSS LUT — Unreal Material Graph Guide

> Updated: 2026-11-05 KST / UE 5.8.3 / RTR_Advanced_Mobile
> LUT Import complete. Material connection is a user follow-up; existing Material / Mesh untouched.

## 확인한 에셋

Content Browser: `/Game/ASF/PBR/Texture/T_ASF_SkinSSS_Penner2011_R1to100mm_v1`

실제 기존 Debug Material: `/Game/ASF/PBR/Mobile/M_Mobile_Skin_lightDebug` (`light` 소문자). 현재 화면에서는 `NdotL × .5 + .5 → Append(U,.5) → Skin_Curvature_Tex → Emissive`가 보였다. `Skin_Curvature_Tex`의 현재 일반 Curvature texture는 새 SSS LUT가 아니다. 이번 작업은 이 노드를 교체하거나 Graph를 저장하지 않았다. 화면에 원래 있던 4개 미저장 항목도 저장하지 않았다.

## 연결 순서

1. 기존 파일 보존을 위해 Debug Material을 별도 새 이름으로 복제한 후 실험한다. 기존 Graph의 signed NdotL 계산을 사용한다. N과 L은 같은 World 공간의 unit vector이고, L은 표면에서 광원으로 향하는 방향이어야 한다. Dot 이전/직후에 음수 부분을 Saturate하면 U의 왼쪽 절반을 잃는다.
2. signed `NdotL` → Multiply **0.5** → Add **0.5** → Saturate를 **Append의 A**에 연결한다. 이미 있는 Multiply/Add가 이 역할이면 중복해서 추가하지 않는다.
3. Scalar Parameter `Skin_Curvature_Test`, 기본값 **0.5** → **Append B**. 초기에는 Marmoset Curvature texture를 연결하지 않는다. 이번 LUT에서 V=.5는 radius **10 mm**다.
4. Append float2 → Multiply **0.99609375** → Add **0.001953125**. 두 scalar 연산이 U/V 모두에 적용된다. 이것이 endpoint grid를 정확한 texel center로 맞추는 보정이다.
5. `TextureSampleParameter2D`를 추가한다. Parameter Name **Skin_SSS_LUT**, Texture는 위 `T_ASF_SkinSSS_Penner2011_R1to100mm_v1`, Sampler Type **Linear Color**, Sampler Source **From texture asset**. Shared sampler가 asset의 Bilinear/Clamp를 덮어쓰지 않도록 한다. Apply View MipBias는 디버그에서 OFF로 두어도 된다; LUT는 mip이 1개다.
6. 4번의 출력 → Texture Sample의 **UVs**. Texture Sample의 **RGB** → **Emissive Color**. 이전 `Skin_Curvature_Tex` RGB의 Emissive 연결은 복제본에서만 교체한다. 일반 Curvature를 이 LUT 대신 sample하면 SSS 적분을 보는 것이 아니다.
7. 디버그 복제본은 **Surface / Opaque / Unlit** 출력으로 평가한다. 현재 프로젝트는 Substrate가 켜져 있으므로 UI가 legacy Shading Model을 숨기는 경우, 설치 버전이 제공하는 **Substrate Unlit BSDF**에서 Emissive 입력을 연결하고 Front Material에 출력하는 구성을 사용한다. 기존 프로젝트의 Substrate 설정을 끄지 않는다. 현재 Debug의 Emissive 출력 핀을 이용할 수 있으면 기존 방식대로 연결한다. 이 추가 Graph는 이번 작업에서 컴파일·저장하지 않았다.
8. Apply / Save는 사용자 테스트 복제본에만 수행한다. 초기 평가는 LUT RGB만 출력한다. BaseColor, Specular 및 기존 skin shader의 결과를 더하지 않는다. 고정 exposure와 동일 tonemap 조건에서 방향만 회전시켜 terminator를 확인한다. 표시 RGB는 tonemap 뒤의 화면 값이므로 수치 검증에는 source/JSON 값을 사용한다.

```text
signed NdotL → ×0.5 → +0.5 → Saturate ── A ┐
                                           Append → ×0.99609375 → +0.001953125
Skin_Curvature_Test = 0.5 ────────────── B ┘                    │
                                                               ▼ UVs
                               Skin_SSS_LUT (Linear Color, From texture asset)
                                                               │ RGB
                                                               ▼
                                                        Unlit Emissive
```

## 비교할 값

| Skin_Curvature_Test | Radius | 확인 목적 |
|---:|---:|---|
| 0.0 | 100 mm | 거의 Lambert인 큰 표면 |
| 0.5 | 10 mm | 초기 얼굴 규모 디버그 |
| 1.0 | 1 mm | 강한 곡률에서 RGB terminator 확장 |

부호가 정확하면 U=0은 완전히 0이다. U=1 응답도 반경에 따라 달라진다. R=10 mm에서는 약 **(0.99001444, 0.99951740, 0.99982475)**, R=1 mm에서는 **(0.83439229, 0.95646916, 0.98329103)**다. 정면을 모든 V에서 흰색 1로 강제하지 않는다. R=10 mm, NdotL=0의 적분 reference는 RGB **(0.04230752, 0.00981199, 0.00630318)**다. 8-bit/256²/bilinear 샘플은 양자화와 grid 보간 때문에 이 값과 조금 다를 수 있다. 위 값은 화면에서 color picker로 읽은 최종 display 값이 아니다.

## 적용 확인된 Texture 설정

* sRGB: OFF
* Compression: VectorDisplacementmap (RGBA8), 선형 비압축 기준
* Mip Gen Settings: NoMipmaps, Number of Mips=1
* X / Y Tiling: Clamp / Clamp
* Filter: Bilinear
* Never Stream: ON / Virtual Texture Streaming: OFF

새 Unreal 프로세스에서 위 8개 속성을 다시 읽었다. Content Browser에서 Texture 1개와 Texture Editor의 실제 LUT 표시도 확인했다. Texture Editor는 Editor Platform에서 256² / B8G8R8A8 / Resource Size 256 KB를 표시했다. 이것은 Android cook 크기나 실기기 성능 측정값이 아니다.

## Source 관리 / 재생성

동일 폴더의 `.png`는 원본, `.uasset`은 엔진 Texture2D다. 이미 에셋이 있으므로 PNG를 다른 이름으로 다시 Import하여 중복 생성하지 않는다. 새 값 실험은 `v2`처럼 명확한 새 basename을 사용하고, 기존 LUT의 교체·Reimport는 명시적인 버전 변경으로 수행한다. Generator는 기존 이름이 있으면 중단한다.

Marmoset bake는 먼저 알려진 mm sphere로 보정한 뒤 `R_mm`로 변환한다. 그다음 `V=saturate(log(100/R_mm)/log(100))`를 Append B에 연결한다. 일반 Convex/Concave gray값을 곧바로 V나 mm로 동일시하지 않는다. convex ring 가정에 맞지 않는 concave / saddle 영역을 별도 처리한다.

Production에서는 lit diffuse에 LUT를 Add하지 않는다. Unlit은 외부 차폐 그림자를 자동 받지 않으며, 같은 광원의 visibility 없는 emissive correction은 shadow leak을 만든다. renderer source 변경 없이 범용 Mobile Forward 조명을 완전 교체하는 것은 이번 LUT의 완료 범위 밖이다. 세부 전략은 `SSS_LUT_Research.md` §5를 따른다.
