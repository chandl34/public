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

#include "ImageSet.h"

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
	
	// ImageSets
	ImageSet* addImageSet();
	static ImageSet* getImageSet(GLshort);
	
	// Backgrounds
	void addBGImage(Image*);
	static Image* getBGImage(GLshort);

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
	void setFontImage(GLshort, Image*);
	static Image* getFontImage(char);
	
	void setItemSlotImage(GLshort, Image*);
	static Image* getItemSlotImage(GLshort);
	
	void setCursorImage(GLshort, Image*);	
	static Image* getCursorImage(GLshort);
	
	void setFootstepImage(GLshort, Image*);	
	static Image* getFootstepImage(GLshort);	
	
	void setSightIndicatorImage(GLshort, Image*);	
	static Image* getSightIndicatorImage(GLshort);
	
	void setUIImage(GLshort, Image*);
	static Image* getUIImage(GLshort);
	
private:
	static GLuint maxTexName;
	
	//--- VERTS ---//
	static vector<GLshort*> verts;
	static vector<GLfloat*> texCoords;
	
	//--- IMAGEs ---//
	static vector<Image*> image;	// NOTE: this is where all images are deleted.  Other containers are just references.
	static vector<ImageSet> imageSet;
	
	// Backgrounds
	static vector<Image*> bgImage;
	
	// Objects
	static vector<Image*> constImage[CONST_MODELS];
	static vector<Image*> sideImage[SIDE_MODELS][2];
	static vector<Image*> rotateImage[ROTATE_MODELS][PATH_DIRS];
	static vector<Image*> doorImage[DOOR_MODELS][2][2][2][2];
	
	// UI
	static Image* character[CHARACTERS];
	static Image* itemSlot[ITEM_SLOT_SIZES];	
	static Image* cursor[UNIT_MODES];
	static Image* footstep[PATH_DIRS];
	static Image* sightIndicator[LOS_LEVELS];
	static Image* uiImage[UI_IMAGES];
};

#endif
