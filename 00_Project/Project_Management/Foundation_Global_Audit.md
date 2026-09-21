# Foundation Global Integration Text Audit

Status: Complete — Global Integration Text Audit 완료. 원본 Refactoring 및 Engine 검증은 수행하지 않음.
Audit period: 2026-09-20–2026-09-21 (KST); final report saved 2026-09-21.
Scope: Chapter 01–09 원본 Markdown 20개. 실제 루트: C:\Users\kmcoo\Desktop\PW\ASF_Review. 원본 위치: 00_Foundation.
Output: 00_Project/Project_Management/Foundation_Global_Audit.md만 작성. 원문 Refactoring 및 Figure 이미지 재검토는 수행하지 않았다.

## 1. Executive Summary

현재 Foundation은 Pipeline과 좌표를 이해한 뒤 Material·Reflection·현대 Rendering·Stylized 제어를 거쳐 직접 구현하고 측정하는 학습 흐름을 갖추고 있다. Chapter 전체 재배치보다 **정의와 실제 합성 계약을 먼저 바로잡고, 개념별 주 설명 위치를 확정한 뒤 반복을 줄이는 방향**이 적합하다. 길이가 긴 절이라는 이유로 삭제하거나 Chapter 08의 기본 구현·검증을 Advanced로 보내지 않는다.

판단 우선순위는 Project Principles → Accepted DecisionLog → Current Standards → Current Foundation → Implementation Detail이다. ASF-000/001/002/003, ASF_Standard, DecisionLog, Roadmap을 확인했다. Accepted DEC-014의 Chapter 06 Modern Realtime Rendering → Chapter 07 Stylized Rendering, DEC-015의 **Anime Shader Framework**, DEC-016의 Theory/Experiment 분리를 적용한다. 사용자가 제시한 Geometry/Lighting/PBR 흐름은 개념의 선후 관계로 점검했다. 오래된 Roadmap 역할표에 맞추려고 실제 Chapter 03 Lighting Mathematics를 해체하거나 Chapter 05 Reflection/BRDF와 Chapter 06을 통째로 교환하는 Local 권고는 채택하지 않는다.

Technical Consistency의 핵심 문제는 BRDF를 최종 반사광으로 정의하는 Chapter 05, 조명 기법·BRDF·HDR을 연속 실행 Stage처럼 나열하는 Chapter 06, 중간 구현과 최종 계약이 혼재하는 Chapter 08이다. 같은 Space, Texture와 현재 Sample, Visibility와 방향 계수는 여러 절에서 정확히 구분하지만 요약·도식형 문장에서는 다시 합쳐진다. “뒤에서 배운다”는 Deferred/GBuffer, Depth Precision/Reversed-Z, IOR/SSS 안내 중 실제 후속 설명이 없는 것도 확인했다.

Architecture Consistency에서는 ASF-002가 Module≠Material Function을 명확히 하지만 8.1과 8.10은 Module을 MF와 동일시하거나 모든 MF가 직렬로 연결되는 것처럼 설명한다. 최종 구현의 핵심은 **독립 입력과 Mask 계산, Base Lighting에 Visibility 곱셈, Specular/Rim Add, MatCap Lerp, Emission Add, 기존 결과를 재사용하는 Debug 선택**이다. 수동 ShadowVisibility와 별도 Region 실습을 Renderer Shadow 통합·Production Layer System으로 확대 해석해서는 안 된다.

가장 잘 구축된 부분은 2.13의 Position/Direction/Normal 예외, 3.4의 Geometry와 Shading Normal 구분, 4.3–4.5의 Texture/Sample/Data 구분, 8.3의 방향과 Visibility 및 PCF 비교 순서, 8.5의 Rim/Fresnel 목적 차이, 8.7의 Emission/Bloom 분리와 현재 Pixel Scalar 설명, 8.9의 실제 중간 결과 재사용, 9.1–9.8의 측정 우선·단일 수치 단정 금지이다. 이들은 Necessary Reinforcement로 보존할 기반이다.

Refactoring 전에 먼저 확정할 사항은 다음과 같다.

| ID | Severity | 가장 중요한 문제 | 최종 Action |
|---|---|---|---|
| GI-01 | Critical | BRDF 응답·Lighting Result·출력색의 구분 및 Chapter 06의 잘못된 직렬 모델 | Rewrite / Expand |
| GI-02 | Critical | Chapter 08의 실제 분기·Multiply/Add/Lerp·Debug 계약과 설명 불일치 | Rewrite |
| GI-03 | Critical | 8.4 중간 Phong Response→Material Specular 핀 설명이 최종 모델 교체처럼 읽힘 | Rewrite / Needs Technical Verification |
| GI-04 | High | N/L/V 부호·Space·Normalize와 Matrix 곱 convention이 전파 과정에서 변함 | Rewrite / Terminology Unification |
| GI-05 | High | Scene Shadow를 취득하지 않은 수동 Visibility 실습의 완료 범위 과장 | Rewrite |
| GI-06 | High | Forward 계열 Light 입력과 지정 Deferred 환경, Engine 출력·설정의 실행 근거 부족 | Needs Technical Verification |
| GI-07 | High | 기본 반사 수식·단위·Rendering Equation 연결 및 실제 후속 설명이 없는 참조 | Expand / Cross Reference |
| GI-08 | High | Exposure/출력색/Debug 표시와 실제 계산값·측정 증거의 혼동 | Rewrite / Expand |
| GI-09 | High | Camera 가시성·비용 범주·병목 측정의 인과를 지나치게 단정 | Rewrite |
| GI-10 | Medium | 개념 소유권 없는 재설명, 늦은 정의, 반복 요약 | Merge / Shorten / Move / Cross Reference |

현재 Chapter 순서, 8.0 준비→8.1 책임→8.2–8.8 구현→8.9 Debug→8.10 통합, Chapter 09의 최종 진단 역할은 유지한다. 필요한 Section 이동은 최소 개념의 첫 소개와 주 설명 정리에 한정한다. 이 보고서는 수정 권고이며 기술 검증이나 원본 수정 완료를 뜻하지 않는다.

## 2. Foundation Learning Flow Review

| Chapter / Role | Input Knowledge | New Knowledge | Output Knowledge | Next Chapter Connection |
|---|---|---|---|---|
| 01 Rendering Pipeline | Mesh·화면에 대한 기초 경험 | Attribute, Primitive, Rasterization, Interpolation, Depth/Test/Write, Draw/Output | 어디에서 어떤 데이터가 처리되는가 | 02가 Position 변환을 상세화. 1.3의 Surface Attribute를 3.4·4.4·9.3에서 소비한다 |
| 02 Coordinate / Transformation | 01의 Vertex와 화면 변환 필요성 | Position/Direction, 각 Space, Clip/W/Divide, Matrix, TBN, Engine 입력 | 같은 물리량을 필요한 Space로 준비하고 해석 | 03의 N/L/V 연산을 위한 계약. Normal 예외 소개는 2.13, 전체 원리는 3.5 |
| 03 Lighting Mathematics | 02의 Space·변환 의미 | Normalize, Dot, Surface Normal, Inverse Transpose, L/V 생성 | 반사 계산에 사용할 방향·각도 관계 | 04가 Texture/Material을 추가하고 05가 이 입력으로 반사 응답을 평가. Geometry/Surface 역할은 1.3+3.4로 충족 |
| 04 Material Architecture | 01의 보간, 02의 UV/TBN, 03의 N | Property, Texture/Sample, Filtering, Color/Data, Normal Map, Parameter/Instance | 저장 데이터·현재 Sample·Parameter가 Surface 입력으로 합류 | 05에 Base Color/Roughness/Normal을 전달. Base Color의 Metallic별 역할 연결을 보완 |
| 05 Reflection / BRDF | N/L/V와 Material Property | Reflection Vector, Diffuse/Specular, H, Microfacet D/G/F, Radiometry, BRDF | 입력 조명에 대한 반사 응답 | 06의 Direct/환경 기여 계산에 쓰일 계약. 현재 누락된 최소 수식·단위·적분 관계를 먼저 보완 |
| 06 Modern Realtime Rendering | 05의 BRDF와 04의 Linear 계산 | Direct/Indirect, IBL, 환경 반사, HDR, Tone Mapping, 출력 변환 | Material 응답이 전체 이미지에 기여하는 관계 | 07이 어떤 물리량/함수를 표현 목표에 맞춰 제어하는지 설명. PBR을 처음 시작하는 새 장으로 재명명하지 않음 |
| 07 Stylized Rendering | 05 반사 모델 + 06 이미지 형성 | Tone Band, Highlight, Shadow, Rim, Hair/Face/Outline 및 제어 도구 | 유지할 기반과 의도적으로 변형할 응답 | 08의 기초 구현 범위를 명시. Threshold/Ramp 최소 정의를 7.2 전에, 7.9는 종합 적용으로 유지 |
| 08 ASF Implementation | 01–07의 Surface/Direction/Sample/Response/출력 | MF 구현, Master 합성, MI 제어, Region 실습, Debug 선택 | 계산 계약을 구현·관찰·분리 검증하는 Framework | 09에 실제 계산 항목과 관찰 가능 지점을 전달. Production 완료 및 Renderer Shadow 통합은 주장하지 않음 |
| 09 Debug / Profiling / Optimization | Pipeline + 08의 실제 결과·Debug | Frame/Thread/GPU, Geometry·Coverage·Shader·Draw·LOD/Culling, 도구별 질문 | 관찰→가설→측정→원인 후보 분리→수정→재측정 | Foundation을 닫고 이후 상세 실험·Production 사례로 연결. Tool 목록만 늘리지 말고 짧은 기본 측정 예시를 제공 |

Cross Reference는 각 소비 절에 “이번 계산이 필요한 이유 + 입력 의미/Space/범위 + 원리 참조”를 남기는 방식으로 한다. 8.4의 Node 대응이나 8.7의 현재 Pixel Sample을 링크만으로 대체하지 않는다. 미래 예고는 실제 절 제목을 확인한 뒤 연결하고, 구현되지 않은 항목은 후속 범위로 명시한다.

## 3. Concept Source of Truth Map

Primary Source는 Phase 2의 설명 책임이다. 아래에서 “보완”이라고 표시한 곳은 현재 설명이 충분하다는 뜻이 아니다. First Introduction과 상세 설명 위치를 분리한다.

