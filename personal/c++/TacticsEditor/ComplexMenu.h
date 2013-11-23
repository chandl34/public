/*
 *  ComplexMenu.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COMPLEX_MENU_H_
#define COMPLEX_MENU_H_

#include "Selectable.h"

class Button;


class ComplexMenu : public Selectable{
public:
	~ComplexMenu();
	
	//--- GENERAL ---//
	GLshort getSelectedOption() const;
	
	void addSelectable(Selectable*);
	
	Button* getButton(GLshort, GLshort);
	
	//---- DRAW ----//
	void draw(bool);	
	
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
	
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);		
	
private:	
	//--- GENERAL ---//
	vector<Selectable*> selectable;	
	
	Button* getButton(GLshort = 0);
};

#endif


