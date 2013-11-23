/*
 *  InfiniteItemContainer.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INFINITE_ITEM_CONTAINER
#define INFINITE_ITEM_CONTAINER

#include "ItemContainerType.h"

#include "Item.h"


class InfiniteItemContainer : public ItemContainerType{
public:
	~InfiniteItemContainer();
	
	//--- GENERAL ---//
	bool setItem(Item*, GLshort, GLshort);
	Item* getItem(GLshort, GLshort);	
	void getAllItems(ItemMap&, bool);
	
	void resetOffsets(double, double);
	
	Item* findCombine(Item*, Coord2d<GLshort>&);
	
	bool isEmpty() const;
	
	//---- DRAW ----//	
	void draw(bool);
	
	//---- IO ----//	
	void saveData(ofstream&, const Coord2d<GLshort>*);
///	void saveData(ofstream&, GLshort = 0);
	
public:
	set<ItemPtr> _item;
};

#endif