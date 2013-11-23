/*
 *  GridBlockIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DoorObject.h"
#include "Unit.h"


//---- IO ----//	
void GridBlock::saveOtherData(ofstream& file)
{
	if(_door != NULL){
		file << "d " << getCoordIso(X) << " " << getCoordIso(Y) << " ";
		file << _door->isOpen() << "\n";			
	}
	
	_groundCont.saveData(file, &getCoordIso());
}

void GridBlock::saveUnitData(ofstream& file)
{
	if(_unit != NULL){
		file << "u " << getCoordIso(X) << " " << getCoordIso(Y) << " ";
		file << _unit->isKneeling() << "\n";
	}
}

