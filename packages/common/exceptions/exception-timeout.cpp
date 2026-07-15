#include "lib/exception-timeout.hpp"
#include "../utility/to_string.hpp"
#include <format>
#include <utility>

TimeoutException::TimeoutException(
  TimeoutType           type,
  std::string           operationName,
  Duration              configuredTimeout,
  Duration              actualElapsed,
  SubsystemType         subsystemName,
  std::source_location  location
) noexcept
  : FrameworkException(
      formatMessage(
        type, 
        operationName, 
        configuredTimeout, 
        actualElapsed
      ), 
      location
    ),
    m_type(type),
    m_operationName(std::move(operationName)),
    m_subsystemName(std::move(subsystemName)),
    m_configuredTimeout(configuredTimeout),
    m_actualElapsed(actualElapsed)
{}

TimeoutType                 TimeoutException::timeoutType() const noexcept { return m_type; }
std::string_view            TimeoutException::timeoutTypeName() const noexcept { return to_string(m_type); }
std::string_view            TimeoutException::operationName() const noexcept { return m_operationName; }
std::string_view            TimeoutException::subsystemName() const noexcept { return to_string(m_subsystemName); }
TimeoutException::Duration  TimeoutException::configuredTimeout() const noexcept { return m_configuredTimeout; }
TimeoutException::Duration  TimeoutException::actualElapsed() const noexcept { return m_actualElapsed; }

std::string TimeoutException::formatMessage(
  TimeoutType type,
  std::string_view operation,
  Duration configured,
  Duration elapsed
) noexcept {
  try {
    double confMs = static_cast<double>(configured.count()) / 1000.0;
    double elapMs = static_cast<double>(elapsed.count()) / 1000.0;

    return std::format(
      "Timeout occurred during {} operation '{}': Exceeded configured limit of {:.3f}ms (Elapsed: {:.3f}ms).",
      to_string(type), operation, confMs, elapMs
    );
  } catch (...) {
    return "TimeoutException: Operation exceeded its specified time budget.";
  }
}
