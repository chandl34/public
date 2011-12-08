#include "Selection.h"

Selection::Selection(){
	character = NULL;
	door = NULL;
	coord = NULL;
}

Selection::~Selection(){}

void Selection::setCharacter(Character* c){character = c;}
void Selection::setDoor(DoorModel* d){door = d;}
DoorModel* Selection::getDoor(){return door;}
void Selection::setType(int t){type = t;}
int Selection::getType(){return type;}
void Selection::setCoord(Coordinate* c){coord = c;}

Coordinate* Selection::getCoord(){
	if(door != NULL)
		return coord;
	else
		return character->getCoord();
}

Vertex* Selection::getCenter(){
	if(door != NULL)
		return NULL;
	else
		return character->getCharModel()->getModelWrapper(type)->getModel()->getCenter();
}
