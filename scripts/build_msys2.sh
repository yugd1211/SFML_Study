#!/bin/bash
# MSYS2 MINGW64 터미널에서 실행할 빌드 스크립트

echo "SFML 프로젝트 빌드 (MSYS2 MinGW64) 시작..."

# 스크립트 실행 위치를 프로젝트 루트로 변경
cd "$(dirname "$0")/.."

# 환경 변수 설정 확인
echo "환경 변수 확인 중..."
export PATH="/mingw64/bin:$PATH"
export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"

# 필수 도구 확인
echo "필수 도구 확인 중..."
if ! command -v gcc &> /dev/null; then
    echo "❌ GCC를 찾을 수 없습니다!"
    echo "pacman -S mingw-w64-x86_64-toolchain 를 실행하세요."
    exit 1
fi

if ! command -v cmake &> /dev/null; then
    echo "❌ CMake를 찾을 수 없습니다!"
    echo "pacman -S mingw-w64-x86_64-cmake 를 실행하세요."
    exit 1
fi

if ! pkg-config --exists sfml-all; then
    echo "❌ SFML을 찾을 수 없습니다!"
    echo "pacman -S mingw-w64-x86_64-sfml 를 실행하세요."
    exit 1
fi

echo "✅ 모든 도구가 준비되었습니다."

# 빌드 디렉토리 생성
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

echo "CMake 구성 중..."
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "❌ CMake 구성 실패!"
    echo "CMakeLists.txt 파일을 확인하세요."
    exit 1
fi

echo "빌드 실행 중..."
if command -v mingw32-make &> /dev/null; then
    mingw32-make
else
    make
fi

if [ $? -ne 0 ]; then
    echo "❌ 빌드 실패!"
    exit 1
fi

echo ""
echo "========================================"
echo "✅ 빌드 완료!"
echo "실행 파일: build/SFML_Study.exe"
echo "========================================"
echo ""
echo "실행하시겠습니까? (y/n)"
read -r response
if [[ "$response" =~ ^[Yy]$ ]]; then
    ./SFML_Study.exe
fi
