/*
 *  PopupMenu.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef POPUP_MENU_H_
#define POPUP_MENU_H_

#include "Menu.h"

class PopupMenu : public SingleTouchable{
public:
	PopupMenu(Button*, Menu*);
	~PopupMenu();
	
	//--- GENERAL ---//
	GLshort getSelected() const;
	
	//---- DRAW ----//
	void draw(bool);	
		
	//---- TOUCH ----//
	bool push(const Coord2d<GLshort>&);
	void move(const Coord2d<GLshort>&);
	void release(const Coord2d<GLshort>&);		
	
private:	
	//--- GENERAL ---//
	Button* button;
	Menu* menu;	
	GLshort selected;
	bool expanded;	
	
	//---- TOUCH ----//
	double timePushed;
	double actionDelay;	
};

#endif

