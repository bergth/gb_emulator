#include"mem.hh"

using namespace std;

Mem::Mem()
{
    for(size_t i = 0; i < 255; i++)
    {
        mem[i] = nullptr;
    }
}

Mem::~Mem()
{
    for(size_t i = 0; i < 255; i++)
    {
        delete[] mem[i];
    }
}


void Mem::alloc(uint16_t addr)
{
    uint8_t i = (addr >> 2*4);
    if(mem[i] == nullptr)
    {
        mem[i] = new uint8_t[256];
        for(size_t j = 0; j < 256; j++)
        {
            mem[i][j] = 0x1;
        }
    }
}


uint8_t Mem::get_8bit(uint16_t addr) const
{
    uint8_t i = (addr >> 2*4);
    if(mem[i] == nullptr)
    {
        return 0x0;
    }
    uint8_t j = addr;
    return mem[i][j];
}


uint16_t Mem::get_16bit(uint16_t addr) const
{
    if(addr == 0xFFFF)
    {
        return 0;
    }
    uint16_t res = 0;
    res = (get_8bit(addr + 1) << 8);
    res += get_8bit(addr);
    return res;
}


void Mem::set_8bit(uint8_t val, uint16_t addr)
{
    uint8_t i = (addr >> 2*4);
    if(mem[i] == nullptr)
    {
        alloc(addr);
    }
    uint8_t j = addr;
    mem[i][j] = val;
}

void Mem::print_hex(uint16_t addr, size_t n) const
{
    cout << "       0- 1- 2- 3- 4- 5- 6- 7- 8- 9- A- B- C- D- E- F-   │  0123456789ABCDEF" << endl;
    for(size_t i = 0; i < n; i++)
    {
        cout << " " << useGB::str_uint16(addr + i * 0x10);
        cout << ": ";
        for(size_t j = 0x0; j <= 0xF; j++)
        {
            uint8_t val = get_8bit(addr + i * 0x10 + j);
            cout << useGB::str_uint8(val) << " ";
        }
        cout << "  │  ";
        for(size_t j = 0x0; j <= 0xF; j++)
        {
            uint8_t val = get_8bit(addr + i * 0x10 + j);
            cout << useGB::hex_to_char(val);
        }
        cout << endl;
    }
}


string Mem::get_opcode(uint16_t &addr) const
{
    string str = "";
    uint8_t opc = get_8bit(addr);
    uint8_t mask = (opc & 0b11000000) >> 6;  
    switch(mask)
    {
        case 0b00:
            return get_opc_b00(opc,addr);
            break;
        case 0b01:
            return get_opc_b01(opc,addr);
            break;
        case 0b10:
            return get_opc_b10(opc,addr);
            break;
        case 0b11:
            return get_opc_b11(opc,addr);
            break;
    }
    return "??";
}

void Mem::print_dis(uint16_t addr, size_t n) const
{
    for(size_t i = 0; i < n; i++)
    {
        uint8_t opc = get_8bit(addr);
        uint16_t last_addr = addr;
        string res = get_opcode(addr);
        int diff = addr - last_addr;
        if(diff == 0)
        {
            cerr << "Error: index addr not incremented" << endl;
            exit(EXIT_FAILURE);
        }
        string hex = "";
        if(diff == 1)
        {
            hex = useGB::str_uint8(opc) + "      ";
        }
        else if(diff == 2)
        {
            hex = useGB::str_uint8(opc) + " " + useGB::str_uint8(get_8bit(last_addr + 1)) + "   ";
        }
        else if(diff == 3)
        {
            hex = useGB::str_uint8(opc) + " " + useGB::str_uint8(get_8bit(last_addr + 1)) + " " + useGB::str_uint8(get_8bit(last_addr + 2));
        }
        else
        {
            cerr << diff << endl;
            cerr << "Error: index addr incremented more than 3 times: " <<  useGB::str_uint16(last_addr) << ":" <<  res << endl;
            exit(0);
        }
        cout << " " << useGB::str_uint16(last_addr) << " │ " << hex << " │ " << res << endl;
    }
}

std::string Mem::get_cc(uint8_t val) const
{
    val &= 0b00000011;
    switch(val)
    {
        case 0b00:
            return "NZ";
        case 0b01:
            return "Z";
        case 0b10:
            return "NC";
        case 0b11:
            return "C";
        default:
            cerr << "verif param get_cc" << endl;
            exit(0);
    }
}

std::string Mem::get_v81(uint8_t val) const
{
    val &= 0b00000111;
    if(val == 0b000)
    {
        return "B";
    }
    else if(val == 0b001)
    {
        return "C";
    }
    else if(val == 0b010)
    {
        return "D";
    }
    else if(val == 0b011)
    {
        return "E";
    }
    else if(val == 0b100)
    {
        return "H";
    }
    else if(val == 0b101)
    {
        return "L";
    }
    else if(val == 0b110)
    {
        return "(HL)";
    }
    else
    {
        return "A";
    }
}

