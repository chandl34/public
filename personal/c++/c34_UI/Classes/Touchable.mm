/*
 *  Touchable.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Touchable.h"

Touchable::Touchable(bool mt){
//Touchable::Touchable(GLshort mt){
	_multiTouchable = mt;
	//_maxTouches = mt;
}

Touchable::~Touchable()
{

}


bool Touchable::isMultiTouchable() const
{
	return _multiTouchable;
}

/*
bool Touchable::isTouchable() const
{
	return _maxTouches > 0;
}

bool Touchable::isMultiTouchable() const
{
	return _maxTouches > 1;
}
 */
