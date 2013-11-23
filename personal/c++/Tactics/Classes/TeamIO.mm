/*
 *  TeamIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Team.h"

#include "Level.h"


//---- IO ----//	
void Team::saveData(ofstream& file)
{
	file << "t " << _level->getID() << " " << (_level->getTeam(INTRUDER) == this) << "\n";
	
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter)
		(*iter)->saveData(file);
}
