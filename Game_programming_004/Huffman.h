#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

namespace v {
	
	struct node 
	{
		node* leftChild;
		node* rightChild;
		int frequency;
		string content;
		string code;
	};

	struct charNode
	{
		char code[10];
		char content;
		int frequency;
	};

	class Huffman {
	public:
	
		Huffman(void);
		~Huffman(void);

		//for the nodes
		void BFS(node * temproot,string s);
		node extractMin();
		node getHuffmanTree();
		void getHuffmanCode(int size, string text);
		double retunCount(string text, char a_Char);
		void ToBinary(string text);
		//Get file , set File
		void OpenFile(string file);
		void uniqueCharacters(string text);
		void uncompressLine();
		void compressFile(node* root);
		void CompressToBinary(string text);
		void Decompress(string);
	private:
		//vectors
		vector<int> test;

	};
};

