/*
 *  CampaignScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CampaignScreen.h"

#include "Button.h"
#include "CampaignMap.h"
#include "Image.h"
#include "PopupMenu.h"
#include "Team.h"

#include "ImageStorage.h"


CampaignScreen::CampaignScreen()
: BaseScreen(false)
, _levelInfo(185, 240, 29)
{
	printf("Building CampaignMap Screen...\n");
	_campaignMap = NULL;
	
	_background.setImage(ImageStorage::getBGImage(1));
	
	
	//---- MENU ----//
	// Mode
	Image* img1 = new Image(Size2d<GLshort>(60, MENU_SIZE[Y]), 0);	
	ImageStorage::addImage(img1);
	
	PopupMenu* pm = new PopupMenu(Coord2d<double>(0, 0), 
											Size2d<GLshort>(1, 2),
											Size2d<GLshort>(60, MENU_SIZE[Y]));
	Button* b;
	for(GLshort j = 0; j < 3; ++j){
		b = pm->getButton(j);
		b->setImage(img1);	
	}
	_menu.addSelectable(pm);
	
	// Team menu
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
	
	// Level	
	Image* img2 = new Image(Size2d<GLshort>(120, MENU_SIZE[Y]), 0);	
	ImageStorage::addImage(img2);
	
	b = new Button(img2, Coord2d<double>(180, 0));
	_menu.addSelectable(b);
	
	// Next
	b = new Button(img1, Coord2d<double>(300, 0));
	_menu.addSelectable(b);
	
	// Domestics	
	pm = new PopupMenu(Coord2d<double>(360, 0), 
							 Size2d<GLshort>(1, 2),
							 Size2d<GLshort>(60, MENU_SIZE[Y]));
	
	for(GLshort j = 0; j < 3; ++j){
		b = pm->getButton(j);
		b->setImage(img1);	
	}
	_menu.addSelectable(pm);
	
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

CampaignScreen::~CampaignScreen()
{
	delete _campaignMap;
}



//---- GENERAL ----//
void CampaignScreen::setCampaignMap(CampaignMap* campaign)
{
	delete _campaignMap;		
	_campaignMap = campaign;
}


//---- DRAW ----//
void CampaignScreen::draw(bool step)
{
	glColor4f(.75f, .75f, .75f, 1.0f);
	_background.draw(step);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if(_campaignMap == NULL){
		// Draw something here
		
	}
	else
		_campaignMap->draw(step);	
}

void CampaignScreen::drawOther(bool step)
{
	resetView();
	_menu.draw(step);
	
	// Displays
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	Team* sTeam = _campaignMap->getSelectedTeam();
	if(sTeam != NULL){
		_levelInfo.update(sTeam->getLevel());
		_levelInfo.draw(step);
	}	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	
	/*
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
	 */
}
