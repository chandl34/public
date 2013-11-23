/*
 *  Triangle.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Shape.h"

#include "Vertex.h"


class Tri : public Shape{	
public:
	virtual ~Tri();
	
	//--- GENERAL ---//
	virtual const Vertex& getVert(GLshort) const = 0;
	virtual Vertex& getVert(GLshort) = 0;
	
	double getArea() const;
		
	void print() const;
};							


class Triangle : public Tri{
public:
	Triangle(const Vertex&, const Vertex&, const Vertex&);
	
	//--- GENERAL ---//
	const Vertex& getVert(GLshort) const;
	Vertex& getVert(GLshort);
		
private:
	Vertex vert[3];
};


class IndexedTriangle : public Tri{
public:
	IndexedTriangle(const IndexedTriangle&, vector<Vertex>*);				// special copy constructor
	IndexedTriangle(GLshort, GLshort, GLshort, vector<Vertex>*);
	
	//--- GENERAL ---//
	const Vertex& getVert(GLshort) const;	
	Vertex& getVert(GLshort);
	
	//-- MORPH --//
	void flip();
	
private:	
	GLshort index[3];	
	vector<Vertex>* vert;	
};

#endif

