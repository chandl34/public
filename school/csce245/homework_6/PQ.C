#include "PQ.h"
#include <iostream>
using namespace std;
Node::Node(Item* im) {
    item = im;
    left = right = parent = NULL;
}

bool PQ::isEmpty() {
    if (head == NULL) return true;
    else return false;
}


void PQ::insert(Item* item) {
    if (head == NULL) {
        head = new Node(item);
        head->parent = NULL;
        tail = head;
        return;
    }
    Node* newN = new Node(item);
    addToTail(newN);
    shiftUp(tail);
}

void PQ::shiftUp(Node* newN) {
    Node* p = newN->parent;
    Item* temp = newN->item;
    if (p == NULL) return;//has only head
    while (p != NULL && newN->item->getKey() < p->item->getKey()) {
        temp = p->item; //swap
        p->item = newN->item;
        newN->item = temp;
        newN = p;
        p = p->parent;
    }
}

void PQ::shiftDown(Node* newN) {
    Node* p1;
    Node* p2;
    Item* temp = newN->item;
    int key = temp->getKey();
    int key1, key2;
    while (newN != NULL) {
        p1 = newN->left;
        p2 = newN->right;
        if (p1 == NULL) return;
        if (p2 != NULL) {
            key1 = p1->item->getKey();
            key2 = p2->item->getKey();
            if (key > key1 && key > key2) {//larger than both
                if (key1 >= key2) {
                    swap(newN, p2); //swap it with right
                    newN = p2;
                }
                else {
                    swap(newN, p1);
                    newN = p1;
                }
            }
            else if (key > key1) {
                swap(newN, p1);//larger than left
                newN = p1;
            }
            else if (key > key2) {
                swap (newN, p2);//larger than right
                newN = p2;
            }
            else break;//not larger than any
        }
        else if (key > p1->item->getKey()) { //no right and larger than left
            swap(newN, p1);
            newN = p1;
        }
        else break;
    }
    return;
}

void PQ::swap(Node* n1, Node* n2) { //swap itmes
    Item* tmp = n1->item;
    n1->item = n2->item;
    n2->item = tmp;
    return;
}

Node* PQ::findParent() const { //used by insert
    Node* temp = tail; //tail must not be NULL
    if (temp->parent == NULL) return temp;//only head
    if (temp->parent->right == NULL) return temp->parent; 
    //tail has no right sibling
    while (temp->parent != NULL && temp == temp->parent->right) 
        temp = temp->parent;
    if (temp->parent == NULL) { //right branch of head is full
        temp = head;
        while (temp->left != NULL && temp->right != NULL) temp = temp->left;
    }
    else {
        if (temp->right == NULL) return temp;
        temp = temp->parent->right; //jump to the next branch
        while (temp->left != NULL && temp->right != NULL) temp = temp->left;
    }
    return temp;
}

Node* PQ::findParentLeft() const { //used by remove
    Node* temp = tail; //tail must not be NULL
    if (temp->parent == NULL) return NULL;//only head
    if (temp->parent->right != NULL) return temp->parent; 
    //tail's parent has right
    
    while (temp->parent != NULL && temp == temp->parent->left)
        temp = temp->parent;
    if (temp->parent == NULL) { //tail is the only one in the last level
        temp = head;
        while (temp->left != NULL && temp->right != NULL) temp = temp->right;
    }
    else {
        if (temp->left == NULL) return temp;
        temp = temp->parent->left; //jump to the next branch
        while (temp->left != NULL && temp->right != NULL) temp = temp->right;
    }
    return temp;
}

void PQ::addToTail(Node* n) {
    Node* p = tail;
    p = findParent();
    if (p == NULL) { //only head
        head->left = n;
        n->parent = head;
    }
    if (p->left == NULL) p->left = n; //add as left
    else p->right = n;
    tail = n;
    n->parent = p;
    return;
}

Item* PQ::get(void) {
    Item* im;
    if (head == NULL) return NULL; // in case the queue is empty
    im = head->item;
    //delete n; get will not remove head
    return im;
}

Node* PQ::find(Item* im, Node* newN) {
    Node* p1;
    Node* p2;
    Node* result;
    if (newN == NULL) return NULL;
    result = NULL;
    if (newN->item == im) return newN;
    p1 = newN->left;
    p2 = newN->right;
    if (p1 != NULL) { //smaller than left
        result = find(im, p1);
    }
    if (result != NULL) return result; //find, return
    if (p2 != NULL) {
        result = find(im, p2);
    }
    return result;
}

void PQ::remove(Item* im) {
    if (head == NULL) return; //no head
    Node* p;
    Item* oldItem;
    Node* oldtail;
    Node* found = find(im, head);
    if (found == NULL) {
        cout << "Not found\n";
        return;
    }
    if (found == head) {//only head
        removeHead();
        return;
    }

    //find new tail position
    p = findParentLeft();//p can't be tail. if head has one child, p==head
    oldItem = tail->item;
    oldtail = tail;
    if (p == head) {
        if (tail == head->left) tail = head; //tail is the only child of head
        else tail = head->left;
    }
    else if (tail->parent == p) tail = p->left;
    else if (p->left == NULL) tail = p; //p is the right most of previous level
    else tail = p->right;
    
    if (oldtail == oldtail->parent->left) oldtail->parent->left = NULL;
    else oldtail->parent->right = NULL;
    if (found != oldtail) {//if it is not tail
        found->item = oldItem;
        shiftDown(found); //from found
    }
    delete oldtail;
    return;
}
Item* PQ::removeHead(void) {//remove the first, delete the node
    if (head == NULL) return NULL; //no head
    Item* im;
    Node* p;
    Item* oldItem;
    Node* oldtail;
    im = head->item;
    if (head == tail) {//only head
        delete head;
        head = tail = NULL;
        return im;
    }
    p = findParentLeft();//p can't be tail. if head has one child, p==head
    oldItem = tail->item;
    oldtail = tail;
    if (p == head) {
        if (tail == head->left) tail = head; //tail is the only child of head
        else tail = head->left;
    }
    else if (tail->parent == p) tail = p->left; 
    else if (p->left == NULL) tail = p; //p is the right most of previous level
    else tail = p->right;
    
    if (oldtail == oldtail->parent->left) oldtail->parent->left = NULL;
    else oldtail->parent->right = NULL;

    delete oldtail;
    head->item = oldItem;
    shiftDown(head); //from head
    return im; //return oldhead's item
}
