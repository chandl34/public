/*
 *  ImageStorage.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_STORAGE_H_
#define IMAGE_STORAGE_H_

//#include "ImageSet.h"
#include "Image.h"


class ImageStorage{
public:
	~ImageStorage();
	
	//--- VERTS ---//
//	static GLshort* getBoxVerts(const Size2d<GLshort>&);
	static GLshort* getVerts(const Size2d<GLshort>&);
//	static GLfloat* getTexCoords(const Coord2d<GLfloat>&);
	static GLfloat* getTexCoords(const Coord2d<GLfloat>&, const Coord2d<GLfloat>&);
	
	//--- IMAGEs ---//
	static void addImage(Image*);	// todo: remove static later
	static Image* getImage(GLshort);	
	
	static void addBGImage(Image*);
	static Image* getBGImage(GLshort);
	
	static void addItemImage(Image*);
	static Image* getItemImage(GLshort);
	
private:
	static GLuint maxTexName;
	
	//--- VERTS ---//
	static vector<GLshort*> verts;
	static vector<GLfloat*> texCoords;
	
	//--- IMAGEs ---//
	static vector<Image*> image;	
	static vector<Image*> bgImage;
	static vector<Image*> itemImage;

};

#endif
