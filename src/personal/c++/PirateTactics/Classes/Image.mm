/*
 *  Image.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"
#include "ImageContainer.h"
#include "Camera.h"


Image::Image(const Size2d<GLshort>& s, GLshort n) : size(s){
	//--- GENERAL ---//
	texName = n;
	vert = ImageContainer::getVerts(size[X], size[Y]);
	texCoord = ImageContainer::getTexCoords(1, 0);
}

Image::Image(const Size2d<GLshort>& s, const Size2d<GLshort>& rs, GLshort n) : size(rs){
	//--- GENERAL ---//
	texName = n;
	vert = ImageContainer::getVerts(rs[X], rs[Y]);
	texCoord = ImageContainer::getTexCoords(rs[X]/(GLfloat)s[X],
											(s[Y] - rs[Y])/(GLfloat)s[Y]);
}

Image::~Image(){
	
}


//--- GENERAL ---//
const Size2d<GLshort>& Image::getSize() const{
	return size;
}

GLshort Image::getSize(GLshort c) const{
	return size[c];
}


//---- DRAW ----//
void Image::draw(bool step){
	glBindTexture(GL_TEXTURE_2D, texName);	
	glVertexPointer(2, GL_SHORT, 0, vert);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
