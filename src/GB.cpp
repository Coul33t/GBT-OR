#include "GB.h"

GB::GB() {
    //ctor
}

GB::~GB() {
    //dtor
}

// https://github.com/jgilchrist/gbemu/blob/master/src/util/files.cc
bool GB::read_cartridge(std::string path) {
    std::ifstream input(path, std::ios::binary|std::ios::ate);

    if (!input.is_open()) {
        std::cout << "ERROR: can't open binary file." << std::endl;
        return false;
    }

    std::ifstream::pos_type pos = input.tellg();
    size_t file_size = static_cast<size_t>(pos);

    std::vector<char> file_contents(file_size);

    input.seekg(0, std::ios::beg);
    input.read(&file_contents[0], pos);
    input.close();

    this->cart = std::vector<uint8_t>(file_contents.begin(), file_contents.end());
    return true;
}

void GB::output_cartridge_contents(void) {
    for (size_t i = 0; i < this->cart.size(); i++) {
        std::cout << i << " - 0x";
        if (this->cart[i] < 16)
            std::cout << "0";
        std::cout << std::hex <<(unsigned)(this->cart[i]) << std::dec << std::endl;
    }
}

bool GB::verifiy_instructions(void) {
    for (size_t i = 0; i < this->cart.size(); i++) {
        uint8_t instr = (uint8_t)this->cart[i];
        auto it = std::find_if(this->z80.implemented_opcodes.begin(),
                               this->z80.implemented_opcodes.end(),
                               [&instr](instruction instruct) {return instruct.op_code == instr;});
        if (it == this->z80.implemented_opcodes.end()) {
            std::cout << "ERROR: opcode " << std::hex << (unsigned)instr << " not implemented." << std::endl;
            return false;
        }
    }

    return true;
}
