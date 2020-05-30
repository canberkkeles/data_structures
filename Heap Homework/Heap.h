#ifndef HEAP_H
#define HEAP_H

#include <vector>

struct Job{

	int id;
	int deadline;

	Job(){
		id = -1;
		deadline = -1;
	}

	Job(int jid, int jdeadline){
		id = jid;
		deadline = jdeadline;
	}

	bool operator <(const Job & j){
		return deadline < j.deadline;
	}

	bool operator >(const Job & j){
		return deadline > j.deadline;
	}

	bool operator ==(const Job & j){
		return deadline == j.deadline;
	}
};

struct Worker{

	int id;
	Job* assigned;

	Worker(int wid,Job & wassigned){
		id = wid;
		assigned = new Job(wassigned.id,wassigned.deadline);
	}

	Worker(){
		id = -1;
		assigned = nullptr;
	}


	bool operator >(const Worker & w){
		if(*assigned > *w.assigned){
			return true;
		}

		else if(*assigned  == *w.assigned){
			if(id > w.id) return true;
			return false;
		}

		return false;

	}

	bool operator <(const Worker & w){
		if(*assigned < *w.assigned){
			return true;
		}

		else if(*assigned == *w.assigned){
			if(id < w.id) return true;
			return false;
		}

		return false;

	}

	void operator-(const int & d){
		assigned -> deadline -= d;
	}

};

template <class Comparable>
class WorkerHeap{
public:

	WorkerHeap(int capacity = 100);
	bool isEmpty() const;
	bool isFull() const;


	void insert(Comparable & x);
	void deleteMin();
	void deleteMin(Comparable & minItem);
	Comparable getMin();

	void decreaseElements(int t);

private:
	int currentSize;
	std::vector<Comparable> container;

	void buildHeap(std::vector<Comparable> Input);
	void perculateDown(int hole);
};

#include "Heap.cpp"
#endif