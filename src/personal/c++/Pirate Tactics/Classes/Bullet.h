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

#include "RotateObject.h"
#include "GridBlock.h"

class Bullet : public RotateObject{
public:
	static Bullet* create(const ObjType&, const Dir&, GLshort, 
						  const HP&, 
						  const Object*, const Object*);
	virtual ~Bullet();	
	
	//--- GENERAL ---//
	GLshort update();
	
protected:
	Bullet(const ObjType&, const Dir&, GLshort, 
		   const HP&, 
		   const Object*, const Object*);
	
	//--- GENERAL ---//
	GLfloat lifespan;
	Object* hit;
};

#endif 
