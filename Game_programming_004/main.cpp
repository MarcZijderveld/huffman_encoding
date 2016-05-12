//Huffman Encoding
#include<iostream>
#include "Huffman.h"

using namespace std;
using namespace v;

bool run = true;
Huffman* huff;
string name;
char t;

void Load()
{
	cout << "Decompressed name:" << endl;
	huff->OpenFile("data/compressed");
	
	cout << "" << endl;
	cout << "Done? (Y/N) " << endl;
	cin >> t;

	if (t == 'y'){
		run = !run;
	}
}

void Compress()
{
	cout << "Enter your name" << endl;
	cin >> name;

	while (run)
	{
		huff->CompressToBinary(name);
		huff->getHuffmanCode(name.size(), name);

		cout << "" << endl;
		cout << "Done? (Y/N) " << endl;
		cin >> t;

		if (t == 'y'){
			run = !run;
		}
	}
}

int main()
{
	cout << "Compress or Load? (c/l) " << endl;
	cin >> t;

	if (t == 'c')
	{
		Compress();
	}
	else if (t == 'l')
	{
		Load();
	}
	else
	{
		main();
	}

	return 0;
}

