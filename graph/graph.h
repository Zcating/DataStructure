//////////declare//////////////////
#ifndef _GRAPH_H
#define _GRAPH_H
#define DEFAULTVERTICES 30
typedef int EdgeStruct;//weight of the edge
const EdgeStruct MAXWEIGHT = 99999;
const int DefaultVertices = 30;
enum Directivity
{
	Directive,
	Undirective,
};
struct VerDataInfo
{
	/*add the data here*/
	int pos;
	int data;
	VerDataInfo() : pos(0){}
	bool operator == (VerDataInfo temp)const {
		return (pos == temp.pos);
	}
	friend ostream& operator << (ostream& out, VerDataInfo info){
		/*overloading the ostream operator << must use the friend function*/
		cout << info.data;
		return out;
	}
};

template<class VerStruct>
class Graph
{
public:
	/*The default graph is undirective graph*/
	Graph(int size = DefaultVertices) : maxVertices(size), numVertices(0),
		numEdges(0), dirOfGraph(Undirective){};
	~Graph(){};/*The destructive function must be structured*/

	void ChangeDirectivity(Directivity dir){
		/*Select the directive graph or the undirective graph */
		dirOfGraph = dir;
	}
	bool GraphEmpty()const{
		if (numEdges == 0) return true;
		else return false;
	}
	bool GraphFull()const{
		if (numVertices == maxVertices || numEdges == maxVertices*(maxVertices - 1) / 2)
			return true;
		else return false;
	}
	int SizeOfVertices(){ return numVertices; }
	int SizeOfEdge(){ return numEdges; }
	Directivity Direction() { return dirOfGraph; }
	/*All virtual functions must be the pure virtual functions to make it inherit two different classes */
	virtual VerStruct GetValue(int ver) = 0;
	virtual EdgeStruct GetWeight(int ver1, int ver2) = 0;
	virtual int GetFirstNeighbor(int ver) = 0;
	virtual int GetNextNeighbor(int ver, int verx) = 0;
	virtual int GetVerticePos(VerStruct Vertice) = 0;
	virtual bool InsertVertice(const VerStruct& vertex) = 0;
	virtual bool RemoveVertice(int ver) = 0;
	virtual bool RemoveEdge(int v1, int v2) = 0;

protected:
	int maxVertices;
	int numEdges;
	int numVertices;
	Directivity dirOfGraph;
};

////////////////////////////Matrix Graph
template<class VerStruct>
class MatrixGraph : public Graph<VerStruct>{
	friend istream& operator >>(istream& in, MatrixGraph<VerStruct>& TheGraph);
	friend ostream& operator <<(ostream& out, MatrixGraph<VerStruct>& TheGraph);
public:
	MatrixGraph(int size = DefaultVertices);
	~MatrixGraph();

	VerStruct GetValue(int ver);
	EdgeStruct GetWeight(int ver1, int ver2);
	int GetFirstNeighbor(int ver);
	int GetNextNeighbor(int ver, int verx);
	bool InsertVertice(const VerStruct & vertex);
	bool InsertEdge(int v1, int v2, EdgeStruct weight);
	bool RemoveVertice(int ver);
	bool RemoveEdge(int v1, int v2);
	int GetVerticePos(VerStruct ver){
		for (int i = 0; i < numVertices; i++)
		if (VerticesList[i] == ver) return i;
		return -1;
	}

private:
	VerStruct * VerticesList;
	EdgeStruct ** Edges;

};


///////////////////////////Adjacency List Graph
struct Edge
{
	int dest;
	EdgeStruct cost;
	Edge * linker;
	Edge(){}
	Edge(int num, EdgeStruct weight) : 
		dest(num), cost(weight), linker(nullptr){}
	bool operator != (Edge& temp)const {
		return (dest != temp.dest);
	}
};

template<class VerStruct>
struct Vertex
{
	VerStruct data;
	Edge *adj;
};

template<class VerStruct>
class LinkGraph : public Graph<VerStruct>
{
	friend istream& operator >>(istream& in, LinkGraph<VerStruct>& TheGraph);
	friend ostream& operator <<(ostream& out, LinkGraph<VerStruct>& TheGraph);
public:
	LinkGraph(int size = DefaultVertices);
	~LinkGraph();
	VerStruct GetValue(int ver);
	EdgeStruct GetWeight(int v1, int v2);
	bool InsertVertice(const VerStruct& vertex);
	bool InsertEdge(int v1, int v2, EdgeStruct cost);
	bool RemoveVertice(int ver);
	bool RemoveEdge(int v1,int v2);
	int GetFirstNeighbor(int ver);
	int GetNextNeighbor(int ver, int verx);
	int GetVerticePos(VerStruct ver){
		for (int i = 0; i < numVertices; i++)
		if (AdjList[i].data == ver) return i;
		return -1;
	}
private:
	Vertex<VerStruct> * AdjList;
};
//////////////
#endif

