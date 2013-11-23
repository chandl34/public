/*
 *  TextLine.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TEXT_LINE_H_
#define TEXT_LINE_H_

#include "Drawable.h"

#include "StringIcon.h"


class TextLine : public Drawable{
public:
	//--- GENERAL ---//
	void addString(const string&, const Coord2d<double>&, GLshort);
	void setString(const string&, GLshort = 0);
	
	//---- DRAW ----//
	void draw(bool);	
	
protected:
	vector<StringIcon> _str;
};

#endif