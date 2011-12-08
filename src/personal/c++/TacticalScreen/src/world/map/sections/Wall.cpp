#include "Wall.h"

Wall::Wall(){
	blockingDoors = 0;
}

Wall::~Wall(){
	delete frame;
	delete window;
	delete door;
}

void Wall::load(Coordinate* c, map<int, Selection*>& m){
	if(frame != NULL)
		frame->load();
	if(door != NULL){
		door->load();
		id = createID();
		m[id] = new Selection();
		m[id]->setDoor(door);
		m[id]->setCoord(c);
	}
	if(window != NULL)
		window->load();
}

void Wall::incrBlockingDoor(bool closing){
	if(closing)
		blockingDoors--;
	else
		blockingDoors++;
}

bool Wall::passable(){
	if(blockingDoors > 0)
		return false;
	if(frame == NULL)
		return true;
	if(frame->getType() == DOORFRAME){
		if(door->getAngle() == OPEN)
			return true;
	}
	return false;
}

int Wall::getBlockingDoors(){return blockingDoors;}
BreakableModel* Wall::getFrame(){return frame;}
BreakableModel* Wall::getWindow(){return window;}
DoorModel* Wall::getDoor(){return door;}

void Wall::draw(int t, int x, int y, int z){
	if(frame != NULL){
		if(t != DOOR && t != WINDOW){
			if(t == frame->getType())
				frame->draw(x, y, z);
		}
		else if(t == DOOR){ 
			if(frame->getType() == DOORFRAME){
				glLoadName(id);
				door->draw(x, y, z);
			}
		}
		else{
			if(frame->getType() == WINDOWFRAME
					&& frame->getCondition() != BROKEN){
				glEnable(GL_BLEND);
				window->draw(x, y, z);
				glDisable(GL_BLEND);
			}
		}
	}
}
