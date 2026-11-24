# V1 첫 실행

V1 구현과 개발자 검증을 마친 도구의 첫 실행 순서다. 사용자의 직접 검증은 이 순서로 시작하면 된다. 실제 결과와 제약은 Phase 4 보고서를 따른다.

1. 새로 연 `RTR_Advanced` Editor에서 **Show Plugin Content**를 켜고 `/URBenchmark/Phase4/Maps/L_URB_GenericActions`를 연다. 업데이트 전부터 켜져 있던 Editor는 이전 Native 코드를 사용한다. 미저장 작업은 보존한다.
2. World Outliner에서 `BP_URB_Runner`를 고른다. Details의 **Preset**은 `DA_URB4_Scalar`, **Auto Run On Begin Play**는 켜짐인지 확인한다. **Validate Preset**으로 검증한다.
3. Play 옆 메뉴에서 **Standalone Game** 모드를 고른 다음 **초록색 Play 버튼**을 누른다. 메뉴 선택만으로 시작되지 않을 수 있다. A/A 뒤 A/B를 자동 측정한다. 기본 조건은 각 Capture 전 Warmup 120프레임, Capture 300프레임, Variant별 3회다. 측정 중 마우스·키보드·게임패드로 게임을 조작하지 않는다. Pawn이 있는 새 Level에서는 입력으로 Pawn이 이동할 수 있다. 중단할 때만 Esc를 누르고 복원을 기다린다.
4. `URB COMPLETED`를 확인한다. 프로젝트 `Saved\URBenchmark\<이번 RunID>\Completion.json`에서 `status=COMPLETED`와 `restoration`의 네 항목 true를 확인하고 게임 창을 닫는다.
5. 도구 폴더 `local path withheld`를 더블클릭한다. 별도 Console 창 없이 분석 창이 열린다. **Raw 폴더가 들어 있는 Run 폴더**를 선택한다. 파일 연결 문제로 실행되지 않으면 `Analyze.cmd`를 사용한다.
6. 이번 예제는 같은 Run에 A/A를 포함하므로 별도 Calibration 연결 질문에 **아니요**를 선택한다. 브라우저에서 열린 실제 `Report.html`과 완료 창의 저장 위치를 확인한다.

`INCONCLUSIVE`는 실행 실패나 차이 0의 판정이 아니다. 같은 조건의 반복 변동보다 차이가 작거나 비교 근거가 부족하면 보류한다. Measurement Status와 Performance Impact·Budget·Confidence를 구별해 읽는다.

다른 Action은 같은 Level에서 Preset만 바꿔 실행한다. Hair는 `/URBenchmark/Phase4/Maps/L_URB_HairIsolation`과 `DA_URB4_HairPDO`를 사용한다. Production Asset은 수정하지 않는다. 새 시험 만들기·오류·결과 해석·제약은 `V1_User_Guide_KO.md`를 따른다.

새 Level은 실제 Standalone 화면에서 대상이 보이고 가려지지 않는지 먼저 확인한다. 제공한 Phase 4 Level은 불필요한 기본 Pawn을 생성하지 않는다. 화면을 고치거나 Asset을 저장했다면 새 조건에서 A/A와 A/B를 다시 측정한다.

측정 전에 결과 화면부터 보고 싶다면 `phase4/examples/ActualHairReport/Report.html`을 연다. 실제 Hair 단독 장면의 PDO OFF/ON 결과이며 Character 전체의 Hair·Skin·Eye 측정을 완료했다는 뜻은 아니다.
