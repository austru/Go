# Go

## Requirements
- CMake v3.10.0
- Make
- SDL 2.0
- C++20 compiler

### Linux

Install CMake
```
sudo apt install cmake
```
Install Make
```
sudo apt install make
```
Install SDL 2.0
```
sudo apt install libsdl2-dev
```
Install a C++20 compiler (GCC version 8 and later)
```
sudo apt install g++
```

## Compiling
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows
MSYS2 provides a Unix-like environment making it easier to install or build software on Windows using the GCC compiler.
[MSYS2 homepage](https://www.msys2.org/)
The installer will run a shell once complete. Update packages with `pacman -Syuu`, then upon completion close the shell.




