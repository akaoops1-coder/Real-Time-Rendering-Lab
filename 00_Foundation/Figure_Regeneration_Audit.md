# Figure Regeneration Audit — Chapters 01–04

검토일: 2026-10-02. 사용자가 선정한 12개 PNG의 최종 선택본과 Caption 연결을 기록한다. 기존 Chapter / Figure 번호, 파일명과 저장소 경로를 유지하며 새 BRDF 내용이나 알고리즘 범위를 추가하지 않았다. 이 문서의 검수 완료는 이미지의 문자·수식·개념·화살표를 확인했다는 뜻이다.

## 변경 결과

| Figure | 이전 문제 | 최종 수정 | 검수 결과 |
|---|---|---|---|
| Fig1_12 | `Send to GPU`와 Data 목록이 매 Draw 전체 Buffer 업로드처럼 읽히고, Character / Editor의 실행 출처가 불명확했다. | Create / Upload, Bind / Reference, Submit Draw를 분리했다. Resource 수명과 재사용, 매 Draw 전체 업로드가 아님, Object의 Section / Pass / Instancing별 여러 Draw를 표시했다. Color / Depth Writes에서 Output Targets로 기록한 뒤 표시용 Color가 후처리 / Present로 이어지도록 했다. | 정적 검수 완료. Scene / Monitor는 Concept Illustration. |
| Fig1_13 | Object / Bounds Frustum 선별의 고정 GPU 배치, Framebuffer와 개별 Render Target 혼동, 작은 Label과 Stage 묶음이 있었다. | Frustum 선별을 CPU 또는 GPU에서 가능한 Preparation / Selection으로 분리했다. Backface / Clipping, Processing Groups, Output Bindings Container와 Color / Depth / Other Resources를 구분하고 Post Process부터 Present까지 연결했다. | 정적 검수 완료. 실제 Pass / 실행 순서 고정 아님. |
| Fig2_11 | Matrix의 일반 정의가 Space Conversion만으로 제한되어 읽힐 수 있었다. | 일반 Transform 규칙을 적용하는 도구로 정의하고 같은 Space의 Scale / Rotation을 표시했다. Column Vector의 M=T·R·S와 적용 S→R→T, p_clip=P·V·M·p_local, Divide 전 Clip w를 유지했다. | 수식·Convention·화살표·Panel 검수 완료. |
| Fig2_13 | Normal을 실제 Face에 수직인 방향으로 일반화할 수 있었다. | Geometric Normal과 Shading Normal을 별도 그림으로 구분했다. Translation 제외, Non-uniform Scale, Affine의 가역 3×3 A에 대한 normalize((A⁻¹)ᵀ·n) 조건을 표시했다. | Normal 의미·수식·조건 검수 완료. |
| Fig2_14 | Basis N과 Face Normal, TBN 역행렬 조건, Raw Decode와 Sampler 출력의 범위가 불명확할 수 있었다. | Basis N은 Vertex / Shading Normal일 수 있음을 표시했다. 목표 Space의 T/B/N 열벡터, 정규직교일 때만 inverse=transpose, Handedness / UV Seam / 재직교화 / Non-uniform Scale 조건, 이미 Decode한 출력의 중복 Decode 금지를 명시했다. | 수식·기준 Space·Korean Label 검수 완료. |
| Fig2_15 | EngineVerificationRequired 상태의 Node / Coordinate Space 그림이 실제 Unreal Graph 실행 자료처럼 읽힐 수 있었다. | Unreal 실행 Screenshot이 아닌 개념도로 교정했다. ObjectPositionWS의 Bounds Center, VertexNormalWS / PixelNormalWS, Surface→Camera의 CameraVectorWS, ViewportUV / SceneTextureUV, 자동 변환과 명시 World 연산을 구분했다. | 개념도·Label·화살표 검수 완료. 실제 Graph 실행 미검증. |
| Fig3_02 | Footer의 Dot Product Section 번호가 현재 본문과 달랐다. | `3.2 Dot Product`를 `3.3 Dot Product`로 교정했다. Figure 번호, Signed / Clamped 값, 일반 Dot / Unit Dot 공식과 최종 밝기 구분을 유지했다. | Footer·숫자·기존 범위 검수 완료. |
| Fig3_05 | Position 차이로 만드는 View Direction이 모든 Camera에 적용되는 것처럼 읽힐 수 있었다. | Perspective 예제 Label과 Orthographic의 평행 Viewing Ray 반대 방향 V=normalize(−Dview)를 분리했다. Point / Spot 예제 범위, Directional 부호, Spot Cone, 같은 Space / Unit / Zero-length 조건을 유지했다. | Projection별 방향·수식·적용 범위 검수 완료. |
| Fig3_06 | Light / View 입력을 준비하는 Position 차이 경로가 일반화되어 있었다. | 표의 L을 Point / Spot, V를 Perspective 예제로 명시했다. Directional / Orthographic 대체 경로를 추가하고 같은 Lighting Space의 Unit Vector 조건, Normal 변환과 World / View 비교를 유지했다. | Input 경로·Space 비교·Normal 공식 검수 완료. |
| Fig4_04 | Affine 숫자와 표시점 불일치, 대칭 Pattern의 Addressing 비교, Mip / Encoded Normal / Filtering 표현 문제가 있었다. | 표시점 대신 별도 Affine Box에 A .35 / B .03 / C .62 → UV(.34,.62)를 표시했다. 네 Texel Center와 Bilinear 가중치 합 1, Screen footprint Mip, Encoded RGB, 비대칭 ABC의 Wrap / Clamp / Mirror를 구분하고 중복 문구를 정리했다. | 최종 숫자 Box·Pattern·Sampling 관계 대조 완료. |
| Fig4_05 | sRGB Decode의 값 / Curve / 밝기 방향, `No Conversion`, 합성 Checkbox와 자동 Decode 범위가 잘못 읽힐 수 있었다. | 저장 .50 → Linear 약 .214를 Linear .500과 구분하고 Decode Curve를 y=x 아래에 표시했다. 잘못 Decode된 낮은 Roughness가 더 Glossy해지는 관계, No sRGB Decode의 한정 의미, Asset Encoding과 Sampler Type, 이미 Linear / HDR 예외와 중복 Decode 금지를 명시했다. | 수치·Curve·Appearance 방향·설정 의미 검수 완료. |
| Fig4_06 | EngineVerificationRequired 상태에서 Raw RGB와 이미 Decode한 Normal 출력, Space 변환과 Basis 방향이 혼합될 수 있었다. | Unreal 실행 Screenshot이 아닌 개념도로 교정했다. Raw RGB Decode와 이미 Decode한 Sampler 경로, 같은 Space의 Unit N/L, World Lighting 예제의 TBN 흐름, Encoded RGB / 복원된 Unit Direction, 저장 / 계산 Space를 구분하고 화면 방향 문구를 제거했다. | 개념도·수식·분기·조건 검수 완료. Engine Sampler 실행 미검증. |

