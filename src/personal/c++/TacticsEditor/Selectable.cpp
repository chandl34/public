/*
 *  Selectable.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Selectable.h"


Selectable::Selectable() : Touchable(false){
	selected = -1;
}

Selectable::~Selectable(){}


//--- GENERAL ---//
GLshort Selectable::getSelected() const{
	return selected;
}
