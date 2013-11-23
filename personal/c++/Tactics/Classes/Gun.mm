/*
 *  Gun.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Gun.h"

#include "GunData.h"

#include "ItemDataStorage.h"


Gun::Gun(ItemData* data)
: Ammo(data)
{
	
}


//--- GENERAL ---//
GLshort Gun::getSpeed() const
{
	return ((GunData*)_data)->getSpeed();
}

GLshort Gun::getAccuracy() const
{
	return ((GunData*)_data)->getAccuracy();
}

GLshort Gun::getAmmoType() const
{
	return ((GunData*)_data)->getAmmoType();
}

GLshort Gun::getMaxAmmo() const
{
	return ((GunData*)_data)->getMaxAmmo();
}