기존 오류와 수정 과정을 이 표에 이력으로 남긴다. 재생성 후 해소된 오류를 현재 Figure의 미해결 문제처럼 설명하던 Caption은 새 이미지의 읽기 안내로 바꾸며, 기존 기술 적용 조건과 구현 확인 범위는 유지한다.

## 제작 방식과 개념도 범위

Built-in `image_gen__imagegen`의 **Edit Mode**를 사용했다. 각 원본을 `view_image`로 먼저 확인하고 원본 PNG를 Edit Target으로 지정했다. 이후 후보의 실제 Pixel을 검토하여 필요한 부분만 같은 도구로 교정했다. 기본·표적 교정 Prompt 전체는 [Figure_Regeneration_Prompts.md](Figure_Regeneration_Prompts.md)에 보관한다.

Navy Header, White Panels, English 기술 제목과 Korean 설명, 기존 정보 범위와 관계를 유지했다. **Chapter02의 네 Figure는 Text Panel의 가독성을 위해 1586 × 992 가로 Layout으로 재배치했다.** 원본과 최종 비율은 부록에 나란히 기록하며, 원래 비율을 그대로 보존했다고 주장하지 않는다. 나머지 8개는 원본 Pixel 크기까지 동일하다. 이 Layout 재배치를 Engine 동작의 변경으로 해석하지 않는다. Figure 파일명 / 경로 / 번호와 본문의 `width="90%"`는 유지한다.

Character, Scene, Sphere, Data Flow와 Appearance 비교는 학습 관계를 설명하는 개념 삽화다. 특히 이전에 EngineVerificationRequired로 분류했던 **Fig2_15와 Fig4_06는 실행 결과를 주장하지 않는 개념도로 교정했다.** 실제 Unreal Editor / Material Graph Screenshot이나 프로젝트 실행 Capture로 보증하지 않는다.