///////////Function/////////////////////////////


//////////Matrix Graph///////////////////
template<class VerStruct>
MatrixGraph<VerStruct>::MatrixGraph(int size){
	maxVertices = size;
	numVertices = 0;
	numEdges = 0;
	dirOfGraph = Undirective;
	int i = 0, j = 0;
	VerticesList = new VerStruct[maxVertices];
	if (VerticesList == nullptr) {
		cout << "the graph does not allocate the memory" << endl;
		exit(1);
	}
	Edges = (EdgeStruct**) new EdgeStruct *[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		Edges[i] = new EdgeStruct[maxVertices];
	for (int i = 0; i < maxVertices; i++)
	for (int j = 0; j < maxVertices; j++)
		Edges[i][j] = (i == j) ? 0 : MAXWEIGHT;
}

template<class VerStruct>
MatrixGraph<VerStruct>:: ~MatrixGraph(){
	delete[] VerticesList; 
	delete[] Edges;
};

template<class VerStruct>
VerStruct MatrixGraph<VerStruct>::GetValue(int ver){
	return VerticesList[ver];
}

template<class VerStruct>
EdgeStruct MatrixGraph<VerStruct>::GetWeight(int ver1, int ver2){
	return Edges[ver1][ver2];
}

template<class VerStruct>
int MatrixGraph<VerStruct>::GetFirstNeighbor(int ver){
	if (ver != -1){
		for (int i = 0; i < numVertices; i++)
		if (Edges[ver][i] > 0 && Edges[ver][i] < MAXWEIGHT)return i;
		else return -1;
	}
	else return -1;
}

template<class VerStruct>
int MatrixGraph<VerStruct>::GetNextNeighbor(int ver, int verx){
	if (ver != -1 && verx != -1){
		for (int i = verx + 1; i < numVertices; i++)
		if (Edges[ver][i] > 0 && Edges[ver][i] < MAXWEIGHT) return i;
		else return -1;
	}
	else return -1;
}

template<class VerStruct>
bool MatrixGraph<VerStruct>::InsertVertice(const VerStruct& vertex){
	if (numVertices == maxVertices) return false;
	else {
		VerticesList[numVertices++] = vertex;
		return true;
	}
}


template<class VerStruct>
bool MatrixGraph<VerStruct>::RemoveVertice(int ver){
	if (ver < 0 || ver > numVertices)return false;
	else if (numVertices == 1) return false;
	else{
		int i = 0;
		VerticesList[ver] = VerticesList[numVertices - 1];
		for (i = 0; i < numVertices; i++)
		if (Edges[ver][i] > 0 && Edges[ver][i] < MAXWEIGHT) numEdges--;

		for (i = 0; i < numVertices; i++)
			Edges[i][ver] = Edges[i][numVertices - 1];

		numVertices--;
		for (i = 0; i < numVertices; i++)
			Edges[ver][i] = Edges[numVertices][i];

		return true;
	}
}

template<class VerStruct>
bool MatrixGraph<VerStruct>::InsertEdge(int v1, int v2, int weight){
	if (dirOfGraph == Undirective){
		if (v1>-1 && v1<numVertices && v2>-1 && v2 < numVertices && Edges[v1][v2] == MAXWEIGHT){
			Edges[v1][v2] = Edges[v2][v1] = weight;
			numEdges++;
			return true;
		}
		else return false;
	}
	else if (dirOfGraph == Directive){
		if (v1>-1 && v1<numVertices && v2>-1 && v2 < numVertices && Edges[v1][v2] == MAXWEIGHT){
			Edges[v1][v2] = weight;
			numEdges++;
			return true;
		}
		else return false;
	}
}

template<class VerStruct>
bool MatrixGraph<VerStruct>::RemoveEdge(int v1, int v2){
	if (dirOfGraph == Undirective){
		if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices && Edges[v1][v2]>0 && Edges[v1][v2] < MAXWEIGHT){
			Edges[v1][v2] = Edges[v2][v1] = MAXWEIGHT;
			numEdges--;
			return true;
		}
		else return false;
	}
	else if (dirOfGraph == Directive){
		if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices && Edges[v1][v2]>0 && Edges[v1][v2] < MAXWEIGHT){
			Edges[v1][v2] = Edges[v2][v1] = MAXWEIGHT;
			numEdges--;
			return true;
		}
		else return false;
	}
}


