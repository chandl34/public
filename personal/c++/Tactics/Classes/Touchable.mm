/*
 *  Touchable.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Touchable.h"

Touchable::Touchable(bool t){
	_multiTouchable = t;
}

Touchable::~Touchable(){}

bool Touchable::isMultiTouchable(){
	return _multiTouchable;
}