Unreal Engine 실행, Material / Shader Compile, Render Capture, GPU Profiling은 수행하지 않았다. 대상 Engine Version / Stage / Pass, Node 옵션과 출력, Sampler / Compression / Format, Tangent Basis와 Handedness, Non-uniform Scale, Early Depth / Write 설정 등은 본문의 구현 조건을 따라 별도 확인한다. 이미지의 정적 교정은 그 실행 검증을 대신하지 않는다.

## 시각·기술 검수

각 담당자는 원본과 최종 PNG를 직접 열어 확인했고, 최종 선택본은 Root와 독립 Reviewer의 대조를 거쳤다. Figure 번호·제목·주요 Panel, Korean / English Label, 수식과 수치, 화살표 방향, 관계가 유지되는지와 문자 잘림 여부를 확인했다. 최종 12개에서 남은 필수 이미지 교정 항목은 발견되지 않았다.

생성 중 발견한 문제도 교정 이력으로 남긴다.

- Chapter01: 잘못된 Present / Output Connector, Resource 수명 표현과 중복 Recap, Frustum 안에 놓인 제외 Object, Index Buffer 필수처럼 보이는 Bullet, Post Process를 우회하는 표시 Arrow를 표적 교정했다.
- Chapter02: Fig2_14의 UV Seam 글자, Fig2_15의 Surface→Camera와 UV 입력 Arrow, Engine 자동 처리 단계의 중복 금지 문장을 교정했다.
- Chapter03: 초기 Edit 결과의 Section 번호, Light / Camera 적용 범위, 기존 수식과 Space 비교를 확인했다. 추가 Pixel 교정은 필요하지 않았다.
- Chapter04: Affine 숫자를 별도 Box로 분리하고 비대칭 Address Pattern, Decode Curve / Point, Same-Space Unit 조건, Local Basis 방향 Label과 저장 / 계산 Space Checklist를 최종 대조했다.

Python으로 이미지를 생성·편집·합성하거나 문자를 덧씌우지 않았다. 일반 파일 도구와 읽기 전용 메타데이터 도구는 복사, PNG 크기 / Hash 확인에만 사용했다.

## 본문 Caption 연결

Caption 변경안은 정확한 기존 Block과 대체 Block을 LF 줄바꿈으로 보관했다. 각 Chapter의 이미지 경로와 기술 흐름을 유지하며 Figure 주변 읽기 안내만 갱신하는 범위다. Chapter04의 최종 PNG 대조는 완료되었다.

| Chapter | Caption Block 수 | 연결 내용 |
|---|---:|---|
| 01 | 2 | Resource 생성 / 참조 / 제출, Processing Groups, 별도 Buffer, Concept Illustration과 검증 범위 |
| 02 | 4 | 일반 Matrix 도구, Geometric / Shading Normal, Basis N, Unreal Data 개념도 |
| 03 | 3 | Dot Product Section 번호, Perspective / Orthographic, Point / Spot / Directional 준비 범위 |
| 04 | 3 | Affine 숫자 / Sampling 조건, Encoding / Sampler 의미, Raw / Decoded Normal와 Lighting Space |

원본 오류의 이력은 이 Audit에 남기고, 본문에는 수정된 Figure와 일치하는 현재 설명 및 구현 조건을 사용한다. 기존 Rewrite의 Stage 흐름이나 기술 Caveat를 제거하는 변경은 포함하지 않는다.

## 보존과 무결성

원본 12개 PNG는 `work/figure_baseline/Chapter01..04/`에 보존했다. `figure_regeneration_baseline.json`의 SHA256과 각 보존본을 대조하여 **12/12 일치**를 확인했다. 최종 선택본은 `work/figure_regenerated/Chapter01..04/`에 따로 저장했고, 부록에는 저장소 적용 경로와 최종 선택본 Hash를 구분하여 기록한다.

최초 `backup_manifest.json`의 161개 PNG 중 선정한 12개를 제외한 **149개 PNG**를 Staging 저장소와 Local 원본에서 각각 대조하여 모두 기존 SHA256과 일치함을 확인했다. Chapter05와 Chapter01–04의 네 Backup도 두 위치에서 기준 Hash와 모두 일치했다. 이 기록 문서 작성 과정은 Chapter 본문, 기존 Rewrite Audit, PNG, Chapter05, Backup 또는 Desktop 파일을 수정하지 않았다.

