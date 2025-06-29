@echo off
echo MSYS2 + MinGW + SFML 설치 확인 스크립트
echo ==========================================

:: 스크립트 실행 위치를 프로젝트 루트로 변경
cd /d "%~dp0.."

:: MSYS2 MinGW64 환경 설정
set PATH=C:\msys64\mingw64\bin;%PATH%

echo.
echo 1. GCC 컴파일러 확인:
gcc --version
if %ERRORLEVEL% NEQ 0 (
    echo ❌ GCC를 찾을 수 없습니다!
    echo MSYS2가 설치되어 있고 환경 변수가 설정되어 있는지 확인하세요.
    goto :error
) else (
    echo ✅ GCC 설치됨
)

echo.
echo 2. G++ 컴파일러 확인:
g++ --version
if %ERRORLEVEL% NEQ 0 (
    echo ❌ G++를 찾을 수 없습니다!
    goto :error
) else (
    echo ✅ G++ 설치됨
)

echo.
echo 3. CMake 확인:
cmake --version
if %ERRORLEVEL% NEQ 0 (
    echo ❌ CMake를 찾을 수 없습니다!
    echo MSYS2 터미널에서 다음 명령어 실행: pacman -S mingw-w64-x86_64-cmake
    goto :error
) else (
    echo ✅ CMake 설치됨
)

echo.
echo 4. pkg-config 확인:
pkg-config --version
if %ERRORLEVEL% NEQ 0 (
    echo ❌ pkg-config를 찾을 수 없습니다!
    goto :error
) else (
    echo ✅ pkg-config 설치됨
)

echo.
echo 5. SFML 라이브러리 확인:
pkg-config --exists sfml-all
if %ERRORLEVEL% NEQ 0 (
    echo ❌ SFML 라이브러리를 찾을 수 없습니다!
    echo MSYS2 터미널에서 다음 명령어 실행: pacman -S mingw-w64-x86_64-sfml
    goto :error
) else (
    echo ✅ SFML 라이브러리 설치됨
    echo SFML 버전:
    pkg-config --modversion sfml-all
)

echo.
echo ==========================================
echo ✅ 모든 도구가 올바르게 설치되었습니다!
echo 이제 scripts\build_mingw.bat를 실행하여 프로젝트를 빌드할 수 있습니다.
echo ==========================================
goto :end

:error
echo.
echo ==========================================
echo ❌ 설치가 완료되지 않았습니다!
echo docs\MSYS2_SETUP.md 파일의 설치 가이드를 참조하세요.
echo ==========================================

:end
pause
