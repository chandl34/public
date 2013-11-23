/*
 *  AnimationSet.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/22/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "AnimationSet.h"

#include "ImageSet.h"


AnimationSet::AnimationSet(ImageSet* img)
{
	_imageSet = img;
	_animPos = 0;
}


//void AnimationSet::setAnimation(GLshort ad)
void AnimationSet::setAnimation(const AnimDesc& ad)
{
	_sAnim = _imageSet->getAnimation(ad);
	
	//printf("Setting animation to %i %i\n", ad._prop[0], ad._prop[1]);
	//cout << ad._prop[0] << ", " << ad._prop[1] << endl;
	
	_animPos = 0;
}

Image* AnimationSet::getNextImage()
{
	return _sAnim->getNextImage(_animPos);//_imageSet->getNextImage(_sAnim, _animPos);
}
