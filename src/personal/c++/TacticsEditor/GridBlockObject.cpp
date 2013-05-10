/*
 *  GridBlockObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DoorObject.h"
#include "Object.h"

#include "LevelMap.h"


//--- OBJECT ---//
void GridBlock::clearAll()
{
	for(ObjectList::iterator iter = object.begin(); iter != object.end(); ++iter)
		delete *iter;
	object.clear();
	
	if(door != NULL){
		if(door->isOpen())
			toggleDoor();
		delete door;
		door = NULL;
	}
}

void GridBlock::clearSide(GLshort s)
{
	SideObject* so;
	for(ObjectList::iterator iter = object.begin(); iter != object.end(); ){
		if((*iter)->getModelType() == SIDE_MODEL){
			so = (SideObject*)(*iter);
			if(so->getSide() == s){
				delete *iter;
				iter = object.erase(iter);
				continue;
			}
		}
		++iter;
	}
	
	if(door != NULL && door->getSide() == s){
		if(door->isOpen())
			toggleDoor();
		delete door;
		door = NULL;
	}
}

void GridBlock::addObject(Object* o)
{
	o->setCoord3D(coord3D.getLoc(X), coord3D.getLoc(Y), coord3D.getLoc(Z));
	object.push_back(o);
}

void GridBlock::setDoor(DoorObject* d)
{
	d->setCoord3D(coord3D.getLoc(X), coord3D.getLoc(Y), coord3D.getLoc(Z));
	
	if(door != NULL){
		if(door->isOpen())
			toggleDoor();
		delete door;
	}
	
	door = d;
}

void GridBlock::setGround(Object* g)
{	
	g->setCoord3D(coord3D.getLoc(X), coord3D.getLoc(Y), coord3D.getLoc(Z));
	
	if(ground != NULL)
		delete ground;
	
	ground = g;
}


const Object* GridBlock::getGround() const
{
	return ground;
}

const ObjectList* GridBlock::getObjects() const
{
	return &object;
}

const DoorObject* GridBlock::getDoor() const
{
	return door;
}

void GridBlock::toggleDoor()
{
	door->toggleDoor();
	
	if(!door->isInner()){		
		GridBlock* vgb;
		if(door->getSide() == LEFT_SIDE)
			vgb = LevelMap::getBlockByIso(coordIso[X] + PATH_DIR[coordIso[Y]%2][DOWN_LEFT][X],
													coordIso[Y] + PATH_DIR[coordIso[Y]%2][DOWN_LEFT][Y]);
		else
			vgb = LevelMap::getBlockByIso(coordIso[X] + PATH_DIR[coordIso[Y]%2][DOWN_RIGHT][X],
													coordIso[Y] + PATH_DIR[coordIso[Y]%2][DOWN_RIGHT][Y]);	
		
		if(door->isOpen())
			vgb->visitingDoor = door;
		else
			vgb->visitingDoor = NULL;
	}
}
