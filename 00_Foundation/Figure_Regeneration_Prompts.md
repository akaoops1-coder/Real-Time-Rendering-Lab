# Figure Regeneration Prompts — Chapters 01–04

기록일: 2026-10-02. 사용자 승인 범위의 12개 PNG에 사용한 기본 및 표적 교정 Prompt 원문을 Chapter01 → Chapter02 → Chapter03 → Chapter04 → Chapter04 후속 교정 순서로 통합한다.

Tool: Built-in `image_gen__imagegen`. Mode: **Edit**. 기존 PNG를 먼저 `view_image`로 확인한 뒤 Edit Target으로 지정했다. 후속 교정은 앞선 생성 후보를 Edit Target으로 사용했다. 각 Figure는 별도 호출이며 불투명 배경을 유지했다. CLI/API 대체나 Python 이미지 편집은 사용하지 않았다.

아래는 제작 과정의 원문 기록이다. 초기 지시와 후속 교정이 함께 있으므로 최종 선택본은 가장 나중의 해당 교정과 검수 결과를 기준으로 읽는다. Chapter02의 원문 파일은 표적 QA Edit를 기본 Prompt보다 앞에 기록한 순서를 그대로 유지한다. 문서 Heading의 깊이만 통합 구조에 맞췄고, Prompt 문장과 수식은 수정하지 않았다. 원본 비율과 최종 크기, 확정 PNG Hash 및 개념도 / Engine 미실행 범위는 [Figure_Regeneration_Audit.md](Figure_Regeneration_Audit.md)에 기록한다.

이전 Fig2_15와 Fig4_06의 Engine 확인 항목은 실제 Unreal Screenshot을 합성하여 해결한 것이 아니라, 실행 결과를 주장하지 않는 개념도로 교정했다. Unreal Editor 또는 Material Graph를 실행·검증했다는 Prompt나 결과 주장은 포함하지 않는다.

---

## Chapter 01 Figure Regeneration Prompts

Built-in `image_gen__imagegen` 사용. Python 이미지 편집 없음. 원본 PNG를 먼저 시각적으로 확인한 후 Reference로 사용한다. 최종 파일 선택 전에는 기존 Figure를 덮어쓰지 않는다.

### Fig1_12 — initial regeneration

Use case: scientific-educational / infographic-diagram.
Asset type: Korean ASF Foundation textbook figure, landscape 3:2, high-resolution PNG, opaque white background.
Input image: the supplied Fig1_12.png is the edit target and information/style reference. Regenerate the figure with a corrected clearer layout. Preserve its educational information scope and ASF palette, but replace photographic character/editor panels with simple clearly labelled concept illustrations. This is a conceptual diagram, not a verified screenshot or a specific engine implementation.

Primary request: create a beautifully legible educational infographic titled exactly "Fig1_12. CPU, GPU and Draw Calls". Match the existing ASF textbook visual family: dark navy header, white panels with softly tinted blue/green/orange/purple headers, crisp blue/green directional arrows, restrained vector-style geometry/mesh/material/monitor icons, English technical labels and natural Korean explanation text. Spacious four-column main layout, moderate readable text sizes, no cramped microtext. Preserve the original landscape ratio. Use a contemporary clean Korean sans-serif font, all words correctly spaced and spelling exact.

Teaching flow: CPU preparation → binding/resource references + draw-command submission → GPU processing → final image. The critical correction is to distinguish resource creation/upload from per-draw binding/reference and draw command submission. Never imply that each Draw Call uploads the entire Vertex Buffer, Index Buffer, textures or shaders. Depict the existing GPU resource pool as persistent and referenced, with a separate small creation/upload arrow marked "필요할 때 생성 / 업로드". That arrow is NOT repeated for every draw. A labelled dashed reference line from the persistent pool to Bindings clarifies reuse.

Panel 1 title "CPU / Engine". Korean line "Scene 상태와 Rendering 작업을 준비한다." Small labelled icons and brief labels: "Scene / Object", "Mesh / Material", "Transform / Camera", "Game Logic · AI · Physics · Animation". Bottom mini example: "하나의 Object도 여러 Draw로 나뉠 수 있다." and "Section · Pass · Instancing에 따라 달라진다." Use generic cube/mesh/material-sphere/coordinate icons, no fake editor UI.

Panel 2 title "Resources and Draw Commands". Three distinct steps:
1 "Create / Upload" with Korean "필요할 때 자원을 만들고 Data를 업로드한다." Persistent pool labelled "GPU Resources" containing "Vertex / Index Buffer", "Textures", "Shader / Constant Data". State setup is a separate list, not an uploaded texture.
2 "Bind / Reference" with Korean "이미 준비된 자원과 State를 선택한다." Compact readable list: "Geometry: Vertex / Index Buffer", "Shader / Texture / Parameter", "Transform / Camera / Projection", "Rasterizer / Depth / Blend / Stencil", "Viewport / Output Targets".
3 "Submit Draw" with Korean "설정한 자원을 참조하는 Draw 명령을 제출한다." Blue box "Draw / DrawIndexed(...)". Output arrow labelled "Command Submission" and "명령 제출" toward GPU. Include a short prominent note "Draw마다 전체 Buffer를 다시 업로드하는 것은 아니다."

Panel 3 title "GPU Processing". Intro "명령과 참조한 Data로 병렬 계산한다." Vertical processing boxes labelled "Vertex Processing", "Primitive Assembly", "Rasterization / Interpolation", "Fragment / Pixel Processing", "Depth / Stencil / Output Tests", "Color / Depth Writes". Each has one short Korean explanation respectively: "Position과 Attribute 처리", "Topology에 따라 Primitive 구성", "Coverage와 Fragment Attribute 준비", "Texture · Material · Surface 계산", "통과 조건과 기록 설정 확인", "활성화된 저장 대상에 기록". A short note "논리적 흐름: Early Depth 등 실제 순서는 달라질 수 있다." Do not draw depths as always pixel-shader outputs. Do not imply every Fragment writes color and depth unconditionally.

Panel 4 title "Final Image". At top separate compact output resource icons "Color Render Target" and "Depth Buffer". Color line flows to "Post Process / Display Target" → "Present" → generic monitor with a simple cube, character silhouette and scene. Depth remains a separate auxiliary resource, not a visible color. Label monitor art exactly "Concept Illustration" and Korean "개념 설명용 삽화 · Engine 실행 검증 아님". Include "Color 기록과 Depth Write는 별도 설정이다." near resource outputs.

Bottom full-width key sentence "CPU는 Rendering을 준비하고, GPU는 제출된 작업을 실행한다." Smaller footer "Draw Call은 자원과 State를 참조하는 Rendering 요청 단위다." Do not add BRDF equations, new algorithms, extra topics, an Unreal logo, fabricated profiling results or claims of measured performance. All text must be legible and technically consistent; avoid overly dense tiny labels.

### Fig1_13 — initial regeneration

Use case: scientific-educational / infographic-diagram.
Asset type: Korean ASF Foundation textbook overview figure, landscape 3:2, high-resolution PNG, opaque white background.
Input image: the supplied Fig1_13.png is the edit target and information/style reference. Regenerate a clearer technically corrected concept diagram with the same original information scope and ASF family palette. Replace fake editor screenshots/character photos with simple diagrams labelled Concept Illustration. Keep the English technical labels and Korean explanations. Do not introduce new rendering algorithms or proofs.

