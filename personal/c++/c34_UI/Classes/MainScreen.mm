/*
 *  MainScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainScreen.h"

#include "TitleScreen.h"

#include "Options.h"


BaseScreen* MainScreen::_screen[BASE_SCREENS];
BaseScreen* MainScreen::_currentScreen;

SubScreen* MainScreen::_subScreen[SUB_SCREENS];
SubScreen* MainScreen::_currentSubScreen;



MainScreen::MainScreen()
: Screen(true)
{
	// Setup random number generator
	srand([[NSDate date] timeIntervalSince1970]);
	
	// OpenGL
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glClearColor(1.0, 0.0, 0.0, 0.0);	
	
	glEnable(GL_TEXTURE_2D);		
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	
	// this is initializing containers... todo: make a cleaner way to do this
	tempInit();
	
	
	printf("\n//--- BUILDING SCREENS ---//\n");
	// Create screens
	_screen[TITLE_SCREEN] = new TitleScreen();
	_currentScreen = _screen[TITLE_SCREEN];
	
	// Create subScreens
	_currentSubScreen = NULL;
	
	// FPS
	_frames = 0;
	_totalFrames = 0;
	_lastTime = 0;
	_timeElapsed = 0;
}

MainScreen::~MainScreen()
{
	for(GLshort i = 0; i < BASE_SCREENS; ++i)
		delete _screen[i];
	
	for(GLshort i = 0; i < SUB_SCREENS; ++i)
		delete _subScreen[i];
}


//---- GENERAL ----//
void MainScreen::setScreen(GLshort i)
{
	_currentScreen = _screen[i];
}

void MainScreen::setSubScreen(GLshort i)
{
	_currentSubScreen = _subScreen[i];
	_currentSubScreen->open();
}


//---- DRAW ----//
void MainScreen::draw(bool step, TexAttr* ta)
{
	resetView();
	if(_currentSubScreen != NULL)
		_currentSubScreen->draw(step, ta);
	else
		_currentScreen->draw(step, ta);
	_currentScreen->drawOther(step, ta);
}

void MainScreen::draw()
{
//	glClear(GL_COLOR_BUFFER_BIT);	// not needed? - fps improvement is microscopic by removing it
	
//	double timer = [[NSDate date] timeIntervalSince1970];
	
	++_totalFrames;

	//----- SHOW FPS -----//
	if(SHOW_FPS){
		double time = [[NSDate date] timeIntervalSince1970];
		_timeElapsed += time - _lastTime;
		_lastTime = time;		
		++_frames;
		
		if(_timeElapsed > 2){		
			printf("FPS: %.1f\n", _frames/_timeElapsed);		
			_frames = 0;
			_timeElapsed = 0;
		}
	}
	
	//----- DRAW SCREEN -----//
	draw(_totalFrames % 5  == 0);
	
//	timer = [[NSDate date] timeIntervalSince1970] - timer;
//	printf("Frame took %f seconds\n", timer);
}


//--- TOUCH ---//
bool MainScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	if(_currentSubScreen != NULL){
		if(_currentSubScreen->isTouching(p))
			_currentSubScreen->push(t, p);
		else{
			//currentSubScreen->close();
			_currentSubScreen = NULL;
		}
	}
	else
		_currentScreen->push(t, p);
	
	return true;
}

bool MainScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	if(_currentSubScreen != NULL)
		_currentSubScreen->move(t, p);
	else
		_currentScreen->move(t, p);
	
	return true;
}

bool MainScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(_currentSubScreen != NULL){
		if(_currentSubScreen->release(t, p)){
			//currentSubScreen->close();
			_currentSubScreen = NULL;
		}
	}
	else
		_currentScreen->release(t, p);
	
	return true;
}	
