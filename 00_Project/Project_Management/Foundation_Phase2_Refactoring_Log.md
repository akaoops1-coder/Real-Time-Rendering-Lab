# Foundation Phase 2 Refactoring Log

작업 시작: 2026-09-21 (KST).
실제 작업 루트: C:\Users\kmcoo\Desktop\PW\ASF_Review. 첨부 문서의 ASF\_Review 경로는 존재하지 않으므로 이전에 확인한 이 사본만 사용한다.

기준: ASF-000 → Accepted DecisionLog → ASF-001/002/003 및 ASF_Standard → Foundation_Global_Audit → Local/Figure Audit → 원문. 기존 기준·Audit는 읽기 전용으로 유지한다. Chapter 03/05/06의 실제 순서는 Accepted Decision 및 Global Audit에 따라 유지하며 Surface/Lighting/PBR 학습 연결을 보완한다.

Scope: 00_Foundation의 원본 Markdown 20개와 이 Log만 수정. Figure 이미지·경로·파일명은 유지. 낮은 확신의 삭제·이동·병합은 하지 않으며 기본 구현·검증과 새 맥락의 반복을 보존한다. Engine 실행이나 새 성능 실측을 수행하지 않은 항목은 검증 완료로 표현하지 않는다.

## Chapter 01

### Major Changes

- Section: 1.5–1.6. Change: Quad 대각선을 Index 0–2와 맞추고 Indexed/Non-indexed Draw를 구분했다. Frustum Culling의 CPU/GPU 구현 위치와 View별 범위를 명시했다. Reason: Index 사용과 Culling 실행 위치를 보편 법칙으로 읽는 문제 수정. Source: Global B05/B37, Local C1-02/C1-04/C1-05, Technical Consistency.
- Section: 1.8–1.11. Change: Interpolation의 거리 직관과 실제 Weight를 구분하고, Camera Depth/Shadow Map 비교/Visibility 및 raster depth/Shader override/Test/Write를 정리했다. Present 동기화 조건을 보완했다. Reason: Data와 판정·출력 주체 분리. Source: Global B05/B09/TV08, Local C1-03, Figure Fig1_10/11.
- Section: 1.13. Change: CPU 준비·Draw·GPU 처리·저장·표시의 여섯 묶음을 Group으로 표시했다. Reason: 실제 GPU Stage와 교육용 범주의 혼합 방지. Source: ASF-002, Global B19의 전제, Figure Fig1_13.
- Section: 전체. Change: Major 1.1–1.13과 내부 Heading 계층을 정렬하고 English Title, Outfit 용어, 실제 후속 학습 범위로 참조를 교정했다. Source: ASF-001/003, Accepted DEC-001, Global 5/11절.

### Structural Changes

- Move: 없음. Chapter 순서와 상세 학습 흐름 유지.
- Merge: 중복된 1.10의 공통 prefix를 실제 문자열 대조하여 뒤의 완전본으로 통합.
- Remove: 잘린 앞 1.10 중복본과 그 안의 중복 Fig1_10 삽입 1회, 고립 s. Fig1_10의 정상 참조와 파일/경로는 그대로 유지. 고유 학습 내용을 삭제하지 않음.
- Keep: 1.2 Overview/1.13 종합, Attribute/Seam, 보간 후 Normal, Camera-Light 대비와 Early-Z 적용 설명.

### Cross-Chapter Impact

- Related Chapters: 02 Clip/Depth/Matrix, 03 Normal, 06 Forward/Deferred/GBuffer, 08 Shadow/Data 계약, 09 비용/Pass/overlap.
- Follow-up Checked: 현재 Chapter 자체의 Major 13개·1.10 단일화·Figure 경로 유지 확인. 이후 Chapter 소비 절은 해당 순서에서 정렬 예정. 06에 최소 Forward/Deferred 설명을 실제 추가한 뒤 참조를 완료 확인할 것.

### Figure Follow-up

- Figure: Fig1_05/1_06/1_10/1_11/1_13.
- Required Action: Figure Recheck Required. Index/Winding, Culling 위치, Map와 비교 결과, Depth 출력 주체, 개념 Group을 수정 본문에 맞춰 후속 정렬. 이미지 변경 없음.

## Chapter 02

### Major Changes

- Section: 2.6–2.9. Change: Frustum ASCII의 Near/Far 폭을 바로잡고, 같은 Camera ray와 같은 View X/Y Offset을 분리했다. Clip homogeneous 범위와 NDC 고정 범위, 입력 w=1/0과 Projection 뒤 w 및 homogeneous 동치 예제를 연결했다. Reason: 공간/투영 조건 혼동 수정. Source: Global B06/B07/W05/W07, Local C2-02/C2-03/C2-05.
- Section: 2.11–2.13. Change: Column Vector convention으로 T×R×S, P×V×M을 정렬하고 Position/Direction의 4×4 수치 예제와 rigid Camera inverse 예제를 추가했다. Matrix storage와 곱 convention을 분리하고 Normal 상세 원리는 3.5로 연결했다. Source: Global B07/B08/W05, Local C2-01/C2-06.
- Section: 2.14–2.16. Change: Normal의 Geometry/Shading 범위, Decode→TBN→Normalize, basis 공간·handedness·orthonormal 조건을 보완했다. WorldPosition−ObjectPosition은 World Offset이며 Local Position 변환이 아님을 수정하고 Node의 bounds/pivot 의미는 검증 필요로 한정했다. Source: Global B08/B10/B11/TV02, Local C2-07/C2-08/C2-09.
- Section: 전체. Change: FOV와 Camera 이동 조건을 구분하고 없는 09 Depth/Reversed-Z 상세 예고를 현재 범위로 교정했다. Major 16개/단일 Chapter Title 및 English Internal Heading으로 정렬했다. Source: Global W07, ASF-003.

