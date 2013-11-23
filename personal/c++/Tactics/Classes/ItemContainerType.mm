/*
 *  ItemContainerType.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ItemContainerType.h"

#include "Item.h"


ItemContainerType::~ItemContainerType()
{
	
}


//--- GENERAL ---//
void ItemContainerType::getBase(GLshort&, GLshort&)
{
	// do nothing
}

GLshort ItemContainerType::getSize(GLshort)
{
	return 1;
}

void ItemContainerType::resetOffsets(double, double)
{
	// do nothing
}


InventoryContainerType::~InventoryContainerType()
{
	
}