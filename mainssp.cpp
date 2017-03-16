#include <fstream>																		//Including for file read operations.
#include <iostream>																		//Including for output to standard output stream.

#include "Graph.h"																		//Including to create a Graph object.

using namespace std;																	//Set namespace to use ifstream and cout without namespace prefixes. 

int main(int nargs, char *cli[]) {														//Main function to input from command line and execute Dijsktra's.
	int vertices, row, column, weight, source, destination;								//Declare variables.
	unsigned long long edges;															
	ifstream input;																		//Declare input as an input stream.
	Graph *g = new Graph;																//Declare g as a pointer to a new Graph object.
	char *filename = cli[1];															//Read the filename from command line
	source = atoi(cli[2]);																//Read soure from command line.	
	destination = atoi(cli[3]);															//Read destination from command line.
	try{																				//Try to catch any file read exceptions.
		input.open(filename, ios::in);													//Open the input stream using the filename to read.
		if(input.fail())																//If File open fails,
			throw 0;																	//Throw exception 0.
		input>>vertices>>edges;															//Read vertices and edges from the file and assign them.
		g->vertices = vertices;															
		g->edges = edges;
	    while(input>>row) {																//Iterate until end of read by reading the row.
	    	input>>column;																//Read column.
	    	input>>weight;																//Read edge weight.
	    	g->insert(row, column, weight);												//Insert row column and weight into adjlist of g.
	    	g->insert(column, row, weight);												//Insert column row and weight into adjlist of g, since it's an undirected graph.
	    }
	    input.close();																	//Close the input stream.
	    g->dijkstra(source, destination);												//Call dijkstra's on the adjacency list we just read from file.
	    return 0;																		//Return success.
	}
	catch(int e) {																		//Catch exception.
		cout<<"File open/read failed.\nPlease check if "<<filename<<" exists."<<endl;	//Display file read error.
		return 1;																		//Return error.
	}
}