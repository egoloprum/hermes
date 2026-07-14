#pragma once

#include <string>
#include <string_view>
#include <format>
#include "../enums/subsystem.hpp"

[[nodiscard]] constexpr std::string_view to_string(Subsystem subsystem) noexcept {
  switch (subsystem) {
    case Subsystem::Core:          return "Core";
    case Subsystem::Lifecycle:     return "Lifecycle";
    case Subsystem::ServiceMesh:   return "ServiceMesh";
    case Subsystem::ModuleLoader:  return "ModuleLoader";
    case Subsystem::Configuration: return "Configuration";
    case Subsystem::DataStorage:   return "DataStorage";
    case Subsystem::Security:      return "Security";
    default:                       return "UnknownSubsystem";
  }
}
