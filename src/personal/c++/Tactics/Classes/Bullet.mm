/*
 *  Bullet.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Bullet.h"

#include "Gun.h"
#include "Item.h"

#include "HitTest.h"
#include "ImageStorage.h"
#include "ModelStorage.h"



Bullet::Bullet(const ObjType& ot, GLshort is, 
			   const HP& mhp, 
			   const Vertex& t, const Vertex& o,
			   bool ignore, 
			   Item* it, double speed) 
: Projectile(ot, is, mhp, t, o, ignore, it, speed)
{
	// todo: remove
	double speedUp = 15.0;
	//double speedUp = 1.0;
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


//--- GENERAL ---//
void Bullet::dealDamage(Hit& h)
{
	Object* objHit = h.getObjectHit();
	Gun* gun = (Gun*)_item;
	if(objHit != NULL)
		//objHit->takeDamage(h->getSectionHit(), gun->getDamage());
		objHit->takeDamage(h.getSectionHit(), 5);
}

//---- DRAW ----//
void Bullet::draw(bool step, TexAttr* ta)
{	
	if(ta != NULL){
		ta->_texName = -1;
		ta->_texVertName = -1;
	}		
	
	//	/*
	GLshort vert[4];
	vert[0] = getOffset(X);		vert[1] = getOffset(Y);
	vert[2] = _prevOffset[X];	vert[3] = _prevOffset[Y];
	
	//cout << vert[0] << ", " << vert[1] << " : " << vert[2] << ", " << vert[3] << endl;
	
	glLoadIdentity();	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);	
	glVertexPointer(2, GL_SHORT, 0, vert);
	glDrawArrays(GL_LINES, 0, 2);
	// */
}
