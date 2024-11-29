#pragma once

#include "types.h"

struct Emulator {
    u8* rom_data = nullptr;
    usize rom_data_size = 0;
};