Primary request: title exactly "Fig1_13. Complete Rendering Pipeline" in a dark navy header. Subtitle exactly "Scene Data가 Geometry, Fragment, Image Data로 이어지는 논리적 흐름". Professional clean Korean sans-serif typography, white spacious panels, pale blue/green/orange/purple group headers, crisp navy/blue/green arrows, simple mesh/triangle/grid/buffer/monitor illustrations. All labels readable; no malformed Korean or tiny microtext. Landscape 3:2 like the supplied figure.

Arrange six distinct Processing Groups in a clear left-to-right overview across two connected rows. The group labels are teaching groups, NOT a list of single hardware stages. Add near header the readable line "Processing Groups: 여러 처리와 저장·표시를 묶은 교육용 개요".

Group 1 "Preparation / Selection" (blue). Explain "Scene · Mesh · Material · Transform · Camera · LOD 준비" and "Object / Bounds Frustum Selection". Small camera-frustum diagram with one object bounds inside (keep for this View) and one outside (exclude for this View). Explicit line "Frustum 선별은 CPU 또는 GPU에서 수행할 수 있다." Explicit line "현재 View 밖이어도 Shadow / Reflection Pass에는 필요할 수 있다." This is a separate preparation/selection group; do NOT put Object/Bounds Frustum Culling after Primitive Assembly inside a fixed GPU triangle stage. Keep CPU context: "CPU / Engine: Scene 상태와 Command 준비". Small note "Game Logic · AI · Physics" retains broader original CPU context.

Group 2 "Draw Commands" (orange). Compact flow: "Bind / Reference Resources" → "Set Shader / Material / State" → "Draw / DrawIndexed(...)" → "Command Submission". List "Vertex / Index Buffer", "Texture / Parameter", "Transform / Camera / Projection", "Depth / Blend / Rasterizer / Output". Readable note "준비된 자원을 참조한다. 매 Draw 전체 업로드가 아니다." Index is optional: label "Index Buffer: Indexed Draw에서 사용" if needed. No new data upload process repeated in the draw arrow.

Group 3 "GPU: Geometry Processing" (green). Three sequential boxes with simple icons:
"Vertex Processing" with "Position / Attribute 변환" and small list "Transform · Skinning · Morph / WPO".
"Primitive Assembly" with "Vertex와 Topology로 Primitive 구성". Triangle and index example.
"Backface Culling / Clipping" with "Winding과 State로 앞뒤 판정" and "Clip 경계에서 유효한 부분 유지". Distinguish these triangle operations from earlier Object/Bounds Frustum selection. Small line after clipping "Perspective Divide / Viewport Transform". Do not label a GPU geometry step View Frustum Culling.

Group 4 "GPU: Screen / Fragment Processing" (blue). Four sequential boxes:
"Rasterization" with "Screen Sample Coverage → Fragment 후보". Small triangle on pixel grid.
"Interpolation" with "UV · Normal · Color를 Fragment 위치에 보간" and "Perspective-Correct". A colored attribute-gradient triangle.
"Fragment / Pixel Processing" with "Texture · Material · Lighting · Surface Result". Shading-sphere icon, no new BRDF equations.
"Depth / Stencil Tests" with "저장된 Depth와 비교 · 통과 조건 확인". Small overlapping surfaces. Readable note "Early Depth 등 실제 실행 순서는 설정에 따라 달라질 수 있다." Do not imply depth must be a shader output or all candidates become pixels.

Group 5 "Output Bindings / Buffers" (purple). Explicitly depict a container labelled "Framebuffer / Output Bindings" that CONNECTS three separate resources, each with its own little storage icon: "Color Render Target", "Depth / Stencil Buffer", "Other Render Targets". Korean "여러 저장 대상을 함께 구성한다." Under Color icon "Color Output / Blending". Under Depth icon "Raster Depth · 선택적 Shader Override". Under Other icon "Normal / Material Data 등". Prominent short note "Depth Test와 Depth Write는 별도 조건이다." Another line "통과 조건과 Write 설정에 따라 기록한다." Absolutely do NOT write "Framebuffer (Render Target)" or imply the container and each target are identical. Color and Depth remain separate; only image/color results feed display processing.

Group 6 "Final Processing / Present" (gold). Flow "Post Process / Tone Mapping / UI" → "Display Target / Swap Chain" → "Present" → "Final Image". Generic monitor with simple scene silhouette labelled "Concept Illustration" and "개념 설명용 삽화 · Engine 실행 검증 아님". Note "Double / Triple Buffering은 표시용 Buffer를 관리한다." No claim that double buffering alone guarantees no tearing or synchronization.

Use arrows between groups following this logical journey, preferably groups 1–3 on top row and 4–6 below with an obvious connecting arrow from 3 to 4. Include bottom wide key takeaway "Vertex Data → Primitive → Fragment 후보 → Surface Result → Image Data" and footer "이 Diagram은 논리적 학습 흐름이며, 실제 Engine의 Pass와 실행 순서를 고정하지 않는다." Preserve all stage names, resource distinctions and depth/output caveats. No tiny unreadable labels, no bogus GPU culling placement, no fabricated current-project screenshots, no new BRDF scope.

### Fig1_12 — targeted correction after visual QA

Edit target: the supplied regenerated Fig1_12 image. Preserve its four main panels, readable Korean and English, clean cube/mesh/material icons, resource lifecycle distinctions, all six GPU boxes, separate Color and Depth icons, Concept Illustration provenance note, and landscape 3:2 dimensions. Make only the following targeted technical and style corrections. Use a dark navy full-width header strip with white title "Fig1_12. CPU, GPU and Draw Calls" and a pale subtitle, matching the original ASF family. Do not alter the main information scope or add new topics.

1. In Final Image, replace the introductory text "모든 Rendering 결과가 Framebuffer에 기록된 후, 화면에 표시된다." with "활성화된 저장 대상에 결과를 기록한다. 표시용 Color는 후처리와 Present를 거쳐 화면에 나타난다." This must not claim every rendering result is displayed.
2. Remove the green arrow labelled "Present (화면 출력)" between GPU Processing and Post Process. Instead draw a green output arrow from the GPU processing panel INTO the top Render Targets resource box, labelled exactly "Output Writes" and "출력 기록". Preserve the downward flow from Color Render Target to Post Process / Display Target, then Present, then monitor. Present must appear only in that final display sequence, never between a GPU shader and render targets. Depth is a separate auxiliary resource and is not a visible color.
3. In the purple GPU Resources explanation, replace the indefinite lifetime sentence with "Resource 수명 동안 GPU에 저장되며, 여러 Draw에서 재사용할 수 있다." Preserve the dashed existing-resource-reference arrow and the prominent no-full-upload-per-draw note.
4. In the Draw / DrawIndexed(...) box remove the extra parenthesized parameter signature. Keep only "Draw / DrawIndexed(...)". There must be no mixed VertexCount/IndexCount signature that looks like a real API declaration.
5. Remove the THREE small CPU, Draw Call, GPU recap boxes at the bottom; their information is already present in the main panels and they make text crowded. Use the freed space for the two clear full-width takeaway lines "CPU는 Rendering을 준비하고, GPU는 제출된 작업을 실행한다." and "Draw Call은 준비된 자원과 State를 참조하는 Rendering 요청 단위다." Do not say buffers are uploaded or transferred with each draw. Preserve the Object-to-multiple-Draw example in CPU panel.

