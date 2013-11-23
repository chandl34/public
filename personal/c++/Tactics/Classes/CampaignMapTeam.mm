/*
 *  CampaignMapTeam.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CampaignMap.h"

#include "Faction.h"

#include "MainScreen.h"
#include "Options.h"



//---- TEAM ----//
Team* CampaignMap::getSelectedTeam()
{
	return _faction[PLAYER]->getSelectedTeam();
}


void CampaignMap::selectTeam(Team* team)
{
	_faction[PLAYER]->selectTeam(team);
	//setMode(MOVE);
	//_team[PLAYER]->selectUnit(u);
}

void CampaignMap::selectNextTeam()
{
	_faction[PLAYER]->selectNextTeam();
	//setMode(MOVE);
	//_team[PLAYER]->selectNextUnit();
	//Unit* u = getSelectedUnit();
	//centerView(u->getOffset(X), u->getOffset(Y));
}

void CampaignMap::selectPrevTeam()
{
	_faction[PLAYER]->selectPrevTeam();
	//setMode(MOVE);
	//_team[PLAYER]->selectPrevUnit();
	//Unit* u = getSelectedUnit();
	//centerView(u->getOffset(X), u->getOffset(Y));
}


//---- GAMEPLAY ----//	
// Actions
void CampaignMap::confirmAction()
{
	// temp until i get attack subscreeen working
	if(_tLevel != NULL){
		if(_mode == 0){
			Team* aTeam = getSelectedTeam();
			if(aTeam != NULL){				
				Level* aLevel = aTeam->getLevel();
				Faction* aFaction = aTeam->getFaction();
				
				Team* dTeam = _tLevel->getTeam(OWNER);
				Faction* dFaction = dTeam->getFaction();
				
				if(aFaction != dFaction){
					printf("%s from %s attacking %s at %s!\n", 
							 aFaction->getName().c_str(), aLevel->getName().c_str(),
							 dFaction->getName().c_str(), _tLevel->getName().c_str());	
					
					/// temp -- todo: fix this
					_tLevel->setTeam(INTRUDER, aTeam);
					aTeam->setLevel(_tLevel);
					
					Team* nTeam = Team::create(aFaction, aLevel); // Note: this gets added to faction
					aLevel->setTeam(OWNER, nTeam);
					
					_inBattle = true;
					MainScreen::newBattle(_tLevel->getTag(), aTeam, dTeam);
				}
			}
			//	if(sTeam != NULL && sTeam->getFaction() != _tLevel->getOwner()){		
			//		printf("Attacking %s!\n", _sLevel->getName().c_str());
			//		MainScreen::initMap(sLevel->getTag());
			//		MainScreen::setScreen(LEVEL_SCREEN);
			//	}
		}
	}
	/*
	 Unit* sUnit = getSelectedUnit();
	 if(sUnit != NULL){
	 if(_mode == USE){
	 if(!sUnit->mustReload() && sUnit->canAim())
	 return false;
	 }
	 
	 sUnit->act(_mode);
	 
	 // If reloading or changing stance, automatically switch back to MOVE mode afterwards
	 if(_mode >= UNIT_MODES)
	 _mode = MOVE;
	 }
	 return true;
	 */
}

void CampaignMap::setMode(GLshort m)
{
	_mode = m;
	cout << _mode << endl;
}

// Turns
void CampaignMap::endTurn()
{	
	GLshort oldFaction = _turnOwner;
	if(AI_ON)
		_turnOwner = (_turnOwner + 1) % _faction.size();
	
	printf("\nTurn ended for faction %i\n\n", oldFaction);
	_faction[oldFaction]->endTurn();
	
	_faction[_turnOwner]->newTurn();
}
