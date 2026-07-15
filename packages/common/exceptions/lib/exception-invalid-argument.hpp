#pragma once

#include "exception-base.hpp"
#include <string>
#include <string_view>
#include <source_location>

class InvalidArgumentException : public FrameworkException {
public:
  explicit InvalidArgumentException(
    std::string paramName,
    std::string expectedDescription,
    std::string actualDescription,
    std::string detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  ~InvalidArgumentException() noexcept override = default;

  InvalidArgumentException(const InvalidArgumentException& other)             noexcept = default;
  InvalidArgumentException& operator=(const InvalidArgumentException& other)  noexcept = default;
  InvalidArgumentException(InvalidArgumentException&& other)                  noexcept = default;
  InvalidArgumentException& operator=(InvalidArgumentException&& other)       noexcept = default;

  [[nodiscard]] std::string_view parameterName() const noexcept;
  [[nodiscard]] std::string_view expectedDescription() const noexcept;
  [[nodiscard]] std::string_view actualDescription() const noexcept;

private:
  std::string m_paramName;
  std::string m_expected;
  std::string m_actual;

  static std::string formatMessage(
    const std::string& paramName,
    const std::string& expected,
    const std::string& actual,
    const std::string& detailedMessage) noexcept;
};