Keep "Depth / Stencil / Output Tests", "Color / Depth Writes", "Color 기록과 Depth Write는 별도 설정이다.", and "논리적 흐름: Early Depth 등 실제 순서는 달라질 수 있다." readable and unchanged in meaning. Keep the monitor labelled "Concept Illustration" and "개념 설명용 삽화 · Engine 실행 검증 아님". All arrows must connect the correct boxes. No new equations or engine claims.

### Fig1_13 — targeted correction after visual QA

Edit target: the supplied regenerated Fig1_13 image. Preserve all six Processing Groups, their connected two-row layout, labels and stage scope, CPU-or-GPU Frustum selection note, Shadow/Reflection caveat, separate Backface/Clipping, optional Indexed Draw note, Geometry and Screen Processing explanations, logical Early Depth note, output binding container with THREE separate resources, Depth Test versus Depth Write note, display chain and Concept Illustration provenance. Landscape 3:2, opaque white background. Make only these targeted corrections:

1. Use a full-width dark navy header strip, white title "Fig1_13. Complete Rendering Pipeline" and pale subtitle "Scene Data가 Geometry, Fragment, Image Data로 이어지는 논리적 흐름". Preserve the readable Processing Groups teaching-group note, optionally directly below the header.
2. The Preparation panel camera-frustum picture is currently geometrically misleading: the red excluded cube is drawn inside the blue volume. Replace ONLY this mini diagram with a clean, unmistakable camera-frustum outline whose far boundary stops before the excluded object. Camera on left, blue frustum trapezoid in the middle, green dashed object bounds fully inside the blue outline, red dashed object bounds clearly completely outside to the right beyond the far boundary. Green checkmark and label "Keep for this View" under inside object; red X and label "Exclude for this View" under outside object. No overlap of excluded bounds with blue volume. The red outside bounds must visibly be outside, not merely have an X. Keep Korean labels "이 객체는 View 안에 있음" and "이 객체는 View 밖에 있음".
3. In 3.2 Primitive Assembly, replace the bullet "Index Buffer로 삼각형 구성" with "Topology로 Primitive 구성". Indexed draws can use an Index Buffer, but assembly must not imply that every primitive requires one. Keep "Triangle, Line 등".
4. Under Color Render Target, replace "Screen에 표시될 이미지 기록" with "현재 Pass의 Color 결과 기록". Intermediate Color targets need not be directly displayed.
5. The connection from Output Bindings / Buffers to Final Processing must clearly represent the DISPLAY COLOR path, not every depth/other resource being presented. Label the connecting arrow "Display Color" (Korean "표시용 Color 흐름") and route it into "Post Process / Tone Mapping / UI", then preserve its downward chain through "Display Target / Swap Chain" → "Present" → "Final Image". Add a short line in Output Bindings group "표시용 Color 흐름을 다음 단계에 연결". Depth/Stencil and Other Render Targets remain visibly separate auxiliary resources. Do not identify Framebuffer with an individual Render Target, do not collapse resources, and do not draw Present before output writes.

Preserve the bottom Vertex Data → Primitive → Fragment 후보 → Surface Result → Image Data takeaway and the logical-flow caveat. Keep all text legible; avoid invented Korean glyphs or microtext. Do not add new BRDF content, engine proof or performance claims.

### Fig1_12 — final connector correction after second visual QA

Edit target: supplied revised Fig1_12 image with navy header. Preserve all text, icons, four panels, resource creation/upload versus binding versus submission, GPU six-box logical flow, correct Final Image wording, separate Color/Depth resources, display sequence, provenance note, two large takeaway sentences and landscape 3:2 composition. Make ONLY the connector correction below.

The green Output Writes arrow currently starts at the height of Primitive Assembly, which can falsely imply Primitive Assembly writes render targets. Remove that green horizontal arrow and its nearby label. Instead draw a narrow clearly routed green ELBOW connector whose start is the RIGHT EDGE of the BOTTOM GPU box labelled "Color / Depth Writes". The line travels right into the WHITE GAP between GPU Processing and Final Image panels, then UP within that gap, then right to enter the Render Targets resource box near its top or left edge. Put a small arrowhead only where it enters Render Targets. Label the connector "Output Writes" and "출력 기록" in a readable location in the white gap, away from the stage boxes. This explicitly connects Color / Depth Writes to Color Render Target and Depth Buffer. It must NOT originate from Primitive Assembly, Rasterization, or Fragment Processing. Do not overlap text, icons, boxes, or the navy header. Preserve all other blue arrows, including logical GPU order and the downward final display sequence. Avoid any new Present label outside the existing final display sequence.

### Fig1_13 — final connector correction after second visual QA

Edit target: supplied revised Fig1_13 with navy header and correct frustum (red excluded bounds outside). Preserve EVERYTHING except the ONE purple connecting arrow currently pointing into the Present box. This is a local arrow-routing correction, not a redesign.

Delete the purple horizontal arrow at the height of Present and its adjacent "표시용 Color 흐름" arrow label. Draw a compact purple right-pointing arrow in the narrow gap between Group 5 "Output Bindings / Buffers" and Group 6 "Final Processing / Present", at EXACTLY the height of the FIRST box "Post Process / Tone Mapping / UI" (roughly y=625 in this 1536x1024 image). The arrow must enter the LEFT EDGE of "Post Process / Tone Mapping / UI", never the middle "Display Target / Swap Chain" and never "Present". This arrow's meaning is already explained by the existing note under Group 5: "표시용 Color 흐름을 다음 단계에 연결"; keep that note, do not add a crowded connector label. The display sequence must read Output Bindings / Buffers → Post Process / Tone Mapping / UI → Display Target / Swap Chain → Present → Final Image. Do not permit a shortcut arrow from output buffers directly into Present. No arrow through resource icons or text. Preserve the navy header, six groups, all text and pictures, separate resources and depth/write caveats without any other change.

---

## Chapter 02 Figure regeneration prompts

Built-in ImageGen edits. Original PNGs were individually inspected before generation. Non-destructive candidate outputs go to `work/figure_regenerated/Chapter02/`.

### Targeted QA edits

#### Fig2_14.png

Edit only the attached Figure 2-14. Keep the entire layout, all diagrams, header, numbers, Korean explanations and formulas unchanged. In panel 7, replace the small UV Seam bullet, which has a malformed Korean glyph, with this exact clearly typeset text: "UV Seam: 경계에서 Basis가 달라질 수 있다." Improve only that line's Korean character clarity. Do not alter any mathematical expression, handedness statement, TBN column notation, other text or colors. Keep the wide landscape dimensions.

#### Fig2_15.png

