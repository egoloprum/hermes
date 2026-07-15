#pragma once

#include "exception-base.hpp"
#include "../../enums/subsystem.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <system_error>
#include <any>
#include <format>

class NetworkException : public FrameworkException {
public:
  explicit NetworkException(
    int                   osErrno,
    std::string           operationName,
    SubsystemType         subsystemType = SubsystemType::Network,
    std::string           detailedMessage = "",
    std::source_location  location = std::source_location::current()) noexcept;

  explicit NetworkException(
    std::error_code       errorCode,
    std::string           operationName,
    SubsystemType         subsystemType = SubsystemType::Network,
    std::string           detailedMessage = "",
    std::source_location  location = std::source_location::current()) noexcept;

  ~NetworkException() noexcept override = default;

  NetworkException(const NetworkException& other)             noexcept = default;
  NetworkException& operator=(const NetworkException& other)  noexcept = default;
  NetworkException(NetworkException&& other)                  noexcept = default;
  NetworkException& operator=(NetworkException&& other)       noexcept = default;

  [[nodiscard]] int               nativeErrorCode() const noexcept;
  [[nodiscard]] std::string_view  nativeErrorMessage() const noexcept;
  [[nodiscard]] std::error_code   asErrorCode() const noexcept;
  [[nodiscard]] std::string_view  operationName() const noexcept;
  [[nodiscard]] SubsystemType     subsystemType() const noexcept;
  [[nodiscard]] std::string_view  subsystemName() const noexcept;

protected:
  explicit NetworkException(
    std::string           detailedMessage,
    SubsystemType         subsystemType,
    std::source_location  location) noexcept;

private:
  std::error_code   m_errorCode;
  std::string       m_operationName;
  SubsystemType     m_subsystemType{SubsystemType::Unknown};

  static std::string formatMessage(
    const std::error_code&  ec,
    std::string_view        operation,
    std::string_view        detailedMessage) noexcept;
};
