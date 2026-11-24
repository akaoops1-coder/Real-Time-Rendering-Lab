# Universal Rendering Benchmark

Unreal Engine Standalone에서 통제된 A/B 측정을 반복하고 CSV를 분석하는 개인 R&D 도구다.

## Workflow

Test Preset → Native Runner → Unreal CSV Profiler → Python Analyzer → Summary CSV / HTML Report

Runner는 적용 상태를 읽어 확인하고 Warmup과 반복 Capture 뒤 상태를 복원한다. A/A Calibration과 환경 일치가 Confidence 판정의 근거다. 코드 검토에 필요한 Source와 증거를 담은 공개본이다. Unreal Binary와 전용 Level은 별도 설치 범위다.

## Evidence

- [Architecture and measurement contract](docs/Master_Specification_KO.md#3-시스템-구조)
- [Phase 4 implementation and developer validation](docs/Phase4_Implementation_KO.md)
- [Native V1 plugin descriptor](phase4/Plugin/URBenchmark.uplugin)
- [Hair PDO Summary](phase4/examples/ActualHairReport/Summary.csv), [Analysis](phase4/examples/ActualHairReport/Analysis.json), [frame-level CSV](phase4/examples/ActualHairReport/Sources/Benchmark/Raw)
- [Report V1.1 / Analyzer 0.4.0](v1_1/docs/V1_1_Implementation_KO.md)

Hair PDO는 Analyzer 0.3.1의 격리 Hair Scene 실측이다. V1.1 검증은 동일 Scalar Raw를 0.4.0으로 재분석한 기록이다.
