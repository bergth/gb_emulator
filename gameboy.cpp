#include "gameboy.hh"

using namespace std;

Gameboy::Gameboy(const char* filename): ifs(filename, ios::in | ios::binary), Gcarth(ifs)
{
    load_32k_rom();
}

Gameboy::~Gameboy() {}

void Gameboy::load_32k_rom()
{
    for(size_t i = 0; i < 32000; i++)
    {
        Gmem.set_8bit(useGB::read8_ifs(ifs,i),i);
    }
}

