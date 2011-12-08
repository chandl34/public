/*
 *  UnitDraw.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"


void Unit::draw(bool step){
	if(team == GOOD || beenSeen){
		if(team != GOOD && seenBy.empty())
			glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
		RotateObject::draw(step);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

