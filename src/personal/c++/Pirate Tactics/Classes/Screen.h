/*
 *  Screen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "MultiTouchable.h"

class Screen : public MultiTouchable{
public:
	Screen();
	virtual ~Screen();
		
protected:
	void resetView(GLshort);
};

#endif
