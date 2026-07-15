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
    SubsystemType subsystemType,
    std::string message,
    std::source_location location = std::source_location::current()) noexcept;

  RuntimeException(
    SubsystemType subsystemType,
    std::string message,
    std::exception_ptr innerException,
    std::source_location location = std::source_location::current()) noexcept;

  ~RuntimeException() noexcept override = default;

  RuntimeException(const RuntimeException& other)             noexcept = default;
  RuntimeException& operator=(const RuntimeException& other)  noexcept = default;
  RuntimeException(RuntimeException&& other)                  noexcept = default;
  RuntimeException& operator=(RuntimeException&& other)       noexcept = default;

  [[nodiscard]] SubsystemType       subsystemType() const noexcept;
  [[nodiscard]] std::string_view    subsystemName() const noexcept;

private:
  SubsystemType       m_subsystemType{SubsystemType::Unknown};
  static std::string  formatMessage(SubsystemType subsystemType, const std::string& message) noexcept;
};
