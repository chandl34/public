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

#include "Include.h"

class Image;


class ImageStorage{
public:
	~ImageStorage();
	
	//--- VERTS ---//
	static GLshort* getBoxVerts(const Size2d<GLshort>&);
	static GLshort* getVerts(const Size2d<GLshort>&);
	static GLfloat* getTexCoords(const Coord2d<GLfloat>&);
	static GLfloat* getTexCoords(const Coord2d<GLfloat>&, const Coord2d<GLfloat>&);
	
	//--- IMAGEs ---//
	static void addImage(Image*);	// todo: remove static later
	Image* getImage(GLshort);	
	
	// Objects
	void addConstImage(const ObjType&, Image*);
	static Image* getConstImage(const ObjType&, GLshort);
	
	void addSideImage(const ObjType&, const Side&, Image*);
	static Image* getSideImage(const ObjType&, const Side&, GLshort);
	
	void addRotateImage(const ObjType&, const Dir&, Image*);
	static Image* getRotateImage(const ObjType&, const Dir&, GLshort);
	
	void addDoorImage(const ObjType&, const Side&, const Inner&, const Hinge&, const Open&, Image*);
	static Image* getDoorImage(const ObjType&, const Side&, const Inner&, const Hinge&, const Open&, GLshort);
	
	// UI
	void setCursorImage(GLshort, Image*);	
	static Image* getCursorImage(GLshort);
	
private:
	static GLuint maxTexName;
	
	//--- VERTS ---//
	static vector<GLshort*> verts;
	static vector<GLfloat*> texCoords;
	
	//--- IMAGEs ---//
	static vector<Image*> image;	// NOTE: this is where all images are deleted.  Other containers are just references.
	
	// Objects
	static vector<Image*> constImage[CONST_MODELS];
	static vector<Image*> sideImage[SIDE_MODELS][2];
	static vector<Image*> doorImage[DOOR_MODELS][2][2][2][2];
	
	// UI
	static Image* cursor[CURSOR_MODES];
};

#endif
