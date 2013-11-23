/*
 *  Gun.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GUN_H_
#define GUN_H_

#include "Ammo.h"


class Gun : public Ammo{
protected:
	Gun(ItemData*);
	friend class Item;
	
public:
	//--- GENERAL ---//
	GLshort getSpeed() const;	
	GLshort getAccuracy() const;
	GLshort getAmmoType() const;
	GLshort getMaxAmmo() const;
};

#endif
