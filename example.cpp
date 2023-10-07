#include <capstone.hpp>

#include <iostream>

#define asm_code "\x8d\x4c\x32\x08\x01\xd8"

int main()
{
    auto cs = Capstone::Capstone(Capstone::Arch::X86, Capstone::Mode::MODE_64);

    auto insns = cs.disasm(asm_code); // It would return a std::vector<Capstone::Instruction>
    for (auto &insn : insns)
        std::cout << insn.mnemonic << " " << insn.op_str << std::endl;

    return 0;
}