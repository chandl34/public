/*
 *  Color.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Color.h"


Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_val[R] = r;
	_val[G] = g;
	_val[B] = b;
	_val[A] = a;
}

GLfloat& Color::operator[](GLshort i)
{
	return _val[i];
}

const GLfloat& Color::operator[](GLshort i) const
{
	return _val[i];
}


bool operator==(const Color& lhs, const Color& rhs)
{
	for(GLshort i = 0; i < COLORS; ++i){
		if(lhs[i] != rhs[i])
			return false;
	}
	return true;
}