/*
 *  Menu.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MENU_H_
#define MENU_H_

#include "Button.h"

class Menu : public SingleTouchable{
public:
	Menu(const Coord2d<GLshort>&, const Size2d<GLshort>&, const Size2d<GLshort>&);
	~Menu();
	
	//--- GENERAL ---//
	GLshort getDimension(GLshort) const;
	GLshort getSelected() const;
		
	//---- DRAW ----//
	void draw(bool);	
		
	//---- TOUCH ----//
	bool push(const Coord2d<GLshort>&);
	void move(const Coord2d<GLshort>&);
	void release(const Coord2d<GLshort>&);	
	
private:	
	//--- GENERAL ---//
	Size2d<GLshort> dimension;
	Size2d<GLshort> totalSize;
	Button*** button;
	GLshort selected;
};

#endif

