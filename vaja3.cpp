#include "BinWriter.h"
#include "BinReader.h"
#include<iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <cmath>

using namespace std;
int stvue=0;
struct tabelaF{
	unsigned char c;
	unsigned long p = 0;
	vector<bool> bit;
};
tabelaF T[256];
tabelaF T2[256];//t2 uporabim pri zpaisu tabele, ker je T razvrscen po velikosti T2 pa ne

int vseh=0;

bool acompare(tabelaF n1, tabelaF n2) { return n1.p > n2.p; }


void shannonFano(int A, int B){
	cout << "Zacetek: A="<<A<<" B="<<B<<endl;

	if (A==B-1)//B-1 ker klicemo drektno z B in ne z B-1 kot na predavanjih
	{
		cout << "gremo vn"<<endl;
		return;
	}
	else{
		int sum=0, M=0, skupaj=0;
		double W = 0, ostanek = 0, prej=0;
		for (int i = A; i < B; ++i)
		{
			sum+=T[i].p;//sestejemo vse od A do B
		}

		W = (double)sum*0.5f;//delimo na pol
		prej = W;

		for (int i = A; i < B; ++i)
		{
			ostanek = abs(W-skupaj);//abs zato ker gremo lahko tudi cez in gre v - vazen je ostanek npr (mas 15 st, 12 je 3 ostanek 16 pa 1 ostanek ampak pri seznajst gres v -)
			cout <<"sum: "<< sum <<" W: " << W << " skupaj: " << skupaj <<" prej: " << prej << " Ostanek: "<< ostanek<<endl;
			if (ostanek <= prej)//prej je prejsna vrednost ostanka 
			{
				prej = ostanek;
				M = i;// index ki razpoljavla drevo
			}
			skupaj += T[i].p;
		}

		for (int i = A; i < B; ++i)
		{
			if (i < M)
			{
				T[i].bit.push_back(0);
				T2[T[i].c].bit.push_back(0);
			}
			else{
				T[i].bit.push_back(1);
				T2[T[i].c].bit.push_back(1);
			}
		}
		shannonFano(A, M);
		shannonFano(M,B);
	}


	/*if ((A+1) == B || A == B || A > B){
		if (A == B || A > B){
            return; 
		}

		T[A].bit.push_back(0);
		T2[T[A].c].bit.push_back(0);
      	T[B].bit.push_back(1);
      	T2[T[B].c].bit.push_back(1);
      	return;
	}
	else{
		float W=0;
		float sum1=0;
		float sum2=0;
		float diff1=0;
		float diff2=0;
		int i, d, k, j; 

		for (int i = A; i <= B-1; ++i)
		{
			sum1+= (float)T[i].p/vseh;
		}
		sum2 = sum2 + (float)T[B].p/vseh;

		diff1 = sum1 - sum2;

		if (diff1 < 0)
		{
			diff1 = diff1 * -1; 
		}
		j=2;

		while(j != B - A+1){
			k = B - j;
			sum1 = sum2 = 0;
			for (int i = A; i <= k; ++i)
			{
				sum1 = sum1 + (float)T[i].p/vseh;
			}
			for (int i = B; i > k; --i)
			{
				sum2 = sum2 + (float)T[i].p/vseh;
			}
			diff2 = sum1 - sum2;
			if (diff2 < 0) 
                diff2 = diff2 * -1; 
            if (diff2 >= diff1) 
                break; 
            diff1 = diff2; 
            j++; 
		}
		k++;
		
		for (int i = A; i <= k; ++i)
		{
			T[i].bit.push_back(0);
      		T2[T[i].c].bit.push_back(0);

		}
		for (int i = k+1; i <= B; ++i)
		{
			T[i].bit.push_back(1);
      		T2[T[i].c].bit.push_back(1);
		}


		shannonFano(A, k);
		shannonFano(k+1, B);

	}*/


	/*cout << "zacetekk              A: " << A << " B: " << B << endl;

	if (A == B) 
	{
		cout << "gremo vn" << endl;
		return;
	}
	else if( B - A == 1)
    {

		cout << "A: " << A << "B: " << B << endl;

     	T[A].bit.push_back(0);
		//T2[T[A].c].bit.push_back(0);


      	T[B].bit.push_back(1);
		//T2[T[B].c].bit.push_back(1);
    }
	else{
		float W=0;
		long sum=0;

		for (int i = A; i <= B; ++i)
		{
			sum+=T[i].p;
		}

		/*if(sum == 0){
			cout << "konccncncncnc A=" << A << " B=" << B << " B - A=" << B - A << endl;

			exit(0);
		}

		W = sum * 0.5f;

		cout <<"sum: "<< sum << " W: " << W << endl;

		long p = 0;
		int M = -1;

		for (int i = A; i <= B; ++i)
		{
			p += T[i].p;

			if (p <= W)
			{
				cout << "P: " << p << endl;
				T[i].bit.push_back(0);
				//T2[T[i].c].bit.push_back(0);
			}
			else{
				T[i].bit.push_back(1);
				//T2[T[i].c].bit.push_back(1);


				if( M < 0 ){
					M = i;
				}
			}

		}

		if (M < 0)
		{
			M = A+1;
		}


		cout << "A: " << A << " B: " << B << " M2:   " << M-1 <<endl;
		cout << endl;
		cout << endl;

		shannonFano(A, M-1);
		shannonFano(M, B);
	}

	for (int i = A; i <= B; ++i)
	{
		for (int j = 0; j < T[i].bit.size(); ++j)
		{
			cout << T[i].bit[j];
		}
		cout << endl;
	}*/

}	
 
