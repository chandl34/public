/*
 *  ImageStorage.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ImageStorage.h"

#include "Image.h"

#include "Math.h"


GLuint ImageStorage::maxTexName;

vector<GLshort*> ImageStorage::verts;
vector<GLfloat*> ImageStorage::texCoords;

vector<Image*> ImageStorage::image;

// Background
vector<Image*> ImageStorage::bgImage;


ImageStorage::~ImageStorage(){
	for(int i = 0; i < image.size(); ++i)
		delete image[i];
		
	for(int i = 0; i < verts.size(); ++i)
		delete [] verts[i];
	
	for(int i = 0; i < texCoords.size(); ++i)
		delete [] texCoords[i];
	
	for(GLuint i = 1; i < maxTexName; ++i)
		glDeleteTextures(1, &i);
}


GLshort* ImageStorage::getBoxVerts(const Size2d<GLshort>& rs){
	for(int i = 0; i < verts.size(); ++i){
		if(verts[i][4] == rs[X] && verts[i][5] == rs[Y])
			return verts[i];		
	}
	
	GLshort* newVerts = new GLshort[8];
	newVerts[0] = rs[X];	newVerts[1] = 0;
	newVerts[2] = 0;		newVerts[3] = 0;
	newVerts[4] = 0;		newVerts[5] = rs[Y];
	newVerts[6] = rs[X];	newVerts[7] = rs[Y];
	verts.push_back(newVerts);
	
	return newVerts;
}

GLshort* ImageStorage::getVerts(const Size2d<GLshort>& ts){
	for(int i = 0; i < verts.size(); ++i){
		if(verts[i][4] == ts[X] && verts[i][5] == ts[Y])
			return verts[i];		
	}
	
	GLshort* newVerts = new GLshort[8];
	newVerts[0] = ts[X];	newVerts[1] = 0;
	newVerts[2] = 0;		newVerts[3] = 0;
	newVerts[4] = ts[X];	newVerts[5] = ts[Y];
	newVerts[6] = 0;		newVerts[7] = ts[Y];
	verts.push_back(newVerts);
			
	return newVerts;
}

GLfloat* ImageStorage::getTexCoords(const Coord2d<GLfloat>& br){
	return getTexCoords(Coord2d<GLfloat>(0.0f, 1.0f), br);
}

GLfloat* ImageStorage::getTexCoords(const Coord2d<GLfloat>& tl, const Coord2d<GLfloat>& br){	
	for(int i = 0; i < texCoords.size(); ++i){
		if(compare(texCoords[i][4], br[X]) == 0 && compare(texCoords[i][5], br[Y]) == 0){
			if(compare(texCoords[i][2], tl[X]) == 0 && compare(texCoords[i][3], tl[Y]) == 0)
				return texCoords[i];
		}
	}
		
	GLfloat* newTexCoords = new GLfloat[8];
	newTexCoords[0] = br[X];	newTexCoords[1] = tl[Y];
	newTexCoords[2] = tl[X];	newTexCoords[3] = tl[Y];
	newTexCoords[4] = br[X];	newTexCoords[5] = br[Y];
	newTexCoords[6] = tl[X];	newTexCoords[7] = br[Y];
	texCoords.push_back(newTexCoords);
	
	return newTexCoords;
}


void ImageStorage::addImage(Image* img){
	image.push_back(img);
	maxTexName = max(maxTexName, img->getTexName());
}

Image* ImageStorage::getImage(GLshort i){
	return image[i];
}

// Backgrounds
void ImageStorage::addBGImage(Image* img)
{
	//addImage(img);
	bgImage.push_back(img);
}

Image* ImageStorage::getBGImage(GLshort i)
{
	return bgImage[i];
}