Edit only the attached Figure 2-15, preserving the complete conceptual diagram layout, dimensions, navy header/footer, all four numbered panels, all six exact Unreal node labels and their text, formulas and conditions. Make these three precise corrections: (1) In the bottom left World View Direction (V) card, the blue arrow must point FROM the surface sphere TO the camera. The sphere is on the left and the camera on the right, so the arrowhead must point RIGHT toward the camera. Keep the exact caption "Surface → Camera 방향 (World Space)". The upper CameraVectorWS card already has the correct direction; keep it unchanged. (2) In the Normal Map card at the start of panel 3, UV is an INPUT to texture sampling, not an output of the normal map: change the downward arrow to an UPWARD arrow from the UV (TexCoord) label toward the Normal Map texture. Keep UV text legible and do not change the main left-to-right data flow. (3) Replace only the second introductory sentence under "3. Typical Conversion" with this exact sentence: "아래는 Data의 개념 흐름이다. Engine이 처리하는 단계는 다시 적용하지 않는다." This avoids implying every material must use a manual Transform node. Preserve the Raw RGB → Decode → Tangent Normal → TBN / Transform → World Normal → Lighting flow, automatic engine brace, Source=Tangent Destination=World explicit-world note and implementation caveats. No other changes.


### Fig2_11.png

Redesign the attached ASF educational figure, preserving its number and technical scope while correcting the conceptual claim. Create a polished, highly legible landscape technical teaching diagram (wide 16:10 composition, high resolution), navy blue header and footer, white panels, thin pale-blue dividers, navy sans-serif English headings and precise Korean teaching prose, colored simple 3D cubes and arrows. This is Chapter 02 of a Korean 3D graphics foundations course. Preserve all FOUR numbered main panels and the bottom Summary, full information density, no clipped content. Do not copy the old misleading universal statement that Matrix always changes Space. Use these exact text strings and concepts, with no extra claims:
Header: "Figure 2-11. Matrix Transform Basics"
Top right: "ASF  Chapter 02 | Coordinate System"
Subtitle: "Matrix는 Transform 규칙을 일관되게 적용하는 계산 도구다."
Panel 1 heading "1. Matrix as a Transform Rule". Prose "Matrix는 Position과 Direction에 변환 규칙을 적용한다." Draw Input Position / Direction → Matrix M → Transformed Result, with coordinates (x, y, z) and (x′, y′, z′). Three bullets: "Scale: 크기를 바꾼다." "Rotation: 기준 축 주위로 회전한다." "Translation: 위치를 옮긴다." Prominent clarification "같은 Space 안의 Scale·Rotation도 Matrix로 표현할 수 있다."
Panel 2 heading "2. 4×4 Matrix and Homogeneous Coordinate". Short "3D Graphics에서는 Translation까지 함께 다루기 위해 4×4 Matrix를 사용한다." Show accurately a symbolic four by four matrix rows m00 m01 m02 m03 / m10 m11 m12 m13 / m20 m21 m22 m23 / m30 m31 m32 m33 multiplied by the COLUMN vector [x y z w] equals COLUMN vector [x′ y′ z′ w′]. Labels "Matrix M", "Column Vector v", "Result v′". Two bullets "Position: (x, y, z, 1)" and "Direction: (x, y, z, 0)". Footer in panel: "이 그림은 Column Vector Convention을 사용한다."
Panel 3 heading "3. Common Transform". Three side-by-side drawings: Scale cube changes size, Rotation cube turns, Translation cube moves. Captions "크기 변경", "회전", "위치 이동". Small callout "열벡터 기준: M = T · R · S" then "실제 적용: Scale → Rotation → Translation". Clear note "곱셈 순서는 Convention과 적용 순서를 함께 보고 해석한다."
Panel 4 heading "4. Matrix in the Rendering Pipeline". Draw clear horizontal chain "Local Position" → "Model M" → "World Position" → "View V" → "View Position" → "Projection P" → "Clip Position". Under the chain: "Rendering에서는 이 도구로 Space 사이의 전달을 구성한다." Three mini-cards "Model Matrix | Local → World"; "View Matrix | World → View"; "Projection Matrix | View → Clip". Formula small but exact "p_clip = P · V · M · p_local". Note "Clip 결과에는 Perspective Divide 전의 w가 남아 있다."
Bottom Summary three columns: "1  Matrix는 일반적인 Transform 규칙을 담는다." "2  4×4 표현은 Position·Direction·Translation을 함께 다루기 쉽다." "3  Rendering에서는 Model·View·Projection으로 Space 전달을 구성한다."
Layout must be spacious, diagram-first, credible mathematical notation and crisp Korean characters. No engine screenshot, no photorealism, no new topics. Keep each label complete and exact.

### Fig2_13.png

Redesign the attached ASF educational figure into a very legible wide 16:10 landscape technical teaching diagram, high-resolution, navy header, white panels, red Position, blue Direction, green transformation, orange Normal accents. Exact figure number, all four numbered panels and the comparison summary, simple clean 3D cube/plane drawings. English headings, precise Korean prose. Keep original conceptual scope and add necessary Geometric vs Shading Normal distinction, without long proofs.
Header exact "Figure 2-13. Position Transform vs Direction Transform". Top right "ASF  Chapter 02 | Coordinate System". Subtitle "같은 Transform이라도 데이터의 의미에 따라 적용 방식이 달라진다."
Four main columns of balanced width:
1 heading "1. Position". Text "공간 안의 한 점, 즉 위치 데이터다." Formula "Position = (x, y, z, 1)". Bullets "w = 1" "Translation 적용" "Rotation 적용" "Scale 적용". Draw a red cube translated from (x, y, z) to (x+tx, y+ty, z+tz), dashed arrow labelled "Translation". Caption "위치는 이동의 영향을 받는다."
2 heading "2. Direction". Text "위치가 아니라 방향을 나타내는 벡터다." Formula "Direction = (x, y, z, 0)". Bullets "w = 0" "Translation 제외" "Rotation 적용" "Scale 적용". Draw blue direction arrow with same orientation and length before and after a dashed gray Translation shift; gray shift is illustration only, not change to vector components. Caption "Translation은 Direction의 성분을 바꾸지 않는다."
3 heading "3. Same Transform, Different Result". Three color boxes "Scale S", "Rotation R", "Translation T". Show Position gets S,R,T while Direction gets S,R. Callout "Column Vector: M = T · R · S" and "실제 적용: Scale → Rotation → Translation". Text "Position은 이동·회전·크기 변경을 받는다." "Direction에는 Translation을 적용하지 않는다." Note "Scale은 Direction의 길이나 방향을 바꿀 수 있다."
4 heading "4. Normal Needs Special Handling". Two very clear adjacent mini-diagrams on a sloped triangular mesh: one "Geometric Normal" perpendicular to actual triangle face, green straight perpendicular arrow; other "Shading Normal" a tilted artist/interpolated arrow differing from face normal. Make distinction visually unambiguous. Exact captions "Geometric Normal: 실제 면에 수직" and "Shading Normal: Vertex 보간·Normal Map 등으로 달라질 수 있다." Next text "Normal에는 Translation을 적용하지 않는다." "Non-uniform Scale에서는 일반 Direction Transform으로 수직 관계가 보존되지 않을 수 있다." Exact formula "n′ = normalize((A⁻¹)ᵀ · n)" and note "A는 Affine Transform의 3×3 선형 부분이다. Invertible일 때 적용한다." No claim Shading Normal must be perpendicular to actual face. No claim normalize alone fixes Non-uniform Scale.
Bottom full width Comparison Summary table columns "Data | Representation | Translation | Rotation | Scale"; rows "Position | (x,y,z,1) | 적용 | 적용 | 적용"; "Direction | (x,y,z,0) | 제외 | 적용 | 적용"; "Normal | 방향 데이터 | 제외 | 적용 | Inverse Transpose 주의". Footer "w는 Position과 Direction을 구분한다. Normal의 올바른 변환은 별도로 판단한다."
Ensure formulas accurate, readable Korean, no clipped labels, no unnecessary extra detail.

