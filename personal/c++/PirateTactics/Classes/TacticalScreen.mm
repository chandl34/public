/*
 *  TacticalScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "TacticalScreen.h"
#include "ImageContainer.h"


TacticalScreen::TacticalScreen(){
	printf("Building LevelMap...\n");
	levelMap = new LevelMap();
	
	// TEMPORARY!!@!@!@!!11
	Image* img = new Image(Size2d<GLshort>(SCREEN_PIXEL[X], MENU_SIZE[Y]), 0);
	ImageContainer::addImage(img);	
	
	tacticMenu = new PopupMenu(new Button(new Icon(img, Coord2d<GLfloat>(0, 0))), 
							   new Menu(Coord2d<GLshort>(0, MENU_SIZE[Y]), 
										Size2d<GLshort>(8, 2), 
										Size2d<GLshort>(60, MENU_SIZE[Y])));
		
	touched[0] = NULL;
	touched[1] = NULL;
		
	levelMap->addUnit(Unit::create(ObjType(UNIT), Dir(DOWN_LEFT), 0, Team(BAD), HP(100), TU(40)), 
					  6, 8);
	levelMap->addUnit(Unit::create(ObjType(UNIT), Dir(DOWN_RIGHT), 0, Team(BAD), HP(100), TU(40)), 
					  0, 7);	
	levelMap->addUnit(Unit::create(ObjType(UNIT), Dir(DOWN_RIGHT), 0, Team(BAD), HP(100), TU(40)), 
					  4, 2);
	levelMap->addUnit(Unit::create(ObjType(UNIT), Dir(DOWN_LEFT), 0, Team(GOOD), HP(100), TU(40)), 
					  3, 3);
}

TacticalScreen::~TacticalScreen(){
	delete levelMap;
	delete tacticMenu;
}


void TacticalScreen::draw(bool step){
	levelMap->draw(step);
	
	resetView(MAX_ZOOM);
	tacticMenu->draw(step);
}
