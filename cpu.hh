#include<cstdint>

class Cpu{
	private:
		uint16_t AF;
		uint16_t BC;
		uint16_t DE;
		uint16_t HL;
		uint16_t SP;
		uint16_t PC;
		uint8_t flag;

		// 8 bit loads
		// ld_r8_n
		// r8 = A,B,C,D,E,H,L
		// n = 8 bits value
		

	public:
		Cpu();
		uint16_t get_reg16(uint8_t r16, int n);
		uint8_t get_reg8(uint8_t r8);
		uint16_t set_reg16(uint8_t r16, int n, uint16_t val);
		uint8_t set_reg8(uint8_t r8, uint8_t val);
		uint16_t get_SP();
		uint16_t get_PC();
		bool get_FZ();
		bool get_FN();
		bool get_FH();
		bool get_FC();
		void set_FZ(bool val);
		void set_FN(bool val);
		void set_FH(bool val);
		void set_FC(bool val);
};
