/*
 *  Projectile.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "Object.h"

#include "Hit.h"

class Item;


const double PIXELS_PER_METER = 40;			// 1 pixel = 1 inch... 40 inch ~ 1 meter
const double METERS_PER_SECOND = FRAMES_PER_SECOND / PIXELS_PER_METER;
const double GRAVITY = 9.8; // 4.9 meters are travelled downwards after falling from rest
const double GRAVITY_MOD = -0.5 * GRAVITY * PIXELS_PER_METER / FRAMES_PER_SECOND / FRAMES_PER_SECOND;


class Projectile : public Object{
protected:
	Projectile(const ObjType&, GLshort, 
			   const HP&, 
			   const Vertex&, const Vertex&,
			   bool, 
			   Item*, double);
	
public:
	static Projectile* create(const ObjType&, GLshort, 
							  const HP&, 
							  const Vertex&, const Vertex&,
							  bool, 
							  Item*, double);
	virtual ~Projectile();	
	
	//--- GENERAL ---//
	virtual GLshort update();
	
	Object* getObjectHit();
	GLshort getSectionHit();
	
	bool isDynamic() const;
	
protected:
	//--- GENERAL ---//
	Item* _item;
	list<Hit> _hit;
	double _gravity;
	Coord2d<double> _prevOffset;
	
	virtual void dealDamage(Hit&) = 0;
};

#endif 

