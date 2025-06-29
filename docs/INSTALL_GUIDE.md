# SFML 설치 가이드 (Visual Studio 없이)

## 방법 1: 사전 컴파일된 SFML 바이너리 다운로드

### 1. SFML 공식 사이트에서 다운로드

1. https://www.sfml-dev.org/download.php 방문
2. Windows 섹션에서 컴파일러에 맞는 버전 다운로드:
   - **MinGW**: GCC (Code::Blocks, Dev-C++ 등)
   - **Visual C++**: Visual Studio용

### 2. 압축 해제 및 설정

1. 다운로드한 파일을 `C:\SFML` 또는 원하는 위치에 압축 해제
2. 환경 변수 설정 (선택사항):
   - `SFML_DIR=C:\SFML` 추가

### 3. CMakeLists.txt 수정 (수동 경로 지정)

```cmake
# SFML 경로 직접 지정
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED system window graphics network audio)
```

## 방법 2: MinGW + MSYS2 사용 (권장)

### 1. MSYS2 설치

1. https://www.msys2.org/ 에서 MSYS2 다운로드 및 설치
2. MSYS2 터미널에서 실행:

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-sfml
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-gcc
```

### 2. 환경 변수 설정

- PATH에 `C:\msys64\mingw64\bin` 추가

### 3. 빌드

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## 방법 3: Visual Studio Community 설치 (가장 쉬운 방법)

### 1. Visual Studio Community 2022 다운로드

- https://visualstudio.microsoft.com/ko/vs/community/
- 무료이며 개인/학습 목적으로 사용 가능

### 2. 설치 시 포함할 구성 요소

- "C++를 사용한 데스크톱 개발" 워크로드
- Windows 10/11 SDK
- CMake 도구

### 3. vcpkg로 SFML 설치

```cmd
cd vcpkg
.\vcpkg.exe install sfml:x64-windows
```

## 빠른 테스트 방법

현재 상황에서 SFML을 빠르게 테스트하려면:

1. **MinGW 설치**: https://sourceforge.net/projects/mingw-w64/
2. **사전 컴파일된 SFML 다운로드**: MinGW 버전
3. **간단한 컴파일 명령어 사용**:

```bash
g++ -I"SFML경로/include" -L"SFML경로/lib" src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o SFML_Study.exe
```

## 권장 사항

가장 편한 방법은 **MSYS2 + MinGW**를 사용하는 것입니다.

- 패키지 관리가 쉬움
- 의존성 자동 해결
- Linux와 유사한 개발 환경

자세한 MSYS2 설정 가이드는 `docs/MSYS2_SETUP.md`를 참조하세요.
