#ifndef _MST_H
#define _MST_H
const int DefaultSize = 100;
struct MSTEdgeNode
{
	int start;
	int end;
	EdgeStruct key;
	MSTEdgeNode() : start(-1), end(-1), key(0){}
	bool operator <= (MSTEdgeNode & temp)const { return key <= temp.key; }
	bool operator ==(MSTEdgeNode & temp)const { return key == temp.key; }
	bool operator >  (MSTEdgeNode & temp)const { return key  >  temp.key; }
};

class MST{
protected:
	MSTEdgeNode * edgeValue;
	int maxSize;
	int currentSize;
	bool Insert(MSTEdgeNode & item);
public:
	MST(int size = DefaultSize - 1) : maxSize(size), currentSize(0){
		edgeValue = new MSTEdgeNode[size];
	}
	~MST(){}

	void KruskalAlogrithm(Graph<VerDataInfo> & gra);
	void PrimAlogrithm(Graph<VerDataInfo> & gra, const VerDataInfo);
	void PrimAlogrithm(Graph<VerDataInfo> & gra, const int ver);
	friend ostream & operator << (ostream & out, MST mstree);
};
#endif 