#include "Heap.h"


/*
INSERT ITEM X INTO THE HEAP
DUPLICATES ARE ALLOWED
RESIZE IF FULL
*/
template <class Comparable>
void WorkerHeap<Comparable>::insert(Comparable & x){
	if(isFull())
		container.resize(2 * container.size());

	//CREATE A HOLE AT THE LAST LOCATION OF THE container
	int hole = ++currentSize;
	for(;hole > 1 && x < container[hole/2] ; hole /= 2){ //MOVE THE HOLE UP
		container[hole] = container[hole/2];
	}
	container[hole] = x; //INSERT THE ELEMENT
}

/*
DELETE THE MINIMUM ELEMENT
FROM THE HEAP
*/
template <class Comparable>
void WorkerHeap<Comparable>::deleteMin(){
	//Move the last element to the first and shrink the container
	container[1] = container[currentSize--];
	perculateDown(1);
}
/*
DELETE THE MINIMUM ELEMENT 
FROM THE HEAP AND
HOLD THE VALUE INSIDE
REFERENCE PARAMETER
*/
template <class Comparable>
void WorkerHeap<Comparable>::deleteMin(Comparable & minItem){
	//Move the last element to the first and shrink the container
	minItem = container[1];
	//Hold the min item inside the reference parameter
	container[1] = container[currentSize--];
	perculateDown(1);
}

/*
INTERNAL METHOD TO PERCOLATE DOWN
HOLE IS THE INDEX
*/

template<class Comparable>
void WorkerHeap<Comparable>::perculateDown(int hole){
	int child;
	Comparable temp = container[hole];

	for(;hole *2 <= currentSize;hole = child){
		child = hole * 2;
		if(child != currentSize && container[child] > container[child+1])
			child++;
		if(container[child] < temp)
			container[hole] = container[child];
		else
			break;
	}
	container[hole] = temp;
}

/*
BUILD A HEAP FROM AN
UNSORTED OR ARBITRARY
VECTOR
*/
template<class Comparable>
void WorkerHeap<Comparable>::buildHeap(std::vector<Comparable> Input){
	container = Input;
	currentSize = Input.size();
	for(int i = currentSize / 2 ; i > 0 ; i--)
		perculateDown(i);
}

/*
CHECK IF THE HEAP 
IS EMPTY OR NOT
*/
template<class Comparable>
bool WorkerHeap<Comparable>::isEmpty() const{
	return currentSize == 0;
}

/*
CHECK IF THE HEAP 
IS FULL OR NOT
*/
template<class Comparable>
bool WorkerHeap<Comparable>::isFull() const{
	return currentSize == container.size();
}
/*
DEFAULT CONSTRUCTOR FOR HEAP CLASS
*/
template<class Comparable>
WorkerHeap<Comparable>::WorkerHeap(int capacity = 100): container(capacity),currentSize(0){}

/*
GETS THE MINUMUM ELEMENT,
DOES NOT DELETE THE ELEMENT!
*/
template <class Comparable>
Comparable WorkerHeap<Comparable>::getMin(){
	return container[1];
}

/*
DECREASES ALL THE ELEMENTS
BY THE GIVEN PARAMETER T
*/
template<class Comparable>
void WorkerHeap<Comparable>::decreaseElements(int t){
	for(int i = 1 ; i <= currentSize ; i++)
		container[i] - t;
}

