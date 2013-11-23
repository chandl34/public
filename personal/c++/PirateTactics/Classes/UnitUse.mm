/*
 *  UnitUse.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/16/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Unit.h"
#include "LevelMap.h"


GLshort Unit::use(){
	state = IDLE;
	
	switch(dir){
		case DOWN_LEFT:
		case DOWN_RIGHT:
			if(currBlock->hasDoor()){
				if(currBlock->getDoor()->getSide() == LEFT_SIDE){
					if(dir == DOWN_LEFT){
						currBlock->toggleDoor();
						return UPDATE_SIGHT;
					}
				}				
				else if(dir == DOWN_RIGHT){
					currBlock->toggleDoor();
					return UPDATE_SIGHT;
				}
			}
			break;
			
		case UP_LEFT:
		case UP_RIGHT:
			GridBlock* gb = LevelMap::getBlockByIso(currBlock->getCoordIso(X) + 
													DIR[currBlock->getCoordIso(Y)%2][dir][X], 
													currBlock->getCoordIso(Y) + 
													DIR[currBlock->getCoordIso(Y)%2][dir][Y]);	
			if(gb->hasDoor()){
				if(gb->getDoor()->getSide() == LEFT_SIDE){
					if(dir == UP_RIGHT){
						gb->toggleDoor();
						return UPDATE_SIGHT;
					}
				}		
				else if(dir == UP_LEFT){
					gb->toggleDoor();
					return UPDATE_SIGHT;
				}
			}
			break;
	}
			   
	return NO_CHANGE;
}