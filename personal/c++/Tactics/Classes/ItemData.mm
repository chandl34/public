/*
 *  ItemData.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ItemData.h"
#include "Image.h"


ItemData::ItemData(const ItemType& type, GLshort index, 
						 Image* img, const string& n) 
: _itemType(type)
, _name(n)
{
	_index = index;
	_image = img;
}


//--- GENERAL ---//
GLshort ItemData::getType() const
{
	return _itemType;
}

GLshort ItemData::getIndex() const
{
	return _index;
}

Image* ItemData::getImage()
{
	return _image;
}

const string& ItemData::getName() const
{
	return _name;
}