void Encode(const char* dat){

	BinReader br(dat);
	int length = br.length();

	vseh = length;

	printf("Dolzina: %i\n", length);

	std::vector<unsigned char> v;

	for (int i = 0; i < length; i++)
	{
		v.push_back(br.ReadByte()); //zapisemo vse ckre v vetor
		//cout << v[i];
	}

	br.myfile.close();

	/*for (int i = 0; i < length; i++)
	{
		cout << v[i];
	}*/

	for (int i = 0; i < 256; ++i)
	{
		T[i].c = i;
		T2[i].c = i; //nastvimo crke
	}


	for (int i = 0; i < length; ++i)
	{
		T[v[i]].p++;
		T2[v[i]].p++; //prestejemo koliko je vsakih crk
	}


	std::sort(T, T+256, acompare);//sortiramo pov elikost katerih crk je najvec

	unsigned long n=0;

	for (int i = 0; i < 256; ++i)
	{
		if (T[i].p > 0)
		{
			n++; // koliko je unikatnih crk
		}
	}
	cout << endl;
	cout << "St zankov: " << n << endl;

	for (int i = 0; i < n; ++i)
	{
		cout << "st: " << T[i].p << " znak: " << (char)T[i].c << endl;
	}

	shannonFano(0, n);

	for (int i = 0; i < n; ++i)
	{
		cout << T[i].c << "  ";
		for (int j = 0; j < T[i].bit.size(); ++j)
		{
			cout  << T[i].bit[j];
		}
		cout << endl;
	}

	BinWriter out("out.bin");

	out.writeInt(length);//zapisemo dolzino besedila
	out.writeInt(n);//zapisemo st unikatnih znakov

	int steviloZapisanihBitov = 0;

	for (int i = 0; i < n; ++i)
	{
		out.writeInt((int)T[i].p);//zapisemo st znakov 16bitov

		out.writeInt((int)T[i].c);//zapisemo kater znak je ton 16bitov slika ne dela ce zapisujem kot 1 znak z 1 bytom

		steviloZapisanihBitov+=32;
	}

	int stevec = 0;

	for (int i = 0; i < length; ++i)
	{
		//cout << "bit size. " << T2[v[i]].bit.size() << endl;
		for (int j = 0; j < T2[v[i]].bit.size(); ++j)
		{
			//cout << T2[v[i]].bit[j];
			out.writeBit(T2[v[i]].bit[j]); //zapisujemo bite
			stevec++;
			steviloZapisanihBitov++;

			if (stevec == 8)
			{
				stevec = 0;
			}
		}
		//cout << endl;
	}
	if (stevec != 0)
	{
		for (int i = stevec; i < 8; ++i)
		{
			out.writeBit(0); // ce nakoncu ostane npr 1 bit sam se mu doda preostalo stevilo bitov v tem primeru imajo vrednost 0
			steviloZapisanihBitov++;	
		}

	}
	out.f.close();

	cout << endl;
	cout << "Kompresijsko razmerje: " << (float)(length*8)/steviloZapisanihBitov << endl;

}

void Decode(const char* dat){

	BinReader brx(dat);
	int znak=0, stevilo=0;

	int l = brx.length();
	cout << endl;

	for (int i = 0; i < 256; ++i)
	{
		T[i].c = i;
		T2[i].c = i; //nastvimo crke
	}

	//cout << "dolzina zapisa: "<< l << endl;

	int dolzina = brx.ReadInt();
	int stZnakov = brx.ReadInt();

	vseh = dolzina;

	cout << dolzina << endl;
	cout << stZnakov << endl;

	for (int i = 0; i < stZnakov; ++i)
	{
		stevilo = brx.ReadInt();
		znak = brx.ReadInt();

		cout << "st: " << stevilo << " znak: " << znak << endl;

		T[znak].p = stevilo;
		T2[znak].p = stevilo;
	}

	std::sort(T, T+256, acompare);

	for (int i = 0; i < stZnakov; ++i)
	{
		cout << T[i].c << " " << T[i].p << endl;
	}

	shannonFano(0, stZnakov);

	for (int i = 0; i < stZnakov; ++i)
	{
		cout << T[i].c << "  ";
		for (int j = 0; j < T[i].bit.size(); ++j)
		{
			cout  << T[i].bit[j];
		}
		cout << endl;
	}

	brx.ReadByte();
	vector<bool> pomozni;
	int stevecCrk=0;

	BinWriter out("out_d.bmp");//za sliko out_d.bmp

	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < 8; ++j){

			//std::cout << (bool)brx.ReadBit();
			pomozni.push_back((bool)brx.ReadBit());
			for (int y = 0; y < stZnakov; ++y)
			{
				if(pomozni == T[y].bit){
					out.writeByte(T[y].c);
					cout << T[y].c;
					pomozni.clear();
					stevecCrk++;
					if (stevecCrk == dolzina)
					{
						cout << endl;
						return;
					}
				}
			}
		}

	}
	out.f.close();

	brx.myfile.close();


}

int main(int argc, char const *argv[])
{
	const char* file;

	file = argv[2];

	if(strcmp(argv[1],"c") == 0){
      	Encode(file);
    }
    else if (strcmp(argv[1],"d") == 0) {
     	Decode(file);
    }
    else{
      std::cout << "Niste podali pravilnih argumentov !" << '\n';
      return 0;
    }

}