/*
 *  GridBlockPathing.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DoorObject.h"
#include "Object.h"

#include "LevelMap.h"


//-- PATHING --//
bool GridBlock::isBlocked(GLshort dir, GLshort test) const{
	if(test != DOORS_ONLY){
		for(ObjectList::const_iterator iter = _object.begin(); iter != _object.end(); ++iter){
			if((*iter)->blocks(dir))
				return true;		
		}
	}
	
	if(test != WALLS_ONLY){
		if(_door != NULL){
			if(_door->isInner() || !_door->isOpen()){
				if(_door->blocks(dir))
					return true;	
			}
		}		
		
		if(_visitingDoor != NULL){
			if(_visitingDoor->blocks(dir))
				return true;
		}
	}
	
	return false;
}

void GridBlock::toggleDoor(){
	_doorUpdate = true;
	_door->toggleDoor();
	
	if(!_door->isInner()){		
		GridBlock* vgb;
		LevelMap* levelMap = LevelMap::getInstance();
		if(_door->getSide() == LEFT_SIDE)
			vgb = levelMap->getBlockByIso(_coordIso[X] + DIR[_coordIso[Y]%2][DOWN_LEFT][X],
													_coordIso[Y] + DIR[_coordIso[Y]%2][DOWN_LEFT][Y]);
		else
			vgb = levelMap->getBlockByIso(_coordIso[X] + DIR[_coordIso[Y]%2][DOWN_RIGHT][X],
													_coordIso[Y] + DIR[_coordIso[Y]%2][DOWN_RIGHT][Y]);	
		
		if(_door->isOpen())
			vgb->_visitingDoor = _door;
		else
			vgb->_visitingDoor = NULL;
	}
}
