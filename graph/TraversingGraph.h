#ifndef _TRAVERSINGGRAPH_H
#define _TRAVERSINGGRAPH_H
enum DFSFunctionType{
	Recursive,
	Non_Recursive,
};

void DFS(Graph<VerDataInfo> & gra, VerDataInfo & vertex, DFSFunctionType FT);
void DFS(Graph<VerDataInfo> & gra, int ver, DFSFunctionType FT);
void BFS(Graph<VerDataInfo> & gra, VerDataInfo vertex);
void BFS(Graph<VerDataInfo> & gra, int ver);
#endif