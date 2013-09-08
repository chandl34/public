/*
 *  PieceMask.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "PieceMask.h"


// PieceMask
PieceMask::PieceMask(Image* img, const PieceEdges& pe)
: edges(pe)
{
	image = img;
	
}


Image* PieceMask::getImage(){
	return image;
}

bool PieceMask::isMatch(const PieceEdges& pe, PieceFlip& pf, bool& r){	
	for(GLshort i = 0; i < 2; i++){
		if(edges.isMatch(pe, pf, i)){
			r = i;
			return true;
		}
	}
	
	return false;
}
