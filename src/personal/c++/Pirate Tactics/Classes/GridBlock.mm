/*
 *  GridBlock.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"

GridBlock::GridBlock(const Coord2d<GLshort>& iso) : coordIso(iso){	
	//--- GENERAL ---//
	coordPath[X] = coordIso[X] + coordIso[Y]/2 + coordIso[Y]%2;
	coordPath[Y] = -coordIso[X] + coordIso[Y]/2 + MAP_SIDE;
	
	coord3D.setLoc(coordPath[X]*BLOCK_SIZE_3D[X],
				   coordPath[Y]*BLOCK_SIZE_3D[X],
				   0);
	
	selected = false;
		
	//--- OBJECT ---//
	ground = NULL;	
	door = NULL;
	visitingDoor = NULL;
	 	
	//---- UNIT ----//	
	unit = NULL;
}

GridBlock::~GridBlock(){		
	//--- OBJECT ---//
	if(ground != NULL)
		delete ground;	
	
	for(GLshort i = 0; i < object.size(); i++)
		delete object[i];
	
	if(door != NULL)
		delete door;
}


GLfloat GridBlock::getCoord3D(GLshort c) const{
	return coord3D.getLoc(c);
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

GLshort GridBlock::getOffset(GLshort c) const{
	return ground->getOffset(c);
}


void GridBlock::select(bool s){
	selected = s;
}
