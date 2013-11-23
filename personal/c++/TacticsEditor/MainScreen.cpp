/*
 *  MainScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainScreen.h"

#include "Image.h"
#include "MapScreen.h"
#include "Model.h"

#include "Options.h"
#include "ModelIO.h"
#include "TextureIO.h"

// Screens
SaveableScreen* MainScreen::currentScreen;
vector<SaveableScreen*> MainScreen::screen;


MainScreen::MainScreen()
: SaveableScreen(false)
{
	printf("---MainScreen Initialization Started---\n");
	srand(time(0));
	
	// GL
	glClearColor(0.25, 0.25, 1.0, 1.0);	
	
	glEnable(GL_TEXTURE_2D);	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//---- BUILD STORAGES ----//	
	printf("Loading Images...\n");
	{
		// Loading some images for testing!
		Image* tempImg;
		vector<Image*> tempImgs;
		
		// Cursors
		imageStorage.setCursorImage(MOVE, loadPNG("moveCursor", Size2d<GLshort>(80, 41)));
		
		// ConstObject
		imageStorage.addConstImage(ObjType(GROUND), loadPNG("ground", Size2d<GLshort>(80, 40)));
		imageStorage.addConstImage(ObjType(PROJECTILE), new Image(Size2d<GLshort>(2, 2), 0));
		
		// SideObject
		imageStorage.addSideImage(ObjType(WALL), Side(LEFT_SIDE), loadPNG("wall0", Size2d<GLshort>(44, 124)));
		imageStorage.addSideImage(ObjType(WALL), Side(RIGHT_SIDE), loadPNG("wall1", Size2d<GLshort>(44, 124)));
		
		// wall frames
		imageStorage.addSideImage(ObjType(TOP_FRAME), Side(LEFT_SIDE), loadPNG("topFrame0", Size2d<GLshort>(44, 29)));
		imageStorage.addSideImage(ObjType(TOP_FRAME), Side(RIGHT_SIDE), loadPNG("topFrame1", Size2d<GLshort>(44, 29)));
		
		imageStorage.addSideImage(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), loadPNG("bottomFrame0", Size2d<GLshort>(40, 64)));
		imageStorage.addSideImage(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), loadPNG("bottomFrame1", Size2d<GLshort>(40, 64)));
		
		imageStorage.addSideImage(ObjType(FRONT_FRAME), Side(LEFT_SIDE), loadPNG("cornerFrame0", Size2d<GLshort>(6, 103)));
		imageStorage.addSideImage(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), loadPNG("cornerFrame1", Size2d<GLshort>(6, 103)));
		
		imageStorage.addSideImage(ObjType(SIDE_FRAME), Side(LEFT_SIDE), loadPNG("cornerFrame0", Size2d<GLshort>(6, 103)));
		imageStorage.addSideImage(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), loadPNG("cornerFrame1", Size2d<GLshort>(6, 103)));
		
		// DoorObject
		GLshort i, j, k, l;				// Lot of repitition here.  Should find a better storage method
		for(i = 0; i < 2; ++i){
			for(j = 0; j < 2; ++j){
				for(k = 0; k < 2; ++k){
					for(l = 0; l < 2; ++l){
						if((i + l)%2 == 0)
							imageStorage.addDoorImage(ObjType(DOOR), Side(i), Inner(j), Hinge(k), Open(l), loadPNG("door0", Size2d<GLshort>(38, 113)));
						else
							imageStorage.addDoorImage(ObjType(DOOR), Side(i), Inner(j), Hinge(k), Open(l), loadPNG("door1", Size2d<GLshort>(38, 113)));		
					}
				}
			}		
		}	
		
		
	}

	printf("Loading Models...\n");
	{
		// ConstObject
		modelStorage.setConstModel(ObjType(GROUND), loadOBJ("ground"));			
		modelStorage.setConstModel(ObjType(PROJECTILE), loadOBJ("blank"));
		
		// SideObject
		modelStorage.setSideModel(ObjType(WALL), loadOBJ("wall"));	
		
		// wall frames
		modelStorage.setSideModel(ObjType(TOP_FRAME), loadOBJ("topFrame"));		
		modelStorage.setSideModel(ObjType(BOTTOM_FRAME), loadOBJ("bottomFrame"));		
		modelStorage.setSideModel(ObjType(FRONT_FRAME), loadOBJ("frontFrame"));
		modelStorage.setSideModel(ObjType(SIDE_FRAME), loadOBJ("sideFrame"));
		
		// DoorObject
		modelStorage.setDoorModel(ObjType(DOOR), loadOBJ("door"));
	}
	
	
	//---- BUILD SCREENS ----//	
	screen.push_back(new MapScreen());
	//screen.push_back(new GameScreen());
	currentScreen = screen[MAP_SCREEN];
	
	
	printf("---MainScreen Initialization Complete---\n");
}

MainScreen::~MainScreen()
{
	for(GLshort i = 0; i < screen.size(); i++)
		delete screen[i];
}


//---- GENERAL ----//
void MainScreen::setScreen(GLshort i)
{
	currentScreen = screen[i];
}


//---- IO ----//
string MainScreen::getFolder()
{
	return currentScreen->getFolder();
}

string MainScreen::getFilter()
{
	return currentScreen->getFilter();
}

void MainScreen::save(const string& str)
{
	currentScreen->save(str);
}
void MainScreen::load(const string& str)
{
	currentScreen->load(str);
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
		double t = time(0);
		timeElapsed += t - lastTime;
		lastTime = t;		
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


//--- CONTROLS ---//
void MainScreen::keyDown(GLshort k)
{
	currentScreen->keyDown(k);
}

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