### Structural Changes

- Move: 없음. Normal Transform 원리의 Primary를 3.5로 명시하되 2.13의 데이터 종류 비교는 유지.
- Merge: 없음.
- Remove: 없음. 2.8의 같은 x/w 계산 재시작만 짧은 reminder와 바로 다음 2.9의 상세 예제로 연결해 Shorten. Figure 없는 구간임을 확인했고 수치 기반 상세는 2.9에 남겼다.
- Keep: Position/Direction 분기, Pixel Center와 경계, View Depth/거리 구분, TBN/Normal Map 새 맥락, 2.16 종합.

### Cross-Chapter Impact

- Related Chapters: 01 투영/Depth, 03 Matrix·Normal·L/V, 04 Normal Decode, 08 Shadow/MatCap/Node 입력.
- Follow-up Checked: Chapter Title 1개, Major 16개, Figure 참조 16개 유지. 원문 교정 후 03의 Normal 수직 조건·행렬 convention을 이어서 정렬 예정. 04 Decode와 08 World Offset/MatCap에서 후속 확인 필요.
- Process: 최초 저장 명령의 형식 오류는 자동 승인 검토가 차단했으며 실행되지 않았다. 명령을 수정하고 구문 검사 및 원문 일치 검사를 통과한 후 저장했다.

### Figure Follow-up

- Figure: Fig2_01/03/04/06/07/08/09/12/13/14/15/16.
- Required Action: Figure Recheck Required. 축·Transform 수치·Clip/NDC·같은 ray·Normal Decode·L/V·Node 의미를 수정 Text와 정렬. 현재 모든 이미지 경로·참조는 유지.

## Chapter 03

### Major Changes

- Section: 3.1/3.4. Change: Vertex/Triangle과 Normal/Tangent/UV의 Surface Data 관계를 연결하고 Geometric Normal·Shading Normal·Artist Normal·Silhouette를 구분했다. Cross Product의 Edge 정의·순서·degenerate 조건을 보완했다. Reason: Geometry 기반과 Lighting 입력 관계를 보존. Source: Global 2/3절, B10/W04, Local C3-02.
- Section: 3.2–3.3. Change: Normalize의 nonzero 조건·fallback 책임, Dot 성분식/Unit 범위, signed NdotL과 clamped factor를 명시했다. Source: Global B09/W04, Local C3-01.
- Section: 3.5. Change: M의 선형 3×3·invertible·Column Vector 조건과 역전치의 수직 보존 이유, 실제 수치 예제를 추가했다. Reason: Chapter 02에서 연결한 Primary Explanation 완성. Source: Global B08/W04, Local C3-03, Figure Fig3_04.
- Section: 3.6–3.7. Change: L=Surface→Light, V=Surface→Camera, propagation=-L 기준과 Orthographic 예외를 정렬했다. 같은 Space를 실제 N/L/V 진단과 기본 검증으로 연결하고 잘못된 다음 Diffuse 예고를 3.5→3.6→3.7→04/05로 수정했다. Source: Global B09/B38, Local C3-04/C3-05.

### Structural Changes

- Move: 없음. 현재 Chapter 역할 유지.
- Merge: 없음.
- Remove: 없음. 3.7의 Space 목록 재정의만 이전 개념 reminder로 Shorten.
- Keep: Geometry/Shading 대비, 보간 후 Normalize, Non-uniform Scale 설명, 같은 Space의 오류 증상과 Debug 맥락.

### Cross-Chapter Impact

- Related Chapters: 01 Vertex/Interpolation, 02 convention/TBN/Normal 예외, 04 Normal Map, 05 Reflection/Lambert, 08 Base/Specular/Rim/MatCap.
- Follow-up Checked: 01/02와 Position/Direction/Normal 입력 의미 및 Column Vector convention 일치. 03 기본값 예제와 수식 상호 대조. 05/08에서 Unit·부호·clamp 계약 후속 반영 예정.

### Figure Follow-up

- Figure: Fig3_02/03/04/05/06.
- Required Action: Figure Recheck Required. 각도·Winding·동일 Geometry·Normalize 수치·L/V 방향·Normal transform 분기를 Text에 맞춤. 기존 이미지와 경로 유지.

## Chapter 04

### Major Changes

- Section: 4.2–4.4. Change: Metallic workflow의 BaseColor 역할을 연결하고 Texture resource/현재 Sample/Channel Scalar를 구분했다. Mesh UV를 일반 UV의 유일한 출처로 정의하지 않으며 Mip 선택은 footprint 조건으로 수정했다. Source: Global B11/W03, Local C4-01/C4-05.
- Section: 4.5–4.6. Change: transfer encoding과 전체 Color Space, sRGB Off와 압축/Filtering/Normal Decode를 구분했다. raw RGB Decode와 Engine sampler-decoded Normal의 중복 Decode를 방지하고 TBN Space/handedness/Normalize를 연결했다. Source: Global B11/B13/TV03, Local C4-02/C4-04.
- Section: 4.7–4.8. Change: Static Switch compiled variant와 비정적 Parameter override를 분리했다. 마지막 Data Flow를 독립 Mesh/Texture/Parameter/Scene 입력의 합류로 바꾸고 Lit Property와 08의 Unlit 합성을 구분했다. Source: Global B12/B20, Local C4-03/C4-06, Figure Fig4_07/08.

### Structural Changes

