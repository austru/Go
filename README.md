# Go

A simple client for playing the game of go.

## Requirements
- CMake v3.10.0
- Make
- SDL 2.0
- C++20 compiler

## Linux

### Installing Requirements
```
sudo apt update
sudo apt install g++ make cmake libsdl2-dev
```

### Compiling
```
mkdir build
cd build
cmake ..
cmake --build .
```

## Windows (64-bit)
MSYS2 provides a Unix-like environment making it easier to install or build software on Windows using the GCC compiler.
Visit the [MSYS2 homepage](https://www.msys2.org/) to find more information and installers.
The installer will run a shell once complete. Update packages with `pacman -Syuu`, then upon completion close the shell.
Using notepad, copy the following script into a new file called `install.sh`:
```
#!/bin/bash
# install.sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-cmake mingw-w64-x86_64-SDL2 git
mkdir Go
cd Go
git clone https://github.com/austru/Go.git .
mkdir build
cd build
cmake ..
cmake --build .
```
### Compiling
Start a MSYS2 MinGW x64 shell `C:\msys64\mingw64.exe`.
Navigate to where you saved the script, then run it with `bash install.sh`.




