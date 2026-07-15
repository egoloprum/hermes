#pragma once

#include <string>
#include <string_view>
#include <format>
#include "../enums/subsystem.hpp"
#include "../enums/timeout.hpp"

[[nodiscard]] constexpr std::string_view to_string(SubsystemType subsystemType) noexcept {
  switch (subsystemType) {
    case SubsystemType::Core:          return "Core";
    case SubsystemType::Lifecycle:     return "Lifecycle";
    case SubsystemType::ServiceMesh:   return "ServiceMesh";
    case SubsystemType::ModuleLoader:  return "ModuleLoader";
    case SubsystemType::Configuration: return "Configuration";
    case SubsystemType::DataStorage:   return "DataStorage";
    case SubsystemType::Security:      return "Security";
    case SubsystemType::Network:       return "Network";
    case SubsystemType::Unknown:
    default:                       return "Unknown";
  }
}

[[nodiscard]] constexpr std::string_view to_string(TimeoutType timeoutType) noexcept {
  switch (timeoutType) {
  case TimeoutType::Connection:        return "Connection";
  case TimeoutType::Read:              return "Read";
  case TimeoutType::Write:             return "Write";
  case TimeoutType::DnsResolution:     return "DnsResolution";
  case TimeoutType::ServiceStartup:    return "ServiceStartup";
  case TimeoutType::ExecutionDeadline: return "ExecutionDeadline";
  case TimeoutType::TlsHandshake:      return "TlsHandshake";
  case TimeoutType::KeepAlive:         return "KeepAlive";
  case TimeoutType::ConnectionPool:    return "ConnectionPool";
  case TimeoutType::Gateway:           return "Gateway";
  case TimeoutType::DistributedLock:    return "DistributedLock";
  case TimeoutType::Unknown:
  default:                             return "Unknown";
  }
}
