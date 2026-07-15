#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <source_location>
#include <chrono>
#include <memory>
#include <map>
#include <any>

class FrameworkException : public std::exception {
public:
  using Timestamp   = std::chrono::system_clock::time_point;
  using MetadataMap = std::map<std::string, std::any, std::less<>>;

  FrameworkException(std::string message, std::source_location location = std::source_location::current()) noexcept;
  
  FrameworkException(std::string message, 
                     std::exception_ptr innerException, 
                     std::source_location location = std::source_location::current()) noexcept;

  ~FrameworkException() noexcept override = default;

  FrameworkException(const FrameworkException& other) noexcept;
  FrameworkException& operator=(const FrameworkException& other) noexcept;

  FrameworkException(FrameworkException&& other)            noexcept = default;
  FrameworkException& operator=(FrameworkException&& other) noexcept = default;

  [[nodiscard]] const char*         what() const noexcept override;
  [[nodiscard]] std::string_view    message() const noexcept;
  [[nodiscard]] std::string_view    file() const noexcept;
  [[nodiscard]] uint32_t            line() const noexcept;
  [[nodiscard]] std::string_view    function() const noexcept;
  [[nodiscard]] Timestamp           timestamp() const noexcept;
  [[nodiscard]] bool                hasInnerException() const noexcept;
  [[nodiscard]] std::exception_ptr  innerException() const noexcept;

private:
  struct Implementation {
    std::string           message;
    std::source_location  location;
    Timestamp             timestamp;
    std::exception_ptr    innerException;
    std::string           formattedWhat;
  };

  std::shared_ptr<const Implementation> m_implementation;

  static std::string formatWhat(const std::string& message, const std::source_location& location) noexcept;
};
