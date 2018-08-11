#include<cstdint>
#include<cstddef>
#include<vector>
#include<string>
#include "gameboy.hh"

class Debug
{
    private:
        Gameboy gb;
        uint16_t addr;
        bool isRunning;
        void info();
        void finfo();
    public:
        Debug(const char* filename);
        void run();
        std::vector<std::string> get_cmd();
};