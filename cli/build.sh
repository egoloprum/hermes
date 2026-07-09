#!/bin/bash
set -e
cd "$(dirname "$0")"

# -p prevents crashes if the folders already exist
mkdir -p "pcm"
mkdir -p "bin"

echo "1. Precompiling module interfaces..."
clang++ -std=c++23 --precompile -x c++-module commands/base.command.cpp -o pcm/Commands.Base.pcm
clang++ -std=c++23 -fprebuilt-module-path=pcm --precompile -x c++-module commands/add.command.cpp -o pcm/Commands.Add.pcm
clang++ -std=c++23 -fprebuilt-module-path=pcm --precompile -x c++-module commands/build.command.cpp -o pcm/Commands.Build.pcm
clang++ -std=c++23 -fprebuilt-module-path=pcm --precompile -x c++-module commands/new.command.cpp -o pcm/Commands.New.pcm
clang++ -std=c++23 -fprebuilt-module-path=pcm --precompile -x c++-module commands/start.command.cpp -o pcm/Commands.Start.pcm

echo "2. Generating object files from modules..."
clang++ -std=c++23 -fprebuilt-module-path=pcm -c pcm/Commands.Base.pcm -o bin/Commands.Base.o
clang++ -std=c++23 -fprebuilt-module-path=pcm -c pcm/Commands.Add.pcm -o bin/Commands.Add.o
clang++ -std=c++23 -fprebuilt-module-path=pcm -c pcm/Commands.Build.pcm -o bin/Commands.Build.o
clang++ -std=c++23 -fprebuilt-module-path=pcm -c pcm/Commands.New.pcm -o bin/Commands.New.o
clang++ -std=c++23 -fprebuilt-module-path=pcm -c pcm/Commands.Start.pcm -o bin/Commands.Start.o

echo "3. Compiling main application layer..."
clang++ -std=c++23 -fprebuilt-module-path=pcm -c main.cpp -o bin/main.o

echo "4. Linking everything into final binary..."
clang++ -std=c++23 bin/main.o bin/Commands.Base.o bin/Commands.Add.o bin/Commands.Build.o bin/Commands.New.o bin/Commands.Start.o -o hermes

echo "5. Installing hermes globally to /usr/local/bin..."
# sudo is required to write into system binary paths
sudo cp hermes /usr/local/bin/hermes
sudo chmod +x /usr/local/bin/hermes

echo "6. Cleaning up build artifacts..."
rm -rf "bin"
rm -rf "pcm"
rm -f "hermes" # Cleans up the local copy since it is now globally installed

echo "Installation successful! You can now run 'hermes' from anywhere."
