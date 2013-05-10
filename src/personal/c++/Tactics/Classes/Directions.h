/*
 *  Directions.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DIRECTIONS_H_
#define DIRECTIONS_H_

#include "Include.h"

class AStarNode;


class Directions{
public:	
	Directions(AStarNode*);
	
	GLshort getNext();
	GLshort peek() const;
	void push(GLshort);
	bool isEmpty() const;
	
	const list<GLshort>& getList() const;
	
private:
	list<GLshort> _direction;
};

#endif


