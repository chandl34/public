#include "WindowHit.h"
#include "../world/World.h"

WindowHit::WindowHit(int t, Coordinate* c, BreakableModel* b){
	model = b;
	time = t;
	Vertex* v = b->getCenter();
	center = new Vertex(c->get(X) + v->get(X), v->get(Y), c->get(Y) + v->get(Z));
}

WindowHit::~WindowHit(){delete center;}

int WindowHit::getTime(){return time;}
Vertex* WindowHit::getCenter(){return center;}

void WindowHit::breakWindow(){
	if(model->getCondition() == UNBROKEN){
		model->breakModel();
		World::getSelectedMap()->updateModels(WINDOW);
	}
}
