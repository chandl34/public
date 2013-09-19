/*
 *  UnitInventory.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "Options.h"


//--- INVENTORY ---//
bool Unit::moveItem(ItemContainerType* oCont, Coord2d<GLshort>& o,
						  ItemContainerType* tCont, Coord2d<GLshort>& t)
{
	// Charge pickup cost if item going from ground to _inventory or vice versa
	bool pickUp	= oCont == _currBlock->getContainer() || tCont == _currBlock->getContainer();
	pickUp = pickUp && oCont != tCont;
	
	if(pickUp && getEffectiveTU() < PICK_UP_COST)
		return false;	
	
	oCont->getBase(o[X], o[Y]);
	
	// First make sure slot is empty
	if(tCont->getItem(t[X], t[Y]) == NULL){
		Item* item = oCont->getItem(o[X], o[Y]);
		oCont->setItem(NULL, o[X], o[Y]);
		if(!tCont->setItem(item, t[X], t[Y]))
			oCont->setItem(item, o[X], o[Y]);	// Failed to place, reset
		else{
			if(pickUp){
				if(!UNLIMITED_TU)
					_currTU -= PICK_UP_COST;
				cout << "Picked up or dropped item" << endl;
			}
			return true;
		}
	}	
	return false;
}

// NOTE: this doesn't have to apply to the primary gun and ammo.  RELOAD_COST is a catch-all for combining items
bool Unit::combine(Item* it1, Item* it2, bool pickUp)
{		
	if(it1->canCombine(it2)){
		GLshort cost = RELOAD_COST;
		if(pickUp)
			cost += PICK_UP_COST;
		
		if(getEffectiveTU() >= cost){
			if(!UNLIMITED_TU)
				_currTU -= cost;
			
			if(pickUp)
				cout << "Picked up or dropped item before combining" << endl;
			
			return it1->combine(it2);
		}
	}
	return false;
}

bool Unit::mustReload()
{
	Item* item = _inventory.getEquippedItem();
	if(item != NULL){
		if(item->getType() == GUN)
			return _inventory.mustReload();
	}	
	
	return false;
}

void Unit::reload()
{
	if(getEffectiveTU() >= RELOAD_COST){
		if(!UNLIMITED_TU)
			_currTU -= RELOAD_COST;
		printf("Reloaded\n");
		_inventory.reload();
	}
}

