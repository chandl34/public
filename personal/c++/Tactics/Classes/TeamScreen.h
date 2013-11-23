/*
 *  TeamScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 1/7/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TEAM_SCREEN_H_
#define TEAM_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"
#include "Icon.h"

class Team;
class Unit;


class TeamScreen : public SubScreen{
public:
	TeamScreen();
	
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
	Icon _statsBackground;
	
	//---- MENU ----//
	ComplexMenu _menu;
	enum{S_TEAM, S_TEAM_SCROLL, SWAP, O_TEAM, O_TEAM_SCROLL};
	
	//enum{AIM_MENU, BULLETS_MENU, TARGET_MENU, CONFIRM_MENU};
	
	//---- TEAM ----//
	Team* _team[2];
	GLshort _sTeam;
	Unit* _sUnit;
};

#endif



