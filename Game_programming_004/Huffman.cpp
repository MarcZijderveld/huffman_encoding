#include "Huffman.h"


/*TODO:: Make a compress file store all the bits and store the freq en character...
TODO:: make a decompress file where you get all the freq and characters
*/

using namespace std;
using namespace v;

vector<node> nodeArray;// Use nodeArray to record all the nodes that may be created in the whole process
vector<char>characters, uCharacters;
vector<charNode*> charNodes;
vector<charNode*> decompressedNodes;

Huffman::Huffman(void)
{
}

Huffman::~Huffman(void)
{
}



void Huffman::BFS(node * temproot, string s)
{
	node * root1 = new node;
	root1 = temproot;

	root1->code = s;
	if (root1 == NULL)
	{

	}
	else if (root1->leftChild == NULL && root1->rightChild == NULL)
	{
		cout << "the content is " << root1->content << endl;
		cout << "and its corresponding code is " << root1->code << endl;
		const char *newCode = root1->code.c_str();
		charNode* node = new charNode();

		node->frequency = root1->frequency;
		node->content = root1->content[0];
		strcpy(node->code, root1->code.c_str());

		charNodes.push_back(node);
	}
	else
	{
		root1->leftChild->code = s.append("0");
		s.erase(s.end() - 1);
		root1->rightChild->code = s.append("1");
		s.erase(s.end() - 1);
		BFS(root1->leftChild, s.append("0"));
		s.erase(s.end() - 1);
		BFS(root1->rightChild, s.append("1"));
		s.erase(s.end() - 1);
	}
}

node Huffman::extractMin()
{
	double temp = (double)INT_MAX;
	vector<node>::iterator i1, pos;
	for (i1 = nodeArray.begin(); i1 != nodeArray.end(); i1++){

		if (temp > (*i1).frequency){
			pos = i1;
			temp = (*i1).frequency;
		}
	}

	node tempNode = (*pos);
	nodeArray.erase(pos);

	return tempNode;
}

node Huffman::getHuffmanTree()
{
	while (!nodeArray.empty())
	{
		node * tempNode = new node;
		node * tempNode1 = new node;
		node * tempNode2 = new node;
		*tempNode1 = extractMin();
		*tempNode2 = extractMin();
		tempNode->leftChild = tempNode1;
		tempNode->rightChild = tempNode2;
		tempNode->frequency = tempNode1->frequency + tempNode2->frequency;
		nodeArray.push_back(*tempNode);
		if (nodeArray.size() == 1)//only the root node exsits
		{
			break;
		}
	}

	return nodeArray[0];
}

void Huffman::compressFile(node* root)
{
	std::ofstream huffmanDataStream;
	charNode temp;
	huffmanDataStream.open("data/Compressed.BIN", ios::out | ios::binary);
	for (int i = 0; i < charNodes.size(); i++)
	{
		temp = *charNodes[i];
		huffmanDataStream.write((char *)&temp, sizeof(charNode));
	}

	huffmanDataStream.close();
}

void Huffman::getHuffmanCode(int size, string text)
{
	double tempDouble;
	string tempString = "";

	cout << "Total number of Characters " << size << endl;

	for (vector<char>::const_iterator i = uCharacters.begin(); i != uCharacters.end(); ++i)
	{
		node tempNode;
		tempString = *i;
		tempDouble = retunCount(text, *i);

		tempNode.frequency = tempDouble;
		tempNode.content = tempString;
		tempNode.leftChild = NULL;
		tempNode.rightChild = NULL;
		nodeArray.push_back(tempNode);
	}

	node root = getHuffmanTree();

	BFS(&root, "");

	nodeArray.push_back(root);

	compressFile(&root);
	ToBinary(text);
}

void Huffman::ToBinary(string text)
{
	string total;
	for (int i = 0; i < text.size(); i++)
	{
		for (int j = 0; j < charNodes.size(); j++)
		{
			if (text[i] == charNodes[j]->content)
			{
				total += charNodes[j]->code;
			}
		}
	}
	char chars[1000];
	strcpy(chars, total.c_str());

	std::ofstream huffmanDataStream;
	charNode temp;
	huffmanDataStream.open("data/BinaryLine.BIN", ios::out | ios::binary);

	huffmanDataStream.write((char *)&chars, sizeof(char)* 1000);

	huffmanDataStream.close();

}

void Huffman::uniqueCharacters(string text)
{
	string newText = "";
	
	for (unsigned int i = 0; i < text.length(); i++){
		if (newText.find(text[i]) == std::string::npos){
			newText += text[i];
		}
	}

	for (unsigned int i = 0; i < newText.length(); i++){
		uCharacters.push_back(newText[i]);
	}
}

string retunText(string text)
{
	string yourText = "";
	yourText += text;

	return yourText;
}

void Huffman::CompressToBinary(string text)
{
	string wholeText;
	char my_character;

	for (int i = 0; i < text.size() + 1; i++)
	{
		my_character = text[i];
		characters.push_back(my_character);
		wholeText += my_character;
		cout << "char = " << my_character << endl;
	}

	characters.pop_back();
	wholeText.pop_back();

	getchar();

	uniqueCharacters(wholeText);
}

string binaryText;

void  Huffman::uncompressLine()
{
	std::ifstream huffmanDataStream;

	huffmanDataStream.open("Data/BinaryLine.BIN", ios::in | ios::binary);
	char test[1000];

	huffmanDataStream.read((char *)&test, sizeof(char) * 1000);	

	huffmanDataStream.close();

	binaryText = test;
}


void Huffman::OpenFile(string a_file)
{
	std::ifstream huffmanDataStream;

	huffmanDataStream.open("Data/Compressed.BIN", ios::in | ios::binary);
	for (int i = 0; i < 1000; i++)
	{
		charNode temp;
		huffmanDataStream.read((char *)&temp, sizeof(charNode));
		decompressedNodes.push_back(new charNode(temp));

		if (i > 0)
		{
			if (decompressedNodes[i]->content == decompressedNodes[i - 1]->content)
			{
				decompressedNodes.pop_back();
				break;
			}
		}
	}

	huffmanDataStream.close();

	uncompressLine();

	Decompress(binaryText);
}

string fullText = "";

void Huffman::Decompress(string text)
{
	string temp;

	for (int i = 0; i < text.size(); i++)
	{
		temp += text[i];

		for (int j = 0; j < decompressedNodes.size(); j++)
		{
			if (temp == decompressedNodes[j]->code)
			{
				char temp2 = decompressedNodes[j]->content;
				fullText = fullText + temp2;
				temp.clear();
				break;
			}
		}
	}

	cout << fullText << endl;
}

double Huffman::retunCount(string text, char a_Char){

	double count = 0;

	for (unsigned int i = 0; i < text.size(); i++){
		if (text[i] == a_Char) count++;
	}

	return count;
}