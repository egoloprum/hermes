module;

#include <filesystem>

export module Commands.Add;
import Commands.Base;

namespace fs = std::filesystem;

export class AddCommand : public Command {};
