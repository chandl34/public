/*
 *  LimitedItemSlot.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "LimitedItemSlot.h"

#include "Item.h"


LimitedItemSlot::LimitedItemSlot(GLshort at)
{
	_item = NULL;
	_allowedType = at;
}

LimitedItemSlot::~LimitedItemSlot()
{
	delete _item;
}


//--- GENERAL ---//
bool LimitedItemSlot::setItem(Item* it, GLshort x, GLshort y)
{
	if(_item != NULL && it != NULL)
		return false;
	
	if(_allowedType != ANY_ITEM && _allowedType != it->getType())
		return false;
	
	_item = it;
	return true;
}

Item* LimitedItemSlot::getItem(GLshort x, GLshort y)
{
	return _item;
}

void LimitedItemSlot::getAllItems(ItemMap& is, bool null)
{
	if(_item != NULL){
		is[_item] = Coord2d<GLshort>(_loc[X], _loc[Y]);
		if(null)
			_item = NULL;
	}
}

Item* LimitedItemSlot::findCombine(Item* it, Coord2d<GLshort>& loc)
{
	if(it->canCombine(it))
		return it;
	return NULL;
}


//---- DRAW ----//	
void LimitedItemSlot::draw(bool step)
{
	if(_item != NULL)
		_item->draw(step);
}


//---- IO ----//	
void LimitedItemSlot::saveData(ofstream& file, GLshort cont)
{
	if(_item != NULL){
		file << "i " << cont << " ";
		file << _loc[X] << " " << _loc[Y] << " ";
		_item->saveData(file);
		file << "\n";
	}
}
