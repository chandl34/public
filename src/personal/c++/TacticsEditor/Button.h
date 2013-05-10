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

#include "Selectable.h"

#include "Icon.h";

class Image;


class Button : public Selectable{
public:
	Button(Image* = NULL, const Coord2d<double>& = Coord2d<double>(0, 0));
	
	//--- GENERAL ---//
	void select(bool);
	void enable(bool);
	bool isEnabled() const;
	
	const Coord2d<double>& getOffset() const;
	double getOffset(GLshort) const;	
	GLshort getSize(GLshort) const;
	
	void setImage(Image*);
	
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
	Icon icon;
	bool enabled;
};

#endif
