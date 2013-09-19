/*
 *  DoorObject.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DOOR_OBJECT_H_
#define DOOR_OBJECT_H_

#include "SideObject.h"


class DoorObject : public SideObject{
protected:
	DoorObject(const ObjType&, 
				  const Side&, 
				  const Inner&, const Hinge&, 
				  GLshort);
	
public:
	static DoorObject* create(const ObjType&, 
									  const Side&, 
									  const Inner&, const Hinge&, 
									  GLshort);
	virtual ~DoorObject();
		
	//--- GENERAL ---//
	GLshort getModelType() const;
	GLshort isInner() const;
	GLshort getHinge() const;
	GLshort isOpen() const;
	
	void toggleDoor();
	
protected:
	//--- GENERAL ---//
	Inner inner;
	Hinge hinge;
	Open open;
};

#endif
