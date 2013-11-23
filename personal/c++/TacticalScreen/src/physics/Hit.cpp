#include "Hit.h"

Hit::Hit(bool p){
	duration = -1.5f;
	coord = NULL;
	projectile = p;
}

Hit::~Hit(){
	for(list<WindowHit*>::iterator i = window.begin(); i != window.end(); i++)
		delete (*i);	
}

bool Hit::isProjectile(){return projectile;}
float Hit::getDuration(){return duration;}
void Hit::setDuration(float d){duration = d;}
int Hit::getSide(){return side;}
void Hit::setSide(int s){side = s;}
int Hit::getType(){return type;}
void Hit::setType(int t){type = t;}
Coordinate* Hit::getCoord(){return coord;}
void Hit::setCoord(Coordinate* c){coord = c;}
size_t Hit::windowsLeft(){return window.size();}
int Hit::getWindowTime(){return window.front()->getTime();}
Vertex* Hit::getWindowCenter(){return window.front()->getCenter();}

void Hit::addWindow(int t, Coordinate* c, BreakableModel* bm){
	window.push_back(new WindowHit(t, c, bm));
}

void Hit::breakWindow(){
	WindowHit* temp = window.front();
	window.pop_front();
	temp->breakWindow();
	delete temp;
}
