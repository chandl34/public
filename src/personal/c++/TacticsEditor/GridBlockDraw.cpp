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
#include "ImageStorage.h"


void GridBlock::draw(bool step){   	
	ground->draw(step);
}


//--- ISO SORTING ---//	
void GridBlock::isoSort(ObjectList& objList, GLshort sortRule) const{	
	if(sortRule != SORT_DYNAMIC){
		for(ObjectList::const_iterator iter = object.begin(); iter != object.end(); ++iter)
			(*iter)->isoSort(objList);
	}
	
	if(sortRule != SORT_STATIC){
		if(door != NULL){
			if(door->isInner() || !door->isOpen())
				door->isoSort(objList);
		}
		
		if(visitingDoor != NULL)
			visitingDoor->isoSort(objList);
	}
}
