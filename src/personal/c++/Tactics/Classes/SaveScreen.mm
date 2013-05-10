/*
 *  SaveScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SaveScreen.h"

#include "Button.h"
#include "Image.h"
#include "LevelMap.h"
#include "StandardMenu.h"

#include "MainScreen.h"
#include "ImageStorage.h"



SaveScreen::SaveScreen()
: SubScreen(false)
{
	printf("Building Save Screen...\n");
	
	Image* img = new Image(Size2d<GLshort>(SUBSCREEN_SIZE[X], 
														SUBSCREEN_SIZE[Y]), 
								  0);
	ImageStorage::addImage(img);
	_background.setImage(img);
	
	
	// Menu options
	img = new Image(Size2d<GLshort>((SUBSCREEN_SIZE[X] - 20) / 4, 
											  (SUBSCREEN_SIZE[Y] - 20) / 2), 
						 0);
	ImageStorage::addImage(img);
	
	StandardMenu* sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 10, 
																		 _background.getOffset(Y) + 10), 
													Size2d<GLshort>(4, 2),
													Size2d<GLshort>((SUBSCREEN_SIZE[X] - 20) / 4, 
																		 (SUBSCREEN_SIZE[Y] - 20) / 2));
	Button* b;
	for(GLshort j = 0; j < 8; ++j){
		b = sm->getButton(j);
		b->setImage(img);
	}
	_menu.addSelectable(sm);
}


//-- GENERAL --//
void SaveScreen::open(){
	
}

void SaveScreen::close()
{
	//return _levelMap;
}


//---- DRAW ----//
void SaveScreen::draw(bool step)
{
	glColor4f(0.0, 0.0, 0.0, 1.0);
	_background.draw(step);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	_menu.draw(step);
}

//---- TOUCH ----//
void SaveScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.push(t, p);
}

void SaveScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	_menu.move(t, p);
}

bool SaveScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(!_menu.release(t, p))
		return false;
	else{		
		GLshort s;		
		switch(_menu.getSelected()){
			case 0:		// Only option now
				s = _menu.getSelectedOption();
				// todo: expand on this
				// s = save file index
				// show images of save and some text about it
				MainScreen::saveData(s);
				//saveGame("test", _levelMap);
				
				return true;
		}
	}
	
	return false;
}
