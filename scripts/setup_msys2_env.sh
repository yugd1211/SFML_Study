#!/bin/bash
# MSYS2 환경 설정 스크립트
# 사용법: MSYS2 MINGW64 터미널에서 실행
# bash scripts/setup_msys2_env.sh

echo "MSYS2 환경 설정 스크립트"
echo "========================"

# 스크립트 실행 위치를 프로젝트 루트로 변경
cd "$(dirname "$0")/.."

# 현재 PATH 확인
echo "현재 PATH:"
echo $PATH
echo ""

# 필요한 경로들이 PATH에 있는지 확인
if [[ ":$PATH:" == *":/mingw64/bin:"* ]]; then
    echo "✅ /mingw64/bin이 PATH에 있습니다."
else
    echo "❌ /mingw64/bin이 PATH에 없습니다."
    echo "환경 변수를 설정합니다..."
    
    # .bashrc에 PATH 설정 추가
    if ! grep -q 'export PATH="/mingw64/bin:$PATH"' ~/.bashrc 2>/dev/null; then
        echo 'export PATH="/mingw64/bin:$PATH"' >> ~/.bashrc
        echo "PATH 설정을 ~/.bashrc에 추가했습니다."
    else
        echo "PATH 설정이 이미 ~/.bashrc에 있습니다."
    fi
fi

# PKG_CONFIG_PATH 확인 및 설정
if [[ ":$PKG_CONFIG_PATH:" == *":/mingw64/lib/pkgconfig:"* ]]; then
    echo "✅ PKG_CONFIG_PATH가 올바르게 설정되어 있습니다."
else
    echo "❌ PKG_CONFIG_PATH 설정이 필요합니다."
    
    if ! grep -q 'export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"' ~/.bashrc 2>/dev/null; then
        echo 'export PKG_CONFIG_PATH="/mingw64/lib/pkgconfig:$PKG_CONFIG_PATH"' >> ~/.bashrc
        echo "PKG_CONFIG_PATH 설정을 ~/.bashrc에 추가했습니다."
    else
        echo "PKG_CONFIG_PATH 설정이 이미 ~/.bashrc에 있습니다."
    fi
fi

echo ""
echo "설정 적용 중..."
source ~/.bashrc

echo ""
echo "도구 확인:"
echo "=========="

# GCC 확인
if command -v gcc &> /dev/null; then
    echo "✅ GCC: $(gcc --version | head -n1)"
else
    echo "❌ GCC를 찾을 수 없습니다."
    echo "   pacman -S mingw-w64-x86_64-toolchain 를 실행하세요."
fi

# G++ 확인
if command -v g++ &> /dev/null; then
    echo "✅ G++: $(g++ --version | head -n1)"
else
    echo "❌ G++를 찾을 수 없습니다."
fi

# CMake 확인
if command -v cmake &> /dev/null; then
    echo "✅ CMake: $(cmake --version | head -n1)"
else
    echo "❌ CMake를 찾을 수 없습니다."
    echo "   pacman -S mingw-w64-x86_64-cmake 를 실행하세요."
fi

# Make 확인
if command -v mingw32-make &> /dev/null; then
    echo "✅ Make: mingw32-make 사용 가능"
elif command -v make &> /dev/null; then
    echo "✅ Make: make 사용 가능"
else
    echo "❌ Make를 찾을 수 없습니다."
    echo "   pacman -S mingw-w64-x86_64-make 를 실행하세요."
fi

# pkg-config 확인
if command -v pkg-config &> /dev/null; then
    echo "✅ pkg-config: $(pkg-config --version)"
else
    echo "❌ pkg-config를 찾을 수 없습니다."
fi

# SFML 확인
echo ""
echo "SFML 라이브러리 확인:"
if pkg-config --exists sfml-all 2>/dev/null; then
    echo "✅ SFML 버전: $(pkg-config --modversion sfml-all)"
    echo "   SFML 설치 경로: $(pkg-config --variable=prefix sfml-all)"
else
    echo "❌ SFML을 찾을 수 없습니다."
    echo "   pacman -S mingw-w64-x86_64-sfml 를 실행하세요."
fi

echo ""
echo "========================"
echo "설정 완료!"
echo "새로운 터미널을 열거나 'source ~/.bashrc'를 실행하여 설정을 적용하세요."
echo "========================"
