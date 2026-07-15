#include "lib/exception-runtime.hpp"
#include "../utility/to_string.hpp"
#include <any>
#include <utility>

RuntimeException::RuntimeException(
  SubsystemType         subsystemType,
  std::string           message,
  std::source_location  location
) noexcept
  : FrameworkException(
    formatMessage(subsystemType, message), 
    location
  ),
    m_subsystemType(subsystemType) 
{}

RuntimeException::RuntimeException(
  SubsystemType         subsystemType,
  std::string           message,
  std::exception_ptr    innerException,
  std::source_location  location
) noexcept
  : FrameworkException(
    formatMessage(subsystemType, message), 
    std::move(innerException), 
    location
  ),
    m_subsystemType(subsystemType) 
{}

SubsystemType RuntimeException::subsystemType()     const noexcept { return m_subsystemType; }
std::string_view RuntimeException::subsystemName()  const noexcept { return to_string(m_subsystemType); }

std::string RuntimeException::formatMessage(SubsystemType subsystemType, const std::string& message) noexcept {
  try { return "[" + std::string(to_string(subsystemType)) + "] " + message; } 
  catch (...) { return message; }
}
