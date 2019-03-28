#include <iostream>
#include "GB.h"

// http://imrannazar.com/GameBoy-Emulation-in-JavaScript

int main()
{
    std::cout << "Hello world!" << std::endl << std::endl << std::endl;

    GB gb;
    std::string cartridge_path = "data\\rom_boot_test\\DMG_ROM.bin";
    gb.read_cartridge(cartridge_path);
    //gb.output_cartridge_contents();
    gb.verifiy_instructions();

    return 0;
}
