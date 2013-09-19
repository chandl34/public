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
//#include "ModelStorage.h"
//#include "ItemDataStorage.h"


const GLshort BASE_SCREENS = 1;
enum{TITLE_SCREEN};

const GLshort SUB_SCREENS = 0;


class MainScreen : public Screen{
public:
	MainScreen();
	~MainScreen();
	
	void tempInit();
	
	//---- GENERAL ----//
	static void setScreen(GLshort);
	static void setSubScreen(GLshort);
		
	//---- DRAW ----//
	void draw();
	
	//--- TOUCH ---//
	bool push(GLshort, const Coord2d<GLshort>&);
	bool move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	//---- GENERAL ----//
	ImageStorage _imageStorage;
	
	static BaseScreen* _screen[BASE_SCREENS];
	static BaseScreen* _currentScreen;
		
	static SubScreen* _subScreen[SUB_SCREENS];
	static SubScreen* _currentSubScreen;
	
	int _frames;
	GLuint _totalFrames;
	double _lastTime;
	double _timeElapsed;
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);	
};

#endif