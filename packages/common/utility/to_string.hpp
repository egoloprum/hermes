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

inline std::string prefixSubsystem(Subsystem subsystem, const std::string& message) noexcept {
  try { return "[" + std::string(to_string(subsystem)) + "] " + message; } 
  catch (...) { return message; } // Fallback under memory exhaustion 
}

inline std::string formatInvalidArgument(
        std::string_view paramName, 
        std::string_view expected, 
        std::string_view actual, 
        std::string_view message) noexcept 
    {
        try {
            if (message.empty()) {
                return std::format(
                    "Invalid argument '{}': Expected {}, but got {}.", 
                    paramName, expected, actual
                );
            }
            return std::format(
                "Invalid argument '{}': Expected {}, but got {}. Details: {}", 
                paramName, expected, actual, message
            );
        } catch (...) {
            // Fallback strategy under memory or formatting failures
            return "Invalid argument error (formatting failed)";
        }
    }