std::string Mem::get_v82(uint8_t val) const
{
    val &= 0b00000011;
    if(val == 0b00)
        return "(BC)";
    else if(val == 0b01)
        return "(DE)";
    else if(val == 0b10)
        return "(HL+)";
    else
        return "(HL-)";
}

std::string Mem::get_v161(uint8_t val) const
{
    val &= 0b00000011;
    if(val == 0b00)
        return "BC";
    else if(val == 0b01)
        return "DE";
    else if(val == 0b10)
        return "HL";
    else
        return "SP";
}

std::string Mem::get_v162(uint8_t val) const
{
    val &= 0b00000011;
    if(val == 0b00)
        return "BC";
    else if(val == 0b01)
        return "DE";
    else if(val == 0b10)
        return "HL";
    else
        return "AF";
}

std::string Mem::get_ALU(uint8_t val) const
{
    val &= 0b00000111;
    if(val == 0b000)
        return "ADD A,";
    else if(val == 0b001)
        return "ADC A,";
    else if(val == 0b010)
        return "SUB A,";
    else if(val == 0b011)
        return "SBC A,";
    else if(val == 0b100)
        return "AND A,";
    else if(val == 0b101)
        return "XOR A,";
    else if(val == 0b110)
        return "OR A,";
    else
        return "CP A,";
}

std::string Mem::get_n(uint8_t val) const
{
    return to_string(val);
}

std::string Mem::get_opc_b00(uint8_t opc, uint16_t &addr) const
{
    uint8_t mask = opc & 0b00000111;
    switch(mask)
    {
        case 0b000:
            return get_opc_b00x000(opc, addr);
            break;
        case 0b001:
            return get_opc_b00x001(opc,addr);
            break;
        case 0b010:
            return get_opc_b00x010(opc,addr);
            break;
        case 0b011:
            return get_opc_b00x011(opc,addr);
            break;
        case 0b100:
            return get_opc_b00x100(opc,addr);
            break;
        case 0b101:
            return get_opc_b00x101(opc,addr);
            break;
        case 0b110:
            return get_opc_b00x110(opc,addr);
            break;
        case 0b111:
            return get_opc_b00x111(opc,addr);
            break;
        default:
            addr++;
            return "?? (0x00)";
            break;
    }
}

std::string Mem::get_opc_b00x000(uint8_t opc, uint16_t &addr) const
{
    uint8_t mask = (opc & 0b00111000) >> 3;
    string tmp = "";
    if(mask == 0b000)
    {
        addr++;
        return "NOP";
    }
    if(mask == 0b010)
    {
        addr += 2;
        return "STOP 0";
    }
    if(mask == 0b001)
    {
        tmp = "LD (" + useGB::str_uint16(get_16bit(addr + 1)) + "),SP";
        addr += 3;
        return tmp;
    }
    if(mask == 0b011)
    {
        tmp = "JR " + useGB::str_uint8(get_8bit(addr +1));
        addr += 2;
        return tmp;
    }
    if((mask & 0b100) == 0b100)
    {
        tmp = "JR " + get_cc(mask) + "," + useGB::str_uint8(get_8bit(addr +1));
        addr += 2;
        return tmp;
    }
    addr++;
    return "?? (0b00x000)";
}

std::string Mem::get_opc_b00x001(uint8_t opc, uint16_t &addr) const
{
    uint8_t mask = (opc & 0b00001000) >> 3;
    if(!mask)
    {
        string tmp = "LD " + get_v162(opc >> 4) + "," + useGB::str_uint16(get_16bit(addr + 1));
        addr += 3;
        return tmp;
    }
    else
    {
        addr++;
        return "ADD HL," + get_v162(opc >> 4);
    }
}

std::string Mem::get_opc_b00x010(uint8_t opc, uint16_t &addr) const
{
    uint8_t mask = (opc & 0b00001000) >> 3;
    addr++;

    if(!mask)
    {
        return "LD " + get_v82(opc >> 4) + ",A";
    }
    else
    {
        return "LD A," + get_v82(opc >> 4);
    }
}

std::string Mem::get_opc_b00x011(uint8_t opc, uint16_t &addr) const
{
    uint8_t mask = (opc & 0b00001000) >> 3;
    if(!mask)
    {
        addr++;
        return "INC " + get_v162(opc >> 4);
    }
    else
    {
        addr++;
        return "DEC " + get_v162(opc >> 4);
    }
}

std::string Mem::get_opc_b00x100(uint8_t opc, uint16_t &addr) const
{
    addr++;
    return "INC " + get_v81(opc >> 3);
}

