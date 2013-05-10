/*
 *  Tri.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 2/15/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Triangle.h"

#include "Vector.h"


Tri::~Tri(){
	
}


//--- GENERAL ---//
double Tri::getArea() const{
	Vector edge1(getVert(1), getVert(0));
	Vector edge2(getVert(2), getVert(0));
	Vector cprod(edge1, edge2);
	return cprod.size()*0.5;
}

// testing
void Tri::print() const{
	printf("Tri: \n");
	for(GLshort i = 0; i < 3; ++i)
		getVert(i).print();
}
