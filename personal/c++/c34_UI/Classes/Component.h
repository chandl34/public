/*
 *  Component.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/24/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Drawable.h"
#include "OffsetBase.h"
#include "SizeBase.h"
#include "Touchable.h"


class Component 
: public Drawable
, public OffsetBase
, public SizeBase
, public Touchable
{
public:
	Component(const Coord2d<double>& = Coord2d<double>(0.0, 0.0),
			  const Size2d<GLshort>& = Size2d<GLshort>(0.0, 0.0));
	virtual ~Component();
	
	//--- TOUCH ---//
	virtual bool isTouching(const Coord2d<GLshort>&);
	
	virtual bool push(GLshort, const Coord2d<GLshort>&);
	virtual bool move(GLshort, const Coord2d<GLshort>&);
	virtual bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	
};

#endif