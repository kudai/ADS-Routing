#include "fHeap.h"																//Header file included for fHeap class declaration.

bool fHeap::isEmpty() {															//Method to check if fHeap is empty.
	if(minptr == nullptr)														//If minptr is null, the heap is empty, 
		return true;															//So return true.
	return false;																//Else return false.
}

Node* fHeap::insert(int key) {													//Method to insert key into the root List of fHeap.
	Node *in = new Node();														//Create a new Node object in.
	in->data = key;																//Set data of new Node object to key.
	Node* newnode = roots->insertNode(in, minptr);								//Insert in to the left of minptr in List roots and assign newnode to the returned inserted node.
	if(minptr == nullptr || newnode->data < minptr->data)						//If minptr is null or if the newnode data is less than the minptr data,
		minptr = newnode;														//Assign minptr to newnode.
	delete in;																	//Delete in.
	return newnode;																//Return newnode.
}

Node* fHeap::extractMin() {														//Method to extract the minimum element from fHeap's root List.
	if(minptr == nullptr)														//If minptr is nullptr i.e. the fHeap is empty,
		return nullptr;															//Return nullptr.
	else {																		//If fHeap has elements,
		Node *minimum = minptr;													//Store the minptr pointer to minimum.
		List *childrenofmin = roots->deleteNode(minptr);						//Delete the minptr from roots and assign childrenofmin to the children of the deleted node.
		if(roots->head == nullptr)												//If head of roots is null, i.e. roots is empty,			
			minptr=nullptr;														//Set minptr to null.
		if(childrenofmin!=nullptr) {											//If the deleted node has children,
			Node *temp = childrenofmin->head;									//Set temp to the head of the child List of the deleted Node.
			do {																//Iterate over the child List of the deleted Node.
				temp->parent = nullptr;											//Set parent of temp to null.
				temp->childcut = false;											//Set childcut to false since the temp will now go to roots List.
				temp = temp->next;												//Go to next child of child List of deleted Node.
			} while(temp!=childrenofmin->head);									//While temp does not go back to the head of the child List of the deleted Node.
			if(roots->head!=nullptr)											//If head of root is not null,
				roots = roots->mergeLists(childrenofmin);						//Merge the List of children of the deleted node with the roots List.
			else              													//Else,
				roots = childrenofmin;											//Set roots to child List of the deleted Node.
		}
		if(roots->head != nullptr && roots->head != roots->head->next)			//If roots has more than 1 Node
			this->pairwiseCombine();											//Pairwise combine the roots List.
		else if(roots->head != nullptr && roots->head == roots->head->next)		//If roots has exctly 1 Node,
			minptr = roots->head;												//Set minptr to that Node.
		return minimum;															//Return the pointer to the deleted minimum node.
	}
}

