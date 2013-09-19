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

#include "AnimationSet.h"
#include "Ray.h"

class Hit;
class Model;
class Object;


typedef list<Object*> ObjectList;


class Object : public Icon{
protected:
	Object(const ObjType&, GLshort, 
		   const HP&);
	
public:
	static Object* create(const ObjType&, GLshort, 
						  const HP& = HP(1));
	virtual ~Object();	
	
	//--- GENERAL ---//
	void setCoord3D(double, double, double);
	double getCoord3D(GLshort) const;
	
	virtual GLshort getModelType() const;
	GLshort getObjType() const;
	GLshort getIndex() const;
	
	virtual bool isUnit() const;
	virtual bool isDynamic() const;
	
	const Model& getModel() const;
	
	//--- ACTION ---//
	virtual GLshort update();	
	
	//--- COMBAT ---//
	virtual void takeDamage(GLshort, GLshort);
	
	//-- HIT DETECTION --//
	virtual bool detectHit(const Ray&, Hit&);
	
	//--- ISO SORTING ---//	
	virtual double getGlobalLoc(GLshort, const Dimension&, GLshort = -1) const;
	virtual void isoSort(ObjectList&);
	
	//-- PATHING --//
	bool blocks(GLshort) const;
	virtual bool isIdle() const;
	
	//--- STATS ---//
	GLshort getHP() const;
	void setHP(GLshort);
	GLshort getMaxHP() const;
	
protected:
	//--- GENERAL ---//
	Model* _model;	
	ObjType _objectType;
	GLshort _index;
	AnimationSet _animSet;
	GLshort _currAnim;
	Ray _ray;
	
	//--- STATS ---//	
	GLshort _maxHP;
	GLshort _currHP;
	
	void resetCoord3D();
};

#endif 