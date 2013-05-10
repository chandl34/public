/*
 *  Icon.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Icon.h"

#include "Image.h"

#include "HitTest.h"


Icon::Icon(Image* img, const Coord2d<double>& os) 
: Movable(os)
{
	_image = img;
	_texVertName = -1;
	_texCoordName = -1;
}

Icon::~Icon(){
	
}


//--- GENERAL ---//
const Size2d<GLshort>& Icon::getSize() const
{
	return _image->getSize();
}

GLshort Icon::getSize(GLshort c) const
{
	return _image->getSize(c);
}

void Icon::setImage(Image* img)
{
	_image = img;
}


//---- DRAW ----//
void Icon::draw(bool step, TexAttr* ta)
{
	if(_image != NULL){			
		glLoadIdentity();	
		
		if(_texVertName == -1 || ta == NULL){		
			if(ta != NULL){
				ta->_texName = -1;
				ta->_texVertName = -1;
			}		
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glTranslatef(_offset[X], _offset[Y], 0);
			
			_image->draw(step);		
		}
		else{
			_image->draw(step, ta);
			
			if(_texVertName != ta->_texVertName){
				ta->_texCoordName = _texCoordName;
				glBindBuffer(GL_ARRAY_BUFFER, _texCoordName);
				glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				
				ta->_texVertName = _texVertName;												
				glBindBuffer(GL_ARRAY_BUFFER, _texVertName);
				glVertexPointer(2, GL_SHORT, 0, NULL);
			}			
			glDrawArrays(GL_TRIANGLE_STRIP, _texPos, 4);
		}
	}
}


void Icon::buildBuffers(GLuint texVertName, vector<GLshort>& texVert, 
								GLuint texCoordName, vector<GLfloat>& texCoord){
	_texVertName = texVertName;
	_texCoordName = texCoordName;
	_texPos = texVert.size() / 2;
	_image->buildBuffers(texVert, texCoord);
	
	for(GLshort i = texVert.size() - 8; i < texVert.size(); i += 2){
		texVert[i] += _offset[X] + 0.5;
		texVert[i + 1] += _offset[Y] + 0.5;			
	}		
}


//--- TOUCH ---//
bool Icon::isTouching(const Coord2d<GLshort>& p)
{
	return pointInQuad(p, getOffset(), getSize());
}
