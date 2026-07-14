#include "lib/exception-runtime.hpp"
#include "../utility/to_string.hpp"
#include <any>
#include <utility>

RuntimeException::RuntimeException(
  Subsystem subsystem,
  std::string message,
  std::source_location location) noexcept
  : FrameworkException(prefixSubsystem(subsystem, message), location),
    m_subsystem(subsystem) 
{
  addMetadata("framework.subsystem_id", static_cast<uint32_t>(subsystem));
  try {
    addMetadata("framework.subsystem_name", std::string(to_string(subsystem)));
  } catch (...) {}
}

RuntimeException::RuntimeException(
  Subsystem subsystem,
  std::string message,
  std::exception_ptr innerException,
  std::source_location location) noexcept
  : FrameworkException(prefixSubsystem(subsystem, message), std::move(innerException), location),
    m_subsystem(subsystem) 
{
  addMetadata("framework.subsystem_id", static_cast<uint32_t>(subsystem));
  try {
    addMetadata("framework.subsystem_name", std::string(to_string(subsystem)));
  } catch (...) {}
}

Subsystem RuntimeException::subsystem() const noexcept { 
  return m_subsystem; 
}

std::string_view RuntimeException::subsystemName() const noexcept { 
  return to_string(m_subsystem); 
}

std::string RuntimeException::prefixSubsystem(Subsystem subsystem, const std::string& message) noexcept {
  try {
    return "[" + std::string(to_string(subsystem)) + "] " + message;
  } catch (...) {
    return message;
  }
}
