#ifndef MMU_H
#define MMU_H


class MMU
{
    public:
        MMU();
        virtual ~MMU();

        // Read 8 bits from addr
        void RB(uint16_t& addr);

        // Read 16 bits from addr
        void RW(uint16_t& addr);

        // Write 8 bits at addr
        void WB(uint16_t& addr, uint8_t& val);

        // Write 16 bits at addr
        void WW(uint16_t& addr, uint16_t& val);

    protected:
    private:
};

#endif // MMU_H
