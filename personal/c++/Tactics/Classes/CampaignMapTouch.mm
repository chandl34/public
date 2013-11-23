/*
 *  CampaignMapTouch.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "CampaignMap.h"

#include "Faction.h"
#include "Level.h"


//--- TOUCH ---//
bool CampaignMap::isLocked()
{
	if(_turnOwner != PLAYER)
		return true;
	
	return false;
}

void CampaignMap::push(GLshort t, const Coord2d<GLshort>& p)
{
	for(GLshort i = 0; i < 2; ++i){
		_startPoint[t][i] = p[i];
		_lastPoint[t][i] = p[i];
	}
	
	if(_touchCount == 0){
		targetLevel(getLevelByOffset(p[X], p[Y]));
		if(_tLevel != NULL){
			Team* team = _tLevel->getTeam(OWNER);
			if(team->getFactionID() == PLAYER)	
				_timePushed = [[NSDate date] timeIntervalSince1970];			
		}
	}	
		
	//	if(_tLevel != NULL){
	//		Faction* faction = _tLevel->getOwner();
	//		if(faction->getID() == PLAYER)
	//			_timePushed = [[NSDate date] timeIntervalSince1970];	
			
			/*
			Faction* faction = _sLevel->getOwner();
			string owner;
			if(faction != NULL)
				owner = faction->getName();
			else
				owner = "n/a";

			printf("Selected %s, owned by %s\n", _sLevel->getName().c_str(), owner.c_str());
			 */
		
		/*
		 
		 if(_touchCount == 0){
		 selectBlock(getBlockByOffset(p[X], p[Y]));
		 
		 // Start a timer for selecting another character
		 Unit* su = _sBlock->getUnit();
		 Unit* sUnit = getSelectedUnit();
		 if(su != NULL && su != sUnit && su->getTeamID() == PLAYER)	
		 _timePushed = [[NSDate date] timeIntervalSince1970];	
		 
		 // Calculate potential action, so that it represents costs and paths on the screen
		 if(sUnit != NULL)							
		 sUnit->calculateAction(_mode, _sBlock);
		 }
		 */
		
		
		/*		 		 
		 // Start a timer for selecting another character
		 Unit* su = _sBlock->getUnit();
		 Unit* sUnit = getSelectedUnit();
		 if(su != NULL && su != sUnit && su->getTeamID() == PLAYER)	
		 _timePushed = [[NSDate date] timeIntervalSince1970];	
		 
		 // Calculate potential action, so that it represents costs and paths on the screen
		 if(sUnit != NULL)							
		 sUnit->calculateAction(_mode, _sBlock);
		 */
	
	++_touchCount;	
}

void CampaignMap::move(GLshort t, const Coord2d<GLshort>& p)
{
	
}

bool CampaignMap::release(GLshort t, const Coord2d<GLshort>& p)
{
	
	_drag = false;	
	_timePushed = -1;
	--_touchCount;		
	
	return true;
}
