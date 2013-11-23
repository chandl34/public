#include "World.h"

Coordinate*** World::coordinate;
Direction** World::direction;
vector<Character*> World::character;
LevelMap*** World::levelMap;
CharacterModelContainer* World::cmc;
MapModelContainer* World::mmc;
Pathing* World::pathing;

const int World::HEIGHT = 16, World::WIDTH = 16;

Character* World::sChar;
int* World::sMap;

World::World(){
	sChar = NULL;
	sMap = new int[2];
	sMap[X] = 0; sMap[Y] = 0;
	
	coordinate = new Coordinate**[LEVEL_LENGTH];
	for(int i = 0; i < LEVEL_LENGTH; i++){
		coordinate[i] = new Coordinate*[LEVEL_LENGTH];
		for(int k = 0; k < LEVEL_LENGTH; k++){
			if(i + k > LEVEL_OFFSET && i + k < LEVEL_LENGTH + 
					LEVEL_OFFSET && abs(i - k) < LEVEL_OFFSET)
				coordinate[i][k] = new Coordinate(i, k);
			else
				coordinate[i][k] = NULL;
		}
	}	

	direction = new Direction*[8];
	direction[DIR_LEFT] = new Direction(DIR_LEFT, -1, 0, 0, 1);	
	direction[DIR_FRONT_LEFT] = new Direction(DIR_FRONT_LEFT, -1, 1, -M_SQRT1_2, M_SQRT1_2);	
	direction[DIR_FRONT] = new Direction(DIR_FRONT, 0, 1, -1, 0);
	direction[DIR_FRONT_RIGHT] = new Direction(DIR_FRONT_RIGHT, 1, 1, -M_SQRT1_2, -M_SQRT1_2);
	direction[DIR_RIGHT] = new Direction(DIR_RIGHT, 1, 0, 0, -1);
	direction[DIR_BACK_RIGHT] = new Direction(DIR_BACK_RIGHT, 1, -1, M_SQRT1_2, -M_SQRT1_2);
	direction[DIR_BACK] = new Direction(DIR_BACK, 0, -1, 1, 0);
	direction[DIR_BACK_LEFT] = new Direction(DIR_BACK_LEFT, -1, -1, M_SQRT1_2, M_SQRT1_2);
	
	cmc = new CharacterModelContainer();
	Data::load(*cmc, "data/characters.ccs");
	mmc = new MapModelContainer();
	Data::load(*mmc, "data/mapModels.mmc");
	
	pathing = new Pathing();	
	
	levelMap = new LevelMap**[WIDTH];
	for(int i = 0; i < WIDTH; i++){
		levelMap[i] = new LevelMap*[HEIGHT];
		for(int j = 0; j < HEIGHT; j++)
			levelMap[i][j] = NULL;
	}
	
	// JUNK BELOW
	levelMap[sMap[X]][sMap[Y]] = new LevelMap();
	Data::load(*levelMap[sMap[X]][sMap[Y]], "data/maps/map01.map");
	addChar(new Character(MALE, 0, PLAYER));
	addChar(new Character(MALE, 2, ENEMY));
	addChar(new Character(MALE, 1, NPC));
	addChar(new Character(MALE, 2, PLAYER));
	addChar(new Character(MALE, 0, ENEMY));
	getSelectedMap()->addCharacter(getChar(0), getCoord(65, 85));
	getSelectedMap()->addCharacter(getChar(1), getCoord(72, 75));
	getSelectedMap()->addCharacter(getChar(2), getCoord(62, 81));
	getSelectedMap()->addCharacter(getChar(3), getCoord(71, 70));
	getSelectedMap()->addCharacter(getChar(4), getCoord(65, 70));
	getSelectedMap()->clearVision(INVISIBLE, true);
}

World::~World(){
	delete pathing;
	delete cmc;
	delete mmc;
	delete [] sMap;	
	
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++)
			delete levelMap[i][j];
		delete [] levelMap[i];
	}
	delete [] levelMap;
	
	for(int i = 0; i < LEVEL_LENGTH; i++){
		for(int k = 0; k < LEVEL_LENGTH; k++){
			if(coordinate[i][k] != NULL)
				delete coordinate[i][k];
		}
		delete [] coordinate[i];
	}		
	delete [] coordinate;
	
	for(size_t i = 0; i < 8; i++)
		delete direction[i];
	delete [] direction;
	
	for(size_t i = 0; i < character.size(); i++)
		delete character.at(i);	
}

Coordinate* World::getCoord(int x, int y){
	if(x >= 0 && x < LEVEL_LENGTH && y >= 0 && y < LEVEL_LENGTH)
		return coordinate[x][y];
	return NULL;
}

Direction* World::getDir(int i){return direction[i];}

Direction* World::getDir(int dx, int dy){
	if(dx == -1){
		if(dy == -1)
			return direction[DIR_BACK_LEFT];
		else if(dy == 0)
			return direction[DIR_LEFT];
		else if(dy == 1)
			return direction[DIR_FRONT_LEFT];
	}
	else if(dx == 0){
		if(dy == -1)
			return direction[DIR_BACK];
		else if(dy == 1)
			return direction[DIR_FRONT];
	}
	else if(dx == 1){
		if(dy == -1)
			return direction[DIR_BACK_RIGHT];
		else if(dy == 0)
			return direction[DIR_RIGHT];
		else if(dy == 1)
			return direction[DIR_FRONT_RIGHT];
	}
	return NULL;
}

void World::selectChar(Character* c){sChar = c;}
Character* World::getSelectedChar(){return sChar;}

Character* World::getChar(size_t i){
	if(i < character.size())
		return character.at(i);
	return NULL;
}

void World::addChar(Character* c){
	character.push_back(c);
	if(sChar == NULL)
		sChar = c;
}

LevelMap* World::getMap(int x, int y){
	if(x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return NULL;
	return levelMap[x][y];	
}

LevelMap* World::getSelectedMap(){
	return getMap(sMap[X], sMap[Y]);
}

Pathing* World::getPathing(){
	return pathing;
}
