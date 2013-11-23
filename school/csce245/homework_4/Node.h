// Jonathan Chandler
// Node.h

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
using namespace std;

class Node{
	public:		
		Node();
 		Node(Node* newParent, int newData);
        	friend class PriorityQueue;

	private:
		Node *parent, *left, *right;
		int data;		
};

#endif
