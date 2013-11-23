/*
 *  ThrownItem.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef THROWN_ITEM_H_
#define THROWN_ITEM_H_

#include "Projectile.h"


class ThrownItem : public Projectile{
protected:
	ThrownItem(const ObjType&, GLshort, 
			   const HP&, 
			   const Vertex&, const Vertex&,
			   bool, 
			   Item*, double);
	friend class Projectile;
	
public:
	//--- GENERAL ---//
	GLshort update();
	
protected:
	//--- GENERAL ---//
	void dealDamage(Hit&);
};

#endif 

