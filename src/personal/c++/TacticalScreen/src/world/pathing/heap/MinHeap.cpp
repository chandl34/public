#include "MinHeap.h"

MinHeap::MinHeap(){
	head = NULL;
	tail = NULL;
}

MinHeap::~MinHeap(){clear();}

bool MinHeap::isEmpty(){return head == NULL;}

void MinHeap::clear(){
	clearSub(head);
	head = NULL;
	tail = NULL;
}

void MinHeap::clearSub(Node* n){
	if(n != NULL){
		clearSub(n->getLeft());
		clearSub(n->getRight());
		delete n;
	}
}

void MinHeap::push(AStarNode* i){
	if(isEmpty()){
		head = new Node(i);
		tail = head;
	}	
	else{
		if(head == tail){
			head->setLeft(new Node(i));
			tail = head->getLeft();
			tail->setParent(head);
		}	
		else{
			Node* tailParent = tail->getParent();
			if(tailParent->getRight() == NULL){
				tailParent->setRight(new Node(i));
				tail = tailParent->getRight();
				tail->setParent(tailParent);
			}			
			else
				pushSub(tail, i);
		}
		shiftUp(tail);
	}
}

void MinHeap::pushSub(Node* node, AStarNode* i){
	Node* parent = node->getParent();
	if(node == parent->getLeft()){
		node = parent->getRight();
		while(node->getLeft() != NULL)
			node = node->getLeft();
		node->setLeft(new Node(i));
		tail = node->getLeft();
		tail->setParent(node);

	}		
	else if(parent == head){
		node = parent->getLeft();
		while(node->getLeft() != NULL)
			node = node->getLeft();
		node->setLeft(new Node(i));
		tail = node->getLeft();
		tail->setParent(node);
	}
	else
		pushSub(parent, i);
}

AStarNode* MinHeap::pop(){
	if(!isEmpty()){
		AStarNode* p = head->getItem();
		if(head == tail){
			delete head;
			head = NULL;
			tail = NULL;
		}
		else{
			head->setItem(tail->getItem());
			Node* tailParent = tail->getParent();
			if(tailParent->getRight() == tail){
				tailParent->setRight(NULL);
				delete tail;
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

void MinHeap::popSub(Node* node){
	Node* parent = node->getParent(); 
	if(parent->getRight() == node){
		node = parent->getLeft();
		while(node->getRight() != NULL)
			node = node->getRight();
		delete tail;
		tail = node;
	}
	else if(parent == head){
		node = parent;
		while(node->getRight() != NULL)
			node = node->getRight();
		delete tail;
		tail = node;
	}
	else
		popSub(parent);
}

void MinHeap::reheap(Node* node){
	shiftUp(node);
	shiftDown(node);
}


void MinHeap::shiftUp(Node* node){
	while(node != head && node->getParent()->getValue() > node->getValue()){
		swap(node, node->getParent());
		node = node->getParent();
	}		
}

void MinHeap::shiftDown(Node* node){
	if(node->getLeft() != NULL){
		if(node->getRight() != NULL){
			if(node->getRight()->getValue() <= node->getLeft()->getValue()){
				if(node->getRight()->getValue() < node->getValue()){
					swap(node->getRight(), node);
					shiftDown(node->getRight());
				}
				return;
			}
		}
		if(node->getLeft()->getValue() < node->getValue()){
			swap(node->getLeft(), node);
			shiftDown(node->getLeft());
		}
	}
}

void MinHeap::swap(Node* n1, Node* n2){
	AStarNode* i1 = n1->getItem();
	n1->setItem(n2->getItem());
	n2->setItem(i1);	
}

void MinHeap::print(){
	printSub(head, 0);
	if(isEmpty())
		cout << "Empty" << endl;
}

void MinHeap::printSub(Node* n, int d){
	if(n != NULL){
		printSub(n->getRight(), d+1);
		for(int i = 0; i < d; i++)
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
