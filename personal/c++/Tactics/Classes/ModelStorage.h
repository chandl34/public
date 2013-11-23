/*
 *  ModelStorage.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MODEL_STORAGE_H_
#define MODEL_STORAGE_H_

#include "Include.h"

class Model;


class ModelStorage{
public:
	~ModelStorage();
	
	// ConstObject
	static Model* getConstModel(const ObjType&);	
	void setConstModel(const ObjType&, Model*);
	
	// SideObject
	static Model* getSideModel(const ObjType&, const Side&);	
	void setSideModel(const ObjType&, Model*);
	
	// RotateObject
	static Model* getRotateModel(const ObjType&, bool, const Dir&);	
	void setRotateModel(const ObjType&, bool, Model*);
	
	// DoorObject	
	static Model* getDoorModel(const ObjType&, const Side&, const Inner&, const Hinge&, const Open&);	
	void setDoorModel(const ObjType&, Model*);
		
private:
	static Model* constModel[CONST_MODELS]; 
	static Model* sideModel[SIDE_MODELS][2]; 		
	static Model* rotateModel[ROTATE_MODELS][STANCES][PATH_DIRS]; 		
	static Model* doorModel[DOOR_MODELS][2][2][2][2]; 	
};

#endif
