/*
 *  GridBlockObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"


bool GridBlock::hasDoor() const{	
	return door != NULL;
}

void GridBlock::addObject(Object* o){
	o->setCoord3D(coord3D.getLoc(X), coord3D.getLoc(Y), coord3D.getLoc(Z));
	object.push_back(o);
}


void GridBlock::setDoor(DoorObject* d){
	d->setCoord3D(coord3D.getLoc(X), coord3D.getLoc(Y), coord3D.getLoc(Z));
	door = d;
}

void GridBlock::setGround(Object* g){	
	g->setCoord3D(coord3D.getLoc(X), coord3D.getLoc(Y), coord3D.getLoc(Z));
	ground = g;
}


Object* GridBlock::getGround() const{
	return ground;
}

DoorObject* GridBlock::getDoor() const{
	return door;
}