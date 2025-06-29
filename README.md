# SFML_Study

C++ SFML 라이브러리 공부용 레포지토리입니다

## 📁 프로젝트 구조

```
SFML_Study/
├── src/                    # 소스 코드
│   └── main.cpp           # 메인 프로그램
├── include/               # 헤더 파일
├── scripts/               # 빌드 및 설정 스크립트
│   ├── build_mingw.bat    # Windows MinGW 빌드 스크립트
│   ├── build_msys2.sh     # MSYS2 빌드 스크립트
│   ├── setup_msys2_env.sh # MSYS2 환경 설정 스크립트
│   └── check_installation.bat # 설치 확인 스크립트
├── docs/                  # 문서 파일들
│   ├── MSYS2_SETUP.md     # MSYS2 설치 가이드
│   └── INSTALL_GUIDE.md   # 일반 설치 가이드
├── .vscode/               # VS Code 설정
│   ├── tasks.json         # 빌드 작업 설정
│   ├── launch.json        # 디버그 설정
│   ├── settings.json      # 워크스페이스 설정
│   └── extensions.json    # 권장 확장 기능
├── build/                 # 빌드 출력 (생성됨)
├── vcpkg/                 # 패키지 관리자 (선택사항)
├── CMakeLists.txt         # CMake 설정 파일
├── Makefile              # Make 빌드 파일
└── README.md             # 이 파일
```

## 🚀 빠른 시작

### 1. 설치 확인

```bash
# Windows에서
scripts\check_installation.bat

# MSYS2에서
bash scripts/setup_msys2_env.sh
```

### 2. 빌드 및 실행

```bash
# Windows MinGW (권장)
scripts\build_mingw.bat

# MSYS2 터미널
bash scripts/build_msys2.sh

# VS Code에서
Ctrl+Shift+B (기본 빌드 작업)
```

## 📋 설치 및 빌드 방법

## Windows 빌드

### vscode : MSYS2 + MinGW (권장)

1. **MSYS2 설치**: [docs/MSYS2_SETUP.md](docs/MSYS2_SETUP.md) 참조
2. **필수 패키지 설치**:
   ```bash
   pacman -S mingw-w64-x86_64-toolchain
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-sfml
   ```
3. **빌드**: `scripts\build_mingw.bat` 실행

### visual studio : 기존 방법들

- Visual Studio + vcpkg
- 사전 컴파일된 SFML 바이너리

자세한 내용은 [docs/INSTALL_GUIDE.md](docs/INSTALL_GUIDE.md) 참조

## 🎮 VS Code 사용법

### 단축키

- `Ctrl+Shift+B`: 기본 빌드
- `F5`: 디버그 실행
- `Ctrl+F5`: 디버그 없이 실행

### 작업 목록

- **Build SFML Project (MinGW)**: 기본 빌드 작업
- **Build with CMake (MinGW)**: CMake 수동 빌드
- **Configure CMake (MinGW)**: CMake 구성만
- **Build with Make**: Make 직접 사용
- **Clean Build**: 빌드 폴더 정리
- **Run SFML Program**: 프로그램 실행

## 📚 SFML 기본 개념

### 주요 모듈

- **System**: 벡터, 시간, 스레드 등 기본 시스템 기능
- **Window**: 윈도우 생성 및 이벤트 처리
- **Graphics**: 2D 그래픽 렌더링
- **Audio**: 오디오 재생
- **Network**: 네트워크 통신

### 기본 구조

```cpp
#include <SFML/Graphics.hpp>

int main() {
    // 1. 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "제목");

    // 2. 메인 루프
    while (window.isOpen()) {
        // 3. 이벤트 처리
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 4. 화면 클리어
        window.clear();

        // 5. 객체 그리기
        // window.draw(객체);

        // 6. 화면 업데이트
        window.display();
    }

    return 0;
}
```

## 🔧 문제 해결

### 자주 발생하는 문제

1. **"gcc를 찾을 수 없습니다"**: MSYS2 PATH 설정 확인
2. **"SFML을 찾을 수 없습니다"**: PKG_CONFIG_PATH 설정 확인
3. **DLL 오류**: MSYS2 터미널에서 실행하거나 DLL 복사
