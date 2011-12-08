/*
 *  ModelContainer.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MODEL_CONTAINER_H_
#define MODEL_CONTAINER_H_

#include "Model.h"
#include "Image.h"

class ModelContainer{
public:
	ModelContainer();
	~ModelContainer();
	
	// ConstObject
	static Image* getConstImage(GLshort, GLshort);
	static Model* getConstModel(GLshort);
	
	void addConstImage(GLshort, Image*);
	void setConstModel(GLshort, Model*);
	
	// SideObject
	static Image* getSideImage(GLshort, GLshort, GLshort);
	static Model* getSideModel(GLshort, GLshort);
	
	void addSideImage(GLshort, GLshort, Image*);
	void setSideModel(GLshort, Model*);
	
	// RotateObject
	static Image* getRotateImage(GLshort, GLshort, GLshort);
	static Model* getRotateModel(GLshort, GLshort);
	
	void addRotateImage(GLshort, GLshort, Image*);
	void setRotateModel(GLshort, Model*);
	
	// DoorObject	
	static Image* getDoorImage(GLshort, GLshort, GLshort, GLshort, GLshort, GLshort);
	static Model* getDoorModel(GLshort, GLshort, GLshort, GLshort, GLshort);
	
	void addDoorImage(GLshort, GLshort, GLshort, GLshort, GLshort, Image*);
	void setDoorModel(GLshort, Model*);
		
private:
	// ConstObject
	static vector<Image*> constImage[CONST_MODELS];
	static Model* constModel[CONST_MODELS]; 
	
	// SideObject
	static vector<Image*> sideImage[SIDE_MODELS][2];
	static Model* sideModel[SIDE_MODELS][2]; 	
	
	// RotateObject
	static vector<Image*> rotateImage[ROTATE_MODELS][PATH_DIRS];
	static Model* rotateModel[ROTATE_MODELS][PATH_DIRS]; 	
	
	// DoorObject
	static vector<Image*> doorImage[DOOR_MODELS][2][2][2][2];
	static Model* doorModel[DOOR_MODELS][2][2][2][2]; 	
};

#endif
