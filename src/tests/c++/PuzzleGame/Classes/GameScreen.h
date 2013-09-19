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

class Puzzle;


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
	Puzzle* puzzle;
};

#endif