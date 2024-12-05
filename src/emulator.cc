#include "emulator.h"

u8 Emulator::check_sum() const {
    auto rom_data_ = rom_data;
    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; ++address) {
        checksum = checksum - rom_data_[address] - 1;
    }
    return checksum;
}