#pragma once

#include "exception.hpp"
#include "../utility/to_string.hpp"

#include <string>
#include <string_view>
#include <source_location>
#include <any>
#include <format>

class InvalidArgumentException : public FrameworkException {
public:
  explicit inline InvalidArgumentException(
    std::string paramName,
    std::string expectedDescription,
    std::string actualDescription,
    std::string detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept
    : FrameworkException(
        formatInvalidArgument(paramName, expectedDescription, actualDescription, detailedMessage), 
        location
      ),
    m_paramName(std::move(paramName)),
    m_expected(std::move(expectedDescription)),
    m_actual(std::move(actualDescription))
  {
    addMetadata("validation.parameter_name", m_paramName);
    addMetadata("validation.expected_state", m_expected);
    addMetadata("validation.actual_state", m_actual);
  }

  ~InvalidArgumentException() noexcept override = default;

  InvalidArgumentException(const InvalidArgumentException& other) noexcept = default;
  InvalidArgumentException& operator=(const InvalidArgumentException& other) noexcept = default;
  InvalidArgumentException(InvalidArgumentException&& other) noexcept = default;
  InvalidArgumentException& operator=(InvalidArgumentException&& other) noexcept = default;

  
  [[nodiscard]] inline std::string_view parameterName() const noexcept {
    return m_paramName;
  }

  [[nodiscard]] inline std::string_view expectedDescription() const noexcept {
    return m_expected;
  }

  [[nodiscard]] inline std::string_view actualDescription() const noexcept {
    return m_actual;
  }

private:
  std::string m_paramName;
  std::string m_expected;
  std::string m_actual;
};
