# MSYS2 + MinGW + SFML 설치 가이드

## 1단계: MSYS2 다운로드 및 설치

1. **MSYS2 다운로드**

   - https://www.msys2.org/ 방문
   - `msys2-x86_64-*.exe` 다운로드
   - 설치 (기본 경로: `C:\msys64`)

2. **MSYS2 업데이트**

   ```bash
   # MSYS2 터미널에서 실행
   pacman -Syu
   ```

   설치 후 터미널이 닫히면 다시 열어서:

   ```bash
   pacman -Su
   ```

## 2단계: 개발 도구 설치

MSYS2 터미널(MSYS2 MINGW64)에서 다음 명령어들을 실행하세요:

```bash
# 기본 개발 도구
pacman -S mingw-w64-x86_64-toolchain

# CMake
pacman -S mingw-w64-x86_64-cmake

# SFML 라이브러리
pacman -S mingw-w64-x86_64-sfml

# Git (필요시)
pacman -S git

# Make
pacman -S mingw-w64-x86_64-make
```

## 3단계: 환경 변수 설정

### 3-1. Windows 환경 변수 설정 (Windows에서 실행할 때)

**Windows 환경 변수 PATH에 추가:**

```
C:\msys64\mingw64\bin
```

**설정 방법:**

1. 시작 메뉴 → "환경 변수" 검색
2. "시스템 환경 변수 편집" 클릭
3. "환경 변수" 버튼 클릭
4. 시스템 변수의 "Path" 선택 → "편집"
5. "새로 만들기" → `C:\msys64\mingw64\bin` 추가
6. 확인

### 3-2. MSYS2 내부 환경 변수 설정 (MSYS2 터미널에서 실행할 때)

**임시 설정 (현재 세션에만 적용):**

```bash
export PATH="/mingw64/bin:$PATH"
export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"
```

**영구 설정 (권장):**
MSYS2 터미널에서 다음 명령어 실행:

```bash
# 홈 디렉토리의 .bashrc 파일 편집
echo 'export PATH="/mingw64/bin:$PATH"' >> ~/.bashrc
echo 'export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"' >> ~/.bashrc

# 설정 적용
source ~/.bashrc
```

**또는 nano 에디터로 직접 편집:**

```bash
# .bashrc 파일 열기
nano ~/.bashrc

# 파일 끝에 다음 라인들 추가:
export PATH="/mingw64/bin:$PATH"
export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"

# Ctrl+X → Y → Enter로 저장 후 종료
# 설정 적용
source ~/.bashrc
```

## 4단계: 설치 확인

### Windows CMD/PowerShell에서 확인:

```cmd
gcc --version
g++ --version
cmake --version
```

### MSYS2 MINGW64 터미널에서 확인:

```bash
# 환경 변수 확인
echo $PATH
which gcc
which g++
which cmake

# 버전 확인
gcc --version
g++ --version
cmake --version

# SFML 확인
pkg-config --exists sfml-all && echo "SFML found" || echo "SFML not found"
pkg-config --modversion sfml-all
```

## 5단계: 프로젝트 빌드

### 방법 1: 자동 환경 설정 스크립트 사용 (권장)

```bash
# MSYS2 MINGW64 터미널에서 실행
cd /c/Users/dbrud/Documents/SFML_Study

# 환경 설정 (최초 1회만)
bash scripts/setup_msys2_env.sh

# 빌드 및 실행
bash scripts/build_msys2.sh
```

### 방법 2: 수동 명령어

```bash
# MSYS2 MINGW64 터미널에서
cd /c/Users/dbrud/Documents/SFML_Study

# 환경 변수 설정 (매번 필요 - .bashrc에 추가하면 자동)
export PATH="/mingw64/bin:$PATH"
export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"

# 빌드
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make

# 실행
./SFML_Study.exe
```

### 방법 3: Makefile 사용

```bash
# MSYS2 MINGW64 터미널에서
cd /c/Users/dbrud/Documents/SFML_Study

# 환경 변수 설정
export PATH="/mingw64/bin:$PATH"
export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"

# 빌드 및 실행
make
make run
```

### 방법 4: Windows 배치 파일 사용

```cmd
# Windows CMD/PowerShell에서
cd C:\Users\dbrud\Documents\SFML_Study

# 설치 확인
scripts\check_installation.bat

# 빌드 및 실행
scripts\build_mingw.bat
```

## 주의사항 및 문제 해결

### 중요한 주의사항:

- **MSYS2 MINGW64** 터미널을 사용하세요 (일반 MSYS2가 아님)
- MSYS2 내부에서도 환경 변수 설정이 필요합니다 (Windows PATH와 별개)
- 빌드는 MSYS2 터미널에서 하는 것이 안전합니다
- PATH 설정 후 기존 터미널은 재시작하세요

### 자주 발생하는 문제들:

**1. "gcc를 찾을 수 없습니다" 오류**

```bash
# 해결방법:
export PATH="/mingw64/bin:$PATH"
# 또는 패키지 재설치:
pacman -S mingw-w64-x86_64-toolchain
```

**2. "SFML을 찾을 수 없습니다" 오류**

```bash
# 해결방법:
export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"
# 또는 SFML 재설치:
pacman -S mingw-w64-x86_64-sfml
```

**3. "cmake를 찾을 수 없습니다" 오류**

```bash
# 해결방법:
pacman -S mingw-w64-x86_64-cmake
```

**4. 빌드는 되지만 실행이 안 되는 경우**

- DLL 파일이 없는 경우입니다
- MSYS2 터미널에서 실행하거나
- `/mingw64/bin`의 DLL 파일들을 실행 파일과 같은 폴더에 복사하세요

### 환경 설정 영구 적용:

```bash
# ~/.bashrc 파일에 다음 내용 추가:
echo 'export PATH="/mingw64/bin:$PATH"' >> ~/.bashrc
echo 'export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"' >> ~/.bashrc
source ~/.bashrc
```
