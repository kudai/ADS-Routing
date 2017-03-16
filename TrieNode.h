#ifndef TRIENODE_H																//Ifdef guards to prevent mutiple declarations of the same header file.
#define TRIENODE_H

#include <vector>																//Including to use vector containers because arrays need known space allocation and finding array sizes for returned pointers isn't possible.
#include <string>																//Including to use string containers.
#include <iostream>																//Including to print to standard output stream.

using namespace std;															//Set namespace to use string, vector and cout without namespace prefixes.

class TrieNode {																//Declaration of TrieNode class.
	public: 
		TrieNode* left;															//Pointer to left child of type TrieNode.
		TrieNode* right;														//Pointer to left child of type TrieNode.
		int data;																//Data stored in the TrieNode.

	public:
		TrieNode();																//Default constructor.
		TrieNode* create(int source, vector<string> ips, vector<int> prev);		//Method to create a Trie for source to 
		void insert(string bin, int nexthop);									//Method to insert nexhop as data in the invoking TrieNode using bin for traversal.
		int getNextHop(int source, int dest, vector<int> prev);					//Method to get next hop from the source of the the path from source to destination.
		void condense(TrieNode *root);											//Method to compress the TrieNode.
		int traverse(string bin);												//Method to traverse and print the traversal prefixes.
};

#endif