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
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(${SFML_INCLUDE_DIRS})

# Create executable
add_executable(cpp-sfml-project src/main.cpp)

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