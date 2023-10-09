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