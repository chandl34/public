/*
 *  GridBlock.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GRID_BLOCK_H_
#define GRID_BLOCK_H_

#include "Unit.h"
#include "DoorObject.h"


class GridBlock{
public:
	GridBlock(const Coord2d<GLshort>&);
	~GridBlock();
	
	//--- GENERAL ---//
	GLfloat getCoord3D(GLshort) const;
	GLshort getCoordIso(GLshort) const; 
	const Coord2d<GLshort>& getCoordIso() const;
	GLshort getCoordPath(GLshort) const;
	GLshort getOffset(GLshort) const;
		
	void select(bool);
				
	//---- DRAW ----//	
	void draw(bool);
		
	//--- ISO SORTING ---//	
	void isoSort(list<Object*>&) const;
	
	//--- OBJECT ---//
	void addObject(Object*);
	void setDoor(DoorObject*);	
	void setGround(Object*);	
	
	bool hasDoor() const;
	
	Object* getGround() const;
	DoorObject* getDoor() const;
	
	//-- PATHING --//
	bool hasVisibleUnit() const;
	bool isBlocked(GLshort) const;
	void toggleDoor();
	
	//- PROJECTILE -//
	Object* detectHit(const Ray&, GLfloat&, bool) const;
	
	//---- UNIT ----//	
	void setUnit(Unit*);
	Unit* getUnit() const;
	
private:
	//--- GENERAL ---//
	Vertex coord3D;
	Coord2d<GLshort> coordIso;
	Coord2d<GLshort> coordPath;
	bool selected;
		
	//--- OBJECT ---//
	Object* ground;
	vector<Object*> object;
	DoorObject* door;
	DoorObject* visitingDoor;		
		
	//---- UNIT ----//	
	Unit* unit;
};

#endif