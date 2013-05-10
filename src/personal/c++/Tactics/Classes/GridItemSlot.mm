/*
 *  GridItemSlot.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridItemSlot.h"

#include "Item.h"


GridItemSlot::GridItemSlot(GLshort x, GLshort y) 
: _loc(x, y)
{
	_item = NULL;
	_enabled = true;
}

GridItemSlot::~GridItemSlot()
{
	if(isBase())
		delete _item;  
}


void GridItemSlot::setItem(Item* it, const Coord2d<GLshort>& loc)
{
	_item = it;
	_base = loc;
}

Item* GridItemSlot::getItem(){
	return _item;
}

void GridItemSlot::enable(bool e)
{
	_enabled = e;
}

bool GridItemSlot::isEnabled()
{
	return _enabled;
}

bool GridItemSlot::isBase() const
{
	return _loc[X] == _base[X] && _loc[Y] == _base[Y];
}

GLshort GridItemSlot::getBase(GLshort c) const
{
	return _base[c];
}


//---- DRAW ----//	
void GridItemSlot::draw(bool step)
{
	if(_item != NULL && isBase())
		_item->draw(step);
}