std::string Mem::get_opc_b00x101(uint8_t opc, uint16_t &addr) const
{
    addr++;
    return "DEC " + get_v81(opc >> 3);
}

std::string Mem::get_opc_b00x110(uint8_t opc, uint16_t &addr) const
{
    string tmp = "";
    tmp = "LD " + get_v81(opc >> 3) + "," + useGB::str_uint8(get_8bit(addr+1));
    addr += 2;
    return tmp;
}

std::string Mem::get_opc_b00x111(uint8_t opc, uint16_t &addr) const
{
    string tmp = "";
    switch(opc)
    {
        case 0x07:
            tmp = "RLCA";
            break;
        case 0x17:
            tmp = "RLA";
            break;
        case 0x27:
            tmp = "DAA";
            break;
        case 0x37:
            tmp = "SCF";
            break;
        case 0x0F:
            tmp = "RRCA";
            break;
        case 0x1F:
            tmp = "RRA";
            break;
        case 0x2F:
            tmp = "CPL";
            break;
        case 0x3F:
            tmp = "CCF";
    }
    addr++;
    return tmp;
}

std::string Mem::get_opc_b01(uint8_t opc, uint16_t &addr) const
{
    if(opc == 0x76)
    {
        addr++;
        return "HALT";
    }
    else
    {
        string tmp = "LD " + get_v81(opc >> 3) + "," + get_v81(opc);
        addr++;
        return tmp;
    }
}

std::string Mem::get_opc_b10(uint8_t opc, uint16_t &addr) const
{
    uint8_t mask = (opc & 0b00111000) >> 3;
    string tmp = get_ALU(mask) + get_v81(opc);
    addr++;
    return tmp;
}

std::string Mem::get_opc_b11(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = opc & 0b00000111;
    switch(val)
    {
        case 0b000:
            return get_opc_b11x000(opc,addr);
        case 0b001:
            return get_opc_b11x001(opc,addr);
        case 0b010:
            return get_opc_b11x010(opc,addr);
        case 0b011:
            return get_opc_b11x011(opc,addr);
        case 0b100:
            return get_opc_b11x100(opc,addr);
        case 0b101:
            return get_opc_b11x101(opc,addr);
        case 0b110:
            return get_opc_b11x110(opc,addr);
        case 0b111:
            return get_opc_b11x111(opc,addr);
        default:
            addr++;
            return "??";
    }
}

std::string Mem::get_opc_b11x000(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = (opc & 0b00111000) >> 3;
    if(val >> 2 == 0)
    {
        addr++;
        return "RET " + get_cc(val & 0b011);
    }
    else
    {
        uint8_t val2 = val & 0b011;
        uint8_t param = get_8bit(addr + 1);
        switch(val2)
        {
            case 0b00:
                addr += 2;
                return "LDH (" + useGB::str_uint8(param) + "), A";
            case 0b10:
                addr += 2;
                return "LDH A, (" + useGB::str_uint8(param) + ")";
            case 0b01:
                addr += 2;
                return "ADD SP, " + useGB::str_uint8(param);
            case 0b11:
                addr += 2;
                return "LD HL, SP + " + useGB::str_uint8(param);
            default:
                addr += 1;
                return "??";
        }
    }
}

std::string Mem::get_opc_b11x001(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = (opc & 0b00111000) >> 3;
    addr++;
    if((val & 0b001) == 0)
    {
        return "POP " + get_v161((val & 0b110) >> 1);
    }
    else
    {
        if(val == 0b001)
        {
            return "RET";
        }
        else if(val == 0b011)
        {
            return "RETI";
        }
        else if(val == 0b101)
        {
            return "JP (HL)";
        }
        else if(val == 0b111)
        {
            return "LD SP,HL";
        }
        else
        {
            return "??";
        }
    }
}

std::string Mem::get_opc_b11x010(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = (opc & 0b00111000) >> 3;
    if(val >> 2 == 0)
    {
        uint16_t val16 = get_16bit(addr+1);
        addr += 3;
        return "JP " + get_cc(val & 0b011) + "," + useGB::str_uint16(val16);
    }
    else
    {
        if(val == 0b100)
        {
            addr++;
            return "LD (C),A";
        }
        else if(val == 0b110)
        {   
            addr++;
            return "LD A,(C)";
        }
        else if(val == 0b101)
        {
            uint16_t val = get_16bit(addr+1);
            addr += 3;
            return "LD ("+ useGB::str_uint16(val) + "),A";
        }
        else if(val == 0b111)
        {
            uint16_t val = get_16bit(addr+1);
            addr += 3;
            return "LD A,("+ useGB::str_uint16(val) + ")";
        }
        else
        {
            addr++;
            return "??";
        }
    }
}

