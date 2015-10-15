#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

#include "graph.h"
#include "TraversingGraph.h"

//DFS
void DFS_Recursive(Graph<VerDataInfo> & gra, int ver, bool visit[]){
	visit[ver] = true;
	/*Add some visitng function here*/
	cout << gra.GetValue(ver) << endl;
	int verx = gra.GetFirstNeighbor(ver);
	while (verx != -1){
		if (visit[verx] == false)
			DFS_Recursive(gra, verx, visit);

		verx = gra.GetNextNeighbor(ver, verx);
	}
}

void DFS(Graph<VerDataInfo> & gra, VerDataInfo & vertex, DFSFunctionType FT){
	int loc = gra.GetVerticePos(vertex), num = gra.SizeOfVertices();
	bool * visited = new bool[num];
	for (int i = 0; i < num; i++)
		visited[i] = false;

	if (FT == Recursive)
		DFS_Recursive(gra, loc, visited);

	if (FT == Non_Recursive){
		stack<int> sver;
		sver.push(loc);
		while (!sver.empty()){
			loc = sver.top();
			if (visited[loc] == false){
				visited[loc] = true;
				/*Add some visitng function here*/
				cout << gra.GetValue(loc) << endl;/*This is the example*/

				//put all adjacent edge of  loc`s edge into the stack
				for (int locx = gra.GetFirstNeighbor(loc); locx != -1; locx = gra.GetNextNeighbor(loc, locx))
				if (visited[locx] == false)
					sver.push(locx);
			}
			else sver.pop();
		}
	}
	delete[] visited;
}

 
void DFS(Graph<VerDataInfo> & gra, int ver, DFSFunctionType FT){
	if (ver == -1){
		cout << "the parameter of DFS is ERROR!!!!!" << endl;
	}
	int loc = ver, num = gra.SizeOfVertices();
	bool * visited = new bool[num];
	for (int i = 0; i < num; i++)
		visited[i] = false;

	if (FT == Recursive)
		DFS_Recursive(gra, loc, visited);

	if (FT == Non_Recursive){
		stack<int> sver;
		sver.push(loc);
		while (!sver.empty()){
			loc = sver.top();
			if (visited[loc] == false){
				visited[loc] = true;
				/*Add some visitng function here*/
				cout << gra.GetValue(loc) << endl;/*This is the example*/

				//put all adjacent edge of  loc`s edge into the stack
				for (int locx = gra.GetFirstNeighbor(loc); locx != -1; locx = gra.GetNextNeighbor(loc, locx))
				if (visited[locx] == false)
					sver.push(locx);
			}
			else sver.pop();
		}
	}
	delete[] visited;
}

//BFS
 
void BFS(Graph<VerDataInfo> & gra, VerDataInfo vertex){
	int num = gra.SizeOfVertices();
	bool * visited = new bool[num];
	for (int i = 0; i < num; i++)
		visited[i] = false;

	queue<int> qver;
	int loc = gra.GetVerticePos(vertex);
	qver.push(loc);
	visited[loc] = true;
	cout << gra.GetValue(loc) << endl;

	while (!qver.empty()) {
		loc = qver.front();
		qver.pop();
		int locx = gra.GetFirstNeighbor(loc);
		for (int locx = gra.GetFirstNeighbor(loc); locx != -1; locx = gra.GetNextNeighbor(loc, locx))
		if (visited[locx] == false){
			qver.push(locx);
			visited[locx] = true;
			/*Add some visitng function here*/
			cout << gra.GetValue(locx) << endl;
		}
	}
	delete[] visited;
}

void BFS(Graph<VerDataInfo> & gra, int ver){
	if (ver == -1) {
		cout << "The parameter of BFS is ERROR!!!!!" << endl;
		return;
	}
	int num = gra.SizeOfVertices();
	bool * visited = new bool[num];
	for (int i = 0; i < num; i++)
		visited[i] = false;

	queue<int> qver;
	int loc = ver;
	qver.push(loc);
	visited[loc] = true;
	cout << gra.GetValue(loc) << endl;

	while (!qver.empty()) {
		loc = qver.front();
		qver.pop();
		int locx = gra.GetFirstNeighbor(loc);
		for (int locx = gra.GetFirstNeighbor(loc); locx != -1; locx = gra.GetNextNeighbor(loc, locx))
		if (visited[locx] == false){
			qver.push(locx);
			visited[locx] = true;
			/*Add some visitng function here*/
			cout << gra.GetValue(locx) << endl;
		}
	}
	delete[] visited;
}
