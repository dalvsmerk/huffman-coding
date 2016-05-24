#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <map>
#include <string>

using namespace std;

typedef bool			bit;
typedef vector<bool>	bitset;
typedef unsigned long	uint;


class HuffmanTree
{
public:
	char symbol;
	uint freq;

	HuffmanTree* left;
	HuffmanTree* right;

	HuffmanTree(char symbol, uint freq,
				HuffmanTree* left=nullptr,
				HuffmanTree* right=nullptr);
	~HuffmanTree();
	
	class Compare {
	public:
		bool operator () (HuffmanTree* a, HuffmanTree* b)
		{
			return a->freq >= b->freq;
		}
	};
};

bitset encode_to_huffman(string str);
string decode_huffman(bitset code);

#endif // HUFFMAN_H
