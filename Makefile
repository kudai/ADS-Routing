CXX = g++ -std=c++0x -Wall
PERFFLAG = -O3
DEBUGFLAG = -g

all: ssp routing

ssp: mainssp.o Graph.o fHeap.o List.o Node.o
	${CXX} ${PERFFLAG} mainssp.o Graph.o fHeap.o List.o Node.o -o ssp

routing: mainrouting.o Router.o TrieNode.o Graph.o fHeap.o List.o Node.o
	${CXX} ${PERFFLAG} mainrouting.o Router.o TrieNode.o Graph.o fHeap.o List.o Node.o -o routing

mainrouting.o: mainrouting.cpp
	${CXX} ${PERFFLAG} -c mainrouting.cpp -o mainrouting.o

Router.o: Router.cpp Router.h
	${CXX} ${PERFFLAG} -c Router.cpp -o Router.o

TrieNode.o: TrieNode.cpp TrieNode.h
	${CXX} ${PERFFLAG} -c TrieNode.cpp -o TrieNode.o

mainssp.o: mainssp.cpp
	${CXX} ${PERFFLAG} -c mainssp.cpp -o mainssp.o

Graph.o: Graph.cpp Graph.h
	${CXX} ${PERFFLAG} -c Graph.cpp -o Graph.o

fHeap.o: fHeap.cpp fHeap.h
	${CXX} ${PERFFLAG} -c fHeap.cpp -o fHeap.o

List.o: List.cpp List.h Node.h
	${CXX} ${PERFFLAG} -c List.cpp -o List.o

Node.o: Node.cpp Node.h
	${CXX} ${PERFFLAG} -c Node.cpp -o Node.o

clean:
	rm -rf *.o ssp routing