template<class VerStruct>
istream operator >> (istream& in, MatrixGraph<VerStruct>& TheGraph){
	int numVer, numEdg;
	VerStruct v1, v2;
	EdgeStruct weight;
	in >> numVer >> numEdg;
	for (int i = 0; < n; i++)
		in >> TheGraph.InsertVertice(v1);
	int i = 0;
	while (i < numEdg){
		in >> v1 >> v2 >> weight;
		int j = TheGraph.GetVerticePos(v1);
		int k = TheGraph.GetVerticePos(v2);
		if (j == -1 || k == -1)
			cout << "The info of two ends of edge may be wrong, please input again" << endl;
		else {
			TheGraph.InsertEdge(j, k, weight);
			i++;
		}
	}
	return in;
}

template<class VerStruct>
ostream& operator << (ostream& out, MatrixGraph<VerStruct> G){
	VerStruct v1, v2;
	int numV = G.SizeOfVertices(), numE = G.SizeOfEdge();
	out << numV << "," << numE << endl;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++){
		EdgeStruct weight = G.GetWeight(i,j);
		if (weight > 0 && weight < MAXWEIGHT){
			v1 = G.GetValue(i);
			v2 = G.GetValue(j);
			cout << "( " << v1 << ", " << v2 << " )" << endl;
		}
	}
	return out;
}

//////////////////////////////////////////////



////////////Adjaceny List Graph/////////////////////////


template<class VerStruct>
LinkGraph<VerStruct>::LinkGraph(int size){
	maxVertices = size;
	numVertices = 0;
	numEdges = 0;
	dirOfGraph = Undirective;
	AdjList = new Vertex<VerStruct>[maxVertices];
	if (AdjList == nullptr){
		cerr << "memory allocated wrong!" << endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
		AdjList[i].adj = nullptr;
}

template<class VerStruct>
LinkGraph<VerStruct>::~LinkGraph(){
	for (int i = 0; i < numVertices; i++){
		Edge * temp = AdjList[i].adj;
		while (temp != nullptr){
			AdjList[i].adj = temp->linker;
			delete temp;
			temp = AdjList[i].adj;
		}
	}
	delete[] AdjList;
}

template<class VerStruct>
VerStruct LinkGraph<VerStruct>::GetValue(int ver){
	return AdjList[ver].data;
}

template<class VerStruct>
EdgeStruct LinkGraph<VerStruct>::GetWeight(int v1, int v2){
	if (v1 != -1 && v2 != -1){
		Edge * temp = AdjList[v1].adj;
		while (temp != nullptr && temp->dest != v2)
			temp = temp->linker;

		if (temp != nullptr) return temp->cost;
		else return MAXWEIGHT;
	}
	else return MAXWEIGHT;
}

template<class VerStruct>
int LinkGraph<VerStruct>::GetFirstNeighbor(int ver){
	if (ver != -1){
		Edge *temp = AdjList[ver].adj;
		if (temp != nullptr)return temp->dest;
		else return -1;
	}
	else return -1;
}

/* The function is used for getting next edge of verx`s edge  */
template<class VerStruct>
int LinkGraph<VerStruct>::GetNextNeighbor(int ver, int verx){
	if (ver != 1){
		Edge *temp = AdjList[ver].adj;
		while (temp != nullptr && temp->dest != verx) 
			temp = temp->linker;

		if (temp != nullptr && temp->linker != nullptr) return temp->linker->dest;
		else return -1;
	}
	else return -1;
}

template<class VerStruct>
bool LinkGraph<VerStruct>::InsertVertice(const VerStruct& vertex){
	if (numVertices == maxVertices) return false;
	AdjList[numVertices++].data = vertex;
	return true;
}
template<class VerStruct>
bool LinkGraph<VerStruct>::RemoveVertice(int ver){
	Edge *temp= nullptr,  *sub = nullptr, *aux = nullptr;
	while (AdjList[ver].adj != nullptr){
		temp = AdjList[ver].adj;
		sub = AdjList[temp->dest].adj;
		
		while (temp != nullptr && temp->dest != ver){
			aux = sub;
			sub = sub->linker;
		}
		if (sub != nullptr){
			if (aux != nullptr) AdjList[temp->dest].adj = sub->linker;
			else aux->linker = sub->linker;
			delete sub;
		}
		AdjList[ver].adj = temp->linker;
		delete temp;
		numEdges--;
	}
	numVertices--;
	AdjList[ver].data = AdjList[numVertices].data;
	temp = AdjList[ver].adj = AdjList[numVertices].adj;
	while (temp != nullptr){
		sub = AdjList[temp->dest].adj;
		while (sub!= nullptr)
		if (sub->dest == numVertices){
			sub->dest = ver;
			break;
		}
		else sub = sub->linker;
	}
	return true;
}

template<class VerStruct>
bool LinkGraph<VerStruct>::InsertEdge(int v1, int v2, EdgeStruct weight){
	if (dirOfGraph == Undirective){
		if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices){
			Edge *sub = nullptr, *temp = AdjList[v1].adj;

			while (temp != nullptr && temp->dest != v2)
				temp = temp->linker;

			if (temp != nullptr) return false;
			temp = new Edge;
			sub = new Edge;
			temp->dest = v2;
			temp->cost = weight;
			temp->linker = AdjList[v1].adj;
			AdjList[v1].adj = temp;

			sub->dest = v1;
			sub->cost = weight;
			sub->linker = AdjList[v2].adj;
			AdjList[v2].adj = sub;
			numEdges++;
			return true;
		}
		else return false;
	}
	if (dirOfGraph == Directive){
		if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices){
			Edge *sub = nullptr, *temp = AdjList[v1].adj;

			while (temp != nullptr && temp->dest != v2)
				temp = temp->linker;

			if (temp != nullptr) return false;
			temp = new Edge;
			sub = new Edge;
			temp->dest = v2;
			temp->cost = weight;
			temp->linker = AdjList[v1].adj;
			AdjList[v1].adj = temp;
			numEdges++;
			return true;
		}
		else return false;
	}
	return false;
}

