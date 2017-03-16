#ifndef ROUTER_H																				//Ifdef guards to prevent mutiple declarations of the same header file.
#define ROUTER_H

#include <iostream>																				//Including to print to standard output stream.
#include <string>																				//Including to use string containers.
#include <algorithm>																			//Including to access reverse function.

#include "Graph.h"																				//Including to access Graph objects.
#include "TrieNode.h"																			//including to access TrieNode objects.

using namespace std;																			//Set namespace to use string, reverse and cout without namespace prefixes.

class Router {																					//Declaration of Router class.
	public:
		Graph *g;																				//Graph g which stores the adjacency list and to run Dijkstra's algorithm.
		vector<string> ips;																		//Vector of strings which store 32 bit binary IPs
		vector<int> path;																		//Vector of integers which stores the path from source to destination.

	public:
		Router(Graph *graph, vector<string> iplist, vector<int> prev, int source, int dest);	//Constructor which takes the graph, the ips, the predecessor vector and souce and destination.
		vector<int> extractPath(int source, int dest, vector<int> prev);						//Method to extract the path from the predecessor vecctor using the source nd destination.
		void run(vector<int> sourcessp);														//Method to run the routing and display the prefixes of the Tries for the path to destination from source.
};

#endif