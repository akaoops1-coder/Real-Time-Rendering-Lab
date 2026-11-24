# RTR / ASF — Preintegrated SSS LUT Validation

> Date: 2026-11-05 KST
> Result: LUT generation + new Unreal Texture2D Import + fresh process verification + live UI observation complete
> Boundary: Material Graph application / Production lighting / Android device measurement pending

## 1. 실제 저장 위치

확인한 실제 프로젝트:

```text
local path withheld
```

요청서의 Desktop 경로는 문서 저장소였다. Chapter06의 프로젝트 identity와 실제 `.uproject`, Content 구조를 확인한 후 **실제 Unreal 프로젝트** 안에 요청한 `Texture`(단수형) 폴더를 만들었다. 기존 `Textures`(복수형)는 유지했다.

최종 파일:

```text
local path withheld
local path withheld
```

PNG: **16,527 bytes**, SHA256 `1abf0b4934dfeb6416436630491df20b365f8ef809254c66e72c68b207f54bcf`.

`.uasset`: **14,582 bytes**, SHA256 `31a55484e5e49f50bf7229c3ee819dd51a347abc244da75792a49659fe87c960` (finalized package).

다음 파일은 모두 아래 보고서 폴더에 저장했다.

```text
local path withheld
```

| File relative to report directory | 역할 |
|---|---|
| `generate_sss_lut.py` | 재현 가능한 수치 적분 및 자동 검증 |
| `import_sss_lut_unreal.py` | 신규 Import / source finalization / read-only verify |
| `SSS_LUT_Research.md` | 식·profile·단위·가정·source 불일치·참고문헌 |
| `SSS_LUT_Validation.md` | 이 결과 기록 |
| `UE_Material_Graph_Guide.md` | 사용자 연결 순서 및 실제 확인값 |
| `T_ASF_SkinSSS_Penner2011_R1to100mm_v1_RGB16.png` | RGB16 선형 reference, 201,018 bytes |
| `T_ASF_SkinSSS_Penner2011_R1to100mm_v1.npy` | float32 원본, 786,560 bytes |
| `SourceTextures\T_ASF_SkinSSS_Penner2011_R1to100mm_v1.png` | staging 원본; Content PNG와 byte-identical |
| `SSS_LUT_Diagnostic.png` | 실제 데이터로 그린 LUT / RGB response 비교 |
| `sss_lut_validation.json` | 18개 검증과 45개 독립 reference 표본 |
| `SSS_LUT_Manifest.json` | 생성 파라미터·파일 checksum |
| `UE_Import_Result.json`, `UE_Source_Finalization.json`, `UE_Persisted_Verification.json` | Unreal 단계별 인식·설정·경로 증거 |
| `Project_Before.json`, `Project_After_Audit.json` | 기존 파일 보호 audit |
| `Delivery_File_Inventory.json` | 최종 전체 경로·파일 크기·SHA256 목록 |