- Move: 없음.
- Merge: 없음.
- Remove: 없음. 4.8의 Color Space 장문 재정의만 4.5 reminder와 현재 합류 책임으로 Shorten. 해당 범위에 Figure가 없음을 확인.
- Keep: Texture/Sample의 첫 상세, Numeric Mask·Normal Map·Sampling/Filtering·MI 기본 구현 및 새 맥락의 연결.

### Cross-Chapter Impact

- Related Chapters: 02 TBN, 03 N/L/V, 05 Metallic/F0/BRDF, 06 Linear 출력, 08 MatCap/Emission/Region, 09 Static/runtime 비용.
- Follow-up Checked: 02의 Decode/Space 계약 및 03의 Normal과 일치. 05 F0, 06 출력 변환, 08 Function 밖 Sample, 09 Static/runtime 설명은 순차 반영 예정.

### Figure Follow-up

- Figure: Fig4_02/03/04/05/06/07/08.
- Required Action: Figure Recheck Required. Geometry/Normal/Property 비교, encoded/decoded 값, footprint, decode 방향, Static Switch 예외, L/V와 독립 입력 합류를 수정 Text와 맞춤. 이미지·경로 유지.

## Chapter 05

### Major Changes

- Section: 5.1–5.14 Reflection Models / Microfacet.
- Change: N/L/V 방향과 Unit Vector 조건, Reflection 성분 분해·수치 예제, Phong/Blinn-Phong Response 및 H의 경계, D·G·F 분모, NDF 밀도, Schlick/F0와 Metallic 관계를 보완. Surface 전체가 단일 Normal이라는 오류와 일률적인 성능 우열을 수정.
- Reason: Response, BRDF, Scene Visibility, Microfacet Geometry Term의 경계를 명확히 함.
- Section: 5.15–5.19 Radiometry / BRDF.
- Change: Power와 Energy·물리량 단위를 구분하고 BRDF의 dLo/dEi 정의, Rendering Equation, Lambert ρ/π·Cosine 분리 및 기본 검증을 작성.
- Reason: BRDF를 최종 밝기로 설명하는 Critical 오류를 수정하고 이후 Lighting 구현에 사용할 Primary Explanation을 마련.
- Source: Global Audit; Local Audit 04–06; Figure Audit; Technical Consistency.

### Structural Changes

- Move: Chapter 간 Major Section 이동 없음.
- Merge: 5.16–5.19의 동일 Model 목록 반복을 각 Section의 목적에 맞게 정리.
- Remove: 비어 있는 Status 제목을 Chapter Title로 교체. 19개 Major Section 유지.
- Heading: English 제목과 Chapter/Major/Internal 계층으로 정리. Part 구분은 본문 Label로 유지.

### Cross-Chapter Impact

- Related Chapters: 03, 04, 06, 07, 08.
- Follow-up Checked: 03의 Vector/Normal 규칙 및 04의 Material Property와 연결. 06의 Lighting/HDR, 07의 Rim, 08의 교육용 Response는 후속 Chapter 순서에서 일치 여부 확인 예정.

### Figure Follow-up

- Figure: Fig5_02/03/04/05/06/07/08/09/10/12/13/14.
- Required Action: Figure Recheck Required. Normal 방향, L=-Incident, Half Vector의 기여 Facet, NDF 밀도, D·G·F 및 Fresnel 각도 설명을 수정 Text와 대조. 이미지와 모든 기존 Figure 경로는 유지.

## Chapter 06

### Major Changes

- Section: 6.1–6.5 Lighting / Reflection.
- Change: BRDF와 Lighting 기여의 합류를 설명하고 Direct/Indirect와 Environment 표현 방식을 구분. Soft Shadow 경계와 간접광 Fill을 분리. Emission 예외와 Environment Specular의 한정된 사용 의미를 보완.
- Section: 6.1, 6.6–6.9 Architecture / HDR / Output.
- Change: Forward/Deferred 및 GBuffer 기본 설명, Roughness/Metallic 연결, Fixed Exposure 검증을 추가. HDR를 파일 형식·직렬 후처리 Stage와 구분. sRGB Input Decode/Linear Working Space/Display Output 역할 및 0.5→0.214 예제를 교정.
- Reason: Chapter 01의 GBuffer 예고와 Chapter 05의 BRDF 정의를 연결하고 Chapter 08의 Emission 관찰 조건을 마련.
- Source: Global Audit; Local Audit 04–06; Figure Audit; Technical Consistency.

### Structural Changes

- Move: Major Section 이동 없음.
- Merge: 없음. HDR Environment 입력과 HDR 처리 설명은 학습 목적이 달라 유지.
- Remove: 없음.
- Heading: Chapter Title 추가, 9개 Major Section 및 English Internal Heading 정리.

### Cross-Chapter Impact

- Related Chapters: 01, 04, 05, 07, 08, 09.
- Follow-up Checked: 01의 Forward/Deferred 예고를 해소하고 04의 Encoding/Decode 및 05의 BRDF·Rendering Equation과 일치시킴. 08의 지원 경로·Emission 조건과 09의 Pass 측정은 후속 검토 예정.

### Figure Follow-up

- Figure: Fig6_01/02/03/04/05/06/07/08/09/10.
- Required Action: Figure Recheck Required. 특히 Fig6_01/02/10의 직렬 흐름을 Lighting 기여 합류와 HDR 계산 영역으로 교정할 필요. sRGB 고정 출력·HDR 형식·Soft Shadow 표기를 확인. 이번 작업은 Text만 수정하고 이미지/경로 유지.

## Chapter 07

### Major Changes

