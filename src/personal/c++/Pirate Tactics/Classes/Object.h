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
#include "Model.h"
#include "Ray.h"
#include "Stat.h"


class Object : public Icon{
public:
	static Object* create(const ObjType&, GLshort, 
						  const HP&);
	virtual ~Object();	
	
	//--- GENERAL ---//
	void setCoord3D(GLfloat, GLfloat, GLfloat);
	GLfloat getCoord3D(GLshort) const;
	
	virtual bool isUnit();
	
	//-- HIT DETECTION --//
	bool detectHit(const Ray&, GLfloat&) const;
	
	//--- ISO SORTING ---//	
	GLfloat getRange(GLshort, GLshort) const;
	virtual void isoSort(list<Object*>&);
		
	//-- PATHING --//
	bool blocks(GLshort) const;
	virtual bool isMoving() const;
	
protected:
	Object(const ObjType&, GLshort, 
		   const HP&);
	
	//--- GENERAL ---//
	Model* model;	
	Ray ray;
	ObjType objectType;
	GLshort imageSet;	
	
	//--- STATS ---//	
	HP maxHP;
	HP currHP;
};

#endif 