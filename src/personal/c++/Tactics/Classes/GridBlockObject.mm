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
#include "Unit.h"


//--- OBJECT ---//
const Object* GridBlock::getGround() const
{
	return _ground;
}

const ObjectList* GridBlock::getObjects() const
{
	return &_object;
}

const DoorObject* GridBlock::getDoor() const
{
	return _door;
}

void GridBlock::addObject(Object* o)
{
	o->setCoord3D(_coord3D.getLoc(X), _coord3D.getLoc(Y), _coord3D.getLoc(Z));
	_object.push_back(o);
}


bool GridBlock::hasDoor() const
{	
	return _door != NULL;
}

void GridBlock::setDoor(DoorObject* d)
{
	d->setCoord3D(_coord3D.getLoc(X), _coord3D.getLoc(Y), _coord3D.getLoc(Z));
	_door = d;
}

void GridBlock::setGround(Object* g)
{	
	g->setCoord3D(_coord3D.getLoc(X), _coord3D.getLoc(Y), _coord3D.getLoc(Z));
	_ground = g;
}


void GridBlock::addOverlay(Image* img)
{
	_overlay.push_back(Icon(img, getOffset()));
}


//--- ACTION ---//
bool GridBlock::update()
{	
	GLshort ret = false; // todo: fix this so a signal is sent back.  I don't want to test every gridblock every turn
	/*
	 GLshort action;
	for(ObjectList::iterator iter = object.begin(); iter != object.end();){
		action = (*iter)->update();
		if(action == DIED){
			ret = true;
			delete *iter;
			iter = object.erase(iter);
		}
		else
			++iter;
	}
	if(door != NULL){
		action = door->update();
		if(action == DIED){
			ret = true;	
			// Toggle door first so there aren't problems with visiting doors not being set
			if(!door->isInner() && door->isOpen()) 
				toggleDoor();
			delete door;
			door = NULL;
		}
	}
	 */
	if(_doorUpdate){
		ret = true;
		_doorUpdate = false;
	}
	
	return ret;
}


//---- UNIT ----//	
void GridBlock::setUnit(Unit* u)
{
	_unit = u;
}

Unit* GridBlock::getUnit() const
{
	return _unit;
}
