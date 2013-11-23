/*
 *  RangeNode.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "RangeNode.h"


RangeNode::RangeNode(const Coord2d<GLshort>& t, const Coord2d<GLshort>& o, GLshort c) : coord(t){	
	double x = t[X] - o[X];
	double y = t[Y] - o[Y];
	dist = sqrt(x*x + y*y);
	cost = c;
}

RangeNode::RangeNode(const Coord2d<GLshort>& t, double d, GLshort c) : coord(t){
	dist = d;
	cost = c;
}

double RangeNode::getValue() const{
	return dist;
}

GLshort RangeNode::getCost() const{
	return cost;
}

const Coord2d<GLshort>& RangeNode::getCoord() const{
	return coord;
}

GLshort RangeNode::getCoord(GLshort c) const{
	return coord[c];
}
