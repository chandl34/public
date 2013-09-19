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
	SideObject(const ObjType&, const Side&, GLshort, const HP&);
	
public:
	static SideObject* create(const ObjType&, const Side&, GLshort, const HP& = HP(1));
	virtual ~SideObject();
	
	//--- GENERAL ---//	
	virtual GLshort getModelType() const;
	
	GLshort getSide() const;
	
	//---- DRAW ----//
	virtual void draw(bool, TexAttr* = NULL);
		
protected:
	//--- GENERAL ---//
	Side _side;	
};

#endif
