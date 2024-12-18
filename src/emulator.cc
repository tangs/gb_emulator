#include "emulator.h"

#include <iostream>
#include <cassert>

Emulator::~Emulator() {
    close();
}

u8 Emulator::checkSum() const {
    auto rom_data_ = rom_data;
    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; ++address) {
        checksum = checksum - rom_data_[address] - 1;
    }
    return checksum;
}

int Emulator::init() {
    cpu.init();
    return 0;
}

void Emulator::update(f64 delta_time) {
    auto frame_cycles = (u64)((f32)(4194304.0 * delta_time) * clock_speed_scale);
    auto end_cycles = clock_cycles + frame_cycles;
    while(clock_cycles < end_cycles) {
        if (paused) break;
        cpu.step(this);
    }
}

void Emulator::tick(u32 mcycles) {
    // TODO
}

void Emulator::close() {
    // TODO
}


u8 Emulator::bus_read(u16 addr) {

    if (addr < 0x7fff) {
        // cartridge ROM.
        return rom_data[addr];
    }

    if (addr <= 0x9fff) {
        // v ram.
        return vram[addr - 0x8000];
    }

    if (addr <= 0xbfff) {
        // Cartridge RAM.
        // TODO
        return 0xff;
    }

    if (addr <= 0xdfff) {
        // Working RAM.
        return wram[addr - 0xc000];
    }

    if(addr >= 0xFF80 && addr <= 0xFFFE)
    {
        // High RAM.
        return hram[addr - 0xFF80];
    }

    std::cerr << "unsupported bus read address:" << std::hex << std::showbase << addr << std::endl;
    assert(false);
    return 0xFF;
}

void Emulator::bus_write(u16 addr, u8 data) {
    if (addr < 0x7fff) {
        // cartridge ROM.
//        rom_data[addr] = data;
        std::cerr << "Unsupported cartridge write address" << std::hex << std::showbase << addr << std::endl;
        assert(false);
    }

    if (addr < 0x9FFF) {
        // v ram.
        vram[addr - 0x8000] = data;
        return;
    }

    if (addr <= 0xbfff) {
        // Cartridge RAM.
        // TODO
        return;
    }

    if (addr <= 0xDFFF) {
        // Working RAM.
        wram[addr - 0xc000] = data;
        return;
    }

    if (addr >= 0xFF80 && addr <= 0xFFFE) {
        // High RAM.
        hram[addr - 0xFF80] = data;
        return;
    }

    std::cerr << "unsupported bus write address:" << std::hex << std::showbase << addr << std::endl;
    assert(false);
}
