//////////declare//////////////////
#ifndef _GRaPH_H
#define _GRaPH_H
#define DEFaULTVERTICES 30
typedef int EdgeStruct;//weight of the edge
const EdgeStruct MAXWEIGHT = 99999;
const int defaultVertices = 30;


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

//Graph --- basical class
template<class VerStruct>
class Graph
{
public:
	int SizeOfVertices(){ return numVertices; }
	int SizeOfEdge(){ return numEdges; }
	Directivity Direction() { return dirOfGraph; }
	/*all virtual functions must be the pure virtual functions to make it inherit two different classes */
	virtual VerStruct GetValue(int ver) = 0;
	virtual EdgeStruct GetWeight(int ver1, int ver2) = 0;
	virtual int GetFirstNeighbor(int ver) = 0;
	virtual int GetNextNeighbor(int ver, int verx) = 0;
	virtual int GetVerticePos(VerStruct Vertice) = 0;
	virtual bool InsertVertice(const VerStruct& vertex) = 0;
	virtual bool RemoveVertice(int ver) = 0;
	virtual bool RemoveEdge(int v1, int v2) = 0;
	
	/*The default graph is undirective graph*/
	Graph(int size = defaultVertices) : maxVertices(size), numVertices(0),
		numEdges(0), dirOfGraph(Undirective) {};
	~Graph() {};/*The destructive function must be structured*/

	void ChangeDirectivity(Directivity dir) {
		/*Select the directive graph or the undirective graph */
		dirOfGraph = dir;
	}
	bool GraphEmpty()const {
		if (numEdges == 0) return true;
		else return false;
	}
	bool GraphFull()const {
		if (numVertices == maxVertices || numEdges == maxVertices*(maxVertices - 1) / 2)
			return true;
		else return false;
	}
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
	MatrixGraph(int size = defaultVertices);
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
		if (verticesList[i] == ver) return i;
		return -1;
	}

private:
	VerStruct * verticesList;
	EdgeStruct ** edges;

};


///////////////////////////adjacency List Graph
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
	friend istream& operator >>(istream& in, LinkGraph<VerStruct>& theGraph);
	friend ostream& operator <<(ostream& out, LinkGraph<VerStruct>& theGraph);
public:
	LinkGraph(int size = defaultVertices);
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
		if (adjList[i].data == ver) return i;
		return -1;
	}
private:
	Vertex<VerStruct> * adjList;
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
	verticesList = new VerStruct[maxVertices];
	if (verticesList == nullptr) {
		cout << "the graph does not allocate the memory" << endl;
		exit(1);
	}
	edges = (EdgeStruct**) new EdgeStruct *[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		edges[i] = new EdgeStruct[maxVertices];
	for (int i = 0; i < maxVertices; i++)
	for (int j = 0; j < maxVertices; j++)
		edges[i][j] = (i == j) ? 0 : MaXWEIGHT;
}

template<class VerStruct>
MatrixGraph<VerStruct>:: ~MatrixGraph(){
	delete[] verticesList; 
	delete[] edges;
};

template<class VerStruct>
VerStruct MatrixGraph<VerStruct>::GetValue(int ver){
	return verticesList[ver];
}

template<class VerStruct>
EdgeStruct MatrixGraph<VerStruct>::GetWeight(int ver1, int ver2){
	return edges[ver1][ver2];
}

template<class VerStruct>
int MatrixGraph<VerStruct>::GetFirstNeighbor(int ver){
	if (ver != -1){
		for (int i = 0; i < numVertices; i++)
		if (edges[ver][i] > 0 && edges[ver][i] < MaXWEIGHT)return i;
		else return -1;
	}
	else return -1;
}

template<class VerStruct>
int MatrixGraph<VerStruct>::GetNextNeighbor(int ver, int verx){
	if (ver != -1 && verx != -1){
		for (int i = verx + 1; i < numVertices; i++)
		if (edges[ver][i] > 0 && edges[ver][i] < MaXWEIGHT) return i;
		else return -1;
	}
	else return -1;
}

