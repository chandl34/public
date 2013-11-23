/*
 *  Selectable.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef SELECTABLE_H_
#define SELECTABLE_H_

#include "Touchable.h"

class Button;
class Image;


class Selectable : public Touchable{
public:
	Selectable();
	virtual ~Selectable();
	
	//--- GENERAL ---//
	GLshort getSelected() const;
	
	virtual Button* getButton(GLshort = 0) = 0;
	
protected:
	GLshort selected;
};

#endif
