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

#include "Include.h"

class GridBlock;
class Hit;
class Ray;
class Tri;
class Vertex;

		
//----- 2D -----//
bool pointInQuad(const Coord2d<GLshort>&, const Coord2d<double>&, const Size2d<GLshort>&);

//----- 3D -----//
bool rayInTri(const Ray&, const Tri&, const Vertex&, Hit&);

//----- RAY -----//
void testFlight(Ray, Hit&, double, bool);

#endif
