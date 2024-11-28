#pragma once

#include "define.h"
#include "point.h"
#include "color.h"

class Screen {
public:
    static constexpr int COUNT_PER_GROUP = 6;
    static constexpr int VERTICES_LEN = Define::SCREEN_WIDTH * Define::SCREEN_HEIGHT
            * Define::SCREEN_SCALE * COUNT_PER_GROUP;
public:
    float vertices_[VERTICES_LEN] = {};
public:
    Screen();
    void Clear(float r, float g, float b);
    void Clear(Color color);
    void SetPixel(int x, int y, float r, float g, float b);
    void SetPixel(Point pos, Color color);
};
