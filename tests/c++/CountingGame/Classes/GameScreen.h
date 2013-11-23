/*
 *  GameScreen.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GAME_SCREEN_H_
#define GAME_SCREEN_H_

#include "Screen.h"

#include "Sequence.h"


#include "Icon.h"
#include "CompositeIcon.h"


class GameScreen : public BaseScreen{
public:
	GameScreen();
	~GameScreen();
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- TOUCH ---//
	void push(GLshort, const Coord2d<GLshort>&);		
	void move(GLshort, const Coord2d<GLshort>&);		
	bool release(GLshort, const Coord2d<GLshort>&);		
	
private:
	//---- GENERAL ----//		
	Icon _balloon[BALLOONS];
	Icon _box[BOXES];
	
	GLshort _state;
	
	Sequence _seq[SEQUENCES];	
	Sequence* _currSequence;
	
	void reset();
	
	// todo: remove!
	Icon* test1;
	CompositeIcon* test2;
};

#endif