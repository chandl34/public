/*
 *  PuzzlePiece.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/27/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "PuzzlePiece.h"

#include "PieceImage.h"


PuzzlePiece::PuzzlePiece(PieceImage* image,
								 const Coord2d<double>& offset)
: Icon(image, offset)
{
	
}

PuzzlePiece::~PuzzlePiece()
{
	delete _image;		// NOTE: Unlike most Images, PieceImages are only stored here
}


//---- GENERAL ----//
GLshort PuzzlePiece::getEdge(GLshort i)
{
	return ((PieceImage*)_image)->getEdge(i);
}