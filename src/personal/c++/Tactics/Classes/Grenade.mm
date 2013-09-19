/*
 *  Grenade.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Grenade.h"

#include "GridBlock.h"
#include "Unit.h"

#include "ItemDataStorage.h"


Grenade::Grenade(ItemData* data)
: Item(data)
{
	_primed = false;
}


//--- GENERAL ---//
void Grenade::prime()
{
	_primed = true;
}

bool Grenade::isPrimed()
{
	return _primed;
}

void Grenade::explode(GridBlock* gb)
{
	cout << "KA-BOOOOOOOOOM!!!" << endl;
	BlockSet bs;
	find360Scope(bs, gb, 2); // 2 is explosion radius here... todo: make that a item stat
	Unit* u;
	for(BlockSet::iterator iter = bs.begin(); iter != bs.end(); ++iter){
		u = (*iter)->getUnit();
		if(u != NULL)
			u->takeDamage(TORSO, 10);
	}		
}

