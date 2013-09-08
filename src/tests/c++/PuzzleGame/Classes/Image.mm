/*
 *  Image.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"

#include "ImageStorage.h"


Image::Image()
{
	
}

Image::Image(GLuint texName,  
				 const Size2d<GLshort>& texFullSize)
: _texSize(texFullSize)
, _texFullSize(texFullSize)
{		
	_texName = texName;
	init();
}

Image::Image(GLuint texName, 
				 const Size2d<GLshort>& texSize,
				 const Size2d<GLshort>& texFullSize, 
				 const Coord2d<GLshort>& texOffset)
: _texSize(texSize)
, _texFullSize(texFullSize)
, _texOffset(texOffset)
{			
	_texName = texName;
	init();
}

void Image::init()
{
	_texVert = ImageStorage::getVerts(_texSize);
	
	Coord2d<GLfloat> tl(0.0f, 1.0f);	
	Coord2d<GLfloat> br;
	br[X] = _texSize[X] / (GLfloat)_texFullSize[X];
	br[Y] = (_texFullSize[Y] - _texSize[Y]) / (GLfloat)_texFullSize[Y];	
	
	GLfloat texCoord[8];
	texCoord[0] = br[X];	texCoord[1] = tl[Y];
	texCoord[2] = tl[X];	texCoord[3] = tl[Y];
	texCoord[4] = br[X];	texCoord[5] = br[Y];
	texCoord[6] = tl[X];	texCoord[7] = br[Y];	
	
	_texCoord = ImageStorage::getTexCoords(texCoord);
}


//---- GENERAL ----//
GLuint Image::getTexName()
{
	return _texName;
}

const Size2d<GLshort>& Image::getSize()
{
	return _texSize;
}

GLshort Image::getSize(GLshort i)
{
	return _texSize[i];
}

GLshort Image::getFullSize(GLshort i)
{
	return _texFullSize[i];
}

GLshort Image::getTexOffset(GLshort i)
{
	return _texOffset[i];
}


//---- DRAW ----//
void Image::draw(bool step)
{
	glBindTexture(GL_TEXTURE_2D, _texName);
	glVertexPointer(2, GL_SHORT, 0, _texVert);
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoord);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
