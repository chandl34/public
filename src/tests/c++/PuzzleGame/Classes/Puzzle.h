/*
 *  Puzzle.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef PUZZLE_H_
#define PUZZLE_H_

#include "Touchable.h"

#include "PuzzlePiece.h"

class Image;


class Puzzle : public Touchable{
public:
	Puzzle(Image*, const Size2d<GLshort>&);
	~Puzzle();
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- TOUCH ---//
	bool isTouching(const Coord2d<GLshort>&);
	
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	Image* image;
	Size2d<GLshort> size;
	vector<vector<PuzzlePiece*> > piece;
};

#endif
