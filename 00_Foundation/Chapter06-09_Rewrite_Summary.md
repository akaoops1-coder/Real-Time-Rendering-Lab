# Chapter 06–09 수정 요약

수정일: 2026-10-05

Chapter05_Reflection_BRDF_ref.md의 **질문 → 익숙한 예시 → 직관 → 필요한 개념 → 계산·구현 → 결과 해석** 흐름을 Chapter 06–09의 역할에 맞게 적용했다. Chapter 08의 Index와 8.0–8.10을 포함해 총 15개 문서를 수정했다.

| Chapter | 어떻게 바꾸었는가 |
|---|---|
| 06 — Modern Real-time Rendering | 같은 Material도 조명과 표시 기준에 따라 달라지는 예시에서 시작한다. 빛 입력 → BRDF 응답 → 화면 출력으로 연결하고, IBL·Exposure·Tone Mapping·Color Space가 필요한 이유를 먼저 설명한다. |
| 07 — Stylized Rendering | 캐릭터의 형태를 읽기 쉽게 만들려는 목적에서 시작한다. Threshold·Smoothstep·Ramp를 하나씩 소개하고, Shadow·Rim·Hair·Face·Outline은 필요한 입력과 표현 목적을 연결한다. |
| 08 — Building an Anime Shader | 구현 순서를 유지하면서 각 단계의 문제, 필요한 Data, 기대 결과를 보완한다. 앞 장의 개념을 짧게 회수하고, Prototype과 최종 Interface, 기존 관찰과 현재 계약의 검증을 구분한다. |
| 09 — Rendering Debug and Optimization | 증상 → 측정 목적 → 지표 → 도구 → 원인 분리 → 개선 → 재측정으로 연결한다. 측정 조건을 풀어 설명하고, 각 도구가 답하는 질문을 사용 방법보다 먼저 안내한다. |

긴 Figure 주석은 짧은 관찰 Caption과 상세 Reading/Verification Note로 정리했다. 판단에 필요한 입출력·측정·비교 조건은 관련 계산과 실험 곁에 유지했다.

Chapter 01–05, Reference와 Figure 이미지 파일은 변경하지 않았다. 수정 대상의 기존 fenced 수식·코드·Data Flow 2,506개, 기술 표, inline 표현, Figure 태그 100개와 순서를 보존 검사했다. 수정 직전 원고 15개는 각각 `_backup.md`로 보관했다.

이번 작업은 문서 수정이다. Unreal에서 새로 실행하거나 성능을 측정하지 않았으며, 기존 예시 수치와 구현 관찰을 새 검증 결과로 바꾸지 않았다. 2026-10-04의 Chapter06-09_Style_Audit.md는 제안 당시의 기록으로 보존하고, 이번 적용 결과는 이 요약을 기준으로 읽는다.
