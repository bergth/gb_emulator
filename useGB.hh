#ifndef USEGB_HH
#define USEGB_HH

#include<cstdint>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<vector>
#include<string>

namespace useGB {

	std::string str_uint8(const uint8_t& val);
	std::string str_uint16(const uint16_t& val);


	uint16_t str_uint16(std::string str);
	void print_tuint8(const uint8_t* tab, size_t size, size_t size_line);
	void read_tuint8(std::ifstream& ifs, uint32_t seek, uint8_t* tab, size_t size);


	uint8_t read8_ifs(std::ifstream& ifs, uint32_t seek);
	uint16_t read16_ifs(std::ifstream& ifs, uint32_t seek);
	uint32_t read32_ifs(std::ifstream& ifs, uint32_t seek);

	std::vector<std::string> str_split(std::string str);

	char hex_to_char(uint8_t c);
}

#endif