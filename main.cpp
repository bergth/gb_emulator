#include <iostream>
#include "debugger.hh"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cerr << "Error nb param" << endl;
		return 1;
	}
	cout << "Hello GB emulator!" << endl;
	
	Debug db(argv[1]);
	db.run();

	cout << "Bye GB emulator!" << endl;
	return 0;
}
