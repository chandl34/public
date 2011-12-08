// Jonathan Chandler
// PriorityQueue.h

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
using namespace std;

#include "Node.h"

class PriorityQueue{
	public:
		PriorityQueue();
		~PriorityQueue();

		bool isEmpty();	
		void Push(int data);	// Adds data to the end of the queue
		int Pop();		// Removes front node, returns priority
		void Delete(int data);	// Removes first occurence of data
		int Peek();  		// Returns front priority
		void Empty(); 		// Empties Queue
		void PreOrder();	// Prints the prefix order

	private:
		Node *head, *tail;
		void PushSub(Node * node, int data);	// Recursive method for Push
		void DeleteSubTail(Node * node); 	// Locates new tail for Delete(int)
		bool DeleteSub(Node * node, int data);	// Recursive method for Delete(int)
		void EmptySub(Node * node);		// Recursive method for Empty()
		void Reheap(Node * node);		// Recursive resorting method
		void PreOrderSub(Node * node);		// Recursive method for PreOrder()
};

#endif
