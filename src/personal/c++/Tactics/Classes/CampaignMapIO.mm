/*
 *  CampaignMapIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CampaignMap.h"

#include "Faction.h"
#include "Level.h"


//---- IO ----//	
void CampaignMap::saveData(ofstream& file)
{
	// What makes a campaign?
	// Level Data
	// Factions
	// Teams
	// Units
	
	/*
	 static CampaignMap* _campaignMap;
	 
	 //---- LEVEL ----//
	 LevelList _level;
	 Level* _sLevel;					
	 
	 Level* getLevelByOffset(GLshort, GLshort);
	 void selectLevel(Level*);
	 
	 //---- FACTION ----//
	 vector<Faction*> _faction;	
	 */
	
	
	for(GLshort i = 0; i < _faction.size(); ++i)
		_faction[i]->saveData(file);
	
	//for(GLshort i = 0; i < _level.size(); ++i)
	//	_level[i]->saveData(file);	
}