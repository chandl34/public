/*
 *  GrenadeData.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GRENADE_DATA_H_
#define GRENADE_DATA_H_

#include "ItemData.h"


class GrenadeData : public ItemData{
public:
	GrenadeData(const ItemType&, GLshort, 
					Image*, const string&);
};

#endif
