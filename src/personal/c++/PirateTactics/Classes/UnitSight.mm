/*
 *  UnitSight.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"
#include "GridBlock.h"


bool Unit::hasBeenSeen(){
	return beenSeen;
}

bool Unit::canSee(const Unit* u) const{
	if(getSightAngle(u->getBlock()) > M_PI_2 + 0.00001f)	// seeing in a 180 degree arc -- possibly allow for more angles at varying lengths later
		return false;
		
	GLfloat t;
	Ray tRay(u, this);
	tRay.normalize();	
	return tRay.testFlight(t) == u;
}


GLfloat Unit::getSightAngle(GridBlock* t) const{
	GLfloat x = t->getCoordPath(X) - currBlock->getCoordPath(X);
	GLfloat y = t->getCoordPath(Y) - currBlock->getCoordPath(Y);
	GLfloat size = sqrt(x*x + y*y);
	
	// if size > sightrange, return false
	
	Vector v1(x/size, y/size, 0);		// could change this later to be more efficient...
	
	return acos(v1.dot(UNIT_VECTOR[dir][X], UNIT_VECTOR[dir][Y], UNIT_VECTOR[dir][Z]));
}

GLshort Unit::look(){
	looking = false;
	
	GLshort oldDir = dir;		
	dir = (GLshort)(getSightAngle(goalBlock)/M_PI_4 + 0.5f + dir)%PATH_DIRS;		// First round finds the angle
	if((GLshort)(getSightAngle(goalBlock)/M_PI_4 + 0.5f + dir)%PATH_DIRS != dir)	// Second round sees if angle was CCW
		dir = (dir + PATH_DIRS - 2*(dir - oldDir))%PATH_DIRS;
	
	//printf("Looking\n");
	if(oldDir != dir)
		return UPDATE_SIGHT;
	
//	printf("same dir\n");
	// COULD RAISE GUN HERE
	return NO_CHANGE;
}

void Unit::updateSight(vector<Unit*>& unitList){
	GLshort i;
	Unit* u;
	
	// Test others' sight (done first, so enemies can get interrupts chance);
	for(i = 0; i < unitList.size(); i++){
		u = unitList[i];
		if(u->team != team){
			if(u->canSee(this)){
				if(!u->sees.count(this)){
					u->sees.insert(this);
					seenBy.insert(u);
				}				
				// INSERT CODE HERE FOR INTERRUPTS
			}
			else if(u->sees.count(this)){
				u->sees.erase(this);
				seenBy.erase(u);
			}			
		}
	}
		
	// Test this unit's sight
	for(i = 0; i < unitList.size(); i++){
		u = unitList[i];
		if(u->team != team){
			if(canSee(u)){				
				if(!sees.count(u)){	
					if(!u->beenSeen){
						u->beenSeen = true;
						stop();
					}
					sees.insert(u);
					u->seenBy.insert(this);		
				}
			}
			else if(sees.count(u)){
				sees.erase(u);
				u->seenBy.erase(this);
			}
		}
	}
	
}
