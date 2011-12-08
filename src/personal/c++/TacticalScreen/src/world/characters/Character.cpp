#include "Character.h"
#include "../World.h"

Character::Character(int g, int i, int t){		
	gender = g;
	index = i;
	type = t;
	door = NULL;

	if(t == PLAYER)
		visible = VISIBLE;
	else
		visible = INVISIBLE;
	
	lookDir = World::getDir(DIR_FRONT_RIGHT);
	model = CharacterModelContainer::open(gender, DIR_FRONT_RIGHT, index);

	target = NULL;
	targetLook = lookDir;
	lookIncr = 0;

	stopping = false;
	jumping = false;
	turning = false;

	path = NULL;
	destChange = NULL;

	actual = new float[2];
	dist = new int[2];
	id = new int[4];
}

Character::~Character(){	
	if(path != NULL)
		delete path;
	delete [] actual;
	delete [] dist;	
	delete [] id;
}

Selection* Character::init(int ID, int i){
	id[i] = ID;
	Selection* select = new Selection();
	select->setCharacter(this);
	select->setType(i);
	return select;
}

CharacterModel* Character::getCharModel(){return model;}
int Character::getType(){return type;}
void Character::setDoorToOpen(DoorModel* d){door = d;}

void Character::setMap(LevelMap* m, Coordinate* c){		
	if(path != NULL)
		delete path;
	path = NULL;

	loc = c;	
	dest = loc;	
	actual[X] = c->get(X); 
	actual[Y] = c->get(Y);
	dist[X] = 0; 
	dist[Y] = 0;

	map = m;
	map->getBlock(c)->setCharacter(this);
}

void Character::shootAt(Vertex* t){
	if(!jumping){
		target = t;
		lookAt(World::getCoord((int)t->get(X), (int)t->get(Z)));
	}
}

void Character::shoot(){	
	Vertex* m = model->getModelWrapper(GUNPOS)->getModel()->getCenter();
	Vertex* origin = new Vertex(m->get(X) + loc->get(X), 
			m->get(Y), m->get(Z) + loc->get(Y));		
	map->addProjectile(new Bullet(origin, target));	
	delete target;
	target = NULL;
}

void Character::draw(){
	if(model != NULL && (type == PLAYER || visible != INVISIBLE)){
		if(path != NULL)
			move();	
		else if(turning)
			turn();
		else if(target != NULL)
			shoot();	
		else if(door != NULL){
			World::getSelectedMap()->getBlock(loc->get(X) + lookDir->get(X), 
					loc->get(Y) + lookDir->get(Y))->toggleDoor(door);
			door = NULL;
		}
		int i;
		for(i = 0; i < 4; i++){
			glLoadName(id[i]);
			model->getModelWrapper(i)->draw(actual[X], 0, actual[Y], visible);
		}
		for(; i < 8; i++)
			model->getModelWrapper(i)->draw(actual[X], 0, actual[Y], visible);
	}
}
