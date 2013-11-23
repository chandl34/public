/*
 *  Inventory.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Drawable.h"

class GridBlock;
class Item;
class InventoryContainerType;


const GLshort INVENTORY_CONTAINERS = 7;


class Inventory : public Drawable{
public:
	Inventory();
	~Inventory();
	
	//--- GENERAL ---//
	InventoryContainerType* getContainer(GLshort);	
	Item* getEquippedItem();
	
	void dropAll(GridBlock*);
	
	//--- COMBAT ---//
	void takeShot();			
	void reload();
	bool canReload();				// Searches for ammo
	bool mustReload();
	
	//---- DRAW ----//	
	void draw(bool);
	
	//---- IO ----//	
	void saveData(ofstream&);
	
private:
	//--- GENERAL ---//
	vector<InventoryContainerType*> _container;
	
	Item* _ammo;
	GLshort _ammoCont;
	Coord2d<GLshort> _ammoCoord;
};

#endif
