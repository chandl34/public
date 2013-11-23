/*
 *  MainScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainScreen.h"

#include "GameScreen.h"
#include "TitleScreen.h"

#include "Options.h"
#include "TextureIO.h"

#include "PieceMask.h"

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
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	resetView();
	
	//---- BUILD STORAGES ----//	
	printf("Loading Images...\n");
	Image* tempImg;
	
	tempImg = loadPNG("the_great_wave_off_kanagawa", Size2d<GLshort>(480, 320));
	imageStorage.addImage(tempImg);
	imageStorage.addBGImage(tempImg);
	
	tempImg = loadPNG("mask1", Size2d<GLshort>(54, 84));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(IN, OUT, IN, OUT)));
	
	tempImg = loadPNG("mask2", Size2d<GLshort>(69, 68));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(IN, IN, OUT, OUT)));
	
	tempImg = loadPNG("mask3", Size2d<GLshort>(69, 53));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(IN, IN, OUT, IN)));
	
	tempImg = loadPNG("mask4", Size2d<GLshort>(69, 84));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(IN, OUT, OUT, OUT)));
	
	tempImg = loadPNG("mask5", Size2d<GLshort>(68, 53));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, IN, OUT, IN)));
	
	tempImg = loadPNG("mask6", Size2d<GLshort>(50, 69));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, IN, IN, OUT)));
	
	tempImg = loadPNG("mask7", Size2d<GLshort>(50, 84));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, OUT, IN, OUT)));
	
	tempImg = loadPNG("mask8", Size2d<GLshort>(68, 84));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, OUT, OUT, OUT)));
	
	tempImg = loadPNG("mask9", Size2d<GLshort>(52, 52));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, IN, IN, IN)));
	
	tempImg = loadPNG("mask10", Size2d<GLshort>(50, 52));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, EDGE, IN, IN)));
	
	tempImg = loadPNG("mask11", Size2d<GLshort>(66, 68));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, EDGE, OUT, OUT)));
	
	tempImg = loadPNG("mask12", Size2d<GLshort>(52, 66));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, EDGE, IN, OUT)));
	
	tempImg = loadPNG("mask13", Size2d<GLshort>(68, 68));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(EDGE, IN, OUT, OUT)));
	
	tempImg = loadPNG("mask14", Size2d<GLshort>(55, 52));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(IN, IN, IN, IN)));
	
	tempImg = loadPNG("mask15", Size2d<GLshort>(86, 84));
	imageStorage.addImage(tempImg);
	imageStorage.addMask(PieceMask(tempImg, PieceEdges(OUT, OUT, OUT, OUT)));
	
	
	//---- BUILD SCREENS ----//	
	screen.push_back(new TitleScreen());
	screen.push_back(new GameScreen());
	currentScreen = screen[TITLE_SCREEN];
	
	
	printf("---Initialization Complete---\n");
}

MainScreen::~MainScreen()
{
	for(GLshort i = 0; i < screen.size(); i++)
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
