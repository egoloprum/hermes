#pragma once

#include "exception-base.hpp"
#include "../../enums/parse.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <optional>

class ParseException : public FrameworkException {
public:
  explicit ParseException(
    std::string          parserName,
    SourcePosition       position,
    std::string          offendingToken = "",
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  ParseException(
    std::string          parserName,
    SourcePosition       position,
    std::exception_ptr   innerException,
    std::string          offendingToken = "",
    std::string          detailedMessage = "",
    std::source_location location = std::source_location::current()) noexcept;

  ~ParseException() noexcept override = default;

  ParseException(const ParseException& other)             noexcept = default;
  ParseException& operator=(const ParseException& other)  noexcept = default;
  ParseException(ParseException&& other)                  noexcept = default;
  ParseException& operator=(ParseException&& other)       noexcept = default;

  [[nodiscard]] std::string_view        parserName() const noexcept;
  [[nodiscard]] size_t                  byteOffset() const noexcept;
  [[nodiscard]] std::optional<size_t>   lineNumber() const noexcept;
  [[nodiscard]] std::optional<size_t>   columnNumber() const noexcept;
  [[nodiscard]] std::string_view        offendingToken() const noexcept;

private:
  std::string    m_parserName;
  SourcePosition m_position;
  std::string    m_offendingToken;

  static std::string formatMessage(
    std::string_view     parser,
    const SourcePosition& pos,
    std::string_view     token,
    std::string_view     details) noexcept;
};
