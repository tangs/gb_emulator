#include "cpu.h"

#include <iostream>
#include <cassert>

#include "emulator.h"
#include "instructions.h"

void CPU::init() {
    af(0x01B0);
    bc(0x0013);
    de(0x00D8);
    hl(0x014D);
    sp = 0xFFFE;
    pc = 0x0100;
    halted = false;
}

void CPU::step(Emulator* emu) {
    if(!halted)
    {
        // fetch opcode.
        u8 opcode = emu->bus_read(pc);
        // increase counter.
        ++pc;
        // execute opcode.
        auto* instruction = instructions_map[opcode];
        if (instruction == nullptr) {
            char msg[256];
            snprintf(msg, sizeof msg, "Instruction 0x%02X not present.", (u32)opcode);
            std::cerr << msg << std::endl;
            assert(false);
        }
        // TODO...
    }
    else
    {
        emu->tick(1);
    }
}