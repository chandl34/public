/*
 *  EnemyTeam.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ENEMY_TEAM_H_
#define ENEMY_TEAM_H_

#include "Team.h"

#include "Memory.h";


class EnemyTeam : public Team{
protected:	
	EnemyTeam(Faction*, Level*);
	friend class Team;
	
public:	
	//--- GAMEPLAY ---//
	GLshort update(Team&, UnitList&);	
	bool plan();
	void removeDead(Unit*);
	void newTurnLevel(Team&);	
	
	//---- IO ----//	
	void saveMemoryData(ofstream&);
	
private:
	//---- AI ----//	
	UnitSet _known;
	MemoryMap _memory;
};

#endif