# RTR Advanced — 뒤통수 중앙 Shadow / Highlight 조사

2026-10-28 KST · Unreal Engine 5.8.3 · **Final Status: Unresolved**

## 1. Problem Description

Female01의 뒤통수 상단 중앙에서 밝은 Fiber 반사가 불규칙한 어두운 띠와 얼룩으로 끊긴다. 실행 중이던 `RTR_Advanced`의 `/Game/_HairRCI_20261026/TestScene`에서 원본 `M_Hair_Master`와 `MI_Female01_hair`를 직접 검사했다. 새로운 프로젝트·Master·Instance·진단용 Asset 복제본은 만들지 않았다.

2026-10-27 Backlit 작업의 `adopted_fix.json`, `final_readback.json`, `verification.json`, 원본 캡처 및 백업을 먼저 확인했다. 설치된 `SubstrateEvaluation.ush`와 Master의 SHA256은 이전 완료 기록과 같았다. Instance는 작업 시작 전부터 이전 기록과 파일 해시가 달랐지만, 실제 사용 중인 15개 Scalar 값은 이전 완료값과 같았으며 `Hair_Backlit = 0.1`이었다. 이번 조사의 원복 기준은 **이번 작업 시작 시의 실제 원본**이다.

| 기준 항목 | 기록값 |
|---|---|
| Engine | `5.8.3-58210709+++UE5+Release-5.8` |
| 고정 Viewport | `FourPanes2x2.Viewport 2.Viewport1` |
| Camera / FOV | 위치 `(33.859891, -0.294924, 165.212573)`, 회전 `(pitch 2.6, yaw -179.164468, roll 0)`, FOV `60` |
| Directional Light | 회전 `(-33, -43, 112.360672)`, 강도 `1`, Source Angle `1`, RT Shadow Enabled, Samples `8`, Transmission OFF |
| Hair | Masked / Two Sided / Hair, Nanite OFF, 원본 Instance 사용 |
| 주요 Material 값 | Backlit `.1`, Scatter `.1`, Specular `.5`, Roughness `.35`, PDO `.1`, Alpha Cutoff `.2`, HairShadowDensity `1.5` |
| Shadow / Rendering | Hair·Head Cast Shadow ON, VSM 전역 ON, RT NormalBias `.1`, RT Materials / TwoSidedGeometry ON |
| 노출 / AA | 기존 Auto Exposure 유지, MethodOverride `-1`, ExposureOffset `0`, Screen Percentage `100`, AA Method `4` |

