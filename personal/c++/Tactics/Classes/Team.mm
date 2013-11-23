/*
 *  Team.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Team.h"

#include "EnemyTeam.h"
#include "Faction.h"
#include "Level.h"
#include "Unit.h"


Team* Team::create(Faction* faction, Level* level)
{
	if(faction->getID() == PLAYER)
		return new Team(faction, level);
	else 
		return new EnemyTeam(faction, level);
}

Team::Team(Faction* faction, Level* level)
{
	//-- GENERAL --//
	_faction = faction;
	_faction->addTeam(this);
	
	//--- LEVEL ---//
	_level = level;
	//level->setTeam(type, this);
	
	//--- UNIT ---//
	_sUnit = NULL;
}

Team::~Team()
{
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter)
		delete *iter;
}


//-- GENERAL --//
GLshort Team::getFactionID() const
{
	if(_faction == NULL)
		cout << "shit " << endl;
	return _faction->getID();
}

Faction* Team::getFaction()
{
	return _faction;
}


//--- LEVEL ---//
Level* Team::getLevel()
{
	return _level;
}

void Team::setLevel(Level* level)
{
	_level = level;
}


//--- UNIT ---//
void Team::addUnit(Unit* u)
{
	u->setTeam(this);
	_unit.push_back(u);
}

void Team::removeUnit(Unit* u)
{
	_unit.remove(u);
}

Unit* Team::getSelectedUnit()
{
	return _sUnit;
}

void Team::selectUnit(Unit* u)
{
	if(_sUnit != NULL)
		_sUnit->clearData();
	_sUnit = u;
}

void Team::selectNextUnit()
{
	if(_sUnit == NULL){
		if(!_unit.empty())
			selectUnit(*_unit.begin());
	}
	else{	
		UnitList::iterator iter;	
		for(iter = _unit.begin(); iter != _unit.end(); ++iter){
			if(_sUnit == *iter)
				break;
		}
		
		++iter;
		if(iter == _unit.end())
			selectUnit(*_unit.begin());
		else
			selectUnit(*iter);
	}
}

void Team::selectPrevUnit()
{
	if(_sUnit == NULL){
		if(!_unit.empty())
			selectUnit(*_unit.begin());
	}
	else{	
		UnitList::reverse_iterator iter;	
		for(iter = _unit.rbegin(); iter != _unit.rend(); ++iter){
			if(_sUnit == *iter)
				break;
		}
		
		++iter;
		if(iter == _unit.rend())
			selectUnit(*_unit.rbegin());
		else
			selectUnit(*iter);
	}
}


//--- UI ---//
Unit* Team::getUnitByIcon(const Coord2d<GLshort>& p)
{
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter){
		if((*iter)->isTouchingIcon(p))
			return *iter;
	}
	return NULL;
}

void Team::drawIcons(bool step)
{
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter)
		(*iter)->drawIcon(step);
}

void Team::resetIconOffsets(double x, double y)
{
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter){
		y -= UNIT_ICON_SIZE[Y];
		(*iter)->setIconOffset(x, y);
	}
}


//-- GAMEPLAY CAMPAIGN --//
void Team::newTurnCampaign()
{
	// Reset hiring list
	if(_level->getTeam(OWNER) == this)
		_level->resetFreeTeam(_faction);	
}


//-- GAMEPLAY LEVEL --//
void Team::initLevel(Team& ot, bool isNew)
{
	GridBlock* gb;
	// Place each unit in a random location and update sight -- TEMP!!!!!1111!!11
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter){
		if(isNew){		// temp! todo: remove!
			gb = getRandomBlock(true);
			(*iter)->setBlock(gb);
			gb->setUnit(*iter);		
		}
		(*iter)->updateSight(ot._unit, INT_ON_NONE, MOVED);
	}
}

GLshort Team::update(Team& ot, UnitList& dead)
{
	bool deselect = false;
	GLshort action;
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter){
		action = (*iter)->update(ot._unit);
		if(action == DIED)
			dead.push_back(*iter);			
		else if(action == STOPPED)
			deselect = true;
	}
	
	if(deselect)
		return DESELECT;
	
	return NO_CHANGE;
}

void Team::removeDead(Unit* u)
{
	if(u->getFactionID() != getFactionID()){
		for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter)
			(*iter)->removeDead(u);
	}
	
	if(u == _sUnit)
		selectUnit(NULL);
	
	_unit.remove(u);
}

void Team::endTurnLevel()
{
	selectUnit(NULL);
}

void Team::newTurnLevel(Team& ot)
{
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter)
		(*iter)->newTurn();
	
	if(!_unit.empty())
		selectUnit(*_unit.begin());
}


//--- SIGHT ---//	
void Team::getSeen(UnitSet& us)
{	
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter){
		if((*iter)->hasBeenSeen())
			us.insert(*iter);		
	}
}

void Team::updateSight(Team& ot, GLshort interrupt, GLshort reason)
{
	for(UnitList::iterator iter = _unit.begin(); iter != _unit.end(); ++iter)
		(*iter)->updateSight(ot._unit, interrupt, reason);
	
	/*
	 for(UnitList::iterator iter = unit.begin(); iter != unit.end(); ++iter){
	 for(BlockSet::iterator bsiter = bs.begin(); bsiter != bs.end(); bs++iter){
	 if((*iter)->inViewScope(*bsiter)){
	 cout << *iter << " is having its sight updated" << endl;
	 (*iter)->updateSight(ot.unit, interrupt, MAP_CHANGED);
	 break;
	 }
	 }
	 }
	 */
}