### Fig2_14.png

Redesign the attached Figure 2-14 into a polished extremely legible wide landscape ASF technical teaching diagram. Aim wide 16:10 high-resolution composition, navy header/footer, white panels with pale blue dividers, English headings and Korean explanations, crisp colored T red, B blue, N green arrows. Preserve all EIGHT original numbered concepts, density and technical scope, with substantial space for clear illustrations. Do not make text tiny or crop it. Accurate TBN mathematics, no engine screenshot.
Header exact "Figure 2-14. Tangent Space"; right "ASF  Chapter 02 | Coordinate System"; subtitle "표면에 붙은 Basis로 저장한 방향을 Lighting의 Space로 옮긴다."
Layout three top panels 1–3, two broad middle panels 4–5, three bottom panels 6–8.
1 "1. A Basis on the Surface". Curved mesh with two local TBN frames, red T(U), blue B(V), green N. Text "Tangent Space는 표면 각 지점에 붙은 작은 좌표계다." "Basis의 N은 Vertex / Shading Normal일 수 있다." Clear note "Basis N과 실제 Face Normal은 다를 수 있다." Label drawn green vector "Basis N", not unconditionally face perpendicular.
2 "2. TBN Basis". Small orthogonal triad and concise table "T | U 방향" "B | V 방향" "N | Basis의 Normal". Formula exactly "TBN = [ T_world  B_world  N_world ]", label "3×3 Matrix · Column Vectors". Text "이 그림은 정규직교 Basis를 가정한다." "T, B, N은 길이 1이며 서로 직교한다." Small key condition "TBN⁻¹ = TBNᵀ 는 정규직교일 때만 성립한다."
3 "3. UV and Tangent". UV chart U right V up next to curved surface T and B axes. Text "T와 B는 보통 UV의 U·V 방향을 기준으로 만든다." "Mirrored UV와 UV Seam에서는 Basis가 달라질 수 있다." Correct no universal guaranteed equivalence for every mesh.
4 "4. Normal Map Decode". Explain "Normal Map은 Tangent Space의 Shading 방향을 저장한다." Flow Texture + UV → Raw RGB → Decode → n_tangent. Show purple sample "(0.5, 0.5, 1.0)" to "(0, 0, 1)". Formula "n_tangent = normalize(2 × RGB − 1)" labelled "일반적인 Raw RGB Decode 예". Highlight note "Normal Sampler가 이미 Decode했다면 다시 적용하지 않는다." Another small line "압축·Sampler 방식에 따라 실제 Decode 경로는 달라진다."
5 "5. Tangent → World". Large visual from sphere with TBN basis and blue n_tangent to sphere with World XYZ and transformed blue n_world, arrow "TBN Transform". Formula "n_world = normalize(TBN · n_tangent)". Explain "TBN의 열에는 목표 Space의 Basis를 넣는다." "World에서 Lighting을 계산하면 Normal과 Light·View 방향도 World로 맞춘다."
6 "6. Why Tangent Space?". Numbered Korean lines "UV에 맞춰 표면 방향을 Texture로 저장하기 쉽다." "물체가 이동·회전해도 같은 Normal Map을 재사용한다." "표면마다 다른 Basis로 복잡한 형태의 디테일을 표현한다." Small surface plus normal-map icon.
7 "7. Basis Conditions". Three compact bullets "Handedness: tangent.w 등의 부호를 사용해 B를 복원한다." Formula "B = sign · cross(N, T)" labeled "이 그림의 Cross 순서". "UV Seam: Basis 불연속을 고려한다." "보간 뒤에는 정규화·필요한 재직교화를 한다." "Object의 Non-uniform Scale은 Normal Transform으로 따로 처리한다." Do not suggest that normalize alone restores orthogonality.
8 "8. Summary". Bullets "저장된 Normal은 Tangent Basis 기준의 방향이다." "Basis N은 Face Normal과 항상 같지 않다." "Raw Decode와 Space Transform을 구분한다." "Basis 조건·Handedness·목표 Space를 함께 확인한다."
No extra topics or long proof. Every formula/symbol must be exact and Korean text must be legible. Keep original eight numbered coverage areas and provide clear generous spacing.

### Fig2_15.png

Recreate the attached ASF Figure 2-15 as a CONCEPTUAL explanation diagram, NOT a real Unreal Editor screenshot and NOT a fake UI screenshot. Wide landscape 16:10 high-resolution educational infographic with navy header/footer, white panels, pale-blue outlines, English exact node names and headings, clear Korean prose, clean simple 3D cube/surface/camera/UV schematic drawings. Preserve original four numbered panels and their scope; full information density but legible. No engine runtime validation claim.
Header exact "Figure 2-15. Coordinate Space Conversion in Unreal". Top right "ASF  Chapter 02 | Coordinate System". Subtitle "먼저 Data의 의미와 Space를 확인하고, 필요한 곳에서 같은 기준으로 맞춘다."
Panel 1 "1. Common Coordinate Spaces" top left, about 45 percent width. Five aligned cards, each small frame/surface/camera/grid schematic: "Tangent Space | 표면의 Basis"; "Local / Object Space | 물체 자체 기준"; "World Space | Scene 전체 기준"; "View Space | Camera 기준"; "Screen Space | 화면 좌표 기준". Text "이 목록은 Space의 종류이며 실행 순서가 아니다." World/Local axes use Z up to respect Unreal world convention; View camera schematic without asserting world-axis orientation; Tangent basis T,B,N.
Panel 2 "2. Common Unreal Data" top right 55 percent width, six cards in 3×2 grid, with exact node labels and descriptions:
"Absolute World Position" with current pixel point, text "현재 Shading Point의 World 위치" and "출력 옵션·Offset 포함 여부 확인".
"ObjectPositionWS" cube bounds wireframe with red center dot, text "Object Bounds의 World Center" and "ActorPositionWS·Pivot과 구분".
"VertexNormalWS" vertex arrow, text "World Space Vertex Normal" and "Vertex Stage에서 사용하는 입력용".
"PixelNormalWS" per-pixel green arrow, text "현재 Pixel Normal의 World 방향" and "Normal Map 반영은 문맥에 따라 확인".
"CameraVectorWS" show arrow from surface sphere TO camera, text "Surface → Camera 방향" and "World Space".
"ScreenPosition" UV grid with corners labelled "(0,0)" top-left and "(1,1)" bottom-right only within a sublabel "ViewportUV", text "ViewportUV: Viewport 기준 0–1" and "SceneTextureUV: Render Target 기준". No universal screen range claim.
Panel 3 "3. Typical Conversion" bottom left, large readable horizontal conceptual flow: "Normal Map" + UV → "Raw RGB" → "Decode" → "Tangent Normal" → "TBN / Transform" → "World Normal" → "Lighting". Clarify beneath Raw/Decode "Raw일 때의 개념 단계" and beneath Tangent "Normal Sampler는 Decode를 처리할 수 있다." Clear labeled brace under Tangent to World "Normal Input + Tangent Space Normal 설정을 쓰면 Engine 경로에서 변환한다." One short small caption for explicit world-space calculation: "직접 World 연산을 할 때: Transform의 Source = Tangent, Destination = World". Important visible note "자동 처리한 Decode·Space 변환을 중복 적용하지 않는다." Diagram not presented as literal material graph or universal node recipe.
Under main flow draw World Normal N and World View Direction V plus dot product: "같은 Space의 단위 방향: dot(N, V)". Camera arrow still Surface→Camera.
Panel 4 "4. Same Space, Same Meaning" bottom right. Green correct comparison "World Normal ↔ World Light Direction" with small two-arrow spheres, label "같은 Space로 연산". Red crossed mixed comparison "World Normal ↔ View Space Light Direction", label "Space를 섞으면 잘못된 결과". Beneath concise implementation note, not a large checklist: "Transform은 Vector 변환용이다. Position은 TransformPosition과 구분한다." "지원 Source / Destination과 Non-uniform Scale 조건은 대상 Version에서 확인한다." "이 그림은 개념 설명이며 모든 Graph의 실행을 검증한 결과는 아니다."
Footer summary exact "Position·Normal·Vector의 의미와 Space를 함께 확인한 뒤 연산한다."
No screenshot promise, no extra advanced topics, no unconditional supported-any-Space claim, no double decoding, accurate arrows and bounds center. Make Korean typography crisp and all six node names exact.

