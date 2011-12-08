/*
 *  GridBlockPathing.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"
#include "LevelMap.h"


bool GridBlock::hasVisibleUnit() const{	
	return unit != NULL && unit->hasBeenSeen();
}

bool GridBlock::isBlocked(GLshort dir) const{
	for(GLshort i = 0; i < object.size(); i++){
		if(object[i]->blocks(dir))
			return true;		
	}
	
	if(door != NULL && (door->isInner() || !door->isOpen())){
		if(door->blocks(dir))
			return true;		
	}		
	
	if(visitingDoor != NULL){
		if(visitingDoor->blocks(dir))
			return true;
	}
	
	return false;
}

void GridBlock::toggleDoor(){
	door->toggleDoor();
		
	if(!door->isInner()){		
		GridBlock* vgb;
		if(door->getSide() == LEFT_SIDE)
			vgb = LevelMap::getBlockByIso(coordIso[X] + DIR[coordIso[Y]%2][DOWN_LEFT][X],
										  coordIso[Y] + DIR[coordIso[Y]%2][DOWN_LEFT][Y]);
		else
			vgb = LevelMap::getBlockByIso(coordIso[X] + DIR[coordIso[Y]%2][DOWN_RIGHT][X],
										  coordIso[Y] + DIR[coordIso[Y]%2][DOWN_RIGHT][Y]);	
		
		if(door->isOpen())
			vgb->visitingDoor = door;
		else
			vgb->visitingDoor = NULL;
	}
}
