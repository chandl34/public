/*
 *  ItemStorage.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ITEM_DATA_STORAGE_H_
#define ITEMITEM_DATA_STORAGE_H__STORAGE_H_

#include "Include.h"

class ItemData;


class ItemDataStorage{
public:
	~ItemDataStorage();
	
	static ItemData* getItemData(const ItemType&, GLshort);
	static void addItemData(ItemData*);
	
private:
	static vector<ItemData*> itemData[ITEM_TYPES];
};

#endif