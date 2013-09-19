/*
 *  Movable.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MOVABLE_H_
#define MOVABLE_H_

#include "Include.h"


class Movable{
public:	
	Movable(const Coord2d<double>& = Coord2d<double>(0.0, 0.0));
	virtual ~Movable();
	
	//---- GENERAL ----//
	const Coord2d<double>& getOffset() const;
	double getOffset(GLshort) const;
	
	virtual void setOffset(double, double);
	void setOffset(Movable*);
	
protected:
	Coord2d<double> _offset;
};

#endif