- Section: 7.1–7.5.
- Change: PBR의 물리적 제약과 Stylized의 표현 목표를 배타적 분류에서 구분 가능한 축으로 수정. N·L/BRDF/Visibility 경계와 Threshold·Smoothstep·Ramp의 최소 정의를 보완. 물리적 Shadow가 항상 Soft하다는 오류 및 Rim=Fresnel 동일시 수정.
- Section: 7.6–7.9.
- Change: Hair Fiber/Scattering 범위, Face SDF의 Light 연결, Outline의 두 기법 계열과 Pass/Module 차이를 명확히 함. Chapter 08에서 아직 구현하지 않은 Hair/Face/Outline·Ramp 확장은 완료된 기능처럼 서술하지 않음.
- Reason: Chapter 05–06의 수정된 정의와 Chapter 08의 실제 교육용 구현 범위를 연결.
- Source: Global Audit; Local Audit 07–09; Figure Audit; Technical Consistency.

### Structural Changes

- Move: 없음. Hair/Face/Outline의 Foundation 개념 설명과 향후 Advanced 구현 경계 유지.
- Merge: 없음. Diffuse Remap과 Visibility의 다른 역할을 유지.
- Remove: 없음.
- Heading: 9개 Major Section 유지, English 제목 및 한 개 Chapter Title로 정리.

### Cross-Chapter Impact

- Related Chapters: 05, 06, 08, 09.
- Follow-up Checked: Fresnel/IOR는 05.14, Lambert는 05.19, Shadow/Exposure는 06과 일치. 08의 Phong/Rim 교육용 Interface와 미완성 Renderer 연결을 명시; 세부 구현 일치는 다음 Chapter 검토에서 확인 예정.

### Figure Follow-up

- Figure: Fig7_01/02/03/04/05/06/07/08/09.
- Required Action: Figure Recheck Required. PBR/NPR 배타 분류, Shadow의 Soft/Hard 단정, Rim=Fresnel, Outline 네 방식의 동등 나열 및 구현 완료 인상을 수정 Text와 대조. 기존 이미지/경로 유지.

## Chapter 08 — Checkpoint: Overview / 8.0 / 8.1

### Major Changes

- Section: Chapter Overview, 8.0, 8.1.
- Change: Module/Material Function/Renderer Stage와 Pass를 구분. Shared Inputs와 Lighting Branch 합류 및 Multiply/Add/Lerp 역할 교정. Chapter 09/10의 오래된 참조 수정. 목표 Engine/Deferred 설정과 실제 실행 검증을 구분하고 초기 측정 인식을 유지. Naming의 Primary는 ASF-001로 명시.
- Reason: 이후 구현의 정확한 Interface와 지원 경로를 검토할 기반 마련.
- Source: Global Audit; Local Audit 08; Figure Audit; ASF-001/002; Technical Consistency.

### Structural Changes

- Move/Merge/Remove: Major Content 이동·삭제 없음. Environment 반복 표는 설치와 확인 Context가 달라 유지.
- Heading: 8.0/8.1은 Major Section, 기존 8.0.x/8.1.x 내부 번호를 제거하고 English Internal Heading으로 정리.

### Cross-Chapter Impact

- Related Chapters: 04, 06, 07, 09.
- Follow-up Checked: 06의 GBuffer/Rendering Path와 07의 확장 범위 구분 반영. Chapter 08 전체는 아직 진행 중이며 8.2부터 실제 Interface를 계속 확인해야 함.

### Figure Follow-up

- Figure: Fig8_01/02/03/04/05/06.
- Required Action: 오래된 Chapter 흐름, 검증되지 않은 Engine 기본값, Fig8_03/04/05의 Setup/Architecture 문맥 재사용을 Figure 단계에서 수정 검토. 이미지/경로 유지.

## Chapter 08 — Checkpoint: 8.2 Base Lighting

### Major Changes

- Section: 8.2.
- Change: Surface→Light 부호, World Space/Unit Vector/0 Vector 조건, 세 Input과 Scalar D / Vector3 Lighting Result를 구분. Unlit Material과 Fixed Exposure의 기본 검증을 명시.
- Change: Deferred 설정에서 Forward Selected Directional Light를 무조건 사용할 수 있다는 서술을 수정. 명시적 LightDirection 입력을 기준으로 유지하고 Scene Light Adapter의 Space·부호·Node 지원·갱신을 별도로 검증하도록 구성.
- Reason: Engine 지원 조건의 충돌을 해결하고 Function 계산과 데이터 공급을 분리.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move: 없음.
- Merge: 실제 Light 연결의 반복 설명을 Reference Input / Adapter / Conditional Expression / Validation으로 Rewrite.
- Remove: 검증되지 않은 Engine 신구 지원 단정 및 실제 연결 검증 완료 단정 교체. 기본 구현과 두 단계 테스트는 유지.
- Heading: 내부 번호 제거, English 제목으로 정리.

### Cross-Chapter Impact

- Related Chapters: 03, 05, 06, 08.3–8.10.
- Follow-up Checked: 03의 Unit/Space, 05의 Direction Factor≠BRDF, 06 및 8.0의 Rendering Path와 일치. Specular는 별도 N/L/V Branch임을 명시. 후속 Function 계약은 순차 확인 예정.

### Figure Follow-up

- Figure: Fig8_24/25/26/27.
- Required Action: 세 Input/두 Output, Node 지원 경로와 L 부호, Unlit 검증 조건을 Figure와 대조. Fig8_26 정지 이미지로 Runtime Light 회전 검증을 단정하지 않음. 기존 이미지/경로 유지.

## Chapter 08 — Checkpoint: 8.3 Shadow

### Major Changes

