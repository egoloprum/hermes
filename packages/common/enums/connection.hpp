#pragma once

#include <cstdint>

enum class ConnectionState : uint32_t {
  Disconnected    = 0,
  Connecting      = 1,
  Connected       = 2,
  Disconnecting   = 3,
  Faulted         = 4
};
