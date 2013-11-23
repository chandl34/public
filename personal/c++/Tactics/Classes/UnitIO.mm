/*
 *  UnitIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "Unit.h"


//---- IO ----//	
void Unit::saveData(ofstream& file)
{
	file << "u ";// << _currBlock->getCoordIso(X) << " " << _currBlock->getCoordIso(Y) << " "; 
	Coord2d<GLshort> coord(-1, -1);
	if(_currBlock != NULL)
		coord = _currBlock->getCoordIso();
	file << coord[X] << " " << coord[Y] << " ";	
	file << getDir() << " " << getIndex() << " ";	
	file << getHP() << " " << getMaxHP() << " ";
	file << getTU() << " " << getMaxTU() << "\n";
	
	_inventory.saveData(file);
}
