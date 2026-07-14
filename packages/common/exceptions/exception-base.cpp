#include "lib/exception-base.hpp"
#include <format>
#include <utility>

FrameworkException::FrameworkException(std::string message, std::source_location location) noexcept {
  try {
    auto formatted = formatWhat(message, location);
    m_implementation = std::make_shared<const Implementation>(Implementation{
      .message = std::move(message),
      .location = location,
      .timestamp = std::chrono::system_clock::now(),
      .innerException = nullptr,
      .metadata = {},
      .formattedWhat = std::move(formatted)
    });
  } catch (...) {
    m_implementation = nullptr;
  }
}

FrameworkException::FrameworkException(std::string message, 
                                       std::exception_ptr innerException, 
                                       std::source_location location) noexcept {
  try {
    auto formatted = formatWhat(message, location);
    m_implementation = std::make_shared<const Implementation>(Implementation{
      .message = std::move(message),
      .location = location,
      .timestamp = std::chrono::system_clock::now(),
      .innerException = std::move(innerException),
      .metadata = {},
      .formattedWhat = std::move(formatted)
    });
  } catch (...) {
    m_implementation = nullptr;
  }
}

FrameworkException::FrameworkException(const FrameworkException& other) noexcept 
  : m_implementation(other.m_implementation) {}

FrameworkException& FrameworkException::operator=(const FrameworkException& other) noexcept {
  if (this != &other) { m_implementation = other.m_implementation; }
  return *this;
}

const char* FrameworkException::what() const noexcept {
  if (m_implementation) [[likely]] {
    return m_implementation->formattedWhat.c_str();
  }
  return "FrameworkException (Degraded State due to Allocation Failure)";
}

std::string_view FrameworkException::message() const noexcept {
  return m_implementation ? m_implementation->message : std::string_view{};
}

std::string_view FrameworkException::file() const noexcept {
  return m_implementation ? m_implementation->location.file_name() : std::string_view{};
}

uint32_t FrameworkException::line() const noexcept {
  return m_implementation ? m_implementation->location.line() : 0;
}

std::string_view FrameworkException::function() const noexcept {
  return m_implementation ? m_implementation->location.function_name() : std::string_view{};
}

FrameworkException::Timestamp FrameworkException::timestamp() const noexcept {
  return m_implementation ? m_implementation->timestamp : std::chrono::system_clock::time_point{};
}

bool FrameworkException::hasInnerException() const noexcept {
  return m_implementation && m_implementation->innerException != nullptr;
}

std::exception_ptr FrameworkException::innerException() const noexcept {
  return m_implementation ? m_implementation->innerException : nullptr;
}

const FrameworkException::MetadataMap& FrameworkException::metadata() const noexcept {
  static const MetadataMap emptyMap;
  return m_implementation ? m_implementation->metadata : emptyMap;
}

void FrameworkException::addMetadata(std::string key, std::any value) {
  if (!m_implementation) return;
  
  auto* mutableImpl = const_cast<Implementation*>(m_implementation.get());
  try { mutableImpl->metadata[std::move(key)] = std::move(value); } 
  catch (...) {} // Enforce strong FrameworkException safety; drop metadata rather than throwing
}

std::string FrameworkException::formatWhat(const std::string& message, const std::source_location& location) noexcept {
  try {
    return std::format(
      "{}:{} [{}] {}", 
      location.file_name(), 
      location.line(), 
      location.function_name(), 
      message
    );
  } catch (...) { 
    return message; 
  }
}
