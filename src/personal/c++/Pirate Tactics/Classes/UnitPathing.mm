/*
 *  UnitPathing.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"
#include "LevelMap.h"


bool Unit::isMoving() const{
	return state == MOVE;
}

void Unit::stop(){
	delete directions;
	directions = NULL;
	state = IDLE;
	stepsLeft = 0;
	ray.setDir(0, 0, 0);
}

GLshort Unit::move(){	
	if(stepsLeft == 0){							// New block reached
		if(directions->isEmpty())				// Out of directions
			//printf("Out of Directions\n");
			stop();	
		else{									// Get next direction
			//printf("Getting next direction\n");
			GLshort odir = dir;
									
			dir = directions->getNext();
			stepsLeft = MOVE_STEPS[dir%2];
			
			if(odir != dir)
				return UPDATE_SIGHT;
		}
	}
	if(state == MOVE){					
		if(stepsLeft == 1){						// Last step to next block, snap to				
			setCoord3D(currBlock->getCoord3D(X), 
					   currBlock->getCoord3D(Y),
					   currBlock->getCoord3D(Z));
			stepsLeft--;	
			return UPDATE_SIGHT;
		}
		else{									
			if(stepsLeft == MOVE_STEPS[dir%2]){	// First step
				printf("First step\n");
				currBlock->setUnit(NULL);	
				
				currBlock = LevelMap::getBlockByIso(currBlock->getCoordIso(X) + 
													DIR[currBlock->getCoordIso(Y)%2][dir][X], 
													currBlock->getCoordIso(Y) + 
													DIR[currBlock->getCoordIso(Y)%2][dir][Y]);	
				ray.setDir(MOVE_STEP_3D[dir][X],
							MOVE_STEP_3D[dir][Y],
							0);
				
				currBlock->setUnit(this);
			}		
			
			setCoord3D(ray.getLoc(X) + ray.getDir(X), 
					   ray.getLoc(Y) + ray.getDir(Y),
					   ray.getLoc(Z) + ray.getDir(Z));
			stepsLeft--;				
		}	
	}	
	
	return NO_CHANGE;
}
