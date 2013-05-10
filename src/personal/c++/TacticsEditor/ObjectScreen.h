/*
 *  ObjectScreen.h
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_SCREEN_H_
#define OBJECT_SCREEN_H_

#include "Screen.h"

#include "Object.h"


class ObjectScreen : public BaseScreen{
public:
	ObjectScreen();
	~ObjectScreen();
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- CONTROLS ---//
	void keyDown(GLshort);
	void push(GLshort, const Coord2d<GLshort>&);				// Defined in MapScreenTouch.mm
	void move(GLshort, const Coord2d<GLshort>&);				// Defined in MapScreenTouch.mm
	bool release(GLshort, const Coord2d<GLshort>&);			// Defined in MapScreenTouch.mm
	
private:
	//---- GENERAL ----//
	ObjectList objList[OBJECT_OPTIONS];
	GLshort objIndex[OBJECT_OPTIONS];
	
	GLshort objSide;
	GLshort objInner;
	GLshort objHinge;
	GLshort objOpen;
	GLshort sObjectType;
	
	//---- DRAW ----//
	bool resort;
};

#endif