| Concept | First Introduction | Primary Source | Reinforcement | Implementation | Recommendation |
|---|---|---|---|---|---|
| Pipeline Stage / Raster 데이터 흐름 | 1.1–1.2 | 1.3–1.11, 종합 1.13 | 6.1/6.9는 전체 이미지 관계, 9.3–9.8은 비용 | 8.1/8.10 | 실제 Stage와 설명용 Group·Module을 분리 |
| Vertex / Surface Attribute / Seam | 1.3 | 1.3, Index 소비 1.5 | 3.4 Normal, 2.14 TBN, 9.3 비용 | PixelNormalWS·UV 입력 | Ch03으로 전체 이동하지 않음 |
| Position / Direction | 1.4 개요 | 2.2; 변환 분류 2.13 | 2.8 w, 3.6 위치 차이 | 2.15, 8.2/8.5/8.6 | 의미와 Space를 함께 표기 |
| Matrix / Model View Projection | 1.4 개요 | 2.11–2.12 | 2.16 요약, 3.5 Normal 예외 | 2.15, 8.6 | 실제 행렬 예제와 convention 보완 |
| Clip / W / NDC / Screen | 01 개요 | 2.7/2.8/2.9/2.10 각각 | 2.16, 8.3 light projection | 8.3 Shadow 개념 | 같은 Space로 합치지 않음 |
| Normal과 Geometry/Shading 차이 | 1.3 | 3.4 | 2.14 basis, 4.6 Normal Map, 5.2 소비 | 8.2–8.6 | Artist Normal·Silhouette 불변 설명 유지 |
| Normal Transform | 2.13 | 3.5, Surface 조건 3.4 | 2.16은 경로, 3.7은 진단 | 8.6 입력 Space | Local의 Primary=2.13을 수정. 선형부·invertible 조건 보완 |
| Normalize / Dot | 1.8 보간 후 필요성 | 3.2/3.3 | 3.7 계약, 5의 각도 사용 | 8.2/8.4/8.5 | 영벡터·Unit 조건·signed 값과 clamp를 분리 |
| L / V Convention | 03 개요 | 3.6 | 3.7, 5.3/5.6 | 8.2/8.4/8.5 | L=Surface→Light, V=Surface→Camera; 입사 진행은 -L |
| Texture / Sample / UV | 1.3 UV 개요 | 4.3 저장/현재 값, 4.4 Sampling | 4.8 합류, 6.8 데이터 해석 | 8.6 Texture Object, 8.7 Mask, 8.8 Region | Ch06을 Texture Primary로 지정하지 않음 |
| Color / Numeric Data / Linear | 04 Property 개요 | 4.5 입력, 6.8 출력 | 4.6 Decode, 6.6 HDR | 8.6/8.7 설정, 8.9 표시 | 입출력 transfer와 색공간 전체를 구분 |
| Normal Map / Decode / TBN | 2.14 소개 | 4.6, Basis 자체는 2.14 | 4.8 및 5.2 | 8의 N 입력 | raw RGB Decode와 Engine sampler 결과를 구분 |
| Material / Parameter / Instance | 4.1–4.2 | 4.7 | 4.8, 8.0/8.1 | 8.8 Region, 8.9 Debug, 8.10 MI | Static variant와 runtime 값 override 분리 |
| Reflection Vector / Phong / H | 5.1 | 5.3/5.5/5.6/5.7, 수식 보완 | 5.9 Microfacet, 7.3 스타일 | 8.4 | 상세 reflection 투영 유도를 없애기 전에 05의 기반 보완 |
| Roughness / D/G/F / BRDF | 4.2 Property | 5.9–5.14, 정의 5.17–5.19 보완 | 6 기여 평가, 7 스타일 | 8.4 비교, 8.5 Rim 대비 | BRDF≠Radiance, D≠정규분포/개수, G≠Scene Shadow |
| Fresnel / F0 | 5.14; F0 상세는 현재 8.5 | 5.14로 최소 F0/각도 설명 보완 | 7.5 목적 대비 | 8.5 Schlick 비교·Rim | F0 기반 이동 후 8.5 장문만 축약 |
| Rendering Equation / Light 기여 | 05 후반 예고 | 05 정의와 06.1 연결 보완 | 6.2–6.5, 8.3.6 | Base/Vis 예제 | 현재 “이미 배웠다”는 참조는 성립하지 않음 |
| HDR / Exposure / Tone Mapping | 6.4–6.8; Exposure 상세는 8.7 | 6.6–6.8에 Exposure 기본 보완 | 8.7 값과 화면 비교 | 8.7 테스트, 8.9 Debug | 출력 변환과 계산 범위 분리 |
| Camera Depth / Light Visibility | 1.10 | 1.10 Test/Write; 2.9 Depth 의미; 8.3 Shadow 상세 | 7.4 스타일 제어 | 8.3 MF_Shadow | Map·Sample·Compare·Visibility·기여를 구분 |
| Threshold / Smoothstep / Ramp | 7.2 사용 | 7.2 직전 최소 정의, 7.9 종합 | 7.4/7.5 | 8.5 Width/Softness | 이진화 후 Smoothstep으로 gradient 복원한다고 설명하지 않음 |
| Module / MF / Master composition | ASF-002, 8 Overview | ASF-002 규범; 8.1 교육; 8.10 최종 계약 | 각 8.x MF 추출 | 8.2–8.10 | Module은 책임, MF는 이 구현의 수단 |
| MatCap Lookup / Blend | 8.6 | 8.6 좌표→UV→Sample→Lerp | 8.7/8.10 합성 | MF_MatCap | IBL·Screen Reflection과 구분 |
| Emission / Emissive / Bloom | 4 Property, 6 출력 | 8.7 | 8.9 RGB 표시, 8.10 합성 | MF_Emission | 역할 구분 유지, Engine Emissive 영향은 별도 검증 |
| Region Mask / Parameter Blend | 4.3 Mask | 8.8 | 8.10 미통합 범위 | Specular Intensity 실습 | UE Material Layers로 확대하지 않음 |
| Debug / Validation | ASF-000; 8 각 단계 | 8.9 공유 데이터 선택 | 8.10 통합 검증, 9 진단 | MF_DebugView | 현재 최종 Mode와 타입을 단일 표로 고정 |
| Frame Time / Bottleneck / Tools | 1.12 비용 개요 | 9.1 측정, 9.2 Thread, 9.8 도구 | 9.3–9.7 적용, 9.9 절차 | 8.9 결과와 함께 진단 | 각 비용을 독립 가산 항으로 취급하지 않음 |
| LOD / Culling / Overdraw / Quad | 01 개요 | 9.7 / 9.4 / 9.8 | 9.3 Geometry, 9.5 Shader | 향후 측정 | Pass·coverage·작업 실행 조건을 유지 |

## 4. Cross-Chapter Duplication Map

| Concept | Appears In | Primary Source | Necessary Reinforcement | Unnecessary Duplication | Final Recommendation |
|---|---|---|---|---|---|
| 전체 Pipeline·좌표 흐름 | 1.2/1.13, 2.16, 6.9, 8.10 | 각 장의 종합 역할 | Overview→상세→합성→진단의 관점 변화 | 동일 요약 내 같은 목록·직렬 도식 반복 | Keep 종합, Shorten 내부 반복; 잘못된 순서는 Rewrite |
| Depth Test 절 | 1.10 | L4778 이후 완전본 | Camera/Light 관점 대비 | L4560–4774의 중복 시작·잘린 문장 | Merge 후 고유 내용 대조를 통과한 중복만 Remove |
| Position/Direction | 1.4, 2.2/2.8/2.13/2.16, 3.5 | 2.2 | w 의미와 Normal 예외 | Translation 정의의 장문 재시작 | Cross Reference + 예외 Keep |
| Perspective Divide | 2.6/2.8/2.9/2.16 | 2.9 | Clip w 소개, 마지막 경로 | x=2,w=2/10 계산과 Near/Far 경고 반복 | 2.9 수치 예제 유지, 2.8/2.16 Shorten |
| Normal Transform | 2.13/2.16, 3.5/3.7 | 3.5 | 2.13 데이터 종류, 3.7 Lighting 진단 | 동일 역전치 원리의 여러 유도 | Merge 주 설명, 각 소비 절 계약 Keep |
| Normalize / 같은 Space | 1.8, 2.15, 3.2/3.7, 8.2/8.4–8.6 | 3.2 + 02 | 보간 후 Normalize, 실제 잘못된 Space 테스트 | 정의·비유·동일 요약 | Shorten 재정의, 첫 Node 대응과 실패 사례 Keep |
| Normal / Material / Texture | 3.4, 4.2–4.8, 5.2, 8 | 3.4 / 4.1–4.7 | Normal Map·Basis 합류, 현재 Sample 소비 | 4.8 및 5.2에서 최초 정의 재시작 | Cross Reference, 4.8은 합류 흐름에 집중 |
| Color 처리 | 4.5, 6.8, 8.6/8.7/8.9 | 4.5 입력 / 6.8 출력 | Numeric Mask·HDR Color·Debug 표시의 다른 목적 | 동일 Import 표·밝기 비유 | 설정 표 주 설명 통합, 실제 조건 Keep |
| H / Roughness / DGF | 5.6–5.14, 6.4–6.5, 7.3 | 05 | H 생성→기여 Facet→D(H), Property→IBL | 성능 우위·역사·모델 목록 반복 | Necessary Reinforcement; 반복 목록 Shorten |
| Radiometry / BRDF 마무리 | 5.14 끝, 5.15–5.19 | 5.15 단위, 5.17–5.19 정의·적용 | 응답과 결과의 연결 | 비슷한 다음 단계 예고·정의 결론 | Merge 후 수식·단위 Expand; 빈 Status만 Remove |
| Toon 명암 / Shadow | 7.2/7.4, 8.3 | 7.2 방향 재구성 / 8.3 Visibility | Cast Shadow와 Shading Band 대비 | 구분 없이 같은 Threshold 설명 | 7.4 Keep, 원인·제어 대상 Rewrite |
| Shadow Mapping / Bias | 1.10, 8.3.4–8.3.6 | 8.3 | Light-space 비교·PCF·오류 원리 | Bias/Acne/Peter Panning 동일 예제, Map/Lightmap 비교 반복 | Merge 정확한 중복; PCF 기본과 수동값 검증 Keep |
| Fresnel / Rim | 5.14, 7.5, 8.5.4 | 5.14 보완 / Rim 8.5 | 물리 반사율과 표현 Mask 목적 대비 | 광학 기초 재설명 | F0 최소 기반 Move 후 Shorten, 목적 대비 Keep |
| MatCap 좌표 / Sample | 02/04, 8.6 | 02/04 + 8.6 적용 | View Normal, V Flip, Texture Object 계약 | World/View 정의·요약 반복 | 일반 기초 Cross Reference, 실제 UV 유도·오류 테스트 Keep |
| HDR / Emission / Mask | 06, 8.7 | 06 기반 + 8.7 적용 | Manual Exposure, Bloom 분리, UV→Sample R→Scalar | 같은 밝기/흰색·검정 설명과 여러 요약 | 기반 보완 후 Shorten; 샘플의 현재값 설명 Keep |
| MI / Region | 4.7, 8.0/8.8/8.10 | 4.7, Region 8.8 | Parameter 보간과 결과 보간의 차이 | MI 기본 정의·장점 재강의 | 정의 Shorten, A/B/Mask 테스트 Keep |
| Debug / Final Flow | 8.9 전반, 8.10 | 8.9 Mode표 / 8.10 계약 | Mode0 보존·공유 데이터·최종 통합 | 여러 Mode 목록·진단 예시·생산 원칙 | Merge 단일 계약; 기본 검증 Keep |
| 측정 순환·비용 예시 | 9.1/9.2/9.8/9.9, 9.3/9.7, 9.4/9.5 | 9.1 원칙 / 9.8 도구 | Thread, Pass, Coverage별 가설 적용 | 동일 LOD/Hair/측정 결론 반복 | Shorten 예시 복제; 질문→도구→한계→재측정 유지 |

## 5. Terminology Consistency Map

| Concept | Terms Currently Used | Preferred Term | Affected Chapters | Recommendation |
|---|---|---|---|---|
| 프로젝트 이름 | Anime Shader Framework; Figure Report의 Ari’s 및 이미지 보고된 임의 확장 | Anime Shader Framework (ASF) | 07/08/09 및 Figure Report 판단 | DEC-015 적용. Anime을 옛 이름으로 바꾸라는 권고 Rejected |
| Rendering 구조 | Stage, Module, MF, 전체 Pipeline | Pipeline Stage / Rendering Module / Material Function | 01/06/08/09 | 층위별 사용. MF는 Module의 구현 수단 |
| 최종 화면·응답 | BRDF, Reflected Light, Lighting Result | BRDF response / outgoing radiance / composed color | 05/06/08 | 출력 물리량과 타입을 명시 |
| 조명 데이터 | Lighting Data, 조명량, NdL | LightingData: clamped directional factor | 3.3/5.4/8.2/8.10 | 실제 Irradiance나 완성 Lighting으로 부르지 않음 |
| 빛 방향 | Incoming Light Direction, L, LightDirection | L=Surface→Light; propagation=-L | 03/05/08 | 실제 Engine Node의 부호는 Needs Technical Verification |
| V | View Direction, Visibility | V=View Direction; Vis 또는 ShadowVisibility | 03/05/8.3–8.10 | 벡터와 Scalar 기호 분리 |
| Texture 값 | Texture, Sample, RGB, Scalar | Texture resource / Texture Sample / sampled channel | 04/8.6–8.8 | 현재 UV에서 R을 취한 Scalar로 설명 |
| Normal 표현 | Normal, Normal Map RGB, Depth | Geometric/Shading Normal; encoded RGB; decoded direction | 02–05/8.6 | Normal Z를 위치 Depth로 부르지 않음 |
| Space | Local, Object, World Offset, View, Screen(NDC) | 해당 기준과 물리량을 함께 명시 | 02/8.6 | WorldPosition−ObjectPosition은 일반 Local Position이 아님 |
| Shadow | Shadow Map, Shadow Mask, Visibility | stored depth / sampled depth comparison / visibility mask | 01/07/8.3/8.10 | 저장 자원·판정 결과·합성 입력 분리 |
| Reflection | Specular, 환경 반사, IBL, MatCap | Reflection 상위; Specular/Diffuse response; environment contribution; MatCap Lookup | 05–08 | 6.5 범위를 환경 반사로 한정. MatCap=IBL 금지 |
| NDF | Normal Distribution, 정규분포, 확률·개수 | Normal Distribution Function: 방향 밀도 | 5.12 및 Figure Report | Gaussian 오역과 D=빛의 수를 채택하지 않음 |
| Mask / Result | EmissionMask, EmissionResult; Specular/Rim Color | Scalar Mask / Vector3 Result | 8.4–8.10 | Debug Mode5는 RGB EmissionResult |
| Layer | Material Layer, Region Mask, Material Slot | 이 실습은 Region Mask / Parameter selection | 8.8/8.10 | UE Material Layers 시스템과 구분 |
| 비용 | Geometry Cost, Pixel Cost, Shader Cost | 처리량·실행 빈도·실행당 비용이 겹치는 분석 관점 | 09 | 서로 독립적인 총비용 가산 항으로 쓰지 않음 |
| 겹침 | Overdraw, Quad Overdraw | repeated coverage/work / quad utilization-related diagnostic | 9.4/9.8 | Quad와 GPU wave, 출력 Pixel 수를 구분 |
| 제출 / 표시 | Section, Slot, Draw Call; Framebuffer/Render Target | 조건부 draw 관계; attachment와 저장 대상 구분 | 1.11/9.6 | Pass·batching 조건 및 Present 동기화 명시 |
| 세부 수준·가시성 | High/Low LOD, Culling | LOD index와 detail level을 명시; Pass-specific culling | 9.3/9.7 | Camera에서 안 보임≠모든 Pass에서 불필요 |
| Asset 표기 | MF_Lighting, MF_Matcap, Debug 등 | MF_BaseLighting, MF_MatCap, MF_DebugView | 8.7/8.9/8.10 | 001/002 기준 문서 표기 통일. 실제 Asset rename은 이번 범위 밖 |
| Character 분류 | Cloth | Outfit, 실제 섬유/천 의미는 Cloth | 01/09 및 응용 | DEC-001에 따라 의미별 교정 |
| 문서 표현 | English 장문, 음역 혼용, s, 내부 citation token | Korean 설명 + English Technical Term | 전반, 특히 9.8 | 용어 정렬 후 Minor Editing. 파일명의 기존 오타는 이번에 변경하지 않음 |

