/*
 *  LevelMapUnit.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/8/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"

#include "EnemyTeam.h"
#include "GridBlock.h"

#include "MainScreen.h"
#include "Options.h"


//---- UNIT ----//	
// Team changes

void LevelMap::addUnit(Unit* u, GLshort team, GLshort i, GLshort j)
{
	u->setBlock(_gridBlock[i][j]);
	_gridBlock[i][j]->setUnit(u);
	
	//_team[team]->addUnit(u, *_team[(team + 1) % 2]);
}


// Selection
Unit* LevelMap::getSelectedUnit()
{
	return _team[PLAYER]->getSelectedUnit();
}

void LevelMap::selectUnit(Unit* u){	
	setMode(MOVE);
	_team[PLAYER]->selectUnit(u);
}

void LevelMap::selectNextUnit()
{
	setMode(MOVE);
	_team[PLAYER]->selectNextUnit();
	Unit* u = getSelectedUnit();
	centerView(u->getOffset(X), u->getOffset(Y));
}

void LevelMap::selectPrevUnit()
{
	setMode(MOVE);
	_team[PLAYER]->selectPrevUnit();
	Unit* u = getSelectedUnit();
	centerView(u->getOffset(X), u->getOffset(Y));
}

// Updates
void LevelMap::removeDead()
{
	if(!_dead.empty()){
		Unit* sUnit = getSelectedUnit();
		for(UnitList::iterator iter = _dead.begin(); iter != _dead.end(); ++iter){
			if(*iter == sUnit)
				selectBlock(NULL);
			
			for(GLshort i = 0; i < TEAMS_PER_FIGHT; ++i)
				_team[i]->removeDead(*iter);
			
			delete *iter;
		}
		_dead.clear();
	}
}


//---- GAMEPLAY ----//
// Actions
void LevelMap::confirmAction()
{
	Unit* sUnit = getSelectedUnit();
	if(sUnit != NULL){
		if(_mode == USE){
			if(!sUnit->mustReload() && sUnit->canAim()){
				printf("Opening Aiming Screen\n");							
				MainScreen::setSubScreen(AIMING_SCREEN);
			}
		}
		
		sUnit->act(_mode);
		
		// If reloading or changing stance, automatically switch back to MOVE mode afterwards
		if(_mode >= UNIT_MODES)
			_mode = MOVE;
	}
}

void LevelMap::setMode(GLshort m)
{
	// Clear previously calculated actions and remove cursor
	//	if(unitMode != m){	
	selectBlock(NULL);
	Unit* sUnit = getSelectedUnit();
	if(sUnit != NULL){
		sUnit->clearData();
		if(m >= UNIT_MODES)
			sUnit->calculateAction(m, NULL);
	}
	//	}
	_mode = m;
}

// Turns
void LevelMap::endTurn()
{	
	GLshort oldTeam = _turnOwner;
	if(AI_ON)
		_turnOwner = (_turnOwner + 1) % TEAMS_PER_FIGHT;
	
	// Clear up unused data
	setMode(MOVE);
	
	printf("\nTurn ended for team %i\n\n", oldTeam);
	_team[oldTeam]->endTurnLevel();
	
	// Clear LOS Data from GridBlocks  -- will be rebuilt when newTurn is called
	if(_turnOwner != PLAYER){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
			for(GLshort i = 0; i < MAP_BLOCK[X]; ++i)
				_gridBlock[i][j]->clearLOS();
		}
	}
	
	_team[_turnOwner]->newTurnLevel(*_team[oldTeam]);
}

