#pragma once

#include "types.h"

struct Emulator {
  [[nodiscard]] u8 checkSum() const;
public:
    u8* rom_data = nullptr;
    usize rom_data_size = 0;
};