Naming은 ASF-001을 주 규칙으로 삼고 8.0에 새 규칙을 중복 정의하지 않는다. 역할 중심·full word·platform prefix와 8.0의 과도한 underscore 금지/영구 이름 선언 사이의 충돌은 예제 범위로 정리한다. 기존 자산명이 존재한다는 이유만으로 표준을 역으로 바꾸지 않는다.


## 6. Concept Boundary Issues

아래 L번호는 검토 시점 원본의 행 번호다. Chapter/Section을 우선 식별자로 사용하며 Phase 2에서 행 이동 후 다시 찾는다. “후속 원문에 이미 있다”는 경우 그 내용을 삭제하거나 새 누락으로 중복 등록하지 않는다.

### 6.1 Technical / Architecture conflict register

| ID / Severity | Location / Evidence | Boundary / Cause and Effect | Final Action / 완료 기준 |
|---|---|---|---|
| B01 / Critical | 5.17–5.19 L2958–3008, L3069 | BRDF를 반사된 빛으로 설명해 Material response와 Light transport 결과가 같아짐 | Rewrite / Expand. f_r=dL_o/dE_i, 단위 sr^-1의 응답과 L_o 구분; 입사광·cosine·적분/합산 후 결과라는 계약 |
| B02 / High | 5.4, 5.19; 5.15 L2653 | max(N·L,0)은 각도 계수이며 Lambert BRDF 자체가 아님. Flux를 에너지로 설명하면 Power와 혼동 | Rewrite / Expand. f_r=ρ/π와 각도 항을 분리. Flux[W], Radiance/Irradiance/Intensity의 의미·단위를 최소 표로 보완 |
| B03 / Critical | 6.9 L832–890, 6.1; 4.8 | Direct/Indirect→IBL/Reflection→BRDF→HDR을 고정 Stage처럼 직렬화 | Rewrite. BRDF는 각 기여 평가에 쓰이고 HDR은 계산 값 표현 범위. 독립 입력→기여 합류→표시 변환만 데이터 의존으로 표시 |
| B04 / High | 6.2 L170, 6.3 L290, 6.4–6.5 | 환경 표현과 bounce 분류 혼합; 부드러운 Shadow를 Indirect가 만드는 것으로 설명 | Rewrite. 경로 기반 Direct/Indirect와 Environment/IBL 기법을 구분. Penumbra의 광원 크기와 Indirect fill을 분리 |
| B05 / High | 1.10 L5050/5338; 1.11 L5369/5385/5643 | Shadow Map=판정; Shader가 항상 Depth를 출력 | Rewrite. raster depth→test/write와 선택적 Shader depth override 구분. Map은 저장 자원, Compare 결과가 Visibility |
| B06 / High | 2.6 L4086, 2.8 L5675 vs 2.9의 같은 offset 조건 | 같은 Camera ray와 같은 X/Y offset은 다름 | Rewrite. 같은 ray는 같은 투영 위치, 같은 횡방향 offset·다른 View Depth 예시는 중심 접근. 2.9의 올바른 조건을 보존 |
| B07 / High | 2.7 L4743, 2.11 L8757/8832, 2.12 L9929/9963/9970 | Clip 고정 cube/NDC 혼동; 적용 순서와 Matrix 곱·storage 혼동 | Rewrite. homogeneous inequalities와 NDC 분리. 열벡터 예시라면 P·V·M·p, T·R·S의 적용 방향 명시; memory layout과 별개 |
| B08 / High | 2.15 L13185–13244; 3.5 | WorldPosition−ObjectPosition만으로 Object rotation/scale을 따른 Local 좌표가 되지 않음 | Rewrite. World offset과 inverse object transform 구분. Normal Matrix에는 선형 3×3·역행렬 존재 조건, Translation 제외 명시 |
| B09 / High | 3.2 L166, 3.3 L349/377/389; 5.3 L340/366; 8.2 L103/113 | 영벡터 Normalize, Unit dot 범위, 입사 진행 방향과 L 부호가 혼재 | Expand / Rewrite. N/L/V 계약 고정. signed dot와 saturate 결과를 구분; 입력 실패 처리 정책 명시 |
| B10 / Medium | 3.4/3.5, 5.2 L197 | 모든 Shading Normal이 Geometry에 수직·유일하다는 설명 | Rewrite. 3.4 L475–483의 Artist Normal과 Geometry 분리를 기준으로 ±방향·orientation·winding 조건 보완 |
| B11 / High | 4.4 L907, 4.6, 2.14 | UV는 항상 Mesh에서 온다는 일반화; RGB×2−1을 Engine decode 뒤 반복할 위험 | Rewrite / Needs Technical Verification. procedural/View Normal UV 허용. raw encoded RGB와 sampler-decoded Normal 상태를 명시 |
| B12 / High | 4.7 L2071 vs L2130/2166, 4.8 L2613 | 모든 Instance가 동일 Shader이고 모든 Parameter가 runtime 구조 불변이라는 일반화 | Rewrite. Static Switch variant/compile과 runtime 값 override 구분; 9.5의 static/dynamic 구분으로 연결 |
| B13 / High | 4.5, 6.8 L777/787/820 | Linear transfer와 전체 Color Space, 입력 decode와 출력 encode를 혼합 | Rewrite. 입력·연산·출력 경계를 분리. Numeric 0.5에 잘못된 sRGB decode가 적용되는 변화 방향을 일관되게 설명 |
| B14 / High | 5.6 L945 vs 5.9, 5.7–5.12 | 모든 Facet Normal=H; macro Normal 하나면 전체가 매끈함; D=확률/개수 | Rewrite. H에 해당하는 Facet의 기여와 통계 분포 구분. Surface normal field와 subpixel roughness 별개 |
| B15 / Medium | 5.13, 7.4, 8.3 | Microfacet G와 Scene Shadow Visibility, Toon 명암과 Cast Shadow | Keep 구분 + Rewrite 혼용. G는 미시적 masking/shadowing, Scene Vis는 광경로 차폐; 둘의 역할을 한 문장으로 연결 |
| B16 / High | 7.1–7.5; 7.3 L295 vs 8.4 | PBR/NPR 이분법, PBR=soft Shadow, ASF가 PBR Specular를 유지한다는 구현 과장 | Rewrite. 물리 제약과 미술 목표는 독립 축. 현재 8.4는 교육용 Phong response이며 완성 Cook-Torrance 구현이 아님 |
| B17 / High | 7.5 L489–505 vs 8.5 L1226–1391 | Rim=Fresnel로 축약했으나 뒤에서는 목적 차이를 올바르게 구분 | Rewrite 7.5; Keep 8.5 대비. 반사율이 크다고 조명 없이 항상 밝아지는 것은 아님 |
| B18 / Medium | 7.8, 7.9 | Normal Expansion/Inverted Hull과 Edge Detection/Screen Space를 독립 네 기술로 나열 | Rewrite 분류. Geometry 방식과 Screen Space 방식 아래 구현/연산을 배치; Outline Pass≠Module |
| B19 / Critical | 8.1 L169, 8.10 L80–104/169/4080/4495 | Master=전체 GPU Pipeline; 모든 MF가 앞 함수의 결과를 순차 소비 | Rewrite. ASF-002 책임 경계와 6.2 아래 canonical contract 사용 |
| B20 / High | 8.2 L830 및 8.10 L1108/1771 | Base Lighting 입력 개수 변화, LightingData+BaseColor로 표시 | Rewrite. N/L/BaseColor의 세 입력, Scalar D와 RGB B의 두 출력. B=BaseColor×D |
| B21 / Critical | 8.4 L1156/1198/1269 vs L1374–1410/1526–1534 | Phong response를 Material Specular pin에 넣는 설명과 최종 Unlit 외부 합성이 혼재 | Rewrite / Needs Technical Verification. 중간 관찰 단계인지 명시하거나 최종 경로로 정렬. pin이 엔진 반사 모델을 교체한다는 해석 금지 |
| B22 / High | 8.3 L5114–5145; 8.5 L2836; 8.6 L4381/4863/5147; 8.9 L815; 8.10 L587/1132/3791 | 수동 ShadowVisibility를 실제 Renderer Shadow 데이터처럼 읽히게 하는 후속 완료 표현 | Rewrite. 취득은 미통합, 소비 연산만 구현. 8.3 per-light 원리와 실제 Base-only Vis 적용 범위 구분 |
| B23 / High | 8.5 L2054 및 최종 Width/Softness | Smoothstep edge 순서·Softness=0·Max>1·Width=0 의미가 계약에 없음 | Expand. 유효 범위와 비활성화 정의, 불법 입력 처리, 최대 Mask 도달 여부를 명시. API 동작은 검증 필요 |
| B24 / Medium | 8.5 L1888 vs L2248/3351 | 계산된 Mask 영역과 화면에서 느끼는 Width를 혼동 | Keep 지각/계산 구분; Rewrite 이진화하면 모든 조건에서 Width와 밝기가 완전 독립이라는 주장. Tone Mapping/Bloom 영향 존재 |
| B25 / High | 8.6 L1191/1375/1804, 8.7 L5224 | Camera translation과 rotation 혼동; Normal Z=Depth; MatCap=ViewDirection | Rewrite. 방향에는 camera orientation 변환; 위치/깊이와 별개. View Normal XY Lookup의 approximation 범위 명시 |
| B26 / High | 8.6 L4869 이후, 8.7 L62/4802, 8.10 L784/2060/3938 | MatCap Lerp를 Add로 요약 | Rewrite. Alpha=1이면 기존 합성 A가 제거됨. Intensity=0은 Blend가 남으면 완전 off와 다름; off는 Blend=0 |
| B27 / Medium | 8.7 L132/351/5561 | Emission 모듈과 Emissive output 역할 구분을 “앞선 결과는 Emissive가 아님”으로 절대화 | Rewrite / Needs Technical Verification. 논리적 기여와 Engine 출력 의미를 구분; 전체 Emissive 출력의 Bloom/GI 영향은 설정 의존 |
| B28 / High | 8.8 L573/664/1333 vs L924/1265 | Region Intensity가 MF_Specular 입력이라는 설명 | Rewrite. 실제는 SpecularMask×선택 Intensity를 외부 합성. Parameter Lerp와 nonlinear Shader 결과 Lerp는 다름 |
| B29 / High | 8.9 L988–1337 vs L712/880/1420 이후 | Mode5=EmissionMask Scalar와 최종 EmissionResult RGB 충돌 | Rewrite. 6.2 계약으로 통일. Local08의 ShadowVisibility 포함·MatCap 누락 종합표도 Rejected |
| B30 / High | 8.9 L2470; 8.7 L1210/5137; 8.10 L4121 | Emissive 화면이 raw 값 또는 완료 검증이라는 주장 | Rewrite. Material Unlit≠Viewport Unlit; 노출/표시 변환 영향. 관찰된 결과·설정 확인·수치 검증·동작 검증을 구분 |
| B31 / High | 9.1–9.2, 9.8 | 가장 긴 표시 시간만으로 확정 병목, GPU 감소량=Frame 감소량 | Rewrite. Wait/VSync/Cap·internal resolution·warmup·build 조건 확인, Frame overlap/latency/throughput 구분 |
| B32 / High | 9.3 L1451/1847, 9.4, 9.5 | Vertex는 항상 부차적, Geometry/Pixel/Shader 비용을 서로 독립 가산 | Rewrite. Skinning/Attribute/Pass·coverage·실행당 비용 등 영향 경로를 명시. Triangle 수 단독 원인 단정 금지 |
| B33 / High | 9.4 Hair, 9.6 L4689 | Masked와 Translucent를 같은 투명 처리로 설명 | Expand 최소 경계. Depth Write/Sorting/early rejection/Pass가 다를 수 있음; 실제 동작은 Engine 검증 |
| B34 / High | 9.5 L3436, L3720; 9.6 L4212 | Lerp 입출력 방향 반대, fullscreen 2–3 Triangle, CPU가 모든 Draw 결정이라는 보편화 | Rewrite. A/B/Alpha→Lerp→Result; fullscreen triangle 1개 또는 quad 2개. CPU-driven 예시로 한정, GPU-driven 예외 검증 |
| B35 / High | 9.7 L5332/5665–5703/6288–6319 | Camera에 안 보이면 기여 없음; LOD와 Culling 동시 변경 후 원인 확정 | Rewrite. Shadow/Reflection/GI 등 Pass별 기여. 한 변수 검증과 여러 항목을 끄는 탐색 probe 구분 |
| B36 / Medium | 9.8 L7015 등 | Quad Overdraw를 단순 레이어 수/출력 pixel 수로 축약 | Keep 작은 Triangle 설명, Expand 2×2 quad/helper 개념. quad≠wave, helper≠최종 출력 |
| B37 / Low | 1.5 L1919–1932, 2.6 L3657/2.7 L4608 | 원문 ASCII Index 대각선 및 Near/Far 폭이 설명과 불일치 | Rewrite 원문 도형 후보. 이미지 재검토와 별개로 수치·도형 대응 필요 |
| B38 / Low | 3.4 L581/3.5 L818, 8.4 L1718, 8.9 L3504, 9.6 L4160 | 잘못된 다음 절, 하지 않은 Threshold/Smoothstep 완료 요약, 고립 s, 편집 안내 | Cross Reference / Rewrite / Remove. 의미 수정 뒤 편집 |

