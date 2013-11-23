/*
 *  ImageSet.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/22/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ImageSet.h"

#include "Image.h"


void ImageSet::addImage(Image* img)
{
	_image.push_back(img);
}

//void ImageSet::addAnimation(GLshort ad, GLshort st, GLshort si)
void ImageSet::addAnimation(const AnimDesc& ad, GLshort st, GLshort si)
{
	_anim[ad] = Animation(&_image, st, si);
	//_anim.push_back(Animation(&_image, st, si));
}

//Image* ImageSet::getNextImage(GLshort ad, GLshort& animPos)
/*
Image* ImageSet::getNextImage(const AnimDesc& ad, GLshort& animPos)
{
	if(_anim.size() == 0)
		return _image[0];
	
	printf("Using animation for %i %i\n", ad._prop[0], ad._prop[1]);
	
	return _anim[ad].getNextImage(animPos);
}
*/

Animation* ImageSet::getAnimation(const AnimDesc& ad)
{
	return &_anim[ad];
}