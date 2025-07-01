@echo off
echo Checking MinGW installation...

REM Set user-specific paths (no admin rights needed)
SET USER_TOOLS=%USERPROFILE%\DevTools
SET MINGW_PATH=%USER_TOOLS%\mingw64\bin
SET TDM_GCC_PATH=%USER_TOOLS%\TDM-GCC-64\bin
SET SYSTEM_MINGW=C:\dev-tools\mingw64\bin

REM Check if g++ is available in PATH
where g++ >nul 2>nul
if %errorlevel% equ 0 (
    echo MinGW is already installed and available in PATH.
    g++ --version
    goto :EOF
)

REM Check if MinGW exists in user folder
if exist "%MINGW_PATH%\g++.exe" (
    echo MinGW found at %MINGW_PATH%
    set PATH=%PATH%;%MINGW_PATH%
    goto :EOF
)

if exist "%TDM_GCC_PATH%\g++.exe" (
    echo TDM-GCC found at %TDM_GCC_PATH%
    set PATH=%PATH%;%TDM_GCC_PATH%
    goto :EOF
)

REM Check if MinGW exists in system folder
if exist "%SYSTEM_MINGW%\g++.exe" (
    echo MinGW found at %SYSTEM_MINGW%
    set PATH=%PATH%;%SYSTEM_MINGW%
    goto :EOF
)

echo MinGW not found. Installing TDM-GCC (portable, no admin rights needed)...

REM Create user tools directory
if not exist "%USER_TOOLS%" mkdir "%USER_TOOLS%"

REM Download TDM-GCC (portable version)
echo Downloading TDM-GCC...
curl -L -o "%USER_TOOLS%\tdm-gcc-installer.exe" "https://jmeubank.github.io/tdm-gcc/download/tdm64-gcc-10.3.0-2.exe"
if %errorlevel% neq 0 (
    echo Failed to download TDM-GCC installer.
    exit /b 1
)

echo Installing TDM-GCC to user directory...
cd /d "%USER_TOOLS%"
tdm-gcc-installer.exe /S /D="%USER_TOOLS%\TDM-GCC-64"
del tdm-gcc-installer.exe

REM Add to current session PATH
set PATH=%PATH%;%USER_TOOLS%\TDM-GCC-64\bin

echo TDM-GCC installation completed.
echo GCC Version:
"%USER_TOOLS%\TDM-GCC-64\bin\g++.exe" --version