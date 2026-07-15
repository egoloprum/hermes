#include "lib/exception-protocol.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <any>
#include <format>
#include <vector>

ProtocolException::ProtocolException(
  std::string          protocolName,
  std::string          parserState,
  std::string          offendingInput,
  SourcePosition       position,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : ParseException(
    protocolName + "Engine", 
    position, 
    "", 
    formatMessage(
      protocolName, 
      parserState, 
      detailedMessage), 
    location
  ),
    m_protocolName(std::move(protocolName)),
    m_parserState(std::move(parserState)),
    m_offendingInput(std::move(offendingInput))
{}

ProtocolException::ProtocolException(
  std::string          protocolName,
  std::string          parserState,
  std::string          offendingInput,
  SourcePosition       position,
  std::exception_ptr   innerException,
  std::string          detailedMessage,
  std::source_location location) noexcept
  : ParseException(
    protocolName + "Engine", 
    position, 
    std::move(innerException), 
    "", 
    formatMessage(
      protocolName, 
      parserState, 
      detailedMessage), 
    location
  ),
    m_protocolName(std::move(protocolName)),
    m_parserState(std::move(parserState)),
    m_offendingInput(std::move(offendingInput))
{}


std::string_view ProtocolException::protocolName() const noexcept { return m_protocolName; }
std::string_view ProtocolException::parserState() const noexcept { return m_parserState; }
std::string_view ProtocolException::offendingInput() const noexcept { return m_offendingInput; }

std::string ProtocolException::formatMessage(
  std::string_view protocol,
  std::string_view state,
  std::string_view detailedMessage
) noexcept {
  try {
    if (detailedMessage.empty()) {
      return std::format(
        "Protocol violation detected in {} layer (Parser State: {}).",
        protocol, state
      );
    }
    return std::format(
      "Protocol violation in {} [State: {}]: {}",
      protocol, state, detailedMessage
    );
  } catch (...) {
    return "ProtocolException: Post-transport state processing validation failed.";
  }
}
