@echo off
setlocal EnableDelayedExpansion

echo Checking dependencies...

REM Set user-specific paths
SET USER_TOOLS=%USERPROFILE%\DevTools
SET CMAKE_PATH=%USER_TOOLS%\cmake\bin
SET SFML_PATH=%USER_TOOLS%\SFML
SET SYSTEM_CMAKE=C:\dev-tools\cmake\bin
SET SYSTEM_SFML=C:\dev-tools\sfml

REM Check for CMake installation
where cmake >nul 2>nul
if !errorlevel! equ 0 (
    echo CMake is already installed.
    cmake --version
) else (
    REM Check user-installed CMake
    if exist "!CMAKE_PATH!\cmake.exe" (
        echo CMake found in user directory.
        set "PATH=!PATH!;!CMAKE_PATH!"
    REM Check system-installed CMake
    ) else if exist "!SYSTEM_CMAKE!\cmake.exe" (
        echo CMake found in system directory.
        set "PATH=!PATH!;!SYSTEM_CMAKE!"
    ) else (
        echo CMake is not installed. Installing CMake to user directory...
        
        REM Create user tools directory
        if not exist "!USER_TOOLS!" mkdir "!USER_TOOLS!"
        
        REM Download CMake portable version
        curl -LO "https://github.com/Kitware/CMake/releases/download/v3.27.7/cmake-3.27.7-windows-x86_64.zip"
        if !errorlevel! neq 0 (
            echo Failed to download CMake.
            exit /b 1
        )
        
        echo Extracting CMake...
        powershell -command "Expand-Archive -Path 'cmake-3.27.7-windows-x86_64.zip' -DestinationPath '!USER_TOOLS!' -Force"
        ren "!USER_TOOLS!\cmake-3.27.7-windows-x86_64" cmake
        del "cmake-3.27.7-windows-x86_64.zip"
        
        REM Add to current session PATH
        set "PATH=!PATH!;!CMAKE_PATH!"
        echo CMake installed to user directory.
    )
)

REM Check for SFML installation
if not exist "!SFML_PATH!" (
    if not exist "!SYSTEM_SFML!" (
        echo SFML is not installed. Installing SFML to user directory...
    
    REM Create user tools directory
    if not exist "!USER_TOOLS!" mkdir "!USER_TOOLS!"
    
    REM Download SFML for MinGW
    curl -LO "https://www.sfml-dev.org/files/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip"
    if !errorlevel! neq 0 (
        echo Failed to download SFML.
        exit /b 1
    )
    
    echo Extracting SFML...
    powershell -command "Expand-Archive -Path 'SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip' -DestinationPath '!USER_TOOLS!' -Force"
    ren "!USER_TOOLS!\SFML-2.6.1" SFML
    del "SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip"        echo SFML installed to !SFML_PATH!
    ) else (
        echo SFML found in system directory.
    )
) else (
    echo SFML is already installed in user directory.
)

echo All dependencies are installed.