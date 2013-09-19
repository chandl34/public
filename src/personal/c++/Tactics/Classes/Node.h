/*
 *  Node.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef NODE_H_
#define NODE_H_

class HeapItem;


class Node{
public:
	Node(HeapItem*);
	
	void setItem(HeapItem*);
	HeapItem* getItem() const;
	
	double getValue() const;
	
	void clear();
	void setLeft(Node*);
	Node* getLeft() const;
	void setRight(Node*);
	Node* getRight() const;
	void setParent(Node*);
	Node* getParent() const;
	
private:
	HeapItem* item;
    Node* left;
    Node* right;
    Node* parent;
	
};

#endif
