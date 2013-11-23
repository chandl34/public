/*
 *  BlockCursor.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 4/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BLOCK_CURSOR_H_
#define BLOCK_CURSOR_H_

#include "GridBlockOverlay.h"


class BlockCursor : public GridBlockOverlay{
public:
	BlockCursor();

	void setCursorMode(GLshort);
};

#endif
