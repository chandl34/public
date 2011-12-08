#include "Ray.h"

Ray::Ray(Vertex* o, Vector* d){
	origin = o;
	direction = d;
}

Ray::~Ray(){
	delete origin;
	delete direction;
}

Vertex* Ray::getOrigin(){return origin;}
void Ray::setOrigin(Vertex* o){origin = o;}
Vector* Ray::getDirection(){return direction;}
void Ray::setDirection(Vector* d){direction = d;}
