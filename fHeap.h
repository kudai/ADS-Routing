#ifndef FHEAP_H													//Ifdef guards to prevent mutiple declarations of the same header file.
#define FHEAP_H

#include <unordered_map>										//Including to use hashmaps for O(1) access.

#include "List.h"												//Including List class (which includes Node class) for the top level Circular Doubly Linked List (and Node class for the min pointer of the Fibonacci Heap).

using namespace std;											//Set namespace to use pair and unordered_map without namespace prefixes. 

class fHeap {													//Declaration of the Fibonacci Heap class.
	public:
		Node *minptr;											//Pointer to the minimum Node in the Fibonacci Heap class. This will always belong to the roots top level List object.
		List *roots; 											//Pointer to the top level Circular Doubly Linked List.

	public:
		fHeap() {												//Default Constructor.
			minptr = nullptr;									//Assign minptr to null.
			roots = new List();									//Create a new empty List and assign it to roots.
		}

		bool isEmpty();											//Method to check if the Fibonacci Heap is empty.
		Node* insert(int key);									//Method to insert key into roots.
		Node* extractMin();										//Method to extract the minptr from roots and remove it from the Fibonacci Heap.
		void pairwiseCombine();									//Method to pairwise combine the root list after extract min.
		bool decreaseKey(Node* todecrease, int decreasekeyto);	//Method to decrease key to decreasekeyto for Node todecrease.
		void cut(Node* cutnode, Node* cutfrom);					//Method to cut Node cutnode from the child List of cutfrom.
		void cascadeCut(Node* tocut);							//Method to recursively cut depending on the childcut flag of the tocut Node.
};

#endif