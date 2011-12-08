/*
 *  GridBlockUnit.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"


void GridBlock::setUnit(Unit* u){
	unit = u;
}

Unit* GridBlock::getUnit() const{
	return unit;
}
