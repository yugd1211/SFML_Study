@echo off
setlocal EnableDelayedExpansion

SET PROJECT_ROOT=%~dp0..

echo Running the compiled SFML project and checking for UCRT issues...
"%PROJECT_ROOT%\build\cpp-sfml-project.exe"
if !errorlevel! equ 3221225785 (
    echo WARNING: The SFML project exited with error code 0xc0000139. This often indicates missing Universal C Runtime (UCRT) DLLs. Please install the latest Microsoft Visual C++ Redistributable for Visual Studio 2015, 2017, 2019, and 2022 (x64). You can download it from: https://learn.microsoft.com/ko-kr/cpp/windows/latest-supported-vc-redist
) else if !errorlevel! neq 0 (
    echo The SFML project exited with an unexpected error code: !errorlevel!
) else (
    echo The SFML project ran successfully.
)