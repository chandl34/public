/*
 *  GridBlockDraw.mm
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

#include "ImageStorage.h"


void GridBlock::draw(bool step){   	
	_ground->draw(step);
}

void GridBlock::drawOverlays(bool step){
	glColor4f(1.0, 0.0, 0.0, 1.0);	
	
	// todo:  remove this later.  it is a temporary fix to no image for ground
	if(!_groundCont.isEmpty())
		addOverlay(ImageStorage::getConstImage(ObjType(GROUND), 0));
	
	
	for(list<Icon>::iterator iter = _overlay.begin(); iter != _overlay.end(); ++iter)
		iter->draw(step);
	
	// todo:  remove this later.  it is a temporary fix to no image for ground
	if(!_groundCont.isEmpty())
		_overlay.pop_back();
		
	
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void GridBlock::drawItems(bool step){
	_groundCont.draw(step);
}


//--- ISO SORTING ---//	
void GridBlock::isoSort(ObjectList& objList, GLshort sortRule) const{	
	if(sortRule != SORT_DYNAMIC){
		for(ObjectList::const_iterator iter = _object.begin(); iter != _object.end(); ++iter)
			(*iter)->isoSort(objList);
	}
	
	if(sortRule != SORT_STATIC){
		if(_door != NULL){
			if(_door->isInner() || !_door->isOpen())
				_door->isoSort(objList);
		}
		
		if(_visitingDoor != NULL)
			_visitingDoor->isoSort(objList);
		
		if(_unit != NULL)
			_unit->isoSort(objList);
	}
}
