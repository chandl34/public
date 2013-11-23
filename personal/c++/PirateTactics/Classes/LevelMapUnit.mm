/*
 *  LevelMapUnit.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/8/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"


// Add unit to location
void LevelMap::addUnit(Unit* u, GLshort i, GLshort j){
	gridBlock[i][j]->setUnit(u);
	u->setBlock(gridBlock[i][j]);	
	if(u->getTeam() == GOOD)
		sUnit = u;			
	unit.push_back(u);
}

Unit* LevelMap::getSelectedUnit(){
	return sUnit;
}

void LevelMap::setUnitMode(GLshort m){
	unitMode = m;
}

void LevelMap::unitAction(){
	if(sUnit != NULL)
		sUnit->act(unitMode);
}

