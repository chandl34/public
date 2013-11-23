/*
 *  PieceImage.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "PieceImage.h"

#include "Image.h"

#include "ImageStorage.h"


PieceImage::PieceImage(Image* image, const Coord2d<GLshort>& texOffset,
							  const PieceEdges& edges)
: _edges(edges)
{
	// Setup mask
	PieceFlip flip;
	bool rotated;
	Image* pMask = ImageStorage::getMask(_edges, flip, rotated);
	
	if(pMask == NULL)
		return;
	
	GLshort x = (X + rotated) % 2;
	GLshort y = (Y + rotated) % 2;	
	
	// Init 0-defaulted values
	_texName = pMask->getTexName();
	
	_texSize[X] = pMask->getSize(x);
	_texSize[Y] = pMask->getSize(y);
	
	_texOffset = texOffset;
	
	_texVert = ImageStorage::getVerts(_texSize);
	
	Coord2d<GLfloat> tl(0.0f, 1.0f);	
	Coord2d<GLfloat> br;
	br[X] = pMask->getSize(X) / (GLfloat)pMask->getFullSize(X);
	br[Y] = (pMask->getFullSize(Y) - pMask->getSize(Y)) / (GLfloat)pMask->getFullSize(Y);	
	
	// Regular
	GLfloat texCoord[8];
	texCoord[0] = br[X];	texCoord[1] = tl[Y];
	texCoord[2] = tl[X];	texCoord[3] = tl[Y];
	texCoord[4] = br[X];	texCoord[5] = br[Y];
	texCoord[6] = tl[X];	texCoord[7] = br[Y];
	
	if(flip[X]){
		swap(texCoord[0], texCoord[2]);
		swap(texCoord[4], texCoord[6]);
	}
	
	if(flip[Y]){
		swap(texCoord[1], texCoord[5]);
		swap(texCoord[3], texCoord[7]);
	}
	
	if(rotated){
		swap(texCoord[0], texCoord[6]);
		swap(texCoord[3], texCoord[5]);
	}
	
	_texCoord = ImageStorage::getTexCoords(texCoord);
	
	
	// Setup base image
	_baseTexName = image->getTexName();
	
	tl[X] = 0; tl[Y] = 1;
	br[X] = 1; br[Y] = 0;
	
	//cout << "os: " << os[X] << ", " << os[Y] << "   _rotated: " << _rotated << endl;
	tl[X] = _texOffset[X] / (GLfloat)image->getFullSize(X);
	tl[Y] = (image->getFullSize(Y) - _texOffset[Y]) / (GLfloat)image->getFullSize(Y);
	
	br[X] = (_texOffset[X] + pMask->getSize(x)) / (GLfloat)image->getFullSize(X);
	br[Y] = (image->getFullSize(Y) - _texOffset[Y] - pMask->getSize(y)) / (GLfloat)image->getFullSize(Y);	
	
	texCoord[0] = br[X];	texCoord[1] = tl[Y];
	texCoord[2] = tl[X];	texCoord[3] = tl[Y];
	texCoord[4] = br[X];	texCoord[5] = br[Y];
	texCoord[6] = tl[X];	texCoord[7] = br[Y];	
	
	_baseTexCoord = ImageStorage::getTexCoords(texCoord);
}

PieceImage::~PieceImage(){
	
}


//---- GENERAL ----//
GLshort PieceImage::getEdge(GLshort i)
{
	return _edges.getEdge(i);
}


//---- DRAW ----//
void PieceImage::draw(bool step)
{
	if(_texName != 0){
		//glLoadIdentity();
		// todo: remove.. temp
		glTranslatef(-16 * (getEdge(LEFT) == OUT), -16 * (getEdge(DOWN) == OUT), 0);
		
		// Draw Mask
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
		glBlendFunc(GL_ONE, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, _texName);
		glTexCoordPointer(2, GL_FLOAT, 0, _texCoord);
		glVertexPointer(2, GL_SHORT, 0, _texVert);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		// Draw Background Image
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
		glBindTexture(GL_TEXTURE_2D, _baseTexName);
		glTexCoordPointer(2, GL_FLOAT, 0, _baseTexCoord);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		// todo:  must add a 3rd pass to fix the alpha
	}
}
