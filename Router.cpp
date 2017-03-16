#include "Router.h"																				//Header file included for Router class declaration.

Router::Router(Graph *graph, vector<string> iplist, vector<int> prev, int source, int dest) {	//Constructor.
	g = graph;																					//Assign g to graph parameter.
	ips = iplist;																				//Assign ips to iplist vector.
	path = extractPath(source, dest, prev);														//Assign path to the extracted path.
}

vector<int> Router::extractPath(int source, int dest, vector<int> prev) {						//Method to extract path from the predecessor vector.
	vector<int> p;																				//Declare vector p for final path.
	while(dest!=source) {																		//Iterate until dest is the same as source.
		p.push_back(dest);																		//Push dest into p.
		dest = prev[dest];																		//Set dest to predecessor of dest.
	}
	p.push_back(source);																		//Push source into p.
	reverse(p.begin(), p.end());																//Reverse p to get the path.													
	return p;																					//Return p.
}

void Router::run(vector<int> sourcessp) {														//Method to construct tries for all vertices and display trie prefixes for path from source to destination.
	unordered_map<int, TrieNode*> tries;														//Declare a hashmap tries mapping vertex ID to the constructed trie for that vertex.
	typedef pair<int, TrieNode*> vertextrie;													//Define a pair of integer and TrieNode pointers called vertextrie.
	TrieNode *temp = new TrieNode();															//Declare temp and assign it to a new TrieNode object's pointer.
	int source = path[0];																		//Set source as first vertex in path.
	int dest = path[path.size()-1];																//Set destination last vertex in path.
	int vertices = sourcessp.size();															//Set vertex as size of predecessor vertex.
	temp = temp->create(source, ips, sourcessp);												//Set temp to the trie which has a constructed trie of all vertices for the source.
	tries.insert(vertextrie(source, temp));														//Insert source and temp as a vertextrie pair.
	for(int i=0;i<vertices;i++) {																//Iterate over all vertices.
		if(i==source)																			//If i is souce, 
			continue;																			//Continue.
		temp = new TrieNode();																	//Assign temp to a new TrieNode pointer.
		sourcessp = g->dijkstra(i, 0, false);													//Assign sourcessp to predecessor vector for source i.
		sourcessp.pop_back();																	//Pop the shortest distance from the 
		temp = temp->create(i, ips, sourcessp);													//Assign temp to the created tries of all vertices for  source as i.
		tries.insert(vertextrie(i, temp));														//Insert i and temp as a vertextrie pair.
	}
	int current = path[0];																		//Set current to source.
	while(current!= dest) {																		//Iterate until current is not destination.
		temp = tries.find(current)->second;														//Set temp to trie of current, as found from the tries hashmap.
		current = temp->traverse(ips[dest]);													//Set current to the next hop found from the trie traversal which also prints the traversal prefixes.
		cout<<" ";																				//Print a space to seperate the 
	}
}