/*
 *  LevelScreen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LEVEL_SCREEN_H_
#define LEVEL_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"
#include "EstimateDisplayLS.h"
#include "ItemDisplayLS.h"
#include "UnitDisplayLS.h"

class LevelMap;


class LevelScreen : public BaseScreen{
public:
	LevelScreen();
	~LevelScreen();
	
	//---- GENERAL ----//
	void setLevelMap(LevelMap*);
	
	//---- DRAW ----//
	void draw(bool);
	void drawOther(bool);
	
	//--- TOUCH ---//
	void push(GLshort, const Coord2d<GLshort>&);			
	void move(GLshort, const Coord2d<GLshort>&);			
	bool release(GLshort, const Coord2d<GLshort>&);				
	
private:
	//---- GENERAL ----//
	LevelMap* _levelMap;
	
	//---- MENU ----//
	ComplexMenu _menu;		
	enum{CURSOR_MODE_MENU, STATIC_MODE_MENU, 
		PREV_MENU, UNIT_MENU, NEXT_MENU, 
		MAP_MENU, OPTION_MENU};
	
	//---- DISPLAYS ----//
	EstimateDisplayLS _estimate;	
	ItemDisplayLS _itemInfo;	
	UnitDisplayLS _unitInfo;	
	
	//--- TOUCH ---//
	Touchable* _touched[2];
};

#endif
