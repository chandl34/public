/*
 *  Icon.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Icon.h"
#include "Camera.h"


Icon::Icon(Image* img) : offset(0, 0){	
	image = img;	
}

Icon::Icon(Image* img, const Coord2d<GLfloat>& os) : offset(os){
	image = img;
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

void Icon::setOffset(GLfloat x, GLfloat y){
	offset[X] = x;
	offset[Y] = y;
}

const Coord2d<GLfloat>& Icon::getOffset() const{
	return offset;
}

GLfloat Icon::getOffset(GLshort i) const{
	return offset[i];
}


//---- DRAW ----//
void Icon::draw(bool step){
	if(image != NULL){
		glLoadIdentity();
		glTranslatef(offset[X], offset[Y], 0);
		image->draw(step);
	}
}
