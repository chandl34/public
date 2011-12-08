#include "AStarNode.h"

AStarNode::AStarNode(Coordinate* c, int s){
	coord = c; 
	status = s;
	parent = NULL;  
}

AStarNode::~AStarNode(){}

int AStarNode::getEstimate(){return estimate;}
void AStarNode::setEstimate(int e){estimate = e;}
int AStarNode::getPriority(){return priority;}
void AStarNode::findPriority(){priority = estimate + distance + changed();}
int AStarNode::getDistance(){return distance;}	
void AStarNode::setDistance(int d){distance = d;}
AStarNode* AStarNode::getParent(){return parent;}
void AStarNode::setParent(AStarNode* a){parent = a;}
bool AStarNode::hasJumped(){return jumped;}
void AStarNode::setJumped(bool j){jumped = j;}
Direction* AStarNode::getDirection(){return dir;}
void AStarNode::setDirection(Direction* d){dir = d;}

int AStarNode::getStatus(){return status;}
void AStarNode::setStatus(int s){status = s;}
Coordinate* AStarNode::getCoord(){return coord;}

void AStarNode::setNode(Node* n){node = n;}
Node* AStarNode::getNode(){return node;}

int AStarNode::changed(){
	if(parent == NULL || parent->getDirection() == dir)
		return 0;
	return 1;
}
