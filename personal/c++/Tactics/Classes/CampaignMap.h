/*
 *  CampaignMap.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CAMPAIGN_MAP_H_
#define CAMPAIGN_MAP_H_

#include "Screen.h"

#include "Level.h"

class Faction;


class CampaignMap : public MapScreen{
protected:
	CampaignMap();
	
public:
	static CampaignMap* getInstance();
	~CampaignMap();
	
	void tempInit();
	void initCampaign(bool);
	
	//---- GENERAL ----//
	bool inBattle() const;
	void setInBattle(bool);
	
	//---- LEVEL ----//	
	Level* getLevel(GLshort);
	Level* getSelectedLevel();
	Level* getTargetLevel();
	
	void selectLevel(Level*);
	void targetLevel(Level*);
	
	//---- FACTION ----//
	Faction* getFaction(GLshort);
	void addFaction(Faction*);
	
	//---- TEAM ----//
	Team* getSelectedTeam();
	void selectTeam(Team*);
	void selectNextTeam();
	void selectPrevTeam();
	
	//---- GAMEPLAY ----//	
	void confirmAction(); 
	void setMode(GLshort);
	void endTurn();
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- TOUCH ---//
	bool isLocked();		
	void push(GLshort, const Coord2d<GLshort>&);			
	void move(GLshort, const Coord2d<GLshort>&);			
	bool release(GLshort, const Coord2d<GLshort>&);				
	
	//---- IO ----//	
	void saveData(ofstream&);
	
private:
	//---- GENERAL ----//
	static CampaignMap* _campaignMap;
	bool _inBattle;
	
	//---- LEVEL ----//
	vector<Level*> _level;
	Level* _tLevel;					
	
	Level* getLevelByOffset(GLshort, GLshort);
	
	//---- FACTION ----//
	vector<Faction*> _faction;	
};

#endif
