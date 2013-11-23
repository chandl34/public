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

#include "Drawable.h"
#include "Event.h"
#include "Touchable.h"

#include "Section.h"


class Screen
: public Drawable
, public Touchable
{
protected:			
	Screen(bool);
	
public:
	virtual ~Screen();
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);
	
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
	
protected:			
	//-- GENERAL --//
	Section _base;
	
	void resetView(GLshort = MAX_ZOOM);
	void resetView(GLshort, GLshort);
};


class BaseScreen
: public Screen
, public EventHandler
{	
protected:	
	BaseScreen(bool);
	
public:
	virtual ~BaseScreen();
	
	//---- DRAW ----//
	virtual void drawOther(bool, TexAttr* = NULL);
};



const GLshort SUBSCREEN_SIZE[] = {440, 230};

class SubScreen 
: public Screen
, public EventHandler
{
protected:	
	SubScreen(bool);	
	
public:
	virtual ~SubScreen();
	
	//-- GENERAL --//
	virtual void open() = 0;		// todo: later change this to open with all necessary game data.  map + campaign
	virtual void close() = 0;
};

#endif
