/*
 *  RotateObject.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ROTATE_OBJECT_H_
#define ROTATE_OBJECT_H_

#include "Object.h"

class RotateObject : public Object{
public:
	virtual ~RotateObject();	
	
	//--- GENERAL ---//
	const Dir& getDir() const;
	GLfloat getDir(GLshort) const;

	virtual GLshort update() = 0;
		
protected:
	RotateObject(const ObjType&, const Dir&, GLshort, 
				 const HP&);
	
	//--- GENERAL ---//
	Dir dir;
};

#endif
