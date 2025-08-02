@echo off
setlocal EnableDelayedExpansion

echo Starting full setup and build process...

SET PROJECT_ROOT=%~dp0..
SET USER_TOOLS=%USERPROFILE%\DevTools
SET MINGW_BIN_PATH=%USER_TOOLS%\mingw64\bin
SET CMAKE_BIN_PATH=%USER_TOOLS%\cmake\bin

REM Step 1: Setup MinGW/GCC 13.1.0
call "%PROJECT_ROOT%\scripts\setup-mingw.bat"
if !errorlevel! neq 0 (
    echo MinGW setup failed. Exiting.
    exit /b 1
)

REM Add newly installed MinGW to current session PATH
set "PATH=!PATH!;!MINGW_BIN_PATH!"

REM Step 2: Install other dependencies (CMake, SFML)
call "%PROJECT_ROOT%\scripts\install-dependencies.bat"
if !errorlevel! neq 0 (
    echo Dependency installation failed. Exiting.
    exit /b 1
)

REM Add newly installed CMake to current session PATH
set "PATH=!PATH!;!CMAKE_BIN_PATH!"

REM Step 3: Update c_cpp_properties.json with correct compiler path
REM echo Updating c_cpp_properties.json...
REM SET CPP_PROPERTIES_FILE="%PROJECT_ROOT%\.vscode\c_cpp_properties.json"

REM Use PowerShell for robust string replacement
REM powershell -command "(Get-Content '!CPP_PROPERTIES_FILE!') -replace '(\"compilerPath\": \".*?\"', '"compilerPath": "!MINGW_BIN_PATH!/g++.exe"' | Set-Content '!CPP_PROPERTIES_FILE!')"
REM if !errorlevel! neq 0 (
REM     echo Failed to update c_cpp_properties.json. Manual update may be required.
REM )

REM echo c_cpp_properties.json updated.

REM Step 4: Clean build directory
echo Cleaning build directory...
if exist "%PROJECT_ROOT%\build" rmdir /s /q "%PROJECT_ROOT%\build"

REM Step 5: Configure and Build with CMake
echo Configuring and building project with CMake...

REM Ensure CMake is in PATH for this session
where cmake >nul 2>nul
if !errorlevel! neq 0 (
    echo CMake not found in PATH. Please ensure it's installed and in your PATH.
    exit /b 1
)

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH="!MINGW_BIN_PATH!\gcc.exe" -DCMAKE_CXX_COMPILER:FILEPATH="!MINGW_BIN_PATH!\g++.exe" --no-warn-unused-cli -S "%PROJECT_ROOT%" -B "%PROJECT_ROOT%\build" -G Ninja
if !errorlevel! neq 0 (
    echo CMake configuration failed. Exiting.
    exit /b 1
)

cmake --build "%PROJECT_ROOT%\build"
if !errorlevel! neq 0 (
    echo CMake build failed. Exiting.
    exit /b 1
)


