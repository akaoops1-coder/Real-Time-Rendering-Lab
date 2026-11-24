# Current View Hair Cast Shadow Comparison

- Date: 2026-11-17
- Engine: Unreal Engine 5.8.3
- Project: `RTR_Advanced_Mobile`
- Level: `/Game/ASF/L_Female01_BrightSoft_Integration`
- Preview: Android Vulkan High / Mobile Forward

## Assigned Material

| Item | Confirmed state |
| --- | --- |
| Hair Component | Female01 / hair / Material Slot 0 |
| Material Instance | `/Game/ASF/Characters/Female01/Materials/MI_Female01_hair` |
| Parent | `/Game/ASF/PBR/Mobile/M_Mobile_Hair_Production` |
| Use_CustomSpecular | ON |
| Use_CSM_Visibility | 현재 할당된 원본 Material에 해당 Parameter가 없음. ON/OFF 값이 있는 상태가 아님. |
| Initial Hair Cast Shadow | ON |
| External Cube | 기존 Actor가 남아 있지만 Editor에서 임시 숨김 상태. 이번 테스트에서 변경하지 않음. |

이전 CSM 테스트 후 원래 Material 할당으로 복구된 상태가 유지되고 있었다. 이번 비교에서는 CSM 테스트 복제본을 할당하지 않았다. 따라서 이 결과는 현재 원본 Material의 Hair Cast Shadow 영향 비교이며, Custom Specular에 CSM Visibility를 곱한 ON/OFF 비교가 아니다.

## Fixed Conditions

- Camera Location: `(-36.075329, 12.753424, 168.115568)` cm
- Camera Rotation: Pitch `-0.800001`, Yaw `-32.764472`, Roll `0`
- Directional Light Intensity: `0.5`
- Dynamic Shadow Distance: `1000` cm
- Cascades: `4`
- Shadow Bias / Slope Bias: `0.5 / 0.5`
- Shadow Sharpen: `0`
- Specular Strength: `0.05`
- Specular Shape: `128`
- DepthShade Strength: `0.5`
- Roughness: `0.7`
- 나머지 Scalar·Vector·Static Switch Parameter는 `initial_state.json`에 기록했다.

Camera·Light Transform 및 조회한 Light 설정·Material 할당과 모든 노출 Parameter가 ON/OFF 사이에 동일함을 확인했다. 렌더링 품질 설정, Material Graph, Texture, Light 값은 변경하지 않았다. 변경한 장면 변수는 Hair Component의 Cast Shadow뿐이다.

## Images

원본 캡처는 양쪽 모두 2560 × 1440이다. Camera를 이동하거나 Zoom하지 않고 동일 Pixel 영역을 Crop하여 비교했다. 비교 이미지의 밝기·색상·Shadow 표현은 보정하지 않았다.

Forehead and temple

Hair interior

## Observations

- 이마·관자놀이: Cast Shadow ON에서 Hair가 만든 그림자가 명확히 보이며, OFF에서 해당 부분이 밝아진다. 차폐물이 Editor에서 숨겨진 현재 장면에서도 Hair → Head Shadow가 작동한다.
- 앞머리 안쪽과 얼굴 옆 Hair: Cast Shadow OFF에서 일부 어두운 영역이 줄어든다. Hair 자체의 Shadow가 외형에 영향을 준다는 근거다.
- Hair 내부의 큰 검은 띠: OFF에서도 남는 영역이 있다. 해당 영역 전체를 Cast Shadow만의 문제로 판단할 수 없다. 이번 테스트에서는 다른 계산을 변경하지 않았으므로 잔존 원인의 분리 검증은 하지 않았다.
- Custom Specular: 현재 원본 Material에는 CSM Visibility가 연결되지 않았다. ON/OFF 비교만으로 Custom Specular 차폐 품질을 검증했다고 해석하면 안 된다.

## Restored State

- Hair Cast Shadow를 원래 값인 ON으로 복구했다.
- Material Instance와 Camera·Light·Parameter는 그대로 유지했다.
- 기존 Cube의 숨김 상태를 유지했다.
- Material 또는 Level의 일괄 저장을 수행하지 않았다.
- 품질 설정은 변경하지 않았다.

원본 캡처: `01_HairCastShadow_ON.png`, `02_HairCastShadow_OFF.png`

검증 기록: `initial_state.json`, `verification.json`
