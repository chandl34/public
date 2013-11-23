/*
 *  SeqStep.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SeqStep.h"


SeqStep::SeqStep(GLshort steps)
{
	init = false;
	_steps = steps;
}

SeqStep::~SeqStep()
{
	
}


//--- GENERAL ---//
bool SeqStep::isFinished()
{
	return _steps <= 0;
}


