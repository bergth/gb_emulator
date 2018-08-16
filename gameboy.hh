#include<iostream>
#include "cpu.hh"
#include "mem.hh"
#include "carth.hh"
#include "useGB.hh"

class Gameboy {
    friend class Debug;
    private:
        std::ifstream ifs;
        Cpu Gcpu;
        Mem Gmem;
        CartH Gcarth;
    public:
        Gameboy(const char* filename);
        ~Gameboy();
        void load_32k_rom();
        void create_test();
        void run();
};