# Foundation 문서 통일 편집 결과

편집일: 2026-10-02

Chapter 01–09와 Chapter 08 index·8.0–8.10의 현재 학습 문서 **20개**를 편집했다. 공통 기준은 [ASF-003 Documentation Standard v0.3](../00_Project/ASF/ASF-003_Documentation_Standard.md)에 반영했다. 개념 설명, 구현, 측정·진단이라는 각 문서의 목적을 유지하면서 연결 문단·제목 계층·회고·다음 안내의 역할을 맞췄다.

## 적용한 기준

- 반복되는 Callback 제목을 없애고 필요한 관계 설명을 도입이나 본문에 연결했다.
- Key Takeaways는 절·Module 회고에 선택적으로 사용한다. Chapter Summary는 장 전체 회고, Part Summary는 여러 절의 관계를 합성하는 회고이다.
- 비교, Interface, Data Flow, 긴 Implementation Reference를 요약과 구분한다. 새로운 기술 설명과 검증 조건은 회고 앞에 둔다.
- 같은 결론의 반복은 합치고 서로 다른 수치 예시·수식·비교 조건·구현 범위는 유지한다.
- 다음 주제 안내는 실제 순서와 제목에 맞추고, 파일 간 안내는 존재하는 상대 경로 링크로 연결한다.
- Chapter 제목 형식과 제목 수준을 맞추고 설명 문체는 다체로 통일한다. 코드·UI 문구의 표현은 보존한다.

## Chapter별 반영

| Chapter | 편집 결과 |
| --- | --- |
| [01](<Chapter01_RnderingPipeline.md>) | Coverage·Visibility 비교와 Data Flow를 요약 앞으로 옮겼다. 장 전체 회고와 Chapter 02 연결을 한 번 닫는다. |
| [02](<Chapter02_CoodinateSystem.md>) | 관계 표와 Data Flow의 제목을 참조 역할에 맞췄다. 같은 결론을 반복하는 문단을 통합하고 장 요약 뒤에 Chapter 03으로 연결한다. |
| [03](<Chapter03_LightingMathematics.md>) | 기존 개념 설명과 자연스러운 연결을 유지했다. 장 전체 회고와 Chapter 04 안내의 역할을 정돈했다. |
| [04](<Chapter04_MaterialArchitecture.md>) | 기존 설명 흐름을 유지했다. 마지막 개념 관계와 요약을 끝낸 뒤 Chapter 05로 연결한다. |
| [05](<Chapter05_Reflection_BRDF.md>) | Callback을 본문 관계 설명으로 통합하고 문단을 연결했다. Part 회고와 절 요약의 중복 및 실제 읽기 순서를 정돈했다. |
| [06](<Chapter06_ModernRealtimeRendering.md>) | Callback과 중복 예고를 통합했다. HDR의 Exposure·검증 조건을 요약 앞으로 옮기고 장 회고와 Chapter 07 안내를 정돈했다. |
| [07](<Chapter07_Stylized Rendering.md>) | Callback과 반복 Transition을 통합했다. 현재 기본 구현·교육용 예제·향후 확장 범위를 유지하면서 장 회고와 Chapter 08 연결을 정돈했다. |
| [08](<Chapter08_BuildingAnAnimeShader/Chapter08_BuildingAnAnimeShader.md>) | index와 8.0–8.10의 목적별 구성, 제목 계층, 요약·참조의 역할, 실제 파일 이동을 맞췄다. |
| [09](<Chapter09_RenderingDebugandOptimization.md>) | 다체로 통일했다. 사용 조건을 필요한 위치에 두고, Optimization Workflow·Chapter Summary·향후 Advanced 실습 계획을 구분했다. |

## Chapter 08 하위 문서

index의 8.8은 실제 문서 주제인 Region-based Parameter Control로 표시했다. 각 Module의 구현 목적은 유지하고, 마지막 8.10에서 장 전체를 합성한다. 기존 파일명과 Module 번호를 유지했다.

