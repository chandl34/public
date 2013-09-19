/*
 *  Path.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 9/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Path.h"

#include "Directions.h"
#include "GridBlock.h"

#include "ImageStorage.h"
#include "LevelMap.h"
#include "Pathing.h"


Path::Path()
{
	_directions = NULL;
	_cost = 0;
}

Path::~Path()
{
	clear();
}


//--- GENERAL ---//
void Path::find(Unit* u, const GridBlock* curr, const GridBlock* goal, GLshort tu)
{	
	LevelMap* levelMap = LevelMap::getInstance();
	_directions = Pathing::getDirections(u, curr->getCoordIso(), goal->getCoordIso());
	
	if(_directions != NULL){
		_cost = tu;
		const list<GLshort>& dir = _directions->getList();
		for(list<GLshort>::const_iterator iter = dir.begin(); iter != dir.end(); ++iter){
			tu -= MOVE_COST[*iter % 2];
			_footstep.push_back(make_pair(Icon(ImageStorage::getFootstepImage(*iter), curr->getOffset()), tu));
			curr = levelMap->getBlockByIso(curr->getCoordIso(X) +  DIR[curr->getCoordIso(Y) % 2][*iter][X],
													 curr->getCoordIso(Y) +  DIR[curr->getCoordIso(Y) % 2][*iter][Y]);
		}
		_cost -= tu;
	}
}

bool Path::isEmpty()
{
	return _directions == NULL || _directions->isEmpty();
}

void Path::clear()
{
	if(_directions != NULL){
		delete _directions;
		_directions = NULL;
		_footstep.clear();
		_cost = 0;
	}
}

GLshort Path::getNextDirection()
{
	_footstep.pop_front();
	return _directions->getNext();
}

GLshort Path::getCost()
{
	return _cost;
}

//---- DRAW ----//	
void Path::draw(bool step)
{
	for(list<pair<Icon, TU> >::iterator iter = _footstep.begin(); iter != _footstep.end(); ++iter){
		if(iter->second < 0)							// Gray out if out of range
			glColor4f(0.5, 0.5, 0.5, 1.0);
		iter->first.draw(step);
	}
	glColor4f(1.0, 1.0, 1.0, 1.0);
}