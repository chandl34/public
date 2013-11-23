/*
 *  GridBlockInventory.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"


//--- INVENTORY ---//
ItemContainerType* GridBlock::getContainer(){
	return &_groundCont;
}
