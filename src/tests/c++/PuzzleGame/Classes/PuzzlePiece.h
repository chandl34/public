/*
 *  PuzzlePiece.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/27/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PUZZLE_PIECE_H_
#define PUZZLE_PIECE_H_

#include "Icon.h"

class PieceImage;


class PuzzlePiece : public Icon{
public:
	PuzzlePiece(PieceImage*,
					const Coord2d<double>&);
	~PuzzlePiece();
	
	//---- GENERAL ----//
	GLshort getEdge(GLshort);
	
private:
	
};


#endif