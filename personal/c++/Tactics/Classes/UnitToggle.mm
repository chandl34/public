/*
 *  UnitUse.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/16/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Unit.h"

#include "DoorObject.h"
#include "GridBlock.h"

#include "LevelMap.h"
#include "Options.h"


GridBlock* Unit::findToggleBlock(GridBlock* curr, GLshort ndir)
{
	LevelMap* levelMap = LevelMap::getInstance();
	switch(ndir){
		case DOWN_LEFT:
		case DOWN_RIGHT:
			if(curr->hasDoor()){
				if(curr->getDoor()->getSide() == LEFT_SIDE){
					if(ndir == DOWN_LEFT)
						return curr;
				}				
				else if(ndir == DOWN_RIGHT)
					return curr;
			}
			break;
			
		case UP_LEFT:
		case UP_RIGHT:
			GridBlock* gb = levelMap->getBlockByIso(curr->getCoordIso(X) + 
																 DIR[curr->getCoordIso(Y)%2][ndir][X], 
																 curr->getCoordIso(Y) + 
																 DIR[curr->getCoordIso(Y)%2][ndir][Y]);	
			if(gb->hasDoor()){
				if(gb->getDoor()->getSide() == LEFT_SIDE){
					if(ndir == UP_RIGHT)
						return gb;
				}		
				else if(ndir == UP_LEFT)
					return gb;
			}
			break;
	}
	
	return NULL;
}

void Unit::toggle()
{
	if(_currTU >= TOGGLE_COST){		
		GridBlock* gb = findToggleBlock(_currBlock, _dir);
		if(gb != NULL){
			if(!UNLIMITED_TU)
				_currTU -= TOGGLE_COST;
			gb->toggleDoor();
		}
	}
}