#ifndef BLOCK_H_
#define BLOCK_H_

#include <boost/serialization/utility.hpp>
#include "LevelMap.h"
#include "sections/Object.h"
#include "sections/Ground.h"
#include "sections/Wall.h"
#include "../containers/MapModelContainer.h"

class Block{
public:
	Block();
	virtual ~Block();
	void init();
	void load();
	
	void draw(int, int);

	void addGround();
	void addDebris();
	void addGrass();
	void addWall();
	void addObject();
	void addFence();
	void addWindow();
	void addDoor();
	void clear();
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & object;
		ar & ground;
		for(int i = 0; i < 2; i++)
			ar & wall[i];
	}
	
	Wall** wall;
	Object* object;
	Ground* ground;
		
};


#endif /*BLOCK_H_*/
