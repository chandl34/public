/*
 *  ImageSet.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/22/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_SET_H_
#define IMAGE_SET_H_

#include "Animation.h"

class Image;


class ImageSet{
public:	
	void addImage(Image*);	
	//void addAnimation(GLshort, GLshort, GLshort);
	void addAnimation(const AnimDesc&, GLshort, GLshort);
	
	//Image* getNextImage(GLshort, GLshort&);
	//Image* getNextImage(const AnimDesc&, GLshort&);
	Animation* getAnimation(const AnimDesc&);
	
private:
	vector<Image*> _image;
	//map<GLshort, Animation> _anim;
	map<AnimDesc, Animation> _anim;
};

#endif