/*
 *  Animation.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/22/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Include.h"

class Image;


class Animation{
public:
	Animation();
	Animation(vector<Image*>*, GLshort, GLshort);
	
	Image* getNextImage(GLshort&);	
	
private:
	vector<Image*>* _image;
	GLshort _start;
	GLshort _size;	
};


// Animation Description
enum{IDLE_ANIM, KNEEL_ANIM, MOVE_ANIM};

struct AnimDesc{
	explicit AnimDesc(GLshort = 0, GLshort = 0);		
	
	GLshort _prop[2];
};

bool operator<(const AnimDesc&, const AnimDesc&);

#endif