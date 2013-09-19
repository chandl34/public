/*
 *  Screen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "Controls.h"

class Image;


class Screen : public Controls{
public:
	virtual ~Screen();
	
protected:	
	Screen(bool);
	
	void resetView(GLshort, GLshort);
};


class BaseScreen : public Screen{
public:
	virtual ~BaseScreen();
	
	//---- DRAW ----//
	void draw(bool);
	
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
	
protected:	
	BaseScreen(bool);
	
	Image* bgImage;
};


class SaveableScreen : public BaseScreen{
public:
	SaveableScreen(bool);
	virtual ~SaveableScreen();
	
	//---- IO ----//
	virtual string getFolder() = 0;
	virtual string getFilter() = 0;
	virtual void save(const string&) = 0;
	virtual void load(const string&) = 0;
};

#endif
