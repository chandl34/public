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

#include "Touchable.h"

#include "Camera.h"
#include "Cursor.h"
#include "Icon.h"

class LevelMap;


class Screen : public Touchable{
protected:			
	Screen(bool);
	
public:
	virtual ~Screen();
	
protected:			
	//-- GENERAL --//
	Icon _background;
	
	void resetView(GLshort = MAX_ZOOM);
	void resetView(GLshort, GLshort);
};


class BaseScreen : public Screen{	
protected:	
	BaseScreen(bool);
	
public:
	virtual ~BaseScreen();
	
	//---- DRAW ----//
	virtual void drawOther(bool);
	
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
};


class MapScreen : public BaseScreen{
protected:	
	MapScreen(bool);
	
public:
	virtual ~MapScreen();
	
	//-- GENERAL --//	
	void selectTarget(Movable*);
	
	//--- TOUCH ---//
	virtual bool isLocked() = 0;
	
	//--- GAMEPLAY ---//
	virtual void confirmAction() = 0;
	virtual void setMode(GLshort) = 0;	
	virtual void endTurn() = 0;
	
protected:
	//-- GENERAL --//
	Camera _camera;	
	Cursor _cursor;	
	
	GLshort _mode;
	GLshort _turnOwner;
	
	//--- TOUCH ---//	
	Coord2d<GLshort> _startPoint[2];		
	Coord2d<GLshort> _lastPoint[2];	
	GLshort _touchCount;								
	bool _drag;										
	double _actionDelay;							
	double _timePushed;		
};


const GLshort SUBSCREEN_SIZE[] = {440, 230};

class SubScreen : public Screen{
protected:	
	SubScreen(bool);	
	
public:
	virtual ~SubScreen();
	
	//-- GENERAL --//
	virtual void open() = 0;		// todo: later change this to open with all necessary game data.  map + campaign
	virtual void close() = 0;
	
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
};

#endif
