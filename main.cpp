#include <iostream>
#include <string>
#include <vector>

#include "huffman.h"

using namespace std;

int main()
{
	string str = "abracadabra";

	vector<bool> code = encode_to_huffman(str);

	cout << "huffman('" << str << "') = ";
	for (vector<bool>::iterator it = code.begin(); it != code.end(); it++)
		cout << *it;

	cout << endl;


	return 0;
}

