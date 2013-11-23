/*
 *  StandardMenu.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STANDARD_MENU_H_
#define STANDARD_MENU_H_

#include "Selectable.h"

class Button;


class StandardMenu : public Selectable{
public:
	StandardMenu(const Coord2d<double>&, const Size2d<GLshort>&, const Size2d<GLshort>&);
	
	//--- GENERAL ---//	
	Button* getButton(GLshort = 0);
	
	//---- DRAW ----//
	void draw(bool);	
		
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
	
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);		
	
private:	
	//--- GENERAL ---//
	vector<vector<Button> > button;
	Size2d<GLshort> totalSize;
};

#endif

