/*
 *  UnitCombat.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"
#include "LevelMap.h"


void Unit::shoot(){	
	LevelMap::addProjectile(goalBlock->getGround(), this);
}
