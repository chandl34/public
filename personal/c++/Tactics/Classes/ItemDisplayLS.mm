/*
 *  ItemDisplayLS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ItemDisplayLS.h"

#include "Gun.h"
#include "Item.h"

#include "String.h"


ItemDisplayLS::ItemDisplayLS(GLshort lx, GLshort rx, GLshort ty) 
: StatDisplay<Item>(lx, rx, ty){
	_prevItem = NULL;
	
	GLshort y = _topY;
	
	_text.push_back(TextLine());
	_text[NAME_STR].addString(" ", Coord2d<double>(_centerX, y), CENTERED);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[AMMO_STR].addString(" ", Coord2d<double>(_centerX, y), CENTERED);
}


void ItemDisplayLS::update(Item* sItem){
	if(sItem != _prevItem)
		_text[NAME_STR].setString(sItem->getName());
	
	if(sItem->getType() == GUN){
		Gun* gun = (Gun*)sItem;
		
		if(sItem != _prevItem || _prevAmmo != gun->getAmmo()){
			_prevAmmo = gun->getAmmo();
			string temp(numToString(_prevAmmo, 2) + " / " + numToString(gun->getMaxAmmo(), 2));
			_text[AMMO_STR].setString(temp);
		}
	}
	else
		_text[AMMO_STR].setString(" ");
	
	_prevItem = sItem;
}
