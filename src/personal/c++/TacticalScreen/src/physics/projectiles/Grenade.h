#ifndef GRENADE_H_
#define GRENADE_H_

#include "Projectile.h"

class Grenade : public Projectile{
public:
	Grenade(Vertex*, Vertex*);
	virtual ~Grenade();
		
	bool draw();	
	
private:
	void findInitialVector(Vertex*, Vertex*, Vertex*);
	
	Coordinate* targCoord;
	const static float gravity;
};

#endif /*GRENADE_H_*/
