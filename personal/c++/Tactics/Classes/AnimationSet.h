/*
 *  AnimationSet.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/22/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ANIMATION_SET_H_
#define ANIMATION_SET_H_

#include "ImageSet.h"

class Image;


class AnimationSet{
public:
	AnimationSet(ImageSet*);
	
	//void setAnimation(GLshort);
	void setAnimation(const AnimDesc&);
	Image* getNextImage();
	
private:
	ImageSet* _imageSet;
	Animation* _sAnim;
	GLshort _animPos;
};

#endif
