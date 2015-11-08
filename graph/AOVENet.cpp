#include "stdafx.h"
#include "graph.h"
#include "AOVENet.h"

void AOVENet::TopologicalSort(Graph<VerDataInfo> & gra){
	int numver = gra.SizeOfVertices();
	int top = -1;
	int *topoStack = new int[numver];
	flagOfLoop = false;
	for (int i = 0; i < numver; i++) topoStack[i] = 0;

	for (int i = 0; i < numver; i++) 
	for (int j = 0; j < numver; j++)
	if (gra.GetWeight(i, j) < MAXWEIGHT)
		topoStack[j]++;

	for (int i = 0; i < numver; i++)
	if (topoStack[i] == 0){
		topoStack[i] = top;
		top = i;
	}
	for (int i = 0; i < numver; i++)
	if (top == -1){
		flagOfLoop = true;
		topologicalVertex.~vector();
	}
	else {
		int ver = top;
		top = topoStack[top];
		topologicalVertex.push_back(ver);
		int wer = gra.GetFirstNeighbor(ver);
		while (wer != -1){
			if (--topoStack[wer] == 0){
				topoStack[wer] = top;
				top = wer;
			}
			wer = gra.GetNextNeighbor(ver, wer);
		}
	}
	delete[] topoStack;
}


void AOVENet::CriticalPath(Graph<VerDataInfo> & gra){
	int numver = gra.SizeOfVertices();
	EdgeStruct *ve = new EdgeStruct[numver];
	EdgeStruct * vl = new EdgeStruct[numver];
	for (int i = 0; i < numver; i++) ve[i] = 0,vl[i] = MAXWEIGHT;

	/*Caculation for ve[]*/
	for (int loc = 0; loc < numver; loc++){
		int locx = gra.GetFirstNeighbor(loc);
		while (locx != -1)
		{
			int temp = gra.GetWeight(loc, locx);
			if (ve[loc] + temp > ve[locx]) ve[locx] = ve[loc] + temp;
			locx = gra.GetNextNeighbor(loc, locx);
		}
	}

	/*Reverse caculation for vl[] */
	vl[numver - 1] = ve[numver - 1];
	for (int loc = numver - 2; loc >= 0; loc--){
		int lock = gra.GetFirstNeighbor(loc);
		while (lock != -1){
			int temp = gra.GetWeight(loc, lock);
			if (vl[lock] - temp < vl[loc])vl[loc] = vl[lock] - temp;
			lock = gra.GetNextNeighbor(loc, lock);
		}
	}
	/*Gets early value and late value of each activity */
	for (int loc = 0; loc < numver; loc++){
		int locx = gra.GetFirstNeighbor(loc);
		while (locx != -1){
			int Ae = ve[loc];
			int Al = vl[locx] - gra.GetWeight(loc, locx);
			if (Ae == Al){
				pair<int, int> ActionEdge(loc, locx);
				criticalAction.push_back(ActionEdge);
			}
			locx = gra.GetNextNeighbor(loc, locx);
		}
	}
	delete[] ve;
	delete[] vl;
}

void AOVENet::PrintTSort(Graph<VerDataInfo> & gra){
	if (flagOfLoop == true) {
		cout << "there is at least one loop in the graph" << endl;
		return;
	}
	cout << "the result of the topological sort is " << endl << "start";
	for (int i = 0; i < (int)topologicalVertex.size(); i++)
		cout << "->" << gra.GetValue(topologicalVertex[i]);
}

void AOVENet::PrintCPath(Graph<VerDataInfo> & gra){
	for (int i = 0; i < (int)criticalAction.size(); i++){
		cout << "Action edge ( " << gra.GetValue(criticalAction[i].first)
			<<", "<< gra.GetValue(criticalAction[i].second) << " )";
		cout << "is critical action" << endl;
	}
}
