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
    std::string path;        
    std::string fieldName;   
    std::string detailedMessage = "";
  };

  using ValidationErrors = std::vector<ValidationError>;

  explicit ValidationException(
    ValidationErrors      errors, 
    std::source_location  location = std::source_location::current()
  ) noexcept;

  ValidationException(
    ValidationError       error,
    std::source_location  location = std::source_location::current()
  ) noexcept;

  ~ValidationException() noexcept override = default;

  ValidationException(const ValidationException& other)             noexcept = default;
  ValidationException& operator=(const ValidationException& other)  noexcept = default;
  ValidationException(ValidationException&& other)                  noexcept = default;
  ValidationException& operator=(ValidationException&& other)       noexcept = default;

  [[nodiscard]] const ValidationErrors& errors() const noexcept;
  [[nodiscard]] bool                    hasMultipleErrors() const noexcept;

private:
  ValidationErrors m_errors;

  static std::string formatMessage(const ValidationErrors& errors) noexcept;
};
