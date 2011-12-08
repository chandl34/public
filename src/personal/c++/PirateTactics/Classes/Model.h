/*
 *  Model.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Triangle.h"
#include "Ray.h"


class Model{
public:
	Model();
	Model(const Model&);
	~Model();
	
	//--- GENERAL ---//
	void addTriangle(GLshort, GLshort, GLshort);
	void addVertex(Vertex*);
	
	//--- ISO SORTING ---//		
	void findRange();
	GLfloat getRange(GLshort, GLshort) const;
	
	//-- HIT DETECTION --//
	bool detectHit(const Ray&, const Vertex&, GLfloat&) const;	
		
	//--- MORPHS ---//
	void flip();	
	void shift(GLfloat, GLfloat);
	void rotateZ(GLfloat);
	
	//--- PATHING ---//
	bool blocks(GLshort) const;
	void addBlockedDir(GLshort);
	
private:	
	//--- GENERAL ---//
	vector<Triangle*> tri;
	vector<Vertex*> vert;	
	
	//--- ISO SORTING ---//	
	GLfloat range[3][3];
		
	//--- PATHING ---//
	vector<GLshort> block;
};

#endif
