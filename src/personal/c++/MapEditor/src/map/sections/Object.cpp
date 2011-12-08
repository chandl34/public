#include "Object.h"

Object::Object(){object = NULL;}

Object::~Object(){
	delete object;
}

void Object::load(){
	if(object != NULL)
		object->load();
}

void Object::setObject(BreakableModel* o){
	if(object != NULL)
		delete object;
	object = o;
}

int Object::getType(){return object->getType();}

void Object::clear(){delete object; object = NULL;}

void Object::draw(int x, int z){
	if(object != NULL)
		object->draw(x, 0, z);
}
