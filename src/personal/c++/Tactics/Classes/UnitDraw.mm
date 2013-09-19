/*
 *  UnitDraw.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "ImageSet.h"
#include "LevelMap.h"


void Unit::draw(bool step, TexAttr* ta)
{
	// Update image
	if(step && _currAnim == MOVE_ANIM)
		_image = _animSet.getNextImage();	
	
	// TEMPORARY todo: remove
	if(getFactionID() != PLAYER && !hasBeenSeen()){
		glColor4f(0.0, 0.0, 1.0, 1.0);				// Gray out if out of range
		RotateObject::draw(step, ta);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
	
	LevelMap* levelMap = LevelMap::getInstance();
	Unit* sUnit = levelMap->getSelectedUnit();
	if(getFactionID() == PLAYER || hasBeenSeen()){
		if(getFactionID() != PLAYER && sUnit != NULL && !_seenBy.count(sUnit))
			glColor4f(0.5, 0.5, 0.5, 1.0);				// Gray out if out of range
		else if(sUnit == this)
			glColor4f(0.8, 1.0, 1.0, 1.0);
	/*	
		// todo: remove these two.  only for testing, so I always know what enemies are thinking
		if(_teamID == PLAYER){
			if(_seenBy.empty()){
				if(hasBeenSeen())
					glColor4f(1.0, 0.0, 0.0, 1.0);	// Red = known
				else
					glColor4f(0.0, 1.0, 0.0, 1.0);	// Green = unknown
			}
		}
	*/
		RotateObject::draw(step, ta);
		
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
}

void Unit::drawInventory(bool step)
{
	_inventory.draw(step);
}

void Unit::drawPath(bool step)
{
	_path.draw(step);
}

void Unit::drawView(bool step)
{
	_view->draw(step);
}

void Unit::drawIcon(bool step)
{
	_uiIcon.draw(step);
}