std::string Mem::get_opc_b11x011(uint8_t opc, uint16_t &addr) const 
{
    uint8_t val = (opc & 0b00111000) >> 3;
    if(val == 0b000)
    {
        uint16_t param = get_16bit(addr+1);
        addr += 3;
        return "JP " + useGB::str_uint16(param);
    }
    else if(val == 0b110)
    {
        addr++;
        return "DI";
    }
    else if(val == 0b001)
    {
        string pcb = get_CB(get_8bit(addr + 1));
        addr += 2;
        return pcb;
    }
    else if(val == 0b111)
    {
        addr++;
        return "EI";
    }
    else
    {
        addr++;
        return "??";
    }
}

std::string Mem::get_opc_b11x100(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = (opc & 0b00111000) >> 3;
    if((val >> 2) == 0)
    {
        string a16 = useGB::str_uint16(get_16bit(addr + 1));
        addr += 3;
        return "CALL " + get_cc(val) + "," + a16;
    }
    else
    {
        addr++;
        return "??";
    }
}

std::string Mem::get_opc_b11x101(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = (opc & 0b00111000) >> 3;
    if((val & 0b001) == 0)
    {
        addr += 1;
        return "PUSH " + get_v162(val >> 1);
    }
    else
    {
        if(val == 0b001)
        {
            uint16_t param = get_16bit(addr + 1);
            addr += 3;
            return "CALL " + useGB::str_uint16(param);
        }
        else
        {
            addr++;
            return "??";
        }
    }
}

std::string Mem::get_opc_b11x110(uint8_t opc, uint16_t &addr) const
{
    string param = useGB::str_uint8(get_8bit(addr + 1));
    uint8_t val = (opc & 0b00111000) >> 3;
    if(val == 0b000)
    {
        addr += 2;
        return "ADD A," + param;
    }
    if(val == 0b001)
    {
        addr += 2;
        return "ADC A," + param;
    }    
    if(val == 0b010)
    {
        addr += 2;
        return "SUB A," + param;
    }   
    if(val == 0b011)
    {
        addr += 2;
        return "SBC A," + param;
    }    
    if(val == 0b100)
    {
        addr += 2;
        return "AND A," + param;
    }
    if(val == 0b101)
    {
        addr += 2;
        return "XOR A," + param;
    }
    if(val == 0b110)
    {
        addr += 2;
        return "OR A," + param;
    }
        if(val == 0b111)
    {
        addr += 2;
        return "CP A," + param;
    }
    else
    {
        addr += 1;
        return "??";
    }
}

std::string Mem::get_opc_b11x111(uint8_t opc, uint16_t &addr) const
{
    uint8_t val = (opc & 0b00111000) >> 3;
    addr++;
    string tmp = "";
    switch(val)
    {
        case 0b000:
            tmp = "00h";
            break;
        case 0b001:
            tmp = "08h";
            break;
        case 0b010:
            tmp = "10h";
            break;
        case 0b011:
            tmp = "18h";
            break;
        case 0b100:
            tmp = "20h";
            break;
        case 0b101:
            tmp = "28h";
            break;
        case 0b110:
            tmp = "30h";
            break;
        case 0b111:
            tmp = "38h";
            break;
        default:
            tmp = "??";
            break;
    }
    return "RST " + tmp;
}

std::string Mem::get_CB(uint8_t opc) const
{
    uint8_t val = opc >> 6;
    if(val == 0b00)
    {
        uint8_t val2 = (val & 0b00111000) >> 3;
        string flag = "";
        switch(val2)
        {
            case 0:
                flag = "RLC";
                break;
            case 1:
                flag = "RRC";
                break;
            case 2:
                flag = "RL";
                break;
            case 3:
                flag = "RR";
                break;
            case 4:
                flag = "SLA";
                break;
            case 5:
                flag = "SRA";
                break;
            case 6:
                flag = "SWAP";
                break;
            case 7:
                flag = "SRL";
                break;
            default:
                flag = "??";
                break;
        }
        flag += " " + get_v81(val & 0b00000111);
        return flag;
    }
    else if(val == 0b01)
    {
        uint8_t n = (val & 0b00111000) >> 3;
        uint8_t r8 = val & 0b00000111;
        return "BIT " + get_n(n) + "," + get_v81(r8);
    }
    else if(val == 0b10)
    {
        uint8_t n = (val & 0b00111000) >> 3;
        uint8_t r8 = val & 0b00000111;
        return "RES " + get_n(n) + "," + get_v81(r8);
    }
    else if(val == 0b11)
    {
        uint8_t n = (val & 0b00111000) >> 3;
        uint8_t r8 = val & 0b00000111;
        return "SET " + get_n(n) + "," + get_v81(r8);
    }
    return "??";
}

