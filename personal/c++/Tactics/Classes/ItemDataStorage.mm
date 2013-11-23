/*
 *  ItemDataStorage.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ItemDataStorage.h"

#include "ItemData.h"

#include "ImageStorage.h"


vector<ItemData*> ItemDataStorage::itemData[ITEM_TYPES];


ItemDataStorage::~ItemDataStorage(){
	for(GLshort i = 0; i < ITEM_TYPES; ++i){
		for(GLshort j = 0; j < itemData[i].size(); ++j)
			delete itemData[i][j];
	}
}

ItemData* ItemDataStorage::getItemData(const ItemType& t, GLshort is){
	return itemData[t][is];	
}

void ItemDataStorage::addItemData(ItemData* it){
	ImageStorage::addImage(it->getImage());
	itemData[it->getType()].push_back(it);
};
