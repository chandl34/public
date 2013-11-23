/*
 *  HitTest.h
 *  When Pirates Attack
 *
 *  Created by Jonathan Chandler on 2/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HIT_TEST_H_
#define HIT_TEST_H_

#include "Ray.h"
#include "Triangle.h"

//----- 2D -----//
bool pointInQuad(const Coord2d<GLshort>&, const Coord2d<GLfloat>&, const Size2d<GLshort>&);
	
//----- 3D -----//
bool rayInTriangle(const Ray&, const Vertex&, const Vertex&, const Vertex&, const Vertex&, GLfloat&);

#endif
