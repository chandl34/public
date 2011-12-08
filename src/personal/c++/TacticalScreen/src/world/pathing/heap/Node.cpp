#include "Node.h"

Node::Node(AStarNode* i){setItem(i); left = NULL; right = NULL; parent = NULL;}
Node::~Node(){item->setNode(NULL);}

void Node::setItem(AStarNode* i){item = i; i->setNode(this);}
AStarNode* Node::getItem(){return item;}

int Node::getValue(){return item->getPriority();}

void Node::setLeft(Node* l){left = l;}
Node* Node::getLeft(){return left;}
void Node::setRight(Node* r){right = r;}
Node* Node::getRight(){return right;}
void Node::setParent(Node* p){parent = p;}
Node* Node::getParent(){return parent;}
