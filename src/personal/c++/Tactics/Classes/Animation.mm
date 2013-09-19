/*
 *  Animation.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/22/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Animation.h"

#include "Image.h"


Animation::Animation()
{
	
}

Animation::Animation(vector<Image*>* img, GLshort st, GLshort si)
{
	_image = img;
	_start = st;
	_size = si;
}


Image* Animation::getNextImage(GLshort& animPos)
{
	Image* img = (*_image)[animPos + _start];
	animPos = (animPos + 1) % _size;	
	return img;
}


// Animation Description
AnimDesc::AnimDesc(GLshort p0, GLshort p1)
{
	_prop[0] = p0;
	_prop[1] = p1;
}

bool operator<(const AnimDesc& lhs, const AnimDesc& rhs)
{
	for(GLshort i = 0; i < 2; ++i){
		if(lhs._prop[i] < rhs._prop[i])
			return true;
		
		if(lhs._prop[i] > rhs._prop[i])
			return false;
	}
	
	return false;
}
