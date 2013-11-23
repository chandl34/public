/*
 *  Item.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ITEM_H_
#define ITEM_H_

#include "Icon.h"

class Item;
class ItemData;


//typedef set<Item*> ItemSet;
typedef map<Item*, Coord2d<GLshort> > ItemMap;


class Item : public Icon{
protected:
	Item(ItemData*);
	
public:
	static Item* create(const ItemType&, GLshort);
	
	//--- GENERAL ---//	
	GLshort getType() const;
	GLshort getIndex() const;
	const string& getName() const;
	
	virtual bool canCombine(Item*);
	virtual bool combine(Item*);
	
	//---- IO ----//	
	virtual void saveData(ofstream&);
	
protected:
	//--- GENERAL ---//
	ItemData* _data;
};


// Non-member functions
struct ItemPtr{	
	ItemPtr(Item*);
	
	Item* _item;
};

bool operator<(const ItemPtr&, const ItemPtr&);

#endif