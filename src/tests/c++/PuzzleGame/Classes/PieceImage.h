/*
 *  PieceImage.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIECE_IMAGE_H_
#define PIECE_IMAGE_H_

#include "Image.h"

#include "PieceData.h"


class PieceImage : public Image{
public:
	PieceImage(Image*, const Coord2d<GLshort>&,
				  const PieceEdges&);
	~PieceImage();
	
	//---- GENERAL ----//
	GLshort getEdge(GLshort);
	
	//---- DRAW ----//
	void draw(bool);
	
private:	
	PieceEdges _edges;
	
	GLuint _baseTexName;
	const GLfloat* _baseTexCoord;
};

#endif