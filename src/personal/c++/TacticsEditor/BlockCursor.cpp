/*
 *  BlockCursor.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 4/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "BlockCursor.h"

#include "ImageStorage.h"


BlockCursor::BlockCursor() : GridBlockOverlay(NULL, NULL)
{
	
}

void BlockCursor::setCursorMode(GLshort i)
{
	setImage(ImageStorage::getCursorImage(i));
}
