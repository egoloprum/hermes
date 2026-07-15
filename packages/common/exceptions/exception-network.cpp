#include "lib/exception-network.hpp" 
#include "../enums/subsystem.hpp"
#include "../utility/to_string.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <any>
#include <format>

NetworkException::NetworkException(
  int                  osErrno,
  std::string          operationName,
  SubsystemType        subsystemType,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : NetworkException(
      std::error_code(osErrno, std::generic_category()), 
      std::move(operationName), 
      subsystemType, 
      std::move(detailedMessage), 
      location
    ) 
{}

NetworkException::NetworkException(
  std::error_code      errorCode,
  std::string          operationName,
  SubsystemType        subsystemType,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : FrameworkException(formatMessage(errorCode, operationName, detailedMessage), location),
    m_errorCode(errorCode),
    m_operationName(std::move(operationName)),
    m_subsystemType(subsystemType)
{}

NetworkException::NetworkException(
  std::string          detailedMessage,
  SubsystemType        subsystemType,
  std::source_location location) noexcept
  : FrameworkException(std::move(detailedMessage), location),
    m_errorCode(make_error_code(std::errc::bad_message)), 
    m_operationName("LifecycleShift"),
    m_subsystemType(subsystemType)
{}

int NetworkException::nativeErrorCode() const noexcept { return m_errorCode.value(); }

std::string_view NetworkException::nativeErrorMessage() const noexcept {
  // Note: error_code::message returns std::string, but structural string layout 
  // properties are already captured inside the formatted string payload.
  // For direct raw access without heap overhead, downstreams inspect what().
  return "See network.errno_msg metadata or asErrorCode().message()";
}

std::error_code  NetworkException::asErrorCode() const noexcept { return m_errorCode; }
std::string_view NetworkException::operationName() const noexcept { return m_operationName; }
SubsystemType    NetworkException::subsystemType() const noexcept { return m_subsystemType; }
std::string_view NetworkException::subsystemName() const noexcept { return to_string(m_subsystemType); }

std::string NetworkException::formatMessage(
  const std::error_code& ec,
  std::string_view       operation,
  std::string_view       details
) noexcept {
  try {
    if (!details.empty()) {
      return std::format(
        "NetworkException during '{}' failure: {} (Category: {}, Code: {}). Details: {}",
        operation, ec.message(), ec.category().name(), ec.value(), details
      );
    } 

    return std::format(
      "NetworkException during '{}' failure: {} (Category: {}, Code: {}).",
      operation, ec.message(), ec.category().name(), ec.value()
    );
  } catch (...) {
    return "NetworkException: Low-level transport operation failed.";
  }
}
