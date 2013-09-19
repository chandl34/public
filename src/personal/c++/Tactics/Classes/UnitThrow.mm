/*
 *  UnitThrow.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "Bullet.h"
#include "Grenade.h"
#include "GridBlock.h"
#include "Item.h"
#include "LevelMap.h"
#include "ThrownItem.h"

#include "Math.h"
#include "Options.h"


GridBlock* Unit::findThrowBlock()
{
	Item* item = getEquippedItem();
	// todo: use this item's weight to base max speed... add later
	
	Vertex origVert(getGlobalLoc(X, Dimension(MIDDLE), TORSO),
					getGlobalLoc(Y, Dimension(MIDDLE), TORSO),
					getGlobalLoc(Z, Dimension(MAXIMUM), TORSO));		
	
	const Object* targ = _goalBlock->getGround();
	Vertex targVert(targ->getGlobalLoc(X, Dimension(MIDDLE), _targetSection),
					targ->getGlobalLoc(Y, Dimension(MIDDLE), _targetSection),
					getGlobalLoc(Z, Dimension(MAXIMUM), TORSO));
	
	double cos0 = cos(degreeToRad(22.5));
	double sin0 = sin(degreeToRad(22.5));		
	double grav = GRAVITY * PIXELS_PER_METER;
	
	Vector toTarg(targVert, origVert);
	double dist = toTarg.size();
	double a = dist * grav / 2.0;
	double b = cos0 * (origVert.getLoc(Z) / dist * cos0 + sin0);
	double speed = sqrt(a / b) / PIXELS_PER_METER;	
	
	double maxSpeed = 7;
	if(speed > maxSpeed){
		speed = maxSpeed * PIXELS_PER_METER;
		double nDist = speed * sin0;
		nDist += sqrt(speed * speed * sin0 * sin0 + 2.0 * grav * origVert.getLoc(Z));
		nDist *= speed * cos0 / grav;
		double ratio = nDist / dist;
		
		// Reduce the vector size to max range
		targVert.setLoc(origVert.getLoc(X) + toTarg.getDir(X) * ratio, 
						origVert.getLoc(Y) + toTarg.getDir(Y) * ratio, 
						targVert.getLoc(Z));
	}
	
	LevelMap* levelMap = LevelMap::getInstance();
	GridBlock* gb = levelMap->getBlockBy3D(targVert.getLoc(X), targVert.getLoc(Y)); 
	
	if(!ALWAYS_HIT){ // NOTE: this is the same as bullet randomization code.  may be able to put elsewhere
		randomizeShot(targVert, origVert);
		
		GridBlock* temp = levelMap->getBlockBy3D(targVert.getLoc(X), targVert.getLoc(Y));
		if(temp != NULL)
			gb = temp;		
	}
	
	return gb;
}

void Unit::throwItem(GLshort cost)
{
	// Disallow shooting the block you're standing on
	if(getEffectiveTU() >= cost){
		if(!UNLIMITED_TU)
			_currTU -= cost;
		
		Item* item = getEquippedItem();
		ItemContainerType* cont = _inventory.getContainer(0);
		cont->setItem(NULL);
		
		Vertex origVert(getGlobalLoc(X, Dimension(MIDDLE), TORSO),
						getGlobalLoc(Y, Dimension(MIDDLE), TORSO),
						getGlobalLoc(Z, Dimension(MAXIMUM), TORSO));		
		
		const Object* targ = _goalBlock->getGround();
		Vertex targVert(targ->getGlobalLoc(X, Dimension(MIDDLE), _targetSection),
						targ->getGlobalLoc(Y, Dimension(MIDDLE), _targetSection),
						getGlobalLoc(Z, Dimension(MAXIMUM), TORSO));
		
		// todo: make this more complex later
		//	if(!ALWAYS_HIT)
		//		_goalBlock = getRandomBlockInRange(_goalBlock, 2);
		
		// todo: base angle on if going through a window or not.  only use 22.5 then, or range gets reduced
		
		// Find velocity to hit target at a 45 degree angle
		double cos0 = cos(degreeToRad(22.5));
		double sin0 = sin(degreeToRad(22.5));	
		double tan0 = tan(degreeToRad(22.5));		
		double grav = GRAVITY * PIXELS_PER_METER;
		
		Vector toTarg(targVert, origVert);
		double dist = toTarg.size();
		double a = dist * grav / 2.0;
		double b = cos0 * (origVert.getLoc(Z) / dist * cos0 + sin0);
		double speed = sqrt(a / b) / PIXELS_PER_METER;	
		
		cout << "Throwing speed: " << speed << endl;
		
		targVert.setLoc(targVert.getLoc(X),
						targVert.getLoc(Y),
						targVert.getLoc(Z) + tan0 * dist);
		
		LevelMap* levelMap = LevelMap::getInstance();
		levelMap->addProjectile(Projectile::create(ObjType(THROWN_ITEM), 0, HP(10), targVert, origVert, 
												   false, item, speed));	
	}
}
