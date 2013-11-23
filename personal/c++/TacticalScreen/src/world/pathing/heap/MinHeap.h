#ifndef MINHEAP_H_
#define MINHEAP_H_

#include "Node.h"

class MinHeap{
public:
	MinHeap();
	virtual ~MinHeap();
	
	bool isEmpty();
	void clear();
	
	void push(AStarNode*);
	AStarNode* pop();	
	void reheap(Node*);	

	void print();
	
private:
	Node* head;
	Node* tail;	

	void shiftUp(Node*);
	void shiftDown(Node*);
	void swap(Node*, Node*);
	void clearSub(Node*);
	void pushSub(Node*, AStarNode*);
	void popSub(Node*);
	void printSub(Node*, int);
};

#endif /*MINHEAP_H_*/
