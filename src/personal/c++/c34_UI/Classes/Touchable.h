/*
 *  Touchable.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TOUCHABLE_H_
#define TOUCHABLE_H_

#include "Include.h"


class Touchable{	
public:
	Touchable(bool);
	//Touchable(GLshort);
	virtual ~Touchable();	
	
	//bool isTouchable() const;
	bool isMultiTouchable() const;
	
	// Virtual methods
	virtual bool isTouching(const Coord2d<GLshort>&) = 0;
	
	virtual bool push(GLshort, const Coord2d<GLshort>&) = 0;
	virtual bool move(GLshort, const Coord2d<GLshort>&) = 0;
	virtual bool release(GLshort, const Coord2d<GLshort>&) = 0;
	
protected:
	bool _multiTouchable;
	//GLshort _maxTouches;
};

#endif
