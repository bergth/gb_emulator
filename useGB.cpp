#include "useGB.hh"
using namespace std;

namespace useGB {


	std::string str_uint8(const uint8_t& val)
	{
		std::stringstream buffer;
		buffer << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(val) << std::dec;
		return buffer.str();
	}


	std::string str_uint16(const uint16_t& val)
	{
		std::stringstream buffer;
		buffer << std::hex << std::setfill('0') << std::setw(4) << static_cast<int>(val) << std::dec;
		return buffer.str();
	}


	void print_tuint8(const uint8_t* p, size_t size, size_t size_line)
	{
		for(size_t i = 0; i < size; i++)
		{
			cout << str_uint8(p[i]);
			if( (i+1) % size_line == 0)
			{
				cout << endl;
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	void read_tuint8(ifstream& ifs, uint32_t seek, uint8_t* tab, size_t size)
	{
		if(!ifs.seekg(seek))
		{
			cerr << "Error seek tab !" << endl;
			exit(1);
		}
		
		if(!ifs.read((char*)(tab), size))
		{
			cerr << "Error read tab !" << endl;
			exit(1);
		}
	}

	uint8_t read8_ifs(ifstream& ifs, uint32_t seek)
	{
		char res;
		if(!ifs.seekg(seek))
		{
			cerr << "Error seek !" << endl;
			exit(1);
		}

		if(!ifs.read(&res,1))
		{
			cerr << "Error read !" << endl;
			exit(1);
		}
		return (uint8_t)res;
	}
	
	uint16_t read16_ifs(ifstream& ifs, uint32_t seek)
	{
		uint16_t res;
		if(!ifs.seekg(seek))
		{
			cerr << "Error seek !" << endl;
			exit(1);
		}

		if(!ifs.read((char*)(&res),2))
		{
			cerr << "Error read !" << endl;
			exit(1);
		}
		return res;
	}
	
	uint32_t read32_ifs(ifstream& ifs, uint32_t seek)
	{
		uint32_t res;
		if(!ifs.seekg(seek))
		{
			cerr << "Error seek !" << endl;
			exit(1);
		}

		if(!ifs.read((char*)(&res),4))
		{
			cerr << "Error read !" << endl;
			exit(1);
		}
		return res;
	}

	std::vector<std::string> str_split(std::string str)
	{
		vector<string> vect;
		string tmp = "";
		for(size_t i = 0; i < str.size(); i++)
		{
			if(str[i] == ' ')
			{
				vect.push_back(tmp);
				tmp = "";
			}
			else
			{
				tmp += str[i];
			}
		}
		vect.push_back(tmp);
		return vect;
	}

	uint16_t str_uint16(std::string str)
	{
		uint16_t res = 0;
		cout << "[" << str << "]" << endl;
		for(size_t i = 0; i < str.size(); i++)
		{
			res *= 0x10;
			if(str[i] >= '0' && str[i] <= '9')
				res += str[i] - '0';
			else if(str[i] == 'A' || str[i] == 'a')
				res += 0xA;
			else if(str[i] == 'B' || str[i] == 'b')
				res += 0xB;
			else if(str[i] == 'C' || str[i] == 'c')
				res += 0xC;
			else if(str[i] == 'D' || str[i] == 'd')
				res += 0xD;
			else if(str[i] == 'E' || str[i] == 'e')
				res += 0xE;
			else if(str[i] == 'F' || str[i] == 'f')
				res += 0xF;
			else
			{
				cerr << "Error parsing hex" << endl;
				exit(1);
			}
		}
		return res;
	}

	char hex_to_char(uint8_t c)
	{
		if(c >= 0x20 && c <= 0x7E)
		{
			return (char)c;
		}
		else
		{
			return '.';
		}
	}

	uint16_t concat_uint8(uint8_t most, uint8_t	least)
	{
		uint16_t val = most;
		val = val << 8;
		val += least;
		return val;
	}
}


