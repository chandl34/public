/*
 *  StringIcon.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/31/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "StringIcon.h"

#include "Icon.h"
#include "Image.h"

#include "ImageStorage.h"


StringIcon::StringIcon(const string& str, const Coord2d<double>& os, GLshort a)
: ComplexIcon(NULL, os)
, _alignPoint(os)
{
	_align = a;
	setString(str);
}

StringIcon::~StringIcon()
{

}


//--- GENERAL ---//
void StringIcon::setString(const string& str)
{
	clear();
	
	if(_align == ALIGN_LEFT)
		_offset[X] = _alignPoint[X];
	else{
		GLshort width = 0;
		for(GLshort i = 0; i < str.size(); ++i)
			width += ImageStorage::getFontImage(str[i])->getSize(X);
		
		if(_align == ALIGN_RIGHT)
			_offset[X] = _alignPoint[X] - width;
		else	// else, Centered
			_offset[X] = _alignPoint[X] - width / 2.0;
	}
	
	_image = ImageStorage::getFontImage(str[0]);
	Coord2d<double> os(_image->getSize(X), 0.0);	
	
	for(GLshort i = 1; i < str.size(); ++i){
		addIcon(ImageStorage::getFontImage(str[i]), os);
		os[X] += _overlay[i - 1].getSize(X);
	}
}
