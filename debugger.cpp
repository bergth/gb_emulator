#include "debugger.hh"
#include "useGB.hh"
#include <iostream>


using namespace std;
using namespace useGB;

Debug::Debug(const char* filename): gb(filename)
{
    addr = 0x0;
    isRunning = false;
}

void Debug::run()
{
    isRunning = true;
    while(isRunning)
    {
        vector<string> cmd = get_cmd();
        if(cmd[0] == "exit" || cmd[0] == "quit")
        {
            isRunning = false;
        }
        else if(cmd[0] == "info")
        {
            info();
        }
        else if(cmd[0] == "finfo")
        {
            finfo();
        }
        else if(cmd[0] == "px")
        {
            gb.Gmem.print_hex(addr,16);
        }
        else if(cmd[0] == "pd")
        {
            gb.Gmem.print_dis(addr,100);
        }
        else if(cmd.size() == 2 && cmd[0] == "s")
        {
            addr = str_uint16(cmd[1]);
        }
        else
        {
            cout << "error cmd" << endl;
        }
    }
}

void Debug::info()
{
    gb.Gcarth.raw_print();
}

void Debug::finfo()
{
    gb.Gcarth.fancy_print();
}

vector<string> Debug::get_cmd()
{
    cout << "[0x" << str_uint16(addr) << "]> ";
    char cmd[256];
    cin.getline(cmd,256);
    return str_split(cmd);
}

