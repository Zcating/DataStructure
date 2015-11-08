#include "stdafx.h"
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

#include "graph.h"
#include "TraversingGraph.h"
void function(int presentVer, bool* visited) { visited[presentVer] = true; }
void EulerCricuit(Graph<VerDataInfo> & gra) {
	if (gra.Direction() == Directive) return;
	bool *visited = new bool[gra.SizeOfVertices()];
	for (int count = 0; count < gra.SizeOfVertices(); count++) {
		visited[count] = false;
	}
}