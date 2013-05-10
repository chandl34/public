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

#include "Movable.h"

#include "InfiniteItemContainer.h"
#include "Object.h"
#include "Vertex.h"

class DataLOS;
class DoorObject;
class GridBlock;
class Hit;
class Item;
class Ray;
class Unit;


typedef set<GridBlock*> BlockSet;
enum{WALLS_ONLY, DOORS_ONLY, WALLS_AND_DOORS};


class GridBlock : public Movable{
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
	
	//--- ACTION ---//
	bool update();
	
	//---- DRAW ----//	
	void draw(bool);
	void drawOverlays(bool);
	void drawItems(bool);
		
	//--- ISO SORTING ---//	
	void isoSort(ObjectList&, GLshort = SORT_ALL) const;
	
	//--- OBJECT ---//
	const Object* getGround() const;
	const ObjectList* getObjects() const;
	const DoorObject* getDoor() const;
	
	void addObject(Object*);
	void setDoor(DoorObject*);	
	void setGround(Object*);	
	
	bool hasDoor() const;
	
	void addOverlay(Image*);
	
	//-- PATHING --//
	bool isBlocked(GLshort, GLshort) const;
	void toggleDoor();
	
	//- PROJECTILE -//
	void detectHit(const Ray&, Hit&, bool, bool) const;	
	
	//---- SIGHT ----//	
	bool hasVisibleUnit(Unit*);
	GLshort viewBlocked(GLshort, GLshort) const;
	
	void addLOS(GLshort, GLshort);
	void removeLOS(GLshort, GLshort);
	GLshort getLOS(GLshort, GLshort);
	
	GLshort getDangerLevel();
	void clearLOS();
	
	//---- UNIT ----//	
	void setUnit(Unit*);
	Unit* getUnit() const;
	
	//--- INVENTORY ---//
	ItemContainerType* getContainer();	
	
	//---- IO ----//	
	void saveOtherData(ofstream&);
	void saveUnitData(ofstream&);
	
private:
	//--- GENERAL ---//
	Vertex _coord3D;
	Coord2d<GLshort> _coordIso;
	Coord2d<GLshort> _coordPath;
		
	//--- OBJECT ---//
	Object* _ground;
	ObjectList _object;
	DoorObject* _door;
	DoorObject* _visitingDoor;		
	list<Icon> _overlay;
	bool _doorUpdate;
	
	//---- SIGHT ----//	
	DataLOS* _losData;
	
	//---- UNIT ----//	
	Unit* _unit;
	
	//--- INVENTORY ---//
	InfiniteItemContainer _groundCont;
};


// Non-member functions
double getAngleBetween(GridBlock*, GridBlock*, GLshort);
GLshort getDirectionBetween(GridBlock*, GridBlock*);
double getDistanceBetween(GridBlock*, GridBlock*);

void findBlocksAlongRay(BlockSet&, Ray);
void find360Scope(BlockSet&, const GridBlock*, GLshort);
void findScope(BlockSet&, const GridBlock*, Dir, Size2d<GLshort>&, Size2d<GLshort>&, double);

GridBlock* getRandomBlock(bool);
GridBlock* getRandomBlockInRange(GridBlock*, GLshort);

#endif