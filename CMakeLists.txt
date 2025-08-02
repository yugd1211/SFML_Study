cmake_minimum_required(VERSION 3.10)
project(cpp-sfml-project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows specific settings
if(WIN32)
    # Check for user-installed SFML first
    if(EXISTS "$ENV{USERPROFILE}/DevTools/SFML")
        set(SFML_ROOT "$ENV{USERPROFILE}/DevTools/SFML")
        message(STATUS "Using user-installed SFML at: ${SFML_ROOT}")
    # Fallback to system installation
    elseif(EXISTS "C:/SFML/SFML-2.6.1")
        set(SFML_ROOT "C:/SFML/SFML-2.6.1")
        message(STATUS "Using system-installed SFML at: ${SFML_ROOT}")
    endif()
    
    if(SFML_ROOT)
        set(CMAKE_PREFIX_PATH ${SFML_ROOT})
        # Add SFML DLL path to runtime
        set(SFML_DLL_DIR "${SFML_ROOT}/bin")
    endif()
endif()

# Find SFML
cmake_policy(SET CMP0074 NEW)
find_package(SFML 2.6.1 CONFIG REQUIRED COMPONENTS graphics window system network audio)

# Include directories
include_directories(${SFML_INCLUDE_DIRS})

# Collect all source files from src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "src/*.cxx")

# If no source files found, fallback to main.cpp
if(NOT SOURCES)
    set(SOURCES "src/main.cpp")
    message(WARNING "No source files found in src/, using main.cpp")
else()
    message(STATUS "Found source files: ${SOURCES}")
endif()

# Create executable with all source files
add_executable(cpp-sfml-project ${SOURCES})

# Add include directories for headers in src/
target_include_directories(cpp-sfml-project PRIVATE src)

# Link libraries
target_link_libraries(cpp-sfml-project sfml-graphics sfml-window sfml-system)

# Windows specific: Copy SFML DLLs to output directory
if(WIN32 AND EXISTS ${SFML_DLL_DIR})
    file(GLOB SFML_DLLS "${SFML_DLL_DIR}/*.dll")
    foreach(dll ${SFML_DLLS})
        add_custom_command(TARGET cpp-sfml-project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${dll} $<TARGET_FILE_DIR:cpp-sfml-project>)
    endforeach()
endif()