#pragma once

#include <chrono>

#include "screen.h"
#include "emulator.h"

class Context {
public:
//    static Context gContext;
public:
    void init();
    void update();
public:
    Screen screen;
    Emulator emulator;
    std::array<std::array<bool, Define::SCREEN_WIDTH>, Define::SCREEN_HEIGHT> dp = {};
//private:
    std::chrono::time_point<std::chrono::steady_clock> start_time = {};
    std::chrono::time_point<std::chrono::steady_clock> last_frame_ticks = {};
    bool is_exiting = false;
};
