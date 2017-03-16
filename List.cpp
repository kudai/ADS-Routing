#include "List.h"												//Header file included for List class definition.

Node* List::insertNode(Node *t, Node* min, bool createnew) {	//Method: Insert Node object t to the left of the min Node in the invoking List class. 
	Node* temp;													//Create a new temp Node pointer.
	if(createnew) {												//If createnew is true, create a new Node object and assign it to temp.
		temp = new Node();
		Node(t, temp);
	}
	else {														//If createnew is false, copy over to be insterted node into temp instead of allocating new memory.
		temp = t;
		t->childcut = false;									//Since we're inserting an existing node from the Fibonacci Heap, the childcut will become false.
	}
	if(min == nullptr) {										//If min is null, the list is empty.
		min = temp;												//Set min to the inserted node.
		head = temp;											//Set head to the inserted node.
		temp->next = temp;										//Assign it's left point to itself.
		temp->prev = temp;										//Assign it's right point to itself.
	}
	else if(head == min) {										//If head is the same as min, insert to left of head.
		temp->next = head;										//Assign next of temp to head.
		temp->prev = head->prev;								//Assign previos of head to tail of the list (head->prev).
		head->prev->next = temp;								//Assign next of tail to temp.
		head->prev = temp;										//Assign previous of head to temp.
		head = temp;											//Make temp the new head.
	}
	else {														//When inserting in the middle of the invoking List object (to the left of the min).
		Node* minprev = min->prev;								//Initialize minprev as previous of the min.
		temp->prev = minprev;									//Assign previous of temp to minprev.
		temp->next = min;										//Assign next of temp to min.
		minprev->next = temp;									//Assign next of minprev to temp.
		min->prev = temp;										//Assign previous of min to temp.
	}
	return temp;												//Return the inserted node.
}

List* List::deleteNode(Node *t, bool deletemem) {				//Method: Delete object t from the invoking List class.
	if(t == nullptr)											//If t is null, nothing to do so return.
		return nullptr;
	else if(head == head->next) {								//If head is the same as next of head, there's only one element in the List.
		head = nullptr;											//So remove it by assigning head to null.
	}
	else {														//When deleting from the middle of the List, 
		Node *prevT = t->prev, *nextT = t->next;				//Assign prevT to previous of t, nextT to next of t.
		prevT->next = nextT;									//Assign next of prevT to nextT.
		nextT->prev = prevT;									//Assign previous of nextT to prevT.
		if(t == head)											//If the deleted node is the head,
			head = nextT;										//Set head to the next node.
	}
	List *childlist = t->child;									//Get the child List of the deleted node.
	if(deletemem)												//If deletemem  is true, 
		delete t;												//Delete the node.
	return childlist;											//Return the child List object of the deleted node.
}
	
List* List::mergeLists(List* toappend) {						//Merge the toappend object to the invoking List object.
	if(toappend == nullptr)										//If toappend is null,
		return this;											//Return the invoking List
	Node* tail = head->prev;									//Assign tail to last Node of invoking List object (previous of head).
	Node* toappendtail = toappend->head->prev;					//Assign toappendtail to last Node of toappend List object.
	tail->next = toappend->head;								//Assign next of tail to head of toappend.
	head->prev = toappendtail;									//Assign previous of head of invoking List object to toappendtail.
	toappend->head->prev = tail;								//Assign previous of head of toappend to tail.
	toappendtail->next = head;									//Assign next of toappendtail to head.
	return this;												//Return the invokking list object which has been appended with the toappend List object.
}

List* List::Nullify() {											//Return null for an invoking List which has a null head.
	if(head==nullptr)											//If head is null,
		return nullptr;											//Return null.
	else return this;											//Else return invoking List object.
}
