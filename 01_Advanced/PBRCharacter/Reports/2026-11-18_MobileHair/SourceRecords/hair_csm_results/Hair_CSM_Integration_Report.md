# Mobile Hair CSM Visibility Integration Test

- Date: 2026-11-17
- Engine: Unreal Engine 5.8.3
- Project: `local path withheld`
- Level: `/Game/ASF/L_Female01_BrightSoft_Integration`
- Validation: Android Vulkan High Preview / Mobile Forward
- Scope: Editor Preview 검증. Android Cook·실기기·GPU Timing 검증은 수행하지 않았다.

---

## Result

Production Hair의 복제 Material에서 실제 Mobile CSM Visibility를 기존 Kajiya-Kay Custom Specular의 최종 출력에 곱하는 통합 테스트에 성공했다. 외부 Cube의 위치와 Cast Shadow에 따라 Custom Specular의 차폐가 달라졌으며, Hair Self Shadow도 별도 Visibility 출력으로 확인했다.

원본 Production Material과 원본 Hair Material Instance는 수정하지 않았다. 테스트 후 Hair의 원래 Material 할당과 Cast Shadow, 기존 Cube의 Transform, Camera를 복구하고 임시 Cube를 제거했다. Directional Light의 Dynamic Shadow Distance는 기존 수정값인 1,000cm를 유지했다.

---

## Assets

Folder: `/Game/ASF/Debug/MobileHairCSM/`

| Asset | Role |
| --- | --- |
| `M_Mobile_Hair_Production_CSM_Test` | Production Master를 복제한 통합 테스트 Material |
| `MI_Female01_Hair_CSM_OFF` | 기존 Hair Instance의 파라미터 값을 복제하고 Visibility를 OFF한 비교군 |
| `MI_Female01_Hair_CSM_ON` | 동일한 파라미터 값으로 Visibility를 ON한 비교군 |
| `M_Mobile_Hair_CSM_Visibility_View` | Masked / Two Sided를 유지한 Unlit Visibility 시각화 전용 Material |

Source Master: `/Game/ASF/PBR/Mobile/M_Mobile_Hair_Production`

Restored Instance: `/Game/ASF/Characters/Female01/Materials/MI_Female01_hair`

## Material Changes

기존 `Use_CustomSpecular` 출력 뒤에 Multiply와 `Use_CSM_Visibility` Static Switch Parameter를 추가했다.

| Switch | Emissive input |
| --- | --- |
| OFF | 기존 Custom Specular의 최종 출력 |
| ON | 기존 Custom Specular의 최종 출력 × 실제 CSM Visibility |

`Use_CSM_Visibility`의 Group은 `CSM Visibility Test`, Master 기본값은 ON이다. 기존 `Use_CustomSpecular`, Root/Tip Color, Depth 기반 Shading, LightFacing, Root Specular Attenuation, Specular Shape·Strength·Color는 유지했다. Base Color·Metallic·Specular·Roughness·Normal·Opacity Mask·World Position Offset의 입력 연결이 원본과 같음을 확인했다.

Visibility는 실제 `MobileDirectionalLight`의 CSM Texture, Cascade Distance, Screen-to-Shadow Matrix와 Transition Scale을 사용한다. 현재 Pixel의 Receiver Depth와 실제 Shadow Map Depth를 비교하며 NdotL이나 Hair Depth Texture의 감쇠로 대체하지 않는다.

Custom HLSL은 `SHADING_PATH_MOBILE && PIXELSHADER && IS_MOBILE_BASE_PASS`에서만 CSM 리소스를 조회한다. 나머지 경로는 Visibility=1로 통과시킨다. 이는 Desktop과 Debug Shader 경로에서 선언되지 않은 Mobile 리소스를 참조하지 않기 위한 조건이다. 해당 경로의 Compile 성공이 Mobile CSM 실행 성공을 뜻하지 않으므로, 별도로 Preview의 실제 차폐 반응을 확인했다.

## Capture Conditions

- 고정 Camera Location: `(-28, 28, 176)` cm
- Camera Rotation: Pitch `-10`, Yaw `-45`, Roll `0`
- 외부 Cube Scale: `(0.12, 0.08, 0.20)` — Engine Basic Cube 기준 약 12 × 8 × 20cm
- Cube A Location: `(-12, 120, 240)` cm
- Cube B Location: `(3, 120, 240)` cm
- Boundary 비교 Location: `(-11.75, 120, 240)` cm — A에서 X축으로 0.25cm 이동
- 기존 Level의 Cube는 Camera를 가리므로 테스트 중 잠시 이동시켰고, 테스트 종료 후 원래 Transform으로 복구했다.
- 각 ON/OFF 쌍은 Camera·광원·Cube 위치·기존 Material Parameter가 같다. 원본 전체 화면 PNG도 함께 보관했다.

---

## External Occluder Test

| Test | Observation | Verdict |
| --- | --- | --- |
| Cube A, Cast Shadow ON, Visibility OFF | Cube로 가려진 Hair 뒤쪽의 Custom Specular가 남음 | 기존 문제 재현 |
| 동일 조건, Visibility ON | 해당 영역의 Custom Specular가 억제됨 | 차폐 연동 성공 |
| Cube A → B 이동 | Hair를 가리던 영역에서 Highlight가 돌아옴 | Cube 이동에 반응 |
| Cube A 위치 유지, Cube Cast Shadow OFF | Visibility ON에서도 외부 Cube 차폐가 사라짐 | 실제 Shadow 생성 여부에 반응 |
| Cube B 또는 Cube Cast Shadow OFF에서 ON/OFF 비교 | 외부 차폐가 없는 영역은 유사하며, 미세한 차이는 Self Shadow 등 CSM 차폐 범위에서 발생 | 전체 Specular를 일괄 낮추는 연산과 구별 |

