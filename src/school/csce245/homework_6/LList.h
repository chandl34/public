// Jonathan Chandler
// LList.C

#ifndef _LLIST_H_
#define _LLIST_H_

#include <iostream>
using namespace std;

class LNode{
	private:
		LNode * next;
	public:
		int x, y;
		LNode(int x1, int y1){x = x1; y = y1; next = NULL;}
		LNode * getNext(){return next;}
		void setNext(LNode * node){next = node;}
};

class LList{
	public:
		LNode * head;
		LNode * cursor;
		LList(){head = NULL; cursor = NULL;}
		~LList(){
			cursor = head;
			while(head != NULL){
				cursor = head->getNext();
				delete head;
				head = cursor;
			}
		}
		void push(int i, int j){
			LNode * node = new LNode(i, j);
			if(head == NULL){
				head = node;
				cursor = head;
			}
			else{
				cursor->setNext(node);
				cursor = cursor->getNext();
			}
		}
		LNode * get(int number){
			LNode * temp = head;
			for(int i = 0; i < number; i++)
				temp = temp->getNext();
			return temp;
		}
};

#endif
