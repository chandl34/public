
/*
 *  ComplexIcon.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COMPLEX_ICON_H_
#define COMPLEX_ICON_H_

#include "Icon.h"


class ComplexIcon : public Icon{
public:
	ComplexIcon(Image* = NULL, const Coord2d<double>& = Coord2d<double>(0, 0));
	virtual ~ComplexIcon();	
	
	//--- GENERAL ---//
	virtual void setOffset(double, double);
	
	void addIcon(Image*, const Coord2d<double>&);
	
	//---- DRAW ----//
	void draw(bool);
	
protected:
	void clear();
	
	//--- GENERAL ---//
	vector<Icon> _overlay;
};

#endif