Visibility OFF and ON under Cube A

Cube movement and Cast Shadow controls

## Hair Self Shadow Test

외부 Cube의 Cast Shadow를 OFF한 뒤, Hair Cast Shadow를 ON/OFF하여 확인했다. Root·앞머리 안쪽·Hair Card가 겹치는 부분의 차폐가 Hair Cast Shadow OFF에서 줄어드는 것을 Visibility Debug에서 확인했다. 일부 남는 차폐는 Head 등 다른 Mesh의 영향을 포함할 수 있으므로 Hair 자체의 Shadow로 단정하지 않는다.

최종 Hair 외형의 ON/OFF 차이는 비교적 작았다. 기존 Root 감쇠와 LightFacing, 기존 조명 Shadow가 함께 작동하므로, Visibility Debug에서 보이는 모든 차폐가 동일한 크기의 Specular 변화로 나타나지는 않는다. 이 테스트는 Hair 전체의 미세한 Card Shadow 품질이 충분하다는 판정을 포함하지 않는다.

Visibility Debug는 표시가 과도하게 밝아지는 것을 피하기 위해 Emissive에 `Visibility × 0.01`을 출력한다. 이 배율은 시각화 전용이며 통합 Material에는 적용하지 않았다. 회색이 비차폐, 검정이 차폐를 나타낸다.

Self shadow visibility with Hair Cast Shadow ON and OFF

---

## Single-Sample Quality

| Item | Result |
| --- | --- |
| Filtering | Shadow Texture를 1회 조회한다. 엔진의 다중 Sample PCF와 동일하지 않다. |
| Boundary | 경계가 날카롭고 부분적으로 계단 및 불연속 형태가 보인다. Hair Card의 실루엣·Opacity Mask도 영향을 주므로 모든 거친 경계를 CSM만의 문제로 분류하지 않는다. |
| Small movement | Cube를 0.25cm 이동한 비교에서 차폐 경계와 작은 가닥 부근의 상태가 변했다. |
| Flicker | 정지 캡처와 미세 이동 비교만으로 지속적인 시간적 깜빡임 발생 여부를 확정하지 않았다. 6개 정지 캡처도 완전히 동일한 파일은 아니었으므로, 단일 Sample 때문에 생긴 깜빡임과 다른 Temporal 변동을 분리했다고 주장하지 않는다. |
| Remaining checks | 연속 Camera/Cube 이동 영상, Cascade 전환과 거리 변화, Android 실기기에서의 Shimmering 및 GPU 비용 검증이 남아 있다. |

Single sample boundary after a 0.25cm Cube movement

## Shader Statistics

아래는 `MaterialEditingLibrary.get_statistics`의 동일한 Desktop RHI 경로(`GMaxRHIShaderPlatform`)에서 조회한 값이다. **Android Vulkan Mobile Shader 통계가 아니다.**

| Variant | Pixel instructions | Vertex instructions | Samplers | Estimated VS/PS Texture Samples |
| --- | ---: | ---: | ---: | --- |
| Original Instance | 339 | 153 | 4 | 3 / 3 |
| CSM OFF Instance | 339 | 153 | 4 | 3 / 3 |
| CSM ON Instance | 339 | 153 | 4 | 3 / 3 |

Desktop 경로에서는 Mobile CSM 코드가 제외되므로 수치가 같다. 이 결과로 Mobile 비용이 증가하지 않았다고 판단하면 안 된다. 또한 Custom HLSL의 직접 Texture 조회가 Material Graph의 Estimated Texture Samples에 그대로 반영된다고 가정하지 않는다. Mobile 경로에는 CSM Texture 조회 1회와 Cascade 선택·좌표 변환·Depth 비교가 추가되지만, 정확한 Instruction·Sampler 증가량과 GPU Timing은 이번 테스트에서 확보하지 못했다.

---

## Restoration and Integrity

- Hair Slot 0을 `MI_Female01_hair`로 복구했다.
- Hair Cast Shadow를 원래 값인 ON으로 복구했다.
- 기존 Cube Transform과 Camera를 복구했다.
- 임시 Cube를 제거했으며 Level Actor 수는 원래 11개로 돌아왔다.
- Directional Light의 Dynamic Shadow Distance 1,000cm를 유지했다.
- 원본 Production Master·Instance와 설치된 Engine의 Shader 파일을 포함한 1,148개 파일을 SHA-256으로 비교했으며 변경된 파일은 0개였다.
- 테스트 복제 에셋을 저장하고 복구된 Level을 저장했다.
- 이 결과는 통합 테스트의 성공을 뜻하며, 원본 Production Material에 최종 채택했다는 뜻은 아니다.

## Evidence Files

- `01_OFF_CubeA.png`, `02_ON_CubeA.png`: 주 비교
- `03_ON_CubeB.png`, `04_OFF_CubeB.png`: Cube 이동 비교
- `05_ON_CastShadowOFF.png`, `06_OFF_CastShadowOFF.png`: Cube Cast Shadow OFF 비교
- `07_ON_HairCastShadowOFF.png`: 최종 외형에서 Hair Cast Shadow OFF 확인
- `08_Visibility_HairCastON.png`, `09_Visibility_HairCastOFF.png`: Self Shadow 시각화
- `10_Visibility_CubeA.png`, `11_Visibility_CubeA_Move0p25cm.png`: 단일 Sample 경계 비교
- `Mobile_CSM_Visibility.hlsl`: 통합 Material의 Custom HLSL
- `verification.json`: 에셋 경로, 복구 확인, 파일 무변경 확인, 통계

Comparison PNG는 동일한 사각형 영역을 Crop하여 나란히 배치한 이미지다. 밝기·색상·Shadow 표현은 보정하지 않았다.