| Module | 편집 결과 |
| --- | --- |
| [8.0](<Chapter08_BuildingAnAnimeShader/Chapter08.0_PreparingTheASFProject.md>) | 중복 도입·환경 소개를 합치고 준비 조건과 완료 확인 뒤에 절 회고를 둔다. |
| [8.1](<Chapter08_BuildingAnAnimeShader/Chapter08.1_ArchitectureOverview copy.md>) | Architecture의 단계와 그 하위 설명의 위계를 맞춘다. |
| [8.2](<Chapter08_BuildingAnAnimeShader/Chapter08.2_BaseLighting.md>) | 계산·Interface·검증과 마지막 회고의 역할을 구분한다. |
| [8.3](<Chapter08_BuildingAnAnimeShader/Chapter08.3_Shadow.md>) | Shadow의 적용·관찰 범위를 유지하고 회고와 Specular 연결을 정돈한다. |
| [8.4](<Chapter08_BuildingAnAnimeShader/Chapter08.4_Specular.md>) | Module 회고를 마지막 Function의 하위 항목에서 분리한다. |
| [8.5](<Chapter08_BuildingAnAnimeShader/Chapter08.5_RimLight.md>) | 긴 단계별 설명과 Module 회고를 구분하며 Width·Intensity·적용 범위를 유지한다. |
| [8.6](<Chapter08_BuildingAnAnimeShader/Chapter08.6_MatCap.md>) | 긴 재설명은 Implementation Reference로 구분하고 Lookup·Remap·Lerp 예시와 식을 유지한다. |
| [8.7](<Chapter08_BuildingAnAnimeShader/Chapter08.7_Emission.md>) | Emission 상세 참조와 마지막 회고를 구분하며 출력·Post Process 조건을 유지한다. |
| [8.8](<Chapter08_BuildingAnAnimeShader/Chapter08.8_MaterialLayer.md>) | 새 적용 판단을 본문으로 구분하고 Module 회고와 완료 안내의 반복을 합친다. |
| [8.9](<Chapter08_BuildingAnAnimeShader/Chapter08.9_DebugView.md>) | 검증 예시와 Mode/Type 참조 목록의 역할을 유지하며 마지막 회고를 정돈한다. |
| [8.10](<Chapter08_BuildingAnAnimeShader/Chapter08.10_FinalFramwork.md>) | 통합의 목적부터 설명하고 Interface·계산·검증을 전개한 뒤 장 전체를 회고한다. |

## 보존과 확인

| 확인 항목 | 결과 |
| --- | --- |
| 현재 학습 문서 | 20개 편집 |
| 공통 문서 기준 | ASF-003 v0.3, 1개 편집 |
| 주요 Section 번호와 순서 | 101개 유지 |
| Callback 제목 | 31개 → 0개 |
| Figure 태그와 순서 | 158개 유지 |
| PNG 파일 | 161개 모두 편집 전과 SHA-256 동일 |
| 기존 Chapter 01–04 원본 backup | 4개 모두 편집 전과 SHA-256 동일 |
| Code/Formula/Data Flow fence | 편집 전 3410개, 편집 후 3410개; 고유 원문 보존 및 아래 예외 확인 |
| 표시 수식 블록 | 누락 0개 |
| 새 문서·내부 이동 링크 | 실제 파일과 Heading 대상으로 확인 |

기술 코드·계산식·수치 예시의 고유 fenced 원문은 유지했다. 순서 안내와 문서 표제 예시는 다음 두 예외를 확인했다.

1. Chapter 05의 5.1 학습 경로에서 Microfacet Model을 Cook–Torrance보다 먼저 읽도록 실제 5.9→5.10 순서에 맞췄다. 계산 코드 변경이 아니다.
2. ASF-003의 Chapter 제목 예시 구분자를 공통 `—` 형식으로 맞췄다.

Unreal Engine 실행, 새 Screenshot 제작, GPU 성능 측정은 이번 편집에 포함하지 않았다. 기존 본문의 미검증 상태와 설치 버전·Rendering Path·Space·Unit Vector·View/Pass·Texture/표시 조건을 유지했다. 현재 구현, 교육용 예제, 설계 방향, 향후 확장을 모두 완료된 기능으로 바꾸지 않았다.

## 파일과 원본 보존

전체 수정본 `Foundation_All_Chapters_Style_Aligned.zip`은 현재 문서 20개, 공통 기준, 이 결과 보고서, 기존 backup 4개와 PNG 161개를 포함한다. 원래 폴더 구조와 파일명을 유지하여 기존 작업 폴더에 대응한다.

수정 직전 원본 `Foundation_Before_Style_Alignment.zip`은 이번 편집 직전 문서 20개와 ASF-003을 별도로 보존한다. 이전 Chapter 01–04 `_backup.md`와 다른 시점의 보존본이며 기존 backup을 덮어쓰지 않는다.

수정 전 형식 검토 `Chapter01-09_Style_Consistency_Review.md`는 과거 검토 기록으로 남겼고, 원문 링크를 당시 보존본으로 연결했다. 사용자 작업 폴더의 별도 `.gitignore` 변경과 삭제된 과거 Rewrite Audit은 이번 문서 편집에 포함하지 않는다.
