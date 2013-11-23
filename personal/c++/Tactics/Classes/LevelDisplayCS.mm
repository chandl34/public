/*
 *  LevelDisplayCS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelDisplayCS.h"

#include "Level.h"


LevelDisplayCS::LevelDisplayCS(GLshort lx, GLshort rx, GLshort ty) 
: StatDisplay<Level>(lx, rx, ty)
{
	_prevLevel = NULL;
	
	GLshort y = _topY;
	
	_text.push_back(TextLine());
	_text[NAME_STR].addString(" ", Coord2d<double>(_centerX, y), CENTERED);
	y -= 10;
}


//--- GENERAL ---//	
void LevelDisplayCS::update(Level* sLevel)
{
	if(sLevel != _prevLevel)
		_text[NAME_STR].setString(sLevel->getName());
	
	_prevLevel = sLevel;		
}