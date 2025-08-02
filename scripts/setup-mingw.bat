@echo off
setlocal EnableDelayedExpansion
echo Checking MinGW installation...

REM Set user-specific paths
SET USER_TOOLS=%USERPROFILE%\DevTools
SET MINGW_INSTALL_PATH=%USER_TOOLS%\mingw64
SET MINGW_BIN_PATH=%MINGW_INSTALL_PATH%\bin
SET SEVEN_ZIP_PATH=%USER_TOOLS%\7-Zip
SET SEVEN_ZIP_EXE=%SEVEN_ZIP_PATH%\7z.exe

REM Check if MinGW-w64 13.1.0 is already installed
if exist "!MINGW_BIN_PATH!\g++.exe" (
    echo MinGW-w64 GCC 13.1.0 found at !MINGW_BIN_PATH!
    echo GCC Version:
    "!MINGW_BIN_PATH!\g++.exe" --version
    goto :EOF
)

echo MinGW-w64 GCC 13.1.0 not found. Installing...

REM Create user tools directory
if not exist "!USER_TOOLS!" mkdir "!USER_TOOLS!"

REM Download 7-Zip if not present
if not exist "!SEVEN_ZIP_EXE!" (
    echo Downloading 7-Zip...
    curl -LO "https://www.7-zip.org/a/7z2301-x64.exe"
    if !errorlevel! neq 0 (
        echo Failed to download 7-Zip installer.
        exit /b 1
    )
    
    echo Installing 7-Zip...
    start /wait 7z2301-x64.exe /S /D="!SEVEN_ZIP_PATH!"
    del 7z2301-x64.exe
    if not exist "!SEVEN_ZIP_EXE!" (
        echo 7-Zip installation failed.
        exit /b 1
    )
)

REM Download MinGW-w64 GCC 13.1.0 (7z archive) from niXman/mingw-builds-binaries
SET MINGW_ARCHIVE_URL="https://github.com/niXman/mingw-builds-binaries/releases/download/13.1.0-rt_v11-rev1/x86_64-13.1.0-release-posix-seh-ucrt-rt_v11-rev1.7z"
SET MINGW_ARCHIVE_NAME=x86_64-13.1.0-release-posix-seh-ucrt-rt_v11-rev1.7z
SET MINGW_EXTRACT_DIR=mingw64
SET MINGW_DOWNLOAD_PATH="!USER_TOOLS!\!MINGW_ARCHIVE_NAME!"

echo Downloading MinGW-w64 GCC 13.1.0...
curl -L -o "!MINGW_DOWNLOAD_PATH!" !MINGW_ARCHIVE_URL!
if !errorlevel! neq 0 (
    echo Failed to download MinGW-w64.
    exit /b 1
)

echo Extracting MinGW-w64...
"!SEVEN_ZIP_EXE!" x "!MINGW_DOWNLOAD_PATH!" -o"!USER_TOOLS!" -y
if !errorlevel! neq 0 (
    echo Failed to extract MinGW-w64.
    exit /b 1
)

REM Rename the extracted directory to 'mingw64' for consistency (niXman builds usually extract directly to mingw64)
REM if not exist "!MINGW_INSTALL_PATH!" ren "!USER_TOOLS!\!MINGW_EXTRACT_DIR!" mingw64
del "!MINGW_DOWNLOAD_PATH!"

REM Add to current session PATH
set "PATH=!PATH!;!MINGW_BIN_PATH!"

REM Add to user-level PATH (requires setx)
echo Setting user-level PATH...
setx PATH "%PATH%;!MINGW_BIN_PATH!" > nul 2>&1

echo MinGW-w64 GCC 13.1.0 installation completed.
echo GCC Version:
"!MINGW_BIN_PATH!\g++.exe" --version