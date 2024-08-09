#pragma once

#include "define.h"

class Screen {
public:
    static constexpr int COUNT_PER_GROUP = 6;
    static constexpr int VERTICES_LEN = Define::SCREEN_WIDTH * Define::SCREEN_HEIGHT * COUNT_PER_GROUP;
public:
    float vertices[VERTICES_LEN] = {};
};