#pragma once

#include <optional>

struct SourcePosition {
  size_t byteOffset{0};          // Zero-based raw stream index
  std::optional<size_t> line;    // One-based line count (if tracking text lines)
  std::optional<size_t> column;  // One-based column index matching line data
};
