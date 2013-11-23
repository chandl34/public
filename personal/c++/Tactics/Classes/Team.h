/*
 *  Team.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TEAM_H_
#define TEAM_H_

#include "Unit.h"

class Object;
class Faction;
class Level;
class Team;


enum{DESELECT = 1};

typedef list<Team*> TeamList;


class Team{
protected:
	Team(Faction*, Level*);
	
public:
	static Team* create(Faction*, Level*);
	virtual ~Team();
	
	//-- GENERAL --//
	GLshort getFactionID() const;
	Faction* getFaction();
	
	//--- LEVEL ---//
	Level* getLevel();
	void setLevel(Level*);
	
	//--- UNIT ---//
	void addUnit(Unit*);
	void removeUnit(Unit*);
	
	Unit* getSelectedUnit();
	void selectUnit(Unit*);
	void selectNextUnit();
	void selectPrevUnit();
	
	//--- UI ---//
	Unit* getUnitByIcon(const Coord2d<GLshort>&);
	void drawIcons(bool);
	void resetIconOffsets(double, double);
	
	//-- GAMEPLAY CAMPAIGN --//
	void newTurnCampaign();
	
	//-- GAMEPLAY LEVEL --//
	void initLevel(Team&, bool);
	virtual GLshort update(Team&, UnitList&);
	virtual void removeDead(Unit*);	
	void endTurnLevel();
	virtual void newTurnLevel(Team&);
	
	//--- SIGHT ---//	
	void getSeen(UnitSet&);
	void updateSight(Team&, GLshort, GLshort);
	
	//---- IO ----//	
	void saveData(ofstream&);
		
protected:
	//-- GENERAL --//
	Faction* _faction;
	
	//--- LEVEL ---//
	Level* _level;
	
	//--- UNIT ---//
	UnitList _unit;
	Unit* _sUnit;
};

#endif