/*
 *  Heap.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HEAP_H_
#define HEAP_H_

#include "Node.h"

class Heap{
public:
	Heap(bool);
	virtual ~Heap();
	
	bool isEmpty() const;
	void clear();	
	void push(HeapItem*);
	HeapItem* pop();	
	HeapItem* peek() const;
	void reheap(Node*);	
	void print() const;
	
private:
	Node* head;
	Node* tail;	
	bool minHeap;
		
	void shiftUp(Node*);
	void shiftDown(Node*);
	void clearSub(Node*);
	void pushSub(Node*, HeapItem*);
	void popSub(Node*);
	void printSub(Node*, int) const;
	
	void swap(Node*, Node*);
	bool compare(GLfloat, GLfloat) const;
};

#endif

