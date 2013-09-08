/*
 *  Color.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "Include.h"


const GLshort COLORS = 4;
enum{R, G, B, A};


class Color{
public:
	Color(GLfloat = 1.0f, GLfloat = 1.0f, GLfloat = 1.0f, GLfloat = 1.0f);
	
	GLfloat& operator[](GLshort);
	const GLfloat& operator[](GLshort) const;
	
private:
	GLfloat _val[COLORS];
};

bool operator==(const Color&, const Color&);

#endif
