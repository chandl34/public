/*
 *  InfoScreen.cpp
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "InfoScreen.h"

#include "ObjectScreen.h"


// Screens
BaseScreen* InfoScreen::currentScreen;
vector<BaseScreen*> InfoScreen::screen;


InfoScreen::InfoScreen()
: BaseScreen(false)
{
	printf("---InfoScreen Initialization Started---\n");
	//srand(time(0));
	
	// GL
	glClearColor(0.25, 0.25, 1.0, 1.0);	
	
	glEnable(GL_TEXTURE_2D);	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	//---- BUILD SCREENS ----//	
	screen.push_back(new ObjectScreen());
	currentScreen = screen[MAP_SCREEN];
	
	printf("---InfoScreen Initialization Complete---\n");
}

InfoScreen::~InfoScreen()
{
	for(GLshort i = 0; i < screen.size(); i++)
		delete screen[i];
}


//---- GENERAL ----//
void InfoScreen::setScreen(GLshort i)
{
	currentScreen = screen[i];
}


//---- DRAW ----//
void InfoScreen::draw(bool step)
{
	currentScreen->draw(step);
}

void InfoScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	resetView(INFO_FRAME_SIZE[X], INFO_FRAME_SIZE[Y]);
	
	//----- DRAW SCREEN -----//
	draw(true);
}


//--- CONTROLS ---//
void InfoScreen::keyDown(GLshort k)
{
	currentScreen->keyDown(k);
}

void InfoScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	currentScreen->push(t, p);
}

void InfoScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	currentScreen->move(t, p);
}

bool InfoScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	return currentScreen->release(t, p);
}	
