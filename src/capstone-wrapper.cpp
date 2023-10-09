#include <capstone.hpp>
#include <capstone/capstone.h> // source code of capstone

#include <stdexcept>

using namespace Capstone;

Capstone::Capstone::Capstone(::Arch arch, ::Mode mode)
{
    cs_err err = cs_open(static_cast<cs_arch>(arch), static_cast<cs_mode>(mode), &handle);
    if (err != CS_ERR_OK)
        throw std::runtime_error("Failed on cs_open()");

    set_option(CS_OPT_DETAIL, CS_OPT_ON);
}

Capstone::Capstone::~Capstone()
{
    cs_close(&handle);
}

int Capstone::Capstone::set_option(int type, size_t value) noexcept
{
    return cs_option(handle, static_cast<cs_opt_type>(type), value);
}

DEPRECATED std::vector<Instruction> Capstone::Capstone::disasm(const std::string &code)
{
    size_t count;
    cs_insn *insn;
    count = cs_disasm(handle, reinterpret_cast<const uint8_t *>(code.data()), code.size(), 0, 0, &insn);
    if (count <= 0)
        throw std::runtime_error("Failed on cs_disasm()");

    std::vector<Instruction> insns;
    for (size_t i = 0; i < count; i++)
    {
        insns.emplace_back(
            Instruction{
                std::string(insn[i].mnemonic),
                std::string(insn[i].op_str)});
    }

    cs_free(insn, count);
    return insns;
}

std::vector<Instruction> Capstone::Capstone::disasm(const std::vector<uint8_t> &code)
{
    size_t count;
    cs_insn *insn;
    count = cs_disasm(handle, code.data(), code.size(), 0, 0, &insn);
    if (count <= 0)
        throw std::runtime_error("Failed on cs_disasm()");

    std::vector<Instruction> insns;
    for (size_t i = 0; i < count; i++)
    {
        insns.emplace_back(
            Instruction{
                std::string(insn[i].mnemonic),
                std::string(insn[i].op_str)});
    }

    cs_free(insn, count);
    return insns;
}