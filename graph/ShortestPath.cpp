#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

#include "graph.h"
#include "heap.h"
#include "ShortestPath.h"

SHORTESTPATH::SHORTESTPATH(int size) {
	path = new int[size];
	dist = new EdgeStruct[size];
}

/*
fake code:
	(1)initiate:		
				Set(S) <- {v0}
				dist[j] <- Edge[0][j]  ( j = 0, 1, 2, ...... , n)
	
	(2)get the shortest path:
				dist[k] <- min{ dist[j] }, i belong to Set(V) - Set(S)
				Set(S) <- Set(S) merge {k}

	(3)modify:
				dist[i]  <- min{ dist[i], dist[k] + Edge[k][i] } for each i , i belong to Set(V) - Set(S)

	(4)judge: 
			if the Set(V) equals to the Set(S), end the algorithm; else skip to the code (2)    
*/

void SHORTESTPATH::Dijkstra(Graph<VerDataInfo> & gra, VerDataInfo vertex){
	numVertices = gra.SizeOfVertices();
	bool *SetVer = new bool[numVertices];
	start = gra.GetVerticePos(vertex);
	for (int i = 0; i < numVertices; i++){
		dist[i] = gra.GetWeight(start,i);
		SetVer[i] = false;
		if (i !=start && dist[i] < MAXWEIGHT) path[i] =start;
		else path[i] = -1;
	}
	SetVer[start] = true;
	dist[start] = 0;
	for (int i = 0; i < numVertices - 1; i++){
		EdgeStruct min = MAXWEIGHT;
		int verx =start; 
		for (int j = 0; j < numVertices; j++)
		if (SetVer[j] == false && dist[j] < min){
			verx = j;
			min = dist[j];
		}
		SetVer[verx] = true;
		for (int k = 0; k < numVertices; k++){
			EdgeStruct weight = gra.GetWeight(verx, k);
			//relax the edge
			if (SetVer[k] == false && weight < MAXWEIGHT && dist[verx] + weight < dist[k]){
				dist[k] = dist[verx] + weight;
				path[k] = verx;
			}
		}
	}
	delete[] SetVer;
}

void SHORTESTPATH::Dijkstra(Graph<VerDataInfo> & gra, int ver){
	start = ver;
	numVertices = gra.SizeOfVertices();
	bool *SetVer = new bool[numVertices];
	for (int i = 0; i < numVertices; i++){
		dist[i] = gra.GetWeight(start, i);
		SetVer[i] = false;
		if (i !=start && dist[i] < MAXWEIGHT) path[i] =start;
		else path[i] = -1;
	}
	SetVer[start] = true;
	dist[start] = 0;
	for (int i = 0; i < numVertices - 1; i++){
		EdgeStruct min = MAXWEIGHT;
		int verx =start;
		for (int j = 0; j < numVertices; j++)
		if (SetVer[j] == false && dist[j] < min){
			verx = j;
			min = dist[j];
		}
		SetVer[verx] = true;
		for (int k = 0; k < numVertices; k++){
			EdgeStruct weight = gra.GetWeight(verx, k);
			//relax the edge
			if (SetVer[k] == false && weight < MAXWEIGHT && dist[verx] + weight < dist[k]){
				dist[k] = dist[verx] + weight;
				path[k] = verx;
			}
		}
	}
	delete[] SetVer;
}


void SHORTESTPATH::Floyd(Graph<VerDataInfo> &gra){
	numVertices = gra.SizeOfVertices();
	for (int i = 0; i < numVertices; i++)
	for (int j = 0; j < numVertices; j++){
		FDist[i][j] = gra.GetWeight(i, j);
		if (i != j && FDist[i][j] < MAXWEIGHT) FPath[i][j] = 1;
		else FPath[i][j] = 0;
	}
	for (int k = 0; k < numVertices; k++)
	for (int i = 0; i < numVertices; i++)
	for (int j = 0; j < numVertices; j++)
	if (FDist[i][k] + FDist[k][j] < FDist[i][j]){
		FDist[i][j] = FDist[i][k] + FDist[k][j];
		FPath[i][j] = FPath[k][j];
	}
}


