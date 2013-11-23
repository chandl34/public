#include "Projectile.h"

Projectile::Projectile(){
	time = 0;
}

Projectile::~Projectile(){
	delete model;
	delete ray;
	delete hit;
}

bool Projectile::draw(){return true;}
