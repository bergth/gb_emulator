 #include "carth.hh"
 
using namespace std;

 CartH::CartH(ifstream& _ifs): ifs(_ifs)
 {
	 fill_CartH();
 }


 void CartH::raw_print() const
 {
    cout.setf(ios::hex, ios::basefield);
   	cout << "Entry point       : " << "[" << hex << setfill('0') << setw(8) << static_cast<int>(entry_point) << "]" << endl;
	print_logo();
	cout << "Name: " << endl;
	cout << "Manufacturer Code : " << endl;
	cout << "CGB flag          : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(CGBf) 		<< dec << "]" << endl;
	cout << "New Licensee Code : " << "[" << hex << setfill('0') << setw(4) << static_cast<int>(NliCode) 		<< dec << "]" << endl;
	cout << "SGB Flag          : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(SGBf) 		<< dec << "]" << endl;
	cout << "Cartridge Type    : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(CARTt) 		<< dec << "]" << endl;
	cout << "ROM Size          : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(ROMs) 		<< dec << "]" << endl;
	cout << "RAM Size          : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(RAMs) 		<< dec << "]" << endl;
	cout << "Destination Code  : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(DESTc) 		<< dec << "]" << endl;
	cout << "Old Licensee Code : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(OliCode) 		<< dec << "]" << endl;
	cout << "Mask ROM V num    : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(MROMv)	<< dec << "]" << endl;
	cout << "Head Checksum     : " << "[" << hex << setfill('0') << setw(2) << static_cast<int>(HeadChecksum)	<< dec << "]" << endl;
	cout << "Global Checksum   : " << "[" << hex << setfill('0') << setw(4) << static_cast<int>(GlobCheckSum) << dec << "]" << endl;
	cout.unsetf(ios::hex);
 }

bool CartH::cmp_logo() const
{
	for(int i = 0; i < 48; i++)
	{
		if(logo[i] != logo_cmp[i])
			return false;
	}
	return true;
}

string CartH::get_name() const
{
	string str = "";
	for(size_t i = 0; i < 16; i++)
	{
		if(name[i] == 0)
			break;
		else
			str += name[i]; 
	}
	return str;
}


void CartH::fancy_print() const
{
	// logo
	cout << "Nintendo graphic: ";
	if(cmp_logo())
	{
		cout << "OK";
	}
	else
	{
		cout << "KO";
	}
	cout << endl;

	// Title
	cout << "Title of the game: " << get_name() << endl;

	// CGB Flag
	cout << "CGB Flag: ";
	if(CGBf == 0x80)
	{
		cout << "support GB and CGB" << endl;
	}
	else if(CGBf == 0xC0)
	{
		cout << "support CGB only" << endl;
	}
	else
	{
		cout << "support GB only" << endl;
	}

	// SGB Flag
	cout << "SGB Flag: ";
	if(SGBf == 0x00)
	{
		cout << "No SGB functions" << endl;
	}
	else if(SGBf == 0x03)
	{
		cout << "supports SGB functions" << endl;
	}
	else
	{
		cout << "??" << endl;
	}

	cout << "Cartridge type: " << get_ctype() << endl;
	cout << "ROM Size: " << get_rsize() << endl;
	cout << "RAM Size: " << get_rasize() << endl;
}

void CartH::print_logo() const
{
	cout << "*--------- logo model ---------*" << endl;
	useGB::print_tuint8(logo_cmp, 48, 16);
	cout << "*--------- logo readed ---------*" << endl;
	useGB::print_tuint8(logo, 48, 16);
}

