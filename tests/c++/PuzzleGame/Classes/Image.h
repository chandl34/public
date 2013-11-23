/*
 *  Image.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "Drawable.h"


class Image : public Drawable{
public:
	Image();
	
	Image(GLuint,  
			const Size2d<GLshort>&);
	
	Image(GLuint,  
			const Size2d<GLshort>&, 
			const Size2d<GLshort>&,			
			const Coord2d<GLshort>& = Coord2d<GLshort>(0, 0));
	
	//---- GENERAL ----//
	GLuint getTexName();
	
	const Size2d<GLshort>& getSize();
	GLshort getSize(GLshort);
	GLshort getFullSize(GLshort);
	GLshort getTexOffset(GLshort);
	
	//---- DRAW ----//
	virtual void draw(bool);
	
protected:
	//---- GENERAL ----//
	void init();
	
	GLuint _texName;
	const GLshort* _texVert;
	const GLfloat* _texCoord;
	
	Size2d<GLshort> _texSize;
	Size2d<GLshort> _texFullSize;
	Coord2d<GLshort> _texOffset;	
};

#endif