template<class VerStruct>
bool LinkGraph<VerStruct>::RemoveEdge(int v1, int v2){
	if (dirOfGraph == Undirective){
		if (v1 != -1 && v2 != -1){
			Edge *temp = AdjList[v1].adj, *sub = nullptr, *aux = temp;
			while (temp != nullptr && temp->dest != v2){
				temp = sub;
				temp = temp->linker;
			}
			if (temp != nullptr){
				if (temp == aux) AdjList[v1].adj = temp->linker;
				else sub->linker = temp->linker;
				delete temp;
			}
			else return false;

			temp = AdjList[v2].adj, sub = nullptr, aux = temp;
			while (temp != nullptr && temp->dest != v1){
				temp = sub;
				temp = temp->linker;
			}
			if (temp != nullptr){
				if (temp == aux) AdjList[v2].adj = temp->linker;
				else sub->linker = temp->linker;
				delete temp;
				return true;
			}
			else return false;
		}
		else return false;
	}
	if (dirOfGraph == Directive){
		if (v1 != -1 && v2 != -1){
			Edge *temp = AdjList[v1].adj, *sub = nullptr, *aux = temp;
			while (temp != nullptr && temp->dest != v2){
				temp = sub;
				temp = temp->linker;
			}
			if (temp != nullptr){
				if (temp == aux) AdjList[v1].adj = temp->linker;
				else sub->linker = temp->linker;
				delete temp;
				return true;
			}
			else return false;
		}
		else return false;
	}
	return false;
}

template<class VerStruct>
istream operator >> (istream& in, LinkGraph<VerStruct>& TheGraph){
	int numVer, numEdg;
	VerStruct v1, v2;
	EdgeStruct weight;
	in >> numVer >> numEdg;
	for (int i = 0;i < numVer; i++)
		in >> TheGraph.InsertVertice(v1);
	int i = 0;
	while (i < numEdg){
		in >> v1 >> v2 >> weight;
		int j = TheGraph.GetVerticePos(v1);
		int k = TheGraph.GetVerticePos(v2);
		if (j == -1 || k == -1)
			cout << "The info of two ends of edge may be wrong, please input again" << endl;
		else {
			TheGraph.InsertEdge(j, k, weight);
			i++;
		}
	}
	return in;
}

template<class VerStruct>
ostream& operator << (ostream& out, LinkGraph<VerStruct> G){
	VerStruct v1, v2;
	int numV = G.SizeOfVertices(), numE = G.SizeOfEdge();
	out << numV << "," << numE << endl;
	for (int i = 0; i < numVer; i++)
	for (int j = 0; j < n; j++){
		EdgeStruct weight = G.GetWeight(i, j);
		if (weight > 0 && weight < MAXWEIGHT){
			v1 = G.GetValue(i);
			v2 = G.GetValue(j);
			cout << "( " << v1 << ", " << v2 << " )" << endl;
		}
	}
	return out;
}
