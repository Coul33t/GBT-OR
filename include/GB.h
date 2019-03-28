#ifndef GB_H
#define GB_H

#include "common_includes.h"

#include <fstream>
#include <cstdlib>
#include <algorithm>

#include "Z80.h"
class GB
{
    public:
        GB();
        virtual ~GB();
        bool read_cartridge(std::string path);
        void output_cartridge_contents(void);
        bool verifiy_instructions(void);

        Z80 z80;
        std::vector<uint8_t> cart;
};

#endif // GB_H
