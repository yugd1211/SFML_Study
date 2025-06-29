cmake_minimum_required(VERSION 3.16)
project(SFML_Study)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MinGW 특정 설정
if(MINGW)
    # MinGW에서 콘솔과 윈도우 모두 표시
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
endif()

# SFML 찾기 (MSYS2/MinGW 방식)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all>=2.5)

# 대체 방법: find_package 사용
if(NOT SFML_FOUND)
    find_package(SFML 2.5 COMPONENTS system window graphics network audio)
endif()

# 실행 파일 생성
add_executable(SFML_Study src/main.cpp)

# SFML 라이브러리 링크
if(SFML_FOUND AND SFML_LIBRARIES)
    # pkg-config 방식
    target_include_directories(SFML_Study PRIVATE ${SFML_INCLUDE_DIRS})
    target_link_libraries(SFML_Study PRIVATE ${SFML_LIBRARIES})
    target_compile_options(SFML_Study PRIVATE ${SFML_CFLAGS_OTHER})
else()
    # find_package 방식
    target_link_libraries(SFML_Study PRIVATE 
        sfml-system 
        sfml-window 
        sfml-graphics 
        sfml-audio 
        sfml-network
    )
endif()

# 헤더 파일 디렉토리 포함
target_include_directories(SFML_Study PRIVATE include)

# Windows에서 정적 링크 설정
if(WIN32 AND MINGW)
    # 정적 링크를 위한 추가 라이브러리
    target_link_libraries(SFML_Study PRIVATE 
        -static-libgcc 
        -static-libstdc++
        winmm
        gdi32
        opengl32
        freetype
    )
endif()
