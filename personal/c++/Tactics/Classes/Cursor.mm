/*
 *  Cursor.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 4/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Cursor.h"

#include "ImageStorage.h"


Cursor::Cursor() 
: Icon(ImageStorage::getCursorImage(MOVE))
{
	setOffset(NULL);
}

void Cursor::setCursorMode(GLshort i)
{
	setImage(ImageStorage::getCursorImage(i));
}
