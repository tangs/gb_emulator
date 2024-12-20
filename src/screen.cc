#include "screen.h"

#include <iostream>
#include <cassert>

Screen::Screen() {
    auto& vertices = this->vertices_;
    int idx = 0;
    for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
            auto percentX = (float) j / Define::SCREEN_WIDTH;
            auto percentY = (float) i / Define::SCREEN_HEIGHT;
            auto x = percentX * 2.0f - 1.0f;
            auto y = percentY * 2.0f - 1.0f;

            // position(x, y, z)
            vertices[idx++] = x;
            vertices[idx++] = y;
            vertices[idx++] = 0.0f;

            idx += 3;
        }
    }
}

void Screen::clear(float r, float g, float b) {
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

void Screen::setPixel(int x, int y, float r, float g, float b) {
    int idx = (y * Define::SCREEN_WIDTH + x) * COUNT_PER_GROUP + 3;
//    std::cout << idx << "(" << x << ", " << y << ")" << std::endl;
    assert(x >= 0 && x < Define::SCREEN_WIDTH);
    assert(y >= 0 && y < Define::SCREEN_HEIGHT);

    auto& vertices = this->vertices_;
    vertices[idx++] = r;
    vertices[idx++] = g;
    vertices[idx++] = b;
}

void Screen::clear(const Color& color) {
    auto [r, g, b, _] = color;
    clear((float) r / 255.f, (float) g / 255.f, (float) b / 255.f);
}

void Screen::setPixel(const Point& pos, const Color& color) {
    auto [r, g, b, _] = color;
    auto [x, y] = pos;
    setPixel(x, y, (float) r / 255.f, (float) g / 255.f, (float) b / 255.f);
}
