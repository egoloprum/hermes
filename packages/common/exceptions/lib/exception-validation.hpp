#pragma once

#include "exception-base.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <vector>
#include <any>
#include <memory>

class ValidationException : public FrameworkException {
public:
  struct ValidationError {
    std::string path;        // Dot-notation or JSON-pointer style path
    std::string fieldName;   // Raw name of the validating target
    std::string message;     // Validation failure text
  };

  using ValidationErrors = std::vector<ValidationError>;

  explicit ValidationException(
    ValidationErrors errors, 
    std::source_location location = std::source_location::current()
  ) noexcept;

  ValidationException(
    ValidationError error,
    std::source_location location = std::source_location::current()
  ) noexcept;

  ~ValidationException() noexcept override = default;

  ValidationException(const ValidationException& other)             noexcept = default;
  ValidationException& operator=(const ValidationException& other)  noexcept = default;
  ValidationException(ValidationException&& other)                  noexcept = default;
  ValidationException& operator=(ValidationException&& other)       noexcept = default;

  // Provides inspection capabilities for downstream formatters, JSON converters, or DTO boundary maps
  [[nodiscard]] const ValidationErrors& errors() const noexcept;

  // Indicates if multiple fields failed simultaneously during a pipeline phase
  [[nodiscard]] bool hasMultipleErrors() const noexcept;

private:
  static std::string formatSummary(const ValidationErrors& errors) noexcept;
  ValidationErrors m_errors;
};
