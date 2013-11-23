/*
 *  ItemDisplayIS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ITEM_DISPLAY_I_S_H_
#define ITEM_DISPLAY_I_S_H_

#include "StatDisplay.h"

class Item;


class ItemDisplayIS : public StatDisplay<Item>{
public:	
	ItemDisplayIS(GLshort, GLshort, GLshort);
	
	//--- GENERAL ---//	
	void update(Item*);
};

#endif