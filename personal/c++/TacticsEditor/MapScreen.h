/*
 *  MapScreen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MAP_SCREEN_H_
#define MAP_SCREEN_H_

#include "Screen.h"

class LevelMap;


class MapScreen : public SaveableScreen{
public:
	MapScreen();
	~MapScreen();
	
	//---- IO ----//
	string getFolder();
	string getFilter();
	void save(const string&);
	void load(const string&);
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- CONTROLS ---//
	void keyDown(GLshort);
	void push(GLshort, const Coord2d<GLshort>&);				// Defined in MapScreenTouch.mm
	void move(GLshort, const Coord2d<GLshort>&);				// Defined in MapScreenTouch.mm
	bool release(GLshort, const Coord2d<GLshort>&);			// Defined in MapScreenTouch.mm
	
private:
	LevelMap* levelMap;
};

#endif
