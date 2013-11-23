/*
 *  EnemyFaction.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 1/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "EnemyFaction.h"


EnemyFaction::EnemyFaction(GLshort factionID, const string& name, const Color& color)
: Faction(factionID, name, color)
{

}


//--- GAMEPLAY ---//	
bool EnemyFaction::plan()
{
	return false;
}
