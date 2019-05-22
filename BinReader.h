#include <iostream>
#include <fstream>
using namespace std;

class BinReader
{
public:
	std::ifstream myfile;
	int k;
	char x;

	BinReader(const char* pot) : k(0){
		myfile.open(pot, ios::binary);
	}
	char ReadByte(){
		myfile.read((char*)&x, 1);
		return x;
	}
	bool ReadBit(){
		if(k==8){
			ReadByte();
			k=0;
		}
		bool tF = (x >> k) & 1;

		k++;
		return tF;
	}
	int ReadInt(){
		int y;
		myfile.read((char*)&y, 4);
		return y;
	}
	float ReadFloat(){
		float y;
		myfile.read((char*)&y, 4);
		return y;
	}

	int length(){
		myfile.seekg (0, myfile.end);
	    int l = myfile.tellg();
	    myfile.seekg (0, myfile.beg);

	    return l;
	}
		
};

