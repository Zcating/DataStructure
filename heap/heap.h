#ifndef _Heap_H
#define _Heap_H
const int MAXSIZE = 50;
//use Array as storage structure 
struct Key {

};

template<class type>
class MinHeap{
private:
	type *Heap;
	int size;
	int MaxSize;
	void SiftUp(int);
	void SiftDown(int, int);
public:
	MinHeap(int size = MAXSIZE);
	~MinHeap(){ delete[] Heap; };
	type Front();
	bool Insert(const type&);
	bool Remove();
	bool Empty() const { return size == 0; }
	bool Full() const { return size == MaxSize; }
	int Size() const { return size; }
	void MakeEmpty(){ count = 0; }
};
#endif


template<class type>
MinHeap<type>::MinHeap(int size) : MaxSize(size), size(0){
	Heap = new type[MaxSize];
}

template<class type>
bool MinHeap<type>::Insert(const type& data){
	if (Full()) return false;
	Heap[size] = data;
	SiftUp(size);
	size++;
	return true;
}

//Remove Heap[0]
template<class type>
bool MinHeap<type>::Remove(){
	if (Empty()) return false;
	Heap[0] = Heap[size - 1];
	size--;
	SiftDown(0, size - 1);
	return true;
}

//Get Heap[0]
template<class type>
type MinHeap<type>::Front(){
	return Heap[0];
}


template<class type>
void MinHeap<type>::SiftDown(int start, int num){

	int index = start, chlidIndex = 2 * index + 1;
	type temp = Heap[sub];
	while (childIndex <= num){
		if (childIndex < num && Heap[childIndex] > Heap[childIndex + 1]) aux++;
		if (temp <= Heap[childIndex]) break;
		else {
			Heap[index] = Heap[childIndex];
			index = childIndex;
			childIndex = 2 * childIndex + 1;
		}
		Heap[index] = temp;
	}
}

template<class type>
void MinHeap<type>::SiftUp(int start){
	int childIndex = start, index = (index - 1) / 2;
	type temp = Heap[index];
	while (childIndex > 0){
		if (Heap[childIndex] <= temp) break;
		else{
			Heap[childIndex] = Heap[index];
			childIndex = index;
			index = (index - 1) / 2;
		}
	}
	Heap[childIndex] = temp;
}
