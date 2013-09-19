/*
 *  Grenade.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GRENADE_H_
#define GRENADE_H_

#include "Item.h"

class GridBlock;


class Grenade : public Item{
protected:
	Grenade(ItemData*);
	friend class Item;
	
public:
	//--- GENERAL ---//
	void prime();
	bool isPrimed();
	void explode(GridBlock*);
	
private:
	bool _primed;
};

#endif
