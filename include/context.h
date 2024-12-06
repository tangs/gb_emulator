#pragma once

#include <chrono>

#include "screen.h"
#include "emulator.h"

class Context {
public:
//    static Context gContext;
public:
    void start();
    void update();
public:
    Screen screen;
    Emulator emulator;
    std::array<std::array<bool, Define::SCREEN_WIDTH>, Define::SCREEN_HEIGHT> dp = {};
//private:
    std::chrono::time_point<std::chrono::steady_clock> startTime = {};
};
