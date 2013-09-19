/*
 *  LevelScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelScreen.h"

#include "EnemyUnit.h"
#include "Button.h"
#include "Icon.h"
#include "Image.h"
#include "LevelMap.h"
#include "PopupMenu.h"
#include "Unit.h"

#include "AimingScreen.h"
#include "InventoryScreen.h"
#include "MiniMapScreen.h"
#include "MenuScreen.h"

#include "ImageStorage.h"
#include "ItemDataStorage.h"
#include "Options.h"
#include "SaveIO.h"

#include "Ammo.h"
#include "Grenade.h"
#include "Gun.h"
#include "ItemContainerType.h"


LevelScreen::LevelScreen()
: BaseScreen(true)
, _estimate(420, 480, 14)
, _itemInfo(245, 295, 19)
, _unitInfo(185, 240, 29)
{
	printf("Building Level Screen...\n");
	_levelMap = NULL;
	
	// Mode
	Image* img1 = new Image(Size2d<GLshort>(60, MENU_SIZE[Y]), 0);	
	ImageStorage::addImage(img1);
	
	PopupMenu* pm = new PopupMenu(Coord2d<double>(0, 0), 
											Size2d<GLshort>(1, 5),
											Size2d<GLshort>(60, MENU_SIZE[Y]));
	Button* b;
	for(GLshort j = 0; j < 6; ++j){
		b = pm->getButton(j);
		b->setImage(img1);	
	}
	_menu.addSelectable(pm);
	
	// Stance/Reload
	pm = new PopupMenu(Coord2d<double>(60, 0), 
							 Size2d<GLshort>(1, 2),
							 Size2d<GLshort>(60, MENU_SIZE[Y]));
	
	for(GLshort j = 0; j < 3; ++j){
		b = pm->getButton(j);
		b->setImage(img1);	
	}
	_menu.addSelectable(pm);
	
	// Prev
	b = new Button(img1, Coord2d<double>(120, 0));
	_menu.addSelectable(b);
	
	// Unit	
	Image* img2 = new Image(Size2d<GLshort>(120, MENU_SIZE[Y]), 0);	
	ImageStorage::addImage(img2);
	
	b = new Button(img2, Coord2d<double>(180, 0));
	_menu.addSelectable(b);
	
	// Next
	b = new Button(img1, Coord2d<double>(300, 0));
	_menu.addSelectable(b);
	
	// Map	
	b = new Button(img1, Coord2d<double>(360, 0));
	_menu.addSelectable(b);
	
	// Options
	pm = new PopupMenu(Coord2d<double>(420, 0), 
							 Size2d<GLshort>(1, 2),
							 Size2d<GLshort>(60, MENU_SIZE[Y]));
	
	for(GLshort j = 0; j < 3; ++j){
		b = pm->getButton(j);
		b->setImage(img1);	
	}
	_menu.addSelectable(pm);
	
	
	//--- TOUCH ---//
	_touched[0] = NULL;
	_touched[1] = NULL;
}

LevelScreen::~LevelScreen()
{
	delete _levelMap;	
}


//---- GENERAL ----//
void LevelScreen::setLevelMap(LevelMap* levelMap)
{
	delete _levelMap;	
	_levelMap = levelMap;
}


//---- DRAW ----//
void LevelScreen::draw(bool step)
{
	if(_levelMap == NULL){
		// draw loading screen
		
	}
	else
		_levelMap->draw(step);
}

void LevelScreen::drawOther(bool step)
{
	resetView();
	_menu.draw(step);
	
	// Displays
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	Unit* u = _levelMap->getSelectedUnit();
	if(u != NULL){
		_unitInfo.update(u);
		_unitInfo.draw(step);
		
		Item* it = u->getEquippedItem();
		if(it != NULL){
			_itemInfo.update(it);
			_itemInfo.draw(step);
		}
		
		_estimate.update(u);
		_estimate.draw(step);		
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
