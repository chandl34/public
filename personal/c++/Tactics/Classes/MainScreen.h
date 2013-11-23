/*
 *  MainScreen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MAIN_SCREEN_H_
#define MAIN_SCREEN_H_

#include "Screen.h"

#include "ImageStorage.h"
#include "ModelStorage.h"
#include "ItemDataStorage.h"

class Team;


const GLshort BASE_SCREENS = 3;
enum{TITLE_SCREEN, CAMPAIGN_SCREEN, LEVEL_SCREEN};

const GLshort SUB_SCREENS = 8;
enum{MENU_SCREEN, LOAD_SCREEN, SAVE_SCREEN, OPTIONS_SCREEN,
	 TEAM_SCREEN,
	 AIMING_SCREEN, INVENTORY_SCREEN, MINI_MAP_SCREEN};


class MainScreen : public BaseScreen{
public:
	MainScreen();
	~MainScreen();
	
	void tempInit();
	
	//---- GENERAL ----//
	static void setScreen(GLshort);
	static void setSubScreen(GLshort);
		
	//---- IO ----//
	static void saveData(GLshort);
	static void loadData(GLshort);
	
	static void newGame();
	static void newBattle(const string&, Team*, Team*);
	
	//---- DRAW ----//
	void draw();
	
	//--- TOUCH ---//
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	//---- GENERAL ----//
	ImageStorage _imageStorage;
	ModelStorage _modelStorage;
	ItemDataStorage _itemDataStorage;
	
	static BaseScreen* _screen[BASE_SCREENS];
	static BaseScreen* _currentScreen;
		
	static SubScreen* _subScreen[SUB_SCREENS];
	static SubScreen* _currentSubScreen;
	
	int _frames;
	GLuint _totalFrames;
	double _lastTime;
	double _timeElapsed;
	
	//---- IO ----//
	static string _save[8];
	
	//---- DRAW ----//
	void draw(bool);	
};

#endif