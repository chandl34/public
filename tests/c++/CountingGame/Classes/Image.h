/*
 *  Image.h
 *  CountingGame
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
	Image(GLuint,  
			const Size2d<GLshort>&);
	
	Image(GLuint,  
			const Size2d<GLshort>&, 
			const Size2d<GLshort>&,			
			const Coord2d<GLshort>& = Coord2d<GLshort>(0, 0));
	
	//---- GENERAL ----//	
	GLuint getTexName() const;
	
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;
		
	//---- DRAW ----//
	void draw(bool);
	
private:
	//---- GENERAL ----//
	GLuint _texName;
	Size2d<GLshort> _size;
	const GLshort* _texVert;
	const GLfloat* _texCoord;
		
	void init(const Size2d<GLshort>&, 
				 const Coord2d<GLshort>&);
};

#endif