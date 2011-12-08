/*
 *  BaseScreen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BASE_SCREEN_H_
#define BASE_SCREEN_H_

#include "TacticalScreen.h"
#include "ImageContainer.h"
#include "ModelContainer.h"


class BaseScreen : public Screen{
public:
	BaseScreen();
	~BaseScreen();
	
	bool push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	void release(GLshort, const Coord2d<GLshort>&);	
	
	void draw();
	
private:	
	ImageContainer imageContainer;
	ModelContainer modelContainer;
	
	Screen* currentScreen;
	TacticalScreen* tacticalScreen;
		
	int frames;
	double lastTime;
	double timeElapsed;
	
	void draw(bool);	
};

#endif