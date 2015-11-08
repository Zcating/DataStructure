#ifndef _SHORTESETPATH_H
#define _SHORTESETPATH_H
class SHORTESTPATH{
public:
	SHORTESTPATH(int size = defaultVertices);
	~SHORTESTPATH(){ delete[] path; delete[] dist; };
	void Dijkstra(Graph<VerDataInfo> & gra, VerDataInfo vertex);
	void Dijkstra(Graph<VerDataInfo> & gra, int ver);
	void Dijkstra_Heap(Graph<VerDataInfo> & gra, VerDataInfo vertex);
	void Dijkstra_Heap(Graph<VerDataInfo> & gra, int ver);
	void Floyd(Graph<VerDataInfo> & gra);
	void PrintShortestPath(Graph<VerDataInfo> & gra);
private:
	int numVertices;
	int start;
	/*Dijkstra varities*/
	int *path;
	EdgeStruct *dist;

	/*Floyd varities*/
	int **FPath;
	EdgeStruct **FDist;
	
};
#endif 