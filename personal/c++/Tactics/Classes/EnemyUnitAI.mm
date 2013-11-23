/*
 *  EnemyUnitAI.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "EnemyUnit.h"

#include "GridBlock.h"
#include "Heap.h"
#include "RangeNode.h"
#include "View.h"

#include "LevelMap.h"
#include "Math.h"



//--- AI ---//
bool EnemyUnit::isFinished()
{
	return _plan.empty() && _stage == S_END;
}

// todo: implement all these and any others
// When does this get called?
// 1.  a new enemy was spotted, while this unit was moving ==> insert into known and update LOS
// 2.  an enemy disappeared, while it was moving during enemy turn ==> store as a memory  -- note:: this might not be the sUnit
// 3.  an enemy took a shot -------------- not handled yet, but would go into memory if unseen


// --- when else should memories be made?  when hiding unseen.  that is at turn's end
void EnemyUnit::findNewData(UnitSet& known, MemoryMap& memory)
{
	if(!_unhandled.empty()){
		for(MemoryMap::iterator iter = _unhandled.begin(); iter != _unhandled.end(); ++iter){
			Unit* u = iter->first;
			memory.erase(u);	
			if(u->hasBeenSeen()){
				if(!known.count(u)){
					printf("--Adding to known enemy list--\n");
					known.insert(u);
					u->addLOS();
				}
			}			
			else{
				printf("--Adding enemy location memory--\n");
				known.erase(u);
				memory[u] = iter->second;
			}
		}
		
		_unhandled.clear();
	}
}


void EnemyUnit::findPlan(UnitSet& known, MemoryMap& memory)
{
	if(_plan.empty()){
		//enum{S_AMMO, S_FIND, S_APPROACH, S_ATTACK, S_COVER, S_TURN_180, S_END}; 
		switch(_stage){
			case S_AMMO:
				checkAmmo();
				break;
				
			case S_FIND:
				findEnemy(known, memory);
				break;
				
			case S_APPROACH:
				approach();
				break;
				
			case S_ATTACK:
				attackEnemy();
				break;
				
			case S_COVER:
				runOrKneel();
				break;
				
			case S_TURN:
				turn(known, memory);
				break;
		};
	}
}

void EnemyUnit::workPlan()
{
	if(!_plan.empty()){
		Plan& p = _plan.front();
		if(p.getGoal() != NULL){
			calculateAction(p.getAction(), p.getGoal());
			act(p.getAction());		
		}
		_plan.pop_front();		
	}
}


// Stages
// Reload if needed
void EnemyUnit::checkAmmo()
{
	if(mustReload())
		_plan.push_back(Plan(RELOAD, _currBlock));
	
	_stage = S_FIND;
	
	// todo: later, add ability to search for ammo if low
}

// Find an enemy if you don't see any
void EnemyUnit::findEnemy(UnitSet& known, MemoryMap& memory)
{
	if(_sees.empty()){
		_reserveTU = USE_COST + LOOK_COST;
		
		GridBlock* t = getClosestEnemyLoc(known, &memory);
		if(t == NULL)
			t = getRandomBlockInRange(_currBlock, PATROL_MAX);
		
		if(t != NULL)
			_plan.push_back(Plan(MOVE, t));
		
		_reserveTU = 0;
		
		// 1. if any known enemies are within a certain range, head toward nearest one ----- done!
		// --- note: if this area is considered too dangerous, stay still and look toward enemies
		// 2. if any assumed enemies are within a certain range, head toward nearest one  ---- done!		
	}
	
	_stage = S_APPROACH;
}

// Get closer if necessary
void EnemyUnit::approach()
{
	if(!_sees.empty()){
		// Determine if chance to hit is too low
		GridBlock* t = getClosestEnemyLoc(_sees);
		aim(TORSO, 1, 0, t);
		
		printf("\nDeciding whether to approach. CTH: %f\n", getEffectiveCTH()); 
		if(getEffectiveCTH() < 25){
			GLshort moveDist = getEffectiveTU() / MOVE_COST[DIAG] - 1;
			moveDist = min(APPROACH_MAX, moveDist);
			if(moveDist > 0){
				t = getEmptyLocNear(t->getUnit(), moveDist);
				if(t != NULL){
					printf("Getting closer for a better shot\n");
					cout << "closer spot:  " << t->getCoordPath(X) << ", " << t->getCoordPath(Y) << endl;
					_plan.push_back(Plan(MOVE, t));		
				}
			}				
		}		
	}	
	
	_stage = S_ATTACK;
}

// Attack
void EnemyUnit::attackEnemy()
{
	if(!_sees.empty()){
		GridBlock* t = getClosestEnemyLoc(_sees);
		aim(TORSO, 1, 0, t);
		
		
		// 1. Decide whether to use a grenade or not
		// 2. Decide aiming level would be the most efficient
		// 3. Decide ahead of time if this is going to be a shoot and run, or kneel and shoot and stay
		// --- if running, find nearest out of view spot, and determine if path is too long to do a shoot, run and turn
		// --- also consider standing or kneeling in orange/yellow zones where possible
		
		printf("\nTaking shot.  CTH: %f", getEffectiveCTH()); 
		_plan.push_back(Plan(USE, t));
	}
	
	_stage = S_COVER;
}

// Get out of harm's way
void EnemyUnit::runOrKneel()
{
	// If potential threats are nearby
	if(_currBlock->getDangerLevel() != 0){		
		GridBlock* t = getClosestEnemyLoc(_sees);
		GLshort effTU = getEffectiveTU();	
		GLshort cost = USE_COST;		
		
		if(t != NULL){	
			if(getDirectionBetween(t, _currBlock) != _dir)
				++cost;
		
			// If can make another good shot, do that
			if(effTU >=	cost){
				aim(TORSO, 1, 0, t);
				printf("\nDeciding whether to shoot or run. CTH: %f\n", getEffectiveCTH());
				if(getEffectiveCTH() > 75){
					_stage = S_AMMO;
					return;
				}
			}
		}
		
		// Check for a safer spot to end turn
		printf("\nLooking for a safer location\n");
		GLshort runDist = min((int)RUN_MAX, effTU / MOVE_COST[DIAG]);		
		BlockEst be = getSaferLocInRange(runDist);	
		
		if(be.first != NULL)
			printf("\nSafest location at %i, %i\n", be.first->getCoordPath(X), be.first->getCoordPath(Y));
		
		// Run if you can't afford another shot also
		if(be.first != NULL && (t == NULL || effTU - be.second < cost)){
			printf("Moving to safe spot before turn ends\n");
			_plan.push_back(Plan(MOVE, be.first));
			_stage = S_TURN;
			return;
		}		
		else if(t != NULL && effTU >= cost){
			_stage = S_AMMO;		
			return;
		}
	}	
	
	_stage = S_END;
}
		
// As last step, turn around
void EnemyUnit::turn(UnitSet& known, MemoryMap& memory)
{
	if(_sees.empty()){
		GridBlock* t = getClosestEnemyLoc(known, &memory);
		if(t != NULL){ // Should never be NULL
			printf("Turning toward target\n");
			_plan.push_back(Plan(LOOK, t));
		}
	}
	
	_stage = S_END;
}


// Helper methods	
GridBlock* EnemyUnit::getClosestEnemyLoc(UnitSet& us, MemoryMap* mm)
{	
	if(us.empty() && (mm == NULL || mm->empty()))
		return NULL;	
	
	GridBlock* gb;
	Heap heap(true); // minheap
	for(UnitSet::iterator iter = us.begin(); iter != us.end(); ++iter){
		gb = (*iter)->getBlock();
		heap.push(new RangeNode(gb->getCoordPath(), _currBlock->getCoordPath()));
	}			
	
	if(mm != NULL){
		for(MemoryMap::iterator iter = mm->begin(); iter != mm->end(); ++iter){
			gb = (*iter).second.getBlock();
			heap.push(new RangeNode(gb->getCoordPath(), 
											getDistanceBetween(_currBlock, gb) + MEMORY_MOD));
		}	
	}
	
	RangeNode* rn = (RangeNode*)heap.pop();
	LevelMap* levelMap = LevelMap::getInstance();
	gb = levelMap->getBlockByPath(rn->getCoord(X), rn->getCoord(Y));
	delete rn;
	
	while(!heap.isEmpty()){
		rn = (RangeNode*)heap.pop();
		delete rn;
	}
		
	return gb;
}

GridBlock* EnemyUnit::getEmptyLocNear(Unit* u, GLshort maxRng)
{
	LevelMap* levelMap = LevelMap::getInstance();
	GridBlock* ublock = u->getBlock();
	GLshort distToTarg = ceil(getDistanceBetween(_currBlock, ublock)) - 1;
	
	cout << "distToTarg: " << distToTarg << "   " << "maxRng: " << maxRng << endl;
	
	BlockSet uScope, myScope;	
	find360Scope(uScope, ublock, distToTarg);
	find360Scope(myScope, _currBlock, maxRng);
	
	// Push all traversable blocks to the heap
	Heap heap(true); // minheap
	for(BlockSet::iterator iter = myScope.begin(); iter != myScope.end(); ++iter){
		if(uScope.count(*iter)){	// Find overlap between the two scopes
			if(!(*iter)->isBlocked(ALL_DIR, WALLS_ONLY) && !(*iter)->hasVisibleUnit(this) && u->couldSee(*iter))
				heap.push(new RangeNode((*iter)->getCoordPath(), ublock->getCoordPath()));
		}
	}
	
	GridBlock* gb = NULL;
	GridBlock* lastResort = NULL;
	GridBlock* temp;
	RangeNode* rn;
	while(!heap.isEmpty()){
		rn = (RangeNode*)heap.pop();
		if(gb == NULL){
			temp = levelMap->getBlockByPath(rn->getCoord(X), rn->getCoord(Y));
			if(getDistanceBetween(_currBlock, temp) > getDistanceBetween(_currBlock, ublock)){
				if(lastResort == NULL)
					lastResort = temp;
			}
			else
				gb = temp;
		}
		delete rn;
	}
	
	if(gb == NULL)
		return lastResort;	
	return gb;
}

// This finds the best combination of safeness and distance
BlockEst EnemyUnit::getSaferLocInRange(GLshort maxRng)
{
	GLshort currDanger = _currBlock->getDangerLevel();
	BlockSet bs;	
	find360Scope(bs, _currBlock, maxRng);	
	
	// Remove bad options
	GLshort testDanger;
	Heap heap(true); // minheap
	for(BlockSet::iterator iter = bs.begin(); iter != bs.end(); ++iter){
		testDanger = (*iter)->getDangerLevel();
		
		// Test basics before attempting a real calculation		
		if(testDanger + MOVE_COST[DIAG] * getDistanceBetween(_currBlock, *iter) <= currDanger){
			printf("\nTesting path to %i, %i", (*iter)->getCoordPath(X), (*iter)->getCoordPath(Y));
			calculateAction(MOVE, *iter);	
			if(_estimateTU != 0){
				testDanger += _estimateTU;
				if(getEffectiveTU() >= _estimateTU && testDanger <= currDanger){
					heap.push(new RangeNode((*iter)->getCoordPath(), testDanger, _estimateTU));
				}
			}
		}		
	}
	
	// Use the closest one
	BlockEst est(NULL, 0);
	if(!heap.isEmpty()){	
		LevelMap* levelMap = LevelMap::getInstance();
		RangeNode* rn = (RangeNode*)heap.pop();
		est.first = levelMap->getBlockByPath(rn->getCoord(X), rn->getCoord(Y));
		est.second = rn->getCost();
		delete rn;
	
		while(!heap.isEmpty()){
			rn = (RangeNode*)heap.pop();
			delete rn;
		}
	}
	
	return est;			
}

