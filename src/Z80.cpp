#include "Z80.h"

Z80::Z80() {
    reset();
}

Z80::~Z80() {
    //dtor
}

void Z80::reset(void) {
    this->reg.af = 0x0000;
    this->reg.bc = 0x0000;
    this->reg.de = 0x0000;
    this->reg.hl = 0x0000;

    this->reg.pc = 0x0000;
    this->reg.sp = 0x0000;

    this->m = 0;
    this->t = 0;

    this->clock.m = 0;
    this->clock.t = 0;

    set_implemented_opcodes();
}

void Z80::print_registers(void) {
    std::cout << "8 bits registers" << std::endl;
    std::cout << "Register A: " << std::bitset<8>(this->reg.a) << " (" << (unsigned int)this->reg.a << ")" << std::endl;
    std::cout << "Register B: " << std::bitset<8>(this->reg.b) << " (" << (unsigned int)this->reg.b << ")" << std::endl;
    std::cout << "Register C: " << std::bitset<8>(this->reg.c) << " (" << (unsigned int)this->reg.c << ")" << std::endl;
    std::cout << "Register D: " << std::bitset<8>(this->reg.d) << " (" << (unsigned int)this->reg.d << ")" << std::endl;
    std::cout << "Register E: " << std::bitset<8>(this->reg.e) << " (" << (unsigned int)this->reg.e << ")" << std::endl;
    std::cout << "Register F: " << std::bitset<8>(this->reg.f) << " (" << (unsigned int)this->reg.f << ")" << std::endl;
    std::cout << "Register H: " << std::bitset<8>(this->reg.h) << " (" << (unsigned int)this->reg.h << ")" << std::endl;
    std::cout << "Register L: " << std::bitset<8>(this->reg.l) << " (" << (unsigned int)this->reg.l << ")" << std::endl;

    std::cout << std::endl << "16 bits registers" << std::endl;
    std::cout << "Register PC: " << std::bitset<16>(this->reg.sp) << " (" << (unsigned int)this->reg.sp << ")" << std::endl;
    std::cout << "Register SP: " << std::bitset<16>(this->reg.pc) << " (" << (unsigned int)this->reg.pc << ")" << std::endl;

    std::cout << std::endl << "Timers" << std::endl;
    std::cout << "Register M: " << std::bitset<8>(this->m) << " (" << (unsigned int)this->m << ")" << std::endl;
    std::cout << "Register T: " << std::bitset<8>(this->t) << " (" << (unsigned int)this->t << ")" << std::endl;

    std::cout << std::endl << "Clock" << std::endl;
    std::cout << "Clock M: " << std::bitset<8>(this->clock.m) << " (" << (unsigned int)this->clock.m << ")" << std::endl;
    std::cout << "Clock T: " << std::bitset<8>(this->clock.t) << " (" << (unsigned int)this->clock.t << ")" << std::endl;
}

// Checks for reg1 - reg2 < 0
bool Z80::check_underflow(uint8_t reg1, uint8_t reg2) {
    return (reg1 < reg2);
}

// Checks for reg1 + reg2 > 256
bool Z80::check_overflow(uint8_t reg1, uint8_t reg2) {
    if (reg1 > 256 - reg2)
        return true;
    if (reg2 > 256 - reg1)
        return true;
    return false;
}

// No operation
void Z80::NOP(void) {
    this->m = 1;
    this->t = 4;
}

// Adds reg2 (8bits) to reg1 (8bits)
void Z80::LDrr(uint8_t& reg1, uint8_t& reg2) {
    reg1 += reg2;
    this->m = 1;
    this->t = 4;
}

// Adds reg2 (8bits) to reg1 (16bits)
void Z80::LDrr(uint16_t& reg1, uint8_t& reg2) {
    reg1 += reg2;

    this->m = 1;
    this->t = 4;
}

// Adds reg2 (16bits) to reg1 (8bits)
void Z80::LDrr(uint8_t& reg1, uint16_t& reg2) {
    reg1 += reg2;

    this->m = 1;
    this->t = 4;
}

void Z80::set_implemented_opcodes(void) {
    this->implemented_opcodes.push_back(instruction((uint8_t)0x00, std::string("NOP"), (void*)&Z80::NOP));
}

