/*
 *  PuzzleTouch.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Puzzle.h"


//--- TOUCH ---//
bool Puzzle::isTouching(const Coord2d<GLshort>& p)
{
	/*
	for(GLshort i = 0; i < size[X]; i++){
		for(GLshort j = 0; j < size[Y]; j++){
			if(piece[i][j]->isTouching(p))
				return true;
		}
	}
	 */
	return false;
}

void Puzzle::push(GLshort t, const Coord2d<GLshort>& p)
{	
	
}

void Puzzle::move(GLshort t, const Coord2d<GLshort>& p)
{	
	
}

bool Puzzle::release(GLshort t, const Coord2d<GLshort>& p)
{	
	return false;
}


