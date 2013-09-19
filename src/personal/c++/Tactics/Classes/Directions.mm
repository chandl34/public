/*
 *  Directions.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Directions.h"

#include "AStarNode.h"


Directions::Directions(AStarNode* p)
{
	while(p->getParent() != NULL){
		_direction.push_front(p->getDirection());
		p = p->getParent();
	}
}


GLshort Directions::getNext()
{
	if(_direction.empty())
		return NULL;
	GLshort t = _direction.front();
	_direction.pop_front();
	return t;
}

GLshort Directions::peek() const
{
	return _direction.front();
}

void Directions::push(GLshort d)
{
	_direction.push_front(d);
}

bool Directions::isEmpty() const
{
	return _direction.empty();
}


const list<GLshort>& Directions::getList() const
{
	return _direction;
}