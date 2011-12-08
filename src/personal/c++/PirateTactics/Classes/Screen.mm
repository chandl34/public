/*
 *  Screen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Screen.h"


Screen::Screen(){}

Screen::~Screen(){}


void Screen::resetView(GLshort zoom){	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();		
	glOrthof(0, VIEW_SIZE[zoom][Y], 
			 0, VIEW_SIZE[zoom][X], 
			 -1.0f, 1.0f);
	glRotatef(-90.0f, 0, 0, 1.0f);	
	glTranslatef(-VIEW_SIZE[zoom][X], 0, 0);
}