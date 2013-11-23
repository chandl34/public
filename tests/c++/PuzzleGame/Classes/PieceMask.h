/*
 *  PieceMask.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIECE_MASK_H_
#define PIECE_MASK_H_

#include "PieceData.h"

class Image;


class PieceMask{
public:
	PieceMask(Image*, const PieceEdges&);
	
	Image* getImage();
	bool isMatch(const PieceEdges&, PieceFlip&, bool&);
	
private:			
	Image* image;
	PieceEdges edges;
};


#endif