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
	_texCoord = ImageStorage::getTexCoords(Coord2d<GLfloat>(1.0f, 1.0f));
}

Image::Image(const Size2d<GLshort>& s, const Size2d<GLshort>& ts, GLuint n, const Coord2d<double>& os)
: _size(ts)
, _offset(os)
{	
	//--- GENERAL ---//
	_texName = n;
	_texVert = ImageStorage::getVerts(ts);	
	Coord2d<GLfloat> tr(ts[X] / (GLfloat)s[X],
							  ts[Y] / (GLfloat)s[Y]);
	_texCoord = ImageStorage::getTexCoords(tr);
}

Image::Image(const Size2d<GLshort>& s, const Size2d<GLshort>& bl, const Size2d<GLshort>& ts, GLuint n, const Coord2d<double>& os)
: _size(ts)
, _offset(os)
{	
	//--- GENERAL ---//
	_texName = n;	
	_texVert = ImageStorage::getVerts(ts);	
	
	Coord2d<GLfloat> blRel(bl[X] / ((GLfloat)s[X]),
								  bl[Y] / ((GLfloat)s[Y]));
	
	Coord2d<GLfloat> tr((bl[X] + ts[X]) / ((GLfloat)s[X]),
							  (bl[Y] + ts[Y]) / ((GLfloat)s[Y]));
	
	_texCoord = ImageStorage::getTexCoords(blRel, tr);
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
void Image::draw(bool step, GLuint* tn){
	if(tn == NULL){
		glBindTexture(GL_TEXTURE_2D, _texName);
		glVertexPointer(2, GL_SHORT, 0, _texVert);
		glTexCoordPointer(2, GL_FLOAT, 0, _texCoord);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else if(_texName != *tn){
		*tn = _texName;
		glBindTexture(GL_TEXTURE_2D, _texName);
	}	
}


void Image::buildBuffers(vector<GLshort>& texVert, vector<GLfloat>& texCoord){
	for(GLshort i = 0; i < 8; ++i){
		texVert.push_back(_texVert[i]);
		texCoord.push_back(_texCoord[i]);			
	}		
}

