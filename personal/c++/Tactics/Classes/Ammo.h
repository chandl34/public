/*
 *  Ammo.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef AMMO_H_
#define AMMO_H_

#include "Item.h"


class Ammo : public Item{
protected:
	Ammo(ItemData*);
	friend class Item;
	
public:
	//--- GENERAL ---//
	virtual GLshort getMaxAmmo() const;
	virtual GLshort getAmmoType() const;
	
	void setAmmo(GLshort);
	GLshort getAmmo() const;
	
	bool canCombine(Item*);
	bool combine(Item*);
	
	//---- IO ----//	
	void saveData(ofstream&);
	
private:
	AmmoCount _ammo;
};

#endif
