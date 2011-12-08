#ifndef BLOCK_H_
#define BLOCK_H_

class Wall;

#include "sections/Object.h"
#include "sections/Ground.h"
#include "sections/Wall.h"

class Block{
public:
	Block();
	virtual ~Block();
	void load(Coordinate*, map<int, Selection*>&);

	Coordinate* getCoord(){return coord;}	
	void setCharacter(Character* c){character = c;}
	Character* getCharacter(){return character;}
	Wall* getWall(int i);
	Object* getObject();
	
	bool accessible(){return object->accessible();}
	bool jumpable();
	bool jumpable(int);
	bool passable(int);
	
	void toggleDoor(DoorModel*);
	void draw(int, int, int, int);
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & object;
		ar & ground;
		for(int i = 0; i < 2; i++)
			ar & wall[i];
	}

	void incrBlockingDoor(bool, DoorModel*);
	
	Wall** wall;
	Object* object;
	Ground* ground;
	Coordinate* coord;
	Character* character;
	
};


#endif /*BLOCK_H_*/
