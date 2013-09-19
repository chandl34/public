/*
 *  Path.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 9/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef PATH_H_
#define PATH_H_

#include "Drawable.h"

#include "Icon.h"

class Directions;
class GridBlock;
class Unit;


class Path : public Drawable{
public:
	Path();
	~Path();
	
	//--- GENERAL ---//
	void find(Unit*, const GridBlock*, const GridBlock*, GLshort);
	
	bool isEmpty();
	GLshort getNextDirection();
	void clear();
	
	GLshort getCost();	
	
	//---- DRAW ----//	
	void draw(bool);
	
private:
	Directions* _directions;	
	list<pair<Icon, TU> > _footstep;	
	
	GLshort _cost;
};

#endif
