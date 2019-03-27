#include "Z80.h"

Z80::Z80() {
    reset();
}

Z80::~Z80() {
    //dtor
}

void Z80::reset(void) {
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->d = 0;
    this->e = 0;
    this->f = 0;
    this->h = 0;
    this->l = 0;

    this->pc = 0;
    this->sp = 0;

    this->m = 0;
    this->t = 0;

    this->clock.m = 0;
    this->clock.t = 0;
}

void Z80::print_registers(void) {
    std::cout << "8 bits registers" << std::endl;
    std::cout << "Register A: " << std::bitset<8>(this->a) << " (" << (unsigned int)this->a << ")" << std::endl;
    std::cout << "Register B: " << std::bitset<8>(this->b) << " (" << (unsigned int)this->b << ")" << std::endl;
    std::cout << "Register C: " << std::bitset<8>(this->c) << " (" << (unsigned int)this->c << ")" << std::endl;
    std::cout << "Register D: " << std::bitset<8>(this->d) << " (" << (unsigned int)this->d << ")" << std::endl;
    std::cout << "Register E: " << std::bitset<8>(this->e) << " (" << (unsigned int)this->e << ")" << std::endl;
    std::cout << "Register F: " << std::bitset<8>(this->f) << " (" << (unsigned int)this->f << ")" << std::endl;
    std::cout << "Register H: " << std::bitset<8>(this->h) << " (" << (unsigned int)this->h << ")" << std::endl;
    std::cout << "Register L: " << std::bitset<8>(this->l) << " (" << (unsigned int)this->l << ")" << std::endl;

    std::cout << std::endl << "16 bits registers" << std::endl;
    std::cout << "Register PC: " << std::bitset<16>(this->sp) << " (" << (unsigned int)this->sp << ")" << std::endl;
    std::cout << "Register SP: " << std::bitset<16>(this->pc) << " (" << (unsigned int)this->pc << ")" << std::endl;

    std::cout << std::endl << "Timers" << std::endl;
    std::cout << "Register M: " << std::bitset<8>(this->m) << " (" << (unsigned int)this->m << ")" << std::endl;
    std::cout << "Register T: " << std::bitset<8>(this->t) << " (" << (unsigned int)this->t << ")" << std::endl;

    std::cout << std::endl << "Clock" << std::endl;
    std::cout << "Clock M: " << std::bitset<8>(this->clock.m) << " (" << (unsigned int)this->clock.m << ")" << std::endl;
    std::cout << "Clock T: " << std::bitset<8>(this->clock.t) << " (" << (unsigned int)this->clock.t << ")" << std::endl;
}

void Z80::NOP(void) {
    this->m = 1;
    this->t = 4;
}

void Z80::ADD(uint8_t& reg1, uint8_t& reg2) {
    reg1 += reg2;
    this->f = 0;
    if(!(reg1 & 255))
        this->f |= FLAG_Z;

    this->m = 1;
    this->t = 4;
}

void Z80::CPR(uint8_t& reg1, uint8_t& reg2) {
    uint8_t i = reg1;
    i -= reg2;
    this->f |= FLAG_N;
    if(!i & 255)
        this->f |= FLAG_Z;
}


