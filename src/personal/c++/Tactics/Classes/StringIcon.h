/*
 *  StringIcon.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/31/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STRING_ICON_H_
#define STRING_ICON_H_

#include "ComplexIcon.h"


enum{ALIGN_LEFT, CENTERED, ALIGN_RIGHT};
const GLshort SLASH_WIDTH = 6;
const GLshort HUNDRED_WIDTH = 15;


class StringIcon : public ComplexIcon
{
public:
	StringIcon(const string& = " ", const Coord2d<double>& = Coord2d<double>(0, 0), GLshort = ALIGN_LEFT);
	virtual ~StringIcon();	
	
	//--- GENERAL ---//
	void setString(const string&);
	
protected:
	GLshort _align;
	Coord2d<double> _alignPoint;
};

#endif


