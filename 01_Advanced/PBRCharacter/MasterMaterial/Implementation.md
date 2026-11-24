# PBR Master Material — Implementation

> Status : In Progress / User Reported
> Updated : 2026-10-11 (KST)
> Roadmap : Phase 03 — Production PBR Character Rendering
> Environment : Unreal Engine 5.8.3, Default Lit

## Purpose

Foundation에서 설명한 Material 입력을 실제 `M_PBR_Master`의 Data Flow로 연결하고, Texture가 의도한 의미로 해석되는지 확인한다. 현재 범위는 UV, Base Color, Normal과 ORM 입력이다. Character의 Skin, Hair, Eye 적용과 POM은 후속 작업이다.

## Current Evidence

| Item | State | Evidence and Remaining Work |
|---|---|---|
| UE 실행 환경 | 파일·로그 확인 | 기존 `RTR_Advanced.uproject`와 5.8.3 로그 확인. 새 저장 위치에서의 실행은 미검증 |
| Default Lit / M_PBR_Master | 사용자 보고 | 현재 그래프와 정식 저장 파일을 확인해야 함 |
| UV / Base Color | 사용자 보고 기준 구현 완료 | Graph Capture, Parameter 값, 재실행 후 상태 확인 필요 |
| Normal / ORM | 진행 중 | Texture 설정, Channel 계약, Graph와 Debug 결과 검증 필요 |
| 정식 Content Material | 미확보 | 기존 프로젝트 Content에 파일 0개. 자동 저장 복구 자료만 확인 |
| Capture / 비교 결과 | 미확보 | 이번 문서 작성 중 새 UE Capture나 Rendering 검증은 수행하지 않음 |

파일·로그 기준선과 검증 계획은 Validation에 기록한다. 구현되었다는 보고와 저장·재현·검증 완료를 구분한다.

## Data Flow to Record

다음 흐름은 기록해야 할 계약이다. 현재 Graph의 모든 연결이 직접 확인되었다는 뜻은 아니다.

```text
Mesh UV → Shared UV / Tiling → Texture Sampling
                              ├─ Base Color Data → Color Control → Base Color
                              ├─ Normal Data → Normal Control → Normal
                              └─ ORM Data → Channel Selection → AO / Roughness / Metallic
```

UV를 공유하는 입력과 개별 UV가 필요한 입력을 구분한다. Texture마다 Data의 의미, Color Space, Compression과 Sampler 설정을 함께 기록한다. ORM은 이름만 보고 순서를 추측하지 않고 원본 Texture의 Channel 의미를 확인한 뒤 연결을 확정한다.

## Input Contract — Pending Confirmation

| Input | Record Before Verification | Current Confirmation |
|---|---|---|
| UV | Coordinate Index, Tiling, Offset, 공유 입력 | 사용자 보고 외 세부 값 미기록 |
| Base Color | Texture, Tint, Color Space, Sampler, 기본값 | 구현 완료 보고; 값·설정 미확인 |
| Normal | Texture, Normal 데이터 해석, Sampler, Strength, 사용 Space | 진행 중; 값·설정 미확인 |
| ORM | R/G/B 각각의 의미, Texture 설정, AO/Roughness/Metallic 연결, 기본값 | 진행 중; Channel 계약 미확인 |

확인된 값은 실제 Texture 설정과 Graph Capture를 근거로 이 표에 추가한다. Texture가 없는 경우의 기본값과 Material Instance에서 노출할 Parameter도 함께 기록한다.

## Implementation Decisions

- Default Lit 기반으로 현재 기본 PBR 입력을 구성한다. 진행 상태는 사용자 보고를 따른다.
- UE 내부 경로는 기존 `/Game/ASF/PBR/Masters/M_PBR_Master`를 유지한다. 외부 문서 폴더의 이름으로 내부 경로를 다시 만들지 않는다.
- Normal / ORM 연결과 검증을 마친 뒤 Parameter Group과 최소 Material Instance를 정리한다.
- POM은 독립 R&D 프로젝트에서 다룬다. 중앙 구조 결정은 [DEC-017](../../../00_Project/Project_Management/DecisionLog.md)에 기록한다.

Sampler, Strength 구현 방식, Channel 계약 등 아직 확인하지 않은 선택은 Accepted 결과로 적지 않는다. 선택할 때 후보, 이유, 영향과 확인 방법을 이 Section에 추가한다.

## Evidence Storage

원본 Screenshot은 `Captures/`에, 설명용 Diagram과 본문용 파생 이미지는 `Figures/`에 저장한다. 현재 두 폴더에는 증거 이미지가 없다.

Capture에는 날짜와 내용을 알 수 있는 이름을 사용한다. 실제 Chapter 번호가 없는 현재 실습에는 임의의 Figure 번호를 배정하지 않는다. 자세한 기준은 Figure Style Guide를 따른다.

필요한 증거는 전체 Graph, 입력별 Texture 설정, Parameter 값, 고정 조건의 Viewport / Debug View, 변경 전후 결과다. Capture 링크는 파일을 확보한 다음 추가한다.

## Next Work

1. 기존 프로젝트에서 Material을 정식 저장하고 다시 열어 복구·저장 상태를 확인한다.
2. UV / Base Color의 현재 연결과 값을 기록한다.
3. Normal과 ORM의 입력 계약과 연결을 확인한다.
4. 한 번에 하나의 변수만 바꿔 비교하고 Validation에 기대 결과와 실제 관찰을 적는다.
5. 검증 근거를 확보한 작업만 Backlog에서 Done으로 전환한다.

세부 완료 기준은 Backlog를 따른다.
