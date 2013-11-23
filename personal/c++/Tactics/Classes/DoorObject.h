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
				  const Side&, const Inner&, const Hinge&, GLshort, 
				  const HP&);
	
public:
	static DoorObject* create(const ObjType&, 
									  const Side&, const Inner&, const Hinge&, GLshort, 
									  const HP& = HP(1));
	virtual ~DoorObject();
	
	//--- GENERAL ---//
	virtual GLshort getModelType() const;
	
	bool isDynamic() const;
	
	bool isInner() const;
	GLshort getHinge() const;
	bool isOpen() const;
	
	void toggleDoor();
	
protected:
	friend class GridBlock;
	//--- GENERAL ---//
	Inner _inner;
	Hinge _hinge;
	Open _open;
};

#endif
