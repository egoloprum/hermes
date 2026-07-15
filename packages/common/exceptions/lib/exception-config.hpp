#pragma once

#include "exception-base.hpp"
#include "../../enums/errors.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <exception>
#include <any>
#include <format>

class ConfigurationException : public FrameworkException {
public:
  explicit ConfigurationException(
    ConfigurationErrorType  type,
    std::string             providerName,
    std::string             configSource,
    std::string             keyPath,
    std::string             detailedMessage = "",
    std::source_location    location = std::source_location::current()) noexcept;

  ConfigurationException(
    ConfigurationErrorType  type,
    std::string             providerName,
    std::string             configSource,
    std::string             keyPath,
    std::exception_ptr      innerException,
    std::string             detailedMessage = "",
    std::source_location    location = std::source_location::current()) noexcept;

  ~ConfigurationException() noexcept override = default;

  ConfigurationException(const ConfigurationException& other)             noexcept = default;
  ConfigurationException& operator=(const ConfigurationException& other)  noexcept = default;
  ConfigurationException(ConfigurationException&& other)                  noexcept = default;
  ConfigurationException& operator=(ConfigurationException&& other)       noexcept = default;

  [[nodiscard]] ConfigurationErrorType   errorType() const noexcept; 
  [[nodiscard]] std::string_view         errorTypeName() const noexcept; 
  [[nodiscard]] std::string_view         providerName() const noexcept;
  [[nodiscard]] std::string_view         configSource() const noexcept; 
  [[nodiscard]] std::string_view         keyPath() const noexcept;

private:
  ConfigurationErrorType  m_type{ConfigurationErrorType::Unknown};
  std::string             m_providerName;
  std::string             m_configSource;
  std::string             m_keyPath;

  static std::string formatMessage(
    ConfigurationErrorType  type,
    std::string_view        provider,
    std::string_view        source,
    std::string_view        keyPath,
    std::string_view        detailedMessage) noexcept;
};

