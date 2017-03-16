#ifndef NODE_H								//Ifdef guards to prevent mutiple declarations of the same header file.
#define NODE_H

#include <cstddef>							//Included to use nullptr.

class List; 								//Forward declaration of List class which will be a child object of the Node class.

class Node { 								//Node class declaration.
	public:
		Node *next; 						//Next Node pointer.
		Node *prev; 						//Previous Node pointer.
		Node *parent;						//Parent Node pointer.
		List *child;						//Child List pointer.
		bool childcut;						//childcut flag - defaults to false and for the root list nodes.
		int data;							//Value for the fibonacci heap.
		int degree;							//Number of children in it's child List.

	public:
		Node();								//Constructor to initialize default values.
		Node(Node *copyfrom, Node *copyto); //Copy constructor.
};

#endif