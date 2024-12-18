#include "context.h"

//Context Context::gContext = {};
//std::array<std::array<bool, Define::SCREEN_WIDTH>, Define::SCREEN_HEIGHT> Context::dp = {};

void Context::init() {
    start_time = std::chrono::high_resolution_clock::now();
    last_frame_ticks = start_time;
    is_exiting = false;
    emulator.init();
}

void Context::update() {
    auto& screen_ = screen;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_time);

    auto count = duration.count();
    auto val = (u8)((std::sin((float)count / 1000.f) + 1.0f) / 2.0f * 255);
    auto col = Color{val, 0, 0};
    auto col1 = col.reverse();
    for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
            screen_.setPixel({j, i}, dp[i][j] ? col1 : col);
        }
    }

    auto ticks = std::chrono::high_resolution_clock::now();
    auto delta_ticks = std::chrono::duration_cast<std::chrono::milliseconds>(ticks - last_frame_ticks);

    auto delta_time = std::min((f64)delta_ticks.count() / 1000.0, 0.125);
    emulator.update(delta_time);

    last_frame_ticks = ticks;
}
