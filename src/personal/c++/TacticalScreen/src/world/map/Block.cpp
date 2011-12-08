#include "Block.h"
#include "../World.h"

Block::Block(){
	wall = new Wall*[2];
	character = NULL;
}

Block::~Block(){
	for(int i = 0; i < 2; i++)
		delete wall[i];
	delete [] wall;
	delete object;
	delete ground;
}

void Block::load(Coordinate* c, map<int, Selection*>& m){
	coord = c;	
	for(int i = 0; i < 2; i++){
		wall[i]->load(coord, m);
		if(wall[i]->getFrame() != NULL){
			if(wall[i]->getFrame()->getType() == DOORFRAME){
				if(wall[i]->getDoor()->getAngle() == OPEN)
					incrBlockingDoor(false, wall[i]->getDoor());
			}
		}
	}
	object->load();
	ground->load();
}

void Block::incrBlockingDoor(bool closing, DoorModel* d){
	int x = coord->get(X);
	int y = coord->get(Y);
	bool mir = d->getMirror();
	bool inv = d->getInvert();
	bool shi = d->getShift();
	if(inv && shi);
	else if(mir){
		if(inv)
			y++;
		else if(shi)
			x++;
		else{
			x++;
			y++;
		}
	}
	else{
		if(inv)
			x--;
		else if(shi)
			y--;
		else{
			x--;
			y--;
		}
	}
	Coordinate* c = World::getCoord(x, y);
	if(c == NULL)
		return;
	World::getSelectedMap()->getBlock(c)->getWall(!mir)->incrBlockingDoor(closing);
}

Wall* Block::getWall(int i){return wall[i];}
Object* Block::getObject(){return object;}

void Block::toggleDoor(DoorModel* d){
	if(d->getAngle() == OPEN){
		d->setMotion(DoorModel::CLOSING);
		incrBlockingDoor(true, d);
		World::getSelectedMap()->updateModels(DOOR);
	}
	else if(d->getAngle() == CLOSED){
		d->setMotion(DoorModel::OPENING);
		incrBlockingDoor(false, d);
		World::getSelectedMap()->updateModels(DOOR);
	}
}

void Block::draw(int t, int x, int y, int z){
	if(t < DOOR)
		ground->draw(t, x, y, z);
	else if(t == FENCE || t == OBJECT)
		object->draw(t, x, y, z);
	else{
		for(int i = 0; i < 2; i++)
			wall[i]->draw(t, x, y, z);
	}			
}

bool Block::jumpable(){
	return object->jumpable();
}

bool Block::jumpable(int d){
	return object->jumpable(d);
}

bool Block::passable(int d){
	return wall[d]->passable();
}
