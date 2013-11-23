#include "Grenade.h"
#include "../../world/World.h"

const float Grenade::gravity = 0.025f;

Grenade::Grenade(Vertex* origin, Vertex* target) : Projectile(){
	targCoord = World::getCoord((int)target->get(X), (int) target->get(Z));
	target->set(targCoord->get(X) + 0.5f, target->get(Y), targCoord->get(Y) + 0.5f);

	Vector* vec = new Vector(target, origin);
	vec->normalize();	
	ray = new Ray(origin, vec);
	model = Reader::readOBJ("obj/Projectile/Grenade.obj");	
	hit = HitDetection::hitDetect(ray, 0, true);
	if(hit->windowsLeft() > 0)
		findInitialVector(origin, target, hit->getWindowCenter());
	else if(hit->getType() == HIT_WINDOWFRAME){
		Coordinate* c = hit->getCoord();
		Vertex* w = World::getSelectedMap()->getBlock(c)->getWall(hit->getSide())->getWindow()->getCenter();
		Vertex* v = new Vertex(c->get(X) + w->get(X), w->get(Y), c->get(Y) + w->get(Z));
		findInitialVector(origin, target, v);
		delete v;
	}		
	else{
		float x = (target->get(X) + origin->get(X))/2.0f;
		float z = (target->get(Z) + origin->get(Z))/2.0f;		
		Vertex* v = new Vertex(x, origin->get(Y) + 0.5f, z);
		findInitialVector(origin, target, v);
		delete v;
	}
	delete hit;
	hit = HitDetection::hitDetect(ray, gravity, true);
	cout << hit->getType() << endl;
}

Grenade::~Grenade(){}

void Grenade::findInitialVector(Vertex* o, Vertex* f, Vertex* w){
	Vector* vec = ray->getDirection();
	int basis = Z;
	int other = X;
	float zf_zw = f->get(Z) - w->get(Z);
	if((int)o->get(Z) - (int)f->get(Z) == 0){
		basis = X;
		other = Z;
		zf_zw = f->get(basis) - w->get(basis);		
	}			
	float c = vec->get(other)/vec->get(basis);
	float zf_zo = f->get(basis) - o->get(basis);
	float zw_zo = w->get(basis) - o->get(basis);
	float yf_yo = f->get(Y) - o->get(Y);
	float zcmpt = gravity*zf_zo*zw_zo*zf_zw;
	float zcmpb = 2.0f*((w->get(Y) - o->get(Y))*zf_zo - yf_yo*zw_zo);
	float zcmp = sqrt(zcmpt/zcmpb);
	if(zcmpt < 0)
		zcmp *= -1;
	float ycmp = gravity*zf_zo*0.5f/zcmp + yf_yo*zcmp/zf_zo;
	if(basis == Z)
		vec->set(c*zcmp, ycmp, zcmp);
	else
		vec->set(zcmp, ycmp, c*zcmp);
}

bool Grenade::draw(){
	if(time == 100)
		return true;
	ray->getDirection()->set(Y, ray->getDirection()->get(Y) - gravity);
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
