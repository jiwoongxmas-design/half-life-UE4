# Half-Life UE4 - 프로젝트 설정 가이드

## 📋 프로젝트 정보
- **엔진**: Unreal Engine 4.27.2
- **언어**: C++
- **플랫폼**: Windows, Linux, Mac
- **장르**: FPS (First Person Shooter)

---

## 🚀 초기 설정

### 1. UE4 프로젝트 생성
```bash
# 터미널에서 실행
git clone https://github.com/jiwoongxmas-design/half-life-UE4.git
cd half-life-UE4

# Unreal Engine 4.27.2에서 새 프로젝트 생성
# - C++ 프로젝트 선택
# - Blank 템플릿 선택
# - 이 폴더에 생성
```

### 2. 필요한 파일 구조
```
half-life-UE4/
├── Binaries/           # 컴파일된 바이너리 (Git 제외)
├── Content/            # 게임 에셋 (맵, 모델, 텍스처)
│   ├── Characters/     # 플레이어, NPC 모델
│   ├── Environments/   # 맵, 건물, 오브젝트
│   ├── Weapons/        # 무기 모델, 이펙트
│   └── UI/             # UI 요소
├── Source/             # C++ 소스 코드
│   ├── Public/         # 헤더 파일 (.h)
│   └── Private/        # 구현 파일 (.cpp)
├── Plugins/            # 플러그인
├── Saved/              # 저장 파일 (Git 제외)
├── Intermediate/       # 중간 파일 (Git 제외)
└── half-life-UE4.uproject  # 프로젝트 파일
```

---

## 💻 개발 구조

### C++ 클래스 구성
- **Character**: 플레이어/AI 캐릭터
- **Weapon**: 무기 시스템
- **AI**: 적 인공지능
- **GameMode**: 게임 규칙
- **PlayerController**: 플레이어 조종

### 주요 기능
- [ ] 플레이어 컨트롤러 (이동, 점프, 회전)
- [ ] 카메라 시스템 (1인칭 FPS)
- [ ] 무기 시스템 (권총, 라이플 등)
- [ ] 적 AI (순찰, 추적, 공격)
- [ ] 맵/레벨 디자인
- [ ] UI (체력, 탄약, 미니맵)
- [ ] 사운드 효과

---

## 📦 Git 워크플로우

### 커밋 메시지 규칙
```
[Feature] 새로운 기능 추가
[Fix] 버그 수정
[Refactor] 코드 리팩토링
[Docs] 문서 수정
```

### 예시
```bash
git add .
git commit -m "[Feature] Add basic player controller"
git push origin main
```

---

## 🎮 다음 단계

1. UE4 프로젝트 생성
2. 기본 캐릭터 클래스 작성
3. 플레이어 컨트롤러 구현
4. 무기 시스템 설계

---

**참고**: 
- `Content/` 폴더의 큰 에셋은 Git LFS 사용 권장
- `.gitignore`로 불필요한 파일 자동 제외됨
