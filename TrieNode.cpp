#include "TrieNode.h"															//Header file included for TrieNode class declaration.

TrieNode::TrieNode() {															//Constructor.
	left = nullptr;																//Set left to null.
	right = nullptr;															//Set right to null.
	data = -1;																	//Set data to -1.
}

TrieNode* TrieNode::create(int source, vector<string> ips, vector<int> prev) {	//Method to create tries for all vertices for the given source.
	int next;																	//Declare next as an integer to store the next hop.
	int vertices = ips.size();													//Set vertices to size of ips.
	TrieNode *root = this;														//Set root to the invoking TrieNode object.
	for(int i=0;i<vertices;i++) {												//Iterate over all vertices.
		if(i==source)															//If i is the same as source,
			continue;															//Continue.
		next = getNextHop(source, i, prev);										//Assign next to the next hop for the given source with i as destination.
		root->insert(ips[i], next);												//Insert a trie with IP of vertex i, using next as te data.
	}
	condense(root->left);														//Condense left trie.
	condense(root->right);														//Condense right trie. Done seperately to insure that the leaf node does not come to the root TrieNode.
	return root;																//Return the root.
}

void TrieNode::insert(string bin, int nexthop) {								//Method to insert using a 32 bit binary string as the IP and nexthop as the data.
	int i=0; 																	//Declare i and assign it to 0.
	bool bit;																	//Declare bit as bool.
	TrieNode *current = this;													//Declare and set current to the invoking TrieNode object.
	while(i<32) {																//Iterate until the 32 charatcer string is traversed.
		bit = bin[i++] - '0';													//Set bit to character at i of string bin.
		if(!bit && current->left==nullptr)										//If bit is false and left of current is null,
			current->left = new TrieNode();										//Initialize left of current to a new TrieNode.
		if(!bit)																//If bit is false,
			current = current->left;											//Set current to left of current.
		if(bit && current->right==nullptr)										//If bit is true and right of current is null,
			current->right = new TrieNode();									//Set right of current to a new TrieNode object.
		if(bit)																	//If bit is true, 
			current = current->right;											//Set current to right of current.
		if(i==32)																//If i is 32, i.e. the last bit has been traversed,
			current->data = nexthop;											//Set current's data to next.
	}
}

int TrieNode::getNextHop(int source, int dest, vector<int> prev) {				//Method to get next hop for source for the shortest path from source to destination.
	while(prev[dest]!=source) 													//Iterate until dest is not source.
		dest = prev[dest];														//Set dest to predecessor of dest.
	return dest;																//Return dest.
}

void TrieNode::condense(TrieNode *root) {										//Method to recursively condense the TrieNode.
	if(!root)																	//If root is null,
		return;																	//Return.
	if(root->left!=nullptr)														//If left of root isn't null,
		condense(root->left);													//Call condense on left of root.
	if(root->right!=nullptr)													//If right of root isn't null,
		condense(root->right);													//Call condense on right of root.
	if(root->left == nullptr || root->right==nullptr) {							//If either left or right of root is null,
		if(root->left && root->left->data!=-1) {								//If left of root isn't null and it's a leaf node (denoted) by a data which is not -1.
			root->data = root->left->data;										//Set data of root to data of left of root.
			delete root->left;													//Delete left of root.
			root->left = nullptr;												//Set root's left pointer to null.
		}
		else if(root->right && root->right->data!=-1) {							//If right of root isn't null and it's a leaf node (denoted) by a data which is not -1.
			root->data = root->right->data;										//Set data of root to data of right of root.
			delete root->right;													//Delete right of root.
			root->right = nullptr;												//Set root's right pointer to null.
		}
	}
	else if(root->left->data !=-1 && root->left->data == root->right->data) {	//Else if data of left of root is equal to data of right of root and neither are -1, i.e both are leaf nodes,
		root->data = root->left->data;											//Set data of root to data of left of root.
		delete root->left;														//Delete left of root.
		delete root->right;														//Delete right of root.
		root->left = nullptr;													//Set root's left pointer to null.
		root->right = nullptr;													//Set root's right pointer to null.
	}
}

int TrieNode::traverse(string bin) {											//Method to traverse the invoking TrieNode structure using the 32 bit binary tring passed as the parameter.
	int i=0;																	//Declare i and set it to 0.
	bool bit;																	//Declare bit as a bool.
	TrieNode *cur = this;														//Set cur to the invoking TrieNode object.
	while(cur->data==-1 && i<32) {												//Iterate until a leaf node is found or the string is completely traversed.
		bit=bin[i++] - '0';														//Set bit to character of string at i.
		cout<<bit;																//Display bit for traversal.
		if(bit)																	//If bin is true,
			cur = cur->right;													//Set cur to right of cur.
		else 																	//Else if bit is false,
			cur = cur->left;													//Set cur to left of cur.
	}
	return cur->data;															//Return data of cur.
}