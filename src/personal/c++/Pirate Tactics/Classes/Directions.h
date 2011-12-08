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

#include "AStarNode.h"

class Directions{
public:	
	Directions(AStarNode*);
	virtual ~Directions();
	
	GLshort getNext();
	GLshort peek() const;
	void push(GLshort);
	bool isEmpty() const;
	
private:
	stack<GLshort> direction;
};

#endif


