/*
 *  UnitAction.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 3/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"
#include "Pathing.h"
#include "LevelMap.h"
#include "Bullet.h"


GLshort Unit::update(){
	if(looking)
		return look();
	else{
		switch(state){
			case MOVE:
				return move();
								
			case USE:
				return use();	
		}
	}
	
	return true;
}

void Unit::calculateAction(GLshort m, GridBlock* goal){
	switch(m){
		case MOVE:
			if(directions != NULL){
				delete directions;
				directions = NULL;
			}			
			// If the goal is accessible, try to find a path			
			if(!goal->isBlocked(ALL_DIR) && !goal->hasVisibleUnit()){
				directions = Pathing::getDirections(currBlock->getCoordIso(), goal->getCoordIso());
			//	if(directions != NULL)
			//		goalBlock = goal;
				
			}
			//printf("Got new directions\n");
			break;
			
		case LOOK:
			goalBlock = goal;
			break;		
			
		case USE:
			goalBlock = goal;
			break;
			
		case SHOOT:
			goalBlock = goal;
			// Change this later to pre-calculate like pathing does~!!@!@!@!@!@!@
			break;
	}	
}

void Unit::act(GLshort m){	
	switch(m){
		case MOVE:
			if(directions != NULL)	// Confirm button doesn't work if directions haven't been found yet
				state = MOVE;
			break;
			
		case LOOK:
			if(goalBlock != NULL){
				looking = true;
				state = IDLE;
			}
			break;
			
		case USE:
			if(goalBlock != NULL){
				looking = true;
				state = USE;
			}
			break;
			
		case SHOOT:
			if(goalBlock != NULL){
				// Change this later to pre-calculate like pathing does~!!@!@!@!@!@!@
				shoot();				 
			}
			break;
	}
}
