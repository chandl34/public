/*
 *  Menu.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MENU_H_
#define MENU_H_

#include "Component.h"

#include "Button.h"


class Menu 
: public Component
{
public:
	Menu(const Coord2d<double>& = Coord2d<double>(0, 0),
		 const Size2d<GLshort>& = Size2d<GLshort>(0, 0),
		 const Size2d<GLshort>& = Size2d<GLshort>(1, 1),
		 bool = false);
	virtual ~Menu();
	
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
	vector<vector<Button> >  _button;
	Size2d<GLshort> _dim;
	Button* _selected;
	bool _mobile;
};

#endif
