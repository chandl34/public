/*
 *  FactionIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Faction.h"


//---- IO ----//	
void Faction::saveData(ofstream& file)
{
	file << "f " << _factionID << " " << _name;
	for(GLshort i = 0; i < COLORS; ++i)
		file << " " << _color[i];
	file << "\n";
	
	for(TeamList::iterator iter = _team.begin(); iter != _team.end(); ++iter)
		(*iter)->saveData(file);
}
