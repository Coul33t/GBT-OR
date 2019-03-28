#ifndef Z80_H
#define Z80_H

#include "common_includes.h"

#include <bitset>
#include <map>

#define FLAG_C 0x10
#define FLAG_H 0x20
#define FLAG_N 0x40
#define FLAG_Z 0x80

#include "mmu.h"
#include "registers.h"

struct Clock {
    unsigned int m, t;
};

// https://cturt.github.io/cinoop.html
struct instruction {
    uint8_t op_code;
    std::string disassembly;
    void *execute;

    instruction(uint8_t op_code, std::string disassembly, void* execute) {
        this->op_code = op_code;
        this->disassembly = disassembly;
        this->execute = execute;
    }
};

class Z80 {
    public:
        Z80();
        virtual ~Z80();

        void set_implemented_opcodes(void);

        void reset(void);

        void print_registers(void);

        // Checks for reg1 - reg2 < 0
        bool check_underflow(uint8_t reg1, uint8_t reg2);

        // Checks for reg1 + reg2 > 255
        bool check_overflow(uint8_t reg1, uint8_t reg2);

        // No operation
        void NOP(void);

        // Put val into reg1
        // Adds reg2 to reg1
        void LDrr(uint8_t& reg1, uint8_t& reg2);
        void LDrr(uint16_t& reg1, uint8_t& reg2);
        void LDrr(uint8_t& reg1, uint16_t& reg2);

        // Put value into reg1
        // reg1 = B, C, D, E, H, L, BC, DE, HL, SP
        void LDnn(uint8_t& reg1, uint8_t val);
        void LDnn(uint16_t& reg1, uint8_t val);


        // Yeah I don't want to bother with accessors
        // 8-bits registers
        // F -> Flag register (see below)
        // A, B, C, D, E, H, L -> General purpose registers
        // 16-bits registers :
        // AF, BC, DE, HL -> combination of the 8-bits above
        // PC -> Program Counter, points to the next instruction to be executed
        // SP -> Stack Pointer, points to the current stack location
        registers reg;

        // clock
        unsigned int m, t;

        Clock clock;

        MMU mmu;

        std::vector<instruction> implemented_opcodes;
};

// A, B, C, D, E, H, L : general purpose registers
// F : flag register -> 0x10 -> FLAG_C = carry (over 255 for additions, under 0 for subtractions)
//                      0x20 -> FLAG_H = half-carry (result of the last op, lower half of the byte overflowed past 15)
//                      0x40 -> FLAG_N = operation (last op was a subtraction)
//                      0x80 -> FLAG_Z = Zero (last op produced 0)
#endif // Z80_H
