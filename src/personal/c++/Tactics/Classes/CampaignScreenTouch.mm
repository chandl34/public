/*
 *  CampaignScreenTouch.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "CampaignScreen.h"

#include "CampaignMap.h"
#include "Faction.h"
#include "Level.h"

#include "MainScreen.h"


//--- TOUCH ---//
void CampaignScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	// If screen is locked, touch will be ignored.
	if(_campaignMap->isLocked())
		return;
	
	if(_menu.isTouching(p))
		_touched[t] = &_menu;
	else
		_touched[t] = _campaignMap;
	
	// Disallow illegal touches
	if(_touched[0] == _touched[1]){
		if(!_touched[t]->isMultiTouchable())
			_touched[t] = NULL;
	}
	else{
		// Disable touching two different touchables at once
		if(_touched[(t + 1) % 2] != NULL)
			_touched[t] = NULL;
	}
	
	if(_touched[t] != NULL)
		_touched[t]->push(t, p);
}

void CampaignScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	if(_touched[t] == NULL)
		return;
	
	_touched[t]->move(t, p);
}

bool CampaignScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(_touched[t] == NULL)
		return false;
	
	if(_touched[t]->release(t, p)){
		if(_touched[t] == &_menu){
			GLshort s = _menu.getSelectedOption();			
			switch(_menu.getSelected()){
				case MODE_MENU:	
					if(s > 0){
						printf("Selected %i Mode Button\n", s - 1);
						_campaignMap->setMode(s - 1);
					}				
					break;
					
				case TEAM_MENU:
					if(s == 1){
						printf("Opening Inventory Screen\n");
					}
					else if(s == 2){
						if(_campaignMap->getSelectedTeam() != NULL){							
							printf("Opening Team Management Screen\n");				
							MainScreen::setSubScreen(TEAM_SCREEN);
						}
					}
					break;
					
				case PREV_MENU:
					printf("Select Previous Team\n");
					_campaignMap->selectPrevTeam();
					break;
					
				case LEVEL_MENU:
					printf("Opening Level Info Screen\n");
					break;
					
				case NEXT_MENU:
					printf("Select Next Team\n");
					_campaignMap->selectNextTeam();
					break;
					
				case DOMESTICS_MENU:
					if(s == 1){
						printf("Opening Store Menu\n");
					}
					else if(s == 2){
						printf("Opening Research Screen\n");
					}
					break;
					
				case OPTION_MENU:	
					if(s == 0){
						printf("Selected Confirm Button\n");
						_campaignMap->confirmAction();
						//if(!_levelMap->confirmAction()){
						//	printf("Opening Aiming Screen\n");							
						//	MainScreen::setSubScreen(AIMING_SCREEN);
						//}
					}
					else if(s == 1){
						printf("End Turn\n");
						_campaignMap->endTurn();
					}
					else{
						printf("Opening Menu Screen\n");						
						MainScreen::setSubScreen(MENU_SCREEN);
					}
					break;					
			};
		}
	}   
	
	_touched[t] = NULL;
	
	return true;
}
