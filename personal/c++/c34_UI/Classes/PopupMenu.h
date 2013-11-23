/*
 *  PopupMenu.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef POPUP_MENU_H_
#define POPUP_MENU_H_

#include "Button.h"

#include "Menu.h"


class PopupMenu 
: public Button
{
public:
	PopupMenu(Image* = NULL,
			  const Coord2d<double>& = Coord2d<double>(0, 0),
			  const Size2d<GLshort>& = Size2d<GLshort>(0, 0),
			  const Size2d<GLshort>& = Size2d<GLshort>(0, 0),
			  const Size2d<GLshort>& = Size2d<GLshort>(1, 1));
	virtual ~PopupMenu();
	
	//--- GENERAL ---//		// todo: remove... TEMP!
	Button* getButton(GLshort);
	void setColor(const Color&);
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);
	
	//--- TOUCH ---//
	bool push(GLshort, const Coord2d<GLshort>&);
	bool move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	//--- GENERAL ---//
	Menu _menu;
	bool _expanded;
	
	//---- TOUCH ----//
	double _timePushed;
	double _actionDelay;	
};

#endif

