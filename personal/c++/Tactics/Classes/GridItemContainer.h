/*
 *  GridItemContainer.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GRID_ITEM_CONTAINER_H_
#define GRID_ITEM_CONTAINER_H_

#include "ItemContainerType.h"

#include "GridItemSlot.h"

class Item;


class GridItemContainer : public InventoryContainerType{
public:
	GridItemContainer(GLshort, GLshort);
	
	//--- GENERAL ---//
	bool setItem(Item*, GLshort, GLshort);	
	Item* getItem(GLshort, GLshort);
	void getAllItems(ItemMap&, bool);
	
	void getBase(GLshort&, GLshort&);	
	GLshort getSize(GLshort);
	
	void enable(bool, GLshort, GLshort);
	
	Item* findCombine(Item*, Coord2d<GLshort>&);
	
	//---- DRAW ----//	
	void draw(bool);
	
	//---- IO ----//	
	void saveData(ofstream&, GLshort);
	
protected:
	//--- GENERAL ---//
	vector<vector<GridItemSlot> > _itemSlot;
	Size2d<GLshort> _size;
	
	bool canFit(Item*, GLshort, GLshort, const Size2d<GLshort>&);
	void setItemSub(Item*, GLshort, GLshort, const Size2d<GLshort>&);
};

#endif
