#pragma once

#include "lib/exception-connection.hpp" 
#include "../utility/to_string.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <any>
#include <format>

ConnectionException::ConnectionException(
  std::string          connectionId,
  ConnectionState      previousState,
  ConnectionState      currentState,
  std::string          remoteEndpoint,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : NetworkException(
      formatMessage(connectionId, previousState, currentState, remoteEndpoint, detailedMessage), 
      SubsystemType::Network,
      location
    ),
    m_connectionId(std::move(connectionId)),
    m_previousState(previousState),
    m_currentState(currentState),
    m_remoteEndpoint(std::move(remoteEndpoint))
{}

std::string_view  ConnectionException::connectionId() const noexcept { return m_connectionId; }
ConnectionState   ConnectionException::previousState() const noexcept { return m_previousState; }
std::string_view  ConnectionException::previousStateName() const noexcept { return to_string(m_previousState); }
ConnectionState   ConnectionException::currentState() const noexcept { return m_currentState; }
std::string_view  ConnectionException::currentStateName() const noexcept { return to_string(m_currentState); }
std::string_view  ConnectionException::remoteEndpoint() const noexcept { return m_remoteEndpoint; }

std::string ConnectionException::formatMessage(
  std::string_view connectionId,
  ConnectionState  prev,
  ConnectionState  curr,
  std::string_view endpoint,
  std::string_view detailedMessage
) noexcept {
  try {
    if (detailedMessage.empty()) {
      return std::format(
        "ConnectionException [ID: {}] at endpoint '{}': Invalid lifecycle shift from '{}' to '{}'.",
        connectionId, endpoint, to_string(prev), to_string(curr)
      );
    }
    return std::format(
      "ConnectionException [ID: {}] at endpoint '{}' (State: {} -> {}): {}.",
      connectionId, endpoint, to_string(prev), to_string(curr), detailedMessage
    );
  } catch (...) {
    return "ConnectionException: Operation failed during server connection lifecycle phase.";
  }
}
