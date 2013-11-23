/*
 *  ObjectScreenControls.cpp
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ObjectScreen.h"

#include "DoorObject.h"
#include "GridBlock.h"
#include "LevelMap.h"
#include "SideObject.h"


//--- CONTROLS ---//
void ObjectScreen::keyDown(GLshort k)
{
	GridBlock* sBlock = LevelMap::getSelectedBlock();
	
	switch(k){
		// Map movement
		case 'a':
			LevelMap::moveCursor(DOWN_LEFT);			
			break;
			
		case 's':
			LevelMap::moveCursor(DOWN_RIGHT);	
			break;
			
		case 'd':
			LevelMap::moveCursor(UP_RIGHT);	
			break;
			
		case 'w':
			LevelMap::moveCursor(UP_LEFT);	
			break;
			
		// Select Change
		case 'j':
			// do nothing yet, need to know size of the these containers
			break;
			
		case 'l':
			// do nothing yet, need to know size of the these containers
			break;
			
		case 'i':
			sObjectType = (sObjectType + 1) % OBJECT_OPTIONS;
			break;
			
		case 'k':
			sObjectType = (sObjectType - 1 + OBJECT_OPTIONS) % OBJECT_OPTIONS;
			break;
			
		// Object Changes
		case 'h':
			resort = true;
			objSide = (objSide + 1) % 2;
			break;
			
		case 'u':
			resort = true;
			objInner = (objInner + 1) % 2;
			break;
			
		case 'o':
			resort = true;
			objHinge = (objHinge + 1) % 2;
			break;
			
		case 'p':
			resort = true;
			objOpen = (objOpen + 1) % 2;
			break;
			
		// Clear
		case ';':
			LevelMap::refresh();
			sBlock->clearAll();
			break;
	}
	
	// Object Placement
	if(k == ' '){
		//printf("Adding object to sBlock\n");
		LevelMap::refresh();
		
		ObjectList:: iterator iter = objList[sObjectType].begin();
		if(sObjectType == GROUND_S)
			sBlock->setGround(new Object(**iter));	
		else{
			SideObject* so = (SideObject*)(*iter);
			sBlock->clearSide(so->getSide());
			
			for( ; iter != objList[sObjectType].end(); ++iter){
				if((*iter)->getModelType() == SIDE_MODEL){
					so = (SideObject*)(*iter);
					so = new SideObject(*so);
					sBlock->addObject(so);
				}
				else{
					DoorObject* dobj = (DoorObject*)(*iter);
					dobj = new DoorObject(*dobj);
					sBlock->setDoor(dobj);
					if(dobj->isOpen()){
						sBlock->toggleDoor();
						sBlock->toggleDoor();
					}
				}					
			}				
		}
	}
}

void ObjectScreen::push(GLshort t, const Coord2d<GLshort>& p)
{		
	sObjectType = p[Y] / (INFO_FRAME_SIZE[Y] / OBJECT_OPTIONS);
}

void ObjectScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	
}

bool ObjectScreen::release(GLshort t, const Coord2d<GLshort>& p)
{		
	
	return true;
}	


