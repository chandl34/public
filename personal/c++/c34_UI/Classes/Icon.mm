/*
 *  Icon.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Icon.h"


Icon::Icon(Image* img, 
		   const Coord2d<double>& os,
		   const Size2d<GLshort>& size) 
: Component(os, size)
, _colorMod(0, 0, 0, 0)
{
	setImage(img);
	
	_texVertName = -1;
	_texCoordName = -1;
}

Icon::~Icon(){
	
}


//--- GENERAL ---//
void Icon::setImage(Image* img)
{
	_image = img;
	if(_image != NULL)
		_image->resize(_size);
}

void Icon::setColor(const Color& color)
{
	_color = color;
}


//---- DRAW ----//
void Icon::draw(bool step, TexAttr* ta)
{
	if(_image != NULL){				
		glLoadIdentity();	
		
		GLfloat currColor[4];
		glGetFloatv(GL_CURRENT_COLOR, currColor);		
		glColor4f(_color[R] + _colorMod[R],
				  _color[G] + _colorMod[G], 
				  _color[B] + _colorMod[B], 
				  _color[A] + _colorMod[A]);
		
		if(_texVertName == -1 || ta == NULL){		
			if(ta != NULL){
				ta->_texName = -1;
				ta->_texVertName = -1;
			}		
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glTranslatef(_offset[X], _offset[Y], 0);
			
			_image->draw(step, ta);		
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
		
		glColor4f(currColor[R], currColor[G], currColor[B], currColor[A]);
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
