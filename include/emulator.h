#pragma once

#include "types.h"
#include "cpu.h"

struct Emulator {
public:
  ~Emulator();
public:
  [[nodiscard]] u8 checkSum() const;
public:
  int init();
  void update(f64 delta_time);
  void tick(u32 mcycles);
  void close();

  u8 bus_read(u16 addr);
  void bus_write(u16 addr, u8 data);
public:
    u8* rom_data = nullptr;
    usize rom_data_size = 0;

    bool paused = false;
    u64 clock_cycles = 0;
    f32 clock_speed_scale = 1.0;

    // v ram
    u8 vram[8 * 1024] = {};
    // working ram
    u8 wram[8 * 1024] = {};
    // high ram
    u8 hram[128] = {};

    CPU cpu;
};