/*
 *  Level.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Level.h"

#include "Faction.h"
#include "Team.h"

#include "Math.h"
#include "Options.h"


Level::Level(GLshort levelID, const string& tag, const string& name)
: _levelID(levelID)
, _tag(tag)
, _name(name)
{
	_team[OWNER] = NULL;
	_team[INTRUDER] = NULL;
	_team[FREE] = NULL;
}

Level::~Level()
{
	
}


//---- GENERAL ----//
GLshort Level::getID() const
{
	return _levelID;
}

const string& Level::getTag() const
{
	return _tag;
}

const string& Level::getName() const
{
	return _name;
}


//---- FACTION ----//
Team* Level::getTeam(GLshort c)
{
	return _team[c];
}

Team* Level::getPlayerTeam()
{
	for(GLshort i = 0; i < TEAMS_PER_FIGHT; ++i){
		if(_team[i] != NULL && _team[i]->getFactionID() == PLAYER)
			return _team[i];
	}
	return NULL;
	/*
	if(_team[OWNER] != NULL && _team[OWNER].getFactionID() == PLAYER)
		return &_team[OWNER];
	else if(_team[INTRUDER] != NULL && _team[INTRUDER
	 */
}

void Level::setTeam(GLshort c, Team* t)
{
	_team[c] = t;
}

void Level::resetFreeTeam(Faction* f)
{
	if(_team[FREE] != NULL){
		Faction* tf = _team[FREE]->getFaction();
		tf->removeTeam(_team[FREE]);
		delete _team[FREE];
	}
	
	_team[FREE] = Team::create(f, this);
	
	// Fill with random units
	GLshort units = MIN_NEW_HIRES + random(MAX_NEW_HIRES - MIN_NEW_HIRES);
	for(GLshort i = 0; i < units; ++i)
		_team[FREE]->addUnit(Unit::create(ObjType(UNIT), f->getID(), 
										  Dir(0), 0,
										  HP(MIN_NEW_HIRE_HP + random(MAX_NEW_HIRE_HP - MIN_NEW_HIRE_HP)),
										  TU(MIN_NEW_HIRE_TU + random(MAX_NEW_HIRE_TU - MIN_NEW_HIRE_TU))));
										  
	
	/*
	 Unit* Unit::create(const ObjType& ot, GLshort fid, 
	 const Dir& d, GLshort is, 
	 const HP& mhp, const TU& mtu)
	 */
}
