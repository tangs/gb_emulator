#include "types.h"

class CPU {
public:
    u8 a;
    u8 f;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;
    u8 l;

    u16 pc;
    u16 sp;
public:
    u16 af() const { return (((u16)a) << 8) | (u16)f; }
    u16 bc() const { return (((u16)b) << 8) | (u16)c; }
    u16 de() const { return (((u16)d) << 8) | (u16)e; }
    u16 hl() const { return (((u16)h) << 8) | (u16)l; }
};