- Section: 8.3 Shadow / Depth Comparison / Rendering Equation / Validation.
- Change: 물리적 Visibility와 Artistic Shadow Mask의 차이, Unit Ray Direction 및 Light까지의 검사 구간, Light View/Projection·UV·동일 Depth Encoding 조건, Depth 비교 Convention을 보완.
- Change: Li가 이미 차폐를 포함할 때 Vis를 중복 적용하지 않도록 수정하고 V/View와 Vis/Visibility 표기를 분리. Debug Mode 미확인 이미지와 Runtime 갱신 검증을 구분.
- Change: 올바르게 작성된 Per-light Visibility, PCF 비교 결과 평균, Renderer/Material 경계, 수동 Vis=1/0.5/0 검증을 유지. 현재 Base에만 Vis를 적용하는 합성은 교육용 Artistic 정책임을 명시.
- Reason: Renderer 구현 완료 오인 및 Depth/Visibility 의미 혼동 방지.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move: 없음.
- Merge: 동일한 10.0000/10.0001 Bias 예제와 Peter Panning 재설명은 앞의 상세 설명을 유지하고 후반 반복만 Reminder로 정리.
- Remove: 이미지/기본 구현/Validation 제거 없음.
- Heading: 8.3 Major 아래 내부 번호를 제거하고 English 계층 정리. 깊은 분기는 Bold Label로 유지.

### Cross-Chapter Impact

- Related Chapters: 02, 05, 06, 07, 08.2, 08.10.
- Follow-up Checked: 02의 Projection, 05.18의 Radiance/Visibility, 07의 Artistic Mask, 08.2의 BaseColor·D와 연결. 08.10의 동일 합성 정책은 후속 확인 예정.

### Figure Follow-up

- Figure: Fig8_28–38.
- Required Action: Depth/UV/비교 Convention, PCF, Per-light 기여, Debug Mode 및 동작 증거 범위를 수정 Text와 대조. 정지 이미지를 Runtime 검증 완료로 해석하지 않음. 이미지/경로 유지.

## Chapter 08 — Checkpoint: 8.4 Specular

### Major Changes

- Section: 8.4 Phong Specular / MF_Specular.
- Change: Clamp 후 Power와 양의 Shininess를 명시. 직접 계산한 Highlight를 Lit Material의 Specular Property Pin에 넣는 잘못된 설명을 Unlit Final Color 합성으로 교정.
- Change: Function은 Scalar Mask, Color/Intensity는 Master Material이라는 기존 올바른 Interface 유지. 교육용 Phong과 PBR BRDF를 구분하고 현재 ungated Artistic Mask의 Hemisphere 한계를 명시. 1, 0.25, 0.0625 기본 검증과 Fixed Exposure 조건 추가.
- Reason: Property와 Lighting Result의 경계 및 이전 Chapter의 Reflection 규칙 일치.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move/Merge/Remove: Major Content 이동·삭제 없음. Reflection 성분 설명은 05의 개념을 Node로 옮기는 새로운 Context이므로 유지.
- Heading: 8.4 Major 및 English Internal Heading, 내부 번호 제거.

### Cross-Chapter Impact

- Related Chapters: 03, 05, 06, 07, 08.8, 08.9, 08.10.
- Follow-up Checked: 동일 Space/정규화, Surface→Light, Phong 교육용 범위, Fixed Exposure와 일치. 후속 Material Layer/Debug/Composition에서 Mask와 외부 Color/Intensity 계약을 이어서 확인해야 함.

### Figure Follow-up

- Figure: Fig8_10/14/15/16/17/18/19/20/21/22/23/49.
- Required Action: Reflection 방향·Clamp 및 특히 Fig8_19의 Lit Specular Pin 연결과 현재 Unlit 합성 차이를 교정할 필요. 원본 Figure는 변경하지 않고 본문에 해석 범위 명시.

## Saved Checkpoint Validation — 2026-09-21

- Saved Scope: Chapter 01–07 및 Chapter 08 Overview/8.0–8.4. Chapter 08 전체와 Chapter 09는 아직 미완료.
- Next Work: Chapter 08.5 Rim Light → 8.6 MatCap → 8.7 Emission → 8.8 Material Layer → 8.9 Debug View → 8.10 Final Framework → Chapter 09 → 전체 Cross-Chapter 최종 검증.
- File Integrity: 시작 시점 SHA-256과 비교한 기존 파일 변경은 허용된 Foundation Markdown 13개뿐. Figure 이미지·Standards·DecisionLog/Roadmap·Audit Report 변경 및 기존 파일 누락 없음.
- Markdown Validation: 저장한 문서는 파일당 Chapter Title 1개, 미종결 Code Fence 없음, 한글/내부 3단 번호 Heading 없음. Overview의 중복 H1 한 곳 수정.
- Figure References: 전체 Foundation의 현재 HTML Image Reference 160개 모두 실제 경로 존재. Chapter 01의 중복 Section 정리에 따른 같은 Figure 참조 1건 제거는 해당 Chapter 로그에 기록. 이미지 파일/파일명/경로 변경 없음.
- Technical Validation Boundary: 문서의 수식·Interface·조건을 대조했으며 Unreal 프로젝트 Compile/Runtime 실행 검증은 수행하지 않음. Node 지원·Debug Mode·Figure 해석의 후속 확인 사항을 관련 Chapter에 기록.
- Remaining Completion Gate: Chapter 08.5 이후 수정, Chapter 09 수정 및 모든 후속 Interface 연결 확인 전에는 Phase 2를 Complete로 표시하지 않음.

## Chapter 08 — Checkpoint: 8.5 Rim Light

### Major Changes

