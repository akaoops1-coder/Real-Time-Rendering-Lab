# Chapter 06 — Mobile Eye Evidence and Provenance

> Date : 2026-11-18 (KST)
> Status : Current Preview Record / User Review
> Scope : Android Vulkan High Editor Preview

## Capture Provenance

이번 기록은 `RTR_Advanced_Mobile`에서 이미 열려 있던 Character Viewport와 `MI_Eye` Material Instance Editor를 Unreal Engine의 Native Slate Screenshot으로 저장한 것이다. 캡처를 위해 Parameter, Preview Platform, Camera를 변경하거나 Apply / Save를 실행하지 않았다. 실제 Capture는 `Captures/2026-11-18_MobileEye/`에 원래 파일명으로 보관하고, 본문용 Figure는 같은 PNG 바이트를 `Figures/Chapter06/`에 복사했다. Crop, Annotation, 색·밝기 보정과 이미지 재구성은 하지 않았다.

| Figure | Original Capture | Resolution | Visible Evidence |
|---|---|---|---|
| Figure 6-28 | Female01 Android Vulkan High Viewport | 1164 × 1012 | Near-front Female01에서 양쪽 Iris와 Pupil이 보인다. 하단의 `Android Vulkan High` 표시를 함께 확인할 수 있다. |
| Figure 6-29 | MI_Eye Android Vulkan High Preview | 1406 × 1162 | 우측 상단에 `Android Vulkan High`, General의 Parent에 `M_Eye_Master`가 표시된다. Iris Detail과 Corneal Reflection이 보인다. |

2026-11-02의 기존 Desktop 시점 `MI_Eye` Capture는 Mobile Platform 표시가 없어 이번 Mobile 결과의 증거로 사용하지 않았다. Engine Version `5.8.3`은 기존 프로젝트 Audit 기록을 계승한 환경 정보이며, 이번 두 화면에서 Version을 새로 검증한 것은 아니다. 현재 Map, Camera Transform, Light, Exposure 및 모든 Asset Override의 정확한 값은 이번 Capture로 기록하지 않았다.

## Capture Integrity

원본 Capture와 해당 Figure의 SHA-256이 각각 일치한다. 네 PNG의 크기, Chunk CRC와 압축된 전체 Scanline의 정상 해제를 확인했다. 두 원본 Capture 및 두 Figure의 상대 링크도 확인했다.

| Original Capture / Figure | Bytes per File | SHA-256 of Both Files |
|---|---:|---|
| `2026-11-18_Female01_AndroidVulkanHigh_Viewport.png` / `Fig6_28.png` | 1,380,786 | `25af3b1d35122c02e30e795637c569f23e299562fbfc23400ad563a4dbffc696` |
| `2026-11-18_MI_Eye_AndroidVulkanHigh_Preview.png` / `Fig6_29.png` | 1,285,458 | `d327df38dbf539154dbc409d0ccce1387676144d552512869555d403269afe95` |

## Current Preview Observation

사용자는 현재 Mobile Eye 표현을 재사용하기로 확인했다. Figure 6-28은 그 결정과 연결되는 현재 Character Preview다. 이 화면에서 양쪽 Iris / Pupil과 눈꺼풀의 관계를 확인할 수 있으며, 눈꺼풀 주변의 뚜렷한 검은 덩어리나 Eye가 떠 보이는 현상은 관찰되지 않았다. 이는 해당 정지 화면과 구도에 한정된 관찰이다.

Figure 6-29는 `MI_Eye`의 Preview와 Parent 관계를 함께 보여준다. Iris의 세부 무늬와 Corneal Reflection이 현재 Mobile Preview에서 보인다는 근거다. 이 한 장으로 모든 Material Parameter의 기능이나 Character에 배정된 각 Eye Surface의 독립적인 효과를 검증한 것으로 해석하지 않는다.

## Validation Boundary

이번 작업은 기존 상태의 두 화면을 직접 기록한 것이며, 통제된 A/B 비교는 수행하지 않았다. 다음 항목은 이번 증거의 검증 범위에 포함하지 않는다.

- 같은 조건의 Desktop / Mobile A/B 비교
- 사선 Camera 이동에 따른 Iris Parallax와 깊이 변화 검증
- Wetness / Occlusion Surface의 개별 ON/OFF 및 배정 검증
- Android Package / Cook와 실기기 실행·화질 검증
- GPU Timing 및 성능 비용 측정

사용자의 재사용 결정과 현재 화면의 직접 관찰은 구분한다. 두 Capture가 현재 Preview의 외형과 화면에 표시된 Platform / Parent를 뒷받침하더라도 전체 Eye의 Production Ready 판정이나 실기기 검증 완료를 뜻하지 않는다.
