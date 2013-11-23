/*
 *  LevelScreenTouch.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelScreen.h"

#include "Button.h"
#include "LevelMap.h"
#include "PopupMenu.h"

#include "MainScreen.h"


#include "MemCheck.h"


void LevelScreen::push(GLshort t, const Coord2d<GLshort>& p)
{	
	// If screen is locked, touch will be ignored.
	if(_levelMap->isLocked())
		return;
	
	if(_menu.isTouching(p))
		_touched[t] = &_menu;
	else
		_touched[t] = _levelMap;
	
	// Disallow illegal touches
	if(_touched[0] == _touched[1]){
		if(!_touched[t]->isMultiTouchable())
			_touched[t] = NULL;
	}
	else{
		// Disable touching two different touchables at once
		if(_touched[(t + 1) % 2] != NULL)
			_touched[t] = NULL;
	}
	
	if(_touched[t] != NULL)
		_touched[t]->push(t, p);
}

void LevelScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	if(_touched[t] == NULL)
		return;
	
	_touched[t]->move(t, p);
}

bool LevelScreen::release(GLshort t, const Coord2d<GLshort>& p)
{	
	if(_touched[t] == NULL)
		return false;
	
	if(_touched[t]->release(t, p)){
		if(_touched[t] == &_menu){
			GLshort s = _menu.getSelectedOption();	
			switch(_menu.getSelected()){
				case CURSOR_MODE_MENU:			
					if(s > 0){
						printf("Selected %i Mode Button\n", s - 1);
						_levelMap->setMode(s - 1);
					}
					break;
					
				case STATIC_MODE_MENU:				
					if(s > 0){
						printf("Selected %i Mode Button\n", s - 1 + UNIT_MODES);
						_levelMap->setMode(s - 1 + UNIT_MODES);
					}
					
					// random testing stuff linked to this button
					if(s == 0){
						freeMemory();
						for(GLshort i = 2; i >= 0; --i)
							cout << "CAM BOUND: " << CAMERA_BOUND[i][X] << ", " << CAMERA_BOUND[i][Y] << endl;
						cout << endl;
						for(GLshort i = 2; i >= 0; --i)
							cout << "VIEW SIZE: " << VIEW_SIZE[i][X] << ", " << VIEW_SIZE[i][Y] << endl;
						cout << endl;
						for(GLshort i = 2; i >= 0; --i)
							cout << "MAP VIEW SIZE: " << MAP_VIEW_SIZE[i][X] << ", " << MAP_VIEW_SIZE[i][Y] << endl;
					}
					
					break;
					
				case PREV_MENU:
					printf("Select Previous Unit\n");
					_levelMap->selectPrevUnit();
					break;
					
				case UNIT_MENU:
					printf("Opening Inventory Screen\n");
					if(_levelMap->getSelectedUnit() != NULL){
						_levelMap->setMode(MOVE);
						MainScreen::setSubScreen(INVENTORY_SCREEN);
					}
					break;
					
				case NEXT_MENU:
					printf("Select Next Unit\n");
					_levelMap->selectNextUnit();
					break;
					
				case MAP_MENU:
					printf("Opening Mini Map Screen\n");
					_levelMap->setMode(MOVE);
					MainScreen::setSubScreen(MINI_MAP_SCREEN);
					break;
					
				case OPTION_MENU:	
					if(s == 0){
						printf("Selected Confirm Button\n");
						_levelMap->confirmAction();
					}
					else if(s == 1){
						printf("End Turn\n");
						_levelMap->endTurn();
					}
					else{
						printf("Opening Menu Screen\n");						
						MainScreen::setSubScreen(MENU_SCREEN);
					}
					break;					
			};
		}
	}
	
	_touched[t] = NULL;
	
	return true;
}	
