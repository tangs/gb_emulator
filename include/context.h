#pragma once

#include "screen.h"

class Context {
public:
  static Context gContext;
public:
  Screen screen;
  Emulator emulator;
};

Context Context::gContext = {};
