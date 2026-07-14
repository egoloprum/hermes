#pragma once;

#include "exception.hpp"
#include "../enums/subsystem.hpp"
#include "../utility/to_string.hpp"

#include <string_view>
#include <string>
#include <any>

class RuntimeException : public FrameworkException {
public:
  explicit inline RuntimeException(
    Subsystem subsystem,
    std::string message,
    std::source_location location = std::source_location::current()) noexcept
    : FrameworkException(prefixSubsystem(subsystem, message), location),
      m_subsystem(subsystem) 
  {
    addMetadata("framework.subsystem_id", static_cast<uint32_t>(subsystem));
    addMetadata("framework.subsystem_name", std::string(to_string(subsystem)));
  }

  // Subsystem constructor supporting nested inner exceptions (e.g., third-party failures)
  inline RuntimeException(
    Subsystem subsystem,
    std::string message,
    std::exception_ptr innerException,
    std::source_location location = std::source_location::current()) noexcept
    : FrameworkException(prefixSubsystem(subsystem, message), std::move(innerException), location),
      m_subsystem(subsystem) 
  {
    addMetadata("framework.subsystem_id", static_cast<uint32_t>(subsystem));
    addMetadata("framework.subsystem_name", std::string(to_string(subsystem)));
  }

  ~RuntimeException() noexcept override = default;

  RuntimeException(const RuntimeException& other)             noexcept = default;
  RuntimeException& operator=(const RuntimeException& other)  noexcept = default;
  RuntimeException(RuntimeException&& other)                  noexcept = default;
  RuntimeException& operator=(RuntimeException&& other)       noexcept = default;

  [[nodiscard]] inline Subsystem subsystem() const noexcept { return m_subsystem; }
  [[nodiscard]] inline std::string_view subsystemName() const noexcept { return to_string(m_subsystem); }

private:
  Subsystem m_subsystem{Subsystem::Unknown};
};
