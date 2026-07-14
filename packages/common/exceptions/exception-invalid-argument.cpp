#include "lib/exception-invalid-argument.hpp"
#include <format>
#include <utility>

InvalidArgumentException::InvalidArgumentException(
  std::string paramName,
  std::string expectedDescription,
  std::string actualDescription,
  std::string detailedMessage,
  std::source_location location) noexcept
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

std::string_view InvalidArgumentException::parameterName() const noexcept {
  return m_paramName;
}

std::string_view InvalidArgumentException::expectedDescription() const noexcept {
  return m_expected;
}

std::string_view InvalidArgumentException::actualDescription() const noexcept {
  return m_actual;
}

std::string InvalidArgumentException::formatInvalidArgument(
  const std::string& paramName,
  const std::string& expected,
  const std::string& actual,
  const std::string& detailedMessage) noexcept 
{
  try {
    if (detailedMessage.empty()) {
      return std::format(
        "Invalid argument '{}': Expected [{}], but got [{}].", 
        paramName, expected, actual
      );
    }
    return std::format(
      "Invalid argument '{}': Expected [{}], but got [{}]. Detail: {}", 
      paramName, expected, actual, detailedMessage
    );
  } catch (...) {
    return "Invalid argument error matching parameter: " + paramName;
  }
}
