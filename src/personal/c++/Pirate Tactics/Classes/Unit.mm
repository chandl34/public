/*
 *  Unit.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"
#include "GridBlock.h"
#include "Camera.h"
#include "ModelContainer.h"


Unit* Unit::create(const ObjType& ot, const Dir& d, GLshort is, 
				   const Team& te, const HP& mhp, const TU& mtu){
	Unit* u = new Unit(ot, d, is, te, mhp, mtu);	
	u->image = ModelContainer::getRotateImage(ot, d, is);
	u->model = ModelContainer::getRotateModel(ot, d);
		
	return u;
}

Unit::Unit(const ObjType& ot, const Dir& d, GLshort is, 
		   const Team& te, const HP& mhp, const TU& mtu) : RotateObject(ot, d, is, mhp), 
														   team(te), maxTU(mtu), currTU(mtu){	
	//-- GENERAL --//
	currBlock = NULL;
	goalBlock = NULL;
	state = IDLE;
	looking = false;
			
	//-- PATHING --//
	directions = NULL;
	stepsLeft = 0;
		
	//--- SIGHT ---//
	beenSeen = false;
}

Unit::~Unit(){
	
}


//-- GENERAL --//
GridBlock* Unit::getBlock() const{
	return currBlock;
}

void Unit::setBlock(GridBlock* gb){	
	currBlock = gb;
	setCoord3D(gb->getCoord3D(X), gb->getCoord3D(Y), gb->getCoord3D(Z));
}

bool Unit::isUnit(){
	return true;
}

const Team& Unit::getTeam() const{
	return team;
}
