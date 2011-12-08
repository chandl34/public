#ifndef RAY_H_
#define RAY_H_

#include "Vector.h"

class Ray{
public:
	Ray(Vertex*, Vector*);
	Ray(Vertex*, Vertex*);
	virtual ~Ray();
	
	Vertex* getOrigin();
	void setOrigin(Vertex*);
	Vector* getDirection();
	void setDirection(Vector*);
	
	
private:
	Vertex* origin;
	Vector* direction;
};

#endif /*RAY_H_*/
