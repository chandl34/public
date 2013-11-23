/*
 *  DataLOS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "DataLOS.h"


void DataLOS::add(GLshort v, GLshort los)
{
	if(los < DANGER_LEVELS)
		++_losData[v][los];
}

void DataLOS::remove(GLshort v, GLshort los)
{
	if(los < DANGER_LEVELS)
		--_losData[v][los];
}

GLshort DataLOS::get(GLshort v, GLshort los)
{
	if(los < DANGER_LEVELS)
		return _losData[v][los];
	return 0;
}