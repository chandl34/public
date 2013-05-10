/*
 *  Cursor.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 4/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include "Icon.h"


class Cursor : public Icon{
public:
	Cursor();

	void setCursorMode(GLshort);
};

#endif
