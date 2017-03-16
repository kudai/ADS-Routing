#ifndef LIST_H															//Ifdef guards to prevent mutiple declarations of the same header file.
#define LIST_H

#include "Node.h"														//Included to use the Node class.

class List {															//Circular Doubly Linked List class declaration.
	public:
		Node *head;														//Pointer to head of the List.

	public:
		List() { head = nullptr;}										//Default constructor to set the head to null. Defined inline in the header file.

		Node* insertNode(Node *t, Node* min, bool createnew = true);	//Method to insert a node into the invoking List object. Will create a new Node object by default.
		List* deleteNode(Node *t, bool deletemem = true);				//Method to delete a node from the invoking List object. Will delete the Node object from memory by default.
		List* mergeLists(List* toappend);								//Method to merge the toappend List object to the invoking List object.
		List* Nullify();												//Method to return null if the head is null for a List object.
};

#endif