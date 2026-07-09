module;

#include <filesystem>

export module Commands.Build;
import Commands.Base;

namespace fs = std::filesystem;

export class BuildCommand : public Command {};