- Section: 8.5 Rim Light.
- Change: Power Prototype과 Width/Softness 최종 계약을 구분. Unit/Space 및 Smoothstep 유효 범위와 Width=0/Softness=0 정책·수치 검증 추가. Binary Mask도 표시 폭 독립을 보장하지 않는 점과 Microfacet Fresnel의 V·H 각도를 명시.
- Reason: Concept/Data Flow/Implementation Interface의 기술적 일관성.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move/Merge/Remove 없음. 물리 Fresnel과 Artistic Rim의 비교, Unlit/Viewport 구분 및 Shadow 미연결 경계 유지.
- Heading: English 제목 및 Major/Internal 계층 정리.

### Cross-Chapter Impact

- Related Chapters / Follow-up Checked: 05.14/06.6/07.5 및 08.4와 일치. 후속 08.10에서 Width/Softness 계약 확인 예정.

### Figure Follow-up

- Figure: Fig8_39–48/50
- Required Action: 수정된 Text·Interface·검증 조건과 대조하여 Figure Recheck/Revision 필요. 이미지와 기존 경로는 변경하지 않음.

## Chapter 08 — Checkpoint: 8.6 MatCap

### Major Changes

- Section: 8.6 MatCap.
- Change: Camera Translation과 Rotation, Normal Z와 Position Depth, MatCap의 Unit Disk/UV/Axis Convention을 구분. sRGB Encoding 조건과 Blend/Intensity 끝값 교정. Light 입력은 검증된 World-space 공급으로 연결.
- Reason: Concept/Data Flow/Implementation Interface의 기술적 일관성.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move/Merge/Remove 없음. Texture Object/Sample 차이와 Lerp 기본 예제, Constant Alpha 및 선택적 MI Parameter 유지.
- Heading: English 제목 및 Major/Internal 계층 정리.

### Cross-Chapter Impact

- Related Chapters / Follow-up Checked: 02/04/06/08.2와 일치. Shadow는 수동 Vis 기준이며 Renderer 연결 완료 아님. 08.10에 동일 Lerp 계약 적용 예정.

### Figure Follow-up

- Figure: Fig8_51–58
- Required Action: 수정된 Text·Interface·검증 조건과 대조하여 Figure Recheck/Revision 필요. 이미지와 기존 경로는 변경하지 않음.

## Chapter 08 — Checkpoint: 8.7 Emission

### Major Changes

- Section: 8.7 Emission.
- Change: 논리적 Emission과 Engine Emissive Output 구분 보완. Fixed Exposure와 Presentation Auto Exposure 구분, Feedback 단정 교정. 전체 Texture≠현재 UV Sample의 R Scalar 계약을 유지. Color·Intensity·Mask 함수 내부 곱 및 MatCap Lerp 뒤 Add 유지. Mask=0은 로컬 기여만 0이며 Compression/Filtering 예외 명시.
- Reason: Concept/Data Flow/Implementation Interface의 기술적 일관성.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move/Merge/Remove 없음. Sampling 설명과 기본 Scalar/Texture 검증은 핵심 요구여서 유지.
- Heading: English 제목 및 Major/Internal 계층 정리.

### Cross-Chapter Impact

- Related Chapters / Follow-up Checked: 04.5/06.6/08.6과 일치. 최종 합성 Branch 및 MF_BaseLighting 명칭 통일.

### Figure Follow-up

- Figure: Fig8_59–67
- Required Action: 수정된 Text·Interface·검증 조건과 대조하여 Figure Recheck/Revision 필요. 이미지와 기존 경로는 변경하지 않음.

## Chapter 08 — Checkpoint: 8.8 Region Control

### Major Changes

- Section: 8.8 Region Control.
- Change: Region Parameter Lerp와 결과 Lerp를 구분. SpecularIntensity는 MF_Specular Input이 아니라 Mask 출력에 외부 Multiply하는 계약으로 수정. Outfit 및 Full Words Naming 정리. Material Slot은 이름이 아닌 Shading/Pass/비용 기준으로 판단.
- Reason: Concept/Data Flow/Implementation Interface의 기술적 일관성.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move/Merge/Remove 없음. Scalar 0/0.5/1, Texture Region 검증 및 Master 미통합 범위 유지.
- Heading: English 제목 및 Major/Internal 계층 정리.

### Cross-Chapter Impact

- Related Chapters / Follow-up Checked: 04의 Parameter/Texture Sample, 08.4의 네 Input/Mask Output 계약과 일치.

### Figure Follow-up

- Figure: Fig8_68–70
- Required Action: 수정된 Text·Interface·검증 조건과 대조하여 Figure Recheck/Revision 필요. 이미지와 기존 경로는 변경하지 않음.

## Chapter 08 — Checkpoint: 8.9 Debug View

### Major Changes

- Section: 8.9 Debug View.
- Change: Mode 5를 EmissionResult RGB로 모든 Architecture 표/흐름에 일치시킴. 정수 0–5 계약과 Else/비정수/음수/Equality Threshold 경계, Unlit 이후 표시 변환, If≠분기 보장 및 Runtime 0≠Compile 제거를 명시.
- Reason: Concept/Data Flow/Implementation Interface의 기술적 일관성.
- Source: Global Audit; Local Audit 08; Figure Audit; Technical Consistency.

### Structural Changes

- Move/Merge/Remove 없음. 여섯 Mode 기본 검증, 실제 데이터 공유, Shadow/Region 제외 및 기존 fallback 설명 유지.
- Heading: English 제목 및 Major/Internal 계층 정리.

### Cross-Chapter Impact

- Related Chapters / Follow-up Checked: 08.2 D Scalar /08.4 SpecularMask /08.5 RimMask /08.6 MatCapResult RGB /08.7 EmissionResult RGB와 일치.

### Figure Follow-up

