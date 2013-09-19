/*
 *  MenuScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MenuScreen.h"

#include "Button.h"
#include "Image.h"
#include "LevelMap.h"
#include "StandardMenu.h"

#include "ImageStorage.h"
#include "MainScreen.h"


MenuScreen::MenuScreen()
: SubScreen(false)
{
	printf("Building Menu Screen...\n");
	
	Image* img = new Image(Size2d<GLshort>(SUBSCREEN_SIZE[X], 
														SUBSCREEN_SIZE[Y]), 
								  0);
	ImageStorage::addImage(img);
	_background.setImage(img);
	
	
	// Menu options
	img = new Image(Size2d<GLshort>((SUBSCREEN_SIZE[X] - 20), 
											  (SUBSCREEN_SIZE[Y] - 20) / 4), 
						 0);
	ImageStorage::addImage(img);
	
	StandardMenu* sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 10, 
																		 _background.getOffset(Y) + 10), 
													Size2d<GLshort>(1, 4),
													Size2d<GLshort>((SUBSCREEN_SIZE[X] - 20), 
																		 (SUBSCREEN_SIZE[Y] - 20) / 4));
	Button* b;
	for(GLshort j = 0; j < 4; ++j){
		b = sm->getButton(j);
		b->setImage(img);
	}
	_menu.addSelectable(sm);
}


//-- GENERAL --//
void MenuScreen::open(){
	
}

void MenuScreen::close()
{
	//return _levelMap;
}


//---- DRAW ----//
void MenuScreen::draw(bool step)
{
	glColor4f(0.0, 0.0, 0.0, 1.0);
	_background.draw(step);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	_menu.draw(step);
}

//---- TOUCH ----//
void MenuScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.push(t, p);
}

void MenuScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.move(t, p);
}

bool MenuScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(!_menu.release(t, p))
		return false;
	else{		
		GLshort s;		
		switch(_menu.getSelected()){
			case 0:		// Only option now
				s = _menu.getSelectedOption();
				if(s == 0){		// todo: add enums for all this stuff
					printf("Return to Main Menu\n");
					MainScreen::setScreen(TITLE_SCREEN);
				}
				else if(s == 1){
					printf("Open Options Menu\n");
					
				}
				else if(s == 2){
					printf("Open Load Menu\n");
					MainScreen::setSubScreen(LOAD_SCREEN);
					return false;
				}
				else{
					printf("Open Save Menu\n");
					MainScreen::setSubScreen(SAVE_SCREEN);
					return false;
				}				
				break;
		}
		
		return true;
	}
}
