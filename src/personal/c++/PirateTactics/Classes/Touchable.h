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
	Touchable();
	virtual ~Touchable();	
	
	bool isMultiTouchable();	
	
	// Multi-touchable methods
	virtual bool push(GLshort, const Coord2d<GLshort>&);
	virtual void move(GLshort, const Coord2d<GLshort>&);
	virtual void release(GLshort, const Coord2d<GLshort>&);
	
protected:
	bool multiTouchable;
};

#endif
