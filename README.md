# C++ SFML Project - Automated Setup

This project provides a fully automated C++ SFML development environment for Windows with VS Code. Just press F5 and everything (MinGW, CMake, SFML) will be automatically installed and configured!

## Features

- ✅ **One-Click Setup**: Press F5 to automatically install and configure everything
- ✅ **No Admin Rights Required**: All tools are installed to user directory (`%USERPROFILE%\DevTools`)
- ✅ **Portable Installation**: Works on any Windows machine
- ✅ **Auto Build & Debug**: Complete CMake build and debugging setup
- ✅ **Cross-User Compatible**: Uses environment variables for different users

## Quick Start

1. **Clone this repository**:
   ```bash
   git clone <repository-url>
   cd SFML_Study
   ```

2. **Open in VS Code**:
   ```bash
   code .
   ```

3. **Press F5** and wait for automatic setup:
   - MinGW (TDM-GCC) will be downloaded and installed
   - CMake will be downloaded and installed  
   - SFML library will be downloaded and installed
   - Project will be built and executed automatically

That's it! The SFML window should open and you're ready to develop.

## Project Structure

```
cpp-sfml-project
├── src
│   └── main.cpp          # Main application source file
├── scripts
│   ├── setup-mingw.bat   # Script to install MinGW
│   └── install-dependencies.bat # Script to install required dependencies
├── CMakeLists.txt        # CMake configuration file
├── .vscode
│   ├── launch.json       # Debug configuration for VS Code
│   ├── tasks.json        # Build tasks for the project
│   └── c_cpp_properties.json # IntelliSense configuration
└── README.md             # Project documentation
```

## What Gets Installed Automatically

When you press F5, the following tools are automatically downloaded and installed to `%USERPROFILE%\DevTools`:

- **MinGW (TDM-GCC 64-bit)**: C++ compiler toolchain
- **CMake**: Build system generator  
- **SFML 2.6.1**: Graphics and multimedia library

All installations are:
- Portable (no registry changes)
- User-specific (no admin rights needed)
- Environment variable based (works for any user)

## Manual Setup (Alternative)

If you prefer manual setup, run these scripts in order:

```bash
# 1. Install MinGW compiler
scripts/setup-mingw.bat

# 2. Install CMake and SFML
scripts/install-dependencies.bat

# 3. Set up environment variables
scripts/setup-environment.bat

# 4. Build project
cmake -G "MinGW Makefiles" -S . -B build
cmake --build build

# 5. Run executable
cd build && ./cpp-sfml-project.exe
```

## Troubleshooting

**"unable to start debugging. the value of midebuggerpath is invalid"**
- This error occurs if gdb is not found in PATH
- The project automatically handles multiple installation paths
- If the error persists, restart VS Code after setup

**Build folder doesn't exist**
- The project automatically creates the build folder when needed
- CMake uses `-B build` flag to create the directory structure

**Permission errors**
- All installations use user directory (`%USERPROFILE%\DevTools`)
- No administrator privileges required

## Usage

Once the project is built successfully, the application will open a window initialized with SFML. You can modify the `src/main.cpp` file to implement your game logic or graphical application features.

## Contributing

Feel free to contribute to this project by submitting issues or pull requests. Your contributions are welcome!