## 부록 A — 경로와 크기

저장소 적용 경로는 아래 표와 같고, 실제 최종 선택본은 각 행의 `Figures/` 대신 `work/figure_regenerated/`를 기준으로 `ChapterXX/파일명.png`에 보관한다. 예: `work/figure_regenerated/Chapter01/Fig1_12.png`.

| 적용 대상 경로 | 원본 Pixel 크기 | 최종 Pixel 크기 | 최종 Bytes | 크기 관계 |
|---|---:|---:|---:|---|
| `00_Foundation/Figures/Chapter01/Fig1_12.png` | 1536 × 1024 | 1536 × 1024 | 1,907,469 | 동일 |
| `00_Foundation/Figures/Chapter01/Fig1_13.png` | 1536 × 1024 | 1536 × 1024 | 1,974,796 | 동일 |
| `00_Foundation/Figures/Chapter02/Fig2_11.png` | 1448 × 1086 | 1586 × 992 | 1,471,499 | 가독성을 위한 가로 재배치 |
| `00_Foundation/Figures/Chapter02/Fig2_13.png` | 1448 × 1086 | 1586 × 992 | 1,566,445 | 가독성을 위한 가로 재배치 |
| `00_Foundation/Figures/Chapter02/Fig2_14.png` | 1312 × 1199 | 1586 × 992 | 1,820,982 | 가독성을 위한 가로 재배치 |
| `00_Foundation/Figures/Chapter02/Fig2_15.png` | 1536 × 1024 | 1586 × 992 | 1,878,243 | 가독성을 위한 가로 재배치 |
| `00_Foundation/Figures/Chapter03/Fig3_02.png` | 1536 × 1024 | 1536 × 1024 | 1,591,100 | 동일 |
| `00_Foundation/Figures/Chapter03/Fig3_05.png` | 1491 × 1055 | 1491 × 1055 | 1,740,718 | 동일 |
| `00_Foundation/Figures/Chapter03/Fig3_06.png` | 1536 × 1024 | 1536 × 1024 | 1,857,969 | 동일 |
| `00_Foundation/Figures/Chapter04/Fig4_04.png` | 1536 × 1024 | 1536 × 1024 | 2,051,347 | 동일 |
| `00_Foundation/Figures/Chapter04/Fig4_05.png` | 1536 × 1024 | 1536 × 1024 | 1,962,037 | 동일 |
| `00_Foundation/Figures/Chapter04/Fig4_06.png` | 1536 × 1024 | 1536 × 1024 | 2,067,740 | 동일 |

## 부록 B — 최종 선택 PNG Hash

| Figure | 최종 선택 PNG SHA256 |
|---|---|
| Fig1_12.png | `958c351aadf192df67f6b58b84af7f2846cdf09ddaad7c9dfcca9ca8bb12fe44` |
| Fig1_13.png | `7ec02982bc203f52d2907716180a971fcb3c01078e75ea4566cfc115082bb54c` |
| Fig2_11.png | `1a1e5e210b3eef7de5321e26ed65e6ca9f1e05a25085e8759fb3d86bc659cd16` |
| Fig2_13.png | `d4e39786a2aeb6ad12b321d6020d406c676b57e60ea027463ddc0b6e3bc12e24` |
| Fig2_14.png | `56586ab420d51ef84bb66ffdcbc375886ac2bae96b1ecbfc0607ef477e9ef3c0` |
| Fig2_15.png | `46483411d3ddbd947099c21e6a9eb4ce75c9481a127406f217e9edd001f3d839` |
| Fig3_02.png | `bb5ddb49805961e310065c48081f649bef296e80c3522f7ce01f91f60dfbd27b` |
| Fig3_05.png | `ead8fa6dc79d1670fe3f958daaeb3d02d8aa5976789e484a15e814a96be85424` |
| Fig3_06.png | `34c33e1624b6f5323934a73c9098fee8510c5130558eac599ff9b41b715cc617` |
| Fig4_04.png | `e65dc3254f130054be38efcd68bbf9793abe6c925f65d40aa789f33ae2d51b8f` |
| Fig4_05.png | `202ba986620367ee5afb355e9ed1aaac17d94a2019905a961e68a4065c37aa85` |
| Fig4_06.png | `469c60788990b23d9a53f74c17ac2515e8e62f9e99d7d89e8eeb46a640f53df9` |

