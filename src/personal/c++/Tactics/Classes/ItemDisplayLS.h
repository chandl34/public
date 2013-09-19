/*
 *  ItemDisplayLS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ITEM_DISPLAY_T_S_H_
#define ITEM_DISPLAY_T_S_H_

#include "StatDisplay.h"

class Item;


class ItemDisplayLS : public StatDisplay<Item>{
public:
	ItemDisplayLS(GLshort, GLshort, GLshort);
	
	//--- GENERAL ---//	
	void update(Item*);
	
private:
	//--- GENERAL ---//
	Item* _prevItem;
	GLshort _prevAmmo;
	
	enum{NAME_STR, AMMO_STR};
};

#endif