#include "screen.h"

#include <cassert>

Screen::Screen() {
    auto& vertices = this->vertices_;
    int idx = 0;
    for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
            float percentX = (float) j / Define::SCREEN_WIDTH;
            float percentY = (float) i / Define::SCREEN_HEIGHT;
            float x = percentX * 2.0f - 1.0f;
            float y = percentY * 2.0f - 1.0f;

            // position(x, y, z)
            vertices[idx++] = x;
            vertices[idx++] = y;
            vertices[idx++] = 0.0f;

            idx += 3;
        }
    }
}

void Screen::Clear(float r, float g, float b) {
    auto& vertices = this->vertices_;
    int idx = 0;
    for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
            idx += 3;

            // color(r, g, b)
            vertices[idx++] = r;
            vertices[idx++] = g;
            vertices[idx++] = b;
        }
    }
}

void Screen::SetPixel(int x, int y, float r, float g, float b) {
    assert(x > 0 && x < Define::SCREEN_WIDTH);
    assert(y > 0 && x < Define::SCREEN_HEIGHT);

    auto& vertices = this->vertices_;
    int idx = (y * Define::SCREEN_WIDTH + x) * COUNT_PER_GROUP;
    vertices[idx++] = r;
    vertices[idx++] = g;
    vertices[idx++] = b;
}