template<class VerStruct>
bool MatrixGraph<VerStruct>::InsertVertice(const VerStruct& vertex){
	if (numVertices == maxVertices) return false;
	else {
		verticesList[numVertices++] = vertex;
		return true;
	}
}

template<class VerStruct>
inline bool MatrixGraph<VerStruct>::InsertEdge(int v1, int v2, EdgeStruct weight)
{
	if (dirOfGraph == Undirective) {
		if (v1>-1 && v1<numVertices && v2>-1 && v2 < numVertices && edges[v1][v2] == MaXWEIGHT) {
			edges[v1][v2] = edges[v2][v1] = weight;
			numedges++;
			return true;
		}
		else return false;
	}
	else if (dirOfGraph == Directive) {
		if (v1>-1 && v1<numVertices && v2>-1 && v2 < numVertices && edges[v1][v2] == MaXWEIGHT) {
			edges[v1][v2] = weight;
			numEdges++;
			return true;
		}
		else return false;
	}
	return false;
}


template<class VerStruct>
bool MatrixGraph<VerStruct>::RemoveVertice(int ver){
	if (ver < 0 || ver > numVertices)return false;
	else if (numVertices == 1) return false;
	else{
		int i = 0;
		verticesList[ver] = verticesList[numVertices - 1];
		for (i = 0; i < numVertices; i++)
		if (edges[ver][i] > 0 && edges[ver][i] < MaXWEIGHT) numEdges--;

		for (i = 0; i < numVertices; i++)
			edges[i][ver] = edges[i][numVertices - 1];

		numVertices--;
		for (i = 0; i < numVertices; i++)
			edges[ver][i] = edges[numVertices][i];

		return true;
	}
}

template<class VerStruct>
bool MatrixGraph<VerStruct>::RemoveEdge(int v1, int v2){
	if (dirOfGraph == Undirective){
		if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices 
			&& edges[v1][v2]>0 && edges[v1][v2] < MaXWEIGHT){
			edges[v1][v2] = edges[v2][v1] = MaXWEIGHT;
			numEdges--;
			return true;
		}
		else return false;
	}
	else if (dirOfGraph == Directive){
		if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices 
			&& edges[v1][v2]>0 && edges[v1][v2] < MaXWEIGHT){
			edges[v1][v2] = edges[v2][v1] = MaXWEIGHT;
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
ostream& operator << (ostream& out, MatrixGraph<VerStruct> gra){
	VerStruct v1, v2;
	int numV = gra.SizeOfVertices(), numE = gra.SizeOfEdge();
	out << numV << "," << numE << endl;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++){
		EdgeStruct weight = gra.graetWeight(i,j);
		if (weight > 0 && weight < MaXWEIgraHT){
			v1 = gra.GetValue(i);
			v2 = gra.GetValue(j);
			cout << "( " << v1 << ", " << v2 << " )" << endl;
		}
	}
	return out;
}

//////////////////////////////////////////////



////////////adjaceny List Graph/////////////////////////


