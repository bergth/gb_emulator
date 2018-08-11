#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdint>
#include<string>
#include "useGB.hh"

#define SEEKGB_EP		0x100
#define SEEKGB_LOGO 	0x104
#define SEEKGB_TITLE	0x134
#define SEEKGB_MANCO	0x13F
#define SEEKGB_CGBF		0x143
#define	SEEKGB_NLIC		0x144
#define SEEKGB_SGBF		0X146
#define SEEKGB_CATY		0x147
#define SEEKGB_ROMS		0x148
#define SEEKGB_RAMS		0x149
#define SEEKGB_DESTCO	0x14A
#define SEEKGB_OLIC		0x14B
#define SEEKGB_MARO		0x14C
#define SEEKGB_HECH		0x14D
#define SEEKGB_GOCH		0x14E



class CartH{
	private:
	
		std::ifstream& ifs;
	
		const uint8_t logo_cmp[48] = { 	0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
										0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
										0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

		uint32_t entry_point; 	// 0x100-0x103 Entry point
		uint8_t logo[48]; 		// 0x104-0x133 Logo
		uint8_t name[16];		// 0x134-(0x13E / 0x143)
		uint8_t manCode[4];		// 0x13F - 0x142
		uint8_t CGBf;			// 0x143
		uint16_t NliCode;		// 0x144 - 0x145
		uint8_t SGBf;			// 0x146
		uint8_t CARTt;			// 0x147
		uint8_t ROMs;			// 0x148
		uint8_t RAMs;			// 0x149
		uint8_t DESTc;			// 0x14A
		uint8_t OliCode;		// 0x14B
		uint8_t MROMv;			// 0x14C
		uint8_t HeadChecksum;	// 0x14D
		uint16_t GlobCheckSum;	// 0x14E - 0x14F


		void print_logo() const;
		void print_char(uint n) const;
		void fill_CartH();
		bool cmp_logo() const;
		std::string get_name() const;
		std::string get_ctype() const;
		std::string get_rsize() const;
		std::string get_rasize() const;
	public:
		CartH(std::ifstream& _ifs);
		void raw_print() const;
		void fancy_print() const;
};
