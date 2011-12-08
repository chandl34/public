/*
 *  GridBlockIsoSorting.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"


void GridBlock::isoSort(list<Object*>& objList) const{	
	for(GLshort i = 0; i < object.size(); i++)
		object[i]->isoSort(objList);
	if(door != NULL)
		door->isoSort(objList);
}