---

## Chapter 03 Figure Regeneration Prompts

Mode: built-in image_gen edit. Existing PNGs are edit targets; opaque background. Final candidate files are saved under `work/figure_regenerated/Chapter03/`; original outputs/Desktop/staging PNGs are not overwritten.

### Fig3_02

Source: `outputs/00_Foundation/Figures/Chapter03/Fig3_02.png`

```text
Use case: text-localization; scientific educational raster infographic edit.
Image 1 is the edit target, not just a style reference. Preserve its original wide landscape aspect ratio, every existing panel, every diagram, unit-vector direction arrows, all numeric results, all Korean explanation text, all formulas, all logos and navy ASF header/footer styling. Make one surgical text correction only: the bottom-right footer currently reads "Foundation · Chapter 03 · 3.2 Dot Product". Replace that exact footer with "Foundation · Chapter 03 · 3.3 Dot Product", using the same small gray type and placement. The next-section panel "다음 절: 3.4 Surface Normal" must stay unchanged.
Preserve N and L in the same Space as Unit Vectors. Preserve signed dot values for angles 0°,45°,90°,135°,180°: 1.0, approximately 0.707,0.0,approximately -0.707,-1.0. Preserve corresponding max(N·L,0) values 1.0,0.707,0.0,0.0,0.0. Preserve dot(a,b)=|a||b|cosθ, unit-vector dot=cosθ, Scalar direction coefficient versus final lighting distinction and Lambert clamp caveat. Do not reword any other text, do not add or remove panels, do not crop, and do not turn the edit into a simplified summary. Clear legible Korean glyphs and mathematical symbols. Opaque background.
```

### Fig3_05

Source: `outputs/00_Foundation/Figures/Chapter03/Fig3_05.png`

```text
Use case: precise-object-edit; scientific educational ASF raster infographic.
Image 1 is the edit target. Preserve the original wide landscape aspect ratio, navy header, white/light panels, six-panel layout, 3D surface/light/camera diagrams, blue light-propagation arrows, red L/V arrows, green checkmark callouts, English panel titles and Korean explanations. Preserve all technical content, formulas, signs and Normalize conditions; change only scope labels and add concise orthographic scope information with careful readable spacing.
Title stays "Figure 3-5. Light and View Direction"; Section 3.6.
Panel 1 Directional Light: preserve D as Light Propagation Direction and L pointing Surface→Light opposite to D; preserve "L = normalize(-D)" and position-independent parallel direction.
Panel 2 Point Light: preserve "L = normalize(LightPosition - SurfacePosition)" and different L at each surface.
Panel 3 Spot Light: preserve the same L formula, spot axis s pointing Light→Surface, half angle α, and "dot(s, -L) ≥ cos(α)", with s and L Unit Vectors.
Panel 4: change heading "View Direction" to "View Direction — Perspective". Change Korean introduction to "Perspective Camera에서는 Surface에서 Camera Position을 향하는 V를 구한다." Keep the existing perspective camera scene and "V = normalize(CameraPosition - SurfacePosition)". Keep the Diffuse/Specular note. Add a distinct compact light-blue scope box with EXACT text:
"Orthographic Camera"
"평행한 Viewing Ray의 반대 방향을 V로 사용한다."
"V = normalize(-Dview)"
"Dview: Camera → Scene의 평행 Viewing Ray 방향"
It must be clearly separate from the perspective position-subtraction example, and must not imply orthographic rays converge to one CameraPosition.
Panel 5 Common Pattern: keep both position-subtraction diagrams. Left subsection title "Light Direction (Point / Spot Light 예제)"; right subsection title "View Direction (Perspective Camera 예제)". In the introduction use "Point / Spot Light와 Perspective Camera의 예제는 Position 차이로 Direction을 준비한다." Keep formulas and the "Position 차이 → Normalize → Direction" strips. Add a short line "Directional / Orthographic의 준비 경로는 위 패널의 구분을 따른다."
Panel 6 Important: preserve same coordinate space, Unit Vectors before dot, light-type distinctions, zero-length vector separate handling. Revise camera qualifier in item3 to "V는 Camera Projection에 맞게 준비한다." Make no changes to vector signs, spotlight cone relation, mathematical content or other topics. Avoid malformed Korean, clipping and tiny unreadable notes. Opaque background.
```

### Fig3_06

Source: `outputs/00_Foundation/Figures/Chapter03/Fig3_06.png`

```text
Use case: precise-object-edit; scientific educational ASF raster infographic.
Image 1 is the edit target. Preserve its original landscape aspect ratio, ASF navy header/footer, white panels, five-section layout, blue/green/red arrow conventions, all diagrams, coordinate-axis transformations, English technical labels with Korean explanations, all numeric basis examples and formulas. Make only scope corrections to the bottom-left preparation table and add a compact alternative-path note. Preserve all existing technical scope; do not reduce the figure to a summary.
Title stays "Figure 3-6. Coordinate Space for Lighting".
Panels1–3 stay unchanged: Local/World/View Spaces, same World-Space N/L/V at P, correct World dot=1; basis example +Xview=+Yworld, +Yview=-Xworld,+Zview=+Zworld; same physical L=(0,-1,0) in View; mixed World N/View L produces dot=0 and is invalid. Keep these numeric equations exact.
Panel4 heading stays "4. 공통 Space로의 변환 과정". Keep Position row: Local Position, Model Matrix M,p_world. Keep Normal row: Local Normal,normalize((A^-1)^T × n_local),N_world. Keep "A는 Model의 가역 선형 부분이다." or equally precise existing annotation.
In the Light Position input row, explicitly label it "Point / Spot Light 예제" and keep "Light Position, p_world" plus "normalize(p_light - p_world)" giving L_world.
In Camera Position input row, explicitly label it "Perspective Camera 예제" and keep "Camera Position, p_world" plus "normalize(p_camera - p_world)" giving V_world.
Keep Lighting inputs N_world,L_world,V_world.
Below the table add a clearly separate concise scope note, with readable font and no collision:
"다른 준비 경로"
"Directional Light: L은 빛 진행 방향 D의 반대 방향으로 준비한다."
"Orthographic Camera: V는 평행한 Viewing Ray의 반대 방향으로 준비한다."
"두 방향도 선택한 같은 Lighting Space의 Unit Vector로 준비한다. (3.6 참조)"
These alternatives must not use LightPosition/CameraPosition subtraction. Do not add a fictitious light/camera position for them.
Panel5 stays unchanged: World Space or View Space are both valid if N/L/V all consistently share the selected Space. Footer stays "Space 이름보다 입력들의 기준 일치가 중요하다."
Preserve same-space comparisons, correct Normal transformation, inverse-transpose notation, Normalize after normal transformation, and all original content. Table may grow vertically within the same canvas with gentle layout adjustment so every scope label remains legible. No clipping, no duplicated text, no added unrelated topics. Opaque background.
```

