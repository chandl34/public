/*
 *  Node.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Node.h"

Node::Node(HeapItem* i){
	item = i; 
	//setItem(i); 
	clear();
}

Node::~Node(){}

void Node::setItem(HeapItem* i){item = i; i->setNode(this);}
HeapItem* Node::getItem() const{return item;}
GLfloat Node::getValue() const{return item->getValue();}
void Node::clear(){parent = NULL; right = NULL; left = NULL;}
void Node::setLeft(Node* l){left = l;}
Node* Node::getLeft() const{return left;}
void Node::setRight(Node* r){right = r;}
Node* Node::getRight() const{return right;}
void Node::setParent(Node* p){parent = p;}
Node* Node::getParent() const{return parent;}

