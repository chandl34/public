/*
 *  TeamScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 1/7/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "TeamScreen.h"

#include "Button.h"
#include "CampaignMap.h"
#include "Team.h"
#include "Unit.h"

#include "ImageStorage.h"


TeamScreen::TeamScreen()
: SubScreen(false)
{
	printf("Building Team Screen...\n");
	
	Image* img = new Image(Size2d<GLshort>(SUBSCREEN_SIZE[X], 
										   SUBSCREEN_SIZE[Y]), 
						   0);
	ImageStorage::addImage(img);
	_background.setImage(img);
	
	// Stat display background
	img = new Image(Size2d<GLshort>(110, 120), 0);
	ImageStorage::addImage(img);
	_statsBackground.setImage(img);	
	_statsBackground.setOffset(_background.getOffset(X) + 10, 
							   _background.getOffset(Y) + 100);
	
	// Current Team
	/*
	img = new Image(Size2d<GLshort>(110, 20), 0);
	ImageStorage::addImage(img);
	Button* b = new Button(img, Coord2d<double>(_background.getOffset(X) + 130, 
												_background.getOffset(Y) + 10));
	_menu.addSelectable(b);
	
	img = new Image(Size2d<GLshort>(110, 170), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 130, 
										_background.getOffset(Y) + 30));
	_menu.addSelectable(b);
	
	img = new Image(Size2d<GLshort>(110, 20), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 130, 
										_background.getOffset(Y) + 200));
	_menu.addSelectable(b);
	 */
	
	// Current Team
	img = new Image(Size2d<GLshort>(90, 210), 0);
	ImageStorage::addImage(img);
	Button* b = new Button(img, Coord2d<double>(_background.getOffset(X) + 130, 
												_background.getOffset(Y) + 10));
	_menu.addSelectable(b);
	
	img = new Image(Size2d<GLshort>(20, 210), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 220, 
										_background.getOffset(Y) + 10));
	_menu.addSelectable(b);
	
	// Swap Button
	img = new Image(Size2d<GLshort>(60, 30), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 250, 
										_background.getOffset(Y) + 100));
	_menu.addSelectable(b);
	
	// Available Team
	/*
	img = new Image(Size2d<GLshort>(110, 20), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 320, 
										_background.getOffset(Y) + 10));
	_menu.addSelectable(b);
	
	img = new Image(Size2d<GLshort>(110, 170), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 320, 
										_background.getOffset(Y) + 30));
	_menu.addSelectable(b);
	
	img = new Image(Size2d<GLshort>(110, 20), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 320, 
										_background.getOffset(Y) + 200));
	_menu.addSelectable(b);
	 */
	
	// Available Team
	img = new Image(Size2d<GLshort>(90, 210), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 320, 
										_background.getOffset(Y) + 10));
	_menu.addSelectable(b);
	
	img = new Image(Size2d<GLshort>(20, 210), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 410, 
										_background.getOffset(Y) + 10));
	_menu.addSelectable(b);
	
	
	
	
	
	// const GLshort SUBSCREEN_SIZE[] = {440, 230};
	/*
	
	Image* img = new Image(Size2d<GLshort>(SUBSCREEN_SIZE[X], 
										   SUBSCREEN_SIZE[Y]), 
						   0);
	ImageStorage::addImage(img);
	_background.setImage(img);
	
	// Aim
	img = new Image(Size2d<GLshort>(80, 80), 0);
	ImageStorage::addImage(img);
	
	StandardMenu* sm = new StandardMenu(Coord2d<double>(24, MENU_SIZE[Y] + 24), 
										Size2d<GLshort>(1, 2),
										Size2d<GLshort>(80, 80));
	Button* b;
	for(GLshort j = 0; j < 2; ++j){
		b = sm->getButton(j);
		b->setImage(img);
	}
	_menu.addSelectable(sm);
	
	// Bullets
	sm = new StandardMenu(Coord2d<double>(108, MENU_SIZE[Y] + 24), 
						  Size2d<GLshort>(1, 2),
						  Size2d<GLshort>(80, 80));
	for(GLshort j = 0; j < 2; ++j){
		b = sm->getButton(j);
		b->setImage(img);
	}
	_menu.addSelectable(sm);
	
	// Target
	sm = new StandardMenu(Coord2d<double>(192, MENU_SIZE[Y] + 24), 
						  Size2d<GLshort>(1, 3),
						  Size2d<GLshort>(80, 80));
	for(GLshort j = 0; j < 3; ++j){
		b = sm->getButton(j);
		b->setImage(img);
	}
	_menu.addSelectable(sm);
	
	// Confirm
	img = new Image(Size2d<GLshort>(80, 160), 0);
	ImageStorage::addImage(img);
	
	b = new Button(img, Coord2d<double>(276, MENU_SIZE[Y] + 24));
	_menu.addSelectable(b);
	 
	 */
}


//-- GENERAL --//
void TeamScreen::open()
{	
	CampaignMap* campaign = CampaignMap::getInstance();
	Level* sLevel = campaign->getSelectedLevel();
	_team[0] = sLevel->getTeam(OWNER);
	_team[1] = sLevel->getTeam(FREE);	
	
	_team[0]->resetIconOffsets(_background.getOffset(X) + 130, 
							   _background.getOffset(Y) + 220);
	
	_team[1]->resetIconOffsets(_background.getOffset(X) + 320, 
							   _background.getOffset(Y) + 220);
	
	_sUnit = NULL;
}

void TeamScreen::close()
{
	//return _levelMap;
}


//---- DRAW ----//
void TeamScreen::draw(bool step)
{
	glColor4f(0.8, 0.8, 0.8, 1.0);
	_background.draw(step);
	
	glColor4f(0.9, 0.9, 0.9, 1.0);
	_statsBackground.draw(step);
	
	glColor4f(1.0, 1.0, 1.0, 1.0);	
	_menu.draw(step);
	
	_team[0]->drawIcons(step);
	_team[1]->drawIcons(step);
}


//---- TOUCH ----//
void TeamScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.push(t, p);
}

void TeamScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.move(t, p);
}

bool TeamScreen::release(GLshort t, const Coord2d<GLshort>& p)
{	
	if(!_menu.release(t, p))
		return false;
	else{
		GLshort s = _menu.getSelectedOption();	
		
		cout << _menu.getSelected() << " - " << s << endl;
		
		//enum{S_TEAM, S_TEAM_SCROLL, SWAP, O_TEAM, O_TEAM_SCROLL};
		Unit* u;
		switch(_menu.getSelected()){
			case S_TEAM:
				_sUnit = _team[0]->getUnitByIcon(p);
				_sTeam = 0;
				break;
				
			case S_TEAM_SCROLL:
				break;
				
			case SWAP:
				if(_sUnit != NULL){
					_team[_sTeam]->removeUnit(_sUnit);
					_sTeam = (_sTeam + 1) % 2;
					_team[_sTeam]->addUnit(_sUnit);
					open();	// Reset
				}
				break;
				
			case O_TEAM:
				_sUnit = _team[1]->getUnitByIcon(p);
				_sTeam = 1;
				break;
				
			case O_TEAM_SCROLL:
				break;
		};
		
		return false;
	}
}
