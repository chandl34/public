/*
 *  HitTest.cpp
 *  When Pirates Attack
 *
 *  Created by Jonathan Chandler on 2/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "HitTest.h"

	
bool pointInQuad(const Coord2d<GLshort>& p, const Coord2d<double>& tl, const Size2d<GLshort>& s)
{	
	return (p[X] >= tl[X] && p[X] < tl[X] + s[X] && 
			  p[Y] >= tl[Y] && p[Y] < tl[Y] + s[Y]);
}
