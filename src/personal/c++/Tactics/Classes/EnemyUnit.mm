/*
 *  EnemyUnit.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "EnemyUnit.h"

#include "ImageStorage.h"
#include "ModelStorage.h"


EnemyUnit::EnemyUnit(const ObjType& ot, const Dir& d, GLshort is, 
					 const HP& mhp, const TU& mtu) 
: Unit(ot, d, is, mhp, mtu)
{
	//--- AI ---//
	_stage = 0;
}


//--- TURN ---//
void EnemyUnit::newTurn()
{
	Unit::newTurn();
	_stage = 0;
}
