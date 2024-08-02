#pragma once

#include "types.h"

struct CartridgeHeader
{
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
