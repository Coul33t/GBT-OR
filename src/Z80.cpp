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

// OPCODE 06
void Z80::LDBn() {

    this->m = 2;
    this->t = 8;
}

// OPCODE 21
void Z80::LDHLnn() {
    this->reg.hl = this->mmu.RW(this->reg.pc);
    this->reg.pc += 2;
    this->m = 3;
    this->t = 12;
}

// OPCODE 31
void Z80::LDSPnn() {
    this->reg.sp = this->mmu.RW(this->reg.pc);
    this->reg.pc += 2;
    this->m = 3;
    this->t = 12;
}

// OPCODE 9F
void Z80::SBCAA() {
    this->reg.a -= this->reg.a;

    if (check_underflow(this->reg.a, this->reg.a - (this->reg.f & FLAG_C)))
        this->reg.f |= FLAG_C;

    this->reg.a -= (this->reg.f & FLAG_C)?1:0;

    if (!(this->reg.a & 255))
        this->reg.f |= FLAG_Z;

    this->reg.f |= FLAG_N;
    this->reg.f |= FLAG_Z;

    this->m = 1;
    this->t = 4;
}

// OPCODE AF
void Z80::XORA() {
    this->reg.a ^= this->reg.a;
    this->reg.f = 0x00;
    if(!(this->reg.a & 255))
        this->reg.f |= FLAG_Z;

    this->m = 1;
    this->t = 4;
}

//OPCODE FE
void Z80::CPn() {
    uint8_t i = this->reg.a;
    if(check_underflow(i, this->mmu.RB(this->reg.pc)))
        this->reg.f |= FLAG_C;

    i -= this->mmu.RB(this->reg.pc);

    if (!(i & 255))
        this->reg.f |= FLAG_Z;

    this->m = 2;
    this->t = 8;
}

// OPCODE FF
void Z80::RST38() {
    this->reg.sp -= 2;
    this->mmu.WW(this->reg.sp, this->reg.pc);
    this->reg.pc = 0x38;
    this->m = 8;
    this->t = 32;
}

void Z80::set_implemented_opcodes(void) {
    this->implemented_opcodes.push_back(instruction((uint8_t)0x00, std::string("NOP"), (void*)&Z80::NOP));

    //this->implemented_opcodes.push_back(instruction((uint8_t)0x06, std::string("LDBn"), (void*)&Z80::LDBn));

    this->implemented_opcodes.push_back(instruction((uint8_t)0x21, std::string("LD_HL_nn"), (void*)&Z80::LDHLnn));
    this->implemented_opcodes.push_back(instruction((uint8_t)0x31, std::string("LD_SP_nn"), (void*)&Z80::LDSPnn));
    this->implemented_opcodes.push_back(instruction((uint8_t)0x9F, std::string("SBC_A_A"), (void*)&Z80::SBCAA));
    this->implemented_opcodes.push_back(instruction((uint8_t)0xAF, std::string("XOR_A"), (void*)&Z80::XORA));
    this->implemented_opcodes.push_back(instruction((uint8_t)0xFE, std::string("CP_n"), (void*)&Z80::CPn));
    this->implemented_opcodes.push_back(instruction((uint8_t)0xFF, std::string("RST_38"), (void*)&Z80::RST38));
}

