/*
 *  EnemyTeamIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "EnemyTeam.h"

#include "EnemyUnit.h"
#include "GridBlock.h"


//---- IO ----//	
void EnemyTeam::saveMemoryData(ofstream& file)
{
	// Make sure all memory data is up-to-date
	//EnemyUnit* eu = (EnemyUnit*)(*_unit.begin());
	EnemyUnit::findNewData(_known, _memory);
	
	Unit* u;
	GridBlock* gbReal;
	GridBlock* gbRem;
	for(MemoryMap::iterator iter = _memory.begin(); iter != _memory.end(); ++iter){
		u = iter->first;
		gbReal = u->getBlock();
		gbRem = iter->second.getBlock();
		file << "m " << gbReal->getCoordIso(X) << " " << gbReal->getCoordIso(Y) << " ";
		file << gbRem->getCoordIso(X) << " " << gbRem->getCoordIso(Y) << " ";
		file << iter->second.getTimer() << "\n";
	}
}
