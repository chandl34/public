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
#include "GameScreen.h"

#include "Options.h"
#include "TextureIO.h"


// Screens
BaseScreen* MainScreen::currentScreen;
vector<BaseScreen*> MainScreen::screen;


MainScreen::MainScreen()
: BaseScreen(false)
{
	printf("---Initialization Started---\n");
	
	
	srand([[NSDate date] timeIntervalSince1970]);
	
	// GL
	glClearColor(0.0, 0.0, 1.0, 1.0);	
	
	glEnable(GL_TEXTURE_2D);	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	resetView();
	
	//---- BUILD STORAGES ----//	
	printf("Loading Images...\n");
	Image* tempImg;
	vector<Image*> tempImgs;
	
	tempImg = loadPNG("the_great_wave_off_kanagawa", Size2d<GLshort>(480, 320));
	imageStorage.addImage(tempImg);
	imageStorage.addBGImage(tempImg);
	
	tempImgs = loadPNG("items");
	for(GLshort i = 0; i < tempImgs.size(); i++){
		imageStorage.addImage(tempImgs[i]);
		imageStorage.addItemImage(tempImgs[i]);
	}
	/*
	tempImg = loadPNG("items", Size2d<GLshort>(20, 20));
	imageStorage.addImage(tempImg);
	imageStorage.addItemImage(tempImg);
	 */
	
	//---- BUILD SCREENS ----//	
	screen.push_back(new TitleScreen());
	screen.push_back(new GameScreen());
	
	currentScreen = screen[TITLE_SCREEN];
	

	printf("---Initialization Complete---\n");
}

MainScreen::~MainScreen()
{
	for(GLshort i = 0; i < screen.size(); ++i)
		delete screen[i];
}


//---- GENERAL ----//
void MainScreen::setScreen(GLshort i){
	currentScreen = screen[i];
}


//---- DRAW ----//
void MainScreen::draw(bool step)
{
	currentScreen->draw(step);
}

void MainScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	++totalFrames;
	
	//----- SHOW FPS -----//
	if(SHOW_FPS){
		double time = [[NSDate date] timeIntervalSince1970];
		timeElapsed += time - lastTime;
		lastTime = time;		
		++frames;
		
		if(timeElapsed > 2){		
			printf("FPS: %.1f\n", frames/timeElapsed);		
			frames = 0;
			timeElapsed = 0;
		}
	}
	
	//----- DRAW SCREEN -----//
	draw(totalFrames % 5  == 0);
}


//--- TOUCH ---//
void MainScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	currentScreen->push(t, p);
}

void MainScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	currentScreen->move(t, p);
}

bool MainScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	return currentScreen->release(t, p);
}	
