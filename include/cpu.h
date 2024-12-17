#pragma once

#include "types.h"

class Emulator;

class CPU {
public:
    u8 a = 0;
    u8 f = 0;
    u8 b = 0;
    u8 c = 0;
    u8 d = 0;
    u8 e = 0;
    u8 h = 0;
    u8 l = 0;

    u16 pc = 0;
    u16 sp = 0;

    bool halted = false;
public:
    u16 af() const { return (((u16)a) << 8) | (u16)f; }
    u16 bc() const { return (((u16)b) << 8) | (u16)c; }
    u16 de() const { return (((u16)d) << 8) | (u16)e; }
    u16 hl() const { return (((u16)h) << 8) | (u16)l; }

    void af(u16 v) { a = v >> 8; f = v & 0xf0; } // The lower 4 bits of F should always be 0.
    void bc(u16 v) { b = v >> 8; c = v & 0xff; }
    void de(u16 v) { d = v >> 8; e = v & 0xff; }
    void hl(u16 v) { h = v >> 8; l = v & 0xff; }

    bool fz() const { return (f & 0x80) != 0; }
    bool fn() const { return (f & 0x40) != 0; }
    bool fh() const { return (f & 0x20) != 0; }
    bool fc() const { return (f & 0x10) != 0; }

    void set_fz() { f |= 0x80; }
    void set_fn() { f |= 0x40; }
    void set_fh() { f |= 0x20; }
    void set_fc() { f |= 0x10; }

    void reset_fz() { f &= 0x7f; }
    void reset_fn() { f &= 0xbf; }
    void reset_fh() { f &= 0xdf; }
    void reset_fc() { f &= 0xef; }

    void init();
    void step(Emulator* emu);
};