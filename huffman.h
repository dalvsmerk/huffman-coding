#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <map>
#include <string>
#include <fstream>

using namespace std;

typedef bool            bit;
typedef vector<bool>    bitset;
typedef unsigned long    uint;


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

HuffmanTree* build_tree(const string& str);

bitset encode_to_huffman(string str);
string decode_huffman(const bitset& code, HuffmanTree* tree);

void encode_file(ifstream& input_f, ofstream& compressed_f);

#endif // HUFFMAN_H
