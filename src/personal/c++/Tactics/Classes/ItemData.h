/*
 *  ItemData.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ITEM_DATA_H_
#define ITEM_DATA_H_

#include "Include.h"

class Image;


class ItemData{
public:
	ItemData(const ItemType&, GLshort, 
				Image*, const string&);
	
	//--- GENERAL ---//
	GLshort getType() const;
	GLshort getIndex() const;
	Image* getImage();
	const string& getName() const;
	
private:
	//--- GENERAL ---//
	ItemType _itemType;
	GLshort _index;

	Image* _image;
	string _name;
	//GLshort size;
};

#endif