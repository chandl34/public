/*
 *  LevelDisplayCS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LEVEL_DISPLAY_C_S_
#define LEVEL_DISPLAY_C_S_

#include "StatDisplay.h"

class Level;


class LevelDisplayCS : public StatDisplay<Level>{
public:
	LevelDisplayCS(GLshort, GLshort, GLshort);	
	
	//--- GENERAL ---//	
	void update(Level*);
	
private:
	Level* _prevLevel;
	
	enum{NAME_STR};
};

#endif