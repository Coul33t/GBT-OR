#ifndef MMU_H
#define MMU_H

#include "common_includes.h"

class MMU
{
    public:
        MMU();
        virtual ~MMU();

        // Read 8 bits from addr
        uint8_t RB(uint16_t& addr);

        // Read 16 bits from addr
        uint16_t RW(uint16_t& addr);

        // Write 8 bits at addr
        void WB(uint16_t& addr, uint8_t& val);

        // Write 16 bits at addr
        void WW(uint16_t& addr, uint16_t& val);

    protected:
    private:
};

#endif // MMU_H
