/*
 *  TextLine.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextLine.h"


//--- GENERAL ---//
void TextLine::addString(const string& s, const Coord2d<double>& os, GLshort a)
{
	_str.push_back(StringIcon(s, os, a));
}

void TextLine::setString(const string& s, GLshort i)
{
	_str[i].setString(s);
}
											

//---- DRAW ----//
void TextLine::draw(bool step)
{
	for(GLshort i = 0; i < _str.size(); ++i)
		_str[i].draw(step);
}
