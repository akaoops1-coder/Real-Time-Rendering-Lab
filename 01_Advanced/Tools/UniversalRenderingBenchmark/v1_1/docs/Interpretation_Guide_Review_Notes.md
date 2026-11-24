# Interpretation Guide Review Notes

> Updated: 2026-11-03 KST · Scope: V1.1 문서 검토 근거

## Reviewed Sources

- `Real-Time-Rendering-Lab/00_Project/ASF/ASF-003_Documentation_Standard.md`: Korean `…다` 본문, English Title·Technical Term, 실제 Heading·상대 링크, 사실·검증 한계 구별을 확인했다.
- `Real-Time-Rendering-Lab/00_Project/FigureStyleGuide.md`: Chapter 번호가 없는 Advanced Topic의 설명적 Figure 이름, Topic 내부 상대 경로와 실제 Capture 보존을 확인했다.
- `UniversalRenderingBenchmark/docs/Master_Specification_KO.md`: §6 통계·대표값, §7 Impact·Budget·Confidence, 독립 상태와 §10 Report 계약을 확인했다.
- `UniversalRenderingBenchmark/docs/Phase3_Implementation_KO.md`, `Phase3_User_Guide_KO.md`: immutable Sources 묶음·재현성·nearest-rank P95·Noise·CLI 의미를 확인했다.
- `UniversalRenderingBenchmark/docs/Phase4_Implementation_KO.md`, `V1_User_Guide_KO.md`: 사용자 UI Run, CPU caveat, 원본 보호·오프라인 묶음, 실제 Character 전체 미측정 범위를 확인했다.
- 실제 Run `20261103T114935_URB4_Scalar_30CCDBF0/Analysis/0.3.1_C8B6BCA5E40C/Report.html`, `Analysis.json` 및 `phase4/analyzer/urb_analyzer/policy.json`을 확인했다.

## Exact Sample Semantics

GPU A=`2.9288`, B=`2.92615`, Delta=`-0.00265 ms`다. 4자리 HTML 표시는 B=`2.9261`, Delta=`-0.0027`이다. 반올림한 화면 숫자를 원본 정밀도로 간주하지 않는다.

GPU A/A Range=`0.0509`, A Range=`0.0211`, B Range=`0.0321`, Floor minimum=`0.05 ms`이므로 Noise Floor=`0.0509 ms`다. Calibration=`VALID`, environment_match=true이며 GPU의 직접 보류 사유는 `DELTA_WITHIN_NOISE_FLOOR` 하나다. Measurement=`PASS`, Native=`COMPLETED`, GPU Confidence/Impact=`INCONCLUSIVE`, Budget A/B=`GREEN`이다. Budget usage A=`17.5728%`, B=`17.5569%`다.

FrameTime·GameThreadTime·RenderThreadTime은 모두 INCONCLUSIVE다. Variant 불안정·A/A 불안정·Noise 이하의 사유와 CPU 보조 정책 설명을 유지해야 한다. Frame/Render Thread 음수 Delta를 개선으로 소개하면 기존 의미와 충돌한다.

## Figure Contract

Guide에서 참조하는 경로는 `../Figures/V1_1/Report_Scalar_Desktop.png`, `../Figures/V1_1/Report_Scalar_Narrow390.png`다. 새 HTML의 실제 브라우저 Capture가 필요하다. 현재 문서 내용은 스크린샷의 실측 자료가 새 측정이 아니라 동일 Run의 표시 개선임을 명시한다.

## Final Integration

V1.1은 `UniversalRenderingBenchmark/v1_1/`에 독립 배치한다. 루트 Launcher는 `Analyze.pyw`·`Analyze.cmd`이며 `analyzer/urb_analyzer/cli.py`의 실제 argparse를 확인했다. Run은 위치 인자이며 출력 옵션은 `--output-root`다. `--run`·`--output` 옵션은 존재하지 않는다.

가이드의 실행 예는 이 계약을 따르며 샘플은 `../examples/ActualScalarReport/README.md`, 원문 보존 문서는 `Reference_Documents/*.md`로 연결했다. 설치·Capture 절차를 길게 반복하지 않고 결과 해석에 집중한다.
