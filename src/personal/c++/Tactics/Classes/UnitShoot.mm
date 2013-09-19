/*
 *  UnitShoot.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "Bullet.h"
#include "Grenade.h"
#include "GridBlock.h"
#include "Gun.h"
#include "Item.h"
#include "LevelMap.h"
#include "ThrownItem.h"

#include "Math.h"
#include "Options.h"


void Unit::takeDamage(GLshort section, GLshort damage)
{
	GLshort dmg;
	
	if(damage == 0)
		dmg = 1;
	else{	
		if(section == HEAD)
			printf("Hit %i in head!\n", (int)this);	
		else if(section == TORSO)
			printf("Hit %i in torso!\n", (int)this);
		else // section == LEGS
			printf("Hit %i in legs!\n", (int)this);		
		
		dmg = damage * 1.0 * (section + 1);
	}
	
	printf("%i took %i damage!\n", (int)this, dmg);
	if(!GOD_MODE)
		_currHP -= dmg;
}

bool Unit::canAim()
{	
	if(_goalBlock != NULL){
		Unit* u = _goalBlock->getUnit();
		Item* it = getEquippedItem();
		if(u != NULL && it->getType() == GUN && couldSee(u))
			return true;
	}
	return false;
}

void Unit::aim(GLshort sect, GLshort bullets, GLshort aimTime, GridBlock* goal)
{
	_targetSection = sect;
	//bullets;
	//aimTime;
	if(goal == NULL)
		goal = _goalBlock;
	findCTH(goal->getUnit());
}

void Unit::findCTH(Unit* targ)
{
	// Should never be NULL!
	if(targ == NULL){
		printf("ERROR: findCTH() used on empty GridBlock\n");
		_chanceToHit = -1;
	}
	
	// Get base CTH (based off worst shot at 22.5 degree angle)
	double dist = getDistanceBetween(targ->getBlock(), _currBlock);
	if(_targetSection == TORSO){
		_chanceToHit = 0.013445144 * dist - 0.7159588142 + 85.26749364 / dist - 5.70527252 / dist / dist;
	}
	else if(_targetSection == LEGS){
		_chanceToHit = 0.02621170201 * dist - 1.123577877 + 84.10711904 / dist - 39.10277835 / dist / dist;
	}
	else{
		_chanceToHit = -0.1014556507 * dist + 1.123744085 + 22.84294713 / dist + 5.201740729 / dist / dist;
	}
	
	// Reduce the CTH on the torso if kneeling
	if(targ->_kneeling)
		_chanceToHit *= 0.7;
	
	// Add the effect of accuracy
	double acc = 75.0;
	_chanceToHit *= (1.0 + 3.0 * acc / 100.0);
	_chanceToHit = min(_chanceToHit, 99.0);
	
	printf("Chance to hit: %f\n", _chanceToHit);
}

double Unit::getEffectiveCTH() const
{
	return 100.0 * (1.0 - (1.0 - _chanceToHit * IGNORE_RATIO / 100.0) * (1.0 - _chanceToHit / 100.0));
}

void Unit::shoot()
{	
	// Disallow shooting the block you're standing on
	if(getEffectiveTU() >= USE_COST){
		if(!UNLIMITED_TU)
			_currTU -= USE_COST;
		
		double timer = [[NSDate date] timeIntervalSince1970];
		
		Gun* item = (Gun*)getEquippedItem();
		_inventory.takeShot(); 
		GLshort speed = item->getSpeed();
		
		const Object* targ;
		if(canAim())
			targ = _goalBlock->getUnit();
		else
			targ = _goalBlock->getGround();
		
		Vertex origVert(getGlobalLoc(X, Dimension(MIDDLE), TORSO),
						getGlobalLoc(Y, Dimension(MIDDLE), TORSO),
						getGlobalLoc(Z, Dimension(MAXIMUM), TORSO));	
		
		/*  Hit trials
		 int trials = 100000;
		 float hits = 0;
		 
		 for(int i = 0; i < trials; ++i){			
		 Vertex targVert(targ->getGlobalLoc(X, Dimension(MIDDLE), _targetSection),
		 targ->getGlobalLoc(Y, Dimension(MIDDLE), _targetSection),
		 targ->getGlobalLoc(Z, Dimension(MIDDLE), _targetSection));
		 
		 randomizeShot(targVert, origVert);
		 Bullet* b = Bullet::create(0, HP(10), targVert, origVert, false, item);
		 
		 if(b->getObjectHit() == targ && b->getSectionHit() == _targetSection)
		 hits++;
		 
		 delete b;
		 
		 if(i % 10000 == 0)
		 cout << "Trial " << i << endl;
		 }
		 
		 cout << "Hit chance: " << hits / trials * 100.0 << endl;
		 //*/
		///*
		Vertex targVert(targ->getGlobalLoc(X, Dimension(MIDDLE), _targetSection),
						targ->getGlobalLoc(Y, Dimension(MIDDLE), _targetSection),
						targ->getGlobalLoc(Z, Dimension(MIDDLE), _targetSection));
		
		
		// Roll to see if you make a guaranteed hit
		LevelMap* levelMap = LevelMap::getInstance();
		if((targ->isUnit() && roll(_chanceToHit * IGNORE_RATIO)) || ALWAYS_HIT){
			printf("Shot will hit\n");
			levelMap->addProjectile(Projectile::create(ObjType(BULLET), 0, HP(10), targVert, origVert, 
													   true, item, speed));
		}
		else{
			randomizeShot(targVert, origVert);
			levelMap->addProjectile(Projectile::create(ObjType(BULLET), 0, HP(10), targVert, origVert, 
													   false, item, speed));
		}
		//*/
		
		timer = [[NSDate date] timeIntervalSince1970] - timer;
		printf("Hit detection took %f seconds\n", timer);
	}	
}

void Unit::randomizeShot(Vertex& targVert, Vertex& origVert)
{
	printf("Shot has random variation\n");
	// Randomly rotate vector... must first rotate vector to <0, 1, 0>
	Vector vect3d(targVert, origVert);
	GLfloat size3d = vect3d.size();
	
	Vector vect2d(vect3d.getDir(X), vect3d.getDir(Y));
	GLfloat size2d = vect2d.size();
	
	// Find rotation angles for z then x
	// <0, 1, 0> dot 2dToTarg / |2dToTarg|
	GLfloat zRot = arccos(vect2d.getDir(Y)/size2d);
	if(vect3d.getDir(X) > 0)
		zRot *= -1;	
	
	// 2dToTarg dot 3dToTarg / |2dToTarg| / |3dToTarg|
	GLfloat xRot = arccos((vect2d.getDir(X) * vect3d.getDir(X) + 
						   vect2d.getDir(Y) * vect3d.getDir(Y)) / size2d / size3d);
	if(vect3d.getDir(Z) < 0)
		xRot *= -1;	
	
	vect3d.rotateZ(zRot);
	double acc = 75.0;
	double rand = random(5626 * (1 + 3 * (100.0 - acc) / 100.0)) / 1000.0;
	//	double rand = random(2251) / 100.0;
	
	printf("Shot at %f degree angle\n", rand);
	vect3d.rotateX(xRot + degreeToRad(rand));				// random x to y degrees rotation
	vect3d.rotateY(degreeToRad(random(360)));				// random 0 to 359 degrees rotation						
	vect3d.rotateX(-xRot);
	vect3d.rotateZ(-zRot);
	
	targVert.setLoc(origVert.getLoc(X) + vect3d.getDir(X),
					origVert.getLoc(Y) + vect3d.getDir(Y),
					origVert.getLoc(Z) + vect3d.getDir(Z));
}

