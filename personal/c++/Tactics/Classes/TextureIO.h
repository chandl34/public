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


//Image* loadPVRTC(const string&, GLshort, GLshort);
Image* loadPNG(const string&, const Size2d<GLshort>&, const Coord2d<double>& = Coord2d<double>(0, 0));
vector<Image*> loadPNG(const string&);

#endif