- Figure: Fig8_71–72
- Required Action: 수정된 Text·Interface·검증 조건과 대조하여 Figure Recheck/Revision 필요. 이미지와 기존 경로는 변경하지 않음.

## Chapter 08 — Completion: 8.10 Final Framework

### Major Changes

- Section: 8.10 and Cross-Section Contracts.
- Change: Canonical Input/Output 표와 D/B/Vis/Specular/Rim/MatCap/Emission/Debug 계약을 추가. 직렬 MF 흐름을 Shared Input Branch 합류로 수정. BaseColor·D의 Multiply 및 MatCap Lerp 뒤 Emission Add를 전체 설명/검증에 일치시킴.
- Change: MatCapBlend는 Constant 또는 선택적 MI Parameter, ShadowVisibility는 수동 Test Input. Engine Light Adapter·Renderer Shadow·Physical Specular 지원과 교육용 계산의 범위를 구분.
- Reason: 앞 절의 실제 Interface와 최종 Architecture의 Critical 불일치를 해소.
- Source: Global Audit; Local Audit 08; Figure Audit; ASF-002; Technical Consistency.

### Structural Changes

- Move/Merge/Remove: Major Section 유지. 앞 절의 구현을 다시 설명하는 내용은 최종 Contract/검증 관점으로 연결하며 불확실한 대규모 삭제 없음.
- Heading: English 제목, 8.10 Major 및 내부 번호 제거.

### Cross-Chapter Impact

- Related Chapters: 03–07, 08.0–8.9, 09.
- Follow-up Checked: Unit/Space, BRDF≠Artistic Response, Fixed Exposure, sampled Scalar Mask, Specular 외부 Color/Intensity, Rim Width/Softness, MatCap Lerp, Emission RGB 및 Debug Mode 0–5 일치. Chapter 09의 측정/Runtime Cost 연결은 다음 작업.

### Figure Follow-up

- Figure: Fig8_73/74, 관련 Fig8_03/04/05/19/24/26/27/48/58/67/71/72.
- Required Action: 직렬 흐름·단순 Add·Lit Specular Pin·Engine 지원·Placeholder Visibility 및 타입을 본문과 맞추는 Figure Revision 필요. 이미지/경로는 그대로 유지.

## Chapter 09 — Technical Corrections Checkpoint

### Major Changes

- Frame Timing을 실제 실행/대기/동기화와 구분하고 반복 측정 조건 및 기록 표 추가. 모든 Timing 수치는 교육용 예시임을 명시.
- Triangle/Vertex 지표, Pass 중첩, Masked/Translucent, GPU-driven 가능성, View/Pass별 Culling 범위를 교정.
- Lerp 입력 흐름, Full-screen Triangle 수, 2×2 Quad/Helper 설명 수정. LOD 비교에서 Culling을 고정하여 한 변수만 변경.

### Structural Changes

- 9.1/9.2 Major Heading 깊이를 통일하고 한국어 Heading 3개를 English로 변경. 기존 9개 Major Section과 기초 실험 흐름 유지.

### Cross-Chapter Impact

- Chapter 06의 Exposure/내부 해상도 조건과 Chapter 08의 Runtime Debug/Static Switch 비용 설명 연결.
- Unreal Tool의 출처 링크 및 전체 문서 최종 검증 진행 중.

### Figure Follow-up

- Quad, Pass Cost, Culling 및 측정 비교 Figure는 본문의 조건과 대조하는 후속 Revision 대상. 이미지와 경로는 수정하지 않음.

## Chapter 09

### Major Changes

- Section: 9.1–9.9.
- Change: Frame/CPU/GPU 처리·대기 구분, 비교 조건·반복 측정 기록, Pass 중첩 및 인과 판단을 보완. Triangle/Vertex, Pixel/Shader, Masked/Translucent, Quad/Helper, Draw Submission, LOD/Culling 경계 정리.
- Change: 잘못된 Lerp 도식과 Full-screen Triangle 수를 수정. Tool 출처의 비정상 인용 Token을 확인 가능한 Epic 문서 링크로 교체하고 Version/Build별 지원 확인 및 미실행 범위를 명시.
- Change: Character 분류를 Outfit으로 통일. 가상 Timing 숫자를 실측과 구분.
- Reason: 비용 지표와 실제 병목을 혼동하거나 복합 변경을 단일 원인의 증명으로 읽는 문제를 해결.
- Source: Global Audit B31–B36/W14–W15; Local Audit 07–09; Figure Audit; Technical Consistency; Epic official documentation (2026-09-21 확인).

### Structural Changes

- Move: None.
- Merge: None. 9.9의 종합 Workflow는 학습 마무리의 Necessary Reinforcement로 유지.
- Remove: 비정상 인용 Token만 실제 출처 링크로 교체. Major Section 삭제 없음.
- Heading: 9.1/9.2 깊이 및 English 제목 통일. 기본 측정 기록 표 추가.

### Cross-Chapter Impact

- Related Chapters: 01–08.
- Follow-up Checked: 01의 2×2 Quad, 04의 Static/Runtime Parameter, 06의 Exposure, 08의 Debug 표시와 Runtime Cost가 09의 측정 관점으로 연결됨.
- Final QA correction: 8.10에 Basic Contract Checks의 예상값을 추가하고 Module/Function 책임 구분을 한 문장 보완. 실제 Engine 검증 완료로 기록하지 않음.

### Figure Follow-up

