/*
 *  Button.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Icon.h"
#include "SingleTouchable.h"

class Button : public SingleTouchable{
public:
	Button(Icon*);
	~Button();
	
	//--- GENERAL ---//
	void select(bool);
	bool isSelected() const;
	
	//---- DRAW ----//
	void draw(bool);	
		
	// SCREEN OFFSET //
	const Coord2d<GLfloat>& getOffset() const;
	GLfloat getOffset(GLshort) const;	
	GLshort getSize(GLshort) const;
		
	//---- TOUCH ----//
	bool push(const Coord2d<GLshort>&);
	void move(const Coord2d<GLshort>&);
	void release(const Coord2d<GLshort>&);	
	
private:	
	//--- GENERAL ---//
	Icon* icon;
	bool selected;
};

#endif
