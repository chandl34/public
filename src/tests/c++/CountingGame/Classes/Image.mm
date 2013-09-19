/*
 *  Image.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"

#include "ImageStorage.h"


Image::Image(GLuint texName,  
				 const Size2d<GLshort>& size)
: _size(size)
{
	_texName = texName;
	_texVert = ImageStorage::getVerts(_size);
	init(size, Coord2d<GLshort>(0, 0));
}

Image::Image(GLuint texName, 
				 const Size2d<GLshort>& size,
				 const Size2d<GLshort>& relSize, 
				 const Coord2d<GLshort>& offset) 
: _size(relSize)
{
	_texName = texName;
	_texVert = ImageStorage::getVerts(_size);
	init(size, offset);
}

void Image::init(const Size2d<GLshort>& size, 
					  const Coord2d<GLshort>& offset){
	Coord2d<GLfloat> tl;
	tl[X] = offset[X] / (GLfloat)size[X];
	tl[Y] = (size[Y] - offset[Y]) / (GLfloat)size[Y];	
	
	Coord2d<GLfloat> br;
	br[X] = (_size[X] + offset[X]) / (GLfloat)size[X];
	br[Y] = (size[Y] - (_size[Y] + offset[Y])) / (GLfloat)size[Y];	
	
	_texCoord = ImageStorage::getTexCoords(tl, br);
}


//---- GENERAL ----//
GLuint Image::getTexName() const{
	return _texName;
}

const Size2d<GLshort>& Image::getSize() const{
	return _size;
}

GLshort Image::getSize(GLshort a) const{
	return _size[a];
}


//---- DRAW ----//
void Image::draw(bool step)
{
	glBindTexture(GL_TEXTURE_2D, _texName);
	glVertexPointer(2, GL_SHORT, 0, _texVert);
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoord);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
