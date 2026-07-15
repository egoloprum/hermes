#include "lib/exception-validation.hpp"
#include <format>
#include <utility>

ValidationException::ValidationException(
  ValidationErrors errors, std::source_location location) noexcept
  : FrameworkException(formatSummary(errors), location), m_errors(std::move(errors)
) {}

ValidationException::ValidationException(
  ValidationError error, std::source_location location) noexcept
  : FrameworkException(formatSummary(ValidationErrors{error}), location), m_errors()
{
  try {
    m_errors.push_back(ValidationError{
      .path       = std::move(error.path),
      .fieldName  = std::move(error.fieldName),
      .message    = std::move(error.message)
    });
  } catch (...) {}
}

const ValidationException::ValidationErrors& ValidationException::errors() const noexcept { return m_errors; }
bool ValidationException::hasMultipleErrors() const noexcept { return m_errors.size() > 1; }

std::string ValidationException::formatSummary(const ValidationErrors& errors) noexcept {
  if (errors.empty()) {
    return "Validation failed with no specific sub-errors reported.";
  }
  try {
    if (errors.size() == 1) {
      return std::format(
        "Validation failed: Field '{}' at path '{}' - {}", 
        errors[0].fieldName, errors[0].path, errors[0].message
      );
    }
    return std::format(
      "Validation failed with {} structural errors. Root cause: '{}' - {}", 
      errors.size(), errors[0].path, errors[0].message
    );
  } catch (...) {
    return "Validation failed (diagnostic generation exhausted heap space).";
  }
}
