#ifndef __CAPSTONE_CPP_CAPSTONE_HPP__
#define __CAPSTONE_CPP_CAPSTONE_HPP__

#include <cstdint>
#include <vector>
#include <string>

namespace Capstone
{
    enum class Arch : uint8_t
    {
        ARM,
        ARM64,
        MIPS,
        X86,
        PPC,
        SPARC,
        SYSZ,
        XCORE,
        M68K,
        TMS320C64X,
        M680X,
        EVM,
    };

    enum class Mode : uint8_t
    {
        MODE_16,
        MODE_32,
        MODE_64,
        MODE_ARM,
        MODE_BIG_ENDIAN,
        MODE_BOOKE,
        MODE_BPF_CLASSIC,
        MODE_BPF_EXTENDED,
        MODE_LITTLE_ENDIAN,
        MODE_M680X_6301,
        MODE_M680X_6309,
        MODE_M680X_6800,
        MODE_M680X_6801,
        MODE_M680X_6805,
        MODE_M680X_6808,
        MODE_M680X_6809,
        MODE_M680X_6811,
        MODE_M680X_CPU12,
        MODE_M680X_HCS08,
        MODE_M68K_000,
        MODE_M68K_010,
        MODE_M68K_020,
        MODE_M68K_030,
        MODE_M68K_040,
        MODE_M68K_060,
        MODE_MCLASS,
        MODE_MICRO,
        MODE_MIPS2,
        MODE_MIPS3,
        MODE_MIPS32,
        MODE_MIPS32R6,
        MODE_MIPS64,
        MODE_MOS65XX_6502,
        MODE_MOS65XX_65816,
        MODE_MOS65XX_65816_LONG_M,
        MODE_MOS65XX_65816_LONG_MX,
        MODE_MOS65XX_65816_LONG_X,
        MODE_MOS65XX_65C02,
        MODE_MOS65XX_W65C02,
        MODE_PS,
        MODE_QPX,
        MODE_RISCV32,
        MODE_RISCV64,
        MODE_RISCVC,
        MODE_SH2,
        MODE_SH2A,
        MODE_SH3,
        MODE_SH4,
        MODE_SH4A,
        MODE_SHDSP,
        MODE_SHFPU,
        MODE_SPE,
        MODE_THUMB,
        MODE_TRICORE_110,
        MODE_TRICORE_120,
        MODE_TRICORE_130,
        MODE_TRICORE_131,
        MODE_TRICORE_160,
        MODE_TRICORE_161,
        MODE_TRICORE_162,
        MODE_V8,
        MODE_V9,
    };

    class Instruction;

    class Capstone
    {
    public:
        /**
         * @brief Construct a new Capstone object
         *
         * @param arch: architecture
         * @param mode: mode
         *
         * @exception std::runtime_error: when initializing failed
         */
        Capstone() : Capstone(Arch::X86, Mode::MODE_64) {}
        Capstone(Arch arch, Mode mode);
        ~Capstone();

        int set_option(int type, size_t value) noexcept;

        /**
         * @brief Input machine code and disassemble it.
         *
         * @param code: like "\x8d\x4c\x32\x08\x01\xd8"
         * @return std::vector<Instruction>: disassembled instructions
         *
         * @exception std::runtime_error: when disassembling failed
         */
        std::vector<Instruction> disasm(const std::string &code);

    private:
        using csh = size_t; // The underlying type of handle is size_t in the original capstone-engine
        csh handle;
    };

    class Instruction
    {
    public:
        Instruction() = default;
        ~Instruction() = default;

        std::string mnemonic;
        std::string op_str;
    };
} // namespace Capstone

#endif