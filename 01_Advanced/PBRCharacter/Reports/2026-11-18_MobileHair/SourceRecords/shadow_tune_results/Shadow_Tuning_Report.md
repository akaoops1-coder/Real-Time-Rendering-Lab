# Hair CSM 정밀도 비교 결과

2026-11-17 · UE 5.8.3 · Android Vulkan High Editor Preview / Mobile Forward

현재 구도의 비용 대비 채택값은 **Distance 1,000cm / Distribution 7 / CSM 2,048**이다. 이마의 뭉친 그림자 경계는 기준값보다 선명해졌다. 가닥 그림자의 분리만 보면 **CSM 4,096**이 가장 좋았다. Hair 내부의 넓고 어두운 띠는 모든 비교에서 상당 부분 남아, 이번 조정만으로 해결됐다고 판단하지 않는다.

## 비교 조건

- Shadow 생성 여부, Hair Cast Shadow ON/OFF 검증은 반복하지 않았다. Hair Cast Shadow는 계속 ON.
- Cube는 editor hidden 상태를 유지했다.
- Camera 위치 (-36.075329, 12.753424, 168.115568), 회전 (Pitch -0.800001, Yaw -32.764472, Roll 0) 고정.
- Directional Light 방향, 위치, intensity 0.5 고정. Transform은 비교 전후 동일.
- Hair 실제 할당: `/Game/ASF/Characters/Female01/Materials/MI_Female01_hair`.
- Parent: `/Game/ASF/PBR/Mobile/M_Mobile_Hair_Production`.
- 이 원본 MI에는 `Use_CSM_Visibility`가 없다. `Use_CustomSpecular=True`. 현재 테스트는 엔진 Mobile CSM의 기본 조명 반응이며, 복제 Custom Visibility Material은 할당하지 않았다.
- Material 파라미터와 원본 Material, 엔진 소스는 수정하지 않았다. Custom Visibility PCF도 추가하지 않았다.
- Shadow Bias 0.5 / Slope Bias 0.5 / Sharpen 0 / Resolution Scale 1 / transition fraction 0.1 유지.
- 각 변형은 기준값에서 한 항목만 바꿨다. Distribution 4 및 7은 각각 독립 비교다.
- 2,560×1,440 캡처에서 동일 픽셀 영역을 잘랐다. Camera를 움직이거나 확대하지 않았다. 이마 crop (1260,370,440,310), Hair crop (1580,270,440,600). 확대 보정이나 생성형 이미지 처리는 없다.

## 설정별 관찰

| 비교 | Distance cm | Distribution | CSM tile 상한 | 첫 Cascade 범위 cm (overlap 포함) | 관찰 및 비용 |
|---|---:|---:|---:|---|---|
| 기준 | 1000 | 3 | 2048 | 10–277.30 | 이마 경계가 넓게 뭉침. 2 Cascade, 16MiB 아틀라스 |
| Distance | 500 | 3 | 2048 | 10–142.30 | 이마 경계가 얇고 선명해짐. 추가 해상도/메모리 없음. coverage 10m→5m |
| Distribution 소폭 | 1000 | 4 | 2048 | 10–223.84 | 개선은 작음. coverage와 아틀라스 동일, 원거리 분할 정밀도 감소 |
| Resolution | 1000 | 3 | 4096 | 기준과 동일 | 이마에 가는 그림자 띠가 가장 잘 분리됨. Hair 내부 큰 검은 영역은 유지. 아틀라스 64MiB |
| Distribution 집중 | 1000 | 7 | 2048 | 10–143.65 | 500cm와 비슷한 근거리 경계 개선. coverage 10m 유지. 비용 대비 채택 |

Distribution 7의 두 번째 Cascade는 133.75–1,000cm다. 기준은 257.50–1,000cm, Distribution 4는 208–1,000cm, Distance 500은 132.50–500cm다. 이 수치는 `r.DumpShadows` 출력이며 light-space texel의 cm 크기를 직접 측정한 수치는 아니다. Distribution 7의 원거리 정밀도 저하는 분할 범위로부터 예상되는 trade-off이며, 원거리 피사체의 별도 시각 평가는 하지 않았다.

## 해상도: 상한과 실제 할당

| 항목 | 기준 / 최종 | 4096 비교 |
|---|---:|---:|
| `r.Shadow.MaxResolution` (일반 Shadow 상한) | 1024 | 1024 유지 |
| `r.Shadow.MaxCSMResolution` | 2048 | 4096 |
| Light 요청 Cascade 수 | 4 | 4 |
| 실행 상한 `r.Shadow.CSM.MaxCascades` | 2 | 2 |
| 실제 생성 Cascade 수 (dump) | 2 | 2 |
| 실제 `MobileCSMAndSpotLightShadowmap` 아틀라스 | 4096×2048 | 8192×4096 |
| 풀에서 보고한 아틀라스 메모리 | 16MiB | 64MiB |

