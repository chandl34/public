/*
 *  Puzzle.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Puzzle.h"

#include "PieceImage.h"

#include "Math.h"


Puzzle::Puzzle(Image* i, const Size2d<GLshort>& s)
: Touchable(false)
, size(s)
, piece(s[X])
{
	image = i;
	
	GLshort up, left, down, right;
	Coord2d<GLshort> texOffset;
	for(GLshort i = 0; i < size[X]; i++){     // ^ all the way 
		texOffset[Y] = 0;								// then >	
		for(GLshort j = 0; j < size[Y]; j++){			
			// Determine edges
			if(i == 0)
				left = EDGE;
			else 
				left = (piece[i - 1][j]->getEdge(RIGHT) + 1) % 2;
			
			if(j == 0)
				down = EDGE;
			else 
				down = (piece[i][j - 1]->getEdge(UP) + 1) % 2;
			
			if(i == size[X] - 1)
				right = EDGE;
			else
				right = random(2);
			
			if(j == size[Y] - 1)
				up = EDGE;
			else
				up = random(2);
			
			if(i > 0){
				texOffset[X] = piece[i - 1][j]->getTexOffset(X) + 
				piece[i - 1][j]->getSize(X) - OFFSET;			
			}
			
			piece[i].push_back(new PuzzlePiece(new PieceImage(image, texOffset, 
																			  PieceEdges(left, down, right, up)),
														  Coord2d<double>(i * 67, j * 67)));	
			texOffset[Y] += piece[i][j]->getSize(Y) - OFFSET;
		}	
	}
}

Puzzle::~Puzzle(){
	for(GLshort i = 0; i < size[X]; i++){
		for(GLshort j = 0; j < size[Y]; j++)
			delete piece[i][j];
	}	
}


//---- DRAW ----//
void Puzzle::draw(bool step)
{
	glEnable(GL_BLEND);
	glLoadIdentity();
	for(GLshort i = 0; i < size[X]; i++){
		for(GLshort j = 0; j < size[Y]; j++)	
			piece[i][j]->draw(step);
	}
	glDisable(GL_BLEND);
}
