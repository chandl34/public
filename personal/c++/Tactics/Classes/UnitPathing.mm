/*
 *  UnitPathing.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "GridBlock.h"
#include "LevelMap.h"

#include "ImageStorage.h"
#include "ModelStorage.h"
#include "Options.h"


const double MOVE_SPEED = 1.0;
const double STEP_COST[] = {MOVE_SPEED * 1.0, MOVE_SPEED * sqrt(0.5)};

const GLshort MOVE_STEPS[] = {
	BLOCK_SIZE_3D[X] / STEP_COST[DIAG] + 0.5, 
	BLOCK_SIZE_3D[Y] / STEP_COST[ORTH] + 0.5
};

const double MOVE_STEP_3D[PATH_DIRS][2] = {
	-STEP_COST[DIAG], 0,								// DOWN_LEFT
	-STEP_COST[ORTH], STEP_COST[ORTH],			// LEFT	
	0, STEP_COST[DIAG],								// UP_LEFT	
	STEP_COST[ORTH], STEP_COST[ORTH],			// UP	
	STEP_COST[DIAG], 0,								// UP_RIGHT	
	STEP_COST[ORTH], -STEP_COST[ORTH],			// RIGHT	
	0, -STEP_COST[DIAG],								// DOWN_RIGHT	
	-STEP_COST[ORTH], -STEP_COST[ORTH],			// DOWN	
};


void Unit::setDir(GLshort d)
{
	if(_dir != d){
		_dir = d;
		updateGraphics();
	}
}

GLshort Unit::move(UnitList& enemyTeam)
{	
	if(_stepsLeft == 0 || _hadToOpenDoor){		// New block reached
		if(_path.isEmpty() && !_hadToOpenDoor){	// Out of directions
			printf("Out of directions\n");
			stop();	
		}
		else{	
			// Original direction
			if(_currAnim != MOVE_ANIM){
				if(_kneeling)
					changeStance(&enemyTeam);
				_currAnim = MOVE_ANIM;
				_animSet.setAnimation(AnimDesc(MOVE_ANIM, _dir));
			}
			
			// Get next direction
			bool turned = false;
			if(!_hadToOpenDoor){
				//printf("Getting next direction\n");
				GLshort ndir = _path.getNextDirection();
				_stepsLeft = MOVE_STEPS[ndir % 2];
				
				if(getEffectiveTU() < MOVE_COST[ndir % 2]){
					printf("Not enough TU to make next step\n");
					stop();
				}
				
				// Update direction
				if(ndir != _dir){				
					if(getEffectiveTU() >= LOOK_COST){							
						// Charge LOOK_COST if not enough TU to move
						if(_state == IDLE){
							if(!UNLIMITED_TU)
								_currTU -= LOOK_COST;
						}
						
						turned = true;
						setDir(ndir);
						updateSight(enemyTeam, INT_ON_NONE, TURNED);
					}
				}				
			}
			// Bad unit spent too many TUs opening the door.  It can't afford the next step.
			else if(getEffectiveTU() < MOVE_COST[_dir % 2]){
				printf("Not enough TU to make next step\n");
				stop();
			}
			
			// If sight update didn't stop the unit, continue
			if(_state == MOVE){
				LevelMap* levelMap = LevelMap::getInstance();
				GridBlock* nextBlock = levelMap->getBlockByIso(_currBlock->getCoordIso(X) + 
																			  DIR[_currBlock->getCoordIso(Y)%2][_dir][X], 
																			  _currBlock->getCoordIso(Y) + 
																			  DIR[_currBlock->getCoordIso(Y)%2][_dir][Y]);
				
				// Bad units must check for doors and open them
				GridBlock* toggleBlock = NULL;
				if(/*teamName == ENEMY && */!_hadToOpenDoor){
					if(_currBlock->isBlocked(_dir, DOORS_ONLY)){
						toggleBlock = findToggleBlock(_currBlock, _dir);
					}
					if(toggleBlock == NULL){
						if(nextBlock->isBlocked((_dir + 4) % PATH_DIRS, DOORS_ONLY))
							toggleBlock = findToggleBlock(_currBlock, _dir);
					}
				}
				
				if(toggleBlock != NULL){
					_hadToOpenDoor = true;
					if(turned){
						if(!UNLIMITED_TU)
							_currTU -= LOOK_COST;
					}
					
					if(_currTU < TOGGLE_COST){
						printf("Not enough TU to open door\n");
						stop();
					}
					else{
						toggleBlock->toggleDoor();
						if(!UNLIMITED_TU)
							_currTU -= TOGGLE_COST;
					}
				}
				else{
					_hadToOpenDoor = false;
					
					_currBlock->setUnit(NULL);					
					_currBlock = nextBlock;
					_currBlock->setUnit(this);
					
					_ray.setDir(MOVE_STEP_3D[_dir][X],
									MOVE_STEP_3D[_dir][Y],
									0);					
					
					if(!UNLIMITED_TU)
						_currTU -= MOVE_COST[_dir % 2];
					
					findLOSThreaded();						
				}
			}			
		}
	}
	else if(_state == MOVE){					
		if(_stepsLeft == 1){						// Last step to next block, snap to			
			if(_threadActive){
				printf("waiting on thread...\n");
				return NO_CHANGE;
			}
			setCoord3D(_currBlock->getCoord3D(X), 
						  _currBlock->getCoord3D(Y),
						  _currBlock->getCoord3D(Z));
			
			updateSight(enemyTeam, INT_ON_ANY, MOVED);
		}
		else{						
			setCoord3D(_ray.getLoc(X) + _ray.getDir(X), 
						  _ray.getLoc(Y) + _ray.getDir(Y),
						  _ray.getLoc(Z) + _ray.getDir(Z));
		}	
		--_stepsLeft;	
	}	
	
	if(_state == IDLE)
		return STOPPED;
	
	return NO_CHANGE;
}
