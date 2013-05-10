/*
 *  Item.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Item.h"

#include "Ammo.h"
#include "Grenade.h"
#include "Gun.h"
#include "ItemData.h"

#include "ItemDataStorage.h"


Item::Item(ItemData* data) 
: Icon(data->getImage())
{
	_data = data;
}

Item* Item::create(const ItemType& type, GLshort index)
{
	ItemData* data = ItemDataStorage::getItemData(type, index);
	
	Item* it;	
	if(type == ITEM)
		it = new Item(data);
	else if(type == AMMO){
		it = new Ammo(data);	
		Ammo* ammo = (Ammo*)it;
		ammo->setAmmo(ammo->getMaxAmmo());
	}
	else if(type == GRENADE)
		it = new Grenade(data);
	else if(type == GUN)
		it = new Gun(data);
	
	return it;
}


//--- GENERAL ---//
GLshort Item::getType() const
{
	return _data->getType();
}

GLshort Item::getIndex() const
{
	return _data->getIndex();
}

const string& Item::getName() const{
	
	return _data->getName();
}

bool Item::canCombine(Item* item)
{
	return false;
}

bool Item::combine(Item* item)
{
	return false;
}


//---- IO ----//	
void Item::saveData(ofstream& file)
{
	file << getType() << " " << getIndex() << " ";
}




// Non-member functions
ItemPtr::ItemPtr(Item* item)
{
	_item = item;
}

bool operator<(const ItemPtr& lhs, const ItemPtr& rhs){
	GLshort l = lhs._item->getSize(X) * lhs._item->getSize(Y);
	GLshort r = rhs._item->getSize(X) * rhs._item->getSize(Y);
	
	if(l == r)
		return lhs._item < rhs._item;	
	
	return l < r;
}
