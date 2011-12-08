/*
 *  BaseScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BaseScreen.h"
#include "TextureIO.h"
#include "ModelIO.h"


BaseScreen::BaseScreen(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);		
		
	//---- BUILD CONTAINERS ----//	
	// Loading some images for testing!
	printf("Loading Images...\n");
	imageContainer.addImage(loadPNG("cursor", 80, 41));
	
	
	// One ring to rule them all
	Model* m;
	GLshort i, j, k, l;				// Lot of repitition here.  Should find a better storage method
	
	printf("Loading Models...\n");
	
	// ConstObject
	modelContainer.addConstImage(GROUND, loadPNG("ground", 80, 40));
	modelContainer.setConstModel(GROUND, loadOBJ("ground"));
		
	
	// SideObject
	modelContainer.addSideImage(WALL, LEFT_SIDE, loadPNG("wall0", 44, 124));
	modelContainer.addSideImage(WALL, RIGHT_SIDE, loadPNG("wall1", 44, 124));
	m = loadOBJ("wall");
	m->addBlockedDir(LEFT);
	m->addBlockedDir(DOWN_LEFT);
	m->addBlockedDir(DOWN);
	modelContainer.setSideModel(WALL, m);	
	
	// wall frames
	modelContainer.addSideImage(TOP_FRAME, LEFT_SIDE, loadPNG("topFrame0", 44, 29));
	modelContainer.addSideImage(TOP_FRAME, RIGHT_SIDE, loadPNG("topFrame1", 44, 29));
	modelContainer.setSideModel(TOP_FRAME, loadOBJ("topFrame"));
	
	modelContainer.addSideImage(BOTTOM_FRAME, LEFT_SIDE, loadPNG("bottomFrame0", 40, 64));
	modelContainer.addSideImage(BOTTOM_FRAME, RIGHT_SIDE, loadPNG("bottomFrame1", 40, 64));
	m = loadOBJ("bottomFrame");
	m->addBlockedDir(DOWN_LEFT);
	modelContainer.setSideModel(BOTTOM_FRAME, m);
		
	modelContainer.addSideImage(FRONT_FRAME, LEFT_SIDE, loadPNG("cornerFrame0", 6, 103));
	modelContainer.addSideImage(FRONT_FRAME, RIGHT_SIDE, loadPNG("cornerFrame1", 6, 103));
	m = loadOBJ("frontFrame");
	m->addBlockedDir(DOWN);
	modelContainer.setSideModel(FRONT_FRAME, m);
	
	modelContainer.addSideImage(SIDE_FRAME, LEFT_SIDE, loadPNG("cornerFrame0", 6, 103));
	modelContainer.addSideImage(SIDE_FRAME, RIGHT_SIDE, loadPNG("cornerFrame1", 6, 103));
	m = loadOBJ("sideFrame");
	m->addBlockedDir(LEFT);
	modelContainer.setSideModel(SIDE_FRAME, m);
	
	
	// RotateObject
	for(i = 0; i < PATH_DIRS; i++)
		modelContainer.addRotateImage(UNIT, i, loadPNG("unit", 34, 80));	
	modelContainer.setRotateModel(UNIT, loadOBJ("unit"));
	
	modelContainer.addRotateImage(BULLET, 0, new Image(Size2d<GLshort>(2, 2), 0));
	modelContainer.setRotateModel(BULLET, loadOBJ("blank"));
	
	
	// DoorObject
	modelContainer.setDoorModel(DOOR, loadOBJ("door"));
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			for(k = 0; k < 2; k++){
				for(l = 0; l < 2; l++){
					if((i + l)%2 == 0)
						modelContainer.addDoorImage(DOOR, i, j, k, l, loadPNG("door0", 38, 113));
					else
						modelContainer.addDoorImage(DOOR, i, j, k, l, loadPNG("door1", 38, 113));		
				}
			}
		}		
	}	
	
	
	tacticalScreen = new TacticalScreen();
	currentScreen = tacticalScreen;
	
	frames = 0;
	lastTime = 0;
	timeElapsed = 0;
}

BaseScreen::~BaseScreen(){
	delete tacticalScreen;
}


bool BaseScreen::push(GLshort t, const Coord2d<GLshort>& p){
	return currentScreen->push(t, p);
}

void BaseScreen::move(GLshort t, const Coord2d<GLshort>& p){
	currentScreen->move(t, p);
}

void BaseScreen::release(GLshort t, const Coord2d<GLshort>& p){
	currentScreen->release(t, p);
}	

void BaseScreen::draw(bool step){
	currentScreen->draw(step);
}

void BaseScreen::draw(){
	glClear(GL_COLOR_BUFFER_BIT);	// not needed? - fps improvement is microscopic by removing it
	
		
	//----- SHOW FPS -----//
	if(SHOW_FPS){
		double time = [[NSDate date] timeIntervalSince1970];
		timeElapsed += time - lastTime;
		lastTime = time;		
		frames++;
				
		if(timeElapsed > 2){		
			printf("FPS: %.1f\n", frames/timeElapsed);		
			frames = 0;
			timeElapsed = 0;
		}
	}
	
	//----- DRAW SCREEN -----//
	draw(true);
	/*
	//----- DRAW SCREEN -----//
	if(time > lastStep + STEP_DELAY){
		lastStep = time;
		draw(true);
	}
	else{		
		draw(false);
	}
	 */
}
