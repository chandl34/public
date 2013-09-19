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

// Objects
vector<Image*> ImageStorage::constImage[CONST_MODELS];
vector<Image*> ImageStorage::sideImage[SIDE_MODELS][2];
vector<Image*> ImageStorage::doorImage[DOOR_MODELS][2][2][2][2];

// UI
Image* ImageStorage::cursor[CURSOR_MODES];



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

GLfloat* ImageStorage::getTexCoords(const Coord2d<GLfloat>& tr){
	return getTexCoords(Coord2d<GLfloat>(0.0f, 0.0f), tr);
}

GLfloat* ImageStorage::getTexCoords(const Coord2d<GLfloat>& bl, const Coord2d<GLfloat>& tr){	
	for(int i = 0; i < texCoords.size(); ++i){
		if(compare(texCoords[i][4], tr[X]) == 0 && compare(texCoords[i][5], tr[Y]) == 0){
			if(compare(texCoords[i][2], bl[X]) == 0 && compare(texCoords[i][3], bl[Y]) == 0)
				return texCoords[i];
		}
	}
		
	GLfloat* newTexCoords = new GLfloat[8];
	newTexCoords[0] = tr[X];	newTexCoords[1] = bl[Y];
	newTexCoords[2] = bl[X];	newTexCoords[3] = bl[Y];
	newTexCoords[4] = tr[X];	newTexCoords[5] = tr[Y];
	newTexCoords[6] = bl[X];	newTexCoords[7] = tr[Y];
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


// Objects
void ImageStorage::addConstImage(const ObjType& ot, Image* img){
	addImage(img);
	constImage[ot].push_back(img);
}

Image* ImageStorage::getConstImage(const ObjType& ot, GLshort is){
	return constImage[ot][is];
}

void ImageStorage::addSideImage(const ObjType& ot, const Side& si, Image* img){
	addImage(img);
	sideImage[ot][si].push_back(img);
}

Image* ImageStorage::getSideImage(const ObjType& ot, const Side& si, GLshort is){
	return sideImage[ot][si][is];
}

void ImageStorage::addDoorImage(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, const Open& op, Image* img){
	addImage(img);
	doorImage[ot][si][inn][hin][op].push_back(img);
}

Image* ImageStorage::getDoorImage(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, const Open& op, GLshort is){
	return doorImage[ot][si][inn][hin][op][is];
}


// UI
void ImageStorage::setCursorImage(GLshort i, Image* img){
	addImage(img);
	cursor[i] = img;
}

Image* ImageStorage::getCursorImage(GLshort i){
	return cursor[i];
}
