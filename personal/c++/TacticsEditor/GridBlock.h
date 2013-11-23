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

#include "GridBlockOverlay.h"
#include "Object.h"
#include "Vertex.h"

class DoorObject;
class Ray;


typedef set<GridBlock*> BlockSet;
enum{WALLS_ONLY, DOORS_ONLY, WALLS_AND_DOORS};


class GridBlock{
public:
	GridBlock(const Coord2d<GLshort>&);
	~GridBlock();
	
	//--- GENERAL ---//
	double getCoord3D(GLshort) const;
	const Vertex& getCoord3D() const;
	GLshort getCoordIso(GLshort) const; 
	const Coord2d<GLshort>& getCoordIso() const;
	GLshort getCoordPath(GLshort) const;
	const Coord2d<GLshort>& getCoordPath() const;
	GLshort getOffset(GLshort) const;
		
	void select(bool);
	
	//---- DRAW ----//	
	void draw(bool);
		
	//--- ISO SORTING ---//	
	void isoSort(ObjectList&, GLshort = SORT_ALL) const;
	
	//--- OBJECT ---//
	void addObject(Object*);
	void setDoor(DoorObject*);	
	void setGround(Object*);	
	
	void clearAll();
	void clearSide(GLshort);
	
	const Object* getGround() const;
	const ObjectList* getObjects() const;
	const DoorObject* getDoor() const;
	
	//-- PATHING --//
	bool isBlocked(GLshort, GLshort) const;
	void toggleDoor();
	
private:
	//--- GENERAL ---//
	Vertex coord3D;
	Coord2d<double> offset;
	Coord2d<GLshort> coordIso;
	Coord2d<GLshort> coordPath;
	bool selected;
		
	//--- OBJECT ---//
	Object* ground;
	ObjectList object;
	DoorObject* door;
	DoorObject* visitingDoor;		
	list<GridBlockOverlay> overlay;
};

#endif