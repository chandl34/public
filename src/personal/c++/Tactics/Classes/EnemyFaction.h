/*
 *  EnemyFaction.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 1/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ENEMY_FACTION_H_
#define ENEMY_FACTION_H_

#include "Faction.h"


class EnemyFaction : public Faction{
protected:
	EnemyFaction(GLshort, const string&, const Color&);
	friend class Faction;
	
public:
	//--- GAMEPLAY ---//	
	bool plan();	
	
};

#endif