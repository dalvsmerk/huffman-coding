#include "huffman.h"

#include <queue>
#include <utility>
#include <iostream>
#include <iomanip>
#include <fstream>


// A node of Huffman Tree
HuffmanTree::HuffmanTree(char symbol, uint freq,
                         HuffmanTree* left, HuffmanTree* right)
{
    this->symbol = symbol;
    this->freq = freq;
    this->left = left;
    this->right = right;
}


HuffmanTree::~HuffmanTree()
{
    delete left;
    delete right;
}


/* Builds frequency table (symbol -> frequency).
 * 
 * @param str Input string.
 * @return Frequency table.
 */
map<char, uint> make_freq_table(string str)
{
    map<char, uint> freq_table;
    
    for (string::iterator it = str.begin(); it != str.end(); it++)
        freq_table[*it]++;
    
    return freq_table;
}


/* Builds frequency table using file stream
 * 
 * @param fin File stream.
 * @return Frequency table.
 */
map<char, uint> make_freq_table(ifstream& fin)
{
    map<char, uint> freq_table;
    
    while (true) {
        char c;
        fin >> c;
        
        freq_table[c]++;
        if ( fin.eof() ) break;
    }
    
    fin.seekg(0, ios_base::beg);
    
    return freq_table;
}


/* Builds Hffman Tree using frequency table
 * and priority queue.
 * 
 * @param freq_table Frequency table (symbol -> frequency).
 * @return Root of Huffman Tree.
 */
HuffmanTree* build_tree(map<char, uint> freq_table)
{
    priority_queue<HuffmanTree*, vector<HuffmanTree*>, HuffmanTree::Compare> trees;
    
    map<char, uint>::iterator it = freq_table.begin();
    
    for (; it != freq_table.end(); it++) {
        HuffmanTree* leaf = new HuffmanTree(it->first, it->second);
        trees.push(leaf);
    }
    
    HuffmanTree* node = nullptr;
    while ( trees.size() > 1 ) {
        HuffmanTree* left = trees.top();
        trees.pop();
        
        HuffmanTree* right = trees.top();
        trees.pop();
        
        node = new HuffmanTree(0, left->freq + right->freq, left, right);
        trees.push(node);
        
        node = nullptr;
    }
    
    return trees.top();
}


HuffmanTree* build_tree(const string& str) {
    return build_tree(make_freq_table(str));
}


/* Counts Huffman code for each symbol (leaf) in the tree
 * 
 * @param tree Root of Huffman tree.
 * @return Table containing (symbol -> it's code).
 */
map<char, bitset> count_codes(HuffmanTree* tree)
{
    map<char, bitset> code_table;
    deque<pair<HuffmanTree*, bitset>> q;
    
    q.push_back(make_pair(tree, bitset()));
    
    while ( !q.empty() ) {
        HuffmanTree* node  = nullptr;
        HuffmanTree* left  = nullptr;
        HuffmanTree* right = nullptr;
        
        node        = q.front().first;
        bitset code = q.front().second;
        
        q.pop_front();
        
        left = node->left;
        right = node->right;
        
        // if the node has any children
        // as Huffman tree is always full
        if (left) {
            code.push_back(0);
            q.push_back(make_pair(left, code));
            
            code.pop_back();
            
            code.push_back(1);
            q.push_back(make_pair(right, code));
        } else {
            code_table.insert(make_pair(node->symbol, code));
        }
    }
    
    
    return code_table;
}


/* Makes inorder tree traversal and outputs nodes in stdout.
 * 
 * @param tree Root of Huffman tree
 * @param indent Indent
 */
void tree_traversal(HuffmanTree* tree, uint indent)
{
    if (tree == nullptr)
        return;
    
    tree_traversal(tree->left, indent + 4);
    cout << setw(indent) << tree->symbol << ":" << tree->freq << endl;
    tree_traversal(tree->right, indent + 4);
}


/* Builds Huffman code for a string @str.
 *
 * @params str Input string.
 * @return Huffman code.
 */
bitset encode_to_huffman(std::string str)
{
    bitset code;
    
    map<char, uint> freq_table = make_freq_table(str);
    HuffmanTree* huff_tree = build_tree(freq_table);
    
    map<char, bitset> code_table = count_codes(huff_tree);
    
    tree_traversal(huff_tree, 0);
    
    // encoding each character of @str
    for (uint i = 0; i < str.length(); i++) {
        bitset c_code = code_table[str[i]];
        
        code.insert(code.end(), c_code.begin(), c_code.end());
    }
    
    delete huff_tree;
    huff_tree = nullptr;
    
    return code;
}


/* Decodes Huffman code to original string.
 * 
 * @param code Huffman code.
 * @param root Root of Huffman tree.
 * @return Original string.
 */
string decode_huffman(const bitset& code, HuffmanTree* root)
{
    string origin;
    
    HuffmanTree* curr_node = root;
        
    for (uint i = 0; i <= code.size(); i++) {            
        if (curr_node->symbol != 0) {
            origin += curr_node->symbol;
            curr_node = root;
            i--;
        } else {
            if (code[i] == 0) {
                curr_node = curr_node->left;
            } else {
                curr_node = curr_node->right;
            }
        }
    }
    
    return origin;
}


/* Encodes data from file stream @fin to @compressed_f.
 * 
 * @param input_f Input file stream.
 * @param compressed_f Output file stream.
 */
void encode_file(ifstream& input_f, ofstream& compressed_f)
{
        
}













