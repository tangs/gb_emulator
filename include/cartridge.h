#pragma once

#include "types.h"
#include <array>

struct CartridgeHeader {
public:
    constexpr static i32 LOGO_WIDTH = 12 * 4;
    constexpr static i32 LOGO_HEIGHT = 2 * 4;
    using LOGO_BITS = std::array<std::array<bool, LOGO_WIDTH>, LOGO_HEIGHT>;
public:
    [[nodiscard]] const c8* get_cartridge_lic_code_name() const;
    [[nodiscard]] LOGO_BITS get_logo_bitmap() const;
public:
    u8 entry[4];
    u8 logo[0x30];
    c8 title[16];
    u8 new_lic_code[2];
    u8 sgb_flag;
    u8 cartridge_type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 lic_code;
    u8 version;
    u8 checksum;
    u8 global_checksum[2];
};


