#include "LevelMap.h"

bool LevelMap::update = false;
const int LevelMap::LEVEL_LENGTH = 150, LevelMap::LEVEL_OFFSET = 75;
Block*** LevelMap::block;

LevelMap::LevelMap(){
	block = new Block**[LEVEL_LENGTH];
	for(int i = 0; i < LEVEL_LENGTH; i++)
		block[i] = new Block*[LEVEL_LENGTH];
}

LevelMap::~LevelMap(){
	for(int i = 0; i < LEVEL_LENGTH; i++){
		for(int k = 0; k < LEVEL_LENGTH; k++)
			delete block[i][k];
		delete [] block[i];
	}
	delete [] block;
}

void LevelMap::init(){
	for(int i = LEVEL_LENGTH - 1; i >= 0; i--){
		for(int k = LEVEL_LENGTH - 1; k >= 0; k--){
			if(i + k > LEVEL_OFFSET && i + k < LEVEL_LENGTH + LEVEL_OFFSET && abs(i - k) < LEVEL_OFFSET){
				block[i][k] = new Block();
				block[i][k]->init();
			}
			else
				block[i][k] = NULL;
		}
	}		
	update = true;
}

void LevelMap::load(){
	for(int i = LEVEL_LENGTH - 1; i >= 0; i--){
		for(int k = LEVEL_LENGTH - 1; k >= 0; k--){
			if(block[i][k] != NULL)
				block[i][k]->load();
		}
	}
	update = true;
}

void LevelMap::refreshMap(){
	glDeleteLists(id, 1);
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	drawMap();
	glEndList();
}

void LevelMap::drawMap(){
	for(int i = LEVEL_LENGTH - 1; i >= 0; i--){
		for(int k = 0; k < LEVEL_LENGTH; k++){
			if(block[i][k] != NULL)
				block[i][k]->draw(i, k);		
		}
	}
	update = false;
}
