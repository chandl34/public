/*
 *  Ammo.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ammo.h"

#include "AmmoData.h"

#include "ItemDataStorage.h"


Ammo::Ammo(ItemData* data) 
: Item(data)
{
	
}


//--- GENERAL ---//
GLshort Ammo::getAmmoType() const
{
	return ((AmmoData*)_data)->getAmmoType();
}

GLshort Ammo::getMaxAmmo() const
{
	return ((AmmoData*)_data)->getMaxAmmo();
}


void Ammo::setAmmo(GLshort a)
{
	_ammo = a;
}

GLshort Ammo::getAmmo() const
{
	return _ammo;
}

bool Ammo::canCombine(Item* it)
{
	if(it == NULL)
		return false;
	
	if(_ammo == getMaxAmmo() || it->getType() != AMMO)
		return false;
	
	Ammo* am = (Ammo*)it;
	return am->getAmmoType() == getAmmoType();
}

bool Ammo::combine(Item* it)
{
	Ammo* am = (Ammo*)it;
	GLshort need = min((int)am->getAmmo(), getMaxAmmo() - _ammo);
	_ammo += need;
	am->setAmmo(am->getAmmo() - need);
	return am->getAmmo() == 0;
}


//---- IO ----//	
void Ammo::saveData(ofstream& file)
{
	Item::saveData(file);
	file << getAmmo() << " ";
}
