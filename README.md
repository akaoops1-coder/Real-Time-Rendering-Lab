# Real-Time-Rendering-Lab

**Real-Time-Rendering-Lab**은 Real-Time Rendering의 기초 원리를 이해하고, 이를 실제 Shader 구현과 Rendering 환경에서 검증하기 위한 학습 및 연구 프로젝트입니다.

특정 Shader나 Material의 결과를 그대로 따라 만드는 것보다, 화면에 나타나는 결과가 **왜 그렇게 만들어지는지**를 Rendering Pipeline의 흐름 안에서 이해하는 것을 목표로 합니다.

> **Concept → Implementation → Verification → Debugging → Optimization**

---

## Purpose

Real-Time Rendering을 구성하는 개별 기술을 단편적으로 학습하는 것이 아니라, 각 개념이 전체 Rendering Pipeline에서 어떤 역할을 하며 서로 어떻게 연결되는지 이해하는 것을 목표로 합니다.

가능한 경우 학습한 개념을 Unreal Engine에서 직접 구현하고, Rendering Result와 Debug View를 통해 이론과 실제 결과가 일치하는지 검증합니다.

최종적으로는 다음과 같은 역량을 구축하는 것을 목표로 합니다.

- Rendering Result가 만들어지는 과정을 설명할 수 있는 능력
- Rendering 문제의 원인을 Pipeline을 따라 추적할 수 있는 능력
- Shader와 Material의 Data Flow를 이해하고 수정할 수 있는 능력
- Visual Quality와 Rendering Cost 사이의 Trade-off를 판단할 수 있는 능력

---

## Target Audience

이 프로젝트는 다음과 같은 학습자를 대상으로 합니다.

- Real-Time Rendering의 기초 원리를 체계적으로 학습하려는 Artist
- Shader와 Material의 동작 원리를 이해하려는 Technical Artist
- Unreal Engine의 Rendering 구조를 기초부터 학습하려는 사용자
- PBR과 NPR을 원리부터 실제 구현까지 연결해서 이해하려는 사용자

---

## Learning Scope

현재 프로젝트에서는 다음 영역을 단계적으로 다룹니다.

- Rendering Pipeline
- GPU Rendering Process
- Coordinate System & Transform
- Rasterization
- Texture & Sampling
- Lighting
- Reflection
- BRDF
- Physically Based Rendering
- Non-Photorealistic Rendering
- Shadow
- Unreal Engine Material
- Shader Implementation
- Character Rendering
- Rendering Debug
- Profiling
- Optimization

Foundation 이후에는 실제 Character Shader 제작을 중심으로 Advanced Rendering 영역으로 확장할 예정입니다.

---

## Repository Structure

### 00_Project

Project Direction, Documentation Standard, Project Management, Decision Log 등 프로젝트 전체를 관리하기 위한 문서를 포함합니다.

### 00_Foundation

Real-Time Rendering을 이해하기 위해 필요한 핵심 개념을 단계적으로 정리합니다.

각 개념을 독립적으로 설명하기보다 Rendering Pipeline 안에서의 위치와 역할, 다른 Rendering Concept과의 연결 관계를 중심으로 구성합니다.

이후 실제 Shader Implementation과 Advanced Rendering Study의 기반으로 사용합니다.

---

## Documentation Approach

문서는 단순한 Tool 사용법이나 Shader Recipe를 기록하는 것을 목표로 하지 않습니다.

기술을 구현하기 전에 해당 기술이 **왜 필요한지**, Rendering Pipeline의 어느 단계에서 동작하는지, 어떤 Data를 입력받아 어떤 결과를 만드는지를 이해하는 것을 우선합니다.

Documentation은 다음 원칙을 기준으로 작성합니다.

- **Explain Why First**
- **Flow Before Implementation**
- **Concept Before Platform**
- **Verification Before Conclusion**
- **One Document, One Topic**

공식이나 Shader Node는 출발점이 아니라, 앞에서 이해한 원리를 표현하고 실제 구현으로 연결하기 위한 수단으로 사용합니다.

---

## Roadmap

- [x] Rendering Foundation Documentation
- [ ] Foundation Review & Verification
- [ ] Production PBR Character Material
- [ ] Production Anime Shader
- [ ] Character Rendering
- [ ] Rendering Debug & Profiling
- [ ] Shader Optimization
- [ ] Advanced Rendering Case Studies

---

## Feedback

이 프로젝트는 Review와 Verification을 통해 지속적으로 내용을 수정하고 개선합니다.

Rendering Theory, Technical Accuracy, Documentation Clarity, Unreal Engine Implementation 등에 대한 Feedback을 환영합니다.

### GitHub Discussions

질문, 의견, Technical Discussion, 개선 제안처럼 여러 관점에서 논의할 수 있는 내용은 **GitHub Discussions**를 이용합니다.

다음과 같은 내용을 남길 수 있습니다.

- 설명이 이해하기 어렵거나 추가 설명이 필요한 부분
- Rendering Concept에 대한 질문
- Documentation에 대한 전반적인 의견
- Technical Discussion
- 추가하면 좋을 학습 주제
- Project Direction에 대한 제안

### GitHub Issues

명확한 확인이나 수정이 필요한 문제는 **GitHub Issues**를 이용합니다.

다음과 같은 내용을 남길 수 있습니다.

- 잘못된 Rendering Theory 또는 Technical Description
- Formula 또는 Terminology 오류
- Figure 또는 Diagram 오류
- Broken Link 또는 잘못된 File Path
- Unreal Engine Implementation 오류
- Typo
- 기타 구체적인 Documentation 문제

등록된 Issue는 내용을 확인한 뒤 수정 작업과 연결하고, 수정과 Verification이 완료되면 Close합니다.

---

## Status

**Foundation Documentation — Review & Verification in Progress**

현재 Foundation Documentation의 1차 작성이 완료되었으며, 전체 내용에 대한 Review와 Verification을 진행하고 있습니다.

검수가 완료된 이후에는 Foundation에서 학습한 내용을 기반으로 실제 Character Shader 제작과 Advanced Rendering Study를 진행합니다.

---

## Summary

Real-Time-Rendering-Lab은 Rendering 기술의 결과만 재현하는 프로젝트가 아니라, 그 결과가 만들어지는 원리를 이해하고 실제 구현과 검증으로 연결하기 위한 프로젝트입니다.

Foundation에서 Rendering Pipeline과 핵심 개념을 구축한 뒤, Character Rendering과 Advanced Rendering으로 확장하며 **Concept → Implementation → Verification → Debugging → Optimization**의 흐름을 반복합니다.

---

## Next

Foundation Documentation의 Review와 Verification을 완료한 뒤, 실제 Production PBR Character Material과 Production Anime Shader 구현 단계로 진행합니다.
