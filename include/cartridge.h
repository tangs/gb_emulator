#pragma once

#include "types.h"

struct CartridgeHeader {
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

const c8* get_cartridge_lic_code_name(u8 lic_code) {
    switch(lic_code)
    {
        case 0x00 : return "None";
        case 0x01 : return "Nintendo R&D1";
        case 0x08 : return "Capcom";
        case 0x13 : return "Electronic Arts";
        case 0x18 : return "Hudson Soft";
        case 0x19 : return "b-ai";
        case 0x20 : return "kss";
        case 0x22 : return "pow";
        case 0x24 : return "PCM Complete";
        case 0x25 : return "san-x";
        case 0x28 : return "Kemco Japan";
        case 0x29 : return "seta";
        case 0x30 : return "Viacom";
        case 0x31 : return "Nintendo";
        case 0x32 : return "Bandai";
        case 0x33 : return "Ocean/Acclaim";
        case 0x34 : return "Konami";
        case 0x35 : return "Hector";
        case 0x37 : return "Taito";
        case 0x38 : return "Hudson";
        case 0x39 : return "Banpresto";
        case 0x41 : return "Ubi Soft";
        case 0x42 : return "Atlus";
        case 0x44 : return "Malibu";
        case 0x46 : return "angel";
        case 0x47 : return "Bullet-Proof";
        case 0x49 : return "irem";
        case 0x50 : return "Absolute";
        case 0x51 : return "Acclaim";
        case 0x52 : return "Activision";
        case 0x53 : return "American sammy";
        case 0x54 : return "Konami";
        case 0x55 : return "Hi tech entertainment";
        case 0x56 : return "LJN";
        case 0x57 : return "Matchbox";
        case 0x58 : return "Mattel";
        case 0x59 : return "Milton Bradley";
        case 0x60 : return "Titus";
        case 0x61 : return "Virgin";
        case 0x64 : return "LucasArts";
        case 0x67 : return "Ocean";
        case 0x69 : return "Electronic Arts";
        case 0x70 : return "Infogrames";
        case 0x71 : return "Interplay";
        case 0x72 : return "Broderbund";
        case 0x73 : return "sculptured";
        case 0x75 : return "sci";
        case 0x78 : return "THQ";
        case 0x79 : return "Accolade";
        case 0x80 : return "misawa";
        case 0x83 : return "lozc";
        case 0x86 : return "Tokuma Shoten Intermedia";
        case 0x87 : return "Tsukuda Original";
        case 0x91 : return "Chunsoft";
        case 0x92 : return "Video system";
        case 0x93 : return "Ocean/Acclaim";
        case 0x95 : return "Varie";
        case 0x96 : return "Yonezawa/s’pal";
        case 0x97 : return "Kaneko";
        case 0x99 : return "Pack in soft";
        case 0xA4 : return "Konami (Yu-Gi-Oh!)";
        default: break;
    }
    return "UNKNOWN";
}
