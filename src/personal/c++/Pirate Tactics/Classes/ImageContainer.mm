/*
 *  ImageContainer.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ImageContainer.h"


vector<Image*> ImageContainer::image;
vector<GLshort*> ImageContainer::verts;
vector<GLfloat*> ImageContainer::texCoords;

ImageContainer::ImageContainer(){
}

ImageContainer::~ImageContainer(){
	for(int i = 0; i < image.size(); i++)
		delete image[i];
		
	for(int i = 0; i < verts.size(); i++)
		delete [] verts[i];
	
	for(int i = 0; i < texCoords.size(); i++)
		delete [] texCoords[i];
}


void ImageContainer::addImage(Image* img){
	image.push_back(img);
}


Image* ImageContainer::getImage(GLshort i){
	return image[i];
}

GLshort* ImageContainer::getVerts(GLshort x, GLshort y){
	for(int i = 0; i < verts.size(); i++){
		if(verts[i][4] == x && verts[i][5] == y)
			return verts[i];		
	}
	
	GLshort* newVerts = new GLshort[8];
	newVerts[0] = x;	newVerts[1] = 0;
	newVerts[2] = 0;	newVerts[3] = 0;
	newVerts[4] = x;	newVerts[5] = y;
	newVerts[6] = 0;	newVerts[7] = y;
	verts.push_back(newVerts);
			
	return newVerts;
}

GLfloat* ImageContainer::getTexCoords(GLfloat x, GLfloat y){
	for(int i = 0; i < texCoords.size(); i++){
		if(texCoords[i][4] == x && texCoords[i][5] == y)
			return texCoords[i];		
	}
	
	GLfloat* newTexCoords = new GLfloat[8];
	newTexCoords[0] = x;	newTexCoords[1] = 1.0f;
	newTexCoords[2] = 0;	newTexCoords[3] = 1.0f;
	newTexCoords[4] = x;	newTexCoords[5] = y;
	newTexCoords[6] = 0;	newTexCoords[7] = y;
	texCoords.push_back(newTexCoords);
		
	return newTexCoords;
}
/*


80.0f/128.0f, 24.0f/64.0f,
0, 24.0f/64.0f,
80.0f/128.0f, 1.0f,
0, 1.0f
*/