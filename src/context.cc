#include "context.h"

//Context Context::gContext = {};
//std::array<std::array<bool, Define::SCREEN_WIDTH>, Define::SCREEN_HEIGHT> Context::dp = {};

void Context::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Context::update() {
    auto& screen_ = screen;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime);

    auto count = duration.count();
    auto val = (u8)((std::sin((float)count / 1000.f) + 1.0f) / 2.0f * 255);
    auto col = Color{val, 0, 0};
    auto col1 = col.reverse();
    for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
            screen_.SetPixel({j, i}, dp[i][j] ? col1 : col);
        }
    }
}
