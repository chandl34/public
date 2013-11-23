/*
 *  Faction.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Faction.h"

#include "EnemyFaction.h"


Faction* Faction::create(GLshort factionID, const string& name, const Color& color)
{
	if(factionID == PLAYER)
		return new Faction(factionID, name, color);
	else 
		return new EnemyFaction(factionID, name, color);
}

Faction::Faction(GLshort factionID, const string& name, const Color& color)
: _factionID(factionID)
, _name(name)
, _color(color)
{
	_sTeam = NULL;
}

Faction::~Faction()
{
	for(TeamList::iterator iter = _team.begin(); iter != _team.end(); ++iter)
		delete *iter;
}


//-- GENERAL --//
GLshort Faction::getID() const
{
	return _factionID;
}

const string& Faction::getName() const
{
	return _name;
}

const Color& Faction::getColor() const
{
	return _color;
}


//---- LEVEL ----//
void Faction::addTeam(Team* team)
{
	_team.push_back(team);
}

void Faction::removeTeam(Team* team)
{
	_team.remove(team);
}


Team* Faction::getSelectedTeam()
{
	return _sTeam;
}

void Faction::selectTeam(Team* team)
{
//	if(_sUnit != NULL)
//		_sUnit->clearData();
	_sTeam = team;
}

void Faction::selectNextTeam()
{
	if(_sTeam == NULL){
		if(!_team.empty())
			selectTeam(*_team.begin());
	}
	else{	
		TeamList::iterator iter;	
		for(iter = _team.begin(); iter != _team.end(); ++iter){
			if(_sTeam == *iter)
				break;
		}
		
		++iter;
		if(iter == _team.end())
			selectTeam(*_team.begin());
		else
			selectTeam(*iter);
	}
}

void Faction::selectPrevTeam()
{
	if(_sTeam == NULL){
		if(!_team.empty())
			selectTeam(*_team.begin());
	}
	else{	
		TeamList::reverse_iterator iter;	
		for(iter = _team.rbegin(); iter != _team.rend(); ++iter){
			if(_sTeam == *iter)
				break;
		}
		
		++iter;
		if(iter == _team.rend())
			selectTeam(*_team.rbegin());
		else
			selectTeam(*iter);
	}
}

//--- GAMEPLAY ---//
void Faction::endTurn()
{
	
}

void Faction::newTurn()
{
	for(TeamList::iterator iter = _team.begin(); iter != _team.end(); ++iter){
		(*iter)->newTurnCampaign();
	}
}

