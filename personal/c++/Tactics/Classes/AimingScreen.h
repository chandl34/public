/*
 *  AimingScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/23/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AIMING_SCREEN_H_
#define AIMING_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"


class AimingScreen : public SubScreen{
public:
	AimingScreen();
	
	//-- GENERAL --//
	void open();
	void close();
	
	//---- DRAW ----//
	void draw(bool);
	
	//---- TOUCH ----//
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);
	
private:
	//-- GENERAL --//
	GLshort aimAdd;
	GLshort target;
	GLshort bullets;
	
	//---- MENU ----//
	ComplexMenu _menu;
	enum{AIM_MENU, BULLETS_MENU, TARGET_MENU, CONFIRM_MENU};
};

#endif


