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
    std::cout << "Register A: " << (unsigned int)this->a << std::endl;
    std::cout << "Register B: " << (unsigned int)this->b << std::endl;
    std::cout << "Register C: " << (unsigned int)this->c << std::endl;
    std::cout << "Register D: " << (unsigned int)this->d << std::endl;
    std::cout << "Register E: " << (unsigned int)this->e << std::endl;
    std::cout << "Register F: " << (unsigned int)this->f << std::endl;
    std::cout << "Register H: " << (unsigned int)this->h << std::endl;
    std::cout << "Register L: " << (unsigned int)this->l << std::endl;

    std::cout << std::endl << "16 bits registers" << std::endl;
    std::cout << "Register PC: " << (unsigned int)this->sp << std::endl;
    std::cout << "Register SP: " << (unsigned int)this->pc << std::endl;

    std::cout << std::endl << "Timers" << std::endl;
    std::cout << "Register M: " << (unsigned int)this->m << std::endl;
    std::cout << "Register T: " << (unsigned int)this->t << std::endl;

    std::cout << std::endl << "Clock" << std::endl;
    std::cout << "Clock M: " << (unsigned int)this->clock.m << std::endl;
    std::cout << "Clock T: " << (unsigned int)this->clock.t << std::endl;
}

void Z80::NOP(void) {
    this->m = 1;
    this->t = 4;
}

void Z80::ADD(uint8_t& reg1, uint8_t& reg2) {
    reg1 += reg2;
    this->f = 0;
    if(!(reg1 & 255))
        this->f |= 0x80;

    this->m = 1;
    this->t = 4;
}

void Z80::CPR(uint8_t& reg1, uint8_t& reg2) {
    uint8_t i = reg1;
    i -= reg2;
    this->f |= 0x40;
    if(!i & 255)
        this->f |= 0x80;
}


