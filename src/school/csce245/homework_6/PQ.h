#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_
#include "Item.h"
#include <stdlib.h>
class Node {
    Node* left;
    Node* right;
    Node* parent;
    Item* item;
    friend class PQ;
    Node() {left = right = parent = NULL; 
        item = NULL; 
    }
    public:
    Node(Item* im);
    ~Node() { 
    }
};

class PQ{
    Node* head;
    Node* tail;
    size_t length;
    void addToTail(Node* n);
    Node* findParent() const;
    Node* findParentLeft() const;
    void swap(Node* n1, Node* n2); //swap items only
    Node* find(Item*, Node*);

    void clean(Node* n) {
        if (n == NULL) return;
        if (n->left != NULL) clean(n->left);
        if (n->right != NULL) clean(n->right);
        delete n;
    }

    void deepClean(Node* n) {
        if (n == NULL) return;
        if (n->left != NULL) clean(n->left);
        if (n->right != NULL) clean(n->right);
        delete n->item; //also clean the items
        delete n;
    }
public:
    void deepClean() {
        deepClean(head);
    }
    PQ():head(NULL),tail(NULL),length(0) {}
    ~PQ() {
        clean(head);
    }
    void insert(Item* item);
    void shiftUp(Node* n);
    void shiftDown(Node* n);
    bool isEmpty();
    Item* get(void);
    Item* removeHead(void);
    void remove(Item*);
};
#endif
