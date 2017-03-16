#include "Node.h"							//Header file included for Node class definition.

Node::Node() {								//Default constructor to initialize values for a new Node object.
	this->next = nullptr;
	this->prev = nullptr;
	this->parent = nullptr;
	this->child = nullptr;
	this->childcut = false;
	this->data = 0;
	this->degree = 0;
}

Node::Node(Node *copyfrom, Node* copyto) {	//Copy Constructor to copy data from one pointer to another.
	copyto->next = copyfrom->next;
	copyto->prev = copyfrom->prev;
	copyto->parent = copyfrom->parent;
	copyto->child = copyfrom->child;
	copyto->childcut = copyfrom->childcut;
	copyto->data = copyfrom->data;
	copyto->degree = copyfrom->degree;
}