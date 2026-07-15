#pragma once

#include <cstdint>

enum class ConfigurationErrorType : uint32_t {
  Unknown                 = 0,
  FileNotFound            = 1,
  SyntaxError             = 2,
  MissingSection          = 3,
  UnsupportedProvider     = 4,
  ValueConversionFailed   = 5,
  SchemaValidationError   = 6
};
