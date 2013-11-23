/*
 *  Image.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef IMAGE_H_
#define IMAGE_H_

#include "Drawable.h"
#include "OffsetBase.h"
#include "SizeBase.h"


class Image 
: public Drawable
, public OffsetBase
, public SizeBase
{	
public:
	Image(GLuint = 0, 
		  const Size2d<GLshort>& = Size2d<GLshort>(0, 0), 
		  const Coord2d<double>& = Coord2d<double>(0, 0));
	Image(GLuint, 
		  const Size2d<GLshort>&, 
		  const Size2d<GLshort>&, 
		  const Coord2d<double>& = Coord2d<double>(0, 0));
	Image(GLuint, 
		  const Size2d<GLshort>&, 
		  const Size2d<GLshort>&, 
		  const Size2d<GLshort>&,
		  const Coord2d<double>& = Coord2d<double>(0, 0));
	~Image();
	
	//--- GENERAL ---//
	GLuint getTexName() const;
	
	void resize(const Size2d<GLshort>&);
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);	
	void buildBuffers(vector<GLshort>&, vector<GLfloat>&);
	
private:	
	//--- GENERAL ---//
	GLuint _texName;
	const GLshort* _texVert;
	const GLfloat* _texCoord;
};

#endif.