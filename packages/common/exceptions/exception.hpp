#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <source_location>
#include <chrono>
#include <memory>
#include <map>
#include <any>
#include <format>

class FrameworkException : public std::exception {
public:
  using Timestamp   = std::chrono::system_clock::time_point;
  using MetadataMap = std::map<std::string, std::any, std::less<>>;

  inline FrameworkException(std::string message, std::source_location location = std::source_location::current()) noexcept {
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

  inline FrameworkException( 
                    std::string message, 
                    std::exception_ptr innerException, 
                    std::source_location location = std::source_location::current()
  ) noexcept {
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

  ~FrameworkException() noexcept override = default;

  inline FrameworkException(const FrameworkException& other) noexcept : m_implementation(other.m_implementation) {}

  inline FrameworkException& operator=(const FrameworkException& other) noexcept {
    if (this != &other) { m_implementation = other.m_implementation; }
    return *this;
  }

  FrameworkException(FrameworkException&& other)            noexcept = default;
  FrameworkException& operator=(FrameworkException&& other) noexcept = default;

  [[nodiscard]] inline const char* what() const noexcept override {
    if (m_implementation) [[likely]] {
      return m_implementation->formattedWhat.c_str();
    }
    return "FrameworkException (Degraded State due to Allocation Failure)";
  }

  [[nodiscard]] inline std::string_view message() const noexcept {
    return m_implementation ? m_implementation->message : std::string_view{};
  }

  [[nodiscard]] inline std::string_view file() const noexcept {
    return m_implementation ? m_implementation->location.file_name() : std::string_view{};
  }

  [[nodiscard]] inline uint32_t line() const noexcept {
    return m_implementation ? m_implementation->location.line() : 0;
  }

  [[nodiscard]] inline std::string_view function() const noexcept {
    return m_implementation ? m_implementation->location.function_name() : std::string_view{};
  }

  [[nodiscard]] inline Timestamp timestamp() const noexcept {
    return m_implementation ? m_implementation->timestamp : std::chrono::system_clock::time_point{};
  }

  [[nodiscard]] inline bool hasInnerException() const noexcept {
    return m_implementation && m_implementation->innerException != nullptr;
  }

  [[nodiscard]] inline std::exception_ptr innerException() const noexcept {
    return m_implementation ? m_implementation->innerException : nullptr;
  }

  [[nodiscard]] inline const MetadataMap& metadata() const noexcept {
    static const MetadataMap emptyMap;
    return m_implementation ? m_implementation->metadata : emptyMap;
  }

protected:
  inline void addMetadata(std::string key, std::any value) {
    if (!m_implementation) return;
    
    // Cast away constness safely only inside internal initialization pathways
    auto* mutableImpl = const_cast<Implementation*>(m_implementation.get());
    try {
      mutableImpl->metadata[std::move(key)] = std::move(value);
    } catch (...) {
      // Enforce strong FrameworkException safety; drop metadata rather than throwing
    }
  }

private:
  struct Implementation {
    std::string           message;
    std::source_location  location;
    Timestamp             timestamp;
    std::exception_ptr    innerException;
    MetadataMap           metadata;
    std::string           formattedWhat;
  };

  std::shared_ptr<const Implementation> m_implementation;

  static inline std::string formatWhat(const std::string& message, const std::source_location& location) noexcept {
    try {
      return std::format(
        "{}:{} [{}] {}", 
        location.file_name(), 
        location.line(), 
        location.function_name(), 
        message
      );
    } catch (...) { return message; }
  }
};
