#include<cstdint>
#include<cstddef>
#include<iostream>
#include "useGB.hh"

class Mem {
    private:
        uint8_t* mem[256];
        void alloc(uint16_t addr);

        std::string get_cc(uint8_t val) const;
        std::string get_r16(uint8_t val, int n) const;
        std::string get_r8(uint8_t val) const;


        std::string get_opcode(uint16_t &addr) const;

        std::string get_opc_b00(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x000(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x001(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x010(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x011(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x100(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x101(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x110(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b00x111(uint8_t opc, uint16_t &addr) const;

        std::string get_opc_b01(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b10(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x000(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x001(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x010(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x011(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x100(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x101(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x110(uint8_t opc, uint16_t &addr) const;
        std::string get_opc_b11x111(uint8_t opc, uint16_t &addr) const;


        std::string get_CB(uint8_t opc) const;
        std::string get_n(uint8_t val) const; 
    public:
        Mem();
        ~Mem();
        void set_8bit(uint8_t val, uint16_t addr);
        uint8_t get_8bit(uint16_t addr) const;
        uint16_t get_16bit(uint16_t addr) const;
        void print_hex(uint16_t addr, size_t n) const;
        void print_dis(uint16_t addr, size_t n) const;
};