### 6.2 Chapter 08 canonical data contract

이 계약은 원문에서 확인한 **최종 교육용 구현을 일관되게 설명하기 위한 기준**이다. 전체 물리 기반 Renderer의 식이 아니다. 같은 Space의 유효한 N/L/V와 각 함수의 Unit 입력 조건을 선언한다. Zero vector, Shininess, Width/Softness, Blend의 유효 범위는 기본 검증 항목이다.

```text
D = saturate(dot(normalize(N), normalize(L)))
B = BaseColor * D
ShadowedBase = B * Vis

SpecularColorResult = SpecularMask * SpecularColor * SpecularIntensity
RimColorResult      = RimMask * RimColor * RimIntensity
A = ShadowedBase + SpecularColorResult + RimColorResult

MatCapContribution = MatCapResult * MatCapIntensity
F = lerp(A, MatCapContribution, MatCapBlend) + EmissionResult
DebugColor = select(DebugMode, F, D, SpecularMask, RimMask,
                    MatCapResult, EmissionResult)
Final Material output = DebugColor through the documented Unlit/Emissive path
```

| Module / 구현 수단 | 입력 계약 | 출력 계약 | 책임 / 현재 제한 |
|---|---|---|---|
| Base Lighting / MF_BaseLighting | N Vector3, L Vector3, BaseColor Vector3 | LightingData Scalar D, LightingResult Vector3 B | 방향 기반 기초 조명. Light intensity/attenuation/Indirect를 모두 구현한 결과가 아님 |
| Shadow / MF_Shadow | LightingResult Vector3, ShadowVisibility Scalar | Shadowed LightingResult Vector3 | 곱셈 소비. Renderer에서 실제 Vis를 얻는 기능은 아직 없음 |
| Specular / MF_Specular | N, L, V Vector3; Shininess Scalar | SpecularMask Scalar | Phong response. Color/Intensity는 외부; clamp가 최종 코드에 이미 있음 |
| Rim / MF_RimLight | 같은 Space Unit N/V, 최종 Width/Softness 계약 | RimMask Scalar | 초기 Power 실습과 최종 재설계를 분리. Color/Intensity는 외부 |
| MatCap / MF_MatCap | World Normal Vector3, Texture Object | MatCapResult Vector3 | View transform→Normalize/XY remap→해당 규약의 V Flip→Sample. 외부 Lerp |
| Emission / MF_Emission | sampled EmissionMask Scalar, Color Vector3, Intensity Scalar | EmissionResult Vector3 | 이 함수 내부에서 Color/Intensity 곱셈하는 것은 책임상 허용됨 |
| Region 실습 | sampled RegionMask, A/B intensity | selected intensity Scalar | MF_Specular의 출력에 외부 곱. 최종 Master 미통합 상태를 유지해 설명 |
| Debug / MF_DebugView | DebugMode + F, D, SpecularMask, RimMask, MatCapResult, EmissionResult | DebugColor Vector3 | 기존 결과를 선택. ShadowVisibility·RegionMask는 현재 Debug 입력에서 제외 |

Debug Mode: 0=Final F, 1=Base Lighting D, 2=SpecularMask, 3=RimMask, 4=MatCapResult, 5=EmissionResult. 현재 If 체인의 그 밖 값도 EmissionResult로 fallback한다. 8.9 L1882–1916의 fallback 설명과 L2393–2402의 정수 사용 안내는 이미 있으므로 “누락”으로 쓰지 않는다. 슬라이더 안내가 정수 입력 강제나 If equality threshold를 보장하는지는 별도 검증한다.

SpecularMask/RimMask의 Unit 계약을 전체 함수에서 통일하고, 선택된 Scalar를 RGB로 표시하는 규칙을 명시한다. 회색으로 보인다는 사실만으로 타입 변환의 정확성이 입증되지 않는다. Dynamic DebugMode=0은 Debug 계산의 compile-time 제거를 보장하지 않는다. 8.9 후반과 9.5에 이미 있는 성능 주의를 유지한다.

MatCapBlend는 현재 Constant 또는 MI에 노출하는 선택 사항이다. 8.10의 Parameter 표에서 “누락된 필수 MI Parameter”로 판정하지 않고 **현재 Constant/선택 노출/필수 입력**을 구분하도록 수정한다. Blend=1에서 A가 사라지는 것은 정의된 결과이며 “기존 결과가 절대 덮이지 않아야 한다”는 체크리스트를 적용하지 않는다.

Vis는 해당 Light의 기여에 적용하는 원리가 8.3에 이미 있다. 현재 최종 예제는 Base만 Vis로 조절하고 Specular/Rim에는 곱하지 않는다. 이것을 모든 반사 항에 Scene Shadow가 적용된 상태로 설명해서는 안 된다. 스타일 정책으로 유지할지 향후 per-light direct Specular까지 확장할지는 Phase 2에서 명시할 설계 결정이며, 이번 Audit가 새 Renderer를 요구하는 것은 아니다.

### 6.3 Needs Technical Verification register

로컬 원문만으로 확정하지 못하는 플랫폼/성능 주장은 아래에 모았다. 오류가 명확한 수식·계약 문제와 구분한다. 외부 문서 검색·UE 실행·Shader compilation·벤치마크를 수행하지 않았으며, 검증 완료로 표시하지 않는다.

| ID | Current Location | 확인할 구체 조건 / 완료 증거 |
|---|---|---|
| TV01 | 8.0 환경, 8.2 L627/643/903, 8.10 L508–522 | 지정 UE5.8/Deferred/RHI와 Forward 계열 selected Directional Light 입력의 지원 경로, output meaning/Space/sign, Light 없음·여러 개일 때 선택. 실제 대상 설정 및 Node 결과 |
| TV02 | 2.15, 4.6, 8.6 | ObjectPosition의 bounds/pivot 의미, PixelNormalWS의 단계별 값, CameraVector의 projection 조건, ScreenPosition mode, Normal sampler decode/채널 convention. 정확한 Node·출력·설정 |
| TV03 | 4.5/4.6, 6.8, 8.6 L3260 | sRGB decode/filter 순서, compression/normal reconstruction, HDR MatCap encoding. sRGB Off가 모든 변환·손실을 없애는 것은 아님 |
| TV04 | 8.4 Specular pin, 8.2/8.5/8.7 output | 대상 Material Domain/Shading Model의 Specular pin 의미, Unlit+Emissive 출력, Bloom/GI 영향. 초기 관찰과 최종 합성 분리 |
| TV05 | 8.3 L4570 및 관찰 절 | 실제 Depth/Shadow Debug Mode, 범례, Shadow method/Mobility, resolution/bias/filtering 변경의 통제 증거 |
| TV06 | 8.5 Smoothstep, 8.9 If, 8.10 타입 안내 | equal edges 처리, If equality threshold/implicit conversion, 최종 컴파일 타입·지원 범위. 같은 설정의 작은 입력 테스트 |
| TV07 | 8.7 L2159/2420/2735/3289/5137 | effective Metering Mode/Override, Compensation과 adaptation 관계, camera exposure, tone mapping 적용. 관찰되지 않은 ToneMapper 영향은 미검증 유지 |
| TV08 | 1.11 Present, 9.1/9.2/9.6/9.7 | buffer swap과 sync, Thread/RHI/Queue, GPU-driven draw, Pass별 culling. 구현 범위를 일반 법칙처럼 확장하지 않음 |
| TV09 | 9.8, 특히 L6530–7442 | 실제 stat/ProfileGPU/ViewMode 명령·도구 차이·범례·capture 조건. 내부 citation token 11곳을 확인 가능한 출처로 교체 |
| TV10 | 5.7–5.12, 7.6, 9.3–9.6 | Phong/Blinn 비용 비교, 역사 연대, GGX 우월성, Hair 모델 계보, 비용 효과의 플랫폼 조건. DEC-013 학습 순서를 역사적 입증으로 사용하지 않음 |
| TV11 | 2.6 FOV 설명, 3.6 V | 같은 framing/Camera 위치에서 FOV 효과, orthographic View Direction 예외. 조건 없는 시각 인과를 제한 |

## 7. Missing / Weak Concept Map

전체 원문을 확인한 결과 실제 사용에 필요한 최소 설명만 보완한다. 없는 Production 기술을 Foundation의 결함으로 추가하지 않는다.

