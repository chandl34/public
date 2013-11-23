// Jonathan Chandler
// PriorityQueue.C

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(){
	head = NULL;
	tail = NULL;
}

PriorityQueue::~PriorityQueue(){
	Empty();
}

bool PriorityQueue::isEmpty(){
	return head == NULL;
}

void PriorityQueue::Push(int data){
	if(isEmpty()){				// First element
		head = new Node(NULL, data);
		tail = head;
	}
	else{
		if(tail == head){		// Second element
			head->left = new Node(head, data);
			tail = head->left;
		}
		else				// All later elements
			PushSub(tail, data);
		Reheap(tail);
	}	
}

void PriorityQueue::PushSub(Node * node, int data){
        Node *prevNode = node;
        node = node->parent;
        if(node->right == NULL){		// Parent had one child
                node->right = new Node(node, data);
                tail = node->right;
        }
	else if((node->right == prevNode) && (node != head))  // Going up the tree
               	PushSub(node, data);  			 			
       	else{
               	if(node->right != prevNode)	// False if starting a new level
               		node = node->right;
       	        while(node->left != NULL)
               	        node = node->left;
               	node->left = new Node(node, data);
        	tail = node->left;
        }
}

int PriorityQueue::Pop(){
	if(head != NULL){
		int temp = head->data;
		Delete(temp);
		return temp;
	}
	return 0;
}

void PriorityQueue::Delete(int data){
	if(head == NULL)
		return;
	if(head->data == data){
                if(head == tail){
                        delete head;
                        head = NULL;
                }
	}
	if(!DeleteSub(head, data) && head != NULL)  // head check to prevent true
		cout << "VALUE NOT FOUND" << endl;  //  when last element deleted
}

bool PriorityQueue::DeleteSub(Node * node, int data){ // boolean so that only
	if(node == NULL)			      //  first instance of data
		return false;			      //   is deleted
	if(node->data == data){
    		node->data = tail->data;
       		Node *temp = tail;
        	if(temp->parent->right == temp)	   // Dereferencing old tail
        		temp->parent->right = NULL;
        	else
        		temp->parent->left = NULL;
	        DeleteSubTail(temp); 		// Locates and sets new tail
		if(node != temp)		// Disallows unnecessary reheap
			Reheap(node);		//  if tail is deleted
		delete temp;
		return true;
  	}
        if(DeleteSub(node->left, data))
		return true;
        if(DeleteSub(node->right, data))
		return true;
	return false;	
}

void PriorityQueue::DeleteSubTail(Node * node){  // Traverses an opposite route
	Node *prevNode = node;			 //  from PushSub
        node = node->parent;
	if(node->left != NULL){
		if(node->right == NULL)
			tail = node->left;
		else if((node->left == prevNode) && (node != head))
			DeleteSubTail(node);
		else{
			if(node->left != prevNode)
				node = node->left;
			while(node->right != NULL)
				node = node->right;
			tail = node;
		}
	}
	else{
		if(node == head)
			tail = head;
		else
			DeleteSubTail(node);
	}
}


int PriorityQueue::Peek(){
	return head->data;
}

void PriorityQueue::Empty(){
	if(head != NULL){
		EmptySub(head->left);
		EmptySub(head->right);
		delete head;
		head = NULL;
	}
}

void PriorityQueue::EmptySub(Node * node){
	if(node != NULL){
		EmptySub(node->left);	
		EmptySub(node->right);
		delete node;
	}
}

void PriorityQueue::Reheap(Node * node){
	if(node != head) {
		if(node->parent->data > node->data){
			int temp = node->data;
			node->data = node->parent->data;
			node->parent->data = temp;
			Reheap(node->parent);
		}
	}
	if(node->left != NULL){
		if(node->left->data < node->data){
			int temp = node->data;
                        node->data = node->left->data;
                        node->left->data = temp;
                        Reheap(node->left);
		}
	}
	if(node->right != NULL){
                if(node->right->data < node->data){
                        int temp = node->data;
                        node->data = node->right->data;
                        node->right->data = temp;
                        Reheap(node->right);
                }
        }
}

void PriorityQueue::PreOrder(){
	if(head == NULL)
		cout << "EMPTY LIST";
	else{
		cout << head->data << " ";
		if(head == tail) cout << "<-TAIL ";
		PreOrderSub(head->left);
		PreOrderSub(head->right);
	}
	cout << endl;	
}

void PriorityQueue::PreOrderSub(Node * node){
	if(node != NULL){
		cout << node->data << " ";
		if(node == tail) cout << "<-TAIL ";
	        PreOrderSub(node->left);
       	 	PreOrderSub(node->right);
	}
}
