/*
 *  InfoScreen.h
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INFO_SCREEN_H_
#define INFO_SCREEN_H_

#include "Screen.h"

class InfoScreen : public BaseScreen{
public:
	InfoScreen();
	~InfoScreen();
	
	//---- GENERAL ----//
	static void setScreen(GLshort);
	
	//---- DRAW ----//
	void draw();
	
	//--- CONTROLS ---//
	void keyDown(GLshort);
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	//---- GENERAL ----//
	// Screens
	static BaseScreen* currentScreen;
	static vector<BaseScreen*> screen;
	
	//---- DRAW ----//
	void draw(bool);	
};

#endif