/*
 *  LevelMapProjectile.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"


void LevelMap::addProjectile(const Object* t, const Object* u){
	if(bullet == NULL)
		bullet = Bullet::create(ObjType(BULLET), Dir(0), 0, HP(10), t, u);	
}
