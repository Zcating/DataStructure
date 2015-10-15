
#include "UFSet.h"
UFSet::UFSet(int size){
	currentSize = size;
	parent = new int[currentSize];
	for (int i = 0; i < currentSize; i++) parent[i] = -1;
}

int UFSet::Find(int x){
	while (parent[x] >= 0) x = parent[x];
	return x;
}

void  UFSet::Union(int r1, int r2){
	parent[r1] += parent[r2];
	parent[r2] = r1;
}

UFSet & UFSet::operator = (UFSet & temp){
	return temp;
}

void UFSet::WeightedUnion(int r1, int r2){
	int sub1 = Find(r1), sub2 = Find(r2), temp;
	if (sub1 != sub2){
		temp = parent[sub1] + parent[sub2];
		if (parent[sub2] < parent[sub1]){
			parent[sub1] = sub2;
			parent[sub2] = temp;
		}
		else {
			parent[sub2] = sub1;
			parent[sub1] = temp;
		}	
	}
}

