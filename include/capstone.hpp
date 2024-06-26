#ifndef __CAPSTONE_CPP_CAPSTONE_HPP__
#define __CAPSTONE_CPP_CAPSTONE_HPP__

#include <cstdint>
#include <vector>
#include <string>
#include <array>

// defined DEPRECATED macro
#if __cplusplus >= 201402L
#define DEPRECATED [[deprecated]]
#else
#if defined(__GNUC__) || defined(__clang__)
#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#endif
#endif // __cplusplus >= 201402L

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
        MOS65XX,
        WASM,
        BPF,
        RISCV,
        SH,
        TRICORE,
        MAX,
        ALL,
    };

    enum class Mode : uint32_t
    {
        MODE_LITTLE_ENDIAN = 0,               ///< little-endian mode (default mode)
        MODE_ARM = 0,                         ///< 32-bit ARM
        MODE_16 = 1 << 1,                     ///< 16-bit mode (X86)
        MODE_32 = 1 << 2,                     ///< 32-bit mode (X86)
        MODE_64 = 1 << 3,                     ///< 64-bit mode (X86, PPC)
        MODE_THUMB = 1 << 4,                  ///< ARM's Thumb mode, including Thumb-2
        MODE_MCLASS = 1 << 5,                 ///< ARM's Cortex-M series
        MODE_V8 = 1 << 6,                     ///< ARMv8 A32 encodings for ARM
        MODE_MICRO = 1 << 4,                  ///< MicroMips mode (MIPS)
        MODE_MIPS3 = 1 << 5,                  ///< Mips III ISA
        MODE_MIPS32R6 = 1 << 6,               ///< Mips32r6 ISA
        MODE_MIPS2 = 1 << 7,                  ///< Mips II ISA
        MODE_V9 = 1 << 4,                     ///< SparcV9 mode (Sparc)
        MODE_QPX = 1 << 4,                    ///< Quad Processing eXtensions mode (PPC)
        MODE_SPE = 1 << 5,                    ///< Signal Processing Engine mode (PPC)
        MODE_BOOKE = 1 << 6,                  ///< Book-E mode (PPC)
        MODE_PS = 1 << 7,                     ///< Paired-singles mode (PPC)
        MODE_M68K_000 = 1 << 1,               ///< M68K 68000 mode
        MODE_M68K_010 = 1 << 2,               ///< M68K 68010 mode
        MODE_M68K_020 = 1 << 3,               ///< M68K 68020 mode
        MODE_M68K_030 = 1 << 4,               ///< M68K 68030 mode
        MODE_M68K_040 = 1 << 5,               ///< M68K 68040 mode
        MODE_M68K_060 = 1 << 6,               ///< M68K 68060 mode
        MODE_BIG_ENDIAN = 1U << 31,           ///< big-endian mode
        MODE_MIPS32 = MODE_32,                ///< Mips32 ISA (Mips)
        MODE_MIPS64 = MODE_64,                ///< Mips64 ISA (Mips)
        MODE_M680X_6301 = 1 << 1,             ///< M680X Hitachi 6301,6303 mode
        MODE_M680X_6309 = 1 << 2,             ///< M680X Hitachi 6309 mode
        MODE_M680X_6800 = 1 << 3,             ///< M680X Motorola 6800,6802 mode
        MODE_M680X_6801 = 1 << 4,             ///< M680X Motorola 6801,6803 mode
        MODE_M680X_6805 = 1 << 5,             ///< M680X Motorola/Freescale 6805 mode
        MODE_M680X_6808 = 1 << 6,             ///< M680X Motorola/Freescale/NXP 68HC08 mode
        MODE_M680X_6809 = 1 << 7,             ///< M680X Motorola 6809 mode
        MODE_M680X_6811 = 1 << 8,             ///< M680X Motorola/Freescale/NXP 68HC11 mode
        MODE_M680X_CPU12 = 1 << 9,            ///< M680X Motorola/Freescale/NXP CPU12
                                              ///< used on M68HC12/HCS12
        MODE_M680X_HCS08 = 1 << 10,           ///< M680X Freescale/NXP HCS08 mode
        MODE_BPF_CLASSIC = 0,                 ///< Classic BPF mode (default)
        MODE_BPF_EXTENDED = 1 << 0,           ///< Extended BPF mode
        MODE_RISCV32 = 1 << 0,                ///< RISCV RV32G
        MODE_RISCV64 = 1 << 1,                ///< RISCV RV64G
        MODE_RISCVC = 1 << 2,                 ///< RISCV compressed instructure mode
        MODE_MOS65XX_6502 = 1 << 1,           ///< MOS65XXX MOS 6502
        MODE_MOS65XX_65C02 = 1 << 2,          ///< MOS65XXX WDC 65c02
        MODE_MOS65XX_W65C02 = 1 << 3,         ///< MOS65XXX WDC W65c02
        MODE_MOS65XX_65816 = 1 << 4,          ///< MOS65XXX WDC 65816, 8-bit m/x
        MODE_MOS65XX_65816_LONG_M = (1 << 5), ///< MOS65XXX WDC 65816, 16-bit m, 8-bit x
        MODE_MOS65XX_65816_LONG_X = (1 << 6), ///< MOS65XXX WDC 65816, 8-bit m, 16-bit x
        MODE_MOS65XX_65816_LONG_MX = MODE_MOS65XX_65816_LONG_M | MODE_MOS65XX_65816_LONG_X,
        MODE_SH2 = 1 << 1,         ///< SH2
        MODE_SH2A = 1 << 2,        ///< SH2A
        MODE_SH3 = 1 << 3,         ///< SH3
        MODE_SH4 = 1 << 4,         ///< SH4
        MODE_SH4A = 1 << 5,        ///< SH4A
        MODE_SHFPU = 1 << 6,       ///< w/ FPU
        MODE_SHDSP = 1 << 7,       ///< w/ DSP
        MODE_TRICORE_110 = 1 << 1, ///< Tricore 1.1
        MODE_TRICORE_120 = 1 << 2, ///< Tricore 1.2
        MODE_TRICORE_130 = 1 << 3, ///< Tricore 1.3
        MODE_TRICORE_131 = 1 << 4, ///< Tricore 1.3.1
        MODE_TRICORE_160 = 1 << 5, ///< Tricore 1.6
        MODE_TRICORE_161 = 1 << 6, ///< Tricore 1.6.1
        MODE_TRICORE_162 = 1 << 7, ///< Tricore 1.6.2
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
        DEPRECATED std::vector<Instruction> disasm(const std::string &code);
        std::vector<Instruction> disasm(const std::vector<uint8_t> &code);

    private:
        using csh = size_t; // The underlying type of handle is size_t in the original capstone-engine
        csh handle;
    };

    class Instruction
    {
    public:
        Instruction() = default;
        ~Instruction() = default;
        Instruction(uint32_t id, uint64_t address, uint16_t size, std::array<uint8_t, 24> bytes, std::string mnemonic, std::string op_str)
            : id(id), address(address), size(size), bytes(bytes), mnemonic(mnemonic), op_str(op_str) {}

        // Similar to cs_insn, please refer to the source code of capstone for more details
        uint32_t id = 0;                  // The id of instruction, e.g. X86_INS_MOV (which is defined typedef in enum x86_insn)
        uint64_t address = -1;            // The address of instruction
        uint16_t size = 0;                // The size of this instruction, which is the number of bytes
        std::array<uint8_t, 24> bytes{0}; // The bytes of instruction, the number of bytes is determined by size
        std::string mnemonic;
        std::string op_str;
    };
} // namespace Capstone

#endif