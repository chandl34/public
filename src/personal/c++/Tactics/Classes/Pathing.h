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

class AStarNode;
class Directions;
class GridBlock;
class Unit;


enum{NOT_BLOCKED, BLOCKED_BY_DOOR, BLOCKED};


class Pathing{
public:	
	Pathing();
	~Pathing();
	
	static Directions* getDirections(Unit*, const Coord2d<GLshort>&, const Coord2d<GLshort>&);
		
private:
	static AStarNode* _node[MAP_BLOCK_X][MAP_BLOCK_Y];
	static Heap _openHeap;
	static GLshort _open;
	static GLshort _closed;
	
	static double findEstimate(const Coord2d<GLshort>&, const Coord2d<GLshort>&);
	static GLshort canGoTo(Unit*, const Coord2d<GLshort>&, const Coord2d<GLshort>&, GLshort);
	static void reset();
};

#endif

