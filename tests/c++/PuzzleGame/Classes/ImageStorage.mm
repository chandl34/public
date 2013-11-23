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


GLuint ImageStorage::maxTexName;

vector<GLshort*> ImageStorage::verts;
vector<GLfloat*> ImageStorage::texCoords;

vector<Image*> ImageStorage::image;
vector<Image*> ImageStorage::bgImage;
vector<PieceMask> ImageStorage::_pMask;


ImageStorage::~ImageStorage()
{
	for(int i = 0; i < image.size(); ++i)
		delete image[i];
	
	for(int i = 0; i < verts.size(); ++i)
		delete [] verts[i];
	
	for(int i = 0; i < texCoords.size(); ++i)
		delete [] texCoords[i];
	
	for(GLuint i = 1; i < maxTexName; ++i)
		glDeleteTextures(1, &i);
}


//--- VERTS ---//
/*
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
 */
GLshort* ImageStorage::getVerts(const Size2d<GLshort>& ts)
{
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

GLfloat* ImageStorage::getTexCoords(const GLfloat* tc)
{
	for(int i = 0; i < texCoords.size(); ++i){
		for(GLshort j = 0; j < 8; ++j){
			if(texCoords[i][j] != tc[j])
				break;
			else if(j == 7)
				return texCoords[i];
		}
	}
	
	GLfloat* newTexCoords = new GLfloat[8];
	for(GLshort i = 0; i < 8; ++i)
		newTexCoords[i] = tc[i];
	
	texCoords.push_back(newTexCoords);
	return newTexCoords;
}


//--- IMAGEs ---//
void ImageStorage::addImage(Image* img)
{
	image.push_back(img);
	maxTexName = max(maxTexName, img->getTexName());
}

Image* ImageStorage::getImage(GLshort i)
{
	return image[i];
}

void ImageStorage::addBGImage(Image* img)
{
	bgImage.push_back(img);
}

Image* ImageStorage::getBGImage(GLshort i)
{
	return bgImage[i];
}

void ImageStorage::addMask(const PieceMask& pm)
{
	_pMask.push_back(pm);
}

Image* ImageStorage::getMask(const PieceEdges& pe, PieceFlip& pf, bool& r)
{
	for(GLshort i = 0; i < _pMask.size(); i++){
		if(_pMask[i].isMatch(pe, pf, r))
			return _pMask[i].getImage();
	}
	
	printf("ERROR: Could not find mask image!\n");
	//cout << "Piece needed is: " << pe[0][0] << " " << pe[1][0] << " " << pe[0][1] << " " << pe[1][1] << endl;
	return NULL;
}