| ID / Severity | Concept / Current Location | 부족한 연결 | 필요한 최소 보완 / Action |
|---|---|---|---|
| W01 / High | BRDF / 5.15–5.19→6.1→8.3 | 응답 단위와 입사광에서 결과까지의 연결 | Expand: BRDF 정의·단위, Lambert ρ/π, L_o=L_e+∫f_r L_i max(N·ω_i,0)dω_i의 개념 계약. Vis를 별도 쓰면 L_i가 unoccluded인지 선언해 이중 차폐를 피함 |
| W02 / High | 5.5–5.10→8.4 | Phong/H/Blinn 및 microfacet 설명이 결론 중심 | Expand: unit 입력·clamped dot·exponent, H=normalize(L+V)와 L+V=0 예외, f_spec=DGF/[4(N·L)(N·V)]의 positive hemisphere 조건. GGX/Smith 전체 유도는 요구하지 않음 |
| W03 / High | 4.2→5.14→8.5 | Metallic BaseColor와 F0의 연결; F0 첫 상세가 8.5 | Expand/Move 최소 기반: dielectric/metal의 Diffuse와 Specular 색 역할, F0와 grazing 반사율, microfacet 각도. IOR/SSS 전체 구현은 추가하지 않음 |
| W04 / Medium | 3.2–3.5 | Normalize와 Cross의 유효 조건 및 성분 계산 | Expand: dot 성분식 한 줄, 영벡터 정책, edge order/winding/degenerate Triangle, inverse transpose의 선형부·invertible 조건 |
| W05 / Medium | 2.11–2.12, 2.5 L3231 예고 | convention을 말하지만 실제 계산 예가 약함 | Expand: 하나의 작은 Transform 수치 예제로 Position/Direction 차이, 적용 순서, Camera inverse를 확인. 별도 Matrix 교재 불필요 |
| W06 / High | 1.9/1.11/1.13의 06 Deferred/GBuffer 예고 | 06에 실제 설명 없음. 9.8의 짧은 GBuffer 언급으로 충족되지 않음 | Expand: 06에 Forward/Deferred의 최소 저장·소비 차이 및 Material/Lighting 경계. 선택한 UE 경로 상세는 TV01 |
| W07 / Medium | 02 L3697/7252의 09 Depth Precision/Reversed-Z 예고 | 09에 해당 상세가 없음 | Modified scope: 2.9에 near/far와 projected depth precision의 최소 주의, 8.3 bias로 연결. Reversed-Z 상세는 후속 범위로 예고 교정 또는 실제 근거를 갖춘 최소 설명 |
| W08 / Low | 01의 09 Interpolator·Early-Z 예고 | 09가 Interpolator 비용을 전개하지 않고 Early-Z는 짧은 주의만 제공 | Cross Reference: 실제 제공 범위로 안내 축소; 새로운 성능 Case Study를 만들지 않음 |
| W09 / Medium | 7.2/7.9 | Threshold/Ramp 사용 후 늦은 공통 정의 | Move 최소 정의만 7.2 전에. 7.9는 기능 간 공통 구조를 종합하며 Smoothstep=AA 보장이라는 단정 제거 |
| W10 / High | 7.3/7.5/7.7→08 | PBR Specular·IOR·SSS의 후속 구현 예고가 현재 08에서 충족되지 않음 | Rewrite: 실제 Phong·Rim·Mask·Lookup 구현 범위를 명시. 후속 계획과 현재 완료를 구분 |
| W11 / High | 6.6–6.8→8.7→8.9 | Exposure 기본이 너무 늦고 Debug의 수치/화면 관계가 약함 | Move/Expand: 06에 Exposure gain·Tone Mapping·출력 변환의 역할 한 단락. 8.7 Manual 테스트와 8.9 정성/정량 구분은 그대로 Keep |
| W12 / Medium | 8.6 View Normal UV | Perspective view ray와 fixed camera basis approximation, unit disk/back hemisphere·edge sampling 조건 약함 | Expand: 구현 가정과 axis/UV convention 표, Texture 방향 marker 및 sampler 경계 조건. 새 MatCap 알고리즘 전체는 요구하지 않음 |
| W13 / High | 8.10 최종 완료·08 전반 관찰 | 인터페이스 구현·연결·시각 관찰·값 검증·Renderer 통합이 같은 완료로 읽힘 | Expand: 기능별 현재 지원/미구현 표 및 기본 테스트 기대값. Vis1/.5/0, Blend0/1, EmissionMask0/1, Debug0–5, 잘못된 입력 처리 |
| W14 / Medium | 9.1/9.8 | 질문→도구 표는 있지만 재현 가능한 최소 측정 사례가 약함 | Expand: Scene/Camera/해상도·노출·build·warmup·cap 상태, ms baseline, 한 변수 변경, 관찰과 제한을 담은 짧은 예시. 실측 없이 수치 결과를 만들어 쓰지 않음 |
| W15 / High | 9.4/9.6/9.7 | Masked/Translucent와 Pass-specific visibility가 약함 | Expand 최소 범주 설명 후 실제 Engine 동작 TV08/09. Hair off·Camera movement는 복합 영향 탐색이라는 범위 표시 |

다음은 **전체 누락으로 판정하지 않는다**: 2.10 Pixel Center/경계, 2.13 Normal 예외, 3.4 Artist Normal, 4.4 Filtering, 8.3 PCF의 compare-then-average와 per-light Vis, 8.4 최종 saturate, 8.5 Rim/Fresnel 대비, 8.6 V Flip, 8.7 UV Sample Scalar, 8.8 독립 실습 경계, 8.9 fallback/정수 안내/Debug 비용, 9.2 RHI·overlap, 9.8 질문별 도구 및 작은 Triangle의 Quad 문제. 필요한 것은 연결과 일관성 보완이며 이미 있는 설명을 또 추가하는 것이 아니다.


## 8. Foundation / Advanced Boundary

단순히 한 변수만 바꾸는 기초 확인도 재현 조건을 갖춰야 한다. 이것을 이유로 모든 Basic Verification을 Controlled Experiment로 분류하지 않는다. ASF-000과 사용자 지시에 따라 원리·데이터·기본 구현·기본 검증·기본 측정은 Foundation에 남긴다.

| Content | Current Location | Final Decision | Reason |
|---|---|---|---|
| Attribute·Space·Normal·기초 수학 | 01–03 | Keep / 필요한 계산 Expand | 모든 후속 Shader 입력의 기반. Ch03 역할표 충돌로 내용을 이동할 이유 없음 |
| Sampling·Color/Data·MI | 04 | Keep | 현재 Pixel 의미와 재사용 architecture. UI 예시 자체는 이동 근거가 아님 |
| BRDF 최소 수식·DGF·단위·F0 | 05, 일부 현재 8.5 | Keep / Expand / 최소 기반 Move to 05 | 구현 전에 이해할 원리. 상세 분포 유도와 수치 적분 구현은 별도 심화 |
| Direct/Indirect·IBL·HDR·Exposure | 06, Exposure 상세 8.7 | Keep / 최소 기반 Move to 06 | 계산 결과와 화면 차이를 읽는 데 필요 |
| Toon·Rim·Hair·Face·Outline 개요 | 07 | Keep | 표현 목표·입력·출력·기존 기반과 차이를 이해하는 사례 |
| 상세 Face SDF·Fiber scattering·Outline Pass 제작 | 7.6–7.8 후속 예고 | 미래 상세 구현은 Advanced; 현재 짧은 연결 Keep | 현재 완료된 복잡한 구현 블록이 있는 것은 아님 |
| 프로젝트 생성·폴더·Git·환경 기록 | 8.0 | Keep / 반복 Shorten | 첫 구현 재현에 필요한 준비 |
| MF Input/Output·Node 대응·Unit 계약 | 8.2–8.7 | Keep Detailed | Concept→Data Flow→구현 연결의 핵심 |
| Shadow Depth/Visibility·PCF·Bias | 8.3 | Keep / 같은 Bias 예제 Merge | 01의 개요만으로 대체 불가. 첫 상세 설명이며 Scalar 입력 의미를 준비 |
| Renderer Shadow 취득·Custom Renderer 구현 | 8.3/8.10 미구현 경계 | 한계 설명 Keep; 실제 심화 구현은 Advanced | 수동 Vis 실습의 설명 책임과 Renderer 제작을 분리 |
| Rim Width/Softness·MatCap UV·Emission/Bloom | 8.5–8.7 | Keep | 기본 제어를 수치와 화면으로 확인하는 구현 |
| UV Sample→Scalar·Region A/B 선택 | 8.7–8.8 | Keep Detailed | Texture 전체와 현재 값, Parameter와 출력의 경계를 검증 |
| Unlit·고정 조건·0/.5/1·Mode0–5 | 8.2–8.10 | Keep | 기능의 예상 결과를 확인하는 Basic Verification |
| MI·Debug·합성·Built-in/Custom 선택 이유 | 8.9–8.10 | Keep / 반복 Shorten | 재사용·분리 진단의 원칙. Custom HLSL이 자동으로 renderer data 접근을 해결하지 않음 |
| 실제 생성 Shader 분석·플랫폼 성능 Case Study | 8.9/8.10의 후속 주의 | 일반 주의 Keep, 향후 상세 실행 Advanced | 현재 완성된 실험 결과가 존재한다고 판정하지 않음 |
| 대규모 Character Variation·자동화·Production Layer | 8.8/8.10의 확장 방향 | 짧은 연결 Keep, 실제 구축 Advanced | 기본 Region 실습과 규모·유지보수 책임이 다름 |
| ms·baseline·Thread·비용·도구별 질문 | 9.1–9.8 | Keep / 최소 측정 예시 Expand | 구현을 진단하는 마지막 Foundation 역할 |
| Hair off·Resolution·LOD 기본 probe | 9.4–9.8 | Keep | 원인 후보를 좁히는 기초 적용. 단일 원인 증명으로 과장하지 않음 |
| Test Matrix / Before–After / Portfolio 설계 | 9.9 L8432–8561 | 현재 예고 목록은 Shorten + Keep; 미래 상세 계획/사례 Advanced | 실제 원문은 개요·목록이며 이동할 완성된 실측 프로토콜은 없음 |
| Target Hardware·Build·warmup 조건 | 9.8 및 보완 9.1 | Keep | 측정 한계를 알기 위한 기초. 실험이 심화여도 조건 인지는 필수 |

## 9. Local Audit Revalidation

네 Local Report를 모두 읽고 원문의 앞뒤 사용처까지 확인했다. 아래 표는 Shorten/Merge/Move/Remove 및 같은 의미의 Condense 후보를 개별 재판정한 기록이다. 한 Local 항목에 서로 다른 변경이 있으면 분리했다. 반복 요약·계획표에 재기재된 같은 후보는 동일 행을 참조한다.

Confirmed=제안의 방향·범위를 확인, Modified=범위·주 설명 위치·선행 조건 수정, Rejected=그대로 적용하지 않음, Necessary Reinforcement=새 맥락의 설명을 유지. 어떤 판정도 이번에 원문을 수정했다는 뜻은 아니다.

### 9.1 Foundation_Audit_01-03.md

| Original Local Recommendation | Location | Global Decision | Reason / Final Global Action |
|---|---|---|---|
| G01: Chapter03 역할 충돌에 따른 Move/Merge | Local L45–53; 실제 1.3/3.4→5/8 | Rejected | Ch03 Lighting Mathematics는 05/08의 필수 선행. 오래된 Roadmap 역할을 따르는 전체 재구성은 불필요; 1.3+3.4의 Surface 연결 보완 |
| G02: 개념별 Shorten/Merge | Local L55–63; 01–03 전반 | Modified | 정의를 줄일지 적용을 남길지 개념별 분리. 본 보고서 3–4절의 Primary와 Reinforcement 기준 적용 |
| C1-01: 중복 1.10 Merge/Remove | 원문 L4560–4774, L4778 이후 | Confirmed | 완전본에 고유 내용이 포함됨을 대조한 뒤 미완성 중복만 제거. Depth/Camera-Light 대비는 보존 |
| C1-06: 전체 요약·같은 UV 예시 축약 | 1.2/1.13 및 동일 예시 재시작 | Confirmed | Overview/종합 역할은 남기고 내부 정의·예시 반복만 Shorten |
| C1-07: 잔여 s Remove | 01 편집 흔적 | Confirmed | 의미 없는 잔여 문자만 제거. 파일 삭제와 무관 |
| C1-07: 파일명 오타 정리 연계 | Chapter01 파일명 | Modified | 현재 경로 참조 영향이 크므로 이번/본문 축약의 부수 작업으로 rename 금지. 향후 별도 참조 일괄 점검 대상 |
| C2-10: Space 예제·전체 흐름 Merge/Shorten | 2.3/2.4/2.8/2.9/2.16 | Confirmed | 2.9의 정확한 Divide 예제·2.16 Position/Direction 분기 유지, 같은 기초 재시작만 축약 |
| C3-05: Same Space 장문 축약 | 3.7과 2.13–2.16 | Necessary Reinforcement | 3.7은 N/L/V가 만나는 실제 Lighting 오류 진단. 정의 목록은 줄여도 전체 절 이동/삭제 불가 |
| Duplication Map: Attribute Primary를 새 Ch03으로 | Local L396; 1.3/1.5/1.8/3.4 | Modified | Primary 1.3 유지. Index 소비·Interpolation·Shading 방향은 각 위치의 새 역할 |
| Geometry/Shading Normal 반복 참조 | Local L397; 1.8/2.13/3.4–3.5 | Necessary Reinforcement | Geometry가 같아도 shading이 다름을 뒤의 Normal Map·Rim까지 연결해야 함 |
| Position/Direction 정의 재시작 Shorten | Local L398; 2.2/2.8/2.13/3.5 | Confirmed | 주 정의 2.2, w 2.8; Normal 예외를 일반 Direction과 합치지 않음 |
| Normal Transform Primary=2.13, 3.5 축약 | Local L399 | Modified | full mathematical explanation은 3.5에 둔다. 2.13은 변환 종류와 예외 소개, 3.7 적용 진단 |
| 보간 후 Normalize 참조 | Local L400; 1.8/3.2/3.4/3.5 | Necessary Reinforcement | 1.8 발생 원인, 3.2 연산, 3.4/3.5 실제 Normal 준비는 다른 역할 |
| Same Space 목록 반복 축약 | Local L401 | Confirmed | 목록 복제만 Shorten; 회전·잘못된 Space의 오류 증상 Keep |
| Surface Position→L/V 재유도 축약 | Local L402; 3.1/3.6/3.7 | Confirmed | 3.6에 생성 원리. 3.1 입력 개요와 3.7 완성 계약은 유지 |
| Depth/Screen/Visibility Merge 회피 | Local L403 | Necessary Reinforcement | 값의 의미 02, Test/Write 1.10, Output 1.11을 통째로 합치면 처리 경계 소실 |
| 1.13/2.16 요약 내부 반복 축약 | Local L404 | Confirmed | 장별 종합은 필요. 정의·동일 flow 반복만 정리 |
| Tangent/UV Seam의 설명 책임 조정 | Local 구조·약한 개념 제안 | Modified | Basis는 2.14, Vertex split은 1.3, 비용은 9.3. 새 Ch03 전체 이동으로 해결하지 않음 |
| G05 및 Advanced 범위: 기초 검증 보완 | Local L85–99; 1.12/2.15 | Modified | Local 범위의 검증 제약을 Global에 확대하지 않는다. 8의 Basic Implementation/Verification과 9의 기초 Profiling Keep |

