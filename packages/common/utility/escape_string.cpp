#include "escape_string.hpp"
#include <string_view>
#include <format>
#include <iterator>
#include <algorithm>
#include <cctype>

std::string escapeBinaryFrame(std::string_view rawInput, size_t maxWindowBytes) noexcept {
  if (rawInput.empty()) {
    return "[Empty Frame Context]";
  }
  
  try {
    std::string_view rawWindow = rawInput.substr(0, std::min(rawInput.size(), maxWindowBytes));
    
    std::string printableOutput;
    printableOutput.reserve((rawWindow.size() * 4) + 16); 
      
    for (char ch : rawWindow) {
      const auto u_ch = static_cast<unsigned char>(ch);
      switch (ch) {
        case '\r': printableOutput.append("\\r"); break;
        case '\n': printableOutput.append("\\n"); break;
        case '\t': printableOutput.append("\\t"); break;
        default:
          if (std::iscntrl(u_ch)) {
            std::format_to(std::back_inserter(printableOutput), "\\x{:02X}", u_ch);
          } else {
            printableOutput.push_back(ch);
          }
          break;
      }
    }
      
    if (rawInput.size() > maxWindowBytes) {
      printableOutput.append("... [truncated]");
    }
      
    return printableOutput;
  } catch (...) {
    return "[Failed to extract partial message reconstruction frame due to OOM]";
  }
}
