/*
 *  CampaignScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CAMPAIGN_SCREEN_H_
#define CAMPAIGN_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"
#include "LevelDisplayCS.h"

class CampaignMap;


class CampaignScreen : public BaseScreen{
public:
	CampaignScreen();
	~CampaignScreen();
	
	//---- GENERAL ----//
	void setCampaignMap(CampaignMap*);
	
	//---- DRAW ----//
	void draw(bool);
	void drawOther(bool);
	
	//--- TOUCH ---//
	void push(GLshort, const Coord2d<GLshort>&);			
	void move(GLshort, const Coord2d<GLshort>&);			
	bool release(GLshort, const Coord2d<GLshort>&);				
	
private:
	//---- GENERAL ----//
	CampaignMap* _campaignMap;
	
	//---- MENU ----//
	ComplexMenu _menu;	
	enum{MODE_MENU, TEAM_MENU, 
		PREV_MENU, LEVEL_MENU, NEXT_MENU,
		DOMESTICS_MENU, OPTION_MENU};
	
	//---- DISPLAYS ----//
	LevelDisplayCS _levelInfo;	
	
	//--- TOUCH ---//
	Touchable* _touched[2];
};

#endif

