/*
 *  GridBlockProjectile.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlock.h"
#include "Camera.h"


Object* GridBlock::detectHit(const Ray& r, GLfloat& t, bool ignore) const{	
	Object* o = NULL;
	
	if(ground->detectHit(r, t))
		o = ground;
	
	for(GLshort i = 0; i < object.size(); i++){
		if(object[i]->detectHit(r, t))
			o = object[i];
	}
		
	if(door != NULL && (door->isInner() || !door->isOpen())){
		if(door->detectHit(r, t))
			o = door;
	}		
	
	if(visitingDoor != NULL){
		if(visitingDoor->detectHit(r, t))
			o = visitingDoor;
	}
		
	if(unit != NULL && !ignore){
		if(unit->detectHit(r, t))
			o = unit;
	}
	
	return o;
}
