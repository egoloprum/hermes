#pragma once

#include "exception-base.hpp"
#include "../../enums/timeout.hpp"
#include "../../enums/subsystem.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <chrono>

class TimeoutException : public FrameworkException {
public:
  using Duration = std::chrono::microseconds;

  explicit TimeoutException(
    TimeoutType           type,
    std::string           operationName,
    Duration              configuredTimeout,
    Duration              actualElapsed,
    SubsystemType         subsystemName = SubsystemType::Network,
    std::source_location  location = std::source_location::current()
  ) noexcept;

  ~TimeoutException() noexcept override = default;

  TimeoutException(const TimeoutException& other)             noexcept = default;
  TimeoutException& operator=(const TimeoutException& other)  noexcept = default;
  TimeoutException(TimeoutException&& other)                  noexcept = default;
  TimeoutException& operator=(TimeoutException&& other)       noexcept = default;

  [[nodiscard]] TimeoutType       timeoutType() const noexcept;
  [[nodiscard]] std::string_view  timeoutTypeName() const noexcept;
  [[nodiscard]] std::string_view  operationName() const noexcept;
  [[nodiscard]] std::string_view  subsystemName() const noexcept;
  [[nodiscard]] Duration          configuredTimeout() const noexcept;
  [[nodiscard]] Duration          actualElapsed() const noexcept;

private:
  static std::string formatMessage(
      TimeoutType       type,
      std::string_view  operation,
      Duration          configured,
      Duration          elapsed
    ) noexcept;

  TimeoutType   m_type{TimeoutType::Unknown};
  std::string   m_operationName;
  SubsystemType m_subsystemName{SubsystemType::Network};
  Duration      m_configuredTimeout{0};
  Duration      m_actualElapsed{0};
};
