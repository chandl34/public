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
#include "Vertex.h"

class Ray;
class Vector;


class Model{
public:		
	Model();
	Model(const Model&);
	
	//--- GENERAL ---//
	void addVertex(double, double, double);
	void addTriangle(GLshort, GLshort, GLshort);
	
	//--- ISO SORTING ---//		
	double getRelativeLoc(GLshort, const Dimension&);
	
	//--- MORPHS ---//
	void flip();	
	void shift(double x = 0.0, 
			   double y = 0.0, 
			   double z = 0.0);
	void rotateX(double);
	void rotateY(double);
	void rotateZ(double);
	
private:	
	//--- GENERAL ---//
	vector<Vertex> vert;	
	vector<IndexedTriangle> tri;
	
	//--- ISO SORTING ---//	
	double loc[3][3];
	bool dimensionsKnown;
	
	void findDimensions();	
};

#endif
