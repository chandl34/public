/*
 *  Pathing.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PATHING_H_
#define PATHING_H_

#include "Heap.h"
#include "AStarNode.h"

class Directions;

class Pathing{
public:	
	Pathing();
	~Pathing();
	
	static Directions* getDirections(const Coord2d<GLshort>&, const Coord2d<GLshort>&);
		
private:
	static AStarNode* node[][MAP_BLOCK_Y];
	static Heap openHeap;
	static GLshort open;
	static GLshort closed;
	
	static GLfloat findEstimate(const Coord2d<GLshort>&, const Coord2d<GLshort>&);
	static bool canGoTo(const Coord2d<GLshort>&, const Coord2d<GLshort>&, GLshort);
	static void reset();
};

#include "LevelMap.h"

#endif

