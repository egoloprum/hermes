#pragma once

#include "lib/exception-config.hpp"
#include "../enums/errors.hpp"
#include "../utility/to_string.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <exception>
#include <any>
#include <format>

ConfigurationException::ConfigurationException(
  ConfigurationErrorType  type,
  std::string             providerName,
  std::string             configSource,
  std::string             keyPath,
  std::string             detailedMessage,
  std::source_location    location
) noexcept
  : FrameworkException(
    formatMessage(type, providerName, configSource, keyPath, detailedMessage), 
    location
  ),
  m_type(type),
  m_providerName(std::move(providerName)),
  m_configSource(std::move(configSource)),
  m_keyPath(std::move(keyPath))
{}

ConfigurationException::ConfigurationException(
  ConfigurationErrorType  type,
  std::string             providerName,
  std::string             configSource,
  std::string             keyPath,
  std::exception_ptr      innerException,
  std::string             detailedMessage,
  std::source_location    location
) noexcept
  : FrameworkException(
    formatMessage(type, providerName, configSource, keyPath, detailedMessage),
    std::move(innerException),
    location
  ),
  m_type(type),
  m_providerName(std::move(providerName)),
  m_configSource(std::move(configSource)),
  m_keyPath(std::move(keyPath))
{}

ConfigurationErrorType  ConfigurationException::errorType() const noexcept { return m_type; }
std::string_view        ConfigurationException::errorTypeName() const noexcept { return to_string(m_type); }
std::string_view        ConfigurationException::providerName() const noexcept { return m_providerName; }
std::string_view        ConfigurationException::configSource() const noexcept { return m_configSource; }
std::string_view        ConfigurationException::keyPath() const noexcept { return m_keyPath; }

std::string ConfigurationException::formatMessage(
  ConfigurationErrorType type,
  std::string_view provider,
  std::string_view source,
  std::string_view keyPath,
  std::string_view detailedMessage
) noexcept {
  try {
    if (!keyPath.empty()) {
      return std::format(
        "Configuration Error [{}] inside provider '{}' ({}) at key path '{}'.",
        to_string(type), provider, source, keyPath
      );
    }

    if (!detailedMessage.empty()) {
      return std::format(
        "Configuration Error [{}] inside provider '{}' ({}). Details: {}.",
        to_string(type), provider, source, detailedMessage
      );
    } 

    return std::format(
      "Configuration Error [{}] inside provider '{}' ({}).", 
      to_string(type), provider, source
    );
  } catch (...) {
    return "ConfigurationException: Failed to parse configuration state.";
  }
}
