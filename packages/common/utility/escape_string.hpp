#pragma once
#include <string>
#include <string_view>
#include <format>

// Partially reconstructs readable request data by extracting context from around the violation index
[[nodiscard]] std::string escapeBinaryFrame(std::string_view rawInput, size_t maxWindowBytes) noexcept;
