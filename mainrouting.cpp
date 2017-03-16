#include <fstream>																	//Including for file read operations.
#include <iostream>																	//Including for output to standard output stream.
#include <vector>																	//Including to use vector containers because arrays need known space allocation and finding array sizes for returned pointers isn't possible.
#include <string>																	//Including to use string containers.
#include <bitset>																	//Including to use bitset containers.

#include "Graph.h"																	//Including to use Graph objects.
#include "Router.h"																	//Including to use Router containers.

using namespace std;																//Set namespace to use vector, string, bitset, ifstream and cout without namespace prefixes. 

string to32BitBinary(string ip) {													//Function to convert string ip to a 32 bit binary string.
	unsigned short start=0,i;														//Declare start for the index of '.' and i to iterate over the string.
	string final, block;															//Declare strings final to store final output and block to store parts of IP seperated by '.'.
	for(i=0;i<=ip.size();i++) {														//Iterate over ip.
		if(i==ip.size() || ip[i]=='.') {											//If i is the end of sring or ip[i] is a '.'.
			final.append(bitset<8>(stoi(ip.substr(start, i-start))).to_string());	//Get substring from last '.' to the next one or the end of the string, convert to integer, get a fixed 8 bit bitset of that integer, convert it to string and append it to the final string.
			start=i+1;																//Set start to the next character after '.'.
		}
	}
	return final;																	//Return the finaal string.
}

int main(int nargs, char *cli[]) {													//Main function to take input from file and , run Dijkstra's to get shortest distance, run routing to create tries and display the traversal prefixes.
	int vertices, row, column, weight, source, destination;							//Declare variables.
	unsigned long long edges;														
	ifstream inputg, inputip;														//Declare input streams.
	Graph *g = new Graph;															//Declare Graph object.
	vector<string> ips;																//Declare vector of strings to store IPs as 32 bit strings.
	vector<int> path;																//Declare vector of integers to store the predecessor array.
	string ip;																		//Declare string ip to temporarily store input IPs.
	char *graphfilename = cli[1];													//Read filename of graph input from commandline.
	char *ipfilename = cli[2];														//Read filename of IP input from commandline.
	source = stoi(cli[3]);															//Read source from commandline.
	destination = stoi(cli[4]);														//Read destination from commandline.
	try{																			//Try to catch any file read exceptions.
		inputg.open(graphfilename, ios::in);										//Open the input stream using graphfilename to read.
		if(inputg.fail())															//If File open fails,
			throw 0;																//Throw exception 0.
		inputg>>vertices>>edges;													//Read vertices and edges from the file and assign them.
		g->vertices = vertices;
		g->edges = edges;
	    while(inputg>>row) {														//Iterate until end of read by reading the row.
	    	inputg>>column;															//Read column.
	    	inputg>>weight;															//Read edge weight.
	    	g->insert(row, column, weight);											//Insert row column and weight into adjlist of g.
	    	g->insert(column, row, weight);											//Insert column row and weight into adjlist of g, since it's an undirected graph.
	    }
	    inputg.close();																//Close the graph input stream.
	    inputip.open(ipfilename, ios::in);											//Open the input stream using ipfilename to read.
		if(inputip.fail())															//If File open fails,
			throw 1;																//Throw exception 1.
		while(inputip) {															//Iterate until read is possible.
			inputip>>ip;															//Read IP.
			ips.push_back(to32BitBinary(ip));										//Convert IP to binary and push to ips vector.
		}
		ips.pop_back();																//Pop last push for duplicate read of last input.
		path = g->dijkstra(source, destination, false);								//Get predecessor vertices using Dijkstra's for the read adjacency list using the given soure and destination.
		cout<<path[path.size()-1]<<endl;											//Display shortest distance from source to destination.
		path.pop_back();															//Pop the distance from the predecessor vector.
		Router *r = new Router(g, ips, path, source, destination);					//Create a Router object.
		r->run(path);																//Run to display Trie prefixes for the path.
	}
	catch(int e) {																	//Catch exception.
		cout<<"File open/read failed.\nPlease check if "<<(e?ipfilename:graphfilename)<<" exists."<<endl;
		return 1;																	//Display which file gave the read error and return error.
	}
}