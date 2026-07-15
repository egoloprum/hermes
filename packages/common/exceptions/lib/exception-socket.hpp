#pragma once

#include "exception-network.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <system_error>
#include <any>
#include <format>

class SocketException : public NetworkException {
public:
    
  explicit SocketException(
    int                  osErrno,
    std::string          operationName,
    int                  socketDescriptor,
    std::string          address = "0.0.0.0",
    uint16_t             port = 0,
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  explicit SocketException(
    std::error_code      errorCode,
    std::string          operationName,
    int                  socketDescriptor,
    std::string          address = "0.0.0.0",
    uint16_t             port = 0,
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  explicit SocketException(
    std::error_code      errorCode,
    std::string          operationName,
    int                  socketDescriptor,
    std::string          address,
    uint16_t             port,
    std::exception_ptr   innerException,
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  ~SocketException() noexcept override = default;

  SocketException(const SocketException& other)             noexcept = default;
  SocketException& operator=(const SocketException& other)  noexcept = default;
  SocketException(SocketException&& other)                  noexcept = default;
  SocketException& operator=(SocketException&& other)       noexcept = default;

  [[nodiscard]] int              socketDescriptor() const noexcept;
  [[nodiscard]] std::string_view address() const noexcept;
  [[nodiscard]] uint16_t         port() const noexcept;

protected:
  static std::string formatMessage(
    std::string_view       derivedExceptionName,
    const std::error_code& errorCode,
    std::string_view       operation,
    int                    socketDescriptor,
    std::string_view       address,
    uint16_t               port,
    std::string_view       detailedMessage) noexcept;

private:
  int         m_socketDescriptor{-1};
  std::string m_address;
  uint16_t    m_port{0};
};

class SocketCreationException : public SocketException {
public:
  explicit SocketCreationException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketCreationException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketCreationException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketBindException : public SocketException {
public:
  explicit SocketBindException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketBindException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketBindException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketListenException : public SocketException {
public:
  explicit SocketListenException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketListenException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketListenException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketAcceptException : public SocketException {
public:
  explicit SocketAcceptException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketAcceptException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketAcceptException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketReceiveException : public SocketException {
public:
  explicit SocketReceiveException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketReceiveException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketReceiveException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketSendException : public SocketException {
public:
  explicit SocketSendException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketSendException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketSendException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketShutdownException : public SocketException {
public:
  explicit SocketShutdownException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketShutdownException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketShutdownException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

class SocketCloseException : public SocketException {
public:
  explicit SocketCloseException(
    int                   osErrno, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketCloseException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address = "0.0.0.0", 
    uint16_t              port = 0, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;

  explicit SocketCloseException(
    std::error_code       errorCode, 
    std::string           operationName,
    int                   socketDescriptor,
    std::string           address, 
    uint16_t              port, 
    std::exception_ptr    innerException, 
    std::string           detailedMessage = "", 
    std::source_location  location = std::source_location::current()) noexcept;
};

