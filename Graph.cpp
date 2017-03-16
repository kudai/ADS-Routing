#include "Graph.h"															//Header file included for Graph class declaration.

void Graph::insert(int row, int column, int weight) {						//Method to insert into the adjacency list.
	adjlist_it it = adjlist.find(row);										//Find iterator which has the row as key.
	if(it==adjlist.end()) {													//If row does not exist,
		unordered_map<int, int> n;											//Create a new hashmap n of a pair of ints.
		n.insert(edge(column, weight));										//Insert column and weight as edge pair into n.
		adjlist.insert(neighbours(row, n));									//Insert row and n into adjlist as a neighbours pair.
	}
	else 																	//If row exists in the adjlist hashmap,
		it->second.insert(edge(column, weight));							//Insert column and weight as an edge pair into the hashmap of the row key in adjlist.
}

vector<int> Graph::dijkstra(int source, int dest, bool hasdest) {			//Method to run Dijkstra's algorithm on the adjacency list using the source and destination parameters if hasdest (has destination) is true. If not, it runs to find the shortest path for all vertices from the source node.
	typedef pair<int, unsigned long long> vertexdist;						//Define vertexdist as a pair of int (predecessor) and unsigned long long (distance).
	typedef pair<Node*, int> Qpair;											//Define Qpair as a pair of Node pointers (of the Fibonacci Heap) and int (vertex ID).
	typedef pair<int, Node*> Qpairrev;										//Define Qpairrev as a pair of int (vertex ID) and Node pointers.
	adjlist_it it;															//Define it as an iterator of adjlist_it defined in Graph.h.
	neighbours_it it2;														//Define it2 as an iterator of neighbours_it defined in Graph.h.
	vertexdist *path = (vertexdist*)malloc((sizeof(vertexdist))*vertices);	//Declare and allocate path as an array of vertexdist with as many elements as vertices.
	unordered_map<Node*, int> Qmap;											//Declare Qmap as a hashmap of Node pointer (of the Fibonacci Heap) and int (vertex ID).
	unordered_map<Node*, int>::iterator Qmapit;								//Declare Qmapit as an iterator of the Qmap hashmap.
	unordered_map<int, Node*> Qmaprev;										//Declare Qmaprev as a hashmap of int (vertex ID) and Node pointer (of the Fibonacci Heap). This is a reverse mapping of Qmap.
	unordered_map<int, Node*>::iterator Qmaprevit;							//Declare Qmaprevit as an iterator of the Qmaprev hashmap.
	fHeap Q;																//Declare Q (a minimum priority queue) as an object of the fHeap.
	Node *current, *temp;													//Declare current and temp Node pointers.
	int i, u;																//Declare ints i and u.
	unsigned long long alt;
	for(i=0;i<vertices;i++)													//Iterate over all vertices,
		path[i] = vertexdist(-1, LLONG_MAX);								//Set each vertexdist in path as pair (-1, LLONG_MAX).
	path[source] = vertexdist(-1, 0);										//Set path of source as vertexdist pair (-1, 0).
	current = Q.insert(0);													//Insert source into Q and set current to the Node pointer it is inserted into.
	Qmaprev.insert(Qpairrev(source, current));								//Insert source and current (it's Node pointer) into Qmaprev.
	Qmap.insert(Qpair(current, source));									//Insert current (source's Node pointer) and source into Qmap.
	while(!Q.isEmpty()) {													//Iterate until Q is empty.
		current = Q.extractMin();											//Extract the minimum Node from Q.
		Qmapit = Qmap.find(current);										//Set Qmapit to the iterator which has the Node pointer as it's key in Qmap.
		u = Qmapit->second;													//Set u to the vertex ID of the retrieved Node pointer.
		Qmap.erase(Qmapit);													//Remove this pair from Qmap.
		Qmaprev.erase(u);													//Remove this pair from Qmaprev as well.
		if(hasdest && u==dest)												//If hasdest is true, i.e. we're running Dijkstra's for a particular destination, and the minimum extracted from Q is the destination,
			break;															//Break the loop. We have found our answer.
		it = adjlist.find(u);												//Find the hashmap which has the neighbours of u.
		for(it2=it->second.begin();it2!=it->second.end();it2++) {			//Iterate over those neighbours.
			alt=path[u].second + it2->second;								//Set alt to the sum of the distance of u stored so far and the edge weight of the neighbour of u.
			if(alt<path[it2->first].second) {								//If alt is less than distance of the neighbour vertex sstored in path,
				path[it2->first]=vertexdist(u, alt);						//Set path of neighbour vertex to vertexdist pair (u, alt).
				Qmaprevit = Qmaprev.find(it2->first);						//Set Qmaprevit to the pair with the node of the neighbour vertex and it's vertex ID.
				if(Qmaprevit==Qmaprev.end()) {								//If it does not exist in Qmaprev, i.e. It is not in Q.
					temp = Q.insert(alt);									//Insert alt into Q and set temp to the returned Node which was created in Q for alt.
					Qmap.insert(Qpair(temp, it2->first));					//Insert temp and the neighbour vertex as a Qpair into Qmap.
					Qmaprev.insert(Qpairrev(it2->first, temp));				//Insert the neighbour vertex and temp as a Qpair into Qmaprev.
				}
				else {														//If it exists in Qmaprev, i.e. it exists in Q.
					temp = Qmaprevit->second;								//Set temp to the Node pointer of the neighbour vertex in Q found from Qmaprev.
					Q.decreaseKey(temp, alt);								//Decrease key of temp Node to alt.
				}
			}
		}
	}
	vector<int> shortestpath;												//Declare vector shortestpath.
	if(hasdest) {															//If hasdest is true,
		if(path[dest].first==-1)											//If path of destination has redecessor of -1,
			return shortestpath;											//Return because this means there is no path.
		cout<<path[dest].second<<endl;										//Print the total distance from source to destination.
		u = dest;															//Set u to destination.
		stack<int> pathrev;													//Declare an integer stack pathrev.
		while(u!=source){													//Iterate until u is the source.
			pathrev.push(u);												//Push u into stack.
			u = path[u].first;												//Set u to predecessor of u for the shortest path.
		}
		pathrev.push(source);												//Push source into pathrev.
		while(!pathrev.empty()) {											//Iterate until stack is empty.
			cout<<pathrev.top()<<" ";										//Print the path starting with source.
			pathrev.pop();													//Remove the top element from pathrev.
		}
	}
	else {																	//If Dijkstra's had no destination,
		for(i=0;i<vertices;i++)												//Itterate over the vertices,
			shortestpath.push_back(path[i].first);							//And push predecessors of each vertex into shortestpath.
		shortestpath.push_back(path[dest].second);							//Push the distance from source to destination into shortest path.
	}
	return shortestpath;													//Return the shortestpath vector (which has the predecessors of all vertices) and the computed distance from source to destination.
}