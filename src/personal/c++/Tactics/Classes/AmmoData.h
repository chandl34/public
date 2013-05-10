/*
 *  AmmoData.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AMMO_DATA_H_
#define AMMO_DATA_H_

#include "ItemData.h"


class AmmoData : public ItemData{
public:
	AmmoData(const ItemType&, GLshort, 
				Image*, const string&, 
				AmmoType, AmmoCount);
	
	//--- GENERAL ---//
	GLshort getAmmoType() const;
	GLshort getMaxAmmo() const;
	
private:
	//--- GENERAL ---//
	AmmoType _ammoType;
	AmmoCount _maxAmmo;
	
	
	// damage type
	// hp?
	// range?
	// 
};

#endif

