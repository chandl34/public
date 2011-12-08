/*
 *  Directions.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Directions.h"


Directions::Directions(AStarNode* p){
	while(p->getParent() != NULL){
		direction.push(p->getDirection());
		p = p->getParent();
	}
}

Directions::~Directions(){
	
}


GLshort Directions::getNext(){
	if(direction.empty())
		return NULL;
	GLshort t = direction.top();
	direction.pop();
	return t;
}

GLshort Directions::peek() const{
	return direction.top();
}

void Directions::push(GLshort d){
	direction.push(d);
}

bool Directions::isEmpty() const{
	return direction.empty();
}