### 9.2 Foundation_Audit_04-06.md

| Original Local Recommendation | Location | Global Decision | Reason / Final Global Action |
|---|---|---|---|
| G01: 05/06의 역할을 계획에 맞게 Move/Merge | Local L45–53; 05 DGF, 06 Direct/Indirect | Rejected | Accepted DEC-014 및 현재 07/08의 전제를 기준으로 05 Reflection/BRDF→06 Modern Realtime 유지 |
| G04: 반복 주 설명 Merge/Shorten | Local L75–83 | Modified | 분량 기준 대신 Property→응답→이미지, 입력 Decode→출력 Encode 등 역할별 분리 |
| C4-06: 4.8 재정의 Shorten | 4.8 | Confirmed | 개별 정의는 4.1–4.7에 두고 UV/Texture/Parameter/Normal/Light 합류를 남김 |
| C5-04: Surface Normal 재시작 Shorten | 5.2→3.4 | Confirmed | 3.4 Primary 참조. 5에서 사용하는 N의 orientation·Unit·Shading 의미는 유지 |
| C5-12: 5.16–5.19 Merge/Shorten | 05 마지막 BRDF 절 | Confirmed | 공통 언어/모델 목록 반복을 합치되 단위·정의·Lambert 검증은 삭제 대신 Expand |
| C5-12: 빈 Status Remove | 05 미완성 편집 흔적 | Confirmed | 의미 없는 placeholder만 제거 가능 |
| C5-12: 미사용 Fig5_15 처리 후보 | 원문 참조 없는 Figure 언급 | Modified | 미참조만으로 삭제 확정하지 않음. 이번 이미지/경로/파일 변경 없음; 필요 역할·다른 참조 확인 후 후속 결정 |
| Material Property와 결과의 반복 | Local L443; 4.1/4.2/4.8/5.17/6.1 | Necessary Reinforcement | Material 입력→BRDF response→이미지로 결과의 층위가 달라짐 |
| Texture/Sample의 4.8 재강의 축약 | Local L444 | Confirmed | Primary 4.3/4.4. 6.8의 출력 변환까지 함께 삭제하지 않음 |
| Import/Linear 원칙 Shorten | Local L445; 4.5/6.8 | Confirmed | 같은 입력 설정 표는 참조. decode와 output encoding 대비 Keep |
| Normal Map/반사 연결 | Local L446; 4.6/5.2 | Necessary Reinforcement | 4.6 Decode/TBN은 3.4의 Normal 정의와 다른 책임. 5.2 소비 계약만 간결화 |
| Roughness 낮음/높음 반복 | Local L447; 4.2/5.11–5.12/6.5 | Modified | Property 의미·분포·환경 응답은 Keep. 같은 이미지적 비유만 축약 |
| Diffuse/Specular를 IBL에서 다시 설명 | Local Duplication Map; 05→6.4 | Necessary Reinforcement | 새로운 입사 환경의 두 기여를 연결하는 적용이며 기본 반사 정의 재강의만 불필요 |
| H/Microfacet 성능·역사 반복 축약 | Local L449 | Confirmed | H 생성·기여 Facet·D(H)는 Keep. 반복 비용 우위/연표는 Shorten 또는 TV10 |
| 6.5 Reflection 원리 재유도 회피 | Local L450 | Necessary Reinforcement | 환경 반사 적용으로 남기되 Reflection 전체와 동의어로 제한하지 않음 |
| BRDF 모델 목록 반복 Merge | Local L451 | Confirmed | Primary 정의와 Lambert 실제 적용을 분리해 유지. 6.1은 Transport 연결 |
| HDR 입력/계산/출력 비교 | Local Keep 및 Boundary 판단 | Necessary Reinforcement | 새 문맥의 중요한 경계. 파일 포맷으로 HDR 전체를 정의하는 부분만 Rewrite |
| 04–06 일괄 Advanced Move 없음 | Local L105–107 | Confirmed | 기본 Sampling·MI·BRDF 수학은 Foundation. 상세 GGX/Smith 유도·플랫폼 사례만 후속 범위 |

### 9.3 Foundation_Audit_07-09.md

| Original Local Recommendation | Location | Global Decision | Reason / Final Global Action |
|---|---|---|---|
| C07-04: 공통 연산 Move/Merge | 7.9→7.2 앞 | Modified | Threshold/Smoothstep/Ramp 최소 소개만 앞으로. 7.9 전체를 옮기지 않고 종합 적용 유지 |
| C07-10: 비교/Callback/핵심 요약 Merge/Shorten | 7.2–7.9 | Confirmed | 동일 결론 복제만 정리. Diffuse/Shadow/Rim 등 제어 대상·확인 질문은 Keep |
| C07-12: Heading·장 끝 정리 Merge | 07 전체 | Confirmed | ASF-003 계층과 장 마무리 한 곳으로 정리. 새로운 Topic 계층을 만들지 않음 |
| C07-11: 08 후속 참조 교정 | 7.3/7.5/7.7 | Modified | 전체 08 확인으로 PBR Specular/IOR/SSS 예고 미충족을 확정. 단순 보류가 아니라 현재 범위 Rewrite |
| C09-07: Draw Call 앞 편집 문장 Remove | 9.6 L4160 주변 | Confirmed | Pixel Cost 안내 잔여 제거. Draw 개념·비용 설명 삭제가 아님 |
| C09-12: 9.8/9.9 Merge/Shorten | 도구표·종합 절 | Confirmed | 도구별 질문·측정 한계는 9.8, 최종 workflow는 9.9. 반복 도구 목록만 축약 |
| C09-13: Test Matrix 상세 Advanced Move | 9.9 L8432–8499 | Modified | 현재는 예고 목록이다. 짧게 남기고 미래 상세 프로토콜은 Advanced; 존재하지 않는 완성 실험을 이동했다고 쓰지 않음 |
| C09-13: Portfolio/Case Study Move | 9.9 L8503–8561 | Modified | Foundation 끝의 연결은 Keep/Shorten. 실제 산출물 설계와 Before/After 증명은 향후 Advanced |
| C09-14: 기준 설명 Merge | 9.1/9.2/9.8/9.9 | Confirmed | 9.1 측정, 9.2 Thread, 9.8 질문별 도구로 역할 분리; 적용 절의 진단 맥락 Keep |
| Detailed Face SDF 이동 | 7.7 후속 예고 | Modified | 현재 개요는 Keep, 미래 상세 제작·방향 판정·보정은 Advanced |
| Character Hair/Complex HLSL 이동 | 7.6/7.9 | Modified | 현재 모델 목적·입력 소개는 Necessary Reinforcement, 실제 복잡한 알고리즘만 미래 심화 |
| Outline 상세 Pass 이동 | 7.8 | Necessary Reinforcement | 큰 분류·입출력은 Foundation; 향후 Pass 구현/Production 예외만 Advanced |
| 기본 시각 검증 및 수치 예제 유지 | 7.2–7.9, 9.1–9.8 | Necessary Reinforcement | 입력 변화→예상 결과 확인은 기초. 가상 수치는 예시로 명시 |
| Hair off/Resolution/LOD probe 유지 | 9.4–9.8 | Necessary Reinforcement | 탐색적 비교와 단일 원인 검증을 구분하면 Foundation의 중요한 적용 |
| 9.3/9.7 LOD, 9.4/9.5 Hair 반복 정리 | Local 요약·Duplication 권고 | Confirmed | Geometry·coverage·Shader 관점의 새 이유만 남기고 같은 서술·수치 예제 복제는 축약 |

### 9.4 Foundation_Audit_08.md

