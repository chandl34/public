/*
 *  GunData.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GUN_DATA_H_
#define GUN_DATA_H_

#include "ItemData.h"


class GunData : public ItemData{
public:
	GunData(const ItemType&, GLshort, 
			  Image*, const string&, 
			  Speed, Accuracy, AmmoType, AmmoCount);
	
	//--- GENERAL ---//
	GLshort getSpeed() const;	
	GLshort getAccuracy() const;
	GLshort getAmmoType() const;
	GLshort getMaxAmmo() const;
	
private:
	//--- GENERAL ---//
	Speed _speed;
	Accuracy _acc;
	AmmoCount _maxAmmo;
	AmmoType _ammoType;
	
	
	// damage type
	// hp?
	// range?
	// 
};

#endif
