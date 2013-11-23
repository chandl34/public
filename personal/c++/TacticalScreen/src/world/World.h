#ifndef WORLD_H_
#define WORLD_H_

#include "../io/Data.h"

class World{	
public:
	World();
	virtual ~World();

	static Coordinate* getCoord(int, int);
	
	static Direction* getDir(int);
	static Direction* getDir(int, int);
	
	static void selectChar(Character*);
	static Character* getChar(size_t);
	static Character* getSelectedChar();
	
	static void addChar(Character*);	
	static LevelMap* getMap(int, int);
	static LevelMap* getSelectedMap();
	static Pathing* getPathing();

private:
	const static int HEIGHT, WIDTH;
	
	static int* sMap;
	static Character* sChar;
	
	static Coordinate*** coordinate;
	static Direction** direction;
	static vector<Character*> character;
	static LevelMap*** levelMap;
	static CharacterModelContainer* cmc;
	static MapModelContainer* mmc;
	static Pathing* pathing;
};

#endif /*WORLD_H_*/
