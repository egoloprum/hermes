#pragma once

#include "exception-base.hpp"
#include "../../enums/subsystem.hpp"
#include <string_view>
#include <string>
#include <source_location>
#include <exception>

class RuntimeException : public FrameworkException {
public:
  explicit RuntimeException(
    Subsystem subsystem,
    std::string message,
    std::source_location location = std::source_location::current()) noexcept;

  RuntimeException(
    Subsystem subsystem,
    std::string message,
    std::exception_ptr innerException,
    std::source_location location = std::source_location::current()) noexcept;

  ~RuntimeException() noexcept override = default;

  RuntimeException(const RuntimeException& other)             noexcept = default;
  RuntimeException& operator=(const RuntimeException& other)  noexcept = default;
  RuntimeException(RuntimeException&& other)                  noexcept = default;
  RuntimeException& operator=(RuntimeException&& other)       noexcept = default;

  [[nodiscard]] Subsystem         subsystem() const noexcept;
  [[nodiscard]] std::string_view  subsystemName() const noexcept;

private:
  Subsystem m_subsystem{Subsystem::Unknown};
  
  static std::string prefixSubsystem(Subsystem subsystem, const std::string& message) noexcept;
};
