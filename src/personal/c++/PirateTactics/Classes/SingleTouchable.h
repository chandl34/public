/*
 *  SingleTouchable.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SINGLE_TOUCHABLE_H_
#define SINGLE_TOUCHABLE_H_

#include "Touchable.h"

class SingleTouchable : public Touchable{	
public:
	SingleTouchable();
	virtual ~SingleTouchable();	
	
	virtual bool push(const Coord2d<GLshort>&) = 0;
	virtual void move(const Coord2d<GLshort>&) = 0;
	virtual void release(const Coord2d<GLshort>&) = 0;	
};

#endif


