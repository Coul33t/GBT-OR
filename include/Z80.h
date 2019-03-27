#ifndef Z80_H
#define Z80_H

#include <cstdint>
#include <iostream>

struct Clock {
    unsigned int m, t;
};

class Z80 {
    public:
        Z80();
        virtual ~Z80();
        void reset(void);
        void print_registers(void);

        void NOP(void);

        void ADD(uint8_t& reg1, uint8_t& reg2);
        void CPR(uint8_t& reg1, uint8_t& reg2);


        // Yeah I don't want to bother with accessors
        // 8 bits registers
        uint8_t a, b, c, d, e, f, h, l;
        // 16 bits registers
        uint16_t pc, sp;
        // clock
        unsigned int m, t;

        Clock clock;
    protected:

    private:


};

// A, B, C, D, E, H, L : general purpose registers
// F : flag register -> 0x10 = carry (over 255 for additions, under 0 for subtractions)
//                      0x20 = half-carry (result of the last op, lower half of the byte overflowed past 15)
//                      0x40 = operation (last op was a subtraction)
//                      0x80 = Zero (last op produced 0)
#endif // Z80_H
