/*
 *  LevelMapIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "LevelMap.h"

#include "EnemyTeam.h"


//---- IO ----//	
void LevelMap::saveData(ofstream& file)
{
	_camera.saveData(file);
	
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			_gridBlock[i][j]->saveOtherData(file);
	}
	
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			_gridBlock[i][j]->saveUnitData(file);
	}
	
	EnemyTeam* eTeam = (EnemyTeam*)_team[ENEMY];
	eTeam->saveMemoryData(file);
}
