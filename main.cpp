#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map>

#include "huffman.h"

typedef vector<bool> bitset;

using namespace std;

int main()
{
    string str = "abracadabra";

    vector<bool> code = encode_to_huffman(str);

    cout << "huffman('" << str << "') = ";
    for (vector<bool>::iterator it = code.begin(); it != code.end(); it++)
        cout << *it;
    cout << endl;      
    
    string origin = decode_huffman(code, build_tree(str));
    cout << "original string: " << origin << endl;
    
    return 0;
}

