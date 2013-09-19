/*
 *  AimingScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/23/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "AimingScreen.h"

#include "Button.h"
#include "Icon.h"
#include "Image.h"
#include "LevelMap.h"
#include "StandardMenu.h"

#include "ImageStorage.h"


AimingScreen::AimingScreen()
: SubScreen(false)
{
	printf("Building Aiming Screen...\n");
	
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
}


//-- GENERAL --//
void AimingScreen::open()
{	
	aimAdd = 0;	
	target = TORSO;	
	bullets = 1;	
	
	LevelMap* levelMap = LevelMap::getInstance();
	Unit* u = levelMap->getSelectedUnit();
	u->aim(target, bullets, aimAdd);
}

void AimingScreen::close()
{
	//return _levelMap;
}


//---- DRAW ----//
void AimingScreen::draw(bool step)
{
	glColor4f(0.8, 0.8, 0.8, 1.0);
	_background.draw(step);
	
	glColor4f(0.9, 0.9, 0.9, 1.0);
	
	
	glColor4f(1.0, 1.0, 1.0, 1.0);	
	_menu.draw(step);
}


//---- TOUCH ----//
void AimingScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.push(t, p);
}

void AimingScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.move(t, p);
}

bool AimingScreen::release(GLshort t, const Coord2d<GLshort>& p)
{	
	if(!_menu.release(t, p))
		return false;
	else{
		LevelMap* levelMap = LevelMap::getInstance();
		Unit* u = levelMap->getSelectedUnit();
		
		GLshort s;				
		switch(_menu.getSelected()){
			case AIM_MENU:
				s = _menu.getSelectedOption();
				if(s == 0){
					printf("Aim down\n");
					--aimAdd;
				}
				else{
					printf("Aim up\n");
					++aimAdd;
				}				
				break;
				
			case BULLETS_MENU:
				s = _menu.getSelectedOption();
				if(s == 0){
					printf("Less bullets\n");
					--bullets;
				}
				else{
					printf("More bullets\n");
					++bullets;
				}				
				break;
				
			case TARGET_MENU:
				s = _menu.getSelectedOption();				
				target = s;
				if(s == LEGS){
					printf("Targetting legs\n");
				}
				else if(s == TORSO){
					printf("Targetting torso\n");
				}		
				else{
					printf("Targetting head\n");
				}
				break;
				
			case CONFIRM_MENU:
				printf("Confirm shot\n");
				u->act(USE);
				return true;
		};		
		
		u->aim(target, bullets, aimAdd);
		printf("effective chance hit to hit:  %.2f\n", u->getEffectiveCTH());
		return false;
	}
}
