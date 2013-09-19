/*
 *  Level.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "Icon.h"

class Faction;
class Level;
class Team;


class Level : public Icon{
public:
	Level(GLshort, const string&, const string&);
	~Level();
	
	//---- GENERAL ----//
	GLshort getID() const;
	const string& getTag() const;
	const string& getName() const;
	
	//---- FACTION ----//
	Team* getTeam(GLshort);	
	Team* getPlayerTeam();
	void setTeam(GLshort, Team*);
	
	void resetFreeTeam(Faction*);
	
	//---- DRAW ----//
	void draw(bool);
	
private:
	//---- GENERAL ----//
	GLshort _levelID;
	string _tag;
	string _name;
	
	//---- FACTION ----//
	Team* _team[TEAMS_PER_LEVEL];
};

#endif