전체 설정은 Baseline 상태와 추가 상태에 보관했다. 전역 `r.RayTracing.Shadows=0`이어도 해당 광원의 `Cast Ray Traced Shadows=Enabled`는 개별 설정이다. 이 속성의 의미는 [Epic 공식 문서](https://dev.epicgames.com/documentation/en-us/unreal-engine/ray-tracing-and-path-tracer-features-properties-in-unreal-engine)를 참고했다.

## 2. Root Cause Analysis

**확인된 범위는 Hair 자체의 Shadow에 연동되는 중앙 패턴이라는 점이다. 정확한 결함 위치는 미확정이다.**

- Hair Cast Shadow OFF에서 중앙 패턴이 사라지고 전체 모발이 크게 밝아졌다. 동시에 Head가 만드는 큰 어두운 경계가 드러났다. 자기 그림자를 제거한 결과를 수정 성공으로 채택하지 않았다.
- Head Cast Shadow OFF에서는 중앙 패턴이 남았다. 이전 Work의 큰 Dark Crescent와 이번 중앙 패턴은 동일한 Head Shadow 하나로 설명되지 않는다.
- PDO `.1 → 0`, Specular `.5 → 0`에서도 패턴이 남았다. Specular 감소는 섬유 반사를 약화시킬 뿐 해결이 아니었다.
- RT Samples `8 → 64`, Denoiser OFF에서도 큰 패턴이 유지됐다. 시험 범위에서는 샘플 부족이나 Denoiser가 단독 원인이라는 근거를 얻지 못했다.
- VSM으로 바꾸면 더 강한 어두운 면과 하이라이트 끊김이 나타났다. RT에서만 생기는 현상으로 한정할 수 없다.
- 큰 RT Bias는 그림자와 밝은 면의 위치를 바꾸었지만 다른 부분에 부자연스러운 경계를 만들었다. Bias 민감성은 확인했으나 올바른 보정값을 입증하지 못했다.

원본 Graph에는 카메라용 / Shadow용 Opacity를 나누는 `MaterialExpressionShadowReplace_0`가 있고, Shadow 입력은 기존 `MF_Hair_Opacity` 호출과 `HairShadowDensity`에 연결되어 있다. 구조를 변경하지 않았다. 설치 소스 `RayTracingOcclusionRGS.usf:368–387, 432–439, 479–509`에는 Hair의 광원 방향 Bias와 가까운 교차 회피 처리가 있다. 이는 진단 항목을 정한 근거이며, 해당 코드가 이번 패턴의 버그라는 증명은 아니다.

**추정:** 겹친 Masked Hair Card의 차폐 구조와 Hair BSDF 반응이 패턴의 주요 조건일 가능성이 높다. 실제 카드의 정상적인 투영 그림자, 카드 교차 / 겹침, Bias 근사, Shadow Mask 및 BSDF 반응의 상대 기여는 픽셀·기하 수준에서 분리하지 못했다. Tangent / Direction 데이터의 모든 영향을 배제한 것도 아니다. 엔진 버그로 단정하지 않는다.

## 3. Test Summary

동일 Camera에서 각 항목을 기준값으로 복구한 후 한 변수를 바꿨다. 변경 후 약 10초 대기하고 `1120 × 944` 원본 이미지를 저장했다. 기준선 반복 4장과 최종 재시작 확인을 포함해 총 18장을 확보했다. 자세한 조건은 Test events에 있다.

| Capture | 변경값 | 관찰 / 판정 |
|---|---|---|
| 000 / 005 / 015 / 024 | 기준선 및 반복 | 중앙의 고정 패턴 재현 |
| 001 | Hair Cast Shadow ON → OFF | 패턴 제거되지만 과도한 밝기·차폐 손실. 미채택 |
| 002 | Head Cast Shadow ON → OFF | 중앙 패턴 잔존. Head 단독 원인 아님 |
| 003 | Directional Light Cast Shadows ON → OFF | 중앙 띠 변화, 전체 반응·밝기 변화 큼. 미채택 |
| 004 | PDO Strength `.1 → 0` | 해결되지 않음 |
| 010 | RT NormalBias `.1 → .01` | 명확한 개선 없음 |
| 011 | RT NormalBias `.1 → 1` | 중앙 일부 변화, 다른 곳의 밝은 경계와 차폐 손실. 미채택 |
| 012 | Light RT Samples `8 → 64` | 큰 패턴 유지 |
| 013 | Light RT Enabled → Disabled, VSM 사용 | 어두운 면·끊김 악화. 미채택 |
| 014 | Hair Specular `.5 → 0` | 반사 약화 후에도 패턴 잔존. 미채택 |
| 020 / 021 | RT AvoidSelfIntersectionTraceDistance `1 → 0 / .1` | 명확한 개선 없음 |
| 022 | Shadow Denoiser `2 → 0` | 큰 패턴 유지 |
| 023 | HairShadowDensity `1.5 → 2` | 해결되지 않음 |
| 030 | 원복 후 에디터 재시작 | 기존 패턴 및 원본 상태 재확인 |

원인 분리 비교

동일 좌표의 원본 Crop이다. 밝기·색상 보정이나 패턴 제거 처리는 하지 않았다.

## 4. Applied Fix

**최종 적용한 수정 없음. 모든 실험 변경을 원복했다.**

`M_Hair_Master`, `MI_Female01_hair`, Material Functions, Texture, Mesh, Level 및 Engine Shader를 최종 수정·저장하지 않았다. 셰이더 변경 후보나 새 노드도 추가하지 않았다. 기존 Backlit 전달 수정(`SubstrateEvaluation.ush:1171,1174`)과 `Hair_Backlit = 0.1`을 유지했다. Roughness는 시험 중에도 바꾸지 않았다.

원복값 검사 후 미저장 상태를 정리하려고 Python `ReloadPackages`를 실행하는 과정에서 `World Memory Leaks` 오류로 에디터가 종료됐다. 이는 이번 작업의 재로드 절차 실패이며 Hair 렌더링 원인의 근거로 사용하지 않는다. 같은 프로젝트를 다시 열고 자동 저장 복구를 건너뛴 뒤, 디스크의 원본 TestScene을 로드해 재검증했다. 오류 보고는 외부로 전송하지 않았다. 오류 기록을 보관했다.

재시작 후 Scalar, 광원, Shadow, CVars, Camera / FOV, Game View가 기준선과 일치함을 확인했다. Camera 재설정의 yaw 차이는 약 `0.000006°`로 부동소수점 반올림 범위다. Master와 Instance의 T3D 내보내기도 시작 상태와 바이트 단위로 같다. 세 대상 디스크 파일의 SHA256은 시작 / 종료가 같고, 미저장 Content / Map Package는 없다. 진단용 Tick Callback도 해제했다. 기존 백업은 수정하지 않았다.

근거: 복구 검증, 파일 및 결과 검증.

## 5. Before / After

여기서 **After는 수정 성공 이미지가 아니라 원복·재시작 후 확인 이미지**다. 동일한 카메라·해상도·머티리얼·조명을 사용했으며 중앙 패턴이 남아 있다. 하늘의 구름은 시간에 따라 움직여 배경 픽셀은 같지 않다.

Before 및 원복 후 After

Before 원본 · After 원본 · Figure 구성 기록

채택하지 않은 큰 Bias

Bias `1`은 전체 차폐 형태와 다른 위치의 경계를 바꾸므로 최종 해결로 판단하지 않았다.

## 6. Remaining Limitations

중앙 패턴은 해결되지 않았다. Hair Card의 실제 겹침·교차와 Shadow 수신 지점을 대응시키는 기하 분석, Shadow Visibility의 직접 관찰, BSDF 반응과 차폐의 분리가 추가로 필요하다. 기존 Direction / Normal 구조나 Backlit Fix를 임의로 바꿀 근거는 얻지 못했다.

수용 가능한 후보가 없어 반대쪽 조명·다른 Camera Angle의 최종 개선 검증 단계로 진행하지 않았다. 이전 Work의 Direction / Backlit / Transmission 광범위 실험도 반복하지 않았다. Motion, 거리, 다른 플랫폼, 성능은 이번 조사의 검증 범위에 포함하지 않는다. 기존 Auto Exposure와 움직이는 하늘을 유지했으므로 정밀한 픽셀 밝기 차이를 개선 수치로 제시하지 않는다.

## 7. Final Status

**Unresolved** — 원인 범위를 Hair 자기 그림자에 연동된 패턴으로 좁혔으나, Fiber Reflection·Volume·기존 Backlit 효과를 유지하면서 문제를 해결하는 수정은 입증하지 못했다. 실험 변경은 모두 원복했으며, 실제 최종 변경 파일은 이 보고서와 캡처·검증 기록뿐이다.
