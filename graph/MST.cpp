#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

#include "graph.h"
#include "heap.h"
#include "UFSet.h"
#include "MST.h"

bool MST::Insert(MSTEdgeNode & item){
	if (currentSize < maxSize){
		edgeValue[currentSize++] = item;
		return true;
	}
	else return false;
}

ostream & operator<< (ostream & out, MST mstree){
	for (int i = 0; i < mstree.currentSize; i++)
		cout << mstree.edgeValue[i].start << " "
		<< mstree.edgeValue[i].end << " "
		<< mstree.edgeValue[i].key << " "
		<< endl;
	return out;
}

void MST::KruskalAlogrithm(Graph<VerDataInfo> & gra){
	MSTEdgeNode temp;
	int numver = gra.SizeOfVertices();
	int numedg = gra.SizeOfEdge();
	MinHeap<MSTEdgeNode> heapEdge(numedg);
	UFSet setEdge(numver);
	for (int loc = 0; loc < numver; loc++)
	for (int locx = loc + 1; locx < numver; locx++)
	if (gra.GetWeight(loc, locx) < MAXWEIGHT){
		temp.start = loc;
		temp.end = locx;
		temp.key = gra.GetWeight(loc, locx);
		heapEdge.Insert(temp);
	}
	int count = 1;
	while (count < numver){
		temp = heapEdge.Front();
		heapEdge.Remove();
		int loc = setEdge.Find(temp.start);
		int locx = setEdge.Find(temp.end);
		if (loc != locx){
			setEdge.Union(locx, loc);
			Insert(temp);
			count++;
		}
	}
}


void MST::PrimAlogrithm(Graph<VerDataInfo> & gra, const VerDataInfo vertex){
	MSTEdgeNode temp;
	int numVer = gra.SizeOfVertices();
	int numEdg = gra.SizeOfVertices();
	int ver = gra.GetVerticePos(vertex);
	MinHeap<MSTEdgeNode> heapEdge(numEdg);
	bool *VerSet = new bool[numVer];
	for (int i = 0; i < numVer; i++) VerSet = false;
	
	VerSet[ver] = true;
	int count = 1;
	do{
		int verx = gra.GetFirstNeighbor(ver);
		while (verx != -1){
			if (VerSet[verx] == false){
				temp.start = verx;
				temp.end = ver;
				temp.key = gra.GetWeight(ver, verx);
				heapEdge.Insert(temp);
			}
			verx = gra.GetNextNeighbor(ver, verx);
		}
		while (heapEdge.Empty() == false && count < numVer){
			temp = heapEdge.Front();
			heapEdge.Remove();
			if (VerSet[temp.start] == false){
				Insert(temp);
				ver = temp.start;
				VerSet[ver] = true;
				count++;
				break;
			}
		}
	} while (count < numVer);

}

void MST::PrimAlogrithm(Graph<VerDataInfo> & gra, const int verStart){
	if (verStart == -1) return;
	MSTEdgeNode temp;
	int numVer = gra.SizeOfVertices();
	int numEdg = gra.SizeOfVertices();
	int ver = verStart;
	MinHeap<MSTEdgeNode> heapEdge(numEdg);
	bool *VerSet = new bool[numVer];
	for (int i = 0; i < numVer; i++) VerSet[i] = false;

	VerSet[ver] = true;
	int count = 1;
	do{
		int verx = gra.GetFirstNeighbor(ver);
		while (verx != -1){
			if (VerSet[verx] == false){
				temp.start = verx;
				temp.end = ver;
				temp.key = gra.GetWeight(ver, verx);
				heapEdge.Insert(temp);
			}
			verx = gra.GetNextNeighbor(ver, verx);
		}
		while (heapEdge.Empty() == false && count < numVer){
			temp = heapEdge.Front();
			heapEdge.Remove();
			if (VerSet[temp.start] == false){
				Insert(temp);
				ver = temp.start;
				VerSet[ver] = true;
				count++;
				break;
			}
		}
	} while (count < numVer);
}
 