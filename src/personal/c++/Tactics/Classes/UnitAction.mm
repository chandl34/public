/*
 *  UnitAction.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 3/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "Bullet.h"
#include "Grenade.h"
#include "GridBlock.h"
#include "Gun.h"
#include "ImageSet.h"

#include "Options.h"


bool Unit::isIdle() const
{
	return _state == IDLE && !_threadActive;
}

void Unit::clearData()
{
	stop();
}

void Unit::stop()
{
	//printf("Unit stopped.\n");
	_path.clear();
	_state = IDLE;
	_stepsLeft = 0;
	_ray.setDir(0, 0, 0);
	_goalBlock = NULL;
	_estimateTU = 0;
	_hadToOpenDoor = false;
	_animSet.setAnimation(AnimDesc(_kneeling, _dir));//AnimDesc(_dir, _kneeling));
}

void Unit::act(GLshort m)
{	
	if(_goalBlock != NULL || m >= UNIT_MODES){
		_state = m;
		//if(_state == MOVE){		
		//_kneeling = false;
		//_currAnim = MOVE_ANIM;
		//setDir(_dir);
		//	_animSet.setAnimation(AnimDesc(dir, _currAnim));
		//}
		_estimateTU = 0;
	}
}

void Unit::calculateAction(GLshort m, GridBlock* goal)
{	
	printf("\nCalculating new action...\n");
	stop();
	
	if(_currBlock == goal)
		return;
	
	if(m == MOVE){
		// If the goal is accessible, try to find a _path			
		if(!goal->isBlocked(ALL_DIR, WALLS_ONLY) && !goal->hasVisibleUnit(this)){
			_path.find(this, _currBlock, goal, _currTU);
			
			if(!_path.isEmpty()){
				_goalBlock = goal;
				_estimateTU = _path.getCost();		
				if(_kneeling)
					_estimateTU += KNEEL_COST;
			}
		}
	}
	else if(m < UNIT_MODES){		
		_goalBlock = goal;
		GLshort ndir = getDirectionBetween(_goalBlock, _currBlock);
		if(ndir != _dir)
			_estimateTU = LOOK_COST;		
		
		if(m == TOGGLE){ // todo: add a check for if a toggle is possible
			if(findToggleBlock(_currBlock, ndir) != NULL)
				_estimateTU += TOGGLE_COST;
		}
		else{
			Item* item = getEquippedItem();
			if(item != NULL){
				if(m == USE){
					if(item->getType() == GUN){
						if(_inventory.mustReload()){
							if(_inventory.canReload())
								_estimateTU = RELOAD_COST;
						}
						else
							_estimateTU += USE_COST;
					}
					else if(item->getType() == GRENADE){
						_goalBlock = findThrowBlock();
						_estimateTU += USE_COST;
					}
				}
				else if(m == THROW){
					_goalBlock = findThrowBlock();
					cout << _goalBlock->getCoordIso(X) << ", " << _goalBlock->getCoordIso(Y) << endl;
					_estimateTU += THROW_COST;					
				}
			}
		}	
	}
	else{
		if(m == KNEEL)
			_estimateTU = KNEEL_COST;
		else{
			Item* item = getEquippedItem();
			if(item != NULL){
				if(item->getType() == GUN){
					if(_inventory.canReload())
						_estimateTU = RELOAD_COST;
				}
			}
		}		
	}
	
	printf("Action will cost %i out of %i TUs\n", (GLshort)_estimateTU, (GLshort)_currTU);
}

GLshort Unit::update(UnitList& enemyTeam)
{
	if(_currHP <= 0)
		return DIED;
	
	// Update unit
	if(_state == MOVE)
		return move(enemyTeam);
	else if(_state != IDLE){
		if(_state < UNIT_MODES){
			look(enemyTeam);
			
			if(_state == TOGGLE)
				toggle();
			else{
				Item* item = getEquippedItem();
				if(item != NULL){
					if(_state == USE){				
						if(item->getType() == GUN){
							if(_inventory.mustReload()){	
								if(_inventory.canReload())
									reload();
								else
									printf("Out of ammo!\n");
							}
							else{
								// Alert enemy to gunshot -- NOTE: does not happen with grenades
								if(getFactionID() == PLAYER){
									cout << "UNHANDLED E" << endl;
									_unhandled[this] = Memory(_currBlock);
								}	
								
								shoot();
								// todo: add interrupt chance on any in view
							}
						}
						else if(item->getType() == GRENADE){
							Grenade* gren = (Grenade*)item;
							gren->prime();
							throwItem(USE_COST);
						}
					}
					else if(_state == THROW)
						throwItem(THROW_COST);
				}
			}
		}// todo: make these their own methods later
		else if(_state == KNEEL)
			changeStance(&enemyTeam);
		else{
			Item* item = _inventory.getEquippedItem();
			if(item != NULL){
				if(item->getType() == GUN){				
					if(_inventory.canReload())
						reload();
					else
						printf("Out of ammo!\n");
				}
			}
		}
		
		printf("Action over\n");
		stop();
		return STOPPED;
	}
	
	return NO_CHANGE;
}


bool Unit::isKneeling() const
{
	return _kneeling;
}

void Unit::changeStance(UnitList* enemyTeam)
{
	if(getEffectiveTU() >= KNEEL_COST){
		printf("Changed stance\n");
		if(!UNLIMITED_TU && enemyTeam != NULL)		//todo: make this code less confusing.  enemyTeam != NULL on load
			_currTU -= KNEEL_COST;
		
		_kneeling = !_kneeling;
		_currAnim = _kneeling;
		updateGraphics();
		
		if(enemyTeam != NULL)
			updateSight(*enemyTeam, INT_ON_NONE, STANCE_CHANGED);
		
		// update sight -- new rules need to be added!
	}
}
