/*
 *  RangeNode.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef RANGE_NODE_H_
#define RANGE_NODE_H_

#include "HeapItem.h"


class RangeNode : public HeapItem{
public:
	RangeNode(const Coord2d<GLshort>&, const Coord2d<GLshort>&, GLshort = 0);
	RangeNode(const Coord2d<GLshort>&, double, GLshort = 0);
	
	double getValue() const;
	GLshort getCost() const;
	
	const Coord2d<GLshort>& getCoord() const;
	GLshort getCoord(GLshort) const;
	
private:	
	Coord2d<GLshort> coord;
	double dist;
	GLshort cost;
};


#endif