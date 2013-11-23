
/*
 *  CompositeIcon.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COMPLEX_ICON_H_
#define COMPLEX_ICON_H_

#include "BaseIcon.h"

#include "Icon.h"


class CompositeIcon : public BaseIcon{
public:
	CompositeIcon(const Coord2d<double>& = Coord2d<double>(0, 0));
	virtual ~CompositeIcon();	
	
	//--- GENERAL ---//
	void clear();
	virtual void setOffset(double, double);
	
	void addIcon(Image*, const Coord2d<double>& = Coord2d<double>(0, 0));
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- TOUCH ---//
	bool isTouching(const Coord2d<GLshort>&);
	
	virtual void push(GLshort, const Coord2d<GLshort>&);
	virtual void move(GLshort, const Coord2d<GLshort>&);
	virtual bool release(GLshort, const Coord2d<GLshort>&);
	
protected:
	//--- GENERAL ---//
	vector<Icon> overlay;
};



// Non-member Functions
void addIcon(CompositeIcon*, void*);


#endif