Manifest의 `texture_rgb8` 경로는 처음 생성한 staging 위치를 기록한다. 최종 Content 경로는 UE evidence와 Delivery inventory가 기록한다. staging과 Content PNG의 SHA256은 같다. RGB16 / NPY / 도표는 Auto Import에 걸리지 않도록 Content 밖에 둔다. PNG와 `.uasset`의 동거는 [Epic Auto Reimport](https://dev.epicgames.com/documentation/en-us/unreal-engine/reimporting-assets-automatically-in-unreal-engine)의 source 관리 방식에 따른다.

## 2. Unreal 인식과 실제 설정

**Content Browser에서 직접 확인한 에셋 경로:**

```text
/Game/ASF/PBR/Texture/T_ASF_SkinSSS_Penner2011_R1to100mm_v1
```

Object path:

```text
/Game/ASF/PBR/Texture/T_ASF_SkinSSS_Penner2011_R1to100mm_v1.T_ASF_SkinSSS_Penner2011_R1to100mm_v1
```

UE 5.8.3의 실제 Editor Python Import로 **Texture2D**를 만들고 저장했다. Python plugin은 해당 commandlet 실행에서만 활성화했으며 `.uproject`를 바꾸지 않았다. [Epic Python scripting](https://dev.epicgames.com/documentation/en-us/unreal-engine/scripting-the-unreal-editor-using-python)의 commandlet 경로를 사용했다.

1. Content 밖의 staging PNG를 읽고 동일 이름 기존 `.uasset` / registry asset / Content PNG가 없음을 확인한 뒤 신규 Import했다.
2. 아래 속성을 적용하고 신규 텍스처 하나만 저장했다.
3. canonical PNG를 Content로 exclusive copy하고, 실제 파일이 존재하는 상태에서 AssetImportData source filename / timestamp / MD5를 연결했다.
4. **새 Unreal 프로세스**에서 저장된 Texture2D, dimensions, 8개 속성, Content source filename/hash 및 Asset Registry 인식을 다시 확인했다. 이 과정은 read-only였다.
5. 열린 에디터의 Content Browser에서 `Texture` 폴더의 **1개 텍스처**를 직접 관찰하고 열었다. Texture Editor에서 LUT의 실제 패턴과 256×256 표시를 확인했다. 기존 Debug graph와 피부 mesh에는 적용하지 않았다.

| Setting | Persisted API verification | Live UI |
|---|---|---|
| Dimensions | 256×256 | Imported / Displayed 256×256 |
| sRGB | False | 체크 OFF |
| Compression | TC_VECTOR_DISPLACEMENTMAP | VectorDisplacementmap |
| Mip Gen | TMGS_NO_MIPMAPS | NoMipmaps / Number of Mips 1 |
| Address X / Y | Clamp / Clamp | Clamp / Clamp |
| Filter | Bilinear | 이번 UI 화면에서 별도 필터 줄은 확인하지 않음; API 재로드로 확인 |
| Never Stream | True | 체크 ON / Not Streamed |
| Virtual Texture Streaming | False | 일반 Texture 상태; API 재로드로 확인 |

Texture Editor의 Editor Platform은 Format **B8G8R8A8**, Resource Size **256 KB**로 표시했다. Android cook format이나 GPU 성능 검증값으로 해석하지 않는다. RGB16 reference는 Import하지 않았고 canonical RGB8만 사용했다. VectorDisplacementmap은 선형 RGB8 데이터 보존을 위한 비압축 기준 설정이다.

Source PNG 추가에 따른 live Auto Import 알림의 `What Changed?`를 확인했으며 대상은 이 신규 `Content/ASF/PBR/Texture/T_ASF_...png` 한 개였다. 이미 올바르게 Import·저장한 `.uasset`가 있으므로 **Don't Import**로 해당 중복 알림만 닫았다. 전역 auto-reimport 설정이나 Don't ask again은 바꾸지 않았다.

검증 스크립트의 최초 fresh-process run은 Asset Registry 함수 인자 타입 차이로 실패했다. 텍스처 재로드와 설정 확인 이후 registry 조회에서 발생한 오류였다. `get_assets_by_package_name`으로 수정한 뒤 새 프로세스에서 재검증하여 **0 errors / 0 warnings / exit 0**을 확인했다. 실패 JSON / 최초 로그와 성공한 `UE_Persisted_Verification_Retry.log`를 모두 보존했다. 이 수정은 텍스처나 기존 재질 변경이 아니다.

## 3. 수학 생성 모델과 가정

* Penner Appendix normalized half-ring, alpha ∈ [-π/2,π/2], clamped cosine.
* chord distance `2R abs(sin(alpha/2))`, 6개 RGB Gaussian, NVIDIA 원본 variance mm² 및 weights.
* Appendix 호환 variance multiplier **1.414**는 경험적 계수다. 물리 단위 변환이나 새로운 측정값으로 해석하지 않는다.
* 8192-step float64 midpoint sum / 채널별 denominator 정규화.
* `U=(NdotL+1)/2`, `V=log(100/R_mm)/log(100)`, 범위 **R=100→1 mm**. V=.5는 R=10 mm.
* endpoint grid이므로 UE sample UV에 `(UV*255+.5)/256`을 적용한다.
* 선형 RGB8/16 UNORM, gamma encoding 없음, 값 clipping 없음. profile 및 다른 source 식의 차이는 Research 문서에 기록했다.

## 4. 자동 검증 — 18 / 18 PASS

| Check / metric | Result |
|---|---:|
| Full-grid 8192 → 16384 steps max absolute error | 2.533034846×10⁻⁷ |
| Independent composite 64-node Gauss-Legendre, 45 (mu,R) pairs, max error | 2.016036656×10⁻⁶ |
| Cumulative midpoint vs direct midpoint | 6.550315845×10⁻¹⁵ |
| R=1000 mm validation only: max difference from Lambert | 0.000424161 |
| Raw linear range | 0 to 0.9999982486 |
| RGB8 quantization max absolute error | 0.001960720319, within 0.5/255 |
| RGB16 quantization max absolute error | 0.000007629481, within 0.5/65535 |
| Float32 storage max error | 2.980105263×10⁻⁸ |
| PNG dimensions / bit depth / RGB color type / CRC | PASS |
| PNG color transfer tags | IHDR / IDAT / IEND only; sRGB / gAMA / iCCP absent |

그 밖의 자동 검증은 finite 값, 채널별 weight 합 1, radius 양 끝과 방향, NdotL 응답의 단조성, 완전 뒷면 0, terminator의 R>G>B, 상수 irradiance 보존, texel center 대응 및 PNG 행 순서를 확인했다.

`NdotL=0, R=10mm`의 float64 reference RGB는 **[0.0423075197, 0.0098119869, 0.0063031773]**다. 이는 full response이며 Lambert에 Add하는 증분이 아니다. 각 수치는 계산 데이터이며 tonemap 후 화면 RGB가 아니다.

8-bit 양자화 오차는 적분 오차보다 크다. 압축을 피하더라도 8-bit의 최소 간격은 남는다. 고정밀 reference를 RGB16/NPY로 보관했으므로 EXR은 별도 추가하지 않았다. CPU 수학 계산과 source 값을 확인한 것이며, Material GPU readback이나 mobile cook 후 sample 오차는 이번에 측정하지 않았다.

## 5. 재생성

필요 환경은 Python 3.10+ / NumPy / Pillow다. 사용한 bundled runtime은 NumPy **2.3.5**, Pillow **13.0.0**이다. 기본 시스템 Python에는 NumPy가 없었으므로 다음 확인된 Python을 사용했다.

```powershell
$sssPython = 'local path withheld'
$sssReport = 'local path withheld'
& $sssPython "$sssReport\generate_sss_lut.py" --output-dir "$sssReport\Reproduced_Run01" --texture-dir "$sssReport\Reproduced_Run01\SourceTextures"
```

출력 폴더는 **새 경로**여야 한다. 동일명 source / 보고서 / `.uasset`가 존재하면 계산·쓰기 전에 중단한다. 기존 generator 재실행 거부도 확인했다. 바로 기존 Content에 재생성하면 기존 파일 충돌이므로, 먼저 별도 보고서 폴더에서 재현한 뒤 명시적으로 새 버전 이름을 결정한다. 사용한 runtime은 앱 업데이트로 경로가 달라질 수 있으며 일반 Python에 NumPy/Pillow를 준비해서 같은 스크립트를 실행해도 된다.

## 6. 사용자가 진행할 Material Graph / 미완료 범위

기존 Debug의 signed NdotL → ×.5 → +.5 → Append A, `Skin_Curvature_Test=.5` → Append B, Append → texel center 보정 → **새 LUT** UVs, RGB → Unlit Emissive 순서다. 상세한 노드 단위 절차와 Substrate 관련 주의점은 `UE_Material_Graph_Guide.md`에 있다. 현재 Graph의 `Skin_Curvature_Tex`는 일반 curvature 입력이므로 LUT 텍스처로 바꿔야 한다; 이 작업은 기존 Material 변경 금지 조건에 따라 직접 실행하지 않았다.

미완료 / 제약:

* 기존 Material / Mesh에 LUT를 적용하거나 저장하지 않았다. Debug 복제본의 컴파일·시각 비교도 다음 단계다.
* Marmoset Convex/Concave와 물리 radius의 calibration은 미수행이다. 일반 bake 값은 mm가 아니다.
* full 2D BSSRDF, 다른 principal curvature, concave/saddle, subject-specific tissue 및 ear transmission은 모델 범위 밖이다.
* 전체 LUT를 기존 lit 결과와 Add하면 이중 조명이다. 수동 Unlit Emissive는 외부 그림자를 자동 수신하지 않는다. renderer source 변경 없이 per-light shadow / attenuation과 일치하는 Production 통합은 추가 설계가 필요하다.
* Android packaging/cook과 실기기 GPU 성능은 검증하지 않았다. commandlet의 SDK 진단에 Android r27c INVALID가 표시됐지만 LUT Import에는 영향이 없었다. Android Vulkan High Preview는 실제 Android GPU 측정이 아니다.
* 출판사 PDF는 cached text로 Appendix를 교차 확인했으며 live PDF 다운로드는 0 bytes였다. 공식 SIGGRAPH PPTX와 NVIDIA 원본 table image의 직접 확인과 구분했다.

기존 파일 보호 결과는 `Project_After_Audit.json`에 별도 기록한다. 신규 PNG와 `.uasset` 두 개만 Content에 추가되었는지 검사하며, 기존 PBR 에셋·Config·`.uproject` SHA256과 Content 전체 파일 metadata를 비교한다. 작업 전부터 열려 있던 미저장 상태는 이 디스크 audit와 별개이며 이번 작업에서 Save All을 실행하지 않았다.
