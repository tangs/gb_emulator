cmake_minimum_required(VERSION 3.10)
project(console_game_boy_emulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(./include)

add_executable(emulator src/main.cc)
target_link_libraries(emulator ncurses)