#include <iostream>
#include <fstream>
using namespace std;

class BinWriter {
public:
	int k;
	ofstream f;
	char x;

	BinWriter(const char *p) : k(0) {
		f.open(p, ios::binary);
	}

	~BinWriter() {
		if (k > 0) writeByte(x);
		f.close();
	}

	void writeByte(char x) {
		//cout << " "; //<< x << " ";
		f.write((char*)&x, 1);
	}

	void writeBit(bool b) {

		x ^= (-b ^ x) & (1 << k);
		k++;
		if (k == 8) {
			//cout << x << endl;
			writeByte(x);
			k = 0;
		}
		//dau spodi, ker kaj ce imamo tocno 8 bitov ampak za zpais tega potrebujemo se 1 bit saj drugace ne bo zapisal ker je na zacetku if
	}
	void writeInt(int y) {
		f.write((char*)&y, 4);
	}
	void writeFloat(float y) {
		f.write((char*)&y, 4);
	}
};
