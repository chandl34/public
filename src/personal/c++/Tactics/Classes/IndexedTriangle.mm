/*
 *  IndexedTriangle.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 2/15/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Triangle.h"


IndexedTriangle::IndexedTriangle(const IndexedTriangle& tri, vector<Vertex>* v){
	for(GLshort i = 0; i < 3; ++i)
		index[i] = tri.index[i];
	
	vert = v;
}

IndexedTriangle::IndexedTriangle(GLshort v0, GLshort v1, GLshort v2, vector<Vertex>* v){
	index[0] = v0;
	index[1] = v1;
	index[2] = v2;
	
	vert = v;
}


//--- GENERAL ---//
const Vertex& IndexedTriangle::getVert(GLshort i) const{
	return vert->at(index[i]);
}

Vertex& IndexedTriangle::getVert(GLshort i){
	return vert->at(index[i]);
}


//-- MORPH --//
void IndexedTriangle::flip(){
	GLshort tmp1 = index[0];
	index[0] = index[1];
	index[1] = tmp1;
}
