#include "LevelMap.h"
#include "../World.h"

LevelMap::LevelMap(){
	block = new Block**[LEVEL_LENGTH];
	for(int i = 0; i < LEVEL_LENGTH; i++)
		block[i] = new Block*[LEVEL_LENGTH];
	update = new bool[10];
	id = new int[10];
	doorUpdate = false;
	character = new vector<Character*>[3];
}

LevelMap::~LevelMap(){
	for(int i = 0; i < LEVEL_LENGTH; i++){
		for(int k = 0; k < LEVEL_LENGTH; k++)
			delete block[i][k];
		delete [] block[i];
	}
	delete [] block;
	for(map<int, Selection*>::iterator i = select.begin(); i != select.end(); i++)
		delete (*i).second;	
	delete [] update;
	delete [] id;
	delete [] character;
}

void LevelMap::load(){
	for(int i = 0; i < LEVEL_LENGTH; i++){
		for(int k = 0; k < LEVEL_LENGTH; k++){
			if(block[i][k] != NULL)
				block[i][k]->load(World::getCoord(i, k), select);
		}
	}
	for(int i = 0; i < 10; i++){
		update[i] = true;
		id[i] = -1;
	}
	_update = true;	
}

void LevelMap::refreshMap(){
	for(int i = 0; i < 10; i++){
		if(update[i])
			refresh(i);
	}
	if(doorUpdate){
		doorUpdate = false;
		update[DOOR] = true;
	}
	else
		_update = false;
}

void LevelMap::refresh(int m){
	glDeleteLists(id[m], 1);
	id[m] = glGenLists(1);
	glNewList(id[m], GL_COMPILE);
	draw(m);
	glEndList();
	update[m] = false;
}

void LevelMap::draw(int m){
	for(int i = LEVEL_LENGTH - 1; i >= 0; i--){
		for(int k = 0; k < LEVEL_LENGTH; k++){
			if(block[i][k] != NULL)
				block[i][k]->draw(m, i, 0, k);		
		}
	}
}

void LevelMap::updateMap(){_update = true;}

void LevelMap::updateModels(int i){
	update[i] = true;
	_update = true;
	if(i == DOOR)
		doorUpdate = true;
}

bool LevelMap::needsUpdate(){return _update;}
int LevelMap::getID(int i){return id[i];}
Block* LevelMap::getBlock(int i, int k){return block[i][k];}
Block* LevelMap::getBlock(Coordinate* c){return block[c->get(X)][c->get(Y)];}
Selection* LevelMap::getSelection(size_t i){return select[i];}
void LevelMap::addProjectile(Projectile* p){projectile.push_back(p);}
size_t LevelMap::getCharacterSize(size_t i){return character[i].size();}
Character* LevelMap::getCharacter(size_t i, size_t j){
	return character[i].at(j);
}

void LevelMap::addCharacter(Character* c, Coordinate* loc){
	c->setMap(this, loc);
	character[c->getType()].push_back(c);
	int temp;
	for(int i = 0; i < 4; i++){
		temp = createID();
		select[temp] = c->init(temp, i);
	}	
}

void LevelMap::drawCharacters(){
	for(size_t i = 0; i < 3; i++){
		for(size_t j = 0; j < character[i].size(); j++) 
			character[i].at(j)->draw();
	}
}

void LevelMap::clearVision(int v, bool reset){
	bool seen;
	if(reset){
		for(size_t j = 0; j < character[PLAYER].size(); j++)
			character[PLAYER].at(j)->clearSeen();
	}
	for(size_t i = 1; i < 3; i++){		
		for(size_t j = 0; j < character[i].size(); j++){
			if(character[i].at(j)->getVisible() < v){
				seen = false;
				for(size_t k = 0; k < character[PLAYER].size(); k++){
					if(character[PLAYER].at(k)->isSeen(character[i].at(j)))
						seen = true;
				}			
				if(!seen)
					character[i].at(j)->setVisible(v);
			}
		}
	}
	if(reset){
		for(size_t j = 0; j < character[PLAYER].size(); j++)
			character[PLAYER].at(j)->findVisible();
	}
}

void LevelMap::drawProjectiles(){
	if(!projectile.empty()){
		stack<Projectile*> remove;
		for(list<Projectile*>::iterator i = projectile.begin(); i != projectile.end(); i++){ 
			if((*i)->draw())
				remove.push(*i);
		}
		while(!remove.empty()){
			projectile.remove(remove.top());
			delete remove.top();
			remove.pop();		
		}
	}
}
