@echo off
echo SFML 프로젝트 빌드 (MinGW) 시작...

:: 스크립트 실행 위치를 프로젝트 루트로 변경
cd /d "%~dp0.."

:: MSYS2 MinGW64 환경 설정
set PATH=C:\msys64\mingw64\bin;%PATH%

:: 빌드 디렉토리 생성
if not exist build mkdir build
cd build

echo CMake 구성 중...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

if %ERRORLEVEL% NEQ 0 (
    echo CMake 구성 실패!
    echo MSYS2가 설치되어 있고 환경 변수가 설정되어 있는지 확인하세요.
    pause
    exit /b 1
)

echo 빌드 실행 중...
mingw32-make

if %ERRORLEVEL% NEQ 0 (
    echo 빌드 실패!
    pause
    exit /b 1
)

echo.
echo ========================================
echo 빌드 완료!
echo 실행 파일: build\SFML_Study.exe
echo ========================================
echo.
echo 실행하려면 ENTER를 누르세요... (VS Code에서 F5로 실행한 경우 무시하고 ESC)
pause > nul
SFML_Study.exe
