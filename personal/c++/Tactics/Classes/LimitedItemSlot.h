/*
 *  LimitedItemSlot.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LIMITED_ITEM_SLOT_H_
#define LIMITED_ITEM_SLOT_H_

#include "ItemContainerType.h"


class LimitedItemSlot : public InventoryContainerType{
public:
	LimitedItemSlot(GLshort);
	~LimitedItemSlot();
	
	//--- GENERAL ---//
	bool setItem(Item*, GLshort = 0, GLshort = 0);
	Item* getItem(GLshort = 0, GLshort = 0);	
	void getAllItems(ItemMap&, bool);
	
	Item* findCombine(Item*, Coord2d<GLshort>&);
	
	//---- DRAW ----//	
	void draw(bool);
	
	//---- IO ----//	
	void saveData(ofstream&, GLshort);
	
private:
	//--- GENERAL ---//
	Item* _item;
	Coord2d<GLshort> _loc;
	GLshort _allowedType;
	
	// todo: add sizes later
};

#endif

