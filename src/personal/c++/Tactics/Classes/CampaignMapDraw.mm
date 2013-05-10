/*
 *  CampaignMapDraw.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CampaignMap.h"

#include "EnemyFaction.h"



//---- DRAW ----//
void CampaignMap::draw(bool step)
{
	//----- CHECK FOR PRESSES -----//
	if(_timePushed > 0 && [[NSDate date] timeIntervalSince1970] - _timePushed > _actionDelay){
		_timePushed = -1;
		selectTeam(_tLevel->getTeam(OWNER));
	}	
	
	
	//----- DRAW LEVELS -----//
	resetView();
	glMatrixMode(GL_PROJECTION);	
	glTranslatef(0, 
					 MENU_SIZE[Y], 
					 0);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	
	for(GLshort i = 0; i < _level.size(); ++i)
		_level[i]->draw(step);
	
	
	//----- DRAW OVERLAYS -----//
	_cursor.draw(step);
	
	
	//----- AI PLANNING -----//
	if(_turnOwner != PLAYER){
		EnemyFaction* ef = (EnemyFaction*)_faction[_turnOwner];
		if(!ef->plan())
			endTurn();
	}
}
