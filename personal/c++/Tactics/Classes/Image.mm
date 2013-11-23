/*
 *  Image.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"

#include "ImageStorage.h"


Image::Image(const Size2d<GLshort>& s, GLuint n, const Coord2d<double>& os)
: _size(s)
, _offset(os)
{
	//--- GENERAL ---//
	_texName = n;
	_texVert = ImageStorage::getVerts(s);
	_texCoord = ImageStorage::getTexCoords(Coord2d<GLfloat>(1.0f, 0.0f));
}

Image::Image(const Size2d<GLshort>& s, const Size2d<GLshort>& ts, GLuint n, const Coord2d<double>& os)
: _size(ts)
, _offset(os)
{	
	//--- GENERAL ---//
	_texName = n;
	_texVert = ImageStorage::getVerts(ts);	
	Coord2d<GLfloat> br(ts[X] / (GLfloat)s[X],
							  (s[Y] - ts[Y]) / (GLfloat)s[Y]);
	_texCoord = ImageStorage::getTexCoords(br);
}

Image::Image(const Size2d<GLshort>& s, const Size2d<GLshort>& tl, const Size2d<GLshort>& ts, GLuint n, const Coord2d<double>& os)
: _size(ts)
, _offset(os)
{	
	//--- GENERAL ---//
	_texName = n;	
	_texVert = ImageStorage::getVerts(ts);	
	
	Coord2d<GLfloat> tl2(tl[X] / (GLfloat)s[X],		
								(s[Y] - tl[Y]) / (GLfloat)s[Y]);
	
	Coord2d<GLfloat> br((tl[X] + ts[X]) / (GLfloat)s[X],
							  (s[Y] - (tl[Y] + ts[Y])) / (GLfloat)s[Y]);
	
	_texCoord = ImageStorage::getTexCoords(tl2, br);
}

Image::~Image(){
	
}


//--- GENERAL ---//
const Size2d<GLshort>& Image::getSize() const{
	return _size;
}

GLshort Image::getSize(GLshort c) const{
	return _size[c];
}

void Image::setOffset(double x, double y){
	_offset[X] = x;
	_offset[Y] = y;
}

const Coord2d<double>& Image::getOffset() const{
	return _offset;
}

double Image::getOffset(GLshort i) const{
	return _offset[i];
}

GLuint Image::getTexName() const{
	return _texName;
}

//---- DRAW ----//
void Image::draw(bool step, TexAttr* ta){
	glTranslatef(_offset[X], _offset[Y], 0);
	
	if(ta == NULL){
		glBindTexture(GL_TEXTURE_2D, _texName);
		glVertexPointer(2, GL_SHORT, 0, _texVert);
		glTexCoordPointer(2, GL_FLOAT, 0, _texCoord);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else if(_texName != ta->_texName){
		ta->_texName = _texName;
		glBindTexture(GL_TEXTURE_2D, _texName);
	}	
}


void Image::buildBuffers(vector<GLshort>& texVert, vector<GLfloat>& texCoord){
	for(GLshort i = 0; i < 8; ++i){
		texVert.push_back(_texVert[i]);
		texCoord.push_back(_texCoord[i]);			
	}		
}

