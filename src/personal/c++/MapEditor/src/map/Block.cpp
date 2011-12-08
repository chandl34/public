#include "Block.h"

Block::Block(){
	wall = new Wall*[2];
}

Block::~Block(){
	for(int i = 0; i < 2; i++)
		delete wall[i];
	delete [] wall;
	delete object;
	delete ground;
}

void Block::init(){
	for(int i = 0; i < 2; i++)
		wall[i] = new Wall();

	object = new Object();
	object->clear();

	ground = new Ground();
	ground->setGround(new UnbreakableModel(GROUND, false, 0));
}

void Block::load(){
	for(int i = 0; i < 2; i++)
		wall[i]->load();
	object->load();
	ground->load();
}

void Block::draw(int x, int z){
	for(int i = 0; i < 2; i++)
		wall[i]->draw(x, z);
	object->draw(x, z);
	ground->draw(x, z);
}

void Block::addGround(){
	ground->setGround(new UnbreakableModel(GROUND, 
			MapModelContainer::getMirror(),
			MapModelContainer::getIndex(GROUND)));
	LevelMap::updateMap();
}

void Block::addDebris(){
	ground->addDebris(new UnbreakableModel(DEBRIS, 
			MapModelContainer::getMirror(),
			MapModelContainer::getIndex(DEBRIS)));
	LevelMap::updateMap();
}

void Block::addGrass(){
	ground->setGrass(new UnbreakableModel(GRASS, 
			MapModelContainer::getMirror(),
			MapModelContainer::getIndex(GRASS)));
	LevelMap::updateMap();
}

void Block::addWall(){
	Wall* temp = wall[MapModelContainer::getMirror()];
	temp->setFrame(new BreakableModel(WALL, 
			MapModelContainer::getMirror(),
			MapModelContainer::getCondition(WALL),
			MapModelContainer::getIndex(WALL)));
	LevelMap::updateMap();
}

void Block::addObject(){
	object->setObject(new BreakableModel(OBJECT, 
			MapModelContainer::getMirror(),
			MapModelContainer::getCondition(OBJECT),
			MapModelContainer::getIndex(OBJECT)));
	LevelMap::updateMap();
}

void Block::addFence(){
	object->setObject(new BreakableModel(FENCE, 
			MapModelContainer::getMirror(),
			MapModelContainer::getCondition(FENCE),
			MapModelContainer::getIndex(FENCE)));
	LevelMap::updateMap();
}

void Block::addWindow(){
	Wall* temp = wall[MapModelContainer::getMirror()];
	temp->setFrame(new BreakableModel(WINDOWFRAME, 
			MapModelContainer::getMirror(),
			MapModelContainer::getCondition(WINDOWFRAME),
			MapModelContainer::getIndex(WINDOWFRAME)));
	temp->setWindow(new BreakableModel(WINDOW, 
			MapModelContainer::getMirror(),
			MapModelContainer::getCondition(WINDOW),
			MapModelContainer::getIndex(WINDOW)));
	LevelMap::updateMap();
}

void Block::addDoor(){
	Wall* temp = wall[MapModelContainer::getMirror()];
	temp->setFrame(new BreakableModel(DOORFRAME, 
			MapModelContainer::getMirror(),
			MapModelContainer::getCondition(DOORFRAME),
			MapModelContainer::getIndex(DOORFRAME)));
	temp->setDoor(new DoorModel(MapModelContainer::getMirror(),
			MapModelContainer::getShift(),
			MapModelContainer::getInvert(),
			MapModelContainer::getAngle(),
			MapModelContainer::getIndex(DOOR)));			
	LevelMap::updateMap();
}

void Block::clear(){
	for(int i = 0; i < 2; i++)
		wall[i]->clear();
	ground->clear();
	object->clear();
	LevelMap::updateMap();
}