## 부록 C — 보존 원본 PNG

아래 `work/` 경로는 이 작업의 Workspace를 기준으로 한다. Workspace: `C:/Users/kmcoo/Documents/Codex/2026-10-01/files-pasted-by-the-user-astra/`.

| 보존 원본 경로 | 원본 Bytes | 원본 SHA256 |
|---|---:|---|
| `work/figure_baseline/Chapter01/Fig1_12.png` | 1,797,631 | `92c5ecb6652cfdc183a21b47789c0c2b2c98eb8ef0e45c2d1632f06baf2ed8e2` |
| `work/figure_baseline/Chapter01/Fig1_13.png` | 1,852,297 | `b0597cada3666f3d6af74c6be2f00e2f1b055fcda862c4850c961a6a005efa02` |
| `work/figure_baseline/Chapter02/Fig2_11.png` | 1,438,443 | `14425ddb29e369df3b0025b7afd74f3def404281185e1e52c883f7cb350248c2` |
| `work/figure_baseline/Chapter02/Fig2_13.png` | 1,624,533 | `b0fd2604ccb9a46108e568d409f31f500898b05a29f9261d01428f67fd4f5cfa` |
| `work/figure_baseline/Chapter02/Fig2_14.png` | 1,731,193 | `242208c58508f803bb70284e4d26a7848a6968adeca11b566f3cec2fed59784b` |
| `work/figure_baseline/Chapter02/Fig2_15.png` | 1,907,819 | `d3b9997194b36b15a80440e6f8e05f87d952899b6ab84e5242f6370a10a7bd33` |
| `work/figure_baseline/Chapter03/Fig3_02.png` | 1,608,204 | `77189f4341b07ef32ca5d673880831ea2144ee8e98a7775cd44482b8f61944e0` |
| `work/figure_baseline/Chapter03/Fig3_05.png` | 1,711,598 | `1a730761e07312c5989ae805cd5a2a6546d5ac9d3664f42cb04c6f1d210f1d6d` |
| `work/figure_baseline/Chapter03/Fig3_06.png` | 1,809,118 | `f6b863148fc978de6a771f95a54343b02f3f4adbea507cf59ea20a564182bdbf` |
| `work/figure_baseline/Chapter04/Fig4_04.png` | 1,844,952 | `6ae1ed225155f68187048b70eab2a941a2eae7b563d41497d26ef201350aca13` |
| `work/figure_baseline/Chapter04/Fig4_05.png` | 1,868,229 | `00ff7e6174ac15f0077e017bc6a984399031e56f1d188632f55008ab8a62a540` |
| `work/figure_baseline/Chapter04/Fig4_06.png` | 1,963,270 | `741a38a1c3e28b111a24b5859d7cb1c41196acf5bb0fe6a4228613b56bfe73b6` |

## 부록 D — Chapter05와 Backup 보존 Hash

| 보존 문서 | SHA256 | Staging / Local 원본 대조 |
|---|---|---|
| `Chapter01_RnderingPipeline_backup.md` | `02a4444ae3b6ce81336a60ebfc81eb6022fa1e4f5ece075b7ccb23acb546f4a4` | 일치 / 일치 |
| `Chapter02_CoodinateSystem_backup.md` | `1660acd06167bd3d6f49526abd2f9c32529b0e1fd15d7b040d5207bb6b36e48b` | 일치 / 일치 |
| `Chapter03_LightingMathematics_backup.md` | `30a6a3e0ae810655666b8db3819bf45c4a8852d5fc45c5ce01f35a51d8569db5` | 일치 / 일치 |
| `Chapter04_MaterialArchitecture_backup.md` | `230fbc4c2e4711d19ae622ac59f26d678f07ed32c06fab409a3d8656d25a5f4a` | 일치 / 일치 |
| `Chapter05_Reflection_BRDF.md` | `19fb6dd1746e56923619d549f40499612cd0ac2667b3c174ec70979c96ef9abb` | 일치 / 일치 |

## 기록 근거

통합 근거는 Chapter별 `figure_review_ch01..04.md`, `figure_prompts_ch01..04.md`, `figure_prompts_ch04_corrections.md`, `figure_caption_changes_ch01..04.json`, `figure_regeneration_baseline.json`, `backup_manifest.json`, 최종 PNG 메타데이터 대조다. 상세 원문 Prompt는 동봉 문서에 포함했다.

