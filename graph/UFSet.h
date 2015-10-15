#ifndef _UFSET_H
#define _UFSET_H
const int UFDefaultSize = 50;
class  UFSet
{
public:
	 UFSet(int size = UFDefaultSize);
	 ~UFSet(){ delete[] parent; };
	 UFSet& operator = (UFSet& temp);
	 void Union(int r1, int r2);
	 int Find(int x);
	 void WeightedUnion(int r1, int r2);
private:
	int * parent;
	int currentSize;
};

 
#endif