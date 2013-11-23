/*
 *  Object.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Icon.h"

#include "Ray.h"

class Model;
class Object;


typedef list<Object*> ObjectList;


class Object : public Icon{
protected:
	Object(const ObjType&, GLshort);
	
public:
	static Object* create(const ObjType&, GLshort);
	virtual ~Object();	
	
	//--- GENERAL ---//
	void setCoord3D(double, double, double);
	double getCoord3D(GLshort) const;
	
	const Model& getModel() const;
	
	virtual GLshort getModelType() const;
	GLshort getObjType() const;
	
	GLshort getIndex() const;
	
	//---- DRAW ----//
	virtual void draw(bool, bool = false, GLuint* = NULL, GLuint* = NULL, GLuint* = NULL);
	
	//--- ISO SORTING ---//	
	virtual double getGlobalLoc(GLshort, const Dimension&, GLshort = -1) const;
	virtual void isoSort(ObjectList&);
	
protected:
	//--- GENERAL ---//
	Model* model;	
	ObjType objectType;
	Ray ray;
	GLshort index;
	
	void resetCoord3D();
};

#endif 