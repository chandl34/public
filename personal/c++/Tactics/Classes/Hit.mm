/*
 *  Hit.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Hit.h"

#include "Object.h"


Hit::Hit()
{
	_objHit = NULL;
	_sectionHit = -1;
	_timeLeft = -1.0;
}

void Hit::setObjectHit(Object* oh)
{
	_objHit = oh;
}

Object* Hit::getObjectHit()
{
	return _objHit;
}

void Hit::setSectionHit(GLshort sh)
{
	_sectionHit = sh;
}

GLshort Hit::getSectionHit()
{
	return _sectionHit;
}

void Hit::setTimeLeft(double th)
{
	_timeLeft = th;
}

double Hit::getTimeLeft()
{
	return _timeLeft;
}
