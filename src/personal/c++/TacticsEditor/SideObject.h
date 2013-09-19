/*
 *  SideObject.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef SIDE_OBJECT_H_
#define SIDE_OBJECT_H_

#include "Object.h"


class SideObject : public Object{
protected:
	SideObject(const ObjType&, const Side&, GLshort);
	
public:
	static SideObject* create(const ObjType&, const Side&, GLshort);
	virtual ~SideObject();
	
	//--- GENERAL ---//	
	GLshort getModelType() const;
	GLshort getSide() const;
	
	//---- DRAW ----//
	virtual void draw(bool, bool = false, GLuint* = NULL, GLuint* = NULL, GLuint* = NULL);
		
protected:
	//--- GENERAL ---//
	Side side;	
};

#endif
