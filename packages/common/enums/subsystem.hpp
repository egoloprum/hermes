#pragma once

#include <cstdint>

enum class Subsystem : uint32_t {
  Unknown = 0,
  Core,
  Lifecycle,
  ServiceMesh,
  ModuleLoader,
  Configuration,
  DataStorage,
  Security
};
