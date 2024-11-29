#pragma once

#include "types.h"

struct Color {
public:
//  Color (u8 r, u8 g, u8 b, u8 a = 0xff)
//          : r(r)
//          , g(g)
//          , b(b)
//          , a(a)
//  {}
    static Color CreateWithRGB(u8 r_, u8 g_, u8 b_) {
        return Color {
          .r =  r_,
          .g = g_,
          .b = b_,
          .a = 0xff
        };
    }
    Color reverse() {
        return Color {
            .r = u8(0xff - r),
            .g = u8(0xff - g),
            .b = u8(0xff - b),
            .a = a
        };
    }
public:
  u8 r = 0;
  u8 g = 0;
  u8 b = 0;
  u8 a = 255;
};