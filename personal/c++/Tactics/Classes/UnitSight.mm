/*
 *  UnitSight.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "GridBlock.h"
#include "LevelMap.h"

#include "HitTest.h"
#include "Options.h"


bool Unit::hasBeenSeenBy(Unit* u) const
{
	if(u->getFactionID() == PLAYER)
		return hasBeenSeen();
	else
		return _beenSeenBy.count(u);
	
}

bool Unit::hasBeenSeen() const
{
	return !_beenSeenBy.empty();
}


bool Unit::canSee(Unit* u)
{
	return _view->canSee(u->getBlock());
}

bool Unit::canSee(GridBlock* gb)
{
	return _view->canSee(gb);
}

bool Unit::couldSee(GridBlock* gb)
{
	return _view->couldSee(gb);
}	

bool Unit::couldSee(Unit* u)
{
	return _view->couldSee(u->getBlock());
}

bool Unit::inViewScope(GridBlock* gb)
{
	return _view->inScope(gb);
}

void Unit::look(UnitList& enemyTeam)
{
	GLshort newDir = getDirectionBetween(_goalBlock, _currBlock);
	
	//printf("Looking\n");
	if(newDir != _dir){
		if(getEffectiveTU() >= LOOK_COST){
			if(!UNLIMITED_TU)
				_currTU -= LOOK_COST;
			setDir(newDir);
			updateSight(enemyTeam, INT_ON_NONE, TURNED);	
		}
	}
	
//	printf("same dir\n");
	// todo: COULD RAISE GUN HERE ... THIS WILL HAVE TO BE MOVED FROM THIS FUNCTION
}

// Child process
void Unit::setBackupView(View* v)
{
	_backupView = v;
	_threadActive = false;
}

void Unit::updateSight(UnitList& enemyTeam, GLshort interrupt, GLshort updateReason)
{
	if(_backupView != NULL){
		delete _view;
		_view = _backupView;
		_backupView = NULL;
	}
	else
		_view->findLOS(_currBlock, Dir(_dir), updateReason, _kneeling);	
	
	Unit* u;
	
	// Test others' sight (done first, so enemies can get interrupts chance)	
	for(UnitList::iterator iter = enemyTeam.begin(); iter != enemyTeam.end(); ++iter){
		u = *iter;
		if(u->canSee(this)){
			if(!u->_sees.count(this)){
				u->_sees.insert(this);
				_seenBy.insert(u);
				_beenSeenBy.insert(u);
				
				if(interrupt == INT_ON_NEW){
					; // todo: add interrupt chance
				}
			}				
			
			if(interrupt == INT_ON_ANY){
				; // todo: add interrupt chance
			}
		}
		else if(u->_sees.count(this)){
			u->_sees.erase(this);
			_seenBy.erase(u);			
			_beenSeenBy.erase(u);// makes enemies disappear immediately, if they go out of sight
			
			if(u->getFactionID() != PLAYER){
				if(!hasBeenSeen()){
					cout << "UNHANDLED A" << endl;
					_unhandled[this] = Memory(_currBlock);//.push_back(UnitBlock(this, _currBlock));
				}
			}
		}	
	}
		
	// Test this unit's sight
	for(UnitList::iterator iter = enemyTeam.begin(); iter != enemyTeam.end(); ++iter){		
		u = *iter;
		if(canSee(u)){				
			if(!_sees.count(u)){	
				// Stop, if unit hasn't been seen before
				if(!u->hasBeenSeenBy(this)){					
					if(getFactionID() != PLAYER){						
						if(!u->hasBeenSeen()){
							cout << "UNHANDLED B" << endl;
							_unhandled[u] = Memory(u->getBlock());//.push_back(UnitBlock(u, u->getBlock()));
						}
					}
					
					// Charge LOOK_COST if turned and found new unit while moving
					if(_state == MOVE && updateReason == TURNED){
						if(!UNLIMITED_TU)
							_currTU -= LOOK_COST;
					}
					
					printf("New unit spotted\n");
					stop();
				}
				
				_sees.insert(u);
				u->_seenBy.insert(this);	
				u->_beenSeenBy.insert(this);	
			}
		}
		else if(_sees.count(u)){
			_sees.erase(u);
			u->_seenBy.erase(this);
		}
	}	
}

void Unit::hideUnseen()
{
	if(getFactionID() == PLAYER){
		if(!_beenSeenBy.empty() && _seenBy.empty()){
			cout << "UNHANDLED C" << endl;
			_unhandled[this] = Memory(_currBlock);//.push_back(UnitBlock(this, _currBlock));
		}
	}	
	_beenSeenBy = _seenBy;
}


void Unit::addLOS()
{
	_view->addLOS();
}

void Unit::removeLOS()
{
	_view->removeLOS();
}

void Unit::removeDead(Unit* u)
{
	_sees.erase(u);
	_seenBy.erase(u);
	
	// Note:: this is a repeat of the hideUnseen code, but I want a different print _statement
	if(getFactionID() == PLAYER){
		if(!_beenSeenBy.empty() && _seenBy.empty()){
			cout << "UNHANDLED D" << endl;
			_unhandled[this] = Memory(_currBlock);//.push_back(UnitBlock(this, _currBlock));
		}		
	}
	_beenSeenBy.erase(u);
}


void Unit::findLOSThreaded()
{
	_threadActive = true;	
	
	ViewArgs va;
	va.unit = this;
	va.gb = _currBlock;
	va.dir = _dir;
	va.reason = MOVED;
	va.kneeling = _kneeling;
	
	LevelMap* levelMap = LevelMap::getInstance();
	levelMap->sendToBackground(va);
}


//---- AI ----//	
MemoryMap* Unit::getUnhandledMemories()
{
	return &_unhandled;
}