아틀라스는 2개의 nominal 2048² / 4096² Cascade tile에 해당하며 border가 포함된다. 해상도 상한만 읽고 실제 해상도로 간주하지 않았다. `r.DumpRenderTargetPoolMemory`에서 해당 크기와 `Unused frames: 1`을 확인했다. 복구 후 64MiB 항목은 풀에 남아 있으나 `Unused frames: 7474`, 사용되는 16MiB 항목은 `Unused frames: 1`이었다. 따라서 풀에 남은 고해상도 항목을 최종 활성 할당으로 계산하지 않았다.

4096은 Shadow depth texel 수/저장공간이 4배다. Shadow raster와 bandwidth 비용이 증가할 수 있으나 GPU 프레임 시간이 4배라는 의미는 아니다. 실제 Android 기기 GPU ms는 측정하지 않았다. Distance/Distribution 비교는 tile 크기와 Cascade 수, filtering kernel을 유지하므로 고해상도 테스트와 같은 4배 저장공간 증가가 없다. Caster 포함 범위에 따른 draw/raster 비용은 달라질 수 있다.

## Filtering

동일 Android Vulkan Preview의 컴파일된 Mobile Base Pass shader dump에서 `MOBILE_SHADOW_QUALITY 2`를 확인했다. 현재 엔진의 `MobileLightingCommon.ush`에서 이 값은 `Manual3x3PCF`다. `r.ShadowQuality=2`, `r.Shadow.FilterMethod=0`도 읽었지만, 이 값들만으로 Mobile kernel을 판정하지 않았다.

현재 Directional Mobile CSM 함수는 `MobileShadowPCF` 이후 distance fade를 적용하며 Shadow Sharpen 값을 사용하지 않는다. 따라서 이 경로에서 `Shadow Filter Sharpen`은 지원되는 개선 수단으로 판단하지 않아 증가 비교를 수행하지 않았다. 값은 0으로 유지했다. PCF kernel 변경, Custom HLSL PCF 추가, Bias 비교는 수행하지 않았다.

근거: 실행 중인 엔진의 `local path withheld` 115–129 및 159 이후. 컴파일 dump는 프로젝트 `Saved/ShaderDebugInfo/VULKAN_ES3_1_ANDROID_Preview/M_Female01_BrightSoft_Production_7dedf8634927ec95/Default/FLocalVertexFactory/TMobileBasePassPSFMobileDirectionalLightAndCSMPolicy/0/MobileBasePassPixelShader.usf`의 define이다. CSM 할당/분할의 보조 근거는 설치본 UE 5.8 `ShadowSetup.cpp`의 CSM 크기 결정 및 `AllocateMobileCSMAndSpotLightShadowDepthTargets` 코드다. 보조 C++ 소스는 실행 바이너리의 직접 계측을 대체하지 않으며, 실제 크기/분할은 로그로 확인했다.

## 같은 영역 비교

왼쪽부터 기준 / Distance 500 / Distribution 4 / Resolution 4096:

이마 4개 독립 비교
Hair 내부 4개 독립 비교

왼쪽부터 기준 / Distance 500 / Distribution 7 / Resolution 4096:

이마 근거리 집중 비교
Hair 내부 근거리 집중 비교

채택한 Distribution 3→7 전후:

이마 채택 전후
Hair 내부 채택 전후

이마에서는 경계 폭 감소가 명확하다. Hair 내부에서는 개별 어두운/밝은 가닥 경계의 차이는 있으나, 넓은 검은 띠와 겹친 실루엣의 상당 부분이 남는다. 이 검은 영역 전체를 CSM blur로 단정할 수 없다. 얇은 가닥의 픽셀 계단과 알파 실루엣은 여전히 보이며, 이번 고정 구도 정지 이미지로 시간적 깜빡임 개선 여부는 판정하지 않았다.

## 최종 상태와 복구

현재 Editor 세션에 Distribution 7만 채택했다. Distance는 1000cm, CSM 상한은 2048로 복구했으며 일반 해상도 상한 1024, Bias 0.5/0.5, Sharpen 0, Cascade 수/상한, Material 할당/파라미터를 유지했다. Camera, Light Transform, Hair Cast Shadow도 유지했다. `*_state.json`과 `verification.json`에 비교 증거를 담았다.

레벨은 시작부터 미저장 변경이 있었으므로 기존 작업을 함께 저장하지 않도록 맵 전체 저장은 실행하지 않았다. Distribution 7은 현재 열린 Editor에 적용된 상태이며 디스크에 저장된 맵의 영구 변경으로 보고하지 않는다.