---

## Chapter 04 Figure Regeneration Prompts

Built-in image generation/editing tool. Each referenced PNG is the edit target and style/layout reference. Original paths and numbers stay unchanged. No Engine screenshot or execution verification is claimed.

### Fig4_04

Use case: scientific-educational infographic edit.
Input image: existing Fig4_04.png is the edit target and ASF style reference.
Regenerate this complete educational infographic with the same landscape 3:2 composition, navy title band, white panels, bright blue English headings, Korean explanations, existing panel numbering1–11, diagrams and material examples. Produce crisp high resolution, generous spacing, perfectly readable Korean and exact formulas. Keep title "Fig 4.04 UV and Texture Sampling" and ASF Foundation/Chapter04 identity. Preserve every teaching topic; correct the following, without adding advanced topics.

1–2 retain 3D Surface→UV Layout and normalized U/V axes. 3: vertex UVs A=(0,0), B=(1,0), C=(0.5,1). Use the SAME triangular shape and move the sample marker to the correct affine example: weights A0.35/B0.03/C0.62 yield UV(0.34,0.62). The marker must be about34% across and62% up in these UV coordinates, not in the triangle center. Show a short caption "Affine 보간 예시; 실제 Rasterization은 Perspective-Correct 조건을 따른다." Only this specified example is affine; do not claim all runtime UV interpolation is affine. 4: explain Texel stores Material Data, fix any doubled "값을 값을" to a single "값을".

5: keep UV(0.34,0.62)→Texture Sample→illustrative sampled Color(0.82,0.68,0.61). Clearly mark values as illustrative and Color decoding depends on Texture interpretation. 6: sample between four TEXEL CENTERS, not ambiguously on tile boundaries. Show C00/C10/C01/C11 at four centers, sample between them, bilinear weights and exact general expression "Color = w00 × C00 + w10 × C10 + w01 × C01 + w11 × C11" with "w00 + w10 + w01 + w11 = 1". Keep illustrative output(0.71,0.61,0.52), label "Illustrative Result" rather than a measured Engine output.

7: keep Mip0 4096×4096, Mip1 2048×2048, Mip2 1024×1024, Mip3 512×512. Replace a distance-only explanation with "화면의 Pixel이 덮는 Texture 범위(Screen Footprint)에 맞춰 Mip을 선택한다. 거리 외에 UV Scale과 표면 각도도 영향을 준다." Use small/large footprint with fine/coarse mip, distance only as one example. 8: retain sameUV→BaseColor/Roughness/Metallic/Normal/Emissive. Values Color(0.82,0.68,0.61), Roughness0.58, Metallic0, Emissive(0,0,0). Normal(0.52,0.47,1.00) MUST be labelled "Encoded Tangent Normal RGB"; it is not a decoded Unit Normal.

9: replace the symmetric checker demonstrations by a clearly ASYMMETRIC strip "A B C" within U0–1. For U1–2 show Wrap "A B C", Clamp "C C C", Mirror "C B A". Clearly show U ticks0,1,2 and distinguish the three actual patterns. 10: retain Sampled Data→Material Inputs→Lighting→Final Appearance; no claim all inputs must execute in that exact serial order. 11: preserve five concise takeaways from source. No new scope, no invented software UI, no source attribution/Engine runtime claim. Match the original overall look and diagrams while correcting text and relationships.

### Fig4_05

Use case: scientific-educational infographic edit.
Input image: existing Fig4_05.png is the edit target and ASF style reference.
Regenerate the infographic in the same3:2 navy header/white panels/bright blue English numbered headings1–8/Korean explanation style. Preserve title "Fig 4.5 Color Space for Material Data", Color/Data/Normal Texture distinctions, sampling flows, Roughness/Mask examples and takeaways. All text legible, exact numeric labels. The rendering illustrations are controlled conceptual comparisons, NOT actual Unreal screenshots.

Panel1: explain Color Space describes color encoding and interpretation, not just Gamma. Compare SAME Stored RGB(0.5,0.5,0.5). Left "sRGB Decode" → "Linear≈0.214", darker neutral sphere; right "Linear Data" → "Linear0.500", visibly brighter neutral sphere. Identical lighting/camera/exposure/display assumptions, differing input interpretation only. Do not swap the brightness. Label "동일 저장값·동일 조건의 개념 비교".

Panel2: replace the encode-like concave-down curve with the correct sRGB→Linear DECODE plot. X axis "Stored sRGB Value"0..1, Y axis "Linear Value"0..1. Decode curve is monotonic CONCAVE UP, below the identity line, through(0,0),(0.5,0.214),(1,1). Show exact marked dot and label "0.50 → 0.214". Identity dashed line y=x. Legend "sRGB Decode" versus "Linear Data". Do NOT draw encode curve, gamma2.2 as exact sRGB, or "Perceived Brightness" on the output axis.

Panel3: Color Texture(sRGB On) for encoded color/basecolor; Data Texture(sRGB Off) for Roughness/Metallic/AO/Mask; NormalTexture(sRGB Off) stores encoded directions and still needs appropriate Normal sampling/decoding. Avoid saying every color texture is necessarily sRGB, include compact already-linear/HDR exception in Additional Note.

Panel4: Texture Asset(sRGB On)→Sample(Automatic sRGB Decode)→Linear Color. Texture Asset(sRGB Off)→Sample(No sRGB Decode)→Numeric Data. Exact label "No sRGB Decode", never "No Conversion". Other format/compression/Normal reconstruction may still occur; short Korean note after the flow.

Panel5 and6 MUST preserve the corrected relationship: Correct Numeric Data0.50 versus Incorrect sRGB Decode0.50→0.214. Roughness decreases, narrower highlight and glossier appearance. Do not use0.73 for this decode. Keep Mask example with same stored0.5→0.214; explain threshold behavior can change, without promising a universal appearance. Rename panel6 "Conceptual Appearance Comparison" and add "동일 조건의 개념도"; roughness0.50 sphere has broad highlight, roughness≈0.214 sphere has narrow highlight, same scene exposure/light/view.

Panel7: replace synthetic checkbox inside Texture Sample with two distinct labelled conceptual cards: "Texture Asset: sRGB" and "Texture Sample: Sampler Type". Explain encoded Color with proper sampler is normally automatically decoded; do not add a manual SRGBToLinear chain after an already-decoded sample. If showing manual transfer, keep it separate labelled "Raw Encoded Data에만 수동 Decode". No screenshot-like fake UI, no claim a Texture Sample owns an sRGB checkbox.

