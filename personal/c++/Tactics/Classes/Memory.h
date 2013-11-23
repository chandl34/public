/*
 *  Memory.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "Include.h"

class GridBlock;
class Memory;
class Unit;


typedef map<Unit*, Memory> MemoryMap;
const GLshort MEMORY_MOD = 2;				// How much further away a remembered enemy must be to be prioritized for searches
const GLshort MEMORY_DURATION = 2;			// How long a memory stays in memory (in turns)


class Memory{
public:
	Memory(GridBlock* = NULL, GLshort = MEMORY_DURATION);	
	
	//--- GENERAL ---//
	GridBlock* getBlock();
	GLshort getTimer();
	
	bool tick();
	
private:
	//--- GENERAL ---//
	GridBlock* _oldBlock;
	GLshort _timer;
};

#endif