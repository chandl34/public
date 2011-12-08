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
public:
	static SideObject* create(const ObjType&, const Side&, GLshort, const HP&);
	virtual ~SideObject();
	
	//--- GENERAL ---//
	const Side& getSide() const;
		
protected:
	SideObject(const ObjType&, const Side&, GLshort, const HP&);
	
	//--- GENERAL ---//
	Side side;	
};

#endif
