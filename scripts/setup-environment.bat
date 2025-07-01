@echo off
REM Set environment variables for current session and future sessions (user-level)

SET USER_TOOLS=%USERPROFILE%\DevTools

REM Add paths to current session (both user and system paths)
set PATH=%PATH%;%USER_TOOLS%\TDM-GCC-64\bin;C:\dev-tools\mingw64\bin
set PATH=%PATH%;%USER_TOOLS%\cmake\bin;C:\dev-tools\cmake\bin

REM Set user-level environment variables (no admin rights needed)
if exist "%USER_TOOLS%\TDM-GCC-64\bin\g++.exe" (
    echo Setting up TDM-GCC in PATH...
    setx PATH "%PATH%;%USER_TOOLS%\TDM-GCC-64\bin" > nul 2>&1
)

if exist "C:\dev-tools\mingw64\bin\g++.exe" (
    echo Setting up system MinGW in PATH...
    setx PATH "%PATH%;C:\dev-tools\mingw64\bin" > nul 2>&1
)

if exist "%USER_TOOLS%\cmake\bin\cmake.exe" (
    echo Setting up CMake in PATH...
    setx PATH "%PATH%;%USER_TOOLS%\cmake\bin" > nul 2>&1
)

if exist "C:\dev-tools\cmake\bin\cmake.exe" (
    echo Setting up system CMake in PATH...
    setx PATH "%PATH%;C:\dev-tools\cmake\bin" > nul 2>&1
)

echo Environment variables updated for user profile.
echo Please restart VS Code to use the updated PATH.
