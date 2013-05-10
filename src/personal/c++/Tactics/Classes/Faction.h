/*
 *  Faction.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FACTION_H_
#define FACTION_H_

#include "Color.h"
#include "Team.h"


class Faction{
protected:
	Faction(GLshort, const string&, const Color&);
	
public:
	static Faction* create(GLshort, const string&, const Color&);
	virtual ~Faction();
	
	//-- GENERAL --//
	GLshort getID() const;
	const string& getName() const;
	const Color& getColor() const;
	
	//---- LEVEL ----//
	void addTeam(Team*);
	void removeTeam(Team*);
	
	Team* getSelectedTeam();
	void selectTeam(Team*);
	void selectNextTeam();
	void selectPrevTeam();	
	
	//--- GAMEPLAY ---//
	void endTurn();
	void newTurn();
	
	//---- IO ----//	
	void saveData(ofstream&);
	
private:
	//-- GENERAL --//
	GLshort _factionID;
	string _name;
	Color _color;
	
	//---- TEAM ----//	
	TeamList _team;
	Team* _sTeam;
	
	// teams, levels owned, etc...
	
};

#endif