- Figure: Fig9_01/02 — 가상 Timing/병목 라벨 및 Frame 의존 관계 수정 필요.
- Figure: Fig9_04 — 투명 합성과 Pixel Cost의 인과를 Blend Mode/조건과 일치시킬 것.
- Figure: Fig9_07 — Frustum Culling 문장 반전 및 Pass별 가시성 경계 수정 필요.
- Figure: Fig9_08 — 실행 명령·화면 출처·Version과 병목 해석 조건 확인 필요.
- Figure: Fig9_03/05/06/09 — 기존 Figure Audit의 후속 항목 유지. 이번에 이미지 자체를 재검토·수정하지 않음.

## Final Verification — 2026-09-21

### Audit Coverage

| Global Priority | Refactoring Location / Resolution |
|---|---|
| GI-01 / BRDF, Lighting Result, HDR | 04의 Material 입력, 05의 응답·단위·Rendering Equation, 06의 기여 합류와 표시 변환을 구분 |
| GI-02 / Branch and Composition | 8.1–8.10의 공유 입력 Branch, Base Multiply, MatCap Lerp, Emission Add, Debug 0–5 계약 일치 |
| GI-03 / Phong and Specular Pin | 8.4의 Artistic Scalar Mask와 외부 Color/Intensity 및 Unlit 합성 구분; Lit Specular 핀의 모델 교체로 설명하지 않음 |
| GI-04 / Direction and Matrix | 02의 column-vector convention, 03의 Unit/Space/영벡터 및 L/V 방향, 05·08 소비 관계 확인 |
| GI-05 / Shadow Scope | Shadow Map/Compare/Visibility 구분; 8.3·8.10의 수동 Vis 실습과 Renderer Shadow 통합 분리 |
| GI-06 / Engine Support | 명시적 LightDirection을 기본 계약으로 정리; Forward Expression/Adapter 및 실제 Engine 지원은 실행 검증 대상으로 유지 |
| GI-07 / Reflection Foundations | 05에 기본 반사 수식·응답 단위·Lambert/Rendering Equation 기반, 06에 Forward/Deferred/GBuffer 최소 설명 보완 |
| GI-08 / Display and Evidence | 06 Exposure, 8.7 Emissive/Bloom, 8.9 Debug 표시, 8.10 예상값 및 미실행 범위 정리 |
| GI-09 / Visibility and Measurement | 09의 Pass별 Culling, 처리/대기, 복합 Probe, 한 변수 비교 및 가상 Timing 구분 |
| GI-10 / Repetition and Ownership | Chapter 01의 중복 1.10 정리, 02·04·05·8.3의 확인된 반복 재구성; 새 맥락의 구현·검증·종합 반복 유지 |

### Concept Source of Truth

- Pipeline/Attribute 기본은 01, Space/Transform은 02, Normal/벡터 계산 계약은 03, Sample/Material 입력은 04에 유지.
- Reflection/BRDF의 상세 기반은 05, Light 기여와 HDR/Exposure/출력 관계는 06, Stylized 재해석은 07에 유지.
- 실제 Function Interface와 기본 합성·검증은 08, 비용 원인과 측정 Workflow는 09로 연결.
- 03/05/06 전체 Chapter 이동이나 제목 체계 재설계는 수행하지 않음. Accepted Decision 및 Global Audit의 실제 역할을 따름.
- Foundation의 Basic Implementation/Validation/Debug는 보존. Production Case Study, Renderer 통합 및 복잡한 최적화 실험은 완료된 기능으로 추가하지 않음.

### Verification Results

- Foundation Markdown: 20개 수정 및 저장 완료, Chapter 01–09 범위.
- Heading: 모든 문서에 Chapter H1 한 개, 내부 다단계 번호·한국어/Hanja Heading 없음. Chapter 08 Overview는 개요 문서이며 번호 있는 Major Section은 별도 파일에 유지.
- Code Fences: 20개 문서에서 닫힘 확인.
- Figure References: HTML 이미지 참조 160개 전부 유효한 파일로 연결. Chapter 01 중복 Section에서 같은 Fig1_10 참조 하나를 제거한 변경 외 Figure 경로 변경 없음.
- File Integrity: 시작 시점 194개 파일 중 허용된 Foundation Markdown 20개만 변경. 나머지 174개 파일의 SHA-256 동일, 삭제된 파일 없음. 새 파일은 이 Refactoring Log 한 개.
- Terminology: Character Outfit, MF_BaseLighting/MF_MatCap/MF_DebugView 및 Anime Shader Framework 표기 대조. 실제 파일명과 Figure 파일은 유지.
- Arithmetic: Rim Smoothstep 0/0.5/1, 수동 Vis 1/0.5/0 및 Lerp 양 끝점의 예상값 확인. Unreal 실행 테스트가 아님.
- Final QA의 8.10/09 보완은 앞선 Chapter를 다시 처음부터 Refactoring한 것이 아니라 합성 계약 및 지표 설명의 마지막 일치 확인으로 수행.

### Remaining Verification and Figure Work

- 이번 Phase 2의 문서 수정 범위는 완료. Unreal Editor/실제 Project를 실행하지 않았으므로 Compile/Runtime 지원, Light Adapter, Renderer Shadow 공급, Platform별 Timing과 Output은 검증 완료로 주장하지 않음.
- Chapter별 Figure Follow-up에 기록한 Revision/Replacement와 신규 Figure 제작은 후속 이미지 작업. 기존 Figure에 남은 내용상 오류를 이번에 해결한 것으로 간주하지 않음.
- 모든 기존 Standard, DecisionLog, Audit Report, 이미지 및 외부 원본은 수정하지 않음.


# Refactoring Progress

Completed:
- Chapter 01
- Chapter 02
- Chapter 03
- Chapter 04
- Chapter 05
- Chapter 06
- Chapter 07
- Chapter 08
- Chapter 09

Current:
- None — text refactoring complete

Next:
- None — Phase 2 text scope complete

Status:
Complete
