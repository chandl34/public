/*
 *  ComplexIcon.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ComplexIcon.h"


ComplexIcon::ComplexIcon(Image* img, const Coord2d<double>& os) 
: Icon(img, os)
{

}

ComplexIcon::~ComplexIcon(){
	clear();
}

void ComplexIcon::clear()
{
	_overlay.clear();
}


//--- GENERAL ---//

void ComplexIcon::setOffset(double x, double y)
{
	GLshort dx = x - getOffset(X);
	GLshort dy = y - getOffset(Y);	
	
	for(GLshort i = 0; i < _overlay.size(); ++i)
		_overlay[i].setOffset(_overlay[i].getOffset(X) + dx, 
									 _overlay[i].getOffset(Y) + dy);
		
	Icon::setOffset(x, y);
}

void ComplexIcon::addIcon(Image* img, const Coord2d<double>& os)
{	
	_overlay.push_back(Icon(img, Coord2d<double>(os[X] + getOffset(X), 
																os[Y] + getOffset(Y))));
}


//---- DRAW ----//
void ComplexIcon::draw(bool step)
{
	Icon::draw(step);
	
	for(GLshort i = 0; i < _overlay.size(); ++i)
		_overlay[i].draw(step);
}
