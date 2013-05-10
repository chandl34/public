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
protected:
	RotateObject(const ObjType&, const Dir&, GLshort, 
				 const HP& = HP(1));
	
public:
	virtual ~RotateObject();	
	
	//--- GENERAL ---//
	virtual GLshort getModelType() const;
	
	bool isDynamic() const;
	
	GLshort getDir() const;
	double getDir(GLshort) const;
	
protected:
	//--- GENERAL ---//
	GLshort _dir;
};

#endif
