#include "lib/exception-socket.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <system_error>
#include <any>
#include <format>

SocketException::SocketException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
    std::error_code(osErrno, std::generic_category()),
    std::move(operationName),
    socketDescriptor,
    std::move(address),
    port,
    std::move(detailedMessage),
    location) 
{}

SocketException::SocketException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : NetworkException(
      errorCode,
      std::move(operationName),
      SubsystemType::Network,
      formatMessage(
        "SocketException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ),
    m_socketDescriptor(socketDescriptor),
    m_address(std::move(address)),
    m_port(port) 
{}

SocketException::SocketException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   innerException,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : NetworkException(
      errorCode,
      std::move(operationName),
      SubsystemType::Network,
      formatMessage(
        "SocketException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      std::move(innerException),
      location
    ),
    m_socketDescriptor(socketDescriptor),
    m_address(std::move(address)),
    m_port(port) 
{}

int               SocketException::socketDescriptor() const noexcept { return m_socketDescriptor; }
std::string_view  SocketException::address() const noexcept { return m_address; }
uint16_t          SocketException::port() const noexcept { return m_port; }

std::string SocketException::formatMessage(
  std::string_view       derivedExceptionName,
  const std::error_code& errorCode,
  std::string_view       operation,
  int                    SocketDescriptor,
  std::string_view       address,
  uint16_t               port,
  std::string_view       detailedMessage
) noexcept {
  try {
    if (!detailedMessage.empty()) {
      return std::format(
        "{} [SocketDescriptor: {}] failed during '{}' on {}:{}. System Error: {} (Code: {}) | Context: {}",
        derivedExceptionName, SocketDescriptor, operation, address, port, errorCode.message(), errorCode.value(), detailedMessage
      );
    }
    return std::format(
      "{} [SocketDescriptor: {}] failed during '{}' on {}:{}. System Error: {} (Code: {})",
      derivedExceptionName, SocketDescriptor, operation, address, port, errorCode.message(), errorCode.value()
    );
  } catch (...) {
    return "SocketException: Underling operating system socket interaction boundary failed.";
  }
}

SocketCreationException::SocketCreationException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketCreationException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketCreationException::SocketCreationException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketCreationException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketCreationException::SocketCreationException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketCreationException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketBindException::SocketBindException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketBindException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketBindException::SocketBindException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketBindException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketBindException::SocketBindException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketBindException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketListenException::SocketListenException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketListenException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketListenException::SocketListenException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketListenException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketListenException::SocketListenException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketListenException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketAcceptException::SocketAcceptException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketAcceptException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketAcceptException::SocketAcceptException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketAcceptException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketAcceptException::SocketAcceptException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketAcceptException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketReceiveException::SocketReceiveException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketReceiveException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketReceiveException::SocketReceiveException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketReceiveException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketReceiveException::SocketReceiveException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketReceiveException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketSendException::SocketSendException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketSendException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketSendException::SocketSendException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketSendException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketSendException::SocketSendException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketSendException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketShutdownException::SocketShutdownException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketShutdownException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketShutdownException::SocketShutdownException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketShutdownException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketShutdownException::SocketShutdownException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketShutdownException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketCloseException::SocketCloseException(
  int                  osErrno,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      osErrno,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketCloseException",
        std::error_code(osErrno, std::generic_category()),
        operationName,
        socketDescriptor,
        address,
        port,
        detailedMessage
      ),
      location
    ) 
{}

SocketCloseException::SocketCloseException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      formatMessage(
        "SocketCloseException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}

SocketCloseException::SocketCloseException(
  std::error_code      errorCode,
  std::string          operationName,
  int                  socketDescriptor,
  std::string          address,
  uint16_t             port,
  std::exception_ptr   inner,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : SocketException(
      errorCode,
      std::move(operationName),
      socketDescriptor,
      std::move(address),
      port,
      std::move(inner),
      formatMessage(
        "SocketCloseException", 
        errorCode, 
        operationName, 
        socketDescriptor, 
        address, 
        port, 
        detailedMessage
      ),
      location
    ) 
{}
