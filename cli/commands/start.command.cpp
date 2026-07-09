module;

#include <filesystem>

export module Commands.Start;
import Commands.Base;

namespace fs = std::filesystem;

export class StartCommand : public Command {};
