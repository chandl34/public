/*
 *  ObjectScreen.cpp
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ObjectScreen.h"

#include "DoorObject.h"
#include "Object.h"
#include "SideObject.h"


ObjectScreen::ObjectScreen()
: BaseScreen(true)
{
	sObjectType = WINDOW_S;
	objSide = LEFT_SIDE;
	resort = true;
}

ObjectScreen::~ObjectScreen()
{
	
}


//---- DRAW ----//
void ObjectScreen::draw(bool step)
{
	if(resort){
		resort = false;
		for(GLshort i = 0; i < OBJECT_OPTIONS; i++)
			objList[i].clear();
		
		Object* o;
		GLshort coord[] = {30, -30};
		
		// Ground
		objList[GROUND_S].clear();
		o = Object::create(ObjType(GROUND), objIndex[GROUND_S]);
		objList[GROUND_S].push_back(o);	
		o->setCoord3D(coord[X] + 40, 
						  coord[Y] + 40, 
						  0);
		o->isoSort(objList[GROUND_S]);		
		
		// Wall
		objList[WALL_S].clear();
		o = SideObject::create(ObjType(WALL), Side(objSide), objIndex[WALL_S]);
		objList[WALL_S].push_back(o);	
		o->setCoord3D(coord[X] + 160 * WALL_S, 
						  coord[Y] + 160 * WALL_S, 
						  0);		
		o->isoSort(objList[WALL_S]);	
	
		// WindowFrame
		objList[WINDOW_S].clear();
		for(GLshort i = 1; i < SIDE_MODELS; i++){
			o = SideObject::create(ObjType(i), Side(objSide), objIndex[WINDOW_S]);
			objList[WINDOW_S].push_back(o);	
			o->setCoord3D(coord[X] + 160 * WINDOW_S, 
							  coord[Y] + 160 * WINDOW_S, 
							  0);			
			o->isoSort(objList[WINDOW_S]);	
		}
		
		// Door
		objList[DOOR_S].clear();
		
		o = SideObject::create(ObjType(SIDE_FRAME), Side(objSide), objIndex[DOOR_S]);
		objList[DOOR_S].push_back(o);	
		o->setCoord3D(coord[X] + 160 * DOOR_S, 
						  coord[Y] + 160 * DOOR_S, 
						  0);	
		
		o = DoorObject::create(ObjType(DOOR), Side(objSide),
									  Inner(objInner), Hinge(objHinge),
									  objIndex[DOOR_S]);		
		objList[DOOR_S].push_back(o);
		o->setCoord3D(coord[X] + 160 * DOOR_S, 
						  coord[Y] + 160 * DOOR_S, 
						  0);		
		if(objOpen)
			((DoorObject*)o)->toggleDoor();
		
		o = SideObject::create(ObjType(FRONT_FRAME), Side(objSide), objIndex[DOOR_S]);
		objList[DOOR_S].push_back(o);	
		o->setCoord3D(coord[X] + 160 * DOOR_S, 
						  coord[Y] + 160 * DOOR_S, 
						  0);	
		
		o = SideObject::create(ObjType(TOP_FRAME), Side(objSide), objIndex[DOOR_S]);
		objList[DOOR_S].push_back(o);	
		o->setCoord3D(coord[X] + 160 * DOOR_S, 
						  coord[Y] + 160 * DOOR_S, 
						  0);	
	}
	
	glMatrixMode(GL_PROJECTION);	
	glTranslatef(-MAP_OFFSET[X], -MAP_OFFSET[Y], 0);
	glMatrixMode(GL_MODELVIEW);	
	
	for(GLshort i = 0; i < OBJECT_OPTIONS; i++){
		if(i != sObjectType)
			glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
		else
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		for(ObjectList::iterator iter = objList[i].begin(); iter != objList[i].end(); ++iter)
			(*iter)->draw(step);
	}
}
