/*
 *  TacticalScreenTouch.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "TacticalScreen.h"


bool TacticalScreen::push(GLshort t, const Coord2d<GLshort>& p){	
	// Screen is locked while action is performed.
	if(levelMap->isLocked())
		return false;
	
	if(tacticMenu->push(p))
		touched[t] = tacticMenu;
	else if(levelMap->push(t, p))
		touched[t] = levelMap;	
	
	if(!touched[t]->isMultiTouchable() && touched[0] == touched[1])	// Disallow multi-touching on this object
		touched[t] = NULL;
	
	return true;
}

void TacticalScreen::move(GLshort t, const Coord2d<GLshort>& p){	
	if(touched[t] == NULL)
		return;
		
	if(touched[t]->isMultiTouchable())
		touched[t]->move(t, p);
	else
		((SingleTouchable*)touched[t])->move(p);
}

void TacticalScreen::release(GLshort t, const Coord2d<GLshort>& p){	
	if(touched[t] == NULL)
		return;
	
	if(touched[t]->isMultiTouchable())
		touched[t]->release(t, p);
	else
		((SingleTouchable*)touched[t])->release(p);
	
	if(touched[t] == tacticMenu){	
		switch(tacticMenu->getSelected()){
			case 1:
				printf("Confirm Action\n");
				levelMap->unitAction();
				break;
			case 2:
				printf("Center On Unit\n");
				break;
			case 3:
				printf("Lower Map Level\n");
				break;
			case 4:
				printf("Select Move Mode\n");
				levelMap->setUnitMode(MOVE);
				break;
			case 5:
				printf("Select Shoot Mode\n");
				levelMap->setUnitMode(SHOOT);
				break;
			case 6:
				printf("Select Next Unit\n");
				break;
			case 7:
				printf("Use Ladder\n");
				break;
			case 8:
				printf("Open Inventory\n");
				break;
			case 9:
				printf("End Turn\n");
				break;
			case 10:
				printf("Open Minimap\n");
				break;
			case 11:
				printf("Raise Map Level\n");
				break;
			case 12:
				printf("Select Look Mode\n");
				levelMap->setUnitMode(LOOK);
				break;
			case 13:
				printf("Select Use Mode\n");
				levelMap->setUnitMode(USE);
				break;
			case 14:
				printf("Select Next Unit, Do Not Return\n");
				break;
			case 15:
				printf("Kneel\n");
				break;
			case 16:
				printf("???\n");
				break;
			case 17:
				printf("Open File Menu\n");
				break;
		}
	}
	else{
		
	}
		
	touched[t] = NULL;
}	
