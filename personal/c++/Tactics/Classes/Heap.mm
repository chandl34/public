/*
 *  Heap.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Heap.h"

#include "HeapItem.h"
#include "Node.h"


Heap::Heap(bool mh){
	head = NULL;
	tail = NULL;
	minHeap = mh;
	if(minHeap)
		comp = &compMin;
	else
		comp = &compMax;
}


bool Heap::isEmpty() const{return head == NULL;}

void Heap::clear(){
	clearSub(head);
	head = NULL;
	tail = NULL;
}

void Heap::clearSub(Node* n){
	if(n != NULL){
		clearSub(n->getLeft());
		clearSub(n->getRight());
		//delete n->getItem();
		//delete n;
		n->clear();
	}
}

void Heap::push(HeapItem* i){
	if(isEmpty()){
		//head = new Node(i);
		head = i->getNode();
		tail = head;
	}	
	else{
		if(head == tail){
			//head->setLeft(new Node(i));
			head->setLeft(i->getNode());
			tail = head->getLeft();
			tail->setParent(head);
		}	
		else{
			Node* tailParent = tail->getParent();
			if(tailParent->getRight() == NULL){
				//tailParent->setRight(new Node(i));
				tailParent->setRight(i->getNode());
				tail = tailParent->getRight();
				tail->setParent(tailParent);
			}			
			else
				pushSub(tail, i);
		}
		shiftUp(tail);
	}
}

void Heap::pushSub(Node* node, HeapItem* i){
	Node* parent = node->getParent();
	if(node == parent->getLeft()){
		node = parent->getRight();
		while(node->getLeft() != NULL)
			node = node->getLeft();
		//node->setLeft(new Node(i));
		node->setLeft(i->getNode());
		tail = node->getLeft();
		tail->setParent(node);
		
	}		
	else if(parent == head){
		node = parent->getLeft();
		while(node->getLeft() != NULL)
			node = node->getLeft();
		//node->setLeft(new Node(i));
		node->setLeft(i->getNode());
		tail = node->getLeft();
		tail->setParent(node);
	}
	else
		pushSub(parent, i);
}

HeapItem* Heap::pop(){
	if(!isEmpty()){
		HeapItem* p = head->getItem();
		if(head == tail){
			//delete head;
			head->clear();
			head = NULL;
			tail = NULL;
		}
		else{
			//head->setItem(tail->getItem());
			swap(head, tail);
			Node* tailParent = tail->getParent();
			if(tailParent->getRight() == tail){
				tailParent->setRight(NULL);
				//delete tail;
				tail->clear();
				tail = tailParent->getLeft();
			}
			else{
				tailParent->setLeft(NULL);
				popSub(tail);
			}
			shiftDown(head);
		}
		return p;
	}
	return NULL;
}

void Heap::popSub(Node* node){
	Node* parent = node->getParent(); 
	if(parent->getRight() == node){
		node = parent->getLeft();
		while(node->getRight() != NULL)
			node = node->getRight();
		//delete tail;
		tail->clear();
		tail = node;
	}
	else if(parent == head){
		node = parent;
		while(node->getRight() != NULL)
			node = node->getRight();
		//delete tail;
		tail->clear();
		tail = node;
	}
	else
		popSub(parent);
}

HeapItem* Heap::peek() const{
	if(head != NULL)
		return head->getItem();
	return NULL;
}

void Heap::reheap(Node* node){
	shiftUp(node);
	shiftDown(node);
}


void Heap::shiftUp(Node* node){
	while(node != head && comp(node, node->getParent())){
		swap(node, node->getParent());
		node = node->getParent();
	}		
}

void Heap::shiftDown(Node* node){
	if(node->getLeft() != NULL){
		if(node->getRight() != NULL){
			if(!comp(node->getLeft(), node->getRight())){
				if(comp(node->getRight(), node)){
					swap(node->getRight(), node);
					shiftDown(node->getRight());
				}
				return;
			}
		}
		if(comp(node->getLeft(), node)){
			swap(node->getLeft(), node);
			shiftDown(node->getLeft());
		}
	}
}

void Heap::print() const{
	printSub(head, 0);
	if(isEmpty())
		cout << "Empty" << endl;
}

void Heap::printSub(Node* n, int d) const{
	if(n != NULL){
		printSub(n->getRight(), d+1);
		for(int i = 0; i < d; ++i)
			cout << "\t";
		cout << n->getValue();
		if(n == head)
			cout << "h";
		if(n == tail)
			cout << "t";
		else if(n->getLeft() != NULL)
			cout << "<";
		cout << endl;
		printSub(n->getLeft(), d+1);
	}
}

void Heap::swap(Node* n1, Node* n2){
	HeapItem* i1 = n1->getItem();
	n1->setItem(n2->getItem());
	n2->setItem(i1);	
}

bool Heap::compMin(Node* v1, Node* v2){
	return v1->getValue() < v2->getValue();
}

bool Heap::compMax(Node* v1, Node* v2){
	return v1->getValue() > v2->getValue();
}

void Heap::setCompFunc(bool (*compare)(Node*, Node*)){
	comp = compare;
}
