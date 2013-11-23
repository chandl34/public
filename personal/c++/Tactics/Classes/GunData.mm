/*
 *  GunData.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GunData.h"


GunData::GunData(const ItemType& it, GLshort index,
					  Image* img, const string& n,
					  Speed sp, Accuracy ac, AmmoType at, AmmoCount ma)
: ItemData(it, index, img, n){
	_speed = sp;
	_acc = ac;
	_maxAmmo = ma;
	_ammoType = at;
}


//--- GENERAL ---//
GLshort GunData::getSpeed() const{
	return _speed;
}

GLshort GunData::getAccuracy() const{
	return _acc;
}	

GLshort GunData::getMaxAmmo() const{
	return _maxAmmo;
}

GLshort GunData::getAmmoType() const{
	return _ammoType;
}