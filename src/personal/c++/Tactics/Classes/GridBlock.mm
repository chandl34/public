/*
 *  GridBlock.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DataLOS.h"
#include "DoorObject.h"
#include "Object.h"
#include "Vector.h"

#include "LevelMap.h"
#include "Math.h"


GridBlock::GridBlock(const Coord2d<GLshort>& iso)
: _coordIso(iso)
{	
	//--- GENERAL ---//
	_coordPath[X] = _coordIso[X] + _coordIso[Y]/2 + _coordIso[Y]%2;
	_coordPath[Y] = -_coordIso[X] + _coordIso[Y]/2 + MAP_SIDE;
	
	_coord3D.setLoc(_coordPath[X] * BLOCK_SIZE_3D[X],
						 _coordPath[Y] * BLOCK_SIZE_3D[X],
						 0);
	
	_offset[X] = BLOCK_SIZE_ISO[MAX_ZOOM][X] * (_coordIso[X] + (_coordIso[Y] % 2 - 1) / 2.0);
	_offset[Y] = BLOCK_SIZE_ISO[MAX_ZOOM][Y] * (_coordIso[Y] - 1) / 2.0;	
		
	//--- OBJECT ---//
	_ground = NULL;	
	_door = NULL;
	_visitingDoor = NULL;
	_doorUpdate = false;
	
	//---- SIGHT ----//	
	_losData = NULL;
	
	//---- UNIT ----//	
	_unit = NULL;
}

GridBlock::~GridBlock()
{		
	//--- OBJECT ---//
	if(_ground != NULL)
		delete _ground;	
	
	for(ObjectList::iterator iter = _object.begin(); iter != _object.end(); ++iter)
		delete *iter;
	
	if(_door != NULL)
		delete _door;
	
	delete _losData;
}


//--- GENERAL ---//
double GridBlock::getCoord3D(GLshort c) const
{
	return _coord3D.getLoc(c);
}

const Vertex& GridBlock::getCoord3D() const
{
	return _coord3D;
}

GLshort GridBlock::getCoordIso(GLshort c) const
{
	return _coordIso[c];
}

const Coord2d<GLshort>& GridBlock::getCoordIso() const
{
	return _coordIso;
}

GLshort GridBlock::getCoordPath(GLshort c) const
{
	return _coordPath[c];
}

const Coord2d<GLshort>& GridBlock::getCoordPath() const
{
	return _coordPath;
}


// Non-member functions
double getAngleBetween(GridBlock* t, GridBlock* o, GLshort dir)
{
	double x = t->getCoordPath(X) - o->getCoordPath(X);
	double y = t->getCoordPath(Y) - o->getCoordPath(Y);
	double size = sqrt(x*x + y*y);
	
	Vector v1(x/size, y/size, 0);		// could change this later to be more efficient...
	
	return arccos(v1.dot(UNIT_VECTOR[dir][X], UNIT_VECTOR[dir][Y], UNIT_VECTOR[dir][Z]));
}

GLshort getDirectionBetween(GridBlock* t, GridBlock* o)
{
	// RIGHT is chosen arbitrarily.  Could use any dir.
	GLshort dir = (GLshort)(getAngleBetween(t, o, RIGHT)/M_PI_4 + 0.5 + RIGHT)%PATH_DIRS;	// First round finds the angle
	if((GLshort)(getAngleBetween(t, o, dir)/M_PI_4 + 0.5 + dir)%PATH_DIRS != dir)			// Second round sees if angle was CCW
		dir = (dir + PATH_DIRS - 2*(dir - RIGHT))%PATH_DIRS;
	return dir;
}

double getDistanceBetween(GridBlock* t, GridBlock* o)
{
	double x = t->getCoordPath(X) - o->getCoordPath(X);
	double y = t->getCoordPath(Y) - o->getCoordPath(Y);
	return sqrt(x*x + y*y);
}


void findBlocksAlongRay(BlockSet& gb, Ray ray)
{
	GridBlock* ogb = NULL;
	GridBlock* cgb;
	double mod = 2.0;			// gives a slight optimization... todo:  make sure this doesn't cause any errors at any location
	GLshort rt = ray.size() / mod;
	ray.normalize();
	ray.setDir(ray.getDir(X) * mod,
				  ray.getDir(Y) * mod,
				  ray.getDir(Z) * mod);
	
	LevelMap* levelMap = LevelMap::getInstance();
	for(GLshort ct = 0.0; ct < rt; ++ct){
		cgb = levelMap->getBlockBy3D(ray.getLoc(X), ray.getLoc(Y));
		if(cgb != ogb){
			if(cgb == NULL)
				return;
			ogb = cgb;
			gb.insert(ogb);
		}
		ray.step();
	}
}

void find360Scope(BlockSet& bs, const GridBlock* orig, GLshort range)
{
	Size2d<GLshort> rng(range, range);
	Size2d<GLshort> incr(36, 36);
	double angle = M_PI / 36;			// 5 degrees * 36 == 180 degrees in each direction == full view scope		
	
	findScope(bs, orig, Dir(0), rng, incr, angle);
}

void findScope(BlockSet& bs, const GridBlock* orig, Dir dir, 
					Size2d<GLshort>& rng, Size2d<GLshort>& incr, double angle)
{
	// prevent divide by 0
	if(incr[FRONTAL] == 0)
		incr[FRONTAL] = incr[PERIPHERAL];
	++incr[FRONTAL]; 
	
	Vertex edgeCoord;
	Vertex baseCoord(orig->getCoord3D(X) + BLOCK_SIZE_3D[X]/2,
						  orig->getCoord3D(Y) + BLOCK_SIZE_3D[Y]/2,
						  0);
	
	GLshort range[2][2];
	
	for(GLshort i = 0; i < 2; ++i){
		for(GLshort j = 0; j < 2; ++j)
			range[i][j] = rng[i] * BLOCK_SIZE_3D[j];	
	}
	
	edgeCoord.setLoc(baseCoord.getLoc(X) + range[FRONTAL][X] * cos(DIR_ANGLE[dir]), 
						  baseCoord.getLoc(Y) + range[FRONTAL][Y] * sin(DIR_ANGLE[dir]), 
						  0);
	findBlocksAlongRay(bs, Ray(edgeCoord, baseCoord));
	
	for(GLshort i = 1; i <= incr[PERIPHERAL]; ++i){		
		edgeCoord.setLoc(baseCoord.getLoc(X) + range[i / incr[FRONTAL]][X] * cos(DIR_ANGLE[dir] + angle * i), 
							  baseCoord.getLoc(Y) + range[i / incr[FRONTAL]][Y] * sin(DIR_ANGLE[dir] + angle * i), 
							  0);
		findBlocksAlongRay(bs, Ray(edgeCoord, baseCoord));
		
		edgeCoord.setLoc(baseCoord.getLoc(X) + range[i / incr[FRONTAL]][X] * cos(DIR_ANGLE[dir] - angle * i), 
							  baseCoord.getLoc(Y) + range[i / incr[FRONTAL]][Y] * sin(DIR_ANGLE[dir] - angle * i), 
							  0);
		findBlocksAlongRay(bs, Ray(edgeCoord, baseCoord));
	}
}


GridBlock* getRandomBlock(bool empty)
{
	LevelMap* levelMap = LevelMap::getInstance();
	GridBlock* gb;
	Coord2d<GLshort> loc;
	while(true){		// Note: there should always be a location.  This should be safe.
		loc[X] = random(MAP_BLOCK[X]);
		loc[Y] = random(MAP_BLOCK[Y]);
		gb = levelMap->getBlockByIso(loc[X], loc[Y]);
		if(!empty || (gb->getUnit() == NULL && !gb->isBlocked(ALL_DIR, WALLS_ONLY)))
			return gb;
	}
	return NULL;
}

GridBlock* getRandomBlockInRange(GridBlock* gb, GLshort maxRange)
{
	BlockSet bs;	
	find360Scope(bs, gb, maxRange);
	
	GLshort end = random(bs.size());
	BlockSet::iterator iter = bs.begin();
	for(GLshort i = 0; i < end; ++i)
		++iter;
 	
	return *iter;
}
