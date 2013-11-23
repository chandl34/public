// Jonathan Chandler
// Node.C

#include "Node.h"

Node::Node(){
	parent = NULL;
	left = NULL;
	right = NULL;
	data = 0;
}

Node::Node(Node* newParent, int newData){
	parent = newParent;
	left = NULL;
	right = NULL;
	data = newData;
}
