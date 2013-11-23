#include "Object.h"

Object::Object(){}

Object::~Object(){
	delete object;
}

void Object::load(){
	if(object != NULL)
		object->load();
}

bool Object::accessible(){
	return object == NULL;
}

bool Object::jumpable(){
	return object->getType() == FENCE;
}

bool Object::jumpable(int d){
	return d == object->getMirror() && object->getType() == FENCE;
}

BreakableModel* Object::getModel(){
	return object;
}

void Object::draw(int t, int x, int y, int z){	
	if(object != NULL && t == object->getType())
		object->draw(x, y, z);
}
