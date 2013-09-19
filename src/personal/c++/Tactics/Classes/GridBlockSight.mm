/*
 *  GridBlockSight.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 9/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DataLOS.h"
#include "DoorObject.h"
#include "SideObject.h"
#include "Unit.h"

#include "LevelMap.h"


bool GridBlock::hasVisibleUnit(Unit* u)
{	
	if(_unit == NULL)
		return false;
	
	if(_unit->getFactionID() == u->getFactionID())
		return true;
	
	return _unit->hasBeenSeenBy(u);
}

GLshort GridBlock::viewBlocked(GLshort side, GLshort test) const
{
	if(test != WALLS_ONLY){
		// Check for doors
		if(side == LEFT_SIDE){
			if(_door != NULL && (_door->isInner() || !_door->isOpen()) && _door->blocks(DOWN_LEFT))
				return NO_LOS;
			if(_visitingDoor != NULL && _visitingDoor->blocks(DOWN_LEFT))
				return NO_LOS;
		}	
		else{
			if(_door != NULL && (_door->isInner() || !_door->isOpen()) && _door->blocks(DOWN_RIGHT))
				return NO_LOS;
			if(_visitingDoor != NULL && _visitingDoor->blocks(DOWN_RIGHT))
				return NO_LOS;
		}
		
		// Check for complex visiting door cases
		GLshort c[2];
		for(GLshort i = 0; i < 2; ++i)
			c[i] = _coordPath[i];
		--c[side];
		
		LevelMap* levelMap = LevelMap::getInstance();
		GridBlock* gb = levelMap->getBlockByPath(c[X], c[Y]);
		if(gb != NULL){
			if(gb->_visitingDoor != NULL){
				if(side == LEFT_SIDE){
					if(gb->_visitingDoor->blocks(UP_RIGHT))
						return NO_LOS;
				}
				else{
					if(gb->_visitingDoor->blocks(UP_LEFT))
						return NO_LOS;			
				}
			}
		}
	}
	
	if(test != DOORS_ONLY){
		for(ObjectList::const_iterator iter = _object.begin(); iter != _object.end(); ++iter){
			SideObject* so = (SideObject*)(*iter);
			if(so->getSide() == side){
				if(so->getObjType() == WALL)
					return NO_LOS;
				else if(so->getObjType() == BOTTOM_FRAME)
					return LOW_LOS;
			}
		}
	}
	
	return FULL_LOS;
}


void GridBlock::addLOS(GLshort v, GLshort los)
{
	if(_losData == NULL)
		_losData = new DataLOS();
	
	_losData->add(v, los);
}

void GridBlock::removeLOS(GLshort v, GLshort los)
{
	if(_losData != NULL)
		_losData->remove(v, los);
}

GLshort GridBlock::getLOS(GLshort v, GLshort los)
{
	if(_losData == NULL)
		return 0;
	return _losData->get(v, los);
}

void GridBlock::clearLOS()
{
	delete _losData;
	_losData = NULL;
}

GLshort GridBlock::getDangerLevel()
{
	GLshort danger = 0;
	for(GLshort i = 0; i < DANGER_LEVELS; ++i){
		danger += getLOS(VIEWED, i);
		danger += (DANGER_LEVEL[i] - 1) * getLOS(VIEWABLE, i);
	}
	return danger;
}
