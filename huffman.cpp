#include "huffman.h"

#include <queue>
#include <utility>
#include <iostream>
#include <iomanip>

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
		
		node		= q.front().first;
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
			
			// delete later
			cout << "(" << node->symbol << ", ";
			for (uint i = 0; i < code.size(); i++)
				cout << code[i];
			cout << ")" << endl;
		}
	}
	
	
	return code_table;
}


/* Makes inorder tree traversal and outputs nodes in stdout
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
	
	// a, b, r, d, c
	map<char, bitset> code_table = count_codes(huff_tree);
	
	map<char, bitset>::iterator it = code_table.begin();
	
	for (; it != code_table.end(); it++) {
		cout << it->first << endl;
		for (uint i = 0; i < it->second.size(); i++) {
			code.push_back(it->second[i]);
		}		
	}
	
	tree_traversal(huff_tree, 0);
	
	return code;
}
























