/*
 *  AmmoData.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "AmmoData.h"


AmmoData::AmmoData(const ItemType& it, GLshort index,
						 Image* img, const string& n,
						 AmmoType at, AmmoCount ma) 
: ItemData(it, index, img, n)
{
	_ammoType = at;
	_maxAmmo = ma;
}


//--- GENERAL ---//
GLshort AmmoData::getAmmoType() const
{
	return _ammoType;
}

GLshort AmmoData::getMaxAmmo() const
{
	return _maxAmmo;
}