void fHeap::pairwiseCombine() {													//Method to pairwise combine the roots List.
	typedef pair<int, Node*> degreeptr;											//Define degreeptr as a pair of int and Node pointer.
	unordered_map<int, Node*> h_map;											//Define a hashmap h_map of an integer key (degree of Node) and pointer to the Node.
	unordered_map<int, Node*>::iterator it;										//Define an iterator it of h_map.
	bool flag = false;															//Set flag to false. Used to go back to the last node if it had another Node of the roots List became it's child.
	Node *current = roots->head;												//Set current Node pointer to head of the roots List.
	minptr = current;															//Set minptr to current.
	do {																		//Iterate until no Node in the roots List has the same degree as another node in the roots List.
		if(flag)		 														//If flag is true,
			current = current->prev;											//Set current to the previous node.
		if(minptr->data >= current->data)										//If minptr data is greater than or equal to current data,
			minptr = current;													//Set minptr to current.
		it = h_map.find(current->degree);										//Find pair which in h_map which has the same degree as current.
		if(it == h_map.end()) {													//If no Node in h_map has the same degree,
			h_map.insert(degreeptr(current->degree, current));					//Insert the current degree and the current pointer into h_map as a degreeptr pair.
			current = current->next;											//Go to next Node.
			flag = false;														//No need to go back to the previous Node in the next iteration so set flag to false.
		}
		else {																	//If a Node exists with the same degree as current in h_map,
			Node *samedegree = it->second;										//Set samedegree to the Node pointer which has the same degree as current as retrieved from h_map.
			Node* child_head;													//Declare child_head.
			if(samedegree == current) {											//If retrieved Node is the same as current,
				flag = false;													//Set flag to false so we do not go back to it.
				current=current->next;											//Go to next Node in the roots List.
				if(current == roots->head)										//If current is now head of roots, we have completely iterated over the roots List,
					break;														//So break.
				else 															//Else,
					continue;													//Go to begining of iteration for the next Node in the roots List.
			}
			else if(current->data > samedegree->data) {							//Else if current data is greater than samedegree data,
				if(minptr->data >= samedegree->data)							//If minptr of data is greater than or equal to samedegree data,
					minptr = samedegree;										//Set minptr to samedegree.
				if(samedegree->child!=nullptr)									//If child List of samedegree is not empty,
					child_head = samedegree->child->head;						//Set child_head to head of the child List of samedegree.
				else {															//Else if child List of samedegree is nullptr,
					samedegree->child = new List();								//Set child of samedegree to a new empty List.
					child_head = nullptr;										//Set child_head to nullptr.
				}
				roots->deleteNode(current, false);								//Delete current from roots List without deleting it's memory.
				samedegree->child->insertNode(current, child_head, false);		//Insert current into the child List of samedegree without allocating new memory. 
				samedegree->degree++;											//Increment degree of samedegree since we added a child to it's child List.
				current->parent = samedegree;									//Set parent of current to samedegree.
				h_map.erase(it);												//Remove the retrieved pair (degree of samedegree, pointer to samedegree) from h_map.
				current = samedegree;											//Set current bck to samedegree (a Node in the roots List).
			}
			else {																//Else if samedegree data is greater than current data,
				if(current->child!=nullptr)										//If child List of current is not empty,
					child_head = current->child->head;							//Set child_head to head of the child List of current.
				else {															//Else if child List of current is nullptr,
					current->child = new List();								//Set child of current to a new empty List.
					child_head = nullptr;										//Set child_head to nullptr.
				}
				roots->deleteNode(samedegree, false);							//Delete samedegree from roots List without deleting it's memory.
				current->child->insertNode(samedegree, child_head, false);		//Insert samedegree into the child List of current without allocating new memory. 
				current->degree++;												//Increment degree of current since we added a child to it's child List.
				samedegree->parent = current;									//Set parent of samedegree to current.
				h_map.erase(it);												//Remove the retrieved pair (degree of current, pointer to current) from h_map.
			}
			current = current->next;											//Go to next Node in the roots List.
			flag = true;														//Set flag to true to since we pairwise combined two nodes and want to go back to the same node to check if another Node in h_map has the same degree as the new Node.
		}
	} while(current != roots->head || (current==roots->head?flag==true:true)); 	//Iterate while the current Node is not heads of roots or if it is, and flag is true (which means we'll go back to the previous node).
}
	
bool fHeap::decreaseKey(Node* todecrease, int decreasekeyto) {					//Method to decrease the key of todecrease Node to decreasekeyto.
	if(decreasekeyto > todecrease->data)										//If decreasekeyto is greater than the data in todecrease Node,
		return false;															//Return false. Cannot increase key.
	else if(decreasekeyto == todecrease->data)									//If the todecrease data is the same as decreasekeyto,
		return true;															//Return true, since we don't need to do anything.
	todecrease->data = decreasekeyto;											//Set todecrease data to decreaseketo.
	Node* p = todecrease->parent;												//Set p to parent of todecrease.
	if(p!=nullptr && todecrease->data < p->data) {								//If parent isn't null and todecrease data is less than it's parent's data, i.e. min heap property the parent's heap is violated.
		cut(todecrease, p);														//Cut todecrease from it's parent and insert into roots list.
			cascadeCut(p);														//Go up and check again to see if min heap property is violated anywhere in the parents of the decreasedkey
	}
	if(todecrease->data < minptr->data)											//If minptr is data is less than todecrease data,
		minptr = todecrease;													//Set minptr to tpdecrease.
	return true;																//Return true for a successful decreaseKey operation.
}

void fHeap::cut(Node* cutnode, Node* cutfrom) {									//Method to cutnode Node from cutfrom Node's child List and insert into roots List.
	cutfrom->degree--;															//Decrease degree of cutfrom.
	cutfrom->child->deleteNode(cutnode, false);									//Delete cutnode from child List of cutfrom without clearing the memory.
	cutfrom->child = cutfrom->child->Nullify();									//Nullify the child List of cutfrom if it is empty.
	roots->insertNode(cutnode, roots->head, false);								//Insert cutnode into the roots List.
	cutnode->parent = nullptr;													//Set parent of cutnode to null.
}

void fHeap::cascadeCut(Node* tocut) {											//Method to recursively cut tocut and insert it into roots List.
	Node* p = tocut->parent;													//Set p to parent of tocut.
	if(p!=nullptr) {															//If p is not null,
		if(!tocut->childcut)													//If childcut of tocut Node is false,
			tocut->childcut = true;												//Set it to true.
		else {																	//If childcut of tocut was true,
			cut(tocut, p);														//Cut tocut from it's parent and insert it into the roots List.
			cascadeCut(p);														//Check the same thing for it's parent using a recursive call.
		}
	}
}