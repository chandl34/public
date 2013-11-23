/*
 *  ThrownItem.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/16/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ThrownItem.h"

#include "Grenade.h"
#include "GridBlock.h"

#include "HitTest.h"
#include "ImageStorage.h"
#include "LevelMap.h"
#include "ModelStorage.h"



ThrownItem::ThrownItem(const ObjType& ot, GLshort is, 
					   const HP& mhp, 
					   const Vertex& t, const Vertex& o,
					   bool ignore, 
					   Item* it, double speed) 
: Projectile(ot, is, mhp, t, o, ignore, it, speed)
{
	// todo: remove
	double speedUp = 5.0;
	double ratio = speed / METERS_PER_SECOND / speedUp;
	_gravity = GRAVITY_MOD / ratio / ratio;
	
	_ray.setDir(_ray.getDir(X) * speedUp, 
				_ray.getDir(Y) * speedUp, 
				_ray.getDir(Z) * speedUp - _gravity);
	
	_hit.push_back(Hit());
	list<Hit>::reverse_iterator h = _hit.rbegin();
	testFlight(_ray, *h, _gravity, ignore);
	
	printf("lifespan %f on Object %i\n", h->getTimeLeft(), (int)h->getObjectHit());
}


GLshort ThrownItem::update()
{	
	GLshort ret = Projectile::update();
	if(ret == DIED){
		LevelMap* levelMap = LevelMap::getInstance();
		GridBlock* gb = levelMap->getBlockBy3D(_ray.getLoc(X), _ray.getLoc(Y));
		
		// Explode grenades
		if(_item->getType() == GRENADE){
			Grenade* gren = (Grenade*)_item;
			if(gren->isPrimed()){
				gren->explode(gb);
				delete gren;
				return ret;
			}
		}	
		
		ItemContainerType* cont = gb->getContainer();	
		cont->setItem(_item);
	}
	
	return ret;
}

//--- GENERAL ---//
void ThrownItem::dealDamage(Hit& h)
{
	Object* objHit = h.getObjectHit();
	if(objHit != NULL)
		objHit->takeDamage(h.getSectionHit(), 0);
}
