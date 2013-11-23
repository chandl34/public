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

#include "Drawable.h"


class Touchable : public Drawable{	
public:
	Touchable(bool);
	virtual ~Touchable();	
	
	bool isMultiTouchable();	
	
	// Virtual methods
	virtual bool isTouching(const Coord2d<GLshort>&) = 0;
	
	virtual void push(GLshort, const Coord2d<GLshort>&) = 0;
	virtual void move(GLshort, const Coord2d<GLshort>&) = 0;
	virtual bool release(GLshort, const Coord2d<GLshort>&) = 0;
	
protected:
	bool multiTouchable;
};

#endif
