module;

#include <filesystem>

export module Commands.New;
import Commands.Base;

namespace fs = std::filesystem;

export class NewCommand : public Command {};
