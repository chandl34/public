/*
 *  Bullet.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Projectile.h"


class Bullet : public Projectile{
protected:
	Bullet(const ObjType&, GLshort, 
		   const HP&, 
		   const Vertex&, const Vertex&,
		   bool, 
		   Item*, double);
	friend class Projectile;
	
	
	//--- GENERAL ---//
	void dealDamage(Hit&);
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);
};

#endif 
