# Chapter 06 — Mobile Hair Evidence and Provenance

## Figure Provenance

Figure 6-21은 실제 Capture의 바이트가 같은 복사본이고, Figure 6-22는 저장 Graph의 배선을 전사한 도식이다. Figure 6-23–6-27은 실제 Capture를 Crop·배치한 비교 자료이며, 6-27의 청록색 행은 같은 Camera의 기준 Frame 대비 화면 밝기 차를 표시한 파생 시각화다. 이번 원본 반영에서는 이미지 바이트를 변경하지 않았다. 원본 Capture 36장은 `Captures/2026-11-18_MobileHair/`에 기존 파일명과 하위 경로를 유지해 보관했다. 원본·합성 입력·스크립트·보고서의 전체 SHA-256은 Asset Manifest에 기록한다.

| Figure | Original or Derivation | SHA-256 of PNG |
| --- | --- | --- |
| Fig6_21.png | Original Capture · 원본 Capture와 바이트가 같다. | `1f1a532469dff9158d00828fa58c2efe15b81b1ddb59f40b673964a750b7a187` |
| [Fig6_22.png](../../Figures/Chapter06/Fig6_22.png) | [편집용 SVG](../../Figures/Chapter06/Fig6_22.svg) · [Specification](../../Figures/Chapter06/Fig6_22.spec.md) · 실제 배선 Audit을 전사한 도식. | `bf30371ac87369473b3922688406e0e33d491af156b529ddfad73a696066b8e9` |
| Fig6_23.png | 기존 비교 이미지 `hair_cast_current_results/Forehead_Temple_CastShadow_ON_OFF.png`와 바이트가 같다. Composition Source · 아래 Raw Capture Index 참조. | `c9f878a74f32b753cf497f179a67056fed94acd8f3f1e23759cd011c9970fc98` |
| Fig6_24.png | 기존 비교 이미지 `shadow_tune_results/Forehead_All.png`와 바이트가 같다. Composition Source · 아래 Raw Capture Index 참조. | `f38b432400d845cd045da0a72a003013034bf764198ec937955ae6273e31923e` |
| Fig6_25.png | 기존 비교 이미지 `hair_csm_results/Hair_CSM_Before_After.png`와 바이트가 같다. Composition Source · 아래 Raw Capture Index 참조. | `3d51ced42a767e6c1c0755d519cb73c0551801d270e8fa2502ba71f390f82bd2` |
| Fig6_26.png | 기존 비교 이미지 `angel_ring_results/AngelBand_Android_Vulkan_High.png`와 바이트가 같다. Composition Source · 아래 Raw Capture Index 참조. | `dcc648bcca863e851c2ea85739143ca6841d97ae3fa401b1d83b6aeae9196298` |
| Fig6_27.png | 기존 비교 이미지 `angel_axis_tilt_results/verified/AngelBand_Camera_Orbit_Comparison.png`와 바이트가 같다. Composition Source · 아래 Raw Capture Index 참조. | `a1204fbc6548f59ddaa12b8dc0096f53a703af522b70bf41294a6e9fbc75c5fc` |

---

## Material and Assignment

