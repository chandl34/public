#include "Bullet.h"
#include "../../world/World.h"

Bullet::Bullet(Vertex* origin, Vertex* target) : Projectile(){
	Vector* vec = new Vector(target, origin);
	vec->normalize();	
	ray = new Ray(origin, vec);
	model = Reader::readOBJ("obj/Projectile/bullet.obj");	
	hit = HitDetection::hitDetect(ray, 0, true);
}

Bullet::~Bullet(){}

bool Bullet::draw(){
	if(hit->getDuration() - time > 1){
		for(int i = 0; i < 3; i++)
			ray->getOrigin()->set(i, ray->getOrigin()->get(i) + ray->getDirection()->get(i));
		model->draw(ray->getOrigin()->get(X), ray->getOrigin()->get(Y), ray->getOrigin()->get(Z));
		while(hit->windowsLeft() > 0 && hit->getWindowTime() == time)
			hit->breakWindow();
		if(hit->getType() == HIT_GROUND && ray->getOrigin()->get(Y) < 0)
			return true;
		if(hit->getType() == HIT_BOUNDS &&
				World::getCoord((int)ray->getOrigin()->get(X), (int)ray->getOrigin()->get(Z)) == NULL)
			return true;
		time += 1;
		return false;
	}
	else{
		for(int i = 0; i < 3; i++)
			ray->getOrigin()->set(i, ray->getOrigin()->get(i)+ 
					ray->getDirection()->get(i)*(hit->getDuration()-time));
		model->draw(ray->getOrigin()->get(X), ray->getOrigin()->get(Y), ray->getOrigin()->get(Z));		
		while(hit->windowsLeft() > 0)
			hit->breakWindow();
		return true;
	}
}
