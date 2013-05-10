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
vector<ImageSet> ImageStorage::imageSet;

// Background
vector<Image*> ImageStorage::bgImage;

// Objects
vector<Image*> ImageStorage::constImage[CONST_MODELS];
vector<Image*> ImageStorage::sideImage[SIDE_MODELS][2];
vector<Image*> ImageStorage::rotateImage[ROTATE_MODELS][PATH_DIRS];
vector<Image*> ImageStorage::doorImage[DOOR_MODELS][2][2][2][2];

// UI
Image* ImageStorage::character[CHARACTERS];
Image* ImageStorage::itemSlot[ITEM_SLOT_SIZES];
Image* ImageStorage::cursor[UNIT_MODES];
Image* ImageStorage::footstep[PATH_DIRS];
Image* ImageStorage::sightIndicator[LOS_LEVELS];
Image* ImageStorage::uiImage[UI_IMAGES];


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


// ImageSet
ImageSet* ImageStorage::addImageSet(){
	imageSet.push_back(ImageSet());
	return &imageSet[imageSet.size() - 1];
}

ImageSet* ImageStorage::getImageSet(GLshort is){
	return &imageSet[is];
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


// Objects
void ImageStorage::addConstImage(const ObjType& ot, Image* img){
	//addImage(img);
	constImage[ot].push_back(img);
}

Image* ImageStorage::getConstImage(const ObjType& ot, GLshort is){
	return constImage[ot][is];
}

void ImageStorage::addSideImage(const ObjType& ot, const Side& si, Image* img){
	//addImage(img);
	sideImage[ot][si].push_back(img);
}

Image* ImageStorage::getSideImage(const ObjType& ot, const Side& si, GLshort is){
	return sideImage[ot][si][is];
}

void ImageStorage::addRotateImage(const ObjType& ot, const Dir& dir, Image* img){
	//addImage(img);
	rotateImage[ot][dir].push_back(img);
}

Image* ImageStorage::getRotateImage(const ObjType& ot, const Dir& dir, GLshort is){
	return rotateImage[ot][dir][is];
}

void ImageStorage::addDoorImage(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, const Open& op, Image* img){
	//addImage(img);
	doorImage[ot][si][inn][hin][op].push_back(img);
}

Image* ImageStorage::getDoorImage(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, const Open& op, GLshort is){
	return doorImage[ot][si][inn][hin][op][is];
}


// UI
void ImageStorage::setFontImage(GLshort i, Image* img){
	//addImage(img);
	character[i] = img;
}

Image* ImageStorage::getFontImage(char ch){
	return character[ch - CHAR_OFFSET];
}

void ImageStorage::setItemSlotImage(GLshort i, Image* img){
	//addImage(img);
	itemSlot[i] = img;
}

Image* ImageStorage::getItemSlotImage(GLshort i){
	return itemSlot[i];
}

void ImageStorage::setCursorImage(GLshort i, Image* img){
	//addImage(img);
	cursor[i] = img;
}

Image* ImageStorage::getCursorImage(GLshort i){
	return cursor[i];
}

void ImageStorage::setFootstepImage(GLshort i, Image* img){
	//addImage(img);
	footstep[i] = img;	
}

Image* ImageStorage::getFootstepImage(GLshort i){
	return footstep[i];
}

void ImageStorage::setSightIndicatorImage(GLshort i, Image* img){
	//addImage(img);
	sightIndicator[i] = img;
}

Image* ImageStorage::getSightIndicatorImage(GLshort i){
	return sightIndicator[i];
}

void ImageStorage::setUIImage(GLshort i, Image* img)
{
	uiImage[i] = img;
}

Image* ImageStorage::getUIImage(GLshort i)
{
	return uiImage[i];
}

