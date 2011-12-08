/*
 *  Touchable.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Touchable.h"

Touchable::Touchable(){}

Touchable::~Touchable(){}

bool Touchable::isMultiTouchable(){
	return multiTouchable;
}

bool Touchable::push(GLshort, const Coord2d<GLshort>&){
	cout << "Warning: improper use of a single-touchable class" << endl;
	return false;
}


void Touchable::move(GLshort, const Coord2d<GLshort>&){
	cout << "Warning: improper use of a single-touchable class" << endl;
}

void Touchable::release(GLshort, const Coord2d<GLshort>&){
	cout << "Warning: improper use of a single-touchable class" << endl;
}