template<class VerStruct>
LinkGraph<VerStruct>::LinkGraph(int size){
	maxVertices = size;
	numVertices = 0;
	numEdges = 0;
	dirOfGraph = Undirective;
	adjList = new Vertex<VerStruct>[maxVertices];
	if (adjList == nullptr){
		cerr << "memory allocated wrong!" << endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
		adjList[i].adj = nullptr;
}

template<class VerStruct>
LinkGraph<VerStruct>::~LinkGraph(){
	for (int i = 0; i < numVertices; i++){
		Edge * temp = adjList[i].adj;
		while (temp != nullptr){
			adjList[i].adj = temp->linker;
			delete temp;
			temp = adjList[i].adj;
		}
	}
	delete[] adjList;
}

template<class VerStruct>
VerStruct LinkGraph<VerStruct>::GetValue(int ver){
	return adjList[ver].data;
}

template<class VerStruct>
EdgeStruct LinkGraph<VerStruct>::GetWeight(int v1, int v2){
	if (v1 != -1 && v2 != -1){
		Edge * temp = adjList[v1].adj;
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
		Edge *temp = adjList[ver].adj;
		if (temp != nullptr)return temp->dest;
		else return -1;
	}
	else return -1;
}

/* The function is used for getting next edge of verx`s edge  */
template<class VerStruct>
int LinkGraph<VerStruct>::GetNextNeighbor(int ver, int verx){
	if (ver != 1){
		Edge *temp = adjList[ver].adj;
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
	adjList[numVertices++].data = vertex;
	return true;
}
template<class VerStruct>
bool LinkGraph<VerStruct>::RemoveVertice(int ver){
	Edge *temp= nullptr,  *sub = nullptr, *aux = nullptr;
	while (adjList[ver].adj != nullptr){
		temp = adjList[ver].adj;
		sub = adjList[temp->dest].adj;
		
		while (temp != nullptr && temp->dest != ver){
			aux = sub;
			sub = sub->linker;
		}
		if (sub != nullptr){
			if (aux != nullptr) adjList[temp->dest].adj = sub->linker;
			else aux->linker = sub->linker;
			delete sub;
		}
		adjList[ver].adj = temp->linker;
		delete temp;
		numEdges--;
	}
	numVertices--;
	adjList[ver].data = adjList[numVertices].data;
	temp = adjList[ver].adj = adjList[numVertices].adj;
	while (temp != nullptr){
		sub = adjList[temp->dest].adj;
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
			Edge *sub = nullptr, *temp = adjList[v1].adj;

			while (temp != nullptr && temp->dest != v2)
				temp = temp->linker;

			if (temp != nullptr) return false;
			temp = new Edge;
			sub = new Edge;
			temp->dest = v2;
			temp->cost = weight;
			temp->linker = adjList[v1].adj;
			adjList[v1].adj = temp;

			sub->dest = v1;
			sub->cost = weight;
			sub->linker = adjList[v2].adj;
			adjList[v2].adj = sub;
			numEdges++;
			return true;
		}
		else return false;
	}
	if (dirOfGraph == Directive){
		if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices){
			Edge *sub = nullptr, *temp = adjList[v1].adj;

			while (temp != nullptr && temp->dest != v2)
				temp = temp->linker;

			if (temp != nullptr) return false;
			temp = new Edge;
			sub = new Edge;
			temp->dest = v2;
			temp->cost = weight;
			temp->linker = adjList[v1].adj;
			adjList[v1].adj = temp;
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
			Edge *temp = adjList[v1].adj, *sub = nullptr, *aux = temp;
			while (temp != nullptr && temp->dest != v2){
				temp = sub;
				temp = temp->linker;
			}
			if (temp != nullptr){
				if (temp == aux) adjList[v1].adj = temp->linker;
				else sub->linker = temp->linker;
				delete temp;
			}
			else return false;

			temp = adjList[v2].adj, sub = nullptr, aux = temp;
			while (temp != nullptr && temp->dest != v1){
				temp = sub;
				temp = temp->linker;
			}
			if (temp != nullptr){
				if (temp == aux) adjList[v2].adj = temp->linker;
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
			Edge *temp = adjList[v1].adj, *sub = nullptr, *aux = temp;
			while (temp != nullptr && temp->dest != v2){
				temp = sub;
				temp = temp->linker;
			}
			if (temp != nullptr){
				if (temp == aux) adjList[v1].adj = temp->linker;
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
		if (weight > 0 && weight < MaXWEIGHT){
			v1 = G.GetValue(i);
			v2 = G.GetValue(j);
			cout << "( " << v1 << ", " << v2 << " )" << endl;
		}
	}
	return out;
}
