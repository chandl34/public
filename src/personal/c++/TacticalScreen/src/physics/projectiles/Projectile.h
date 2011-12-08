#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "../../io/Reader.h"
#include "../HitDetection.h"

class Projectile{
public:
	Projectile();
	virtual ~Projectile();
	
	virtual bool draw();

protected:
	Model* model;
	Ray* ray;
	Hit* hit;
	int time;
};

#endif /*PROJECTILE_H_*/
