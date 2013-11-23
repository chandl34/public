/*
 *  HeapItem.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef HEAP_ITEM_H_
#define HEAP_ITEM_H_

#include "Include.h"

class Node;


class HeapItem{
public:
	HeapItem();
	virtual ~HeapItem();
	
	Node* getNode() const;
	void setNode(Node*);	
	
	virtual double getValue() const = 0;
	
private:
	Node* node;
};

#endif