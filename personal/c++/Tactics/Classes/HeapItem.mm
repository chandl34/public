/*
 *  HeapItem.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "HeapItem.h"

#include "Node.h"


HeapItem::HeapItem(){
	node = new Node(this);
}

HeapItem::~HeapItem(){
	delete node;
}


Node* HeapItem::getNode() const{return node;}
void HeapItem::setNode(Node* n){node = n;}
