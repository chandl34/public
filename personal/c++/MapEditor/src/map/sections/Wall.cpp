#include "Wall.h"

Wall::Wall(){
	frame = NULL;
	window = NULL;
	door = NULL;
}

Wall::~Wall(){
	delete frame;
	delete window;
	delete door;
}

void Wall::load(){
	if(frame != NULL)
		frame->load();
	if(door != NULL)
		door->load();
	if(window != NULL)
		window->load();
}

void Wall::setFrame(BreakableModel* m){
	if(frame != NULL)
		delete frame;
	frame = m;
	if(frame->getType() == WALL){
		delete window;
		delete door;
		window = NULL;
		door = NULL;
	}		
}

void Wall::setWindow(BreakableModel* m){
	if(window != NULL)
		delete window;
	if(door != NULL)
		delete door;
	window = m;
	door = NULL;
}	

void Wall::setDoor(DoorModel* m){
	if(window != NULL)
		delete window;
	if(door != NULL)
		delete door;
	door = m;
	window = NULL;
}	

void Wall::clear(){
	delete frame;
	delete window;
	delete door;
	frame = NULL;
	window = NULL;
	door = NULL;
}

int Wall::getType(){
	if(frame != NULL)
		return frame->getType();
	return -1;
}

int Wall::getMirror(){
	if(frame != NULL)
		return frame->getMirror();
	return -1;
}

int Wall::getInvert(){
	if(door != NULL)
		return door->getInvert();
	return -1;
}

int Wall::getShift(){
	if(door != NULL)
		return door->getShift();
	return -1;
}

int Wall::getAngle(){
	if(door != NULL)
		return door->getAngle();
	return -1;
}

int Wall::getFrameCondition(){
	if(frame != NULL)
		return frame->getCondition();
	return -1;
}

int Wall::getWindowCondition(){
	if(window != NULL)
		return window->getCondition();
	return -1;
}

void Wall::draw(int x, int z){
	if(frame != NULL){
		frame->draw(x, 0, z);
		if(getFrameCondition() != BROKEN){
			if(getType() == WINDOWFRAME){
				glEnable(GL_BLEND);
				window->draw(x, 0, z);
				glDisable(GL_BLEND);
			}
			else if(getType() == DOORFRAME)
				door->draw(x, 0, z);
		}
	}
}
