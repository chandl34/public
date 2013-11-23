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


Icon::Icon(Image* img, const Coord2d<double>& os) : offset(os){
	image = img;
	_texVertName = -1;
}

Icon::~Icon(){
	
}


//--- GENERAL ---//
const Size2d<GLshort>& Icon::getSize() const{
	return image->getSize();
}

GLshort Icon::getSize(GLshort c) const{
	return image->getSize(c);
}

void Icon::setOffset(double x, double y){
	offset[X] = x;
	offset[Y] = y;
	if(image != NULL){
		offset[X] += image->getOffset(X);
		offset[Y] += image->getOffset(Y);
	}
}

const Coord2d<double>& Icon::getOffset() const{
	return offset;
}

double Icon::getOffset(GLshort i) const{
	return offset[i];
}

void Icon::setImage(Image* img){
	image = img;
}

bool Icon::isTouching(const Coord2d<GLshort>& p){
	return pointInQuad(p, getOffset(), getSize());
}


//---- DRAW ----//
void Icon::draw(bool step, GLuint* tn, GLuint* tc, GLuint* tv){
	if(image != NULL){			
		glLoadIdentity();	
		if(_texVertName == -1 || tn == NULL){		
			if(tn != NULL){
				*tn = -1;
				*tv = -1;
			}		
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glTranslatef(offset[X], offset[Y], 0);
			
			image->draw(step);		
		}
		else{
			image->draw(step, tn);
			
		if(_texVertName != *tv){
				*tc = _texCoordName;
				glBindBuffer(GL_ARRAY_BUFFER, _texCoordName);
				glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				
				*tv = _texVertName;												
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
	image->buildBuffers(texVert, texCoord);
	
	for(GLshort i = texVert.size() - 8; i < texVert.size(); i += 2){
		texVert[i] += offset[X] + 0.5;
		texVert[i + 1] += offset[Y] + 0.5;			
	}		
}

