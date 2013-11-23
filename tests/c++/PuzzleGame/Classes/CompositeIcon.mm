/*
 *  CompositeIcon.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CompositeIcon.h"


CompositeIcon::CompositeIcon(const Coord2d<double>& os)
: BaseIcon(os)
{

}

CompositeIcon::~CompositeIcon()
{
	clear();
}

void CompositeIcon::clear()
{
	overlay.clear();
}


//--- GENERAL ---//

void CompositeIcon::setOffset(double x, double y)
{
	double dx = x - getOffset(X);
	double dy = y - getOffset(Y);	
	
	for(GLshort i = 0; i < overlay.size(); ++i)
		overlay[i].setOffset(overlay[i].getOffset(X) + dx, 
									overlay[i].getOffset(Y) + dy);
		
	BaseIcon::setOffset(x, y);
}

void CompositeIcon::addIcon(Image* img, const Coord2d<double>& os)
{	
	overlay.push_back(Icon(img, Coord2d<double>(os[X] + getOffset(X), 
															  os[Y] + getOffset(Y))));
}


//---- DRAW ----//
void CompositeIcon::draw(bool step)
{
	for(GLshort i = 0; i < overlay.size(); ++i)
		overlay[i].draw(step);
}


//--- TOUCH ---//
bool CompositeIcon::isTouching(const Coord2d<GLshort>& p)
{
	for(GLshort i = 0; i < overlay.size(); ++i){
		if(overlay[i].isTouching(p))
			return true;
	}
	return false;
}

void CompositeIcon::push(GLshort, const Coord2d<GLshort>&){}
void CompositeIcon::move(GLshort, const Coord2d<GLshort>&){}
bool CompositeIcon::release(GLshort, const Coord2d<GLshort>&){return false;}


// Non-member Functions
void addIcon(CompositeIcon* icon, void* arg)
{
	icon->addIcon((Image*)arg);
}


