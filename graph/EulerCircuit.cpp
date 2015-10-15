#include "stdafx.h"
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

#include "graph.h"


void EulerCricuit(Graph<VerDataInfo> & gra) {
	if (gra.Direction() == Directive) return;
	bool *visited = new bool;

}