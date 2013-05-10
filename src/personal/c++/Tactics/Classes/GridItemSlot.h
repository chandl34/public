/*
 *  GridItemSlot.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GRID_ITEM_SLOT_H_
#define GRID_ITEM_SLOT_H_

#include "Drawable.h"

#include "Item.h"


class GridItemSlot : public Drawable{
public:
	GridItemSlot(GLshort, GLshort);
	~GridItemSlot();
	
	//--- GENERAL ---//
	void setItem(Item*, const Coord2d<GLshort>&);
	Item* getItem();
	
	bool isBase() const;
	GLshort getBase(GLshort) const;
	
	void enable(bool);
	bool isEnabled();
	
	//---- DRAW ----//	
	void draw(bool);
	
private:
	//--- GENERAL ---//
	Item* _item;
	Coord2d<GLshort> _loc;
	Coord2d<GLshort> _base;
	bool _enabled;
	
	void setItem(Item*);
};

#endif