#pragma once

#include <cstdint>

enum class SubsystemType : uint32_t {
  Unknown       = 0,
  Core          = 1,
  Lifecycle     = 2,
  ServiceMesh   = 3,
  ModuleLoader  = 4,
  Configuration = 5,
  DataStorage   = 6,
  Security      = 7,
  Network       = 8,
};
