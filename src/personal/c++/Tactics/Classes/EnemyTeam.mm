/*
 *  EnemyTeam.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "EnemyTeam.h"

#include "EnemyUnit.h"


EnemyTeam::EnemyTeam(Faction* faction, Level* level)
: Team(faction, level)
{
	
}


//-- GENERAL --//
bool EnemyTeam::plan()
{
	if(_unit.empty()){
		printf("All enemies dead.  Mission complete\n");
		return false;
	}
	
	EnemyUnit* bu = (EnemyUnit*)_sUnit;	
	if(bu->isIdle()){		
		if(!bu->isFinished()){
			bu->findPlan(_known, _memory);
			bu->workPlan();
		}
		else{
			printf("\nEnemy unit finished his turn\n\n\n");
			selectNextUnit();
			
			// All units are done, end enemy turn
			if(_sUnit == *_unit.begin())
				return false;
		}
	}
	
	return true;
}

// NOTE:: moving findNewData() method to here will cause incorrect danger levels during PLAYER turn.
// ------ as long as I don't move a unit during that turn, the data will be correct
//--- UPDATES ---//
GLshort EnemyTeam::update(Team& ot, UnitList& dead)
{	
	GLshort ret = Team::update(ot, dead);
	EnemyUnit::findNewData(_known, _memory);
	return ret;
}

void EnemyTeam::newTurnLevel(Team& ot)
{
	Team::newTurnLevel(ot);	
	
	// Reconstruct known enemies list
	_known.clear();
	ot.getSeen(_known);
	
	// Add LOS info to gridblocks -- NOTE: this gets removed every time the enemy turn ends
	for(UnitSet::iterator iter = _known.begin(); iter != _known.end(); ++iter)
		(*iter)->addLOS();		
	
	// Remove old memories
	for(MemoryMap::iterator iter = _memory.begin(); iter != _memory.end(); ++iter){
		if(!(*iter).second.tick())
			_memory.erase(iter);
	}	
	
	printf("Enemy turn starting.  %i known enemies.  %i other enemies in memory.\n", (int)_known.size(), (int)_memory.size());
}

void EnemyTeam::removeDead(Unit* u)
{	
	Team::removeDead(u);
	
	if(_sUnit == NULL)
		selectNextUnit();
	
	// Adds in changes from 
	if(_sUnit != NULL){
		EnemyUnit* bu = (EnemyUnit*)_sUnit;
		bu->findNewData(_known, _memory);
	}
	
	if(u->getFactionID() == PLAYER){
		_known.erase(u);
		_memory.erase(u);
	}
}
