/*
 *  Inventory.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Inventory.h"

#include "GridBlock.h"
#include "Gun.h"
#include "GridItemContainer.h"
#include "LimitedItemSlot.h"


Inventory::Inventory()
{
	// Weapon slot
	_container.push_back(new LimitedItemSlot(ANY_ITEM));			
	
	// todo: TEMPORARY FIX for armor slots
	_container.push_back(new LimitedItemSlot(ARMOR));				
	
	// Left holster
	GridItemContainer* igc = new GridItemContainer(2, 2);	
	igc->enable(false, 1, 0);
	_container.push_back(igc);								
	
	// Left pocket
	_container.push_back(new GridItemContainer(2, 2));		
	
	// Right holster
	igc = new GridItemContainer(2, 2);						
	igc->enable(false, 0, 0);
	_container.push_back(igc);	
	
	// Right pocket
	_container.push_back(new GridItemContainer(2, 2));		
	
	// Backpack
	_container.push_back(new GridItemContainer(3, 4));		
		
	_ammo = NULL;
}

Inventory::~Inventory()
{
	for(GLshort i = 0; i < _container.size(); ++i)
		delete _container[i];
}


InventoryContainerType* Inventory::getContainer(GLshort i)
{
	return _container[i];
}

Item* Inventory::getEquippedItem()
{
	return _container[0]->getItem(0);
}

void Inventory::dropAll(GridBlock* gb)
{
	ItemMap itemMap;
	for(GLshort i = 0; i < _container.size(); ++i)
		_container[i]->getAllItems(itemMap, true);
	
	ItemContainerType* groundCont = gb->getContainer();
	for(ItemMap::iterator iter = itemMap.begin(); iter != itemMap.end(); ++iter)
		groundCont->setItem(iter->first);
}


//--- COMBAT ---//
void Inventory::takeShot()
{
	Gun* gun = (Gun*)getEquippedItem();
	gun->setAmmo(gun->getAmmo() - 1);
}

void Inventory::reload()
{
	if(getEquippedItem()->combine(_ammo)){
		delete _ammo;
		_ammo = NULL;
		_container[_ammoCont]->setItem(NULL, _ammoCoord[X], _ammoCoord[Y]);	
	}
}

bool Inventory::canReload()
{
	Gun* gun = (Gun*)getEquippedItem();
	if(gun->getAmmo() == gun->getMaxAmmo())
		return false;
	
	// Search for ammo
	if(_ammo == NULL || !gun->canCombine(_ammo)){	
		for(GLshort i = 0; i < _container.size(); ++i){
			Item* tempAmmo = _container[i]->findCombine(gun, _ammoCoord);
			if(tempAmmo != NULL){
				_ammoCont = i;
				_ammo = tempAmmo;
				return true;
			}
		}
		return false;
	}
	return true;
}

bool Inventory::mustReload()
{
	Gun* gun = (Gun*)getEquippedItem();
	return gun->getAmmo() == 0;
}


//---- DRAW ----//	
void Inventory::draw(bool step)
{
	for(GLshort i = 0; i < _container.size(); ++i)
		_container[i]->draw(step);
}


//---- IO ----//	
void Inventory::saveData(ofstream& file)
{
	for(GLshort i = 0; i < _container.size(); ++i)
		_container[i]->saveData(file, i);
}