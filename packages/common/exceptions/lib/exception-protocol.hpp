#pragma once

#include "exception-parse.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <any>
#include <format>
#include <vector>

class ProtocolException : public ParseException {
public:
  explicit ProtocolException(
    std::string          protocolName,
    std::string          parserState,
    std::string          offendingInput,
    SourcePosition       position,
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  explicit ProtocolException(
    std::string          protocolName,
    std::string          parserState,
    std::string          offendingInput,
    SourcePosition       position,
    std::exception_ptr   innerException,
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  ~ProtocolException() noexcept override = default;

  ProtocolException(const ProtocolException& other)             noexcept = default;
  ProtocolException& operator=(const ProtocolException& other)  noexcept = default;
  ProtocolException(ProtocolException&& other)                  noexcept = default;
  ProtocolException& operator=(ProtocolException&& other)       noexcept = default;

  [[nodiscard]] std::string_view protocolName() const noexcept;
  [[nodiscard]] std::string_view parserState() const noexcept;
  [[nodiscard]] std::string_view offendingInput() const noexcept;

private:
  std::string m_protocolName;
  std::string m_parserState;
  std::string m_offendingInput;

  static std::string formatMessage(
    std::string_view protocol,
    std::string_view state,
    std::string_view detailedMessage) noexcept;
};
