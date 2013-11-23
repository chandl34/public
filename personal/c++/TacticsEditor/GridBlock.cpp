/*
 *  GridBlock.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

#include "DoorObject.h"
#include "Object.h"
#include "Vector.h"

#include "LevelMap.h"
#include "Math.h"


GridBlock::GridBlock(const Coord2d<GLshort>& iso) : coordIso(iso){	
	//--- GENERAL ---//
	coordPath[X] = coordIso[X] + coordIso[Y]/2 + coordIso[Y]%2;
	coordPath[Y] = -coordIso[X] + coordIso[Y]/2 + MAP_SIDE;
	
	coord3D.setLoc(coordPath[X] * BLOCK_SIZE_3D[X],
						coordPath[Y] * BLOCK_SIZE_3D[X],
						0);
	
	offset[X] = BLOCK_SIZE_ISO[MAX_ZOOM][X] * (coordIso[X] + (coordIso[Y] % 2 - 1) / 2.0);
	offset[Y] = BLOCK_SIZE_ISO[MAX_ZOOM][Y] * (coordIso[Y] - 1) / 2.0;	
	
	selected = false;
		
	//--- OBJECT ---//
	ground = NULL;
	door = NULL;
	visitingDoor = NULL;
}

GridBlock::~GridBlock(){		
	//--- OBJECT ---//
	if(ground != NULL)
		delete ground;	
	
	for(ObjectList::iterator iter = object.begin(); iter != object.end(); ++iter)
		delete *iter;
	
	if(door != NULL)
		delete door;
}


//--- GENERAL ---//
double GridBlock::getCoord3D(GLshort c) const{
	return coord3D.getLoc(c);
}

const Vertex& GridBlock::getCoord3D() const{
	return coord3D;
}

GLshort GridBlock::getCoordIso(GLshort c) const{
	return coordIso[c];
}

const Coord2d<GLshort>& GridBlock::getCoordIso() const{
	return coordIso;
}

GLshort GridBlock::getCoordPath(GLshort c) const{
	return coordPath[c];
}

const Coord2d<GLshort>& GridBlock::getCoordPath() const{
	return coordPath;
}

GLshort GridBlock::getOffset(GLshort c) const{
	return offset[c];
}

void GridBlock::select(bool s){
	selected = s;
}