void SHORTESTPATH::PrintShortestPath (Graph<VerDataInfo> & gra){
	cout << "The start vertice is vertice " << gra.GetValue(start) << endl;
	int *Dest = new int[numVertices];
	for (int i = 0; i < numVertices; i++){
		if (start != i){
			int j = i, k = 0;
			while (j != start){
				Dest[k++] = j;
				j = path[j];
			}
			cout << "the shortest path of vertice " << gra.GetValue(i)
				<< " is the path of " << gra.GetValue(start) ;
			while (k > 0) cout << " -> " << gra.GetValue(Dest[--k]) ;
			cout << endl << "the minimum lenth is " << dist[i] << endl;
		}
	}
}

struct MinPos {
	int pos;
	EdgeStruct key;
	MinPos(int P = 0, int K = 0) : pos(P), key(K) {}
	bool operator > (MinPos & temp)const { return key > temp.key; }
	bool operator <=(MinPos & temp)const { return key <= temp.key; }
};

void SHORTESTPATH::Dijkstra_Heap(Graph<VerDataInfo> & gra, VerDataInfo vertex){
	numVertices = gra.SizeOfVertices();
	bool *SetVer = new bool[numVertices];
	start = gra.GetVerticePos(vertex);
	MinHeap<MinPos> vheap(numVertices);//Get item of minimum vertices
	for (int i = 0; i < numVertices; i++) {
		dist[i] = gra.GetWeight(start, i);
		SetVer[i] = false;
		if (i != start && dist[i] < MAXWEIGHT) path[i] = start;
		else path[i] = -1;
	}
	/*Initiate the heap*/
	for (int verx = gra.GetFirstNeighbor(start); verx != -1; verx = gra.GetNextNeighbor(start, verx))
		vheap.Insert(MinPos(verx, gra.GetWeight(start, verx)));
	SetVer[start] = true;
	dist[start] = 0;
	while (!vheap.Empty()) {
		/*The vertice which has visited will be not exist in the heap*/
		/*The top of heap is the minimum*/
		EdgeStruct min = vheap.Front().key;
		int verx = vheap.Front().pos;
		dist[verx] = min;
		vheap.Remove();

		for (int verk = gra.GetFirstNeighbor(verx); verk != -1; verk = gra.GetNextNeighbor(verx, verk))
			if (SetVer[verk] == false && verk != -1)
				vheap.Insert(MinPos(verx, gra.GetWeight(verx, verk)));
		
		for (int k = 0; k < numVertices; k++) {
			EdgeStruct weight = vheap.Front().key;
			//relax the edge
			if (SetVer[k] == false && weight < MAXWEIGHT && dist[verx] + weight < dist[k]) {
				dist[k] = dist[verx] + weight;
				path[k] = verx;
				vheap.Remove();
			}
		}
	}
	delete[] SetVer;
}

void SHORTESTPATH::Dijkstra_Heap(Graph<VerDataInfo> & gra, int ver) {
	numVertices = gra.SizeOfVertices();
	bool *SetVer = new bool[numVertices];
	start = ver;
	MinHeap<MinPos> vheap(numVertices);//Get item of minimum vertices
	for (int i = 0; i < numVertices; i++) {
		dist[i] = MAXWEIGHT;
		SetVer[i] = false;
		path[i] = -1;
	}
	/*Initiate the heap*/
	vheap.Insert(MinPos(start, 0));//The distance from the start to start is 0 
	SetVer[start] = true;
	dist[start] = 0;
	while (!vheap.Empty()) {
		/*The vertice which has visited will be not exist in the heap*/
		/*The top of heap is the minimum*/
		int verx = vheap.Front().pos;					//Get vertice to which the mimimum value edge pose
		SetVer[verx] = true;							//The vertice has been visited
		vheap.Remove();									//Remove the top of the heap

		for (int verSelector = gra.GetFirstNeighbor(verx); verSelector != -1; verSelector = gra.GetNextNeighbor(verx, verSelector)) {
			EdgeStruct weight = gra.GetWeight(verx, verSelector);
			if (SetVer[verSelector]==false && dist[verx] < MAXWEIGHT && dist[verx] + weight < dist[verSelector]) {
				dist[verSelector] = dist[verx] + weight;
				path[verSelector] = verx;
				vheap.Insert(MinPos(verSelector, dist[verSelector]));	//	Get the adjacent vertice of verSelector 
			}
		}
	}
	delete[] SetVer;
}
