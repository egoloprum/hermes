#pragma once

#include <cstdint>

enum class TimeoutType : uint32_t {
  Unknown            = 0,
  
  // Core Network & I/O
  Connection         = 1,
  Read               = 2,
  Write              = 3,
  
  // Lifecycle & Process Management
  DnsResolution      = 4,
  ServiceStartup     = 5,
  ExecutionDeadline  = 6,
  
  // Advanced & Infrastructure Layers
  TlsHandshake       = 7,
  KeepAlive          = 8,
  ConnectionPool     = 9,
  Gateway            = 10,
  DistributedLock    = 11
};

