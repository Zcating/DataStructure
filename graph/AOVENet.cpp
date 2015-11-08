#include "stdafx.h"
#include "graph.h"
#include "AOVENet.h"

void AOVENet::TopologicalSort(Graph<VerDataInfo> & gra){
	int numver = gra.SizeOfVertices();
	int top = -1;
	int *TopoStack = new int[numver];
	flagOfLoop = false;
	for (int i = 0; i < numver; i++) TopoStack[i] = 0;

	for (int i = 0; i < numver; i++) 
	for (int j = 0; j < numver; j++)
	if (gra.GetWeight(i, j) < MAXWEIGHT)
		TopoStack[j]++;

	for (int i = 0; i < numver; i++)
	if (TopoStack[i] == 0){
		TopoStack[i] = top;
		top = i;
	}
	for (int i = 0; i < numver; i++)
	if (top == -1){
		flagOfLoop = true;
		TopologicalVertex.~vector();
	}
	else {
		int ver = top;
		top = TopoStack[top];
		TopologicalVertex.push_back(ver);
		int wer = gra.GetFirstNeighbor(ver);
		while (wer != -1){
			if (--TopoStack[wer] == 0){
				TopoStack[wer] = top;
				top = wer;
			}
			wer = gra.GetNextNeighbor(ver, wer);
		}
	}
	delete[] TopoStack;
}


void AOVENet::CriticalPath(Graph<VerDataInfo> & gra){
	int numver = gra.SizeOfVertices();
	EdgeStruct *Ve = new EdgeStruct[numver];
	EdgeStruct * Vl = new EdgeStruct[numver];
	for (int i = 0; i < numver; i++) Ve[i] = 0,Vl[i] = MAXWEIGHT;

	/*Caculation for Ve[]*/
	for (int loc = 0; loc < numver; loc++){
		int locx = gra.GetFirstNeighbor(loc);
		while (locx != -1)
		{
			int temp = gra.GetWeight(loc, locx);
			if (Ve[loc] + temp > Ve[locx]) Ve[locx] = Ve[loc] + temp;
			locx = gra.GetNextNeighbor(loc, locx);
		}
	}

	/*Reverse caculation for Vl[] */
	Vl[numver - 1] = Ve[numver - 1];
	for (int loc = numver - 2; loc >= 0; loc--){
		int lock = gra.GetFirstNeighbor(loc);
		while (lock != -1){
			int temp = gra.GetWeight(loc, lock);
			if (Vl[lock] - temp < Vl[loc])Vl[loc] = Vl[lock] - temp;
			lock = gra.GetNextNeighbor(loc, lock);
		}
	}
	/*Gets early value and late value of each activity */
	for (int loc = 0; loc < numver; loc++){
		int locx = gra.GetFirstNeighbor(loc);
		while (locx != -1){
			int Ae = Ve[loc];
			int Al = Vl[locx] - gra.GetWeight(loc, locx);
			if (Ae == Al){
				pair<int, int> ActionEdge(loc, locx);
				CriticalAction.push_back(ActionEdge);
			}
			locx = gra.GetNextNeighbor(loc, locx);
		}
	}
	delete[] Ve;
	delete[] Vl;
}

void AOVENet::PrintTSort(Graph<VerDataInfo> & gra){
	if (flagOfLoop == true) {
		cout << "there is at least one loop in the graph" << endl;
		return;
	}
	cout << "the result of the topological sort is " << endl << "start";
	for (int i = 0; i < (int)TopologicalVertex.size(); i++)
		cout << "->" << gra.GetValue(TopologicalVertex[i]);
}

void AOVENet::PrintCPath(Graph<VerDataInfo> & gra){
	for (int i = 0; i < (int)CriticalAction.size(); i++){
		cout << "Action edge ( " << gra.GetValue(CriticalAction[i].first)
			<<", "<< gra.GetValue(CriticalAction[i].second) << " )";
		cout << "is critical action" << endl;
	}
}
