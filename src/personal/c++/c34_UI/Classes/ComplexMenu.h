/*
 *  ComplexMenu.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/26/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COMPLEX_MENU_H_
#define COMPLEX_MENU_H_

#include "Component.h"

#include "Button.h"
#include "Menu.h"


class ComplexMenu 
: public Component
{
public:
	ComplexMenu();
	virtual ~ComplexMenu();
	
	//--- GENERAL ---//		
	void addButton(Button*);
	void setColor(const Color&);
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);
	
	//--- TOUCH ---//
	bool isTouching(const Coord2d<GLshort>&);
	
	bool push(GLshort, const Coord2d<GLshort>&);
	bool move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	list<Button*>  _button;
	Button* _selected;
};

#endif

