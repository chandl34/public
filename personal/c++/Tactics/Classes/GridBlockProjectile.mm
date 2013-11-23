/*
 *  GridBlockProjectile.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DoorObject.h"
#include "Object.h"
#include "Unit.h"

void GridBlock::detectHit(const Ray& r, Hit& hit, bool ignoreObj, bool ignoreUnit) const
{	
	_ground->detectHit(r, hit);
	
	if(!ignoreObj){	
		for(ObjectList::const_iterator iter = _object.begin(); iter != _object.end(); ++iter)
			(*iter)->detectHit(r, hit);
		
		if(_door != NULL){
			if(_door->isInner() || !_door->isOpen())
				_door->detectHit(r, hit);
		}
	
		if(_visitingDoor != NULL)
			_visitingDoor->detectHit(r, hit);
	}
		
	if(_unit != NULL && !ignoreUnit)
		_unit->detectHit(r, hit);
}