| Original Local Recommendation | Location | Global Decision | Reason / Final Global Action |
|---|---|---|---|
| 08-00-B: 독립 Naming/구조 규칙 Merge | 8.0.5–8.0.7 | Confirmed | ASF-001/002가 규범. 현재 Asset 예제와 준비에 필요한 설명만 유지 |
| 08-00-E: 준비 원칙·환경·구조·요약 Shorten/Merge | 8.0 | Confirmed | 실제 생성·Git·환경 기록은 Keep; 장점·목록 재시작만 축약 |
| 08-01-D: Architecture 장점·요약 Merge | 8.1 | Confirmed | 책임/분기 설명 유지. 임시 파일명 정리는 별도 참조 관리 문제 |
| 08-02-B: Light 접근의 역사/성능 일반화 축소 | 8.2.3 | Modified | 핵심은 Deferred 환경과 입력 지원의 미검증 의존성 TV01. 일반 서사는 줄이되 입력 출처·조건을 먼저 검증 |
| 08-02-E: Base Lighting flow/요약 Merge | 8.2 | Confirmed | 세 입력/두 출력 단일 계약으로 정렬. 첫 테스트 vector와 실제 Light 적용은 서로 다른 확인이므로 Keep |
| 08-03-E: Shadow 기초 이론 축약/Move | 8.3 | Modified | 01에 Shadow mapping 상세가 이미 충분하다는 전제로 줄이지 않음. Depth→UV→Sample→Compare→Vis와 PCF 기본은 Keep |
| 08-03-E: Bias/Artifact 중복 Merge | 8.3 L2878–3066 및 L3494–3629 | Confirmed | 같은 Acne/Bias/Peter Panning 예제 통합; 실제 자기 그림자와 오류를 구분 |
| 08-03-E: Texel/Pixel·Map/Lightmap 반복 Shorten | 8.3.4–8.3.6 | Modified | 일반 Sampling은 4.4 참조. Light projection footprint·현재 샘플 비교는 새 맥락이므로 유지 |
| 08-03-E: 실제 Renderer/성능 심화 이동 | 8.3 한계·후속 안내 | Modified | 현재 미구현 계약과 기본 검증 Keep; 향후 내부 제작·상세 성능 사례만 Advanced |
| 08-04-E: Dot/Normalize/Reflection 재유도 Shorten | 8.4.2–8.4.6 | Modified | Dot/Normalize 정의는 03 참조. Reflection 투영 유도는 현재 05보다 상세하므로 먼저 05 기반을 보완한 뒤 줄임 |
| 08-04-E: MF 추출·수식/Node 대응 유지 | 8.4 후반 | Necessary Reinforcement | 첫 구현의 중간값·예상 결과·Unit L 분기 재사용은 일반 수학 반복이 아님 |
| 08-05-F: Fresnel 광학 설명 Condense | 8.5.4 | Modified | F0/Schlick 기초의 실제 첫 상세가 여기 있음. 5.14로 최소 기반을 옮긴 후 참조로 축약 |
| 08-05-F: Rim 목적 대비·최종 요약 | 8.5.4/후반 | Necessary Reinforcement | Fresnel≠Rim의 목적 차이와 지각 Width 구분 Keep. 동일 결론 여러 번 반복만 Shorten |
| 08-06-E: 좌표·Normalize·Remap 장문 Condense | 8.6 | Modified | World/View 기초는 02 참조. MatCap의 View Normal→UV·V Flip·Texture Object·오류 테스트는 첫 적용으로 Keep |
| 08-06-E: MatCap 요약·동일 비교 반복 | 8.6 후반 | Confirmed | axis convention 표와 대표 비교를 남기고 동일 요약 통합 |
| 08-07-F: HDR/Exposure 장문 Condense | 8.7.2–8.7.4 | Modified | Exposure 기반을 06에 보완한 뒤 줄임. Manual Exposure·Bloom 비교·수치/화면 차이는 Keep |
| 08-07-F: Mask 반복 Condense | 8.7.5–8.7.6 및 후반 | Modified | 8.7.6의 현재 UV Sample R→Scalar는 ASF-002를 구현에 연결하므로 유지. 동일 흰색/검정 설명 반복만 축약 |
| 08-08-D: Region/Multiply/Lerp Condense | 8.8 | Necessary Reinforcement | Parameter interpolation≠최종 반응 interpolation. A/B/Mask 3조건 테스트는 Keep; 기본 정의만 참조 |
| 08-09-E: Mode표·진단·결과 반복 Condense | 8.9 | Confirmed | 단일 최종 Mode표와 실제 tap을 기준으로 통합. Mode0 보존 및 0–5 기본 테스트 유지 |
| 08-09-E: Fig8_72 중복 설명 정리 | 8.9 두 참조 | Necessary Reinforcement | 같은 최종 비교를 설명/종합에서 재사용하는 목적은 유효. 단순 재사용을 Figure 제거 근거로 삼지 않음 |
| 08-10-F: contract/MI/Production 원칙 Condense | 8.10 | Confirmed | 단일 계약·지원 상태·최소 검증표에 통합. 4.7 MI 재강의만 줄이고 최종 연결 확인 유지 |
| Dup Map: Coordinate/Normal/View Shorten | Local L780; 8.2/8.4–8.6 | Modified | 일반 정의는 02/03, 각 함수의 Space/Unit 계약과 실패 테스트는 유지 |
| Dup Map: Dot/Reflection/Power Shorten | Local L781 | Modified | 03에 Reflection 전체가 있다고 간주하지 않음. 05 기반 보완 전 8.4 상세를 먼저 삭제하지 않음 |
| Dup Map: MF/Master/MI 클릭 안내 통합 | Local L782 | Confirmed | 첫 생성과 특수 설정 Keep, 이후 동일 클릭 절차는 참조 |
| Dup Map: Fresnel Primary / 장문 축약 | Local L783 | Modified | 개념 Primary는 05, 07은 스타일 대비; 실제 F0 기반을 05에 보완한 뒤 적용 |
| Dup Map: Shadow/Bias/PCF 통합 | Local L785 | Confirmed | 명시한 Bias 중복만 Merge. 이미 정확한 compare-then-average·Vis scalar 테스트 Keep |
| Dup Map: HDR/Exposure 일반 이론 참조 | Local L786 | Modified | 06의 Exposure 설명을 먼저 보완해야 링크가 성립함 |
| Dup Map: Texture Primary=01/06, Sample 축약 | Local L787 | Modified | 실제 Primary는 4.3–4.5. 8.7.6 현재 Sample 계약 유지, 후속은 채널/범위/색 해석만 연결 |
| Dup Map: Multiply/Lerp 정의 재강의 축약 | Local L788 | Confirmed | 8.6 합성 Alpha 양끝, 8.8 parameter 선택·A=0 특수식, 8.10 off 조건은 새 맥락으로 유지 |
| Dup Map: Debug Mode/재계산 금지 Merge | Local L789 | Confirmed | 최종 Mode표와 공유 경로 한 곳에 모으되 기능별 기본 확인 보존 |
| Dup Map: Final Flow/Production 원칙 Shorten | Local L790 | Confirmed | ASF-000/002 참조, 8.10은 실제 contract·미구현·검증 중심 |
| 종합 Debug 입력/최종 식 승계 | Local L737–768 | Rejected | ShadowVisibility를 Debug 입력에 넣고 MatCapResult를 빼는 표·식은 원문 최종 계약과 다름. 본 보고서 6.2로 교정 |
| MF=Module으로 읽히는 종합표 | Local Module 표 및 설명 | Modified | 표는 현재 구현 대응표로 제한. Module≠MF라는 ASF-002가 상위 |
| 08-10-D: MatCapBlend Parameter 목록 정렬 | 8.10 Parameter/MI | Modified | Constant/선택 노출을 구분. 노출 필수라고 강제하지 않음 |
| 08-G-01: Stylized Diffuse 연결 보완 | 08 overview/8.2/8.10 | Modified | 현재 연속 clamped cosine 기반과 07의 Toon 가능성을 연결. 실제 Threshold/Ramp 구현 완료라고 추가하지 않음 |
| Boundary: Basic Verification 유지 | Local L796–802 | Necessary Reinforcement | 첫 프로젝트·Sample·Unit·Unlit·Mode 검증은 사용자 지시와 ASF-000에 부합 |
| Boundary: 상세 성능·HLSL·대규모 시스템 이동 | Local L803–804 | Modified | 현재는 후속 주의/예고. 미래 상세 실행을 Advanced로 지정하며 실제 존재하는 대량 구현으로 서술하지 않음 |
| Boundary: Built-in/Custom 이유 Shorten | Local L805 | Confirmed | 선택 이유는 남기고 같은 Production 원칙만 축약. Renderer 접근 가능성을 자동 보장하지 않음 |

### 9.5 Other local findings and global corrections

Shorten/Merge/Move/Remove 외 기술·용어·참조 권고도 전체 원문과 대조했다. 최종 판단은 6–7절에 통합했으며, 다음과 같이 범위를 정리했다.

| Local finding group | Global validation |
|---|---|
| 01–03 Matrix/Space/Normal/ASCII/Node 계약 | B05–B11/B37, W04–W05, TV02/08/11로 반영. 뒤 원문에 존재하는 Normal 예외·Pixel Center를 누락으로 재등록하지 않음 |
| 04–06 BRDF·Lambert·H/DGF·F0·Color·Static Parameter | B01–B04/B11–B15, W01–W03, TV03/10. 금속 BaseColor 연결과 에너지 보존·reciprocity의 최소 물리 조건 보완 방향 유지 |
| 07 PBR/NPR·Shadow/Rim·Face/Hair·Outline | B15–B18, W09–W10. 7.7 Face SDF는 반드시 Light-independent가 아니며 의도적 제어 선택으로 한정; 모델 계보는 TV10 |
| 09 Timing·비용·Lerp·Culling·인용 | B31–B36/B38, W14–W15, TV08–TV10. 이미 있는 RHI/overlap·Slot/Pass trade-off·Object update 구분을 보존 |
| 08 각 함수의 부호·Space·type·output·관찰 | B19–B30 및 6.2 계약, TV01–TV07. 최종 코드에 이미 있는 clamp/V Flip/fallback과 초기 screenshot·중간 서술을 구분 |
| Naming/Heading/미래 참조 | 5절, W06–W10, Plan Priority6–7. 실제 원본 순서와 Accepted Decision을 기준으로 교정 |


## 10. Figure Audit Integration

Foundation_Phase1B_Figure_Audit.md L1–3289 전체를 읽었다. 이 보고서의 Completed Chapters=01–09, Last Completed Figure=Fig9_09, Next Figure=None, Status=Complete는 **이전 Figure 검토가 끝났다는 뜻**이며 이미지 문제가 수정되었다는 뜻은 아니다. 이번에는 이미지 파일을 열어 재검토하지 않았다. 아래 항목은 Figure Report의 텍스트 기록과 현재 원문의 직접 대조에 따른 **Figure Recheck Required**이며, 새 시각 판정을 내린 목록이 아니다.

Figure Report의 명칭 판단은 교정이 필요하다. L147의 Ari’s Shader Framework 및 Fig7_01/Fig8_01/Fig8_08의 Anime이 옛 명칭이라는 권고는 ASF-000/Accepted DEC-015와 충돌하므로 Rejected다. Anime을 Ari’s로 바꾸지 않는다. Fig8_74의 Art Stylized Foliage, Fig9_02/03/09의 Art/System/Framework, Fig9_04의 ARTIST SURVIVAL GUIDE는 보고된 문자열이 실제로 존재하는지 필요한 수정 단계에서 확인하고, 올바른 확장은 Anime Shader Framework로 한다. Figure Audit의 기술 판정과 잘못된 브랜드 권고를 분리한다.

| Text Refactoring trigger | Related Figure record | 왜 추가 대조가 필요한가 / 유지할 Text 기준 |
|---|---|---|
| B05/B37: Depth 생성·판정 및 Index 일치 | Fig1_05/1_10/1_11 | Index 수치, Shadow Map과 Visibility, 기본 raster depth와 선택적 Shader override를 구분한 본문과 함께 확인 |
| B06–B08: Clip/NDC·같은 ray·Matrix 의미 | Fig2_01/2_03/2_04/2_07/2_08/2_09/2_12/2_13/2_16 | 특히 2.9의 같은 offset 조건은 현재 본문이 더 정확함. 그림 설명을 맞추려고 본문을 “같은 방향”으로 되돌리지 않음 |
| B09–B11: Normal·L/V·Decode·Normalize | Fig2_14/2_15, Fig3_02–3_06, Fig4_06/4_08 | 3.4 Artist Normal·동일 Geometry, 3.5 unit 결과, L/V 부호, input type/Space 계약과 충돌하는 보고 기록 |
| B13: 입력 decode/출력 encode | Fig4_05 및 Fig6_08/6_09 | 0.5→0.73을 decode라고 부르는 방향 및 normalized value에 휘도 단위를 붙이는 기록. 본문 수치·단위를 먼저 확정 |
| B01–B04/B14: BRDF·DGF·현대 Rendering 합류 | Fig5_06–5_10/5_12–5_14, Fig6_01/6_02/6_05/6_06/6_10 | BRDF=final direction/result, NDF=Gaussian, 고정 Stage 직렬화 기록. 특히 5.12 본문의 “정규분포 아님”을 보존 |
| B16–B18/W09: Stylized 제어 대상 | Fig7_04/7_05/7_09 | Toon band≠Cast Shadow, Rim≠물리 Fresnel 밝기, Step 결과를 Smoothstep으로 복원한다는 잘못된 연결 |
| 8.0/8.1 참조 목적·다음 단계 교정 | Fig8_03/8_04/8_05/8_08 | 같은 파일이 설정/폴더와 Architecture/Data Flow에 재사용된 목적 충돌. 후속 별도 도식 필요 여부를 확인하되 이번 경로 변경 없음 |
| B20/TV01: Base Lighting 계약·관찰 증거 | Fig8_24/8_25/8_26/8_27 | 두 output 누락, D를 표시한 화면을 BaseColor 적용 B 검증이라고 설명하는 기록; 실제 source 지원 조건 필요 |
| B21 및 최종 Specular 계약 | Fig8_14/8_15/8_19/8_20/8_23; 비교 Fig8_49 | 초기 Unit L 분기·미연결 Dot·Specular pin과 최종 MF가 다름. Fig8_49에서 정규화 분기 문제가 해소된 기록을 무시해 모든 버전을 동일 오류로 취급하지 않음 |
| B22: Shadow 관찰/취득 범위 | Fig8_31/8_32/8_33/8_35/8_36/8_39 | Light-space 비교·수치 대응 및 Debug Mode/움직임/품질 변경 증거가 부족하다는 기록. 수동 Vis와 Renderer 통합을 분리 |
| B17/B23: Rim/Fresnel 및 구현 버전 | Fig8_45/8_48/8_50 | Schlick 수식과 곡선, 최종 Width/Softness에서 초기 Power 입력의 잔존, Scene Shadow가 ASF Vis 증거인지 확인 |
| B25/B26: MatCap Normal·UV·Blend | Fig8_52/8_53/8_55/8_58 | Normal Z를 Depth로 설명한 기록, raw remap와 최종 V Flip, 수동 Vis=1·Blend=1의 의미 |
| B27/B30: Emission/표시 조건 | Fig8_59/8_62/8_63, 필요 시 Fig8_66 | 실제 Multiply/Lerp/Add 관계 및 effective Exposure 설정. Fig8_66의 Emission 합성 Match는 모든 Light/Shadow 기여 검증을 뜻하지 않음 |
| B28: Region Parameter의 소비 위치 | Fig8_67 vs Fig8_68 | 초기 설명은 MF 입력, 최종 실제 연결은 SpecularMask에 외부 Multiply. 후자를 계약 기준으로 보존 |
| B29/B19/B26: 최종 Debug/Framework | Fig8_69/8_70/8_71 vs Fig8_72/8_73/8_74 | Final input·MatCap tap·RGB Emission, 실제 Add→Lerp→Add를 정렬. Fig8_72의 유효한 두 참조는 삭제 후보 아님; Fig8_73의 Blend=1은 기여 전부 검증 증거 아님 |
| B31–B36: 측정·비용·가시성 | Fig9_01/9_02/9_04/9_05/9_07/9_08 | 병목 숫자와 label, Frame overlap, Blend/Branch, LOD/coverage, frustum 반대 문장 및 실제 명령/예시 화면 범위 확인 |

