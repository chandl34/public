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

#include "Include.h"

class HeapItem;
class Node;


class Heap{
public:
	Heap(bool);
	
	bool isEmpty() const;
	void clear();	
	void push(HeapItem*);
	HeapItem* pop();	
	HeapItem* peek() const;
	void reheap(Node*);	
	void print() const;
	
	void setCompFunc(bool (*)(Node*, Node*));
	
private:
	Node* head;
	Node* tail;	
	bool minHeap;
	bool (*comp)(Node*, Node*);
		
	void shiftUp(Node*);
	void shiftDown(Node*);
	void clearSub(Node*);
	void pushSub(Node*, HeapItem*);
	void popSub(Node*);
	void printSub(Node*, int) const;
	
	void swap(Node*, Node*);
	static bool compMin(Node*, Node*);
	static bool compMax(Node*, Node*);
};

#endif

