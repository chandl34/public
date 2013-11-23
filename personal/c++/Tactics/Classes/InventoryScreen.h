/*
 *  InventoryScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/3/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INVENTORY_SCREEN_H_
#define INVENTORY_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"
#include "Icon.h"
#include "ItemDisplayIS.h"
#include "UnitDisplayIS.h"

class GridBlock;
class Item;
class ItemContainerType;
class Unit;


class InventoryScreen : public SubScreen{
public:
	InventoryScreen();
	
	//-- GENERAL --//
	void open();
	void close();
	
	//---- DRAW ----//
	void draw(bool);
	
	//---- TOUCH ----//
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);
	
private:
	//---- GENERAL ----//
	Icon _statsBackground;
	Icon _unitBackground;
	
	//---- DISPLAYS ----//
	ItemDisplayIS _itemInfo;
	UnitDisplayIS _unitInfo;	
	
	//---- ITEMS ----//
	ComplexMenu _itemSlot;	
	ItemContainerType* _sContainer;
	Coord2d<GLshort> _sLoc;
	Item* _sItem;
};

#endif