Match 기록이나 단순 가독성/색상/배치 수정 목록을 전부 복제하지 않았다. Figure의 기술 오류가 본문에도 있는지와 **본문이 이미 맞는데 Figure만 오래된 상태인지**를 구분했다. Text를 수정한 뒤 위 관련 Figure만 필요한 범위에서 재확인하며, Figure Report의 일괄 Replace/Revision 수량을 Global Text의 완료 기준으로 사용하지 않는다.

## 11. Final Refactoring Plan

Phase 2는 아래 의존 순서로 진행한다. 각 단계에서 기준 계약과 관련 소비 절을 함께 정렬한 다음 중복을 줄인다. 원본 수정은 이번 단계에서 실행하지 않았다.

| Priority | Related Chapter / Section | Work / Action | 완료 판단 |
|---|---|---|---|
| 1A Technical / Architecture | 5.4–5.19, 6.1–6.9 | B01–B04/B13–B15 Rewrite/Expand. BRDF·Lighting·HDR·출력 관계, 단위, 최소 DGF/에너지 보존·reciprocity 조건, 역할별 데이터 합류 확정 | BRDF와 radiance를 구분하고 하나의 Lambert 예시가 05 정의→06 기여→08 방향 계수 제한까지 모순 없이 연결 |
| 1B Implementation contract | 8.1–8.10 | B19–B30 Rewrite, 6.2 canonical contract로 세 입력/두 출력·MF 책임·합성·Debug 표를 정렬 | BaseColor Multiply, MatCap Lerp, RGB Emission, Debug input tap이 모든 설명에서 동일 |
| 1C Data / observation conditions | 1.10–1.11, 02/03, 4.5–4.7, 8.2/8.4/8.7/8.9, 09 | 부호·Space·Matrix·Static/Runtime·표시/계산 경계 수정. TV01–TV09는 실제 대상 환경에서 검증 | 기술 확인 전까지 플랫폼 단정은 제한하고 검증 상태를 명시. 수동 Vis/Region 미통합이 완료 표에서 분명함 |
| 1D Profiling causality | 9.1–9.8 | B31–B36 Rewrite/Expand; Camera/Pass, Wait/Cap, 복합 probe의 의미 | 측정값만으로 단일 원인을 확정하지 않고 다음 분리 검증이 연결 |
| 2 Concept Source of Truth | 1.3, 2.2/2.9/2.11–2.14, 3.2–3.7, 4.3–4.7, 05/06, 8.9/8.10, 9.1/9.2/9.8 | 본 보고서 3절 기준으로 primary definition/consumption 지정 | 정의를 고칠 곳과 영향 소비 절이 명확하며 중복 정의의 competing contract가 없음 |
| 3 Missing / Weak Explanation | W01–W15 | BRDF 최소 수학, F0/Metallic, Matrix 예제, Deferred/GBuffer, Exposure, 함수 유효 입력·검증 증거 보완 | 앞 개념이 준비된 뒤 소비. 현재 없는 Production 기술·실험은 새 Foundation 필수 범위로 늘리지 않음 |
| 4 Learning Flow / Placement | 7.2/7.9, 5.14/8.5, 6.6–6.8/8.7, 장간 안내 | 최소 정의 Move, 실제 후속 참조 교정. 03/05/06 전체 장 순서는 유지 | 잘못된 이전/다음 장·완료형 문장이 없고 현재·향후 범위가 분리됨 |
| 5 Duplication / Reinforcement | 1.10/1.13, 2.8/2.9/2.16, 3.7, 4.8, 5.16–5.19, 7/8/9 요약 | 4절과 9절 개별 판정대로 Merge/Shorten/Remove/Cross Reference | 고유 원리·첫 Node 구현·입력 계약·실패 진단·기본 검증 손실 없음; 목표 글자 수를 설정하지 않음 |
| 6 Terminology / Cross Reference | 전반 및 8.0/8.10/9.8 | 5절 통일, Accepted ASF 명칭, 실제 절의 제목/Anchor, 내부 citation token 교정 | 용어의 의미·Space·type이 일치. 실제 존재하지 않는 학습 참조가 없음 |
| 7 Minor Editing / Heading / Formatting | 01/02 ASCII, 3의 예고, 8.9 s, 9.1/9.2 heading, 9.6 편집 흔적 등 | ASF-003 기준 계층·중복 heading·오타·형식 정리 | # Chapter / ## 번호 major / ### unnumbered internal 중심. 기술 변경 뒤 표·식·도식·참조를 마지막 대조 |

Phase 2 최소 기본 검증은 수식의 기대값과 연결 상태를 먼저 대상으로 한다. N/L/V 기준 방향과 0/90/180도, Unit L 재사용, BaseColor×D, Vis=1/.5/0, Specular/Rim Intensity=0, MatCapBlend=0/1과 Intensity=0 차이, EmissionMask=0/1, RGB 보존, Debug0–5와 fallback을 확인한다. 한 가지 제어만 바꾼 관찰은 Foundation에 남긴다. 플랫폼별 비용 수집·Before/After Production 사례는 Advanced로 분리한다. 이 검증들은 **후속 완료 기준이며 이번 Audit에서 실행한 테스트가 아니다**.

## 12. Refactoring Safety Notes

### 12.1 Change propagation

| Changing this definition affects | Related Chapters / Sections | 함께 확인할 사항 |
|---|---|---|
| L/V sign, same Space, Unit Vector | 2.15→3.2/3.6/3.7→5.3/5.6→8.2/8.4/8.5/8.10 | 방향 화살표·수식·Node input·Debug 표시를 함께 정렬. -L 분기의 Normalize 이전값 사용 방지 |
| Normal/Matrix convention | 1.3/1.8→2.11–2.16→3.4/3.5→4.6→8.6 | Geometry/Shading, inverse transpose, TBN, raw/decode/Space 구분. matrix storage와 vector convention 분리 |
| BRDF/Roughness/F0/Material | 4.2/4.8→05→06→7.3/7.5→8.4/8.5 | BaseColor의 역할, 응답 단위, G/Scene Vis, 교육용 Phong/PBR 범위를 확인 |
| Texture/Data/Color transfer | 4.3–4.6→6.8→8.6–8.9 | Texture Object와 sampled RGB/Scalar, Normal decode 중복, HDR texture, Mask numeric 보존 |
| Visibility / Shadow | 1.10→7.4→8.3→8.5–8.10→9.7 | Scene 취득과 Scalar 소비, Camera/Light/Pass, per-light 원리와 현재 Base-only 적용 범위 |
| Final composition / parameter | 8.2–8.8→8.9→8.10 | Add/Multiply/Lerp 순서, Alpha off, 외부 Color/Intensity, Constant와 MI 노출, Region 미통합 |
| Debug contract | 8.9 전체→8.10→9.8 | Mode0 Final, MatCapResult 포함, Emission RGB, fallback, 표시 경로·postprocess·runtime 비용 |
| HDR/Exposure / verification | 06→8.7→8.9/8.10→09 | 계산 값·표시값·관찰·실측 구분. 캡처가 주장하는 조건을 실제로 보여주는지 확인 |
| Performance / culling | 1.12→9.1–9.8 | Frame overlap·Pass·coverage·Shader work·Geometry/Vertex·GPU-driven 예외. 최적화의 품질 손실과 병목 이동 |
| Primary Source / Heading / naming | 모든 소비 절·Figure caption·계획 문서 | 링크를 먼저 만들고 설명 삭제. 링크 대상이 실제 내용을 제공하는지 확인. Asset/파일 rename은 별도 의존성 검토 |

Remove는 중복 원문·빈 Status·고립 문자·편집 잔여처럼 의미가 없는 부분으로 제한한다. 미참조 Figure나 이름이 오래된 파일을 자동 삭제하지 않는다. Merge 전에 고유 예제·조건·예외·검증 질문을 대조한다. 기존 그림에 맞추려고 정확한 본문을 잘못된 정의로 되돌리지 않는다.

Shorten은 Concept→왜 필요함→입력/출력→실제 적용→기본 확인이라는 연결을 남긴다. Cross Reference는 필요한 전제를 한두 문장으로 재연결하며 독자가 여러 파일을 왕복해야만 현재 함수 계약을 이해하는 구조를 만들지 않는다.

### 12.2 Coverage and completion evidence

실제 원문은 00_Foundation 아래 다음 20개 Markdown이며 모두 처음부터 끝까지 읽었다. 공백 행은 도구 출력에서 생략했지만 본문·표·수식·코드·원문 도식·Figure 참조는 확인했다. 출력이 잘린 구간은 별도 다시 읽어 복구했다.

| Original file (00_Foundation 기준) | Lines | Full read |
|---|---:|---|
| Chapter01_RnderingPipeline.md | 7754 | Complete |
| Chapter02_CoodinateSystem.md | 14954 | Complete |
| Chapter03_LightingMathematics.md | 1285 | Complete |
| Chapter04_MaterialArchitecture.md | 2739 | Complete |
| Chapter05_Reflection_BRDF.md | 3450 | Complete |
| Chapter06_ModernRealtimeRendering.md | 916 | Complete |
| Chapter07_Stylized Rendering.md | 1227 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08_BuildingAnAnimeShader.md | 142 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.0_PreparingTheASFProject.md | 1067 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.1_ArchitectureOverview copy.md | 436 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.2_BaseLighting.md | 976 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.3_Shadow.md | 5370 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.4_Specular.md | 1733 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.5_RimLight.md | 3550 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.6_MatCap.md | 6228 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.7_Emission.md | 6195 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.8_MaterialLayer.md | 1886 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.9_DebugView.md | 3603 | Complete |
| Chapter08_BuildingAnAnimeShader/Chapter08.10_FinalFramwork.md | 4659 | Complete |
| Chapter09_RenderingDebugandOptimization.md | 8595 | Complete |

기준·보조 자료 전체 확인: ASF-000_Project_Principles.md, ASF-001_Naming_Philosophy.md, ASF-002_Rendering Architecture.md, ASF-003_Documentation_Standard.md, ASF_Standard.md, DecisionLog.md, Roadmap.md. 활성 000–003과 폐기/이관된 이전 계획 규칙을 구분했으며 Accepted가 아닌 향후 renumbering 제안을 확정 정책으로 사용하지 않았다.

Local Report 전체 확인: Foundation_Audit_01-03.md 497행, Foundation_Audit_04-06.md 565행, Foundation_Audit_07-09.md 466행, Foundation_Audit_08.md 897행. Figure Report 전체 확인: Foundation_Phase1B_Figure_Audit.md 3289행. Figure 보고서가 기록한 154개 고유 Figure/161개 참조를 이번에 다시 이미지 전수검사한 것은 아니다.

기존 보존 baseline phase1b_sources_before.json에 기록된 **181개 파일의 현재 SHA-256을 대조해 변경/누락 0개**를 확인했다. 이는 기존 baseline과의 보존 확인이며 새로 실행한 시각 검토나 엔진 검증이 아니다. 이번 작업의 쓰기 대상은 Foundation_Global_Audit.md 한 파일이었다. 원본 Markdown, Figure, Standards, Local/Figure Audit 파일·경로·이름을 변경하지 않았다.

### 12.3 Final audit status

- Chapter 01–09 원본 전체 확인: Complete.
- 기준 문서 및 네 Local Audit 전체 재검증: Complete.
- Concept Source of Truth / Cross-Chapter Duplication / Terminology: Complete.
- Learning Flow / Foundation–Advanced Boundary / Chapter08–09 Integration: Complete.
- Figure Audit report의 필요한 Text 관련 판단 및 오류 재판정: Complete.
- Final Refactoring Plan / 변경 영향 관계: Complete.
- Global Integration Text Audit: Complete.
- 실제 Refactoring / Figure 수정 / Engine 기술·성능 검증: Not performed; 이번 범위 밖.
- Remaining Audit Chapters: None.
- Report validation: 필수 12개 항목·20개 원문 목록과 행 수·표 열 구조·코드 블록 확인 완료.