Panel8: five original concepts, phrased accurately: storage/interpretation vs numeric calculation; lighting in linear calculation space; Color vs Data/Normal; wrong interpretation corrupts data; import settings matter. Additional Note: already-linear/HDR textures need matching settings; sRGB Off skips sRGB decode rather than all conversions. Correct spelling and keep the visual design/technical depth.

### Fig4_06

Use case: scientific-educational infographic edit.
Input image: existing Fig4_06.png is the edit target and ASF style reference.
Regenerate as a Foundation CONCEPT DIAGRAM, retaining landscape3:2 navy header/white panels/bright-blue English titles/Korean explanations, all nine existing teaching topics and checklist. Title "Fig 4.6 Normal Map and Normal Encoding". Keep examples and scope, crisply readable text/formulas. No actual Unreal screenshot or execution verification claim.

1: Normal Map changes Shading Normal details without adding geometry, preserve smooth/detailed illustrative surface comparison and silhouette/geometry caveat. 2: same-space UnitN/L with "N · L = cosθ" and short "방향 관계이며 최종 밝기 전체가 아니다." 3: Direction encoded in RGB, generally Tangent Space. Pixel example(0.52,0.47,1.00) labelled "Encoded RGB Example"; not a decoded normal. Flat encoded RGB(0.5,0.5,1) corresponds to Tangent Normal(0,0,1).

4: clearly separate TWO paths. PathA "Raw Encoded RGB"→"n_raw = 2 × RGB − 1"→"Normalize"→"Decoded Tangent Normal". PathB "Normal Sampler Output (이미 Decode된 경우)"→"Decoded Tangent Normal" WITHOUT applying2RGB−1 again. Exact Korean note "이미 Decode된 방향에는 RGB × 2 − 1을 다시 적용하지 않는다." The storage model is a conceptual RGB encoding; actual Compression/Format may reconstruct components and is not guaranteed to output original stored RGB.

5: Tangent Space basis at each surface point differs from ObjectLocalSpace. BasisN is shading/basis normal and may differ from triangle faceNormal; T/B/N axes form an orthonormal illustrative basis. If Lighting comparison usesWorldSpace: DecodedTangentNormal→TBN Tangent→World→Normalize→WorldNormal. Add short separate note "Material Normal 입력은 Tangent Space Normal 설정과 맞춘다. Tangent 입력 경로에 World Normal을 그대로 넣지 않는다." Clearly this TBN flow is for a WORLD-SPACE LIGHTING target, not mandatory manual operations in every Unreal Material.

6: preserve three exact raw encoding examples with separate labels "Encoded RGB" ABOVE and "Decoded Unit Direction" BELOW. Flat RGB(0.5,0.5,1.0)→(0,0,1); +X RGB(1.0,0.5,0.5)→(1,0,0); +Y RGB(0.5,1.0,0.5)→(0,1,0). These are illustrative raw encodings, not claims about any compression output. 7: preserve same-geometry lighting comparison, label conceptual illustration.

8: retain +Y/−Y Green-channel convention/import agreement, TangentSpace vsObjectSpace normal storage and proper target-space Normal transform. Do not imply an ordinary Direction transform always handles ObjectSpaceNormal under nonuniformscale. Brief implementation note: sampler/Compression, G-channel convention and tangent basis must match; no engine execution verification claim. 9: retain six concise takeaways while changing "eachpixelRGBareNormal" to "RGB에는Direction성분을Encoding해저장" and restricting raw decoding formula toRawEncodedRGB.

Checklist retains sRGBOff for numericNormalData, appropriate NormalSampler/Compression, matchingGreenChannel, matchingTargetSpace, resolution/mips, correctNormalInputSpace, optionalstrength. No overloaded exception list in main flow, no new advanced topics. Match original ASF look, preserve number/path and full teaching coverage.

---

## Chapter04 refinement prompts

### Fig4_04

Targeted correction of the input edit target ONLY. Preserve all11panels, design, dimensions, text and formulas except these exact fixes. Panel3 triangle vertices are A=(868,385),B=(1066,385),C=(968,230) in this1536×1024image. For weightsA0.35/B0.03/C0.62, the white sample dot MUST move from approximately(957,312) to(936,289); redirect its annotation leader to that point. This is UV(0.34,0.62), about34%across and62%up from the base. Retain the affine/perspective-correct caveat and all three weights. Panel9 consists of six character cells per strip, separated into U0–1(first3) andU1–2(last3). Exact left-to-right text: Wrap strip A B C A B C; Clamp strip A B C C C C; Mirror strip A B C C B A. Keep boundary0/1/2correctlyaligned, with1between3rd/4thcells. First half must be identicalABC in allthree. Do not use CCCCCC orCBACBA. Panel6C00 etc are Texel index names, remove extra(0,1)/(1,1)/(0,0)/(1,0)coordinate labels that confuse the indexing while preserving the actual four texel centers/sample/formula. Do not alter other content or add any topics. All Korean legible.

### Fig4_05

Targeted correction of this edit target ONLY. Preserve all8panels, corrected brightness andRoughness examples, asset-versus-sampler cards, style/dimensions/wording except specified items. Panel2 must have a mathematically faithful sRGB→Linear decode curve. Plot origin approx(538,387), endpoint(780,205); xStoredRGB0..1,yLinear0..1. Exact curve points: input0.25→0.0509(about599,378); input0.50→0.214(about659,348); input0.75→0.5225(about720,292); input1→1(780,205). The current dot atabout657,340is too high; put it at659,348 and fit a smooth convex-up curve through the provided points, below identity. Retain exact0.50→0.214label. Do not draw an Encode curve or change axes. Panel8Takeaway2 verbatim 'Lighting의 Color 연산은 Linear 값으로 수행한다.' Panel8Takeaway3 verbatim 'sRGB로 Encoding된 Color는 Decode하고, Numeric Data에는 sRGB Decode를 적용하지 않는다.' This must agree with already-linear/HDR exceptions in AdditionalNote. Keep everything else, including0.50→0.214→moreGlossy,unchanged.

### Fig4_06

Targeted correction of this edit target ONLY. Preserve all9panels, two explicit raw-vs-decoded paths, exact encoded/decoded examples, TBNflow, implementation conditions, style/dimensions. Panel2 add clearly readable exact condition next toN·L=cosθ: '같은 Space의 Unit Vector N과 L'. In panel5remove only the direction words '(UP)','(RIGHT)','(down LEFT)' from basisaxislabels; keep N(0,0,1),T(1,0,0),B(0,1,0) and current arrows. These are local surfacebasis axes, not screen/world-up directions. The checklist currently has '적절한 Target Space (Tangent/Object)를 사용한다.' Replace it with exact 'Normal의 저장 Space와 계산 Space를 확인한다.' Keep NormalInputSpace matchingcondition unchanged. Do not add Engine screenshots or runtime-verification claims, no additionalScope. Preserve correct formulas, raw-decoded caveats and legible Korean.

### Fig4_04 final refinement

Final correction instruction: Preserve all eleven panels and all approved corrections. Remove the incorrect interior sample marker and its leader from the UV triangle. Keep vertex UV labels and the gradient triangle. Put the Affine Example in a separate numerical box, with A 0.35 / B 0.03 / C 0.62 and Interpolated UV (0.34, 0.62). Keep the affine example and perspective-correct rasterization caveat. Do not change other panels, layout, or wording.

---

