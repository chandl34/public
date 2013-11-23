/*
 *  LevelDraw.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Level.h"

#include "Color.h"
#include "Faction.h"


//---- DRAW ----//
void Level::draw(bool step)
{
	GLfloat currColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currColor);
	
	if(_team[OWNER] != NULL){
		Faction* faction = _team[OWNER]->getFaction();
		const Color& factColor = faction->getColor();
		glColor4f(factColor[R], factColor[G], factColor[B], factColor[A]);
	}
	Icon::draw(step);
	glColor4f(currColor[R], currColor[G], currColor[B], currColor[A]);
}