#ifndef _AOVENET_H
#define _AOVENET_H
class AOVENet{
public:
	AOVENet() : flagOfLoop(true){}
	void TopologicalSort(Graph<VerDataInfo> & gra);
	void CriticalPath(Graph<VerDataInfo> &gra);
	void PrintCPath(Graph<VerDataInfo> &gra);
	void PrintTSort(Graph<VerDataInfo> &gra);
private:

	/*'False' means that there is not loop in the graph. 
	'True' means that there is one loop at least in graph */
	bool flagOfLoop;
	vector<int> topologicalVertex;
	vector<pair<int,int>> criticalAction;
};

#endif