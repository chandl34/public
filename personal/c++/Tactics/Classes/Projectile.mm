/*
 *  Projectile.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Projectile.h"

#include "Bullet.h"
#include "Item.h"
#include "ThrownItem.h"

#include "HitTest.h"
#include "ImageStorage.h"
#include "Math.h"
#include "ModelStorage.h"



Projectile* Projectile::create(const ObjType& ot, GLshort is, 
							   const HP& mhp, 
							   const Vertex& t, const Vertex& o,
							   bool ignore, 
							   Item* it, double speed)
{
	Projectile* p = NULL;
	if(ot == BULLET)
		p = new Bullet(ot, is, mhp, t, o, ignore, it, speed);	
	else if(ot == THROWN_ITEM)
		p = new ThrownItem(ot, is, mhp, t, o, ignore, it, speed);

	return p;
}


Projectile::Projectile(const ObjType& ot, GLshort is, 
					   const HP& mhp, 
					   const Vertex& t, const Vertex& o,
					   bool ignore, 
					   Item* it, double speed) 
: Object(ot, is, mhp)
, _item(it)
{
	_image = ImageStorage::getConstImage(ot, is);
	_model = ModelStorage::getConstModel(ot);	
	
	_ray.setRay(t, o);
	_ray.normalize();
	
	setCoord3D(_ray.getLoc(X), 
			   _ray.getLoc(Y),
			   _ray.getLoc(Z));
	
	_prevOffset[X] = getOffset(X);
	_prevOffset[Y] = getOffset(Y);	
	
	//double speedUp = 5.0;			// todo:   base this speed in some way, so thrown items seem to move faster, etc	
	
	// todo: re-add this stuff later... it's temporarily going to both projectile type's constructors
	/*
	 double speedUp = 15.0;
	 double ratio = speed / METERS_PER_SECOND / speedUp;
	 _gravity = GRAVITY_MOD / ratio / ratio;
	 
	 _ray.setDir(_ray.getDir(X) * speedUp, 
	 _ray.getDir(Y) * speedUp, 
	 _ray.getDir(Z) * speedUp - _gravity);
	 
	 _hit.push_back(Hit());
	 list<Hit>::reverse_iterator h = _hit.rbegin();
	 testFlight(_ray, *h, _gravity, ignore);
	 
	 printf("lifespan %f on Object %i\n", h->getTimeLeft(), (int)h->getObjectHit());
	 */
}

Projectile::~Projectile()
{
	
}


//--- GENERAL ---//
GLshort Projectile::update()
{		
	_ray.setDir(_ray.getDir(X),
				_ray.getDir(Y),
				_ray.getDir(Z) + 2 * _gravity);
	
	_prevOffset[X] = getOffset(X);
	_prevOffset[Y] = getOffset(Y);
	
	list<Hit>::iterator h = _hit.begin();	
	h->setTimeLeft(h->getTimeLeft() - 1);
	
	if(compare(h->getTimeLeft() - 1, 0) == 1){		
		setCoord3D(_ray.getLoc(X) + _ray.getDir(X), 
				   _ray.getLoc(Y) + _ray.getDir(Y),
				   _ray.getLoc(Z) + _ray.getDir(Z));
	}
	else{
		setCoord3D(_ray.getLoc(X) + _ray.getDir(X) * (h->getTimeLeft() - 1), 
				   _ray.getLoc(Y) + _ray.getDir(Y) * (h->getTimeLeft() - 1),
				   _ray.getLoc(Z) + _ray.getDir(Z) * (h->getTimeLeft() - 1));		
	}
	
	if(compare(h->getTimeLeft(), 0) == 1 && compare(_ray.getLoc(Z), 0) == 1)
		return NO_CHANGE;
	
	dealDamage(*h);
	
	_hit.pop_front();
	if(_hit.empty())
		return DIED;
	return NO_CHANGE;
}

Object* Projectile::getObjectHit()
{
	return _hit.begin()->getObjectHit();
}

GLshort Projectile::getSectionHit()
{
	return _hit.begin()->getSectionHit();
}

bool Projectile::isDynamic() const
{
	return true;
}

