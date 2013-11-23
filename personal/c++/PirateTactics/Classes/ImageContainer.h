/*
 *  ImageContainer.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_CONTAINER_H_
#define IMAGE_CONTAINER_H_

#include "Image.h"


class ImageContainer{
public:
	ImageContainer();
	~ImageContainer();
	
	static void addImage(Image*);
	
	static Image* getImage(GLshort);
	
	static GLshort* getVerts(GLshort, GLshort);
	static GLfloat* getTexCoords(GLfloat, GLfloat);
	
private:
	static vector<Image*> image;
	static vector<GLshort*> verts;
	static vector<GLfloat*> texCoords;
};

#endif
