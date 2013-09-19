/*
 *  TextureIO.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef TEXTURE_IO_H_
#define TEXTURE_IO_H_

#include "Include.h"

class Image;


//Image* loadPVRTC(const char*, GLshort, GLshort);
Image* loadPNG(const char*, const Size2d<GLshort>&);
//vector<Image*> loadPNG(const char*);

#endif
