# Capstone-cpp

The Modern C++ wrapper for the [Capstone-Engine](https://github.com/capstone-engine/capstone).

## Purpose
Design a wrapper for our [VMPilot](https://github.com/25077667/vmpilot) project.

## Requirements
- CMake
- C++11 or higher compiler

### Optional requirements
- [Ninja](https://github.com/ninja-build/ninja)
- [mold](https://github.com/rui314/mold)

## Build
Release build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja -DCMAKE_LINKER=mold
ninja
```

Debug build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G Ninja -DCMAKE_LINKER=mold
ninja
```

## Usage
```cpp
#include <capstone.hpp>

#include <iostream>

int main()
{
    auto cs = Capstone::Capstone(Capstone::Arch::X86, Capstone::Mode::MODE_64);

    std::vector<uint8_t> code = {0x8d, 0x4c, 0x32, 0x08, 0x01, 0xd8};
    auto insns = cs.disasm(code);
    for (auto &insn : insns)
        std::cout << insn.mnemonic << " " << insn.op_str << std::endl;

    return 0;
}
```

### On your CMakeLists.txt
```cmake
add_executable(your_executable main.cpp)
target_include_directories(your_executable PRIVATE ${CAPSTONE_WRAPPER_INCLUDE_DIR})
target_link_libraries(your_executable ${CAPSTONE_WRAPPER_LIBRARY})
```
