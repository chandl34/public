/*
 *  Controls.h
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "Touchable.h"


class Controls : public Touchable{
public:
	Controls(bool);
	virtual ~Controls();
	
	virtual void keyDown(GLshort) = 0;	
};

#endif