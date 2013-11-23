/*
 *  ItemContainerType.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ITEM_CONTAINER_TYPE_H_
#define ITEM_CONTAINER_TYPE_H_

#include "Drawable.h"

#include "Item.h"


class ItemContainerType : public Drawable{
public:
	virtual ~ItemContainerType();
	
	//--- GENERAL ---//
	virtual bool setItem(Item*, GLshort = 0, GLshort = 0) = 0;
	virtual Item* getItem(GLshort = 0, GLshort = 0) = 0;	
	virtual void getAllItems(ItemMap&, bool) = 0;	// Collects all items in the set and removes them from the source
	
	virtual void getBase(GLshort&, GLshort&); 
	virtual GLshort getSize(GLshort);	
	virtual void resetOffsets(double, double);
	
	virtual Item* findCombine(Item*, Coord2d<GLshort>&) = 0;
};


class InventoryContainerType : public ItemContainerType{
public:
	virtual ~InventoryContainerType();
	
	//---- IO ----//	
	virtual void saveData(ofstream&, GLshort) = 0;
};

#endif
