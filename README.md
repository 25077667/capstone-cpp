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

#define asm_code "\x8d\x4c\x32\x08\x01\xd8"

int main() {
    auto cs = Capstone::Capstone(Capstone::Arch::X86, Capstone::Mode::MODE_64);

    auto insns = cs.disasm(asm_code);// It would return a std::vector<Capstone::Instruction>
    for (auto &insn : insns)
        std::cout << insn.mnemonic << " " << insn.op_str << std::endl;
    
    return 0;
}
```