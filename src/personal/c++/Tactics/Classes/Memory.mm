/*
 *  Memory.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Memory.h"

#include "GridBlock.h"


Memory::Memory(GridBlock* gb, GLshort t)
{
	_oldBlock = gb;
	_timer = t;
}


//--- GENERAL ---//
GridBlock* Memory::getBlock()
{
	return _oldBlock;	
}

GLshort Memory::getTimer()
{
	return _timer;
}

bool Memory::tick()
{
	--_timer;
	return _timer >= 0;
}