- **Production.** 2026-11-18에 Unreal에서 `M_Mobile_Hair_Production`의 Expression과 Material Output을 읽었다. `Use_CustomSpecular` 결과가 Custom CSM Visibility에 곱해지는 분기와 `MP_EmissiveColor` 연결을 확인했다. 저장된 파일의 SHA-256은 `bb9e746f810749a63ae8916614435f4e05b19612e89e71acbcc016df8dc367bd`다. 저장된 에셋에서 단일 Shadow Texture 조회 코드와 `Use_CSM_Visibility` 이름도 확인했다. Material Graph Audit
- **PDO and AO.** PDO 미연결은 2026-11-17 Mobile Hair Shadow Diagnosis의 MaterialEditorOnlyData 기록을 따른다. 최신 Graph 조회에서는 해당 Output Enum을 반환하지 못했고, AO Output은 미연결로 반환됐다.
- **R&D.** Angel Band Verification이 기록한 R&D Master의 저장 SHA-256 `701dfe8bab3e11cb15b8057c00b18fb45a6ef06b2c9553575af769cf37583da3`과 현재 파일이 일치한다. 최신 Audit에서도 SmoothStep Value가 Card Normal을 사용하는 Dot에 연결되어 있다.
- **Instance.** Orbit Preflight 및 Orbit Restoration에서 Hair Slot 0이 `MI_Female01_hair`이며 Parent가 R&D Master이고 `Angel_AxisTilt` Override가 0.5였음을 확인했다. 이후 저장된 Instance 파일에서도 R&D Parent 참조가 확인된다. 이 조회로 이전 Production 외형의 모든 Instance Override가 복원됐다고 판단할 수는 없다.

## Cast Shadow and CSM

- **Recovery.** 2026-11-17의 Mobile Hair Shadow Diagnosis는 고정 Camera에서 20,000↔1,000cm를 비교해 이마 및 Hair 내부의 Shadow 복원, Level의 1,000cm 변경 저장을 기록한다. Figure 6-23은 이후 1,000cm에서 수행한 Cast Shadow 단일 변수 비교다.
- **Hair-to-Head and Self Shadow.** [Cast Shadow Report](SourceRecords/hair_cast_current_results/Current_View_Hair_Cast_Shadow_Report.md)의 이마·관자놀이 및 Hair 내부 Crop을 확인했다. 외부 Cube는 숨김 상태였고 당시 Production Parent에는 Custom CSM 분기가 아직 없었다.
- **Near-field Quality.** [Shadow Tuning Report](SourceRecords/shadow_tune_results/Shadow_Tuning_Report.md)와 [Runtime Evidence](SourceRecords/shadow_tune_results/runtime_evidence.json)은 500cm, Distribution 변경과 해상도 비교의 실측 할당 정보를 기록한다. Figure 6-24는 이마 비교다. 당시 세션 채택 상태인 1,000cm/E7/2048은 Character 근접 500cm 비교와 다른 조건이다.
- **Custom Visibility.** [CSM Integration Report](SourceRecords/hair_csm_results/Hair_CSM_Integration_Report.md)와 CSM Verification은 Production 복제 Material의 외부 Cube 위치·Cast Shadow 대조, Hair Self Shadow Debug 및 Single-Sample 경계 관찰을 기록한다. Figure 6-25는 이 복제본 비교다. 실제 Production 적용은 사용자 작업 기록 및 저장 Graph에서 확인했다. 실제 Production의 이식 직후 OFF/ON 원본 화면은 확보되지 않았다. Single-Sample HLSL

## Angel Ring and Camera Orbit

- **Virtual Tangent.** `Angel_DepthShift = 0 / 0.23`은 사용자 실험 기록이다. 저장 R&D Graph에서 Depth 보정항이 Tangent Lobe의 내적에 더해지는 경로는 남아 있다. 같은 Camera와 노출에서 촬영된 이 중간 비교의 원본 두 장은 확보하지 못했다.
- **Band Attenuation.** Figure 6-26은 같은 Camera, Light, 노출 설정, Hair Cast Shadow와 Material Switch가 유지된 Before/After다. Angel Band Verification에서 수정된 노드는 SmoothStep 하나이며, Value가 `DotProduct_4`에서 `DotProduct_0`으로 바뀐 것을 확인했다.
- **Camera Orbit.** Orbit Lit Record과 Orbit Baseline Record은 각 Camera 위치와 회전을 기록한다. Figure 6-27의 청록색은 화면 밝기 차를 일정한 표시 범위로 시각화한 것이다. 이는 Card-facing 및 CSM 감쇠 이후의 결과다.

## Evidence Limits

