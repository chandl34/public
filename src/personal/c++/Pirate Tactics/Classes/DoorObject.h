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
public:
	static DoorObject* create(const ObjType&, const Side&, const Inner&, const Hinge&, GLshort, 
							  const HP&);
	virtual ~DoorObject();
		
	//--- GENERAL ---//
	bool isOpen() const;
	bool isInner() const;
	void toggleDoor();
		
protected:
	DoorObject(const ObjType&, const Side&, const Inner&, const Hinge&, GLshort, 
			   const HP&);
	
	//--- GENERAL ---//
	Inner inner;
	Hinge hinge;
	GLshort open;
};

#endif
