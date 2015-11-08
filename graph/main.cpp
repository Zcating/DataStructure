// 图的算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "graph.h"
#include "TraversingGraph.h"
#include "MST.h"
#include "ShortestPath.h"
#include "AOVENet.h"



int _tmain(int argc, _TCHAR* argv[])
{
	int n = 0, m = 0, numver = 0, numedge = 0;
	while (cin >> numver >> numedge){
		LinkGraph<VerDataInfo> gra;
		gra.ChangeDirectivity(Directive);
		for (int i = 0; i < numver; i++){
			VerDataInfo info;
			cin >> info.pos >> info.data;
			gra.InsertVertice(info);
		}
		for (int i = 0; i < numedge; i++){
			int v1, v2, weight;
			cin >> v1 >> v2 >> weight;
			gra.InsertEdge(v1, v2, weight);
		}
		//DFS(gra, gra.GetValue(0), Recursive);
		//BFS(gra, 0);
		//MST mstree;
		//mstree.KruskalAlogrithm(gra);
		//cout << endl;
		//cout << mstree;
		SHORTESTPATH sp;
		sp.Dijkstra_Heap(gra, 0);
		sp.PrintShortestPath(gra);
		//sp.PrintShortestPath(gra);
		//AOVENet anet;
		//anet.CriticalPath(gra);
		//anet.PrintCPath(gra);
		//cout << endl;
	}
	return 0;
}

