#include "lib/exception-parse.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <optional>
#include <format>

inline ParseException::ParseException(
  std::string           parserName,
  SourcePosition        position,
  std::string           offendingToken,
  std::string           detailedMessage,
  std::source_location  location) noexcept
  : FrameworkException(
    formatMessage(
      parserName, 
      position, 
      offendingToken, 
      detailedMessage
    ), location),
    m_parserName(std::move(parserName)),
    m_position(position),
    m_offendingToken(std::move(offendingToken))
{}

inline ParseException::ParseException(
    std::string          parserName,
    SourcePosition       position,
    std::exception_ptr   innerException,
    std::string          offendingToken,
    std::string          detailedMessage,
    std::source_location location) noexcept
    : FrameworkException(
        formatMessage(
          parserName, 
          position, 
          offendingToken, 
          detailedMessage
        ),
        std::move(innerException), 
        location
      ),
      m_parserName(std::move(parserName)),
      m_position(position),
      m_offendingToken(std::move(offendingToken))
{}


std::string_view        ParseException::parserName() const noexcept { return m_parserName; }
size_t                  ParseException::byteOffset() const noexcept { return m_position.byteOffset; }
std::optional<size_t>   ParseException::lineNumber() const noexcept { return m_position.line; }
std::optional<size_t>   ParseException::columnNumber() const noexcept { return m_position.column; }
std::string_view        ParseException::offendingToken() const noexcept { return m_offendingToken; }

std::string ParseException::formatMessage(
  std::string_view      parser,
  const SourcePosition& pos,
  std::string_view      token,
  std::string_view      detailedMessage
) noexcept {
  try {
    std::string prefix = (pos.line && pos.column) 
      ? std::format("{} Parser Error at line {}, col {} (offset {})", parser, *pos.line, *pos.column, pos.byteOffset)
      : std::format("{} Parser Error at stream offset {}", parser, pos.byteOffset);

    // 2. Synthesize everything in a single formatting pass
    return std::format("{}:{}{}", 
      prefix,
      token.empty()           ? "" : std::format(" Unexpected token '{}'.", token),
      detailedMessage.empty() ? "" : std::format(" {}", detailedMessage)
    );
  } catch (...) {
    return "ParseException: Malformed syntax encountered during engine parsing execution loop.";
  }
}
