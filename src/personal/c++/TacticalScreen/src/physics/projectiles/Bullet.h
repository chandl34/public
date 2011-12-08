#ifndef BULLET_H_
#define BULLET_H_

#include "Projectile.h"

class Bullet : public Projectile{
public:
	Bullet(Vertex*, Vertex*);
	virtual ~Bullet();
		
	bool draw();		
};

#endif /*BULLET_H_*/
