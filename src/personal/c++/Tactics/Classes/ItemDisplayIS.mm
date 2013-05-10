/*
 *  ItemDisplayIS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ItemDisplayIS.h"

#include "Ammo.h"
#include "Item.h"
#include "Gun.h"

#include "String.h"

#include "Image.h"
#include "ImageStorage.h"

ItemDisplayIS::ItemDisplayIS(GLshort lx, GLshort rx, GLshort ty) 
: StatDisplay<Item>(lx, rx, ty){
	
}


//--- GENERAL ---//	
void ItemDisplayIS::update(Item* it){
	clear();
	GLshort y = _topY;
	
	_text.push_back(TextLine());
	_text[0].addString(it->getName(), Coord2d<double>(_centerX, y), CENTERED);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[1].addString("Weight", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[1].addString("4", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	Ammo* ammo;
	Gun* gun;
	switch(it->getType()){
		case AMMO:
			ammo = (Ammo*)it;
			
			_text.push_back(TextLine());
			_text[2].addString("Rounds", Coord2d<double>(_leftX, y), ALIGN_LEFT);
			_text[2].addString(numToString(ammo->getAmmo(), 3), Coord2d<double>(_rightX, y), ALIGN_RIGHT);
			y -= 10;
			
			break;
			
		case GUN:
			gun = (Gun*)it;
			
			_text.push_back(TextLine());
			_text[2].addString("Accuracy", Coord2d<double>(_leftX, y), ALIGN_LEFT);
			_text[2].addString(numToString(gun->getAccuracy(), 3), Coord2d<double>(_rightX, y), ALIGN_RIGHT);
			y -= 10;
			
			_text.push_back(TextLine());
			_text[3].addString("Damage", Coord2d<double>(_leftX, y), ALIGN_LEFT);
			_text[3].addString("69", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
			y -= 10;
			
			_text.push_back(TextLine());
			_text[3].addString("Rounds", Coord2d<double>(_leftX, y), ALIGN_LEFT);
			_text[3].addString(numToString(gun->getAmmo(), 3), Coord2d<double>(_rightX, y), ALIGN_RIGHT);
			y -= 10;
			
			_text.push_back(TextLine());
			_text[3].addString("TU to Fire", Coord2d<double>(_leftX, y), ALIGN_LEFT);
			_text[3].addString("8", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
			y -= 10;
			
			break;			
	};
}
