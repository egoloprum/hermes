#include "lib/exception-runtime.hpp"
#include "../utility/to_string.hpp"
#include <any>
#include <utility>

RuntimeException::RuntimeException(
  Subsystem subsystem,
  std::string message,
  std::source_location location) noexcept
  : FrameworkException(
    formatMessage(subsystem, message), 
    location
  ),
    m_subsystem(subsystem) 
{}

RuntimeException::RuntimeException(
  Subsystem subsystem,
  std::string message,
  std::exception_ptr innerException,
  std::source_location location) noexcept
  : FrameworkException(
    formatMessage(subsystem, message), 
    std::move(innerException), 
    location
  ),
    m_subsystem(subsystem) 
{}

Subsystem RuntimeException::subsystem()             const noexcept { return m_subsystem; }
std::string_view RuntimeException::subsystemName()  const noexcept { return to_string(m_subsystem); }

std::string RuntimeException::formatMessage(Subsystem subsystem, const std::string& message) noexcept {
  try { return "[" + std::string(to_string(subsystem)) + "] " + message; } 
  catch (...) { return message; }
}
