cmake_minimum_required(VERSION 3.10)
project(console_game_boy_emulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ./include
        ./third/glfw-3.4/include
        ./third/glad/include
)
link_directories(
        ./third/glfw-3.4/lib-arm64
)

find_library(COREFOUNDATION_LIBRARY CoreFoundation)
find_library(IOKIT_LIBRARY IOKit)
find_library(COCOA_LIBRARY Cocoa)
find_library(COREGRAPHICS_LIBRARY CoreGraphics)

add_executable(emulator
        third/glad/src/glad.c
        src/main.cc
        src/shader.cc
        src/screen.cc
        src/cartridge.cc
)
target_link_libraries(
        emulator
        glfw3
        ${COREFOUNDATION_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COCOA_LIBRARY}
        ${COREGRAPHICS_LIBRARY}
)
