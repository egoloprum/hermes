#pragma once

#include "exception-network.hpp"
#include "../../enums/connection.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <any>
#include <format>

class ConnectionException : public NetworkException {
public:
  explicit ConnectionException(
    std::string          connectionId,
    ConnectionState      previousState,
    ConnectionState      currentState,
    std::string          remoteEndpoint,
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  ~ConnectionException() noexcept override = default;

  ConnectionException(const ConnectionException& other)             noexcept = default;
  ConnectionException& operator=(const ConnectionException& other)  noexcept = default;
  ConnectionException(ConnectionException&& other)                  noexcept = default;
  ConnectionException& operator=(ConnectionException&& other)       noexcept = default;

  [[nodiscard]] std::string_view  connectionId() const noexcept;
  [[nodiscard]] ConnectionState   previousState() const noexcept;
  [[nodiscard]] std::string_view  previousStateName() const noexcept;
  [[nodiscard]] ConnectionState   currentState() const noexcept;
  [[nodiscard]] std::string_view  currentStateName() const noexcept;
  [[nodiscard]] std::string_view  remoteEndpoint() const noexcept;

private:
  std::string       m_connectionId;
  ConnectionState   m_previousState{ConnectionState::Disconnected};
  ConnectionState   m_currentState{ConnectionState::Disconnected};
  std::string       m_remoteEndpoint;

  static std::string formatMessage(
    std::string_view connectionId,
    ConnectionState  prev,
    ConnectionState  curr,
    std::string_view endpoint,
    std::string_view detailedMessage) noexcept;
};
