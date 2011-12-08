/*
 *  UnitTurn.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Unit.h"

void Unit::newTurn(){
	if(seenBy.empty())
		beenSeen = false;
	currTU = maxTU;
}