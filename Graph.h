#ifndef GRAPH_H																	//Ifdef guards to prevent mutiple declarations of the same header file.
#define GRAPH_H

#include <stack>																//Including Stack.
#include <climits>																//Including clmits for max value of data types.												
#include <cstdlib>																//Including for access to malloc.
#include <iostream>																//Including to print to standard output stream.
#include <unordered_map>														//Including to use hashmaps for O(1) access.								
#include <vector>																//Including to use vector containers because arrays need known space allocation and finding array sizes for returned pointers isn't possible.

#include "fHeap.h"		

using namespace std;															//Set namespace to use pair, vector and unordered_map without namespace prefixes. 

typedef pair<int, int> edge;													//Define edge as a pair of ints.
typedef pair<int, unordered_map<int, int>> neighbours;							//Define neighbours hashmap as a pair of int and a hashmap of a pair of ints.
typedef unordered_map<int, unordered_map<int, int>>::iterator adjlist_it;		//Define adjlist_it as an iterator of adjlist hashmap (defined as a member of Graph.
typedef unordered_map<int, int>::iterator neighbours_it;						//Define neighbours_it as an iterator of the neighbours hashmap.

class Graph {																	//Declaration of Graph class.
	public:
		int vertices;															//Number of vertices.
		unsigned long long edges;												//Number of edges.
		unordered_map<int, unordered_map<int, int>> adjlist;					//Adjacency List of the graph stored as a hashmap of first vertex which has a hashmap of second vertex and edge weight.

	public:
		Graph() {																//Default constructor.
			vertices = 0;														//Set vertics to 0.
			edges = 0;															//Set edges to 0.
		}

		void insert(int row, int column, int weight);							//Method to insert into the adjacency list.
		vector<int> dijkstra(int source, int dest = -1, bool hasdest = true);	//Method to run Dijkstra's algorithm. 
};

#endif