저장 Production Graph의 전체 Material Editor 화면은 확보하지 못해 검증한 배선을 도식에 정리했다. 첫 Default Lit + Masked Baseline 첨부와 초기 20,000↔1,000cm의 동일 구도 원본도 확인 가능한 파일로 확보되지 않았다. Figure 6-21에는 Custom Visibility 이식 전의 실제 Production 외형을, Figure 6-25에는 복제 Material의 OFF/ON 결과를 사용했다. 현재 R&D 외형은 Figure 6-26과 6-27에 담았다. Android Cook, 실기기 품질 및 GPU Timing 결과는 없다.

## Raw Capture Index

아래 링크는 보정하지 않은 원본 화면이다. Supporting Comparison은 기존 비교 자료를 `Figures/Chapter06/MobileHairComparisons/`에 보관한 것이다. Source Report는 당시 관찰 기록을 보존하며 Markdown 이미지 링크만 현재 상대 경로로 조정했다. 원문 해시와 저장본 해시를 Manifest에 함께 기록했다. JSON과 합성 스크립트는 원본 바이트를 보존한다. 합성 스크립트의 `$PSScriptRoot`는 이전 작업 디렉터리 기준이므로, 재실행할 경우 Manifest의 원본 경로 구조로 Capture를 배치한 별도 작업 사본에서 사용한다. 이번 반영에서는 스크립트를 실행하지 않았다.

### Figure 6-21 / 6-23 — Cast Shadow

- 01_HairCastShadow_ON.png
- 02_HairCastShadow_OFF.png

### Figure 6-24 — Near-field CSM

- 01_baseline_D1000_E3_R2048.png
- 02_distance_D500_E3_R2048.png
- 03_distribution_D1000_E4_R2048.png
- 04_resolution_D1000_E3_R4096.png
- 05_distribution_D1000_E7_R2048.png

### Figure 6-25 — CSM Visibility and Controls

- 01_OFF_CubeA.png
- 02_ON_CubeA.png
- 03_ON_CubeB.png
- 04_OFF_CubeB.png
- 05_ON_CastShadowOFF.png
- 06_OFF_CastShadowOFF.png
- 07_ON_HairCastShadowOFF.png
- 08_Visibility_HairCastON.png
- 09_Visibility_HairCastOFF.png
- 10_Visibility_CubeA.png
- 11_Visibility_CubeA_Move0p25cm.png

### Figure 6-26 — Angel Band Attenuation

- 50_Matched_Before.png
- 51_Matched_After.png
- 21_axis_dot.png
- 22_virtual_dot.png
- 23_card_dot.png
- 24_csm_visibility.png

### Figure 6-27 — Camera Orbit

- lit_t000_yaw_000.png
- lit_t000_yaw_m28.png
- lit_t000_yaw_p28.png
- lit_t050_yaw_000.png
- lit_t050_yaw_m28.png
- lit_t050_yaw_p28.png
- lit_t100_yaw_000.png
- lit_t100_yaw_m28.png
- lit_t100_yaw_p28.png
- delta_baseline_yaw_000.png
- delta_baseline_yaw_m28.png
- delta_baseline_yaw_p28.png

### Composition Sources

- hair_cast_current_compose.ps1
- shadow_tune_compose.ps1
- hair_csm_compose.ps1
- angel_ring_compose.ps1
- angel_axis_tilt_results/verified/compose_orbit.ps1
- angel_axis_tilt_results/verified/compose_comparison.ps1

### Retained Evidence Limits

초기 20,000↔1,000cm 비교와 `Angel_DepthShift` 중간 비교의 원본 화면은 확인 가능한 파일로 확보되지 않았다. 초기 Diagnosis 보고서는 확보했지만 해당 보고서의 당시 MCP Capture를 새로 구성하거나 대체하지 않았다. Android Cook·실기기·GPU Timing 미검증 상태를 유지한다.
