#include "gameboy.hh"

using namespace std;

Gameboy::Gameboy(const char* filename): ifs(filename, ios::in | ios::binary), Gcarth(ifs)
{
    load_32k_rom();
    //create_test();
}

Gameboy::~Gameboy() {}

void Gameboy::load_32k_rom()
{
    for(size_t i = 0; i < 32000; i++)
    {
        Gmem.set_8bit(useGB::read8_ifs(ifs,i),i);
    }
}

void Gameboy::create_test()
{
	int j = 0;
	for(size_t i = 0; i <= 0xFF; i++)
	{
		Gmem.set_8bit(i,j++);
		Gmem.set_8bit(0,j++);
		Gmem.set_8bit(0,j++);
	}
}
