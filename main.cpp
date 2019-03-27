#include <iostream>
#include "Z80.h"

int main()
{
    std::cout << "Hello world!" << std::endl << std::endl << std::endl;

    Z80 z80;
    z80.a = 0x01;
    z80.b = 0x02;
    z80.print_registers();
    z80.CPR(z80.a, z80.b);
    z80.print_registers();

    return 0;
}