void CartH::fill_CartH()
{
	if(!ifs.is_open())
	{
		cerr << "Error reading header: fs isn't open" << endl;
		exit(1);
	}
	
	
	// READ Entry
	entry_point = useGB::read32_ifs(ifs,SEEKGB_EP);
	// READ LOGO
	useGB::read_tuint8(ifs, SEEKGB_LOGO ,logo, 48);
	useGB::read_tuint8(ifs, SEEKGB_TITLE ,name, 16);
	useGB::read_tuint8(ifs, SEEKGB_TITLE ,manCode, 4);
	CGBf = useGB::read8_ifs(ifs,SEEKGB_CGBF);
	NliCode = useGB::read16_ifs(ifs,SEEKGB_NLIC);
	SGBf = useGB::read8_ifs(ifs,SEEKGB_SGBF);
	CARTt = useGB::read8_ifs(ifs,SEEKGB_CATY);
	ROMs = useGB::read8_ifs(ifs,SEEKGB_ROMS);
	RAMs = useGB::read8_ifs(ifs,SEEKGB_RAMS);
	DESTc = useGB::read8_ifs(ifs,SEEKGB_DESTCO);
	OliCode = useGB::read8_ifs(ifs,SEEKGB_OLIC);
	MROMv = useGB::read8_ifs(ifs,SEEKGB_MARO);
	HeadChecksum = useGB::read8_ifs(ifs,SEEKGB_HECH);
	GlobCheckSum = useGB::read8_ifs(ifs,SEEKGB_GOCH);
}

std::string CartH::get_ctype() const
{
	switch(CARTt)
	{
		case 0x00:
			return "ROM ONLY";
			break;
		case 0x01:
			return "MBC1";
		case 0x02:
			return "MBC1+RAM";
		case 0x03:
			return "MBC1+RAM+BATTERY";
			break;
		case 0x05:
			return "MBC2";
			break;
		case 0x06:
			return "MBC2+BATTERY";
			break;
		case 0x08:
			return "ROM+RAM";
			break;
		case 0x09:
			return "ROM+RAM+BATTERY";
			break;
		case 0x0B:
			return "MMM01";
			break;
		case 0x0C:
			return "MMM01+RAM";
			break;
		case 0x0D:
			return "MMM01+RAM+BATTERY";
			break;
		case 0x0F:
			return "MBC3+TIMER+BATTERY";
			break;
		case 0x10:
			return "MBC3+TIMER+RAM+BATTERY";
			break;
		case 0x11:
			return "MBC3";
			break;
		case 0x12:
			return "MBC3+RAM";
			break;
		case 0x13:
			return "MBC3+RAM+BATTERY";
			break;
		case 0x19:
			return "MBC5";
			break;
		case 0x1A:
			return "MBC5+RAM";
			break;
		case 0x1B:
			return "MBC5+RAM+BATTERY";
			break;
		case 0x1C:
			return "MBC5+RUMBLE";
			break;
		case 0x1D:
			return "MBC5+RUMBLE+RAM";
			break;
		case 0x1E:
			return "MBC5+RUMBLE+RAM+BATTERY";
			break;
		case 0x20:
			return "MBC6";
			break;
		case 0x22:
			return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
			break;
		case 0xFC:
			return "POCKET CAMERA";
			break;
		case 0xFD:
			return "BANDAI TAMA5";
			break;
		case 0xFE:
			return "HuC3";
			break;
		case 0xFF:
			return "HuC1+RAM+BATTERY";
			break;
		default:
			return "??";
			break;
	}
}

std::string CartH::get_rsize() const
{
	switch(ROMs)
	{
		case 0x00:
			return "32KByte (no ROM banking)";
			break;
		case 0x01:
			return "64KByte (4 banks)";
			break;
		case 0x02:
			return "128KByte (8 banks)";
			break;
		case 0x03:
			return "256KByte (16 banks)";
			break;
		case 0x04:
			return "512KByte (32 banks)";
			break;
		case 0x05:
			return "1MByte (64 banks)";
			break;
		case 0x06:
			return "2MByte (128 banks)";
			break;
		case 0x07:
			return "4MByte (256 banks)";
			break;
		case 0x08:
			return "8MByte (512 banks)";
			break;
		case 0x52:
			return "1.1MByte (72 banks)";
			break;
		case 0x53:
			return "1.2MByte (80 banks)";
			break;
		case 0x54:
			return "1.5MByte (96 banks)";
			break;
		default:
			return "??";
	}
}

std::string CartH::get_rasize() const
{
	switch(RAMs)
	{
		case 0x00:
			return "None";
			break;
		case 0x01:
			return "2 KBytes";
			break;
		case 0x02:
			return "8 Kbytes";
			break;
		case 0x03:
			return "32 KBytes (4 banks of 8KBytes each)";
			break;
		case 0x04:
			return "128 KBytes (16 banks of 8KBytes each)";
			break;
		case 0x05:
			return "64 KBytes (8 banks of 8KBytes each)";
			break;
		default:
			return "??";
	}
}
