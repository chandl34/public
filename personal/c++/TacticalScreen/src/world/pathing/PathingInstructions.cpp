#include "PathingInstructions.h"

PathingInstructions::PathingInstructions(LevelMap* m){
	map = m;
	destination = new stack<AStarNode*>;
	charList = new list<Coordinate*>;
}

PathingInstructions::~PathingInstructions(){
	delete destination;
	delete charList;
}


void PathingInstructions::pushPath(AStarNode* p){
	while(p->getParent() != NULL){
		destination->push(p);
		p = p->getParent();
	}
}

void PathingInstructions::addCharLoc(Coordinate* c){charList->push_back(c);}

bool PathingInstructions::charMoved(){
	for(list<Coordinate*>::iterator i = charList->begin(); i != charList->end(); i++){
		if(map->getBlock(*i)->getCharacter() == NULL)
			return true;
	} 	
	return false;
}

AStarNode* PathingInstructions::getNext(){
	if(destination->empty())
		return NULL;
	AStarNode* t = destination->top();
	destination->pop();
	return t;
}

AStarNode* PathingInstructions::peek(){
	return destination->top();
}

bool PathingInstructions::isEmpty(){
	return destination->empty();
}
