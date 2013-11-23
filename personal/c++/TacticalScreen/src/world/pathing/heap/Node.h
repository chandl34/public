#ifndef NODE_H_
#define NODE_H_

#include "../AStarNode.h"

class Node{
public:
	Node(AStarNode*);
	virtual ~Node();
	
	void setItem(AStarNode*);
	AStarNode* getItem();
	
	int getValue();
	
	void setLeft(Node*);
	Node* getLeft();
	void setRight(Node*);
	Node* getRight();
	void setParent(Node*);
	Node* getParent();
	
private:
	AStarNode* item;
    Node* left;
    Node* right;
    Node* parent;
	
};

#endif /*NODE_H_*/
